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
  static StatusCode runCommand(vector<string>& args);
  Command() {}
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

class NullCommand : public Command {
 public:
  NullCommand() {}
  explicit NullCommand(vector<string> a) : Command(a) {}
  virtual StatusCode eval() { return SUCCESS; }
  virtual bool isEmpty() { return true; }
};

class TestCommand : public Command {
 public:
  static StatusCode runCommand(vector<string>& args);
  explicit TestCommand(vector<string> a) : Command(a) { }
};

#endif
