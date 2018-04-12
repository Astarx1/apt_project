#ifndef SERVICESMANAGER__H
#define SERVICESMANAGER__H

#include "HttpStatus.h"
#include "AbstractService.h"

/// class ServicesManager - 
class ServicesManager {
  // Associations
  // Attributes
protected:
  vector<unique_ptr<AbstractService> > services;
  // Operations
public:
  void registerService (unique_ptr<AbstractService> service);
  AbstractService* findService (const string& url) const;
  HttpStatus queryService (string& out, const string& in, const string& url, const string& method);
};

#endif
