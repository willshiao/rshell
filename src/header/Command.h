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
  StatusCode runCommand(const vector<string>& args);
 public:
  explicit Command(vector<string> a) : args(a) { }
  virtual StatusCode eval();
  virtual bool isEmpty();
};

class TestCommand : public Command {
 protected:
  StatusCode runCommand(const vector<string>& args);
 public:
  explicit TestCommand(vector<string> a) : Command(a) { }
};

#endif
