#ifndef _RBTREE
#define _RBTREE

#define BLACK 0
#define RED 1

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
node *rbt_search(rb_tree *t, int key);
void rbt_delete(rb_tree *t, node *n);
void rbt_print(rb_tree *t, node *x, int level);

#endif
