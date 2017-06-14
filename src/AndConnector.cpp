#include "header/AndConnector.h"

using namespace std;

StatusCode AndConnector::eval() {
  left->shouldPrint = true;
  right->shouldPrint = true;
  if(left->eval() != SUCCESS) return COMMAND_ERROR;
  return right->eval();
}
