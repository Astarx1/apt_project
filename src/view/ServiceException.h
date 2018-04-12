#ifndef SERVICEEXCEPTION__H
#define SERVICEEXCEPTION__H

#include "HttpStatus.h"

/// class ServiceException - 
class ServiceException : public std::exception {
  // Associations
  HttpStatus httpStatus;
  // Attributes
protected:
  string msg;
  // Operations
public:
  ServiceException (HttpStatus status, string msg);
  HttpStatus status () const;
  const char* what () const noexcept;
};

#endif
