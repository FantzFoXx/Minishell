/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:57:21 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/19 16:37:48 by udelorme         ###   ########.fr       */
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
	if (err_code == 5)
		ft_putendl(": Not a directory");
	return (err_code);
}

int			catch_setenv_error(int err_code)
{
	ft_putstr("setenv: ");
	if (err_code == 1)
		ft_putendl(": Too many arguments");
	else if (err_code == 2)
		ft_putendl(": Variable name must contain alphanumeric characters.");
	return (err_code);
}

int			catch_cd_error(int err_code)
{
	
}
