/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:49:06 by htaheri           #+#    #+#             */
/*   Updated: 2023/09/08 20:04:32 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# include "../lib/libft/libft.h"
# include "../lib/GNL/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>

void	error_message(char	*msg);
void	mem_free(char **str);
char	*find_path(char **envp);
void	do_exec(char *argv, char **envp);
int		consecutive_pipe(int i, int first, char **argv, char **envp);
char	*get_path(char **cmd, char **envp);

#endif