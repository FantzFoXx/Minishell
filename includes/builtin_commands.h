/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 16:47:54 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/23 17:33:26 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_COMMANDS_H
# define BUILTIN_COMMANDS_H

int		builtins_call(char **command, char ***environ);
int		ft_setenv(char *name, const char *value, char ***env);
int		builtin_setenv(char **command, char ***env);
int		builtin_unsetenv(char **command, char ***env);
int		ft_unsetenv(char *name, char ***env);
int		builtin_env(char **params, char **environ);
int		handle_env_command(char **command, char **env_cp, char ***environ);
int		chk_setenv(char **params);
int		chk_unsetenv(char **params);

#endif
