#ifndef MESSAGELISTDEFINE_HPP
#define MESSAGELISTDEFINE_HPP

#include <cstdint>
#include <array>
#include "MessageConfigure.hpp"

namespace rbNetCOM {

/// \note declared as constexpr in .hpp file would be treated as const and
/// inline variables ODR would never be broken
constexpr uint16_t blockMessageDLC{263U}; // Data + Address = 256+3 +mode(1) +ID(1) +DLC(1) +endofFrame(1)
constexpr uint16_t byteMessageDLC{8U};   // Data + Address = 1+3, +mode(1) +ID(1) +DLC(1) +endofFrame(1)

constexpr uint16_t g_blockMessageIndex{1U};
constexpr uint16_t g_byteMessageIndex{0U};
constexpr uint8_t g_numberOfMessages{2U};

class BlockMessageLayout: public MessageHandlerInterface 
{
public:
  BlockMessageLayout( const messageIDTypeDef &messageID, bool (*cbkFunc)(uint8_t *), 
                      const uint16_t &DLC = blockMessageDLC): 
                     MessageHandlerInterface(DLC, messageID, cbkFunc) {}

  static constexpr uint16_t g_numberOfSignals{4U};
  static constexpr uint16_t g_blockMessageDLC{262U}; // Data + Address = 255+3
  static signalID m_signalList[g_numberOfSignals]; //Reference out to g_signalConfigureTable
  uint8_t m_localBuffer[g_blockMessageDLC]{0U};

  const signalID *getSignalIDList(void) override { return &m_signalList[0U]; }
  const uint16_t getNumberOfSignals(void) override {return g_numberOfSignals;} 
  uint8_t* getLocalBuffer(void) override {return &m_localBuffer[0U];}

  static_assert(g_numberOfSignals == sizeof(m_signalList)/sizeof(m_signalList[0U]), 
                "not consistent");
};

class ByteMessageLayout: public MessageHandlerInterface 
{
public:
  ByteMessageLayout(const messageIDTypeDef &messageID, bool (*cbkFunc)(uint8_t *),
                    const uint16_t &DLC = byteMessageDLC)
      : MessageHandlerInterface(DLC, messageID, cbkFunc) {}


  static constexpr uint16_t g_numberOfSignals = 4U;
  static constexpr uint16_t g_byteMessageDLC{8U};   // Data + Address = 1+3
  uint8_t m_localBuffer[g_byteMessageDLC]{0U};
  static signalID m_signalList[g_numberOfSignals]; //Reference out to g_signalConfigureTable

  const signalID *getSignalIDList(void) override { return &m_signalList[0U]; }
  const uint16_t getNumberOfSignals(void) override {return g_numberOfSignals;} 
  uint8_t* getLocalBuffer(void) override {return &m_localBuffer[0U];}

  static_assert(g_numberOfSignals == sizeof(m_signalList)/sizeof(m_signalList[0U]), 
                "not consistent");
};

//Forward declaration to register messages handler into configuration table
extern BlockMessageLayout g_blockMessageHandler;
extern ByteMessageLayout g_byteMessageHandler;

extern std::array<MessageHandlerInterface* const, g_numberOfMessages> g_messageConfigureTable;

}// End of namespace rbNetCOM
#endif
