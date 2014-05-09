#include <cstdio>
#include "ZMQSocket.h"
#include "ZMQContext.h"

// +++-----------------------
// Server test
// +++-----------------------

int main(int argc, char **argv)
{
    if ( argc < 2 ) {
        printf("usage: %s <bind string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    try {
        wxString connectAddress(argv[1], wxConvUTF8);
        ZMQContext context;
        ZMQSocket s(context, ZMQSocket::Reply); // Server socket type
        s.bind( connectAddress );

        // wait for messages
        s.setTimeout( 1000 );
        
        while ( true ) {
            ZMQMessage incMessage;
            if ( s.recvMessage( incMessage ) ) {
                wxPrintf(wxT("Received message: %s\n"), incMessage.GetString().c_str());
                
                // Message received!
                // process it
                wxString reply( incMessage.GetString() );
                reply << wxT(" - a reply!");
                s.sendMessage( reply );
                
            }
        }

    } catch (ZMQException &e) {
        wxPrintf(wxT("error: %s\n"), e.What().c_str());
    }
    return 0;
}
