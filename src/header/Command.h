#ifndef RSHELL_COMMAND_H
#define RSHELL_COMMAND_H

#include <vector>
#include <string>
#include <iostream>
#include "Base.h"

using namespace std;

class Command : public Base {
 private:
  vector<string> args;
  StatusCode runCommand(const vector<string>& args);
 public:
  explicit Command(vector<string> a) : args(a) {
    std::cout << "Command created with args: ";
    for(unsigned i = 0; i < a.size(); ++i) {
      cout << a.at(i) << " ";
    }
    cout << endl;
  }
  virtual StatusCode eval();
};

#endif
