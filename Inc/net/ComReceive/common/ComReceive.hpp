#ifndef COMRECEIVE_HPP_INCLUDED
#define COMRECEIVE_HPP_INCLUDED

#include "SignalListDefine.hpp"
#include "ContainerList.hpp"
#include <cstdint>

namespace rbNetCOM{

constexpr uint16_t g_maxDataLength{300U};

struct InternalDataContainer 
{
  InternalDataContainer(uint8_t *signalTypeUint8_t,
                        uint16_t *signalTypeUint16_t,
                        uint32_t *signalTypeUint32_t, 
                        float *signalTypeFloat, 
                        uint8_t *signalTypeOthers):
                        m_signalTypeUint8_t(signalTypeUint8_t),
                        m_signalTypeUint16_t(signalTypeUint16_t),
                        m_signalTypeUint32_t(signalTypeUint32_t),
                        m_signalTypeFloat(signalTypeFloat), 
                        m_signalTypeOthers(signalTypeOthers){}

  uint8_t *const m_signalTypeUint8_t;
  uint16_t *const m_signalTypeUint16_t;
  uint32_t *const m_signalTypeUint32_t;
  float *const m_signalTypeFloat;
  uint8_t *const m_signalTypeOthers;
};

/// \brief rbNetComReceive handles receiving message from master and dispatch
/// messages to signals
/// \details
/// \input dataBuffer[]: array container of data
void rbNetComReceive(uint8_t *dataBuffer);

/// \brief rbNetComDisptachSignals handles extracting signals from a message
/// buffer and save in internal data container
/// \details
/// \input MessageLayoutInterface: Layout information and local buffer to extract signal from
/// \output signals saved into internal signal container
void rbNetComDispatchSignals(MessageHandlerInterface &messageLayout);

/// \brief rbNetComReceiveSignal handles getting signal from internal container
/// and return to user
/// \details
/// \input signalID: ID defined in "MessageConfigure.hpp"
/// \output void* ptr: user pointer to be stored with latest signal value
void rbNetComReceiveSignal(signalID ID, void *ptr);

} // End of namespace rbNetCOM

#endif
