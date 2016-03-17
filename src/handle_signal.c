/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:27:25 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/17 08:13:09 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

void		foo(int num)
{
	(void)num;
	ft_putstr("\n");
}

void	init_sign(char **environ)
{
	(void)environ;
	signal(SIGINT, foo);
}
