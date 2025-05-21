#include "../minishell.h"

char	**separate_paths(char *str)
{
	char	**paths;
	int	i;
	int	j;
	int	count;
	int	last_occ;
	int	start_occ;

	i = 0;
	j = 0;
	start_occ = 0;
	count = 1;
	while (str[j])
		if (str[j++] == ':')
			count++;
	j = 0;
	i = 0;
	paths = (char **)malloc(sizeof(char *) * (count + 1));
	while (i <= count)
	{
		while (str[j])
		{
			if (str[j] == ':')
			{
				paths[i] = ft_substr(str, last_occ, 
						//HERE GO FILLING THOSE PATHS!!! 
		}
	}
}
void	check_cmd()
{
	char	**paths;
	char	*path_var;
	int	len;
	//if not buildin cmd found
	path_var = ft_strdup(getenv("PATH"));
}

int	main()
{
	check_cmd();
	return (0);
}
