#include <string.h>


int main () {
    char data[1025];
    void *res = memset(data, 'a', 50);
    if (res != data) {
        return 1;
    }
    memset(data+50, 'b', 35);
    memset(data+50+35, 'c', 50);
    for (int i = 0; i < 50; ++i) {
        if (data[i] != 'a') {
            return 1;
        }
    }
    for (int i = 50; i < 50+35; ++i) {
        if (data[i] != 'b') {
            return 1;
        }
    }
    for (int i = 50+35; i < 50+35+50; ++i) {
        if (data[i] != 'c') {
            return 1;
        }
    }
    return 0; 
}
