/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:59:56 by ecamara           #+#    #+#             */
/*   Updated: 2022/03/25 14:08:54 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_dup_2d(char **str)
{
	char	**dup;
	int		i;

	i = 0;
	while (str[i] != NULL)
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	while (str[i] != NULL)
	{
		dup[i] = ft_strdup(str[i]);
		i++;
	}
	return (dup);
}
