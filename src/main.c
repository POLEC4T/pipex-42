/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/12 15:12:28 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	exit_if_wrong_ac(int ac, char **av)
{
	int	is_here_doc;

	is_here_doc = av[1] && ft_strncmp(av[1], "here_doc", 9) == 0;
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
	exit_process(status, &d);
}
