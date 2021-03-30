#include "linked_list.h"
#include <stdlib.h>

int main() {

  structures::LinkedList<int> list{};

  for (auto i = 9; i >= 0; --i) {
      list.insert_sorted(i);
  }
  for (auto i = 0; i < 10; ++i) {
      list.pop_back();
  }
  list.clear();

  list.insert_sorted(10);
  list.insert_sorted(-10);
  list.insert_sorted(42);
  list.insert_sorted(0);

  return 0;
}