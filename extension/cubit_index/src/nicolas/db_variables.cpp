#include "nicolas/base_table.h"

// Define the global variables that were previously extern
__attribute__((aligned(128))) uint64_t db_timestamp = 0;
uint64_t db_number_of_rows = 0;