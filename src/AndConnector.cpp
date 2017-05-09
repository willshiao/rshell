#include "header/AndConnector.h"

using namespace std;

StatusCode AndConnector::eval() {
  if(left->eval() != SUCCESS) return SUCCESS;
  return right->eval();
}
