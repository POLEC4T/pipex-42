/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:19:33 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/07 20:19:15 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_err_file_names(t_data *d)
{
	int		i_cmds;
	char	*str_i_cmds;

	i_cmds = 0;
	d->err_file_names = ft_calloc(d->nb_cmds + 1, sizeof(char *));
	while (i_cmds < d->nb_cmds)
	{
		str_i_cmds = ft_itoa(i_cmds);
		if (!str_i_cmds)
		{
			msg(strerror(errno), ": ", "ft_itoa", STDERR_FILENO);
			exit_process(EXIT_FAILURE, d);
		}
		d->err_file_names[i_cmds] = ft_strjoin(ERR_FILE_NAME, str_i_cmds);
		if (!d->err_file_names[i_cmds])
		{
			free(str_i_cmds);
			msg(strerror(errno), ": ", "ft_strjoin", STDERR_FILENO);
			exit_process(EXIT_FAILURE, d);
		}
		free(str_i_cmds);
		i_cmds++;
	}
	d->err_file_names[i_cmds] = NULL;
}
