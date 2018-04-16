#ifndef MYSQLLINK_H
#define MYSQLLINK_H

#include "usual.h"
#include "ignored/passwd.h"

#include "model/ExecuteResult.h"

class ConMySQL {
    public:
    	ConMySQL();
    	~ConMySQL();

    	ExecuteResult execute(std::string query);
		void update (std::string query);

    private:
   		bool initialized;

   		sql::Driver* driver;
        sql::Connection* con;
        sql::ResultSet* res;
};

#endif