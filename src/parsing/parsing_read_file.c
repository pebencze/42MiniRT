/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_read_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:45:51 by vados-sa          #+#    #+#             */
/*   Updated: 2024/12/12 16:19:04 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

ssize_t	ft_arr_len(char **arr)
{
	ssize_t	i;

	i = 0;
	if (!arr)
		return (-1);
	while (arr[i])
		i++;
	return (i);
}

char	**free_arr(char **arr1, char **arr2)
{
	int	i;

	i = 0;
	if (arr1)
	{
		while (arr1[i])
			free(arr1[i++]);
		free(arr1);
	}
	i = 0;
	if (arr2)
	{
		while (arr2[i])
			free(arr2[i++]);
		free(arr2);
	}
	return (NULL);
}

/**
 * @brief: appends a char *array to a char **array.
 */
static char	**append_arr(char **arr, char *new_str)
{
	ssize_t	i;
	char	**new_arr;

	i = ft_arr_len(arr);
	new_arr = (char **)ft_calloc(sizeof(char *), (i + 2));
	if (!new_arr)
		return (free_arr(arr, NULL));
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
			return (free_arr(arr, new_arr));
		i++;
	}
	if (ft_strchr(new_str, '\n'))
		new_str[ft_strlen(new_str) - 1] = '\0';
	new_arr[i] = ft_strdup(new_str);
	if (!new_arr[i])
		return (free_arr(arr, new_arr));
	free_arr(arr, NULL);
	return (new_arr);
}

/**
 * @brief: loops throught the file and
 * uses get_next_line(int fd) 
 * to extract the content of each line.
 */
static char	**read_lines(int fd)
{
	char	**arr;
	char	*line;

	arr = (char **)ft_calloc(sizeof(char *), 1);
	if (!arr)
		return (perror("Error\n"), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\0' || line[0] == '\n')
		{
			free (line);
			continue ;
		}
		arr = append_arr(arr, line);
		free (line);
		if (!arr)
			return (ft_putendl_fd(ALLOC_ERR, 2), NULL);
	}
	return (arr);
}

/**
 * @brief: checks the extension, opens the file, 
 * passes the fd to the readline function,
 * closes the file and checks the extracted content.
 */
void	read_file(char *filename, t_data *data)
{
	int	fd;
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(&filename[len - 3], ".rt", 3))
		ft_exit(1, data, EXTENSION_ERR);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_exit(1, data, OPEN_ERR);
	data->lines = read_lines(fd);
	close (fd);
	if (!data->lines)
		ft_exit(1, data, NULL);
	if (!*data->lines)
		ft_exit(1, data, EMPTY_ERR);
}
