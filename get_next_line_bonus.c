/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slord <slord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:14:47 by slord             #+#    #+#             */
/*   Updated: 2022/05/19 15:39:01 by slord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *restant)
{
	char	*line;
	int		i;

	i = 0;
	if (restant[i] == '\0')
		return (NULL);
	while (restant[i] && restant[i] != '\n')
		i++;
	line = ft_calloc(i + 2, 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (restant[i] && restant[i] != '\n')
	{
		line[i] = restant[i];
		i++;
	}
	if (restant[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read_file(char *restant, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		char_read;

	if (!restant)
	{
		restant = ft_calloc(1, 1);
		if (!restant)
			return (NULL);
	}
	char_read = 1;
	while (ft_search_n(restant) == 0 && char_read > 0)
	{
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read < 0)
			return (NULL);
		restant = ft_strjoin(restant, buffer, char_read);
	}
	return (restant);
}

char	*ft_free(char *restant)
{
	char	*debut_prochaine_ligne;
	int		i;
	int		j;

	i = 0;
	if (restant[0] == '\0')
	{
		free(restant);
		return (NULL);
	}
	while (restant[i] && restant[i] != '\n')
		i++;
	debut_prochaine_ligne = ft_calloc((ft_strlen(restant)) + 1 - i, 1);
	if (!debut_prochaine_ligne)
	{
		free (debut_prochaine_ligne);
		return (NULL);
	}
	i++;
	j = 0;
	while (restant[i])
		debut_prochaine_ligne[j++] = restant[i++];
	debut_prochaine_ligne[j] = '\0';
	free(restant);
	return (debut_prochaine_ligne);
}

char	*get_next_line(int fd)
{
	static char	*restant[OPEN_MAX];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	restant[fd] = ft_read_file(restant[fd], fd);
	line = ft_get_line(restant[fd]);
	restant[fd] = ft_free(restant[fd]);
	return (line);
}
