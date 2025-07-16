/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <korzecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:54:16 by korzecho          #+#    #+#             */
/*   Updated: 2025/07/16 13:54:25 by korzecho         ###   ########.fr       */
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
	//cleanup_shell(&myshell);
	free_env(myshell.shell_env);
	return (0);
}
