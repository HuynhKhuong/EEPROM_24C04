#include <iostream>
#include <cstdint>
#include "ComReceive.hpp"

namespace rbNetCOM {

/// \brief This section is project specific, should be done by generating tool 

constexpr uint8_t g_totalNumbersOfSignals{8U};
static uint8_t prvSignalTypeUint8_t[5U];
static uint32_t prvSignalTypeUint32_t[2U];

InternalDataContainer prvSignalContainer(&prvSignalTypeUint8_t[0U],
                                         nullptr, // no uint16_t signals
                                         &prvSignalTypeUint32_t[0U],
                                         nullptr  // no float signal
);

static uint8_t prvsignalMappingTable[8U]{
    0U, // g_AddressSignalIDBlockMessage{0U};
    0U, // g_DataSignalIDByteMessage{1U};
    1U, // g_AddressSignalIDByteMessage{2U};
    0U, // g_DataSignalIDBlockMessage{3U}; // would be handled separately
    1U, // g_OperatorModeSignalIDByteMessage{4U};
    2U, // g_OperatorModeSignalIDBlockMessage{5U};
    3U, // g_ModeSignalIDBlockMessage{6U};
    4U, // g_ModeSignalIDByteMessage{7U};
};

static inline uint16_t signalLayoutToSignalContainerMap(uint16_t signalIndex) {
  uint16_t mappedIndex{signalIndex};
  if (signalIndex >= g_totalNumbersOfSignals) {
    mappedIndex = 0U;
  }

  return prvsignalMappingTable[mappedIndex];
}

//-----------------------------------------------------------------------------//
/// @brief Common part
static inline void castingSignalType(const SignalLayoutTypeDef::SignalDataType type,
                                      const void* source, 
                                      void* destination)
{

  if(type == SignalLayoutTypeDef::SignalDataType::UINT8Type)
  {
      uint8_t tempContainer{*(static_cast<const uint8_t*>(source))};
      *(static_cast<uint8_t*>(destination)) = tempContainer;
  }
  else if(type == SignalLayoutTypeDef::SignalDataType::UINT16Type)
  {  
    uint16_t tempContainer{*(static_cast<const uint16_t *>(source))};
      *(static_cast<uint16_t *>(destination)) = tempContainer;
  }
  else if(type == SignalLayoutTypeDef::SignalDataType::UINT32Type)
  {
      uint32_t tempContainer{*(static_cast<const uint32_t  *>(source))};
      *(static_cast<uint32_t*>(destination)) = tempContainer;
  }
  else if(type == SignalLayoutTypeDef::SignalDataType::FLOATType)
  {
      float tempContainer{*(static_cast<const float*>(source))};
      *(static_cast<float*>(destination)) = tempContainer;
  }
  else 
  {
      //Do nothing
  }
}

///\brief   Dispatch a single signal from buffer
///\input   SignalLayoutTypeDef layoutInfo of a signal
///\input   localBuffer: source data
///\output  prvSignalContainer is written with new data
///\note    This function only processes data with primary datatype
///         e.g: int, float, double....
static void prv_ComSignalExtract(const SignalLayoutTypeDef &layoutInfo,
                                 const uint8_t *localBuffer,
                                 void* const destinationBuffer) {
  // Max data supported is 32bit long
  uint32_t dataContainer{0U};
  const uint8_t byteLength{8U};
  const uint32_t bitMask_u32{0xffffffU};
  const uint8_t bitMask_u8{0xffU};
  const uint8_t bitOffsetInByte{static_cast<uint8_t>(layoutInfo.m_startBit % 8U)};
  uint8_t byteNumber{static_cast<uint8_t>(layoutInfo.m_startBit >> 3U)};

  // For copying progess
  uint32_t numberOfBitsLeft{0U};
  uint32_t totalOfBitsCopied{0U};

  ///\brief signal layout (bytewise) diagram
  ///\note  x means occupied by signal
  ///       o means not occupied by signal
  ///|b7|b6|b5|b4|b3|b2|b1|b0| - byte 0
  ///|x |x |x |x |0 |0 |0 |0 | - byte 0
  ///|x |x |x |x |x |x |x |x | - byte 1
  ///|0 |0 |0 |x |x |x |x |x | - byte 2
  ///|0 |0 |0 |0 |0 |0 |0 |0 | - byte 3

  if (layoutInfo.m_dataType == SignalLayoutTypeDef::SignalDataType::OTHERS) 
  {
    // Other ways to handle this signal
  } 
  else 
  {
    // First get data from start byte
    dataContainer = static_cast<uint32_t>(*(localBuffer + byteNumber));
    dataContainer = dataContainer >> bitOffsetInByte;
    if (layoutInfo.m_bitLength >= static_cast<uint16_t>(8U - bitOffsetInByte)) 
    {
      // bit length is larger than 1 byte
      totalOfBitsCopied = byteLength - bitOffsetInByte;
    } 
    else 
    {
      // bit length is smaller than 1 byte & placed within a byte
      dataContainer = dataContainer & static_cast<uint32_t>(~static_cast<uint32_t>(
                              bitMask_u32 << layoutInfo.m_bitLength));
      totalOfBitsCopied = layoutInfo.m_bitLength;
    }
    //Process if bit length is larger than 1 byte
    while(totalOfBitsCopied < layoutInfo.m_bitLength)
    {
      if(layoutInfo.m_byteOrder == SignalLayoutTypeDef::ByteOrderTypeDef::INTEL)
      {
        byteNumber++;
      }
      else
      {
        //SignalLayoutTypeDef::ByteOrderTypeDef::MOTOROLA)
        byteNumber--;
      }
      uint8_t tempContainer = (*(localBuffer + byteNumber)); //Get next byte
      numberOfBitsLeft =  layoutInfo.m_bitLength - totalOfBitsCopied; 

      if(numberOfBitsLeft >= byteLength)
      {
        dataContainer |= static_cast<uint32_t>(tempContainer << totalOfBitsCopied);
        totalOfBitsCopied += byteLength;
      }
      else
      {
        uint8_t tempBitMask{static_cast<uint8_t>(bitMask_u8 >> (byteLength - numberOfBitsLeft))};
        tempContainer &= tempBitMask;

        dataContainer |= static_cast<uint32_t>(tempContainer << totalOfBitsCopied);
      }

    }
    
    castingSignalType(layoutInfo.m_dataType, static_cast<void*>(&dataContainer), destinationBuffer);
  }
}

void rbNetComReceive(uint8_t *dataBuffer) 
{
  const uint8_t messageIDIndex{0U};
  // get messageID
  const uint8_t messageID{dataBuffer[messageIDIndex]};

  bool messageIDMatched{false};
  bool messageE2EProtectPassed{false};

  // hook to get matched message handler
  MessageHandlerInterface* msgHandlerPtr{nullptr};

  for (MessageHandlerInterface* const messageHandler: g_messageConfigureTable){
    if (messageHandler->m_messageID == messageID) 
    {
      messageE2EProtectPassed = messageHandler->m_cbkFnc(dataBuffer);
      messageIDMatched = true;
      msgHandlerPtr = messageHandler;
      break;
    }
  }

  if (messageIDMatched && messageE2EProtectPassed) 
  {
    // Trigger copy to internal signal buffer and set indication flag to true
    rbNetComDispatchSignals(*msgHandlerPtr);
  } 
  else 
  {
    // In case no match message ID, do nothing
  }
}

void rbNetComDispatchSignals(MessageHandlerInterface &messageLayout) 
{
  const uint16_t numbOfSignals{messageLayout.getNumberOfSignals()};
  const uint16_t *signalList{messageLayout.getSignalIDList()};
  const uint8_t *localBuffer{messageLayout.getLocalBuffer()};

  for (uint8_t i{0U}; i < numbOfSignals; i++) 
  {
    const SignalLayoutTypeDef& signalInstance{g_signalConfigureTable[signalList[i]]};
    const uint16_t index{signalLayoutToSignalContainerMap(signalList[i])};
       
    switch(signalInstance.m_dataType) 
    {
      case SignalLayoutTypeDef::SignalDataType::UINT8Type:
        prv_ComSignalExtract(signalInstance, localBuffer, static_cast<void*>(&(prvSignalContainer.m_signalTypeUint8_t[index])));
        break;
      case SignalLayoutTypeDef::SignalDataType::UINT16Type:
        prv_ComSignalExtract(signalInstance, localBuffer, static_cast<void*>(&(prvSignalContainer.m_signalTypeUint16_t[index])));
        break;
      case SignalLayoutTypeDef::SignalDataType::UINT32Type:
        prv_ComSignalExtract(signalInstance, localBuffer, static_cast<void*>(&(prvSignalContainer.m_signalTypeUint32_t[index])));
        break;
      case SignalLayoutTypeDef::SignalDataType::FLOATType:
        prv_ComSignalExtract(signalInstance, localBuffer, static_cast<void*>(&(prvSignalContainer.m_signalTypeFloat[index])));
        break;
      case SignalLayoutTypeDef::SignalDataType::OTHERS:
      default:
        break;
    }
  }
}

} // End of namespace rbNetCOM
