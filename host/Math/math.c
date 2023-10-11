/*
 * math.c
 *
 *  Created on: Sep 8, 2023
 *      Author: ARYAN
 */
int addnum(int,int);
int subnum(int,int);
long long int mulnum(int,int);
float divnum(int,int);

int addnum(int a,int b){
	return a+b;
}

int subnum(int a, int b){
	return a-b;
}
long long int mulnum(int a,int b){
	return (long long int )a*b;
}
float divnum(int a, int b){
	return (float)a / b;
}
