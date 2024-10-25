#include "cbuffer.h"
bool flag = false;
void cb_init(cbuffer_t *cb, void *buf, uint32_t size)
{
    // if (size > CB_MAX_SIZE) {
    //     size = CB_MAX_SIZE;
    // }
    cb->data = (uint8_t *)buf;
    cb->size = size;
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
    cb->active = true;
}

void cb_clear(cbuffer_t *cb)
{
    cb->writer = 0;
    cb->reader = 0;
    cb->overflow = 0;
}

uint32_t cb_data_count(cbuffer_t *cb)
{
    if (cb->writer >= cb->reader)
    {
        return cb->writer - cb->reader;
    }
    else
    {
        return cb->size - cb->reader + cb->writer;
    }
}

uint32_t cb_space_count(cbuffer_t *cb)
{
    if (cb->reader == 0 && cb->writer == 0)
        return cb->size - 1;
    else if (cb->reader == cb->writer)
        return cb->size - cb->reader - 1;
    else
        return cb->size - cb->writer - 1;
}
uint32_t cb_read(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
    if (!cb->active)
        return 0;

    uint8_t *p = (uint8_t *)buf;
    uint32_t data_count = cb_data_count(cb);
    uint32_t to_read = nbytes;

    for (uint32_t i = 0; i < to_read; i++)
    {
        p[i] = cb->data[cb->reader];
        cb->reader = (cb->reader + 1) % cb->size;
        printf("read %d\n", cb->reader);
    }

    return to_read;
}

uint32_t cb_write(cbuffer_t *cb, void *buf, uint32_t nbytes)
{
    if (!cb->active)
        return 0;
    flag = false;
    uint8_t *p = (uint8_t *)buf;
    uint32_t space_count = cb_space_count(cb);
    uint32_t to_write = nbytes;
    printf("to_write: %d\n", to_write);
    for (uint32_t i = 0; i < to_write; i++)
    {
        printf("write %u\n", cb->writer);
        cb->data[cb->writer] = p[i];
        cb->writer = (cb->writer + 1) % (cb->size); // 0
        if (flag == true)
        {
            cb->overflow++;
        }
        if (cb->writer % (cb->size - 1) == 0)
        {
            flag = true;
            cb->writer = 0;
        }
        printf("write update %d\n", cb->writer);
        printf("overflow %d\n", cb->overflow);
    }
    // flag = false;

    return to_write;
}
