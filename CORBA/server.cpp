/****************************************************************************
FILE          : server.cpp
LAST REVISION : 2004-04-15
SUBJECT       : Chatter server (simple version)
PROGRAMMER    : (C) Copyright 2004 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Vermont Technical College
     Randolph Center, VT 05061
     pchapin@ecet.vtc.edu
****************************************************************************/

#include <iostream>

#if defined(_WINDOWS)  // MICO
#include <CORBA.h>
#include "chat.h"
#else                  // ORBacus
#include <OB/CORBA.h>
#include "chat_skel.h"
#endif

#include "CosNaming.h"

using namespace Chatter;

// Derive a servant class from the IDL generated skeleton class.
//
class ChatServer_impl : public virtual POA_Chatter::ChatServer {
  public:
    virtual void put_line(const char *from, const char *line)
      throw(CORBA::SystemException);

    virtual CORBA::Boolean is_enabled()
      throw(CORBA::SystemException);

    virtual void send_file(FileServer_ptr fs, const CORBA::Octet *key)
      throw(CORBA::SystemException);
};

// Implement the operations required.
//
void ChatServer_impl::put_line(const char *from, const char *line)
  throw(CORBA::SystemException)
{
  std::cout << "(" << from << ") " << line << "\n";
}

CORBA::Boolean ChatServer_impl::is_enabled()
  throw(CORBA::SystemException)
{
  return true;
}

void ChatServer_impl::send_file(FileServer_ptr fs, const CORBA::Octet *key)
  throw(CORBA::SystemException)
{
  std::cout << "NOTE: send_file request ignored.\n";
}


//
// Main Program
//
//   1. Initialize an ORB.
//   2. Create a servant object.
//   3. Publish the servant's object reference.
//
int main(int argc, char **argv)
{
  try {
    // Initialize ORB
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    // Get reference to root POA.
    CORBA::Object_var obj1 = orb->resolve_initial_references("RootPOA");
    if (CORBA::is_nil(obj1)) {
      std::cout << "RootPOA IOR is nil! Something is very wrong.\n";
      return 1;
    }
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj1);

    // Get reference to NameService. This seems to throw if none defined.
    CORBA::Object_var obj2 = orb->resolve_initial_references("NameService");
    if (CORBA::is_nil(obj2)) {
      std::cout << "NameService IOR is nil! Something is very wrong.\n";
      return 1;
    }
    CosNaming::NamingContext_var nc = CosNaming::NamingContext::_narrow(obj2);

    // Activate POA manager.
    PortableServer::POAManager_var mgr = poa->the_POAManager();
    mgr->activate();

    // Create a servant object.
    ChatServer_impl chat_servant;

    // Register the servant's IOR with the naming service.
    ChatServer_var cs = chat_servant._this();
    CosNaming::Name myName;
    myName.length(1);
    myName[0].id = CORBA::string_dup("pchapin");
    nc->bind(myName, cs);

    // Accept requests.
    orb->run();
  }
  catch (const CORBA::Exception &e) {
    std::cerr << "Unhandled CORBA exception: " << e << "\n";
    return 1;
  }
  catch (...) {
    std::cerr << "Uncaught exception of unknown type.\n";
    return 1;
  }
  
  return 0;
}
