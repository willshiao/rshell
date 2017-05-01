#ifndef RSHELL_AND_CONNECTOR_H
#define RSHELL_AND_CONNECTOR_H

#include <vector>
#include <string>
#include "Connector.h"

class AndConnector : public Connector {
 public:
  AndConnector(Base* l, Base* r) : Connector(l, r) {}
  virtual StatusCode eval();
};

#endif
