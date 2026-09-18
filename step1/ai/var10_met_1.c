#include <stdio.h>
#include <math.h>
#include <limits.h>

// Вспомогательная функция для ввода одного double-значения с проверкой
static int readDouble(const char *prompt, double *value)
{
    printf("%s", prompt);
    if (scanf("%lf", value) != 1)
    {
        printf("Ошибка ввода!\n");
        return 0;
    }
    return 1;
}

int main(void)
{
    double a, b, c;
    double StartX, EndX, dX;
    double F;

    printf("Введите параметры:\n");
    if (!readDouble("a = ", &a))           return 1;
    if (!readDouble("b = ", &b))           return 1;
    if (!readDouble("c = ", &c))           return 1;
    if (!readDouble("X нач. = ", &StartX)) return 1;
    if (!readDouble("X кон. = ", &EndX))   return 1;
    if (!readDouble("dX = ", &dX))         return 1;

    // Защита от NaN/Inf — без неё дальнейшие сравнения и цикл
    // ведут себя непредсказуемо
    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        !isfinite(StartX) || !isfinite(EndX) || !isfinite(dX))
    {
        printf("Ошибка: введено недопустимое значение (NaN/Inf).\n");
        return 1;
    }

    // Защита от некорректного интервала
    if (dX <= 0 || StartX > EndX)
    {
        printf("Ошибка: некорректные параметры интервала.\n");
        return 1;
    }

    
    const double LL_SAFE_BOUND = 9e18;
    if (fabs(a) > LL_SAFE_BOUND || fabs(b) > LL_SAFE_BOUND || fabs(c) > LL_SAFE_BOUND)
    {
        printf("Ошибка: значения a, b или c слишком велики для целой части.\n");
        return 1;
    }

    // Целая часть a, b, c (отбрасывание дробной части)
    long long A_int = (long long)a;
    long long B_int = (long long)b;
    long long C_int = (long long)c;


    long long bitExpr = (~(A_int | B_int)) & (A_int ^ C_int);

    // Безопасность от чрезмерного числа точек (защита от зависания
    // при очень маленьком dX на большом интервале)
    double approxSteps = (EndX - StartX) / dX;
    if (approxSteps > 1e7)
    {
        printf("Ошибка: слишком мелкий шаг dX для заданного интервала.\n");
        return 1;
    }

    // Эпсилон для границы цикла — масштабируем от dX, а не берём
    // фиксированную константу
    double loopEps = fabs(dX) * 1e-9;

    printf("\n-----------------------------------\n");
    printf("| %-10s | %-16s |\n", "X", "F(X)");
    printf("-----------------------------------\n");

    // x вычисляется заново на каждом шаге (StartX + i*dX), а не
    // накапливается через x += dX — так исключена погрешность
    // накопления при большом числе итераций
    for (long long i = 0; ; i++)
    {
        double x = StartX + (double)i * dX;
        if (x > EndX + loopEps)
        {
            break;
        }

        int defined = 1;

        // Ветка 1: x < 3 и b != 0
        if (x < 3.0 && b != 0.0)
        {
            F = a * x * x - b * x + c;
        }

        // Ветка 2: x > 3 и b == 0
        else if (x > 3.0 && b == 0.0)
        {

            double eps = 1e-9 * fmax(1.0, fabs(c));
            if (fabs(x - c) < eps)
            {
                defined = 0;
            }
            else
            {
                F = (x - a) / (x - c);
            }
        }

        // Ветка 3: остальные случаи (включая x == 3)
        else
        {
            if (c == 0.0)
            {
                defined = 0;
            }
            else
            {
                F = x / c;
            }
        }

        if (!defined)
        {
            printf("| %-10.2lf | %-16s |\n", x, "Не определена");
        }
        else if (bitExpr == 0)
        {
            // По условию: целое значение — берём (int)F
            printf("| %-10.2lf | %-16d |\n", x, (int)F);
        }
        else
        {
            printf("| %-10.2lf | %-16.2lf |\n", x, F);
        }
    }

    printf("-----------------------------------\n");

    return 0;
}