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
#include "mc_manager_tag.h"

static void free_all_objects(mc_manager *mg)
{
    for (mc_size i = 0; i < mg->cap; ++i) {
	void *p = (void*)(mg->pool[i]);
	if (NULL != p) {
            mc_free(p);
	}
    }
    if (NULL != mg->pool) {
        mc_free(mg->pool);
    }
    if (NULL != mg) {
        mc_free(mg);
    }
}

void mc_check_manager(mc_manager *mg) {
    if (NULL == mg) {
        mc_err(MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
    if (NULL == mg->pool) {
        free_all_objects(mg);
        mc_err(MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
    if (mg->cap < MC_SIZE_CAP_MIN) {
        free_all_objects(mg);
        mc_err(MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
    if (mg->cap > MC_SIZE_CAP_MAX) {
        free_all_objects(mg);
        mc_err(MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
    if (mg->len < 0) {
        free_all_objects(mg);
        mc_err(MC_ERR_INVALID_OBJ, MC_MSG_INVALID_OBJ);
    }
}

mc_manager *mc_alloc_manager(void) {
    mc_manager *ret = mc_alloc(1, sizeof(mc_manager));
    mc_object_ptr *pool = mc_alloc(MC_SIZE_CAP_MIN, sizeof(mc_object_ptr));
    ret->cap = MC_SIZE_CAP_MIN;
    ret->len = 0;
    ret->pool = pool;
    mc_check_manager(ret);
    return ret;
}

void mc_free_manager(mc_manager *mg) {
    mc_check_manager(mg);
    free_all_objects(mg);
}

void mc_add_object(mc_manager *mg, mc_object_ptr p) {
    mc_check_manager(mg);
    mc_check_not_null(p);
    if (mg->len + 1 < mg->cap) {
        mg->pool[mg->len] = p;
    } else {
        mc_object_ptr *pool = mc_alloc(mg->cap + MC_SIZE_CAP_MIN, sizeof(mc_object_ptr));
        mc_copy_bytes(mg->pool, pool, mg->len, sizeof(mc_object_ptr));
        pool[mg->len] = p;
        mc_free(mg->pool);
        mg->pool = pool;
        mg->cap += MC_SIZE_CAP_MIN;
    }
    ++(mg->len);
    mc_check_manager(mg);
}

mc_object_ptr mc_new_object(mc_manager *mg, mc_size s)
{
    mc_check_manager(mg);
    mc_check_size(s);
    mc_object_ptr ret = (mc_object_ptr)mc_alloc(1, s);
    mc_add_object(mg, ret);
    return ret;
}

mc_object_ptr mc_new_array(mc_manager *mg, mc_size c, mc_size s)
{
    mc_check_manager(mg);
    mc_check_size(c);
    mc_check_size(s);
    mc_object_ptr ret = (mc_object_ptr)mc_alloc(c, s);
    mc_add_object(mg, ret);
    return ret;
}

mc_size mc_get_reference(mc_manager *mg, void *p)
{
    mc_check_manager(mg);
    for (mc_size i = 0; i < mg->cap; ++i) {
	void *q = mg->pool[i];
	if (p == q) {
           return i;
	}
    }
    return -1;
}

void *mc_get_pointer(mc_manager *mg, mc_size ref)
{
    mc_check_manager(mg);
    mc_check_size(ref);
    if (ref > mg->len - 1) {
        free_all_objects(mg);
        mc_err(MC_ERR_INVALID_REF, MC_MSG_INVALID_REF);
    }
    return mg->pool[ref];
}

void *mc_handle_error(mc_manager *mg, mc_error_code code, char message[])
{
    mc_free_manager(mg);
    mc_err(code, message);
}
