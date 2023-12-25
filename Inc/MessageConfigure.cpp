#include "MessageConfigure.hpp"

namespace rbNetCOM {

signalID ByteMessageLayout::m_signalList[ByteMessageLayout::g_numberOfSignals]{
    g_AddressSignalIDByteMessage, g_DataSignalIDByteMessage,
    g_OperatorModeSignalIDByteMessage, g_ModeSignalIDByteMessage};

signalID
    BlockMessageLayout::m_signalList[BlockMessageLayout::g_numberOfSignals]{
        g_AddressSignalIDBlockMessage, g_DataSignalIDBlockMessage,
        g_OperatorModeSignalIDBlockMessage, g_ModeSignalIDBlockMessage};

BlockMessageLayout g_blockMessageHandler;
ByteMessageLayout g_byteMessageHandler;

} // End of namespace rbNetCOM
