/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:26:46 by mafioron          #+#    #+#             */
/*   Updated: 2024/12/03 18:26:50 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*stock_extend(char *stock, char *buffer)
{
	char	*temp;

	if (!stock)
	{
		temp = ft_strdup(buffer);
		free(buffer);
		return (temp);
	}
	temp = ft_strjoin(stock, buffer);
	free(stock);
	free(buffer);
	return (temp);
}

char	*extract_line(char *stock, int fd)
{
	char	*buff;
	int		i;

	i = 1;
	while (!ft_strchr(stock, '\n') && i != 0)
	{
		buff = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0 || (i == 0 && stock == NULL))
		{
			free(stock);
			stock = NULL;
			return (free(buff), NULL);
		}
		buff[i] = '\0';
		stock = stock_extend(stock, buff);
		if (!stock)
			return (stock = NULL, NULL);
	}
	return (stock);
}

char	*precise_line(char *stock)
{
	char	*res;
	int		i;
	int		j;

	j = -1;
	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	res = (char *)ft_calloc(i + 2, sizeof(char));
	if (!res)
		return (NULL);
	while (++j < i + 1)
		res[j] = stock[j];
	return (res);
}

char	*after_line(char *stock)
{
	char	*s;
	int		i;

	i = 0;
	while (stock[i] != '\n')
		i++;
	s = ft_strdup(stock + (i + 1));
	if (!s)
		return (NULL);
	free(stock);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*stock[FD_MAX];
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stock[fd])
		stock[fd] = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!stock[fd])
		return (NULL);
	stock[fd] = extract_line(stock[fd], fd);
	if (!stock[fd])
		return (NULL);
	if (stock[fd][0] == '\0')
		return (free(stock[fd]), NULL);
	if (!ft_strchr(stock[fd], '\n'))
		return (buff = ft_strdup(stock[fd]), free(stock[fd]), stock[fd] = NULL, buff);
	else
	{
		buff = precise_line(stock[fd]);
		stock[fd] = after_line(stock[fd]);
		return (buff);
	}
}
/*
#include <stdio.h>
int main(int ac, char **av)
{
	int fd;
	int	fd2;
	char *res;
	int i;

	 //fd = 0;
	fd = open("test.txt", O_RDONLY);
	fd2 = open("test1.txt", O_RDONLY);
	i = 0;
	res = NULL;
	while (i != -1)
	{
		res = get_next_line(fd2);
		printf("this is line : %s", res);
		if (res == NULL)
			i = -1;
		free(res);
		res = get_next_line(fd);
		printf("this is line : %s", res);
		if (res == NULL)
			i = -1;
		free(res);
	}
	printf("\n");
	return (0);
}*/
