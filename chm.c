#include <math.h>
#include <stdio.h>

int nodes[5] = {11, 21, 41, 81, 161};

long double f1(long double x) {
    long double n = 30240*pow(x, 5) - 33600*pow(x, 3) + 7200*x;
    return n;
}

long double f2(long double x) {
    long double n = 30240*pow(x, 9) + 60480*pow(x, 8) + 57120*pow(x, 7) + 53760*pow(x, 6) + 
        57600*pow(x, 5) - 120000*pow(x, 4) - 146400*pow(x, 3) + 28800*pow(x, 2) - 36000*x;
    return n;
}

long double trap(long double (*func)(long double), int n) {
    long double a = -1, b = 1;
    long double h = (b - a) / n;
    long double sum = 0;

    for (int i = 0; i < n; i++) {
        long double p1 = func(a + i * h);
        long double p2 = func(a + (i + 1) * h);
        sum += h * (p1 + p2) / 2;
    }
    return sum;
}

long double simpson(long double (*func)(long double), int n) {
    long double a = -1, b = 1;
    long double h = (b - a) / (n - 1);
    long double sum = 0;
    long double x1 = a, x2 = a + h, x3 = a + 2*h;

    for (int i = 0; i < ((n-1)/2); i++) {
        long double p1 = func(x1);
        long double p2 = func(x2);
        long double p3 = func(x3);
        sum += (h/6) * (p1 + 4*p2 + p3);
        
        x1 = x3; x2 = x3 + h; x3 += 2*h;
    }
    return sum;
}


int main() {
    printf("\n Метод трапеций для 1ой задачи:\n\n");
    printf("Кол-во узлов   Приближ. интеграл\n");
    for (int i = 0; i < 5; i++) {
        printf("    %d\t\t%Lf (%Le)\n", nodes[i], trap(f1, nodes[i]), trap(f1, nodes[i]));
    }
    printf("\n");

    printf("\n Метод трапеций для 2ой задачи:\n\n");
    printf("Кол-во узлов   Приближ. интеграл\n");
    for (int i = 0; i < 5; i++) {
        printf("    %d\t\t%Lf\n", nodes[i], trap(f2, nodes[i]));
    }
    printf("\n");

    printf("\n Метод Симпсона для 1ой задачи:\n\n");
    printf("Кол-во узлов   Приближ. интеграл\n");
    for (int i = 0; i < 5; i++) {
        printf("    %d\t\t%Lf (%Le)\n", nodes[i], simpson(f1, nodes[i]), simpson(f1, nodes[i]));
    }
    printf("\n");

    printf("\n Метод Симпсона для 2ой задачи:\n\n");
    printf("Кол-во узлов   Приближ. интеграл\n");
    for (int i = 0; i < 5; i++) {
        printf("    %d\t\t%Lf\n", nodes[i], simpson(f2, nodes[i]));
    }
    printf("\n\n");
    

    long double misTrap1[5];
    long double misSim1[5];
    for(int i = 0; i < 5; i++){
        misTrap1[i] = 0 - trap(f1, nodes[i]);
        misSim1[i] = 0 - simpson(f1, nodes[i]);
    }

    printf("\nПорядок сходимости для метода трапеций 1ой задачи:\n");
    printf("   Кол-во узлов    Порядок сходимости\n");
    for (int i = 0; i < 4; i++) {
        printf("       %d\t\t%Lf\n", nodes[i+1], log2l(fabsl(misTrap1[i] / misTrap1[i+1])));
    }
    printf("\n\n");

    printf("\nПорядок сходимости для метода парабол 1ой задачи:\n");
    printf("   Кол-во узлов    Порядок сходимости\n");
    for (int i = 0; i < 4; i++) {
        printf("       %d\t\t%Lf\n", nodes[i+1], log2l(fabsl(misSim1[i] / misSim1[i+1])));
    }
    printf("\n\n");


    long double misTran2[5];
    long double misSim2[5];
    for(int i = 0; i < 5;i++){
        misTran2[i] = 0 - trap(f2, nodes[i]);
        misSim2[i] = 0 - simpson(f2, nodes[i]);
    }
    
    printf("\nПорядок сходимости для метода трапеций 2ой задачи:\n");
    printf("   Кол-во узлов    Порядок сходимости\n");
    for (int i = 0; i < 4; i++) {
        printf("       %d\t\t%Lf\n", nodes[i+1], log2l(fabsl(misTran2[i] / misTran2[i+1])));
    }
    printf("\n\n");

    printf("\nПорядок сходимости для метода парабол 2ой задачи:\n");
    printf("   Кол-во узлов    Порядок сходимости\n");
    for (int i = 0; i < 4; i++) {
        printf("       %d\t\t%Lf\n", nodes[i+1], log2l(fabsl(misSim2[i] / misSim2[i+1])));
    }
    printf("\n\n");

    return 0;
}