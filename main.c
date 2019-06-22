#include <stdio.h>
#include <stdlib.h>
#include "rbtree/rbtree.h"

const KEY_ENTER = 10;
const KEY_SPACE = 32;

/* MAIN */

int main(void) {
  char input;
  char action = NULL;
  int stage = 0;
  int cycle = 0;

  rb_tree tree;
  rbt_initialize(&tree);

  char *param;
  int param_size;
  int key;
  while (scanf("%c", &input) != EOF) {
    cycle = 1;
    if (!action) {
      action = input;
      stage = 0;
      cycle = 0;
    }
    if (input == KEY_ENTER) {
      cycle = 2;
    }
    if (input == KEY_SPACE) {
      stage++;
      continue;
    }
    switch (action) {
    case 'i':
      if (input == KEY_ENTER) {
        stage++;
      }
      if (cycle == 0) {
        param_size = 0;
        param = (char *) malloc(0);
      } else if (cycle == 1) {
        param_size++;
        param = realloc(param, sizeof (char*) * param_size);
        param[param_size-1] = input;
      } else if (cycle == 2) {
        key = (int) strtol(param, NULL, 10);
        rbt_insert(&tree, key);
        free(param);
      }
      break;

    default:
      action = NULL;
    }

    if (input == KEY_ENTER) {
      action = NULL;
    }
  }

  return 0;
}
