#include <stdio.h>
#define ADDR_AD2_INDEX 0
#define ADDR_AD3_INDEX 1
unsigned char resultHASH[10] = { 0x9A, 0x7D, 0x72, 0x75, 0xEA, 0x78, 0xA4, 0xE6, 0xF2, 0x02 };
//unsigned char resultHASH[10] = { 0x9a, 0x33, 0x6a, 0x7c, 0x83, 0x74, 0xb5, 0xc7, 0xa0, 0x33 }; 테스트용 값
unsigned char addr_AE4[16] = { 0x4a, 0x18, 0xaf, 0xf7, 0x81, 0x6a, 0xd7, 0x3a, 0x0a, 0xef, 0x07, 0xf7, 0x63, 0x61, 0x74, 0x00 };
unsigned char addr_100[4 * 8] = { 0x4A, 0x16, 0x71, 0x2C, 0x11, 0xBB, 0xAF, 0x1E, 0xB8, 0x9F, 0x68, 0xD3, 0x37,
0xCD, 0x55, 0x1B, 0xB7, 0xA8, 0x02, 0xBD, 0x0B, 0xFF, 0xEE, 0x8E, 0x30, 0xC9, 0xD7, 0x12, 0xE8, 0x60, 0x0A, 0x4B };
unsigned char addr_624[5] = { 0x01,0x00,0x00 ,0x02,0x03 };
unsigned char sub_1DC(char r24);
unsigned char sub_1E7(char r24);

void main()
{
	unsigned char r[32] = { 0, };
	unsigned char Y[100] = { 0, };
	unsigned char counter = 7; // 역연산이므로 7..6..5....0 으로 진행된다.

	unsigned char addr_100_index = 0;
	unsigned char addr_AE4_index = 7;
	do
	{
		addr_100_index = counter * 4;

		//AD2 에서 이전값 추출
		r[24] = addr_AE4[addr_AE4_index] & 0x42;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		Y[9] = r[24] ^ resultHASH[ADDR_AD2_INDEX + 0];

		//AD3 에서 이전값 추출
		r[24] = addr_AE4[addr_AE4_index] & 0x81;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		r[3] = r[24] ^ resultHASH[ADDR_AD2_INDEX + 1];

		//AD4 에서 이전값 추출
		r[24] = addr_AE4[addr_AE4_index] & 0x42;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		Y[0xA] = r[24] ^ resultHASH[ADDR_AD2_INDEX + 2];

		//AD5 에서 이전값 추출
		r[24] = addr_AE4[addr_AE4_index] & 0x24;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		Y[0x6] = r[24] ^ resultHASH[ADDR_AD2_INDEX + 3];


		//AD6 에서 이전값 추출
		r[24] = addr_AE4[addr_AE4_index] & 0x18;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		Y[0x7] = r[24] ^ resultHASH[ADDR_AD2_INDEX + 4];


		//AD7 에서 이전값 추출
		r[24] = addr_AE4[addr_AE4_index] & 0x81;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		Y[0x8] = r[24] ^ resultHASH[ADDR_AD2_INDEX + 5];

		//AD8 에서 이전값 추출
		r[24] = addr_AE4[addr_AE4_index] & 0x42;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		Y[0xB] = r[24] ^ resultHASH[ADDR_AD2_INDEX + 6];

		//AD9 에서 이전값 추출
		r[24] = addr_AE4[addr_AE4_index] & 0x24;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		Y[0xC] = r[24] ^ resultHASH[ADDR_AD2_INDEX + 7];

		//ADA 에서 이전값 추출
		r[24] = addr_AE4[addr_AE4_index--] & 0x18;
		r[24] = sub_1E7(r[24]);
		r[24] = addr_100[addr_100_index + r[24]];
		r[2] = r[24] ^ resultHASH[ADDR_AD2_INDEX + 8];

		//ADB는 애초에 0x02로 역연산과 별개의 값이 덧씌워지므로 배제

		//값을 각 Y포인터 및 레지스터에 옮기고 있음

		r[18] = Y[0xB];
		r[19] = Y[0x8];
		r[20] = Y[0x7];
		r[21] = Y[0x6];
		r[22] = Y[0xA];
		r[23] = Y[0x9];
		r[25] = Y[0xC];

		resultHASH[ADDR_AD2_INDEX + 0] = r[23];
		resultHASH[ADDR_AD2_INDEX + 1] = r[22];
		resultHASH[ADDR_AD2_INDEX + 2] = r[20];
		resultHASH[ADDR_AD2_INDEX + 3] = r[02];
		resultHASH[ADDR_AD2_INDEX + 4] = r[03];
		resultHASH[ADDR_AD2_INDEX + 5] = r[19];
		resultHASH[ADDR_AD2_INDEX + 6] = r[18];
		resultHASH[ADDR_AD2_INDEX + 7] = r[25];
		resultHASH[ADDR_AD2_INDEX + 8] = r[21];
		//counter 증가
		counter--;
	} while (counter != 0xFF);

	//두번째 루틴 진입전 초기화
	counter = 7; // 역연산이므로 7..6..5....0 으로 진행된다.
	addr_100_index = 0;
	addr_AE4_index = 7;
	do
	{
		addr_100_index = counter * 4;

		//AD2는 유추가 불가능 하므로 제거

		//AD3에서 값 생성
		r[24] = addr_AE4[addr_AE4_index] & 0x5;
		r[24] = sub_1DC(r[24]);
		Y[6] = addr_100[addr_100_index + r[24]] ^ resultHASH[ADDR_AD2_INDEX + 1];


		//AD4에서 값 생성
		r[24] = addr_AE4[addr_AE4_index];
		r[24] &= 0xA;
		r[24] >>= 1;
		r[24] = sub_1DC(r[24]);
		Y[7] = addr_100[addr_100_index + r[24]] ^ resultHASH[ADDR_AD2_INDEX + 2];

		//AD5에서 값 생성
		r[24] = ((addr_AE4[addr_AE4_index] & 0x50) >> 4) & 0x0f;
		r[24] = sub_1DC(r[24]);
		r[3] = addr_100[addr_100_index + r[24]] ^ resultHASH[ADDR_AD2_INDEX + 3];
		

		//AD6에서 값 생성
		r[24] = ((addr_AE4[addr_AE4_index] & 0xA0) >> 4) & 0x0f;
		r[24] >>= 1;
		r[24] &= 0x7;
		r[24] = sub_1DC(r[24]);
		Y[8] = addr_100[addr_100_index + r[24]] ^ resultHASH[ADDR_AD2_INDEX + 4];
		

		//AD7에서 값 생성
		r[24] = (addr_AE4[addr_AE4_index] & 0x05);
		r[24] = sub_1DC(r[24]);
		Y[5] = addr_100[addr_100_index + r[24]] ^ resultHASH[ADDR_AD2_INDEX + 5];

		//AD8에서 값 생성
		r[24] = (addr_AE4[addr_AE4_index] & 0x0A) >> 1;
		r[24] = sub_1DC(r[24]);
		Y[4] = addr_100[addr_100_index + r[24]] ^ resultHASH[ADDR_AD2_INDEX + 6];

		//AD9에서 값 생성
		r[24] = ((addr_AE4[addr_AE4_index] & 0x50) >> 4) & 0x0f;
		r[24] = sub_1DC(r[24]);
		Y[0xB] = addr_100[addr_100_index + r[24]] ^ resultHASH[ADDR_AD2_INDEX + 7];
		

		//ADA에서 값 생성
		r[24] = ((addr_AE4[addr_AE4_index--] & 0xA0) >> 4) & 0x0f;
		r[24] >>= 1;
		r[24] &= 0x7;
		r[24] = sub_1DC(r[24]);
		Y[0x3] = addr_100[addr_100_index + r[24]] ^ resultHASH[ADDR_AD2_INDEX + 8];
		 

		//ADB는 위의 첫번째 루틴과 마찬가지로 구할 수 없으므로 제거

		r[18] = Y[0xB];
		r[19] = Y[8];
		r[20] = Y[7];
		r[21] = Y[6];

		resultHASH[ADDR_AD2_INDEX + 1] = r[19];
		resultHASH[ADDR_AD2_INDEX + 2] = r[18];
		resultHASH[ADDR_AD2_INDEX + 3] = r[3];
		resultHASH[ADDR_AD2_INDEX + 4] = r[21];
		resultHASH[ADDR_AD2_INDEX + 7] = r[20];
		resultHASH[ADDR_AD2_INDEX + 5] = Y[5];
		resultHASH[ADDR_AD2_INDEX + 6] = Y[4];
		resultHASH[ADDR_AD2_INDEX + 8] = Y[3];

		counter--;

		for (int i = 0; i < 10; i++)
		{
			printf("%02x ", (unsigned)resultHASH[i]);
		}
		printf("\n");
	} while (counter != 0xFF);

	for (int i = 1; i < 9; i++)
	{
		printf("%c ", (unsigned)resultHASH[i]);
	}
	printf("\n");
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
	switch (r24)
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