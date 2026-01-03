#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	get_pos_nl(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	if (str[i] == '\n')
	{
		return (i);
	}
	return (-1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	pos_end_subw;
	size_t	len_of_s;
	size_t	l;
	size_t	i;
	char	*subw;

	pos_end_subw = start + len - 1;
	len_of_s = ft_strlen(s);
	l = 0;
	i = start;
	if (!s)
		return (NULL);
	if ((start >= len_of_s) || len == 0)
		return (NULL);
	if (pos_end_subw >= len_of_s)
		pos_end_subw = len_of_s - 1;
	subw = malloc((pos_end_subw - start + 1 + 1) * sizeof(char));
	if (!subw)
		return (NULL);
	while (i <= pos_end_subw)
	{
		subw[l++] = s[i++];
	}
	subw[l] = '\0';
	return (subw);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		s[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	s[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (s);
}

char	*ft_strdup(const char *s)
{
	char	*strdup;
	size_t	lens;
	size_t	i;

	i = 0;
	lens = ft_strlen(s);
	strdup = malloc(lens + 1);
	if (!strdup)
		return (NULL);
	while (i < lens)
	{
		strdup[i] = s[i];
		i++;
	}
	strdup[lens] = '\0';
	return (strdup);
}

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

// a b c  \n d e f 0 1 2 3 4 5 6

// 	lens = 7 pos_nl = 3

// 	lens -
// 	pos_nl - 1 = 7 - 3 - 1 = 3