/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:22:41 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:41:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


//Args check
/*
void	too_many_args(char **argv)
{
    
}
*/

//Begins minishell and checks the input
int main(int argc, char **argv)
{
    char *input;
	/*if (argc != 1)
		too_many_args(argv);*/
    while(1)
    {
        input = readline("minishell> ");
        if (input) 
        {
            add_history(input);
            pipe_manager(input);
        }
        //Ctrl+D and NULL management to exit program
        if (input == NULL) 
        {
            printf("\n");
            break;        
        }
        //We print the input back
        printf("Input: %s\n", input);
        //Free variable input
        free(input);
    }
	return (0);
}