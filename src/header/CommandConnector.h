#ifndef RSHELL_COMMAND_CONNECTOR_H
#define RSHELL_COMMAND_CONNECTOR_H

#include <vector>
#include <string>
#include "Connector.h"

class CommandConnector : public Connector {
 public:
  CommandConnector(Base* l, Base* r) : Connector(l, r) {}
  virtual StatusCode eval();
};

#endif
