#include <wx/string.h>
#include "ZMQSocket.h"
#include "ZMQException.h"

#define ZMQ_ERR_STR() wxString(zmq_strerror(zmq_errno()), wxConvUTF8)

ZMQSocket::ZMQSocket(const ZMQContext& context, ZMQSocket::SocketType type)
    : m_socket(NULL)
{
    m_socket = zmq_socket(context.getContext(), (int) type );
}

ZMQSocket::~ZMQSocket()
{
    if ( m_socket ) {
        zmq_close(m_socket);
    }
    m_socket = NULL;
}

void ZMQSocket::bind(const wxString& address) throw (ZMQException)
{
    if ( !m_socket ) {
        throw ZMQException(wxString() << wxT("Bind error: ") << address << wxT(". NULL socket"));
    }
    
    wxCharBuffer cb = address.mb_str(wxConvUTF8);
    int rc = zmq_bind(m_socket, cb.data());
    if ( rc == -1 ) {
        throw ZMQException( wxString() << wxT("Bind error: ") << ZMQ_ERR_STR());
    }
    m_address = address;
}

void ZMQSocket::connect(const wxString& address) throw (ZMQException)
{
    if ( !m_socket ) {
        throw ZMQException(wxString() << wxT("Connect error. NULL socket") );
    }
    
    wxCharBuffer cb = address.mb_str(wxConvUTF8).data();
    int rc = zmq_connect(m_socket, cb.data());
    if ( rc == -1 ) {
        throw ZMQException(wxString() << wxT("Connect error. ") << ZMQ_ERR_STR() );
    }
    m_address = address;
}

void ZMQSocket::setTimeout(int millSeconds) throw (ZMQException)
{
    if ( !m_socket ) {
        throw ZMQException(wxString() << wxT("setTimeout error: ") << wxT(". NULL socket"));
    }
    
    int timeout = millSeconds;
    int rc = zmq_setsockopt(m_socket, ZMQ_RCVTIMEO, &timeout, sizeof(timeout));
    if ( rc == -1 ) {
        throw ZMQException(wxString() << wxT("setTimeout error: ") << ZMQ_ERR_STR() );
    }
}

bool ZMQSocket::recvMessage(ZMQMessage& msg) throw (ZMQException)
{
    if ( !m_socket ) {
        throw ZMQException(wxString() << wxT("recvMessage error: ") << wxT(". NULL socket"));
    }
    
    msg.clear();
    int rc = zmq_msg_recv( &msg.m_zmqmsg, m_socket, 0);
    int err_code = zmq_errno();
    if ( rc == -1 && (err_code == EAGAIN || err_code == EINTR) ) {
        return false;
        
    } else if ( rc == -1 ) {
        throw ZMQException(wxString() << wxT("zmq_msg_recv: error: ") << ZMQ_ERR_STR() );
    }
    return true;
}

bool ZMQSocket::sendMessage(wxMemoryBuffer* buffer) throw (ZMQException)
{
    if ( !m_socket ) {
        throw ZMQException(wxString(wxT("ZMQSocket::sendMessage: could not send message. NULL socket")));
    }
    
    if ( !buffer ) {
        wxDELETE( buffer );
        return false;
    }
    
    zmq_msg_t msg;
    zmq_msg_init( &msg );
    zmq_msg_init_data(&msg, buffer->GetData(), buffer->GetDataLen(), &ZMQSocket::ReleaseMemoryBuffer, buffer);
    int rc = zmq_msg_send(&msg, m_socket, 0);
    if ( rc == -1 ) {
        throw ZMQException(wxString() << wxT("zmq_msg_send: error: ") << ZMQ_ERR_STR() );

    } else if ( rc == 0 ) {
        // timeout
        return false;
    }
    return true;
}

bool ZMQSocket::sendMessage(const wxString& str, const wxMBConv& converter) throw (ZMQException)
{
    if ( !m_socket ) {
        throw ZMQException(wxString(wxT("ZMQSocket::sendMessage: could not send message. NULL socket")));
    }
    
    if ( str.IsEmpty() ) {
        return false;
    }
    
    zmq_msg_t msg;
    zmq_msg_init( &msg );
    
    wxCharBuffer cb = str.mb_str(converter);
    size_t bufLen = ::strlen( cb.data() );
    char* pdata = new char[ bufLen + 1 ];
    memcpy(pdata, cb.data(), bufLen);
    pdata[bufLen] = 0;

    // we send it along the NULL terminating char
    zmq_msg_init_data(&msg, pdata, bufLen+1, &ZMQSocket::ReleaseString, NULL);
    
    int rc = zmq_msg_send(&msg, m_socket, 0);
    if ( rc == -1 ) {
        throw ZMQException(wxString() << wxT("zmq_msg_send: error: ") << ZMQ_ERR_STR() );

    } else if ( rc == 0 ) {
        // timeout
        return false;
    }
    return true;
}

void ZMQSocket::ReleaseMemoryBuffer(void* data, void* hint)
{
    wxUnusedVar( data );
    wxMemoryBuffer* buffer = reinterpret_cast<wxMemoryBuffer*>( hint );
    wxDELETE( buffer );
}

void ZMQSocket::ReleaseString(void* data, void* hint)
{
    wxUnusedVar(hint);
    char* p = (char*)data;
    wxDELETEA( p );
}
