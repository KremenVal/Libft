/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 12:37:40 by vkremen           #+#    #+#             */
/*   Updated: 2018/10/29 12:13:37 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*neg(int n)
{
	int		copy_n;
	int		count;
	char	*answer;

	copy_n = n;
	count = 0;
	while (copy_n < 0)
	{
		copy_n = copy_n / 10;
		count++;
	}
	answer = (char*)malloc(sizeof(char) * count + 2);
	if (answer == 0)
		return (0);
	answer[count + 1] = '\0';
	while (count > 0)
	{
		answer[count--] = (n % 10 * -1) + '0';
		n = n / 10;
	}
	answer[count] = '-';
	return (answer);
}

static	char	*poss(int n)
{
	int		copy_n;
	int		count;
	char	*answer;

	copy_n = n;
	count = 0;
	while (copy_n > 0)
	{
		copy_n = copy_n / 10;
		count++;
	}
	answer = (char*)malloc(sizeof(char) * count + 1);
	if (answer == 0)
		return (0);
	answer[count] = '\0';
	while (count-- > 0)
	{
		answer[count] = (n % 10) + '0';
		n = n / 10;
	}
	return (answer);
}

char			*ft_itoa(int n)
{
	char *answer;

	if (n == 0)
	{
		answer = (char*)malloc(sizeof(char) + 1);
		if (answer == 0)
			return (0);
		answer[0] = '0';
		answer[1] = '\0';
		return (answer);
	}
	if (n < 0)
		return (neg(n));
	else
		return (poss(n));
}
