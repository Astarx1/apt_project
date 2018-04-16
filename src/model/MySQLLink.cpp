/* Null, because instance will be initialized on demand. */
#include "model/MySQLLink.h"

ConMySQL::ConMySQL () {
	initialized = false;
	try {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", MYSQL_USER, MYSQL_PWD);
        con->setSchema("goranking");
        if(con->isValid()) {
	        initialized = true;
		    std::cout << "MySQLLink.cpp - Database connected" << std::endl;
        }
	    else
	    	throw std::exception();

	    std::cout << "MySQL connection : " << initialized << std::endl;
	}
	catch(std::exception& e) {
		std::cout << "Unable to connect to MySQL" << std::endl;
	}
}

ConMySQL::~ConMySQL () {
	delete con;
}

ExecuteResult ConMySQL::execute (std::string query) {
	ExecuteResult h(query);

	try { 
	    std::cout << "MySQLLink.cpp - Creating Query statement" << std::endl;
	    sql::Statement* stmt = con->createStatement();
		std::cout << "MySQLLink.cpp - Executing request : " << query << std::endl;
		sql::ResultSet * rs = stmt->executeQuery(query);
		std::cout << "MySQLLink.cpp - Request executed : " << query << ", linking result" << std::endl;
		h.link_result(rs);
		std::cout << "MySQLLink.cpp - Request linked, deleting statemement" << std::endl;
	  	delete stmt;
	}
	catch(std::exception& e) {
		std::cout << "Unable to perform query : " + query << std::endl;
		std::cout << e.what() << std::endl;
	} 

	return h;
}

void ConMySQL::update (std::string query) {
	try { 
	    std::cout << "MySQLLink.cpp - Creating Query statement" << std::endl;
	    sql::Statement* stmt = con->createStatement();
		std::cout << "MySQLLink.cpp - Executing request : " << query << std::endl;
		stmt->executeUpdate(query);
		std::cout << "MySQLLink.cpp - Request linked, deleting statemement" << std::endl;
	  	delete stmt;
	}
	catch(std::exception& e) {
		std::cout << "Unable to perform query : " + query << std::endl;
		std::cout << e.what() << std::endl;
	} 	
}