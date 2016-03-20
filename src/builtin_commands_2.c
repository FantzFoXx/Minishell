/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:36:14 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/19 14:21:33 by udelorme         ###   ########.fr       */
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
	while (params[i])
	{
		while (params[i][j])
		{
			if (!ft_isalnum(params[i][j]))
				return (catch_setenv_error(2));
			j++;
		}
		j = 0;
		i++;
	}
	if (i > 3)
		return (catch_setenv_error(1));
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

int		builtin_setenv(char **command, int overwrite, char ***env)
{
	(void)overwrite;
	if (!chk_setenv(command))
	{
		if (!command[1])
			return (builtin_env(command[0], *env));
		else if (!command[2])
			ft_setenv(command[1], "", 0, env);
		else
			ft_setenv(command[1], command[2], 0, env);
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

int		ft_unsetenv(char *name, char ***env)
{
	int		i;
	size_t	cur_var_len;
	char	*tmp;

	i = 0;
	cur_var_len = 0;
	if (!ft_strchr(name, '='))
		tmp = ft_strjoin(name, "=");
	else
		tmp = ft_strdup(name);
	while ((*env)[i])
	{
		while ((*env)[i][cur_var_len] != ('\0' ^ '='))
				cur_var_len++;
		cur_var_len += 1;
		if (ft_strncmp((*env)[i], tmp, cur_var_len) == 0)
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
		cur_var_len = 0;
		i++;
	}
	free(tmp);
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
