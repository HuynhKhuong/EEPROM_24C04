#ifndef NETRUNNABLE_HPP_INCLUDED
#define NETRUNNABLE_HPP_INCLUDED

#include "Interface.hpp"

/// \brief NetRunnable is a runnable class that controls MCU's communication (Tx and Rx)
/// \details  NetRunnable handles signals from event-based incoming message, setting up the Interface and 
///           deliver to functional components.
///           NetRunnable receives request from functional components and prepare signals value, process signals value and 
///           transfer them to lower infrastructure.
/// \note     NetRunnable is intended to be the interface of lower infrastructure, to be accessed from functional components.
///           As lower infrastructure is unique and exists only 1 entity inside the system, there exists only 1 instance of  
///           NetRunnable. Therefore, Singleton design pattern is taken in used
namespace rbNetCOM
{
class NetRunnable
{
public: 

#ifdef DEBUG_SESSION
  friend void printout(void);
#endif 

  static NetRunnable& getSingletonEntity()
  {
    static NetRunnable singletonEntity;
    return singletonEntity;
  }

  void run(void)
  {
    rxCustomerHook(); //handle incoming message first 
    txCustomerHook(); //handle transmitting message later
  }
  
  // Entry point for other user to get data
  void deliver(ByteDataRequest& byteDataReceiverPtr, BlockDataRequest& blockDataReceiverPtr);

private: 
  // singleton would not allow an explicit instance creation 
  NetRunnable() = default;

  // Avoid copy attempts
  NetRunnable(const NetRunnable& obj) = default;
  const NetRunnable& operator=(const NetRunnable& obj) = delete;

  void rxCustomerHook(void);
  void txCustomerHook(void);

  ByteDataRequest   byteDataRequestMemChunk{g_messageConfigureTable[g_byteMessageIndex]};
  BlockDataRequest  blockDataRequestMemChunk{g_messageConfigureTable[g_blockMessageIndex]};
};
}
#endif