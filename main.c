#include <stdio.h>
#include <stdlib.h>
#include "rbtree/rbtree.h"

/* MAIN */

int main(void) {
  rb_tree tree;
  rbt_initialize(&tree);
  rbt_insert(&tree, 10);
  rbt_insert(&tree, 29);
  rbt_insert(&tree, 21);
  rbt_insert(&tree, 5);
  rbt_insert(&tree, 15);
  rbt_insert(&tree, 2);
  rbt_insert(&tree, 17);
  rbt_insert(&tree, 4);
  rbt_insert(&tree, 19);
  rbt_insert(&tree, 3);
  rbt_insert(&tree, 6);
  rbt_insert(&tree, 7);

  _rbt_print(&tree, tree.root, 0);

  node *searched_node = rbt_search(&tree, 17);
  printf("Search de node has key: %d and color: %s \n",
    searched_node->value,
    searched_node->color ? "red" : "black"
  );

  node *delete_node = rbt_search(&tree, 10);
  rbt_delete(&tree, delete_node);

  _rbt_print(&tree, tree.root, 0);


  return 0;
}
