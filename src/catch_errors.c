/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:57:21 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/17 18:31:13 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <dirent.h>

int				catch_error(int err_code, char *err_msg)
{
	DIR *dir_chk;

	ft_putstr("minishell: ");
	ft_putstr(err_msg);
	dir_chk = NULL;
	if (err_code == 1)
	{
	}
	if (err_code == 2)
	{
		if (ft_strchr(err_msg, '/'))
			ft_putendl(": No such file or directory");
		else if (opendir(err_msg))
			ft_putendl(": is a directory");
		else
			ft_putendl(": command not found");
		if (dir_chk)
			closedir(dir_chk);
	}
	return (err_code);
}
