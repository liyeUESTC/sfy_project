#ifndef FORWARD_COMMON_BASEFUNCTION_H_
#define FORWARD_COMMON_BASEFUNCTION_H_

#include <stdint.h>
#include <sys/types.h>

#define SUCCESSFUL 1
#define FAILED   -1

const int kRequestId = 1;
const uint32_t kForwardMsg = 2;
const uint32_t kReturnId = 3;

const int kDataSize = 10000;
const int kMsgHeaderSize = 20;


struct MsgHeader
{
	uint32_t cmd;
	uint32_t length;
	uint32_t error;
	uint32_t src_id;
	uint32_t dst_id;
};
struct Msg
{
	struct MsgHeader msg_header;
	char *data;
};

#endif //FORWARD_COMMON_BASEFUNCTION_H_
