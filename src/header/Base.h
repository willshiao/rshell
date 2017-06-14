#ifndef RSHELL_BASE_H
#define RSHELL_BASE_H

#include "StatusCode.h"

class Base {
 public:
  std::string inputString;
  std::string outputString;
  bool shouldPrint = false;

  virtual StatusCode eval() = 0;
  virtual bool isEmpty() = 0;
};

#endif
