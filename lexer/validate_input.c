/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmusic <mmusic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:41:54 by mmusic            #+#    #+#             */
/*   Updated: 2025/04/10 20:32:19 by mmusic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
state 0 - outside quotes
state 1 - inside single quotes
state 2 - inside double quotes
*/

int validate_quotes(char *input)
{
    int state = 0;
    if (!input)
        return -1;
    if (input[0] == '\0')
        return -1;
    while(*input)
    {
        if (state == 0)
        {
            if (*input == '\'')
                state = 1;
            else if (*input == '\"')
                state = 2;
        }
        else if (state == 1)
        {
            if (*input == '\'')
                state = 0;
        }
        else if (state == 2)
        {
            if (*input == '\"')
                state = 0;
        }
        else
        {
            if (*input == '\'' || *input == '\"')
                return -1;
        }
        if (*input == '\\')
        {
            input++;
            if (*input == '\'' || *input == '\"')
                return -1;
        }
        else
        {
            if (*input == '\\')
                return -1;
        }
        /* if (*input == ' ')
            return -1;
        if (*input == '\t')
            return -1;
        if (*input == '\n')
            return -1;     */        
        input++;
    }

    
    return 0;
}