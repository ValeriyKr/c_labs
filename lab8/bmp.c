/* Made by ValeriyKr */

#include <stdlib.h>
#include <stdio.h>

#include "image.h"

#pragma pack(push, 2)
typedef struct {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmp_header_t;
#pragma pack(pop)


static size_t bmp_row_length(uint32_t width) {
    return 3*width + width % 4;
}


static pixel_t* bmp_at(image_t *this, size_t i, size_t j) {
    size_t row_length;
    if (NULL == this) return NULL;
    row_length = bmp_row_length(this->width);
    return (pixel_t*) ((char*) this->data + row_length*(this->height-i-1) + 3*j);
}


static const pixel_t* bmp_at_const(const image_t *this, size_t i, size_t j) {
    size_t row_length;
    if (NULL == this) return NULL;
    row_length = bmp_row_length(this->width);
    return (pixel_t*) ((char*) this->data + row_length*(this->height-i-1) + 3*j);
}


static void bmp_destroy(image_t *this) {
    free(this->data);
}


read_error_code_t from_bmp(FILE *in, image_t *img) {
    bmp_header_t header;
    size_t img_size;
    /*printf("%d\n", 1 != fread(&header, sizeof(bmp_header_t), 1, in));*/
    /*return READ_INVALID_HEADER;*/
    if (1 != fread(&header, sizeof(bmp_header_t), 1, in))
        return READ_INVALID_HEADER;
    img->width = header.biWidth;
    img->height = header.biHeight;
    img->at = bmp_at;
    img->at_const = bmp_at_const;
    img->destroy = bmp_destroy;
    img_size = header.biSizeImage - sizeof(bmp_header_t);
    if (!(img_size % 4)) return READ_INVALID_HEADER;
    if (NULL == (img->data = (pixel_t*) malloc(img_size)))
        return READ_ALLOC_ERROR;
    fseek(in, header.bOffBits, SEEK_SET);
    if (img_size/sizeof(pixel_t) != fread(img->data, sizeof(pixel_t), img_size/sizeof(pixel_t), in)) {
        free(img->data);
        return READ_INVALID_FILE;
    }

    return READ_OK;
}

static void bmp_fill_header(struct image_t *img,
        bmp_header_t *header) {
    uint32_t row_length = bmp_row_length(img->width);
    /* 19778
     * 60122
     * 0
     * 122
     * 108
     * 200
     * 100
     * 1
     * 24
     * 0
     * 60000
     * 2835
     * 2835
     * 0
     * 0
     */
    header->bfType          = 19778;
    header->bfileSize       = sizeof(bmp_header_t) + sizeof(pixel_t)
                              * img->height * row_length;
    header->bfReserved      = 0;
    header->bOffBits        = 54;
    header->biSize          = 40;
    header->biWidth         = img->width;
    header->biHeight        = img->height;
    header->biPlanes        = 1;
    header->biBitCount      = 24;
    header->biCompression   = 0;
    header->biSizeImage     = sizeof(pixel_t) * img->height * row_length;
    header->biXPelsPerMeter = 2835;
    header->biYPelsPerMeter = 2835;
    header->biClrUsed       = 0;
    header->biClrImportant  = 0;
}

write_error_code_t to_bmp(FILE *out, struct image_t *img) {
    bmp_header_t header;
    uint32_t i, j;
    char nul = '\0';
    bmp_fill_header(img, &header);
    fwrite(&header, sizeof(header), 1, out);
    fseek(out, sizeof(header), SEEK_SET);
    for (i = 0; i < img->height; ++i) {
        for (j = 0; j < img->width; ++j) 
            fwrite(img->at_const(img, img->height-i-1, j), 3, 1, out);
        fwrite(&nul, 1, img->width % 4, out);
    }
    return WRITE_OK;
}
