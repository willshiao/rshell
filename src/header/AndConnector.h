#ifndef RSHELL_AND_CONNECTOR_H
#define RSHELL_AND_CONNECTOR_H

#include <vector>
#include <string>
#include "Base.h"

class AndConnector : public Base {
 public:
  virtual StatusCode eval();
};

#endif
