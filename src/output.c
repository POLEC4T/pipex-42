/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/10 13:28:26 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	msg(char *str1, char *str2, char *str3, int fd)
{
	ft_putstr_fd("pipex: ", fd);
	ft_putstr_fd(str1, fd);
	ft_putstr_fd(str2, fd);
	ft_putendl_fd(str3, fd);
}

void	display_errors(t_data *d)
{
	int		i;
	char	*line;
	int		fd;

	i = -1;
	line = NULL;
	while (++i < d->nb_cmds)
	{
		fd = open(d->err_file_names[i], O_RDONLY);
		if (fd == -1)
		{
			msg(d->err_file_names[i], ": ", strerror(errno), STDERR_FILENO);
			continue ;
		}
		line = get_next_line(fd);
		while (line)
		{
			ft_putstr_fd(line, STDERR_FILENO);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		unlink(d->err_file_names[i]);
	}
}
