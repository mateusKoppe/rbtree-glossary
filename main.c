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
  char *action = malloc(0);
  while (scanf("%c", &input) != EOF) {
    cmdtool_handle(&cmd, input);

    if (cmd.is_digesting) continue;

    if (cmd.actual_param_key == 0) {
      strcpy(action, cmd.actual_param_value);

      if(cmdtool_is_param(&cmd, "p")) {
        rbt_print(&tree, tree.root, 0);
      }
    }

    if (cmd.actual_param_key == 1) {
      if (strcmp(action, "i") == 0) {
        int key = (int) strtol(cmd.actual_param_value, NULL, 10);
        rbt_insert(&tree, key);
      }

      if (strcmp(action, "e") == 0) {
        int key = (int) strtol(cmd.actual_param_value, NULL, 10);
        rbt_delete(&tree, rbt_search(&tree, key));
      }
    }

  }

  return 0;
}
