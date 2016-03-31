/****************************************************************************
FILE          : NameService.h
LAST REVISION : 2007-04-08
SUBJECT       : Interface to Chatter name service class.
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#ifndef NAMESERVICE_H
#define NAMESERVICE_H

#include <string>
#include <map>
#include <Ice/Ice.h>
#include "Chatter.h"

class NameService_impl : virtual public chatter::NameService {
public:
  // Register the given TextSink instance under the given name.
  std::string
  registerName(const std::string &name,
               const chatter::TextSinkPrx &instance,
               const Ice::Current &);

  // Remove the registration for a particular name.
  void
  unregisterName(const std::string &name,
                 const Ice::Current &);

  // Look up the object represented by a particular name.
  chatter::TextSinkPrx
  lookupName(const std::string &name,
             const Ice::Current &);

private:
  typedef std::map<std::string, chatter::TextSinkPrx> name_map;
  name_map the_map;
};

#endif
