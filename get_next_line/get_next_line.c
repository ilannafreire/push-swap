/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inaomi-i <inaomi-i@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 15:00:01 by inaomi-i          #+#    #+#             */
/*   Updated: 2026/08/02 14:22:45 by inaomi-i         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char const *s)
{
	size_t	line_len;
	char	*line;

	if (!s)
		return (NULL);
	line_len = 0;
	while (s[line_len] && s[line_len] != '\n')
		line_len++;
	line = malloc((line_len + 2) * sizeof(char));
	if (!line)
		return (NULL);
	ft_strlcpy(line, s, line_len + 2);
	return (line);
}

static char	*update_stash(char const *s)
{
	size_t	line_len;
	size_t	stash_len;
	char	*stash;

	if (!s)
		return (NULL);
	line_len = 0;
	while (s[line_len] && s[line_len] != '\n')
		line_len++;
	if (s[line_len] == '\0')
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
		return (stash);
	}
	stash_len = ft_strlen(s) - line_len - 1;
	stash = malloc((stash_len + 1) * sizeof(char));
	if (!stash)
		return (NULL);
	ft_strlcpy(stash, s + line_len + 1, stash_len + 1);
	return (stash);
}

static ssize_t	read_file(int fd, char **stash)
{
	char	*buffer;
	char	*temp_stash;
	ssize_t	bytes_read;

	bytes_read = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (!has_newline(*stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), -1);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp_stash = ft_strjoin(*stash, buffer);
		if (!temp_stash)
			return (free(buffer), -1);
		free(*stash);
		*stash = temp_stash;
	}
	free(buffer);
	return (bytes_read);
}

static char	*clear_memory(char **stash, char *line)
{
	free(*stash);
	*stash = NULL;
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*temp_stash;
	ssize_t		status;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (clear_memory(&stash, NULL));
	status = read_file(fd, &stash);
	if (status < 0 || (status == 0 && (!stash || stash[0] == '\0')))
		return (clear_memory(&stash, NULL));
	line = extract_line(stash);
	if (!line)
		return (clear_memory(&stash, NULL));
	temp_stash = update_stash(stash);
	if (!temp_stash)
		return (clear_memory(&stash, line));
	free(stash);
	stash = temp_stash;
	return (line);
}
