#include <stdio.h>

int sum(int, int);
void func(int (*f)(int, int));

int main(int argc, char const *argv[])
{
    func(sum);
    return 0;
}

void func(int (*f)(int, int))
{
    int first, second;
    scanf("%d%d",&first, &second);
    printf("%d", (*f)(first,second));
}

int sum(int a, int b)
{
    return a + b;
}
