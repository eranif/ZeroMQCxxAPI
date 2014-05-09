#include "ZMQMessage.h"

ZMQMessage::ZMQMessage()
{
    zmq_msg_init(&m_zmqmsg);
}

ZMQMessage::~ZMQMessage()
{
    zmq_msg_close(&m_zmqmsg);
}

void* ZMQMessage::data()
{
    return zmq_msg_data(&m_zmqmsg);
}

void* ZMQMessage::data() const
{
    return zmq_msg_data(const_cast<zmq_msg_t*>(&m_zmqmsg));
}

size_t ZMQMessage::length() const
{
    return zmq_msg_size( const_cast<zmq_msg_t*>(&m_zmqmsg) );
}

void ZMQMessage::clear()
{
    zmq_msg_close(&m_zmqmsg);
    zmq_msg_init(&m_zmqmsg);
}

wxMemoryBuffer ZMQMessage::GetBuffer() const
{
    wxMemoryBuffer buffer;
    buffer.AppendData(data(), length());
    return buffer;
}

wxString ZMQMessage::GetString(const wxMBConv& converter) const
{
    wxString str((char*)data(), converter);
    return str;
}
