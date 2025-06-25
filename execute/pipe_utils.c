/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:30:29 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/16 21:52:30 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_access(char *exec, char **opt, char **path)
{
	if (!access(exec, F_OK | X_OK))
	{
		clear_array(opt);
		clear_array(path);
		return (1);
	}
	return (0);
}

char	*ft_get_path(char **ep)
{
	int		i;
	char	*path;

	path = NULL;
	i = 0;
	while (ep[i])
	{
		if (!ft_strncmp(ep[i], "PATH=", 5))
		{
			path = ep[i] + 5;
			break ;
		}
		i++;
	}
	if (!path)
		exit(1);
	return (path);
}

char	*ft_get_cmd(char *cmd, char **ep)
{
	char	**path;
	char	*part;
	char	**opt;
	char	*exec;
	int		i;

	i = -1;
	path = ft_split(ft_get_path(ep), ':');
	opt = ft_split(cmd, ' ');
	if (!opt || !path)
		exit(0);
	while (path[++i])
	{
		part = ft_strjoin(path[i], "/");
		exec = ft_strjoin(part, opt[0]);
		free(part);
		if (ft_access(exec, opt, path))
			return (exec);
		free(exec);
	}
	clear_array(path);
	clear_array(opt);
	return (cmd);
}

void	ft_execute(char **commands, char **ep)
{
	char	*path;

	if (!commands || !commands[0])
	{
		clear_array(commands);
		exit(1);
	}
	path = ft_get_cmd(commands[0], ep);
	if (execve(path, commands, ep) == -1)
	{
		ft_putstr_fd(commands[0], 2);
		ft_putendl_fd(": command not found", 2);
		clear_array(commands);
		exit(127);
	}
}
