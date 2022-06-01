/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:27:53 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/01 17:09:56 by ullorent         ###   ########.fr       */
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

char	**ft_dollar_1(char *temp, char **hold, t_data *data)
{
	int	i;
	int	len;
	int	index;

	i = 0;
	len = 0;
	index = 0;
	while (1)
	{
		if (temp[i] == '\0' || (!ft_isalnum(temp[i]) && (ft_isalnum(temp[i + 1])
					|| temp[i + 1] == '\0' || temp[i + 1] == '$') && i != 0))
		{
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
	hold = ft_dollar_2(hold, len, data);
	return (hold);
}

char	**ft_dollar_2(char **hold, int len, t_data *data)
{
	int	i;
	int	env_index;

	i = 0;
	while (hold[i] != NULL)
	{
		if (hold[i][0] == '$')
		{
			env_index = ft_str_compare(data->env, hold[i] + 1);
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
	return (hold);
}

char	*ft_dollar(char *temp, t_data *data)
{
	char	**hold;
	int		i;
	int		index;
	char	*final;

	i = 0;
	if (ft_check_dollar(temp))
		return (temp);
	index = 0;
	while (temp[i] != '\0')
	{
		if (!ft_isalnum(temp[i]) && (ft_isalnum(temp[i + 1])
				|| temp[i + 1] == '\0' || temp[i + 1] == '$') && i != 0)
			index++;
		i++;
	}
	hold = malloc(sizeof(char *) * (index + 2));
	hold[index + 1] = NULL;
	hold = ft_dollar_1(temp, hold, data);
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
