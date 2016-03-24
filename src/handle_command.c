/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 15:58:14 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/24 13:01:02 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>
#include "minishell.h"
#include "builtin_commands.h"
#include "catch_errors.h"
#include <sys/wait.h>

int		exec_command(char *cmd, char **av, char **env)
{
	pid_t	child;
	int		status;

	child = fork();
	status = 0;
	if (child > 0)
		waitpid(child, &status, 0);
	if (child == 0)
	{
		execve(cmd, &av[0], env);
		exit(1);
	}
	return (1);
}

int		initiate_command(char **bin_paths, char **command, char **env)
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

int		file_x_access(char *path)
{
	return (access(path, X_OK) == 0) ? 1 : 0;
}

int		check_is_dirfile(char **path, char **env)
{
	struct stat	file_prop;

	if (ft_strchr(path[0], '/'))
	{
		if (stat(path[0], &file_prop) == 0)
		{
			if (S_ISDIR(file_prop.st_mode))
				return (catch_error(2, path[0]));
			else if (file_x_access(path[0]) == 0)
				return (catch_error(3, path[0]));
			else
				return (initiate_command(NULL, path, env));
		}
		else
			return (catch_error(4, path[0]));
	}
	return (0);
}

int		handle_command(char **command, char ***environ)
{
	char	**bin_paths;
	int		path_index;

	if (!builtins_call(command, environ))
	{
		path_index = get_var_index(*environ, "PATH=");
		if (path_index >= 0)
			bin_paths = parse_var_env((*environ)[path_index]);
		else
			bin_paths = parse_var_env(
				"PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
		if (!check_is_dirfile(command, *environ))
			if (initiate_command(bin_paths, command, *environ) == -1)
				catch_error(1, command[0]);
		ft_freetab(bin_paths);
	}
	return (0);
}
