#include "header/CommandConnector.h"

using namespace std;

StatusCode CommandConnector::eval() {
  left->eval();
  right->eval();
  return SUCCESS;
}
