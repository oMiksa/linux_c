#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define MAX_PLAG 10

int main(int argc, char const *argv[]){
    DIR *dir;
    struct dirent *de;
    void *ext_library[MAX_PLAG];
    char *path = "./plag";
    char path_new[MAX_PLAG][256];
    int (*func)(int a, int b);
    int value1 = 3, value2 = 5;
    if((dir = opendir(path)) == NULL){
        printw( "fail open dir!");
    }
    int i = 0;
    while(de = readdir(dir)){
        strcat(path_new[i], path);
        strcat(path_new[i], "/");
        strcat(path_new[i], de->d_name);

        ext_library[i] = dlopen(path_new[i], RTLD_LAZY);
        if(!ext_library[i]){
            fprintf(stderr,"dlopen() error: %s\n", dlerror());
		    return 1;
        }
        i++;
    }
    
    //как узнать имя функции?

    

    
    func = dlsym(ext_library[i], "name");
    printf("sum(%d, %d) = %d\n", value1, value2, (*funk)(value1, value2));

    dlclose(ext_library[i]);
    return 0;
}
