#define _GNU_SOURCE

//#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#include <stdarg.h>
#include <fcntl.h>

#define  FROM  "/var/run/gpspipe"
#define  TO    "/var/run/gpspip2"

/* try to see if we can save some ram if we don't overwrite this function

FILE *fopen(const char *path, const char *mode) {
    //printf("In our own fopen, opening %s\n", path);

    void *(*original_fopen)(const char*, const char*) = dlsym(RTLD_NEXT, "fopen");
    if (!strcmp(path, FROM)) {
        //printf("Redirecting %s to %s\n", FROM, TO);
        path = TO;
    }
    return (*original_fopen)(path, mode);
}

*/

int open(const char *path, int oflag, ...) {
    //printf("In ower own open, opening %s\n", path);

    int (*original_open)(const char *, int, ...) = dlsym(RTLD_NEXT, "open");
    int ret;
    va_list args;
    if (!strcmp(path, FROM)) {
        //printf("Redirecting %s to %s\n", FROM, TO);
        path = TO;
    }
    va_start(args, oflag);
    if (oflag & O_CREAT) {
        ret = original_open(path, oflag, (mode_t)va_arg(args, mode_t));
    } else {
        ret = original_open(path, oflag);
    }
    va_end(args);
    return ret;
}
