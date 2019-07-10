#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmdtool.h"

char input;
int stage = 0;
int cycle = 0;

void cmdtool_reset_values(cmdstatus *cmd) {
  cmd->is_command_ending = 0;
  cmd->is_command_starting = 0;
  cmd->is_command_ready = 0;
  cmd->is_digesting = 0;
  cmd->actual_param_key = 0;
  cmd->is_param_ending = 0;
}

void cmdtool_initialize(cmdstatus *cmd) {
  cmdtool_reset_values(cmd);
  cmd->actual_param_value = (char *) malloc(0);
}

int cmdtool_is_param(cmdstatus *cmd, char value[]) {
  return strcmp(cmd->actual_param_value, value) == 0;
}

void cmdtool_restart(cmdstatus *cmd) {
  cmdtool_reset_values(cmd);
  free(cmd->actual_param_value);
  cmd->actual_param_value = (char *) malloc(0);
  cmd->is_digesting = 1;
  cmd->is_command_starting = 1;
}

void cmdtool_restart_param(cmdstatus *cmd) {
  cmd->is_param_ending = 0;
  cmd->actual_param_value = (char *) malloc(sizeof(char*));
  strcpy(cmd->actual_param_value, "");
}

void cmdtool_handle (cmdstatus *cmd, char input) {
  cmd->is_digesting = 1;

  if (cmd->is_command_ending) {
    cmdtool_restart(cmd);
  }

  if (cmd->is_param_ending) {
    cmdtool_restart_param(cmd);
    cmd->actual_param_key++;
  }
  
  if (input == KEY_ENTER) {
    cmd->is_command_ending = 1;
    cmd->is_digesting = 0;
  }

  if (input == KEY_SPACE) {
    cmd->is_digesting = 0;
    cmd->is_param_ending = 1;
  }

  if (cmd->is_digesting) {
    cmd->actual_param_value = (char*) realloc(
      cmd->actual_param_value,
      sizeof (char*) * (strlen(cmd->actual_param_value) + 1)
    );
    char to_concat[] = {input};
    strcat(cmd->actual_param_value, to_concat);
  }
}
