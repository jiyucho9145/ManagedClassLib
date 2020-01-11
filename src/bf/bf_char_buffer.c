#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <mc/mc.h>
#include <bf/bf_char_buffer.h>
#include "bf_char_buffer_tag.h"

void bf_check_char_buffer(mc_manager *mg, bf_char_buffer *buf)
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

bf_char_buffer *bf_new_char_buffer(mc_manager *mg)
{
    mc_check_manager(mg);
    bf_char_buffer *ret = mc_new_object(mg, sizeof(bf_char_buffer));
    ret->content = mc_new_array(mg, MC_SIZE_CAP_MIN, sizeof(mc_char));
    ret->cap = MC_SIZE_CAP_MIN;
    ret->len = 0;
    bf_check_char_buffer(mg, ret);
    return ret;
}

bf_char_buffer *bf_clone_char_buffer(mc_manager *mg, bf_char_buffer *buf)
{
    bf_check_char_buffer(mg, buf);
    bf_char_buffer *ret = mc_new_object(mg, sizeof(bf_char_buffer));
    ret->content = mc_new_array(mg, buf->cap, sizeof(mc_char));
    ret->cap = buf->cap;
    ret->len = buf->len;
    mc_copy_bytes(buf->content, ret->content, buf->len, sizeof(mc_char));
    bf_check_char_buffer(mg, ret);
    return ret;
}

mc_bool bf_char_buffer_is_empty(mc_manager *mg, bf_char_buffer *buf)
{
    bf_check_char_buffer(mg, buf);
    return (0 == buf->len);
}

mc_size bf_count_chars(mc_manager *mg, bf_char_buffer *buf)
{
    bf_check_char_buffer(mg, buf);
    return buf->len;
}

mc_char bf_get_char(mc_manager *mg, bf_char_buffer *buf, mc_size i)
{
    bf_check_char_buffer(mg, buf);
    mc_check_size(i);
    if (i >= buf->len) {
        mc_handle_error(mg, MC_ERR_INDEX_OUT_OF_BOUNDS, MC_MSG_INDEX_OUT_OF_BOUNDS);
    }
    return buf->content[i];
}

mc_size bf_find_char(mc_manager *mg, bf_char_buffer *buf, mc_char c) {
    bf_check_char_buffer(mg, buf);
    for (mc_size i = 0; buf->len; ++i) {
    mc_char d = buf->content[i];
        if (c == d) {
            return i;
        }
    }
    return -1;
}

void bf_add_char(mc_manager *mg, bf_char_buffer *buf, mc_char c)
{
    bf_check_char_buffer(mg, buf);
    if (buf->len + 1 < buf->cap) {
        buf->content[buf->len] = c;
    } else {
        mc_char *content = mc_new_array(mg, buf->cap + MC_SIZE_CAP_MIN, sizeof(mc_char));
        mc_copy_bytes(buf->content, content, buf->len, sizeof(mc_char));
        content[buf->len] = c;
        buf->content = content;
        buf->cap += MC_SIZE_CAP_MIN;
    }
    ++(buf->len);
    bf_check_char_buffer(mg, buf);
}

void bf_remove_char(mc_manager *mg, bf_char_buffer *buf, mc_size i)
{
    bf_check_char_buffer(mg, buf);
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
    bf_check_char_buffer(mg, buf);
}

mc_short bf_compare_char_buffers(mc_manager *mg,
                                 bf_char_buffer *buf1,
                                 bf_char_buffer *buf2)
{
    bf_check_char_buffer(mg, buf1);
    bf_check_char_buffer(mg, buf2);
    mc_size n = buf1->len;
    mc_size m = buf2->len;
    if (n < m) {
        return -1;
    }
    if (n > m) {
        return 1;
    }
    for (mc_size i = 0; i < n; ++i) {
        mc_char c = buf1->content[i];
        mc_char d = buf2->content[i];
        if (c < d) {
            return -1;
        } else if (c > d) {
            return 1;
        }
    }
    return 0;
}

bf_char_buffer *bf_cat_char_buffers(mc_manager *mg,
                                    bf_char_buffer *buf1,
                                    bf_char_buffer *buf2)
{
    bf_check_char_buffer(mg, buf1);
    bf_check_char_buffer(mg, buf2);
    bf_char_buffer *ret = mc_new_object(mg, sizeof(bf_char_buffer));
    mc_size n = buf1->len + buf2->len;
    ret->content = mc_new_array(mg, n + MC_SIZE_CAP_MIN, sizeof(mc_char));
    ret->cap = n + MC_SIZE_CAP_MIN;
    ret->len = n;
    mc_copy_bytes(buf1->content, ret->content, buf1->len, sizeof(mc_char));
    mc_copy_bytes(buf2->content, ret->content + buf1->len, buf2->len, sizeof(mc_char));
    bf_check_char_buffer(mg, ret);
    return ret;
}

bf_char_buffer *bf_sub_char_buffer(mc_manager *mg,
                                   bf_char_buffer *buf,
                                   mc_size i, mc_size c)
{
    bf_check_char_buffer(mg, buf);
    mc_check_size(i);
    mc_check_size(c);
    if (buf->len - i < c) {
        mc_handle_error(mg, MC_ERR_INDEX_OUT_OF_BOUNDS, MC_MSG_INDEX_OUT_OF_BOUNDS);
    }
    bf_char_buffer *ret = mc_new_object(mg, sizeof(bf_char_buffer));
    ret->content = mc_new_array(mg, c + MC_SIZE_CAP_MIN, sizeof(mc_char));
    ret->cap = c + MC_SIZE_CAP_MIN;
    ret->len = c;
    mc_copy_bytes(buf->content + i, ret->content, c, sizeof(mc_char));
    bf_check_char_buffer(mg, ret);
    return ret;
}

void bf_add_chars_from_array(mc_manager *mg,
                             bf_char_buffer *buf,
                             int n,
                             char *array)
                             
{
    bf_check_char_buffer(mg, buf);
    mc_check_size((mc_size)n);
    mc_check_not_null(array);
    mc_size c = (mc_size)n;
    for (mc_size i = 0; i < c; ++i) {
        bf_add_char(mg, buf, array[i]);
    }
    bf_check_char_buffer(mg, buf);
}

void bf_copy_chars_to_array(mc_manager *mg,
                            bf_char_buffer *buf,
                            int n,
                            char *array)
                            
{
    bf_check_char_buffer(mg, buf);
    mc_check_size((mc_size)n);
    mc_check_not_null(array);
    mc_size c = (mc_size)n;
    if (c < buf->len) {
        mc_handle_error(mg, MC_ERR_INDEX_OUT_OF_BOUNDS, MC_MSG_INDEX_OUT_OF_BOUNDS);
    }
    mc_copy_bytes(buf->content, array, buf->len, sizeof(mc_char));
}
