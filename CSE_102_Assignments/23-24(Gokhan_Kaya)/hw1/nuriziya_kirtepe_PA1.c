#include <stdio.h>
#include <math.h>
#define PTSNUM 10  // number of points each class have
#define EPSILON 0.1

float slopeCal(float avgx1, float avgy1, float avgx2, float avgy2); // calculates the slope
int classifier(float xToCheck, float yToCheck, float slope, float mptx, float mpty);
float distanceCal(float x1, float y1, float x2, float y2);
  
int main()
{
    float sumx1 = 0, sumy1 = 0, sumx2 = 0, sumy2 = 0; // variables to take coordinates of each point of each class
    float avgx1, avgx2, avgy1, avgy2; // coordinates of the average points of each class
    float slope1, slope2; // slope1 is the slope of the line between the average points
                           // slope2 is the slope of the line which is perpendicular to that line, also passes through the midpoint 
    float xToCheck, yToCheck; // coordinates of the point to be check by class
    float mptx, mpty; // coordinates of midpoint of the line between average points
    float tempx, tempy;
    float distance;
    int class;

    // taking and summing the coordinates of the first class 
    for(int i = 0; i < PTSNUM; i++)
    {
        scanf("%f %f", &tempx, &tempy);
        sumx1 += tempx;
        sumy1 += tempy;
    }

    avgx1 = sumx1 / PTSNUM; // take the average of the summed x coordinates of the first class
    avgy1 = sumy1 / PTSNUM;

    // taking and summing the coordinates of the second class 
    for(int i = 0; i < PTSNUM; i++)
    {
        scanf("%f %f", &tempx, &tempy);
        sumx2 += tempx;
        sumy2 += tempy;
    }

    avgx2 = sumx2 / PTSNUM; // take the average of the summed x coordinates of the second class
    avgy2 = sumy2 / PTSNUM;

    // we need the coordinates of the midpoint of that line to draw the second line
    mptx = (avgx1 + avgx2) / 2;
    mpty = (avgy1 + avgy2) / 2;
    
    printf("midpoint = %.1f %.1f\n", mptx, mpty);

    slope1 = slopeCal(avgx1, avgy1, avgx2, avgy2);  // now we have the slope of the line between average points of two classes
    
    if(slope1 == 0)    
        slope2 = 1 / -(slope1 + EPSILON); // because of the relation between slopes of the lines which are perpendicular

    else
        slope2 = 1 / -slope1;

    printf("separating line slope: %.1f\n", slope2);

    // now we can have the formula of the second line by using the general formula "y - y1 = m(x - x1)"
    // so the formula of the second line is "y - mpty = slope2(x - mptx)"

    while(scanf("%f %f", &xToCheck, &yToCheck) == 2) // if two float coordinates are not taken properly, terminate the program
    {    
        class = classifier(xToCheck, yToCheck, slope2, mptx, mpty);

        if(class == 1) // if class is 1, calculate the distance according to the avg point of the class 1
        {
            distance = distanceCal(xToCheck, yToCheck, avgx1, avgy1);
            printf("class 1, distance = %.1f\n", distance);
        }   

        else // if class is 2, calculate the distance according to the avg point of the class 2
        {
            distance = distanceCal(xToCheck, yToCheck, avgx2, avgy2);
            printf("class 2, distance = %.1f\n", distance);
        }
    }

    return 0;
}

float slopeCal(float avgx1, float avgy1, float avgx2, float avgy2)
{
    float slope;
    
    if((avgx2 - avgx1) == 0) // if denominator is 0, add EPSILON to denominator
        slope = (avgy2-avgy1) / ((avgx2-avgx1) + EPSILON);
    
    else
        slope = (avgy2-avgy1) / (avgx2-avgx1);

    return slope;
}

int classifier(float xToCheck, float yToCheck, float slope, float mptx, float mpty)
{
    float yOfLine; // value of the y when xToCheck is entered to formula y - mpty = slope2(x - mptx)
    
    yOfLine = slope * (xToCheck - mptx) + mpty; // value of the line at the xToCheck is found

    // check if the point is in the class 2 or not
    if(yOfLine < yToCheck)
        return 1;
        
    else
       return 2;
}

float distanceCal(float x1, float y1, float x2, float y2)
{
    float distance; // distance between two points

    distance = fabs(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2))); // absolute value of the sqrt of the summation of the (x2-x1)^2 and (y2-y1)^2 

    return distance;
}