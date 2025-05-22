#include "../minishell.h"

int	chr_in_str(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str || !c)
		return (-1);
	while (str[i])
		if (str[i++] == c)
			count++;
	return (count);
}

char	**fill_buffer_paths(char **paths, int count, char *str)
{
	int	last_occ;
	int	i;
	int	j;
	int	len;

	if (!str || !paths)
		return (NULL);
	len = ft_strlen(str);
	i = -1;
	j = -1;
	last_occ = 0;
	while (++i < count)
	{
		while (++j < len + 1)
		{
			if (str[j] == ':' || str[j] == '\0')
			{
				paths[i] = ft_substr(str, last_occ, (j) - last_occ);
				last_occ = ++j;
				break ;
			}
		}
	}
	paths[i] = NULL;
	return (paths);
}

char	**separate_paths(char *str)
{
	char	**paths;
	int		count;

	count = chr_in_str(str, ':') + 1;
	paths = (char **)malloc(sizeof(char *) * (count + 1));
	if (!paths || count < 1)
	{
		perror("Alloc error!");
		return (NULL);
	}
	paths = fill_buffer_paths(paths, count, str);
	if (!paths)
	{
		perror("Error");
		return (NULL);
	}
	return (paths);
}
//void	check_cmd()
//{
//	char	**paths;
//	char	*path_var;
//	int	len;
//	//if not buildin cmd found
//	path_var = ft_strdup(getenv("PATH"));
//}

/*
//int	main()
//{
//	//check_cmd();
//	char *str = "test:dupa/ale/akscja:okey:bbbb";
//	char **a = separate_paths(str);
//	if (a == NULL)
//		perror("ERROR!");
	int i = 0;
	while (a[i])
	{
		printf("path %d: %s\n", i, a[i]);
		i++;
	}
	printf("path %d: %s\n", i, a[i]);
	return (0);
}
*/
