#ifndef RSHELL_COMMAND_H
#define RSHELL_COMMAND_H

#include <vector>
#include <string>
#include "Base.h"

class Command : public Base {
 private:
  std::vector<std::string> args;
  StatusCode runCommand(std::string path, const std::vector<std::string>& args);
 public:
  virtual StatusCode eval();
};

#endif
