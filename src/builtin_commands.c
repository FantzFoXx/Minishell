#include "libft.h"
#include "builtin_commands.h"
#include <unistd.h>
#include "minishell.h"

int		ft_setenv(char *name, const char *value, int overwrite, char **env)
{
	int index;
	char *new_var;
	(void)overwrite;

	new_var = NULL;
	if (name && name[0] != '\0')
	{
		index = get_var_index(env, name);
		if (index != -1)
		{
			if ((ft_strlen(name) + ft_strlen(value) + 2) <= ft_strlen(env[index]))
				ft_strcpy(&env[index][ft_strlen(name) + 1], value);
			else
			{
				new_var = ft_strnew(sizeof(char)
						* (ft_strlen(name) + ft_strlen(value) + 1));
				ft_strcat(new_var, name);
				ft_strcat(new_var, "=");
				ft_strcat(new_var, value);
				env[index] = new_var;
			}
		}
	}
	return (0);
}

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
	return (0);
}

int		builtin_cd(char **params, char **environ)
{
	char	*tmp;
	char **homedir;
	char new_dir[1024];

	tmp = ft_getenv(environ, "HOME=");
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

int		builtins_call(char **command, char **environ)
{
	if (ft_strcmp(command[0], "cd") == 0)
		return (builtin_cd(command, environ));
	else if (ft_strcmp(command[0], "exit") == 0)
		builtin_exit();
	else if (ft_strcmp(command[0], "env") == 0)
		builtin_env(NULL, environ);
	return (0);
}
