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
		exit(1);
	}
	return (1);
}

static int	initiate_command(char **bin_paths, char **command, char **env)
{
	char		*complete_cmd;
	int			i;

	i = 0;
	if (bin_paths)
		while (bin_paths[i])
		{
			complete_cmd = ft_join_paths(bin_paths[i], command[0]);
			if (access(complete_cmd, F_OK) == 0)
			{
				 if (access(complete_cmd, X_OK) == 0)
					return (exec_command(complete_cmd, command, env));
				 else
					 return (catch_error(3, command[0]));
			}
			i++;
			free(complete_cmd);
		}
	else
		return (exec_command(command[0], &command[0], env));
	return (-1);
}

int			file_x_access(char *path)
{
	return (access(path, X_OK) == 0) ? 1 : 0;
}

int			check_is_dirfile(char **path, char **env)
{
	struct stat	file_prop;

	if (stat(path[0], &file_prop) == 0)
	{
		if (S_ISDIR(file_prop.st_mode))
			return (catch_error(2, path[0]));
		else if (file_x_access(path[0]) == 0)
			return (catch_error(3, path[0]));
		else
			return (initiate_command(NULL, path, env));
	}
	else if (ft_strchr(path[0], '/'))
		return (catch_error(4, path[0]));
	return (0);
}

int			handle_command(char **command, char ***environ)
{
	char	**bin_paths;
	int		path_index;


	if (!builtins_call(command, environ))
	{
		if (!check_is_dirfile(command, *environ))
		{
			path_index = get_var_index(*environ, "PATH=");
			if (path_index >= 0)
			{
				bin_paths = parse_var_env((*environ)[path_index]);
				if (initiate_command(bin_paths, command, *environ) == -1)
					catch_error(1, command[0]);
			}
			else
				catch_error(1, command[0]);
		}
	}
	return (0);
}

/*
int			handle_command(char **command, char ***environ)
{
	char		**bin_paths;
	struct stat	file_prop;
	int				var_index;

	var_index = 0;
	bin_paths = NULL;
	//ft_trace("command", command[0]);
	if (stat(command[0], &file_prop) == -1)
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
*/
