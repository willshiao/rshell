#include "header/AndConnector.h"

using namespace std;

StatusCode AndConnector::eval() {
  if(left->eval() != SUCCESS) return SUCCESS;
  right->eval();
  return SUCCESS;
}
