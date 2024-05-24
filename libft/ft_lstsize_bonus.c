/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:35:55 by polmarti          #+#    #+#             */
/*   Updated: 2023/10/02 11:35:57 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*int main()
{
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		*str = ft_strdup("lorem");
	char		*str2 = ft_strdup("ipsum");
	char		*str3 = ft_strdup("dolor");
	char		*str4 = ft_strdup("sit");
	elem = ft_lstnew(str);
	elem2 = ft_lstnew(str2);
	elem3 = ft_lstnew(str3);
	elem4 = ft_lstnew(str4);
	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;
	printf("%d\n", ft_lstsize(elem));
	return (0);

}*/