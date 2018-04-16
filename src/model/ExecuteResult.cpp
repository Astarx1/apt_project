#include "model/ExecuteResult.h"

ExecuteResult::ExecuteResult() : valid(false) {}

ExecuteResult::~ExecuteResult() {
	std::cout << "ExecuteResult.cpp - Erasing the result" << std::endl;
	delete l;
	std::cout << "ExecuteResult.cpp - Result erased" << std::endl;
}

bool ExecuteResult::isValid() {
	return valid;
}

void ExecuteResult::link_result(sql::ResultSet * res) {
	if (valid)
		throw std::exception ();
	l = res;
	valid = true;
}

sql::ResultSet * ExecuteResult::get_link_result() {
	return l;
}
