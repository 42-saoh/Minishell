/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_env_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taesan <taesan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 03:57:34 by taesan            #+#    #+#             */
/*   Updated: 2021/08/27 05:57:40 by taesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	write_env_file(char *key, char *param)
{
	if (!datafile_to_temp(ENV_FILE, ENV_FILE_2, key, param))
		return (0);
	if (!temp_to_datafile(ENV_FILE_2, ENV_FILE))
		return (0);
	if (!remove_var(EXPORT_FILE, EXPORT_FILE_2, key))
		return (0);
	return (1);
}
