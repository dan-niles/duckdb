#define DUCKDB_EXTENSION_MAIN
#include "cubit_index_extension.hpp"
#include "duckdb/main/extension_util.hpp"
#include "cubit_index_function_list.hpp"

namespace duckdb {

void LoadInternalCubit(DuckDB &db) {
    CubitFunctionList::RegisterFunctions(*db.instance);
}

void CubitIndexExtension::Load(DuckDB &db) {
    LoadInternalCubit(db);
}

std::string CubitIndexExtension::Name() {
    return "cubit_index";
}

std::string CubitIndexExtension::Version() const {
    return "1.0";  // You can modify this with the actual version
}

} // namespace duckdb

extern "C" {

DUCKDB_EXTENSION_API void cubit_index_init(duckdb::DatabaseInstance &db) {
    duckdb::DuckDB db_wrapper(db);
    duckdb::CubitIndexExtension extension;
    extension.Load(db_wrapper);
}

DUCKDB_EXTENSION_API const char *cubit_index_version() {
    return "1.0";
}
}

#ifndef DUCKDB_EXTENSION_MAIN
#error DUCKDB_EXTENSION_MAIN not defined
#endif
