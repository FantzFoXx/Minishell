#ifndef BUILTIN_COMMANDS_H
# define BUILTIN_COMMANDS_H

int		builtins_call(char **command, char ***environ);
int		ft_setenv(char *name, const char *value, int overwrite, char ***env);
int		builtin_setenv(char **command, int overwrite, char ***env);
int		builtin_unsetenv(char **command, char ***env);
int		ft_unsetenv(char *name, char ***env);
int		builtin_env(char *params, char **environ);

#endif
