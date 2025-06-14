#include "../minishell.h"

int	expand_env(char *s, int fd)
{
	char	*env;
	char	*temp;

	//TODO If double dollar "$$" print getpid, also fix reading envs from string where $ right in front.
	if (s[0] != '$')
		return (-1);
	env = ft_substr(s, 1, ft_strlen(s) - 1);
	temp = getenv(env);
	free(env);
	if (!temp)
		return (0);
	ft_putstr(temp);
	return (0);
}

void	ft_putstr(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len == 1)
		write(1, &s[0], 1);
	else if (expand_env(s, 1) == -1)
		write(1, s, len);
}

void	ft_putendl(char *s)
{
	int		len;

	len = ft_strlen(s);
	if (len == 1)
		write(1, &s[0], 1);
	else if (expand_env(s, 1) == -1)
		write(1, s, len);
	write(1, "\n", 1);
}
