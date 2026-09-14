#include <stdio.h>
#include <math.h>

int main(void)
{
    float a, b, c;              
    float StartX, EndX, dX;      
    float F;                     

    printf("Введите:\n");

    printf("a = ");       scanf("%f", &a);
    printf("b = ");       scanf("%f", &b);
    printf("c = ");       scanf("%f", &c);
    printf("X нач. = ");  scanf("%f", &StartX);
    printf("X кон. = ");  scanf("%f", &EndX);
    printf("dX = ");      scanf("%f", &dX);

    for (float x = StartX; x <= EndX; x += dX)
    {
        if (x < 3 && b != 0)
        {
            F = a * x * x - b * x + c;
        }

        else if (x > 3 && b == 0)
        {
            F = (x - a) / (x - c);
        }
        
        else
        {
            F = x / c;
        }

        int Az = (int)floor(a);   
        int Bz = (int)floor(b);   
        int Cz = (int)floor(c);   


        long bitExpr = (~(Az | Bz)) & (Az ^ Cz);


        if (!bitExpr)
        {
            printf("x = %.2f\tF = %.0f\n", x, F);
        }
        else
        {
            printf("x = %.2f\tF = %.2f\n", x, F);
        }
    }

    return 0;
}
