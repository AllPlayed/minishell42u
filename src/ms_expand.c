/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:27:53 by ullorent          #+#    #+#             */
/*   Updated: 2022/06/11 11:52:12 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_simplecomas(char *str, char **temp2, int *i)
{
	char	*hold;

	hold = NULL;
	hold = ft_substr(str, (*i) + 1, ft_pass_2(str + (*i), str[(*i)]) - 2);
	(*temp2) = ft_ms_join((*temp2), hold, ft_strlen((*temp2)), ft_strlen(hold));
	free (hold);
	(*i) += ft_pass_2(str + (*i), str[(*i)]);
}

void	ft_noexpand(char *str, char **temp2, int *i)
{
	char	*hold;

	hold = NULL;
	hold = ft_substr(str, (*i), ft_pass_5(str + (*i)));
	(*temp2) = ft_ms_join((*temp2), hold, ft_strlen((*temp2)), ft_strlen(hold));
	free (hold);
	(*i) += ft_pass_5(str + (*i));
}

void	ft_expand2(char *str, t_data *data, int *i, char **temp2)
{
	char	*h;

	h = NULL;
	(*i) += ft_pass(str + (*i));
	if (str[(*i)] == '\'')
		ft_simplecomas(str, temp2, i);
	else if (str[(*i)] == '\"')
	{
		h = ft_substr(str, (*i) + 1, ft_pass_2(str + (*i), str[(*i)]) - 2);
		h = ft_dollar_v2(h, data);
		(*temp2) = ft_ms_join((*temp2), h, ft_strlen((*temp2)), ft_strlen(h));
		(*i) += ft_pass_2(str + (*i), str[(*i)]);
		free (h);
	}
	else if (str[(*i)] == '$')
	{
		h = ft_substr(str, (*i), ft_pass_5(str + (*i) + 1) + 1);
		h = ft_dollar_v2(h, data);
		(*temp2) = ft_ms_join((*temp2), h, ft_strlen((*temp2)), ft_strlen(h));
		free (h);
		(*i) += ft_pass_5(str + (*i) + 1) + 1;
	}
	else
		ft_noexpand(str, temp2, i);
}

void	ft_expansion(char **str, t_data *data, int n, int j)
{
	char	*temp2;
	int		i;

	if (str == NULL)
		return ;
	temp2 = NULL;
	while (j < n)
	{
		i = 0;
		while (str[j][i])
			ft_expand2(str[j], data, &i, &temp2);
		free (str[j]);
		if (!temp2 || temp2 == NULL)
			str[j] = NULL;
		else
			str[j] = ft_strdup(temp2);
		free(temp2);
		temp2 = NULL;
		j++;
	}
}
