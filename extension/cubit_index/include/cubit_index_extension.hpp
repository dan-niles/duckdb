//===----------------------------------------------------------------------===//
//                         DuckDB
//
// cubit_index_extension.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb.hpp"

namespace duckdb {

class CubitIndexExtension : public Extension {
public:
    void Load(DuckDB &db) override;
    std::string Name() override;
    std::string Version() const override;
};

} // namespace duckdb
