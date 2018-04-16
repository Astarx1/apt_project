#ifndef EXECUTE_RESULT_H
#define EXECUTE_RESULT_H

#include "usual.h"

class ExecuteResult {
public:
	ExecuteResult(std::string query);
	~ExecuteResult();
	
	bool isValid();
	void link_result(sql::ResultSet *);
	sql::ResultSet * get_link_result();

private:
	std::string query;
	bool valid;
	sql::ResultSet * l;
};

#endif