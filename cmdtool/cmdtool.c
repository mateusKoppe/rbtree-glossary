#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmdtool.h"

char input;
int stage = 0;
int cycle = 0;

void cmdtool_initialize(cmdstatus *cmd) {
  cmd->is_command_ending = 0;
  cmd->is_command_starting = 0;
  cmd->is_command_ready = 0;
  cmd->is_digesting = 0;
  cmd->actual_param_size = 0;
  cmd->actual_param_key = 0;
  cmd->is_param_ending = 0;
  cmd->actual_param_value = (char *) malloc(0);
}

int cmdtool_is_param(cmdstatus *cmd, char value[]) {
  return strcmp(cmd->actual_param_value, value) == 0;
}

void cmdtool_restart(cmdstatus *cmd) {
  free(cmd->actual_param_value);
  cmdtool_initialize(cmd);
  cmd->is_digesting = 1;
  cmd->is_command_starting = 1;
}

void cmdtool_restart_param(cmdstatus *cmd) {
  free(cmd->actual_param_value);
  cmd->is_param_ending = 0;
  cmd->actual_param_size = 0;
  cmd->actual_param_value = (char *) malloc(0);
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
    cmd->actual_param_size++;
    cmd->actual_param_value = realloc(
      cmd->actual_param_value,
      sizeof (char*) * cmd->actual_param_size
    );
    cmd->actual_param_value[cmd->actual_param_size-1] = input;
  }
}