/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:03:54 by ade-tole          #+#    #+#             */
/*   Updated: 2024/02/15 15:03:56 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_aux(int i, char *s1, char *s2)
{
	size_t	j;
	char	*rtrn;

	i = ft_strlen(s1);
	rtrn = (char *)malloc(sizeof(char) * \
	(ft_strlen(s1) + ft_strlen(s2) +1));
	if (!rtrn)
		exit (1);
	rtrn = ft_memcpy(rtrn, s1, (int)i);
	free(s1);
	j = 0;
	while (s2[j])
	{
		rtrn[i] = s2[j];
		i++;
		j++;
	}
	rtrn[i] = '\0';
	return (rtrn);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*rtrn;

	rtrn = NULL;
	if (!s1)
	{
		rtrn = ft_strdup(s2);
		if (!rtrn)
			exit (1);
	}
	else
		rtrn = ft_aux(0, s1, s2);
	free(s2);
	return (rtrn);
}
