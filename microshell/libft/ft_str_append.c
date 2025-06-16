/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:36:58 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/11 23:04:54 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// this functions appends the string `src` to the end of the string `dst`
char	*ft_str_append(char *dst, const char *src)
{
	int	dst_len;
	int	i;

	dst_len = 0;
	i = 0;
	while (dst[dst_len])
		dst_len++;
	while (src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst);
}

// // testing main
// #include <stdio.h>
// #include <stdlib.h>
// int main(void)
// {
// 	char *dst = malloc(200);
// 	if (!dst)
// 		return (1);
// 	dst[0] = '\0'; // Initialize dst as an empty string
// 	const char *src = "Hello, ";
// 	ft_str_append(dst, src);
// 	ft_str_append(dst, "World!");
// 	ft_str_append(dst, " YOYOYOYO aight tight");
// 	printf("%s\n", dst); // Should print "Hello, World!"
// 	free(dst);
// 	return (0);
// }