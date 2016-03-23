/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:36:14 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/23 17:33:07 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_commands.h"
#include "minishell.h"
#include "libft.h"
#include "catch_errors.h"

char	*comp_var_name(char *name)
{
	char	*tmp;

	if (!ft_strchr(name, '='))
		tmp = ft_strjoin(name, "=");
	else
		tmp = ft_strdup(name);
	return (tmp);
}

size_t	count_cur_var_len(char **env, int i)
{
	size_t	cur_var_len;

	cur_var_len = 0;
	while (env[i][cur_var_len] != ('\0' ^ '='))
		cur_var_len++;
	cur_var_len += 1;
	return (cur_var_len);
}

int		ft_unsetenv(char *name, char ***env)
{
	int		i;
	size_t	cur_var_len;
	char	*tmp;

	i = 0;
	tmp = comp_var_name(name);
	while ((*env)[i])
	{
		cur_var_len = count_cur_var_len(*env, i);
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

char	*cat_new_var(char *name, const char *value)
{
	char *new_var;

	new_var = ft_strnew((ft_strlen(name) + ft_strlen(value) + 1));
	ft_strcat(new_var, name);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	return (new_var);
}

int		ft_setenv(char *name, const char *value, char ***env)
{
	int		index;
	char	**env_ptr;

	env_ptr = *env;
	if (name && name[0] != '\0')
	{
		index = get_var_index(env_ptr, name);
		if (index != -1)
			if ((ft_strlen(name) + ft_strlen(value) + 2)
					<= ft_strlen(env_ptr[index]))
				ft_strcpy(&env_ptr[index][ft_strlen(name) + 1], value);
			else
				env_ptr[index] = cat_new_var(name, value);
		else
		{
			index = 0;
			while (env_ptr[index])
				index++;
			ft_realloc_tab(env, 1);
			(*env)[index] = cat_new_var(name, value);
			index = 0;
		}
	}
	return (1);
}
