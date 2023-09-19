/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:03:30 by htaheri           #+#    #+#             */
/*   Updated: 2023/09/12 17:53:52 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	do_exec(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = get_path(cmd, envp);
	if (execve(path, cmd, envp) == -1)
	{
		ft_putstr_fd(*cmd, 2);
		ft_putstr_fd("COMMAND NOT FOUND", 2);
		ft_putchar_fd('\n', 2);
		mem_free(cmd);
		exit(0);
	}
}

void	do_pipe(int argc, char **argv, char **envp)
{
	int		i;
	int		infile;
	int		outfile;
	int		pid;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		error_message("Error Opening Infile");
	outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		error_message("Error opening outfile");
	i = 0;
	while (i < argc - 4)
		infile = consecutive_pipe(i++, infile, argv, envp);
	pid = fork();
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		do_exec(argv[argc - 2], envp);
	}
	close(infile);
	close (outfile);
	waitpid(pid, NULL, 0);
}

void	here_doc(char **argv)
{
	char	*line;
	int		fd;

	fd = open("temp", O_WRONLY | O_CREAT, 0644);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free (line);
			return ;
		}
		ft_putstr_fd(line, fd);
		free (line);
	}
}

void	do_here_doc(int argc, char **argv, char **envp)
{
	int		first;
	int		outfile;
	int		pid;
	int		i;

	outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	first = open("temp", O_CREAT | O_RDWR, 0777);
	here_doc(argv);
	i = 1;
	while (i < argc - 4)
		first = consecutive_pipe(i++, first, argv, envp);
	unlink ("temp");
	pid = fork();
	if (pid == 0)
	{
		dup2(first, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		do_exec(argv[argc - 2], envp);
	}
	close(first);
	close (outfile);
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		error_message("Not Enough ARGS");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			error_message("Not Enough ARGS");
		do_here_doc(argc, argv, envp);
	}
	else
		do_pipe(argc, argv, envp);
	return (EXIT_SUCCESS);
}
