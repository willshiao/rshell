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
  Connector(Base* l, Base* r) : left(l), right(r) {}
  virtual StatusCode eval() = 0;
};

#endif
