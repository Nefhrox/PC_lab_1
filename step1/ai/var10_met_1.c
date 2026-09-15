#include <stdio.h>

int main(void)
{
    float a, b, c;
    float StartX, EndX, dX;
    float F;

    printf("Введите:\n");
    printf("\ta = "); scanf("%f", &a);
    printf("\tb = "); scanf("%f", &b);
    printf("\tc = "); scanf("%f", &c);
    printf("\tX нач. = "); scanf("%f", &StartX);
    printf("\tX кон. = "); scanf("%f", &EndX);
    printf("\tdX = "); scanf("%f", &dX);

    // Защита от некорректного шага и бесконечного цикла
    if (dX <= 0 || StartX > EndX)
    {
        printf("Некорректные параметры интервала.\n");
        return 1;
    }

    // Находим целые части a, b и c
    long Az = (long)a;
    long Bz = (long)b;
    long Cz = (long)c;

    // НЕ(Aц ИЛИ Bц) И (Aц МОД2 Cц)
    long bitExpr = (~(Az | Bz)) & (Az ^ Cz);

    for (float x = StartX; x <= EndX; x += dX)
    {
        int defined = 1;

        if (x < 3 && b != 0)
        {
            F = a * x * x - b * x + c;
        }
        else if (x > 3 && b == 0)
        {
            // Проверка деления на ноль для второй формулы
            if (x == c)
            {
                defined = 0;
            }
            else
            {
                F = (x - a) / (x - c);
            }
        }
        else
        {
            // Проверка деления на ноль для третьей формулы
            if (c == 0)
            {
                defined = 0;
            }
            else
            {
                F = x / c;
            }
        }

        // Вывод результата
        if (!defined)
        {
            printf("x = %.2f\tF не определена\n", x);
        }
        else if (bitExpr == 0)
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