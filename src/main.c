#include "libft.h"
#include "handle_signal.h"
#include "catch_errors.h"
#include "minishell.h"

char	**ft_strdup_tab(char **tab)
{
	char	**new;
	int		size_tab;
	int		i;

	size_tab = 0;
	if (tab)
		while (tab[size_tab] != 0)
			size_tab++;
	new = (char **)malloc(sizeof(char *) * (size_tab + 1));
	new[size_tab] = NULL;
	i = -1;
	if (tab)
		while (++i < size_tab)
			new[i] = ft_strdup(tab[i]);
	return (new);
}

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
	if (pwd_index >= 0)
		wd = parse_var_env(env[pwd_index]);
	if (wd)
	{
		if (home_index >= 0)
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
	char	**spl_line;
	char	**env_cp;

	env_cp = ft_strdup_tab(environ);
	gnl_ret = 0;
	line = NULL;
	init_sign(env_cp);
	while (1)
	{
		aff_prompt(env_cp);
		while (gnl_ret == 0)
			gnl_ret = get_next_line(1, &line);
		if (gnl_ret < 0)
			catch_error(1, "gnl");
		else
		{
			line = ft_strtrim_w(line);
			spl_line = ft_strsplit(line, ' ');
			if (line && ft_strcmp(line, ""))
				handle_command(spl_line, &env_cp);
			free(line);
		}
		gnl_ret = 0;
	}
	return (0);
}
