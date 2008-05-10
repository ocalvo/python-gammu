/* Test for decoding SMS on Nokia 6510 driver */

#include <gammu.h>
#include <stdlib.h>
#include <stdio.h>
#include "../common/protocol/protocol.h" /* Needed for GSM_Protocol_Message */
#include "../common/gsmstate.h" /* Needed for state machine internals */

#include "sms-printing.h"

unsigned char data[] = {
	0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x71, 0x00, 0x00, 0x02, 0x48, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35,
	0x00, 0x39, 0x00, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x04, 0x03, 0x81, 0x95, 0xF5, 0x00, 0x00, 0x70, 0x40, 0x41, 0x70, 0x24, 0x43, 0x80, 0x6F, 0xD6,
	0x37, 0x39, 0x6C, 0x7E, 0xBB, 0xCB, 0xA0, 0x66, 0x79, 0x3E, 0x2F, 0xBB, 0xCF, 0x65, 0xB9, 0x0B,
	0x04, 0x0D, 0xCB, 0xC3, 0xA0, 0xF1, 0xDB, 0x5D, 0x1E, 0xD3, 0xC3, 0x72, 0x7A, 0x19, 0x44, 0x2E,
	0xCF, 0xC9, 0x65, 0x50, 0x99, 0x0D, 0x1A, 0xB2, 0xD3, 0x65, 0x37, 0xBD, 0x0C, 0x82, 0x0E, 0x41,
	0xF4, 0x3A, 0x28, 0x49, 0x04, 0x91, 0xCB, 0xA0, 0x66, 0x79, 0x3E, 0x2F, 0xBB, 0xCF, 0x65, 0x39,
	0xA8, 0x3C, 0xD7, 0x81, 0xCA, 0x73, 0x98, 0x0C, 0x16, 0x93, 0xC1, 0x6A, 0x33, 0x50, 0x1E, 0x44,
	0xAF, 0x83, 0xC6, 0xEC, 0xB0, 0xBD, 0x0C, 0x2A, 0xCF, 0x75, 0xA0, 0x99, 0x0D, 0x76, 0xCB, 0xB9,
	0x00, 0x01, 0x01, 0x24, 0x01, 0x00, 0x01, 0x00, 0x02, 0x00, 0x0D, 0x2B, 0x33, 0x34, 0x36, 0x30,
	0x37, 0x30, 0x30, 0x33, 0x31, 0x31, 0x30, 0x00, 0x03, 0x00, 0xE0, 0x00, 0x56, 0x00, 0x6F, 0x00,
	0x64, 0x00, 0x61, 0x00, 0x66, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x65, 0x00, 0x20, 0x00, 0x4D, 0x00,
	0x65, 0x00, 0x73, 0x00, 0x73, 0x00, 0x65, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x65, 0x00, 0x72, 0x00,
	0x2E, 0x00, 0x20, 0x00, 0x50, 0x00, 0x61, 0x00, 0x72, 0x00, 0x61, 0x00, 0x20, 0x00, 0x63, 0x00,
	0x6F, 0x00, 0x6E, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x61, 0x00, 0x72, 0x00, 0x74, 0x00,
	0x65, 0x00, 0x20, 0x00, 0x64, 0x00, 0x65, 0x00, 0x73, 0x00, 0x64, 0x00, 0x65, 0x00, 0x20, 0x00,
	0x65, 0x00, 0x6C, 0x00, 0x20, 0x00, 0x43, 0x00, 0x6C, 0x00, 0x69, 0x00, 0x65, 0x00, 0x6E, 0x00,
	0x74, 0x00, 0x65, 0x00, 0x20, 0x00, 0x50, 0x00, 0x43, 0x00, 0x20, 0x00, 0x74, 0x00, 0x75, 0x00,
	0x20, 0x00, 0x49, 0x00, 0x44, 0x00, 0x20, 0x00, 0x64, 0x00, 0x65, 0x00, 0x20, 0x00, 0x4D, 0x00,
	0x65, 0x00, 0x73, 0x00, 0x73, 0x00, 0x65, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x65, 0x00, 0x72, 0x00,
	0x20, 0x00, 0x65, 0x00, 0x73, 0x00, 0x3A, 0x00, 0x20, 0x00, 0x65, 0x00, 0x73, 0x00, 0x30, 0x00,
	0x32, 0x00, 0x30, 0x00, 0x31, 0x00, 0x32, 0x00, 0x30, 0x00, 0x35, 0x00, 0x33, 0x00, 0x20, 0x00,
	0x79, 0x00, 0x20, 0x00, 0x74, 0x00, 0x75, 0x00, 0x20, 0x00, 0x63, 0x00, 0x6C, 0x00, 0x61, 0x00,
	0x76, 0x00, 0x65, 0x00, 0x20, 0x00, 0x65, 0x00, 0x73, 0x00, 0x3A, 0x00, 0x20, 0x00, 0x33, 0x00,
	0x36, 0x00, 0x30, 0x00, 0x37, 0x00, 0x39, 0x00, 0x2E, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x35,
	0x00, 0x39, 0x00, 0x35, 0x00, 0x00, 0x0C, 0x00, 0x01, 0x00, 0x07, 0x00, 0x01, 0x00, 0x05, 0x00,
	0x01, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0x00, 0x0B, 0x00, 0x01,
	0x00, 0x09, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00,
	};

/* This is not part of API! */
extern GSM_Error N6510_DecodeFilesystemSMS(GSM_StateMachine *s, GSM_MultiSMSMessage *sms, GSM_File *FFF, int location);

int main(int argc UNUSED, char **argv UNUSED)
{
	GSM_Debug_Info *debug_info;
	GSM_StateMachine *s;
	GSM_File file;
	GSM_Error error;
	GSM_MultiSMSMessage sms;

	debug_info = GSM_GetGlobalDebug();
	GSM_SetDebugFileDescriptor(stderr, debug_info);
	GSM_SetDebugLevel("textall", debug_info);

	/* Allocates state machine */
	s = GSM_AllocStateMachine();
	if (s == NULL) {
		printf("Could not allocate state machine!\n");
		return 1;
	}
	debug_info = GSM_GetDebug(s);
	GSM_SetDebugGlobal(true, debug_info);
	GSM_SetDebugFileDescriptor(stderr, debug_info);
	GSM_SetDebugLevel("textall", debug_info);

	/* Init file */
	file.Buffer = malloc(sizeof(data));
	memcpy(file.Buffer, data, sizeof(data));
	file.Used = sizeof(data);
	file.ID_FullName[0] = 0;
	file.ID_FullName[1] = 0;

	/* Parse it */
	error = N6510_DecodeFilesystemSMS(s, &sms, &file, 0);

	/* Check expected text */
	if (strcmp("Vodafone Messenger. Para conectarte desde el Cliente PC tu ID de Messenger es: es02012053 y tu clave es: 36079.",
				DecodeUnicodeConsole(sms.SMS[0].Text)) != 0) {
		printf("Messages do not match!\n");
		return 1;
	}

	/* Display message */
	DisplayTestSMS(sms);

	/* Free state machine */
	GSM_FreeStateMachine(s);

	printf("%s\n", GSM_ErrorString(error));

	return (error == ERR_NONE) ? 0 : 1;
}

/* Editor configuration
 * vim: noexpandtab sw=8 ts=8 sts=8 tw=72:
 */
