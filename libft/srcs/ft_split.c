/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavicent <pavicent@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:36:46 by pavicent          #+#    #+#             */
/*   Updated: 2024/02/21 17:15:13 by pavicent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_word_count(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s != '\0')
	{
		if (*s == c)
			s++;
		else
		{
			cnt++;
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	return (cnt);
}

static char	**free_memory(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (NULL);
}

static char	**split_words(size_t idx, char const *s, char c, char **words)
{
	size_t	word_count;
	size_t	len;

	word_count = get_word_count(s, c);
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			len = 0;
			while (*(s + len) && *(s + len) != c)
				len++;
			if (idx < word_count)
			{
				words[idx] = ft_substr(s, 0, len);
				if (!words[idx])
					return (free_memory(words));
				idx++;
			}
			s += len;
		}
	}
	words[idx] = 0;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	idx;
	char	**words;

	if (!s)
		return (NULL);
	words = (char **)malloc(sizeof(char *) * (get_word_count(s, c) + 1));
	if (!words)
		return (NULL);
	idx = 0;
	words = split_words(idx, s, c, words);
	if (!words)
		return (NULL);
	return (words);
}
