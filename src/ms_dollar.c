/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:51:00 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/11 11:53:39 by ecamara          ###   ########.fr       */
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
	while (str[i] != '\0')
	{
		if (str[i] != '$')
		{
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
		}
	}
	free (str);
	return (hold);
}
