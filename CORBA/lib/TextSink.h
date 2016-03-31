/****************************************************************************
FILE          : TextSink.h
LAST REVISION : 2004-04-20
SUBJECT       : Interface to base implementation of a TextSink servant.
PROGRAMMER    : (C) Copyright 2004 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#ifndef TEXTSINK_H
#define TEXTSINK_H

#if defined(_WINDOWS)  // MICO
#include <CORBA.h>
#include "chatter.h"
#else                  // ORBacus
#include <OB/CORBA.h>
#include "chatter_skel.h"
#endif

#include "CosNaming.h"

class TextSink_impl : public virtual POA_Chatter::TextSink {
 public:
  TextSink_impl() : is_registered(false) { }

  virtual CORBA::Boolean is_enabled()
    throw(CORBA::SystemException);

  virtual void put_line(const char *from, const char *line)
    throw(CORBA::SystemException) = 0;

  virtual void eot()
    throw(CORBA::SystemException);

  virtual void reg(CosNaming::NamingContext_ptr nc, const char *nm)
    throw(CORBA::SystemException);

  virtual void unreg()
    throw(CORBA::SystemException);

 protected:
  CosNaming::NamingContext_var name_context;
  CORBA::String_var name;
  bool is_registered;
};

#endif
