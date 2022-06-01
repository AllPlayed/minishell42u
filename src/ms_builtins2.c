/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:43:21 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/01 10:11:38 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_error(t_data *data, char *str)
{
	printf("bashie: export: `%s': not a valid identifier\n", str);
	data->status = 1;
	return (1);
}

int	check_export(t_data *data)
{
	int		i;
	int		check;
	char	*temp;

	i = 1;
	temp = ft_super_join(data->cmd + 1);
	check = 0;
	if (temp[0] == '=')
		return (ft_export_error(data, temp));
	while (temp[i] != '\0')
	{
		if (check == 0 && !ft_isalnum(temp[i]) && temp[i] != '=')
			return (ft_export_error(data, temp));
		if (temp[i] == '=')
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
	int		j;
	char	*temp;

	i = 0;
	if (data->cmd[1] == NULL)
		return ;
	temp = ft_super_join(data->cmd + 1);
	if (check_export(data))
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
	j = 1;
	env2[i] = NULL;
	while (data->cmd[j] != NULL)
	{
		env2[i] = ft_ms_join(&env2[i], &data->cmd[j], ft_strlen(env2[i]), ft_strlen(data->cmd[j]), 0);
		j++;
	}
	env2[i + 1] = NULL;
	free (data->env);
	data->env = env2;
}

int	ft_findequal(char *str)
{
	int	i;

	i = 0;
	if (!str || str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_unset(t_data *data)
{
	int		index;
	char	**temp;
	int		size;
	int		i;

	i = 0;
	if (data->cmd[1] == NULL)
		return ;
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
