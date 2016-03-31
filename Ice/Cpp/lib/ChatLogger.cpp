/****************************************************************************
FILE          : ChatLogger.cpp
LAST REVISION : 2004-04-29
SUBJECT       : Implementation of a ChatLogger.
PROGRAMMER    : (C) Copyright 2004 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include <ctime>
#include <iomanip>
#include "ChatLogger.h"

void ChatLogger::putLine(
  const std::string &from,
  const std::string &line,
  const Ice::Current &)
{
  // Get the current time.
  std::time_t raw = std::time(NULL);
  std::tm *cooked = std::localtime(&raw);

  if (os) {
    os.fill('0');
    os << std::setw(4) << cooked->tm_year + 1900 << "-"
       << std::setw(2) << cooked->tm_mon + 1 << "-"
       << std::setw(2) << cooked->tm_mday    << " "
       << std::setw(2) << cooked->tm_hour    << ":"
       << std::setw(2) << cooked->tm_min     << ":"
       << std::setw(2) << cooked->tm_sec     << " ";
    os.fill(' ');
    os << "[" << std::setw(8) << from << "] " << line << "\n";
  }
}

bool ChatLogger::isEnabled(const Ice::Current &)
{
  if (!os) return false;
  return true;
}

