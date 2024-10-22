/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aditer <aditer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:14:24 by rderkaza          #+#    #+#             */
/*   Updated: 2024/10/22 14:00:42 by aditer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_sigint_hd(int sig)
{
	g_sigflag = sig;
	ft_putstr_fd("\n", 1);
	close(STDIN_FILENO);
}

void	handle(int sig)
{
	g_sigflag = sig;
}

void	handle_here_doc(int sig)
{
	g_sigflag = sig;
	ft_putendl_fd("", STDOUT_FILENO);
	close(STDIN_FILENO);
}

void	handle_sigint(int sig)
{
	g_sigflag = sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	g_sigflag = sig;
	ft_putstr_fd("Quit (core dumped)\n", 1);
}
