
typedef struct bf_char_buffer_tag bf_char_buffer;

void bf_check_char_buffer(mc_manager *mg, bf_char_buffer *buf);

bf_char_buffer *bf_new_char_buffer(mc_manager *mg);

bf_char_buffer *bf_clone_char_buffer(mc_manager *mg, bf_char_buffer *buf);

mc_bool bf_char_buffer_is_empty(mc_manager *mg, bf_char_buffer *buf);

mc_size bf_count_chars(mc_manager *mg, bf_char_buffer *buf);

mc_char bf_get_char(mc_manager *mg, bf_char_buffer *buf, mc_size i);

mc_size bf_find_char(mc_manager *mg, bf_char_buffer *buf, mc_char c);

void bf_add_char(mc_manager *mg, bf_char_buffer *buf, mc_char c);

void bf_remove_char(mc_manager *mg, bf_char_buffer *buf, mc_size i);

mc_short bf_compare_char_buffers(mc_manager *mg,
                                 bf_char_buffer *buf1,
                                 bf_char_buffer *buf2);

bf_char_buffer *bf_cat_char_buffers(mc_manager *mg,
                                    bf_char_buffer *buf1,
                                    bf_char_buffer *buf2);

bf_char_buffer *bf_sub_char_buffer(mc_manager *mg,
                                   bf_char_buffer *buf,
                                   mc_size i,
                                   mc_size len);

void bf_add_chars_from_array(mc_manager *mg,
                             bf_char_buffer *buf,
                             int n,
                             char *array);

void bf_copy_chars_to_array(mc_manager *mg,
                            bf_char_buffer *buf,
                            int n,
                            char *array);
