/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:13:21 by polmarti          #+#    #+#             */
/*   Updated: 2023/10/03 10:13:23 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_lst;
	t_list	*tmp_content;

	new_lst = 0;
	while (lst)
	{
		tmp_content = f(lst->content);
		tmp = ft_lstnew(tmp_content);
		if (!tmp)
		{
			ft_lstclear(&new_lst, del);
			free(tmp_content);
			return (0);
		}
		ft_lstadd_back(&new_lst, tmp);
		lst = lst->next;
	}
	return (new_lst);
}

/*void    ft_del(void *content)
{
	free(content);
}
void	*ft_map(void *ct)
{
	int i;
	void	*c;
	char	*pouet;

	c = ct;
	i = -1;
	pouet = (char *)c;
	while (pouet[++i])
		if (pouet[i] == 'o')
			pouet[i] = 'a';
	return (c);
}

int	main()
{
	int			i;
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	t_list		*list;
	char		*str = strdup("lorem");
	char		*str2 = strdup("ipsum");
	char		*str3 = strdup("dolor");
	char		*str4 = strdup("sit");

	i = 0;
	elem = ft_lstnew(str);
	elem2 = ft_lstnew(str2);
	elem3 = ft_lstnew(str3);
	elem4 = ft_lstnew(str4);
	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;
	ft_lstmap(elem, &ft_map, &ft_del);
	while (elem)
		{
			printf("%s\n", elem->content);
			elem = elem->next;
			i++;
		}
		free(elem);
		free(elem->content);
		free(elem2);
		free(elem2->content);
		free(elem3);
		free(elem3->content);
		free(elem4);
		free(elem4->content);
	return (0);
}

Cuando creas un nuevo elemento, 
su contenido te lo da la función pasada 
por parámetro que reserva memoria para 
hacerlo, entonces si cuando vas a crear 
el nodo falla, y no tienes un puntero al 
contenido, vas a liberar la lista pero no 
ese contenido, porque ese nodo no se ha 
creado ni mucho menos añadido a la lista.

DEBE SER EN 3 VARIABLES*/