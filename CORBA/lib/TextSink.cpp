/****************************************************************************
FILE          : TextSink.cpp
LAST REVISION : 2004-04-29
SUBJECT       : Base implementation of a TextSink servant.
PROGRAMMER    : (C) Copyright 2004 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include "TextSink.h"

CORBA::Boolean TextSink_impl::is_enabled()
  throw(CORBA::SystemException)
{
  return true;
}

void TextSink_impl::eot()
  throw(CORBA::SystemException)
{
}

void TextSink_impl::reg(CosNaming::NamingContext_ptr nc, const char *nm)
  throw(CORBA::SystemException)
{
  if (is_registered) unreg();  // Allow reregistrations.

  CosNaming::Name name_string;

  name = nm;
  name_context = nc;
  name_string.length(1);
  name_string[0].id = name;
  name_context->bind(name_string, _this());
  is_registered = true;
}

void TextSink_impl::unreg()
  throw(CORBA::SystemException)
{
  if (!is_registered) return;

  CosNaming::Name name_string;

  name_string.length(1);
  name_string[0].id = name;
  name_context->unbind(name_string);
  is_registered = false;
}
