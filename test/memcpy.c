#include <string.h>


int main() {
    char data1[1024];
    char data2[1024];
    memset(data1, 'a', 1024);

    memcpy(data2, data1, 1024);
    for (int i = 0; i < 1024; ++i) {
        if (data2[i] != 'a') {
            return 1;
        }
    }
    memset(data2, 0, 1024);

    // test start alignment
    memcpy(data2+1, data1, 1023);
    if (data2[0] != 0) {
        return 1;
    }
    for (int i = 1; i < 1024; ++i) {
        if (data2[i] != 'a') {
            return 1;
        }
    }
    memset(data2, 0, 1024);

    // test end alignment
    memcpy(data2, data1, 1023);
    if (data2[1023] != 0) {
        return 1;
    }
    for (int i = 0; i < 1023; ++i) {
        if (data2[i] != 'a') {
            return 1;
        }
    }
    memset(data2, 0, 1024);

    return 0;
}
