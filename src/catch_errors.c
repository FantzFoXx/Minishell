/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:57:21 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/23 12:02:52 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <dirent.h>

int				catch_error(int err_code, char *err_msg)
{
	ft_putstr("minishell: ");
	ft_putstr(err_msg);
	if (err_code == 1)
		ft_putendl(": command not found");
	else if (err_code == 2)
		ft_putendl(": is a directory");
	else if (err_code == 3)
		ft_putendl(": Permission denied");
	else if (err_code == 4)
		ft_putendl(": No such file or directory");
	else if (err_code == 5)
		ft_putendl(": Not a directory");
	return (err_code);
}

int			catch_setenv_error(int err_code)
{
	ft_putstr("minishell: ");
	ft_putstr("setenv");
	if (err_code == 6)
		ft_putendl(": Too many arguments");
	else if (err_code == 7)
		ft_putendl(": Variable name must contain alphanumeric characters.");
	return (err_code);
}

int			catch_cd_error(int err_code, char *err_msg)
{
	ft_putstr("minishell: ");
	ft_putstr("cd: ");
	if (err_code == 11)
	{
		ft_putstr(err_msg);
		ft_putendl(" not set");
		return (err_code);
	}
	ft_putstr(err_msg);
	if (err_code == 8)
		ft_putendl(": Not a directory");
	else if (err_code == 9)
		ft_putendl(": Permission denied");
	else if (err_code == 10)
		ft_putendl(": No such file or directory");
	return (err_code);
}

int			catch_env_error(int	err_code, char *err_msg)
{
	ft_putstr("env: ");
	ft_putstr(err_msg);
	if (err_code == 1)
		ft_putendl(": No such file or directory");
	if (err_code == 2)
		ft_putendl(": Permission denied");
	return (err_code);
}
