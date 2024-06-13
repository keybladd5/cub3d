/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:14:45 by polmarti          #+#    #+#             */
/*   Updated: 2023/10/02 12:14:46 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
		*lst = new;
	else if (lst)
		ft_lstlast(*lst)->next = new;
}

/*int main() 
{
    char *ptr;
    ptr = "42";
	char *ptr2;
	ptr = "Hola";
	t_list **lst;
    t_list *new_node = ft_lstnew(ptr);
	t_list *node2 = ft_lstnew(ptr2);

	ft_lstadd_front(lst, new_node);
    printf("Content: %s\n", new_node->content);
	printf("Content: %s\n", node2->content);

    free(new_node);
	free(node2);
    return (0);
}*/