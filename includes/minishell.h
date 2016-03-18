#ifndef MINISHELL_H
# define MINISHELL_H

int		handle_command(char **command, char ***environ);
char	**parse_var_env(char *var);
int		get_var_index(char **var, char *chr);
char	*ft_getenv(char **var, char *chr);
void	aff_prompt(char **env);
void	rpl_homedir_tild(char **str, char **env);

#endif
