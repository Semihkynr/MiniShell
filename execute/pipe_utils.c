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

char	*ft_get_cmd(char *cmd, t_stack **env, int i)
{
	char	**path;
	char	*part;
	char	**opt;
	char	*exec;

	if (cmd && (ft_strchr(cmd, '/') || cmd[0] == '.'))
		return (ft_strdup(cmd));
	i = -1;
	path = ft_split(find_value(env, "PATH"), ':');
	opt = ft_split(cmd, ' ');
	if (!opt || !path)
		return (clear_array(path), clear_array(opt), NULL);
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

void	ft_execute(char **commands, char **ep, t_shell *shell)
{
	char	*path;

	if (!commands || !commands[0])
		return ;
	path = ft_get_cmd(commands[0], shell->env, -1);
	if (execve(path, commands, ep) == -1)
	{
		ft_putstr_fd(commands[0], 2);
		ft_putendl_fd(": command not found", 2);
		free_cmd_list(shell->cmd);
		free_shell(shell);
		exit(127);
	}
}
