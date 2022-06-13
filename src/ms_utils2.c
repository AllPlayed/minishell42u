/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:56:14 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/13 10:15:12 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_split2(char *str, int *i)
{
	int	k;

	while (str && str[*i] && str[*i] == '$' && str[(*i) + 1] == '$')
		(*i)++;
	k = *i;
	(*i) += 1;
	while (str && str[*i] != '$' && str[*i] != '\0')
		(*i)++;
	return (ft_substr(str, k, (*i) - k));
}

int	ft_strlen2d(char **str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	ft_pass_6(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			break ;
		i++;
	}
	return (i);
}

int	ft_pass_7(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_close_builtinpipe(t_data *data)
{
	if (data->stdin != -1)
	{
		dup2(0, STDIN_FILENO);
	}
	if (data->stdout != -1)
	{
		dup2(0, STDOUT_FILENO);
	}
}
