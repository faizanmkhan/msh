#include "myshell.h"

t_env_data *parse_env_var(char *env_str)
{
	t_env_data	*new_env;
	char	*delimiter;
	char	*key;
	char	*value;

	delimiter = ft_strchr(env_str, '=');
	if (!delimiter)
		return NULL;
	*delimiter = 0;
	key = ft_strdup(env_str);
	value = ft_strdup(delimiter + 1);
	*delimiter = '=';
	new_env = malloc(sizeof(t_env_data));
	if (!new_env)
		return NULL;
	new_env->key = key;
	new_env->value = value;
	new_env->next = NULL;
	return new_env;
}

void append_env_vars(t_shell_data *myshell, t_env_data *sh_env)
{
	t_env_data	*current;

	if(!myshell->shell_env)
		myshell->shell_env = sh_env;
	else
	{
		current = myshell->shell_env;
		while (current->next)
			current = current->next;
		current->next = sh_env;
	}
}

int	ft_char_pos(char *s, int start, char c)
{
	while (s[start])
	{
		if (s[start] == c)
			return (start);
		start++;
	}
	return (-1);
}

char	*expand_env_value(char *env_s)
{
	char	*env_big;
	char	*fin_str;

	fin_str = NULL;
	if (env_s[0] == '?')
	{
		
		if (!fin_str)
			return (NULL);
		return (fin_str);
	}
	else
	{
		env_big = getenv(env_s);
		if (!env_big)
			env_big = ft_strdup("");
		return (env_big);
	}
	return (NULL);
}

char	*processing_env_expansion(char *s)
{
	int		sign_pos;
	int		space_i;
	char	*bef_s;
	char	*env_s;
	char	*final_str;
	char	*exp_env;

	final_str = NULL;
	sign_pos = ft_char_pos(s, 0, '$');
	if (sign_pos == -1)
		return (s);
	bef_s = ft_substr(s, 0, sign_pos);
	space_i = ft_char_pos(s, sign_pos, ' ');
	if (space_i == -1)
		space_i = ft_strlen(s);
	env_s = ft_substr(s, sign_pos + 1, space_i - sign_pos - 1);
	exp_env = expand_env_value(env_s);
	free(env_s);
	final_str = ft_strjoin(bef_s, exp_env);
	free(bef_s);
	if (!final_str)
		return (NULL);
	return (final_str);
}

