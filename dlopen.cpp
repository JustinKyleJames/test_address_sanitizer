#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <sanitizer/lsan_interface.h>

extern "C" const char* __asan_default_options()
{
    printf("This ran!");
    return "log_path=/tmp/irods_asan_output:detect_odr_violation=1";
}

void leak() {
    int * ptr = (int*) malloc(500 * sizeof(int));
    ptr[0] = 5;
}

int main(int argc, char** argv)
{
    void *handle;
    void (*func_doit)(const char *);

    handle = dlopen("./shared.so", RTLD_LAZY);

    if (!handle) {
        /* fail to load the library */
        fprintf(stderr, "Error: %s\n", dlerror());
        return EXIT_FAILURE;
    }

    *(void**)(&func_doit) = dlsym(handle, "doit");
    if (!func_doit) {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return EXIT_FAILURE;
    }

    //leak();

    func_doit("hello");
    dlclose(handle);

    //__lsan_do_leak_check();

    return EXIT_SUCCESS;
}
