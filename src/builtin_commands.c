/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 14:49:22 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/24 13:01:00 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_commands.h"
#include "minishell.h"
#include <sys/stat.h>
#include "catch_errors.h"

int		check_params_cd(char **params)
{
	struct stat	prop;
	int			stat_ret;

	stat_ret = 0;
	if (params[1])
	{
		if ((stat_ret = lstat(params[1], &prop)) == 0)
		{
			if (!S_ISDIR(prop.st_mode))
				return (catch_cd_error(8, params[1]));
			else if (access(params[1], X_OK) == -1)
				return (catch_cd_error(9, params[1]));
		}
		else
			return (catch_cd_error(10, params[1]));
	}
	return (0);
}

int		builtin_cd(char **params, char ***environ)
{
	int		chdir_ret;
	char	*tmp;
	char	**homedir;
	char	new_dir[1024];

	chdir_ret = 0;
	tmp = ft_getenv(*environ, "HOME=");
	if (tmp)
		tmp = ft_strdup(tmp);
	if (!params[1])
		if (tmp)
		{
			homedir = parse_var_env(tmp);
			chdir_ret = chdir(homedir[0]);
		}
		else
			catch_cd_error(11, "HOME");
	else
		chdir_ret = chdir(params[1]);
	if (chdir_ret == -1)
		return (check_params_cd(params));
	getcwd(new_dir, 1024);
	ft_setenv("PWD", new_dir, environ);
	return (1);
}

void	builtin_exit(void)
{
	exit(0);
}

int		builtins_call(char **command, char ***environ)
{
	if (ft_strcmp(command[0], "cd") == 0)
		return (builtin_cd(command, environ));
	else if (ft_strcmp(command[0], "exit") == 0)
		builtin_exit();
	else if (ft_strcmp(command[0], "env") == 0)
		return (builtin_env(command, *environ));
	else if (ft_strcmp(command[0], "setenv") == 0)
		return (builtin_setenv(command, environ));
	else if (ft_strcmp(command[0], "unsetenv") == 0)
		return (builtin_unsetenv(command, environ));
	return (0);
}
