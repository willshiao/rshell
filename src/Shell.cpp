#include <iostream>
#include <vector>
#include <cstring>

#include "header/Shell.h"
#include "header/Command.h"
#include "header/StatusCode.h"

using namespace std;

Shell::Shell(vector<string> args) {
  if(args.size() < 1) return;
  cout << "Shell intialized with arguments: ";
  for(unsigned i = 0; i < args.size(); ++i) {
    cout << args.at(i) << ' ';
  }
  cout << endl;
}

StatusCode Shell::run() {
  while(true) {
    string line;
    vector<string> words;

    cout << "$ ";
    getline(cin, line);

    char *piece;
    char *cline = new char[line.size() + 1];
    strcpy(cline, line.c_str());
    piece = strtok(cline, " ");

    while(piece != nullptr) {
      words.push_back(string(piece));
      piece = strtok(nullptr, " ");
    }

    cout << "Got words: ";
    for(unsigned i = 0; i < words.size(); ++i) {
      cout << words.at(i) << " ";
    }
    cout << endl;
    // Clean up
    delete[] cline;
    delete[] piece;
    cline = nullptr;
    piece = nullptr;

    Command c(words);
    c.eval();
  }
  return SUCCESS;
}
