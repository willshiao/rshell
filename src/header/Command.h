#ifndef RSHELL_COMMAND_H
#define RSHELL_COMMAND_H

#include <vector>
#include <string>
#include "Base.h"

using namespace std;

class Command : public Base {
 private:
  vector<string> args;
  StatusCode runCommand(const vector<string>& args);
 public:
  explicit Command(vector<string> a) : args(a) {}
  virtual StatusCode eval();
};

#endif
