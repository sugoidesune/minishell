/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbatis <tbatis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:31:11 by tbatis            #+#    #+#             */
/*   Updated: 2025/06/11 20:19:07 by tbatis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// error lib
int		*error_store(void);
int		error_code(void);
bool	had_error(void);
void	*set_error(int error);

# define ERR_MALLOC 1
# define ERR_READ 2
# define ERR_OPEN 3
# define ERR_NOT_FOUND 127
# define ERR_NOT_EXECUTABLE 126