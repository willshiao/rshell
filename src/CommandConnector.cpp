#include "header/CommandConnector.h"

using namespace std;

StatusCode CommandConnector::eval() {
  StatusCode s = SUCCESS;

  left->eval();
  if(!right->isEmpty()) s = right->eval();
  return s;
}
