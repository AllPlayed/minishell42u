/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_input2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:27:53 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/10 14:05:10 by ecamara          ###   ########.fr       */
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

char	*ft_dollar_v22(char *str, t_data *data)
{
	int		env_index;
	int		len;


	if (str[0] == '$' && str[1] == '\0')
		return (str);
	else if (str[0] == '$' && str[1] != '?')
	{
		env_index = ft_str_compare(data->env, str + 1);
		len = ft_strlen(str);
		free (str);
		if (env_index == -1)
			str = NULL;
		else
			str = ft_substr(data->env[env_index],
					len, ft_strlen(data->env[env_index] + len));
	}
	else if (str[0] == '$' && str[1] == '?')
	{
		free (str);
		str = ft_itoa(data->status);
	}
	return (str);
}

int	ft_pass_dollar(char *str)
{
	int	i;

	i = 1;
	if (str[1] == '?')
		return (2);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}	

char	*ft_dollar_v2(char *str, t_data *data)
{
	char	*hold;
	char	*aux;
	int		index;
	int		i;

	i = 0;
	hold = NULL;
	//printf("%s", str);
	while (str[i] != '\0')
	{
		if (str[i] != '$')
		{
			//printf("[%s][%c][%d]",str, str[i], i);
			hold = ft_ms_join(hold, &str[i], ft_strlen(hold), 1);
			i++;
		}
		else
		{
			index = i;
			i += ft_pass_dollar(str + i);
			aux = ft_dollar_v22(ft_substr(str, index, i - index), data);
			hold = ft_ms_join(hold, aux, ft_strlen(hold), ft_strlen(aux));
			free (aux);
			//printf("[%s][%c][%d]",str, str[i], i);
		}
	}
	free (str);
	return (hold);
}

void	ft_expansion(char **str, t_data *data, int n, int j)
{
	char	*temp2;
	int		i;
	char	*hold;

	if (str == NULL)
		return ;
	temp2 = NULL;
	while (j < n)
	{
		i = 0;
		while (str[j][i])
		{
			i += ft_pass(str[j] + i);
			if (str[j][i] == '\'')
			{
				hold = ft_substr(str[j], i + 1, ft_pass_2(str[j] + i, str[j][i]) - 2);
				temp2 = ft_ms_join(temp2, hold,
						ft_strlen(temp2), ft_strlen(hold));
				free (hold);
				i += ft_pass_2(str[j] + i, str[j][i]);
			}
			else if (str[j][i] == '\"')
			{
				hold = ft_substr(str[j], i + 1, ft_pass_2(str[j] + i, str[j][i]) - 2);
				hold = ft_dollar_v2(hold, data);
				temp2 = ft_ms_join(temp2, hold, ft_strlen(temp2), ft_strlen(hold));
				i +=  ft_pass_2(str[j] + i, str[j][i]);
				free (hold);
			}
			else if (str[j][i] == '$')
			{
				hold = ft_substr(str[j], i, ft_pass_5(str[j] + i + 1) + 1);
				hold = ft_dollar_v2(hold, data);
				temp2 = ft_ms_join(temp2, hold, ft_strlen(temp2), ft_strlen(hold));
				free (hold);
				i += ft_pass_5(str[j] + i + 1) + 1;
			}
			else
			{
				hold = ft_substr(str[j], i, ft_pass_5(str[j] + i));
				temp2 = ft_ms_join(temp2, hold,
				ft_strlen(temp2), ft_strlen(hold));
				free (hold);
				i += ft_pass_5(str[j] + i);
			}
		}
		free (str[j]);
		if (!temp2 || temp2 == NULL)
			str[j] = NULL;
		else
			str[j] = ft_strdup(temp2);
		free(temp2);
		temp2 = NULL;
		j++;
	}
}
