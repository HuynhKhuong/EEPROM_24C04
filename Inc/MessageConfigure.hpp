#ifndef MESSAGE_CONFIGURE_HPP_INCLUDED
#define MESSAGE_CONFIGURE_HPP_INCLUDED

#include <array>
#include <cstdint>

namespace rbNetCOM {
using signalID = uint16_t;

/// \note declared as constexpr in .hpp file would be treated as const and
/// inline variables ODR would never be broken
constexpr uint16_t g_blockMessageIndex{1U};
constexpr uint16_t g_byteMessageIndex{0U};
constexpr uint8_t g_numberOfMessages{2U};
constexpr uint8_t g_numberOfSignals{8U};

constexpr uint16_t g_AddressSignalIDBlockMessage{0U};
constexpr uint16_t g_DataSignalIDByteMessage{1U};
constexpr uint16_t g_AddressSignalIDByteMessage{2U};
constexpr uint16_t g_DataSignalIDBlockMessage{3U};
constexpr uint16_t g_OperatorModeSignalIDByteMessage{4U};
constexpr uint16_t g_OperatorModeSignalIDBlockMessage{5U};
constexpr uint16_t g_ModeSignalIDBlockMessage{6U};
constexpr uint16_t g_ModeSignalIDByteMessage{7U};

struct MessageLayoutInterface {
public:
  MessageLayoutInterface() = default;

protected:
  bool m_isNewMessageReceived{false};

private:
  // To prevent copying attempts
  MessageLayoutInterface(const MessageLayoutInterface &obj) = default;
  MessageLayoutInterface(MessageLayoutInterface &&obj) = default;
  MessageLayoutInterface &operator=(const MessageLayoutInterface &obj) = delete;
};

struct BlockMessageLayout : MessageLayoutInterface {
public:
  BlockMessageLayout() = default;

  static constexpr uint16_t g_numberOfSignals = 4U;

  static signalID m_signalList[g_numberOfSignals];
};

struct ByteMessageLayout : MessageLayoutInterface {
public:
  ByteMessageLayout() = default;

  static constexpr uint16_t g_numberOfSignals = 4U;

  static signalID m_signalList[g_numberOfSignals];
};

struct SignalLayoutTypeDef {

  enum class ByteOrderTypeDef : uint8_t { MOTOROLA = 0U, INTEL };

  constexpr SignalLayoutTypeDef(const uint16_t &startBit,
                                const uint16_t &bitLength,
                                const ByteOrderTypeDef &byteOrder,
                                const uint16_t &correspondingPDUIndex)
      : m_startBit(startBit), m_bitLength(bitLength), m_byteOrder(byteOrder),
        m_correspondingPDUIndex(correspondingPDUIndex) {}

  const uint16_t m_startBit;
  const uint16_t m_bitLength;
  const ByteOrderTypeDef m_byteOrder;
  const uint16_t m_correspondingPDUIndex;
};

constexpr std::array<SignalLayoutTypeDef, g_numberOfSignals>
    g_signalConfigureTable{
        SignalLayoutTypeDef(24U, 16U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            g_blockMessageIndex), // Address
        SignalLayoutTypeDef(43U, 1U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            g_blockMessageIndex), // Byte Data
        SignalLayoutTypeDef(24U, 16U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            g_byteMessageIndex), // Address
        SignalLayoutTypeDef(43, 255U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            g_byteMessageIndex), // Block Data
        SignalLayoutTypeDef(0U, 1U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            g_blockMessageIndex), // Mode (Read
                                                  // or Write)
        SignalLayoutTypeDef(0U, 1U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            g_byteMessageIndex), // Mode (Read
                                                 // or Write)
        SignalLayoutTypeDef(
            8U, 1U, SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
            g_blockMessageIndex), // Mode (Block or
                                  // Byte), this signal is both ID of the
                                  // message, and the value to be monitored to
                                  // handle E2E protection along with DLC check
        SignalLayoutTypeDef(
            8U, 1U, SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
            g_byteMessageIndex), // Mode (Block or
                                 // Byte), this signal is both ID of the
                                 // message, and the value to be monitored to
                                 // handle E2E protection along with DLC check
    };

extern BlockMessageLayout g_blockMessageHandler;
extern ByteMessageLayout g_byteMessageHandler;

} // End of namespace rbNetCOM
#endif
