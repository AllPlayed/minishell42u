/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:43:21 by ecamara           #+#    #+#             */
/*   Updated: 2022/05/31 12:57:13 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export(t_data *data)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	if (data->cmd[1][0] == '=')
	{
		printf("bash: export: `%s': not a valid identifier\n", data->cmd[1]);
		data->status = 1;
	}
	while (data->cmd[1][i] != '\0')
	{
		if (data->cmd[1][i] == '=')
			check++;
		i++;
	}
	if (check)
		return (0);
	return (1);
}

void	ft_export(t_data *data)
{
	int		i;
	char	**env2;

	i = 0;
	if (check_export(data) || data->cmd[1] == NULL)
		return ;
	ft_unset(data);
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
	printf("bashie: %d: commmand not found\n", data->status);
	data->status = 127;
}
