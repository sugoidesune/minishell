/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:55:03 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/13 15:55:26 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	free_data_and_exit(t_mini *data, int exit_code);
void	free_lexer_list(t_lexer **lexer_list);
void	free_parser_list(t_parser **parser_list);
void	free_strarr(char **strarr);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
#endif
