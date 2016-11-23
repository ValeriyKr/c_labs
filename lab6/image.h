/* Made by ValeriyKr */

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#pragma pack(push, 1)
typedef struct pixel_t {
    uint8_t b;
    uint8_t g;
    uint8_t r;
} pixel_t;
#pragma pack(pop)


/* height and width of image in pixels.
 * Access to data by .at() and .at_const()
 * from_*() must put .at() and .at_const() functions into this fields
 * When work is done, destroying image must be accompanied .destroy() call.
 */
typedef struct image_t {
    uint32_t width;
    uint32_t height;
    struct pixel_t *data;
    pixel_t* (*at)(struct image_t *this, size_t i, size_t j);
    const pixel_t* (*at_const)(const struct image_t *this, size_t i, size_t j);
    void (*destroy)(struct image_t *this);
} image_t;


typedef enum {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER,
    READ_INVALID_FILE,
    READ_ALLOC_ERROR
} read_error_code_t;

typedef enum {
    WRITE_OK = 0,
    WRITE_ERROR
} write_error_code_t;

read_error_code_t from_bmp(FILE *in, image_t *img);
image_t img_rotate(const image_t *source);
write_error_code_t to_bmp(FILE *out, image_t *img);

void log_read(read_error_code_t err);
void log_write(write_error_code_t err);

#endif /* _IMAGE_H_ */
