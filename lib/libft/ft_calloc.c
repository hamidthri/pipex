/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:30:26 by htaheri           #+#    #+#             */
/*   Updated: 2023/09/08 13:58:35 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	char	*s;
	int		counter;

	counter = count * size;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	s = (char *) ptr;
	if (ptr != 0)
	{
		while (counter--)
		{
		*s = 0;
		s++;
		}
	}
	return (ptr);
}
// void	*ft_calloc(size_t elementCount, size_t elementSize)
// {
// 	char	*res;

// 	res = malloc(elementSize * elementCount);
// 	if (!res)
// 		return (NULL);
// 	ft_bzero(res, elementSize * elementCount);
// 	return (res);
// }
// void
// 	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr;

// 	ptr = (void*)malloc(count * size);
// 	if (!ptr)
// 		return (NULL);
// 	ft_bzero(ptr, count);
// 	return (ptr);
// }
