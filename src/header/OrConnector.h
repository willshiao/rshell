#ifndef RSHELL_OR_CONNECTOR_H
#define RSHELL_OR_CONNECTOR_H

#include <vector>
#include <string>
#include "Base.h"

class OrConnector : public Base {
 public:
  virtual StatusCode eval();
};

#endif
