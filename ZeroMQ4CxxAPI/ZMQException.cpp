#include "ZMQException.h"

ZMQException::ZMQException(const wxString &error)
    : m_what(error)
{
}

ZMQException::~ZMQException()
{
}

