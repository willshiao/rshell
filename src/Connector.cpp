#include "header/Connector.h"

using namespace std;

bool Connector::isEmpty() {
  return left->isEmpty() && right->isEmpty();
}
