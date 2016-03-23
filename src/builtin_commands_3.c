/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:41:28 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/23 16:53:42 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_commands.h"
#include "minishell.h"
#include "libft.h"
#include "catch_errors.h"

int		chk_setenv(char **params)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (ft_tab_size(params) > 3)
		return (catch_setenv_error(6));
	while (params[i])
	{
		while (params[i][j])
		{
			if (i == 1 && !ft_isalnum(params[i][j]) && params[i][j] != '_')
				return (catch_setenv_error(7));
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int		chk_unsetenv(char **params)
{
	int i;

	i = 1;
	while (params[i])
		i++;
	if (i >= 2)
		return (i - 1);
	else
		return (0);
}

int		builtin_setenv(char **command, char ***env)
{
	if (!chk_setenv(command))
	{
		if (!command[1])
			return (builtin_env(command, *env));
		else if (!command[2])
			ft_setenv(command[1], "", env);
		else
			ft_setenv(command[1], command[2], env);
	}
	return (1);
}

int		builtin_unsetenv(char **command, char ***env)
{
	int		nb_params;

	if ((nb_params = chk_unsetenv(command)) && nb_params)
	{
		while (nb_params > 0)
		{
			ft_unsetenv(command[nb_params], env);
			nb_params--;
		}
		return (1);
	}
	else
		catch_error(1, "unsetenv");
	return (1);
}
