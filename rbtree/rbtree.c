#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rbtree.h"

void _node_initialize (node *new_node, rb_tree *tree, node *parent, char *key, char *description) {
  new_node->parent = parent;
  new_node->value = malloc(string_length(key) * sizeof(char));
  strcpy(new_node->value, key);
  new_node->description = malloc(string_length(description) * sizeof(char));
  strcpy(new_node->description, description);
  new_node->left = tree->nil;
  new_node->right = tree->nil;
  new_node->color = RED;
}

node* _clone_node (node *n, node *clone_node) {
  n->parent = clone_node->parent;
  n->value = malloc(string_length(clone_node->value) * sizeof(char));
  strcpy(n->value, clone_node->value);
  n->description = malloc(string_length(clone_node->description) * sizeof(char));
  strcpy(n->description, clone_node->description);
  n->left = clone_node->left;
  n->right = clone_node->right;
  n->color = clone_node->color;
  return n;
}

int _is_node_on_left(rb_tree *t, node *n) {
  return n == n->parent->left;
}

int _is_node_on_right(rb_tree *t, node *n) {
  return n == n->parent->right;
}

void rbt_query(rb_tree *t, node *x, char *query) {
  if (x == t->nil) return;
  if (strcmp(x->value, query) != 0) return;
  
  printf("%s\n", x->description);
  if (x->left != t->nil) {
    rbt_query(t, x->left, query);
  }
  if (x->right != t->nil) {
    rbt_query(t, x->right, query);
  }
}

void rbt_print(rb_tree *t, node *x, int level) {
  if (x == t->nil) return;
  
  int i;
  for (i = 0; i < level; i++)
  {
    printf("-   ");
  }
  
  printf("%s %s%s%s\n",
    _is_node_on_left(t, x) ? "<"
      : _is_node_on_right(t, x) ? ">" : "*",
    x->color ? "[" : "(",
    x->value,
    x->color ? "]" : ")"
  );

  for (i = 0; i < level; i++)
  {
    printf("-   ");
  }

  printf("%s\n", x->description);

  if (x->right != t->nil) {
    rbt_print(t, x->right, level + 1);
  }
  if (x->left != t->nil) {
    rbt_print(t, x->left, level + 1);
  }
  if(level == 0) {
    printf("\n");
  }
}

void rbt_list(rb_tree *t, node *x, char *actual_word) {
  if (x == t->nil) return;
  rbt_list(t, x->left, x->value);
  if (strcmp(x->value, actual_word) != 0) {
    printf("-- %s -- %s\n", x->value, actual_word);
  }
  printf("%s: %s\n", x->value, x->description);
  rbt_list(t, x->right, x->value);
}

void rbt_delete_word(rb_tree *t, char *word) {
  node *fetch = rbt_search(t, word);
  while (fetch != t->nil) {
    rbt_delete(t, fetch);
    fetch = rbt_search(t, word);
  }
}

void rbt_delete_description(rb_tree *t, char *word, char *description) {
  node *fetch = rbt_search(t, word);
  while (
    fetch != t->nil
    && strcmp(word, fetch->value) == 0
    && strcmp(description, fetch->description) != 0
  ) {
    if (strcmp(description, fetch->description) < 0) { 
      fetch = fetch->left;
    }
    else {
      fetch = fetch->right;
    }
  }
  if (fetch == t->nil) return;
  rbt_delete(t, fetch);
}

void left_rotate(rb_tree *t, node *pivot) {
  node *child = pivot->right;
  pivot->right = child->left;
  if (pivot->right != t->nil) {
    pivot->right->parent = pivot;
  }
  child->parent = pivot->parent;
  if (pivot->parent == t->nil) {
    t->root = child;
  } else if (pivot == pivot->parent->left) {
    pivot->parent->left = child;
  } else {
    pivot->parent->right = child;
  }
  child->left = pivot;
  pivot->parent = child;
}

void right_rotate(rb_tree *t, node *pivot) {
  node *child = pivot->left;
  pivot->left = child->right;
  if (pivot->left != t->nil) {
    pivot->left->parent = pivot;
  }
  child->parent = pivot->parent;
  if (pivot->parent == t->nil) {
    t->root = child;
  } else if (pivot == pivot->parent->right) {
    pivot->parent->right = child;
  } else {
    pivot->parent->left = child;
  }
  child->right = pivot;
  pivot->parent = child;
}

void _delete_fixup (rb_tree *t, node *n) {
  while (n != t->root && n->color == BLACK) {
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
      else {
        if (x->right->color == BLACK) {
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
      }
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

node *rbt_search(rb_tree *t, char *key) {
  node *fetch_node = t->root;
  while (fetch_node != t->nil &&  strcmp(key, fetch_node->value) != 0) {
    if (strcmp(key, fetch_node->value) < 0) { 
      fetch_node = fetch_node->left;
    }
    else {
      fetch_node = fetch_node->right;
    }
  }
  return fetch_node;
}

int rbt_insert (rb_tree *tree, char *key, char *description) {
  node *new_node = malloc(sizeof(node));
  node *fetch_node = tree->root;
  node *backup_node = tree->nil;

  while (fetch_node != tree->nil) {
    backup_node = fetch_node;

    if (
      strcmp(key, backup_node->value) < 0
      || (
        (strcmp(key, backup_node->value) == 0)
        && (strcmp(description, backup_node->description) < 0)
      )
    ) {
      fetch_node = fetch_node->left;
    } else {
      fetch_node = fetch_node->right;
    }
  }

  _node_initialize(new_node, tree, backup_node, key, description);
  if (backup_node == tree->nil) {
    tree->root = new_node;
  } else if (
    strcmp(key, backup_node->value) < 0
    || (
      (strcmp(key, backup_node->value) == 0)
      && (strcmp(description, backup_node->description) < 0)
    )
  ) {
    backup_node->left = new_node;
  } else {
    backup_node->right = new_node;
  }

  _rbt_insert_fixup(tree, new_node);

  return 1;
}

void rbt_transplant (rb_tree *t, node *old_node, node *new_node) {
  if (old_node == t->nil || old_node == t->root) {
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
    if (y->parent == n) {
      x->parent = y;
    } else {
      rbt_transplant(t, y, y->right);
      y->right = n->right;
      y->right->parent = y;
    }
    rbt_transplant(t, n, y);
    if (n == t->root) {
      t->root = y;
    }
    y->left = n->left;
    y->left->parent = y;
    y->color = n->color;
  }
  if (y_original_color == BLACK) {
    _delete_fixup(t, x);
  }
  free(n);
}

void _rbtree_free(rb_tree *t, node *x) {
  if (x == t->nil) return;
  _rbtree_free(t, x->left);
  _rbtree_free(t, x->right);
  free(x);
}

void rbt_free(rb_tree *t) {
  _rbtree_free(t, t->root);
  free(t->nil);
}
