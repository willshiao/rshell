#include "header/OrConnector.h"

using namespace std;

StatusCode OrConnector::eval() {
  if(left->eval() == SUCCESS) return SUCCESS;
  right->eval();
  return SUCCESS;
}
