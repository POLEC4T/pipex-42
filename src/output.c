/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:41:22 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/12 15:00:32 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @details using a buffer in order to write every strs in one putstr
 */
void	msg(char *str1, char *str2, char *str3, int fd)
{
	char	buffer[1024];
	int		len1;
	int		len2;
	int		len3;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	len3 = ft_strlen(str3);
	if (7 + len1 + len2 + len3 + 1 > 1024)
	{
		ft_putstr_fd("pipex: msg: buffer overflow\n", STDERR_FILENO);
		return ;
	}
	ft_memcpy(buffer, "pipex: ", 7);
	ft_memcpy(buffer + 7, str1, len1);
	ft_memcpy(buffer + 7 + len1, str2, len2);
	ft_memcpy(buffer + 7 + len1 + len2, str3, len3);
	buffer[7 + len1 + len2 + len3] = '\n';
	buffer[7 + len1 + len2 + len3 + 1] = '\0';
	write(fd, buffer, 7 + len1 + len2 + len3 + 1);
}
