/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:38:32 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/05 15:31:54 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include "errors.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define ERR_MALLOC 1
# define ERR_READ 2
# define ERR_OPEN 3

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
bool	hasnewline(char *string);
bool	setnewlinetoendline(char *string);
char	*getafternewline(char *string);
char	*ft_strdup(const char *b);


#endif