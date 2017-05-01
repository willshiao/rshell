#ifndef RSHELL_COMMAND_CONNECTOR_H
#define RSHELL_COMMAND_CONNECTOR_H

#include <vector>
#include <string>
#include "Base.h"

class CommandConnector : public Base {
 public:
  virtual StatusCode eval();
};

#endif
