#include "syscall.h"

int main()
{

    int n,i;
    int arr[100];
    int sel,j,temp;
    do {
    PrintString("Nhap so phan tu cua mang: ");
    n=ReadNum();
    }
    while(n<0 || n>100);
    PrintString("Nhap cac phan tu cua mang: \n");
    for(i=0;i<n;i++){
        PrintString("Nhap phan tu thu ");
        PrintNum(i);
        PrintString(": ");
        arr[i]=ReadNum();
    }
    
    do {
    PrintString("Nhap 1 de xep tang dan\nNhap 2 de xep giam dan\nNhap: ");
    sel=ReadNum();  // nhập lựa chọn
    }while(sel!= 1 && sel!=2);
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1; j++) {
            if (sel == 1) {
                if (arr[j] > arr[j + 1]) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            } else if (sel == 2) {
                if (arr[j] < arr[j + 1]) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
    PrintString("Mang sau khi sap xep: ");
    for(i=0;i<n;i++){
        PrintNum(arr[i]);
        PrintChar(' ');
    }

    Halt();
}