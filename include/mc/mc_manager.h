/* Object manager type */
typedef struct mc_manager_tag mc_manager;

/* Validates an object manager. */
void mc_check_manager(mc_manager *mg);

/* Allocates an object manager. */
mc_manager *mc_alloc_manager(void);

/* Frees an object manager. */
void mc_free_manager(mc_manager *mg);

/* Creates an object. */
mc_object_ptr mc_new_object(mc_manager *mg, mc_size s);

/* Creates an array. */
mc_object_ptr mc_new_array(mc_manager *mg, mc_size c, mc_size s);

/* Converts a pointer of an object into a reference of it.*/
mc_size mc_get_reference(mc_manager *mg, void *p);

/* Converts a reference of an object into a pointer of it. */
void *mc_get_pointer(mc_manager *mg, mc_size i);

/* Adds an object to an object manager. */
void mc_add_object(mc_manager *mg, mc_object_ptr p);

/* Frees objects, print an error message, and exit. */
void *mc_handle_error(mc_manager *mg, mc_error_code code, char message[]);
