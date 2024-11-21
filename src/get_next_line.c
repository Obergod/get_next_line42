/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:14 by mafioron          #+#    #+#             */
/*   Updated: 2024/11/21 19:17:31 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_utils.h"

char    *stock_extend(char *stock, char *buffer)
{
    char    *temp;

    temp = ft_strjoin(stash, buffer);
    free(stash);
    return (temp);
}

char	*extract_line(static char *stock, int fd)
{
	char	*buff

	while (!ft_strchr(stock, '\n'))
	{
		buff = ft_calloc(sizeof(char) * BUFFER_SIZE + 1);
		if (read(fd, buff, BUFF_SIZE) <= 0)
			return (NULL);
		stock = stock_extended(stock, buff);
	}
	return (stock);
}

char	*precise_line(char *stock)
{
	char	*res;
	int	i;
	int	j;

	j = -1;
	i = 0;
	while (stock[i] != '\n')
		i++;
	res = calloc(sizeof(char) * i + 2);
	while (++j < i + 1)
		res[j] = stock[j];
	return (res);
		
}
// A refaire avec du sommeil (c degueu)
char	*after_line(char *stock)
{
	char	*s;
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (stock[i] != '\n')
		i++;
	j = i;
	while (stock[i])
		i++;
	s = calloc(sizeof(char) * (i - j) + 1);
	i = j;
	j = -1;
	while (++j < i)
		s[j++] = stock[i++];
	free(stock);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char	*buff;
	
	if (fd <= 0)
		return (NULL);
	if (!stock)
		stock = ft_calloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!stock)
		return (NULL);
	stock = extract_line(stock, fd);
	buff = precise_line(stock);
	if (ft_strchr(stock, '\n'))
		stock = after_line(stock);
	return (buff);
}
/*
#include <stdio.h>

int	main(int ac, char **av)
{
	int	fd;
	char	*res;

	fd = open(av[1], O_RDONLY);
	res = get_next_line(fd);
	printf("this is line : %s\n", res);
	free(res);
}*/
