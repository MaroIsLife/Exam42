#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ER_ARG "Error: argument\n"
#define ER_FILE "Error: Operation file corrupted\n"


int write_error(char *s)
{
    write(1,s,strlen(s));
    return (1);
}


int main(int argc, char **argv)
{

    FILE *file;
    int width, height;
    char background;

    if (argc != 2)
        return(write_error(ER_ARG));


    file = fopen(argv[1],"r");
    if (file == NULL)
        return(write_error(ER_FILE));

    if (fscanf(file,"%d %d %c\n",&width,&height,&background) != 3)
        return (write_error(ER_FILE));
    
    if ((width < 0 && width >= 300) && (height < 0 && height >= 300))
        return (write_error(ER_FILE));

    char paper[height * width];
    
    memset(paper,background,width * height);
    
    int read;
    float idx ,idy , rad;
    char id ,c;
    int x, y;
    float distance;

    while((read = fscanf(file,"%c %f %f %f %c\n",&id,&idx,&idy,&rad,&c)) == 5)
    {
        if (rad <= 0 || !(id == 'c' || id == 'C'))
            return (write_error(ER_FILE));

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
                        paper[y * width + x] = c;
                    else if ((rad - distance) < 1. && id == 'c')
                        paper[y * width + x] = c;   
                }
                x++; 
            }
            y++;
        }
    }
    y = 0;
    while (y < height)
    {
        write(1, paper + (y * width), width);
        write(1,"\n",1);
        y++;
    }
    return (0);
}
