#include "syscall.h"

int main()
{
    int i;
    for(i=33;i<127;i++){
        PrintNum(i);
        PrintChar((char)(i));
    }
    Halt();
}