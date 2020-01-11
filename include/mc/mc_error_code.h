/* Error codes */
typedef enum mc_error_code_tag {
    MC_ERR_ALLOC = 1,
    MC_ERR_FREE = 2,
    MC_ERR_NULL_PTR = 3,
    MC_ERR_INVALID_SIZE = 4,
    MC_ERR_INVALID_OBJ = 5,
    MC_ERR_INVALID_ARG = 6,
    MC_ERR_INVALID_REF = 7,
    MC_ERR_INDEX_OUT_OF_BOUNDS = 8
} mc_error_code;
