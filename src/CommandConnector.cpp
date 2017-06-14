#include "header/CommandConnector.h"

using namespace std;

StatusCode CommandConnector::eval() {
  StatusCode s = SUCCESS;

  left->shouldPrint = true;
  left->eval();
  right->shouldPrint = true;
  if(!right->isEmpty()) s = right->eval();
  return s;
}
