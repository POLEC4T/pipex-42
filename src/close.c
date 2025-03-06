/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:37:03 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/06 13:29:25 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	close_fds_and_pipes(t_data *d)
{
	close_fds_in_out(d);
	close_pipes(d);
}

void	close_fds_in_out(t_data *d)
{
	if (d->fds.in != -1)
		close(d->fds.in);
	if (d->fds.out != -1)
		close(d->fds.out);
}

void	close_pipe_index(int index, t_data *d)
{
	if (d->pipes[index][READ] != -1)
		close(d->pipes[index][READ]);
	if (d->pipes[index][WRITE] != -1)
		close(d->pipes[index][WRITE]);
}

void	close_pipes(t_data *d)
{
	int	i;

	i = 0;
	while (d->pipes[i])
	{
		close_pipe_index(i, d);
		i++;
	}
}
