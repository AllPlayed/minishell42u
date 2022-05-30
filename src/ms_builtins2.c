/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:43:21 by ecamara           #+#    #+#             */
/*   Updated: 2022/05/30 12:53:42 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_data *data)
{
	int		i;
	char	**env2;

	i = 0;
	if (data->cmd[1] == NULL)
		return ;
	while (data->env[i] != NULL)
		i++;
	env2 = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (data->env[i] != NULL)
	{
		env2[i] = data->env[i];
		i++;
	}
	env2[i] = ft_strdup(data->cmd[1]);
	env2[i + 1] = NULL;
	free (data->env);
	data->env = env2;
}

void	ft_unset(t_data *data)
{
	int		index;
	char	**temp;
	int		size;
	int		i;

	i = 0;
	index = ft_str_compare(data->env, data->cmd[1]);
	if (index == -1)
		return ;
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

void	ft_exitstatus(t_data *data)
{
	printf("exitstatus\n");
	printf("%d", data->status);
}