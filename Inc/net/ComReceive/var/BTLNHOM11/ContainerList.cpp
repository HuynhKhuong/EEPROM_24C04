#include "ContainerList.hpp"

namespace NetCom
{
uint8_t prvSignalTypeUint8_t[5U];
uint32_t prvSignalTypeUint32_t[2U];
uint8_t prvSignalArrayType[256U]; //Size of this array is total size of all OTHER-TYPE array signal 

InternalDataContainer prvSignalContainer(&prvSignalTypeUint8_t[0U],
                                         nullptr, // no uint16_t signals
                                         &prvSignalTypeUint32_t[0U],
                                         nullptr,  // no float signal,
                                         &prvSignalArrayType[0U]);

uint16_t signalLayoutToSignalContainerMap(uint16_t signalIndex)
{
  uint16_t mappedIndex{signalIndex};
  if (signalIndex >= g_totalNumbersOfSignals) {
    mappedIndex = 0U;
  }

  return prvsignalMappingTable[mappedIndex];
}

} // end of namespace NetCom 
