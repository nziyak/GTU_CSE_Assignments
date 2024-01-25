#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define LINE 1000
#define VALNUM 100

void reader(void);

int main()
{
    reader();

    return 0;
}

void reader(void)
{
    FILE *reader;

    double coef, result = 0; 
    char before, after, line[LINE]; // character before the x, after the x, the line string
    char *ptr = line; // pointer to traverse the line string
    int bytesRead, val = 5, power, first; 

    reader = fopen("polynomials.txt", "r");

    if (reader == NULL)
    {
        printf("polynomials.txt file could not be opened!");
        exit(0);
    }

    while (fgets(line, LINE, reader) != NULL)
    {
        ptr = line; // take ptr to the beginning at each line

        first = 1;

        while (*ptr != '\0') // while the line traverser pointer did not arrive to end of line
        {
            if (first)
            {
                if (line[0] == 'x') // if the first element of the line is x
                {
                    coef = 1;

                    if (line[1] == '^') 
                    {
                        sscanf(line, "x^%d%n", &power, &bytesRead);
                        ptr += bytesRead;
                    }
                    
                    else if (line[1] == '+' || line[1] == '-')
                    {
                        power = 1;
                        ptr++;
                    }
                }

                result = coef * pow(val, power);
                first = 0;
            }

            sscanf(ptr, "%cx%c%n", &before, &after, &bytesRead); // first take element with the chars before and after it and hold the processed char number

            if (before == '+' || before == '-')
            {
                if (after == '+' || after == '-')
                {
                    power = 1; // if there is no power power is automatically 1
                }
                
                else if (after == '^')
                {
                    sscanf(ptr, "x^%d%n", &power, &bytesRead); // take power
                    ptr += bytesRead;
                }

                if (before == '+')  coef = 1;
                else if (before == '-')  coef = -1;
            }

            if (bytesRead > 0)
            {
                ptr += bytesRead;
            }

            result = coef * pow(val, power);
            printf("result: %lf\n", result);
        }
    }

    fclose(reader);
}
