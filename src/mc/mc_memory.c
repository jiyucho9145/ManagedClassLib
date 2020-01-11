#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <mc/mc_messages.h>
#include <mc/mc_char.h>
#include <mc/mc_short.h>
#include <mc/mc_size.h>
#include <mc/mc_size_constant.h>
#include <mc/mc_error_code.h>
#include <mc/mc_object_ptr.h>
#include <mc/mc_check.h>
#include <mc/mc_memory.h>
#include <mc/mc_manager.h>

void *mc_alloc(mc_size c, mc_size s)
{
    mc_check_size(c);
    mc_check_size(s);
    void *p = calloc(c, s);
    mc_check_alloc(p);
    return p;
}

void mc_free(void *p)
{
    mc_check_free(p);
    free(p);
}

void mc_copy_bytes(void *from, void *to, mc_size c, mc_size s) {
    mc_check_not_null(from);
    mc_check_not_null(to);
    mc_check_size(c);
    mc_check_size(s);
    mc_check_size(c*s);
    if (from == to) {
        mc_err(MC_ERR_INVALID_ARG, MC_MSG_INVALID_ARG);
    }
    memcpy(to, from, c*s);
}
