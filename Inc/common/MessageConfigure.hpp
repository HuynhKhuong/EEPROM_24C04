#ifndef MESSAGE_CONFIGURE_HPP_INCLUDED
#define MESSAGE_CONFIGURE_HPP_INCLUDED

#include <array>
#include <cstdint>

namespace rbNetCOM {

using signalID = uint16_t;

struct MessageHandlerInterface {
public:
  using messageIDTypeDef = uint8_t;
  
  MessageHandlerInterface(const uint16_t &DLC,
                          const messageIDTypeDef &messageID,
                          bool (*cbkFunc)(uint8_t *))
      : m_DLC(DLC), m_messageID(messageID), m_cbkFnc(cbkFunc) {}

  const uint16_t m_DLC;
  const messageIDTypeDef m_messageID;

  bool (*m_cbkFnc)(uint8_t *);
  
  virtual const signalID *getSignalIDList(void) = 0; //this API should be improved to be memory safe
  virtual const uint16_t getNumberOfSignals(void) = 0; 
  virtual uint8_t* getLocalBuffer(void) = 0; //this API should be improved to be memory safe

protected:
  bool m_isNewMessageReceived{false};

private:
  // To prevent copying attempts
  MessageHandlerInterface(const MessageHandlerInterface &obj) = default;
  MessageHandlerInterface(MessageHandlerInterface &&obj) = default;
  const MessageHandlerInterface& operator=(const MessageHandlerInterface &obj) = delete;
};


struct SignalLayoutTypeDef {

  enum class ByteOrderTypeDef : uint8_t { MOTOROLA = 0U, INTEL };
  enum class SignalDataType : uint8_t {
    UINT8Type = 0U,
    UINT16Type,
    UINT32Type,
    FLOATType,
    OTHERS // signal length larger than 4 bytes
  };

  constexpr SignalLayoutTypeDef(const uint16_t &startBit,
                                const uint16_t &bitLength,
                                const ByteOrderTypeDef &byteOrder,
                                const SignalDataType &dataType,
                                const uint16_t &correspondingPDUIndex)
      : m_startBit(startBit), m_bitLength(bitLength), m_byteOrder(byteOrder),
        m_dataType(dataType), m_correspondingPDUIndex(correspondingPDUIndex) {}

  ///\brief signal layout (bytewise) diagram
  ///\note  x means occupied by signal
  ///       o means not occupied by signal
  ///|b7|b6|b5|b4|b3|b2|b1|b0| - byte 0
  ///|x |x |x |x |0 |0 |0 |0 | - byte 0
  ///|x |x |x |x |x |x |x |x | - byte 1
  ///|0 |0 |0 |x |x |x |x |x | - byte 2
  ///|0 |0 |0 |0 |0 |0 |0 |0 | - byte 3
  
  ///\brief Some terms used to describe signal layout
  ///\note  m_startByte: LSB byte of the signal
  ///\note  m_startBit: first LSB bit of m_startByte
  const uint16_t m_startBit;
  const uint16_t m_bitLength;
  const ByteOrderTypeDef m_byteOrder;
  const SignalDataType m_dataType;
  const uint16_t m_correspondingPDUIndex;
};

} // End of namespace rbNetCOM

#endif
