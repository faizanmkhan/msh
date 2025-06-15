#include "../minishell.h"

int	ft_chr_pos(char *s, int start, char c);

int	print_env(char *env_s)
{
	int		pid;
	char	*new_str;
	char	*env_big;

	if (env_s[0] == '$')
	{
		pid = (int)getpid();
		ft_putnbr_fd(pid, 1);
		new_str = ft_substr(env_s, 1, ft_strlen(env_s) - 1);
		ft_putstr(new_str);
		return (1);
	}
	else
	{
		env_big = getenv(env_s);
		if (!env_big)
			env_big = ft_strdup("");
		ft_putstr(env_big);
		if (!getenv(env_s))
			free(env_big);
	}
	return (-1);
}

int	manage_env(char *s)
{
	int		sign_pos;
	int		i;
	char	*bef_s;
	char	*env_s;
	char	*env_big;

	sign_pos = ft_chr_pos(s, 0, '$');
	if (sign_pos == -1)
		return (-1);
	bef_s = ft_substr(s, 0, sign_pos);
	i = ft_chr_pos(s, sign_pos, ' ');
	if (i == -1)
		i = ft_strlen(s);
	env_s = ft_substr(s, sign_pos + 1, i - sign_pos - 1);
	ft_putstr(bef_s);
	print_env(env_s);
	free(bef_s);
	free(env_s);
	return (0);
}

int	ft_chr_pos(char *s, int start, char c)
{
	while (s[start])
	{
		if (s[start] == c)
			return (start);
		start++;
	}
	return (-1);
}

void	ft_putstr(char *s)
{
	int	len;

	if (manage_env(s) == 0)
		return ;
	len = ft_strlen(s);
	write(1, s, len);
}

void	ft_putendl(char *s)
{
	int		len;

	if (manage_env(s) == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	len = ft_strlen(s);
	write(1, s, len);
	write(1, "\n", 1);
}
