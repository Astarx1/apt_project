#include "model/ExecuteResult.h"

ExecuteResult::ExecuteResult(std::string query) : valid(false), query(query) {}

ExecuteResult::~ExecuteResult() {
	std::cout << "ExecuteResult.cpp - Erasing the result from " << query << std::endl;
	delete l;
	std::cout << "ExecuteResult.cpp - Result erased" << std::endl;
}

void ExecuteResult::link_result(sql::ResultSet * res) {
	l = res;
}

sql::ResultSet * ExecuteResult::get_link_result() {
	return l;
}
