/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:31:15 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/24 13:02:38 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "catch_errors.h"

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

char	*getenv_value(char *var_name, char **env)
{
	int		i;
	char	*ret;
	char	*complete_var;

	i = 0;
	complete_var = ft_getenv(env, var_name);
	ret = NULL;
	if (complete_var)
	{
		while (complete_var[i] != '=')
			i++;
		ret = ft_strsub(complete_var, i + 1, ft_strlen(complete_var) - i);
	}
	return (ret);
}

int		get_var_index(char **var, char *chr)
{
	char	*comp_chr;
	int		i;

	if (!ft_strchr(chr, '='))
		comp_chr = ft_strjoin(chr, "=");
	else
		comp_chr = ft_strdup(chr);
	i = -1;
	while (var[++i])
		if (ft_strnstr(var[i], comp_chr, ft_strlen(comp_chr)))
		{
			free(comp_chr);
			return (i);
		}
	free(comp_chr);
	return (-1);
}

char	*ft_getenv(char **var, char *chr)
{
	int		index;
	char	*ret;

	index = get_var_index(var, chr);
	ret = NULL;
	if (index != -1)
		ret = var[index];
	return (ret);
}

char	*ft_join_paths(char *path, char *filename)
{
	char *tmp;
	char *ret;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, filename);
	free(tmp);
	return (ret);
}
