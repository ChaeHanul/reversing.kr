#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int findValue(unsigned __int64 after_value);
unsigned __int64 reverse_calculator(unsigned __int64 after_value, unsigned __int64 LSB_before_value,unsigned __int64 CRC1_untable_element);
unsigned __int64 calculator(unsigned __int64 before_value,int count);
int compare(void  * first,void * second);
void valueInit(); // header file���� �������� ���� �����ϹǷ� ������ �ʱ�ȭ�ϴ� �Լ��� �������.

unsigned char CRC1_data[256];
unsigned __int64 CRC1_untable[256];