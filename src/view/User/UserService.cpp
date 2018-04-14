#include "view/User/UserService.hpp"
#include "usual.h"

UserService::UserService () : AbstractService("/player") {}

HttpStatus UserService::get (Json::Value& out, const std::vector<std::string>& params) const {
	if (params[0] != "") {
		return HttpStatus::OK;
	}
	else if (params[1] != "") {
		return HttpStatus::OK;
	}
	return HttpStatus::NOT_FOUND;
}

HttpStatus UserService::post (const Json::Value& in, const std::vector<std::string>& params) {
	std::cout << "User Service POST !" << std::endl;
    return HttpStatus::OK;
}

HttpStatus UserService::put (Json::Value& out, const Json::Value& in) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
}

HttpStatus UserService::remove (const std::vector<std::string>& params) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Non implanté");
}

