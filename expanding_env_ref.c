//from gpt, ignore

static int is_var_char(char c)
{
    return isalnum(c) || c == '_';
}

static char *expand_exit_status(t_shell *shell, char *result, int *j)
{
    char exit_str[16];
    sprintf(exit_str, "%d", shell->exit_status);
    strcat(result, exit_str);
    *j += strlen(exit_str);
    return result;
}

static char *expand_env_variable(t_shell *shell, const char *str, int *i, char *result, int *j)
{
    int start = ++(*i);
    while (str[*i] && is_var_char(str[*i]))
        (*i)++;
    int len = *i - start;
    char *var_name = malloc(len + 1);
    strncpy(var_name, &str[start], len);
    var_name[len] = '\0';

    char *env_value = get_env_value(shell, var_name);
    if (env_value)
    {
        strcat(result, env_value);
        *j += strlen(env_value);
    }
    free(var_name);
    return result;
}

char *expand_variables(t_shell *shell, char *str)
{
    if (!str || !strchr(str, '$'))
        return ft_strdup(str);

    char *result = malloc(1024); /* Simple buffer, could be improved */
    result[0] = '\0';

    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] == '$')
        {
            if (str[i + 1] == '?')
            {
                expand_exit_status(shell, result, &j);
                i += 2;
                continue;
            }
            else if (str[i + 1] && is_var_char(str[i + 1]))
            {
                expand_env_variable(shell, str, &i, result, &j);
                continue;
            }
        }
        result[j++] = str[i++];
        result[j] = '\0';
    }
    return result;
}