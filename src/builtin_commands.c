#include "libft.h"
#include "builtin_commands.h"
#include <unistd.h>
#include "minishell.h"

int		builtin_env(char *params, char **environ)
{
	(void)params;
	int		i;

	i = 0;
	while (environ[i])
	{
		ft_putendl(environ[i]);
		i++;
	}
	return (1);
}

int		builtin_cd(char **params, char ***environ)
{
	char	*tmp;
	char **homedir;
	char new_dir[1024];

	tmp = ft_getenv(*environ, "HOME=");
	if (((params[1] && ft_strcmp(params[1], "~") == 0) || !params[1]) && tmp)
	{
		homedir = parse_var_env(tmp);
		chdir(homedir[0]);
	}
	else
		chdir(params[1]);
	getcwd(new_dir, 1024);
	ft_setenv("PWD", new_dir, 0, environ);
	return (1);
}

void	builtin_exit(void)
{
	// add free function
	exit(0);
}

int		builtins_call(char **command, char ***environ)
{
	if (ft_strcmp(command[0], "cd") == 0)
		return (builtin_cd(command, environ));
	else if (ft_strcmp(command[0], "exit") == 0)
		builtin_exit();
	else if (ft_strcmp(command[0], "env") == 0)
		return (builtin_env(NULL, *environ));
	else if (ft_strcmp(command[0], "setenv") == 0)
		return (builtin_setenv(command, 0, environ));
	return (0);
}
