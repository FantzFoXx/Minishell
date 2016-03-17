/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:27:25 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/17 11:55:11 by udelorme         ###   ########.fr       */
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

static void		catch_segv(pid_t pid, char **cmd)
{
	ft_putnbr(pid);
	ft_putstr(" segmentation fault  ");
	ft_putnbr(status);
	ft_putchar('\n');
}

static void		catch_abrt(pid_t pid, char **cmd)
{
	ft_putnbr(pid);
	ft_putstr(" abort : ");
	ft_putnbr(status);
	ft_putchar('\n');
}

void	handle_fork_signal(pid_t pid, int signum, char **cmd)
{
	if (signum == SIGSEGV)
		catch_segv(pid, cmd);
	else if (signum == SIGABRT)
		catch_abrt(pid, cmd);

}
