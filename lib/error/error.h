#ifndef __ERROR_H__

#define __ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *
 * \typedef  api_err_t
 *
 * \brief    API errors typedefs
 *
 * \param    API_NO_ERR       No erros in result
 * \param    API_MEM_ERR      Memory allocation error. Violation of access rights or boundaries when accessing memory.
 * \param    API_NET_ERR      Error communicating over the network.
 * \param    API_PROTO_ERR    Error in the interaction Protocol.
 * \param    API_CMD_ERR      Error executing a command on the device.
 * \param    API_UNK_ERR      An error not covered by the above.
 * \param    API_STOR_ERR     Storage error.
 */

typedef enum {
	API_NO_ERR = 0,
	API_MEM_ERR = -1,
	API_NET_ERR = -2,
	API_PROTO_ERR = -3,
	API_CMD_ERR = -4,
	API_DB_ERR = -5,
	API_STOR_ERR = -6,
	API_OTHER_ERR = -255
} api_err_t;

#define DECODE_ERR(ERR)                                                        \
	(ERR == API_NO_ERR) ? "No error detected." :                           \
	(ERR == API_MEM_ERR) ?                                                 \
			      "Memory allocation or access violation error." : \
	(ERR == API_NET_ERR)   ? "Network error." :                            \
	(ERR == API_PROTO_ERR) ? "Protocol error." :                           \
	(ERR == API_CMD_ERR)   ? "Operation code error." :                     \
	(ERR == API_DB_ERR)    ? "Database error." :                           \
	(ERR == API_STOR_ERR)  ? "Storage error." :                            \
				 "Other error."

#ifdef __cplusplus
}
#endif

#endif // __ERROR_H__
