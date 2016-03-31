/****************************************************************************
FILE          : NameService.cpp
LAST REVISION : 2007-04-08
SUBJECT       : Implementation of the name service class.
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include <algorithm>
#include <cctype>
using namespace std;

#include "NameService.h"


// The following function returns true if the given character is acceptable for nicknames. Note
// that some special characters are allowed, but other special characters are not (reserved for
// other purposes).
//
static bool allowed_char(char ch)
{
  static const char allowed[] = " '!?-_";
  static const int  allowed_size  = sizeof(allowed)/sizeof(char);

  if (isalnum(ch)) return true;
  if (find(allowed, allowed + allowed_size, ch) != allowed + allowed_size)
    return true;

  return false;
}


string NameService_impl::registerName(
  const string &name,
  const chatter::TextSinkPrx &instance,
  const Ice::Current &)
{
  string clean;
  string::const_iterator sp;

  // Scan down the given name and copy only the "good" characters to clean.
  for (sp = name.begin(); sp != name.end(); ++sp) {
    if (allowed_char(*sp)) clean += *sp;
  }

  // If there is nothing left, return without actually registering the name. We might want to
  // enforce additional rules such as requiring that a nickname contain at least one letter,
  // does not contain two special characters in a row, does not contain trailing spaces, etc,
  // etc.
  //
  if (clean.length() == 0) throw chatter::BadNameException();

  // Allow a new object with the same name to just overwrite an existing entry. Clearly this is
  // not acceptable in the long run. Only the owner of a name should be able to overwrite that
  // name. This requires introducing the notion of "name owner" and then using some security
  // mechanism to authenticate registration requests.
  //
  the_map[clean] = instance;
  return clean;
}


void NameService_impl::unregisterName(
  const string &name,
  const Ice::Current &)
{
  // Clearly only the owner of a name should be allowed to unregister it.
  name_map::iterator p = the_map.find(name);
  if (p != the_map.end()) {
    the_map.erase(p);
  }
}


chatter::TextSinkPrx NameService_impl::lookupName(
  const string &name,
  const Ice::Current &)
{
  // We might eventually want to restrict access to certain names so that the name owner can
  // prevent her names from being looked up by certain people.

  name_map::iterator p = the_map.find(name);
  if (p == the_map.end()) {
    return chatter::TextSinkPrx();
  }
  return p->second;
}
