#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

typedef unsigned char *byte_pointer;
typedef unsigned int uint32_t;

void show_bytes(byte_pointer start, int len)
{
	int i;
	for(i=0; i<len; i++)
	{
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

void show_int(int x)
{
	show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) 
{
	show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x)
{
	show_bytes((byte_pointer)&x, sizeof(void *));
}

void test_show_bytes(int val)
{
	int ival = val;
	float fval = (float)ival;
	int *pval = &ival;
	show_int(ival);
	show_float(fval);
	show_pointer(pval);
}

void test_show_hex(int val)
{
	byte_pointer valp = (byte_pointer)&val;
	show_bytes(valp,1);
	show_bytes(valp,2);
	show_bytes(valp,3);
}

int main(void)
{
	test_show_bytes(12345);
	
	test_show_hex(0x87654321);
	
	// show big-endian;
	printf("********** big-endian **********\n");
	uint32_t num = htonl(12345);	
	test_show_bytes(num);
	printf("********** 0x87654321 **********\n");
	num =  htonl(0x87654321);	
	//test_show_bytes(num);
	test_show_hex(num);
	
	printf("********** 3510593 **********\n");
	show_int(3510593);
	printf("********** 3510593.0 **********\n");
	show_float(3510593.0);
	
	char* str = "12345";
	show_pointer(str);
	
	printf("********** abcdef **********\n");
	const char *s = "abcdef";
	show_bytes((byte_pointer)s, strlen(s));
		
	return 0;
}