/* Made by ValeriyKr */

#include <string.h>

#include "image.h"


struct image_t rotate(const struct image_t source);

void log_read(read_error_code_t err) {
    switch (err) {
    case READ_OK:
        fputs("Read successful", stderr);
        break;
    case READ_INVALID_HEADER:
        fputs("Invalid image header", stderr);
        break;
    default:
        fputs("Unknown reading error", stderr);
    }
}


void log_write(write_error_code_t err) {
    switch (err) {
    case WRITE_OK:
        fputs("Written successful", stderr);
        break;
    default:
        fputs("Unknown reading error", stderr);
    }
}


static pixel_t* img_at(image_t *img, size_t i, size_t j) {
    return img->data + img->width*i + j;
}


static const pixel_t* img_at_const(const image_t *img, size_t i, size_t j) {
    return img->data + img->width*i + j;
}


static void img_destroy(image_t *img) {
    free(img->data);
}


image_t img_rotate(const image_t *orig) {
    size_t i, j;
    image_t img;
    img.at = img_at;
    img.at_const = img_at_const;
    img.destroy = img_destroy;
    img.height = orig->width;
    img.width = orig->height;
    img.data = (pixel_t*) malloc(sizeof(pixel_t)*img.height*img.width);
    for (i = 0; i < img.height; ++i)
        for (j = 0; j < img.width; ++j)
            *img.at(&img, img.height-i-1, j) = *orig->at_const(orig, j, i);
    return img;
}
