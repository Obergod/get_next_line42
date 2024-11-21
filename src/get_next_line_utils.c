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



size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	void	*r;
	size_t	len;

	len = (size * nmemb);
	res = (void *)malloc(len);
	r = res;
	if (!res)
		return (NULL);
	while (len--)
		*r = 0;
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
	res = ft_calloc(sizeof(char) * (len1 + len2) + 1);
	if (!res)
		return (NULL);
	stock = res;
	while (len1--)
		*res++ = *s1++;
	while (len2--)
		*res++ = *s2++;
	return (stock);
}

char	*ft_strchr(const char *s, int c)
{
	char	*stock;

	if ((unsigned char)c == '\0')
	{
		stock = (char *)s + ft_strlen(s);
		return (stock);
	}
	while (*s)
	{
		if (*s == (unsigned char)c)
		{
			stock = (char *)s;
			return (stock);
		}
		s++;
	}
	return (NULL);
}
