/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:43:21 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/07 10:40:09 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset3(t_data *data, char *str)
{
	int	index;

	index = ft_str_compare(data->env, str);
			free (str);
	if (index != -1)
		ft_unset2(data, index);
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


int	ft_export_error(t_data *data, char *str)
{
	printf("bashie: export: `%s': not a valid identifier\n", str);
	data->status = 1;
	return (1);
}

int	ft_unset_error(t_data *data, char *str)
{
	printf("bashie: unset: `%s': not a valid identifier\n", str);
	data->status = 1;
	return (1);
}

int	check_unset(t_data *data, char *temp)
{
	int		i;

	i = 0;
	while (temp[i] != '\0')
	{
		if (!ft_isalnum(temp[i]))
			return (ft_unset_error(data, temp));
		i++;
	}
	return (0);
}

int	check_export(t_data *data, char *temp)
{
	int		i;
	int		check;

	i = 1;
	check = 0;
	if (!ft_isalnum(temp[0]))
		return (ft_export_error(data, temp));
	while (temp[i] != '\0')
	{
		if (check == 0 && !ft_isalnum(temp[i]) && temp[i] != '=')
			return (ft_export_error(data, temp));
		if (temp[i] == '=')
			check++;
		i++;
	}
	if (check == 1)
		return (0);
	return (1);
}

static void	ft_export2(t_data *data, int i, char **env2)
{
	int	j;

	j = 0;
	while (data->env[j] != NULL)
	{
		env2[j] = data->env[j];
		j++;
	}
	env2[j] = ft_strdup(data->cmd[i]);
	env2[j + 1] = NULL;
	free (data->env);
	data->env = env2;
}

void	ft_export3(t_data *data, int i)
{
	int	j;
	char	**env2;

	j = 0;
	while (data->env[j] != NULL)
		j++;
	env2 = malloc(sizeof(char *) * (j + 2));
	ft_export2(data, i, env2);
}

void	ft_export(t_data *data)
{
	int	i;
	int	len;

	i = 0;
	if (data->cmd[1] == NULL)
		return ;
	while (data->cmd[i] != NULL)
	{
		if (!check_export(data, data->cmd[i]))
		{
			len = ft_findequal(data->cmd[i]);
			ft_unset3(data, ft_substr(data->cmd[i], 0, len));
			ft_export3(data, i);
		}
		i++;
	}
	
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
		return ;
	while (data->cmd[i] != NULL)
	{
		ft_print_data(data);
		if (check_unset(data, data->cmd[i]))
		{
			i++;
			continue ;
		}
		final = ft_strdup(data->cmd[i]);
		ft_unset3(data, final);
		i++;
	}
	ft_print_data(data);
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
