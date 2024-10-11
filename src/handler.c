/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rderkaza <rderkaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:14:24 by rderkaza          #+#    #+#             */
/*   Updated: 2024/10/11 14:20:00 by rderkaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	handle_sigint_hd(int sig)
{
	g_sigflag = sig;
	ft_putstr_fd("\n", 1);
	close(STDIN_FILENO);
}
