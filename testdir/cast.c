#include <stdio.h>
#include "../libft/includes/libft.h"

int find_index(char *base, char c)
{
    int i;

    i = 0;
    while (base[i])
    {
        if (base[i] == ft_toupper(c))
            return (i);
        i++ ;
    }
    return (-1);
}

void exit_error(char *s, int exit_code)
{
    perror (s);
    exit (exit_code);
}

int atoi_base(char *s)
{
    int n;
    char *base;
    int idx;
 
    base = "0123456789ABCDEF";
    if (!s)
        exit_error ("bad address", 1);
    if (ft_strlen (s) > 10)
        exit_error ("wrong len", 1);
    if (ft_strncmp (s, "0x", 2))
        exit_error ("not found prefix", 1);
    s += 2 ;
    n = 0;
    while (*s)
    {
        idx = find_index(base, *s);
        if (idx == -1)
            exit_error ("wrong character", 1);
        n = (n * 16) + idx;
        s++ ;
    }
    return (n);
}

int main(void)
{
    // char *str = "0xFFFFFFFF";
    // int hex = 0xFFFFFFFF;
    // char *str = "0xFF000000";
    // int hex = 0xFF000000;
    char str[] = "0xFaFFb0A0";
    int hex = 0xFaFFb0A0;

    printf ("hex: %d\n", hex);
    printf ("hex: %u\n", hex);
    // printf ("hex: %d\n", atoi_base (str + 2));
    // printf ("hex: %u\n", atoi_base (str + 2));
    printf ("hex: %d\n", atoi_base (str));
    printf ("hex: %u\n", atoi_base (str));
    return (0);
}