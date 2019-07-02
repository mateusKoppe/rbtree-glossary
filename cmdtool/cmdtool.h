#ifndef _CMDToll
#define _CMDToll

#define KEY_ENTER 10
#define KEY_SPACE 32
#define CMDTOOL_STARTING 0;
#define CMDTOOL_RUNNING 1;
#define CMDTOOL_ENDING 1;

typedef struct {
  int is_digesting;
  int is_command_ending;
  int is_command_starting;
  int is_command_ready;
  int is_param_ending;
  int actual_param_key;
  int actual_param_size;
  char *actual_param_value;
} cmdstatus;

void cmdtool_initialize(cmdstatus *cmd);
void cmdtool_handle(cmdstatus *cmd, char input);
int cmdtool_is_param(cmdstatus *cmd, char value[]);

#endif
