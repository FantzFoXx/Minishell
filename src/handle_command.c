#include "libft.h"
#include <sys/stat.h>
#include "minishell.h"
#include "builtin_commands.h"
#include "catch_errors.h"
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "handle_signal.h"

#include <stdio.h>

char	**parse_var_env(char *var)
{
	int		i;
	char	**ret;
	char	*tmp;

	i = 0;
	while (var[i] != '=')
		i++;
	tmp = ft_strsub(var, i + 1, ft_strlen(var) - i);
	ret = ft_strsplit(tmp, ':');
	free(tmp);
	return (ret);
}

int	get_var_index(char **var, char *chr)
{
	int	i;

	i = -1;
	while (var[++i])
		if (ft_strnstr(var[i], chr, ft_strlen(chr)))
			return (i);
	return (-1);
}

char	*ft_getenv(char **var, char *chr)
{
	int index;
	char *ret;

	index = get_var_index(var, chr);
	ret = NULL;
	if (index != -1)
		ret = var[index];
	return (ret);
}

static char	*ft_join_paths(char *path, char *filename)
{
	char *tmp;
	char *ret;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, filename);
	free(tmp);
	return (ret);
}


static int	exec_command(char *cmd, char **av, char **env)
{
	pid_t child;
	int status;

	child = fork();
	status = 0;
	if (child > 0)
	{
		waitpid(child, &status, 0);
		if (WTERMSIG(status))
			handle_fork_signal(WTERMSIG(status));
	}
	if (child == 0)
	{
		execve(cmd, &av[0], env);
		ft_trace("out execve", "pass");
		exit(1);
	}
	return (1);
}

static int	initiate_command(char **bin_paths, char **command, char **env)
{
	struct stat	useless;
	char		*complete_cmd;
	int			i;

	i = 0;
	if (bin_paths)
		while (bin_paths[i])
		{
			complete_cmd = ft_join_paths(bin_paths[i], command[0]);
			if (stat(complete_cmd, &useless) == 0)
				return (exec_command(complete_cmd, command, env));
			i++;
			free(complete_cmd);
		}
	else
		exec_command(command[0], &command[0], env);
	return (-1);
}

int			handle_command(char **command, char ***environ)
{
	char		**bin_paths;
	struct stat	file_prop;
	int				var_index;

	var_index = 0;
	bin_paths = NULL;
	//ft_trace("command", command[0]);
	if (stat(command[0], &file_prop) == -1 )
	{
		if (!builtins_call(command, environ))
		{
			var_index = get_var_index(*environ, "PATH=");
			if (var_index != -1)
			{
				bin_paths = parse_var_env((*environ)[var_index]);
				if (initiate_command(bin_paths, command, *environ) == -1)
					catch_error(2, command[0]);
			}
		}
	}
	else
		initiate_command(NULL, command, *environ);
	return (0);
}
