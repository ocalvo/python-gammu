
#include <string.h>
#include <ctype.h>

#include "../../../cfg/config.h"
#include "../../phone/nokia/nfunc.h"
#include "../../phone/nokia/dct3/n7110.h"
#include "../../misc/coding.h"
#include "../gsmlogo.h"
#include "../gsmmisc.h"
#include "backvcf.h"

#ifdef GSM_ENABLE_BACKUP

GSM_Error SaveVCard(FILE *file, GSM_Backup *backup)
{
	int 		i, Length = 0;
	unsigned char 	Buffer[1000];

	i=0;
	while (backup->PhonePhonebook[i]!=NULL) {
		sprintf(Buffer, "%c%c",13,10);
		fwrite(Buffer,1,2,file);
		Length = 0;
		GSM_EncodeVCARD(Buffer,&Length,backup->PhonePhonebook[i],true,Nokia_VCard21);
		fwrite(Buffer,1,Length,file);
		i++;
	}
	return GE_NONE;
}

GSM_Error LoadVCard(char *FileName, GSM_Backup *backup)
{
	GSM_File 		File;
	GSM_Error		error;
	GSM_PhonebookEntry	Pbk;
	int			numPbk = 0, Pos;

	File.Buffer = NULL;
	error = GSM_ReadFile(FileName, &File);
	if (error != GE_NONE) return error;

	Pos = 0;
	while (1) {
		error = GSM_DecodeVCARD(File.Buffer, &Pos, &Pbk, Nokia_VCard21);
		if (error == GE_EMPTY) break;
		if (error != GE_NONE) return error;
		if (numPbk < GSM_BACKUP_MAX_PHONEPHONEBOOK) {
			backup->PhonePhonebook[numPbk] = malloc(sizeof(GSM_PhonebookEntry));
		        if (backup->PhonePhonebook[numPbk] == NULL) return GE_MOREMEMORY;
			backup->PhonePhonebook[numPbk + 1] = NULL;
		} else {
			dprintf("Increase GSM_BACKUP_MAX_PHONEPHONEBOOK\n");
			return GE_MOREMEMORY;
		}
		memcpy(backup->PhonePhonebook[numPbk],&Pbk,sizeof(GSM_PhonebookEntry));
		backup->PhonePhonebook[numPbk]->Location 	= numPbk + 1;
		backup->PhonePhonebook[numPbk]->MemoryType 	= GMT_ME;
		numPbk++;
	}

	return GE_UNKNOWN;
}

#endif

/* How should editor hadle tabs in this file? Add editor commands here.
 * vim: noexpandtab sw=8 ts=8 sts=8:
 */
