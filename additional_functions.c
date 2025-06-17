#include "myshell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>');
}
