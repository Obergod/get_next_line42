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

#include "get_next_line.h"

char *stock_extend(char *stock, char *buffer)
{
    char *temp;

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

char *extract_line(char *stock, int fd)
{
	char *buff;
	long i;

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
			free(buff);
				return (NULL);
        }
		buff[i] = '\0';
		stock = stock_extend(stock, buff);
		if (!stock)
		{
			stock = NULL;
			return (NULL);
		}
	}
	return (stock);
}

char *precise_line(char *stock)
{
	char *res;
	int i;
	int j;

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

char *after_line(char *stock)
{
	char *s;
	int i;
	int j;

	j = 0;
	i = 0;
	while (stock[i] != '\n')
		i++;
	j = i;
	while (stock[i])
		i++;
	s = ft_strdup(stock + (j + 1));
	free(stock);
	return (s);
}

char *get_next_line(int fd)
{
	static char *stock;
	//static char *stock[FD_MAX] = {0};
	char *buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stock)
    	stock = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!stock)
		return (NULL);
	stock = extract_line(stock, fd);
	if (!stock || stock[0] == '\0')
	{
		if (stock)
			free(stock);
		return (NULL);
	}
	if (!ft_strchr(stock, '\n'))
	{
		buff = ft_strdup(stock);
		free(stock);
		stock = NULL;
		return (buff);
	}
	else
	{
		buff = precise_line(stock);
		stock = after_line(stock);
		return (buff);
	}
}

#include <stdio.h>
int main(int ac, char **av)
{
	int fd;
	char *res;
	int i;

	fd = open("empty.txt", O_RDONLY);
	// fd = 0;

	i = 0;
	res = NULL;
	while (i != -1)
	{
		res = get_next_line(fd);
		printf("this is line : %s", res);
		if (res == NULL)
			i = -1;
		free(res);
	}
	printf("\n");
	return (0);
}
