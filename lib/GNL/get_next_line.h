/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:55:16 by htaheri           #+#    #+#             */
/*   Updated: 2023/07/27 17:17:41 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *str);
void	*gnl_calloc(size_t count, size_t size);
char	*gnl_strjoin(char *buffer, char *temp);
char	*gnl_strchr(const char *s, int c);
int		check(char *buffer, char *temp);
#endif