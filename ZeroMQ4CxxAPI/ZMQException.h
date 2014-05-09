#ifndef ZMQEXCEPTION_H
#define ZMQEXCEPTION_H

#include <wx/string.h>
#include <zmq.h>
#include "zmq_utils.h"
#include "ZMQExports"

class ZMQC_EXPORT ZMQException
{
    wxString m_what;
public:
    ZMQException(const wxString &error);
    virtual ~ZMQException();
    
    const wxString &What() const {
        return m_what;
    }
};

#endif // ZMQEXCEPTION_H
