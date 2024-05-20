/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:08:26 by root              #+#    #+#             */
/*   Updated: 2024/05/20 17:44:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    pipe_manager(char *input)
{
    int pipe_manager_error = 0;
    int found_pipe = 0;
    int found_non_space_before_pipe = 0;
    int i = 0;
    
    while (input[i] != '\0') 
    {
        //Ignore spaces
        if (input[i] == ' ') 
        {
            continue;
        }
        else if (input[i] == '|') 
        {
            found_pipe = 1;
            // Si encontramos un pipe sin nada antes (sin contar espacios), hay un error
            if (!found_non_space_before_pipe) 
            {
                pipe_manager_error = 1;
                printf("Error con el pipe");
            }
        } 
        // Encontramos un carácter que no es espacio
        else 
        {
            found_non_space_before_pipe = 1;
            // Si encontramos un carácter no espacio después de un pipe, reseteamos el flag de pipe encontrado
            if (found_pipe) {
                found_pipe = 0;
            }
        }
        i++;
    }
}
