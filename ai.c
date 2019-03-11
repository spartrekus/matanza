#define AI_SCREEN_HEIGHT 24
#define AI_SCREEN_WIDTH 80 \

#define REGISTER_SHIP_TAIL(xname)  \
{ \
MatShip*ship; \
 \
int pos; \
 \
REGISTER_SHIP_STANDARD(xname) ; \
 \
ship->ship->next= NULL; \
ship->ship->prev= mat_universe->ship_list_tail; \
 \
if(mat_universe->ship_list_tail)  \
mat_universe->ship_list_tail->next= ship->ship; \
else \
mat_universe->ship_list_head= ship->ship; \
 \
mat_universe->ship_list_tail= ship->ship; \
} \

#define REGISTER_SHIP_HEAD(xname)  \
{ \
MatShip*ship; \
 \
int pos; \
 \
REGISTER_SHIP_STANDARD(xname) ; \
 \
ship->ship->next= mat_universe->ship_list_head; \
ship->ship->prev= NULL; \
 \
if(mat_universe->ship_list_head)  \
mat_universe->ship_list_head->prev= ship->ship; \
else \
mat_universe->ship_list_tail= ship->ship; \
 \
mat_universe->ship_list_head= ship->ship; \
} \

#define REGISTER_SHIP_STANDARD(xname)  \
{ \
ship= malloc(sizeof(MatShip) ) ; \
if(!ship)  \
{ \
fprintf(stderr,"%s: malloc: %s\n",program_name,strerror(errno) ) ; \
exit(EXIT_FAILURE) ; \
} \
 \
ship->name= xname; \
 \
ship->ship= malloc(sizeof(MatMovingObj) ) ; \
if(!ship->ship)  \
{ \
fprintf(stderr,"%s: malloc: %s\n",program_name,strerror(errno) ) ; \
exit(EXIT_FAILURE) ; \
} \
 \
pos= fhash(ship->name) %MAT_SHIP_HASH_SIZE; \
 \
ship->next= mat_universe->ship_hash[pos]; \
mat_universe->ship_hash[pos]= ship; \
} \

#define REMOVE_SHIP(xname)  \
{ \
MatShip*ship; \
int pos; \
 \
pos= fhash(xname) %MAT_SHIP_HASH_SIZE; \
 \
ship= mat_universe->ship_hash[pos]; \
 \
ASSERT(ship) ; \
 \
if(!strcmp(ship->name,xname) )  \
mat_universe->ship_hash[pos]= ship->next; \
else \
{ \
MatShip*tmp; \
 \
ASSERT(ship->next) ; \
while(strcmp(ship->next->name,xname) )  \
{ \
ship= ship->next; \
 \
ASSERT(ship->next) ; \
ASSERT(ship->next->name) ; \
} \
 \
tmp= ship->next; \
ship->next= ship->next->next; \
ship= tmp; \
} \
 \
if(ship->ship->prev)  \
ship->ship->prev->next= ship->ship->next; \
else \
mat_universe->ship_list_head= ship->ship->next; \
 \
if(ship->ship->next)  \
ship->ship->next->prev= ship->ship->prev; \
else \
mat_universe->ship_list_tail= ship->ship->prev; \
 \
free(ship->ship) ; \
free(ship->name) ; \
free(ship) ; \
} \

#define MAT_SHIP_HASH_SIZE 47 \

#define AI_INST_STORE 0 \

#define ASSERT(x) if(!(x) ) fprintf(stderr,"%s:%d: ASSERT failed\n",__FILE__,__LINE__) ,assert_exit()  \

#define ASSERT_FOR(x) for(x)  \

#define VERBOSE printf \

/*1:*/
#line 3 "./ai.w"

/*67:*/
#line 1187 "./ai.w"

#ifdef HAVE_CONFIG_H
#include <config.h> 
#else
#define PACKAGE "matanza"
#define VERSION "{Unknown-Version}"
#endif

/*63:*/
#line 1137 "./ai.w"

#include <stdarg.h> 
#include <sys/time.h> 
#include <sys/types.h> 
#include <signal.h> 
#include <sys/socket.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <netdb.h> 
#include <unistd.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <sys/ioctl.h> 
#include <ctype.h> 
#include <fcntl.h> 
#include <stdarg.h> 
#include <getopt.h> 
#include <sys/ioctl.h> 
#include <math.h> 
#include <limits.h> 

#include <shipreal.c> 

#include <mmp.h> 

/*:63*/
#line 1195 "./ai.w"


#if ! HAVE_HSTRERROR
#  define hsterror(x) "Host not found"
#endif/*:67*/
#line 4 "./ai.w"

/*51:*/
#line 978 "./ai.w"

typedef struct MatShip MatShip;

/*:51*//*53:*/
#line 1004 "./ai.w"

typedef struct MatMovingObj MatMovingObj;

/*:53*//*55:*/
#line 1031 "./ai.w"

typedef struct MatUniverse MatUniverse;

/*:55*//*58:*/
#line 1070 "./ai.w"

typedef struct AIInstruction AIInstruction;

/*:58*/
#line 5 "./ai.w"

/*52:*/
#line 993 "./ai.w"

struct MatShip
{
char*name;
MatMovingObj*ship;
MatShip*next;
};

/*:52*//*54:*/
#line 1018 "./ai.w"

struct MatMovingObj
{
int pos_x[2];
int pos_y[2];
int ang[2];

MatMovingObj*next;
MatMovingObj*prev;
};

/*:54*//*56:*/
#line 1046 "./ai.w"


struct MatUniverse
{
int size_x,size_y;

int read;

unsigned long frames;

MatMovingObj*ship_read;

MatShip*ship_hash[MAT_SHIP_HASH_SIZE];

MatMovingObj*ship_list_head;
MatMovingObj*ship_list_tail;
};

/*:56*//*59:*/
#line 1074 "./ai.w"


struct AIInstruction
{
int code;
int arg1;
int arg2;
int arg3;
AIInstruction*next;
};

/*:59*/
#line 6 "./ai.w"

/*4:*/
#line 62 "./ai.w"

unsigned long fhash(char*name);

/*:4*//*7:*/
#line 86 "./ai.w"

void input_process_initial(unsigned int c);
void input_process_close(unsigned int c);
void input_process_string(unsigned int c);
void input_process_number(unsigned int c);
void input_process_default(unsigned int c);
void input_process_joinfail(unsigned int c);
void input_process_frame(unsigned int c);

/*:7*//*8:*/
#line 104 "./ai.w"


void input_process_shiprm_un(void);
void input_process_shiprm_name(void);
void input_process_frame_ships(void);
void input_process_shipname(void);
void input_process_mmperror(void);
void input_process_syserror(void);
void input_process_connect_server_id(void);
void input_process_connect_server_version(void);
void input_process_frame_ships_name(void);
void input_process_frame_ships_x(void);
void input_process_frame_ships_y(void);
void input_process_frame_ships_ang(void);
void input_process_shipadd_other_un(void);
void input_process_shipadd_other_name(void);

/*:8*//*64:*/
#line 1170 "./ai.w"

void assert_exit(void);

/*:64*/
#line 7 "./ai.w"

/*2:*/
#line 17 "./ai.w"


char screen_buffer[AI_SCREEN_HEIGHT*AI_SCREEN_WIDTH];

char*program_name;

FILE*mat_server_in;
FILE*mat_server_out;

void(*input_process)(unsigned int)= input_process_initial;

void(*input_process_done)(void);

char*input_string;
int input_string_siz;
int input_string_len;

int input_number;
int input_number_bytes;

/*:2*//*43:*/
#line 782 "./ai.w"


char*arg_host= "localhost";
int arg_port= 7793;

char*arg_src= NULL;

/*:43*//*57:*/
#line 1065 "./ai.w"

MatUniverse*mat_universe= NULL;

/*:57*/
#line 8 "./ai.w"

/*3:*/
#line 39 "./ai.w"

unsigned long
fhash(char*name)
{
unsigned long h= 0;
unsigned long g;

ASSERT(name);



while(*name)
{
h= (h<<4)+tolower(*name++);
if((g= h&0xF0000000))
h^= g>>24;
h&= ~g;
}

return h;
}

/*:3*//*9:*/
#line 127 "./ai.w"

void
input_process_close(unsigned int c)
{
switch(c)
{
case MMP_SERVER_CLOSE_SYSERROR:
input_process= input_process_string;
input_process_done= input_process_syserror;
break;

case MMP_SERVER_CLOSE_MMPERROR:
input_process= input_process_string;
input_process_done= input_process_mmperror;
break;

case MMP_SERVER_CLOSE_SHUTDOWN:
fprintf(stderr,"%s: Server is being shutdown.\n",program_name);
exit(EXIT_FAILURE);
break;

case MMP_SERVER_CLOSE_CLIENT:
fprintf(stderr,"%s: Server is closing the connection.\n",program_name);
exit(EXIT_FAILURE);
break;
}
}

/*:9*//*10:*/
#line 157 "./ai.w"

void
input_process_syserror(void)
{
fprintf(stderr,"%s: Server error: %s\n",program_name,input_string);
exit(EXIT_FAILURE);
}

/*:10*//*11:*/
#line 167 "./ai.w"

void
input_process_mmperror(void)
{
fprintf(stderr,"%s: Server reported violation of MMP: %s\n",program_name,input_string);
exit(EXIT_FAILURE);
}

/*:11*//*12:*/
#line 178 "./ai.w"

void
input_process_initial(unsigned int c)
{
switch(c)
{
case MMP_SERVER_INITIAL_FULL:
/*13:*/
#line 205 "./ai.w"

{
fprintf(stderr,"%s: Server full\n",program_name);
exit(EXIT_FAILURE);
}

/*:13*/
#line 185 "./ai.w"
;
break;

case MMP_SERVER_CLOSE:
input_process= input_process_close;
break;

case MMP_SERVER_INITIAL_CONNECTED:
/*14:*/
#line 214 "./ai.w"

{
input_string= NULL;
input_string_len= 0;
input_string_siz= 0;

input_process= input_process_string;
input_process_done= input_process_connect_server_id;
}

/*:14*/
#line 193 "./ai.w"
;
break;

default:
fprintf(stderr,"Unknown message: [msg:%d][state:Initial]\n",c);
break;
}
}

/*:12*//*15:*/
#line 225 "./ai.w"

void
input_process_string(unsigned int c)
{
if(input_string_len==input_string_siz)
/*16:*/
#line 239 "./ai.w"

{
input_string_siz= input_string_siz?input_string_siz*2:256;
input_string= realloc(input_string,input_string_siz+1);
if(!input_string)
{
fprintf(stderr,"%s: realloc: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
}

/*:16*/
#line 230 "./ai.w"


input_string[input_string_len++]= c;

if(c==0)
input_process_done();
}

/*:15*//*17:*/
#line 252 "./ai.w"

void
input_process_connect_server_id()
{
printf("Server: %s\n",input_string?input_string:"");

free(input_string);

input_string= NULL;
input_string_len= 0;
input_string_siz= 0;

input_process= input_process_string;
input_process_done= input_process_connect_server_version;
}

/*:17*//*18:*/
#line 270 "./ai.w"

void
input_process_connect_server_version()
{
input_process= input_process_default;

printf("Server version: %s\n",input_string?input_string:"Unknown");

free(input_string);

fprintf(mat_server_out,"%c%c%c",MMP_CLIENT_DEFAULT_JOIN,0,0);
fflush(mat_server_out);
}

/*:18*//*19:*/
#line 286 "./ai.w"

void
input_process_default(unsigned int c)
{

switch(c)
{
case MMP_SERVER_DEFAULT_JOIN_OK:
/*33:*/
#line 537 "./ai.w"

{
input_string= NULL;
input_string_len= 0;
input_string_siz= 0;

/*34:*/
#line 550 "./ai.w"

{
int i;

mat_universe= malloc(sizeof(MatUniverse));
if(!mat_universe)
{
fprintf(stderr,"%s: malloc: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

for(i= 0;i<MAT_SHIP_HASH_SIZE;i++)
mat_universe->ship_hash[i]= NULL;

mat_universe->read= 0;

mat_universe->ship_list_head= NULL;
mat_universe->ship_list_tail= NULL;

mat_universe->size_x= 1200;
mat_universe->size_y= 1000;
}

/*:34*/
#line 543 "./ai.w"
;

input_process= input_process_string;
input_process_done= input_process_shipname;
}

/*:33*/
#line 294 "./ai.w"
;
break;

case MMP_SERVER_DEFAULT_JOIN_FAIL:
input_process= input_process_joinfail;
break;

case MMP_SERVER_CLOSE:
input_process= input_process_close;
break;

case MMP_SERVER_DEFAULT_SHIPADD_CLIENT:
/*26:*/
#line 405 "./ai.w"

{
static int current= 0;
char*buffer;

buffer= malloc(9);
if(!buffer)
{
fprintf(stderr,"%s: malloc: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

sprintf(buffer,"AI%d",current++);

printf("Added a ship to the universe.\n");
REGISTER_SHIP_HEAD(strdup(buffer));
}

/*:26*/
#line 306 "./ai.w"
;
break;

case MMP_SERVER_DEFAULT_SHIPADD_OTHER:
/*23:*/
#line 366 "./ai.w"

{
input_number= 0;
input_number_bytes= 2;

input_process= input_process_number;
input_process_done= input_process_shipadd_other_un;
}

/*:23*/
#line 310 "./ai.w"
;
break;

case MMP_SERVER_DEFAULT_FRAME_SHIPS:
input_process= input_process_number;
input_process_done= input_process_frame_ships;

input_number= 0;
input_number_bytes= 2;
break;

case MMP_SERVER_DEFAULT_SHIPRM:
/*20:*/
#line 332 "./ai.w"

{
input_process= input_process_number;
input_process_done= input_process_shiprm_un;

input_number= 0;
input_number_bytes= 2;
}

/*:20*/
#line 322 "./ai.w"
;
break;

default:
fprintf(stderr,"Unknown message: [msg:%d][state:Default]\n",c);
exit(EXIT_FAILURE);
}
}

/*:19*//*21:*/
#line 342 "./ai.w"

void
input_process_shiprm_un(void)
{
input_process= input_process_string;
input_process_done= input_process_shiprm_name;

input_string= NULL;
input_string_len= 0;
input_string_siz= 0;
}

/*:21*//*22:*/
#line 355 "./ai.w"

void
input_process_shiprm_name(void)
{
input_process= input_process_default;
VERBOSE("Remove ship: %s\n",input_string);
REMOVE_SHIP(input_string);
free(input_string);
}

/*:22*//*24:*/
#line 376 "./ai.w"

void
input_process_shipadd_other_un(void)
{
ASSERT(input_number==0);

input_string= NULL;
input_string_len= 0;
input_string_siz= 0;

input_process= input_process_string;
input_process_done= input_process_shipadd_other_name;
}

/*:24*//*25:*/
#line 391 "./ai.w"

void
input_process_shipadd_other_name(void)
{
ASSERT(input_string);

REGISTER_SHIP_HEAD(input_string);

VERBOSE("Adding ship: %s\n",input_string);

input_process= input_process_default;
}

/*:25*//*27:*/
#line 425 "./ai.w"

void
input_process_number(unsigned int c)
{
ASSERT(input_number_bytes> 0);

ASSERT(0<=c);
ASSERT(c<=255);

input_number= input_number*255+c;

if(input_number_bytes==1)
input_process_done();
else
input_number_bytes--;
}

/*:27*//*28:*/
#line 443 "./ai.w"

void
input_process_frame_ships(void)
{
if(!mat_universe->ship_list_head)
input_process= input_process_frame;
else
{
input_process= input_process_number;
input_process_done= input_process_frame_ships_x;

input_number= 0;
input_number_bytes= 2;

mat_universe->ship_read= mat_universe->ship_list_head;
}
}

/*:28*//*29:*/
#line 462 "./ai.w"

void
input_process_frame_ships_x(void)
{
mat_universe->ship_read->pos_x[mat_universe->read]= input_number;

input_process= input_process_number;
input_process_done= input_process_frame_ships_y;

input_number= 0;
input_number_bytes= 2;
}

/*:29*//*30:*/
#line 476 "./ai.w"

void
input_process_frame_ships_y(void)
{
mat_universe->ship_read->pos_y[mat_universe->read]= input_number;

input_process= input_process_number;
input_process_done= input_process_frame_ships_ang;

input_number= 0;
input_number_bytes= 2;
}

/*:30*//*31:*/
#line 490 "./ai.w"

void
input_process_frame_ships_ang(void)
{
mat_universe->ship_read->ang[mat_universe->read]= input_number;

VERBOSE("[x:%d][y:%d][ang:%d]\n",
mat_universe->ship_read->pos_x[mat_universe->read],
mat_universe->ship_read->pos_y[mat_universe->read],
mat_universe->ship_read->ang[mat_universe->read]);

if(!mat_universe->ship_read->next)
{
VERBOSE("Done\n");
input_process= input_process_frame;
}
else
{
input_process= input_process_number;
input_process_done= input_process_frame_ships_x;

input_number= 0;
input_number_bytes= 2;

mat_universe->ship_read= mat_universe->ship_read->next;
}
}

/*:31*//*32:*/
#line 519 "./ai.w"

void
input_process_frame(unsigned int c)
{
switch(c)
{
case MMP_SERVER_FRAME_DONE:
input_process= input_process_default;
break;
default:
fprintf(stderr,"Unknown message: [msg:%d][state:Frame]\n",c);
exit(EXIT_FAILURE);
}
}

/*:32*//*35:*/
#line 575 "./ai.w"

void
input_process_shipname(void)
{
if(!input_string||!*input_string)
/*37:*/
#line 706 "./ai.w"

{
input_process= input_process_default;

printf("Successfully joined default universe.\n");

fprintf(mat_server_out,"%c%c%c%s%c",MMP_CLIENT_DEFAULT_SHIPADD,0,0,"AICode",0);
fflush(mat_server_out);
}

/*:37*/
#line 580 "./ai.w"

else
{
REGISTER_SHIP_TAIL(input_string);

input_string= NULL;
input_string_len= 0;
input_string_siz= 0;

input_process= input_process_string;
input_process_done= input_process_shipname;
}
}

/*:35*//*38:*/
#line 718 "./ai.w"

void
input_process_joinfail(unsigned int c)
{
switch(c)
{
case MMP_SERVER_JOINFAIL_UNEXISTANT:
fprintf(stderr,"%s: Default universe not available\n",program_name);
break;

default:
fprintf(stderr,"Unknown message: [msg:%d][state:JoinFail]\n",c);
break;
}
exit(EXIT_FAILURE);
}

/*:38*//*65:*/
#line 1176 "./ai.w"

void assert_exit(void)
{
exit(-1);
}

/*:65*/
#line 9 "./ai.w"

/*5:*/
#line 66 "./ai.w"

int
main(int argc,char**argv)
{
/*40:*/
#line 753 "./ai.w"

{
/*41:*/
#line 767 "./ai.w"

{
program_name= strrchr(argv[0],'/');
if(program_name)
program_name++;
else
program_name= argv[0];
}

/*:41*/
#line 755 "./ai.w"
;
/*44:*/
#line 790 "./ai.w"

{
int iterate= 1;
int show_help= 0;
int show_version= 0;

while(iterate)
{
int oi= 0;
static struct option lopt[]= 
{
{"help",no_argument,NULL,'h'},
{"version",no_argument,NULL,'v'},
{"host",required_argument,NULL,1},
{"port",required_argument,NULL,2},
{0,0,0,0}
};

switch(getopt_long(argc,argv,"hvm:bW:H:x:y:l:A:t:p::",lopt,&oi))
{
case-1:
iterate= 0;
break;
case'h':
show_help= 1;
break;
case'v':
show_version= 1;
break;
case 1:
arg_host= optarg;
break;
case 2:
arg_port= atoi(optarg);
break;
default:
printf("Try '%s --help' for more information.\n",program_name);
exit(EXIT_FAILURE);
}
}

if(show_help)
{
printf("Usage: %s [OPTION]... [FILE]\n"
"Execute a Matanza Artificial Inteligence from FILE\n\n"
"  -h, --help                  Show this information and exit\n"
"  -v, --version               Show version number and exit\n"
"  --host=HOST                 Connect to HOST\n"
"  --port=NUM                  Use TCP port NUM\n"
"\n"
"Report bugs to <bachue@bachue.com>\n",program_name);
exit(EXIT_SUCCESS);

}

if(show_version)
{
printf("Freaks Unidos' %s %s\n"
"Copyright (C) 2000 Alejandro Forero Cuervo\n"
"Report any bugs to <bachue@bachue.com>\n"
"Check <http://bachue.com/matanza> for updates\n",
PACKAGE,VERSION);
exit(EXIT_SUCCESS);
}
}

/*:44*/
#line 756 "./ai.w"
;
/*42:*/
#line 777 "./ai.w"

{
}

/*:42*/
#line 757 "./ai.w"
;
/*45:*/
#line 859 "./ai.w"

{
struct sockaddr_in addr;
struct hostent*host= NULL;
int i= 0;
int fd;

/*49:*/
#line 943 "./ai.w"

{

memset(&addr,0,sizeof(struct sockaddr_in));
addr.sin_addr.s_addr= inet_addr(arg_host);
if(addr.sin_addr.s_addr!=-1)
addr.sin_family= AF_INET;
else
{
host= gethostbyname(arg_host);
if(!host)
{
#if HAVE_HSTRERROR
fprintf(stderr,"%s: %s: %s\n",program_name,arg_host,hstrerror(errno));
#else
fprintf(stderr,"%s: %s: Host not found\n",program_name,arg_host);
#endif
exit(EXIT_FAILURE);
}

addr.sin_family= host->h_addrtype;
memmove((caddr_t)&addr.sin_addr,host->h_addr_list[0],host->h_length);
}

addr.sin_port= htons(arg_port);
}

/*:49*/
#line 866 "./ai.w"
;


fd= socket(AF_INET,SOCK_STREAM,0);
if(fd<0)
{
fprintf(stderr,"%s: socket: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}


while(connect(fd,&addr,sizeof(struct sockaddr_in))==-1)
if(errno!=EINTR)
{
if(!host||!host->h_addr_list[++i])
{
fprintf(stderr,"%s: %s: %s\n",program_name,arg_host,strerror(errno));
exit(EXIT_FAILURE);
}

memmove((caddr_t)&addr.sin_addr,host->h_addr_list[i],host->h_length);
}

/*47:*/
#line 904 "./ai.w"

{
int opts;

opts= fcntl(fd,F_GETFL);
if(opts<0)
{
fprintf(stderr,"%s: fcntl: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

opts= (opts|O_NONBLOCK);
if(fcntl(fd,F_SETFL,opts)<0)
{
fprintf(stderr,"%s: fcntl: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
}

/*:47*/
#line 889 "./ai.w"
;
/*48:*/
#line 925 "./ai.w"

{
mat_server_in= fdopen(fd,"r");
if(!mat_server_in)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

mat_server_out= fdopen(fd,"w");
if(!mat_server_out)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
}

/*:48*/
#line 890 "./ai.w"
;
/*46:*/
#line 895 "./ai.w"

{
fprintf(mat_server_out,"%c%s%c%s%c",MMP_CLIENT_INITIAL_ID,
PACKAGE" - Artificial Inteligence System",0,VERSION,0);
fflush(mat_server_out);
}

/*:46*/
#line 891 "./ai.w"
;
}

/*:45*/
#line 758 "./ai.w"
;
}

/*:40*/
#line 70 "./ai.w"
;

while(1)
{
/*39:*/
#line 737 "./ai.w"

{
int read;

while((read= getc(mat_server_in))!=EOF)
{

input_process((unsigned int)read);
}
}

/*:39*/
#line 74 "./ai.w"
;
usleep(10000);
}
}

/*:5*/
#line 10 "./ai.w"


/*:1*/
