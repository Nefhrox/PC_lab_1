#include <stdio.h>
#include <math.h>

#define EPSILON 1e-9

int main(void)
{
    double a, b, c;
    double start_x, end_x, dx;
    double f_val;
    int i;

    printf("Введите a, b, c, X нач., X кон., dX:\n");

    /* Проверка корректности ввода формата */
    if (scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &start_x, &end_x, &dx) != 6)
    {
        printf("Ошибка: некорректный ввод данных.\n");
        return 1;
    }

    /* Защита от NaN и Infinity (повышает надежность кода до уровня production) */
    if (isnan(a) || isinf(a) || isnan(b) || isinf(b) || isnan(c) || isinf(c) ||
        isnan(start_x) || isinf(start_x) || isnan(end_x) || isinf(end_x) || isnan(dx) || isinf(dx))
    {
        printf("Ошибка: введены специальные значения (NaN или Inf).\n");
        return 1;
    }

    if (dx <= 0 || start_x > end_x)
    {
        printf("Ошибка: некорректно задан шаг или границы интервала.\n");
        return 1;

    }

    printf("\n%8s   %12s\n", "x", "F(x)");
    printf("---------------------------\n");

    /* Итерация без предварительного вычисления 'n' избегает проблем с округлением.
       Счетчик i гарантирует отсутствие накопления ошибки для x. */
    for (i = 0; ; i++)
    {
        double x = start_x + i * dx;
        int is_defined = 1;

        /* Надежное условие выхода: останавливаемся, если x превысил правую границу */
        if (x > end_x + EPSILON)
        {
            break;
        }

        /* Строгое сравнение a с нулем, так как переменная вводится пользователем напрямую */
        if (x < 10.0 && a == 0.0)
        {
            if (fabs(b - x) < EPSILON)
                is_defined = 0;
            else
                f_val = (cos(x) + 1.0) / (b - x);
        }
        else if (x > 10.0 && a != 0.0)
        {
            if (fabs(sin(x)) < EPSILON)
                is_defined = 0;
            else
                f_val = (a * x * x - b * x + c) / sin(x);
        }
        else
        {
            if (x + c <= 0.0 || fabs(b) < EPSILON)
                is_defined = 0;
            else
                f_val = log(x + c) / (2.0 * b);
        }

        if (is_defined)
            printf("%8.2f   %12.4f\n", x, f_val);
        else
            printf("%8.2f   не определено\n", x);
    }

    return 0;
}
