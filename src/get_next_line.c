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
	free (buffer);
    return (temp);
}

char	*extract_line(char *stock, int fd)
{
	char	*buff;
	int	i;

	i = 1;
	while (!ft_strchr(stock, '\n'))
	{
		buff = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buff)
			return (NULL);
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			return (free(buff), NULL);
		if (i == 0)
			return (free(buff), stock);
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
	res = (char *)ft_calloc(i + 1, sizeof(char));
	if (!res)
		return (NULL);
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
	if (!s)
		return (NULL);
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
	/*else
		free(buff);*/
	if (!stock)
		return (NULL);
	stock = extract_line(stock, fd);
	if (!stock || stock[0] == '\0')
	{
		free(stock);
		return (NULL);
	}
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
//erreur d'affichage terminal
int	main(int ac, char **av)
{
	int	fd;
	char	*res;
	int	i;

	fd = open(av[1], O_RDONLY);
	//fd = 1;
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
