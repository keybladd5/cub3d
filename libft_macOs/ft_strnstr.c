/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:14:22 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/19 10:14:26 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s;
	char	*tf;
	size_t	i;
	size_t	tmp;

	i = 0;
	if (haystack == needle || !*needle)
		return ((char *)haystack);
	while (*haystack && i < len)
	{
		s = (char *)haystack;
		tf = (char *)needle;
		tmp = 0;
		while (*s && *tf && *s == *tf && tmp + i < len)
		{
			++s;
			++tf;
			tmp++;
		}
		if (!*tf)
			return ((char *)haystack);
		++haystack;
		i++;
	}
	return (0);
}

/*int	main(void)
{
  char	*s1 = "aaabcabcd";
  char	*s2 = "cd";
  //char *s1 = "MZIRIBMZIRIBMZE123";
  //char *s2 = "MZIRIBMZE";
  //size_t max = strlen(s2);
  //printf("%zu\n", max);
  printf("%s\n", strnstr("aabcabc", "aabc", -1));
  printf("%s\n", ft_strnstr("aabcabc", "aabc", -1));

  //printf("%s\n", ft_strnstr(dest, to_find, 0));
  //printf("%s\n", strnstr(dest, to_find, 0));
  return (0);
}*/