#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <iterator>
#include <stack>
#include <boost/regex.hpp>

#include "header/Base.h"
#include "header/Shell.h"
#include "header/Command.h"
#include "header/StatusCode.h"
#include "header/CommandConnector.h"
#include "header/AndConnector.h"
#include "header/OrConnector.h"

using namespace std;

Base* popOrNull(stack<Base*>& s) {
  Base* ret;
  if(!s.empty()) {
    ret = s.top();
    s.pop();
  } else {
    cout << "Invalid expression" << endl;
    ret = new NullCommand();
  }
  return ret;
}

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

  // Insert parentheses as seperate tokens
  for(auto it = words.begin(); it != words.end(); ++it) {
    if(it->size() > 1 && it->at(0) == '(') {
      *it = it->substr(1);
      it = words.insert(it, "(");
    } else if(it->size() > 1 && it->at(it->size() - 1) == ')') {
      int count = 0;
      for(; it->size() > 1 && it->at(it->size() - 1) == ')'; ++count) {
        *it = it->substr(0, it->size() - 1);
      }
      for(int i = 0; i < count; ++i) {
        it = words.insert(it + 1, ")");
      }
    }
  }

  #ifdef DEBUG
    cout << "Got words: ";
    for(unsigned i = 0; i < words.size(); ++i) {
      cout << words.at(i) << ", ";
    }
    cout << endl;
  #endif

  // Clean up
  delete[] cline;
  delete[] piece;
  cline = nullptr;
  piece = nullptr;

  vector<string> tempArgs;
  stack<string> operators;
  stack<Base*> operands;

  // Do actual parsing
  for(unsigned i = 0; i < words.size(); ++i) {
    string word = words.at(i);
    if(!isSymbol(word)) {
      #ifdef DEBUG
        cout << "Not a symbol: " << word << endl;
      #endif
      for(; i < words.size() && !isSymbol(words.at(i)); ++i) {
        tempArgs.push_back(words.at(i));
      }
      --i;
      operands.push(new Command(tempArgs));
      tempArgs.clear();
      continue;
    } else if(word == "(") {
      operators.push(word);
      continue;
    } else if(word == ")") {
      if(operators.empty()) cout << "Operators are empty!?" << endl;
      while(!operators.empty() && operators.top() != "(") {
        string op = operators.top();
        operators.pop();
        #ifdef DEBUG
          cout << "(1) Got operator: " << op << endl;
        #endif

        Base *right = popOrNull(operands);
        Base *left = popOrNull(operands);
        operands.push(applyOperator(op, left, right));
      }
      if(!operators.empty() && operators.top() == "(") operators.pop();
    } else if(isOperator(word)) {
      #ifdef DEBUG
        cout << "Current word is operator: " << word << endl;
      #endif
      while(!operators.empty() && operators.top() != "(") {
        string op = operators.top();
        operators.pop();
        #ifdef DEBUG
          cout << "(2) Got operator: " << op << endl;
        #endif

        Base *right = popOrNull(operands);
        Base *left = popOrNull(operands);
        operands.push(applyOperator(op, left, right));
      }
      operators.push(word);
    }
  }
  while(!operators.empty()) {
    string op = operators.top();
    #ifdef DEBUG
      cout << "(3) Got operator: " << op << endl;
    #endif
    operators.pop();
    if(isParens(op)) continue;

    Base *right = popOrNull(operands);
    Base *left = popOrNull(operands);
    operands.push(applyOperator(op, left, right));
  }

  if(!operators.empty()) {
    cout << "Messed up command" << endl;
  }
  return operands.top();
}

Base* Shell::applyOperator(const string& op, Base* left, Base* right) {
  if(!isOperator(op)) {
    cout << "Invalid operator: " << op << endl;
    return nullptr;
  }
  #ifdef DEBUG
    if(left == nullptr) cout << "Left operator side is null" << endl;
    if(right == nullptr) cout << "Left operator side is null" << endl;
  #endif
  if(op == "||") {
    #ifdef DEBUG
      cout << "Created new OrConnector" << endl;
    #endif
    return new OrConnector(left, right);
  } else if(op == "&&") {
    #ifdef DEBUG
      cout << "Created new AndConnector" << endl;
    #endif
    return new AndConnector(left, right);
  }
  #ifdef DEBUG
    cout << "Created new CommandConnector" << endl;
  #endif
  return new CommandConnector(left, right);
}

bool Shell::isOperator(const string &s) {
  return s == "||" || s == "&&" || s == ";";
}

bool Shell::isParens(const string &s) {
  return s == "(" || s == ")";
}

bool Shell::isSymbol(const string &s) {
  return Shell::isOperator(s) || Shell::isParens(s);
}
