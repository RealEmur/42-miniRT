#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*strchr(const char *s, int c);
char	*substr(char const *s, unsigned int start, size_t len);
char	*strjoin(char const *s1, char const *s2);
size_t	strlen(const char *s);

#endif