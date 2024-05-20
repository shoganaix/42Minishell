#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


void    pipe_manager(char *input);
int     main(int argc, char **argv);

#endif
