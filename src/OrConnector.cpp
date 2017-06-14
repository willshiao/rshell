#include "header/OrConnector.h"

using namespace std;

StatusCode OrConnector::eval() {
  left->shouldPrint = true;
  if(left->eval() == SUCCESS) return SUCCESS;
  right->shouldPrint = true;
  return right->eval();
}
