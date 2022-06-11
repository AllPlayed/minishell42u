/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:57:57 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/11 12:23:52 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_error(t_data *data, char *str)
{
	printf("bashie: unset: `%s': not a valid identifier\n", str);
	data->status = 1;
	return (1);
}

int	check_unset(t_data *data, char *temp)
{
	int		i;

	i = 1;
	if (temp[0] != '_' && !ft_isalpha(temp[0]))
		return (ft_unset_error(data, temp));
	while (temp[i] != '\0')
	{
		if (!ft_isalnum(temp[i]) && temp[i] != '_')
			return (ft_unset_error(data, temp));
		i++;
	}
	return (0);
}

void	ft_unset3(t_data *data, char *str)
{
	int	index;

	index = ft_str_compare(data->env, str);
	free (str);
	if (index != -1)
		ft_unset2(data, index);
}

void	ft_unset2(t_data *data, int index)
{
	int		i;
	char	**temp;
	int		size;

	i = 0;
	size = ft_strlen2d(data->env);
	temp = malloc(size * sizeof(char *));
	while (data->env[i] != NULL && i != index)
	{
		temp[i] = data->env[i];
		i++;
	}
	free(data->env[i]);
	i++;
	while (data->env[i] != NULL)
	{
		temp[i - 1] = data->env[i];
		i++;
	}
	free(data->env);
	temp[i - 1] = NULL;
	data->env = temp;
}

void	ft_unset(t_data *data)
{
	char	*final;
	int		i;

	i = 1;
	if (data->cmd[1] == NULL)
	{
		ft_unset_error(data, "");
		return ;
	}
	while (data->cmd[i] != NULL)
	{
		if (check_unset(data, data->cmd[i]))
		{
			i++;
			continue ;
		}
		final = ft_strdup(data->cmd[i]);
		ft_unset3(data, final);
		i++;
	}
}
