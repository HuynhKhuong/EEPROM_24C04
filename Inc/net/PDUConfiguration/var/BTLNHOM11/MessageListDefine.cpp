///\note This is user's configuration 
///      In practice, this configuration should be visualized with UI & code generating tool to prevent 
///      human mistake

#include "MessageListDefine.hpp"
#include "SignalListDefine.hpp"

// forward declaration to feed class constructor
namespace rbNet_E2EProtect {
bool blockMessageCbk(uint8_t *dataBuffer);
bool byteMessageCbk(uint8_t *dataBuffer);
}// End of namespace rbNet_E2EProtect

namespace NetCom
{
constexpr MessageHandlerInterface::messageIDTypeDef g_blockMessageID{1U}; // 
constexpr MessageHandlerInterface::messageIDTypeDef g_byteMessageID{0U}; // 

signalID ByteMessageLayout::m_signalList[ByteMessageLayout::g_numberOfSignals]
{
        g_AddressSignalIDByteMessage, g_DataSignalIDByteMessage,
        g_OperatorModeSignalIDByteMessage, g_ModeSignalIDByteMessage
};

signalID BlockMessageLayout::m_signalList[BlockMessageLayout::g_numberOfSignals]
{
        g_AddressSignalIDBlockMessage, g_DataSignalIDBlockMessage,
        g_OperatorModeSignalIDBlockMessage, g_ModeSignalIDBlockMessage
};

BlockMessageLayout g_blockMessageHandler(g_blockMessageID, rbNet_E2EProtect::blockMessageCbk);
ByteMessageLayout g_byteMessageHandler(g_byteMessageID, rbNet_E2EProtect::byteMessageCbk);

std::array<MessageHandlerInterface* const, g_numberOfMessages> g_messageConfigureTable
          {&g_blockMessageHandler, &g_byteMessageHandler};
}// End of namespace NetCom