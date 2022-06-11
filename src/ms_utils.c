/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:59:56 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/11 12:27:13 by ecamara          ###   ########.fr       */
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
	dup[i] = NULL;
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		dup[i] = ft_strdup(str[i]);
		i++;
	}
	return (dup);
}

char	*ft_ms_join(char *str1, char *str2, int len1, int len2)
{
	int		i;
	char	*final;

	if (str2 == NULL)
		return (str1);
	final = malloc(len1 + len2 + 1);
	if (!final)
		return (NULL);
	final[len1 + len2] = '\0';
	i = 0;
	while (i < len1)
	{
		final[i] = str1[i];
		i++;
	}
	while (i - len1 < len2)
	{
		final[i] = str2[i - len1];
		i++;
	}
	free(str1);
	return (final);
}

char	*ft_substr_ms(const char *s, unsigned int start, size_t len)
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
	return (mem);
}

int	ft_strncmp_ms(char *str1, char *str2, int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (str1[count] != '\0' && str2[count] != '\0' && count <= n)
	{
		if (str1[count] != str2[count])
			return (1);
		count++;
	}
	if (str1[count] != '=')
		return (1);
	return (0);
}

int	ft_str_compare(char **str1, char *str2)
{
	int	j;

	j = 0;
	while (str1[j] != NULL)
	{
		if (!ft_strncmp_ms(str1[j], str2, ft_strlen(str2)))
			return (j);
		j++;
	}
	return (-1);
}
