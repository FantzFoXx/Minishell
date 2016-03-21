#include "libft.h"
#include "builtin_commands.h"
#include <unistd.h>
#include "minishell.h"
#include <sys/stat.h>
#include "catch_errors.h"
#include <stdio.h>
#include <dirent.h>

int		env_is_var(char *param)
{
	if (!ft_isalnum(param[0]))
		//return (env_catch_error(11, param));
		return (11);
	if (ft_strchr(param, '='))
		return (1);
	return (0);
}

int		set_new_env(char *param, char ***env_cp)
{
	char	*name;
	char	*value;
	int		spl;
	(void)env_cp;

	spl = 0;
	while (param[spl] != (0 ^ '='))
		spl++;
	name = ft_strsub(param, 0, spl++);
	value = ft_strsub(param, spl, ft_strlen(param) - spl);
	ft_setenv(name, value, 0, env_cp);
	return (0);
}

void	print_environ(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		ft_putendl(env[i]);
		i++;
	}
}

int		builtin_env(char **params, char **environ)
{
	int		ret_chk;
	int		i;
	int		newvar_count;
	char	**env_cp;

	env_cp = ft_strdup_tab(environ);
	i = 1;
	if (!params[i])
	{
	while ((ret_chk = env_is_var(params[i])) == 1)
		i++;
	if (ret_chk == 11)
		return (1);
	newvar_count = 0;
	while (++newvar_count <= i)
		set_new_env(params[newvar_count], &env_cp);
	}
		print_environ(env_cp);
	return (1);
}
