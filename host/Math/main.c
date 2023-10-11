/*
 * main.c
 *
 *  Created on: Sep 8, 2023
 *      Author: ARYAN
 */
#include<stdio.h>
#include"math.h"
//extern int addnum(int, int);
int main(){
	printf("Addition is :%X\n",addnum(0x0FFF,0x0FFA));
	printf("sub is :%X\n",subnum(0x0FFF,0x0FFA));
	printf("div is :%fX\n",divnum(0x0FFF,0x0FAA));
	printf("mul is :%I64x",mulnum(0x0FFF,0x0FFA)); // NOTE we can use %x 2byte * 2 byte = 4byte around and int is sufficient other wise use I64x;
	printf("mul is :%I64x",mulnum(0x0FFFFFFF,0x0FFAFFFF));
}

