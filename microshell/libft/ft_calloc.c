/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:39:03 by tbatis            #+#    #+#             */
/*   Updated: 2024/10/03 20:52:51 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	alloc = malloc(nmemb * size);
	if (alloc == NULL)
		return (NULL);
	ft_bzero(alloc, nmemb * size);
	return (alloc);
}

/*
int	main(void)
{
	size_t	nmemb;
	size_t	size;
	int		*arr;

	nmemb = SIZE_MAX;
	size = 2;
	arr = (int *)ft_calloc(nmemb, size);
	if (arr == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	printf("arr[%zu] = %d\n", size, arr[1]);
	// for (size_t i = 0; i < nmemb; i++)
	// {
	// }
	free(arr);
	return (0);
} */
