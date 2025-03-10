/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:19:33 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/10 11:18:45 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	msg_exit(char *text, t_data *d)
{
	msg(text, ": ", strerror(errno), STDERR_FILENO);
	exit_process(EXIT_FAILURE, d);
}

void	set_err_file_names(t_data *d)
{
	int		i_cmds;
	char	*str_i_cmds;

	i_cmds = -1;
	d->err_file_names = ft_calloc(d->nb_cmds + 1, sizeof(char *));
	if (!d->err_file_names)
		msg_exit("ft_calloc", d);
	while (++i_cmds < d->nb_cmds)
	{
		str_i_cmds = ft_itoa(i_cmds);
		if (!str_i_cmds)
			msg_exit("ft_itoa", d);
		d->err_file_names[i_cmds] = ft_strjoin(ERR_FILE_NAME, str_i_cmds);
		free(str_i_cmds);
		if (!d->err_file_names[i_cmds])
			msg_exit("ft_strjoin", d);
	}
	d->err_file_names[i_cmds] = NULL;
}
