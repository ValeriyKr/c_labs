/* Made by ValeriyKr */

#include <string.h>

#include "image.h"


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


static uint8_t sat(uint64_t x) {
    return x < 256 ? x : 255;
}


static void sepia_c_one(struct pixel_t *p) {
    static const float c[3][3] = {
        { .393f, .769f, .189f },
        { .349f, .686f, .168f },
        { .272f, .543f, .131f }
    };
    struct pixel_t old = *p;
    p->r = sat(old.r * c[0][0] + old.g * c[0][1] + old.b * c[0][2]);
    p->g = sat(old.r * c[1][0] + old.g * c[1][1] + old.b * c[1][2]);
    p->b = sat(old.r * c[2][0] + old.g * c[2][1] + old.b * c[2][2]);
}


static void sepia_c(image_t *img) {
    size_t x, y;
    for (y = 0; y < img->height; ++y)
        for (x = 0; x < img->width; ++x)
            sepia_c_one(img->at(img, y, x));
}


image_t img_sepia(const image_t *orig) {
    size_t i, j;
    image_t img;
    img.at = img_at;
    img.at_const = img_at_const;
    img.destroy = img_destroy;
    img.height = orig->height;
    img.width = orig->width;
    img.data = (pixel_t*) malloc(sizeof(pixel_t)*img.height*img.width);
    for (i = 0; i < img.height; ++i)
        for (j = 0; j < img.width; ++j)
            *img.at(&img, i, j) = *orig->at_const(orig, i, j);
    sepia_c(&img);
    return img;
}


