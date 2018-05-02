/* Null, because instance will be initialized on demand. */
#include "model/MySQLLink.h"

ConMySQL::ConMySQL (std::string url) {
	initialized = false;
	try {
        driver = get_driver_instance();
        con = driver->connect(url.c_str(), MYSQL_USER, MYSQL_PWD);

	    /*sql::Statement* stmt = con->createStatement();
	    std::string query = "CREATE DATABASE IF NOT EXISTS goranking";
		std::cout << "MySQLLink.cpp - Executing request : " << query << std::endl;
		stmt->executeUpdate(query);
		std::cout << "MySQLLink.cpp - Request linked, deleting statemement" << std::endl;
	  	delete stmt;*/

        std::cout << "Setting db" << std::endl;
        con->setSchema("goranking");
        if(con->isValid()) {
	        initialized = true;
		    std::cout << "MySQLLink.cpp - Database connected" << std::endl;
        }
	    else {
	    	std::cout << "Error when connecting, bad url " << url << std::endl;
	    	throw std::exception();
	    }

	    /*stmt = con->createStatement();
	    query = "CREATE TABLE IF NOT EXISTS GAMES(id_game INT PRIMARY KEY NOT NULL AUTO_INCREMENT, id_player_1 INT NOT NULL, level_player_1 FLOAT NOT NULL, id_player_2 INT NOT NULL, level_player_2 FLOAT NOT NULL, date_game INT NOT NULL, moves TEXT)";
		std::cout << "MySQLLink.cpp - Executing request : " << query << std::endl;
		stmt->executeUpdate(query);
		std::cout << "MySQLLink.cpp - Request linked, deleting statemement" << std::endl;
	  	delete stmt;

	    stmt = con->createStatement();
	    query = "CREATE TABLE IF NOT EXISTS GAMESINFOS(id_info INT PRIMARY KEY NOT NULL AUTO_INCREMENT, id_game INT NOT NULL, type_info INT NOT NULL, value_info TEXT)";
		std::cout << "MySQLLink.cpp - Executing request : " << query << std::endl;
		stmt->executeUpdate(query);
		std::cout << "MySQLLink.cpp - Request linked, deleting statemement" << std::endl;
	  	delete stmt;

	    stmt = con->createStatement();
	    query = "CREATE TABLE IF NOT EXISTS PLAYERS(id_player INT PRIMARY KEY NOT NULL AUTO_INCREMENT, current_level FLOAT NOT NULL, trivia_player TEXT)";
		std::cout << "MySQLLink.cpp - Executing request : " << query << std::endl;
		stmt->executeUpdate(query);
		std::cout << "MySQLLink.cpp - Request linked, deleting statemement" << std::endl;
	  	delete stmt;

	    stmt = con->createStatement();
	    query = "CREATE TABLE IF NOT EXISTS PLAYERSINFOS(id_info INT PRIMARY KEY NOT NULL AUTO_INCREMENT, id_player INT NOT NULL, type_info INT NOT NULL, value_info TEXT);";
		std::cout << "MySQLLink.cpp - Executing request : " << query << std::endl;
		stmt->executeUpdate(query);
		std::cout << "MySQLLink.cpp - Request linked, deleting statemement" << std::endl;
	  	delete stmt;*/

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