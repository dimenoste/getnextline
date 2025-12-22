#include "get_next_line.h"

// if newline is at the end of buffer = 0
// if newline is before the end of buffer  = 1
// if newline is not found within buffer size = -1
int	find_newline_inbuffer(char *s, int buffer_size)
{
	int	i;

	i = 0;
	while (s[i] && i < buffer_size && s[i] != '\n')
		i++;
	if (s[i] == '\n' && i == (buffer_size - 1))
		return (0);
	if (s[i] == '\n' && i < (buffer_size - 1))
		return (1);
	return (-1);
}

int	pos_newline_inbuffer(char *s, int buffer_size)
{
	int	i;

	i = 0;
	while (i < (int)buffer_size && s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char *fill_line(char *left_over, char *buffer)
{
	if (!left_over)
	{
		// printf("leftover vide, il va etre cree");
		left_over = ft_strdup("");
	}
	left_over = ft_strjoin(left_over, buffer);
	// printf("new left_over is %s\n", left_over);
	//free(left_over);
	return (left_over);
}

char *before_nl(char *line)
{
	int nl;
	
	nl = 0;
	nl = pos_newline_inbuffer(line, (ft_strlen(line) + 1));
	if (nl != -1)
	{
		// printf("adress of line  %p\n", &line[nl + 1]);
		line[nl + 1] = '\0';
	}
	return (line);
}


char	*ft_after_nl(const char *s, char c)
{

	while (*s != '\0' && c != *s)
		s++;
	if (c == *s && *(s+1) != '\0')
		return ((char *)(s+1));
	return (NULL);
}


// char *set_line(char *line, char **pleftover)
// {
// 	int nl;
	
// 	nl = pos_newline_inbuffer(line, '\n');
// 	if (nl != -1)
// 	{
// 		line[nl + 1] = '\0';
// 	}
// 	return (line);
// }

char	*get_next_line(int fd)
{
	// printf("\n========================================================\n");
	// printf("========================================================\n");
	static char	*left_over;
	char *tmp;
	char	*line;
	char	*buffer;
	int		n;


	if (fd == -1)
	{
		return NULL;
	}

	buffer = malloc(BUFFER_SIZE + 1);
	n = read(fd, buffer, BUFFER_SIZE);
	buffer[n] = '\0';
	// printf("n is %d\n", n);
	// printf("first buffer is %s\n", buffer);
	// printf("first left_over is %s\n", left_over);

	while (n > 0 && ft_strchr(buffer, '\n') == NULL)//renvoie NULL quand NO nl
	{
		left_over = fill_line(left_over, buffer);
		n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = '\0';
	}
	// printf("left_over before fill_line is %s\n", left_over);
	left_over = fill_line(left_over, buffer);
	// printf(" left_over is %s\n", left_over);
	// if (ft_strchr(buffer, '\0'))
	// 	printf("back0 trouve hors du cas du newline\n");
	//printf("buffer is %s\n", buffer);

	// printf("has new line ?  buffer is %s\n", buffer);
	tmp = left_over; 
	//printf("tmp is %s\n", tmp);
	line = before_nl(tmp);
	// printf("before nl, line is %s\n", line);
	// printf("buffer is  %s\n", buffer);
	left_over = ft_after_nl(buffer, '\n');
	// printf("after nl, left_over is %s\n", left_over);
	//line = ft_strjoin(tmp, line);
	return (line);
}

// int	main(void)
// {
// 	int	fd;
// 	char *line;
// 	fd = open("inputsmall.txt", O_RDONLY);
// 	//printf("fd is %d\n", fd);
// 	if (fd == -1)
// 	{
// 		return(1);
// 	}
// 	line = getnexline(fd);
// 	printf("line 1 in main is :%s\n", line);
// 	free(line);

// 		line = getnexline(fd);
// 	printf("line 2 in main is :%s\n", line);
// 	free(line);

// 		line = getnexline(fd);
// 	printf("line 3 in main is :%s\n", line);
// 	free(line);

// 	// 	line = getnexline(fd);
// 	// printf("line 4 in main is :%s\n", line);
// 	// free(line);

// 	// 		line = getnexline(fd);
// 	// printf("line 4 in main is :%s\n", line);
// 	// free(line);
	
// 	// while (getnexline(fd))
// 	// {
		
// 	// 	printf("line 1 in main is :%s\n", line);	
// 	// }
// 	// free(line);

// 	// char *buffer = ft_strdup("abc\0def\nffdfdfd");
// 	// printf("buffer is  %s\n", buffer);

// 	// printf("adress of buffer  %p\n", &buffer[8]);
// 	// line = before_nl(buffer);
// 	// printf("before nl, line is %s\n", line);
// 	// printf("before nl, buffer is %s\n", buffer);

// 	close(fd);
// 	return (0);
// }