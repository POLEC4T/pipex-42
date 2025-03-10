/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mniemaz <mniemaz@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:47:35 by mniemaz           #+#    #+#             */
/*   Updated: 2025/03/10 13:26:43 by mniemaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	copy = malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	ft_strlcpy(copy, s, len + 1);
	return (copy);
}

int	ft_strchr_idx(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (*(unsigned char *)(s + i) == (char)c)
			return (i);
	return (-1);
}
