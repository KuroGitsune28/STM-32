/*
 * test.c
 *
 *  Created on: Sep 6, 2023
 *      Author: ARYAN
 */

#include<stdio.h>

//static int privatevar; // TO prevent access from file1 we need to static it so it will be private to main.c.
int privatevar;
void myfunc(void);

int main(){

	char a1 = 'A';
	char a2 = '@';

	printf("a1 = %p\n",&a1);
	printf("a2 = %p\n",&a2);

	privatevar = 100;
	printf("the value of variable is %d\n",privatevar);
	myfunc();
	printf("the value of variable is %d\n",privatevar);
	return 0;
}

void changesystem_clock(int clock){
	printf("System clock changed to : %d\n",clock);
}
