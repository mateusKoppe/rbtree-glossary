#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

/* TREE */
void _rbt_insert_fixup(rb_tree *t, node *z);

void _node_initialize (node *new_node, rb_tree *tree, node *parent, int key) {
  new_node->parent = parent;
  new_node->value = key;
  new_node->left = tree->nil;
  new_node->right = tree->nil;
  new_node->color = RED;
}

node* _clone_node (node *n, node *clone_node) {
  n->parent = clone_node->parent;
  n->value = clone_node->value;
  n->left = clone_node->left;
  n->right = clone_node->right;
  n->color = clone_node->color;
  return n;
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

void _delete_fixup (rb_tree *t, node *n) {
  while (n != t->nil && n->color == BLACK) {
    if (n == n->parent->left) {
      node *x = n->parent->right;
      if (x->color == RED) {
        x->color = BLACK;
        n->parent->color = RED;
        left_rotate(t, n->parent);
        x = n->parent->right;
      }
      if (x->left->color == BLACK && x->right->color == BLACK) {
        x->color = RED;
        n = x->parent;
      }
      else if (x->right->color == BLACK) {
        x->left->color = BLACK;
        x->color = RED;
        right_rotate(t, x);
        x = n->parent->right;
      }
      x->color = n->parent->color;
      n->parent->color = BLACK;
      x->right->color = BLACK;
      left_rotate(t, n->parent);
      n = t->root;
    } else {
      node *x = n->parent->left;
      if (x->color == RED) {
        x->color = BLACK;
        n->parent->color = RED;
        right_rotate(t, n->parent);
        x = n->parent->left;
      }
      if (x->right->color == BLACK && x->left->color == BLACK) {
        x->color = RED;
        n = x->parent;
      }
      else if (x->left->color == BLACK) {
        x->right->color = BLACK;
        x->color = RED;
        left_rotate(t, x);
        x = n->parent->left;
      }
      x->color = n->parent->color;
      n->parent->color = BLACK;
      x->left->color = BLACK;
      right_rotate(t, n->parent);
      n = t->root;
    }
  }
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

int _is_node_on_left(rb_tree *t, node *n) {
  return n == n->parent->left;
}

int _is_node_on_right(rb_tree *t, node *n) {
  return n == n->parent->right;
}

node *rbt_search(rb_tree *t, int key) {
  node *fetch_node = t->root;
  while (fetch_node != t->nil && fetch_node->value != key) {
    if (key < fetch_node->value) { 
      fetch_node = fetch_node->left;
    }
    else {
      fetch_node = fetch_node->right;
    }
  }
  return fetch_node;
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

void rbt_transplant (rb_tree *t, node *old_node, node *new_node) {
  if (old_node == t->nil) {
    t->root = new_node;
  } else if (_is_node_on_left(t, old_node)) {
    old_node->parent->left = new_node;
  } else {
    old_node->parent->right = new_node;
  }
  new_node->parent = old_node->parent;
}

node* rbt_minimum(rb_tree *t, node *n) {
  node *fetch_node = malloc(sizeof(node));
  _clone_node(fetch_node, n);
  while (fetch_node->left != t->nil) {
    fetch_node = fetch_node->left;
  }
  return fetch_node;
}

node* rbt_maximum(rb_tree *t, node *n) {
  node *fetch_node = malloc(sizeof(node));
  _clone_node(fetch_node, n);
  while (fetch_node->right != t->nil) {
    fetch_node = fetch_node->right;
  }
  return fetch_node;
}

void rbt_delete(rb_tree *t, node *n) {
  node *y = malloc(sizeof(node));
  node *x;
  int y_original_color = y->color;
  y = _clone_node(y, n);
	if (n->left == t->nil) {
    x = n->right;
    rbt_transplant(t, n, n->right);
  } else if (n->right == t->nil) {
    x = n->left;
    rbt_transplant(t, n, n->left);
  } else {
    node *y = rbt_minimum(t, n->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent != n) {
      printf("I'm here\n");
      printf("Node is 15 right?\n");
      printf("%s! %d\n", y->value == 15 ? "yeap" : "nope", y->value);
      rbt_transplant(t, y, y->right);
      printf("Still 15?\n");
      printf("%s! %d\n", y->value == 15 ? "yeap" : "nope", y->value);
      y->right = n->right;
      y->right->parent = y;
    }
    rbt_transplant(t, n, y);
    printf("What now? 15?\n");
    printf("%s! %d\n", y->value == 15 ? "yeap" : "nope", y->value);
    y->left = n->left;
    y->left->parent = y;
    y->color = n->color;
  }
  if (y_original_color == BLACK) {
    printf("Wtf is x now?\n");
    printf("it is %d?\n", x->value);
    _delete_fixup(t, x);
  }
	free(n);
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


  printf("with 10 \n ");

  _rbt_print(&tree, tree.root);

  printf("\n");

  node *delete_node = rbt_search(&tree, 10);
  rbt_delete(&tree, delete_node);

  printf("without 10 \n ");

  _rbt_print(&tree, tree.root);

  node *searched_node = rbt_search(&tree, 17);
  printf("Search de node has key: %d and color: %s \n",
    searched_node->value,
    searched_node->color ? "red" : "black"
  );

  return 0;
}
