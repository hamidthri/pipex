/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:42:56 by htaheri           #+#    #+#             */
/*   Updated: 2023/09/08 14:21:46 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_message(char	*msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(1);
}

void	mem_free(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*find_path(char **envp)
{
	int		i;
	char	*envs;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
	}
	envs = envp[i] + 5;
	return (envs);
}

char	*get_path(char **cmd, char **envp)
{
	int		i;
	char	*envs;
	char	**pths;
	char	*path_all;
	char	*final_path;

	envs = find_path(envp);
	pths = ft_split(envs, ':');
	i = -1;
	while (pths[++i])
	{
		path_all = ft_strjoin(pths[i], "/");
		final_path = ft_strjoin(path_all, cmd[0]);
		free (path_all);
		if (access(final_path, F_OK | X_OK) == 0)
		{
			mem_free(pths);
			return (final_path);
		}
		free(final_path);
	}
	mem_free(pths);
	return (cmd[0]);
}
