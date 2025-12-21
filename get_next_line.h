/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberraho <mehdi.berraho@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 22:32:03 by mberraho          #+#    #+#             */
/*   Updated: 2025/12/21 21:50:52 by mberraho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETNEXTLINE_H
# define GETNEXTLINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define BUF_SIZ 3

int		ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		find_newline_inbuffer(char *s, size_t buffer_size);
char	*ft_strdup(const char *s);
char	*getnexline(int fd);
int     pos_newline_inbuffer(char *s, size_t buffer_size);
char    *ft_after_nl(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char *before_nl(char *buffer);

#endif
