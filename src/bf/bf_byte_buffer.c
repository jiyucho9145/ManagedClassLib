#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <mc/mc.h>
#include <bf/bf_byte_buffer.h>
#include "bf_byte_buffer_tag.h"

void bf_check_byte_buffer(mc_manager *mg, bf_byte_buffer *buf)
{
    mc_check_manager(mg);
    if (NULL == buf) {
        mc_handle_error(mg, MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
    if (NULL == buf->content) {
        mc_handle_error(mg, MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
    if (buf->cap < MC_SIZE_CAP_MIN) {
        mc_handle_error(mg, MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
    if (buf->cap > MC_SIZE_CAP_MAX) {
        mc_handle_error(mg, MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
    if (buf->len < 0) {
        mc_handle_error(mg, MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
}

bf_byte_buffer *bf_new_byte_buffer(mc_manager *mg)
{
    mc_check_manager(mg);
    bf_byte_buffer *ret = mc_new_object(mg, sizeof(bf_byte_buffer));
    ret->content = mc_new_array(mg, MC_SIZE_CAP_MIN, sizeof(mc_byte));
    ret->cap = MC_SIZE_CAP_MIN;
    ret->len = 0;
    bf_check_byte_buffer(mg, ret);
    return ret;
}

bf_byte_buffer *bf_clone_byte_buffer(mc_manager *mg, bf_byte_buffer *buf)
{
    bf_check_byte_buffer(mg, buf);
    bf_byte_buffer *ret = mc_new_object(mg, sizeof(bf_byte_buffer));
    ret->content = mc_new_array(mg, buf->cap, sizeof(mc_byte));
    ret->cap = buf->cap;
    ret->len = buf->len;
    mc_copy_bytes(buf->content, ret->content, buf->len, sizeof(mc_byte));
    bf_check_byte_buffer(mg, ret);
    return ret;
}

mc_bool bf_byte_buffer_is_empty(mc_manager *mg, bf_byte_buffer *buf)
{
    bf_check_byte_buffer(mg, buf);
    return (0 == buf->len);
}

mc_size bf_count_bytes(mc_manager *mg, bf_byte_buffer *buf)
{
    bf_check_byte_buffer(mg, buf);
    return buf->len;
}

mc_byte bf_get_byte(mc_manager *mg, bf_byte_buffer *buf, mc_size i)
{
    bf_check_byte_buffer(mg, buf);
    mc_check_size(i);
    if (i >= buf->len) {
        mc_handle_error(mg, MC_ERR_INDEX_OUT_OF_BOUNDS, MC_MSG_INDEX_OUT_OF_BOUNDS);
    }
    return buf->content[i];
}

mc_size bf_find_byte(mc_manager *mg, bf_byte_buffer *buf, mc_byte c) {
    bf_check_byte_buffer(mg, buf);
    for (mc_size i = 0; buf->len; ++i) {
    mc_byte d = buf->content[i];
        if (c == d) {
            return i;
        }
    }
    return -1;
}

void bf_add_byte(mc_manager *mg, bf_byte_buffer *buf, mc_byte c)
{
    bf_check_byte_buffer(mg, buf);
    if (buf->len + 1 < buf->cap) {
        buf->content[buf->len] = c;
    } else {
        mc_byte *content = mc_new_array(mg, buf->cap + MC_SIZE_CAP_MIN, sizeof(mc_byte));
        mc_copy_bytes(buf->content, content, buf->len, sizeof(mc_byte));
        content[buf->len] = c;
        buf->content = content;
        buf->cap += MC_SIZE_CAP_MIN;
    }
    ++(buf->len);
    bf_check_byte_buffer(mg, buf);
}

void bf_remove_byte(mc_manager *mg, bf_byte_buffer *buf, mc_size i)
{
    bf_check_byte_buffer(mg, buf);
    mc_check_size(i);
    if (i >= buf->len) {
        mc_handle_error(mg, MC_ERR_INDEX_OUT_OF_BOUNDS, MC_MSG_INDEX_OUT_OF_BOUNDS);
    }
    if (i < buf->len - 1) {
        for (mc_size j = i; j < buf->len; ++j) {
            buf->content[j] = buf->content[j + 1];
        }
    }
    --(buf->len);
    bf_check_byte_buffer(mg, buf);
}

mc_short bf_compare_byte_buffers(mc_manager *mg,
                                 bf_byte_buffer *buf1,
                                 bf_byte_buffer *buf2)
{
    bf_check_byte_buffer(mg, buf1);
    bf_check_byte_buffer(mg, buf2);
    mc_size n = buf1->len;
    mc_size m = buf2->len;
    if (n < m) {
        return -1;
    }
    if (n > m) {
        return 1;
    }
    for (mc_size i = 0; i < n; ++i) {
        mc_byte c = buf1->content[i];
        mc_byte d = buf2->content[i];
        if (c < d) {
            return -1;
        } else if (c > d) {
            return 1;
        }
    }
    return 0;
}

bf_byte_buffer *bf_cat_byte_buffers(mc_manager *mg,
                                    bf_byte_buffer *buf1,
                                    bf_byte_buffer *buf2)
{
    bf_check_byte_buffer(mg, buf1);
    bf_check_byte_buffer(mg, buf2);
    bf_byte_buffer *ret = mc_new_object(mg, sizeof(bf_byte_buffer));
    mc_size n = buf1->len + buf2->len;
    ret->content = mc_new_array(mg, n + MC_SIZE_CAP_MIN, sizeof(mc_byte));
    ret->cap = n + MC_SIZE_CAP_MIN;
    ret->len = n;
    mc_copy_bytes(buf1->content, ret->content, buf1->len, sizeof(mc_byte));
    mc_copy_bytes(buf2->content, ret->content + buf1->len, buf2->len, sizeof(mc_byte));
    bf_check_byte_buffer(mg, ret);
    return ret;
}

bf_byte_buffer *bf_sub_byte_buffer(mc_manager *mg,
                                   bf_byte_buffer *buf,
                                   mc_size i, mc_size c)
{
    bf_check_byte_buffer(mg, buf);
    mc_check_size(i);
    mc_check_size(c);
    if (buf->len - i < c) {
        mc_handle_error(mg, MC_ERR_INDEX_OUT_OF_BOUNDS, MC_MSG_INDEX_OUT_OF_BOUNDS);
    }
    bf_byte_buffer *ret = mc_new_object(mg, sizeof(bf_byte_buffer));
    ret->content = mc_new_array(mg, c + MC_SIZE_CAP_MIN, sizeof(mc_byte));
    ret->cap = c + MC_SIZE_CAP_MIN;
    ret->len = c;
    mc_copy_bytes(buf->content + i, ret->content, c, sizeof(mc_byte));
    bf_check_byte_buffer(mg, ret);
    return ret;
}

void bf_add_bytes_from_array(mc_manager *mg,
                             bf_byte_buffer *buf,
                             int n,
                             unsigned char *array)
                             
{
    bf_check_byte_buffer(mg, buf);
    mc_check_size((mc_size)n);
    mc_check_not_null(array);
    mc_size c = (mc_size)n;
    for (mc_size i = 0; i < c; ++i) {
        bf_add_byte(mg, buf, array[i]);
    }
    bf_check_byte_buffer(mg, buf);
}

void bf_copy_bytes_to_array(mc_manager *mg,
                            bf_byte_buffer *buf,
                            int n,
                            unsigned char *array)
                            
{
    bf_check_byte_buffer(mg, buf);
    mc_check_size((mc_size)n);
    mc_check_not_null(array);
    mc_size c = (mc_size)n;
    if (c < buf->len) {
        mc_handle_error(mg, MC_ERR_INDEX_OUT_OF_BOUNDS, MC_MSG_INDEX_OUT_OF_BOUNDS);
    }
    mc_copy_bytes(buf->content, array, buf->len, sizeof(mc_byte));
}
