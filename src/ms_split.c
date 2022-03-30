/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:56:15 by ecamara           #+#    #+#             */
/*   Updated: 2022/03/30 13:22:40 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pass(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	count_ms(char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
			s += ft_pass_2(s, *s);
		if (*s != c && j == 0)
		{
			i++;
			j = 1;
		}
		else if (*s == c)
			j = 0;
		s++;
	}
	return (i);
}

char	**str_ms(char *str, int j, char c, char **list)
{
	unsigned int	i;
	unsigned int	index;
	int				r;

	i = 0 ;
	r = 0;
	while (j < count_ms(str, c))
	{
		if (str[i] != c && r == 0)
		{
			index = i;
			r = 1;
		}
		else if ((str[i] == c || str[i] == '\0') && r == 1)
		{
			list[j] = ft_substr(str, index, (i - index));
			if (!list[j])
				freeo(list, 1);
			r = 0;
			j++;
		}
		i++;
	}
	list[j] = 0;
	return (list);
}

char	**ft_split_ms(char *s, char c)
{
	long int	i;
	int			j;
	char		**list;

	j = 0;
	if (!s)
		return (NULL);
	else
	{
		i = count_ms(s, c);
		list = (char **)malloc(sizeof(char *) * (i + 1));
		if (!list)
			return (NULL);
	}
	return (str_ms(s, j, c, list));
}
