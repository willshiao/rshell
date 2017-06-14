#ifndef RSHELL_PIPE_CONNECTOR_H
#define RSHELL_PIPE_CONNECTOR_H

#include <vector>
#include <string>
#include "Connector.h"

class PipeConnector : public Connector {
 public:
  PipeConnector(Base* l, Base* r) : Connector(l, r) {}
  virtual StatusCode eval();
};

#endif
