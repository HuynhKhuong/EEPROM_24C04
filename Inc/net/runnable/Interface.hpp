#ifndef INTERFACE_HPP_INCLUDED
#define INTERFACE_HPP_INCLUDED

#include <iostream>
#include <cstdint>
#include "SignalListDefine.hpp"
/// \brief Interface defines the structure of packets which are exchanged by components
///        packets are defined depending on the layout of messages and their corresponding signals 
///        which are specific for each projects

namespace rbNetCOM
{

#ifdef DEBUG_SESSION
void printout(void);
#endif

enum class InterfaceDataType: uint8_t
{
  rbNet_DataInit = 0U,
  rbNet_DataNotAvailable = 1U,
  rbNet_DataReceived = 2U,
};

class IInterface
{
public: 
  IInterface(MessageHandlerInterface* const ptr): m_messagePtr(ptr){}

  bool isNewMessageReceived()
  {
    bool returnValue{false};

    if(m_messagePtr != nullptr)
    {
      returnValue = m_messagePtr->getNewMessageReceivedFlag();
    }

    m_messagePtr->setNewMessageReceivedFlag(false);
    return returnValue;
  }

private: 
  MessageHandlerInterface* const m_messagePtr;

};

class ByteDataRequest:public IInterface
{
public: 
  ByteDataRequest(MessageHandlerInterface* const messagePtr):IInterface(messagePtr){}

  const ByteDataRequest& operator=(const ByteDataRequest& obj)
  {
    this->addressSignalValue = obj.addressSignalValue;
    this->byteDataSignalValue = obj.byteDataSignalValue;
    this->operationModeSignalValue = obj.operationModeSignalValue;
    this->addressSignalState = obj.addressSignalState;
    this->byteDataSignalState = obj.byteDataSignalState;
    this->operationModeSignalState = obj.operationModeSignalState;

    return (*this);
  }

  enum class OperationMode: uint8_t 
  { 
    READ = 0U, 
    WRITE,
    UNDEFINED
  };

  void setAddressSignalValue(const uint32_t& value)
  {
    /// No signal boundary check required
    addressSignalValue = value;
    addressSignalState = InterfaceDataType::rbNet_DataReceived;
  }  

  void setByteDataSignalValue(const uint8_t& value)  
  {
    /// No signal boundary check required
    byteDataSignalValue = value;
    byteDataSignalState = InterfaceDataType::rbNet_DataReceived;
  }

  void setOperationModeSignalValue(const uint8_t& value)
  {
    /// No signal boundary check required
    operationModeSignalValue = value;
    operationModeSignalState = InterfaceDataType::rbNet_DataReceived;
  }

  InterfaceDataType getAddressSignalValue(uint32_t& value)
  {
    InterfaceDataType returnValue{addressSignalState};
    value = addressSignalValue;
    addressSignalState = InterfaceDataType::rbNet_DataNotAvailable;
    return returnValue;
  }

  InterfaceDataType getByteDataSignalValue(uint8_t& value)
  {
    InterfaceDataType returnValue{byteDataSignalState};
    value = byteDataSignalValue;
    byteDataSignalState  = InterfaceDataType::rbNet_DataNotAvailable;
    return returnValue;
  }

  InterfaceDataType getOperationModeSignalValue(uint8_t& value)
  {
    InterfaceDataType returnValue{operationModeSignalState};
    value = operationModeSignalValue;
    operationModeSignalState  = InterfaceDataType::rbNet_DataNotAvailable;
    return returnValue;
  }

  const ByteDataRequest deliver() 
  {
    ByteDataRequest returnObj{nullptr};
    returnObj = (*this);

    addressSignalState = InterfaceDataType::rbNet_DataNotAvailable;
    byteDataSignalState = InterfaceDataType::rbNet_DataNotAvailable;
    operationModeSignalState = InterfaceDataType::rbNet_DataNotAvailable;
    return returnObj;
  }

  static OperationMode operationModeMapper(uint8_t inputValue)
  {
    OperationMode returnValue{OperationMode::UNDEFINED};
    switch(inputValue)
    {
      case 0U: 
        returnValue = OperationMode::READ;
        break;
      case 1U: 
        returnValue = OperationMode::WRITE;
        break;
      default: 
        //Do nothing
        break;
    }

    return returnValue;
  }

private: 
  uint32_t addressSignalValue{0U};
  uint8_t byteDataSignalValue{0U};
  uint8_t operationModeSignalValue{0U};

  InterfaceDataType addressSignalState{InterfaceDataType::rbNet_DataInit};
  InterfaceDataType byteDataSignalState{InterfaceDataType::rbNet_DataInit};
  InterfaceDataType operationModeSignalState{InterfaceDataType::rbNet_DataInit};
};

class BlockDataRequest: public IInterface
{
public: 
  BlockDataRequest(MessageHandlerInterface* const messagePtr):IInterface(messagePtr){}
  const BlockDataRequest& operator=(const BlockDataRequest& obj)
  {
    this->addressSignalValue = obj.addressSignalValue;
    this->operationModeSignalValue = obj.operationModeSignalValue;
    this->addressSignalState = obj.addressSignalState;
    this->blockDataSignalState = obj.blockDataSignalState;
    this->operationModeSignalState = obj.operationModeSignalState;
    uint16_t index{0U};
    while(index < blockDataSize)
    {
      this->blockDataSignalValue[index] = obj.blockDataSignalValue[index];
      index++;
    }

    return (*this);
  }

  enum class OperationMode: uint8_t 
  { 
    READ = 0U, 
    WRITE,
    UNDEFINED
  };

  void setAddressSignalValue(const uint32_t& value)
  {
    /// No signal boundary check required
    addressSignalValue = value;
    addressSignalState = InterfaceDataType::rbNet_DataReceived;
  }  

  void setBlockDataSignalValue(const uint8_t* value) 
  {
    /// No signal boundary check required
    uint8_t index{0U}; 
    while(index < blockDataSize);
    {
      blockDataSignalValue[index] = (*value);
      value++;
      index++;
    }

    blockDataSignalState = InterfaceDataType::rbNet_DataReceived;
  }

  void setOperationModeSignalValue(const uint8_t& value)
  {
    /// No signal boundary check required
    operationModeSignalValue = value;
    operationModeSignalState = InterfaceDataType::rbNet_DataReceived;
  }

  InterfaceDataType getAddressSignalValue(uint32_t& value)
  {
    InterfaceDataType returnValue{addressSignalState};
    value = addressSignalValue;
    addressSignalState = InterfaceDataType::rbNet_DataNotAvailable;
    return returnValue;
  }

  InterfaceDataType getBlockDataSignalValue(uint8_t* value)
  {
    InterfaceDataType returnValue{blockDataSignalState};

    uint8_t index{0U}; 
    while(index < blockDataSize);
    {
      (*value) = blockDataSignalValue[index];
      value++;
      index++;
    }
    blockDataSignalState  = InterfaceDataType::rbNet_DataNotAvailable;
    return returnValue;
  }
  InterfaceDataType  getOperationModeSignalValue(uint8_t& value)
  {
    InterfaceDataType returnValue{operationModeSignalState};
    value = operationModeSignalValue;
    operationModeSignalState  = InterfaceDataType::rbNet_DataNotAvailable;
    return returnValue;
  }

  BlockDataRequest deliver()
  {
    BlockDataRequest returnObj{nullptr};
    returnObj = (*this);

    addressSignalState = InterfaceDataType::rbNet_DataNotAvailable;
    blockDataSignalState = InterfaceDataType::rbNet_DataNotAvailable;
    operationModeSignalState = InterfaceDataType::rbNet_DataNotAvailable;

    return returnObj;
  }

  static OperationMode operationModeMapper(uint8_t inputValue)
  {
    OperationMode returnValue{OperationMode::UNDEFINED};
    switch(inputValue)
    {
      case 0U: 
        returnValue = OperationMode::READ;
        break;
      case 1U: 
        returnValue = OperationMode::WRITE;
        break;
      default: 
        //Do nothing
        break;
    }

    return returnValue;
  }

private: 
  static constexpr uint16_t blockDataSize{256U};

  uint32_t addressSignalValue{0U};
  uint8_t blockDataSignalValue[blockDataSize]{0U};
  uint8_t operationModeSignalValue{0U};


  InterfaceDataType addressSignalState{InterfaceDataType::rbNet_DataInit};
  InterfaceDataType blockDataSignalState{InterfaceDataType::rbNet_DataInit};
  InterfaceDataType operationModeSignalState{InterfaceDataType::rbNet_DataInit};

};

}//End of namespace rbNetCOM

#endif
