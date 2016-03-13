/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:57:21 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/04 19:52:05 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				catch_error(int err_code, char *err_msg)
{
	char *def_str;

	if (err_code == 1)
	{
		def_str = ft_strjoin("minishell: ", err_msg);
		ft_putendl(def_str);
		free(def_str);
	}

	return (err_code);
}
