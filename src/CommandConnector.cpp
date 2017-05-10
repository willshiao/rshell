#include "header/CommandConnector.h"

using namespace std;

StatusCode CommandConnector::eval() {
  left->eval();
  if(!right->isEmpty()) right->eval();
  return SUCCESS;
}
