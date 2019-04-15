/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkremen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 18:44:42 by vkremen           #+#    #+#             */
/*   Updated: 2018/11/12 15:52:45 by vkremen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void			del_lst(t_list **res, size_t fd)
{
	t_list	*ntd;
	t_list	*nts;

	nts = (*res);
	if (nts->content_size == fd)
	{
		(*res) = (*res)->next;
		free(nts->content);
		free(nts);
		return ;
	}
	while (nts->next->content_size != fd && nts->next)
		nts = nts->next;
	ntd = nts->next;
	nts->next = nts->next->next;
	free(ntd);
}

static t_list		*find_fd(t_list **res, size_t fd)
{
	t_list	*new_fd;
	t_list	*find;

	find = (*res);
	if ((*res) == 0)
	{
		(*res) = ft_lstnew("", fd);
		return ((*res));
	}
	while (find != 0)
	{
		if (find->content_size == fd)
			return (find);
		find = find->next;
	}
	new_fd = ft_lstnew("", fd);
	ft_lstadd(res, new_fd);
	return (new_fd);
}

static int			fill_line(t_list ***res, char ****line)
{
	char	*str;
	int		len;

	len = 0;
	str = (**res)->content;
	while (str[len] != '\n' && str[len])
		len++;
	RETZ(ft_strlen(str));
	***line = ft_strsub(str, 0, len);
	if (str[ft_strlen(***line)] != '\n')
		(**res)->content = ft_strdup(ft_strchr(str, '\0'));
	else
		(**res)->content = ft_strdup(ft_strchr(str, '\n') + 1);
	free(str);
	return (1);
}

static int			fill_res(t_list **res, int fd, char ***line)
{
	int		s;
	char	*ch;
	char	*tmp;

	CHECK(ch = (char*)malloc(sizeof(char) * BUFF_SIZE + 1));
	while ((s = read(fd, ch, BUFF_SIZE)))
	{
		ch[s] = '\0';
		tmp = (*res)->content;
		(*res)->content = ft_strjoin((*res)->content, ch);
		free(tmp);
		if (ft_strchr((*res)->content, '\n'))
			break ;
	}
	if (fill_line(&res, &line) == 0)
	{
		free(ch);
		return (0);
	}
	free(ch);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*res;
	t_list			*an;
	char			*ch;

	CHECK(ch = (char*)malloc(sizeof(char) * 2));
	if (fd < 0 || read(fd, ch, 0) || BUFF_SIZE < 1)
		return (-1);
	free(ch);
	an = find_fd(&res, fd);
	if (fill_res(&an, fd, &line) == 0)
	{
		del_lst(&res, fd);
		return (0);
	}
	return (1);
}
