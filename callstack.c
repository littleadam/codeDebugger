#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

void print_stack_trace() {
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

int main() {
    print_stack_trace();
    return 0;
}
