/* Made by ValeriyKr */

#include <stdio.h>

#include "image.h"


void rotate_test(const char *name_in, const char *name_out) {
    read_error_code_t rstatus;
    write_error_code_t wstatus;
    FILE *in = fopen(name_in, "r");
    FILE *out = fopen(name_out, "w");
    image_t img, img_rotated;
    if (NULL == in) {
        perror("File opening error");
        return;
    }
    if (READ_OK != (rstatus = from_bmp(in, &img))) {
        log_read(rstatus);
        return;
    }

    img_rotated = img_rotate(&img);

    if (WRITE_OK != (wstatus = to_bmp(out, &img_rotated))) {
        log_write(wstatus);
    }
    img.destroy(&img); 
    img_rotated.destroy(&img_rotated);
    fclose(in);
    fclose(out);
}


int main() {
    rotate_test("test.bmp", "result.bmp");
    rotate_test("test2.bmp", "result2.bmp");

    return 0;
}
