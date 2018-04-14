/* 
 * @file https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
 */

#include "usual.h"
#include "ignored/passwd.h"

#include "model/ExecuteResult.h"

class ConMySQL {
    public:
    	ConMySQL();
    	~ConMySQL();

    	ExecuteResult execute(std::string query);

    private:
   		bool initialized;

   		sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;
};