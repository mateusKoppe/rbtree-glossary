#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree/rbtree.h"
#include "cmdtool/cmdtool.h"

/* MAIN */

int main(void) {
  rb_tree tree;
  rbt_initialize(&tree);

  cmdstatus cmd;
  cmdtool_initialize(&cmd);

  char input;
  char *action;
  while (scanf("%c", &input) != EOF) {
    cmdtool_handle(&cmd, input);

    if (cmd.is_digesting) continue;

    printf("here v:%s k:%d\n", cmd.actual_param_value, cmd.actual_param_key);

    if (cmd.actual_param_key == 0) {
      action = cmd.actual_param_value;

      if(cmdtool_is_param(&cmd, "p")) {
        printf("Print\n");
      }

      if(cmdtool_is_param(&cmd, "i")) {
        printf("Insert\n");
      }
    }

  }

  /*
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

  case 'p':
    if (cycle == 0) {
      _rbt_print(&tree, tree.root, 0);
    }
    break;

  case 'e':
    if (cycle == 0) {
      _rbt_print(&tree, tree.root, 0);
    }
    break;

  default:
    action = NULL;
  }
 */
  return 0;
}
