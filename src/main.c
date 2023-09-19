/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:56:28 by htaheri           #+#    #+#             */
/*   Updated: 2023/09/19 17:57:27 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec(char *arg, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, ' ');
	path = get_path(cmd, envp);
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd("COMMAND NOT FOUND", 2);
		ft_putchar_fd('\n', 2);
		mem_free(cmd);
		exit(0);
	}
}

void	child_process(int infile, int fd[], char **argv, char **envp)
{
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(infile);
	close(fd[0]);
	close(fd[1]);
	exec(argv[2], envp);
}

void	parent_process(int outfile, int fd[], char **argv, char **envp)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
		exit(-1);
	if (!pid2)
	{
		dup2(outfile, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close (fd[1]);
		exec(argv[3], envp);
	}
	close(outfile);
	close (fd[1]);
	waitpid(pid2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;
	int		outfile;
	int		infile;

	if (argc != 5)
		error_message("NOT ENOUGH ARGS");
	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (infile < 0 || outfile < 0)
		return (-1);
	if (pipe(fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child_process(infile, fd, argv, envp);
	else
	{
		parent_process(outfile, fd, argv, envp);
		waitpid(pid, NULL, 0);
	}
	return (EXIT_SUCCESS);
}
