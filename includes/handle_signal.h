/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:28:27 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/17 13:26:41 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_SIGNALS_H
# define HANDLE_SIGNALS_H

void	init_sign(char **environ);
void	foo(int num);
void	handle_fork_signal(int signum);

#endif
