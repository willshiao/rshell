#ifndef RSHELL_INPUT_REDIRECTOR_H
#define RSHELL_INPUT_REDIRECTOR_H

#include <vector>
#include <string>
#include "Connector.h"

class InputRedirector : public Connector {
 public:
  InputRedirector(Base* l, Base* r) : Connector(l, r) {}
  virtual StatusCode eval();
};

#endif
