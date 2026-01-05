/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberraho <mehdi.berraho@learner.42.tech    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 23:32:41 by mberraho          #+#    #+#             */
/*   Updated: 2026/01/04 23:33:15 by mberraho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_up_to_nl(const char *s)
{
	int	lens;
	int	pos_nl;

	lens = ft_strlen(s);
	pos_nl = get_pos_nl(s);
	if (pos_nl != -1 && pos_nl < lens)
	{
		return (ft_substr(s, 0, (get_pos_nl(s)) + 1));
	}
	return (NULL);
}

char	*ft_strdup_after_nl(const char *s)
{
	int	lens;
	int	pos_nl;

	lens = ft_strlen(s);
	pos_nl = get_pos_nl(s);
	if (pos_nl != -1 && pos_nl < lens)
	{
		return (ft_substr(s, (pos_nl + 1), (lens - pos_nl - 1)));
	}
	return (NULL);
}

char	*join_line(char *stash, char *buffer)
{
	char	*tmp;

	tmp = stash;
	if (!tmp)
		tmp = ft_strdup("");
	stash = ft_strjoin(tmp, buffer);
	free(tmp);
	return (stash);
}

char	*read_and_stash(int fd, char *stash, size_t buffersize)
{
	char	*buffer;
	int		n;

	n = 0;
	while (get_pos_nl(stash) == -1 && buffersize > 0
		&& buffersize <= 0x7ffff000)
	{
		buffer = malloc(buffersize + 1);
		n = read(fd, buffer, buffersize);
		if (n <= 0)
		{
			free(buffer);
			return (stash);
		}
		buffer[n] = '\0';
		stash = join_line(stash, buffer);
		free(buffer);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*tmp;
	char		*line;

	if (fd <= 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (get_pos_nl(stash) == -1)
	{
		stash = read_and_stash(fd, stash, BUFFER_SIZE);
		if (!stash)
			return (NULL);
	}
	if (get_pos_nl(stash) != -1)
	{
		tmp = stash;
		line = ft_strdup_up_to_nl(tmp);
		stash = ft_strdup_after_nl(tmp);
		free(tmp);
		return (line);
	}
	line = ft_strdup(stash);
	free(stash);
	stash = NULL;
	return (line);
}

// int	main(void)
// {
// 	int fd;
// 	char *line;
// 	fd = open("./gnlTester/files/big_line_with_nl", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		return (1);
// 	}

// 	printf("========================================================\n");
// 	line = get_next_line(fd);
// 	printf("line in main is :|%s|\n", line);
// 	printf("========================================================\n");
// 	free(line);
// 	while (line)
// 	{
// 		printf("========================================================\n");
// 		line = get_next_line(fd);
// 		printf("line in main is :|%s|\n", line);
// 		printf("========================================================\n");
// 		free(line);
// 	}
// 	printf("========================================================\n");
// 	line = get_next_line(fd);
// 	printf("still a line ?  :|%s|\n", line);

// 	printf("========================================================\n");

// 	close(fd);
// 	return (0);
// }