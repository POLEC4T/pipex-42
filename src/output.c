/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/07 19:49:28 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief join the strings in strs with first_str at the beginning
 */
static char	*ft_join_strs(char *first_str, char **strs)
{
	char	*res;
	int		i;
	int		len;
	int		j;

	i = -1;
	len = 0;
	while (strs[++i])
		len += ft_strlen(strs[i]);
	len += ft_strlen(first_str);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	while (strs[++i])
	{
		ft_strlcpy(res + j, strs[i], len + 1);
		j += ft_strlen(strs[i]);
	}
	ft_strlcpy(res + j, first_str, len + 1);
	return (res);
}

void	msg_v2(char *msgs[], int fd, t_data *d)
{
	char	*msg_str;

	(void)d;
	msg_str = ft_join_strs("pipex: ", msgs);
	if (!msg_str)
	{
		ft_putendl_fd("pipex: malloc error in msg_str function", STDERR_FILENO);
		exit_process(EXIT_FAILURE, NULL);
	}
	ft_putendl_fd(msg_str, fd);
	free(msg_str);
}

void	msg(char *str1, char *str2, char *str3, int fd)
{
	ft_putstr_fd("pipex: ", fd);
	ft_putstr_fd(str1, fd);
	ft_putstr_fd(str2, fd);
	ft_putendl_fd(str3, fd);
}

void	msg_old(char *str1, char *str2, char *str3, int fd)
{
	char	*msg1;
	char	*msg2;
	char	*msg3;

	msg1 = ft_strjoin(str1, str2);
	msg2 = ft_strjoin(msg1, str3);
	msg3 = ft_strjoin(msg2, "\n");
	ft_putstr_fd(msg3, fd);
	free(msg1);
	free(msg2);
	free(msg3);
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
			msg(strerror(errno), ": ", d->err_file_names[i], STDERR_FILENO);
			exit_process(EXIT_FAILURE, d);
		}
		line = get_next_line(fd);
		while(line)
		{
			ft_putstr_fd(line, STDERR_FILENO);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
		unlink(d->err_file_names[i]);
	}
}
