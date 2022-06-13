/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 11:56:10 by ecamara           #+#    #+#             */
/*   Updated: 2022/06/13 09:03:46 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_changepwd(t_data *data, int index1, int index2)
{
	char	*hold;
	char	*final;
	int		len;

	free (data->env[index2]);
	len = ft_findequal(data->env[index1]);
	hold = ft_substr(data->env[index1], len + 1,
			ft_strlen(data->env[index1] + len + 1));
	final = ft_strjoin("OLDPWD=", hold);
	free (hold);
	data->env[index2] = final;
	hold = getcwd(NULL, 0);
	data->env[index1] = ft_strjoin("PWD=", hold);
	free (hold);
}

void	ft_reversepwd(t_data *data, int index1, int index2)
{
	char	*hold;
	char	*final;
	char	*hold2;
	int		len;

	hold2 = data->env[index1];
	len = ft_findequal(data->env[index2]);
	hold = ft_substr(data->env[index2], len + 1,
			ft_strlen(data->env[index2] + len + 1));
	chdir(hold);
	final = ft_strjoin("PWD=", hold);
	free (hold);
	data->env[index1] = final;
	len = ft_findequal(hold2);
	hold = ft_substr(hold2, len + 1, ft_strlen(hold2 + len + 1));
	data->env[index2] = ft_strjoin("OLDPWD=", hold);
	free (hold);
	free (hold2);
}

void	ft_cd(t_data *data, int index1, int index2, int boo)
{
	if (data->cmd[1] && !ft_strncmp(data->cmd[1], "-", 2))
	{
		index1 = ft_str_compare(data->env, "PWD");
		index2 = ft_str_compare(data->env, "OLDPWD");
		if (index1 != -1 && index2 != -1)
		{
			ft_reversepwd(data, index1, index2);
			ft_pwd();
		}
	}
	else if (data->cmd[1])
	{
		boo = chdir(data->cmd[1]);
		if (boo == -1)
			printf("bashie: cd: %s: No such file or directory\n", data->cmd[1]);
		else
		{
			index1 = ft_str_compare(data->env, "PWD");
			index2 = ft_str_compare(data->env, "OLDPWD");
			if (index1 != -1 && index2 != -1)
				ft_changepwd(data, index1, index2);
		}
	}
}
