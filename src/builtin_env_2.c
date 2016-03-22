/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 15:58:46 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/22 18:09:55 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_commands.h"
#include <unistd.h>
#include "minishell.h"
#include <sys/stat.h>
#include "catch_errors.h"
#include <stdio.h>
#include <dirent.h>
#include <minishell.h>

static int	initiate_env_command(char **bin_paths, char **command, char **env)
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
					return (catch_env_error(1, command[0]));
			}
			i++;
			free(complete_cmd);
		}
	else
		return (exec_command(command[0], &command[0], env));
	return (-1);
}

int			env_check_is_dirfile(char **path, char **env)
{
	struct stat	file_prop;

	if (ft_strchr(path[0], '/'))
		if (stat(path[0], &file_prop) == 0)
		{
			if (S_ISDIR(file_prop.st_mode))
				return (catch_env_error(1, path[0]));
			else if (file_x_access(path[0]) == 0)
				return (catch_env_error(2, path[0]));
			else
				return (initiate_command(NULL, path, env));
		}
	return (0);
}

int			handle_env_command(char **command, char **env_cp, char ***environ)
{
	char	**bin_paths;
	int		path_index;

	if (!builtins_call(command, environ))
	{
		path_index = get_var_index(*environ, "PATH=");
		if (path_index >= 0)
		{
			bin_paths = parse_var_env((*environ)[path_index]);
			if (initiate_env_command(bin_paths, command, env_cp) == -1)
				if (!env_check_is_dirfile(command, env_cp))
					catch_env_error(1, command[0]);
		}
	}
	return (0);
}
