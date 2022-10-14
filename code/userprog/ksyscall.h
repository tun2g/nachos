/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include "synchconsole.h"
#define __STDC_LIMIT_MACROS
#include <stdint.h>

#define TAB ((char)9)
#define SPACE ((char)' ')

void SysHalt()
{
  kernel->interrupt->Halt();
}

int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

int SysReadNum(){
  char* num = new char[255];

  char c = kernel->synchConsoleIn->GetChar();
  if(c==EOF){
    return 0;
  }
  int i=0,z=1;
  while(c!=((char)10)){

    if(i==0 && (c== SPACE||c==TAB) ){
     c = kernel->synchConsoleIn->GetChar();
      continue;
    }
    else if(i== 0 && c=='-')
      z=-1;
    else
        num[i++]=c;

    c = kernel->synchConsoleIn->GetChar();
  }
  int s=0;
  int LENGTH =strlen(num);
  DEBUG(dbgSys,"LENGTH="<<LENGTH);
  
  for(int i=0;i<LENGTH;i++){
     if(num[i]<'0' || num[i]>'9')
      return 0;

    s=s*10+(num[i]-'0');    
  }
  s*=z; 

  if(strcmp(num,"2147483648")>=0 && LENGTH>=10 && z==1){
    delete[] num;
    return 0;

  }
    
  delete[] num;
  return s;
}

void SysPrintNum(int number){
  char * _num =new char [12];
  if(number==0)
     kernel->synchConsoleOut->PutChar('0');
  
 if(number== INT32_MIN){
  kernel->synchConsoleOut->PutChar('-');
    for(int i=0;i<10;i++){
      kernel->synchConsoleOut->PutChar("2147483648"[i]);
    }
    kernel->synchConsoleOut->PutChar('\n');
    return;
 }
  if(number<0){
    kernel->synchConsoleOut->PutChar('-');
    number = -number;
  }
  

  int n =0;
  while(number>0){
    _num[n++]=((char)(number%10+'0'));
    number = number/10;
  }
  for(int i=n-1;i>=0;i--){
    kernel->synchConsoleOut->PutChar(_num[i]);
  }
}

char SysReadChar() { return kernel->synchConsoleIn->GetChar(); }
void SysPrintChar(int c){
  kernel->synchConsoleOut->PutChar(c);
  kernel->synchConsoleOut->PutChar('\n');
}
int SysRandomNum(){
  return random();
}

char* SysReadString(int addr,int length) {
    DEBUG(dbgSys, "String length:" <<length);
    char* buffer = new char[length + 1];
    for (int i = 0; i < length; i++) { 
        buffer[i] = SysReadChar();     // Nhập các phần tử của chuỗi
    }
    buffer[length] = '\0'; // thêm kí tự kết thúc chuỗi
    for (int i = 0; i < length; i++) {
        kernel->machine->WriteMem(addr + i, 1,buffer[i]); // Ghi từng phần tử của C-string vào bộ nhớ  
    }
    kernel->machine->WriteMem(addr + length, 1, '\0'); // ghi phần tử kết thúc
    return buffer; // trả về char*
}
char* ReadFromMem(int addr)
{
    int i = 0;
    int c;
    char* str=new char[255]; 
    while(c!='\0') {
        kernel->machine->ReadMem(addr + i ,1, &c); //đọc và gán các phần tử của chuỗi tđược lưu trong bô nhớ
                                                    // và lưu vào c(char)
        str[i++] = (char)c;
      //thêm c vào mảng kí tự str  
    } 

    char*cs=new char[i+1];   // khởi tạo lại con trỏ mảng có kích thước là dộ dài của chuỗi+1
    for(int idx=0;idx<i;idx++){
      cs[idx]=str[idx]; // cs sao chép từ chuỗi str
    }
    cs[i]='\0'; //gán phần tử kết thúc
    delete str; //xóa con trỏ
    return cs; //trả về char*
}
void SysPrintString(char * str) {
    for (int i = 0; i < int(strlen(str)); i++) {
        kernel->synchConsoleOut->PutChar(str[i]); // đưa từng ohan62 tử của mảng ra màn hình
    }
}

#endif /* ! __USERPROG_KSYSCALL_H__ */