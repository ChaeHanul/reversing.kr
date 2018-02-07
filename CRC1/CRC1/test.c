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
					//a �� 0��° b�� 16��° c�� 32��° d�� 48��° �����̹Ƿ� crc1_data_table�� ���� �ٲ۴�.
					CRC1_data[0] = (unsigned char)(a);
					CRC1_data[16] = (unsigned char)(b);
					CRC1_data[32] = (unsigned char)(c);
					CRC1_data[48] = (unsigned char)(d);
					before_value = 0x0;
					//48��° ���ڱ����� ���Ͽ� CRC1 ���� ���Ѵ�.
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
	// ���� �������� �ϴµ� 6�� �ɸ���.
	// �Ʒ��� memory_table�� ���Ͽ� quick sort
	qsort(memory_table, table_size, sizeof(__int64), compare);
	printf("\n finish quick sort !!\n");
	// quick sort ��
	// check value�� GOTOHELL �̶�� ���ڿ��� ��� ���� ��, ���������� ���ڿ��� ���� CRC1 �˰����� �����Ͽ� ���� ���̴�.
	// ���� �ݴ�� check value ���� 48�� ���ڿ� ���� after value �������� ���� �� ������ ���� ���� �������� ���� ���̺� �ϳ��� �����Ѵٸ� �װ��� ���̶�� �ǹ��μ�
	//  ���� ��� ������ ��� LLEH ��� ���ڿ��� ���ٸ� GOTO �� ���� �ϹǷ� ���;� �Ѵ� �̸� ���� �׽�Ʈ �� �ڿ� ���� ã�ƺ����� �ϰڴ�.
	// *kyKHELL �� �Ǵ��� üũ�غ��ڴ� --> ������ �ϸ鼭 ��ġ�� �ٲ����� ���� �ε����� ã�°� �Ұ�������
	// �پ��� �ذ����� �ְ����� �ѹ��� ó���ϸ� �Ǵ°��̹Ƿ� ���̺��ϳ� �� ����� ����Ž���ϴ� ������ �ذ���
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
					// 49��° ���ڱ��� ������ �ϸ� 48��° ���ڿ��� �������� �� �����(48���� calculator�� �������� �� after_value)�� ���´�.
					after_value = check_value;
	
					for (int i = 112; i >= 49; i--)
					{
						int index = findValue(after_value);
						unsigned __int64 CRC1_untable_element = CRC1_untable[index];
						before_value = index ^ CRC1_data[i];//���⼭ before_value�� before_value�� ������ ����Ʈ �̴�.
						before_value = reverse_calculator(after_value,before_value,CRC1_untable_element);
						after_value = before_value;
					}
	
					//�ش� after_value�� ������ memory_table�� ���Ͽ� ���� Ž�� ����
					int find = bsearch(&after_value,memory_table,table_size,sizeof(__int64),compare);
					if (!find) //�˻� ���� �� ����
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