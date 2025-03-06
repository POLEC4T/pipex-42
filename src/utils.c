/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/06 14:14:46 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief redirects the standard input and output to the given file descriptors
 */
void	redirect(int input, int output, t_data *d)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		exit_process(EXIT_FAILURE, d);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		exit_process(EXIT_FAILURE, d);
	}
}

void	secure_fork(int *pid, t_data *d)
{
	*pid = fork();
	if (*pid == -1)
	{
		msg("Error fork", strerror(errno), STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
}

/**
 * @returns ["", NULL]
 * @details made because the ft_split function returns [NULL] if the string is
 * empty
 */
char	**empty_split(void)
{
	char	**res;

	res = malloc(2 * sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = malloc(1 * sizeof(char));
	if (!res[0])
	{
		free(res);
		return (NULL);
	}
	res[0][0] = '\0';
	res[1] = NULL;
	return (res);
}
