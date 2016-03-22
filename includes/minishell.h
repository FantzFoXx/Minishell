#ifndef MINISHELL_H
# define MINISHELL_H

int		handle_command(char **command, char ***environ);
char	**parse_var_env(char *var);
int		get_var_index(char **var, char *chr);
char	*ft_getenv(char **var, char *chr);
void	aff_prompt(char **env);
void	rpl_homedir_tild(char **str, char **env);
char	*ft_join_paths(char *path, char *filename);
int		exec_command(char *cmd, char **av, char **env);
int		file_x_access(char *path);
int		initiate_command(char **bin_paths, char **command, char **env);

#endif
