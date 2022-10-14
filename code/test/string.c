#include "syscall.h"

char a[255];
int main()
{
  PrintString("Nhap do dai chuoi: ");
  ReadString(a,ReadNum());
  PrintString("Chuoi vua nhap: ");
  PrintString(a);
  PrintChar('\n');
  Halt();
}