/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:20:32 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/23 16:40:59 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bridge(char *str, t_data *data)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += ft_pass_2(str + 1, str[i]);
		if (str[i + 1] == '|' || str[i + 1] == '\0')
		{
			ft_input(ft_substr(str, index, i - index + 1), data);
			index = i + 2;
			i++;
			ft_print_data(data);
			ft_free_data(data);
		}
		if (str[i])
			i++;
	}
}

int	main(void)
{
	char	*str;
	t_data	data;

	while (1)
	{
		str = readline("bashie > ");
		if (str[0] == '\0')
		{
			free (str);
			continue ;
		}
		ft_bridge(str, &data);
		printf("%s\n", str);
		free (str);
	}
	return (0);
}
