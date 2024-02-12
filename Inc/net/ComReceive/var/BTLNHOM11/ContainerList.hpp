#ifndef CONTAINERLIST_HPP_INCLUDED
#define CONTAINERLIST_HPP_INCLUDED

#include "ComReceive.hpp"

namespace rbNetCOM{

/// \brief This section is project specific, should be done by generating tool 
constexpr uint8_t g_totalNumbersOfSignals{8U};
extern uint8_t prvSignalTypeUint8_t[5U];
extern uint32_t prvSignalTypeUint32_t[2U];

struct InternalDataContainer;

extern InternalDataContainer prvSignalContainer;

constexpr uint8_t prvsignalMappingTable[g_totalNumbersOfSignals]{
    0U, // g_AddressSignalIDBlockMessage{0U};
    0U, // g_DataSignalIDByteMessage{1U};
    1U, // g_AddressSignalIDByteMessage{2U};
    0U, // g_DataSignalIDBlockMessage{3U}; // would be handled separately
    1U, // g_OperatorModeSignalIDByteMessage{4U};
    2U, // g_OperatorModeSignalIDBlockMessage{5U};
    3U, // g_ModeSignalIDBlockMessage{6U};
    4U, // g_ModeSignalIDByteMessage{7U};
};

uint16_t signalLayoutToSignalContainerMap(uint16_t signalIndex); 

} // End of namespace rbNetCOM

#endif
