#include "get_next_line.h"

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

char	*read_and_stash(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		n;

	n = 0;
	while (get_pos_nl(stash) == -1) // stash has NO \n
	{
		printf("read_and_stash... First stash without nl is |%s|\n", stash);
		n = read(fd, buffer, BUFFER_SIZE);
		buffer[n] = '\0';
		if (n == 0)
		{
			printf("read_and_stash... no first read,or last read STASH is |%s|\n",
				stash);
			return (stash);
		}
		stash = join_line(stash, buffer);
		printf("read_and_stash... before free NEW STASH is |%s|\n", stash);
		printf("read_and_stash... NEW STASH is |%s|\n", stash);
	}
	printf("read_and_stash... before return, STASH is |%s|\n", stash);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*tmp;
	char		*line;

	printf("get_next_line... STARTING stash is |%s|\n", stash);
	// printf("\n========================================================\n");
	// printf("========================================================\n");
	// n = 0;
	if (get_pos_nl(stash) == -1)
	{
		stash = read_and_stash(fd, stash);
		printf("get_next_line... in stash null, returned STASH is |%s|\n",
			stash);
		if (!stash)
			return (NULL);
		printf("get_next_line.. in stash null, STASH with nl is |%s|\n", stash);
	}
	printf("get_next_line.. OUTSIDE stash null, STASH with nl is |%s|\n",
		stash);
	if (get_pos_nl(stash) != -1)
	{
		tmp = stash;
		printf("get_next_line... STASH with nl is |%s|\n", stash);
		line = ft_strdup_up_to_nl(tmp);
		printf("get_next_line... LIne before nl is |%s|\n", line);
		stash = ft_strdup_after_nl(tmp);
		free(tmp);
		return (line);
	}
	printf("get_next_line.. END STASH is |%s|\n", stash);
	// verify not to return an incomplete line
	return (stash);
}

int	main(void)
{
	int fd;
	char *line;
	fd = open("./data/inputsmall.txt", O_RDONLY);
	if (fd == -1)
	{
		return (1);
	}
	printf("========================================================\n");
	line = get_next_line(fd);
	printf("line 1 in main is :%s\n", line);
	free(line);
	printf("========================================================\n");
	line = get_next_line(fd);
	printf("line 2 in main is :%s\n", line);
	free(line);
	printf("========================================================\n");
	line = get_next_line(fd);
	printf("line 3 in main is :%s\n", line);
	free(line);
	printf("========================================================\n");

	close(fd);
	return (0);
}