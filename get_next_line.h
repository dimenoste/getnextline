/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberraho <mehdi.berraho@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 22:32:03 by mberraho          #+#    #+#             */
/*   Updated: 2025/12/22 19:26:07 by mberraho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETNEXTLINE_H
# define GETNEXTLINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif


int		ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		find_newline_inbuffer(char *s, int buffer_size);
char	*ft_strdup(const char *s);
char	*get_next_line(int fd);
int     pos_newline_inbuffer(char *s, int buffer_size);
char    *ft_after_nl(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char *before_nl(char *buffer);

#endif
