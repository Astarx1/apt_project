#ifndef USERSERVICE__H
#define USERSERVICE__H

#include "HttpStatus.h"
#include "AbstractService.h"
#include "UserDB.h"

/// class UserService - 
class UserService : public AbstractService {
  // Associations
  // Attributes
protected:
  UserDB& userDB;
  // Operations
public:
  UserService (UserDB& userDB);
  HttpStatus get (Json::Value& out, int id) const;
  HttpStatus post (const Json::Value& in, int id);
  HttpStatus put (Json::Value& out, const Json::Value& in);
  HttpStatus remove (int id);
};

#endif
