/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aphyo-ht <aphyo-ht@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 18:36:44 by aphyo-ht          #+#    #+#             */
/*   Updated: 2026/05/02 00:32:05 by aphyo-ht         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

///////////////////////////////////////////////////////////////////////////////
//									CTYPE                                    //
///////////////////////////////////////////////////////////////////////////////

int					ft_isalpha(int c);
int					ft_isdigit(int i);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isspace(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
int					ft_safe_atoi(const char *str, int *val);
int					ft_safe_atoi_ps(const char *str, int *val);
double				ft_atof(char *str);

///////////////////////////////////////////////////////////////////////////////
//									STRING                                   //
///////////////////////////////////////////////////////////////////////////////

int					ft_startswith(char *str, char *start);
char				**ft_split(char *str, char c);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_sarr_free(char **arr);
char				*ft_strdup(char *str);
char				**ft_split_spaces(char *str);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

///////////////////////////////////////////////////////////////////////////////
//									PRINT                                    //
///////////////////////////////////////////////////////////////////////////////

void				ft_putstr(char *s);
size_t				ft_putstr_fd(char *str, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

///////////////////////////////////////////////////////////////////////////////
//									MATH                                     //
///////////////////////////////////////////////////////////////////////////////

int					ft_iseven(int i);
int					ft_isodd(int i);
int					ft_abs(int n);

///////////////////////////////////////////////////////////////////////////////
//									OTHERS                                   //
///////////////////////////////////////////////////////////////////////////////

void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_calloc(size_t count, size_t size);

///////////////////////////////////////////////////////////////////////////////
//									LINKED LIST                              //
///////////////////////////////////////////////////////////////////////////////


#endif