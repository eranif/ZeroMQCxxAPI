#ifndef ZMQMESSAGE_H
#define ZMQMESSAGE_H

#include <wx/string.h>
#include <wx/buffer.h>
#include <zmq.h>
#include "ZMQExports"

class ZMQSocket;
class ZMQC_EXPORT ZMQMessage
{
    friend class ZMQSocket;

private:
    zmq_msg_t m_zmqmsg;
    
private:
    ZMQMessage(const ZMQMessage& src);
    ZMQMessage& operator=(const ZMQMessage& src);
    
public:
    ZMQMessage();
    virtual ~ZMQMessage();
    
    void* data() const;
    void* data();
    
    size_t length() const;
    void clear();
    
    /**
     * @brief 
     * @param converter
     * @return 
     */
    wxString GetString(const wxMBConv& converter = wxConvUTF8) const;
    /**
     * @brief 
     * @return 
     */
    wxMemoryBuffer GetBuffer() const;
};

#endif // ZMQMESSAGE_H
