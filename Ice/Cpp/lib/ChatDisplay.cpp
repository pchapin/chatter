/****************************************************************************
FILE          : ChatDisplay.cpp
LAST REVISION : 2006-04-09
SUBJECT       : Implementation of a ChatDisplay.
PROGRAMMER    : (C) Copyright 2006 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include <iostream>
#include <iomanip>
#include "ChatDisplay.h"

void ChatDisplay::putLine(
  const std::string &from,
  const std::string &line,
  const Ice::Current &)
{
  std::cout << std::setw(10) << from << ": " << line << "\n";
}

bool ChatDisplay::isEnabled(const Ice::Current &)
{
  return true;
}
