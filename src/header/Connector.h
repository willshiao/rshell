#ifndef RSHELL_CONNECTOR_H
#define RSHELL_CONNECTOR_H

#include <vector>
#include <string>
#include "Base.h"

class Connector : public Base {
 private:
  Base* left;
  Base* right;
 public:
  virtual StatusCode eval();
};

#endif
