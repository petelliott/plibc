#include <unistd.h>


int main() {
    int rval = 1;
    rval = rval && (sbrk(0) == sbrk(0));
    rval = rval && (sbrk(5) != sbrk(0));
    rval = rval && (sbrk(0) == sbrk(5));
    return !rval;
}
