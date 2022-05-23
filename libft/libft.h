/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 11:04:23 by fiaparec          #+#    #+#             */
/*   Updated: 2022/04/02 11:50:41 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUFFER_SIZE 42
# define TAB_INIT 1
# define TAB_RESET 0
# define LEFT 1
# define RIGHT 0

typedef struct s_print
{
	va_list	args;
	int		size;
	int		dash;
	int		zero;
	int		sign;
	int		spce;
	int		hash;
	int		wdth;
	int		prec;
}	t_print;

// libft base
// mem functions
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

// char functions
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

// str functions
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

// fd functions
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// gnl
// get_next_line main function
char	*get_next_line(int fd);

// utils
char	*gnl_join(char *s1, const char *s2);

// printf
// ft_printf main function
int		ft_printf(const char *format, ...);

// flags, wdth, prec identifiers
int		pf_flags_identifier(t_print *tab, int pos, char flag);
int		pf_wdth_prec_identifier(t_print *tab, const char *format,
			int pos, char prec);

// flags, wdth, prec handlers
char	*pf_dash_or_zero_handler(t_print *tab, char *s, char *fill);
char	*pf_sign_or_spce_handler(t_print *tab, char *s);
char	*pf_hash_handler(char *s, char x);
char	*pf_prec_handler(t_print *tab, char *s);
char	*pf_wdth_handler(t_print *tab, char *s);

// conversions
int		printf_c(t_print *tab, char c);
int		printf_s(t_print *tab, char *s);
int		printf_p(t_print *tab, unsigned long int n);
int		printf_d(t_print *tab, int n);
int		printf_i(t_print *tab, int n);
int		printf_u(t_print *tab, unsigned int n);
int		printf_x(t_print *tab, unsigned int n);
int		printf_uppx(t_print *tab, unsigned int n);
int		printf_percent(t_print *tab);

// utils
t_print	*pf_init_reset_tab(t_print *tab, int init);
char	*pf_itoa_base_ul(unsigned long int n, int base, char conv);
char	*pf_joinswap(char *s1, char *s2, int right);
char	*pf_substrswap(char *s, int start, int len);

#endif
