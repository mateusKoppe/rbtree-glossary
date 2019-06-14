#include <stdlib.h>
#include "rbtree.h"

int rbt_initialize (rb_tree *tree) {
  node *nil = malloc(sizeof(node));
  nil->color = BLACK;
  tree->nil = nil;
  return 1;
}

int rbt_insert (rb_tree *tree, int key) {
  node *new_node = malloc(sizeof(node));
  node *fetch_node = tree->root;
  node *backup_node = tree->nil;

  while (fetch_node != tree->nil) {
    backup_node = fetch_node;
    if (key < fetch_node->value) {
      fetch_node = fetch_node->left;
    } else {
      fetch_node = fetch_node->right;
    }
  }

  new_node->parent = backup_node;
  if (backup_node == tree->nil) {
    tree->root = new_node;
  } else if (key < backup_node->value) {
    backup_node->left = new_node;
  } else {
    backup_node->right = new_node;
  }

  return 1;
}

