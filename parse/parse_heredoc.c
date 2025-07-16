/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:20:43 by faikhan           #+#    #+#             */
/*   Updated: 2025/07/16 20:57:15 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

char	*expanded_line(t_appdata *appdata, char *line)
{
	int		i;
	char	**words;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = expand_heredoc_vars(appdata, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	free_ptr(line);
	return (join_words_with_spaces(words));
}

static bool	parse_line(t_appdata *appdata, char **line, t_fds *fds,
		bool *result)
{
	if (*line == NULL)
	{
		ft_print_cmd_error("warning",
			"here-document delimited by end-of-file: wanted",
			fds->heredoc_delim, true);
		*result = true;
		return (false);
	}
	if (ft_strncmp(*line, fds->heredoc_delim, ft_strlen(fds->heredoc_delim)
			+ 1) == 0)
	{
		*result = true;
		return (false);
	}
	if (fds->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = expanded_line(appdata, *line);
		if (!(*line))
		{
			free_ptr(*line);
			*result = false;
			return (false);
		}
	}
	return (true);
}

static bool	get_heredoc_lines(t_appdata *appdata, t_fds *fds, int fd)
{
	char	*line;
	bool	result;

	result = false;
	while (true)
	{
		set_signals_for_parsing();
		line = readline("> ");
		set_signals_for_execution();
		if (!parse_line(appdata, &line, fds, &result))
			break ;
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(line);
	return (result);
}

static bool	create_heredoc(t_appdata *appdata, t_fds *fds)
{
	int		tmp_fd;
	bool	result;

	result = true;
	tmp_fd = open(fds->input_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	result = get_heredoc_lines(appdata, fds, tmp_fd);
	wrapper_close_pipe(&tmp_fd);
	return (result);
}

void	parse_heredoc(t_appdata *appdata, t_cmd **head_cmd, t_tok **head_token)
{
	t_cmd	*cmd;
	t_tok	*tok;
	t_fds	*fds;

	tok = *head_token;
	cmd = last_cmd(*head_cmd);
	init_fds(cmd);
	fds = cmd->fds;
	if (!remove_input_file_ref(fds))
		return ;
	fds->heredoc_delim = find_delimiter(tok->nxt->data, &(fds->heredoc_quotes));
	fds->input_file = heredoc_filename();
	if (create_heredoc(appdata, fds))
		fds->fd_in = open(fds->input_file, O_RDONLY);
	else
		fds->fd_in = -1;
	if (tok->nxt->nxt)
		tok = tok->nxt->nxt;
	else
		tok = tok->nxt;
	*head_token = tok;
}
