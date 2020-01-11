#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
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

void mc_err(mc_error_code code, char msg[])
{
    fprintf(stderr, "%s\n", msg);
    exit((int)code);
}

void mc_check_alloc(void *p)
{
    if (NULL == p) {
        mc_err(MC_ERR_ALLOC, MC_MSG_ALLOC_ERR);
    }
}

void mc_check_free(void *p)
{
    if (NULL == p) {
        mc_err(MC_ERR_FREE, MC_MSG_FREE_ERR);
    }
}

void mc_check_size(mc_size s)
{
    if (s <= 0) {
        mc_err(MC_ERR_NULL_PTR, MC_MSG_NULL_PTR);
    }
}

void mc_check_not_null(void *p)
{
    if (NULL == p) {
        mc_err(MC_ERR_NULL_PTR, MC_MSG_NULL_PTR);
    }
}
