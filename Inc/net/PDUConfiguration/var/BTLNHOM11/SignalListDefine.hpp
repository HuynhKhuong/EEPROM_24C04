///\note This is user's configuration 
///      In practice, this configuration should be visualized with UI & code generating tool to prevent 
///      human mistake

#ifndef SIGNALLISTDEFINE_INCLUDED_HPP
#define SIGNALLISTDEFINE_INCLUDED_HPP

#include "MessageListDefine.hpp"

namespace rbNetCOM {

constexpr uint8_t g_numberOfSignals{8U};
constexpr uint16_t g_AddressSignalIDBlockMessage{0U};
constexpr uint16_t g_DataSignalIDByteMessage{1U};
constexpr uint16_t g_AddressSignalIDByteMessage{2U};
constexpr uint16_t g_DataSignalIDBlockMessage{3U};
constexpr uint16_t g_OperatorModeSignalIDByteMessage{4U};
constexpr uint16_t g_OperatorModeSignalIDBlockMessage{5U};
constexpr uint16_t g_ModeSignalIDBlockMessage{6U};
constexpr uint16_t g_ModeSignalIDByteMessage{7U};

constexpr std::array<SignalLayoutTypeDef, g_numberOfSignals> g_signalConfigureTable{
        SignalLayoutTypeDef(24U, 24U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT32Type,
                            g_blockMessageIndex), // Address
        SignalLayoutTypeDef(48U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_blockMessageIndex), // Byte Data
        SignalLayoutTypeDef(24U, 24U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT32Type,
                            g_byteMessageIndex), // Address
        SignalLayoutTypeDef(48, 2048U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::OTHERS,
                            g_byteMessageIndex), // Block Data
        SignalLayoutTypeDef(8U, 1U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_blockMessageIndex), // Mode (Read
                                                  // or Write)
        SignalLayoutTypeDef(8U, 1U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_byteMessageIndex), // Mode (Read
                                                 // or Write)
        SignalLayoutTypeDef(0U, 1U, 
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_blockMessageIndex), // Mode (Block or
                                                  // Byte), this signal is both ID of the
                                                  // message, and the value to be monitored to
                                                  // handle E2E protection along with DLC check
        SignalLayoutTypeDef(0U, 1U, 
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_byteMessageIndex), // Mode (Block or
                                                 // Byte), this signal is both ID of the
                                                 // message, and the value to be monitored to
                                                 // handle E2E protection along with DLC check
    };
} //End of namespace rbNetCOM
#endif
