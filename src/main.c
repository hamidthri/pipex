/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:56:28 by htaheri           #+#    #+#             */
/*   Updated: 2023/09/08 14:26:32 by htaheri          ###   ########.fr       */
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

void	child_process(int fd[], char **argv, char **envp)
{
	int		infile;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		return ;
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	exec(argv[2], envp);
}

void	parent_process(int fd[], char **argv, char **envp)
{
	int		outfile;

	outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		return ;
	dup2(outfile, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close (fd[1]);
	exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		error_message("NOT ENOUGH ARGUMENTS");
	if (pipe(fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		child_process(fd, argv, envp);
	parent_process(fd, argv, envp);
}
