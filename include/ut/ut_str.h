
typedef struct ut_str_tag ut_str;

void ut_check_str(mc_manager *mg, ut_str *s);

ut_str *ut_new_str(mc_manager *mg, bf_char_buffer *buf);

ut_str *ut_create_str(mc_manager *mg, int n, char *array);

bf_char_buffer *ut_clone_char_buffer(mc_manager *mg, ut_str *s);

void ut_copy_chars_to_array(mc_manager *mg, ut_str *s, int n, char *array);

mc_size ut_count_chars(mc_manager *mg, ut_str *s);

mc_char ut_get_char(mc_manager *mg, ut_str *s, mc_size i);

mc_size ut_find_char(mc_manager *mg, ut_str *s, mc_char c);

mc_short ut_compare_strs(mc_manager *mg, ut_str *s, ut_str *t);

ut_str *ut_cat_str(mc_manager *mg, ut_str *s, ut_str *t);

ut_str *ut_sub_str(mc_manager *mg, ut_str *s, mc_size i, mc_size c);
