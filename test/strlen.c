#include <string.h>


int main() {
    int rval = 1;
    rval = rval && (strlen("") == 0);
    rval = rval && (strlen("a") == 1);
    rval = rval && (strlen("hello world") == 11);
    rval = rval && (strlen("aaaa\0abc") == 4);
    rval = rval && (strlen("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa") == 92);
    return !rval;
}
