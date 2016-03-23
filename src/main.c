/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 15:58:23 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/23 12:03:11 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "handle_signal.h"
#include "catch_errors.h"
#include "minishell.h"
#include <sys/param.h>

/*
void	rpl_homedir_tild(char **str, char **env)
{
	int			home_ind;
	static char	**path_env = NULL;
	char		*tmp;

	home_ind = get_var_index(env, "HOME=");
	if (home_ind >= 0 && path_env == NULL)
		path_env = parse_var_env(env[home_ind]);
	if (path_env && ft_strnstr(*str, *path_env, ft_strlen(*path_env)))
	{
		tmp = ft_strsub(*str, ft_strlen(*path_env), ft_strlen(*str) - ft_strlen(*path_env));
		free(*str);
		*str = ft_strnew(ft_strlen(tmp) + 1);
		ft_strcat(*str, "~");
		ft_strcat(*str, tmp);
		free(tmp);
	}
}
*/

void	aff_prompt(char **env)
{
	(void)env;
	static char *prompt = NULL;
	char		*new_pwd;

	new_pwd = NULL;
	new_pwd = getcwd(new_pwd, MAXPATHLEN);
	if (new_pwd)
	{
		if (prompt && ft_strcmp(prompt, new_pwd))
			free(prompt);
		prompt = new_pwd;
		//rpl_homedir_tild(&prompt, env);
	}
	if (prompt)
		ft_putstr(prompt);
	ft_putstr(" $ ");
}

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	int		gnl_ret;
	char	*line;
	char	**spl_line;
	char	**env_cp;

	env_cp = ft_strdup_tab(environ);
	gnl_ret = 0;
	line = NULL;
	//init_sign(env_cp);
	aff_prompt(env_cp);
	while (1)
	{
		gnl_ret = get_next_line(0, &line);
		if (gnl_ret < 0)
		{
			catch_error(0, "gnl failure");
			exit(1);
		}
		else if (gnl_ret == 0)
			exit(0);
		else
		{
			if (!line)
				ft_putendl(line = ft_strdup("exit"));
			line = ft_strtrim_w(line);
			spl_line = ft_strsplit(line, ' ');
			if (line && ft_strcmp(line, "") != 0)
				handle_command(spl_line, &env_cp);
			free(line);
		}
		gnl_ret = 0;
		aff_prompt(env_cp);
	}
	return (0);
}
