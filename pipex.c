/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaynar <skaynar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:44:38 by skaynar           #+#    #+#             */
/*   Updated: 2025/05/16 22:41:22 by skaynar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_execute(char *cmd, char **ep)
{
	char	**commands;
	char	*path;

	commands = ft_split(cmd, ' ');
	if (!commands || !commands[0])
	{
		ft_free(commands);
		ft_error(1);
	}
	path = ft_get_cmd(commands[0], ep);
	if (execve(path, commands, ep) == -1)
	{
		ft_putstr_fd(commands[0], 2);
		ft_putendl_fd(": command not found", 2);
		ft_free(commands);
		exit(0);
	}
}

static void	ft_child(char **av, int *fd, char **ep)
{
	int	file_d;

	file_d = ft_open(av[1], 0);
	dup2(file_d, 0);
	dup2(fd[1], 1);
	close(fd[0]);	
	ft_execute(av[2], ep);
}

static void	ft_parent(char **av, int *fd, char **ep)
{
	int	file_d;

	file_d = ft_open(av[4], 1);
	dup2(file_d, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	ft_execute(av[3], ep);
}

void	ft_error(int nbr)
{
	if (nbr == 1)
		ft_putstr_fd("USAGE: ./pipex infile '/cmd1' '/cmd2' outfile\n", 2);
	exit(0);
}

int	main(int ac, char **av, char **ep)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		ft_error(1);
	if (pipe(fd) < 0)
		exit(-1);
	pid = fork();
	if (pid < 0)
		exit(-1);
	if (pid == 0)
		ft_child(av, fd, ep);
	ft_parent(av, fd, ep);
	return (0);
}

static int	ft_access(char *exec, char **opt, char **path)
{
	if (!access(exec, F_OK | X_OK))
	{
		ft_free(opt);
		ft_free(path);
		return (1);
	}
	return (0);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_open(char *file, int val)
{
	int	rtn;

	if (val)
		rtn = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		rtn = open(file, O_RDONLY);
	if (rtn < 0)
	{
		ft_putstr_fd("bash: ", 2);
		perror(file);
		exit(1);
	}
	return (rtn);
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
		ft_error(1);
	while (path[++i])
	{
		part = ft_strjoin(path[i], "/");
		exec = ft_strjoin(part, opt[0]);
		free(part);
		if (ft_access(exec, opt, path))
			return (exec);
		free(exec);
	}
	ft_free(path);
	ft_free(opt);
	return (cmd);
}