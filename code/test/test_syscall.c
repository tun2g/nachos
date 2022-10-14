#include "syscall.h"

int main() {
    int result;
    /* Don't need to Halt() anymore because the PC will increase automatically
     */
    result = Add(2, 3);
}