#include <stdio.h>
int gd_color(int color, int step, int i)
{
    unsigned char a, r, g, b;
    a = color >> 24;
    r = color >> 16;
    g = color >> 8;
    b = color;
    // printf ("r: %d, g: %d, b: %d\n", r, g, b);
    // r = r * i / step;
    // g = g * i / step;
    // b = b * i / step;
    a = i * 255 / step;
    // printf ("r: %d, g: %d, b: %d\n", r, g, b);
    color = a;
    color = (color << 8) + r;
    color = (color << 8) + g;
    color = (color << 8) + b;
    printf ("%X\n", color);
    return (color);
}

int main(void)
{
    int color = 0xFF0A10;
    int step = 5;
    for (int i = 0; i < step; i++)
    {
        gd_color (color, step, i + 1);
    }
    return (0);
}