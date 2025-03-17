/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:53:32 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/17 20:22:32 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while(*str)
    {
        i++;
        str++;
    }
    return (i);
}

char *ft_strdup(char *value)
{
    char *str;
    char *result;

    str = malloc(ft_strlen(value) + 1);
    if (!str)
    {
        perror("malloc");
        exit(1);
    }
    result = str;
    while (*value)
    {
        *str = *value;
        str++;
        value++;
    }
    *str = '\0';
    return (result);
}