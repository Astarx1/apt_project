#ifndef EXECUTE_RESULT_H
#define EXECUTE_RESULT_H

#include "usual.h"

class ExecuteResult {
public:
	ExecuteResult();
	~ExecuteResult();
	
	bool isValid();
	void link_result(sql::ResultSet *);
	sql::ResultSet * get_link_result();

private:
	bool valid;
	sql::ResultSet * l;
};

#endif