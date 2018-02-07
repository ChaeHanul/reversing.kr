#include "crc1_support.h"
#include <Windows.h>
#define table_size 96*96*96*96
unsigned __int64 memory_table[table_size] = { 0, };
unsigned __int64 memory_table_temp[table_size] = { 0, };
unsigned int number_table[table_size] = { 0, };
void main()
{
	valueInit();

	unsigned __int64 after_value = 0x4ce6b97f65c99119;
	unsigned __int64 check_value = 0x4ce6b97f65c99119;
	unsigned __int64 before_value = 0x0;
	printf("crc1 reverse calculator test...\n");
	printf("-------------------------------\n");
	int count = 0;
	for (int a = 0x20; a < 0x80; a++)
	{
		for (int b = 0x20; b < 0x80; b++)
		{
			for (int c = 0x20; c < 0x80; c++)
			{
				for (int d = 0x20; d < 0x80; d++)
				{
					number_table[count] = ((unsigned)(a << 24)) | ((unsigned)(b << 16)) | ((unsigned)(c << 8)) | ((unsigned)(d));
					//a 는 0번째 b는 16번째 c는 32번째 d는 48번째 문자이므로 crc1_data_table의 값을 바꾼다.
					CRC1_data[0] = (unsigned char)(a);
					CRC1_data[16] = (unsigned char)(b);
					CRC1_data[32] = (unsigned char)(c);
					CRC1_data[48] = (unsigned char)(d);
					before_value = 0x0;
					//48번째 문자까지에 대하여 CRC1 값을 구한다.
					for (int i = 0; i < 49; i++)
					{
						after_value = calculator(before_value, i);
						before_value = after_value;
					}
					memory_table[count] = after_value;
					count++;
				}
			}
		}
	}
	memcpy(memory_table_temp, memory_table, sizeof(memory_table));
	printf("\n complete to set memory_table!!\n");
	printf("\n start quick sort !!\n");
	// 위에 과정까지 하는데 6분 걸린다.
	// 아래는 memory_table에 대하여 quick sort
	qsort(memory_table, table_size, sizeof(__int64), compare);
	printf("\n finish quick sort !!\n");
	// quick sort 끝
	// check value는 GOTOHELL 이라는 문자열이 들어 갔을 때, 순차적으로 문자열에 대해 CRC1 알고리즘을 적용하여 구한 값이다.
	// 따라서 반대로 check value 부터 48번 문자에 대한 after value 역연산을 했을 때 나오는 값이 위에 과정에서 구한 테이블에 하나라도 존재한다면 그것이 답이라는 의미인셈
	//  예를 들어 지금의 경우 LLEH 라는 문자열이 들어간다면 GOTO 가 존재 하므로 나와야 한다 이를 먼저 테스트 한 뒤에 값을 찾아보도록 하겠다.
	// *kyKHELL 로 되는지 체크해보겠다 --> 정렬을 하면서 위치가 바뀜으로 인해 인덱스로 찾는게 불가능해짐
	// 다양한 해결방법이 있겠지만 한번만 처리하면 되는것이므로 테이블하나 더 만들고 순차탐색하는 것으로 해결함
	printf("\n start reverse calculator \n");
	for (int e = 0x20; e < 0x80; e++)
	{
		for( int f = 0x20 ; f < 0x80 ; f++)
		{
			for( int g = 0x20 ; g < 0x80 ; g++)
			{
				for( int h = 0x20 ; h < 0x80 ;h++)
				{
					CRC1_data[64] = e;
					CRC1_data[80] = f;
					CRC1_data[96] = g;
					CRC1_data[112]= h;
					// 49번째 문자까지 역연산 하면 48번째 문자에서 연산했을 때 결과값(48까지 calculator를 수행했을 때 after_value)이 나온다.
					after_value = check_value;
	
					for (int i = 112; i >= 49; i--)
					{
						int index = findValue(after_value);
						unsigned __int64 CRC1_untable_element = CRC1_untable[index];
						before_value = index ^ CRC1_data[i];//여기서 before_value는 before_value의 최하위 바이트 이다.
						before_value = reverse_calculator(after_value,before_value,CRC1_untable_element);
						after_value = before_value;
					}
	
					//해당 after_value를 가지고 memory_table에 대하여 이진 탐색 수행
					int find = bsearch(&after_value,memory_table,table_size,sizeof(__int64),compare);
					if (!find) //검색 실패 시 진입
						continue;
					else
					{
						printf("\n finish reverse calculator \n");
						printf("after_value is matched!!!\n");
						unsigned int another_num = ((unsigned)(e << 24)) | ((unsigned)(f << 16)) | ((unsigned)(g<<8)) | ((unsigned)h);
						for (int i = 0; i < table_size; i++)
						{
							if (!(after_value^memory_table_temp[i]))
							{
								printf("\n that is %X", number_table[i]);
							}
						}
						printf("\n that is %X\n", another_num);
					}
				}
			}
		}
	}
}