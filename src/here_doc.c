/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:03:02 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/12 12:03:05 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief removes the last character of the string
 * @details made to remove the '\n' character at the end of the ret of gnl
 */
static char	*shorter(char *str)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (str_len > 0)
		str[str_len - 1] = '\0';
	return (str);
}

static void	msg_exit_here_doc(char *text, t_data *d)
{
	msg(text, ": ", strerror(errno), STDERR_FILENO);
	exit_process(EXIT_FAILURE, d);
}

/**
 * @brief process the here_doc feature
 * @details read the input from the user until the limiter is found
 * and write it to a file
 */
void	process_here_doc(t_data *d, char *limiter)
{
	char	*str;
	int		hd_fd;

	hd_fd = open(HEREDOC_FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (hd_fd == -1)
		msg_exit_here_doc(HEREDOC_FILENAME, d);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		str = get_next_line(STDIN_FILENO);
		if (!str || !ft_strncmp(shorter(str), limiter, ft_strlen(limiter) + 1))
			break ;
		ft_putendl_fd(str, hd_fd);
		free(str);
	}
	close(hd_fd);
	free(str);
}
