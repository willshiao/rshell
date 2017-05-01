#ifndef RSHELL_OR_CONNECTOR_H
#define RSHELL_OR_CONNECTOR_H

#include <vector>
#include <string>
#include "Connector.h"

class OrConnector : public Connector {
 public:
  OrConnector(Base* l, Base* r) : Connector(l, r) {}
  virtual StatusCode eval();
};

#endif
