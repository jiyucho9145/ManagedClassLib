/* Prints an error message and exit. */
void mc_err(mc_error_code code, char msg[]);

/* Validate an allocated array. */
void mc_check_alloc(void *p);

/* Validate a freed array. */
void mc_check_free(void *p);

/* Validate a size value. */
void mc_check_size(mc_size s);

/* Validate a pointer. */
void mc_check_not_null(void *p);
