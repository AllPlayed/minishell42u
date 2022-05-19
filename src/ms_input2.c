/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:27:53 by ullorent          #+#    #+#             */
/*   Updated: 2022/05/19 12:49:57 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$'
			&& str[i + 1] != ' ' && str[i + 1] != '\"')
			j++;
		i++;
	}
	return (j);
}

void	ft_split_expand(char *str, char **temp, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < count)
	{
		temp[i] = ft_split2(str, &j);
		/*if (!temp[count])
			error();*/
		i++;
	}
}

void	ft_expand(char ***temp, t_data *data)
{
	int		i;
	int		hold;
	int		len;

	i = 0;
	while ((*temp)[i] != NULL)
	{
		len = ft_strlen((*temp)[i]);
		if ((*temp)[i][0] == '$')
		{
			hold = ft_str_compare(data->env, (*temp)[i]);
			free ((*temp)[i]);
			if (hold == -1)
				(*temp)[i] = NULL;
			else
				(*temp)[i] = ft_substr(data->env[hold],
						len, ft_strlen(data->env[hold] + len));
		}
		i++;
	}
}

void	ft_expansion_2(char **str, t_data *data, int n)
{
	int		i;
	char	**temp;
	int		count;
	char	*temp2;

	i = 0;
	if (str == NULL)
		return ;
	while (i < n)
	{
		printf("[%d]", i);
		if (str[i][0] == '\'')
		{
			temp2 = ft_substr(str[i], 1, strlen(str[i]) - 2);
			free(str[i]);
			str[i] = temp2;
		}
		else
		{
			if (str[i][0] == '\"')
			{
				temp2 = ft_substr(str[i], 1, strlen(str[i]) - 2);
				free(str[i]);
				str[i] = temp2;
			}
			count = ft_count(str[i]);
			if (count == 0)
			{
				i++;
				continue ;
			}
			temp = malloc(sizeof (char *) * (ft_count(str[i]) + 1));
			temp[ft_count(str[i])] = NULL;
			ft_split_expand(str[i], temp, count);
			ft_expand(&temp, data);
			free (str[i]);
			str[i] = ft_super_join(temp);
			//ft_freeo(temp, 1);
		}
		i++;
	}
}
/*
void	ft_expansion_2(char ***str, t_data *data)
{
	int		i;
	char	**temp;
	int		count;
	char	*temp2;

	i = -1;
	if (str == NULL)
		return ;
	while ((*str)[++i] != NULL)
	{
		printf("[%d]", i);
		if ((*str)[i][0] == '\'')
		{
			temp2 = ft_substr((*str)[i], 1, strlen((*str)[i]) - 2);
			free((*str)[i]);
			(*str)[i] = temp2;
		}
		else
		{
			if ((*str)[i][0] == '\"')
			{
				temp2 = ft_substr((*str)[i], 1, strlen((*str)[i]) - 2);
				free((*str)[i]);
				(*str)[i] = temp2;
			}
			count = ft_count((*str)[i]);
			if (count == 0)
				continue ;
			temp = malloc(sizeof (char *) * (ft_count((*str)[i]) + 1));
			temp[ft_count((*str)[i])] = NULL;
			ft_split_expand((*str)[i], temp, count);
			ft_expand(&temp, data);
			free ((*str)[i]);
			(*str)[i] = ft_super_join(temp);
			//ft_freeo(temp, 1);
		}
	}
}*/

void	ft_expansion(t_data *data)
{
	(void)data;
	//ft_print_data(data);
}

