#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <mc/mc.h>
#include <bf/bf.h>
#include <ut/ut_str.h>
#include "ut_str_tag.h"

void ut_check_str(mc_manager *mg, ut_str *s)
{
    mc_check_manager(mg);
    if (NULL == s) {
        mc_handle_error(mg, MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
    bf_check_char_buffer(mg, s->buf);
}

ut_str *ut_new_str(mc_manager *mg, bf_char_buffer *buf)
{
    bf_check_char_buffer(mg, buf);
    ut_str *ret = mc_new_object(mg, sizeof(ut_str));
    ret->buf = bf_clone_char_buffer(mg, buf);
    ut_check_str(mg, ret);
    return ret;
}

ut_str *ut_create_str(mc_manager *mg, int n, char *array)
{
    mc_check_manager(mg);
    mc_check_size((mc_size)n);
    mc_check_not_null(array);
    bf_char_buffer *buf = bf_new_char_buffer(mg);
    bf_add_chars_from_array(mg, buf, n, array);
    return ut_new_str(mg, buf);
}

bf_char_buffer *ut_clone_char_buffer(mc_manager *mg, ut_str *s)
{
    ut_check_str(mg, s);
    return bf_clone_char_buffer(mg, s->buf);
}

void ut_copy_chars_to_array(mc_manager *mg, ut_str *s, int n, char *array)
{
    ut_check_str(mg, s);
    mc_check_size((mc_size)n);
    mc_check_not_null(array);
    bf_copy_chars_to_array(mg, s->buf, n, array);
}

mc_size ut_count_chars(mc_manager *mg, ut_str *s)
{
    ut_check_str(mg, s);
    return bf_count_chars(mg, s->buf);
}

mc_char ut_get_char(mc_manager *mg, ut_str *s, mc_size i)
{
    ut_check_str(mg, s);
    mc_check_size(i);
    return bf_get_char(mg, s->buf, i);
}

mc_size ut_find_char(mc_manager *mg, ut_str *s, mc_char c)
{
    ut_check_str(mg, s);
    return bf_find_char(mg, s->buf, c);
}

mc_short ut_compare_strs(mc_manager *mg, ut_str *s, ut_str *t)
{
    ut_check_str(mg, s);
    ut_check_str(mg, t);
    return bf_compare_char_buffers(mg, s->buf, t->buf);
}

ut_str *ut_cat_strs(mc_manager *mg, ut_str *s, ut_str *t)
{
    ut_check_str(mg, s);
    ut_check_str(mg, t);
    bf_char_buffer *buf = bf_cat_char_buffers(mg, s->buf, t->buf);
    return ut_new_str(mg, buf);
}

ut_str *ut_sub_str(mc_manager *mg, ut_str *s, mc_size i, mc_size c)
{
    ut_check_str(mg, s);
    mc_check_size(i);
    mc_check_size(c);
    bf_char_buffer *buf = bf_sub_char_buffer(mg, s->buf, i, c);
    return ut_new_str(mg, buf);
}
