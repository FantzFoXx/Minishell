#include "libft.h"
#include "catch_errors.h"
#include "minishell.h"

extern char **environ;

void	aff_prompt(char **env)
{
	char **wd;
	char **homedir;
	char *tmp;
	int pwd_index;
	int home_index;

	pwd_index = get_var_index(env, "PWD=");
	home_index = get_var_index(env, "HOME=");
	wd = NULL;
	tmp = NULL;
	homedir = NULL;
	if (pwd_index)
		wd = parse_var_env(env[pwd_index]);
	if (wd)
	{
		if (home_index)
			homedir = parse_var_env(env[home_index]);
		if (homedir)
			if (ft_strstr(wd[0], homedir[0]))
			{
				ft_putstr("~");
				tmp = ft_strsub(wd[0], ft_strlen(homedir[0]), ft_strlen(wd[0]) - ft_strlen(homedir[0]));
				ft_putstr(&wd[0][ft_strlen(homedir[0])]);
			}
			else
				ft_putstr(wd[0]);
		else
			ft_putstr(wd[0]);
		ft_putstr(" $ ");
	}
	else
		ft_putstr("$> ");
}

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	int		gnl_ret;
	char	*line;

	gnl_ret = 0;
	line = NULL;
	while (1)
	{
		aff_prompt(environ);
		while (gnl_ret == 0)
			gnl_ret = get_next_line(1, &line);
		if (gnl_ret < 0)
			catch_error(1, "gnl");
		else
		{
			if (line && ft_strcmp(line, ""))
				handle_command(line, environ);
		}
		gnl_ret = 0;
	}
	return (0);
}
