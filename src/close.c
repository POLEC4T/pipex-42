/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:37:03 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/10 13:06:48 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	close_fds_and_pipes(t_data *d)
{
	close_fds_in_out(d);
	close_pipes(d);
}

void	my_close(int *fd)
{
	if (*fd != -1)
		close(*fd);
	*fd = -1;
}

void	close_fds_in_out(t_data *d)
{
	my_close(&d->fds.in);
	my_close(&d->fds.out);
}

void	close_pipes(t_data *d)
{
	int	i;

	i = 0;
	while (d->pipes && d->pipes[i])
	{
		my_close(&d->pipes[i][READ]);
		my_close(&d->pipes[i][WRITE]);
		i++;
	}
}
