/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:33:15 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/23 17:33:24 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int		handle_command(char **command, char ***environ);
char	**parse_var_env(char *var);
int		get_var_index(char **var, char *chr);
char	*ft_getenv(char **var, char *chr);
void	aff_prompt(void);
void	rpl_homedir_tild(char **str, char **env);
char	*ft_join_paths(char *path, char *filename);
int		exec_command(char *cmd, char **av, char **env);
int		file_x_access(char *path);
int		initiate_command(char **bin_paths, char **command, char **env);
char	*getenv_value(char *var_name, char **env);

#endif
