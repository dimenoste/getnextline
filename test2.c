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
	while (i < buffer_size && s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}
// https://stackoverflow.com/questions/27636306/valgrind-address-is-0-bytes-after-a-block-of-size-8-allocd
// char	*getnexline(int fd)
// {
// 	// printf("\n========================================================\n");
// 	// printf("\n========================================================\n");
// 	static char	*stash = NULL;
// 	char		*line_to_get;
// 	char		*tmpline_to_get;
// 	size_t		n;
// 	char		buf[BUF_SIZ + 1];
// 	char *tmpstash;

// 	n = read(fd, buf, BUF_SIZ);
// 	buf[n] = '\0';

// 	if (n > 0)
// 	{
// 		if (!stash)
// 			stash = ft_strdup("");
// 		tmpstash = stash;
// 		stash = ft_strjoin(stash, buf);
// 		free(tmpstash);
// 		tmpstash = NULL;
// 	}
// 	else
// 	{
// 		printf("stash is %s\n", stash);
// 		return (NULL);
// 	}
	
// 	while (n > 0)
// 	{

// 		if (n > 0 && find_newline_inbuffer(stash, ft_strlen(stash)) > 0) //newline in the middle
// 		{
// 			tmpstash = stash;
// 			line_to_get = ft_substr(stash, 0, pos_newline_inbuffer(stash,ft_strlen(stash)) + 1);
// 			stash = ft_substr(stash, (pos_newline_inbuffer(stash, ft_strlen(stash)) + 1), ft_strlen(stash));
// 			free(tmpstash);
// 			tmpstash = NULL;
// 			return line_to_get;
// 		}
// 		if (n > 0 && find_newline_inbuffer(stash, ft_strlen(stash)) == 0) //newline at the end
// 		{
// 			line_to_get = stash;
// 			line_to_get[ft_strlen(line_to_get) + BUF_SIZ - n - 1] = '\0';
// 			free(stash);
// 			stash = NULL;
// 			return (line_to_get);
// 		}
// 		while (n > 0 && find_newline_inbuffer(stash, ft_strlen(stash)) < 0) // no newline found
// 		{
			
// 			if (n < BUF_SIZ)
// 			{
// 				stash[ft_strlen(stash) + BUF_SIZ - n - 1] = '\0';
// 				line_to_get = stash;
// 				return (line_to_get);
// 			}
// 			n = read(fd, buf, BUF_SIZ);
// 			buf[n] = '\0';
// 			tmpstash = stash;
// 			stash = ft_strjoin(stash, buf);
// 			free(tmpstash);
// 			tmpstash = NULL;
// 		}
// 	}
// }


// char	*getnexline(int fd)
// {
// 	// printf("\n========================================================\n");
// 	// printf("\n========================================================\n");
// 	static char	*buf;
// 	char		*line_to_get;
// 	char		*tmp;
// 	size_t		n;
// 	char *tmpstash;
	
// 	while (find_newline_inbuffer(buf, ft_strlen(buf)) < 0) // no newline found
// 	{
// 		n = read(fd, buf, BUF_SIZ);
// 		buf[n] = '\0';
// 		tmp = buf;
// 		buf = ft_strjoin(tmp, buf);
// 		buf = ft_strdup();
// 	}
// }





// 	while (n > 0)
// 	{

// 		if (n > 0 && find_newline_inbuffer(stash, ft_strlen(stash)) > 0) //newline in the middle
// 		{
// 			tmpstash = stash;
// 			line_to_get = ft_substr(stash, 0, pos_newline_inbuffer(stash,ft_strlen(stash)) + 1);
// 			stash = ft_substr(stash, (pos_newline_inbuffer(stash, ft_strlen(stash)) + 1), ft_strlen(stash));
// 			free(tmpstash);
// 			tmpstash = NULL;
// 			return line_to_get;
// 		}
// 		if (n > 0 && find_newline_inbuffer(stash, ft_strlen(stash)) == 0) //newline at the end
// 		{
// 			line_to_get = stash;
// 			line_to_get[ft_strlen(line_to_get) + BUF_SIZ - n - 1] = '\0';
// 			free(stash);
// 			stash = NULL;
// 			return (line_to_get);
// 		}
// 		while (n > 0 && find_newline_inbuffer(stash, ft_strlen(stash)) < 0) // no newline found
// 		{
			
// 			if (n < BUF_SIZ)
// 			{
// 				stash[ft_strlen(stash) + BUF_SIZ - n - 1] = '\0';
// 				line_to_get = stash;
// 				return (line_to_get);
// 			}
// 			n = read(fd, buf, BUF_SIZ);
// 			buf[n] = '\0';
// 			tmpstash = stash;
// 			stash = ft_strjoin(stash, buf);
// 			free(tmpstash);
// 			tmpstash = NULL;
// 		}
// 	}
// }


int	main(void)
{
	int	fd;
	char *line;
	char *tmpline;
	int n;
	char static *buf;

	fd = open("./inputsmall.txt", O_RDONLY);
	if (fd == -1)
	{
		exit(1);
	}
	
	n = read(1, buf, 3);
	printf("first read  is :%d\n", n);

	// while (line = getnexline(fd))
	// {
	// 	printf("line 1 in main is :%s\n", tmpline);
	// 	free(line);
	// }
	
	// line = getnexline(fd);
	// printf("line 2 in main is :%s\n", line);
	// free(line);
	
	
	// line = getnexline(fd);
	// printf("line 2 in main is :%s\n", line);
	// free(line);
	
	// line = getnexline(fd);
	// printf("line 3 in main is :%s\n", line);
	// free(line);
	
	// line = getnexline(fd);
	// printf("line 4 in main is :%s\n", line);
	// free(line);

	// 	line = getnexline(fd);
	// printf("line 4 in main is :%s\n", line);
	

	close(fd);
	return (0);
}