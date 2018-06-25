#include <stdio.h>
  
int baz_int_int(int a, int b) {
    return a + b;
}
  
int baz_int_float(int a, float b) {
    return a + (int) b;
}
  
int baz_float_int(float a, int b) {
    return (int) a + b;
}
  
int baz_float_float(float a, float b) {
    return (int) a + (int) b;
}
  
#define bar(X, Y) _Generic((X),\
    int:   _Generic((Y),\
        int:   baz_int_int,\
        float: baz_int_float\
    ),\
    float: _Generic((Y),\
        int:   baz_float_int,\
        float: baz_float_float\
    )\
)(X, Y)
  
int main() { 
    int d = bar(1, 2);
    int e = bar(1.0f, 2.0f);
 
    printf("%d\n", d);
    printf("%d\n", e);
     
    return 0;
}