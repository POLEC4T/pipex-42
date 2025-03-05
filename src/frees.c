/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:42:20 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/04 10:51:33 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void close_fds(t_data *d)
{
	if (d->fds.in != -1)
		close(d->fds.in);
	if (d->fds.out != -1)
		close(d->fds.out);
	close(d->pipe[0]);
	close(d->pipe[1]);
}

void free_and_close_fds_data(t_data *d)
{
	// free_str_tab(d->cmd);
	// free(d->cmd_path);
	free_str_tab(d->paths);
}

void	free_str_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	exit_error(int error_status, t_data *data)
{
	if (data)
	{
		close_fds(data);
		if (data->cmd != NULL)
			free_str_tab(data->cmd);
		if (data->cmd_path != NULL)
			free(data->cmd_path);
		if (data->paths != NULL)
			free_str_tab(data->paths);
	}
	exit(error_status);
}
