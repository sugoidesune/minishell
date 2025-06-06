/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:02:55 by tbatis            #+#    #+#             */
/*   Updated: 2025/05/30 20:49:52 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat(char *a, char *b)
{
	char	*cat;
	char	*catstart;

	cat = malloc(((ft_strlen(b) + ft_strlen(a)) * sizeof(char)) + 1);
	if (cat == NULL)
		return (set_error(ERR_MALLOC));
	catstart = cat;
	while (a && *a)
	{
		*cat = *a;
		cat++;
		a++;
	}
	while (b && *b)
	{
		*cat = *b;
		cat++;
		b++;
	}
	*cat = '\0';
	return (catstart);
}

char	*strreadalloc(int fd, int buffer_size)
{
	ssize_t	bytesread;
	char	*buffer;

	buffer = malloc(buffer_size + 1);
	if (!buffer)
		return (set_error(ERR_MALLOC));
	bytesread = read(fd, buffer, buffer_size);
	if (bytesread < 0)
	{
		free(buffer);
		return (set_error(ERR_READ));
	}
	buffer[(size_t)bytesread] = '\0';
	return (buffer);
}

// collects what read is reading until it finds a newline in last read buffer.
// this is the full raw read output therefore the newline is not guaranteed to
// be at the end.
//
// previous_str
// - will be used as prefix of the read stream
// - if it has a newline function will not read and just return previous string

char	*collectnewline(char *previous_str, int fd)
{
	ssize_t	bytesread;
	char	*buffer;
	char	*everything_read;
	char	*previous_read;

	if (previous_str == NULL)
		previous_str = "";
	everything_read = ft_strdup(previous_str);
	if (everything_read == NULL)
		return (set_error(ERR_MALLOC));
	bytesread = 1;
	while (everything_read && bytesread > 0 && !hasnewline(everything_read))
	{
		buffer = strreadalloc(fd, BUFFER_SIZE);
		if (!buffer)
			return (free(everything_read), NULL);
		bytesread = ft_strlen(buffer);
		previous_read = everything_read;
		everything_read = concat(everything_read, buffer);
		free(buffer);
		free(previous_read);
	}
	return (everything_read);
}

char	*get_next_line(int fd)
{
	static char	*cache = NULL;
	char		*full_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(cache);
		cache = NULL;
		return (NULL);
	}
	full_read = collectnewline(cache, fd);
	free(cache);
	cache = NULL;
	if (!full_read || ft_strlen(full_read) == 0 || had_error())
	{
		free(full_read);
		return (NULL);
	}
	cache = getafternewline(full_read);
	if (!cache)
	{
		free(full_read);
		return (NULL);
	}
	setnewlinetoendline(full_read);
	return (full_read);
}
/*
#include <fcntl.h>

 #include <stdio.h>

int main (void)
{
	int	fd;
	int	fdtwo;

	fd = open("simple.fdf", O_RDONLY);
	//fdtwo = open("second.txt", O_RDONLY);
	printf("line 1:%s", get_next_line(fd));
	//printf("second: %s", get_next_line(fdtwo));
	printf("line 2:%s", get_next_line(fd));
	printf("line 3:%s", get_next_line(fd));
	//printf("second:%s", get_next_line(fdtwo));
	//printf("%s", get_next_line(1));
	close(fd);
	//close(fdtwo);
	return (0);
}


int	mainn(void)
{

   int fd = open("read_error.txt", O_RDONLY);
   char * one_line = get_next_line(fd);
   printf("FIRST LINE:\n%s\n",one_line);
   free(one_line);

   one_line = get_next_line(fd);
   printf("SECOND LINE:\n%s\n",one_line);
   free(one_line);
   one_line = get_next_line(fd);
   printf("THIRD LINE:\n%s\n",one_line);
   free(one_line);

			char *temp;
			do {
				temp = get_next_line(fd);
				printf("LOOPIN: %s\n", temp);
				free(temp);
			} while (temp != NULL);

   one_line = get_next_line(fd);
   printf("ONE MORE LINE:\n%s\n",one_line);
   free(one_line);

   one_line = get_next_line(fd);
   printf("NOMORE LINE:\n%s\n",one_line);
   free(one_line);
   close(fd);
   fd = open("read_error.txt", O_RDONLY);

   one_line = get_next_line(fd);
   printf("FIRST LINE:\n%s\n",one_line);
   free(one_line);

   one_line = get_next_line(fd);
   printf("SECOND LINE:\n%s\n",one_line);
   free(one_line);

   one_line = get_next_line(fd);
   printf("THIRD LINE:\n%s\n",one_line);
   free(one_line);

   one_line = get_next_line(fd);
   printf("FOURTH LINE:\n%s\n",one_line);
   free(one_line);

   one_line = get_next_line(fd);
   printf("NOMORE LINE:\n%s\n",one_line);
   free(one_line);
   // char *first_read = collector(NULL, fd);
   // char *leftovers = getafternewline(first_read);
   // setnewlinetoendline(first_read);
   // printf("FIRST LINE:\n%s\n",first_read);
   // free(first_read);
   // printf("LEFTOVERS:\n%s\n",leftovers);
   // //free(leftovers);

   // char *second_read = collector(leftovers, fd);
   // leftovers = getafternewline(first_read);
   // setnewlinetoendline(second_read);
   // printf("SECOND LINE:\n%s\n",second_read);
   // free(second_read);
   // printf("LEFTOVERS:\n%s\n",leftovers);
   // free(leftovers);

   close(fd);
   return(0);
} */
