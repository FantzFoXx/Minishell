#include "libft.h"
#include "builtin_commands.h"
#include <unistd.h>
#include "minishell.h"

int		builtin_cd(char **params, char **environ)
{
	(void)environ;
	if (params[1])
		chdir(params[1]);
	return (1);
}

void	builtin_exit(void)
{
	// add free function
	exit(0);
}

int		builtins_call(char **command, char **environ)
{
	if (ft_strcmp(command[0], "cd") == 0)
		return (builtin_cd(command, environ));
	else if (ft_strcmp(command[0], "exit") == 0)
		builtin_exit();
	return (0);
}
