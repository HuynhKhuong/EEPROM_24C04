#ifndef RX_PROTECT_HPP_INCLUDED
#define RX_PROTECT_HPP_INCLUDED

#include <cstdint>

namespace rbNet_E2EProtect {
/*
 * Specific for project usage:
 * - Cbk for block message
 * - Cbk for byte message
 */

///\brief Callback Functions to be called for each message
///\details Callback Functions is called everytime a new message is received
/// and the corresponding ID is checked
/// \todo
/// \input: dataBuffer[] raw data container
bool blockMessageCbk(uint8_t *dataBuffer);
bool byteMessageCbk(uint8_t *dataBuffer);

} // End of namespace rbNet_E2EProtect

#endif
