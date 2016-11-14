/* Made by ValeriyKr */

#include <stdio.h>

#include "image.h"

int main() {
    read_error_code_t rstatus;
    FILE *in = fopen("test.bmp", "r");
    FILE *out = fopen("result.bmp", "w");
    image_t img, img_rotated;
    if (NULL == in) {
        perror("File opening error");
        return 0;
    }
    if (READ_OK != (rstatus = from_bmp(in, &img))) {
        log_read(rstatus);
        return 0;
    }
    img.at(&img, 1, 1);

    img_rotated = img_rotate(&img);

    to_bmp(out, &img_rotated);
    img.destroy(&img); 
    img_rotated.destroy(&img_rotated);


    return 0;
}
