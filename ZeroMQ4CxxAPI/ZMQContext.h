#ifndef ZMQCONTEXT_H
#define ZMQCONTEXT_H

#include "ZMQExports"

class ZMQC_EXPORT ZMQContext
{
    void* m_context;
public:
    ZMQContext();
    virtual ~ZMQContext();
    
    void* getContext() const {
        return m_context;
    }
};

#endif // ZMQCONTEXT_H
