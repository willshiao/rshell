#include <iostream>
#include <vector>
#include <cstring>
#include <iterator>
#include <boost/regex.hpp>

#include "header/Shell.h"
#include "header/Command.h"
#include "header/StatusCode.h"
#include "header/CommandConnector.h"
#include "header/AndConnector.h"
#include "header/OrConnector.h"

using namespace std;

Shell::Shell(vector<string> args) {
  if(args.size() < 1) return;
  #ifdef DEBUG
    cout << "Shell intialized with arguments: ";
    for(unsigned i = 0; i < args.size(); ++i) {
      cout << args.at(i) << ' ';
    }
    cout << endl;
  #endif
}

StatusCode Shell::run() {
  while(true) {
    string line;

    cout << "$ ";
    getline(cin, line);

    // Clear out comments
    size_t pos = line.find("#");
    line = line.substr(0, pos);
    if(line.size() == 0) continue;

    Base* cmd = parseCommand(line);
    cmd->eval();
  }
  return SUCCESS;
}

Base* Shell::parseCommand(string line) {
  boost::regex testRegex;
  testRegex.assign("\\[(.+?)\\]");
  vector<string> words;

  // Replace [test] shorthand with actual test command
  line = boost::regex_replace(line, testRegex, "test$1");

  // Split by spaces
  char *piece;
  char *cline = new char[line.size() + 1];
  strcpy(cline, line.c_str());
  piece = strtok(cline, " ");

  while(piece != nullptr) {
    words.push_back(string(piece));
    piece = strtok(nullptr, " ");
  }

  // Insert semicolons after commands
  for(auto it = words.begin(); it != words.end(); ++it) {
    if(it->size() > 0 && it->at(it->size() - 1) == ';') {
      while(it->size() > 0 && it->at(it->size() - 1) == ';') {
        *it = it->substr(0, it->size() - 1);
      }
      it = words.insert(it + 1, ";");
    }
  }

  #ifdef DEBUG
    cout << "Got words: ";
    for(unsigned i = 0; i < words.size(); ++i) {
      cout << words.at(i) << " ";
    }
    cout << endl;
  #endif

  // Clean up
  delete[] cline;
  delete[] piece;
  cline = nullptr;
  piece = nullptr;

  Base *left = nullptr,
    *mid = nullptr;
  vector<string> tempArgs;

  for(unsigned i = 0; i < words.size(); ++i) {
    string word = words.at(i);
    if(!isOperator(word)) {
      #ifdef DEBUG
        cout << "Adding " << word << " to argument list" << endl;
      #endif
      tempArgs.push_back(word);
    } else {  // Is an operator character
      if(left == nullptr) {
        left = new Command(tempArgs);
        tempArgs.clear();
      }
      vector<string> rightArgs;
      for(i += 1; i < words.size() && !isOperator(words.at(i)); ++i) {
        rightArgs.push_back(words.at(i));
      }
      --i;
      if(word == "||") {
        mid = new OrConnector(left, new Command(rightArgs));
      } else if(word == "&&") {
        mid = new AndConnector(left, new Command(rightArgs));
      } else {
        mid = new CommandConnector(left, new Command(rightArgs));
      }
      left = mid;
      mid = nullptr;
    }
  }
  #ifdef DEBUG
    cout << "tempArgs.size(): " << tempArgs.size() << endl;
  #endif
  if(left == nullptr) {
    // cout << "Creating command with 1st arg: " << tempArgs.at(0) << endl;
    left = new Command(tempArgs);
  }
  return left;
}

bool Shell::isOperator(const string &s) {
  return s == "||" || s == "&&" || s == ";";
}
