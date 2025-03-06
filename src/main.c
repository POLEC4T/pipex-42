/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/06 13:37:40 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_if_wrong_ac(int ac, char **av)
{
	if (BONUS && ac < 5)
	{
		msg("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile", NULL,
			STDERR_FILENO);
		exit(1);
	}
	if (BONUS && ft_strncmp(av[1], "here_doc", 8) == 0 && ac < 6)
	{
		msg("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile", NULL,
			STDERR_FILENO);
		exit(1);
	}
	else if (!BONUS && ac != 5)
	{
		msg("Usage: ./pipex infile cmd1 cmd2 outfile", NULL, STDERR_FILENO);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	d;
	int		status;

	exit_if_wrong_ac(ac, av);
	init_data(&d, av, ac, env);
	start_children(&d, av, env);
	status = wait_children(&d);
	exit_process(status, &d);
}
