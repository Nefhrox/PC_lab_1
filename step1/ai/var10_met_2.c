#include <stdio.h>
#include <math.h>

#define EPS 1e-6f   // порог для сравнения вещественных чисел с нулём

int main(void)
{
    float a, b, c;
    float StartX, EndX, dX;
    float F;

    printf("Введите:\n");
    printf("a = "); scanf("%f", &a);
    printf("b = "); scanf("%f", &b);
    printf("c = "); scanf("%f", &c);
    printf("X нач. = "); scanf("%f", &StartX);
    printf("X кон. = "); scanf("%f", &EndX);
    printf("dX = ");     scanf("%f", &dX);

    for (float x = StartX; x <= EndX; x += dX)
    {
        // сравнение a с нулём через |a| < EPS, а не a == 0 / a != 0,
        // т.к. прямое сравнение вещественных чисел ненадёжно
        if ((x - 10) < 0 && fabsf(a) < EPS)
        {
            F = (cosf(x) + 1) / (b - x);
        }

        else if ((x - 10) > 0 && fabsf(a) >= EPS)
        {
            F = (a * x * x - b * x + c) / sinf(x);
        }

        else
        {
            F = logf(x + c) / (2 * b);
        }

        //f в функции логарифма/синуса/косинуса указывает C, что нужно
        //работать именно с типом данных float


        // проверка на деление на 0 чтобы программа не падала
        if (isfinite(F))
        {
            printf("x = %.2f\tF = %.4f\n", x, F);
        }
        // %.xf указывает сколько чисел после float отрисовать

        else
        {
            printf("x = %.2f\tF = не определено\n", x);
        }
    }

    return 0;
}
