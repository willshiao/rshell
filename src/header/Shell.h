#ifndef RSHELL_SHELL_H
#define RSHELL_SHELL_H

#include <string>
#include <vector>
#include "Base.h"

class Shell {
 private:
  Base* parseCommand(std::string line);
 public:
  explicit Shell(std::vector<std::string> args);
  virtual StatusCode run();
  static bool isOperator(const std::string &s);
};

#endif
