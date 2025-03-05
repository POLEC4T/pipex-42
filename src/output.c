/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/04 14:19:36 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    msg(char *str1, char *str2, int fd)
{
    ft_putstr_fd("pipex: ", fd);
    ft_putstr_fd(str1, fd);
    if (str2)
        ft_putstr_fd(": ", fd);
    ft_putendl_fd(str2, fd);
}