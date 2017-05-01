#ifndef RSHELL_SHELL_H
#define RSHELL_SHELL_H

#include <string>
#include <vector>
#include "Base.h"

class Shell {
 public:
  explicit Shell(std::vector<std::string> args);
  virtual StatusCode run();
};

#endif
