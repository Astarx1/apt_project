#include "model/ExecuteResult.h"

ExecuteResult::ExecuteResult() : valid(false) {}
ExecuteResult::~ExecuteResult() {
	delete l;
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
