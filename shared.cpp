#include <stdio.h>
#include <stdlib.h>

/*extern "C" const char* __asan_default_options()
{
    printf("This ran!");
    return "log_path=/tmp/irods_asan_output:detect_odr_violation=1";
}*/

void leak() {
    int * ptr = (int*) malloc(100 * sizeof(int));
    ptr[0] = 5;
}


extern "C"  void doit(const char* str)
{
    printf("Doit ran with arg %s.\n", str);
    leak();
}
