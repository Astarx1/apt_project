#ifndef ABSTRACTSERVICE__H
#define ABSTRACTSERVICE__H

#include "HttpStatus.h"
#include "ServiceException.h"
#include "usual.h"

class AbstractService {
protected:
  string pattern;
public:
  AbstractService (const std::string& pattern);
  virtual ~AbstractService ();
  const std::string& getPattern () const;
  void setPattern (const string& pattern);
  virtual HttpStatus get (Json::Value& out, const std::vector<string>& params) const;
  virtual HttpStatus post (const Json::Value& in, const std::vector<string>& params);
  virtual HttpStatus put (Json::Value& out, const Json::Value& in);
  virtual HttpStatus remove (const std::vector<string>& params);
};

#endif
