/* PPMLib is a ppm image reading and writing library written in C
 * Copyright (C) 2017  Jacob Massengill
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ppm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

RGB new_RGB(uchar R, uchar G, uchar B){
    RGB rgb;
    rgb.R = R; rgb.G = G; rgb.B = B;
    return rgb;
}

//creates a new PPM object from fp, assumes 
//only the P6 file format of maxsize 255
//TODO: support for raw type and maxsize > 255
PPM PPM_fnew(FILE *fp){ 
    int width, height, maxsize;
    char type[2];
    PPM image;

    fscanf(fp, "%s\n%d %d\n%d\n", type,  &width, &height, &maxsize);

    if(strcmp(type, "P6") != 0){
        fputs("not a PPM file\n", stderr);
        image = NULL;
        return image;
    }

    image = malloc(sizeof(struct ppm));
    image->width = width;
    image->height = height;
    image->data = malloc(width*height*sizeof(struct rgb));

    if(fread(image->data, sizeof(struct rgb), width*height, fp) != width*height){
        fputs("could not read PPM file\n", stderr);
        image = NULL;
    }

    return image;
}

PPM PPM_snew(const char *fn){
    FILE *fp;
    if((fp = fopen(fn, "r"))==NULL) return NULL;
    PPM image = PPM_fnew(fp);
    fclose(fp); return image;
}

PPM PPM_dnew(int w, int h){
    PPM image = malloc(sizeof(struct ppm));
    image->width = w;
    image->height = h;
    image->data = malloc(w*h*3*sizeof(char));
    RGB black = new_RGB(0,0,0);

    //initialize to black
    for(int i=0; i < w*h; i++){
        image->data[i].R = black.R; 
    }
    return image;
}

void PPM_free(PPM image){
    if(!image) return;
    if(image->data){
        free(image->data);
    }
    free(image);
}

void PPM_fread(FILE *fp, PPM image){
    PPM_free(image);
    image = PPM_fnew(fp);
}

void PPM_sread(const char *fn, PPM image){
    PPM_free(image);
    image = PPM_snew(fn);
}

//write image to fp, assumes fp is good
void PPM_fwrite(FILE *fp, PPM image){
   fprintf(fp, "P6\n%d %d\n255\n", image->width, image->height);
   fwrite(image->data, sizeof(RGB), image->width*image->height, fp);
}

void PPM_swrite(const char *fn, PPM image){
    FILE *fp;
    if((fp=fopen(fn, "w"))==NULL) return;
    PPM_fwrite(fp, image);
    fclose(fp);
}

void PPM_apply_color(PPM image, RGB color){
    for(int i=0; i < image->width*image->height; i++){
        image->data[i] = color;
    }
}
