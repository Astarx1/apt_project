#include "view/Service/ServicesManager.hpp"

using namespace std;

void ServicesManager::registerService (unique_ptr<AbstractService> service) {
	services.push_back(std::move(service));
}

AbstractService* ServicesManager::findService (const string& url) const {
	std::string part;
	int i = 1;

	while (url[i] != '/' && i < url.size()) ++i;
	part = url.substr(0, i);
	std::cout << "ServiceManager.cpp - for " << part << std::endl;
	
	for (int i = 0; i < services.size(); ++i) {
		if (services[i]->getPattern() == part) {
			std::cout << "ServiceManager.cpp : We found a service" << std::endl;
			return services[i].get(); 
		}
	}

	/*
	if (part == "/version") {
		if (url == "/version")
			return (services[0]).get();
		else if (url == "/version/suite")
			return (services[0]).get();
		else if (url == "/version/23")
			return (services[0]).get();
		else 
			throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Gestion version non implanté");
	}
	else {
		
	}*/
	throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
}

HttpStatus ServicesManager::queryService (string& out, const string& in, const string& url, const string& method, const vector<string>& params) { 
	Json::Value jsonObj;
    HttpStatus r;

    AbstractService* as = findService(url);
    std::string part;
	int i = 1;
	while (url[i] != '/' && i < url.size()) ++i;
	if (i < url.size() - 1) part = url.substr(i, url.size() - i);
    i = 0;
    if (part.size() > 0) i = atoi(part.c_str());
     
    if (method == "GET") {
    	r = as->get(jsonObj, params);
    	out = jsonObj.toStyledString();
    }
    if (method == "POST") {
		Json::Reader reader;
    	reader.parse(in.c_str(), jsonObj);
    	r = as->post(jsonObj, params);
    	out = std::string("ok");
    }
    if (method == "PUT") {
    	r = as->put(jsonObj, jsonObj);
    }
    if (method == "REMOVE") {
    	r = as->remove(params);
    }

    return r;
}


