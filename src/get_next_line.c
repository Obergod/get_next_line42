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

char    *stock_extend(char *stock, char *buffer)
{
    char    *temp;

    temp = ft_strjoin(stock, buffer);
    free(stock);
    return (temp);
}

char	*extract_line(char *stock, int fd)
{
	char	*buff;
	int	i;

	i = 1;
	while (!ft_strchr(stock, '\n') && i != 0)
	{
		buff = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			return (NULL);
		stock = stock_extend(stock, buff);
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
	while (stock[i] != '\n' && stock[i])
		i++;
	res = (char *)calloc(i + 1, sizeof(char));
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
	s = (char *)ft_calloc((i - j) + 1, sizeof(char));
	i = j + 1;
	j = 0;
	while (stock[i])
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
		stock = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!stock)
		return (NULL);
	stock = extract_line(stock, fd);
	//quelques free a gerer
	if (ft_strchr(stock, '\n'))
	{
		buff = precise_line(stock);
		stock = after_line(stock);
		return (buff);
	}
	else
		return (stock);
}

#include <stdio.h>
int	main()
{
	int	fd;
	char	*res;

	fd = open("test.txt", O_RDONLY);
	res = get_next_line(fd);
	printf("this is line : %s\n", res);
	//res jamais null ?
	while (res != NULL)
	{
		res = get_next_line(fd);
		printf("this is line : %s\n", res);
	}
	free(res);
	return (0);
}
