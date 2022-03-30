/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:27:53 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/30 13:41:31 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_change(char **str, t_data *data)
{
	int		i;
	int		hold;
	int		len;
	char	**temp;

	i = 0;
	len = ft_strlen(*str);
	while (data->env[i] != NULL)
	{
		hold = ft_strncmp(data->env[i], *str, len + 1);//+1
		if (hold)
		{
			temp = ft_substr_ms(data->env[i], len + 1,
					ft_strlen(data->env[i]) - len - 1);
			ft_freeo(str, 0);
			return (temp);
		}
		i++;
	}
	return (NULL);
}

char	*ft_dollar(char *str, t_data *data)
{
	char	*temp;
	int		i;
	int		index;

	i = 1;
	index = 0;
	while (str[i] != '\0' && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			temp = ft_ms_join(&temp, ft_substr_ms(str, index, i - index),
					0, 0, 0);
			index = i;
			while (str[i] != ' ' || str[i] != '\"')
				i++;
			temp = ft_ms_join(&temp, ft_change(ft_substr_ms(str, index + 1,
							i - index), data), 0, 0, 1);
			continue ;
		}
		i++;
	}
	temp = ft_ms_join(&temp, ft_substr_ms(str, index, i - index), 0, 0, 1);
	return (temp);
}

void	ft_expand(char **str, t_data *data)
{
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == '\'')
		{
			temp = ft_substr(str[i], 1, ft_strlen(str[i]) - 1);
			free (str[i]);
			str[i] = temp;
		}
		else
			temp = ft_dollar(str[i], data);
		i++;
	}
}

void	ft_expansion(t_data *data)
{
	ft_expand(data->cmd, data);
	ft_expand(data->infile.files, data);
	ft_expand(data->outfile.files, data);
}
