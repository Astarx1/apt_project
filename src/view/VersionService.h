#ifndef VERSIONSERVICE__H
#define VERSIONSERVICE__H

#include "HttpStatus.h"
#include "AbstractService.h"

/// class VersionService - 
class VersionService : public AbstractService {
  // Operations
public:
  VersionService ();
  HttpStatus get (Json::Value& out, int id) const;
};

#endif
