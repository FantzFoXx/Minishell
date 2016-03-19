/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:27:25 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/19 11:55:34 by udelorme         ###   ########.fr       */
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

static void		catch_segv(int signum)
{
	ft_putstr("Segmentation fault: ");
	ft_putnbr(signum);
	ft_putchar('\n');
}

static void		catch_abrt(int signum)
{
	ft_putstr("Abort trap: ");
	ft_putnbr(signum);
	ft_putchar('\n');
}

void	handle_fork_signal(int signum)
{
	if (signum == SIGSEGV)
		catch_segv(signum);
	else if (signum == SIGABRT)
		catch_abrt(signum);
}
