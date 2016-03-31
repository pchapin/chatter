/****************************************************************************
FILE          : TextSink.cpp
LAST REVISION : 2007-04-08
SUBJECT       : Base implementation of a TextSink servant.
PROGRAMMER    : (C) Copyright 207 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include "TextSink.h"

bool TextSink_impl::isEnabled(const Ice::Current &)
{
  return true;
}

void TextSink_impl::endOfText(const Ice::Current &)
{
  // Do nothing on purpose.
}
