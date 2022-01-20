#ifndef idgus_regH
#define idgus_regH

#include "Utils\swap_endian.h"

/**
 * @file dgus_reg.h
 * @author Barry Carter
 * @date 01 Jan 2021
 * @brief DGUS II LCD Driver. Register and cointrol definitions
 *
 */

#define member_size(type, member) sizeof(((type *)0)->member) /**< Get the member size of a struct */

/* Command addresses. A REG is 8bit, VAR cmd typically 16 */
/**
 * @brief Addresses of the command and variables
 */
enum command
{
    DGUS_CMD_REG_W_0x80 = 0x80,
    DGUS_CMD_REG_R_0x81,
    DGUS_CMD_VAR_W_0x82,
    DGUS_CMD_VAR_R_0x83,
    DGUS_CMD_CURVE_W_0x84
};

#define DGUS_RETURN bool /**< Defines the return status of a function */

/**
 * @brief DGUS_RETURN Response to an async request such as dgus_request_var()
 */
#define DGUS_OK                      0  /**< Everything was fine */
#define DGUS_TIMEOUT                 1  /**< Timed out waiting for OK */
#define DGUS_ERROR                   2  /**< Unspecified serious error */
#define DGUS_CURVE_BUFFER_FULL       10 /**< Cannot append any more data to this buffer */
#define DGUS_CURVE_CHANNEL_NOT_FOUND 11 /**< The Curve channel 0-7 was not initialised or found */



#endif
