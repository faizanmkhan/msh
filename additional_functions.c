#include "myshell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (unsigned char)(*str1) - (unsigned char)(*str2);
}
