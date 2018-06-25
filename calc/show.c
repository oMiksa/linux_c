#include <stdio.h>
#include "libcalc.h"

void show()
{
    int first, second, result;
    int index;
    char key;
    int run = 0;
    while(!run){
        printf("1)add\n");
        printf("2)ded\n");
        printf("3)mult\n");
        printf("4)div\n");
        printf("5)exit\n");
        printf("?.");

        scanf("%c", &key);
        index = (int)key;

        switch (index - 48)
        {
            case 1:  
                printf("in first number ");
                scanf("%d", &first);
                printf("in second number ");
                scanf("%d", &second);
                printf("result = %d\n\n",add(first,second));
                break;
            case 2: 
                printf("in first number ");
                scanf("%d", &first);
                printf("in second number ");
                scanf("%d", &second);
                printf("result = %d\n\n",ded(first, second));
                break;
            case 3: 
                printf("in first number ");
                scanf("%d", &first);
                printf("in second number ");
                scanf("%d", &second);
                printf("result = %d\n\n",mult(first, second));
                break;
            case 4: 
                printf("in first number ");
                scanf("%d", &first);
                printf("in second number ");
                scanf("%d", &second);
                printf("result = %d\n\n",div(first, second));
                break;
            case 5:
                printf("bye\n"); 
                run++; 
                break;
            default: 
                printf("wrong choice\n\n"); 
                break;
        }
        index = 0;
    }
}