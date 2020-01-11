#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <mc/mc.h>
#include <bf/bf.h>
#include <ut/ut.h>

static ut_str *create_str(mc_manager *mg, char buf[])
{
    size_t n = strlen(buf);
    return ut_create_str(mg, n, buf);
}

int main(int argc, char *argv[])
{
    mc_manager *mg = mc_alloc_manager();
    ut_str *s = create_str(mg, "Hello world.");
    char array[256] = {0};
    ut_copy_chars_to_array(mg, s, sizeof(array), array);
    fprintf(stdout, "%s\n", array);
    mc_free_manager(mg);
    return 0;
}
