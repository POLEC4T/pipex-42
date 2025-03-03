/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miloniemaz <mniemaz@student.42lyon.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/02/28 10:09:50 by miloniemaz       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    msg(char *str1, char *str2, int fd)
{
    ft_putstr_fd("pipex: ", fd);
    ft_putstr_fd(str1, fd);
    if (str2[0])
        ft_putstr_fd(": ", fd);
    ft_putendl_fd(str2, fd);
}