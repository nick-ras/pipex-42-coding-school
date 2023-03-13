/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:05:56 by nickras           #+#    #+#             */
/*   Updated: 2023/03/13 20:08:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* Calls get_path to get the path of the command, then duplicates files to STDIN and STDOUT and then calls the execute function to execute functions. It also closed filedescriptors after duplication
*/
void	pid1_is_0(int *fd, int *pipefd, char *cmd, char **envp)
{
	char	*path;

	path = get_path(cmd, envp);
	close(pipefd[0]);
	close(fd[1]);
	if (dup2(fd[READ], STDIN_FILENO) < 0 || \
	dup2(pipefd[WRITE], STDOUT_FILENO) < 0)
	{
		ft_printf("dup error\n"),
		exit(1);
	}
	close(pipefd[1]);
	close(fd[0]);
	execute(cmd, envp, path);
	ft_printf("first didnt exec\n");
}

/* the second child process, the gets the output from execve from first child, and then executes it into a file. It also closes filedescriptors after duplication
*/
void	pid2_is_0(int *fd, int *pipefd, char *argv, char **envp)
{
	char	*path;

	path = get_path(argv, envp);
	close(pipefd[WRITE]);
	close(fd[READ]);
	if (dup2(pipefd[READ], STDIN_FILENO) < 0 \
	|| dup2(fd[WRITE], STDOUT_FILENO) < 0)
	{
		ft_printf("dup error\n"),
		exit(2);
	}
	close(fd[WRITE]);
	close(pipefd[READ]);
	path = NULL;
	path = get_path(argv, envp);
	execute(argv, envp, path);
	ft_printf("second  didnt exec\n");
}

/* find the index of envp where PATH is the first 4 characters and calls set_paths
*/
char	*get_path(char *arg_idx, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen(envp[i])))
			return (set_paths(arg_idx, envp[i]));
		i++;
	}
	perror("could not find path in envp");
	exit (2);
}

/* finds length of the path index of envp, allocates space and returns it
*/
char	*cmd_get_command(char *arg_idx)
{
	int		i;
	int		len;
	char	*new_cmd;

	i = 0;
	while (arg_idx[i] != ' ')
	{
		i++;
		len = i;
	}
	new_cmd = malloc(sizeof(char) * len + 1);
	ft_strlcpy(new_cmd, arg_idx, len + 1);
	return (new_cmd);
}
