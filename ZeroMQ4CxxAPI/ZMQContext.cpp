#include "ZMQContext.h"
#include <stddef.h>
#include "zmq.h"

ZMQContext::ZMQContext()
    : m_context(NULL)
{
    m_context = zmq_ctx_new();
}

ZMQContext::~ZMQContext()
{
    zmq_term(m_context);
    zmq_ctx_destroy(m_context);
    m_context = NULL;
}
