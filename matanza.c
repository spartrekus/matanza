#define MY_STATE_WILL 0x01
#define MY_WANT_STATE_WILL 0x02
#define MY_STATE_DO 0x04
#define MY_WANT_STATE_DO 0x08 \

#define MAXCHATBUFFERLEN 60 \

#define MAXMESSAGES 5
#define MAXMESSAGELEN 80 \

#define MAT_CONNECTION_SHIP_HASH_SIZE 13 \

#define MAX_UNIVERSE_NAME 32
#define MAT_UNIVERSE_MAX 256 \

#define MAT_TEAM_MAX 8
#define MAT_TEAM_BLANK "        " \

#define MAT_STATE_REMOVE 1
#define MAT_STATE_PREPARE 2
#define MAT_STATE_NORMAL 3
#define MAT_STATE_PLAYING 4
#define MAT_STATE_MACHINE 5 \

#define MAT_USER_MAX 8
#define MAT_USER_BLANK "        " \

#define MAT_MOVING_OBJ_REF(sh)  \
sh->refs++; \

#define MAT_UNIVERSES_HASH_SIZE 1 \

#define MAT_UNIVERSES_FIND(xr,xid)  \
for(xr= mat_universes[xid%MAT_UNIVERSES_HASH_SIZE];xr&&xr->id!=xid;xr= xr->next_hash) ; \

#define MAT_UNIVERSES_ADD(un)  \
{ \
int i; \
 \
un->id= mat_universes_count++; \
 \
i= un->id%MAT_UNIVERSES_HASH_SIZE; \
 \
un->next_hash= mat_universes[i]; \
mat_universes[i]= un; \
} \

#define MAT_PASSWORD_MAX 8
#define MAT_PASSWORD_BLANK "        " \

#define MAT_BACKGROUND_DOTS 1
#define MAT_BACKGROUND_IMG 2 \

#define MAT_IMGWIDTH_DEFAULT 80*4
#define MAT_IMGHEIGHT_DEFAULT 24*4 \

#define STEPS_MOVEMENT 10 \

#define REMOVE_QUEUE_ADD(obj)  \
{ \
obj->rm_next= obj->un->objs_rm; \
obj->un->objs_rm= obj; \
} \

#define CHECK_HIT_BULLET(cache,bpos,opos,osize,msize)  \
{ \
cache= bpos-opos; \
 \
if(0<=cache&&cache<osize)  \
cache= cache; \
else if(msize+cache<osize)  \
cache= cache+msize; \
else \
cache= -1; \
 \
ASSERT(cache==-1||(cache>=0&&cache<osize) ) ; \
} \

#define CRASH_SHIP_DAMAGE 400 \

#define MESSAGE_CRASH_SHIP(x,y)  \
{ \
if(x->info.player.health> 0)  \
{ \
if(dmg> 0)  \
sprintf(message_get(x) ,"-=> You crashed against player %s ! [Health:%d%%]", \
y->info.player.name,HEALTH(x) ) ; \
} \
else \
{ \
int sent_out; \
MatMovingObj*i; \
 \
PLAYER_DEAD_REGISTER(sent_out,x) ; \
 \
for(i= x->un->players_head;i;i= i->nexttype)  \
if(arg_teams_count> 0)  \
{ \
sprintf(message_get(i) , \
"-=> BOOM ! %s of %s died in crash against %s of %s.", \
x->info.player.name,x->info.player.team->name, \
y->info.player.name,y->info.player.team->name) ; \
if(sent_out)  \
sprintf(message_get(i) , \
"-=> %s of %s is sent out of the game.", \
x->info.player.name,x->info.player.team->name) ; \
} \
else \
{ \
sprintf(message_get(i) , \
"-=> BOOM ! %s died in crash against %s.", \
x->info.player.name,y->info.player.name) ; \
if(sent_out)  \
sprintf(message_get(i) , \
"-=> %s is sent out of the game.", \
x->info.player.name) ; \
} \
 \
if(!sent_out)  \
{ \
MatMovingObj*o; \
 \
if(arg_teams_count&&arg_teams_share)  \
for(o= x->info.player.team->head;o;o= o->info.player.team_next)  \
sprintf(message_get(o) ,"-=> [%s] Arg, we have lost %d ships now !", \
x->info.player.team->name,x->info.player.team->times_dead) ; \
else \
sprintf(message_get(x) ,"-=> You have lost %d ships now !",x->info.player.times_dead) ; \
 \
start_game(x) ; \
} \
else \
GAME_OVER_MODE(x) ; \
} \
} \

#define RND_SP()  \
(((double) (rand() %20) ) /100.0+0.1) 
#define PLAYER_DEAD_REGISTER(sent_out,pl)  \
{ \
pl->info.player.times_dead++; \
 \
sent_out= pl->info.player.times_dead>=arg_lives; \
 \
if(arg_teams_count)  \
{ \
pl->info.player.team->times_dead++; \
 \
if(arg_teams_share&&pl->info.player.team->times_dead>=arg_lives)  \
sent_out= 1; \
} \
} \

#define GAME_OVER_MODE(x)  \
{ \
ASSERT((x) ->type==MAT_MOVING_OBJ_SHIP) ; \
ASSERT((x) ->alpha_mod==NULL) ; \
 \
(x) ->draw= 0; \
(x) ->crash= 0; \
(x) ->alpha= 0; \
(x) ->info.player.game_over= 1; \
 \
(x) ->sp= 0; \
(x) ->sp_x= (x) ->sp_y= 0; \
} \

#define TERM_CLEAR_SCREEN(con)  \
mat_printf(con,"%s",con->term->cls) ; \

#define TERM_CLEAR_IMAGE(con)  \
ASSERT(con) ; \
ASSERT(con->graph_imagebuffer) ; \
memset(con->graph_imagebuffer,0,con->graph_imgwidth*con->graph_imgheight)  \

#define TERM_HIDE_CURSOR(con)  \
mat_printf(con,"%s",con->term->cursor_hide) ; \

#define TERM_SHOW_CURSOR(con)  \
mat_printf(con,"%s",con->term->cursor_show) ; \

#define TERM_MOVE_CURSOR(con,y,x)  \
mat_printf(con,con->term->cursor_pos,y,x) ; \

#define MAT_FLUSH_ALL(con)  \
{ \
if(con->state!=MAT_STATE_MACHINE&&!con->info.t.clean)  \
{ \
con->info.t.clean= 1; \
TERM_CLEAR_SCREEN(con) ; \
memset(con->graph_textbufferold,(char) ' ',con->xwinsize*con->ywinsize) ; \
memset(con->graph_attrbufferold,(char) MAT_NORMAL,con->xwinsize*con->ywinsize) ; \
} \
mat_flush(con,0,0,con->xwinsize,con->ywinsize) ; \
} \

#define MESSAGE_FROM(con,reason)  \
MESSAGE_FROM_REAL(con,reason,0)  \

#define MESSAGE_FROM_IP(con,reason)  \
MESSAGE_FROM_REAL(con,reason,1)  \

#define MESSAGE_FROM_REAL(con,reason,showip)  \
{ \
MatMovingObj*sh; \
MatShip*pl; \
 \
for(sh= con->ship_list;sh;sh= sh->info.player.conn_list_next)  \
{ \
ASSERT(sh->type==MAT_MOVING_OBJ_SHIP) ; \
pl= &sh->info.player; \
 \
if(showip)  \
message_broadcast(sh->un,"-=> %s <%s> %s.",pl->name,pl->conn->addr,reason) ; \
else \
message_broadcast(sh->un,"-=> %s %s.",pl->name,reason) ; \
} \
} \

#define TERM_SET_CURSOR(npos_y,npos_x)  \
{ \
if(w_x==-1)  \
{ \
TERM_MOVE_CURSOR(con,npos_y+1,npos_x+1) ; \
} \
else if(npos_y==w_y&&npos_x==w_x)  \
{ \
 \
} \
else if(npos_y!=w_y)  \
{ \
if(npos_x==0&&npos_y==w_y+1)  \
mat_printf(con,"\r\n") ; \
else \
TERM_MOVE_CURSOR(con,npos_y+1,npos_x+1) ; \
} \
else \
{ \
TERMINAL_ADVANCE_CURSOR(npos_x-w_x) ; \
} \
 \
w_x= npos_x; \
w_y= npos_y; \
} \

#define TERMINAL_ADVANCE_CURSOR(length)  \
mat_printf(con,con->term->cursor_adv,length) ; \

#define SET_TERMINAL(term_type)  \
if(term_type!=term_state)  \
{ \
mat_printf(con,con->term->code[term_type]) ; \
term_state= term_type; \
} \

#define SET_TERMINAL_LEN(term_type)  \
con->term->code_len[term_type] \

#define MAT_NORMAL 0
#define MAT_DIM 1
#define MAT_BOLD 2
#define MAT_BOLDFONT 3
#define MAT_REVERSE 4
#define MAT_SPECIAL 5
#define MAT_RED 6
#define MAT_RED_BOLD 7
#define MAT_BLUE 8
#define MAT_TERM_CODES 9 \

#define CLRSCR(p)  \
memset(p->graph_imagebuffer,0,p->graph_imgwidth*p->graph_imgheight)  \

#define TEXTCLRSCR(p)  \
memset(p->graph_textbuffer,' ',p->xwinsize*p->ywinsize) , \
memset(p->graph_attrbuffer,MAT_NORMAL,p->xwinsize*p->ywinsize)  \

#define aa_validmode(x,y,params)  \
(((params) ->minwidth \
||(params) ->maxwidth \
||(params) ->width==(x)  \
||!(params) ->width)  \
&&((params) ->minheight \
||(params) ->maxheight \
||(params) ->height==(y)  \
||!(params) ->height)  \
&&((params) ->minwidth?(params->minwidth) <=(x) :1)  \
&&((params) ->minheight?(params->minheight) <=(x) :1)  \
&&((params) ->maxwidth?(params->maxwidth) >=(x) :1)  \
&&((params) ->maxheight?(params->maxheight) >=(x) :1) )  \

#define MAT_DEFAULT_PALETTE(p)  \
{ \
int i; \
 \
ASSERT(p) ; \
 \
for(i= 0;i<256;i++)  \
p->graph_palette[i]= i; \
} \

#define isset(n,i) (((i) &1<<(n) ) !=0) 
#define canset(n,i) (!isset(n,i) &&isset(n-1,i) ) 
#define MUL 8 \

#define MAT_GRAPH_DIMMUL 5.3
#define MAT_GRAPH_BOLDMUL 2.7 \

#define TABLESIZE 65536 \

#define pow2(i) ((i) *(i) )  \

#define add(i)  \
if(next[(i) ]==(i) &&last!=(i) )  \
{ \
if(last!=-1)  \
next[last]= (i) ,last= (i) ; \
else \
last= first= (i) ; \
}
#define dist(i1,i2,i3,i4,i5,y1,y2,y3,y4,y5)  \
(2*(pow2((int) (i1) -(int) (y1) )  \
+pow2((int) (i2) -(int) (y2) )  \
+pow2((int) (i3) -(int) (y3) )  \
+pow2((int) (i4) -(int) (y4) ) )  \
+pow2((int) (i5) -(int) (y5) ) )  \

#define dist1(i1,i2,i3,i4,i5,y1,y2,y3,y4,y5)  \
((pow2((int) (i1) -(int) (y1) )  \
+pow2((int) (i2) -(int) (y2) )  \
+pow2((int) (i3) -(int) (y3) )  \
+pow2((int) (i4) -(int) (y4) ) )  \
+2*pow2((int) (i5) -(int) (y5) ) )  \

#define pos(i1,i2,i3,i4)  \
(((int) (i1) <<12)  \
+((int) (i2) <<8)  \
+((int) (i3) <<4)  \
+((int) (i4) <<0) )  \

#define postoparams(pos,i1,i2,i3,i4)  \
((i1) = ((pos) >>12) ) , \
((i2) = ((pos) >>8) &15) , \
((i3) = ((pos) >>4) &15) , \
((i4) = ((pos) >>0) &15)  \

#define NCHARS (256*AA_NATTRS)  \

#define ALOWED(i,s)  \
((isgraph((i) &0xff)  \
||(((i) &0xff) ==' ')  \
||(((i) &0xff) > 160&&((s) &AA_EIGHT) )  \
||(((s) &AA_ALL) &&((i) &0xff) ) )  \
&&((s) &TOMASK(((i) >>8) ) ) )  \

#define TOMASK(i) (1<<(i) )  \

#define MAT_GRAPH_SUPPORTED (AA_NORMAL_MASK|(arg_bold?MAT_BOLD|AA_BOLD_MASK:0) )  \

#define MYLONG_MAX 0xffffffff
#define MYRAND() (((state*1103515245) +12345) &MYLONG_MAX)  \

#define MAT_GRAPH_RENDER_ALL(con)  \
mat_graph_render(con,0,0,(con) ->xwinsize,(con) ->ywinsize) ; \

#define MAT_GRAPH_RENDER_NOWIPE_ALL(con)  \
mat_graph_render_nowipe(con,0,0,(con) ->xwinsize,(con) ->ywinsize) ; \

#define DATA000(x) (((MatAnim000*) con->anim_data) ->x)  \

#define DATA001(x) (((MatAnim001*) con->anim_data) ->x)  \

#define MAXTABLE (256*5) 
#define DATA002(x) (((MatAnim002*) con->anim_data) ->x)  \

#define COLORRGB(r,g,b) (((r) *30+(g) *59+(b) *11) >>8)  \

#define FP(i) (fire_pal[j*3+i]*4)  \

#define min(x,y) ((x) <(y) ?(x) :(y) )  \

#define CALC(m)  \
(con->graph_imagebuffer+con->graph_imgwidth*(con->graph_imgheight-m) )  \

#define CALC1(y,x) (*(c+y*con->graph_imgwidth+x) )  \

#define DATAMENU(field) (((MatStateMainMenu*) con->anim_data) ->field)  \

#define MENU_STATE_DATA 0
#define MENU_STATE_KEY 1
#define MENU_STATE_KEYREAL 2 \

#define MAT_TEXTERR_MAX 29
#define MAT_TEXTERR_BLANK "                            " \

#define GET_WORLD_HE(xpl,xwi)  \
(int) ((double) xwi*CORRECTION*(double) (xpl) .imghe/(double) (xpl) .imgwi)  \

#define MAT_SHIP_VIEW_DEFAULT(s)  \
{ \
s->info.player.view= s; \
 \
s->info.player.viewers= s; \
s->info.player.view_next= s->info.player.view_prev= NULL; \
} \

#define MAT_CONNECTION_SHIP_ADD(con,s)  \
{ \
int pos; \
 \
s->info.player.conn= con; \
 \
pos= con->ship_count%MAT_CONNECTION_SHIP_HASH_SIZE; \
 \
s->info.player.conn_id= con->ship_count++; \
 \
s->info.player.conn_hash_next= con->ship_hash[pos]; \
s->info.player.conn_hash_prev= NULL; \
 \
if(con->ship_hash[pos])  \
con->ship_hash[pos]->prev= s; \
 \
con->ship_hash[pos]= s; \
 \
s->info.player.conn_list_next= con->ship_list; \
s->info.player.conn_list_prev= NULL; \
 \
if(con->ship_list)  \
con->ship_list->prev= s; \
 \
con->ship_list= s; \
} \

#define MAT_KEY_DATA 0
#define MAT_KEY_IAC 1
#define MAT_KEY_WILL 2
#define MAT_KEY_WONT 3
#define MAT_KEY_DO 4
#define MAT_KEY_DONT 5
#define MAT_KEY_SB 6
#define MAT_KEY_SE 7
#define MAT_KEY_27 8
#define MAT_KEY_79 9
#define MAT_KEY_91 10 \

#define KEY_ARROW_UP -10
#define KEY_ARROW_DOWN -11
#define KEY_ARROW_RIGHT -12
#define KEY_ARROW_LEFT -13 \

#define GOT_INPUT(con,c)  \
if(con->key_handler)  \
con->key_handler(con,c) ; \

#define MAP_EMPTY ; \

#define POS_AST(j,i)  \
(int) (j+MAT_AST_SIZE_Y/2) *MAT_AST_SIZE_X+(int) (i+MAT_AST_SIZE_X/2)  \

#define POS_MISSILE(j,i)  \
(int) (j+MAT_MISSILESIZE_Y/2) *MAT_MISSILESIZE_X+(int) (i+MAT_MISSILESIZE_X/2)  \

#define ANGLE_SPEED_MAX 1
#define PI 3.141592 \

#define POS_SHIP(j,i)  \
(int) (j+size/2) *size+(int) (i+size/2)  \

#define POS_SHIP_ORIGINAL(j,i)  \
(int) (j+MAT_SHIPSIZE_Y/2) *MAT_SHIPSIZE_X+(int) (i+MAT_SHIPSIZE_X/2)  \

#define MESSAGE_TO(con,msg)  \
{ \
MatMovingObj*sh; \
 \
for(sh= con->ship_list;sh;sh= sh->info.player.conn_list_next)  \
sprintf(message_get(sh) ,msg) ; \
} \

#define GET_SHIP(con,id)  \
con->ship_hash[id] \

#define MAT_PROTOCOL_ERROR_JOIN(m,reason)  \
{ \
mat_printf(m,"%c%c",MMP_SERVER_DEFAULT_JOIN_FAIL,reason) ; \
mat_out_flush(m) ; \
} \

#define MAT_PROTOCOL_ERROR_SHIPADD(m,reason,string)  \
{ \
mat_printf(m,"%c%c",MMP_SERVER_DEFAULT_SHIPADD_FAIL,reason) ; \
if(reason==MMP_SERVER_SHIPADDFAIL_BADNAME)  \
mat_printf(m,"%s%c",string,0) ; \
mat_out_flush(m) ; \
} \
 \

#define LIVES(ship)  \
arg_lives-((arg_teams_count&&arg_teams_share) ? \
ship->info.player.team->times_dead: \
ship->info.player.times_dead)  \

#define HEALTH(x)  \
((int) (100*(double) (x) ->info.player.health/(double) (x) ->un->health) )  \

#define SHIP_KEY_VIEW_LABEL(x)  \
{ \
if(x->info.player.view==x)  \
sprintf(message_get(x) ,"-=> Centering view around yourself.") ; \
else \
{ \
char*name= x->info.player.view->info.player.name; \
sprintf(message_get(x) ,"-=> Centering view around player %s",name) ; \
} \
} \

#define MAT_SHIP_VIEW_RM(SHIP)  \
{ \
if(SHIP->info.player.view_prev)  \
SHIP->info.player.view_prev->info.player.view_next= SHIP->info.player.view_next; \
else \
{ \
ASSERT(SHIP->info.player.view->info.player.viewers==SHIP) ; \
SHIP->info.player.view->info.player.viewers= SHIP->info.player.view_next; \
} \
 \
if(SHIP->info.player.view_next)  \
SHIP->info.player.view_next->info.player.view_prev= SHIP->info.player.view_prev; \
} \

#define CORRECTION 1.5 \

#define VISIBILITY_BROADCAST(obj)  \
{ \
MatMovingObj*i; \
char*msg; \
 \
ASSERT(obj->type==MAT_MOVING_OBJ_SHIP) ; \
 \
msg= obj->info.player.visible? \
"-=> %s appears in the middle of nowhere !": \
"-=> %s becomes invisible !"; \
 \
for(i= obj->un->players_head;i;i= i->nexttype)  \
{ \
ASSERT(i->un==obj->un) ; \
if(i!=obj&&OBJECT_INSIDE(i,obj) )  \
sprintf(message_get(i) ,msg,obj->info.player.name) ; \
} \
} \

#define NM ((p->info.player.messages_start+p->info.player.messages_count-1) %MAXMESSAGES)  \

#define DEL_MOVING_OBJ(obj)  \
{ \
if((obj) ->next)  \
(obj) ->next->prev= (obj) ->prev; \
 \
if((obj) ->prev)  \
(obj) ->prev->next= (obj) ->next; \
else \
(obj) ->un->objs= (obj) ->un->objs->next; \
} \

#define ADD_MOVING_OBJ(obj,un)  \
{ \
(obj) ->prev= NULL; \
(obj) ->next= un->objs; \
 \
if(un->objs)  \
un->objs->prev= (obj) ; \
 \
un->objs= (obj) ; \
} \

#define SEND_NUMBER(x) mat_printf(self,"%c%c",((int) x) &0xff00,((int) x) &0x00ff)  \

#define SEND_STRING(x) mat_printf(self,"%s%c",((char*) x) ,0) ; \

#define POSB()  \
(pl->messages_pos?pl->win_y_s+1:pl->win_y_e-2)  \

#define NMESG(x)  \
((pl->messages_start+x) %MAXMESSAGES)  \

#define ABS(x) ((x) >=0?(x) :-(x) )  \

#define MAXWI(p) p->info.player.world_wi/2+p->img[0].w/2
#define MAXHE(p) p->info.player.world_he/2+p->img[0].h/2 \

#define OBJECT_INSIDE(p,q)  \
(p==q \
||((ABS(q->pos_x-p->pos_x) <MAXWI(p)  \
||p->un->mapsize_x-ABS(q->pos_x-p->pos_x) <MAXWI(p) )  \
&&(ABS(q->pos_y-p->pos_y) <MAXHE(p)  \
||p->un->mapsize_y-ABS(q->pos_y-p->pos_y) <MAXHE(p) ) ) )  \

#define ADJUST_POSITION(res,pos,w,map)  \
{ \
ASSERT((int) pos>=0) ; \
ASSERT((int) pos<map) ; \
 \
ASSERT(w<map) ; \
ASSERT(w>=0) ; \
 \
res= pos+w/2; \
 \
if(res>=map)  \
res-= map; \
 \
ASSERT(res>=0) ; \
ASSERT(res<map) ; \
} \

#define LENAWAY (pl->world_wi*pl->world_wi+pl->world_he*pl->world_he) 
#define LENNEAR (pl->world_wi*pl->world_wi+pl->world_he*pl->world_he) /2 \

#define MAT_GRAPH_CORD(p,s,x,y)  \
((int) (((x) +2*(s) ->win_x_s) +((y) +2*(s) ->win_y_s) *(p) ->graph_imgwidth) )  \

#define MAT_GRAPH_DRAW(p,s,x,y,b)  \
((p) ->graph_imagebuffer[MAT_GRAPH_CORD(p,s,x,y) ]= (b) )  \

#define MAT_GRAPH_DRAW_ALPHA(p,s,x,y,b,a)  \
{ \
unsigned char*xcol= &(p) ->graph_imagebuffer[MAT_GRAPH_CORD(p,s,x,y) ]; \
 \
ASSERT(0.0<=a) ; \
ASSERT(a<=1.0) ; \
 \
ASSERT(0<=b) ; \
ASSERT(b<=255) ; \
 \
ASSERT(0<=(int) ((double) (b) *(a) +(double) *xcol*(1-(a) ) ) ) ; \
ASSERT((int) ((double) (b) *(a) +(double) *xcol*(1-(a) ) ) <=255) ; \
 \
*xcol= (char) ((double) (b) *(a) +(double) *xcol*(1-(a) ) ) ; \
} \

#define AST_ADD_RANDOMPOS(size,un)  \
{ \
ASSERT(un->mapsize_x> 0) ; \
ASSERT(un->mapsize_y> 0) ; \
 \
AST_ADD_POS(size, \
rand() %un->mapsize_x,rand() %un->mapsize_y, \
((double) ((rand() %10) -5) ) /STEPS_MOVEMENT, \
((double) ((rand() %10) -5) ) /STEPS_MOVEMENT, \
un) ; \
 \
ASSERT(un->ast_cur> 0) ; \
} \

#define AST_ADD_POS(size,x,y,sx,sy,un)  \
{ \
MatMovingObj*ast; \
 \
AST_ADD(ast,size,un) ; \
 \
ASSERT(x>=0) ; \
ASSERT(x<un->mapsize_x) ; \
 \
ASSERT(y>=0) ; \
ASSERT(y<un->mapsize_y) ; \
 \
ast->pos_x= x; \
ast->pos_y= y; \
ast->sp_x= sx; \
ast->sp_y= sy; \
} \

#define AST_ADD(ast_new,sz,unx)  \
{ \
ast_new= malloc(sizeof(MatMovingObj) ) ; \
 \
ast_new->type= MAT_MOVING_OBJ_AST; \
ast_new->rm_next= NULL; \
 \
ASSERT(mat_ast[sz]) ; \
ast_new->img= mat_ast[sz]; \
ast_new->pal= mat_ship_palette[0]; \
 \
ast_new->ang= (double) (rand() %arg_ang) ; \
ast_new->sp_ang= ((double) (rand() %arg_ang) -arg_ang/2) /(20*STEPS_MOVEMENT) ; \
 \
ast_new->info.ast.size= sz; \
ast_new->info.ast.health= mat_ast_health[sz]; \
 \
ast_new->crash= 1; \
ast_new->draw= 1; \
 \
ast_new->alpha= 1.0; \
ast_new->alpha_mod= NULL; \
 \
ast_new->un= unx; \
 \
ast_new->nexttype= unx->ast; \
ast_new->prevtype= NULL; \
 \
if(unx->ast)  \
unx->ast->prevtype= ast_new; \
 \
unx->ast= ast_new; \
 \
ADD_MOVING_OBJ(ast_new,unx) ; \
 \
unx->ast_cur++; \
 \
ASSERT(ast_new->img) ; \
} \

#define SET_CRASH_DAMAGE(obj,name)  \
{ \
char*tmp; \
tmp= xmlGetProp(doc->root,name) ; \
un->crash_damage[obj]= tmp?atoi(tmp) :0; \
} \

#define LIBXML_MULTIPLE_BOOL(type,prop,name)  \
{ \
char*tmp; \
 \
tmp= xmlGetProp(node,name) ; \
un->location[color]->prop[type]= tmp&&!strcasecmp(tmp,"yes") ; \
} \

#define LIBXML_MULTIPLE_FLOAT(type,prop,name,default)  \
{ \
char*tmp; \
 \
tmp= xmlGetProp(node,name) ; \
un->location[color]->prop[type]= tmp?atof(tmp) :default; \
} \
 \

#define MAT_UNIVERSE_LOCATIONS_SETALL(un,val)  \
{ \
int i; \
for(i= 0;i<256;i++)  \
un->location[i]= val; \
} \

#define USLEEP_SNOOZE_UNTIL(xusec)  \
{ \
bigtime_t wake_at; \
status_t status; \
 \
wake_at= system_time() +xusec; \
 \
VERBOSE("-=> snooze_until cycle\n") ; \
do \
{ \
VERBOSE("-=> snooze_until\n") ; \
status= snooze_until(wake_at,B_SYSTEM_TIMEBASE) ; \
VERBOSE("<=- snooze_until\n") ; \
} \
while(status==EINTR) ; \
VERBOSE("<=- snooze_until cycle\n") ; \
} \

#define GETMICROSECOND_SYSTEM_TIME(xx)  \
{ \
xx= (unsigned long) system_time() ; \
} \

#define GETMICROSECOND_GETTICKCOUNT(xx)  \
{ \
xx= (unsigned long) GetTickCount() *1000; \
} \

#define GETMICROSECOND_GETTIMEOFDAY(xx)  \
{ \
struct timeval st; \
 \
gettimeofday(&st,NULL) ; \
 \
xx= (unsigned long) (st.tv_sec*1000000+st.tv_usec) ; \
} \

#define NONBLOCKING_IOCTLSOCKET(result)  \
{ \
int dummy= 1; \
 \
VERBOSE("ioctlsocket [fd:%d][option:FIONBIO]\n",result) ; \
if(ioctlsocket(result,FIONBIO,&dummy) ==SOCKET_ERROR)  \
{ \
 \
fprintf(stderr,"%s: ioctlsocket: %s\n",strerror(SOCKET_ERRNO() ) ) ; \
exit(EXIT_FAILURE) ; \
} \
} \

#define NONBLOCKING_SETSOCKOPT(result)  \
{ \
char on= 1; \
VERBOSE("setsockopt [fd:%d][option:SO_NONBLOCK]\n",result) ; \
if(setsockopt(result,SOL_SOCKET,SO_NONBLOCK,(void*) &on,sizeof(char) ) ==-1)  \
{ \
fprintf(stderr,"%s: setsockopt: %s\n",program_name,strerror(errno) ) ; \
exit(EXIT_FAILURE) ; \
} \
} \

#define NONBLOCKING_FCNTL(result)  \
{ \
int opts; \
 \
VERBOSE("fcntl [fd:%d][option:O_NONBLOCK]\n",result) ; \
opts= fcntl(result,F_GETFL) ; \
if(opts<0)  \
{ \
fprintf(stderr,"%s: fcntl: %s\n",program_name,strerror(errno) ) ; \
exit(EXIT_FAILURE) ; \
} \
 \
opts= (opts|O_NONBLOCK) ; \
if(fcntl(result,F_SETFL,opts) <0)  \
{ \
fprintf(stderr,"%s: fcntl: %s\n",program_name,strerror(errno) ) ; \
exit(EXIT_FAILURE) ; \
} \
} \

#define MAT_SUB_MACHINE_HASH_SIZE 1 \

#define MAT_SUB_RM_U(s)  \
{ \
if(s->u_prev)  \
s->u_prev->u_next= s->u_next; \
else \
s->u->subs= s->u_next; \
 \
if(s->u_next)  \
s->u_next->u_prev= s->u_prev; \
} \

#define MAT_SUB_MACHINE_INIT(xm)  \
{ \
int mat_sub_machine_init= 0; \
while(mat_sub_machine_init<MAT_SUB_MACHINE_HASH_SIZE)  \
xm->info.m.subs[mat_sub_machine_init++]= NULL; \
} \

#define MAT_IMAGE_DRAW_ST(xs,xsh,xi,startx,starty,mat_stdpal,arg_bg_adj,alpha)  \
mat_image_draw(xs,xsh,xi,0,0,0,0,startx,starty,mat_stdpal,arg_bg_adj,alpha)  \

#define MAT_IMAGE_DRAW_DY(xs,xsh,xi,x,y,p,startx,starty,xadj)  \
mat_image_draw(xs,xsh,xi,x,y, \
xsh->sp_x-p->sp_x,xsh->sp_y-p->sp_y, \
startx,starty,p->pal,xadj,p->alpha)  \

#define MAT_IMAGE_REDUCTION_H(var,start,modify)  \
{ \
int blank= 1,ang,i; \
 \
for(var= start;blank;var+= modify)  \
for(ang= 0;ang<arg_ang;ang++)  \
for(i= 0;i<img[0].w;i++)  \
if(img[ang].img[var*img[ang].w+i]!=' ')  \
blank= 0,i= img[ang].w,ang= arg_ang; \
 \
var-= modify; \
} \

#define MAT_IMAGE_REDUCTION_X(var,start,modify)  \
{ \
int blank= 1,ang,i; \
 \
for(var= start;blank;var+= modify)  \
for(ang= 0;ang<arg_ang;ang++)  \
for(i= ybeg;i<yend;i++)  \
if(img[ang].img[i*img[ang].w+var]!=' ')  \
blank= 0,i= img[ang].h,ang= arg_ang; \
 \
var-= modify; \
} \

#define MAT_SMART_OBJ_ADD_WOOZKA(xun)  \
MAT_SMART_OBJ_ADD(xun,0)  \

#define MAT_SMART_OBJ_ADD_KASHKA(xun)  \
MAT_SMART_OBJ_ADD(xun,1)  \

#define MAT_SMART_OBJ_ADD(xun,xtype)  \
{ \
MatMovingObj*obj; \
obj= malloc(sizeof(MatMovingObj) ) ; \
if(!obj)  \
{ \
fprintf(stderr,"%s: %s\n",program_name,strerror(errno) ) ; \
exit(EXIT_FAILURE) ; \
} \
 \
obj->type= MAT_MOVING_OBJ_SMART; \
obj->rm_next= NULL; \
 \
obj->refs= 1; \
 \
ASSERT(mat_ast[1]) ; \
 \
obj->img= mat_ast[1]; \
obj->pal= mat_ship_palette[0]; \
 \
obj->ang= 0; \
obj->sp_ang= 0; \
 \
obj->info.smart.type= xtype; \
 \
obj->crash= 0; \
obj->draw= 1; \
 \
obj->alpha= 1; \
obj->alpha_mod= NULL; \
 \
obj->un= xun; \
 \
obj->nexttype= xun->smart_objs; \
obj->prevtype= NULL; \
 \
if(xun->smart_objs)  \
xun->smart_objs->prevtype= obj; \
 \
xun->smart_objs= obj; \
 \
obj->sp= obj->sp_x= obj->sp_y= 0; \
 \
obj->pos_x= (double) (rand() %xun->mapsize_x) ; \
obj->pos_y= (double) (rand() %xun->mapsize_y) ; \
 \
ADD_MOVING_OBJ(obj,xun) ; \
} \

/*1:*/
#line 3 "./matanza.w"

/*345:*/
#line 10615 "./matanza.w"


#ifdef WIN32
#  include <winconfig.h> 
#else 
#  ifdef HAVE_CONFIG_H
#    include <config.h> 
#  else 
#    define PACKAGE "matanza"
#    define VERSION "{Unknown-Version}"
#  endif 
#endif 

/*187:*/
#line 6610 "./matanza.w"


#include <stdarg.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <ctype.h> 
#include <fcntl.h> 
#include <stdarg.h> 
#include <math.h> 
#include <limits.h> 



#if HAVE_WINSOCK2_H
#include <winsock2.h> 
#endif

#if HAVE_WINDOWS_H
#include <windows.h> 
#endif

#if HAVE_DIRECT_H
#include <direct.h> 
#endif



#if HAVE_OS_H
#include <OS.h> 
#endif

#if HAVE_ERRORS_H
#include <Errors.h> 
#endif



#if HAVE_NETDB_H
#include <netdb.h> 
#endif

#if HAVE_UNISTD_H
#include <unistd.h> 
#endif

#if HAVE_NETINET_IN_H
#include <netinet/in.h> 
#endif

#if HAVE_ARPA_INET_H
#include <arpa/inet.h> 
#endif

#if HAVE_SYS_IOCTL_H
#include <sys/ioctl.h> 
#endif

#if HAVE_SYS_TIME_H
#include <sys/time.h> 
#endif

#if HAVE_SYS_TYPES_H
#include <sys/types.h> 
#endif

#if HAVE_SYS_SOCKET_H
#include <sys/socket.h> 
#endif

#ifdef HAVE_ARPA_TELNET_H
#include <arpa/telnet.h> 
#else
/*188:*/
#line 6699 "./matanza.w"

#define SE 240  
#define BREAK 243  
#define IP 244  
#define AO 245  
#define AYT 246  
#define SB 250  
#define WILL 251  
#define WONT 252  
#define DO 253  
#define DONT 254  
#define IAC 255  

#define TELOPT_ECHO 1 
#define TELOPT_SGA 3 
#define TELOPT_LOGOUT 18 
#define TELOPT_TTYPE 24 
#define TELOPT_NAWS 31 
#define TELOPT_TSPEED 32 
#define TELOPT_LINEMODE 34 

#define LM_MODE  1
#define LM_SLC  3

#define TELQUAL_IS 0 
#define TELQUAL_SEND 1 

/*:188*/
#line 6685 "./matanza.w"

#endif






#include <xmlparse.h> 
#include <getopt.h> 
#include <shipreal.c> 
#include <mmp.h> 

/*:187*//*303:*/
#line 9691 "./matanza.w"

#if HAVE_PNG_H
#include <png.h> 
#endif

/*:303*/
#line 10628 "./matanza.w"



/*339:*/
#line 10442 "./matanza.w"

#if HAVE_SETSOCKOPT
#  ifdef SOL_SOCKET
#    ifdef SO_NONBLOCK
#      define HAVE_SETSOCKOPT_NONBLOCK 1
#    else
#      define HAVE_SETSOCKOPT_NONBLOCK 0
#    endif
#  else
#    define HAVE_SETSOCKOPT_NONBLOCK 0
#  endif
#else
#    define HAVE_SETSOCKOPT_NONBLOCK 0
#endif

#if HAVE_FCNTL
#  ifdef F_GETFL
#    ifdef F_SETFL
#      ifdef O_NONBLOCK
#        define HAVE_FCNTL_NONBLOCK 1
#      else
#        define HAVE_FCNTL_NONBLOCK 0
#      endif
#    else
#      define HAVE_FCNTL_NONBLOCK 0
#    endif
#  else
#    define HAVE_FCNTL_NONBLOCK 0
#  endif
#else
#  define HAVE_FCNTL_NONBLOCK 0
#endif

#if HAVE_SETSOCKOPT_NONBLOCK
#  define NONBLOCKING_GENERIC(result) NONBLOCKING_SETSOCKOPT(result)
#elif HAVE_IOCTLSOCKET
#  define NONBLOCKING_GENERIC(result) NONBLOCKING_IOCTLSOCKET(result)
#elif HAVE_FCNTL_NONBLOCK
#  define NONBLOCKING_GENERIC(result) NONBLOCKING_FCNTL(result)
#else
#  error Could not find a way to implement NONBLOCKING_GENERIC.
#endif

/*:339*/
#line 10631 "./matanza.w"



/*335:*/
#line 10378 "./matanza.w"

#if HAVE_SYSTEM_TIME
#  ifdef B_SYSTEM_TIMEBASE
#    ifdef EINTR
#      define HAVE_SYSTEM_TIME_CONST 1
#    else
#      define HAVE_SYSTEM_TIME_CONST 0
#    endif
#  else
#    define HAVE_SYSTEM_TIME_CONST 0
#  endif
#else
#  define HAVE_SYSTEM_TIME_CONST 0
#endif





#if __BEOS__
#  ifndef EINTR
#    error Missing header files for BeOS: EINTR undefined
#  endif
#  ifndef B_SYSTEM_TIMEBASE
#    error Missing header files for BeOS: B_SYSTEM_TIMEBASE undefined
#  endif
#endif

#if HAVE_SYSTEM_TIME
#  define GETMICROSECOND_GENERIC(xx) GETMICROSECOND_SYSTEM_TIME(xx)
#elif HAVE_GETTIMEOFDAY
#  define GETMICROSECOND_GENERIC(xx) GETMICROSECOND_GETTIMEOFDAY(xx)
#elif HAVE_GETTICKCOUNT
#  define GETMICROSECOND_GENERIC(xx) GETMICROSECOND_GETTICKCOUNT(xx)
#else
#  error Could not find a way to implement GETMICROSECOND_GENERIC.
#endif

/*:335*/
#line 10634 "./matanza.w"



/*334:*/
#line 10369 "./matanza.w"

#if HAVE_CLOSESOCKET
#  define SOCKET_CLOSE_GENERIC(s) closesocket(s)
#else
#  define SOCKET_CLOSE_GENERIC(s) close(s)
#endif

/*:334*/
#line 10637 "./matanza.w"



/*332:*/
#line 10333 "./matanza.w"


#if HAVE_USLEEP
#  define USLEEP_GENERIC(x) \
   { VERBOSE("-=> usleep\n"); usleep(x); VERBOSE("<=- usleep\n"); }
#elif HAVE_SNOOZE_UNTIL
#  define USLEEP_GENERIC(x) USLEEP_SNOOZE_UNTIL(x)
#elif HAVE_SLEEP
#  define USLEEP_GENERIC(x) \
   { VERBOSE("-=> Sleep(%d)\n", x / 1000); Sleep(x / 1000); VERBOSE("<=- Sleep\n"); }
#else
#  error Could not find way to implement USLEEP_GENERIC.
#endif

/*:332*/
#line 10640 "./matanza.w"






#ifdef WIN32
#define MatSocketT SOCKET
#else 
#define MatSocketT int
#endif 





#ifndef WIN32
#define SOCKET_ERROR -1
#endif





#ifdef WIN32
#define SOCKET_ERRNO() WSAGetLastError()
#else
#define SOCKET_ERRNO() errno
#endif





#ifdef WIN32
#  define SOCKET_CALL_INTR WSAEINTR
#else
#  define SOCKET_CALL_INTR EINTR
#endif

#ifndef MAX
#  define MAX(x,y) ((x)> (y)?(x):(y))
#endif

#ifndef MIN
#  define MIN(x,y) ((x)<(y)?(x):(y))
#endif

/*:345*/
#line 4 "./matanza.w"

/*183:*/
#line 6570 "./matanza.w"


#if MATANZA_ASSERT
#define ASSERT(x) \
  if(!(x)) \
    fprintf(stderr, "%s:%d: ASSERT failed\n", __FILE__, __LINE__), assert_exit()

#define ASSERT_FOR(x) for(x)
#else
#define ASSERT(x)
#define ASSERT_FOR(x)
#endif

/*:183*//*244:*/
#line 8101 "./matanza.w"

#if MATANZA_ASSERT
#define MAT_SHIP_VIEW_CHECK(X) mat_ship_view_check(X)
#else
#define MAT_SHIP_VIEW_CHECK(X)
#endif

/*:244*/
#line 5 "./matanza.w"

/*355:*/
#line 10987 "./matanza.w"

typedef struct MatSub MatSub;

/*:355*//*378:*/
#line 11722 "./matanza.w"

typedef struct MatSmartObj MatSmartObj;
typedef struct MatSmartObjType MatSmartObjType;

/*:378*/
#line 6 "./matanza.w"

/*2:*/
#line 20 "./matanza.w"


#define AA_NORMAL_MASK 1 
#define AA_DIM_MASK 2
#define AA_BOLD_MASK 4
#define AA_BOLDFONT_MASK 8
#define AA_REVERSE_MASK 16
#define AA_ALL 128
#define AA_EIGHT 256
#define AA_EXTENDED (AA_ALL|AA_EIGHT)

#define AA_ERRORDISTRIB 1 
#define AA_FLOYD_S 2
#define AA_DITHERTYPES 3

#define AA_NATTRS 5
#define AA_NPARAMS 5

struct parameters{
unsigned int p[AA_NPARAMS];
};

typedef struct aa_font aa_font;
struct aa_font{
unsigned char*data;
int height;
char*name;
char*shortname;
};

struct aa_hardware_params{
struct aa_font*font;
int supported;
int minwidth,minheight;
int maxwidth,maxheight;
int recwidth,recheight;
int mmwidth,mmheight;
int width,height;
};

typedef struct MatTerm MatTerm;
typedef struct MatLocation MatLocation;
typedef struct MatTeam MatTeam;
typedef struct MatShip MatShip;
typedef struct MatMovingObj MatMovingObj;
typedef struct MatImage MatImage;
typedef struct MatUniverse MatUniverse;
typedef struct MatConnection MatConnection;

/*379:*/
#line 11727 "./matanza.w"


struct MatSmartObjType
{
char*name;
MatImage*img;
void(*function)(MatMovingObj*obj);
};

struct MatSmartObj
{
int type;
};

/*:379*/
#line 69 "./matanza.w"

/*356:*/
#line 11003 "./matanza.w"

struct MatSub
{
MatConnection*m;

MatSub*m_prev;
MatSub*m_next;

MatUniverse*u;

MatSub*u_prev;
MatSub*u_next;
};

/*:356*/
#line 70 "./matanza.w"

/*357:*/
#line 11030 "./matanza.w"

typedef MatSub*MatSubMachine[MAT_SUB_MACHINE_HASH_SIZE];

/*:357*/
#line 71 "./matanza.w"

/*3:*/
#line 82 "./matanza.w"


struct MatTerm
{
char*code[MAT_TERM_CODES];
int code_len[MAT_TERM_CODES];

char*cls;

char*cursor_hide;
char*cursor_show;
char*cursor_pos;
char*cursor_adv;
};

/*:3*/
#line 72 "./matanza.w"

/*7:*/
#line 297 "./matanza.w"

struct MatTeam
{
int max;
int cur;

int times_dead;

char*name;

MatMovingObj*head;

MatTeam*next;
MatTeam*prev;
};

/*:7*/
#line 73 "./matanza.w"

/*8:*/
#line 330 "./matanza.w"

struct MatShip
{
char name[MAT_USER_MAX+1];

/*9:*/
#line 405 "./matanza.w"

MatConnection*conn;
int conn_id;
MatMovingObj*conn_hash_next;
MatMovingObj*conn_hash_prev;
MatMovingObj*conn_list_next;
MatMovingObj*conn_list_prev;

/*:9*//*10:*/
#line 420 "./matanza.w"

MatMovingObj*view;

/*:10*//*11:*/
#line 431 "./matanza.w"

MatMovingObj*viewers;
MatMovingObj*view_next;
MatMovingObj*view_prev;

/*:11*/
#line 335 "./matanza.w"


MatTeam*team;
MatMovingObj*team_next;

int health;

int visible;
int visible_exp;

int bullets_expire;
int ship_bullets[4];

int ship_speed_inc;

char chat_buffer[MAXCHATBUFFERLEN+1];
int chat_buffer_len;

int times_dead;


int game_over;

int messages_count;
int messages_start;
char messages[MAXMESSAGES][MAXMESSAGELEN];
int messages_expire[MAXMESSAGES];
int messages_pos;
int messages_enabled;



int win_x_s;
int win_x_e;
int win_y_s;
int win_y_e;


int imgwi;
int imghe;


int world_wi;
int world_he;
};

/*189:*/
#line 6728 "./matanza.w"

struct MatImage
{
int h,w;
unsigned char*img;
};

/*:189*/
#line 381 "./matanza.w"

/*190:*/
#line 6742 "./matanza.w"


typedef struct MatBullet MatBullet;

struct MatBullet
{
int expires;
int bright;

MatMovingObj*src;

int type;
};

/*:190*/
#line 382 "./matanza.w"

/*293:*/
#line 9474 "./matanza.w"


typedef struct MatAst MatAst;

struct MatAst
{
int size;
int health;
};

/*:293*/
#line 383 "./matanza.w"


typedef struct MatFont MatFont;

struct MatFont
{
int width,height;
char*data;
};

/*:8*/
#line 74 "./matanza.w"

/*12:*/
#line 437 "./matanza.w"


#define MAT_MOVING_OBJ_SHIP       0
#define MAT_MOVING_OBJ_BULLET     1
#define MAT_MOVING_OBJ_AST        2
#define MAT_MOVING_OBJ_SMART      3

#define MAT_MOVING_OBJ_MOVE_NORMAL 1
#define MAT_MOVING_OBJ_MOVE_DEAD   2

struct MatMovingObj
{
/*13:*/
#line 531 "./matanza.w"

int refs;

/*:13*//*395:*/
#line 12115 "./matanza.w"

double alpha;
void(*alpha_mod)(MatMovingObj*);

/*:395*/
#line 449 "./matanza.w"


MatUniverse*un;


int draw;


int crash;




double pos_x;
double pos_y;

MatImage*img;



double sp_x;
double sp_y;
double sp;

double tmp_sp_x;
double tmp_sp_y;



double ang;
double sp_ang;

unsigned char*pal;

MatMovingObj*next;
MatMovingObj*prev;

MatMovingObj*nexttype;
MatMovingObj*prevtype;












MatMovingObj*rm_next;

int type;

union
{
MatShip player;
MatBullet bullet;
MatAst ast;
MatSmartObj smart;
}info;
};

/*:12*/
#line 75 "./matanza.w"

/*5:*/
#line 198 "./matanza.w"


struct MatUniverse
{
int id;


MatUniverse*next_hash;

MatMovingObj*players_head;
MatMovingObj*players_tail;
int players_real;

MatSub*subs;

int updates;

int crash_damage[3];


char name[MAX_UNIVERSE_NAME];
char*path;

MatMovingObj*bullets;

MatMovingObj*smart_objs;

MatMovingObj*ast;
int ast_cur;

int pause;



MatLocation*location[256];


int health;


int mapsize_x;
int mapsize_y;


int dots;

MatMovingObj*objs;












MatMovingObj*objs_rm;

MatImage*bg;
MatImage*mask;
};

struct MatLocation
{

int crash[3];



int health;



double move[3];
};

/*:5*/
#line 76 "./matanza.w"

/*4:*/
#line 106 "./matanza.w"


struct MatConnection
{
MatSocketT fd;
char*addr;


char*out_buf;
int out_len;
int out_siz;

int state;

MatMovingObj*ship_hash[MAT_CONNECTION_SHIP_HASH_SIZE];
MatMovingObj*ship_list;
int ship_count;

MatTerm*term;

int xwinsize;
int ywinsize;

int graph_randomval;

int graph_palette[256];

unsigned char*graph_imagebuffer;
unsigned char*graph_textbuffer;
unsigned char*graph_textbufferold;
unsigned char*graph_attrbuffer;
unsigned char*graph_attrbufferold;

int graph_imgwidth;
int graph_imgheight;

struct aa_hardware_params params;

int flags;

char terminal_name[14];
int telnet_args;
int input_state;

char*buffer;
int bufsiz;
int buflen;
int bufprc;

union
{

struct
{
int number;
int number_byte;

char*string;
int string_len;
int string_siz;
int string_maxlength;

void(*handler)(MatConnection*);

MatSubMachine subs;
}m;


struct
{
int clean;
}t;

}info;

void(*anim_func)(MatConnection*);
void*anim_data;

void(*key_handler)(MatConnection*,int);

MatConnection*next;
MatConnection*prev;
};

/*:4*/
#line 77 "./matanza.w"


/*:2*//*134:*/
#line 5064 "./matanza.w"

/*136:*/
#line 5084 "./matanza.w"


typedef struct MatAnim000 MatAnim000;

struct MatAnim000
{
int width,height;
int mode;
int colors[12];
int delay;
int next;
int pos_x,pos_y;
};

/*:136*/
#line 5065 "./matanza.w"

/*140:*/
#line 5194 "./matanza.w"


typedef struct MatAnim001 MatAnim001;

struct MatAnim001
{
double head,delta,delay;
int width,height,pos_x,pos_y;
};

/*:140*/
#line 5066 "./matanza.w"

/*144:*/
#line 5276 "./matanza.w"

typedef struct MatAnim002 MatAnim002;

struct MatAnim002
{
unsigned int table[MAXTABLE];
int height,loop,sloop;
int done,curr,text_pos;
};

/*:144*/
#line 5067 "./matanza.w"

/*148:*/
#line 5450 "./matanza.w"

typedef struct MatStateMainMenu MatStateMainMenu;

struct MatStateMainMenu
{
char buffer[2][17];
int buflen[2];

char*texterr;

int focus;
int state;

int text_pos;
int text_cur;

MatTeam*team;
};

/*:148*/
#line 5068 "./matanza.w"


/*:134*//*298:*/
#line 9587 "./matanza.w"

typedef struct MatImgWorld MatImgWorld;

struct MatImgWorld
{
MatImage*img;

char*path;

MatImgWorld*next;
MatImgWorld*prev;


};

/*:298*/
#line 7 "./matanza.w"

/*14:*/
#line 539 "./matanza.w"

void mat_moving_obj_unref(MatMovingObj*ship);

/*:14*//*24:*/
#line 787 "./matanza.w"

/*111:*/
#line 3664 "./matanza.w"

void fastscale(char*b1,char*b2,int x1,int x2,int y1,
int y2,int width1,int width2,int color);
void print(MatConnection*con,
int x,int y,int width,int height,MatFont*f,
int color,char*text);

void mat_graph_resize(MatConnection*con,
int width,
int height);

void mat_graph_pscale(MatConnection*con,
int x1,
int y1,
int x2,
int y2,
char*data,
int w,
int h,
int color);

void mat_graph_render(MatConnection*con,
int x1,
int y1,
int x2,
int y2);

/*:111*/
#line 788 "./matanza.w"

void mat_input(MatConnection*p);

/*:24*//*41:*/
#line 1289 "./matanza.w"

void ast_crash_handler(MatMovingObj*,MatMovingObj*);
void bullet_crash_handler(MatMovingObj*,MatMovingObj*);
void player_crash_handler(MatMovingObj*,MatMovingObj*);

/*:41*//*63:*/
#line 1944 "./matanza.w"

void mat_accept(MatSocketT fildes,int machine);

/*:63*//*80:*/
#line 2352 "./matanza.w"

void check_telnet_negotiation(MatConnection*p);
void mat_animation_cancel(MatConnection*p,int x);

/*:80*//*135:*/
#line 5072 "./matanza.w"

void mat_anim_000(MatConnection*);
void mat_anim_001(MatConnection*);
void mat_anim_002(MatConnection*);
void mat_mainmenu_anim(MatConnection*);

void mat_mainmenu_key(MatConnection*,int);

/*:135*//*149:*/
#line 5470 "./matanza.w"

void main_menu_begin(MatConnection*p);

/*:149*//*168:*/
#line 6269 "./matanza.w"

void mat_connection_free(MatConnection*,unsigned char,char*);

/*:168*//*186:*/
#line 6604 "./matanza.w"

void assert_exit(void);

/*:186*//*245:*/
#line 8109 "./matanza.w"

#if MATANZA_ASSERT
void mat_ship_view_check(MatUniverse*un);
#endif

/*:245*//*252:*/
#line 8260 "./matanza.w"

void ship_key_chat_start(MatConnection*);
void ship_key_chat_end(MatConnection*);

void ship_key_view_next(MatMovingObj*ship);
void ship_key_view_prev(MatMovingObj*ship);
void ship_key_zoom_out(MatMovingObj*ship);
void ship_key_zoom_in(MatMovingObj*ship);
void ship_key_stats(MatMovingObj*ship);
void ship_key_messages_clean(MatMovingObj*ship);
void ship_key_messages_view(MatMovingObj*ship);
void ship_key_chat_backspace(MatMovingObj*ship);
void ship_key_chat_wipe(MatMovingObj*ship);
void ship_key_pause(MatMovingObj*ship);
void ship_key_who(MatMovingObj*ship);
void ship_key_messages_less(MatMovingObj*ship);
void ship_key_swappos(MatMovingObj*ship);
void ship_key_up(MatMovingObj*ship);
void ship_key_down(MatMovingObj*ship);
void ship_key_left(MatMovingObj*ship);
void ship_key_right(MatMovingObj*ship);
void ship_key_visibility(MatMovingObj*ship);

void ship_key_quit(MatConnection*con,int force);
void ship_key_quit_cancel(MatConnection*con);

void ship_key_chat_add(MatMovingObj*ship,int key);

/*:252*//*260:*/
#line 8569 "./matanza.w"

int mat_bullet_new_player(MatMovingObj*p,int type,int dir);

/*:260*//*262:*/
#line 8599 "./matanza.w"


int mat_bullet_new(MatMovingObj*p,
int type,
double sp_x,
double sp_y,
double ang);

/*:262*//*290:*/
#line 9430 "./matanza.w"

void machine_update(MatConnection*self);
void draw_world(MatConnection*p);
void start_game(MatMovingObj*p);
char*message_get(MatMovingObj*p);
void message_broadcast(MatUniverse*,char*,...);

/*:290*//*291:*/
#line 9438 "./matanza.w"

void player_input_quit(MatConnection*p,int key);
void player_input_default(MatConnection*p,int key);
void player_input_buffer(MatConnection*p,int key);
void player_input_multiple(MatConnection*p,int key);

void machine_input_initial(MatConnection*p,int key);
void machine_input_default(MatConnection*p,int key);
void machine_input_string(MatConnection*m,int key);
void machine_input_number(MatConnection*m,int key);

void machine_input_arg_join(MatConnection*m);
void machine_input_arg_ship_add(MatConnection*m);
void machine_input_arg_ship_add_string(MatConnection*m);
void machine_input_arg_id_name(MatConnection*m);
void machine_input_arg_id_ver(MatConnection*m);

/*:291*//*296:*/
#line 9509 "./matanza.w"

int ast_add(int);

/*:296*//*304:*/
#line 9700 "./matanza.w"

MatImage*mat_png_load(char const*path);

/*:304*//*342:*/
#line 10532 "./matanza.w"

MatSocketT mat_listen(int port);

/*:342*//*347:*/
#line 10728 "./matanza.w"

int mat_printf(MatConnection*con,
char*format,
...);

int mat_write(MatConnection*con,
void*buffer,
size_t len);

int mat_out_flush(MatConnection*con);

/*:347*//*354:*/
#line 10981 "./matanza.w"

int mat_sub_add(MatConnection*m,
MatUniverse*un);
void mat_sub_machine_rm(MatConnection*m);

/*:354*//*358:*/
#line 11040 "./matanza.w"


void mat_sub_rm(MatSub*s,
int hf);

/*:358*//*366:*/
#line 11211 "./matanza.w"


void mat_image_draw(MatConnection*self,
MatMovingObj*ship,
MatImage*img,
int x,
int y,
double sp_x,
double sp_y,
int startx,
int starty,
unsigned char*pal,
int adj,
double alpha);

void mat_image_optimize(MatImage*img);

/*:366*//*372:*/
#line 11471 "./matanza.w"

void
mat_image_draw_fast(MatConnection*self,MatMovingObj*ship,MatImage*img,
double pos_x,double pos_y,double rate_x,double rate_y,
double width,double height,unsigned char*pal);
void
mat_image_draw_alpha(MatConnection*self,MatMovingObj*ship,MatImage*img,
double pos_x,double pos_y,double rate_x,double rate_y,
double width,double height,unsigned char*pal,double alpha);

/*:372*//*381:*/
#line 11751 "./matanza.w"

void mat_object_woozka(MatMovingObj*obj);
void mat_object_kashka(MatMovingObj*obj);

/*:381*//*389:*/
#line 11994 "./matanza.w"


void mat_xml_start(void*data,
const char*name,
const char**atts);

void mat_xml_end(void*data,
const char*name);

/*:389*//*396:*/
#line 12120 "./matanza.w"

void mat_alpha_mod_ship_appear(MatMovingObj*s);
void mat_alpha_mod_ship_disappear(MatMovingObj*s);

/*:396*/
#line 8 "./matanza.w"

/*18:*/
#line 624 "./matanza.w"


typedef void(*MatCrashHandler)(MatMovingObj*,MatMovingObj*);

MatCrashHandler crash_handler[]= 
{
player_crash_handler,
bullet_crash_handler,
ast_crash_handler
};

/*20:*/
#line 703 "./matanza.w"


char*program_name;

int arg_compress= 1;

unsigned long arg_usleep= 100000;

int arg_bg_dots= 1;
int arg_bg_size= 0;
int arg_bg_adj= 0;
int arg_bg_color_max= -1;

int arg_max_players= 0;
int arg_bold= 0;

char*arg_ship_graphic_path= NULL;

double arg_ship_friction= 0;

int arg_imgwidth= MAT_IMGWIDTH_DEFAULT;

int arg_health= 1000;

int arg_port= 7993;
int arg_port_machine= 7793;

int arg_mapsize_x= 2000;
int arg_mapsize_y= 1600;

int arg_limits= 0;

int arg_lives= 5;

int arg_ang= 64;
int arg_chat= 1;

int arg_ppc= 1;

int arg_teams_count= 0;
int arg_teams_safe= 0;
int arg_teams_share= 1;
MatTeam*arg_teams_head= NULL;
MatTeam*arg_teams_tail= NULL;

int arg_radar= 1;
int arg_visible_init= 0;

double arg_ang_speed_max= 8.0/STEPS_MOVEMENT;
int arg_fly_back= 0;
int arg_brake= 1;
int arg_space= 1;
double arg_speed_max= 9.0/STEPS_MOVEMENT;

char*arg_password= NULL;

int arg_ast_num= 4;

/*:20*//*21:*/
#line 767 "./matanza.w"


int arg_free_at_exit= 0;

/*:21*//*22:*/
#line 776 "./matanza.w"

int arg_motion_blur= 1;

/*:22*/
#line 635 "./matanza.w"

/*6:*/
#line 278 "./matanza.w"


MatTerm term_vt100= {

{"\033[0;39m","","\033[1;39m","\033[1;39m","\033[0;7m",
"\033[0;7m","\033[0;31m","\033[1;31m","\033[0;34m"},
{7,0,7,7,6,
6,7,7,7},
"\033[2J",
"\033[?25l","\033[?25h","\033[%d;%dH","\033[%dC"
};

/*:6*/
#line 636 "./matanza.w"


MatUniverse*mat_universes[MAT_UNIVERSES_HASH_SIZE];
int mat_universes_count;

MatConnection*connections= NULL;

MatLocation mat_location_default= {{0,0,0},0,{1,1,1}};

MatFont font;


MatSocketT mat_mainsock;


MatSocketT mat_mainsock_machine;

int players_count= 0;

/*125:*/
#line 4315 "./matanza.w"



static unsigned char font16data[]= 
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x81,
0xa5,0x81,0x81,0xbd,0x99,0x81,0x81,0x7e,0x00,0x00,
0x00,0x00,0x00,0x00,0x7e,0xff,0xdb,0xff,0xff,0xc3,
0xe7,0xff,0xff,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x6c,0xfe,0xfe,0xfe,0xfe,0x7c,0x38,0x10,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x38,
0x7c,0xfe,0x7c,0x38,0x10,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x3c,0x3c,0xe7,0xe7,0xe7,0x18,
0x18,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,
0x3c,0x7e,0xff,0xff,0x7e,0x18,0x18,0x3c,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x3c,
0x3c,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,
0xff,0xff,0xff,0xff,0xe7,0xc3,0xc3,0xe7,0xff,0xff,
0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x3c,
0x66,0x42,0x42,0x66,0x3c,0x00,0x00,0x00,0x00,0x00,
0xff,0xff,0xff,0xff,0xff,0xc3,0x99,0xbd,0xbd,0x99,
0xc3,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x1e,0x0e,
0x1a,0x32,0x78,0xcc,0xcc,0xcc,0xcc,0x78,0x00,0x00,
0x00,0x00,0x00,0x00,0x3c,0x66,0x66,0x66,0x66,0x3c,
0x18,0x7e,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x3f,0x33,0x3f,0x30,0x30,0x30,0x30,0x70,0xf0,0xe0,
0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x63,0x7f,0x63,
0x63,0x63,0x63,0x67,0xe7,0xe6,0xc0,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x18,0xdb,0x3c,0xe7,0x3c,0xdb,
0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,
0xf0,0xf8,0xfe,0xf8,0xf0,0xe0,0xc0,0x80,0x00,0x00,
0x00,0x00,0x00,0x02,0x06,0x0e,0x1e,0x3e,0xfe,0x3e,
0x1e,0x0e,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x3c,0x7e,0x18,0x18,0x18,0x7e,0x3c,0x18,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,
0x66,0x66,0x66,0x00,0x66,0x66,0x00,0x00,0x00,0x00,
0x00,0x00,0x7f,0xdb,0xdb,0xdb,0x7b,0x1b,0x1b,0x1b,
0x1b,0x1b,0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,0x60,
0x38,0x6c,0xc6,0xc6,0x6c,0x38,0x0c,0xc6,0x7c,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xfe,0xfe,0xfe,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x3c,0x7e,0x18,0x18,0x18,0x7e,0x3c,0x18,0x7e,
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x3c,0x7e,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7e,
0x3c,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x18,0x0c,0xfe,0x0c,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x60,0xfe,
0x60,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xc0,0xc0,0xc0,0xfe,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,
0x66,0xff,0x66,0x24,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x38,0x38,0x7c,0x7c,0xfe,
0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xfe,0xfe,0x7c,0x7c,0x38,0x38,0x10,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x3c,0x3c,0x3c,0x18,0x18,0x18,0x00,0x18,0x18,
0x00,0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x24,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x6c,0x6c,0xfe,0x6c,0x6c,0x6c,0xfe,
0x6c,0x6c,0x00,0x00,0x00,0x00,0x18,0x18,0x7c,0xc6,
0xc2,0xc0,0x7c,0x06,0x06,0x86,0xc6,0x7c,0x18,0x18,
0x00,0x00,0x00,0x00,0x00,0x00,0xc2,0xc6,0x0c,0x18,
0x30,0x60,0xc6,0x86,0x00,0x00,0x00,0x00,0x00,0x00,
0x38,0x6c,0x6c,0x38,0x76,0xdc,0xcc,0xcc,0xcc,0x76,
0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0x60,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0c,0x18,0x30,0x30,0x30,0x30,0x30,0x30,
0x18,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x18,
0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x18,0x30,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x3c,0xff,
0x3c,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x18,0x7e,0x18,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x18,0x18,0x18,0x30,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x06,0x0c,0x18,
0x30,0x60,0xc0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x7c,0xc6,0xc6,0xce,0xde,0xf6,0xe6,0xc6,0xc6,0x7c,
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x38,0x78,0x18,
0x18,0x18,0x18,0x18,0x18,0x7e,0x00,0x00,0x00,0x00,
0x00,0x00,0x7c,0xc6,0x06,0x0c,0x18,0x30,0x60,0xc0,
0xc6,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,
0x06,0x06,0x3c,0x06,0x06,0x06,0xc6,0x7c,0x00,0x00,
0x00,0x00,0x00,0x00,0x0c,0x1c,0x3c,0x6c,0xcc,0xfe,
0x0c,0x0c,0x0c,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,
0xfe,0xc0,0xc0,0xc0,0xfc,0x06,0x06,0x06,0xc6,0x7c,
0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x60,0xc0,0xc0,
0xfc,0xc6,0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
0x00,0x00,0xfe,0xc6,0x06,0x06,0x0c,0x18,0x30,0x30,
0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,
0xc6,0xc6,0x7c,0xc6,0xc6,0xc6,0xc6,0x7c,0x00,0x00,
0x00,0x00,0x00,0x00,0x7c,0xc6,0xc6,0xc6,0x7e,0x06,
0x06,0x06,0x0c,0x78,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x18,0x18,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,
0x00,0x00,0x00,0x18,0x18,0x30,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x06,0x0c,0x18,0x30,0x60,0x30,0x18,
0x0c,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x7e,0x00,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x60,0x30,0x18,0x0c,0x06,
0x0c,0x18,0x30,0x60,0x00,0x00,0x00,0x00,0x00,0x00,
0x7c,0xc6,0xc6,0x0c,0x18,0x18,0x18,0x00,0x18,0x18,
0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,0xc6,0xc6,
0xde,0xde,0xde,0xdc,0xc0,0x7c,0x00,0x00,0x00,0x00,
0x00,0x00,0x10,0x38,0x6c,0xc6,0xc6,0xfe,0xc6,0xc6,
0xc6,0xc6,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0x66,
0x66,0x66,0x7c,0x66,0x66,0x66,0x66,0xfc,0x00,0x00,
0x00,0x00,0x00,0x00,0x3c,0x66,0xc2,0xc0,0xc0,0xc0,
0xc0,0xc2,0x66,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,
0xf8,0x6c,0x66,0x66,0x66,0x66,0x66,0x66,0x6c,0xf8,
0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x66,0x62,0x68,
0x78,0x68,0x60,0x62,0x66,0xfe,0x00,0x00,0x00,0x00,
0x00,0x00,0xfe,0x66,0x62,0x68,0x78,0x68,0x60,0x60,
0x60,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x66,
0xc2,0xc0,0xc0,0xde,0xc6,0xc6,0x66,0x3a,0x00,0x00,
0x00,0x00,0x00,0x00,0xc6,0xc6,0xc6,0xc6,0xfe,0xc6,
0xc6,0xc6,0xc6,0xc6,0x00,0x00,0x00,0x00,0x00,0x00,
0x3c,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x3c,
0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x0c,0x0c,0x0c,
0x0c,0x0c,0xcc,0xcc,0xcc,0x78,0x00,0x00,0x00,0x00,
0x00,0x00,0xe6,0x66,0x66,0x6c,0x78,0x78,0x6c,0x66,
0x66,0xe6,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x60,
0x60,0x60,0x60,0x60,0x60,0x62,0x66,0xfe,0x00,0x00,
0x00,0x00,0x00,0x00,0xc3,0xe7,0xff,0xff,0xdb,0xc3,
0xc3,0xc3,0xc3,0xc3,0x00,0x00,0x00,0x00,0x00,0x00,
0xc6,0xe6,0xf6,0xfe,0xde,0xce,0xc6,0xc6,0xc6,0xc6,
0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,0xc6,0xc6,
0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
0x00,0x00,0xfc,0x66,0x66,0x66,0x7c,0x60,0x60,0x60,
0x60,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,
0xc6,0xc6,0xc6,0xc6,0xc6,0xd6,0xde,0x7c,0x0c,0x0e,
0x00,0x00,0x00,0x00,0xfc,0x66,0x66,0x66,0x7c,0x6c,
0x66,0x66,0x66,0xe6,0x00,0x00,0x00,0x00,0x00,0x00,
0x7c,0xc6,0xc6,0x60,0x38,0x0c,0x06,0xc6,0xc6,0x7c,
0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xdb,0x99,0x18,
0x18,0x18,0x18,0x18,0x18,0x3c,0x00,0x00,0x00,0x00,
0x00,0x00,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,
0xc6,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0xc3,0xc3,
0xc3,0xc3,0xc3,0xc3,0xc3,0x66,0x3c,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0xc3,0xc3,0xc3,0xc3,0xc3,0xdb,
0xdb,0xff,0x66,0x66,0x00,0x00,0x00,0x00,0x00,0x00,
0xc3,0xc3,0x66,0x3c,0x18,0x18,0x3c,0x66,0xc3,0xc3,
0x00,0x00,0x00,0x00,0x00,0x00,0xc3,0xc3,0xc3,0x66,
0x3c,0x18,0x18,0x18,0x18,0x3c,0x00,0x00,0x00,0x00,
0x00,0x00,0xff,0xc3,0x86,0x0c,0x18,0x30,0x60,0xc1,
0xc3,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x30,
0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3c,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0x70,0x38,
0x1c,0x0e,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x00,
0x3c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x3c,
0x00,0x00,0x00,0x00,0x10,0x38,0x6c,0xc6,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x30,0x30,0x18,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x0c,0x7c,
0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,0x00,0x00,
0xe0,0x60,0x60,0x78,0x6c,0x66,0x66,0x66,0x66,0x7c,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,
0xc6,0xc0,0xc0,0xc0,0xc6,0x7c,0x00,0x00,0x00,0x00,
0x00,0x00,0x1c,0x0c,0x0c,0x3c,0x6c,0xcc,0xcc,0xcc,
0xcc,0x76,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x7c,0xc6,0xfe,0xc0,0xc0,0xc6,0x7c,0x00,0x00,
0x00,0x00,0x00,0x00,0x38,0x6c,0x64,0x60,0xf0,0x60,
0x60,0x60,0x60,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x76,0xcc,0xcc,0xcc,0xcc,0xcc,0x7c,
0x0c,0xcc,0x78,0x00,0x00,0x00,0xe0,0x60,0x60,0x6c,
0x76,0x66,0x66,0x66,0x66,0xe6,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x18,0x00,0x38,0x18,0x18,0x18,0x18,
0x18,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,
0x00,0x0e,0x06,0x06,0x06,0x06,0x06,0x06,0x66,0x66,
0x3c,0x00,0x00,0x00,0xe0,0x60,0x60,0x66,0x6c,0x78,
0x78,0x6c,0x66,0xe6,0x00,0x00,0x00,0x00,0x00,0x00,
0x38,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x3c,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xe6,
0xff,0xdb,0xdb,0xdb,0xdb,0xdb,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xdc,0x66,0x66,0x66,0x66,
0x66,0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x7c,0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xdc,0x66,0x66,
0x66,0x66,0x66,0x7c,0x60,0x60,0xf0,0x00,0x00,0x00,
0x00,0x00,0x00,0x76,0xcc,0xcc,0xcc,0xcc,0xcc,0x7c,
0x0c,0x0c,0x1e,0x00,0x00,0x00,0x00,0x00,0x00,0xdc,
0x76,0x66,0x60,0x60,0x60,0xf0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,0x60,0x38,0x0c,
0xc6,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x30,
0x30,0xfc,0x30,0x30,0x30,0x30,0x36,0x1c,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xcc,0xcc,0xcc,
0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xc3,0xc3,0xc3,0xc3,0x66,0x3c,0x18,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc3,
0xc3,0xc3,0xdb,0xdb,0xff,0x66,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xc3,0x66,0x3c,0x18,0x3c,
0x66,0xc3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0x7e,0x06,0x0c,
0xf8,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0xcc,0x18,
0x30,0x60,0xc6,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,
0x0e,0x18,0x18,0x18,0x70,0x18,0x18,0x18,0x18,0x0e,
0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x18,0x18,
0x00,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x70,0x18,0x18,0x18,0x0e,0x18,0x18,0x18,
0x18,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0xdc,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x38,0x6c,0xc6,
0xc6,0xc6,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x3c,0x66,0xc2,0xc0,0xc0,0xc0,0xc2,0x66,0x3c,0x0c,
0x06,0x7c,0x00,0x00,0x00,0x00,0xcc,0x00,0x00,0xcc,
0xcc,0xcc,0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,
0x00,0x0c,0x18,0x30,0x00,0x7c,0xc6,0xfe,0xc0,0xc0,
0xc6,0x7c,0x00,0x00,0x00,0x00,0x00,0x10,0x38,0x6c,
0x00,0x78,0x0c,0x7c,0xcc,0xcc,0xcc,0x76,0x00,0x00,
0x00,0x00,0x00,0x00,0xcc,0x00,0x00,0x78,0x0c,0x7c,
0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,0x00,0x60,
0x30,0x18,0x00,0x78,0x0c,0x7c,0xcc,0xcc,0xcc,0x76,
0x00,0x00,0x00,0x00,0x00,0x38,0x6c,0x38,0x00,0x78,
0x0c,0x7c,0xcc,0xcc,0xcc,0x76,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x3c,0x66,0x60,0x60,0x66,0x3c,
0x0c,0x06,0x3c,0x00,0x00,0x00,0x00,0x10,0x38,0x6c,
0x00,0x7c,0xc6,0xfe,0xc0,0xc0,0xc6,0x7c,0x00,0x00,
0x00,0x00,0x00,0x00,0xc6,0x00,0x00,0x7c,0xc6,0xfe,
0xc0,0xc0,0xc6,0x7c,0x00,0x00,0x00,0x00,0x00,0x60,
0x30,0x18,0x00,0x7c,0xc6,0xfe,0xc0,0xc0,0xc6,0x7c,
0x00,0x00,0x00,0x00,0x00,0x00,0x66,0x00,0x00,0x38,
0x18,0x18,0x18,0x18,0x18,0x3c,0x00,0x00,0x00,0x00,
0x00,0x18,0x3c,0x66,0x00,0x38,0x18,0x18,0x18,0x18,
0x18,0x3c,0x00,0x00,0x00,0x00,0x00,0x60,0x30,0x18,
0x00,0x38,0x18,0x18,0x18,0x18,0x18,0x3c,0x00,0x00,
0x00,0x00,0x00,0xc6,0x00,0x10,0x38,0x6c,0xc6,0xc6,
0xfe,0xc6,0xc6,0xc6,0x00,0x00,0x00,0x00,0x38,0x6c,
0x38,0x00,0x38,0x6c,0xc6,0xc6,0xfe,0xc6,0xc6,0xc6,
0x00,0x00,0x00,0x00,0x18,0x30,0x60,0x00,0xfe,0x66,
0x60,0x7c,0x60,0x60,0x66,0xfe,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x6e,0x3b,0x1b,0x7e,0xd8,
0xdc,0x77,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x6c,
0xcc,0xcc,0xfe,0xcc,0xcc,0xcc,0xcc,0xce,0x00,0x00,
0x00,0x00,0x00,0x10,0x38,0x6c,0x00,0x7c,0xc6,0xc6,
0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,
0xc6,0x00,0x00,0x7c,0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,
0x00,0x00,0x00,0x00,0x00,0x60,0x30,0x18,0x00,0x7c,
0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
0x00,0x30,0x78,0xcc,0x00,0xcc,0xcc,0xcc,0xcc,0xcc,
0xcc,0x76,0x00,0x00,0x00,0x00,0x00,0x60,0x30,0x18,
0x00,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0x76,0x00,0x00,
0x00,0x00,0x00,0x00,0xc6,0x00,0x00,0xc6,0xc6,0xc6,
0xc6,0xc6,0xc6,0x7e,0x06,0x0c,0x78,0x00,0x00,0xc6,
0x00,0x7c,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,
0x00,0x00,0x00,0x00,0x00,0xc6,0x00,0xc6,0xc6,0xc6,
0xc6,0xc6,0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,
0x00,0x18,0x18,0x7e,0xc3,0xc0,0xc0,0xc0,0xc3,0x7e,
0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x38,0x6c,0x64,
0x60,0xf0,0x60,0x60,0x60,0x60,0xe6,0xfc,0x00,0x00,
0x00,0x00,0x00,0x00,0xc3,0x66,0x3c,0x18,0xff,0x18,
0xff,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0xfc,
0x66,0x66,0x7c,0x62,0x66,0x6f,0x66,0x66,0x66,0xf3,
0x00,0x00,0x00,0x00,0x00,0x0e,0x1b,0x18,0x18,0x18,
0x7e,0x18,0x18,0x18,0x18,0x18,0xd8,0x70,0x00,0x00,
0x00,0x18,0x30,0x60,0x00,0x78,0x0c,0x7c,0xcc,0xcc,
0xcc,0x76,0x00,0x00,0x00,0x00,0x00,0x0c,0x18,0x30,
0x00,0x38,0x18,0x18,0x18,0x18,0x18,0x3c,0x00,0x00,
0x00,0x00,0x00,0x18,0x30,0x60,0x00,0x7c,0xc6,0xc6,
0xc6,0xc6,0xc6,0x7c,0x00,0x00,0x00,0x00,0x00,0x18,
0x30,0x60,0x00,0xcc,0xcc,0xcc,0xcc,0xcc,0xcc,0x76,
0x00,0x00,0x00,0x00,0x00,0x00,0x76,0xdc,0x00,0xdc,
0x66,0x66,0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00,
0x76,0xdc,0x00,0xc6,0xe6,0xf6,0xfe,0xde,0xce,0xc6,
0xc6,0xc6,0x00,0x00,0x00,0x00,0x00,0x3c,0x6c,0x6c,
0x3e,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x38,0x6c,0x6c,0x38,0x00,0x7c,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x30,0x30,0x00,0x30,0x30,0x60,0xc0,0xc6,0xc6,0x7c,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xfe,0xc0,0xc0,0xc0,0xc0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x06,0x06,0x06,
0x06,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xc0,0xc2,
0xc6,0xcc,0x18,0x30,0x60,0xce,0x9b,0x06,0x0c,0x1f,
0x00,0x00,0x00,0xc0,0xc0,0xc2,0xc6,0xcc,0x18,0x30,
0x66,0xce,0x96,0x3e,0x06,0x06,0x00,0x00,0x00,0x00,
0x18,0x18,0x00,0x18,0x18,0x18,0x3c,0x3c,0x3c,0x18,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,
0x6c,0xd8,0x6c,0x36,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xd8,0x6c,0x36,0x6c,0xd8,
0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x44,0x11,0x44,
0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,
0x11,0x44,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0xdd,0x77,
0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,
0xdd,0x77,0xdd,0x77,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xf8,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0xf8,0x18,0xf8,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x18,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xf6,
0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xfe,0x36,0x36,0x36,0x36,
0x36,0x36,0x36,0x36,0x00,0x00,0x00,0x00,0x00,0xf8,
0x18,0xf8,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x36,0x36,0x36,0x36,0x36,0xf6,0x06,0xf6,0x36,0x36,
0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0x36,0x00,0x00,0x00,0x00,0x00,0xfe,0x06,0xf6,
0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0x36,0x36,0xf6,0x06,0xfe,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x18,0x18,0x18,0x18,0xf8,0x18,0xf8,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xf8,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1f,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xff,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1f,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xff,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x1f,0x18,0x1f,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0x37,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0x36,0x36,0x36,0x36,0x37,0x30,0x3f,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x3f,0x30,0x37,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xf7,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xff,0x00,0xf7,0x36,0x36,0x36,0x36,
0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x37,
0x30,0x37,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,
0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x36,0x36,0x36,
0x36,0xf7,0x00,0xf7,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0x36,0x18,0x18,0x18,0x18,0x18,0xff,0x00,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x36,
0x36,0x36,0x36,0x36,0x36,0xff,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,
0x00,0xff,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x36,0x36,
0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0x36,0x36,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x18,0x18,0x18,0x18,0x1f,0x18,0x1f,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1f,0x18,0x1f,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x3f,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,
0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xff,0x36,0x36,
0x36,0x36,0x36,0x36,0x36,0x36,0x18,0x18,0x18,0x18,
0x18,0xff,0x18,0xff,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xf8,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x1f,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xf0,0xf0,0xf0,0xf0,
0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,
0xf0,0xf0,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,
0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,
0xdc,0xd8,0xd8,0xd8,0xdc,0x76,0x00,0x00,0x00,0x00,
0x00,0x00,0x78,0xcc,0xcc,0xcc,0xd8,0xcc,0xc6,0xc6,
0xc6,0xcc,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0xc6,
0xc6,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x6c,0x6c,0x6c,
0x6c,0x6c,0x6c,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xfe,0xc6,0x60,0x30,0x18,0x30,0x60,0xc6,0xfe,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7e,
0xd8,0xd8,0xd8,0xd8,0xd8,0x70,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x66,0x66,0x66,0x66,0x66,0x7c,
0x60,0x60,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x76,0xdc,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x7e,0x18,0x3c,0x66,0x66,
0x66,0x3c,0x18,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x38,0x6c,0xc6,0xc6,0xfe,0xc6,0xc6,0x6c,0x38,
0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x6c,0xc6,0xc6,
0xc6,0x6c,0x6c,0x6c,0x6c,0xee,0x00,0x00,0x00,0x00,
0x00,0x00,0x1e,0x30,0x18,0x0c,0x3e,0x66,0x66,0x66,
0x66,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x7e,0xdb,0xdb,0xdb,0x7e,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x03,0x06,0x7e,0xdb,0xdb,
0xf3,0x7e,0x60,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,
0x1c,0x30,0x60,0x60,0x7c,0x60,0x60,0x60,0x30,0x1c,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0xc6,0xc6,
0xc6,0xc6,0xc6,0xc6,0xc6,0xc6,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0xfe,0x00,0x00,0xfe,0x00,0x00,
0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x18,0x7e,0x18,0x18,0x00,0x00,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x30,0x18,0x0c,0x06,0x0c,
0x18,0x30,0x00,0x7e,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x0c,0x18,0x30,0x60,0x30,0x18,0x0c,0x00,0x7e,
0x00,0x00,0x00,0x00,0x00,0x00,0x0e,0x1b,0x1b,0x1b,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xd8,0xd8,
0xd8,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x18,0x00,0x7e,0x00,0x18,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x76,0xdc,0x00,
0x76,0xdc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,
0x6c,0x6c,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x0c,0x0c,
0x0c,0x0c,0x0c,0xec,0x6c,0x6c,0x3c,0x1c,0x00,0x00,
0x00,0x00,0x00,0xd8,0x6c,0x6c,0x6c,0x6c,0x6c,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,
0xd8,0x30,0x60,0xc8,0xf8,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7c,0x7c,
0x7c,0x7c,0x7c,0x7c,0x7c,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00};

struct aa_font aa_font16= 
{font16data,16,"Standard vga 8x16 font","vga16"};

/*:125*/
#line 655 "./matanza.w"


struct aa_font*graph_font= &aa_font16;
unsigned short*graph_table;
unsigned short*graph_filltable;
struct parameters*graph_parameters;

/*:18*//*182:*/
#line 6526 "./matanza.w"

static int fire_pal[]= 
{
0,0,0,0,0,6,0,0,6,0,0,7,0,0,8,0,0,8,0,0,9,0,0,10,
2,0,10,4,0,9,6,0,9,8,0,8,10,0,7,12,0,7,14,0,6,16,0,5,
18,0,5,20,0,4,22,0,4,24,0,3,26,0,2,28,0,2,30,0,1,32,0,0,
32,0,0,33,0,0,34,0,0,35,0,0,36,0,0,36,0,0,37,0,0,38,0,0,
39,0,0,40,0,0,40,0,0,41,0,0,42,0,0,43,0,0,44,0,0,45,0,0,
46,1,0,47,1,0,48,2,0,49,2,0,50,3,0,51,3,0,52,4,0,53,4,0,
54,5,0,55,5,0,56,6,0,57,6,0,58,7,0,59,7,0,60,8,0,61,8,0,
63,9,0,63,9,0,63,10,0,63,10,0,63,11,0,63,11,0,63,12,0,63,12,0,
63,13,0,63,13,0,63,14,0,63,14,0,63,15,0,63,15,0,63,16,0,63,16,0,
63,17,0,63,17,0,63,18,0,63,18,0,63,19,0,63,19,0,63,20,0,63,20,0,
63,21,0,63,21,0,63,22,0,63,22,0,63,23,0,63,24,0,63,24,0,63,25,0,
63,25,0,63,26,0,63,26,0,63,27,0,63,27,0,63,28,0,63,28,0,63,29,0,
63,29,0,63,30,0,63,30,0,63,31,0,63,31,0,63,32,0,63,32,0,63,33,0,
63,33,0,63,34,0,63,34,0,63,35,0,63,35,0,63,36,0,63,36,0,63,37,0,
63,38,0,63,38,0,63,39,0,63,39,0,63,40,0,63,40,0,63,41,0,63,41,0,
63,42,0,63,42,0,63,43,0,63,43,0,63,44,0,63,44,0,63,45,0,63,45,0,
63,46,0,63,46,0,63,47,0,63,47,0,63,48,0,63,48,0,63,49,0,63,49,0,
63,50,0,63,50,0,63,51,0,63,52,0,63,52,0,63,52,0,63,52,0,63,52,0,
63,53,0,63,53,0,63,53,0,63,53,0,63,54,0,63,54,0,63,54,0,63,54,0,
63,54,0,63,55,0,63,55,0,63,55,0,63,55,0,63,56,0,63,56,0,63,56,0,
63,56,0,63,57,0,63,57,0,63,57,0,63,57,0,63,57,0,63,58,0,63,58,0,
63,58,0,63,58,0,63,59,0,63,59,0,63,59,0,63,59,0,63,60,0,63,60,0,
63,60,0,63,60,0,63,60,0,63,61,0,63,61,0,63,61,0,63,61,0,63,62,0,
63,62,0,63,62,0,63,62,0,63,63,0,63,63,1,63,63,2,63,63,3,63,63,4,
63,63,5,63,63,6,63,63,7,63,63,8,63,63,9,63,63,10,63,63,10,63,63,11,
63,63,12,63,63,13,63,63,14,63,63,15,63,63,16,63,63,17,63,63,18,63,63,19,
63,63,20,63,63,21,63,63,21,63,63,22,63,63,23,63,63,24,63,63,25,63,63,26,
63,63,27,63,63,28,63,63,29,63,63,30,63,63,31,63,63,31,63,63,32,63,63,33,
63,63,34,63,63,35,63,63,36,63,63,37,63,63,38,63,63,39,63,63,40,63,63,41,
63,63,42,63,63,42,63,63,43,63,63,44,63,63,45,63,63,46,63,63,47,63,63,48,
63,63,49,63,63,50,63,63,51,63,63,52,63,63,52,63,63,53,63,63,54,63,63,55,
63,63,56,63,63,57,63,63,58,63,63,59,63,63,60,63,63,61,63,63,62,63,63,63
};

int fire_palette[256];

/*:182*//*185:*/
#line 6595 "./matanza.w"

#if MATANZA_VERBOSE
#define VERBOSE if (arg_verbose) printf
int arg_verbose= 0;
#else
#define VERBOSE
#endif

/*:185*//*191:*/
#line 6760 "./matanza.w"


MatImage*mat_ship;
unsigned char*mat_ship_palette[3];

MatImage*mat_ast[2];
MatImage*mat_missile[3];

/*:191*//*192:*/
#line 6770 "./matanza.w"


int mat_bullets_damage[4]= {15,100,400,3000};

double mat_bullets_speed[4]= {
8.0/STEPS_MOVEMENT,
11.0/STEPS_MOVEMENT,
14.5/STEPS_MOVEMENT,
8.0/STEPS_MOVEMENT
};

int mat_bullets_back[4]= {1,0,0,0};
int mat_bullets_bexp[4]= {20,40,200,3000};
int mat_bullets_pexp[4]= {1,3,6,10};

char*mat_bullets_name[4]= {"bullets","small missiles","missiles","torpedoes"};

char*mat_bullets_hit[4]= {
"-=> You got %s !",
"-=> Your small missile got %s !",
"-=> Bang, your missile got %s !",
"-=> BOOM, your torpedo got %s !"
};

char*mat_bullets_hit_ast[4]= {
"-=> You reached the asteroid !",
"-=> Your small missile reached the asteroid !",
"-=> Bang, your missile hit the asteroid !",
"-=> BOOM, your torpedo got the asteroid !"
};

/*:192*//*277:*/
#line 9082 "./matanza.w"

unsigned char mat_stdpal[256]= {
0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,
100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,
120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,
140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,
180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,
200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,
220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};

/*:277*//*294:*/
#line 9486 "./matanza.w"


int mat_ast_health[]= {500,300};

/*:294*//*299:*/
#line 9604 "./matanza.w"

MatImgWorld*mat_bg_head= NULL;
MatImgWorld*mat_bg_tail= NULL;

MatImgWorld*mat_fg_head= NULL;
MatImgWorld*mat_fg_tail= NULL;

/*:299*//*363:*/
#line 11159 "./matanza.w"


static double*mat_cos;
static double*mat_sin;

/*:363*//*380:*/
#line 11742 "./matanza.w"


MatSmartObjType mat_objects[]= 
{
{"Woozka",NULL,&mat_object_woozka},
{"Kashka",NULL,&mat_object_kashka}
};

/*:380*/
#line 9 "./matanza.w"

/*15:*/
#line 543 "./matanza.w"

void
mat_moving_obj_unref(MatMovingObj*ship)
{
ASSERT(ship->refs> 0);

ship->refs--;
if(ship->refs==0)
{
MAT_SHIP_VIEW_CHECK(ship->un);

MAT_SHIP_VIEW_RM(ship);
/*17:*/
#line 594 "./matanza.w"

{
MatMovingObj*i= ship->info.player.viewers;

while(i)
{
MatMovingObj*tmp= i->info.player.view_next;

ASSERT(i!=ship);

sprintf(message_get(i),"-=> Zip.  %s disappears.",ship->info.player.name);

i->info.player.view= i;

if(i->info.player.viewers)
i->info.player.viewers->info.player.view_prev= i;

i->info.player.view_prev= NULL;
i->info.player.view_next= i->info.player.viewers;

i->info.player.viewers= i;

i= tmp;
}
}

/*:17*/
#line 555 "./matanza.w"
;

ship->un->players_real--;

VERBOSE("Killing player: %s\n",ship->info.player.name);

if(ship->prevtype)
ship->prevtype->nexttype= ship->nexttype;
else
ship->un->players_head= ship->nexttype;

if(ship->nexttype)
ship->nexttype->prevtype= ship->prevtype;
else
ship->un->players_tail= ship->prevtype;

if(ship->prev)
ship->prev->next= ship->next;
else
ship->un->objs= ship->next;

if(ship->next)
ship->next->prev= ship->prev;

MAT_SHIP_VIEW_CHECK(ship->un);

free(ship);
}
}

/*:15*//*23:*/
#line 781 "./matanza.w"

/*110:*/
#line 3654 "./matanza.w"

/*104:*/
#line 3432 "./matanza.w"

void mat_print(MatConnection*p,int x,int y,int attr,char*s,int bl)
{
char s1[10000];
int pos,pos1;
int x1,y1;

ASSERT(x>=0);
ASSERT(y>=0);
ASSERT(x<p->xwinsize);
ASSERT(y<p->ywinsize);

x1= x;
y1= y;
for(pos= 0;s[pos]!=0&&pos<10000;pos++)
{
s1[pos]= s[pos];
pos1= x1+y1*p->xwinsize;
ASSERT(x1<p->xwinsize);
ASSERT(y1<p->ywinsize);
ASSERT(pos1<p->xwinsize*p->ywinsize);
p->graph_textbuffer[pos1]= s[pos];
p->graph_attrbuffer[pos1]= attr;
x1++;
if(x1>=p->xwinsize)
{
if(!bl)
break;
x1= 0;
y1++;
if(y1>=p->ywinsize)
break;
}
}
}

/*:104*/
#line 3655 "./matanza.w"

/*106:*/
#line 3492 "./matanza.w"

void
mat_print_center(MatConnection*p,int x,int y,double size,MatFont*font,int color,char*text)
{
double height,width;

height= p->graph_imgheight/size;
width= p->graph_imgwidth/size;

print(p,
(int)((double)x-width*(double)strlen(text)/2.0),
(int)((double)y-height/2.0),
(int)width,
(int)height,
font,color,text);
}

/*:106*/
#line 3656 "./matanza.w"

/*107:*/
#line 3511 "./matanza.w"

void
print(MatConnection*c,int x,int y,int width,int height,MatFont*f,int color,char*text)
{
int i;

for(i= 0;text[i];i++)
mat_graph_pscale(c,x+i*width,y,x+(i+1)*width,y+height,
f->data+f->width*(f->height*text[i]),f->width,f->height,
color);
}

/*:107*/
#line 3657 "./matanza.w"

/*108:*/
#line 3525 "./matanza.w"

void
mat_graph_pscale(MatConnection*con,int x1,int y1,int x2,int y2,
char*data,int w,int h,int color)
{
float step;
int xx1,xx2,yy1,yy2;


if(x1>=0&&x2<con->graph_imgwidth&&y1>=0&&y2<=con->graph_imgheight)
fastscale(data,con->graph_imagebuffer+x1+con->graph_imgwidth*y1,
w,x2-x1,h,y2-y1,w,con->graph_imgwidth,color);


if(x2<=0||x1>=con->graph_imgwidth||y2<=0||y1>=con->graph_imgheight)
return;


step= w/(float)(x2-x1);


if(x1>=0)
xx1= 0;
else
{
xx1= (int)(-step*x1);
x1= 0;
}


if(x2<=con->graph_imgwidth)
xx2= w;
else
{
xx2= (int)(step*(con->graph_imgwidth-x1));
x2= con->graph_imgwidth-1;
}


step= h/(float)(y2-y1);
if(y1<0)
{
yy1= (int)(-step*y1);
y1= 0;
}
else
yy1= 0;

if(y2> con->graph_imgheight)
{
yy2= (int)(step*(con->graph_imgheight-y1));
y2= con->graph_imgheight-1;
}
else
yy2= h;

fastscale(data+xx1+yy1*w,
con->graph_imagebuffer+x1+con->graph_imgwidth*y1,xx2-xx1,
x2-x1,yy2-yy1,y2-y1,w,con->graph_imgwidth,color);
}

void fastscale(char*b1,char*b2,int x1,int x2,int y1,
int y2,int width1,int width2,int color)
{
int ddx1,ddx,spx= 0,ex;
int ddy1,ddy,spy= 0,ey;
int x;
char*bb1= b1;
width2-= x2;
if(!x1||!x2||!y1||!y2)
return;
ddx= x1+x1;
ddx1= x2+x2;
if(ddx1<ddx)
spx= ddx/ddx1,ddx%= ddx1;
ddy= y1+y1;
ddy1= y2+y2;
if(ddy1<ddy)
spy= (ddy/ddy1)*width1,ddy%= ddy1;
ey= -ddy1;
for(;y2;y2--){
ex= -ddx1;
for(x= x2;x;x--){
if(*b1)
*b2= color;
b2++;
b1+= spx;
ex+= ddx;
if(ex> 0){
b1++;
ex-= ddx1;
}
}
b2+= width2;
bb1+= spy;
ey+= ddy;
if(ey> 0){
bb1+= width1;
ey-= ddy1;
}
b1= bb1;
}
}

/*:108*/
#line 3658 "./matanza.w"

/*132:*/
#line 4847 "./matanza.w"

void
mat_graph_render(MatConnection*con,int x1,int y1,int x2,int y2)
{
int x,y;
int val;
int wi= con->graph_imgwidth;
int pos,pos1;
int i1,i2,i3,i4;
float gamma;

/*124:*/
#line 4295 "./matanza.w"

{
if(x2<0||y2<0||x1> con->xwinsize||y1> con->ywinsize)
return;

if(x2>=con->xwinsize)
x2= con->xwinsize;

if(y2>=con->ywinsize)
y2= con->ywinsize;

if(x1<0)
x1= 0;

if(y1<0)
y1= 0;
}

/*:124*/
#line 4858 "./matanza.w"
;

if(con->graph_randomval> 0)
gamma= con->graph_randomval/2;
else
gamma= 0;

for(y= y1;y<y2;y++)
{
pos= 2*y*wi;
pos1= y*con->xwinsize;
for(x= x1;x<x2;x++)
{
/*131:*/
#line 4833 "./matanza.w"

i1= con->graph_palette[((((int)con->graph_imagebuffer[pos])))];
i2= con->graph_palette[((((int)con->graph_imagebuffer[pos+1])))];
i3= con->graph_palette[((((int)con->graph_imagebuffer[pos+wi])))];
i4= con->graph_palette[((((int)con->graph_imagebuffer[pos+1+wi])))];

/*:131*/
#line 4871 "./matanza.w"
;
/*129:*/
#line 4789 "./matanza.w"

if(gamma)
{
static int state;

state= MYRAND();

i1+= (state>>0)%con->graph_randomval-gamma;
i2+= (state>>8)%con->graph_randomval-gamma;
i3+= (state>>16)%con->graph_randomval-gamma;
i4+= (state>>24)%con->graph_randomval-gamma;

/*130:*/
#line 4807 "./matanza.w"


if((i1|i2|i3|i4)&(~255))
{
if(i1<0)
i1= 0;
else if(i1> 255)
i1= 255;
if(i2<0)
i2= 0;
else if(i2> 255)
i2= 255;
if(i3<0)
i3= 0;
else if(i3> 255)
i3= 255;
if(i4<0)
i4= 0;
else if(i4> 255)
i4= 255;
}

/*:130*/
#line 4801 "./matanza.w"
;
}

/*:129*/
#line 4872 "./matanza.w"
;

val= graph_table[((i1>>4)<<8)+((i2>>4)<<12)+((i3>>4)<<0)+((i4>>4)<<4)];

con->graph_imagebuffer[pos]= 0;
con->graph_imagebuffer[pos+1]= 0;
con->graph_imagebuffer[pos+wi]= 0;
con->graph_imagebuffer[pos+1+wi]= 0;

con->graph_attrbuffer[pos1]= val>>8;
con->graph_textbuffer[pos1]= val&0xff;
pos+= 2;
pos1++;
}
}
}

void
mat_graph_render_nowipe(MatConnection*con,int x1,int y1,int x2,int y2)
{
int x,y;
int val;
int wi= con->graph_imgwidth;
int pos,pos1;
int i1,i2,i3,i4;
float gamma;

/*124:*/
#line 4295 "./matanza.w"

{
if(x2<0||y2<0||x1> con->xwinsize||y1> con->ywinsize)
return;

if(x2>=con->xwinsize)
x2= con->xwinsize;

if(y2>=con->ywinsize)
y2= con->ywinsize;

if(x1<0)
x1= 0;

if(y1<0)
y1= 0;
}

/*:124*/
#line 4899 "./matanza.w"
;

if(con->graph_randomval> 0)
gamma= con->graph_randomval/2;
else
gamma= 0;

for(y= y1;y<y2;y++)
{
pos= 2*y*wi;
pos1= y*con->xwinsize;
for(x= x1;x<x2;x++)
{
/*131:*/
#line 4833 "./matanza.w"

i1= con->graph_palette[((((int)con->graph_imagebuffer[pos])))];
i2= con->graph_palette[((((int)con->graph_imagebuffer[pos+1])))];
i3= con->graph_palette[((((int)con->graph_imagebuffer[pos+wi])))];
i4= con->graph_palette[((((int)con->graph_imagebuffer[pos+1+wi])))];

/*:131*/
#line 4912 "./matanza.w"
;
/*129:*/
#line 4789 "./matanza.w"

if(gamma)
{
static int state;

state= MYRAND();

i1+= (state>>0)%con->graph_randomval-gamma;
i2+= (state>>8)%con->graph_randomval-gamma;
i3+= (state>>16)%con->graph_randomval-gamma;
i4+= (state>>24)%con->graph_randomval-gamma;

/*130:*/
#line 4807 "./matanza.w"


if((i1|i2|i3|i4)&(~255))
{
if(i1<0)
i1= 0;
else if(i1> 255)
i1= 255;
if(i2<0)
i2= 0;
else if(i2> 255)
i2= 255;
if(i3<0)
i3= 0;
else if(i3> 255)
i3= 255;
if(i4<0)
i4= 0;
else if(i4> 255)
i4= 255;
}

/*:130*/
#line 4801 "./matanza.w"
;
}

/*:129*/
#line 4913 "./matanza.w"
;

val= graph_table[((i1>>4)<<8)+((i2>>4)<<12)+((i3>>4)<<0)+((i4>>4)<<4)];

con->graph_attrbuffer[pos1]= val>>8;
con->graph_textbuffer[pos1]= val&0xff;
pos+= 2;
pos1++;
}
}
}

#if 0
#define VAL (13)

void
mat_graph_render_good(MatConnection*con,int x1,int y1,int x2,int y2)
{
static int state;
int x,y;
int val;
int wi= con->graph_imgwidth;
int pos;
int i;
int pos1;
int i1,i2,i3,i4,esum;
int*errors[2];
int cur= 0;
int mval;
int gamma;
unsigned char table[256];

errors[0]= calloc(1,(x2+5)*sizeof(int));
errors[0]+= 3;
errors[1]= calloc(1,(x2+5)*sizeof(int));
errors[1]+= 3;
cur= 0;

#if 0
for(i= 0;i<256;i++)
{
y= con->graph_palette[i]+0;

if(y<0)
y= 0;
else if(y> 255)
y= 255;














table[i]= y;
}
#endif

if(con->graph_randomval)
gamma= con->graph_randomval/2;
else
gamma= 0;

mval= (graph_parameters[graph_filltable[255]].p[4]);
for(y= y1;y<y2;y++)
{
pos= 2*y*wi;
pos1= y*con->xwinsize;
esum= 0;
for(x= x1;x<x2;x++)
{
/*131:*/
#line 4833 "./matanza.w"

i1= con->graph_palette[((((int)con->graph_imagebuffer[pos])))];
i2= con->graph_palette[((((int)con->graph_imagebuffer[pos+1])))];
i3= con->graph_palette[((((int)con->graph_imagebuffer[pos+wi])))];
i4= con->graph_palette[((((int)con->graph_imagebuffer[pos+1+wi])))];

/*:131*/
#line 4991 "./matanza.w"
;
/*129:*/
#line 4789 "./matanza.w"

if(gamma)
{
static int state;

state= MYRAND();

i1+= (state>>0)%con->graph_randomval-gamma;
i2+= (state>>8)%con->graph_randomval-gamma;
i3+= (state>>16)%con->graph_randomval-gamma;
i4+= (state>>24)%con->graph_randomval-gamma;

/*130:*/
#line 4807 "./matanza.w"


if((i1|i2|i3|i4)&(~255))
{
if(i1<0)
i1= 0;
else if(i1> 255)
i1= 255;
if(i2<0)
i2= 0;
else if(i2> 255)
i2= 255;
if(i3<0)
i3= 0;
else if(i3> 255)
i3= 255;
if(i4<0)
i4= 0;
else if(i4> 255)
i4= 255;
}

/*:130*/
#line 4801 "./matanza.w"
;
}

/*:129*/
#line 4992 "./matanza.w"
;

if(i1|i2|i3|i4)
{
errors[cur][x-2]+= esum>>4;
errors[cur][x-1]+= (5*esum)>>4;
errors[cur][x]= (3*esum)>>4;
esum= (7*esum)>>4;
esum+= errors[cur^1][x];
i1+= (esum+1)>>2;
i2+= (esum)>>2;
i3+= (esum+3)>>2;
i4+= (esum+2)>>2;
}

esum= i1+i2+i3+i4;
val= (esum)>>2;
if((abs(i1-val)<VAL&&
abs(i2-val)<VAL&&
abs(i3-val)<VAL&&
abs(i4-val)<VAL))
{
if(esum>=4*256)
val= 255,esum= 4*256-1;
if(val<0)
val= 0;
val= graph_filltable[val];
}
else
{
/*130:*/
#line 4807 "./matanza.w"


if((i1|i2|i3|i4)&(~255))
{
if(i1<0)
i1= 0;
else if(i1> 255)
i1= 255;
if(i2<0)
i2= 0;
else if(i2> 255)
i2= 255;
if(i3<0)
i3= 0;
else if(i3> 255)
i3= 255;
if(i4<0)
i4= 0;
else if(i4> 255)
i4= 255;
}

/*:130*/
#line 5022 "./matanza.w"
;
esum= i1+i2+i3+i4;
i1>>= 4;
i2>>= 4;
i3>>= 4;
i4>>= 4;
val= graph_table[((i1>>4)<<8)+((i2>>4)<<12)+((i3>>4)<<0)+((i4>>4)<<4)];
}
esum= (esum-(graph_parameters[val].p[4])*1020/mval);

con->graph_attrbuffer[pos1]= val>>8;
con->graph_textbuffer[pos1]= val&0xff;
pos+= 2;
pos1++;
}

if(x2-1> x1)
errors[cur][x2-2]+= (esum)>>4;
if(x2> x1)
errors[cur][x2-1]+= (5*esum)>>4;
cur^= 1;
errors[cur][x1]= 0;
errors[cur^1][-1]= 0;
}
free(errors[0]-3);
free(errors[1]-3);
}
#endif

/*:132*/
#line 3659 "./matanza.w"

/*114:*/
#line 3722 "./matanza.w"

void
mat_graph_resize(MatConnection*con,int width,int height)
{
int c;

if(height<=0)
height= 24;
if(width<=0)
width= 80;

ASSERT(width> 0);
ASSERT(height> 0);

if(con->xwinsize!=width||con->ywinsize!=height)
{
if(con->graph_imagebuffer)
free(con->graph_imagebuffer);
if(con->graph_textbuffer)
free(con->graph_textbuffer);
if(con->graph_textbufferold)
free(con->graph_textbufferold);
if(con->graph_attrbuffer)
free(con->graph_attrbuffer);
if(con->graph_attrbufferold)
free(con->graph_attrbufferold);

con->xwinsize= width;
con->ywinsize= height;

con->graph_imgwidth= con->xwinsize*2;
con->graph_imgheight= con->ywinsize*2;

c= width*height;

con->graph_imagebuffer= malloc(c*4);
if(!con->graph_imagebuffer)
{

fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

con->graph_textbuffer= malloc(c);
if(!con->graph_textbuffer)
{

fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

con->graph_attrbuffer= malloc(c);
if(!con->graph_attrbuffer)
{

fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

memset(con->graph_textbuffer,' ',c);
memset(con->graph_attrbuffer,MAT_NORMAL,c);
TERM_CLEAR_IMAGE(con);

con->graph_textbufferold= NULL;
con->graph_attrbufferold= NULL;

if(con->state==MAT_STATE_PLAYING)
/*154:*/
#line 5717 "./matanza.w"

{
MatMovingObj*sh;
int size_y;
int slot= 0;

size_y= con->ywinsize/con->ship_count;

ASSERT(arg_imgwidth> 0);

for(sh= con->ship_list;sh;sh= sh->info.player.conn_list_next)
{
ASSERT(sh->type==MAT_MOVING_OBJ_SHIP);

sh->info.player.win_x_s= 0;
sh->info.player.win_x_e= con->xwinsize;
sh->info.player.imgwi= con->xwinsize*2;

sh->info.player.win_y_s= size_y*(slot+0);
sh->info.player.win_y_e= size_y*(slot+1);
sh->info.player.imghe= 2*(sh->info.player.win_y_e-sh->info.player.win_y_s);


ASSERT(sh->info.player.imgwi> 0);
ASSERT(sh->info.player.imghe> 0);

sh->info.player.world_wi= arg_imgwidth;
sh->info.player.world_he= GET_WORLD_HE(sh->info.player,arg_imgwidth);

ASSERT(sh->info.player.world_wi> 0);
ASSERT(sh->info.player.world_he> 0);

slot++;
}
}

/*:154*/
#line 3789 "./matanza.w"
;
}
}

/*:114*/
#line 3660 "./matanza.w"


/*:110*/
#line 782 "./matanza.w"

/*97:*/
#line 3239 "./matanza.w"

int
mat_flush(MatConnection*con,int x,int y,int w,int h)
{
unsigned char*buf,*att;
int term_state;

term_state= MAT_NORMAL;

ASSERT(x<w);
ASSERT(y<h);
ASSERT(x<con->xwinsize);
ASSERT(y<con->ywinsize);
ASSERT(w<=con->xwinsize);
ASSERT(h<=con->ywinsize);

buf= con->graph_textbuffer+y*con->xwinsize;
att= con->graph_attrbuffer+y*con->xwinsize;

ASSERT(buf);
ASSERT(att);

if(arg_compress)
/*100:*/
#line 3314 "./matanza.w"

{
int i,j;
int advl;
char*bufold,*attold;
int w_x= -1,w_y= -1;

if(!con->graph_textbufferold)
{
con->graph_textbufferold= malloc(con->xwinsize*con->ywinsize);
con->graph_attrbufferold= malloc(con->xwinsize*con->ywinsize);
memset(con->graph_textbufferold,(char)' ',con->xwinsize*con->ywinsize);
memset(con->graph_attrbufferold,(char)MAT_NORMAL,con->xwinsize*con->ywinsize);
TERM_CLEAR_SCREEN(con);
}

bufold= con->graph_textbufferold+y*con->xwinsize;
attold= con->graph_attrbufferold+y*con->xwinsize;

ASSERT(bufold);
ASSERT(attold);

advl= strlen(con->term->cursor_adv);

for(;y<h;y++)
{
for(i= x;i<w;)
{
for(j= i;j<w&&bufold[j]==buf[j]&&(attold[j]==att[j]||buf[j]==' ');j++);

if(j<w)
/*102:*/
#line 3387 "./matanza.w"

{
SET_TERMINAL((int)att[j]);

ASSERT(i<=j);

TERM_SET_CURSOR(y,j);

mat_write(con,buf+j,1);
w_x++;

attold[j]= att[j];
bufold[j]= buf[j];

i= j+1;
}

/*:102*/
#line 3345 "./matanza.w"

else
i= j;
}

buf+= con->xwinsize;
att+= con->xwinsize;
bufold+= con->xwinsize;
attold+= con->xwinsize;
}
}


/*:100*/
#line 3262 "./matanza.w"

else
/*98:*/
#line 3273 "./matanza.w"

{
int len,i;

TERM_MOVE_CURSOR(con,y+1,x+1);

for(;y<h;y++)
{
for(i= x;i<w;i+= len)
{
for(len= 1;len+i<w&&att[i+len]==att[i];len++);
SET_TERMINAL((int)att[i]);
mat_write(con,buf+i,len);
}

if(y<h-1)
{
mat_printf(con,"%c%c",'\r','\n');
buf+= con->xwinsize;
att+= con->xwinsize;
}
}
}

/*:98*/
#line 3264 "./matanza.w"
;

SET_TERMINAL(MAT_NORMAL);

/*99:*/
#line 3299 "./matanza.w"

{
if(!mat_out_flush(con))
{
if(con->state==MAT_STATE_PLAYING)
MESSAGE_FROM(con,"has gone netdead");
mat_connection_free(con,MMP_SERVER_CLOSE_SYSERROR,strerror(errno));
return 0;
}

return 1;
}

/*:99*/
#line 3268 "./matanza.w"
;
}

/*:97*/
#line 783 "./matanza.w"

/*61:*/
#line 1923 "./matanza.w"

void
mat_input(MatConnection*con)
{
/*62:*/
#line 1935 "./matanza.w"

if(con->bufsiz-con->buflen<128)
{
con->bufsiz= con->bufsiz?con->bufsiz*2:128;
con->buffer= realloc(con->buffer,con->bufsiz+1);
}

/*:62*/
#line 1927 "./matanza.w"
;
/*327:*/
#line 10159 "./matanza.w"

/*328:*/
#line 10163 "./matanza.w"

{
int read_len;
int got_input= 0;
int keep_reading= 1;

VERBOSE("-=> recv cycle.\n");
while(keep_reading)
{
VERBOSE("-=> recv\n");
read_len= recv(con->fd,con->buffer+con->buflen,con->bufsiz-con->buflen,0);
VERBOSE("<=- recv\n");

switch(read_len)
{
case SOCKET_ERROR:
switch(SOCKET_ERRNO())
{
case SOCKET_CALL_INTR:

break;

/*329:*/
#line 10227 "./matanza.w"

#ifdef WSAECONNRESET
case WSAECONNRESET:
#endif
#ifdef WSAESHUTDOWN
case WSAESHUTDOWN:
#endif
#ifdef WSAENETRESET
case WSAENETRESET:
#endif
#ifdef ECONNRESET
case ECONNRESET:
#endif
#ifdef EPIPE
case EPIPE:
#endif

/*:329*/
#line 10185 "./matanza.w"


if(con->state==MAT_STATE_PLAYING)
MESSAGE_FROM(con,"has gone netdead");

mat_connection_free(con,MMP_SERVER_CLOSE_SYSERROR,strerror(SOCKET_ERRNO()));

return;

/*330:*/
#line 10247 "./matanza.w"

#ifdef EAGAIN
case EAGAIN:
#endif
#ifdef WSAEWOULDBLOCK
#  if WSAEWOULDBLOCK != EAGAIN
case WSAEWOULDBLOCK:
#  endif
#endif
#ifdef EWOULDBLOCK
#  if EWOULDBLOCK != EAGAIN
case EWOULDBLOCK:
#  endif
#endif

/*:330*/
#line 10194 "./matanza.w"


keep_reading= 0;
break;

default:

fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
break;
case 0:

keep_reading= 0;
break;

default:

ASSERT(read_len> 0);
got_input= 1;
con->buflen+= read_len;
con->buffer[con->buflen]= 0;
}
}
VERBOSE("<=- recv cycle\n");

if(!got_input)
return;
}

/*:328*/
#line 10160 "./matanza.w"
;

/*:327*/
#line 1928 "./matanza.w"
;
/*162:*/
#line 5988 "./matanza.w"

{
if(con->state==MAT_STATE_MACHINE)
/*163:*/
#line 5998 "./matanza.w"

{
int i;

ASSERT(con);

for(i= con->bufprc;i<con->buflen&&con->state!=MAT_STATE_REMOVE;i++)
if(con->key_handler)
{

con->key_handler(con,*(con->buffer+i));
}

memmove(con->buffer,con->buffer+i,con->buflen-i);
con->buflen-= i;
con->bufprc= 0;
}

/*:163*/
#line 5991 "./matanza.w"

else
/*164:*/
#line 6043 "./matanza.w"

{
int i,c;

ASSERT(con);

for(i= con->bufprc;i<con->buflen;i++)
{
c= *(con->buffer+i)&0377;
switch(con->input_state)
{
case MAT_KEY_DATA:
switch(c)
{
case IAC:
con->input_state= MAT_KEY_IAC;
break;
case 27:
con->input_state= MAT_KEY_27;
break;
case 0:
break;
default:
GOT_INPUT(con,c);
}
break;

case MAT_KEY_IAC:
switch(c)
{
case WILL:
con->input_state= MAT_KEY_WILL;
break;
case WONT:
con->input_state= MAT_KEY_WONT;
break;
case DO:
con->input_state= MAT_KEY_DO;
break;
case DONT:
con->input_state= MAT_KEY_DONT;
break;
case IAC:
break;
case IP:
if(con->state==MAT_STATE_PLAYING)
MESSAGE_FROM(con,"has left for the real world.")
mat_connection_free(con,MMP_SERVER_CLOSE_CLIENT,"User interrupt.");
break;
case BREAK:
VERBOSE("Got IAC BREAK\n");
break;
case AYT:
VERBOSE("Got IAC AYT\n");
break;
case AO:
VERBOSE("Got IAC AO\n");
break;
case SB:
con->input_state= MAT_KEY_SB;
con->telnet_args= i+1;
break;
default:
VERBOSE("Ignored Input: [key:%d][state:%d]\n",c,con->input_state);
con->input_state= MAT_KEY_DATA;
}
break;

case MAT_KEY_27:
switch(c)
{
case 79:
con->input_state= MAT_KEY_79;
break;

case 91:
con->input_state= MAT_KEY_91;
break;

default:
con->input_state= MAT_KEY_DATA;
VERBOSE("Ignored Input: [key:%d][state:%d]\n",c,con->input_state);
}
break;

case MAT_KEY_79:
case MAT_KEY_91:
switch(c)
{
case 65:
GOT_INPUT(con,KEY_ARROW_UP);
break;
case 66:
GOT_INPUT(con,KEY_ARROW_DOWN);
break;
case 67:
GOT_INPUT(con,KEY_ARROW_RIGHT);
break;
case 68:
GOT_INPUT(con,KEY_ARROW_LEFT);
break;
default:
VERBOSE("Ignored Input: [key:%d][state:%d]\n",c,con->input_state);
}
con->input_state= MAT_KEY_DATA;
break;

case MAT_KEY_SB:
if(c==IAC)
con->input_state= MAT_KEY_SE;
break;

case MAT_KEY_SE:
/*173:*/
#line 6367 "./matanza.w"

if(c!=SE)
{
ASSERT(c==IAC);
con->input_state= MAT_KEY_IAC;
}
else
{
switch(con->buffer[con->telnet_args++])
{
case TELOPT_TSPEED:
/*169:*/
#line 6273 "./matanza.w"

{
int xspeed,rspeed;




ASSERT(con->buflen> con->telnet_args);

if((con->buffer[con->telnet_args++]&0xff)!=TELQUAL_IS)
ASSERT(0);

xspeed= atoi(con->buffer+con->telnet_args);

while(con->buffer[con->telnet_args]!=','&&con->buflen> con->telnet_args)
con->telnet_args++;

ASSERT(con->buflen> con->telnet_args);

rspeed= atoi(con->buffer+con->telnet_args);

VERBOSE("Ignoring TSPEED: %d %d\n",xspeed,rspeed);
}

/*:169*/
#line 6378 "./matanza.w"
;
break;

case TELOPT_TTYPE:
/*170:*/
#line 6298 "./matanza.w"

{
int j;




ASSERT(con->buflen> con->telnet_args);

if((con->buffer[con->telnet_args++]&0xff)!=TELQUAL_IS)
ASSERT(1);

for(j= 0;j<14&&con->telnet_args+1<i;j++,con->telnet_args++)
con->terminal_name[j]= tolower(con->buffer[con->telnet_args]);

con->terminal_name[j]= 0;

VERBOSE("Got terminal name: %s\n",con->terminal_name);
}

/*:170*/
#line 6382 "./matanza.w"
;
break;

case TELOPT_NAWS:
/*172:*/
#line 6344 "./matanza.w"

{
int width,height;




ASSERT(con->buflen> con->telnet_args);
width= (con->buffer[con->telnet_args++]&0xff)<<8;
ASSERT(con->buflen> con->telnet_args);
width|= (con->buffer[con->telnet_args++]&0xff);
ASSERT(con->buflen> con->telnet_args);
height= (con->buffer[con->telnet_args++]&0xff)<<8;
ASSERT(con->buflen> con->telnet_args);
height|= (con->buffer[con->telnet_args++]&0xff);

VERBOSE("Got window size: %d x %d\n",width,height);

if(width> 0&&height> 0)
mat_graph_resize(con,width,height);
}

/*:172*/
#line 6386 "./matanza.w"
;
break;

case TELOPT_LINEMODE:
/*171:*/
#line 6320 "./matanza.w"

{
ASSERT(con->buflen> con->telnet_args);
con->telnet_args++;
ASSERT(con->buflen> con->telnet_args);

if((con->buffer[con->telnet_args]&0xff)==LM_SLC)
{
VERBOSE("Disabling TELOPT_LINEMODE for player.\n");
mat_printf(con,"%c%c%c%c%c%c",IAC,SB,TELOPT_LINEMODE,LM_SLC,IAC,SE);
}
else if(con->buffer[con->telnet_args]==LM_MODE)
{
VERBOSE("Use edit mode: %d\n",con->buffer[con->telnet_args++]);
}
else
{
ASSERT(con->buflen> con->telnet_args);

VERBOSE("Telnet: Invalid char received in TELOPT_LINEMODE: %s:%d\n",__FILE__,__LINE__);
}
}

/*:171*/
#line 6390 "./matanza.w"
;
break;

default:
VERBOSE("Unknown telnet parameter: %d\n",con->buffer[con->telnet_args-1]);
break;
}
con->input_state= MAT_KEY_DATA;
check_telnet_negotiation(con);
}

/*:173*/
#line 6156 "./matanza.w"
;
break;

case MAT_KEY_WILL:
/*176:*/
#line 6438 "./matanza.w"

{
ASSERT(con);

switch(c)
{
case TELOPT_TSPEED:
case TELOPT_TTYPE:
case TELOPT_NAWS:
mat_printf(con,"%c%c%c%c%c%c",IAC,SB,c,TELQUAL_SEND,IAC,SE);
mat_out_flush(con);
break;
case TELOPT_LINEMODE:
VERBOSE("Telnet: Player TELOPT_LINEMODE\n");
break;
default:
VERBOSE("Telnet: Got WILL %d\n",c);
/*180:*/
#line 6507 "./matanza.w"

{
ASSERT(con);

mat_printf(con,"%c%c%c",IAC,DONT,c);
mat_out_flush(con);
}

/*:180*/
#line 6455 "./matanza.w"
;
}
}

/*:176*/
#line 6160 "./matanza.w"
;
con->input_state= MAT_KEY_DATA;
break;

case MAT_KEY_WONT:
/*177:*/
#line 6461 "./matanza.w"

{
ASSERT(con);

switch(c)
{
case TELOPT_TTYPE:
strcpy(con->terminal_name,"dumb");
check_telnet_negotiation(con);
break;
case TELOPT_NAWS:
mat_graph_resize(con,80,24);
check_telnet_negotiation(con);
break;
case TELOPT_ECHO:
VERBOSE("Telnet: Client won't echo\n");
/*179:*/
#line 6498 "./matanza.w"

{
ASSERT(con);

mat_printf(con,"%c%c%c",IAC,WONT,c);
mat_out_flush(con);
}

/*:179*/
#line 6477 "./matanza.w"
;
break;
case TELOPT_LINEMODE:
VERBOSE("Telnet: Client won't do linemode (may do buffering)\n");
break;
default:
/*180:*/
#line 6507 "./matanza.w"

{
ASSERT(con);

mat_printf(con,"%c%c%c",IAC,DONT,c);
mat_out_flush(con);
}

/*:180*/
#line 6483 "./matanza.w"
;
VERBOSE("Telnet: Got WONT %d\n",c);
}
}

/*:177*/
#line 6165 "./matanza.w"
;
con->input_state= MAT_KEY_DATA;
break;

case MAT_KEY_DO:
/*175:*/
#line 6411 "./matanza.w"

{
ASSERT(con);

switch(c)
{
case TELOPT_LOGOUT:
/*178:*/
#line 6489 "./matanza.w"

{
ASSERT(con);

mat_printf(con,"%c%c%c",IAC,WILL,c);
mat_out_flush(con);
}

/*:178*/
#line 6418 "./matanza.w"
;
if(con->state==MAT_STATE_PLAYING)
MESSAGE_FROM(con,"has left for the real world");
mat_connection_free(con,MMP_SERVER_CLOSE_CLIENT,"User logout.");
break;
case TELOPT_ECHO:
VERBOSE("Telnet: Got DO ECHO\n");
break;
case TELOPT_SGA:
VERBOSE("Telnet: Got DO SGA\n");
/*178:*/
#line 6489 "./matanza.w"

{
ASSERT(con);

mat_printf(con,"%c%c%c",IAC,WILL,c);
mat_out_flush(con);
}

/*:178*/
#line 6428 "./matanza.w"
;
break;
default:
VERBOSE("Telnet: Got DO %d\n",c);
/*179:*/
#line 6498 "./matanza.w"

{
ASSERT(con);

mat_printf(con,"%c%c%c",IAC,WONT,c);
mat_out_flush(con);
}

/*:179*/
#line 6432 "./matanza.w"
;
}
}

/*:175*/
#line 6170 "./matanza.w"
;
con->input_state= MAT_KEY_DATA;
break;

case MAT_KEY_DONT:
/*174:*/
#line 6403 "./matanza.w"

{
VERBOSE("Telnet: Got DONT %d\n",c);
/*179:*/
#line 6498 "./matanza.w"

{
ASSERT(con);

mat_printf(con,"%c%c%c",IAC,WONT,c);
mat_out_flush(con);
}

/*:179*/
#line 6406 "./matanza.w"
;
}

/*:174*/
#line 6175 "./matanza.w"
;
con->input_state= MAT_KEY_DATA;
break;

default:
ASSERT(0);
}
}

memmove(con->buffer,con->buffer+i,con->buflen-i);
con->buflen-= i;
con->bufprc= 0;
}

/*:164*/
#line 5993 "./matanza.w"

}

/*:162*/
#line 1929 "./matanza.w"
;
}

/*:61*/
#line 784 "./matanza.w"

/*:23*//*42:*/
#line 1295 "./matanza.w"

void
ast_crash_handler(MatMovingObj*ast,MatMovingObj*obj)
{
ASSERT(obj);
switch(obj->type)
{
case MAT_MOVING_OBJ_AST:
break;

case MAT_MOVING_OBJ_BULLET:
crash_handler[obj->type](obj,ast);
break;

case MAT_MOVING_OBJ_SHIP:
crash_handler[obj->type](obj,ast);
break;

case MAT_MOVING_OBJ_SMART:
break;

default:
ASSERT(0);
}
}

/*:42*//*43:*/
#line 1322 "./matanza.w"

void
bullet_crash_handler(MatMovingObj*b,MatMovingObj*obj)
{
ASSERT(obj);
switch(obj->type)
{
case MAT_MOVING_OBJ_BULLET:
break;

case MAT_MOVING_OBJ_AST:
/*47:*/
#line 1493 "./matanza.w"

{
ASSERT(b->info.bullet.expires>=0);

if(!b->info.bullet.expires)
return;


b->info.bullet.expires= 0;


obj->info.ast.health-= mat_bullets_damage[b->info.bullet.type];

if(obj->info.ast.health<=0)
/*48:*/
#line 1513 "./matanza.w"

{
VERBOSE("Boom, asteroid broke\n");

ASSERT(obj);
ASSERT(obj->type==MAT_MOVING_OBJ_AST);

ASSERT(b);
ASSERT(b->type==MAT_MOVING_OBJ_BULLET);

ASSERT(b->info.bullet.src);

if(b->info.bullet.src->type==MAT_MOVING_OBJ_SHIP)
sprintf(message_get(b->info.bullet.src),"-=> BOOM, you broke an asteroid to pieces !");

REMOVE_QUEUE_ADD(obj);

if(obj->info.ast.size<1)
/*49:*/
#line 1539 "./matanza.w"

{
int ns;

ns= obj->info.ast.size+1;

AST_ADD_POS(ns,obj->pos_x,obj->pos_y,obj->sp_x+RND_SP(),obj->sp_y+RND_SP(),obj->un);
AST_ADD_POS(ns,obj->pos_x,obj->pos_y,obj->sp_x+RND_SP(),obj->sp_y-RND_SP(),obj->un);
AST_ADD_POS(ns,obj->pos_x,obj->pos_y,obj->sp_x-RND_SP(),obj->sp_y+RND_SP(),obj->un);
AST_ADD_POS(ns,obj->pos_x,obj->pos_y,obj->sp_x-RND_SP(),obj->sp_y-RND_SP(),obj->un);
}

/*:49*/
#line 1531 "./matanza.w"
;
}

/*:48*/
#line 1507 "./matanza.w"

else
sprintf(message_get(b->info.bullet.src),mat_bullets_hit_ast[b->info.bullet.type]);
}

/*:47*/
#line 1333 "./matanza.w"
;
break;

case MAT_MOVING_OBJ_SHIP:
/*50:*/
#line 1552 "./matanza.w"

{
if(!b->info.bullet.expires||b->info.bullet.src==obj)
return;


b->info.bullet.expires= 0;


obj->info.player.health-= mat_bullets_damage[b->info.bullet.type];

if(obj->info.player.health<=0)
/*56:*/
#line 1787 "./matanza.w"

{
int sent_out;
MatMovingObj*i;

ASSERT(obj);
ASSERT(obj->type==MAT_MOVING_OBJ_SHIP);

ASSERT(b);
ASSERT(b->type==MAT_MOVING_OBJ_BULLET);

ASSERT(b->info.bullet.src);
ASSERT(b->info.bullet.src->type==MAT_MOVING_OBJ_SHIP);

ASSERT(obj!=b->info.bullet.src);

ASSERT(obj->un==b->un);

PLAYER_DEAD_REGISTER(sent_out,obj);

for(i= obj->un->players_head;i;i= i->nexttype)
if(arg_teams_count> 0)
{
sprintf(message_get(i),
"-=> KABOOM ! %s of %s is destroyed by %s of %s . . .",
obj->info.player.name,obj->info.player.team->name,
b->info.bullet.src->info.player.name,
b->info.bullet.src->info.player.team->name);
if(sent_out)
sprintf(message_get(i),
"-=> %s of %s is sent out of the game.",
obj->info.player.name,obj->info.player.team->name);
}
else
{
sprintf(message_get(i),
"-=> KABOOM ! %s is destroyed by %s . . .",
obj->info.player.name,b->info.bullet.src->info.player.name);
if(sent_out)
sprintf(message_get(i),
"-=> %s is sent out of the game.",obj->info.player.name);
}

if(!sent_out)
{
if(arg_teams_count&&arg_teams_share)
for(i= obj->info.player.team->head;i;i= i->info.player.team_next)
sprintf(message_get(i),"-=> [%s] Arg, we have lost %d ships now !",
obj->info.player.team->name,obj->info.player.team->times_dead);
else
sprintf(message_get(obj),"-=> You have lost %d ships now !",obj->info.player.times_dead);

start_game(obj);
}
else
{
GAME_OVER_MODE(obj);




}
}

/*:56*/
#line 1564 "./matanza.w"

else
switch(b->info.bullet.src->type)
{
case MAT_MOVING_OBJ_SHIP:
sprintf(message_get(obj),"-=> Argh! %s got you! [Health:%d%%]",
b->info.bullet.src->info.player.name,HEALTH(obj));
sprintf(message_get(b->info.bullet.src),
mat_bullets_hit[b->info.bullet.type],obj->info.player.name);
break;

case MAT_MOVING_OBJ_SMART:
sprintf(message_get(obj),"-=> Argh! An alien got you! [Health:%d%%]",HEALTH(obj));
break;

default:
ASSERT(0);
}
}

/*:50*/
#line 1337 "./matanza.w"
;
break;

case MAT_MOVING_OBJ_SMART:
break;

default:
ASSERT(0);
}
}

/*:43*//*44:*/
#line 1349 "./matanza.w"

void
player_crash_handler(MatMovingObj*p,MatMovingObj*obj)
{
ASSERT(obj);
ASSERT(p->type==MAT_MOVING_OBJ_SHIP);
switch(obj->type)
{
case MAT_MOVING_OBJ_AST:
/*46:*/
#line 1463 "./matanza.w"

{
ASSERT(obj);
ASSERT(obj->type==MAT_MOVING_OBJ_AST);

ASSERT(p);
ASSERT(p->type==MAT_MOVING_OBJ_SHIP);

if(!arg_space)
return;


p->info.player.health-= 200;

if(arg_space)
{
p->sp_x= -p->sp_x;
p->sp_y= -p->sp_y;

obj->sp_x= -obj->sp_x;
obj->sp_y= -obj->sp_y;
}

if(p->info.player.health<=0)
/*55:*/
#line 1731 "./matanza.w"

{
int sent_out;
MatMovingObj*i;

VERBOSE("xxxx player killed by asteroid\n");

ASSERT(p);
ASSERT(p->type==MAT_MOVING_OBJ_SHIP);

ASSERT(obj);
ASSERT(obj->type==MAT_MOVING_OBJ_AST);

ASSERT(p->un==obj->un);

PLAYER_DEAD_REGISTER(sent_out,p);

for(i= p->un->players_head;i;i= i->nexttype)
if(arg_teams_count> 0)
{
sprintf(message_get(i),
"-=> KABOOM ! %s of %s is destroyed by an asteroid . . .",
p->info.player.name,p->info.player.team->name);
if(sent_out)
sprintf(message_get(i),
"-=> %s of %s is sent out of the game.",
p->info.player.name,p->info.player.team->name);
}
else
{
sprintf(message_get(i),
"-=> KABOOM ! %s is destroyed by an asteroid . . .",
p->info.player.name);
if(sent_out)
sprintf(message_get(i),
"-=> %s is sent out of the game.",p->info.player.name);
}

if(!sent_out)
{
if(arg_teams_count&&arg_teams_share)
for(i= p->info.player.team->head;i;i= i->info.player.team_next)
sprintf(message_get(i),"-=> [%s] Arg, we have lost %d ships now !",
p->info.player.team->name,p->info.player.team->times_dead);
else
sprintf(message_get(p),"-=> You have lost %d ships now !",p->info.player.times_dead);

start_game(p);
}
else
GAME_OVER_MODE(p);
}

/*:55*/
#line 1487 "./matanza.w"

else
sprintf(message_get(p),"-=> You crashed against an asteroid ! [Health:%d%%]",HEALTH(p));
}

/*:46*/
#line 1358 "./matanza.w"
;
break;

case MAT_MOVING_OBJ_SHIP:
/*45:*/
#line 1437 "./matanza.w"

{
int dmg;

ASSERT(p->un==obj->un);

if(!arg_space)
return;

dmg= p->un->crash_damage[MAT_MOVING_OBJ_SHIP];
obj->info.player.health-= dmg;
p->info.player.health-= dmg;

if(arg_space)
{
p->sp_x= -p->sp_x;
p->sp_y= -p->sp_y;
obj->sp_x= -obj->sp_x;
obj->sp_y= -obj->sp_y;
}

MESSAGE_CRASH_SHIP(p,obj);
MESSAGE_CRASH_SHIP(obj,p);
}

/*:45*/
#line 1362 "./matanza.w"
;
break;

case MAT_MOVING_OBJ_BULLET:
crash_handler[obj->type](obj,p);
break;

case MAT_MOVING_OBJ_SMART:
break;

default:
ASSERT(0);
}
}

/*:44*//*64:*/
#line 1956 "./matanza.w"

void
mat_accept(MatSocketT source,int machine)
{
MatSocketT result;
socklen_t in_con_size= sizeof(struct sockaddr_in);
struct sockaddr_in in_con;

while(1)
{
do
{
VERBOSE("-=> accept [fd:%d]\n",source);
result= accept(source,(struct sockaddr*)&in_con,&in_con_size);
VERBOSE("<=- accept [fd:%d] [result:%d]\n",source,result);
}
while(result==SOCKET_ERROR&&result==SOCKET_CALL_INTR);

if(result==SOCKET_ERROR)
/*65:*/
#line 1982 "./matanza.w"

{
VERBOSE("error in accept: %d\n",SOCKET_ERRNO());
switch(SOCKET_ERRNO())
{
#ifdef EAGAIN
case EAGAIN:
#endif
#ifdef EWOULDBLOCK
#  if EWOULDBLOCK != EAGAIN
case EWOULDBLOCK:
#  endif
#endif
#ifdef WSAEWOULDBLOCK
#  if WSAEWOULDBLOCK != EAGAIN
case WSAEWOULDBLOCK:
#  endif
#endif

return;

default:
fprintf(stderr,"%s: code: %d\n",program_name,SOCKET_ERRNO());
fprintf(stderr,"%s: accept: %s\n",program_name,strerror(SOCKET_ERRNO()));
exit(EXIT_FAILURE);
}
}

/*:65*/
#line 1975 "./matanza.w"

else
/*66:*/
#line 2015 "./matanza.w"

{
MatConnection*con;
int on= 1;

con= malloc(sizeof(MatConnection));
if(!con)
{

fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

con->fd= result;

/*68:*/
#line 2097 "./matanza.w"

{
#if HAVE_INET_NTOP
/*71:*/
#line 2144 "./matanza.w"

{
char buffer[256];

if(!inet_ntop(in_con.sin_family,&in_con.sin_addr,buffer,sizeof(buffer)))
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

con->addr= strdup(buffer);
if(!con->addr)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
}

/*:71*/
#line 2100 "./matanza.w"
;
#elif HAVE_INET_NTOA
/*70:*/
#line 2126 "./matanza.w"

{
char*tmp;

tmp= inet_ntoa(in_con.sin_addr);

ASSERT(tmp);

con->addr= strdup(tmp);
if(!con->addr)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
}

/*:70*/
#line 2102 "./matanza.w"
;
#else
/*69:*/
#line 2114 "./matanza.w"

{
con->addr= strdup("Unknown");
if(!con->addr)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
}

/*:69*/
#line 2104 "./matanza.w"
;
#endif

ASSERT(con->addr);

VERBOSE("Connection from: %s\n",con->addr);
}

/*:68*/
#line 2030 "./matanza.w"
;

#if HAVE_SETSOCKOPT
#  ifdef SO_KEEPALIVE
#    ifdef SOL_SOCKET
VERBOSE("setsockopt [fd:%d][option:SO_KEEPALIVE]\n",con->fd);
if(setsockopt(con->fd,SOL_SOCKET,SO_KEEPALIVE,(void*)&on,sizeof(on))==-1)
fprintf(stderr,"%s: Warning: setsockopt: SO_KEEPALIVE: %s\n",program_name,strerror(errno));
#    endif
#  endif
#endif


NONBLOCKING_GENERIC(result);

con->out_buf= NULL;
con->out_len= 0;
con->out_siz= 0;

ASSERT(source==mat_mainsock||source==mat_mainsock_machine);

if(arg_max_players==0||players_count<arg_max_players)
{
if(source==mat_mainsock)
/*76:*/
#line 2261 "./matanza.w"

{
/*72:*/
#line 2166 "./matanza.w"

{
mat_printf(con,"%s""%c%c%c""%c%c%c""%c%c%c""%c%c%c""%c%c%c",
"-=> Please stand by . . .\r\n"
"-=> Matanza is preparing your machine to maximize your experience . . . ",
IAC,DO,TELOPT_TTYPE,
IAC,DO,TELOPT_NAWS,
IAC,DONT,TELOPT_LINEMODE,
IAC,WILL,TELOPT_SGA,
IAC,WILL,TELOPT_ECHO);

mat_out_flush(con);
}

/*:72*/
#line 2263 "./matanza.w"
;

con->state= MAT_STATE_PREPARE;

con->info.t.clean= 1;

con->terminal_name[0]= 0;
con->term= &term_vt100;

con->xwinsize= con->ywinsize= -1;

con->buffer= NULL;
con->bufsiz= con->buflen= con->bufprc= 0;

con->key_handler= NULL;
con->anim_func= NULL;

con->input_state= MAT_KEY_DATA;




/*115:*/
#line 3795 "./matanza.w"

{
ASSERT(con);

con->graph_textbuffer= NULL;
con->graph_textbufferold= NULL;
con->graph_attrbuffer= NULL;
con->graph_attrbufferold= NULL;
con->graph_imagebuffer= NULL;

MAT_DEFAULT_PALETTE(con);
}

/*:115*/
#line 2285 "./matanza.w"
;

con->next= connections;
con->prev= NULL;

if(connections)
connections->prev= con;

connections= con;

players_count++;
}

/*:76*/
#line 2054 "./matanza.w"

else
/*74:*/
#line 2219 "./matanza.w"

{
con->state= MAT_STATE_MACHINE;

con->buffer= NULL;
con->bufsiz= con->buflen= con->bufprc= 0;

con->key_handler= machine_input_initial;

con->input_state= MAT_KEY_DATA;
con->anim_func= machine_update;

con->next= connections;
con->prev= NULL;

/*75:*/
#line 2247 "./matanza.w"

{
int i;

con->ship_count= 0;

for(i= 0;i<MAT_CONNECTION_SHIP_HASH_SIZE;i++)
con->ship_hash[i]= NULL;

con->ship_list= 0;
}

/*:75*/
#line 2234 "./matanza.w"
;

MAT_SUB_MACHINE_INIT(con);

if(connections)
connections->prev= con;

connections= con;

players_count++;
}

/*:74*/
#line 2056 "./matanza.w"

}
else
/*67:*/
#line 2070 "./matanza.w"

{
ASSERT(con);

if(source==mat_mainsock)
mat_printf(con,"%s","Sorry, the server is full. Please try again later.\n");
else
mat_printf(con,"%c",MMP_SERVER_INITIAL_FULL);

mat_out_flush(con);

free(con->out_buf);
free(con);
}

/*:67*/
#line 2059 "./matanza.w"
;
}

/*:66*/
#line 1977 "./matanza.w"
;
}
}

/*:64*//*77:*/
#line 2300 "./matanza.w"

void
check_telnet_negotiation(MatConnection*con)
{
if(con->state==MAT_STATE_PREPARE)
{
if(con->terminal_name[0]==0||con->xwinsize==-1||con->ywinsize==-1)
return;

/*78:*/
#line 2325 "./matanza.w"

{
ASSERT(con);
con->term= &term_vt100;
}

/*:78*/
#line 2309 "./matanza.w"
;

TERM_CLEAR_SCREEN(con);
TERM_HIDE_CURSOR(con);

con->state= MAT_STATE_NORMAL;

/*137:*/
#line 5100 "./matanza.w"

{
int i;

ASSERT(con);

con->graph_randomval= 60;

con->anim_func= mat_anim_000;
con->anim_data= malloc(sizeof(MatAnim000));

for(i= 0;i<12;i++)
DATA000(colors[i]= 0);

DATA000(next)= 0;
DATA000(delay)= 30;

DATA000(width)= con->graph_imgwidth/7;
DATA000(height)= con->graph_imgheight/2;

DATA000(pos_x)= con->graph_imgwidth/14;
DATA000(pos_y)= con->graph_imgheight/2;
}

/*:137*/
#line 2316 "./matanza.w"
;

con->key_handler= mat_animation_cancel;
}
}

/*:77*//*79:*/
#line 2333 "./matanza.w"

void
mat_animation_cancel(MatConnection*con,int x)
{
ASSERT(con);

switch(x)
{
case 13:
free(con->anim_data);
MAT_DEFAULT_PALETTE(con);
main_menu_begin(con);
break;
default:
VERBOSE("Input from player during animations: %d\n",x);
}
}

/*:79*//*89:*/
#line 2623 "./matanza.w"

void
term_handler(int sig)
{
MatConnection*c;

printf("Terminating on signal %d\n",sig);

for(c= connections;c;c= c->next)
mat_connection_free(c,MMP_SERVER_CLOSE_SHUTDOWN,"The server is being shutdown.");

if(arg_free_at_exit)
/*90:*/
#line 2642 "./matanza.w"

{
int i;

/*87:*/
#line 2584 "./matanza.w"

{
/*198:*/
#line 7072 "./matanza.w"

{
int i;

if(arg_ast_num> 0)
{
for(i= 0;i<arg_ang;i++)
{
free(mat_ship[i].img);
}

free(mat_ship);
}
}

/*:198*/
#line 2586 "./matanza.w"
;
/*195:*/
#line 6893 "./matanza.w"

{
int i;

if(arg_ast_num> 0)
{
for(i= 0;i<arg_ang;i++)
{
free(mat_missile[0][i].img);
free(mat_missile[1][i].img);
free(mat_missile[2][i].img);
}

free(mat_missile[0]);
free(mat_missile[1]);
free(mat_missile[2]);
}
}
/*:195*/
#line 2587 "./matanza.w"
;
/*193:*/
#line 6802 "./matanza.w"

{
int i;

if(arg_ast_num> 0)
{
for(i= 0;i<arg_ang;i++)
{
free(mat_ast[0][i].img);
free(mat_ast[1][i].img);
}

free(mat_ast[0]);
free(mat_ast[1]);
}
}

/*:193*/
#line 2588 "./matanza.w"
;
}

/*:87*/
#line 2646 "./matanza.w"
;

free(font.data);

for(i= 0;i<MAT_UNIVERSES_HASH_SIZE;i++)
while(mat_universes[i])
{
MatUniverse*d;

d= mat_universes[i];
mat_universes[i]= d->next_hash;

/*91:*/
#line 2678 "./matanza.w"

{
while(d->ast)
{
MatMovingObj*a;

a= d->ast;
d->ast= a->nexttype;

free(a);
}
free(d);
}

/*:91*/
#line 2658 "./matanza.w"
;
}

while(connections)
{
MatConnection*tmp;

ASSERT(connections->state==MAT_STATE_REMOVE);

tmp= connections->next;
free(connections);
connections= tmp;
}

/*122:*/
#line 4039 "./matanza.w"

{
free(graph_parameters);
free(graph_table);
free(graph_filltable);
}

/*:122*/
#line 2672 "./matanza.w"
;
/*282:*/
#line 9191 "./matanza.w"

{
free(mat_ship_palette[0]);
free(mat_ship_palette[1]);
free(mat_ship_palette[2]);
free(mat_ship_palette[3]);
}

/*:282*/
#line 2673 "./matanza.w"
;
/*365:*/
#line 11190 "./matanza.w"

{
free(mat_cos);
free(mat_sin);
}

/*:365*/
#line 2674 "./matanza.w"
;
}

/*:90*/
#line 2635 "./matanza.w"
;

exit(EXIT_SUCCESS);
}

/*:89*//*109:*/
#line 3630 "./matanza.w"

void
uncompressfont(aa_font*src)
{
int i,y;

font.width= 8;
font.height= src->height;
font.data= calloc(1,256*8*src->height);
for(i= 0,y= 0;i<256*font.height;i++,y+= 8)
{
char c= src->data[i];
font.data[y]= (char)c&(1<<7);
font.data[y+1]= (char)c&(1<<6);
font.data[y+2]= (char)c&(1<<5);
font.data[y+3]= (char)c&(1<<4);
font.data[y+4]= (char)c&(1<<3);
font.data[y+5]= (char)c&(1<<2);
font.data[y+6]= (char)c&(1<<1);
font.data[y+7]= (char)c&(1<<0);
}
}

/*:109*//*133:*/
#line 5055 "./matanza.w"

/*138:*/
#line 5126 "./matanza.w"


void
mat_anim_000(MatConnection*con)
{
static char*text0[]= {"F","r","e","a","k","s"};
static char*text1[]= {"U","n","i","d","o","s"};
int i;

ASSERT(con);

for(i= 0;i<6;i++)
if(DATA000(colors[i]))
print(con,DATA000(pos_x)+DATA000(width)*i,0,
DATA000(width),DATA000(height),
&font,DATA000(colors[i]),text0[i]);

for(i= 6;i<12;i++)
if(DATA000(colors[i]))
print(con,DATA000(pos_x)+DATA000(width)*(i-6),DATA000(pos_y),
DATA000(width),DATA000(height),
&font,DATA000(colors[i]),text1[i-6]);

MAT_GRAPH_RENDER_ALL(con);
MAT_FLUSH_ALL(con);

/*139:*/
#line 5157 "./matanza.w"

if(DATA000(delay)==0)
{
if(DATA000(next)!=6)
{
DATA000(colors[DATA000(next)])= 252;
DATA000(colors[11-DATA000(next)])= 252;
DATA000(next)++;
DATA000(delay)= 8;
}
else
DATA000(delay)--;
}
else
{
int i;

if(DATA000(delay)==-1)
{
if(DATA000(colors[5])==0)
{
free(con->anim_data);
/*141:*/
#line 5206 "./matanza.w"

{
con->graph_randomval= 60;

con->anim_func= mat_anim_001;
con->anim_data= malloc(sizeof(MatAnim001));

DATA001(delay)= 0;
DATA001(delta)= 0.3;
DATA001(head)= -7;

DATA001(width)= con->graph_imgwidth/9;
DATA001(height)= con->graph_imgheight/2;

DATA001(pos_x)= con->graph_imgwidth/81;
DATA001(pos_y)= con->graph_imgheight/4;
}

/*:141*/
#line 5179 "./matanza.w"
;
return;
}
}
else
DATA000(delay)--;

for(i= 0;i<12;i++)
if(DATA000(colors[i]))
DATA000(colors[i])-= 6;
}
/*:139*/
#line 5152 "./matanza.w"
;
}

/*:138*/
#line 5056 "./matanza.w"

/*142:*/
#line 5226 "./matanza.w"


void
mat_anim_001(MatConnection*con)
{
static char*text[]= {"P","r","e","s","e","n","t","s"};
int i;
double c;

for(i= 0;i<8;i++)
{
c= 36.0*(((double)i)-((double)DATA001(head)));
c= i>=DATA001(head)?255-c:255+c;
c= c> 0?c:0;

print(con,DATA001(pos_x)+(DATA001(pos_x)+DATA001(width))*i,
DATA001(pos_y),DATA001(width),DATA001(height),
&font,(int)c,text[i]);
}

MAT_GRAPH_RENDER_ALL(con);
MAT_FLUSH_ALL(con);

/*143:*/
#line 5254 "./matanza.w"

if(DATA001(head)<=-3)
DATA001(delta)= +0.4;
else if(DATA001(head)>=10)
{
if(DATA001(delay)<2)
DATA001(delta)= -0.4;
else if(DATA001(delay)> 20)
{
free(con->anim_data);
/*145:*/
#line 5288 "./matanza.w"

{
int minus;
unsigned int i;

ASSERT(con);

con->graph_randomval= 0;

con->anim_func= mat_anim_002;
con->anim_data= malloc(sizeof(MatAnim002));

minus= 800/(con->graph_imgheight-4);

if(minus==0)
minus= 1;

for(i= 0;i<MAXTABLE;i++)
{
if(i> minus)
DATA002(table)[i]= (i-minus)/5;
else
DATA002(table)[i]= 0;
}

/*146:*/
#line 5328 "./matanza.w"

{
int j;

ASSERT(con);

for(j= 0;j<256;j++)
con->graph_palette[j]= COLORRGB(FP(0),FP(1),FP(2));
}

/*:146*/
#line 5313 "./matanza.w"
;

DATA002(loop)= DATA002(sloop)= DATA002(height)= 0;

DATA002(text_pos)= 0;
DATA002(done)= con->graph_imgheight/3;
DATA002(curr)= 0;
}

/*:145*/
#line 5264 "./matanza.w"
;
}

DATA001(delay)++;
}
DATA001(head)+= DATA001(delta);

/*:143*/
#line 5249 "./matanza.w"
;
}

/*:142*/
#line 5057 "./matanza.w"

/*147:*/
#line 5347 "./matanza.w"

void
mat_anim_002(MatConnection*con)
{
unsigned int i,last1,i1,i2;
unsigned char*c;
static char*text= "Welcome to Matanza, the multiplayer, action, "
"network-based, real time, ASCII art based, spaceship, slogan lacking game."
"                                                      "
"Matanza is currently under development by Alejandro Forero Cuervo of the "
"Freaks Unidos.  You can find more information on this organization on the "
"web at <http://bachue.com>."
"                                                      ";

ASSERT(con);

DATA002(height)++;
DATA002(loop)--;

if(DATA002(loop)<0)
{
DATA002(loop)= rand()%3;
DATA002(sloop++);
}

i1= 1;
i2= 4*con->graph_imgwidth+1;

ASSERT(CALC(3)-CALC(4)==con->graph_imgwidth);

for(c= CALC(4);c<CALC(3);c++,i1+= 4,i2-= 4)
{
last1= rand()%min(i1,min(i2,DATA002(height)));
i= rand()%6;
while(c<CALC(3)&&i!=0)
{
*(c)= last1;
last1+= rand()%6-2;
*(c+con->graph_imgwidth)= last1;
last1+= rand()%6-2;
*(c+2*con->graph_imgwidth)= last1;
last1+= rand()%6-2;

c++;
i--;
i1+= 4;
i2-= 4;
}
}

{
unsigned char*c;

c= con->graph_imagebuffer;

while(c<=CALC(4))
*(c++)= DATA002(table)[CALC1(1,-1)+CALC1(1,1)+CALC1(1,0)+CALC1(2,-1)+CALC1(2,1)];
}

{
char buffer[2];

if(!DATA002(done)--)
{
DATA002(done)= con->graph_imgheight/3;

if(DATA002(curr)>=7)
{
if(DATA002(curr)++==13)
DATA002(curr)= 0;
}
else
{
buffer[0]= "Matanza"[DATA002(curr)++];
buffer[1]= 0;

print(con,con->graph_imgwidth/8,con->graph_imgheight/10,
6*con->graph_imgwidth/8,8*con->graph_imgheight/10,
&font,255,buffer);
}
}
}

MAT_GRAPH_RENDER_NOWIPE_ALL(con);

mat_print(con,MAX(con->xwinsize-DATA002(text_pos)-1,0),0,MAT_BOLD,
text+MAX(DATA002(text_pos)-con->xwinsize+1,0),0);

DATA002(text_pos)++;
if(text[MAX(DATA002(text_pos)-con->xwinsize+1,0)]==0)
DATA002(text_pos)= 0;

MAT_FLUSH_ALL(con);
}

/*:147*/
#line 5058 "./matanza.w"

/*161:*/
#line 5957 "./matanza.w"

void
mat_mainmenu_anim(MatConnection*con)
{
static char*text[]= {
"Welcome to Matanga... ",
NULL
};

ASSERT(con);

mat_print(con,MAX(con->xwinsize-DATAMENU(text_pos)-1,0),
con->ywinsize-1,MAT_BOLD,
text[DATAMENU(text_cur)]+MAX(DATAMENU(text_pos)-con->xwinsize+1,0),0);

mat_flush(con,0,con->ywinsize-1,con->xwinsize,con->ywinsize);

if(text[DATAMENU(text_cur)][MAX(DATAMENU(text_pos)-con->xwinsize,0)]==0)
{
DATAMENU(text_pos)= 0;
DATAMENU(text_cur)++;
if(!text[DATAMENU(text_cur)])
DATAMENU(text_cur)= 0;
}
else
DATAMENU(text_pos++);
}

/*:161*/
#line 5059 "./matanza.w"

/*153:*/
#line 5542 "./matanza.w"

void
mat_mainmenu_key(MatConnection*con,int input)
{
MatStateMainMenu*menu;

ASSERT(con->state==MAT_STATE_NORMAL);

menu= con->anim_data;

ASSERT(menu);
ASSERT((menu->focus!=0&&menu->focus!=1)||menu->buflen[menu->focus]>=0);

menu->texterr= MAT_TEXTERR_BLANK;

switch(menu->state)
{
case MENU_STATE_DATA:
switch(input)
{
case 13:
if(menu->focus==3)
{
if(strlen(menu->buffer[0])==0)
{
menu->focus= 0;
menu->texterr= "Enter a user name.";
}
else if(arg_password&&strcmp(arg_password,menu->buffer[1]))
{
menu->buflen[1]= 0;
menu->buffer[1][0]= 0;

menu->focus= 1;
menu->texterr= "Invalid password; try again.";
}
else
{
/*155:*/
#line 5754 "./matanza.w"

{
int slot;
MatUniverse*un;

con->graph_randomval= 60;

ASSERT(arg_ppc> 0);

MAT_UNIVERSES_FIND(un,0);

ASSERT(un);

con->state= MAT_STATE_PLAYING;
con->graph_randomval= 0;
con->anim_func= draw_world;
con->key_handler= arg_ppc==1?player_input_default:player_input_multiple;
con->ship_count= 0;

/*75:*/
#line 2247 "./matanza.w"

{
int i;

con->ship_count= 0;

for(i= 0;i<MAT_CONNECTION_SHIP_HASH_SIZE;i++)
con->ship_hash[i]= NULL;

con->ship_list= 0;
}

/*:75*/
#line 5773 "./matanza.w"
;

MAT_SHIP_VIEW_CHECK(un);

for(slot= 0;slot<arg_ppc;slot++)
/*156:*/
#line 5803 "./matanza.w"

{

MatMovingObj*s;
s= malloc(sizeof(MatMovingObj));
if(!s)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

s->type= MAT_MOVING_OBJ_SHIP;

/*158:*/
#line 5862 "./matanza.w"

{
s->info.player.messages_start= 0;
s->info.player.messages_count= 0;
s->info.player.messages_pos= 0;
s->info.player.messages_enabled= 1;
}

/*:158*/
#line 5816 "./matanza.w"
;
MAT_SHIP_VIEW_DEFAULT(s);

s->refs= 1;

s->img= mat_ship;
s->draw= 1;

s->un= un;

ADD_MOVING_OBJ(s,un);

s->rm_next= NULL;

s->prevtype= NULL;
s->nexttype= un->players_head;

if(un->players_head)
un->players_head->prevtype= s;
else
un->players_tail= s;

un->players_head= s;

strcpy(s->info.player.name,menu->buffer[0]);
s->info.player.times_dead= 0;
s->info.player.game_over= 0;

s->info.player.chat_buffer_len= 0;
s->info.player.chat_buffer[0]= 0;

MAT_CONNECTION_SHIP_ADD(con,s);

start_game(s);
}

/*:156*/
#line 5778 "./matanza.w"


un->players_real+= con->ship_count;

MAT_SHIP_VIEW_CHECK(un);

/*154:*/
#line 5717 "./matanza.w"

{
MatMovingObj*sh;
int size_y;
int slot= 0;

size_y= con->ywinsize/con->ship_count;

ASSERT(arg_imgwidth> 0);

for(sh= con->ship_list;sh;sh= sh->info.player.conn_list_next)
{
ASSERT(sh->type==MAT_MOVING_OBJ_SHIP);

sh->info.player.win_x_s= 0;
sh->info.player.win_x_e= con->xwinsize;
sh->info.player.imgwi= con->xwinsize*2;

sh->info.player.win_y_s= size_y*(slot+0);
sh->info.player.win_y_e= size_y*(slot+1);
sh->info.player.imghe= 2*(sh->info.player.win_y_e-sh->info.player.win_y_s);


ASSERT(sh->info.player.imgwi> 0);
ASSERT(sh->info.player.imghe> 0);

sh->info.player.world_wi= arg_imgwidth;
sh->info.player.world_he= GET_WORLD_HE(sh->info.player,arg_imgwidth);

ASSERT(sh->info.player.world_wi> 0);
ASSERT(sh->info.player.world_he> 0);

slot++;
}
}

/*:154*/
#line 5784 "./matanza.w"
;

#if 0
YYYY
if(p->info.player.team)
{
p->info.player.team_next= p->info.player.team->head;
p->info.player.team->head= p;
}
#endif

/*202:*/
#line 7136 "./matanza.w"

{
MatMovingObj*sh;

ASSERT(con->state==MAT_STATE_PLAYING);

for(sh= con->ship_list;sh;sh= sh->info.player.conn_list_next)
{
ASSERT(sh->type==MAT_MOVING_OBJ_SHIP);
ASSERT(sh->un->players_real>=1);

if(sh->un->players_real==1)
sprintf(message_get(sh),"-=> You are all alone . . .");
else
{
MatSub*i;

MESSAGE_FROM_IP(con,"joins the game");

sprintf(message_get(sh),
"-=> There are %d ships in this universe.",
sh->un->players_real);

for(i= sh->un->subs;i;i= i->u_next)
mat_printf(i->m,"%c%c%c%s%c",MMP_SERVER_DEFAULT_SHIPADD_OTHER,
0,0,sh->info.player.name,0);
}

if(un->pause)
MESSAGE_TO(con,"-=> Time is frozen . . .");
}
}

/*:202*/
#line 5795 "./matanza.w"
;
}

/*:155*/
#line 5580 "./matanza.w"
;
free(con->anim_data);
con->anim_data= NULL;
return;
}
}
else
do
{
menu->focus++;
}
while((menu->focus==1&&!arg_password)||(menu->focus==2&&!arg_teams_count));

break;

case 21:
if(menu->focus==0||menu->focus==1)
{
menu->buflen[menu->focus]= 0;
menu->buffer[menu->focus][0]= 0;
}
break;

case 27:
menu->state= MENU_STATE_KEY;
break;

case 3:
mat_connection_free(con,MMP_SERVER_CLOSE_CLIENT,"User quit.");
return;

case 127:
case 8:
if((menu->focus==0||menu->focus==1)&&menu->buflen[menu->focus]> 0)
{
menu->buflen[menu->focus]--;
menu->buffer[menu->focus][menu->buflen[menu->focus]]= 0;
}
break;

default:
if(menu->focus==2)
{
switch(input)
{
case'h':
menu->team= menu->team->prev;
if(!menu->team)
menu->team= arg_teams_tail;
break;
case'l':
menu->team= menu->team->next;
if(!menu->team)
menu->team= arg_teams_head;
break;
}
}
else if(isalnum(input)&&(isalpha(input)||menu->buflen[menu->focus]> 0)
&&(menu->focus!=0||menu->buflen[0]<MAT_USER_MAX)
&&(menu->focus!=1||menu->buflen[1]<MAT_PASSWORD_MAX)
&&menu->focus!=3)
{
menu->buffer[menu->focus][menu->buflen[menu->focus]++]= input;
menu->buffer[menu->focus][menu->buflen[menu->focus]]= 0;
}
else
VERBOSE("Invalid character: %d\n",input);

break;
}
break;

case MENU_STATE_KEY:
if(input!=91)
{
VERBOSE("%s:%d: Unknown input: %d\n",__FILE__,__LINE__,input);
menu->state= MENU_STATE_DATA;
}
else
menu->state= MENU_STATE_KEYREAL;
break;

case MENU_STATE_KEYREAL:
switch(input)
{
case 65:
do
{
menu->focus--;
}
while((menu->focus==1&&!arg_password)||(menu->focus==2&&!arg_teams_count));
if(menu->focus==-1)
menu->focus= 3;
break;

case 66:
do
{
menu->focus++;
}
while((menu->focus==1&&!arg_password)||(menu->focus==2&&!arg_teams_count));
if(menu->focus==4)
menu->focus= 0;
break;

case 67:
if(menu->focus==2)
{
#if 0
p->info.player.team= p->info.player.team->prev;
if(!p->info.player.team)
p->info.player.team= arg_teams_tail;
#endif
}
break;

case 68:
if(menu->focus==2)
{
#if 0
p->info.player.team= p->info.player.team->next;
if(!p->info.player.team)
p->info.player.team= arg_teams_head;
#endif
}
break;

default:
VERBOSE("%s:%d: Unknown input: %d\n",__FILE__,__LINE__,input);
}
menu->state= MENU_STATE_DATA;
}

/*160:*/
#line 5900 "./matanza.w"

{
int p= 10;

ASSERT(menu);

mat_print(con,10,p,menu->focus==0?MAT_RED_BOLD:MAT_RED,"User:",0);
mat_print(con,21,p,MAT_BLUE,menu->focus==0?"-=> [":"    [",0);
mat_print(con,28+MAT_USER_MAX,p,MAT_BLUE,
menu->focus==0?"] <=-":"]    ",0);
mat_print(con,27,p,MAT_NORMAL,MAT_USER_BLANK,0);
mat_print(con,27,p,MAT_NORMAL,menu->buffer[0],0);
mat_flush(con,10,p,33+MAT_USER_MAX,p+1);

p+= 2;

if(arg_password)
{
mat_print(con,10,p,menu->focus==1?MAT_RED_BOLD:MAT_RED,"Password:",0);
mat_print(con,21,p,MAT_BLUE,menu->focus==1?"-=> [":"    [",0);
mat_print(con,28+MAT_PASSWORD_MAX,p,MAT_BLUE,menu->focus==1?"] <=-":"]    ",0);
mat_print(con,27,p,MAT_NORMAL,MAT_PASSWORD_BLANK,0);
mat_print(con,27,p,MAT_NORMAL,menu->buffer[1],0);
mat_flush(con,10,p,33+MAT_USER_MAX,p+1);

p+= 2;
}

if(arg_teams_count)
{
#if 0
YYYYY
ASSERT(con->ship->info.player.team);
ASSERT(con->ship->info.player.team->name);

mat_print(&p->info.player,10,pos,menu->focus==2?MAT_RED_BOLD:MAT_RED,"Team:");
mat_print(&p->info.player,21,pos,MAT_BLUE,menu->focus==2?"-=> [":"    [");
mat_print(&p->info.player,28+MAT_TEAM_MAX,pos,MAT_BLUE,
menu->focus==2?"] <=-":"]    ");
mat_print(&p->info.player,27,pos,MAT_NORMAL,MAT_TEAM_BLANK);
mat_print(&p->info.player,27,pos,MAT_NORMAL,p->info.player.team->name);
mat_flush(p,10,pos,33+MAT_TEAM_MAX,pos+1);

pos+= 2;
#endif
}

if(menu->texterr)
{
ASSERT(strlen(menu->texterr)<MAT_TEXTERR_MAX);
mat_print(con,10,p,MAT_RED_BOLD,menu->texterr,0);
mat_flush(con,10,p,8+MAT_TEXTERR_MAX,p+1);
}
}

/*:160*/
#line 5713 "./matanza.w"
;
}

/*:153*/
#line 5060 "./matanza.w"


/*:133*//*150:*/
#line 5474 "./matanza.w"

void
main_menu_begin(MatConnection*con)
{
int c;

MatStateMainMenu*menu;

ASSERT(con);

TERM_CLEAR_IMAGE(con);

c= con->xwinsize*con->ywinsize;

memset(con->graph_textbuffer,' ',c);
memset(con->graph_attrbuffer,MAT_NORMAL,c);

TERM_CLEAR_SCREEN(con);

/*152:*/
#line 5515 "./matanza.w"

{
ASSERT(con);

menu= malloc(sizeof(MatStateMainMenu));

menu->focus= 0;
menu->state= MENU_STATE_DATA;

/*73:*/
#line 2182 "./matanza.w"

{
static char*name[]= 
{
"Joe","CmdrTaco","Rob","Pong","Hob","John","Pepe","Moe","Bart",
"Cmdr","Hemos","Azul","Bull","Hal","Fox","Zeus","Odin","Thor",
"Ra","God","Star","Cow","Jack","Pat","Dude","Wyrm","Poet","Llama",
"Argos","Galactus","Javo","Vulpex","MrPong","JoeCool","Morgon",
"Magneto","Polux","Magician","Vader","Draco","Dragon","Demon","DJ",
"Mystery","Killer","Slayer","Vampire","Paco","Gato","Midnight",
"Spock","Kirk","Bastard","Reindeer","Hitler","Stalin","Lenin",
"Guevara","Fidel","Khan","Napoleon","Ulises","Futura","Tux",
"Mozilla","Duke","Bowie","SpaceBoy","Gorilla","Godzilla","Chuk",
"Mercury","Silver","Blake","Stallman","Raymond","Torvalds","Wall",
"Gates","Jobs","Michael","Abyss","DotCom","Dolly","Sturm","Tanis",
"Eastwood","Arnold","Joey","Joy","Snake","Anaconda","Orb","Erinyes",
"Eyes","Shadow","Andy","Pett","Frog","Drop","Hell","Mega","Hard",
"Dharma","Punk","Jesse","Ugo","Dancer","Zuul","Pike","Duck",
"Derek","Eric","Richard","ESR","RMS","Master","Bill","Steve",
"Hax0r","Lamer","Cracker","Dood","Kiddo","Waine","Kent","Wright",
"Stephen","Fred","Tintin","Haddock","Milu","Shiva","Apollo","Mars",
"Jupiter","Butthead","Beavis","ElCHAVO","Laid","Rex","Riff",
"Hunter","Elvis","Hendrix","MajorTom","Moe","Musician","Cat",
"Vladimir","Tricky","Darwin","Freud","Einstein","Newton","Hitman",
"Tato","Pigidik","NOD"
};

int ch;

ch= rand()%(sizeof(name)/sizeof(char*));

menu->buflen[0]= strlen(name[ch]);
strncpy(menu->buffer[0],name[ch],menu->buflen[0]+1);
}

/*:73*/
#line 5524 "./matanza.w"
;

menu->buflen[1]= 0;
menu->buffer[1][0]= 0;

menu->text_pos= 0;
menu->text_cur= 0;

menu->texterr= NULL;
}

/*:152*/
#line 5493 "./matanza.w"
;

con->anim_func= mat_mainmenu_anim;
con->anim_data= menu;
con->key_handler= mat_mainmenu_key;

/*160:*/
#line 5900 "./matanza.w"

{
int p= 10;

ASSERT(menu);

mat_print(con,10,p,menu->focus==0?MAT_RED_BOLD:MAT_RED,"User:",0);
mat_print(con,21,p,MAT_BLUE,menu->focus==0?"-=> [":"    [",0);
mat_print(con,28+MAT_USER_MAX,p,MAT_BLUE,
menu->focus==0?"] <=-":"]    ",0);
mat_print(con,27,p,MAT_NORMAL,MAT_USER_BLANK,0);
mat_print(con,27,p,MAT_NORMAL,menu->buffer[0],0);
mat_flush(con,10,p,33+MAT_USER_MAX,p+1);

p+= 2;

if(arg_password)
{
mat_print(con,10,p,menu->focus==1?MAT_RED_BOLD:MAT_RED,"Password:",0);
mat_print(con,21,p,MAT_BLUE,menu->focus==1?"-=> [":"    [",0);
mat_print(con,28+MAT_PASSWORD_MAX,p,MAT_BLUE,menu->focus==1?"] <=-":"]    ",0);
mat_print(con,27,p,MAT_NORMAL,MAT_PASSWORD_BLANK,0);
mat_print(con,27,p,MAT_NORMAL,menu->buffer[1],0);
mat_flush(con,10,p,33+MAT_USER_MAX,p+1);

p+= 2;
}

if(arg_teams_count)
{
#if 0
YYYYY
ASSERT(con->ship->info.player.team);
ASSERT(con->ship->info.player.team->name);

mat_print(&p->info.player,10,pos,menu->focus==2?MAT_RED_BOLD:MAT_RED,"Team:");
mat_print(&p->info.player,21,pos,MAT_BLUE,menu->focus==2?"-=> [":"    [");
mat_print(&p->info.player,28+MAT_TEAM_MAX,pos,MAT_BLUE,
menu->focus==2?"] <=-":"]    ");
mat_print(&p->info.player,27,pos,MAT_NORMAL,MAT_TEAM_BLANK);
mat_print(&p->info.player,27,pos,MAT_NORMAL,p->info.player.team->name);
mat_flush(p,10,pos,33+MAT_TEAM_MAX,pos+1);

pos+= 2;
#endif
}

if(menu->texterr)
{
ASSERT(strlen(menu->texterr)<MAT_TEXTERR_MAX);
mat_print(con,10,p,MAT_RED_BOLD,menu->texterr,0);
mat_flush(con,10,p,8+MAT_TEXTERR_MAX,p+1);
}
}

/*:160*/
#line 5499 "./matanza.w"
;
}

/*:150*//*167:*/
#line 6229 "./matanza.w"

void
mat_connection_free(MatConnection*con,unsigned char reason,char*desc)
{
ASSERT(con->state!=MAT_STATE_REMOVE);

if(con->state==MAT_STATE_PLAYING||con->state==MAT_STATE_MACHINE)
/*165:*/
#line 6191 "./matanza.w"

{
MatMovingObj*tmp;

while(con->ship_list)
{
/*166:*/
#line 6208 "./matanza.w"

{
MatUniverse*un;
MatSub*c;
char*name;

name= con->ship_list->info.player.name;
un= con->ship_list->un;

for(c= un->subs;c;c= c->u_next)
mat_printf(c->m,"%c%c%c%s%c",
MMP_SERVER_DEFAULT_SHIPRM,
un->id&0xff00,un->id&0x00ff,name,0);
}

/*:166*/
#line 6197 "./matanza.w"
;

con->ship_list->info.player.conn= NULL;

tmp= con->ship_list->info.player.conn_list_next;
mat_moving_obj_unref(con->ship_list);
con->ship_list= tmp;
}
}

/*:165*/
#line 6236 "./matanza.w"
;

if(con->state!=MAT_STATE_MACHINE)
{
/*113:*/
#line 3708 "./matanza.w"

{
free(con->graph_imagebuffer);
free(con->graph_textbuffer);
free(con->graph_textbufferold);
free(con->graph_attrbuffer);
free(con->graph_attrbufferold);

TERM_CLEAR_SCREEN(con);
TERM_SHOW_CURSOR(con);
TERM_MOVE_CURSOR(con,0,0);
}

/*:113*/
#line 6240 "./matanza.w"
;

free(con->buffer);

mat_printf(con,
"You have been disconnected from the server.\r\nReason: %s\r\n\r\n"
"Thanks for playing Matanza.\r\n"
"FU Matanza %s\r\n%s\r\n",
desc,VERSION,"Copyright 2000 Alejandro Forero Cuervo");
}
else
{
mat_sub_machine_rm(con);
mat_printf(con,"%c%c",MMP_SERVER_CLOSE,reason);
if(reason==MMP_SERVER_CLOSE_SYSERROR||reason==MMP_SERVER_CLOSE_MMPERROR)
mat_printf(con,"%s%c",desc,0);
}

mat_out_flush(con);

con->state= MAT_STATE_REMOVE;

free(con->addr);
free(con->out_buf);
free(con->anim_data);
SOCKET_CLOSE_GENERIC(con->fd);
}

/*:167*//*184:*/
#line 6584 "./matanza.w"

#if MATANZA_ASSERT
void assert_exit(void)
{
exit(-1);
}
#endif

/*:184*//*199:*/
#line 7091 "./matanza.w"

void
start_game(MatMovingObj*ship)
{
ASSERT(ship);
ASSERT(ship->type==MAT_MOVING_OBJ_SHIP);
ASSERT(ship->un);

ship->crash= 0;
ship->alpha= 0.0;
ship->alpha_mod= mat_alpha_mod_ship_appear;

/*292:*/
#line 9458 "./matanza.w"

{
ship->pos_x= (double)(rand()%ship->un->mapsize_x);
ship->pos_y= (double)(rand()%ship->un->mapsize_y);

ship->ang= (double)(rand()%arg_ang);
ship->sp_ang= arg_ang_speed_max==0?0:(double)(rand()%5-2)/10;
ship->sp= 0;
ship->sp_x= 0;
ship->sp_y= 0;
}

/*:292*/
#line 7103 "./matanza.w"
;
/*200:*/
#line 7114 "./matanza.w"

{
ship->info.player.ship_bullets[0]= 20000;
ship->info.player.ship_bullets[1]= 7;
ship->info.player.ship_bullets[2]= 2;
ship->info.player.ship_bullets[3]= 0;

ship->info.player.bullets_expire= 0;
}

/*:200*/
#line 7104 "./matanza.w"
;

ship->info.player.visible= 1;
ship->info.player.visible_exp= arg_visible_init;
ship->info.player.health= ship->un->health;
ship->info.player.ship_speed_inc= 0;
ship->pal= mat_ship_palette[2];
}

/*:199*//*203:*/
#line 7171 "./matanza.w"

void
player_input_buffer(MatConnection*con,int key)
{
ASSERT(con);
ASSERT(con->state==MAT_STATE_PLAYING);
ASSERT(con->ship_count==1);

switch(key)
{
case 13:
ship_key_chat_end(con);
break;

case 21:
ship_key_chat_wipe(con->ship_list);
break;

case 127:
case 8:
ship_key_chat_backspace(con->ship_list);
break;

default:
ship_key_chat_add(con->ship_list,key);
break;
}
}

/*:203*//*204:*/
#line 7205 "./matanza.w"

void
player_input_quit(MatConnection*con,int key)
{
ASSERT(con->state==MAT_STATE_PLAYING);

switch(tolower(key))
{
case'q':
case'y':
ship_key_quit(con,1);
break;
default:
ship_key_quit_cancel(con);
break;
}
}

/*:204*//*205:*/
#line 7229 "./matanza.w"

void
player_input_multiple(MatConnection*con,int key)
{
ASSERT(con);

ASSERT(con->ship_count==2);

ASSERT(con->ship_hash[0]);
ASSERT(con->ship_hash[0]->type==MAT_MOVING_OBJ_SHIP);
ASSERT(con->ship_hash[0]->info.player.conn_id==0);
ASSERT(con->ship_hash[0]->refs>=0);

ASSERT(con->ship_hash[1]);
ASSERT(con->ship_hash[1]->type==MAT_MOVING_OBJ_SHIP);
ASSERT(con->ship_hash[1]->info.player.conn_id==1);
ASSERT(con->ship_hash[1]->refs>=0);

ASSERT(con->ship_hash[0]->un==con->ship_hash[1]->un);

switch(key)
{
case KEY_ARROW_UP:
ship_key_up(con->ship_hash[0]);
break;
case KEY_ARROW_DOWN:
ship_key_down(con->ship_hash[0]);
break;
case KEY_ARROW_RIGHT:
ship_key_right(con->ship_hash[0]);
break;
case KEY_ARROW_LEFT:
ship_key_left(con->ship_hash[0]);
break;
case'1':
mat_bullet_new_player(con->ship_hash[0],0,1);
break;
case'2':
mat_bullet_new_player(con->ship_hash[0],1,1);
break;
case'3':
mat_bullet_new_player(con->ship_hash[0],2,1);
break;
case'k':
ship_key_up(con->ship_hash[1]);
break;
case'j':
ship_key_down(con->ship_hash[1]);
break;
case'l':
ship_key_right(con->ship_hash[1]);
break;
case'h':
ship_key_left(con->ship_hash[1]);
break;
case' ':
mat_bullet_new_player(con->ship_hash[1],0,1);
break;
case'n':
mat_bullet_new_player(con->ship_hash[1],1,1);
break;
case'm':
mat_bullet_new_player(con->ship_hash[1],2,1);
break;
case'z':
ship_key_stats(con->ship_hash[1]);
break;
case'0':
ship_key_stats(con->ship_hash[0]);
break;
case'p':
ship_key_pause(con->ship_hash[0]);
break;
case'-':
ship_key_zoom_out(con->ship_hash[1]);
break;
case'=':
ship_key_zoom_in(con->ship_hash[1]);
break;
case'/':
ship_key_zoom_out(con->ship_hash[0]);
break;
case'*':
ship_key_zoom_in(con->ship_hash[0]);
break;
}
}

/*:205*//*206:*/
#line 7319 "./matanza.w"

void
machine_input_initial(MatConnection*m,int key)
{
switch(key)
{
case MMP_CLIENT_INITIAL_ID:
/*207:*/
#line 7336 "./matanza.w"

{
ASSERT(m);

m->key_handler= machine_input_string;

m->info.m.string_maxlength= 256;
m->info.m.string= NULL;
m->info.m.string_len= 0;
m->info.m.string_siz= 0;

m->info.m.handler= machine_input_arg_id_name;
}

/*:207*/
#line 7326 "./matanza.w"
;
break;

default:
/*211:*/
#line 7416 "./matanza.w"

{
char buffer[sizeof("Client sent unknown command: ?")+1];

VERBOSE("Unknown command from machine: %d (%c)\n",key,key);

sprintf(buffer,"Client sent unknown command: %c",key);

mat_connection_free(m,MMP_SERVER_CLOSE_MMPERROR,buffer);
}

/*:211*/
#line 7330 "./matanza.w"
;
break;
}
}

/*:206*//*208:*/
#line 7351 "./matanza.w"

void
machine_input_arg_id_name(MatConnection*m)
{
VERBOSE("[Machine:%s]\n",m->info.m.string);

free(m->info.m.string);

m->key_handler= machine_input_string;

m->info.m.string_maxlength= 256;
m->info.m.string= NULL;
m->info.m.string_len= 0;
m->info.m.string_siz= 0;

m->info.m.handler= machine_input_arg_id_ver;
}

/*:208*//*209:*/
#line 7370 "./matanza.w"

void
machine_input_arg_id_ver(MatConnection*m)
{
VERBOSE("[Version:%s]\n",m->info.m.string);

free(m->info.m.string);

mat_printf(m,"%c%s%c%s%c",MMP_SERVER_INITIAL_CONNECTED,PACKAGE,0,VERSION,0);
mat_out_flush(m);

m->key_handler= machine_input_default;
}

/*:209*//*210:*/
#line 7385 "./matanza.w"

void
machine_input_default(MatConnection*m,int key)
{
switch(key)
{
case MMP_CLIENT_DEFAULT_JOIN:
VERBOSE("Command: join\n");
/*220:*/
#line 7623 "./matanza.w"

{
ASSERT(m);

m->key_handler= machine_input_number;

m->info.m.number_byte= 2;
m->info.m.number= 0;
m->info.m.handler= machine_input_arg_join;
}

/*:220*/
#line 7393 "./matanza.w"
;
break;

case MMP_CLIENT_DEFAULT_SHIPADD:
VERBOSE("Command: shipadd\n");
/*212:*/
#line 7430 "./matanza.w"

{
ASSERT(m);

m->key_handler= machine_input_number;

m->info.m.number_byte= 2;
m->info.m.number= 0;
m->info.m.handler= machine_input_arg_ship_add_string;
}

/*:212*/
#line 7398 "./matanza.w"
;
break;

default:
/*211:*/
#line 7416 "./matanza.w"

{
char buffer[sizeof("Client sent unknown command: ?")+1];

VERBOSE("Unknown command from machine: %d (%c)\n",key,key);

sprintf(buffer,"Client sent unknown command: %c",key);

mat_connection_free(m,MMP_SERVER_CLOSE_MMPERROR,buffer);
}

/*:211*/
#line 7402 "./matanza.w"
;
break;

#if 0
case MMP_CLIENT_DEFAULT_UNIVERSES:
<Send a list with all the universes to machine|m|> ;
break;
#endif
}
}

/*:210*//*213:*/
#line 7443 "./matanza.w"

void
machine_input_arg_ship_add_string(MatConnection*m)
{
ASSERT(m);

m->key_handler= machine_input_string;

m->info.m.string_maxlength= 8;
m->info.m.string= NULL;
m->info.m.string_len= 0;
m->info.m.string_siz= 0;

m->info.m.handler= machine_input_arg_ship_add;
}

/*:213*//*214:*/
#line 7467 "./matanza.w"

void
machine_input_number(MatConnection*m,int key)
{
ASSERT(m->info.m.number_byte> 0);

ASSERT(0<=key);
ASSERT(key<255);

m->info.m.number= m->info.m.number*255+key;

if(--m->info.m.number_byte==0)
m->info.m.handler(m);
}

/*:214*//*215:*/
#line 7490 "./matanza.w"

void
machine_input_string(MatConnection*m,int key)
{
if(m->info.m.string_len==m->info.m.string_maxlength)
return;

if(m->info.m.string_len==m->info.m.string_siz)
/*216:*/
#line 7507 "./matanza.w"

{
m->info.m.string_siz= m->info.m.string_siz?m->info.m.string_siz*2:256;
m->info.m.string= realloc(m->info.m.string,m->info.m.string_siz+1);
if(!m->info.m.string)
{

fprintf(stderr,"%s: realloc: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
}

/*:216*/
#line 7498 "./matanza.w"


m->info.m.string[m->info.m.string_len++]= key;

if(key==0)
m->info.m.handler(m);
}

/*:215*//*217:*/
#line 7520 "./matanza.w"

void
machine_input_arg_ship_add(MatConnection*m)
{
MatUniverse*un;

ASSERT(m);

m->key_handler= machine_input_default;

MAT_UNIVERSES_FIND(un,m->info.m.number);

if(!un)
{
MAT_PROTOCOL_ERROR_SHIPADD(m,MMP_SERVER_SHIPADDFAIL_UNEXISTANT,(char*)NULL);
return;
}

VERBOSE("Adding ship to universe: %d\n",un->id);

/*219:*/
#line 7563 "./matanza.w"

{
MatMovingObj*s;

s= malloc(sizeof(MatMovingObj));
if(!s)
{
mat_connection_free(m,MMP_SERVER_CLOSE_SYSERROR,strerror(errno));
return;
}

s->type= MAT_MOVING_OBJ_SHIP;

/*158:*/
#line 5862 "./matanza.w"

{
s->info.player.messages_start= 0;
s->info.player.messages_count= 0;
s->info.player.messages_pos= 0;
s->info.player.messages_enabled= 1;
}

/*:158*/
#line 7576 "./matanza.w"
;
MAT_SHIP_VIEW_DEFAULT(s);

s->refs= 1;

s->img= mat_ship;
s->draw= 1;

s->un= un;

un->players_real++;

ADD_MOVING_OBJ(s,un);

s->rm_next= NULL;

s->prevtype= NULL;
s->nexttype= un->players_head;

if(un->players_head)
un->players_head->prevtype= s;
else
un->players_tail= s;

un->players_head= s;

ASSERT(m->info.m.string_len<=MAT_USER_MAX);

strcpy(s->info.player.name,m->info.m.string);

s->info.player.times_dead= 0;
s->info.player.game_over= 0;

s->info.player.chat_buffer_len= 0;
s->info.player.chat_buffer[0]= 0;

MAT_CONNECTION_SHIP_ADD(m,s);

MAT_SHIP_VIEW_CHECK(s->un);

start_game(s);

message_broadcast(un,"-=> %s (%s) joins the game",s->info.player.name,m->addr);
}

/*:219*/
#line 7540 "./matanza.w"
;
/*218:*/
#line 7548 "./matanza.w"

{
MatSub*i;

ASSERT(un);

for(i= un->subs;i;i= i->u_next)
if(i->m!=m)
mat_printf(i->m,"%c%c%c%s%c",
MMP_SERVER_DEFAULT_SHIPADD_OTHER,
0,0,m->info.m.string,0);
}

/*:218*/
#line 7541 "./matanza.w"
;

mat_printf(m,"%c",MMP_SERVER_DEFAULT_SHIPADD_CLIENT);
mat_out_flush(m);
}

/*:217*//*221:*/
#line 7639 "./matanza.w"

void
machine_input_arg_join(MatConnection*m)
{
MatUniverse*un;

ASSERT(m);

m->key_handler= machine_input_default;

MAT_UNIVERSES_FIND(un,m->info.m.number)

if(!un)
{
MAT_PROTOCOL_ERROR_JOIN(m,MMP_SERVER_JOINFAIL_UNEXISTANT);
return;
}

VERBOSE("Machine attempts to join universe: [%d]\n",un->id);

/*224:*/
#line 7689 "./matanza.w"

{
if(!mat_sub_add(m,un))
{
mat_connection_free(m,MMP_SERVER_CLOSE_SYSERROR,strerror(errno));
return;
}
}

/*:224*/
#line 7659 "./matanza.w"
;
/*225:*/
#line 7701 "./matanza.w"

{
MatMovingObj*pl;

mat_printf(m,"%c",MMP_SERVER_DEFAULT_JOIN_OK);

for(pl= un->players_head;pl;pl= pl->nexttype)
mat_printf(m,"%s%c",pl->info.player.name,0);

mat_printf(m,"%c",0);

mat_out_flush(m);
}

/*:225*/
#line 7660 "./matanza.w"
;
}

/*:221*//*227:*/
#line 7724 "./matanza.w"

void
player_input_default(MatConnection*con,int key)
{
ASSERT(con);
ASSERT(con->state==MAT_STATE_PLAYING);
ASSERT(con->ship_count==1);

ASSERT(con->ship_hash[0]);
ASSERT(con->ship_hash[0]->type==MAT_MOVING_OBJ_SHIP);
ASSERT(con->ship_hash[0]->info.player.conn_id==0);
ASSERT(con->ship_hash[0]->refs>=0);

switch(key)
{
case'[':
ship_key_view_prev(con->ship_hash[0]);
break;

case']':
ship_key_view_next(con->ship_hash[0]);
break;

case'-':
case'_':
ship_key_zoom_out(con->ship_hash[0]);
break;

case'=':
case'+':
ship_key_zoom_in(con->ship_hash[0]);
break;

case'q':
ship_key_quit(con,0);
break;

case'Q':
ship_key_quit(con,1);
break;

case'p':
ship_key_pause(con->ship_hash[0]);
break;

case'w':
ship_key_who(con->ship_hash[0]);
break;

case'i':
ship_key_visibility(con->ship_hash[0]);
break;

case'l':
case KEY_ARROW_RIGHT:
ship_key_right(con->ship_hash[0]);
break;

case KEY_ARROW_LEFT:
case'h':
ship_key_left(con->ship_hash[0]);
break;

case'k':
case KEY_ARROW_UP:
ship_key_up(con->ship_hash[0]);
break;

case'j':
case KEY_ARROW_DOWN:
ship_key_down(con->ship_hash[0]);
break;

case' ':
mat_bullet_new_player(con->ship_hash[0],0,1);
break;

case'b':
mat_bullet_new_player(con->ship_hash[0],0,-1);
break;

case'n':
mat_bullet_new_player(con->ship_hash[0],1,1);
break;

case'm':
mat_bullet_new_player(con->ship_hash[0],2,1);
break;

case's':
ship_key_swappos(con->ship_hash[0]);
break;

case'c':
ship_key_messages_less(con->ship_hash[0]);
break;

case'z':
ship_key_stats(con->ship_hash[0]);
break;

case'C':
ship_key_messages_clean(con->ship_hash[0]);
break;

case'v':
ship_key_messages_view(con->ship_hash[0]);
break;

case 13:
ship_key_chat_start(con);
break;

default:
VERBOSE("Ignored Input: [key:%d][state:player_input_default]\n",key);
}
}

/*:227*//*228:*/
#line 7843 "./matanza.w"

void
ship_key_quit(MatConnection*con,int force)
{
if(!force)
{
MatMovingObj*sh;


ASSERT(con->ship_count> 0);

con->key_handler= player_input_quit;
for(sh= con->ship_list;sh;sh= sh->info.player.conn_list_next)
sprintf(message_get(sh),"-=> Are you sure you want to quit?");
}
else
{
MESSAGE_FROM(con,"quits the game.");
mat_connection_free(con,MMP_SERVER_CLOSE_CLIENT,"User quit.  Bye bye.");
}
}

/*:228*//*229:*/
#line 7866 "./matanza.w"

void
ship_key_quit_cancel(MatConnection*con)
{
MatMovingObj*sh;
static char*msg[]= 
{
"-=> I knew it!",
"-=> Good!  Have fun! :)",
"-=> Hahahah, I knew you couldn't quit!",
"-=> Great!",
"-=> Wonderful...",
"-=> Ooooer, stay stay stay! :)",
"-=> I knew you weren't such a chicken!",
"-=> Phew, you scared me.",
"-=> Good.  Now kill them all, you bastard!"
};

ASSERT(con->ship_count> 0);

con->key_handler= player_input_default;

for(sh= con->ship_list;sh;sh= sh->info.player.conn_list_next)
sprintf(message_get(sh),"%s",msg[rand()%(sizeof(msg)/sizeof(char*))]);
}

/*:229*//*230:*/
#line 7893 "./matanza.w"

void
ship_key_chat_wipe(MatMovingObj*ship)
{
ship->info.player.chat_buffer_len= 0;
ship->info.player.chat_buffer[0]= 0;
}

/*:230*//*231:*/
#line 7902 "./matanza.w"

void
ship_key_chat_backspace(MatMovingObj*ship)
{
if(ship->info.player.chat_buffer_len> 0)
{
ship->info.player.chat_buffer_len--;
ship->info.player.chat_buffer[ship->info.player.chat_buffer_len]= 0;
}
}

/*:231*//*232:*/
#line 7914 "./matanza.w"

void
ship_key_messages_clean(MatMovingObj*ship)
{
ship->info.player.messages_count= 0;
}

/*:232*//*233:*/
#line 7922 "./matanza.w"

void
ship_key_messages_view(MatMovingObj*ship)
{
ship->info.player.messages_enabled= !ship->info.player.messages_enabled;
}

/*:233*//*234:*/
#line 7930 "./matanza.w"

void
ship_key_chat_start(MatConnection*con)
{
if(arg_chat)
con->key_handler= player_input_buffer;
}

/*:234*//*235:*/
#line 7940 "./matanza.w"

void
ship_key_chat_end(MatConnection*con)
{
MatShip*pl;

ASSERT(con->ship_count==1);

con->key_handler= player_input_default;

pl= &con->ship_hash[0]->info.player;

pl->chat_buffer[pl->chat_buffer_len]= 0;
if(pl->chat_buffer_len> 0)
{
message_broadcast(con->ship_hash[0]->un,"%s> %s",pl->name,pl->chat_buffer);
pl->chat_buffer_len= 0;
pl->chat_buffer[0]= 0;
pl->messages_enabled= 1;
}
}

/*:235*//*236:*/
#line 7963 "./matanza.w"

void
ship_key_messages_less(MatMovingObj*ship)
{
if(ship->info.player.messages_count> 0)
{
ship->info.player.messages_count-= 1;
ship->info.player.messages_start+= 1;
ship->info.player.messages_start%= MAXMESSAGES;
}
}

/*:236*//*237:*/
#line 7976 "./matanza.w"

void
ship_key_swappos(MatMovingObj*ship)
{
ship->info.player.messages_pos= !ship->info.player.messages_pos;
}

/*:237*//*238:*/
#line 7984 "./matanza.w"

void
ship_key_pause(MatMovingObj*ship)
{
char*msg;

ship->un->pause= !ship->un->pause;

msg= ship->un->pause?"freezes time":"makes time go on";
message_broadcast(ship->un,"-=> %s %s . . .",ship->info.player.name,msg);
}

/*:238*//*239:*/
#line 7999 "./matanza.w"

void
ship_key_who(MatMovingObj*ship)
{
MatMovingObj*pl;
char*msg;
int i= MAXMESSAGELEN;

ASSERT(ship->type==MAT_MOVING_OBJ_SHIP);
ASSERT(MAT_USER_MAX<MAXMESSAGELEN);

msg= message_get(ship);
i= sizeof("-=> Players: ")-1;

sprintf(msg,"-=> Players: ");
for(pl= ship->un->players_head;pl;pl= pl->nexttype)
{
char*name;

ASSERT(pl->type==MAT_MOVING_OBJ_SHIP);
ASSERT(pl->un==ship->un);

name= pl->info.player.name;
ASSERT(name);

if(i+strlen(name)+2+3>=MAXMESSAGELEN)
{
msg[i]= 0;
msg= message_get(ship);
i= 4;

sprintf(msg,"    ");
}

sprintf(msg+i,"[%s:%02d]",name,LIVES(pl));

i+= strlen(name)+2+3;
}
}

/*:239*//*240:*/
#line 8049 "./matanza.w"

void
ship_key_stats(MatMovingObj*ship)
{
ship->info.player.messages_enabled= 1;

sprintf(message_get(ship),"[lives:%02d][health:%02d%%][players:%02d]",
LIVES(ship),ship->info.player.health> 0?HEALTH(ship):0,ship->un->players_real);
}

/*:240*//*246:*/
#line 8115 "./matanza.w"

#if MATANZA_ASSERT
void
mat_ship_view_check(MatUniverse*un)
{
MatMovingObj*ship;
int count_total= 0,count_view= 0;

for(ship= un->players_head;ship;ship= ship->nexttype)
{
MatMovingObj*i;

count_total++;

for(i= ship->info.player.viewers;i;i= i->info.player.view_next)
{
count_view++;
ASSERT(i->info.player.view==ship);

if(i->info.player.view_next)
ASSERT(i->info.player.view_next->info.player.view_prev==i);

if(!i->info.player.view_prev)
ASSERT(i==ship->info.player.viewers);
}
}

ASSERT(count_total==count_view);
}
#endif

/*:246*//*248:*/
#line 8157 "./matanza.w"

void
ship_key_view_prev(MatMovingObj*ship)
{
ASSERT(ship);
ASSERT(ship->refs> 0);
ASSERT(ship->info.player.view);

ASSERT(ship->info.player.view->refs> 0);

MAT_SHIP_VIEW_CHECK(ship->un);

/*247:*/
#line 8147 "./matanza.w"

{
if(ship->un->players_real==1)
{
sprintf(message_get(ship),"-=> You are the only player in this universe!\n");
return;
}
}

/*:247*/
#line 8169 "./matanza.w"
;

MAT_SHIP_VIEW_RM(ship);

ASSERT(ship->un->players_tail);

ship->info.player.view= ship->info.player.view->prevtype;
if(!ship->info.player.view)
ship->info.player.view= ship->un->players_tail;

ASSERT(ship->info.player.view);

/*243:*/
#line 8088 "./matanza.w"

{
if(ship->info.player.view->info.player.viewers)
ship->info.player.view->info.player.viewers->info.player.view_prev= ship;

ship->info.player.view_prev= NULL;
ship->info.player.view_next= ship->info.player.view->info.player.viewers;

ship->info.player.view->info.player.viewers= ship;
}

/*:243*/
#line 8181 "./matanza.w"
;


SHIP_KEY_VIEW_LABEL(ship);

MAT_SHIP_VIEW_CHECK(ship->un);
}

/*:248*//*249:*/
#line 8190 "./matanza.w"

void
ship_key_view_next(MatMovingObj*ship)
{
ASSERT(ship);
ASSERT(ship->refs> 0);
ASSERT(ship->info.player.view);

ASSERT(ship->info.player.view->refs> 0);

MAT_SHIP_VIEW_CHECK(ship->un);

/*247:*/
#line 8147 "./matanza.w"

{
if(ship->un->players_real==1)
{
sprintf(message_get(ship),"-=> You are the only player in this universe!\n");
return;
}
}

/*:247*/
#line 8202 "./matanza.w"
;

MAT_SHIP_VIEW_RM(ship);

ASSERT(ship->un->players_head);

ship->info.player.view= ship->info.player.view->nexttype;
if(!ship->info.player.view)
ship->info.player.view= ship->un->players_head;

ASSERT(ship->info.player.view);

/*243:*/
#line 8088 "./matanza.w"

{
if(ship->info.player.view->info.player.viewers)
ship->info.player.view->info.player.viewers->info.player.view_prev= ship;

ship->info.player.view_prev= NULL;
ship->info.player.view_next= ship->info.player.view->info.player.viewers;

ship->info.player.view->info.player.viewers= ship;
}

/*:243*/
#line 8214 "./matanza.w"
;


SHIP_KEY_VIEW_LABEL(ship);

MAT_SHIP_VIEW_CHECK(ship->un);
}

/*:249*//*250:*/
#line 8225 "./matanza.w"

void
ship_key_zoom_out(MatMovingObj*ship)
{
double nw,nh;

nw= (double)ship->info.player.world_wi*1.1;
nh= GET_WORLD_HE(ship->info.player,nw);

if((int)nw<ship->un->mapsize_x&&(int)nh<ship->un->mapsize_y)
{
ship->info.player.world_wi= (int)nw;
ship->info.player.world_he= (int)nh;
}
}

/*:250*//*251:*/
#line 8242 "./matanza.w"

void
ship_key_zoom_in(MatMovingObj*ship)
{
double nw,nh;

nw= (double)ship->info.player.world_wi/1.1;
nh= GET_WORLD_HE(ship->info.player,nw);

if((int)nw> mat_ship[0].w-2&&(int)nh> mat_ship[0].h-2)
{
ship->info.player.world_wi= (int)nw;
ship->info.player.world_he= (int)nh;
}

}

/*:251*//*253:*/
#line 8289 "./matanza.w"

void
ship_key_chat_add(MatMovingObj*ship,int key)
{
MatShip*p= &ship->info.player;

if(isprint(key)&&p->chat_buffer_len<MAXCHATBUFFERLEN)
{
p->chat_buffer[p->chat_buffer_len++]= (char)key;
p->chat_buffer[p->chat_buffer_len]= 0;
}
else
VERBOSE("Ignored Input: [key:%d][state:player_input_buffer]\n",key);
}

/*:253*//*254:*/
#line 8305 "./matanza.w"

void
ship_key_up(MatMovingObj*ship)
{
if(ship->info.player.game_over)
{
double mod_y,mod_t;

if(ship->sp_y<=0)
mod_y= ship->sp_y-1.0/STEPS_MOVEMENT;
else
mod_y= 0;

mod_t= sqrt(ship->sp_x*ship->sp_x+mod_y*mod_y);

if(arg_speed_max==0||(-arg_speed_max<mod_t&&mod_t<arg_speed_max))
{
ship->sp= mod_t;
ship->sp_y= mod_y;
}
}
else if(ship->info.player.ship_speed_inc==0)
{
ship->info.player.ship_speed_inc= 3;
if(arg_space)
{
double mod_x,mod_y,mod_t;

mod_x= ship->sp_x-1.0*mat_sin[(int)ship->ang]/STEPS_MOVEMENT;
mod_y= ship->sp_y-1.0*mat_cos[(int)ship->ang]/STEPS_MOVEMENT;
mod_t= sqrt(mod_x*mod_x+mod_y*mod_y);

if(arg_speed_max==0||(-arg_speed_max<mod_t&&mod_t<arg_speed_max))
{
ship->sp= mod_t;
ship->sp_x= mod_x;
ship->sp_y= mod_y;
}
}
else if(arg_speed_max==0||ship->sp+1.0/STEPS_MOVEMENT<(double)arg_speed_max)
{
ship->sp-= 1.0/STEPS_MOVEMENT;
ship->sp_x= ship->sp*mat_sin[(int)ship->ang];
ship->sp_y= ship->sp*mat_cos[(int)ship->ang];
}
}
}

/*:254*//*255:*/
#line 8355 "./matanza.w"

void
ship_key_down(MatMovingObj*ship)
{
if(ship->info.player.game_over)
{
double mod_y,mod_t;

if(ship->sp_y>=0)
mod_y= ship->sp_y+1.0/STEPS_MOVEMENT;
else
mod_y= 0;

mod_t= sqrt(ship->sp_x*ship->sp_x+mod_y*mod_y);

if(arg_speed_max==0||(-arg_speed_max<mod_t&&mod_t<arg_speed_max))
{
ship->sp= mod_t;
ship->sp_y= mod_y;
}
}
else if(ship->info.player.ship_speed_inc==0&&arg_brake)
{
ship->info.player.ship_speed_inc= 3;
if(arg_space)
{
double mod_x,mod_y,mod_t;

mod_x= ship->sp_x+1.0*mat_sin[(int)ship->ang]/STEPS_MOVEMENT;
mod_y= ship->sp_y+1.0*mat_cos[(int)ship->ang]/STEPS_MOVEMENT;
mod_t= sqrt(mod_x*mod_x+mod_y*mod_y);

if(arg_speed_max==0||(-arg_speed_max<mod_t&&mod_t<arg_speed_max))
{
ship->sp= mod_t;
ship->sp_x= mod_x;
ship->sp_y= mod_y;
}
}
else if(arg_speed_max==0||-arg_speed_max<ship->sp-1.0/STEPS_MOVEMENT)
{
ship->sp+= 1.0/STEPS_MOVEMENT;
if(!arg_fly_back&&0.0<ship->sp)
ship->sp= 0;
ship->sp_x= ship->sp*mat_sin[(int)ship->ang];
ship->sp_y= ship->sp*mat_cos[(int)ship->ang];
}
}
}

/*:255*//*256:*/
#line 8406 "./matanza.w"

void
ship_key_right(MatMovingObj*ship)
{
if(ship->info.player.game_over)
{
double mod_x,mod_t;

if(ship->sp_x>=0)
mod_x= ship->sp_x+1.0/STEPS_MOVEMENT;
else
mod_x= 0;

mod_t= sqrt(mod_x*mod_x+ship->sp_y*ship->sp_y);

if(arg_speed_max==0||(-arg_speed_max<mod_t&&mod_t<arg_speed_max))
{
ship->sp= mod_t;
ship->sp_x= mod_x;
}
}
else if(arg_ang_speed_max> 0)
{
if(ship->sp_ang> 0)
ship->sp_ang= 0;
else if(ship->sp_ang> -arg_ang_speed_max)
ship->sp_ang-= 1.0/STEPS_MOVEMENT;
}
else
{
ship->ang-= 1;
if((int)ship->ang<0)
ship->ang+= arg_ang;
if(!arg_space)
{
ship->sp_x= ship->sp*mat_sin[(int)ship->ang];
ship->sp_y= ship->sp*mat_cos[(int)ship->ang];
}
}
}

/*:256*//*257:*/
#line 8448 "./matanza.w"

void
ship_key_left(MatMovingObj*ship)
{
if(ship->info.player.game_over)
{
double mod_x,mod_t;

if(ship->sp_x<=0)
mod_x= ship->sp_x-1.0/STEPS_MOVEMENT;
else
mod_x= 0;

mod_t= sqrt(mod_x*mod_x+ship->sp_y*ship->sp_y);

if(arg_speed_max==0||(-arg_speed_max<mod_t&&mod_t<arg_speed_max))
{
ship->sp= mod_t;
ship->sp_x= mod_x;
}
}
else if(arg_ang_speed_max> 0)
{
if(ship->sp_ang<0)
ship->sp_ang= 0;
else if(ship->sp_ang<arg_ang_speed_max)
ship->sp_ang+= 1.0/STEPS_MOVEMENT;
}
else
{
ship->ang+= 1;
if((int)ship->ang> arg_ang-1)
ship->ang-= arg_ang;
if(!arg_space)
{
ship->sp_x= ship->sp*mat_sin[(int)ship->ang];
ship->sp_y= ship->sp*mat_cos[(int)ship->ang];
}
}
}

/*:257*//*258:*/
#line 8510 "./matanza.w"

void
ship_key_visibility(MatMovingObj*ship)
{
if(ship->info.player.visible_exp> 0)
{
ship->info.player.visible= !ship->info.player.visible;
VISIBILITY_BROADCAST(ship);
}
}

/*:258*//*259:*/
#line 8526 "./matanza.w"

char*
message_get(MatMovingObj*p)
{
static char buffer[MAXMESSAGELEN];

if(p->type!=MAT_MOVING_OBJ_SHIP
||!p->info.player.conn
||p->info.player.conn->state!=MAT_STATE_PLAYING)
return buffer;

ASSERT(p);
ASSERT(p->type==MAT_MOVING_OBJ_SHIP);
ASSERT(p->info.player.conn);
ASSERT(p->info.player.conn->state==MAT_STATE_PLAYING);

if(p->info.player.messages_count==MAXMESSAGES)
p->info.player.messages_start= (p->info.player.messages_start+1)%MAXMESSAGES;
else
p->info.player.messages_count++;

p->info.player.messages_expire[NM]= 200;
return p->info.player.messages[NM];
}

void
message_broadcast(MatUniverse*u,char*fmt,...)
{
MatMovingObj*p;
va_list arg;

ASSERT(u);
ASSERT(fmt);

for(p= u->players_head;p;p= p->nexttype)
{
va_start(arg,fmt);
vsprintf(message_get(p),fmt,arg);
va_end(arg);
}
}

/*:259*//*261:*/
#line 8579 "./matanza.w"

int
mat_bullet_new_player(MatMovingObj*p,int type,int dir)
{
double sp_x,sp_y;

ASSERT(dir==1||dir==-1);

ASSERT(p->type==MAT_MOVING_OBJ_SHIP);
ASSERT(p->refs>=0);

/*266:*/
#line 8718 "./matanza.w"

{
if(p->info.player.bullets_expire> mat_bullets_pexp[type]/2
||p->info.player.ship_bullets[type]<=0
||p->info.player.game_over)
return 0;
}

/*:266*/
#line 8590 "./matanza.w"
;

sp_x= -dir*mat_bullets_speed[type]*mat_sin[(int)p->ang]+p->sp_x;
sp_y= -dir*mat_bullets_speed[type]*mat_cos[(int)p->ang]+p->sp_y;

return mat_bullet_new(p,type,sp_x,sp_y,p->ang);
}

/*:261*//*263:*/
#line 8608 "./matanza.w"

int
mat_bullet_new(MatMovingObj*p,int type,double sp_x,double sp_y,double ang)
{
MatMovingObj*n;

n= malloc(sizeof(MatMovingObj));
if(!n)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
return 0;
}

MAT_MOVING_OBJ_REF(p);

n->un= p->un;

p->info.player.ship_bullets[type]--;
if(p->info.player.ship_bullets[type]==0)
sprintf(message_get(p),"-=> Ooops, you ran out of %s !",mat_bullets_name[type]);

if(type==2)
p->pal= mat_ship_palette[p->info.player.ship_bullets[2]];

p->info.player.bullets_expire+= mat_bullets_pexp[type];

n->info.bullet.src= p;
n->info.bullet.type= type;
n->info.bullet.expires= mat_bullets_bexp[type];

n->type= MAT_MOVING_OBJ_BULLET;
n->rm_next= NULL;
n->ang= ang;
n->sp_ang= 0;

n->crash= 1;
n->draw= 1;

n->alpha= 1.0;
n->alpha_mod= NULL;

n->img= type> 0?mat_missile[type-1]:NULL;

n->sp_x= sp_x;
n->sp_y= sp_y;

ASSERT(p->img);

n->pos_x= p->pos_x+(p->img[0].w-(type> 0?n->img[0].w:0))/2;
n->pos_y= p->pos_y+(p->img[0].h-(type> 0?n->img[0].h:0))/2;

if((int)n->pos_x>=n->un->mapsize_x)
n->pos_x-= n->un->mapsize_x;
if((int)n->pos_y>=n->un->mapsize_y)
n->pos_y-= n->un->mapsize_y;

ASSERT((int)n->pos_x>=0);
ASSERT((int)n->pos_y>=0);
ASSERT((int)n->pos_x<n->un->mapsize_x);
ASSERT((int)n->pos_y<n->un->mapsize_y);

n->pal= mat_ship_palette[0];

/*264:*/
#line 8676 "./matanza.w"

{
MatUniverse*un;

un= n->un;

n->prevtype= NULL;
n->nexttype= un->bullets;

if(un->bullets)
un->bullets->prevtype= n;

un->bullets= n;

ADD_MOVING_OBJ(n,un);
}

/*:264*/
#line 8671 "./matanza.w"
;
return 1;
}

/*:263*//*267:*/
#line 8732 "./matanza.w"

void
machine_update(MatConnection*self)
{
int i;
MatSub*un;

for(i= 0;i<MAT_SUB_MACHINE_HASH_SIZE;i++)
for(un= self->info.m.subs[i];un;un= un->m_next)
{
mat_printf(self,"%c%c%c",MMP_SERVER_DEFAULT_FRAME_SHIPS,
un->u->id&0xff00,un->u->id,0x00ff);
/*268:*/
#line 8757 "./matanza.w"

{
MatMovingObj*sh;

for(sh= un->u->players_head;sh;sh= sh->nexttype)
mat_printf(self,"%c%c""%c%c""%c%c",
((int)sh->pos_x)&0xff00,((int)sh->pos_x)&0x00ff,
((int)sh->pos_y)&0xff00,((int)sh->pos_y)&0x00ff,
((int)sh->ang)&0xff00,((int)sh->ang)&0x00ff);
}

/*:268*/
#line 8744 "./matanza.w"
;
mat_printf(self,"%c",MMP_SERVER_FRAME_DONE);
}

mat_out_flush(self);
}

/*:267*//*269:*/
#line 8769 "./matanza.w"

void
draw_world(MatConnection*self)
{
int game_moving;

ASSERT(self);
ASSERT(self->state==MAT_STATE_PLAYING);

/*270:*/
#line 8791 "./matanza.w"

{
MatMovingObj*sh= self->ship_list;

game_moving= 0;

do
{
if(!sh->un->pause)
{
game_moving= 1;
break;
}
else
sh= sh->info.player.conn_list_next;
}
while(sh);
}

/*:270*/
#line 8778 "./matanza.w"
;

if(game_moving)
/*272:*/
#line 8855 "./matanza.w"

{
int startx;
int starty;
MatMovingObj*sh;
MatMovingObj*i;
MatMovingObj*p;
MatMovingObj*obj;
MatShip*pl;
MatShip*pl_view;
MatUniverse*un;

TERM_CLEAR_IMAGE(self);

for(i= self->ship_list;i;i= i->info.player.conn_list_next)
{
ASSERT(i->type==MAT_MOVING_OBJ_SHIP);

pl= &i->info.player;

sh= i->info.player.view;

ASSERT(sh);
ASSERT(sh->type==MAT_MOVING_OBJ_SHIP);

pl_view= &sh->info.player;

un= sh->un;
ASSERT(un);

ASSERT((int)sh->pos_x>=0);
ASSERT((int)sh->pos_x<un->mapsize_x);
ASSERT((int)sh->pos_y>=0);
ASSERT((int)sh->pos_y<un->mapsize_y);

ASSERT(pl->world_wi> 0);
ASSERT(pl->world_he> 0);

startx= sh->pos_x-(pl->world_wi-sh->img[0].w)/2;
starty= sh->pos_y-(pl->world_he-sh->img[0].h)/2;

if(startx<0)
startx+= un->mapsize_x;

if(starty<0)
starty+= un->mapsize_y;

ASSERT(startx>=0);
ASSERT(starty>=0);
ASSERT(startx<un->mapsize_x);
ASSERT(starty<un->mapsize_y);

/*275:*/
#line 8990 "./matanza.w"

{
MatImgWorld*obj;

for(obj= mat_bg_head;obj;obj= obj->next)
{
/*301:*/
#line 9653 "./matanza.w"

{
ASSERT(obj->img->w<=sh->un->mapsize_x);
ASSERT(obj->img->h<=sh->un->mapsize_y);

MAT_IMAGE_DRAW_ST(self,i,obj->img,startx,starty,mat_stdpal,arg_bg_adj,1.0);
}

/*:301*/
#line 8996 "./matanza.w"
;
}

if(un->bg)
{
ASSERT(un->bg->w<=un->mapsize_x);
ASSERT(un->bg->h<=un->mapsize_y);

MAT_IMAGE_DRAW_ST(self,i,un->bg,startx,starty,mat_stdpal,arg_bg_adj,1.0);
}

if(un->dots)
{
int i,j;

ASSERT(self);
ASSERT(self->graph_imagebuffer);

for(i= 20-starty%20;i<pl->imghe;i+= 20)
for(j= 40-startx%40;j<pl->imgwi;j+= 40)
MAT_GRAPH_DRAW(self,pl,j,i,100);
}
}

/*:275*/
#line 8907 "./matanza.w"
;

for(obj= un->ast;obj;obj= obj->nexttype)
/*276:*/
#line 9022 "./matanza.w"

{
int x,y;

ASSERT(obj);
ASSERT(!obj->rm_next);

ASSERT(self);

ASSERT((int)obj->pos_x>=0);
ASSERT((int)obj->pos_y>=0);
ASSERT((int)obj->pos_x<un->mapsize_x);
ASSERT((int)obj->pos_y<un->mapsize_y);

if(obj->draw)
{
if(obj->img==NULL)
{
x= (int)obj->pos_x-startx;
y= (int)obj->pos_y-starty;

if(x<0)
x+= un->mapsize_x;
if(y<0)
y+= un->mapsize_y;

ASSERT(x<un->mapsize_x);
ASSERT(y<un->mapsize_y);

ASSERT(x>=0);
ASSERT(y>=0);

if(x<pl->world_wi&&y<pl->world_he)
{
/*283:*/
#line 9200 "./matanza.w"

{
if(pl->imgwi!=pl->world_wi)
x= (double)x*(double)pl->imgwi/(double)pl->world_wi;

if(pl->imghe!=pl->world_he)
y= (double)y*(double)pl->imghe/(double)pl->world_he;
}

/*:283*/
#line 9056 "./matanza.w"
;

ASSERT(x>=0);
ASSERT(x<self->graph_imgwidth);
ASSERT(y>=0);
ASSERT(y<self->graph_imgheight);

MAT_GRAPH_DRAW(self,pl,x,y,255);
}
}
else
{
MatImage*img;
int x,y;

img= &obj->img[(int)obj->ang];

x= (int)obj->pos_x;
y= (int)obj->pos_y;

MAT_IMAGE_DRAW_DY(self,i,img,x,y,obj,startx,starty,0);
}
}
}

/*:276*/
#line 8910 "./matanza.w"
;

for(obj= un->smart_objs;obj;obj= obj->nexttype)
/*276:*/
#line 9022 "./matanza.w"

{
int x,y;

ASSERT(obj);
ASSERT(!obj->rm_next);

ASSERT(self);

ASSERT((int)obj->pos_x>=0);
ASSERT((int)obj->pos_y>=0);
ASSERT((int)obj->pos_x<un->mapsize_x);
ASSERT((int)obj->pos_y<un->mapsize_y);

if(obj->draw)
{
if(obj->img==NULL)
{
x= (int)obj->pos_x-startx;
y= (int)obj->pos_y-starty;

if(x<0)
x+= un->mapsize_x;
if(y<0)
y+= un->mapsize_y;

ASSERT(x<un->mapsize_x);
ASSERT(y<un->mapsize_y);

ASSERT(x>=0);
ASSERT(y>=0);

if(x<pl->world_wi&&y<pl->world_he)
{
/*283:*/
#line 9200 "./matanza.w"

{
if(pl->imgwi!=pl->world_wi)
x= (double)x*(double)pl->imgwi/(double)pl->world_wi;

if(pl->imghe!=pl->world_he)
y= (double)y*(double)pl->imghe/(double)pl->world_he;
}

/*:283*/
#line 9056 "./matanza.w"
;

ASSERT(x>=0);
ASSERT(x<self->graph_imgwidth);
ASSERT(y>=0);
ASSERT(y<self->graph_imgheight);

MAT_GRAPH_DRAW(self,pl,x,y,255);
}
}
else
{
MatImage*img;
int x,y;

img= &obj->img[(int)obj->ang];

x= (int)obj->pos_x;
y= (int)obj->pos_y;

MAT_IMAGE_DRAW_DY(self,i,img,x,y,obj,startx,starty,0);
}
}
}

/*:276*/
#line 8913 "./matanza.w"
;

for(p= un->players_head;p;p= p->nexttype)
if(p->info.player.visible&&p->draw)
/*289:*/
#line 9401 "./matanza.w"

{
MatImage*img;
int x,y;

ASSERT(p);
ASSERT(p->type==MAT_MOVING_OBJ_SHIP);

ASSERT(p->info.player.ship_bullets[2]>=0);
ASSERT(p->info.player.ship_bullets[2]<=2);

ASSERT(!p->rm_next);

x= (int)p->pos_x;
y= (int)p->pos_y;

ASSERT(0<=x);
ASSERT(x<i->un->mapsize_x);

ASSERT(0<=y);
ASSERT(y<i->un->mapsize_y);

img= &p->img[(int)p->ang];
ASSERT(img);

MAT_IMAGE_DRAW_DY(self,i,img,x,y,p,startx,starty,0);
}

/*:289*/
#line 8917 "./matanza.w"
;

for(obj= un->bullets;obj;obj= obj->nexttype)
/*276:*/
#line 9022 "./matanza.w"

{
int x,y;

ASSERT(obj);
ASSERT(!obj->rm_next);

ASSERT(self);

ASSERT((int)obj->pos_x>=0);
ASSERT((int)obj->pos_y>=0);
ASSERT((int)obj->pos_x<un->mapsize_x);
ASSERT((int)obj->pos_y<un->mapsize_y);

if(obj->draw)
{
if(obj->img==NULL)
{
x= (int)obj->pos_x-startx;
y= (int)obj->pos_y-starty;

if(x<0)
x+= un->mapsize_x;
if(y<0)
y+= un->mapsize_y;

ASSERT(x<un->mapsize_x);
ASSERT(y<un->mapsize_y);

ASSERT(x>=0);
ASSERT(y>=0);

if(x<pl->world_wi&&y<pl->world_he)
{
/*283:*/
#line 9200 "./matanza.w"

{
if(pl->imgwi!=pl->world_wi)
x= (double)x*(double)pl->imgwi/(double)pl->world_wi;

if(pl->imghe!=pl->world_he)
y= (double)y*(double)pl->imghe/(double)pl->world_he;
}

/*:283*/
#line 9056 "./matanza.w"
;

ASSERT(x>=0);
ASSERT(x<self->graph_imgwidth);
ASSERT(y>=0);
ASSERT(y<self->graph_imgheight);

MAT_GRAPH_DRAW(self,pl,x,y,255);
}
}
else
{
MatImage*img;
int x,y;

img= &obj->img[(int)obj->ang];

x= (int)obj->pos_x;
y= (int)obj->pos_y;

MAT_IMAGE_DRAW_DY(self,i,img,x,y,obj,startx,starty,0);
}
}
}

/*:276*/
#line 8920 "./matanza.w"
;

if(pl_view->game_over&&pl->messages_enabled)
/*273:*/
#line 8931 "./matanza.w"

{
int imgwi,imghe;

imgwi= pl->win_x_e-pl->win_x_s;
imghe= pl->win_y_e-pl->win_y_s;

print(self,
pl->win_x_s*2+imgwi-2*2*imgwi/5,
pl->win_y_s*2+imghe/2,
2*imgwi/5,
2*imghe/4,
&font,255,"Game");

print(self,
pl->win_x_s*2+imgwi-2*2*(imgwi/5),
pl->win_y_s*2+imghe,
2*imgwi/5,
2*imghe/4,
&font,255,"Over");
}

/*:273*/
#line 8923 "./matanza.w"
;
}
}


/*:272*/
#line 8781 "./matanza.w"


MAT_GRAPH_RENDER_NOWIPE_ALL(self);

/*271:*/
#line 8812 "./matanza.w"

{
MatMovingObj*i;
MatMovingObj*sh;
MatShip*pl;
MatShip*pl_view;
MatUniverse*un;

for(i= self->ship_list;i;i= i->info.player.conn_list_next)
{
ASSERT(i->type==MAT_MOVING_OBJ_SHIP);

pl= &i->info.player;

sh= i->info.player.view;

ASSERT(sh);
ASSERT(sh->type==MAT_MOVING_OBJ_SHIP);

un= sh->un;
ASSERT(un);

pl_view= &sh->info.player;

if(arg_radar&&un->updates%4)
{
MatMovingObj*obj;

for(obj= un->ast;obj;obj= obj->nexttype)
if(!OBJECT_INSIDE(sh,obj))
/*285:*/
#line 9228 "./matanza.w"

{
double x,y,m;
int wi,he,dx,dy,draw= 1;
char buffer[2];

ASSERT(obj!=sh);

/*286:*/
#line 9288 "./matanza.w"

{
double px,sx,py,sy;
double x1,x2,y1,y2;

ASSERT(obj);
ASSERT(sh);

ASSERT(obj->un==sh->un);

ASSERT(!obj->rm_next);
ASSERT(!sh->rm_next);

ASSERT(obj->img);
ASSERT(sh->img);

ADJUST_POSITION(px,obj->pos_x,obj->img->w,obj->un->mapsize_x);
ADJUST_POSITION(sx,sh->pos_x,sh->img->w,obj->un->mapsize_x);

x1= ABS(px-sx);
x2= obj->un->mapsize_x-x1;

if(x1<x2)
x= x1,dx= 1;
else
x= x2,dx= -1;

dx= sx<=px?dx:-dx;

ADJUST_POSITION(py,obj->pos_y,obj->img->h,obj->un->mapsize_y);
ADJUST_POSITION(sy,sh->pos_y,sh->img->h,obj->un->mapsize_y);

y1= ABS(py-sy);
y2= obj->un->mapsize_y-y1;

if(y1<y2)
y= y1,dy= 1;
else
y= y2,dy= -1;

dy= sy<=py?dy:-dy;
}

/*:286*/
#line 9236 "./matanza.w"
;

m= y/x;

ASSERT(x>=0);
ASSERT(y>=0);

ASSERT(pl->imgwi> 0);
ASSERT(pl->imghe> 0);

if(m<=(double)pl->imghe/(double)pl->imgwi)
{
wi= dx> 0?pl->imgwi-1:0;
he= (pl->imghe+dy*m*pl->imgwi)/2;
}
else
{
he= dy> 0?pl->imghe-1:0;
wi= (pl->imgwi+dx*pl->imghe/m)/2;
}

ASSERT(0<=he);
ASSERT(he<pl->imghe);
ASSERT(0<=wi);
ASSERT(wi<pl->imgwi);
ASSERT(he==0||he==pl->imghe-1||wi==0||wi==pl->imgwi-1);

/*287:*/
#line 9336 "./matanza.w"

{
int dist;

ASSERT(obj);

dist= x*x+y*y;

if(dist> LENAWAY)
{
if(obj->type==MAT_MOVING_OBJ_SHIP)
buffer[0]= tolower(obj->info.player.name[0]);
else
draw= 0;
}
else if(dist> LENNEAR)
{
if(obj->type==MAT_MOVING_OBJ_SHIP)
buffer[0]= toupper(obj->info.player.name[0]);
else
buffer[0]= '.';
}
else
{
if(obj->type==MAT_MOVING_OBJ_SHIP)
buffer[0]= '*';
else
buffer[0]= '+';
}

buffer[1]= 0;
}

/*:287*/
#line 9263 "./matanza.w"
;

if(draw)
mat_print(self,wi/2+pl->win_x_s,he/2+pl->win_y_s,MAT_NORMAL,buffer,0);
}

/*:285*/
#line 8842 "./matanza.w"
;

for(obj= un->players_head;obj;obj= obj->nexttype)
if(!OBJECT_INSIDE(sh,obj)&&!obj->info.player.game_over)
/*285:*/
#line 9228 "./matanza.w"

{
double x,y,m;
int wi,he,dx,dy,draw= 1;
char buffer[2];

ASSERT(obj!=sh);

/*286:*/
#line 9288 "./matanza.w"

{
double px,sx,py,sy;
double x1,x2,y1,y2;

ASSERT(obj);
ASSERT(sh);

ASSERT(obj->un==sh->un);

ASSERT(!obj->rm_next);
ASSERT(!sh->rm_next);

ASSERT(obj->img);
ASSERT(sh->img);

ADJUST_POSITION(px,obj->pos_x,obj->img->w,obj->un->mapsize_x);
ADJUST_POSITION(sx,sh->pos_x,sh->img->w,obj->un->mapsize_x);

x1= ABS(px-sx);
x2= obj->un->mapsize_x-x1;

if(x1<x2)
x= x1,dx= 1;
else
x= x2,dx= -1;

dx= sx<=px?dx:-dx;

ADJUST_POSITION(py,obj->pos_y,obj->img->h,obj->un->mapsize_y);
ADJUST_POSITION(sy,sh->pos_y,sh->img->h,obj->un->mapsize_y);

y1= ABS(py-sy);
y2= obj->un->mapsize_y-y1;

if(y1<y2)
y= y1,dy= 1;
else
y= y2,dy= -1;

dy= sy<=py?dy:-dy;
}

/*:286*/
#line 9236 "./matanza.w"
;

m= y/x;

ASSERT(x>=0);
ASSERT(y>=0);

ASSERT(pl->imgwi> 0);
ASSERT(pl->imghe> 0);

if(m<=(double)pl->imghe/(double)pl->imgwi)
{
wi= dx> 0?pl->imgwi-1:0;
he= (pl->imghe+dy*m*pl->imgwi)/2;
}
else
{
he= dy> 0?pl->imghe-1:0;
wi= (pl->imgwi+dx*pl->imghe/m)/2;
}

ASSERT(0<=he);
ASSERT(he<pl->imghe);
ASSERT(0<=wi);
ASSERT(wi<pl->imgwi);
ASSERT(he==0||he==pl->imghe-1||wi==0||wi==pl->imgwi-1);

/*287:*/
#line 9336 "./matanza.w"

{
int dist;

ASSERT(obj);

dist= x*x+y*y;

if(dist> LENAWAY)
{
if(obj->type==MAT_MOVING_OBJ_SHIP)
buffer[0]= tolower(obj->info.player.name[0]);
else
draw= 0;
}
else if(dist> LENNEAR)
{
if(obj->type==MAT_MOVING_OBJ_SHIP)
buffer[0]= toupper(obj->info.player.name[0]);
else
buffer[0]= '.';
}
else
{
if(obj->type==MAT_MOVING_OBJ_SHIP)
buffer[0]= '*';
else
buffer[0]= '+';
}

buffer[1]= 0;
}

/*:287*/
#line 9263 "./matanza.w"
;

if(draw)
mat_print(self,wi/2+pl->win_x_s,he/2+pl->win_y_s,MAT_NORMAL,buffer,0);
}

/*:285*/
#line 8846 "./matanza.w"
;
}

/*274:*/
#line 8961 "./matanza.w"

{
int i,pos;

ASSERT(pl);

pos= pl->messages_pos?pl->win_y_e-pl->messages_count-1:pl->win_y_s+1;

for(i= 0;i<pl->messages_count;i++)
{
if(pl->messages_enabled)
mat_print(self,1,pos+i,MAT_NORMAL,pl->messages[NMESG(i)],0);

if(pl->messages_expire[NMESG(i)]--==0)
{
pl->messages_start= NMESG(1);
pl->messages_count--;
}
}

if(self->ship_count==1&&self->key_handler==player_input_buffer)
{
mat_print(self,1,POSB(),MAT_NORMAL,"> ",0);
mat_print(self,3,POSB(),MAT_NORMAL,pl->chat_buffer,0);
}
}

/*:274*/
#line 8849 "./matanza.w"
;
}
}

/*:271*/
#line 8785 "./matanza.w"
;

MAT_FLUSH_ALL(self);
}

/*:269*//*305:*/
#line 9706 "./matanza.w"


#if HAVE_LIBPNG
/*307:*/
#line 9724 "./matanza.w"

MatImage*
mat_png_load(char const*path)
{
png_structp png_ptr;
png_infop info_ptr;
FILE*fp;

MatImage*nimg;

int bd,color;

fp= fopen(path,"rb");
if(!fp)
{
fprintf(stderr,"%s: %s: %s\n",program_name,path,strerror(errno));
exit(EXIT_FAILURE);
}

/*311:*/
#line 9801 "./matanza.w"

{
png_uint_32 w,h;
int dummy;








png_ptr= png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);

if(!png_ptr)
return 0;


info_ptr= png_create_info_struct(png_ptr);
if(!info_ptr)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
png_destroy_read_struct(&png_ptr,NULL,NULL);
exit(EXIT_FAILURE);
}

if(setjmp(png_ptr->jmpbuf))
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
png_destroy_read_struct(&png_ptr,&info_ptr,NULL);
exit(EXIT_FAILURE);
}

png_init_io(png_ptr,fp);

png_read_info(png_ptr,info_ptr);
png_get_IHDR(png_ptr,info_ptr,&w,&h,&bd,&color,&dummy,NULL,NULL);

nimg= malloc(sizeof(MatImage));
if(!nimg)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

nimg->w= w;
nimg->h= h;

nimg->img= malloc(w*h);
if(!nimg->img)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
}

/*:311*/
#line 9743 "./matanza.w"
;
/*308:*/
#line 9753 "./matanza.w"

{
if(color!=PNG_COLOR_TYPE_GRAY&&color!=PNG_COLOR_TYPE_GRAY_ALPHA)
{
fprintf(stderr,"%s: Only grayscale PNG files are supported\n",program_name);
exit(EXIT_FAILURE);
}
}

/*:308*/
#line 9744 "./matanza.w"
;
/*312:*/
#line 9859 "./matanza.w"

{
png_color_16 my_background,*image_background;




png_set_packing(png_ptr);


if((color==PNG_COLOR_TYPE_GRAY&&bd<8)||png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS))
png_set_expand(png_ptr);








if(png_get_bKGD(png_ptr,info_ptr,&image_background))
png_set_background(png_ptr,image_background,PNG_BACKGROUND_GAMMA_FILE,1,1.0);
else
png_set_background(png_ptr,&my_background,PNG_BACKGROUND_GAMMA_SCREEN,0,1.0);

if(png_set_interlace_handling(png_ptr)!=1)
{
fprintf(stderr,"%s: %s: Interlaced PNGs are not supported\n",program_name,path);
exit(EXIT_FAILURE);
}






png_read_update_info(png_ptr,info_ptr);
}

/*:312*/
#line 9745 "./matanza.w"
;
/*310:*/
#line 9773 "./matanza.w"

{
int y,len,dst;
png_bytep row_pointers;

len= png_get_rowbytes(png_ptr,info_ptr);
row_pointers= malloc(len);

ASSERT(color==PNG_COLOR_TYPE_GRAY||color==PNG_COLOR_TYPE_GRAY_ALPHA);

for(y= dst= 0;y<nimg->h;y++)
{
int rd,stop;

png_read_rows(png_ptr,&row_pointers,NULL,1);

for(rd= 0,stop= dst+nimg->w;dst!=stop;rd++)
{
png_byte p;
p= row_pointers[rd];
nimg->img[dst++]= p;
}
}

free(row_pointers);
}

/*:310*/
#line 9746 "./matanza.w"
;
/*309:*/
#line 9763 "./matanza.w"

{

png_read_end(png_ptr,info_ptr);


png_destroy_read_struct(&png_ptr,&info_ptr,NULL);
}

/*:309*/
#line 9747 "./matanza.w"
;

return nimg;
}

/*:307*/
#line 9709 "./matanza.w"

#else
/*306:*/
#line 9715 "./matanza.w"

MatImage*
mat_png_load(char const*path)
{
fprintf(stderr,"%s: Support for loading PNG files not included\n",program_name);
exit(EXIT_FAILURE);
}

/*:306*/
#line 9711 "./matanza.w"

#endif

/*:305*//*343:*/
#line 10536 "./matanza.w"

MatSocketT
mat_listen(int port)
{
struct sockaddr_in in;
MatSocketT result;
int on= 1;

VERBOSE("Listening on port %d...",port);
fflush(stdout);

memset(&in,0,sizeof(struct sockaddr_in));
in.sin_family= AF_INET;
in.sin_addr.s_addr= INADDR_ANY;
in.sin_port= htons(port);

#if HAVE_WSASOCKET
result= WSASocket(AF_INET,SOCK_STREAM,0,NULL,0,0);
#else
result= socket(AF_INET,SOCK_STREAM,0);
#endif

if(result==SOCKET_ERROR)
{
/*344:*/
#line 10599 "./matanza.w"

#if WIN32
switch(SOCKET_ERRNO())
{
case WSAEMFILE:
fprintf(stderr,"%s: socket: No more socket descriptors are available.\n",program_name);
break;
default:
fprintf(stderr,"%s: socket: Unknown error (code %d)\n",program_name,SOCKET_ERRNO());
}
#else
fprintf(stderr,"%s: socket: %s\n",program_name,strerror(SOCKET_ERRNO()));
#endif

/*:344*/
#line 10560 "./matanza.w"
;
exit(EXIT_FAILURE);
}

#if HAVE_SETSOCKOPT
#  ifdef SOL_SOCKET
#    ifdef SO_REUSEADDR
VERBOSE("setsockopt [fd:%d][option:SO_REUSEADDR]\n",result);
setsockopt(result,SOL_SOCKET,SO_REUSEADDR,(void*)&on,sizeof(on));
#    endif
#  endif
#endif

if(bind(result,(struct sockaddr*)&in,sizeof(struct sockaddr_in))==SOCKET_ERROR)
{
fprintf(stderr,"%s: bind: %s\n",program_name,strerror(SOCKET_ERRNO()));

exit(EXIT_FAILURE);
}

if(listen(result,10)==SOCKET_ERROR)
{
exit(EXIT_FAILURE);
fprintf(stderr,"%s: listen: %s\n",program_name,strerror(SOCKET_ERRNO()));
}


NONBLOCKING_GENERIC(result);

VERBOSE(" Done\n");

return result;
}

/*:343*//*348:*/
#line 10742 "./matanza.w"

int
mat_out_flush(MatConnection*con)
{
int retval;

ASSERT(con);

if(con->out_len==0)
return 1;

ASSERT(con->out_buf);

#ifdef MSG_NOSIGNAL
#  define MAT_SEND_FLAGS MSG_NOSIGNAL
#else
#  define MAT_SEND_FLAGS 0
#endif

send_retry:

VERBOSE("-=> send\n");
retval= send(con->fd,con->out_buf,con->out_len,MAT_SEND_FLAGS);
VERBOSE("<=- send\n");

if(retval==SOCKET_ERROR)
{
switch(SOCKET_ERRNO())
{
case SOCKET_CALL_INTR:
goto send_retry;

case EPIPE:
#ifdef WSAECONNRESET
#  if WSAECONNRESET != EPIPE
case WSAECONNRESET:
#  endif
#endif
#ifdef WSAECONNABORTED
#  if WSAECONNABORTED != EPIPE
case WSAECONNABORTED:
#  endif
#endif
#ifdef ECONNABORTED
#  if ECONNABORTED
case ECONNABORTED:
#  endif
#endif
VERBOSE("send failed: connection closed\n");
return 0;

case EAGAIN:
#ifdef EWOULDBLOCK
#  if EWOULDBLOCK != EAGAIN
case EWOULDBLOCK:
#  endif
#endif
#ifdef WSAEWOULDBLOCK
#  if WSAEWOULDBLOCK != EAGAIN
case WSAEWOULDBLOCK:
#  endif
#endif
VERBOSE("send failed: player lagging\n");
con->info.t.clean= 0;
break;

default:
fprintf(stderr,"%s: send: Unknown error (code %d)\n",program_name,SOCKET_ERRNO());
exit(EXIT_FAILURE);
}
}

VERBOSE("send successful\n");
con->out_len= 0;

return 1;
}

/*:348*//*349:*/
#line 10821 "./matanza.w"

int
mat_write(MatConnection*con,void*buffer,size_t len)
{
/*352:*/
#line 10897 "./matanza.w"

{
int nlen;

nlen= con->out_len+len;

if(nlen>=con->out_siz)
{
char*nbuf;
int nsiz;

nsiz= 2048+nlen;
nbuf= realloc(con->out_buf,nsiz);
if(!nbuf)
{
fprintf(stderr,"%s: realloc: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

VERBOSE("Resized buffer: %d\n",nsiz);

con->out_buf= nbuf;
con->out_siz= nsiz;
}
}

/*:352*/
#line 10825 "./matanza.w"
;
memcpy(con->out_buf+con->out_len,buffer,len);
con->out_len+= len;

return 1;
}

/*:349*//*350:*/
#line 10833 "./matanza.w"

int
mat_printf(MatConnection*con,char*format,...)
{
int slen[10];
int len;

ASSERT(con);
ASSERT(format);

/*353:*/
#line 10924 "./matanza.w"

{
va_list arg;
char*tmp;
int strcur= 0;
char dummy_c;
int dummy_d;

va_start(arg,format);

len= 0;
tmp= format;

while(*tmp)
if(*(tmp++)=='%')
switch(*(tmp++))
{
case'%':
len++;
break;

case'd':
dummy_d= va_arg(arg,int);
len+= 10;
break;

case'c':
len++;
dummy_c= (char)va_arg(arg,int);
break;

case's':

ASSERT(strcur<sizeof(slen)/sizeof(int));
slen[strcur]= strlen(va_arg(arg,char*));
len+= slen[strcur++];
break;

default:
ASSERT(0);
}
else
len++;

va_end(arg);
}

/*:353*/
#line 10843 "./matanza.w"
;
/*352:*/
#line 10897 "./matanza.w"

{
int nlen;

nlen= con->out_len+len;

if(nlen>=con->out_siz)
{
char*nbuf;
int nsiz;

nsiz= 2048+nlen;
nbuf= realloc(con->out_buf,nsiz);
if(!nbuf)
{
fprintf(stderr,"%s: realloc: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

VERBOSE("Resized buffer: %d\n",nsiz);

con->out_buf= nbuf;
con->out_siz= nsiz;
}
}

/*:352*/
#line 10844 "./matanza.w"
;
/*351:*/
#line 10851 "./matanza.w"

{
char*write_buf;
int strcur= 0;
va_list arg;

write_buf= con->out_buf+con->out_len;

va_start(arg,format);

while(*format)
if(*format=='%')
{
switch(*(++format))
{
case'%':
*(write_buf++)= *format;
break;
case'd':
write_buf+= sprintf(write_buf,"%d",va_arg(arg,int));
break;
case'c':
*(write_buf++)= (char)va_arg(arg,int);
break;
case's':
memcpy(write_buf,va_arg(arg,char*),slen[strcur]);
write_buf+= slen[strcur++];
break;
default:
ASSERT(0);
}
format++;
}
else
*(write_buf++)= *(format++);

va_end(arg);

ASSERT(write_buf>=con->out_buf);

con->out_len= write_buf-con->out_buf;

ASSERT(con->out_len>=0);
}

/*:351*/
#line 10845 "./matanza.w"
;

return 1;
}

/*:350*//*359:*/
#line 11058 "./matanza.w"

void
mat_sub_rm(MatSub*s,int hf)
{
if(s->m_prev)
s->m_prev->m_next= s->m_next;
else
s->m->info.m.subs[hf]= s->m_next;

if(s->m_next)
s->m_next= s->m_prev;

MAT_SUB_RM_U(s);

free(s);
}

/*:359*//*360:*/
#line 11078 "./matanza.w"

void
mat_sub_machine_rm(MatConnection*m)
{
MatSub*c;
int i;

ASSERT(m->state==MAT_STATE_MACHINE);

for(i= 0;i<MAT_SUB_MACHINE_HASH_SIZE;i++)
{
c= m->info.m.subs[i];
while(c)
{
MatSub*tmp;

MAT_SUB_RM_U(c);

tmp= c;

c= tmp->m_next;

free(tmp);
}
}
}

/*:360*//*361:*/
#line 11108 "./matanza.w"

int
mat_sub_add(MatConnection*m,MatUniverse*un)
{
MatSub*c;
int pos;

c= malloc(sizeof(MatSub));
if(!c)
return 0;

c->u= un;
c->m= m;

c->u_prev= NULL;
c->u_next= un->subs;

if(un->subs)
un->subs->u_prev= c;

un->subs= c;

pos= un->id%MAT_SUB_MACHINE_HASH_SIZE;

c->m_prev= NULL;
c->m_next= m->info.m.subs[pos];

if(m->info.m.subs[pos])
m->info.m.subs[pos]->m_prev= c;

m->info.m.subs[pos]= c;

return 1;
}

/*:361*//*367:*/
#line 11235 "./matanza.w"

void
mat_image_draw(MatConnection*self,MatMovingObj*ship,MatImage*img,
int x,int y,double sp_x,double sp_y,
int startx,int starty,unsigned char*pal,int adj,double alpha)
{
double height,width,sp;
double rate_x,rate_y,pos_x,pos_y;
int size_x,size_y;

ASSERT(ship);
ASSERT(ship->type==MAT_MOVING_OBJ_SHIP);

ASSERT(img);
ASSERT(img->w> 0);
ASSERT(img->h> 0);

ASSERT(ship->info.player.world_wi> 0);
ASSERT(ship->info.player.imgwi> 0);

if(alpha<=0.0)
return;

if(ship->info.player.world_wi!=ship->info.player.imgwi)
{
rate_x= (double)ship->info.player.world_wi/(double)ship->info.player.imgwi;
width= (double)img->w/rate_x;
}
else
{
rate_x= 1;
width= img->w;
}

ASSERT(rate_x> 0);

ASSERT(ship->info.player.world_he> 0);
ASSERT(ship->info.player.imghe> 0);

if(ship->info.player.world_he!=ship->info.player.imghe)
{
rate_y= (double)ship->info.player.world_he/(double)ship->info.player.imghe;
height= (double)img->h/rate_y;
}
else
{
rate_y= 1;
height= img->h;
}

ASSERT(rate_y> 0);

ASSERT(img->w<=ship->un->mapsize_x);
ASSERT(img->h<=ship->un->mapsize_y);

if(adj)
{
double rate_x,rate_y;

size_x= img->w;
size_y= img->h;

rate_x= (double)size_x/(double)ship->un->mapsize_x;
rate_y= (double)size_y/(double)ship->un->mapsize_y;

x= (double)x*rate_x;
y= (double)y*rate_y;
startx= (double)startx*rate_x;
starty= (double)starty*rate_y;
}
else
{
size_x= ship->un->mapsize_x;
size_y= ship->un->mapsize_y;
}

ASSERT(img->w<=size_x);
ASSERT(img->h<=size_y);

ASSERT(0<=startx);
ASSERT(startx<size_x);
ASSERT(0<=starty);
ASSERT(starty<size_y);

ASSERT(0<=x);
ASSERT(x<size_x);
ASSERT(0<=y);
ASSERT(y<size_y);

pos_x= x-startx;
pos_y= y-starty;

ASSERT(-size_x<(int)pos_x);
ASSERT(-size_y<(int)pos_y);
ASSERT((int)pos_x<size_x);
ASSERT((int)pos_y<size_y);

if(0<(int)pos_x)
pos_x-= size_x;
if(0<(int)pos_y)
pos_y-= size_y;

ASSERT((int)pos_x<=0);
ASSERT((int)pos_y<=0);

ASSERT(-size_x<(int)pos_x);
ASSERT(-size_y<(int)pos_y);

sp= sp_x*sp_x+sp_y*sp_y;

if(!arg_motion_blur||sp<1.0/(double)STEPS_MOVEMENT)
{
if(alpha>=1.0)
/*371:*/
#line 11446 "./matanza.w"

{
#define MAT_IMAGE_DRAW_FAST(xx, yy) \
  mat_image_draw_fast(self, ship, img, xx, yy, rate_x, rate_y, width, height, pal)

if(0<(int)pos_x+img->w)
{
if(0<(int)pos_y+img->h)
MAT_IMAGE_DRAW_FAST(pos_x,pos_y);

if((int)pos_y+size_y<ship->info.player.world_he)
MAT_IMAGE_DRAW_FAST(pos_x,pos_y+size_y);
}

if((int)pos_x+size_x<ship->info.player.world_wi)
{
if(0<(int)pos_y+img->h)
MAT_IMAGE_DRAW_FAST(pos_x+size_x,pos_y);

if((int)pos_y+size_y<ship->info.player.world_he)
MAT_IMAGE_DRAW_FAST(pos_x+size_x,pos_y+size_y);
}
}

/*:371*/
#line 11348 "./matanza.w"

else
/*369:*/
#line 11375 "./matanza.w"

{
#define MAT_IMAGE_DRAW_ALPHA(xx, yy) \
  mat_image_draw_alpha(self, ship, img, xx, yy, rate_x, rate_y, width, height, pal, alpha)

ASSERT((int)pos_x<=0);
ASSERT((int)pos_y<=0);

ASSERT(-size_x<(int)pos_x);
ASSERT(-size_y<(int)pos_y);

if(0<(int)pos_x+img->w)
{
if(0<(int)pos_y+img->h)
MAT_IMAGE_DRAW_ALPHA(pos_x,pos_y);

if((int)pos_y+size_y<ship->info.player.world_he)
MAT_IMAGE_DRAW_ALPHA(pos_x,pos_y+size_y);
}

if((int)pos_x+size_x<ship->info.player.world_wi)
{
if(0<(int)pos_y+img->h)
MAT_IMAGE_DRAW_ALPHA(pos_x+size_x,pos_y);

if((int)pos_y+size_y<ship->info.player.world_he)
MAT_IMAGE_DRAW_ALPHA(pos_x+size_x,pos_y+size_y);
}
}

/*:369*/
#line 11350 "./matanza.w"

}
else
/*368:*/
#line 11357 "./matanza.w"

{
int steps;
int i;

sp= sqrt(sp);

steps= sp*STEPS_MOVEMENT;
alpha= alpha/(double)steps;

for(i= 0;i<steps;i++)
{
/*369:*/
#line 11375 "./matanza.w"

{
#define MAT_IMAGE_DRAW_ALPHA(xx, yy) \
  mat_image_draw_alpha(self, ship, img, xx, yy, rate_x, rate_y, width, height, pal, alpha)

ASSERT((int)pos_x<=0);
ASSERT((int)pos_y<=0);

ASSERT(-size_x<(int)pos_x);
ASSERT(-size_y<(int)pos_y);

if(0<(int)pos_x+img->w)
{
if(0<(int)pos_y+img->h)
MAT_IMAGE_DRAW_ALPHA(pos_x,pos_y);

if((int)pos_y+size_y<ship->info.player.world_he)
MAT_IMAGE_DRAW_ALPHA(pos_x,pos_y+size_y);
}

if((int)pos_x+size_x<ship->info.player.world_wi)
{
if(0<(int)pos_y+img->h)
MAT_IMAGE_DRAW_ALPHA(pos_x+size_x,pos_y);

if((int)pos_y+size_y<ship->info.player.world_he)
MAT_IMAGE_DRAW_ALPHA(pos_x+size_x,pos_y+size_y);
}
}

/*:369*/
#line 11369 "./matanza.w"
;
/*370:*/
#line 11406 "./matanza.w"

{
ASSERT(-size_x<(int)pos_x);
ASSERT((int)pos_x<=0);

ASSERT(ABS(sp_x)<=size_x);

pos_x+= sp_x;

ASSERT(2*-size_x<(int)pos_x);
ASSERT((int)pos_x<=size_x);

if((int)pos_x<=-size_x)
pos_x+= size_x;
else if(0<(int)pos_x)
pos_x-= size_x;

ASSERT(-size_x<(int)pos_x);
ASSERT((int)pos_x<=0);

ASSERT(-size_y<(int)pos_y);
ASSERT((int)pos_y<=0);

ASSERT(ABS(sp_y)<=size_y);

pos_y+= sp_y;

ASSERT(2*-size_y<(int)pos_y);
ASSERT((int)pos_y<=size_y);

if((int)pos_y<=-size_y)
pos_y+= size_y;
else if(0<(int)pos_y)
pos_y-= size_y;

ASSERT(-size_y<(int)pos_y);
ASSERT((int)pos_y<=0);
}

/*:370*/
#line 11370 "./matanza.w"
;
}
}

/*:368*/
#line 11353 "./matanza.w"

}

/*:367*//*373:*/
#line 11482 "./matanza.w"

void
mat_image_draw_alpha(MatConnection*self,MatMovingObj*ship,MatImage*img,
double pos_x,double pos_y,double rate_x,double rate_y,
double width,double height,unsigned char*pal,double alpha)
{
int col_x,col_y,col,i,j;
double x1,y1;
MatShip*sh;

ASSERT(width> 0);
ASSERT(height> 0);

ASSERT(rate_x> 0);
ASSERT(rate_y> 0);

ASSERT(ship);
ASSERT(ship->type==MAT_MOVING_OBJ_SHIP);

if(rate_x!=1)
pos_x= (double)pos_x/rate_x;
if(rate_y!=1)
pos_y= (double)pos_y/rate_y;

ASSERT(0<pos_x+width);
ASSERT(0<pos_y+height);

ASSERT(pos_x>=0||-pos_x<width);
ASSERT(pos_y>=0||-pos_y<height);

if(pos_x<0)
x1= -pos_x;
else
x1= 0;

if(pos_y<0)
y1= -pos_y;
else
y1= 0;

ASSERT(x1>=0);
ASSERT(y1>=0);

ASSERT(x1<width);
ASSERT(y1<height);

if((int)pos_x+(int)width>=ship->info.player.imgwi)
width= ship->info.player.imgwi-(int)pos_x-1;

ASSERT((int)pos_x+(int)width<ship->info.player.imgwi);

if((int)pos_y+(int)height>=ship->info.player.imghe)
height= ship->info.player.imghe-(int)pos_y-1;

ASSERT((int)pos_y+(int)height<ship->info.player.imghe);

sh= &ship->info.player;

for(i= (int)y1;i<(int)height;i++)
for(j= (int)x1;j<(int)width;j++)
{
col= 0;
for(col_y= 0;col_y<rate_y&&(int)(i*rate_y)+col_y<img->h;col_y++)
for(col_x= 0;col_x<rate_x&&(int)(j*rate_x)+col_x<img->w;col_x++)
col+= pal[(int)img->img[((int)(i*rate_y)+col_y)*img->w+((int)(j*rate_x)+col_x)]];

ASSERT(0<col_x);
ASSERT(0<col_y);

ASSERT(col>=0);

if(col> 0)
MAT_GRAPH_DRAW_ALPHA(self,sh,(int)pos_x+j,(int)pos_y+i,col/(col_y*col_x),alpha);
}
}
/*:373*//*374:*/
#line 11558 "./matanza.w"

void
mat_image_draw_fast(MatConnection*self,MatMovingObj*ship,MatImage*img,
double pos_x,double pos_y,double rate_x,double rate_y,
double width,double height,unsigned char*pal)
{
int col_x,col_y,col,i,j;
double x1,y1;
MatShip*sh;

ASSERT(width> 0);
ASSERT(height> 0);

ASSERT(rate_x> 0);
ASSERT(rate_y> 0);

ASSERT(ship);
ASSERT(ship->type==MAT_MOVING_OBJ_SHIP);

if(rate_x!=1)
pos_x= (double)pos_x/rate_x;
if(rate_y!=1)
pos_y= (double)pos_y/rate_y;

ASSERT(0<pos_x+width);
ASSERT(0<pos_y+height);

ASSERT(pos_x>=0||-pos_x<width);
ASSERT(pos_y>=0||-pos_y<height);

if(pos_x<0)
x1= -pos_x;
else
x1= 0;

if(pos_y<0)
y1= -pos_y;
else
y1= 0;

ASSERT(x1>=0);
ASSERT(y1>=0);

ASSERT(x1<width);
ASSERT(y1<height);

if((int)pos_x+(int)width>=ship->info.player.imgwi)
width= ship->info.player.imgwi-(int)pos_x-1;

ASSERT((int)pos_x+(int)width<ship->info.player.imgwi);

if((int)pos_y+(int)height>=ship->info.player.imghe)
height= ship->info.player.imghe-(int)pos_y-1;

ASSERT((int)pos_y+(int)height<ship->info.player.imghe);

sh= &ship->info.player;

for(i= (int)y1;i<(int)height;i++)
for(j= (int)x1;j<(int)width;j++)
{
col= 0;
for(col_y= 0;col_y<rate_y&&(int)(i*rate_y)+col_y<img->h;col_y++)
for(col_x= 0;col_x<rate_x&&(int)(j*rate_x)+col_x<img->w;col_x++)
col+= pal[(int)img->img[((int)(i*rate_y)+col_y)*img->w+((int)(j*rate_x)+col_x)]];

ASSERT(0<col_x);
ASSERT(0<col_y);

ASSERT(col>=0);

if(col> 0)
MAT_GRAPH_DRAW(self,sh,(int)pos_x+j,(int)pos_y+i,col/(col_y*col_x));
}
}

/*:374*//*375:*/
#line 11637 "./matanza.w"

void
mat_image_optimize(MatImage*img)
{
int xbeg,xend,ybeg,yend;

/*376:*/
#line 11675 "./matanza.w"

{
MAT_IMAGE_REDUCTION_H(ybeg,0,1);
ASSERT(0<=ybeg);
ASSERT(ybeg<img[0].h);

MAT_IMAGE_REDUCTION_H(yend,img[0].h-1,-1);
ASSERT(ybeg<yend);
ASSERT(yend<img[0].h);

MAT_IMAGE_REDUCTION_X(xbeg,0,1);
ASSERT(0<=xbeg);
ASSERT(xbeg<img[0].w);

MAT_IMAGE_REDUCTION_X(xend,img[0].w-1,-1);
ASSERT(xbeg<xend);
ASSERT(xend<img[0].w);
}

/*:376*/
#line 11643 "./matanza.w"
;
/*377:*/
#line 11695 "./matanza.w"

{
int ang;

for(ang= 0;ang<arg_ang;ang++)
{
char*tmp;
int pos= 0,x,y;

for(y= ybeg;y<yend;y++)
for(x= xbeg;x<xend;x++)
img[ang].img[pos++]= img[ang].img[y*img[ang].w+x];

ASSERT(pos==(xend-xbeg)*(yend-ybeg));


tmp= realloc(img[ang].img,pos);
if(tmp)
img[ang].img= tmp;

img[ang].h= yend-ybeg;
img[ang].w= xend-xbeg;
}
}

/*:377*/
#line 11644 "./matanza.w"
;
}

/*:375*//*382:*/
#line 11756 "./matanza.w"

void
mat_object_kashka(MatMovingObj*obj)
{
MatMovingObj*dst;
int dist_x,dist_dx,dist_dy,dist_y,dist_total;
double sp_x,sp_y;

ASSERT(obj);
ASSERT(obj->un);

ASSERT(obj->type==MAT_MOVING_OBJ_SMART);
ASSERT(obj->info.smart.type==1);
ASSERT(!obj->crash);

if(!obj->un->players_real||obj->un->updates%5)
return;

/*385:*/
#line 11850 "./matanza.w"

{
MatMovingObj*sh;

ASSERT(obj->un->players_head);

dst= NULL;

#if 0
printf("[woozka: [x:%x][y:%x]]\n",obj->pos_x,obj->pos_y);
#endif

for(sh= obj->un->players_head;sh;sh= sh->nexttype)
{
int x,y,dx,dy,total;

/*286:*/
#line 9288 "./matanza.w"

{
double px,sx,py,sy;
double x1,x2,y1,y2;

ASSERT(obj);
ASSERT(sh);

ASSERT(obj->un==sh->un);

ASSERT(!obj->rm_next);
ASSERT(!sh->rm_next);

ASSERT(obj->img);
ASSERT(sh->img);

ADJUST_POSITION(px,obj->pos_x,obj->img->w,obj->un->mapsize_x);
ADJUST_POSITION(sx,sh->pos_x,sh->img->w,obj->un->mapsize_x);

x1= ABS(px-sx);
x2= obj->un->mapsize_x-x1;

if(x1<x2)
x= x1,dx= 1;
else
x= x2,dx= -1;

dx= sx<=px?dx:-dx;

ADJUST_POSITION(py,obj->pos_y,obj->img->h,obj->un->mapsize_y);
ADJUST_POSITION(sy,sh->pos_y,sh->img->h,obj->un->mapsize_y);

y1= ABS(py-sy);
y2= obj->un->mapsize_y-y1;

if(y1<y2)
y= y1,dy= 1;
else
y= y2,dy= -1;

dy= sy<=py?dy:-dy;
}

/*:286*/
#line 11866 "./matanza.w"
;
total= x*x+y*y;

if(!dst||total<dist_total)
{
#if 0
printf("[obj: [x:%x][y:%x]]\n",sh->pos_x,sh->pos_y);
#endif
dst= sh;
dist_total= total;
dist_x= x;
dist_dx= -dx;
dist_y= y;
dist_dy= -dy;
}
}
}

/*:385*/
#line 11774 "./matanza.w"
;
ASSERT(dst);

sp_x= (double)dist_dx*(double)dist_x/(double)(dist_x+dist_y);
sp_y= (double)dist_dy*(double)dist_y/(double)(dist_x+dist_y);

printf("Shoting: %fx%f\n",sp_x,sp_y);
mat_bullet_new(obj,0,sp_x,sp_y,0);
}

/*:382*//*383:*/
#line 11785 "./matanza.w"

void
mat_object_woozka(MatMovingObj*obj)
{
MatMovingObj*dst;
int dist_x,dist_dx,dist_dy,dist_y,dist_total;

ASSERT(obj);
ASSERT(obj->un);

ASSERT(obj->type==MAT_MOVING_OBJ_SMART);
ASSERT(obj->info.smart.type==0);
ASSERT(!obj->crash);

if(!obj->un->players_real)
return;

/*385:*/
#line 11850 "./matanza.w"

{
MatMovingObj*sh;

ASSERT(obj->un->players_head);

dst= NULL;

#if 0
printf("[woozka: [x:%x][y:%x]]\n",obj->pos_x,obj->pos_y);
#endif

for(sh= obj->un->players_head;sh;sh= sh->nexttype)
{
int x,y,dx,dy,total;

/*286:*/
#line 9288 "./matanza.w"

{
double px,sx,py,sy;
double x1,x2,y1,y2;

ASSERT(obj);
ASSERT(sh);

ASSERT(obj->un==sh->un);

ASSERT(!obj->rm_next);
ASSERT(!sh->rm_next);

ASSERT(obj->img);
ASSERT(sh->img);

ADJUST_POSITION(px,obj->pos_x,obj->img->w,obj->un->mapsize_x);
ADJUST_POSITION(sx,sh->pos_x,sh->img->w,obj->un->mapsize_x);

x1= ABS(px-sx);
x2= obj->un->mapsize_x-x1;

if(x1<x2)
x= x1,dx= 1;
else
x= x2,dx= -1;

dx= sx<=px?dx:-dx;

ADJUST_POSITION(py,obj->pos_y,obj->img->h,obj->un->mapsize_y);
ADJUST_POSITION(sy,sh->pos_y,sh->img->h,obj->un->mapsize_y);

y1= ABS(py-sy);
y2= obj->un->mapsize_y-y1;

if(y1<y2)
y= y1,dy= 1;
else
y= y2,dy= -1;

dy= sy<=py?dy:-dy;
}

/*:286*/
#line 11866 "./matanza.w"
;
total= x*x+y*y;

if(!dst||total<dist_total)
{
#if 0
printf("[obj: [x:%x][y:%x]]\n",sh->pos_x,sh->pos_y);
#endif
dst= sh;
dist_total= total;
dist_x= x;
dist_dx= -dx;
dist_y= y;
dist_dy= -dy;
}
}
}

/*:385*/
#line 11802 "./matanza.w"
;
ASSERT(dst);

/*384:*/
#line 11811 "./matanza.w"

{
double des_sp,des_sp_x,des_sp_y;

#if 0
printf("[x:%d][y:%d][sx:%f][sy:%f]\n",dist_dx*dist_x,dist_dy*dist_y,obj->sp_x,obj->sp_y);
#endif

if(dist_x!=0||dist_y!=0)
{
double dist_sum;

dist_sum= (double)dist_x+dist_y;

des_sp_x= obj->sp_x+0.01*(double)dist_dx*(double)dist_x/dist_sum;
des_sp_y= obj->sp_y+0.01*(double)dist_dy*(double)dist_y/dist_sum;

des_sp= sqrt(des_sp_x*des_sp_x+des_sp_y*des_sp_y);

if(des_sp*3<arg_speed_max)
{
obj->sp= des_sp;
obj->sp_x= des_sp_x;
obj->sp_y= des_sp_y;
}
else
{
double tsp;


tsp= (double)arg_speed_max/3;
obj->sp_x= tsp*(double)dist_dx*(double)dist_x/dist_sum;
obj->sp_y= tsp*(double)dist_dy*(double)dist_y/dist_sum;
obj->sp= sqrt(obj->sp_x*obj->sp_x+obj->sp_y*obj->sp_y);
}
}
}

/*:384*/
#line 11805 "./matanza.w"
;

ASSERT(!obj->crash);
}

/*:383*//*390:*/
#line 12004 "./matanza.w"

void
mat_xml_start(void*data,const char*name,const char**atts)
{
MatUniverse*un= data;

if(!strcmp(name,"Universe"))
/*392:*/
#line 12063 "./matanza.w"

{
int i;
for(i= 0;atts[i];i+= 2)
if(!strcmp(atts[i],"mapsizex"))
un->mapsize_x= atoi(atts[i+1]);
else if(!strcmp(atts[i],"mapsizey"))
un->mapsize_y= atoi(atts[i+1]);
else if(!strcmp(atts[i],"name"))
;
else if(!strcmp(atts[i],"background"))
un->bg= mat_png_load(atts[i+1]);
else if(!strcmp(atts[i],"mask"))
un->mask= mat_png_load(atts[i+1]);
else if(!strcmp(atts[i],"dots"))
un->dots= strcmp(atts[i+1],"no")?1:0;
else if(!strcmp(atts[i],"health"))
un->health= atoi(atts[i+1]);
else
{
fprintf(stderr,"%s: %s: Unknown attribute for <Universe>\n",program_name,atts[i]);
exit(EXIT_FAILURE);
}
}

/*:392*/
#line 12011 "./matanza.w"

else if(!strcmp(name,"Location"))
/*391:*/
#line 12022 "./matanza.w"

{
int i,color= 0;
MatLocation*l;

l= malloc(sizeof(MatLocation));
if(!l)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

memcpy(l,&mat_location_default,sizeof(MatLocation));

for(i= 0;atts[i];i+= 2)
if(!strcmp(atts[i],"color"))
color= atoi(atts[i+1]);
else if(!strcmp(atts[i],"shipcrash"))
l->crash[MAT_MOVING_OBJ_SHIP]= strcmp(atts[i+1],"yes")?0:1;
else if(!strcmp(atts[i],"asteroidcrash"))
l->crash[MAT_MOVING_OBJ_AST]= strcmp(atts[i+1],"yes")?0:1;
else if(!strcmp(atts[i],"health"))
l->health= atoi(atts[i+1]);
else if(!strcmp(atts[i],"shipmove"))
l->move[MAT_MOVING_OBJ_SHIP]= atof(atts[i+1]);
else
{
fprintf(stderr,"%s: %s: Unknown attribute for <Location>\n",program_name,atts[i]);
exit(EXIT_FAILURE);
}

if(color<0||color> 255)
{
fprintf(stderr,"%s: %d: Invalid color specified\n",program_name,color);
exit(EXIT_FAILURE);
}

un->location[color]= l;
}

/*:391*/
#line 12013 "./matanza.w"

else
{
fprintf(stderr,"%s: %s: %s: Unknown tag\n",program_name,un->path,name);
exit(EXIT_FAILURE);
}
}

/*:390*//*393:*/
#line 12089 "./matanza.w"

void
mat_xml_end(void*userData,const char*name)
{
}

/*:393*//*397:*/
#line 12125 "./matanza.w"

void
mat_alpha_mod_ship_appear(MatMovingObj*s)
{
s->alpha+= 0.01;
if(s->alpha>=1.0)
{
s->alpha_mod= NULL;
s->crash= 1;
}
}

/*:397*//*398:*/
#line 12138 "./matanza.w"

void
mat_alpha_mod_ship_disappear(MatMovingObj*s)
{
s->alpha-= 0.01;
if(s->alpha<=0)
{
s->alpha_mod= NULL;
}
}/*:398*/
#line 10 "./matanza.w"

/*25:*/
#line 793 "./matanza.w"

int
main(int argc,char**argv)
{
/*81:*/
#line 2375 "./matanza.w"

{
/*96:*/
#line 3195 "./matanza.w"

program_name= strrchr(argv[0],'/');
if(program_name)
program_name++;
else
program_name= argv[0];

/*:96*/
#line 2377 "./matanza.w"
;
/*92:*/
#line 2693 "./matanza.w"

{
int iterate= 1;
int show_help= 0;
int show_version= 0;
int prompt_password= 0;

while(iterate)
{
int oi= 0;
static struct option lopt[]= 
{
{"help",no_argument,NULL,'h'},
{"version",no_argument,NULL,'v'},
{"max-players",required_argument,NULL,'m'},
{"bold",no_argument,NULL,'b'},
{"imgwidth",required_argument,NULL,'W'},
{"health",required_argument,NULL,1},
{"mapsize-x",required_argument,NULL,'x'},
{"mapsize-y",required_argument,NULL,'y'},
{"lives",required_argument,NULL,'l'},
{"angles",required_argument,NULL,'A'},
{"no-chat",no_argument,NULL,2},
{"team",required_argument,NULL,'t'},
{"password",optional_argument,NULL,'p'},
{"teams-safe",no_argument,NULL,3},
{"no-share",no_argument,NULL,4},
{"ang-speed-max",required_argument,NULL,5},
{"fly-back",no_argument,NULL,6},
{"no-brake",no_argument,NULL,7},
{"air",no_argument,NULL,8},
{"speed-max",required_argument,NULL,9},
{"asteroids",required_argument,NULL,10},
{"limits",no_argument,NULL,11},
{"no-radar",no_argument,NULL,12},
{"invisible",required_argument,NULL,13},
{"ppc",required_argument,NULL,14},
{"bg",required_argument,NULL,15},
{"mapsize-img",no_argument,NULL,16},
{"ship-friction",required_argument,NULL,17},
{"dots",no_argument,NULL,18},
{"nodots",no_argument,NULL,26},
{"bg-adjust",no_argument,NULL,19},
{"no-compress",no_argument,NULL,20},
{"bg-highcol",required_argument,NULL,21},
{"space",no_argument,NULL,22},
{"port",required_argument,NULL,23},
{"usleep",required_argument,NULL,24},
{"port-machine",required_argument,NULL,25},
{"ship-img",required_argument,NULL,27},
{"free-at-exit",no_argument,NULL,28},
{"verbose",no_argument,NULL,29},
{0,0,0,0}
};

switch(getopt_long(argc,argv,"hvm:bW:x:y:l:A:t:p::",lopt,&oi))
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
case'm':
arg_max_players= atoi(optarg);
break;
case'b':
arg_bold= 1;
break;
case'W':
arg_imgwidth= atoi(optarg);
break;
case 1:
arg_health= atoi(optarg);
break;
case'x':
arg_mapsize_x= atoi(optarg);
break;
case'y':
arg_mapsize_y= atoi(optarg);
break;
case'l':
arg_lives= atoi(optarg);
break;
case'A':
arg_ang= atoi(optarg);
break;
case 2:
arg_chat= 0;
break;
case't':
/*94:*/
#line 3054 "./matanza.w"

{
MatTeam*t;
char*m;

t= malloc(sizeof(MatTeam));
if(!t)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

m= strrchr(optarg,':');

if(m)
{
*m= 0;
if(m> optarg+MAT_TEAM_MAX)
{
fprintf(stderr,"%s: %s: Name too long\n",program_name,optarg);
exit(EXIT_FAILURE);
}
t->max= atoi(m+1);
}
else
t->max= 0;

t->name= optarg;
t->cur= 0;
t->times_dead= 0;
t->head= NULL;
t->next= arg_teams_head;
t->prev= NULL;

if(arg_teams_head)
arg_teams_head->prev= t;
else
arg_teams_tail= t;

arg_teams_head= t;

arg_teams_count++;
}

/*:94*/
#line 2787 "./matanza.w"
;
break;
case'p':
if(optarg)
arg_password= optarg;
else
prompt_password= 1;
break;
case 3:
arg_teams_safe= 1;
break;
case 4:
arg_teams_share= 0;
break;
case 5:
arg_ang_speed_max= ((double)atoi(optarg))/STEPS_MOVEMENT;
break;
case 6:
arg_fly_back= 1;
break;
case 7:
arg_brake= 0;
break;
case 8:
arg_space= 0;
break;
case 9:
arg_speed_max= (double)atoi(optarg);
break;
case 10:
arg_ast_num= atoi(optarg);
break;
case 11:
arg_limits= 1;
break;
case 12:
arg_radar= 0;
break;
case 13:
arg_visible_init= atoi(optarg);
break;
case 14:
arg_ppc= atoi(optarg);
break;
case 15:
/*302:*/
#line 9662 "./matanza.w"

{
MatImgWorld*tmp;

tmp= malloc(sizeof(MatImgWorld));
if(!tmp)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

tmp->path= optarg;

tmp->next= NULL;
tmp->prev= mat_bg_tail;

if(mat_bg_tail)
mat_bg_tail->next= tmp;
else
mat_bg_head= tmp;

mat_bg_tail= tmp;
}

/*:302*/
#line 2832 "./matanza.w"
;
break;
case 16:
arg_bg_size= 1;
break;
case 17:
arg_ship_friction= atof(optarg);
mat_location_default.move[MAT_MOVING_OBJ_SHIP]= arg_ship_friction;
break;
case 18:
arg_bg_dots= 1;
break;
case 19:
arg_bg_adj= 1;
break;
case 20:
arg_compress= 0;
break;
case 21:
arg_bg_color_max= atoi(optarg);
break;
case 22:
arg_space= 1;
break;
case 23:
arg_port= atoi(optarg);
break;
case 24:
arg_usleep= atol(optarg);
break;
case 25:
arg_port_machine= atoi(optarg);
break;
case 26:
arg_bg_dots= 0;
break;
case 27:
arg_ship_graphic_path= optarg;
break;
case 28:
arg_free_at_exit= 1;
break;
case 29:
#if MATANZA_VERBOSE
arg_verbose= 1;
#endif
break;
default:
printf("Try '%s --help' for more information.\n",program_name);
exit(EXIT_FAILURE);
}
}

if(show_help)
{
printf("Usage: %s [OPTION]... [FILE]\n"
"Start the Matanza server, reading the universe from FILE\n\n"
"  -h, --help                  Show this information and exit\n"
"  -v, --version               Show version number and exit\n"
"  -m, --max-players=NUM       Never allow more than NUM players\n"
"  -b, --bold                  Use bold characters too\n"
"  -W, --imgwidth=NUM          Image width for default zoom (320)\n"
"  --health=NUM                Health of ships (1000)\n"
"  -x, --mapsize-x=NUM         Map size in the x coordinate\n"
"  -y, --mapsize-y=NUM         Map size in the y coordinate\n"
"  -l, --lives=NUM             Number of lives for the players\n"
"  -A, --angles=NUM            Number of angles for rotations\n"
"  --no-chat                   Disable the chat features\n"
"  -t, --team=STR[:NUM]        Add team STR with maximum NUM players\n"
"  -p, --password[=STR]        Perform authentication using STR as the password\n"
"  --teams-safe                Bullets won't hit players of the same team\n"
"  --no-share                  Players in the same team don't share lives\n"
"  --ang-speed-max=NUM         Maximum angular speed for ships (try 0)\n"
"  --fly-back                  Players will be able to fly backwards\n"
"  --no-brake                  Players will not be able to brake\n"
"  --air                       Ships' speed depend on their angle\n"
"  --speed-max=NUM             Maximum speed (0 = Unlimited)\n"
"  --asteroids=NUM             The number of asteroids at a given moment\n"
"  --limits                    Give the world limits; make it end\n"
"  --no-radar                  When enemy is away, don't show the direction\n"
"  --invisible=NUM             Allow players to become invisible for NUM rounds\n"
"  --ppc=NUM                   Set the number of Players Per Connection\n"
"  --bg=PATH                   Load background image from FILE\n"
"  --mapsize-img               Set the map's size to the background's size\n"
"  --ship-friction=NUM         Set the ship's friction (0 <= NUM <= 1)\n"
"  --dots                      Show dots on the background\n"
"  --nodots                    Don't show dots on the background\n"
"  --bg-adjust                 Adjust the backgrounds to the mapsize\n"
"  --no-compress               Don't perform bandwidth optimizations\n"
"  --bg-highcol=NUM            Adjust the colors in the background\n"
"  --space                     Ships' speed doesn't depend on their angle\n"
"  --port=NUM                  Use TCP port NUM for telnet\n"
"  --usleep=NUM                Sleep NUM microseconds between updates\n"
"  --port-machine=NUM          Use TCP port NUM for machines' friendly protocol\n"
"  --ship-img=PATH             Load image of the ship from PATH\n"
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

if(prompt_password)
{
fprintf(stderr,"%s: Prompting for a password is not supported (yet)\n",program_name);
fprintf(stderr,"%s: Try --password=<string>\n",program_name);
exit(EXIT_FAILURE);
}

while(optind<argc)
{
MatUniverse*un;

un= malloc(sizeof(MatUniverse));
if(!un)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

un->path= argv[optind++];

MAT_UNIVERSES_ADD(un);
}

if(arg_ship_graphic_path)
/*93:*/
#line 2972 "./matanza.w"

{
FILE*in;
int i,j;
int wr= 0;

in= fopen(arg_ship_graphic_path,"r");
if(!in)
{
fprintf(stderr,"%s: open: %s: %s\n",program_name,arg_ship_graphic_path,strerror(errno));
exit(EXIT_FAILURE);
}

arg_ship_graphic= malloc(MAT_SHIPSIZE_X*MAT_SHIPSIZE_Y);
if(!arg_ship_graphic)
{
fprintf(stderr,"%s: malloc: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

for(i= 0;i<MAT_SHIPSIZE_Y;i++)
for(j= 0;j<MAT_SHIPSIZE_X;j++)
{
int c;

ASSERT(wr==i*MAT_SHIPSIZE_X+j);

c= getc(in);
switch(c)
{
case'\n':
memset(arg_ship_graphic+wr,' ',MAT_SHIPSIZE_X-j);
wr+= MAT_SHIPSIZE_X-j;
j= MAT_SHIPSIZE_X-1;
break;

case'#':
while((c= getc(in))!=EOF)
if(c=='\n')
break;

if(j==0)
j--;
else
{
memset(arg_ship_graphic+wr,' ',MAT_SHIPSIZE_X-j);
wr+= MAT_SHIPSIZE_X-j;
j= MAT_SHIPSIZE_X-1;
}

break;

case' ':
case'*':
case'1':
case'2':
case'X':
case'.':
arg_ship_graphic[wr++]= c;
break;

case EOF:
memset(arg_ship_graphic+wr,' ',MAT_SHIPSIZE_X*MAT_SHIPSIZE_Y-wr);
j= MAT_SHIPSIZE_X-1;
i= MAT_SHIPSIZE_Y-1;
break;

default:

fprintf(stderr,"%s: %s: Invalid character: %c\n",
program_name,arg_ship_graphic_path,c);
exit(EXIT_FAILURE);
}

ASSERT(wr==i*MAT_SHIPSIZE_X+j+1);
}

fclose(in);
}

/*:93*/
#line 2966 "./matanza.w"
;

/*95:*/
#line 3099 "./matanza.w"

{
if(!arg_teams_count)
{
if(arg_teams_safe)
fprintf(stderr,"%s: --teams-safe used in individual mode\n",program_name);
if(!arg_teams_share)
fprintf(stderr,"%s: --no-share used in individual mode\n",program_name);
}

if(arg_imgwidth<=0)
{
fprintf(stderr,"%s: width <= 0\n",program_name);
arg_imgwidth= 80*4;
}

#if 0
if(arg_mapsize_x<arg_imgwidth+MAT_SHIPSIZE_X)
{
fprintf(stderr,"%s: mapsize-x < imgwidth + %d\n",program_name,MAT_SHIPSIZE_X);
arg_mapsize_x= arg_imgwidth+MAT_SHIPSIZE_X;
}

if(arg_mapsize_y<arg_imgheight+MAT_SHIPSIZE_Y)
{
fprintf(stderr,"%s: mapsize-y < imgheight + %d\n",program_name,MAT_SHIPSIZE_Y);
arg_mapsize_y= arg_imgheight+MAT_SHIPSIZE_Y;
}
#endif

if(arg_ang<1)
{
fprintf(stderr,"%s: angles < 1\n",program_name);
arg_ang= 1;
}

if(arg_port<1)
{
fprintf(stderr,"%s: port < 1\n",program_name);
arg_port= 7993;
}

if(arg_port_machine<1)
{
fprintf(stderr,"%s: port < 1\n",program_name);
arg_port_machine= 7993;
}

if(arg_speed_max<0)
{
fprintf(stderr,"%s: speed-max < 0\n",program_name);
arg_speed_max= 0;
}

if(arg_fly_back&&!arg_brake)
{
fprintf(stderr,"%s: fly-back && !arg_brake\n",program_name);
arg_brake= 1;
}

if(arg_lives<1)
{
fprintf(stderr,"%s: lives < 1\n",program_name);
arg_lives= 1;
}

if(arg_ppc!=1&&arg_ppc!=2)
{
fprintf(stderr,"%s: ppc != 1 && ppc != 2\n",program_name);
fprintf(stderr,"%s: 1 and 2 are the only supported values\n",program_name);
arg_ppc= 1;
}

if(arg_ppc!=1)
arg_chat= 0;

if(arg_ship_friction<0)
{
fprintf(stderr,"%s: ship-friction < 0\n",program_name);
arg_ship_friction= 0.0;
}
else if(arg_ship_friction> 1)
{
fprintf(stderr,"%s: ship-friction > 1\n",program_name);
arg_ship_friction= 1.0;
}

arg_ship_friction= 1-arg_ship_friction;
}

/*:95*/
#line 2968 "./matanza.w"
;
}

/*:92*/
#line 2378 "./matanza.w"
;
srand(time(NULL));
/*364:*/
#line 11166 "./matanza.w"

{
int i;

mat_cos= malloc(sizeof(double)*arg_ang);
mat_sin= malloc(sizeof(double)*arg_ang);
if(!mat_cos||!mat_sin)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

for(i= 0;i<arg_ang;i++)
{
double ang;

ang= PI*2.0*(double)i/(double)arg_ang;
mat_cos[i]= cos(ang);
mat_sin[i]= sin(ang);
}
}

/*:364*/
#line 2380 "./matanza.w"
;
/*105:*/
#line 3477 "./matanza.w"

{






/*123:*/
#line 4099 "./matanza.w"

{
unsigned short*next;
struct parameters*parameters;
unsigned short*table;
unsigned short*filltable;

static int priority[]= {4,5,3,2,1};
int i;
int i1,i2,i3,i4;
int sum,pos;
int first= -1;
int last= -1;

VERBOSE("Building tables used for rendering...");
fflush(stdout);

next= malloc(sizeof(*next)*TABLESIZE);
parameters= malloc(sizeof(struct parameters)*(NCHARS+1));
table= malloc(TABLESIZE*sizeof(*table));
filltable= malloc(256*sizeof(*filltable));

first= -1;
last= -1;

for(i= 0;i<TABLESIZE;i++)
next[i]= i,table[i]= 0;

/*119:*/
#line 3986 "./matanza.w"

{
int c;
int ma1= 0,ma2= 0,ma3= 0,ma4= 0,msum= 0;
int mi1= 50000,mi2= 50000,mi3= 50000,mi4= 50000,misum= 50000;

/*118:*/
#line 3925 "./matanza.w"

{
int v1,v2,v3,v4;
int c;

for(c= 0;c<NCHARS;c++)
{
if(!ALOWED(c,MAT_GRAPH_SUPPORTED))
continue;

/*117:*/
#line 3832 "./matanza.w"

{
int i;
int car;
unsigned const char*font;

font= graph_font->data;

car= (c%256)*graph_font->height;

v1= 0;
v2= 0;
v3= 0;
v4= 0;

for(i= 0;i<graph_font->height/2;i++)
{
v1+= (isset(0,font[car+i])
+isset(1,font[car+i])
+isset(2,font[car+i])
+isset(3,font[car+i]));
v2+= (isset(4,font[car+i])
+isset(5,font[car+i])
+isset(6,font[car+i])
+isset(7,font[car+i]));
}

for(;i<graph_font->height;i++)
{
v3+= (isset(0,font[car+i])
+isset(1,font[car+i])
+isset(2,font[car+i])
+isset(3,font[car+i]));
v4+= (isset(4,font[car+i])
+isset(5,font[car+i])
+isset(6,font[car+i])
+isset(7,font[car+i]));
}

v1*= MUL;
v2*= MUL;
v3*= MUL;
v4*= MUL;

switch(c/256)
{
case MAT_REVERSE:
v1= graph_font->height*2*MUL-v1;
v2= graph_font->height*2*MUL-v2;
v3= graph_font->height*2*MUL-v3;
v4= graph_font->height*2*MUL-v4;
break;
case MAT_DIM:
v1= (v1+1)/MAT_GRAPH_DIMMUL;
v2= (v2+1)/MAT_GRAPH_DIMMUL;
v3= (v3+1)/MAT_GRAPH_DIMMUL;
v4= (v4+1)/MAT_GRAPH_DIMMUL;
break;
case MAT_BOLD:
v1*= MAT_GRAPH_BOLDMUL;
v2*= MAT_GRAPH_BOLDMUL;
v3*= MAT_GRAPH_BOLDMUL;
v4*= MAT_GRAPH_BOLDMUL;
break;
case MAT_BOLDFONT:
for(i= 0;i<graph_font->height/2;i++)
{
v1+= (isset(0,font[car+i])
+canset(1,font[car+i])
+canset(2,font[car+i])
+canset(3,font[car+i]))*MUL;
v2+= (isset(4,font[car+i])
+canset(5,font[car+i])
+canset(6,font[car+i])
+canset(7,font[car+i]))*MUL;
}
for(;i<graph_font->height;i++)
{
v3+= (isset(0,font[car+i])
+canset(1,font[car+i])
+canset(2,font[car+i])
+canset(3,font[car+i]))*MUL;
v4+= (isset(4,font[car+i])
+canset(5,font[car+i])
+canset(6,font[car+i])
+canset(7,font[car+i]))*MUL;
}
}
}

/*:117*/
#line 3935 "./matanza.w"
;

if(v1> ma1)
ma1= v1;
if(v2> ma2)
ma2= v2;
if(v3> ma3)
ma3= v3;
if(v4> ma4)
ma4= v4;

if(v1+v2+v3+v4> msum)
msum= v1+v2+v3+v4;

if(v1<mi1)
mi1= v1;
if(v2<mi2)
mi2= v2;
if(v3<mi3)
mi3= v3;
if(v4<mi4)
mi4= v4;

if(v1+v2+v3+v4<misum)
misum= v1+v2+v3+v4;

parameters[c].p[0]= v1;
parameters[c].p[1]= v2;
parameters[c].p[2]= v3;
parameters[c].p[3]= v4;
}
msum-= misum;

#if 0
mi1= misum/4;
mi2= misum/4;
mi3= misum/4;
mi4= misum/4;

ma1= msum/4;
ma2= msum/4;
ma3= msum/4;
ma4= msum/4;
#endif
}

/*:118*/
#line 3992 "./matanza.w"
;

for(c= 0;c<NCHARS;c++)
/*120:*/
#line 4001 "./matanza.w"

{
parameters[c].p[4]= (double)
(parameters[c].p[0]
+parameters[c].p[1]
+parameters[c].p[2]
+parameters[c].p[3]
-misum)*(1020/(double)msum)+0.5;

parameters[c].p[0]= ((double)(parameters[c].p[0]-mi1)*(255/(double)ma1)+0.5);
parameters[c].p[1]= ((double)(parameters[c].p[1]-mi2)*(255/(double)ma2)+0.5);
parameters[c].p[2]= ((double)(parameters[c].p[2]-mi3)*(255/(double)ma3)+0.5);
parameters[c].p[3]= ((double)(parameters[c].p[3]-mi4)*(255/(double)ma4)+0.5);

/*121:*/
#line 4020 "./matanza.w"

if(parameters[c].p[0]> 255)
parameters[c].p[0]= 255;
if(parameters[c].p[1]> 255)
parameters[c].p[1]= 255;
if(parameters[c].p[2]> 255)
parameters[c].p[2]= 255;
if(parameters[c].p[3]> 255)
parameters[c].p[3]= 255;
if(parameters[c].p[0]<0)
parameters[c].p[0]= 0;
if(parameters[c].p[1]<0)
parameters[c].p[1]= 0;
if(parameters[c].p[2]<0)
parameters[c].p[2]= 0;
if(parameters[c].p[3]<0)
parameters[c].p[3]= 0;

/*:121*/
#line 4015 "./matanza.w"
;
}

/*:120*/
#line 3995 "./matanza.w"
;
}

/*:119*/
#line 4127 "./matanza.w"
;

for(i= 0;i<NCHARS;i++)
{
if(ALOWED(i,MAT_GRAPH_SUPPORTED))
{
int p1,p2,p3,p4;

i1= parameters[i].p[0];
i2= parameters[i].p[1];
i3= parameters[i].p[2];
i4= parameters[i].p[3];

p1= i1>>4;
p2= i2>>4;
p3= i3>>4;
p4= i4>>4;

sum= parameters[i].p[4];
pos= pos(p1,p2,p3,p4);

if(table[pos])
{
int sum;

p1= (p1<<4)+p1;
p2= (p2<<4)+p2;
p3= (p3<<4)+p3;
p4= (p4<<4)+p4;

sum= p1+p2+p3+p4;

if((p1= dist(parameters[i].p[0],
parameters[i].p[1],
parameters[i].p[2],
parameters[i].p[3],
parameters[i].p[4],
p1,p2,p3,p4,sum))>=
(p1= dist(parameters[table[pos]].p[0],
parameters[table[pos]].p[1],
parameters[table[pos]].p[2],
parameters[table[pos]].p[3],
parameters[table[pos]].p[4],
p1,p2,p3,p4,sum))&&(p1!=p2||priority[i/256]<=priority[table[pos]/256]))
goto skip;
}
table[pos]= i;
add(pos);
skip:;

}
}
for(pos= 0;pos<256;pos++){
int mindist= INT_MAX,d1;
for(i= 0;i<NCHARS;i++){
if(ALOWED(i,MAT_GRAPH_SUPPORTED)){
d1= dist1(parameters[i].p[0],
parameters[i].p[1],
parameters[i].p[2],
parameters[i].p[3],
parameters[i].p[4],
pos,pos,pos,pos,pos*4);
if(d1<=mindist
&&(d1!=mindist
||priority[i/256]> priority[filltable[pos]/256]))
filltable[pos]= i,mindist= d1;
}
}
}
do{
int blocked;
if(last!=-1)
next[last]= last;
else
break;
blocked= last;
i= first;
if(i==-1)
break;
first= last= -1;
do{
int m1,m2,m3,m4,ii,dm;
unsigned short c= table[i];
postoparams(i,m1,m2,m3,m4);
for(dm= 0;dm<4;dm++)
for(ii= -1;ii<=1;ii+= 2){
int dist,dist1,index;
unsigned short ch;
i1= m1;
i2= m2;
i3= m3;
i4= m4;
switch(dm){
case 0:
i1+= ii;
if(i1<0||i1>=16)
continue;
break;
case 1:
i2+= ii;
if(i2<0||i2>=16)
continue;
break;
case 2:
i3+= ii;
if(i3<0||i3>=16)
continue;
break;
case 3:
i4+= ii;
if(i4<0||i4>=16)
continue;
break;

}
index= pos(i1,i2,i3,i4);
ch= table[index];
if(ch==c||index==blocked)
continue;
if(ch){
int ii1= (i1<<4)+i1;
int ii2= (i2<<4)+i2;
int ii3= (i3<<4)+i3;
int ii4= (i4<<4)+i4;
int iisum= ii1+ii2+ii3+ii4;
dist= dist(
ii1,ii2,ii3,ii4,iisum,
parameters[c].p[0],
parameters[c].p[1],
parameters[c].p[2],
parameters[c].p[3],
parameters[c].p[4]);
dist1= dist(
ii1,ii2,ii3,ii4,iisum,
parameters[ch].p[0],
parameters[ch].p[1],
parameters[ch].p[2],
parameters[ch].p[3],
parameters[ch].p[4]);
}
if(!ch||dist<dist1){
table[index]= c;
add(index);
}
}
i1= i;
i= next[i];
next[i1]= i1;
}
while(i!=i1);
}
while(last!=-1);

free(next);

graph_table= table;
graph_filltable= filltable;
graph_parameters= parameters;

VERBOSE("Done\n");
}

/*:123*/
#line 3485 "./matanza.w"
;

uncompressfont(&aa_font16);
}

/*:105*/
#line 2381 "./matanza.w"
;
/*86:*/
#line 2575 "./matanza.w"

{
/*300:*/
#line 9614 "./matanza.w"

{
MatImgWorld*tmp;

for(tmp= mat_bg_head;tmp;tmp= tmp->next)
{
tmp->img= mat_png_load(tmp->path);
if(arg_bg_color_max!=-1)
{
int col_min= 0;
int col_max= arg_bg_color_max;

MatImage*img= tmp->img;

/*278:*/
#line 9101 "./matanza.w"

{
unsigned char col_r_min,col_r_max;
int bufsize= img->h*img->w;

/*280:*/
#line 9136 "./matanza.w"

{
int i;

col_r_min= col_r_max= img->img[0];

for(i= 1;i<bufsize;i++)
{
unsigned char tmp= img->img[i];

if(tmp<col_r_min)
col_r_min= tmp;
else if(col_r_max<tmp)
col_r_max= tmp;
}
}

/*:280*/
#line 9106 "./matanza.w"
;

if(col_r_min!=col_min||col_r_max!=col_max)
/*279:*/
#line 9114 "./matanza.w"

{
double rate;
int i;

ASSERT(bufsize==img->h*img->w);

if(col_r_max==col_r_min)
rate= 0;
else
rate= ((double)col_max-(double)col_min)/((double)col_r_max-(double)col_r_min);

for(i= 0;i<bufsize;i++)
{
img->img[i]= col_min+(img->img[i]-col_r_min)*rate;
ASSERT(col_min<=img->img[i]);
ASSERT(img->img[i]<=col_max);
}
}

/*:279*/
#line 9109 "./matanza.w"
;
}

/*:278*/
#line 9628 "./matanza.w"
;
}
}

for(tmp= mat_fg_head;tmp;tmp= tmp->next)
tmp->img= mat_png_load(tmp->path);

if(arg_bg_size&&(mat_bg_head||mat_fg_tail))
arg_mapsize_x= arg_mapsize_y= 0;

for(tmp= mat_bg_head;tmp;tmp= tmp->next)
{
arg_mapsize_x= MAX(arg_mapsize_x,tmp->img->w);
arg_mapsize_y= MAX(arg_mapsize_y,tmp->img->h);
}

for(tmp= mat_fg_head;tmp;tmp= tmp->next)
{
arg_mapsize_x= MAX(arg_mapsize_x,tmp->img->w);
arg_mapsize_y= MAX(arg_mapsize_y,tmp->img->h);
}
}

/*:300*/
#line 2577 "./matanza.w"
;
/*197:*/
#line 7003 "./matanza.w"

{
int i,j,ang,size;

VERBOSE("Calculating rotations of ships... ");
fflush(stdout);

mat_ship= malloc(sizeof(MatImage)*arg_ang);
if(!mat_ship)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

size= (int)sqrt(MAT_SHIPSIZE_X*MAT_SHIPSIZE_X+MAT_SHIPSIZE_Y*MAT_SHIPSIZE_Y)+1;

for(ang= 0;ang<arg_ang;ang++)
{
double c,s;

c= mat_cos[ang];
s= mat_sin[ang];

mat_ship[ang].w= size;
mat_ship[ang].h= size;

mat_ship[ang].img= malloc(mat_ship[ang].w*mat_ship[ang].h);
if(!mat_ship[ang].img)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

for(j= -size/2;j<size/2;j++)
for(i= -size/2;i<size/2;i++)
{
double x,y;

x= i*c-j*s;
y= i*s+j*c;

ASSERT(0<=POS_SHIP(j,i));
ASSERT(POS_SHIP(j,i)<mat_ship[ang].w*mat_ship[ang].h);

if((int)x<-MAT_SHIPSIZE_X/2||(int)x>=MAT_SHIPSIZE_X/2
||(int)y<-MAT_SHIPSIZE_Y/2||(int)y>=MAT_SHIPSIZE_Y/2)
{
mat_ship[ang].img[POS_SHIP(j,i)]= ' ';
}
else
{
ASSERT((int)y+MAT_SHIPSIZE_Y/2<MAT_SHIPSIZE_Y);
ASSERT((int)x+MAT_SHIPSIZE_X/2<MAT_SHIPSIZE_X);
ASSERT(0<=POS_SHIP_ORIGINAL(y,x));
ASSERT(POS_SHIP_ORIGINAL(y,x)<MAT_SHIPSIZE_X*MAT_SHIPSIZE_Y);
mat_ship[ang].img[POS_SHIP(j,i)]= arg_ship_graphic[POS_SHIP_ORIGINAL(y,x)];
}
}
}
VERBOSE("Done\nOptimizing images for the ships... [%dx%d]",
mat_ship[0].h,mat_ship[0].w);
fflush(stdout);

mat_image_optimize(mat_ship);

VERBOSE(" -> [%dx%d]\n",mat_ship[0].h,mat_ship[0].w);
}

/*:197*/
#line 2578 "./matanza.w"
;
/*196:*/
#line 6916 "./matanza.w"

{
int i,j,ang;
double x,y,c,s;

VERBOSE("Calculating rotations of missiles... ");
fflush(stdout);

mat_missile[0]= malloc(sizeof(MatImage)*arg_ang);
mat_missile[1]= malloc(sizeof(MatImage)*arg_ang);
mat_missile[2]= malloc(sizeof(MatImage)*arg_ang);
if(!mat_missile[0]||!mat_missile[1]||!mat_missile[2])
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

for(ang= 0;ang<arg_ang;ang++)
{
c= mat_cos[ang];
s= mat_sin[ang];

mat_missile[0][ang].w= MAT_MISSILESIZE_X;
mat_missile[1][ang].w= MAT_MISSILESIZE_X;
mat_missile[2][ang].w= MAT_MISSILESIZE_X;

mat_missile[0][ang].h= MAT_MISSILESIZE_Y;
mat_missile[1][ang].h= MAT_MISSILESIZE_Y;
mat_missile[2][ang].h= MAT_MISSILESIZE_Y;

mat_missile[0][ang].img= malloc(MAT_MISSILESIZE_X*MAT_MISSILESIZE_Y);
mat_missile[1][ang].img= malloc(MAT_MISSILESIZE_X*MAT_MISSILESIZE_Y);
mat_missile[2][ang].img= malloc(MAT_MISSILESIZE_X*MAT_MISSILESIZE_Y);
if(!mat_missile[0][ang].img||!mat_missile[1][ang].img||!mat_missile[2][ang].img)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

for(j= -MAT_MISSILESIZE_Y/2;j*2<MAT_MISSILESIZE_Y;j++)
for(i= -MAT_MISSILESIZE_X/2;i*2<MAT_MISSILESIZE_X;i++)
{
x= i*c-j*s;
y= i*s+j*c;

if(x<-MAT_MISSILESIZE_X/2||x> MAT_MISSILESIZE_X/2
||y<-MAT_MISSILESIZE_Y/2||y> MAT_MISSILESIZE_Y/2)
{
mat_missile[0][ang].img[POS_MISSILE(j,i)]= ' ';
mat_missile[1][ang].img[POS_MISSILE(j,i)]= ' ';
mat_missile[2][ang].img[POS_MISSILE(j,i)]= ' ';
}
else
{
mat_missile[0][ang].img[POS_MISSILE(j,i)]= mat_graph_missile[0][POS_MISSILE(y,x)];
mat_missile[1][ang].img[POS_MISSILE(j,i)]= mat_graph_missile[1][POS_MISSILE(y,x)];
mat_missile[2][ang].img[POS_MISSILE(j,i)]= mat_graph_missile[2][POS_MISSILE(y,x)];
}
}
}
VERBOSE("Done\nOptimizing images for [%dx%d] [%dx%d] [%dx%d]",
mat_missile[0][0].h,mat_missile[0][0].w,
mat_missile[1][0].h,mat_missile[1][0].w,
mat_missile[2][0].h,mat_missile[2][0].w);
fflush(stdout);

mat_image_optimize(mat_missile[0]);
mat_image_optimize(mat_missile[1]);
mat_image_optimize(mat_missile[2]);

VERBOSE(" -> [%dx%d] [%dx%d] [%dx%d]\n",
mat_missile[0][0].h,mat_missile[0][0].w,
mat_missile[1][0].h,mat_missile[1][0].w,
mat_missile[2][0].h,mat_missile[2][0].w);
}

/*:196*/
#line 2579 "./matanza.w"
;
/*194:*/
#line 6824 "./matanza.w"

{
int i,j,ang;
double x,y,c,s;

if(arg_ast_num> 0)
{
VERBOSE("Calculating rotations of asteroids... ");
fflush(stdout);

mat_ast[0]= malloc(sizeof(MatImage)*arg_ang);
mat_ast[1]= malloc(sizeof(MatImage)*arg_ang);
if(!mat_ast[0]||!mat_ast[1])
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

for(ang= 0;ang<arg_ang;ang++)
{
c= mat_cos[ang];
s= mat_sin[ang];

mat_ast[0][ang].w= MAT_AST_SIZE_X;
mat_ast[1][ang].w= MAT_AST_SIZE_X;

mat_ast[0][ang].h= MAT_AST_SIZE_Y;
mat_ast[1][ang].h= MAT_AST_SIZE_Y;

mat_ast[0][ang].img= malloc(MAT_AST_SIZE_X*MAT_AST_SIZE_Y);
mat_ast[1][ang].img= malloc(MAT_AST_SIZE_X*MAT_AST_SIZE_Y);
if(!mat_ast[0][ang].img||!mat_ast[1][ang].img)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

for(j= -MAT_AST_SIZE_Y/2;j*2<MAT_AST_SIZE_Y;j++)
for(i= -MAT_AST_SIZE_X/2;i*2<MAT_AST_SIZE_X;i++)
{
x= i*c-j*s;
y= i*s+j*c;

if(x<-MAT_AST_SIZE_X/2||x> MAT_AST_SIZE_X/2
||y<-MAT_AST_SIZE_Y/2||y> MAT_AST_SIZE_Y/2)
{
mat_ast[0][ang].img[POS_AST(j,i)]= ' ';
mat_ast[1][ang].img[POS_AST(j,i)]= ' ';
}
else
{
mat_ast[0][ang].img[POS_AST(j,i)]= mat_graph_ast[0][POS_AST(y,x)];
mat_ast[1][ang].img[POS_AST(j,i)]= mat_graph_ast[1][POS_AST(y,x)];
}
}
}
VERBOSE("Done\nOptimizing images for the asteroids... [%dx%d] [%dx%d]",
mat_ast[0][0].h,mat_ast[0][0].w,mat_ast[1][0].h,mat_ast[1][0].w);
fflush(stdout);

mat_image_optimize(mat_ast[0]);
mat_image_optimize(mat_ast[1]);

VERBOSE(" -> [%dx%d] [%dx%d]\n",
mat_ast[0][0].h,mat_ast[0][0].w,mat_ast[1][0].h,mat_ast[1][0].w);
}
}

/*:194*/
#line 2580 "./matanza.w"
;
}

/*:86*/
#line 2382 "./matanza.w"
;
/*281:*/
#line 9155 "./matanza.w"

{
int i;

for(i= 0;i<3;i++)
{
mat_ship_palette[i]= malloc(sizeof(int)*256);
if(!mat_ship_palette[i])
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

mat_ship_palette[i]['*']= 100;
mat_ship_palette[i]['X']= 255;
mat_ship_palette[i]['.']= 0;
mat_ship_palette[i][' ']= 0;
}

mat_ship_palette[2]['1']= 255;
mat_ship_palette[2]['2']= 255;
mat_ship_palette[2]['3']= 255;
mat_ship_palette[2]['4']= 255;

mat_ship_palette[1]['1']= 0;
mat_ship_palette[1]['2']= 255;
mat_ship_palette[1]['3']= 100;
mat_ship_palette[1]['4']= 255;

mat_ship_palette[0]['1']= 0;
mat_ship_palette[0]['2']= 0;
mat_ship_palette[0]['3']= 100;
mat_ship_palette[0]['4']= 100;
}

/*:281*/
#line 2383 "./matanza.w"
;
/*84:*/
#line 2513 "./matanza.w"

{
if(mat_universes_count)
{
MatUniverse*un;
int i;

for(i= 0;i<MAT_UNIVERSES_HASH_SIZE;i++)
for(un= mat_universes[i];un;un= un->next_hash)
/*388:*/
#line 11957 "./matanza.w"

{
XML_Parser*prs;
FILE*in;
char buf[BUFSIZ];
int done;

/*394:*/
#line 12096 "./matanza.w"

in= fopen(un->path,"r");
if(!in)
{
fprintf(stderr,"%s: %s: %s\n",program_name,un->path,strerror(errno));
exit(EXIT_FAILURE);
}

/*:394*/
#line 11964 "./matanza.w"
;

/*319:*/
#line 9963 "./matanza.w"

{
int i;

ASSERT(un);

un->players_head= un->players_tail= NULL;
un->bullets= un->ast= un->objs= un->smart_objs= NULL;

un->objs_rm= (void*)&main;

un->players_real= un->ast_cur= 0;
un->pause= 0;

un->subs= NULL;

un->updates= 0;

for(i= 0;i<256;i++)
un->location[i]= NULL;

ASSERT(sizeof("Default Universe")+1<MAX_UNIVERSE_NAME);

strcpy(un->name,"Default Universe");

un->mapsize_x= arg_mapsize_x;
un->mapsize_y= arg_mapsize_y;

un->dots= arg_bg_dots;
un->health= arg_health;
}

/*:319*/
#line 11966 "./matanza.w"
;

prs= XML_ParserCreate(NULL);

XML_SetUserData(prs,un);
XML_SetElementHandler(prs,mat_xml_start,mat_xml_end);

do
{
size_t len;

len= fread(buf,1,sizeof(buf),in);
done= len<sizeof(buf);
if(!XML_Parse(prs,buf,len,done))
{
fprintf(stderr,"%s: %s:%d: %s\n",program_name,un->path,
XML_GetCurrentLineNumber(prs),XML_ErrorString(XML_GetErrorCode(prs)));
exit(EXIT_FAILURE);
}
}
while(!done);

XML_ParserFree(prs);

/*322:*/
#line 10096 "./matanza.w"

{
int i;
for(i= 0;i<256;i++)
if(un->location[i]==NULL)
un->location[i]= &mat_location_default;
}

/*:322*/
#line 11990 "./matanza.w"
;
}

/*:388*/
#line 2522 "./matanza.w"
;
}
else
/*85:*/
#line 2531 "./matanza.w"

{
MatUniverse*un;
int i;

un= malloc(sizeof(MatUniverse));
if(!un)
{
fprintf(stderr,"%s: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

MAT_UNIVERSES_ADD(un);

/*319:*/
#line 9963 "./matanza.w"

{
int i;

ASSERT(un);

un->players_head= un->players_tail= NULL;
un->bullets= un->ast= un->objs= un->smart_objs= NULL;

un->objs_rm= (void*)&main;

un->players_real= un->ast_cur= 0;
un->pause= 0;

un->subs= NULL;

un->updates= 0;

for(i= 0;i<256;i++)
un->location[i]= NULL;

ASSERT(sizeof("Default Universe")+1<MAX_UNIVERSE_NAME);

strcpy(un->name,"Default Universe");

un->mapsize_x= arg_mapsize_x;
un->mapsize_y= arg_mapsize_y;

un->dots= arg_bg_dots;
un->health= arg_health;
}

/*:319*/
#line 2545 "./matanza.w"
;

for(i= 0;i<256;i++)
un->location[i]= NULL;

un->path= NULL;

un->crash_damage[MAT_MOVING_OBJ_SHIP]= 200;

un->bg= un->mask= NULL;

/*295:*/
#line 9494 "./matanza.w"

{
ASSERT(un);

while(un->ast_cur<arg_ast_num)
AST_ADD_RANDOMPOS(0,un);

#if 0
arg_ast_num= mat_ast_cur;
fprintf(stderr,"%s: Resetting number of asteroids to %d\n",program_name,arg_ast_num);
#endif
}

/*:295*/
#line 2556 "./matanza.w"
;

#if 0
MAT_SMART_OBJ_ADD_KASHKA(un);
MAT_SMART_OBJ_ADD_KASHKA(un);
MAT_SMART_OBJ_ADD_KASHKA(un);

MAT_SMART_OBJ_ADD_WOOZKA(un);
MAT_SMART_OBJ_ADD_WOOZKA(un);
MAT_SMART_OBJ_ADD_WOOZKA(un);
#endif

/*325:*/
#line 10135 "./matanza.w"

{
if(un->bg)
{
if(un->bg->w> un->mapsize_x)
un->mapsize_x= un->bg->w;

if(un->bg->h> un->mapsize_y)
un->mapsize_y= un->bg->h;
}
}

/*:325*/
#line 2568 "./matanza.w"
;

ASSERT(!un->bg||un->bg->w<=un->mapsize_x);
ASSERT(!un->bg||un->bg->h<=un->mapsize_x);
}

/*:85*/
#line 2525 "./matanza.w"
;
}

/*:84*/
#line 2384 "./matanza.w"
;
/*88:*/
#line 2597 "./matanza.w"

{
#if HAVE_SIGNAL
#  ifdef SIGPIPE
signal(SIGPIPE,SIG_IGN);
#  endif
#  ifdef SIGINT
signal(SIGINT,term_handler);
#  endif
#  ifdef SIGTERM
signal(SIGTERM,term_handler);
#  endif
#  ifdef SIGTTOU
signal(SIGTTOU,SIG_IGN);
#  endif
#  ifdef SIGTTIN
signal(SIGTTIN,SIG_IGN);
#  endif
#  ifdef SIGTSTP
signal(SIGTSTP,SIG_IGN);
#  endif
#endif
}

/*:88*/
#line 2385 "./matanza.w"
;
/*346:*/
#line 10691 "./matanza.w"

{
#if HAVE_WSASTARTUP
WORD ver;
WSADATA data;
int err;

ver= MAKEWORD(2,2);

err= WSAStartup(ver,&data);
if(err!=0)
{
fprintf(stderr,"%s: WSAStartup: Initialization failed.\n",program_name);
exit(EXIT_FAILURE);
}
#endif
}

/*:346*/
#line 2386 "./matanza.w"
;
/*82:*/
#line 2403 "./matanza.w"

{
printf("-=> Matanza has been succesfully started.\n");
printf("-=> Connect to port %d to play.\n",arg_port);
}

/*:82*/
#line 2387 "./matanza.w"
;

#if MATANZA_VERBOSE
if(!arg_verbose)
#endif
/*83:*/
#line 2410 "./matanza.w"

#if HAVE_FORK
{
pid_t childpid;


childpid= fork();
if(childpid<0)
{
fprintf(stderr,"%s: fork: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
else if(childpid> 0)
exit(EXIT_SUCCESS);

#if HAVE_SETSID

if(setsid()<0)
{
fprintf(stderr,"%s: setsid: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}


childpid= fork();
if(childpid<0)
{
fprintf(stderr,"%s: fork: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}
else if(childpid> 0)
exit(EXIT_SUCCESS);
#endif
}
#endif

#if 0
{
int fd;
int dev_null;


dev_null= open("/dev/null",O_RDWR);
if(dev_null<0)
{
fprintf(stderr,"%s: open: /dev/null: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}


if(dup2(dev_null,0)<0)
{
fprintf(stderr,"%s: dup2: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

if(hbd_log_msg)
{

fd= open(hbd_log_msg,O_CREAT|O_WRONLY|O_APPEND,0666);
if(fd<0)
{
fprintf(stderr,"%s: open: %s: %s\n",program_name,hbd_log_msg,strerror(errno));
exit(EXIT_FAILURE);
}
}
else
fd= dev_null;


if(dup2(fd,1)<0)
{
fprintf(stderr,"%s: dup2: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}

if(hbd_log_err)
{

fd= open(hbd_log_err,O_CREAT|O_WRONLY|O_APPEND,0666);
if(fd<0)
{
fprintf(stderr,"%s: open: %s: %s\n",program_name,
hbd_log_err,strerror(errno));
exit(EXIT_FAILURE);
}
}
else
fd= dev_null;


if(dup2(fd,2)<0)
{
fprintf(stderr,"%s: dup2: %s\n",program_name,strerror(errno));
exit(EXIT_FAILURE);
}


for(fd= getdtablesize()-1;fd> 2;fd--)
close(fd);
}
#endif
/*:83*/
#line 2392 "./matanza.w"
;


chdir("/");

mat_mainsock= mat_listen(arg_port);
mat_mainsock_machine= mat_listen(arg_port_machine);

}

/*:81*/
#line 797 "./matanza.w"
;

while(1)
if(players_count==0)
{
/*28:*/
#line 845 "./matanza.w"

{
fd_set i;

ASSERT(players_count==0);

FD_ZERO(&i);
FD_SET(mat_mainsock,&i);
FD_SET(mat_mainsock_machine,&i);

VERBOSE("-=> select\n");
select(MAX(mat_mainsock,mat_mainsock_machine)+1,&i,NULL,NULL,NULL);
VERBOSE("<=- select\n");
}

/*:28*/
#line 802 "./matanza.w"
;
/*26:*/
#line 823 "./matanza.w"

{
VERBOSE("-=> accept incomming connections\n");
mat_accept(mat_mainsock,0);
mat_accept(mat_mainsock_machine,1);
VERBOSE("<=- accept incomming connections\n");
}

/*:26*/
#line 803 "./matanza.w"
;
}
else
{
unsigned long old,now;

GETMICROSECOND_GENERIC(old);

/*26:*/
#line 823 "./matanza.w"

{
VERBOSE("-=> accept incomming connections\n");
mat_accept(mat_mainsock,0);
mat_accept(mat_mainsock_machine,1);
VERBOSE("<=- accept incomming connections\n");
}

/*:26*/
#line 811 "./matanza.w"
;
/*60:*/
#line 1900 "./matanza.w"

{
MatConnection*con;

con= connections;
while(con)
if(con->state==MAT_STATE_REMOVE)
{
MatConnection*tmp;

tmp= con->next;
/*59:*/
#line 1880 "./matanza.w"

{
ASSERT(con);
ASSERT(con->state==MAT_STATE_REMOVE);

if(con->prev)
con->prev->next= con->next;
else
connections= con->next;

if(con->next)
con->next->prev= con->prev;

players_count--;

free(con);
}

/*:59*/
#line 1911 "./matanza.w"
;
con= tmp;
}
else
{
mat_input(con);
con= con->next;
}
}

/*:60*/
#line 812 "./matanza.w"
;
/*27:*/
#line 832 "./matanza.w"

{
int i;
MatUniverse*un;

VERBOSE("-=> update universes\n");
for(i= 0;i<MAT_UNIVERSES_HASH_SIZE;i++)
for(un= mat_universes[i];un;un= un->next_hash)
/*33:*/
#line 987 "./matanza.w"

{
if(!un->pause&&un->players_real)
{
un->updates++;

/*36:*/
#line 1050 "./matanza.w"

{
MatMovingObj*pl;

for(pl= un->players_head;pl;pl= pl->nexttype)
{
if(pl->info.player.bullets_expire> 0)
pl->info.player.bullets_expire--;

if(pl->info.player.ship_speed_inc> 0)
pl->info.player.ship_speed_inc--;

if(pl->alpha_mod)
pl->alpha_mod(pl);

if(!pl->info.player.visible&&pl->info.player.visible_exp--<=0)
{
pl->info.player.visible= 1;
VISIBILITY_BROADCAST(pl);
}
}
}

/*:36*/
#line 993 "./matanza.w"
;
/*387:*/
#line 11941 "./matanza.w"

{
MatMovingObj*obj;

for(obj= un->smart_objs;obj;obj= obj->nexttype)
{
ASSERT(obj->type==MAT_MOVING_OBJ_SMART);
ASSERT(obj->info.smart.type<sizeof(mat_objects)/sizeof(MatSmartObjType));
mat_objects[obj->info.smart.type].function(obj);
}
}



/*:387*/
#line 994 "./matanza.w"
;
/*34:*/
#line 1003 "./matanza.w"

{
MatMovingObj*obj;

for(i= 0;i<STEPS_MOVEMENT;i++)
for(obj= un->objs;obj;obj= obj->next)
if(!obj->rm_next)
{
if(obj->crash)
{
int crash_wall,crash_x,crash_y;

/*29:*/
#line 861 "./matanza.w"

{
MatImage*img;

img= un->mask;

if(!img)
crash_wall= 0;
else
{
crash_x= ((int)obj->pos_x+obj->img->w/2)%un->mapsize_x;
crash_y= ((int)obj->pos_y+obj->img->h/2)%un->mapsize_y;

if(crash_x>=img->w||crash_y>=img->h)
crash_wall= 0;
else
{
ASSERT(img->img);
ASSERT(un->location[img->img[crash_x+crash_y*img->w]]);

crash_wall= un->location[img->img[crash_x+crash_y*img->w]]->crash[obj->type];
}
}
}

/*:29*/
#line 1015 "./matanza.w"
;

if(crash_wall)
/*30:*/
#line 887 "./matanza.w"

{
switch(obj->type)
{
case MAT_MOVING_OBJ_BULLET:

obj->info.bullet.expires= 0;
break;

case MAT_MOVING_OBJ_SHIP:
if(arg_space)
/*31:*/
#line 912 "./matanza.w"

{
int pos0,pos1,pos2;
double spx,spy;

/*32:*/
#line 931 "./matanza.w"

{
int x0,y0,x1,y1,x2,y2;

spx= obj->sp_x;
spy= obj->sp_y;

if(spx> 0)
{
if(spy> 0)
{
x0= crash_x-1;
y0= crash_y;
x1= crash_x-1;
y1= crash_y-1;
x2= crash_x;
y2= crash_y-1;
}
else
{
x0= crash_x;
y0= crash_y+1;
x1= crash_x-1;
y1= crash_y+1;
x2= crash_x-1;
y2= crash_y;
}
}
else
{
if(spy> 0)
{
x0= crash_x;
y0= crash_y-1;
x1= crash_x+1;
y1= crash_y-1;
x2= crash_x+1;
y2= crash_y;
}
else
{
x0= crash_x+1;
y0= crash_y;
x1= crash_x+1;
y1= crash_y+1;
x2= crash_x;
y2= crash_y+1;
}
}
}

/*:32*/
#line 917 "./matanza.w"
;










}

/*:31*/
#line 898 "./matanza.w"
;
break;

case MAT_MOVING_OBJ_AST:
if(arg_space)
{
obj->sp_x= -obj->sp_x;
obj->sp_y= -obj->sp_y;
}
break;
}
}

/*:30*/
#line 1018 "./matanza.w"

else
/*39:*/
#line 1157 "./matanza.w"

{
MatMovingObj*i;

ASSERT((int)obj->pos_x>=0);
ASSERT((int)obj->pos_x<un->mapsize_x);

ASSERT((int)obj->pos_y>=0);
ASSERT((int)obj->pos_y<un->mapsize_y);

for(i= obj->next;i;i= i->next)
if(!i->rm_next&&i->crash)
{
int crash= 0;

if(obj->img&&i->img&&/*51:*/
#line 1585 "./matanza.w"

((((int)(obj->pos_x-i->pos_x)>=0&&(int)(obj->pos_x-i->pos_x)<i->img->w)
||((int)(i->pos_x-obj->pos_x)>=0&&(int)(i->pos_x-obj->pos_x)<obj->img->w)
||(un->mapsize_x+(int)(obj->pos_x-i->pos_x)<i->img->w)
||(un->mapsize_x+(int)(i->pos_x-obj->pos_x)<obj->img->w))
&&(((int)(obj->pos_y-i->pos_y)>=0&&(int)(obj->pos_y-i->pos_y)<i->img->h)
||((int)(i->pos_y-obj->pos_y)>=0&&(int)(i->pos_y-obj->pos_y)<obj->img->h)
||(un->mapsize_y+(int)(obj->pos_y-i->pos_y)<i->img->h)
||(un->mapsize_y+(int)(i->pos_y-obj->pos_y)<obj->img->h)))

/*:51*/
#line 1172 "./matanza.w"
)
{
MatMovingObj*src,*dst;
int xmod,ymod,xbeg,xend,ybeg,yend,xtmp,ytmp;

ASSERT((int)i->pos_x>=0);
ASSERT((int)i->pos_x<un->mapsize_x);

ASSERT((int)i->pos_y>=0);
ASSERT((int)i->pos_y<un->mapsize_y);

if(obj->img->h*obj->img->w<=i->img->h*i->img->w)
src= obj,dst= i;
else
src= i,dst= obj;

xmod= dst->pos_x-src->pos_x;
if(xmod> 0&&xmod> un->mapsize_x/2)
xmod= un->mapsize_x-xmod;
else if(xmod<0&&xmod<-un->mapsize_x/2)
xmod= -un->mapsize_x-xmod;

ASSERT(ABS(xmod)<src->img->w||ABS(xmod)<dst->img->w);

ymod= dst->pos_y-src->pos_y;
if(ymod> 0&&ymod> un->mapsize_y/2)
ymod= un->mapsize_y-ymod;
else if(ymod<0&&ymod<-un->mapsize_y/2)
ymod= -un->mapsize_y-ymod;

ASSERT(ABS(ymod)<src->img->h||ABS(ymod)<dst->img->h);

xbeg= MAX(0,xmod);
xend= MIN(src->img->w,xmod+dst->img->w);

ybeg= MAX(0,ymod);
yend= MIN(src->img->h,ymod+dst->img->h);

for(ytmp= ybeg;ytmp<yend;ytmp++)
for(xtmp= xbeg;xtmp<xend;xtmp++)
{
ASSERT(xtmp<src->img->w);
ASSERT(ytmp<src->img->h);
ASSERT(xtmp-xmod<dst->img->w);
ASSERT(ytmp-ymod<dst->img->h);
if(src->pal[src->img->img[(xtmp)+(ytmp)*src->img->w]]> 0
&&dst->pal[dst->img->img[(xtmp-xmod)+(ytmp-ymod)*dst->img->w]]> 0)
{
crash= 1;
xtmp= xend;
ytmp= yend;
}
}
}
else if(obj->img||i->img)
{
MatMovingObj*src,*b;

src= obj->img?obj:i;
b= obj->img?i:obj;

/*40:*/
#line 1268 "./matanza.w"

{
int posx;

CHECK_HIT_BULLET(posx,b->pos_x,src->pos_x,src->img->w,un->mapsize_x);

if(posx!=-1)
{
int posy;

CHECK_HIT_BULLET(posy,b->pos_y,src->pos_y,src->img->h,un->mapsize_y);

if(posy!=-1)
{
ASSERT(!crash);
crash= src->pal[src->img->img[posx+posy*src->img->w]]> 0;
}
}
}

/*:40*/
#line 1233 "./matanza.w"
;
}

if(crash)
{
ASSERT(i->crash);
ASSERT(obj->crash);
crash_handler[i->type](i,obj);
}
}
}

/*:39*/
#line 1020 "./matanza.w"
;
}
/*37:*/
#line 1075 "./matanza.w"

{
MatImage*img;

img= un->mask;
if(img)
{
int x,y;

x= (int)obj->pos_x+obj->img->w/2%obj->un->mapsize_x;
y= (int)obj->pos_y+obj->img->h/2%obj->un->mapsize_y;

if(x<img->w&&y<img->h)
{
double index;

index= un->location[img->img[x+y*img->w]]->move[obj->type];
if(index!=1.0)
{
(obj)->sp_x*= (index);
(obj)->sp_y*= (index);
(obj)->sp= sqrt(obj->sp_x*obj->sp_x+obj->sp_y*obj->sp_y);
}
}
}
}

/*:37*/
#line 1022 "./matanza.w"
;
/*52:*/
#line 1597 "./matanza.w"

{
ASSERT(-un->mapsize_x<(int)obj->sp_x);
ASSERT((int)obj->sp_x<un->mapsize_x);
ASSERT((int)obj->pos_x>=0);
ASSERT((int)obj->pos_x<un->mapsize_x);

ASSERT(-un->mapsize_y<(int)obj->sp_y);
ASSERT((int)obj->sp_y<un->mapsize_y);
ASSERT((int)obj->pos_y>=0);
ASSERT((int)obj->pos_y<un->mapsize_y);

obj->pos_x+= obj->sp_x;
obj->pos_y+= obj->sp_y;

ASSERT(-un->mapsize_x<=(int)obj->pos_x);
ASSERT((int)obj->pos_x<2*un->mapsize_x);

ASSERT(-un->mapsize_y<=(int)obj->pos_y);
ASSERT((int)obj->pos_y<2*un->mapsize_y);

if((int)obj->pos_x<0)
{
if(!arg_limits||obj->type!=MAT_MOVING_OBJ_SHIP)
{
obj->pos_x+= un->mapsize_x;
ASSERT(0<=(int)obj->pos_x);
}
else
{
obj->pos_x= 0;
obj->sp_x= 0;
}
}
else if((int)obj->pos_x>=un->mapsize_x)
{
if(!arg_limits||obj->type!=MAT_MOVING_OBJ_SHIP)
{
obj->pos_x-= un->mapsize_x;
ASSERT((int)obj->pos_x<un->mapsize_x);
}
else
{
obj->pos_x= un->mapsize_x-1;
obj->sp_x= 0;
}
}

if((int)obj->pos_y<0)
{
if(!arg_limits||obj->type!=MAT_MOVING_OBJ_SHIP)
{
obj->pos_y+= un->mapsize_y;
ASSERT(0<=(int)obj->pos_y);
}
else
{
obj->pos_y= 0;
obj->sp_y= 0;
}
}
else if((int)obj->pos_y>=un->mapsize_y)
{
if(!arg_limits||obj->type!=MAT_MOVING_OBJ_SHIP)
{
obj->pos_y-= un->mapsize_y;
ASSERT((int)obj->pos_y<un->mapsize_y);
}
else
{
obj->pos_y= un->mapsize_y;
obj->sp_y= 0;
}
}

ASSERT((int)obj->pos_x>=0);
ASSERT((int)obj->pos_x<un->mapsize_x);

ASSERT((int)obj->pos_y>=0);
ASSERT((int)obj->pos_y<un->mapsize_y);

ASSERT((int)obj->ang>=0);
ASSERT((int)obj->ang<arg_ang);

obj->ang+= obj->sp_ang;
if((int)obj->ang>=arg_ang)
obj->ang-= arg_ang;
else if((int)obj->ang<0)
obj->ang+= arg_ang;

if(!arg_space&&obj->sp_ang!=0&&obj->type==MAT_MOVING_OBJ_SHIP)
{
obj->sp_x= obj->sp*mat_sin[(int)obj->ang];
obj->sp_y= obj->sp*mat_cos[(int)obj->ang];
}

ASSERT((int)obj->ang>=0);
ASSERT((int)obj->ang<arg_ang);
}

/*:52*/
#line 1023 "./matanza.w"
;
}
}

/*:34*/
#line 995 "./matanza.w"
;
/*35:*/
#line 1028 "./matanza.w"

{
MatMovingObj*b;

ASSERT(un);

for(b= un->bullets;b;b= b->nexttype)
{
ASSERT(b->info.bullet.expires>=0);
if(b->info.bullet.expires--==0)
{
REMOVE_QUEUE_ADD(b);

ASSERT(b->info.bullet.src);
ASSERT(b->info.bullet.src->refs> 0);

mat_moving_obj_unref(b->info.bullet.src);
}
}
}

/*:35*/
#line 996 "./matanza.w"
;
/*38:*/
#line 1110 "./matanza.w"

{
MatMovingObj*tmp;

while(un->objs_rm!=(void*)&main)
{
MatMovingObj*next;

next= un->objs_rm->rm_next;
ASSERT(next);

if(un->objs_rm->nexttype)
un->objs_rm->nexttype->prevtype= un->objs_rm->prevtype;

if(un->objs_rm->prevtype)
un->objs_rm->prevtype->nexttype= un->objs_rm->nexttype;
else
switch(un->objs_rm->type)
{
case MAT_MOVING_OBJ_SHIP:
break;
case MAT_MOVING_OBJ_BULLET:
un->bullets= un->bullets->nexttype;
break;
case MAT_MOVING_OBJ_AST:
un->ast= un->ast->nexttype;
break;
default:
ASSERT(0);
}

DEL_MOVING_OBJ(un->objs_rm);

free(un->objs_rm);
un->objs_rm= next;
}

ASSERT_FOR(tmp= un->players_head;tmp;tmp= tmp->nexttype)
ASSERT(!tmp->rm_next);
ASSERT_FOR(tmp= un->bullets;tmp;tmp= tmp->nexttype)
ASSERT(!tmp->rm_next);
ASSERT_FOR(tmp= un->ast;tmp;tmp= tmp->nexttype)
ASSERT(!tmp->rm_next);
}

/*:38*/
#line 997 "./matanza.w"
;
}
}

/*:33*/
#line 840 "./matanza.w"
;
VERBOSE("<=- update universes\n");
}

/*:27*/
#line 813 "./matanza.w"
;
/*57:*/
#line 1852 "./matanza.w"

{
MatConnection*i;

for(i= connections;i;i= i->next)
if(i->state!=MAT_STATE_REMOVE&&i->anim_func)
i->anim_func(i);
}

/*:57*/
#line 814 "./matanza.w"
;

GETMICROSECOND_GENERIC(now);

/*58:*/
#line 1863 "./matanza.w"

{
unsigned long usec;
unsigned long elapsed;

elapsed= now-old;

usec= elapsed<arg_usleep?arg_usleep-elapsed:0;

ASSERT(usec<=arg_usleep);

if(usec> 0)
USLEEP_GENERIC(usec);
}

/*:58*/
#line 818 "./matanza.w"
;
}
}

/*:25*/
#line 11 "./matanza.w"


/*:1*/
