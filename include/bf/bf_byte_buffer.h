
typedef struct bf_byte_buffer_tag bf_byte_buffer;

void bf_check_byte_buffer(mc_manager *mg, bf_byte_buffer *buf);

bf_byte_buffer *bf_new_byte_buffer(mc_manager *mg);

bf_byte_buffer *bf_clone_byte_buffer(mc_manager *mg, bf_byte_buffer *buf);

mc_bool bf_byte_buffer_is_empty(mc_manager *mg, bf_byte_buffer *buf);

mc_size bf_count_bytes(mc_manager *mg, bf_byte_buffer *buf);

mc_byte bf_get_byte(mc_manager *mg, bf_byte_buffer *buf, mc_size i);

mc_size bf_find_byte(mc_manager *mg, bf_byte_buffer *buf, mc_byte c);

void bf_add_byte(mc_manager *mg, bf_byte_buffer *buf, mc_byte c);

void bf_remove_byte(mc_manager *mg, bf_byte_buffer *buf, mc_size i);

bf_byte_buffer *bf_sub_byte_buffer(mc_manager *mg,
                                   bf_byte_buffer *buf,
                                   mc_size i,
                                   mc_size len);

void bf_add_bytes_from_array(mc_manager *mg,
                             bf_byte_buffer *buf,
                             int n,
                             unsigned char *array);

void bf_copy_bytes_to_array(mc_manager *mg,
                            bf_byte_buffer *buf,
                            int n,
                            unsigned char *array);
