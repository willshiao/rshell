#ifndef RSHELL_COMMAND_H
#define RSHELL_COMMAND_H

#include <vector>
#include <string>
#include <iostream>
#include "Base.h"

using namespace std;

class Command : public Base {
 protected:
  vector<string> args;
 public:
  static StatusCode runCommand(const vector<string>& args);
  explicit Command(vector<string> a) : args(a) {
    #ifdef DEBUG
      cout << "New command created with args: ";
      for(auto str : a) {
        cout << str << " ";
      }
      cout << endl;
    #endif
  }
  virtual StatusCode eval();
  virtual bool isEmpty();
};

class TestCommand : public Command {
 public:
  static StatusCode runCommand(const vector<string>& args);
  explicit TestCommand(vector<string> a) : Command(a) { }
};

#endif
