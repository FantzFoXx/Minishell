/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 15:58:23 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/23 16:43:42 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "catch_errors.h"
#include "minishell.h"
#include <sys/param.h>
#include "builtin_commands.h"

void	calc_shlvl(char ***env)
{
	char	*shlvl;
	int		new_value;
	int		i;
	int		wrong_data;
	char	*lvl_str;

	shlvl = getenv_value("SHLVL=", *env);
	wrong_data = 0;
	new_value = 1;
	i = -1;
	if (shlvl)
	{
		while (shlvl[++i])
			if (!ft_isdigit(shlvl[i]))
				wrong_data = 1;
	}
	else
		wrong_data = 1;
	if (!wrong_data)
		new_value = ft_atoi(shlvl) + 1;
	lvl_str = ft_itoa(new_value);
	ft_setenv("SHLVL", lvl_str, env);
	free(lvl_str);
	free(shlvl);
}

void	aff_prompt(void)
{
	static char *prompt = NULL;
	char		*new_pwd;

	new_pwd = NULL;
	new_pwd = getcwd(new_pwd, MAXPATHLEN);
	if (new_pwd)
	{
		if (prompt)
			free(prompt);
		prompt = new_pwd;
	}
	if (prompt)
		ft_putstr(prompt);
	ft_putstr(" $ ");
}

void	check_params(int ac, char **av)
{
	if (ac > 1 && av[ac - 1])
	{
		ft_putendl("minishell: Usage: ./minishell");
		exit(1);
	}
}

void	get_input(char **line)
{
	int		gnl_ret;

	gnl_ret = get_next_line(0, line);
	if (gnl_ret < 0)
	{
		catch_error(0, "gnl failure");
		exit(1);
	}
	else if (gnl_ret == 0)
		exit(0);
}

int		main(int argc, char **argv, char **environ)
{
	char	*tmp;
	char	*line;
	char	**spl_line;
	char	**env_cp;

	check_params(argc, argv);
	env_cp = ft_strdup_tab(environ);
	line = NULL;
	calc_shlvl(&env_cp);
	while (1)
	{
		aff_prompt();
		get_input(&tmp);
		if (!tmp)
			ft_putendl(tmp = ft_strdup("exit"));
		line = ft_strtrim_w(tmp);
		spl_line = ft_strsplit(line, ' ');
		if (line && ft_strcmp(line, "") != 0)
			handle_command(spl_line, &env_cp);
		free(line);
		free(tmp);
		ft_freetab(spl_line);
	}
	return (0);
}
