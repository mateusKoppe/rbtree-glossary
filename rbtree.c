#include <stdlib.h>
#include "rbtree.h"

void _node_initialize (node *new_node, rb_tree *tree, node *parent, int key);

int rbt_initialize (rb_tree *tree) {
  node *nil = malloc(sizeof(node));
  nil->color = BLACK;
  tree->nil = nil;
  tree->root = nil;
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

  _node_initialize(new_node, tree, backup_node, key);
  if (backup_node == tree->nil) {
    tree->root = new_node;
  } else if (key < backup_node->value) {
    backup_node->left = new_node;
  } else {
    backup_node->right = new_node;
  }

  return 1;
}

void _node_initialize (node *new_node, rb_tree *tree, node *parent, int key) {
  new_node->parent = parent;
  new_node->value = key;
  new_node->left = tree->nil;
  new_node->right = tree->nil;
  new_node->color = RED;
}

