#ifndef ABSTRACTSERVICE__H
#define ABSTRACTSERVICE__H

#include "HttpStatus.h"
#include "ServiceException.h"

/// class AbstractService - 
class AbstractService {
  // Attributes
protected:
  string pattern;
  // Operations
public:
  AbstractService (const std::string& pattern);
  virtual ~AbstractService ();
  const std::string& getPattern () const;
  void setPattern (const string& pattern);
  virtual HttpStatus get (Json::Value& out, int id) const;
  virtual HttpStatus post (const Json::Value& in, int id);
  virtual HttpStatus put (Json::Value& out, const Json::Value& in);
  virtual HttpStatus remove (int id);
};

#endif
