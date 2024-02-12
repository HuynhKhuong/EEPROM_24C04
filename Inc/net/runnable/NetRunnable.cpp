#include "NetRunnable.hpp"
#include "ComReceive.hpp"

namespace NetCom
{

#ifdef DEBUG_SESSION
void printout(void)
{
  NetRunnable& runnable{NetRunnable::getSingletonEntity()};

  uint8_t byteDummyContainer{0U};
  uint8_t blockDummyContainer{0U};

  InterfaceDataType byteState{InterfaceDataType::rbNet_DataInit};
  InterfaceDataType blockState{InterfaceDataType::rbNet_DataInit};

  byteState = runnable.byteDataRequestMemChunk.getOperationModeSignalValue(byteDummyContainer);
  blockState = runnable.blockDataRequestMemChunk.getOperationModeSignalValue(blockDummyContainer);


  if(byteState == InterfaceDataType::rbNet_DataInit)
  {
    std::cout << "dataInit" << std::endl;
  }
  else if(byteState == InterfaceDataType::rbNet_DataNotAvailable)
  {
    std::cout << "datanotavailable" << std::endl;
  }
}
#endif

void NetRunnable::rxCustomerHook(void) //project specific as this function handle messages list specialized on each project
{
  //
  if(byteDataRequestMemChunk.isNewMessageReceived())
  {
    uint8_t dataSignalIDByteMessage{0U};
    uint32_t addressSignalValue{0U};
    uint8_t operatorModeSignalIDByteMessage{0U};

    netComReceiveSignal(g_DataSignalIDByteMessage, static_cast<void*>(&dataSignalIDByteMessage));
    netComReceiveSignal(g_AddressSignalIDByteMessage, static_cast<void*>(&addressSignalValue));
    netComReceiveSignal(g_OperatorModeSignalIDByteMessage, static_cast<void*>(&operatorModeSignalIDByteMessage));
    
    byteDataRequestMemChunk.setByteDataSignalValue(dataSignalIDByteMessage);  
    byteDataRequestMemChunk.setAddressSignalValue(addressSignalValue);
    byteDataRequestMemChunk.setOperationModeSignalValue(operatorModeSignalIDByteMessage);
  }

  if(blockDataRequestMemChunk.isNewMessageReceived())
  {
    uint8_t dataSignalIDBlockMessage[256U]{0U};
    uint32_t addressSignalValue{0U};
    uint8_t operatorModeSignalIDBlockMessage{0U};

    netComReceiveSignal(g_DataSignalIDBlockMessage, static_cast<void*>(&dataSignalIDBlockMessage));
    netComReceiveSignal(g_AddressSignalIDBlockMessage, static_cast<void*>(&addressSignalValue));
    netComReceiveSignal(g_OperatorModeSignalIDBlockMessage, static_cast<void*>(&operatorModeSignalIDBlockMessage));
    
    blockDataRequestMemChunk.setBlockDataSignalValue(dataSignalIDBlockMessage);  
    blockDataRequestMemChunk.setAddressSignalValue(addressSignalValue);
    blockDataRequestMemChunk.setOperationModeSignalValue(operatorModeSignalIDBlockMessage);
  }
}

void NetRunnable::txCustomerHook(void) //project specific as this function handle messages list specialized on each project
{

}

void NetRunnable::deliver(ByteDataRequest& byteDataReceiverPtr, BlockDataRequest& blockDataReceiverPtr) 
{
  ///perform shallow copy only pointer-type members are not used
  byteDataReceiverPtr = byteDataRequestMemChunk.deliver();
  blockDataReceiverPtr = blockDataRequestMemChunk.deliver();
}

}//End of namespace NetCom

