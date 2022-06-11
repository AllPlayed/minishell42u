/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:43:21 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/11 12:26:34 by ecamara          ###   ########.fr       */
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
	if (!ft_isalpha(temp[0]) && temp[0] != '_')
		return (ft_export_error(data, temp));
	while (temp[i] != '\0')
	{
		if (!ft_isalnum(temp[i]) && temp[i] != '=' && temp[i] != '_')
			return (ft_export_error(data, temp));
		if (temp[i] == '=')
			check++;
		i++;
	}
	if (check)
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
	int		j;
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

	i = 1;
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
