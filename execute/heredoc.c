/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:45:09 by skaynar           #+#    #+#             */
/*   Updated: 2025/07/23 17:59:11 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_heredoc(t_cmd *fakecmd, int i, int fd)
{
    char *line;
    
    fd = open("garbage", O_CREAT | O_TRUNC | O_RDWR, 0777);
    while (1 && fakecmd->heredoc_delim[i])
    {
        line = readline(">");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, fakecmd->heredoc_delim[i]) == 0)
		{
			free(line);
            if(fakecmd->heredoc_delim[++i])
                fd = open("garbage", O_CREAT | O_TRUNC | O_RDWR, 0777);
		}
        else
        {
            ft_putstr_fd(line, fd);
            ft_putstr_fd("\n", fd);
            free(line);
        }
    }
    fd = open("garbage", O_RDONLY);
    dup2(fd, 0);
    close(fd);
    unlink("garbage");
}
