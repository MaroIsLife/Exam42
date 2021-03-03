#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#define ER_ARG "Error: argument\n"
#define ER_FILE "Error: Operation file corrupted\n"


int ft_strlen(char *s)
{
    int i = 0;

    while (s[i] != '\0')
        i++;

        return (i);
}

int write_error(char *s)
{
    write(1,s,ft_strlen(s));
    return (1);
}


int main(int argc,char **argv)
{
    FILE *file;

    file = fopen(argv[1],"r");
    if (file == NULL)
        return(write_error(ER_FILE));
    
    int width, height;
    char background;
    if (fscanf(file,"%d %d %c\n",&width,&height,&background) != 3)
        return (write_error(ER_FILE));

    if (width <= 0 || width > 300)
        return(write_error(ER_FILE));
    
    if (height <= 0 || height > 300)
        return(write_error(ER_FILE));

    char id;
    float idx, idy;
    float rad;
    char c;
    int read;
    float distance;
    char paper[width * height];

    memset(paper,background,width * height);

    int y, x;

    while ((read = fscanf(file,"%c %f %f %f %c\n",&id,&idx,&idy,&rad,&c)) == 5)
    {
        if (rad <= 0 || !(id == 'c' || id == 'C'))
            return(write_error(ER_FILE));
        y = 0;
        while (y < height)
        {
            x = 0;
            while (x < width)
            {
                distance = sqrt((x - idx) * (x - idx) + (y - idy) * (y - idy));
                if (distance <= rad)
                {
                    if (id == 'C')
                    {
                        paper[y * width + x] = c;
                    }
                    else if ((rad - distance) < 1. && id == 'c')
                    {
                        paper[y * width + x] = c;
                    }
                }
                x++;
            }
            y++;
        }

    }
if (read != EOF)
    return(write_error(ER_FILE));

y = 0;
while (y < height)
{
    write(1,paper + (y * width),width);
    write(1,"\n",1);
    y++;
}
    return (0);
}