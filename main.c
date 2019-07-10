#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree/rbtree.h"
#include "cmdtool/cmdtool.h"
#include "helpers/helpers.h"

void show_help() {
  printf("\n");
  printf("> i <word> <description>  Add the word and it's description\n");
  printf("> e <word>                Erase the word and it's descriptions\n");
  printf("> e <word> <description>  Erase the word's description\n");
  printf("> q <word>                List words and it's descriptions\n");
  printf("> p                       List all words and descriptions\n");
  printf("> h                       Help\n");
}

int main(void) {
  printf("------------------------------\n");
  printf("-          Glosary           -\n");
  printf("------------------------------\n");
  printf("Enter h to see all the comands\n");

  rb_tree tree;
  rbt_initialize(&tree);

  cmdstatus cmd;
  cmdtool_initialize(&cmd);

  char input;
  char *action = malloc(0);
  char *word = malloc(0);
  char *param = malloc(0);

  while (scanf("%c", &input) != EOF) {
    cmdtool_handle(&cmd, input);

    if (cmd.is_digesting) continue;

    if (cmd.actual_param_key == 0) {
      param = realloc(param, sizeof(char*));
      strcpy(param, "");
      word = realloc(word, sizeof(char*));
      strcpy(word, "");
      action = (char*) realloc(action, strlen(cmd.actual_param_value));
      strcpy(action, cmd.actual_param_value);

      if(cmdtool_is_param(&cmd, "p")) {
        rbt_list(&tree, tree.root, "");
      }

      if(cmdtool_is_param(&cmd, "t")) {
        rbt_print(&tree, tree.root, 0);
      }

      if(cmdtool_is_param(&cmd, "h")) {
        show_help();
      }
    }

    if (cmd.actual_param_key == 1) {
      word = realloc(word, sizeof(char*) * strlen(cmd.actual_param_value));
      strcpy(word, cmd.actual_param_value);

      if (strcmp(action, "q") == 0) {
        node *searched = rbt_search(&tree, word);
        rbt_query(&tree, searched, word);
      }

    }

    if (cmd.actual_param_key >= 2) {
      if (cmd.actual_param_key == 2) {
        param = realloc(param, sizeof(char*) * strlen(cmd.actual_param_value));
        strcpy(param, cmd.actual_param_value);
      } else {
        int param_str_size = sizeof(char*) * strlen(param);
        int value_str_size = sizeof(char*) * (strlen(cmd.actual_param_value) +1);
        param = realloc(param, param_str_size + value_str_size);
        strcat(param, " ");
        strcat(param, cmd.actual_param_value);
      }
    }

    if (cmd.is_command_ending) {
      if (strcmp(action, "i") == 0) {
        rbt_insert(&tree, word, param);
      }

      if (strcmp(action, "e") == 0) {
        if (cmd.actual_param_key == 1) {
          rbt_delete_word(&tree, word);
        }
        if (cmd.actual_param_key > 1) {
          rbt_delete_description(&tree, word, param);
        }
      }
    }
  }

  free(word);
  free(param);
  free(action);
  rbt_free(&tree); 

  return 0;
}
