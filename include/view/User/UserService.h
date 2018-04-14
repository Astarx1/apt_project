#ifndef USERSERVICE__H
#define USERSERVICE__H

#include "view/Service/HttpStatus.h"
#include "view/Service/AbstractService.h"

class UserService : public AbstractService {
public:
  UserService ();
  HttpStatus get (Json::Value& out, const std::vector<std::string>& params) const;	
  HttpStatus post (const Json::Value& in, const std::vector<std::string>& params);
  HttpStatus put (Json::Value& out, const Json::Value& in);
  HttpStatus remove (const std::vector<std::string>& params);
};

#endif
