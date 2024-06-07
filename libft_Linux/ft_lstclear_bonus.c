/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:47:42 by polmarti          #+#    #+#             */
/*   Updated: 2023/10/02 13:47:45 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*toiterate;

	toiterate = *lst;
	if (!lst || !del)
		return ;
	while (toiterate)
	{
		*lst = (*lst)->next;
		ft_lstdelone(toiterate, del);
		toiterate = *lst;
	}
}
