#ifndef RSHELL_BASE_H
#define RSHELL_BASE_H

#include "StatusCode.h"

class Base {
  virtual StatusCode eval() = 0;
};

#endif
