/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:56:14 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/31 13:56:27 by ullorent         ###   ########.fr       */
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
