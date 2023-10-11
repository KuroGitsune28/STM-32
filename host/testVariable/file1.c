extern int privatevar;
extern void changesystem_clock(int);
void myfunc(void){
	privatevar = 2000;
	changesystem_clock(1000000);
}
