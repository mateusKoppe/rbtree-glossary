#include <stdio.h>
#include "rbtree.h"

int main(void) {
  rb_tree tree;
  rbt_initialize(&tree);
  rbt_insert(&tree, 10);
  rbt_insert(&tree, 5);
  rbt_insert(&tree, 15);
  rbt_insert(&tree, 2);
  rbt_insert(&tree, 4);
  return 0;
}
