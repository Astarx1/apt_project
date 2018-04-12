#ifndef USERDB__H
#define USERDB__H

#include "User.h"

/// class UserDB - 
class UserDB {
  // Associations
  // Attributes
protected:
  int idseq;
  map<int,unique_ptr<User> > users;
  // Operations
public:
  UserDB ();
  const User* getUser (int id) const;
  int addUser (unique_ptr<User> user);
  void setUser (int id, unique_ptr<User> user);
  void removeUser (int id);
};

#endif
