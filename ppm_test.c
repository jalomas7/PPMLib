//this file generates a 500x500 white on black x
//and outputs it to X.ppm
#include "ppm.h"
#include <stdio.h>

int main(int argc, char **argv){

    PPM image = dnew_PPM(500, 500);
    RGB white = new_RGB(255,255,255);

    for(int i =0; i < 500; i++){
        image->data[i*500+i] = white; 
        image->data[(500*(500-i))+i] = white;
    }

    swrite_PPM("X.ppm", image);
    return 0;
}
