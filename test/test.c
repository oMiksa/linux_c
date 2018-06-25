#include <stdio.h>

int swap(int*,int*);

int main(int argc, char const *argv[])
{
    int a = 8;
    int b = 13;
    int *ptr = &a;
    printf("%d\n",*ptr);
    swap(ptr, &b);
    printf("%d\n",*ptr);
    return 0;
}

int swap(int *ptr1, int *ptr2)
{
    ptr1 = ptr2;
    printf("swap)%d\n", *ptr1);
    return 0;
}