#include <iostream>
#include "header/PipeConnector.h"

using namespace std;

StatusCode PipeConnector::eval() {
  StatusCode s = SUCCESS;

  left->eval();
  #ifdef DEBUG
    cout << "Output of left side: " << left->outputString << endl;
  #endif
  right->inputString = left->outputString;
  right->eval();
  this->outputString = right->outputString;

  if(this->shouldPrint) {
    cout << this->outputString;
  }

  return s;
}
