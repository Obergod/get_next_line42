/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:23:08 by mafioron          #+#    #+#             */
/*   Updated: 2024/11/21 18:39:55 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	char	*r;
	size_t	len;

	len = (size * nmemb);
	res = (void *)malloc(len);
	r = (char *)res;
	if (!res)
		return (NULL);
	while (len--)
		*r++ = '\0';
	return (res);
}*/

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dst;

	dst = (unsigned char *)s;
	while (n-- > 0)
		*dst++ = c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	len;

	len = (size * nmemb);
	if ((int)len < 0 || ((int)nmemb < 0 && (int)size < 0))
		return (NULL);
	res = (void *)malloc(len);
	if (!res)
		return (NULL);
	ft_memset(res, 0, len);
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*stock;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = (char *)ft_calloc((len1 + len2) + 1, sizeof(char));
	if (!res)
		return (NULL);
	stock = res;
	while (len1--)
		*res++ = *s1++;
	while (len2--)
		*res++ = *s2++;
	return (stock);
}

int	ft_strchr(const char *s, int c)
{

	while (*s)
	{
		if (*s == (unsigned char)c)
		{
			return (1);
		}
		s++;
	}
	return (0);
}
