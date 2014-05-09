#ifndef ZMQSOCKET_H
#define ZMQSOCKET_H

#include <wx/string.h>
#include "ZMQContext.h"
#include "ZMQException.h"
#include "ZMQMessage.h"
#include <zmq.h>

class ZMQC_EXPORT ZMQSocket
{
protected:
    void*    m_socket;
    wxString m_address;

public:
    enum SocketType {
        Request = ZMQ_REQ,
        Reply   = ZMQ_REP,
    };

    static void ReleaseMemoryBuffer(void* data, void* hint);
    static void ReleaseString(void* data, void* hint);

private:
    // Since we are managing here a raw pointer, don't allow copying this object
    ZMQSocket& operator=(const ZMQSocket& src);
    ZMQSocket(const ZMQSocket& src);

public:
    ZMQSocket( const ZMQContext &context, ZMQSocket::SocketType type );
    virtual ~ZMQSocket();

    const wxString& GetAddress() const {
        return m_address;
    }
    /**
     * @brief connect to an address. This function connects a server
     * You should call this function when using a SocketType::Request socket (i.e. a client)
     * @param address e.g. "tcp://127.0.0.1:5557"
     */
    void connect(const wxString &address) throw (ZMQException);

    /**
     * @brief bind an address. This is the server "start" function
     * You should call this function when using a SocketType::Reply socket (i.e. a server)
     * @param address e.g. "tcp://127.0.0.1:5557", note that you can use '*' as wildcard here
     */
    void bind(const wxString &address) throw (ZMQException);

    /**
     * @brief set the receive timeout for this socket
     */
    void setTimeout(int millSeconds) throw (ZMQException);

    /**
     * @brief send message on this socket
     * @param str message to send
     * @return true on success, false on timeout
     * @throw throw a ZMQException in any case of error
     */
    bool sendMessage(const wxString& str, const wxMBConv& converter = wxConvUTF8) throw (ZMQException);

    /**
     * @brief send message on this socket
     * @param buffer message to send. wxMemoryBuffer _must_ be allocated on the heap
     * @return true on success, false on timeout
     * @throw throw a ZMQException in any case of error
     */
    bool sendMessage(wxMemoryBuffer* buffer) throw (ZMQException);

    /**
     * @brief send message on this socket
     * @param msg message to send
     * @return true on success, false on timeout
     * @throw throw a ZMQException in any case of error
     */
    bool recvMessage(ZMQMessage& msg) throw (ZMQException);

};
#endif // ZMQSOCKET_H
