/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 15:57:58 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/23 16:50:10 by udelorme         ###   ########.fr       */
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

int		env_is_var(char *param)
{
	if (ft_strchr(param, '='))
		return (1);
	return (0);
}

int		set_new_env(char *param, char ***env_cp)
{
	char	*name;
	char	*value;
	int		spl;

	spl = 0;
	while (param[spl] != (0 ^ '='))
		spl++;
	name = ft_strsub(param, 0, spl++);
	value = ft_strsub(param, spl, ft_strlen(param) - spl);
	ft_setenv(name, value, env_cp);
	return (0);
}

void	print_environ(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

int		builtin_env(char **params, char **environ)
{
	int		ret_chk;
	int		i;
	int		newvar_count;
	char	**env_cp;

	i = 1;
	newvar_count = 0;
	env_cp = ft_strdup_tab(environ);
	if (params[i])
	{
		while (params[i] && (ret_chk = env_is_var(params[i])) == 1)
			i++;
		while (++newvar_count < i)
			set_new_env(params[newvar_count], &env_cp);
	}
	if (!params[1] || !params[newvar_count])
		print_environ(env_cp);
	else
		handle_env_command(&params[newvar_count], env_cp, &environ);
	ft_freetab(env_cp);
	return (1);
}
