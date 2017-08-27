/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 21:35:21 by jaleman           #+#    #+#             */
/*   Updated: 2016/08/16 21:35:22 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks if the character is a lowercase letter.
*/

static int	ft_islower(int c)
{
	return (c >= 'a' && 'z' >= c);
}

/*
** Checks if the character is a space.
*/

static int	ft_isspace(int c)
{
	return (c == '\t' || c == '\v' || c == '\n' || c == '\r' || c == '\f' \
			|| c == ' ');
}

/*
** Capitalized each word (separated by a space), of a string.
*/

char		*ft_strcap(char *str)
{
	int		i;

	i = 0;
	if (ft_islower(str[i]))
		str[i] -= 32;
	while (str[i++])
		if (ft_isspace(str[i]))
			if (ft_islower(str[i + 1]))
				str[i + 1] -= 32;
	return (str);
}
