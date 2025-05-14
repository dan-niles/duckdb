#pragma once

#include "duckdb.hpp"
#include "duckdb/function/scalar_function.hpp"
#include "duckdb/function/function_set.hpp"
#include "duckdb/main/extension_util.hpp"
#include "cubit/table.h"

namespace duckdb {

class CubitFunctionList {
public:
	static void RegisterFunctions(DatabaseInstance &instance) {
		ExtensionUtil::RegisterFunction(instance, ScalarFunction(
			"cubit_append",
			{LogicalType::INTEGER},
			LogicalType::BOOLEAN,
			cubit_append_function
		));

		// Add other functions like remove/update/etc here
	}

private:
	// UDF implementation for cubit_append
	static void cubit_append_function(DataChunk &input, ExpressionState &state, Vector &result) {
		D_ASSERT(input.ColumnCount() == 1);

		auto &row_ids = input.data[0];
		auto count = input.size();
		auto result_data = FlatVector::GetData<bool>(result);
		FlatVector::Validity(result).SetAllValid(count); // Mark all entries valid

		// Replace this with a real config if needed
		Table_config dummy_config;
		cubit::Cubit cubit_instance(&dummy_config);

		for (idx_t i = 0; i < count; i++) {
			if (FlatVector::IsNull(row_ids, i)) {
				result_data[i] = false;
				continue;
			}
			auto row_id = row_ids.GetValue(i).GetValue<int32_t>();
			bool success = cubit_instance.append(1, 1, row_id) == 0;
			result_data[i] = success;
		}
	}
};

} // namespace duckdb
