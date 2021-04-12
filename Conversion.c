#include <stdio.h>

int 
main(int argc, const char * argv[]) {
    double tempc, tempf, temp;
	char unit;
	printf("Enter Temperature for Conversion: ");
	scanf("%lf%c", &temp, &unit);
	
	if (unit == 'C' || unit == 'c') {
		tempc = temp;
		tempf = (tempc * 9.0/5) + 32 ;
		printf ("Temp is %.2fF", tempf);
	} else if (unit == 'F' | unit == 'f') {
		tempf = temp;
		tempc = (tempf - 32)*(5.0/9);
		printf ("Temp is %.2fC", tempc);
	}
	
    return 0;
}