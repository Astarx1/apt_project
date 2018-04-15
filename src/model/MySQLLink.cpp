/* Null, because instance will be initialized on demand. */
#include "model/MySQLLink.h"

ConMySQL::ConMySQL () {
	initialized = false;
	try {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", MYSQL_USER, MYSQL_PWD);
        if(con->isValid())
	        initialized = true;
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
	ExecuteResult h;

	try { 
		std::cout << "MySQLLink.cpp - Executing request " << query << std::endl;
	    stmt = con->createStatement();
	    stmt->execute("USE goranking");
		h.link_result(stmt->executeQuery(query));

	  	delete stmt;
	}
	catch(std::exception& e) {
		std::cout << "Unable to perform query" + query << std::endl;
	} 

	return h;
}