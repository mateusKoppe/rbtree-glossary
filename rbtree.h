#ifndef _RBTREE
#define _RBTREE

#define BLACK 0
#define RED 0

typedef struct Node {
  int value;
  int color;
  struct Node *parent, *right, *left;
} node;

typedef struct {
  node *root, *nil;
} rb_tree;

int rbt_initialize (rb_tree *t);
int rbt_insert (rb_tree *t, int key);

#endif
