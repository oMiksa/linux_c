#include <stdio.h>

struct StrStruct {
    char a;
    int b;
};

struct StrStructPacked {
    char a;
    int b;
}__attribute__((__packed__));

int main(int argc, char const *argv[])
{
    char str[10] = {'A', 0, 0, 0, 0, 'B', 0, 0, 0, 0};
    
    struct StrStruct *s;
    struct StrStructPacked *s_p;

    s = (struct StrStruct*)str;
    s_p = (struct StrStructPacked*)str;

    printf("str[10] = {'A', 0, 0, 0, 0, 'B', 0, 0, 0, 0};\n\
struct StrStruct {\n   char a;\n   int b;\n};\n");
    printf("out from struct:\n  char a = %c\n   int b = %d\n", s->a, s->b);
    printf("out from struct att(packed):\n  char a = %c\n   int b = %d\n", s_p->a, s_p ->b);

    return 0;
}
