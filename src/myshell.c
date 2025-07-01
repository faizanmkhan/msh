/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:08:40 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/01 17:08:41 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/myshell.h"

int	g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_shell_data	myshell;

	(void) argc;
	(void) argv;
	init_shell_data(&myshell, envp);
	core_shell_loop(&myshell);
	cleanup_shell(&myshell);
	return (0);
}
