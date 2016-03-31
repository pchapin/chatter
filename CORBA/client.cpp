/****************************************************************************
FILE          : client.cpp
LAST REVISION : 2004-04-13
SUBJECT       : Chatter client (simple version)
PROGRAMMER    : (C) Copyright 2004 by Peter C. Chapin

Please send comments or bug reports to

     Peter Chapin
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include <iostream>
#include <string>

#if defined(_WINDOWS)   // MICO
#include <CORBA.h>
#else                   // ORBacus
#include <OB/CORBA.h>
#endif

#include "chat.h"
#include "CosNaming.h"

using namespace Chatter;

int main(int argc, char **argv)
{
  try {
    // Initialize ORB.
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    // Get reference to NameService. This seems to throw if none defined.
    CORBA::Object_var obj1 = orb->resolve_initial_references("NameService");
    if (CORBA::is_nil(obj1)) {
      std::cout << "NameService IOR is nil! Somethign is very wrong.\n";
      return 1;
    }
    CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(obj1);

    // Look up name of the server.
    CosNaming::Name myName;
    myName.length(1);
    myName[0].id = CORBA::string_dup("pchapin");
    CORBA::Object_var obj2 = nc->resolve(myName);

    // Narrow.
    ChatServer_var cs = ChatServer::_narrow(obj2);
    if (CORBA::is_nil(cs)) {
      std::cerr << "Name is not a ChatServer reference\n";
      return 1;
    }
    cs->put_line("tester", "Hello, World!");

    // Chat!
    std::string line;
    while (1) {
      getline(std::cin, line);
      if (line == ".") break;
      cs->put_line("tester", line.c_str());
    }
  }
  catch (const CORBA::Exception &e) {
    std::cerr << "Uncaught CORBA exception: " << e << "\n";
    return 1;
  }
  catch (...) {
    std::cerr << "Uncaught exception of unknown type.\n";
    return 1;
  }

  return 0;
}
