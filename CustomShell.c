#include <stdio.h>
#define ADDR_AD2_INDEX 0
#define ADDR_AD3_INDEX 1
unsigned char resultHASH[10] = { 0x00,'9','9','9','9','a','a','a','a' ,0x00 };
unsigned char addr_AE4[16] = { 0x4a, 0x18, 0xaf, 0xf7, 0x81, 0x6a, 0xd7, 0x3a, 0x0a, 0xef, 0x07, 0xf7, 0x63, 0x61, 0x74, 0x00 };
unsigned char addr_100[4 * 8] = { 0x4A, 0x16, 0x71, 0x2C, 0x11, 0xBB, 0xAF, 0x1E, 0xB8, 0x9F, 0x68, 0xD3, 0x37,
0xCD, 0x55, 0x1B, 0xB7, 0xA8, 0x02, 0xBD, 0x0B, 0xFF, 0xEE, 0x8E, 0x30, 0xC9, 0xD7, 0x12, 0xE8, 0x60, 0x0A, 0x4B };
unsigned char addr_624[5] = { 0x01,0x00,0x00 ,0x02,0x03 };
unsigned char sub_1DC(char r24);
unsigned char sub_1E7(char r24);
unsigned char _rotl(const unsigned char value, int shift);

void main()
{
	unsigned char r[32] = { 0, };
	unsigned char Y[100] = { 0, };
	char inputString[] = "9999aaaa";
	unsigned char counter = 0;
	
	unsigned char addr_100_index = 0;
	unsigned char addr_AE4_index = 0;
	
	//ù��° ����ƾ
	do
	{
		r[19] = resultHASH[ADDR_AD2_INDEX+1];
		r[18] = resultHASH[ADDR_AD2_INDEX+2];
		r[03] = resultHASH[ADDR_AD2_INDEX + 3];
		r[21] = resultHASH[ADDR_AD2_INDEX + 4];
		r[20] = resultHASH[ADDR_AD2_INDEX + 7];
		Y[5] = resultHASH[ADDR_AD2_INDEX + 5];
		Y[4] = resultHASH[ADDR_AD2_INDEX + 6];
		Y[3] = resultHASH[ADDR_AD2_INDEX + 8];
		r[24] = addr_100[addr_100_index] ^ r[18];
		

		//addr_100_index �� 0,4,8,12,...28�� ���� ����������
		addr_100_index = counter * 4;

		//AD2 �� ����
		r[24] = addr_100[addr_100_index];
		resultHASH[ADDR_AD2_INDEX] = r[24]^r[18]; 

			
		r[24] = addr_AE4[addr_AE4_index] & 0x5;
		
		// �� ���� ���� 
		Y[0xB] = r[18];
		Y[8] = r[19];
		Y[7] = r[20];
		Y[6] = r[21];
		Y[0xA] = r[22];
		Y[9] = r[23];
		Y[0xC] = r[25];
		
		
		r[24] = sub_1DC(r[24]);
		

		
		//AD3�� �� ���� ����
		r[24] = addr_100[addr_100_index + r[24]]^ Y[6];
		resultHASH[ADDR_AD2_INDEX + 1] = r[24];

		r[24] = addr_AE4[addr_AE4_index];
		r[24] &= 0xA;
		r[24] >>= 1;

		r[24] = sub_1DC(r[24]);

		//AD4�� �� ���� ����
		r[24] = addr_100[addr_100_index + r[24]] ^ Y[7];
		resultHASH[ADDR_AD2_INDEX + 2] = r[24];

		//AD5�� �� ���� ����
		r[24] = ( (addr_AE4[addr_AE4_index] & 0x50) >> 4) & 0x0f ;
		r[24] = sub_1DC(r[24]);
		r[24] = addr_100[addr_100_index + r[24]] ^ r[3];
		resultHASH[ADDR_AD2_INDEX + 3] = r[24];

		//AD6�� �� ���� ����
		r[24] = ((addr_AE4[addr_AE4_index] & 0xA0) >> 4) & 0x0f;
		r[24] >>= 1;
		r[24] &= 0x7;
		r[24] = sub_1DC(r[24]);
		r[24] = addr_100[addr_100_index + r[24]] ^ Y[8];
		resultHASH[ADDR_AD2_INDEX + 4] = r[24];

		//AD7�� �� ���� ����
		r[24] = (addr_AE4[addr_AE4_index] & 0x05);
		r[24] = sub_1DC(r[24]);
		r[24] = addr_100[addr_100_index + r[24]] ^ Y[5];
		resultHASH[ADDR_AD2_INDEX + 5] = r[24];
	
		//AD8�� �� ���� ����
		r[24] = (addr_AE4[addr_AE4_index] & 0x0A)>>1;
		r[24] = sub_1DC(r[24]);
		r[24] = addr_100[addr_100_index + r[24]] ^ Y[4];
		resultHASH[ADDR_AD2_INDEX + 6] = r[24];

		//AD9�� �� ���� ����
		r[24] = ((addr_AE4[addr_AE4_index] & 0x50) >> 4) & 0x0f;
		r[24] = sub_1DC(r[24]);
		r[24] = addr_100[addr_100_index + r[24]] ^ Y[0xB];
		resultHASH[ADDR_AD2_INDEX + 7] = r[24];

		//ADA�� �� ���� ����
		r[24] = ((addr_AE4[addr_AE4_index] & 0xA0) >> 4) & 0x0f;
		r[24] >>= 1;
		r[24] &= 0x7;
		r[24] = sub_1DC(r[24]);
		r[24] = addr_100[addr_100_index + r[24]] ^ Y[0x3];
		resultHASH[ADDR_AD2_INDEX + 8] = r[24];
			
		//ADB�� �� ���� ����
		r[24] = (addr_AE4[addr_AE4_index++] & 0x05);
		r[24] = sub_1DC(r[24]);
		r[24] = addr_100[addr_100_index + r[24]] ^ r[3];
		resultHASH[ADDR_AD2_INDEX + 9] = r[24];

		counter++;
		for (int i = 0; i < 10; i++)
		{
			printf("%02x ", (unsigned)resultHASH[i]);
		}
		printf("\n");
	} while (counter < 8);


	//����Ͽ��� ���� �ʱ�ȭ
	counter = 0;
	addr_100_index = 0;
	addr_AE4_index = 0;
	r[8] = r[1];
	r[9] = r[1];
	r[18] = 0;
	r[19] = 1;
	

	//�ݺ��� ������ AD2 �� ���
	unsigned char sum = 0;
	unsigned char carry_count = 0;

	for (int i = 0; i < 8; i++)
	{
		if (sum + (unsigned)inputString[i] > 0xFF)
		{
			carry_count++;
		}
		sum += (unsigned)inputString[i] ;
	}
	r[8] = sum;
	r[9] = carry_count;
	Y[2] = r[9];
	Y[1] = r[8];
	resultHASH[ADDR_AD2_INDEX] = r[8];
	r[6] = r[1];
	r[7] = r[1];

	//�ι�° ��� ��ƾ
	do
	{
		//���� �� Y������ �� �������Ϳ� �ű�� ����
		r[23] = resultHASH[ADDR_AD2_INDEX+0];
		r[22] = resultHASH[ADDR_AD2_INDEX+1];
		r[20] = resultHASH[ADDR_AD2_INDEX+2];
		r[02] = resultHASH[ADDR_AD2_INDEX+3];
		r[03] = resultHASH[ADDR_AD2_INDEX+4];
		r[19] = resultHASH[ADDR_AD2_INDEX+5];
		r[18] = resultHASH[ADDR_AD2_INDEX+6];
		r[25] = resultHASH[ADDR_AD2_INDEX+7];
		r[21] = resultHASH[ADDR_AD2_INDEX+8];
		Y[0xB] = r[18] ;
		Y[0x8] = r[19];
		Y[0x7] = r[20];
		Y[0x6] = r[21];
		Y[0xA] = r[22];
		Y[0x9] = r[23];
		Y[0xC] = r[25];

		addr_100_index = counter * 4;

		//AD2 �� ����
		r[24] = addr_AE4[addr_AE4_index] & 0x42;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 0] = r[24] ^ Y[9];
		
		//AD3 �� ����
		r[24] = addr_AE4[addr_AE4_index] & 0x81;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 1] = r[24] ^ r[3];

		//AD4 �� ����
		r[24] = addr_AE4[addr_AE4_index] & 0x42;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 2] = r[24] ^ Y[0xA];
		
		//AD5 �� ����
		r[24] = addr_AE4[addr_AE4_index] & 0x24;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 3] = r[24] ^ Y[0x6];


		//AD6 �� ����
		r[24] = addr_AE4[addr_AE4_index] & 0x18;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 4] = r[24] ^ Y[0x7];


		//AD7 �� ����
		r[24] = addr_AE4[addr_AE4_index] & 0x81;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 5] = r[24] ^ Y[0x8];

		//AD8 �� ����
		r[24] = addr_AE4[addr_AE4_index] & 0x42;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 6] = r[24] ^ Y[0xB];

		//AD9 �� ����
		r[24] = addr_AE4[addr_AE4_index] & 0x24;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 7] = r[24] ^ Y[0xC];

		//ADA �� ����
		r[24] = addr_AE4[addr_AE4_index] & 0x18;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 8] = r[24] ^ r[2];

		//ADB �� ����
		r[24] = addr_AE4[addr_AE4_index++] & 0x81; //AE4�� �ε����� 1�������ϹǷ� ���⼭ ������Ŵ
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		resultHASH[ADDR_AD2_INDEX + 9] = r[24] ^ r[3];
			
		//counter ����
		counter++;

		for (int i = 0; i < 10; i++)
		{
			printf("%02x ", (unsigned)resultHASH[i]);
		}
		printf("\n");

	} while (counter < 8);

	printf("%s \n", inputString);
	printf("hash calculate complete!!!\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%02x ", (unsigned)resultHASH[i]);
	}
}

unsigned char sub_1DC(char r24)
{
	r24 -= 1;
	if (0 <= r24 && r24 <= 4)
		return addr_624[r24];
	else
		return 0;
}
unsigned char sub_1E7(unsigned char r24)
{
	switch(r24)
	{
	case 0x18:
	case 0x24:
	case 0x42:
	case 0x81:
		return 0x3;
	case 0x10:
	case 0x20:
	case 0x40:
	case 0x80:
		return 0x2;
	case 0x1:
	case 0x2:
	case 0x4:
	case 0x8:
		return 0x01;
	default:
		return 0x0;
	}
}
unsigned char _rotl(const unsigned char value, int shift) 
{
	if ((shift &= sizeof(value) * 8 - 1) == 0)
		return value;
	return (value << shift) | (value >> (sizeof(value) * 8 - shift));
}