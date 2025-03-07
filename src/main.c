/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/07 19:48:03 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_if_wrong_ac(int ac, char **av)
{
	int	is_here_doc;

	is_here_doc = ft_strncmp(av[1], "here_doc", 9) == 0;
	if (BONUS && ac < (5 + is_here_doc))
	{
		msg("Bonus usage 1: ", BONUS_USAGE_1, "", STDERR_FILENO);
		msg("Bonus usage 2: ", BONUS_USAGE_2, "", STDERR_FILENO);
		exit(1);
	}
	else if (!BONUS && ac != 5)
	{
		msg("Mandatory usage", ": ", MANDATORY_USAGE, STDERR_FILENO);
		exit(1);
	}
}

void	process_here_doc(t_data *d, char *limiter)
{
	int		i;
	char	*str;
	int		hd_fd;

	str = NULL;
	hd_fd = open(HEREDOC_FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (hd_fd == -1)
	{
		msg(strerror(errno), ": ", HEREDOC_FILENAME, STDERR_FILENO);
		exit_process(EXIT_FAILURE, d);
	}
	while (1)
	{
		if (str)
			free(str);
		i = -1;
		while (++i < d->nb_cmds - 1)
			write(STDOUT_FILENO, "pipe ", 5);
		write(STDOUT_FILENO, "heredoc> ", 9);
		str = get_next_line(STDIN_FILENO);
		str[ft_strlen(str) - 1] = '\0';
		if (!ft_strncmp(str, limiter, ft_strlen(limiter) + 1))
			break ;
		ft_putendl_fd(str, hd_fd);
	}
	close(hd_fd);
	free(str);
}

int	main(int ac, char **av, char **env)
{
	t_data	d;
	int		status;

	exit_if_wrong_ac(ac, av);
	init_data(&d, av, ac, env);
	if (d.is_here_doc)
		process_here_doc(&d, av[2]);
	start_children(&d, av, env);
	status = wait_children(&d);
	display_errors(&d);
	exit_process(status, &d);
}
