/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunhole <hyunhole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 00:11:08 by hyunhole          #+#    #+#             */
/*   Updated: 2022/09/23 14:33:03 by hyunhole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	get_tmp_file_num(void)
{
	static int tmp_file_num;

	return (tmp_file_num++); // static 변수는 0으로 초기화됨 1
}

char	*get_tmp_file_name(void)
{
	int tmp_num;
	char *str_num;
	char *file_name;

	while (1)
	{
		tmp_num = get_tmp_file_num();
		str_num = ft_itoa(tmp_num);
		file_name = ft_strjoin("tmp_file_", str_num);
		if (is_exist_file(file_name) == 0)
		{
			free(str_num);
			return (file_name);
		}
		free(file_name);
		free(str_num);
	}
}

/*
 * tmp_file.c
 * 		get_tmp_file_num()
 * 
 * is_exist_file()
 * unlink()
 */
void	delete_tmp_file(void)
{
	int		tmp_num;
	char	*str_num;
	char	*file_name;

	tmp_num = get_tmp_file_num();
	while (--tmp_num > -1)
	{
		str_num = ft_itoa(tmp_num);
		file_name = ft_strjoin("tmp_file_", str_num);
		if (is_exist_file(file_name))
			unlink(file_name);
		free(str_num);
		free(file_name);
	}
}