#include "libft.h"
#include "handle_signal.h"
#include "catch_errors.h"
#include "minishell.h"
#include <sys/param.h>

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

/*void	aff_prompt(char **env)
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
  */

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

void	aff_prompt(char **env)
{
	(void)env;
	static char *prompt = NULL;
	char		*new_pwd;

	new_pwd = NULL;
	new_pwd = getcwd(new_pwd, MAXPATHLEN);
	if (prompt && ft_strcmp(prompt, new_pwd))
		free(prompt);
	prompt = new_pwd;
	rpl_homedir_tild(&prompt, env);
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
			if (line && ft_strcmp(line, "") != 0)
				handle_command(spl_line, &env_cp);
			free(line);
		}
		gnl_ret = 0;
	}
	return (0);
}
