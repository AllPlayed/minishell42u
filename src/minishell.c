/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:20:32 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/25 13:46:04 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_ms(char *s, char c)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 1;
	j = 0;
	c = 0;
	while (s[k] != '\0')
	{
		if (s[k] == '\'' || s[k] == '\"')
			k += ft_pass_2(s + k, s[k]);
		if (s[k] == '|')
			i++;
		if (s[k] != '\0')
			k++;
	}
	return (i);
}

void	ft_bridge(char *str, t_data *data, int i, int j)
{
	int	index;
	int	r;

	r = 0;
	while (j < count_ms(str, '|'))
	{
		if ((str[i] == '\'' || str[i] == '\"') && r != 0)
				i += ft_pass_2(str + i, str[i]);
		if (str[i] != '|' && r == 0)
		{
			index = i;
			r = 1;
			if (str[i] == '\'' || str[i] == '\"')
				i += ft_pass_2(str + i, str[i]);
		}
		else if ((str[i] == '|' || str[i] == '\0') && r == 1)
		{
			ft_input(ft_substr(str, index, (i - index)), data);
			ft_print_data(data);
			ft_free_data(data);
			r = 0;
			j++;
		}
		if (str[i] != '\0')
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
		ft_bridge(str, &data, 0, 0);
		printf("%s\n", str);
		free (str);
	}
	return (0);
}
