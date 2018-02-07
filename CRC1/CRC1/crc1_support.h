#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int findValue(unsigned __int64 after_value);
unsigned __int64 reverse_calculator(unsigned __int64 after_value, unsigned __int64 LSB_before_value,unsigned __int64 CRC1_untable_element);
unsigned __int64 calculator(unsigned __int64 before_value,int count);
int compare(void  * first,void * second);
void valueInit(); // header file에서 전역변수 선언만 가능하므로 별도로 초기화하는 함수를 만들었음.

unsigned char CRC1_data[256];
unsigned __int64 CRC1_untable[256];