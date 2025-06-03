/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:01:31 by cgelgon           #+#    #+#             */
/*   Updated: 2025/06/03 11:04:19 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_error(const char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd("\n", 2);
}
