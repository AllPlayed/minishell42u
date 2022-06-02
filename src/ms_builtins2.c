/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:43:21 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/02 13:04:32 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_error(t_data *data, char *str)
{
	printf("bashie: export: `%s': not a valid identifier\n", str);
	data->status = 1;
	return (1);
}

int	check_export(t_data *data, char *temp)
{
	int		i;
	int		check;

	i = 1;
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

static void	ft_export2(t_data *data, int i, int j, char **env2)
{
	while (data->env[i] != NULL)
	{
		env2[i] = data->env[i];
		i++;
	}
	env2[i] = NULL;
	while (data->cmd[j] != NULL)
	{
		env2[i] = ft_ms_join(&env2[i], &data->cmd[j],
				ft_strlen(env2[i]), ft_strlen(data->cmd[j]));
		j++;
	}
	env2[i + 1] = NULL;
	free (data->env);
	data->env = env2;
}

void	ft_export(t_data *data, int i)
{
	char	**env2;
	char	*temp;

	if (data->cmd[1] == NULL)
		return ;
	temp = ft_super_join(data->cmd + 1);
	if (check_export(data, temp))
	{
		free (temp);
		return ;
	}
	ft_unset(data);
	while (data->env[i] != NULL)
		i++;
	env2 = malloc(sizeof(char *) * (i + 2));
	free(temp);
	ft_export2(data, 0, 1, env2);
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

static void	ft_unset2(t_data *data, int index)
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
	int		index;
	int		size;
	char	*hold;
	char	*final;

	if (data->cmd[1] == NULL)
		return ;
	hold = ft_super_join(data->cmd + 1);
	size = ft_findequal(hold);
	if (size != -1)
	{
		final = ft_substr(hold, 0, size);
		free (hold);
	}
	else
		final = hold;
	index = ft_str_compare(data->env, final);
	free (final);
	if (index == -1)
		return ;
	ft_unset2(data, index);
}

/*

void	ft_unset(t_data *data)
{
	int		index;
	char	**temp;
	int		size;
	int		i;
	char	*hold;
	char	*final;

	i = 0;
	if (data->cmd[1] == NULL)
		return ;
	hold = ft_super_join(data->cmd + 1);
	size = ft_findequal(hold);
	if (size !=  -1)
	{
		final = ft_substr(hold, 0, size);
		free (hold);
	}
	else
		final = hold;
	index = ft_str_compare(data->env, final);
	if (index == -1)
	{
		free (final);
		return ;
	}
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
	free (final);
	temp[i - 1] = NULL;
	data->env = temp;
}
*/
void	ft_exitstatus(t_data *data)
{
	printf("bashie: %d: commmand not found\n", data->status);
	data->status = 127;
}
