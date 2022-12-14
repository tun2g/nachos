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
        buffer[i] = SysReadChar();     // Nh???p c??c ph???n t??? c???a chu???i
    }
    buffer[length] = '\0'; // th??m k?? t??? k???t th??c chu???i
    for (int i = 0; i < length; i++) {
        kernel->machine->WriteMem(addr + i, 1,buffer[i]); // Ghi t???ng ph???n t??? c???a C-string v??o b??? nh???  
    }
    kernel->machine->WriteMem(addr + length, 1, '\0'); // ghi ph???n t??? k???t th??c
    return buffer; // tr??? v??? char*
}
char* ReadFromMem(int addr)
{
    int i = 0;
    int c;
    char* str=new char[255]; 
    while(c!='\0') {
        kernel->machine->ReadMem(addr + i ,1, &c); //?????c v?? g??n c??c ph???n t??? c???a chu???i t???????c l??u trong b?? nh???
                                                    // v?? l??u v??o c(char)
        str[i++] = (char)c;
      //th??m c v??o m???ng k?? t??? str  
    } 

    char*cs=new char[i+1];   // kh???i t???o l???i con tr??? m???ng c?? k??ch th?????c l?? d??? d??i c???a chu???i+1
    for(int idx=0;idx<i;idx++){
      cs[idx]=str[idx]; // cs sao ch??p t??? chu???i str
    }
    cs[i]='\0'; //g??n ph???n t??? k???t th??c
    delete str; //x??a con tr???
    return cs; //tr??? v??? char*
}
void SysPrintString(char * str) {
    for (int i = 0; i < int(strlen(str)); i++) {
        kernel->synchConsoleOut->PutChar(str[i]); // ????a t???ng ohan62 t??? c???a m???ng ra m??n h??nh
    }
}

#endif /* ! __USERPROG_KSYSCALL_H__ */