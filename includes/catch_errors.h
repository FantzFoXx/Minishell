/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 13:02:59 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/24 10:05:07 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CATCH_ERRORS_H
# define CATCH_ERRORS_H

int				catch_error(int err_code, char *err_msg);
int				catch_setenv_error(int err_code);
int				catch_unsetenv_error(int err_code);
int				catch_cd_error(int err_code, char *err_msg);
int				catch_env_error(int	err_code, char *err_msg);

#endif
