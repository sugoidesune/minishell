/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:53:32 by mmusic            #+#    #+#             */
/*   Updated: 2025/03/19 16:23:34 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    if(!str)
        return (-1);
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

    if(!value)
        return (NULL);
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

char *strndup(const char *s, size_t n)
{
    size_t len = 0;
    char *result;
    
    // Find length of s, but not more than n
    while (len < n && s[len])
        len++;
    
    result = malloc(len + 1);
    if (!result)
    {
        perror("malloc");
        exit(1);
    }
    
    // Copy the string
    for (size_t i = 0; i < len; i++)
        result[i] = s[i];
    
    result[len] = '\0';
    return result;
}