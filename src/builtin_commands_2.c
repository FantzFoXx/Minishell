/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:36:14 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/17 10:53:47 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_commands.h"
#include "minishell.h"
#include "libft.h"
#include "catch_errors.h"

int		chk_setenv(char **params)
{
	int i;

	i = 0;
	while (params[i])
		i++;
	if (i == 2)
		return (2);
	else if (i == 3)
		return (3);
	else
		return (0);
}

int		chk_unsetenv(char **params)
{
	int i;

	i = 0;
	while (params[i])
		i++;
	if (i == 1)
		return (1);
	else
		return (0);
}

int		builtin_setenv(char **command, int overwrite, char ***env)
{
	(void)overwrite;
	int		nb_params;
	if ((nb_params = chk_setenv(command)) && nb_params)
	{
		if (nb_params == 2)
			return (ft_setenv(command[1], "", 0, env));
		else if (nb_params == 3)
			return (ft_setenv(command[1], command[2], 0, env));
	}
	else
		catch_error(1, "setenv");
	return (1);
}

int		builtin_unsetenv(char **command, char ***env)
{
	int		nb_params;

	if ((nb_params = chk_setenv(command)) && nb_params)
	{
		if (nb_params == 1)
			return (ft_unsetenv(command[1], env));
	}
	else
		catch_error(1, "unsetenv");
	return (1);
}

int		ft_unsetenv(char *name, char ***env)
{
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strnstr((*env)[i], name, ft_strlen(name)))
		{
			free((*env)[i]);
			while ((*env)[i + 1])
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = 0;
			i = -1;
		}
		i++;
	}
	return (1);
}

int		ft_setenv(char *name, const char *value, int overwrite, char ***env)
{
	int index;
	char *new_var;
	(void)overwrite;
	char **env_ptr;

	new_var = NULL;
	index = 0;
	env_ptr = *env;
	if (name && name[0] != '\0')
	{
		index = get_var_index(env_ptr, name);
		if (index != -1)
		{
			if ((ft_strlen(name) + ft_strlen(value) + 2) <= ft_strlen(env_ptr[index]))
				ft_strcpy(&env_ptr[index][ft_strlen(name) + 1], value);
			else
			{
				new_var = ft_strnew(sizeof(char)
						* (ft_strlen(name) + ft_strlen(value) + 1));
				ft_strcat(new_var, name);
				ft_strcat(new_var, "=");
				ft_strcat(new_var, value);
				env_ptr[index] = new_var;
			}
		}
		else
		{
			index = 0;
			while (env_ptr[index])
				index++;
			ft_realloc_tab(env, 1);
			new_var = ft_strnew(ft_strlen(name) + ft_strlen(value) + 1);
			ft_strcat(new_var, name);
			ft_strcat(new_var, "=");
			ft_strcat(new_var, value);
			(*env)[index] = new_var;
			index = 0;
		}
	}
	return (1);
}
