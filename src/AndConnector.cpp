#include "header/AndConnector.h"

using namespace std;

StatusCode AndConnector::eval() {
  if(left->eval() != SUCCESS) return COMMAND_ERROR;
  return right->eval();
}
