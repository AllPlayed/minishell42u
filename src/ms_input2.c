/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:27:53 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/01 14:11:20 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_dollar(char *temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (temp[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_dollar(char *temp, t_data *data)
{
	char	**hold;
	int		i;
	int		index;
	int		env_index;
	int		len;
	char	*final;

	i = 0;
	printf("str[%s]\n", temp);
	if (ft_check_dollar(temp))
		return (temp);
	index = 0;
	while (temp[i] != '\0')
	{
		if (!ft_isalnum(temp[i]) && (ft_isalnum(temp[i + 1]) || temp[i + 1] == '\0' || temp[i + 1] == '$') && i != 0)
		{
			//printf("[%s][%d]\n", temp, i);
			index++;
		}
		i++;
	}
	hold = malloc(sizeof(char *) * (index + 2));
	hold[index + 1] = NULL;
	i = 0;
	index = 0;
	len = 0;
	while (1)
	{
		if (temp[i] == '\0' || (!ft_isalnum(temp[i]) && (ft_isalnum(temp[i + 1]) || temp[i + 1] == '\0' || temp[i + 1] == '$') && i != 0))
		{
			//printf("len[%d], i[%d], index[%d], [%s]\n", len, i, index, ft_substr(temp, index, i - index));
			hold[len] = ft_substr(temp, index, i - index);
			index = i;
			if (temp[i] == '\0')
				break ;
			i++;
			len++;
		}
		else
			i++;
	}
	i = 0;
	index = 0;
	while (hold[i] != NULL)
	{
		if (hold[i][0] == '$')
		{
			env_index = ft_str_compare(data->env, hold[i] + 1);
			//printf("[%s]\n", hold[i] + 1);
			len = ft_strlen(hold[i]);
			free (hold[i]);
			if (env_index == -1)
				hold[i] = NULL;
			else
				hold[i] = ft_substr(data->env[env_index],
						len, ft_strlen(data->env[env_index] + len));
		}
		i++;
	}
	final = ft_super_join(hold);
	ft_freeo(hold, 1);
	free(temp);
	return (final);
}

void	ft_expansion_2(char **str, t_data *data, int n)
{
	int		i;
	char	*temp2;

	i = 0;
	if (str == NULL)
		return ;
	while (i < n)
	{
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
			str[i] = ft_dollar(str[i], data);
		}
		i++;
	}
}