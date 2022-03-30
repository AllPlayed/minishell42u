/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:59:56 by ecamara           #+#    #+#             */
/*   Updated: 2022/03/30 14:52:04 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_dup_2d(char **str)
{
	char	**dup;
	int		i;

	i = 0;
	while (str[i] != NULL)
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	while (str[i] != NULL)
	{
		dup[i] = ft_strdup(str[i]);
		i++;
	}
	return (dup);
}

char	*ft_ms_join(char **str1, char **str2, int len1, int len2, int boo)
{
	int		i;
	char	*final;

	len1 = ft_strlen(*str1);
	len1 = ft_strlen(*str2);
	if (str2 == NULL)
		return (*str1);
	final = malloc(len1 + len2 + 1);
	if (!final)
		return (NULL);
	final[len1 + len2] = '\0';
	i = 0;
	while (i < len1)
	{
		final[i] = (*str1)[i];
		i++;
	}
	while (i - len1 < len2)
	{
		final[i] = (*str2)[i - len1];
		i++;
	}
	ft_freeo(str1, 0);
	if (boo)
		ft_freeo(str2, 0);
	return (final);
}

char	**ft_substr_ms(const char *s, unsigned int start, size_t len)
{
	char		*mem;
	size_t		c;

	c = start;
	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
	{
		mem = (char *)malloc(ft_strlen(s + start) + 1);
		len = ft_strlen(s + start);
	}
	else if (start < ft_strlen(s))
		mem = malloc(len + 1);
	else
		mem = (char *)malloc(1);
	if (!mem || !s)
		return (NULL);
	while (len > 0 && start < ft_strlen(s))
	{
		mem[c - start] = s[c];
		c++;
		len--;
	}
	mem[c - start] = '\0';
	return (&mem);
}