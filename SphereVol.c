#include <stdio.h>
#include <math.h>

int 
main(int argc, const char * argv[]) {
    double radius, vol, power;
    scanf("%lf", &radius);
    power = pow(radius, 3.0);
    vol = 3.141596 * 4 * power / 3;
    printf("radius: %.2f, power factor: %.2f, Volume: %.2f", radius, power, vol);
    return 0;
}
