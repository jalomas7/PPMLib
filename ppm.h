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
#ifndef PPM_H
#define PPM_H
 
#include <stdio.h>
typedef unsigned char uchar;
typedef struct rgb {
   uchar R,G,B;
} RGB;

typedef struct ppm {
    int width, height;
    RGB *data;
}* PPM;

RGB new_RGB(uchar R, uchar G, uchar B);

//generates a PPM object from the file fp
PPM fnew_PPM(FILE *fp);
PPM snew_PPM(const char *fn);

//generate a PPM object from scratch
PPM dnew_PPM(int w, int h);

//clears image to color
void apply_color(PPM image, RGB color);
void free_PPM(PPM image);
void fread_PPM(FILE *fp, PPM image);
void sread_PPM(const char *fn, PPM image);
void fwrite_PPM(FILE *fp, PPM image);
void swrite_PPM(const char *fn, PPM image);

#endif //PPM_H
