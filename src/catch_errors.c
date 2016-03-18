/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:57:21 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/18 18:00:33 by udelorme         ###   ########.fr       */
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
		ft_putendl(": command not found");
	else if (err_code == 2)
		ft_putendl(": is a directory");
	else if (err_code == 3)
		ft_putendl(": Permission denied");
	else if (err_code == 4)
		ft_putendl(": No such file or directory");
	/*
	if (err_code == 5)
	{
	}*/
	return (err_code);
}
