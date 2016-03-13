#ifndef MINISHELL_H
# define MINISHELL_H

int		handle_command(char *command, char **environ);
char	**parse_var_env(char *var);
int		get_var_index(char **var, char *chr);

#endif
