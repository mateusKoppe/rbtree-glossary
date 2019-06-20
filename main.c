#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

/* TREE */
void _node_initialize (node *new_node, rb_tree *tree, node *parent, int key);
void _rbt_insert_fixup(rb_tree *t, node *z);;

int rbt_initialize (rb_tree *tree) {
  node *nil = malloc(sizeof(node));
  nil->color = BLACK;
  tree->nil = nil;
  tree->root = nil;
  return 1;
}

void _rbt_print(rb_tree *t, node *x) {
  if (x == t->nil) return;
  printf("%d  color: %d \n", x->value, x->color);
  if (x->left != t->nil) {
    printf("%d left: ", x->value);
    _rbt_print(t, x->left);
  }
  if (x->right != t->nil) {
    printf("%d right: ", x->value);
    _rbt_print(t, x->right);
  }
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

  _rbt_insert_fixup(tree, new_node);

  return 1;
}


void left_rotate(rb_tree *t, node *x) {
  node *y = x->right;
  x->right = y->left;
  if (x->left != t->nil) x->left->parent = x;
  y->parent = x->parent;
  if (x->parent == t->nil) t->root = y;
  else if (x == x->parent->left) x->parent->left = y;
  else x->parent->right = y;
  y->left = x;
  x->parent = y;
}

void right_rotate(rb_tree *t, node *x) {
  node *y = x->left;
  x->left = y->right;
  if (x->right != t->nil) x->right->parent = x;
  y->parent = x->parent;
  if (x->parent == t->nil) t->root = y;
  else if (x == x->parent->right) x->parent->right = y;
  else x->parent->left = y;
  y->right = x;
  x->parent = y;
}

void _rbt_insert_fixup(rb_tree *t, node *z) {
  node *y;
  while (z->parent->color == RED) {
    if (z->parent == t->nil
      || z->parent->parent == t->nil
    ) {
      break;
    }
    if (z->parent == z->parent->parent->left) {
      y = z->parent->parent->right;
      /* Case 1 */
      if (y->color == RED) {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        /* Case 2 */
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        /* Case 3 */
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        right_rotate(t, z->parent->parent);
      }
    } else {
      y = z->parent->parent->left;
      /* Case 1 */
      if (y->color == RED) {
        z->parent->color = y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        /* Case 2 */
        if (z == z->parent->left) {
          z = z->parent;
          right_rotate(t, z);
        }
        /* Case 3 */
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        left_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = BLACK;
}

void _node_initialize (node *new_node, rb_tree *tree, node *parent, int key) {
  new_node->parent = parent;
  new_node->value = key;
  new_node->left = tree->nil;
  new_node->right = tree->nil;
  new_node->color = RED;
}

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


  _rbt_print(&tree, tree.root);

  return 0;
}
