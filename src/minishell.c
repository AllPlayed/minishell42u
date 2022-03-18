/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ullorent <ullorent@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 13:20:32 by ullorent          #+#    #+#             */
/*   Updated: 2022/03/18 13:12:23 by ullorent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ft_input(str, &data);
		printf("%s\n", str);
		free (str);
		//ft_free_data(&data);
	}
	return (0);
}
