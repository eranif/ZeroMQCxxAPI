#include <cstdio>
#include "ZMQSocket.h"

// +++-----------------------
// Client test
// +++-----------------------

int main(int argc, char **argv)
{

    try {

        ZMQContext context;
        ZMQSocket s(context, ZMQSocket::Request); // Client socket type
        
        // Note about multiple servers:
        // When connecting to more than one server
        // the send will start only when _all_ servers are up and connected
        // also note that ZMQ will perform a round robin between the servers
        // so if we have N servers and the client sends X number of messages
        // it means that each server will process X/N messages
        s.connect(wxT("tcp://127.0.0.1:1363"));
        //s.connect("tcp://127.0.0.1:1364");
        
        // s.setTimeout( -1 );
        for ( size_t i=0; i<10000; ++i ) {
            wxString msg;
            msg << i << wxT(" : Hello world from client");
            s.sendMessage( msg );
            
            ZMQMessage mqmsg;
            s.recvMessage( mqmsg );
            wxPrintf(wxT("%04d: Received reply: %s\n"), (int)i, mqmsg.GetString().c_str());
        }

    } catch (ZMQException &e) {
        wxPrintf(wxT("error: %s\n"), e.What().c_str());
    }
    return 0;
}
