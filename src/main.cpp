#ifdef STEAM
#include "steam/steam_api.h"
#include "steam/isteamuserstats.h"
#endif
#ifdef WIN32
#define SDL_MAIN_HANDLED
#endif
#define TVR_COUNT 12

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_FontCache.h"
#include "inifile.h"
#ifdef ANDROID
#include <sys/stat.h>
#include <sys/types.h>
#include <android/log.h>
#define TAG "PODVAL"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,    TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,     TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,     TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,    TAG, __VA_ARGS__)
#else
#define LOGE(...) printf(__VA_ARGS__)
#define LOGW(...) printf(__VA_ARGS__)
#define LOGI(...) printf(__VA_ARGS__)
#define LOGD(...) printf(__VA_ARGS__)
#endif
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#include <random>
#include <functional>
#ifdef WIN32
#include <windows.h>
#endif
#include <sstream>
#include <ctime>
#include <math.h>
#include <iostream>
using namespace std;
using namespace inifile;
#define STRINGS_COUNT 77
#if  defined(linux_install)
const string global_data_dir="/usr/share/dark-podval/";
const string save_data_dir=getenv("HOME")+"/.local/share/dark-podval/";
#elif defined(WIN32)
const string global_data_dir="data/";
const string save_data_dir="data/";
const string mkdir_commend="md ";
#elif defined(ANDROID)
const string global_data_dir="";
string save_data_dir;
#else
const string global_data_dir="data/";
const string save_data_dir="data/";
#endif
#if defined(WIN32)
const string mkdir_command="md ";
#else
const string mkdir_command="mkdir ";
#endif
SDL_Texture *load(const char *way);
bool p(int,int,int,int);
bool change_gate();
bool change_block();
void draw(bool,bool,bool);
bool nadpis(string,int,int);
void gates();
void guns();
void lasers();
void pits();
void rocks();
void portals();
void bullets();
void bombs();
void set_camera(unsigned short,unsigned short,bool);
bool gin(uint8_t* c);
bool gin(int* c);
void subtitres(bool);
void open(string);
void save(string);
void keys();
template<typename T>
char in(T& in);
template<typename T>
unsigned short in16(T& in);
template<typename T>
void out(T& in);
template<typename T>
void out16(T& in);
void open_old(string);
void create_laser(uint8_t x,uint8_t y,uint8_t n);
bool inputwh(string,uint8_t,uint8_t);
bool console();
SDL_Surface *create_surface(int width,int height);
int get_level_c(int w,int h);
void minimap();
void game_init(bool restart);
string command(string);
uint8_t input_number(uint8_t);
bool pause();
bool end(bool,bool,bool);
bool in_range(int,int,int);
bool in_range(int,int,int,int,int,int);
int test(int,int);
vector<vector<uint8_t>> maze_generate(int w,int h);
uint8_t lidtoln(string lid);
string lntolid(uint8_t ln);
string postlid(string lid);
bool editor(bool);
stringstream RWstream(const char *filename);
char *RWget(const char *filename);
void sensor_draw();
void destroy_subt();
int main(int argv,char **argc);
bool Back();
void load_subtitles();
void action_lrd();
void create_kvadrat();
bool floor_type();
bool code(unsigned short c);
void load_passwords();
unsigned short password(uint8_t x,uint8_t y);
bool is_password_door(uint8_t x,uint8_t y);
bool is_terminal(uint8_t x,uint8_t y);
bool is_password_door(uint8_t a);
bool is_terminal(uint8_t a);
void RESIZE(void *data, int size);
float get_zoom();
void about();
uint8_t lidtoln(string lid) {
	uint8_t ln=0;
	ln+=(lid[0]-'0')*110;
	ln+=(lid[1]-'0'-1)*11;
	ln+=(lid[3]-'0')*10;
	ln+=(lid[4]-'0'-1);
	return ln;
}

string lntolid(uint8_t ln) {
	string lid;
	int ch=ln/11+1;
	int lvl=ln%11+1;
	lid+=ch/10+'0';
	lid+=ch%10+'0';
	lid+='-';
	lid+=lvl/10+'0';
	lid+=lvl%10+'0';
	return lid;
}

string postlid(string lid) {
	if(lid[4]=='9') {
		lid[3]++;
		lid[4]='0';
	} else if(lid[4]=='1' && lid[3]=='1') {
		lid[4]='1';
		lid[3]='0';
		lid[1]++;
	} else lid[4]++;
	return lid;
}

struct Wire {
	Wire() {};
	Wire(uint8_t xp1,uint8_t yp1,uint8_t xp2,uint8_t yp2,bool ap=0) {
		x1=xp1;
		y1=yp1;
		x2=xp2;
		y2=yp2;
		active=ap;
	}
	void show();
	uint8_t x1,y1,x2,y2;
	bool active=0;
};
std::vector<Wire> wire;
struct Gate {
	Gate() {};
	Gate(uint8_t xp,uint8_t yp,uint8_t tp,int vp=0,bool ap=0) {
		x=xp;
		y=yp;
		type=tp;
		value=vp;
		active=ap;
	}
	void show();
	uint8_t x,y,type;
	int value=0;
	bool active=0;
};
std::vector<Gate> gate;
struct Player {
	virtual void load_texture(){
		texture=load(string(global_data_dir+"textures/hero.png").c_str());
	}
	unsigned short x,y;
	uint8_t n;
	void show();
	int bar(bool,uint8_t,bool);
	int dietimer=0,timerr=0;
	uint8_t block();
	void move(int8_t,uint8_t);
	void replace(uint8_t);
	void replace_back(uint8_t,uint8_t);
	bool can_go(bool*,uint8_t,bool);
	virtual void kill();
	void clear();
	SDL_Texture* texture;
	uint8_t door_key[18];
	bool push=0;
	uint8_t speed=40;
	bool infhealth=0;
	bool noclip=0;
	uint8_t bring=0;
	uint8_t lives=1;
	uint8_t sx,sy;
	void go();
	void basic_action();
	virtual void action();
	bool update();
	~Player(){
		SDL_DestroyTexture(texture);
	}
}gg;
struct Provodnik : Player {
	void load_texture(){
		texture=load(string(global_data_dir+"textures/prov.png").c_str());
	}
	void kill(){}
	void action();

};
Player *player=&gg;
struct Bullet {
	Bullet() {};
	Bullet(int x,int y,int n,int type);
	Bullet(unsigned short x,unsigned short y,uint8_t n,uint8_t type);
	unsigned short x,y;
	uint8_t n,type;
	void show();
	bool p();
	void move();
};
std::vector<Bullet> bullet;
struct Rock {
	unsigned short x,y;
	void show();
	int update();
	int tm;
	uint8_t type;
	void kill();
};
std::vector<Rock> rock;

struct Profile {
	bool load(uint8_t n);
	bool save(uint8_t n);
	void clear(uint8_t n);
	void new_game();
	string name;
	uint8_t level=0;
} profile;
struct Mouse {
	bool state=0;
	uint8_t touch=0;
	int time=0;
	int x,y,sx,sy;
	int b;
	int timestamp();
	bool update();
	void wait();
	inline int dx();
	inline int dy();
} mouse;
struct Scrollbar {
	void set(int xp,int yp,int hp);
	int update(bool u);
	int getp();
	bool motion=0;
	int x,y,h,p=0;
};
struct Laser {
	void show();
	uint8_t n();
	bool p();
	uint8_t x1,y1,x2,y2;
};
std::vector<Laser> laser;
struct Select {
	short x1,y1,x2,y2,sx=0,sy=0;
	bool state=0;
	uint8_t l[255][255];
	void show();
	void select();
};
struct History {
	History();
	uint8_t l[255][255];
	uint8_t wl,hl;
	std::vector<Gate> gat;
	std::vector<Wire> wir;
	void save();
	void load();
};
std::vector<History> hs;
struct LRD {
	LRD(uint16_t x,uint16_t y);
	LRD();
	uint16_t x,y;
	uint8_t n;
	unsigned int timerr;
	int start;
	void move(int d,uint8_t n);
	bool bar();
	void show();
	void clear();
	bool fly();
	void action();
} *lrd=0;
struct Controller {
	uint16_t x,y;
	uint8_t n;
	unsigned int timerr=0;
	void move();
	void show();
} *contr=0;

SDL_Texture *flr, *textures, *anim_tex, *gates_tex, *kvadrat=0, *controller_tex=0;
#ifdef ANDROID
SDL_Texture *sensor_tex;
#endif
Mix_Chunk *spike_open, *spike_close, *pulemet, *crossbow_fire, *crossbow_load, *button, *buttoff, *dopen, *dclose, *dkey, *boom, *moneta;
SDL_Surface *map=0;
vector<unsigned short>passwords;
FC_Font *def, *text, *menu, *bold;
SDL_Event e;
bool darkost=true;
#define timer ((int)SDL_GetTicks()-timer_pause)
float iface_zoom=1;
int SW=0;
int SH=0;
bool fullscreen=1;
extern SDL_Event e;
SDL_Window *win = 0;
SDL_Renderer *ren = 0;
const SDL_Color white= {255,255,255,255};
const SDL_Color black= {0,0,0,255};
const SDL_Color gray= {128,128,128,255};
const SDL_Color yellow= {255,255,0,255};
const SDL_Color green= {50,255,0,255};
const SDL_Color red= {255,176,50,255};
const SDL_Color blue= {0,0,255,255};
SDL_Texture * load(const char * way) {
	SDL_Surface *src=IMG_Load(way);
	SDL_Texture *tex=SDL_CreateTextureFromSurface(ren,src);
	SDL_FreeSurface(src);
	return tex;
}
bool init(const char * name) {
	SDL_Init(SDL_INIT_VIDEO);
#ifndef ANDROID
	if(SW==0)
#endif
	{
		SDL_DisplayMode c;
		SDL_GetCurrentDisplayMode(0, &c);
		SW=c.w;
#ifdef ANDROID
		SH=c.h;
#else
		SH=c.h-!fullscreen*25;
#endif
	}
#ifdef ANDROID
	win = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SW,SH, fullscreen?1:4);
#else
	win = SDL_CreateWindow(name, fullscreen?0:SDL_WINDOWPOS_UNDEFINED, fullscreen?0:SDL_WINDOWPOS_UNDEFINED, SW,SH, fullscreen?SDL_WINDOW_FULLSCREEN_DESKTOP:4);
#endif

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(ren,0,0,0,255);
	SDL_RenderClear(ren);
	TTF_Init();
	Mix_Init(MIX_INIT_MP3|MIX_INIT_MOD);
	Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
	textures		=load(string(global_data_dir+"textures/all.png").c_str());
	anim_tex		=load(string(global_data_dir+"textures/anim.png").c_str());
	flr				=load(string(global_data_dir+"textures/floor.png").c_str());
	controller_tex	=load(string(global_data_dir+"textures/controller.png").c_str());
	gg.load_texture();
#ifdef ANDROID
	sensor_tex=load(string(global_data_dir+"textures/sensor.png").c_str());
	iface_zoom=min(SH/400.0f,SW/550.0f);
#endif
	def =FC_CreateFont();
	text=FC_CreateFont();
	bold=FC_CreateFont();
	menu=FC_CreateFont();

	FC_LoadFont(def, ren,string(global_data_dir+"fonts/text.ttf").c_str(),iface_zoom*20,white,TTF_STYLE_NORMAL);
	FC_LoadFont(text,ren,string(global_data_dir+"fonts/text.ttf").c_str(),iface_zoom*20,white,TTF_STYLE_NORMAL);
	FC_LoadFont(bold,ren,string(global_data_dir+"fonts/text.ttf").c_str(),iface_zoom*20,white,TTF_STYLE_BOLD);
	FC_LoadFont(menu,ren,string(global_data_dir+"fonts/menu.ttf").c_str(),iface_zoom*30,white,TTF_STYLE_NORMAL);

	spike_open= Mix_LoadWAV         (string(global_data_dir+"sound/spikes/open.wav").c_str());
	spike_close=Mix_LoadWAV         (string(global_data_dir+"sound/spikes/close.wav").c_str());
	pulemet=Mix_LoadWAV             (string(global_data_dir+"sound/pulemet.wav").c_str());
	crossbow_fire=Mix_LoadWAV       (string(global_data_dir+"sound/crossbow/fire.wav").c_str());
	crossbow_load=Mix_LoadWAV       (string(global_data_dir+"sound/crossbow/load.wav").c_str());
	button=Mix_LoadWAV              (string(global_data_dir+"sound/button/on.wav").c_str());
	buttoff=Mix_LoadWAV             (string(global_data_dir+"sound/button/off.wav").c_str());
	dopen=Mix_LoadWAV               (string(global_data_dir+"sound/door/open.wav").c_str());
	dclose=Mix_LoadWAV              (string(global_data_dir+"sound/door/close.wav").c_str());
	dkey=Mix_LoadWAV                (string(global_data_dir+"sound/door/key.wav").c_str());
	boom=Mix_LoadWAV                (string(global_data_dir+"sound/boom.wav").c_str());
	moneta=Mix_LoadWAV              (string(global_data_dir+"sound/moneta.wav").c_str());
	create_kvadrat();
	return 0;
}
void quit(bool ex) {
	SDL_DestroyTexture(flr);
	SDL_DestroyTexture(textures);
	SDL_DestroyTexture(anim_tex);
	SDL_DestroyTexture(controller_tex);
	if(kvadrat) {
		SDL_DestroyTexture(kvadrat);
		kvadrat=0;
	}
	if(map)SDL_FreeSurface(map);
#ifdef ANDROID
	SDL_DestroyTexture(sensor_tex);
#endif
	Mix_FreeChunk(spike_open);
	Mix_FreeChunk(spike_close);
	Mix_FreeChunk(pulemet);
	Mix_FreeChunk(crossbow_fire);
	Mix_FreeChunk(crossbow_load);
	Mix_FreeChunk(button);
	Mix_FreeChunk(buttoff);
	Mix_FreeChunk(dopen);
	Mix_FreeChunk(dclose);
	Mix_FreeChunk(dkey);
	Mix_FreeChunk(boom);
	Mix_FreeChunk(moneta);
	FC_FreeFont(text);
	FC_FreeFont(menu);
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_StopTextInput();
	if(ex) {
		TTF_Quit();
		SDL_Quit();
		Mix_CloseAudio();
		Mix_Quit();
#ifdef STEAM
		SteamAPI_Shutdown();
#endif
		exit(1);
	}
}
SDL_Color color(uint8_t r,uint8_t g,uint8_t b) {
	SDL_Color c= {r,g,b,255};
	return c;
}
void showIMG(int x,int y,int w,int h,SDL_Texture * img,bool align=0) {
	SDL_Rect r = {x,y,w,h};
	if(align)r= {x-w/2,y-h/2,w,h};
	SDL_RenderCopy(ren, img, 0, &r);
}
void showIMG(SDL_Rect r,SDL_Texture* img,bool align=0) {
	showIMG(r.x,r.y,r.w,r.h,img,align);
}
void showIMG(int x,int y,int w,int h,SDL_Texture * img,SDL_Rect tex,bool align=0) {
	SDL_Rect r;
	if(align)r= {x-w/2,y-h/2,w,h};
	else r = {x,y,w,h};
	SDL_RenderCopy(ren, img, &tex, &r);
}
void showIMG(SDL_Rect r,SDL_Texture* img,SDL_Rect tex,bool align=0) {
	showIMG(r.x,r.y,r.w,r.h,img,tex,align);
}
bool in_rect(SDL_Rect r) {
	SDL_Rect v;
	SDL_RenderGetViewport(ren,&v);
	SDL_Rect h= {r.x+v.x,r.y+v.y,r.w,r.h};
	int mx,my;
	int zx,zy;
	SDL_GetMouseState(&mx,&my);
	SDL_GetWindowSize(win,&zx,&zy);
	mx=(float)mx/zx*SW;
	my=(float)my/zy*SH;
	if(mx>h.x && my>h.y && mx<h.x+h.w && my<h.y+h.h)return 1;
	else return 0;
}
void create_kvadrat() {
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, darkost?"1":"0");
	if(!darkost&&kvadrat) {
		SDL_DestroyTexture(kvadrat);
		kvadrat=0;
	} else if(darkost&&!kvadrat) {
		SDL_Surface *src=create_surface(4,4);
		SDL_Rect r= {1,1,2,2};
		SDL_FillRect(src,&r,0xFF000000);
		kvadrat=SDL_CreateTextureFromSurface(ren,src);
		SDL_SetTextureBlendMode(kvadrat,SDL_BLENDMODE_BLEND);
		SDL_FreeSurface(src);
	}
}

uint8_t w,h;
string lid;
uint8_t level[255][255];
uint8_t light[255][255];
const uint8_t* key=SDL_GetKeyboardState(0);
#ifdef ANDROID
float zoom=2;
uint8_t sensor=0;
#else
float zoom=1;
#endif
uint8_t ch_bl=1,ch_gt=0;
uint8_t mode=0;
int cx=0,cy=0;
int profn=0;
bool st=true;
bool drag=false;
int ltime;
int timer_sbt=0,    //subtitles
	timer_trap=0,   //hidden pits
	timer_bl=0,     //bullets
	timer_pm=0,     //guns
	timer_ar=0,     //crossbows
	timer_bomb=0,   //bombs
	timer_minimap=0,//level map
	timer_pause=0,  //timer for pause
	timer_dark=0;
const int delay=1000; //delay for subtitles
bool sb_on=1;
bool key_en=0;
int sound_vol=128,music_vol=128; //sound and music volume
bool tecno=false;
bool harpoon=true;
string txt=" ",buf=" ",qbuf=" ";     //current subtitles, subtitles buffer and questions buffer
string loc="en";                     //current locale (russian or english)
string strings[STRINGS_COUNT];   //strings for current locale
std::vector< std::string* > questions(0);
std::vector< std::string* > replies(0);
const std::vector<bool>block_config[6]= {
	//          0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255
	/*player*/ {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1},
	/*Rock  */ {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  1,  1},
	/*LRD   */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  0,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
	/*Bullet*/ {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  0,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0},
	/*Laser */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  1,  1,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0},
	/*Light */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
};
bool is_password_door(uint8_t x,uint8_t y) {
	if(level[x][y]==148||level[x][y]==149)return 1;
	if(level[x][y]>=170||level[x][y]<=174)return 1;
	return 0;
}
bool is_terminal(uint8_t x,uint8_t y) {
	if(level[x][y]==158)return 1;
	if(level[x][y]>=175||level[x][y]<=180)return 1;
	return 0;
}
bool is_password_door(uint8_t a) {
	if(a==148||a==149)return 1;
	if(a>=170||a<=174)return 1;
	return 0;
}
bool is_terminal(uint8_t a) {
	if(a==158)return 1;
	if(a>=175||a<=180)return 1;
	return 0;
}

bool floor_type() {
	for(int x=0; x<w; ++x) {
		for(int y=0; y<h; ++y) {
			if(level[x][y]>=140&&level[x][y]<=205)return 1;
		}
	}
	return 0;
}
void Laser::show() {
	SDL_SetRenderDrawColor(ren,255,0,0,255);
	bool vertical=(x1==x2);
	if(vertical) {
		for(int q=min(y1,y2); q<=max(y1,y2); ++q) {
			bool b1=(q==min(y1,y2));
			bool b2=(q==max(y1,y2));
			if(light[x1][q]) {
				SDL_Rect r= {cx+(x1*64+30)*zoom,cy+(q*64+b1*32)*zoom,4,(64-b2*32)*zoom};
				SDL_RenderFillRect(ren,&r);
			}
		}
	} else {
		for(int q=min(x1,x2); q<=max(x1,x2); ++q) {
			bool b1=(q==min(x1,x2));
			bool b2=(q==max(x1,x2));
			if(light[q][y1]) {
				SDL_Rect r= {cx+(q*64+b1*32)*zoom,cy+(y1*64+30)*zoom,(64-b2*32)*zoom,4};
				SDL_RenderFillRect(ren,&r);
			}
		}
	}
}
void Select::show() {
	short *x,*y;
	if(sx!=1000||sy!=1000) {
		x=&sx;
		y=&sy;
	} else if(x1!=0 || y1!=0 || x2!=w || y2!=h) {
		x=&x1;
		y=&y1;
	} else return;

	SDL_Rect r= {cx+(int)(*x*64*zoom),cy+(int)(*y*64*zoom),(int)((x2-x1)*64*zoom),(int)((y2-y1)*64*zoom)};
	SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(ren,0,100,255,50);
	SDL_RenderFillRect(ren,&r);
	SDL_SetRenderDrawColor(ren,0,0,0,255);
	SDL_RenderDrawRect(ren,&r);
	SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_NONE);
}
void minimap() {
	if(timer>timer_minimap+500) {
		timer_minimap=timer;
		uint8_t level2[255][255];
		memcpy(level2,level,sizeof(level));
		for(unsigned q=0; q<rock.size(); ++q)
			level2[(rock[q].x+32)/64][(rock[q].y+32)/64]=13;
		level2[(player->x+32)/64][(player->y+32)/64]=51;
		int c=get_level_c(w,h);
		for(int x=0; x<w; ++x) {
			for(int y=0; y<h; ++y) {
				SDL_Color k= {0,0,0,0};
				if(level2[x][y]==0
						|| !light[x][y]) k= {0,  0,  0,  255};
				else if(level2[x][y]==1) k= {128,128,128,255};
				else if(level2[x][y]<=9) k= {128,64, 32, 255};
				else if(level2[x][y]==10)k= {128,128,128,255};
				else if(level2[x][y]<=12)k= {180,0,  0,  255};
				else if(level2[x][y]==13)k= {64, 64, 64, 255};
				else if(level2[x][y]<=15)k= {255,0,  0,  255};
				else if(level2[x][y]<=21)k= {0,  0,  0,  255};
				else if(level2[x][y]<=25)k= {0,  0,  0,  255};
				else if(level2[x][y]<=27)k= {0,  255,0,  255};
				else if(level2[x][y]<=29)k= {128,64, 32, 255};
				else if(level2[x][y]<=35)k= {0,  0,  0,  255};
				else if(level2[x][y]<=39)k= {0,  0,  180,255};
				else if(level2[x][y]<=46)k= {128,128,128,255};
				else if(level2[x][y]<=50)k= {0,  0,  180,255};
				else if(level2[x][y]==51)k= {0,  255,255,255};
				else if(level2[x][y]==52)k= {0,  0,  0,  255};
				else if(level2[x][y]<=72)k= {0,  0,  180,255};
				else if(level2[x][y]<=74)k= {255,0,  0,  255};
				else if(level2[x][y]<=78)k= {255,255,0,  255};
				else if(level2[x][y]<=83)k= {0,  0,  0,  255};
				else if(level2[x][y]==84)k= {128,128,128,255};
				else if(level2[x][y]<=86)k= {0,  0,  0,  255};
				else if(level2[x][y]<=88)k= {0,  0,  180,255};
				SDL_Rect r= {c*x,c*y,c,c};
				SDL_FillRect(map,&r,SDL_MapRGB(map->format,k.r,k.g,k.b));
			}
		}
	}
	SDL_Texture *map_tex=SDL_CreateTextureFromSurface(ren,map);
	showIMG(SW-map->w,0,map->w,map->h,map_tex);
	SDL_DestroyTexture(map_tex);
}
void Gate::show() {
	SDL_Rect r= {64*(type%8), 64*(type/8), 64, 64};
	showIMG(cx+x*64*zoom,cy+y*64*zoom,64*zoom,64*zoom,gates_tex,r);
}
void Wire::show() {
	SDL_SetRenderDrawColor(ren,255,127,255,255);
	SDL_RenderDrawLine(ren,
					   (x1*64+32)*zoom+cx,
					   (y1*64+32)*zoom+cy,
					   (x2*64+32)*zoom+cx,
					   (y2*64+32)*zoom+cy);
}
void LRD::show() {
	SDL_Rect r= {
		64+(timer%90/30)*64+(n%2)*256,
		448+(n/2)*64,
		64,
		64
	};
	int h=0;
	if(start>0) {
		h=min(500,timer-start)/40;
	} else {
		h=12-min(500,timer+start)/40;
	}
	showIMG(cx+x*zoom,cy+y*zoom-h,64*zoom,64*zoom,anim_tex,r);
}
void Rock::show() {
	if((x+64)*zoom<-cx)return;
	if((y+64)*zoom<-cy)return;
	if(x*zoom>SW-cx)return;
	if(y*zoom>SH-cy)return;
	if(!light[(x+32)/64][(y+32)/64])return;
	if(!tm && type==0) {
		SDL_Rect r= {768,0,64,64};
		showIMG(x*zoom+cx,y*zoom+cy,64*zoom,64*zoom,textures,r);
	} else if(type>1) {
		SDL_Rect r= {((type-2)%9-1)*64,192+(type-2)/9*64,64,64};
		if(r.x<0)r.x=0;
		showIMG(x*zoom+cx,y*zoom+cy,64*zoom,64*zoom,anim_tex,r);
	} else {
		int alpha=max(min(255-(int)(timer-tm-2800)/10,255),0);
		SDL_SetTextureAlphaMod(anim_tex,alpha);
		if(alpha<50)type=1;
		int a=min((int)(timer-tm)/100,23);
		SDL_Rect r= {a%8*64,a/8*64,64,64};
		showIMG(x*zoom+cx,y*zoom+cy,64*zoom,64*zoom,anim_tex,r);
	}
	SDL_SetTextureAlphaMod(anim_tex,255);
}
void Player::show() {
	if(dietimer==0 || (dietimer<0 && (timer+dietimer)%200/100)) {
		int c=0;
		switch(n) {
		case 0:
			c=(short)y%64/16;
			break;
		case 1:
			c=(short)x%64/16;
			break;
		case 2:
			c=(short)y%64/16;
			break;
		case 3:
			c=(short)x%64/16;
			break;
		}
		if(bring && n%2==1) {
			SDL_Rect r;
			switch(bring) {
			case 1:
				r= {920,278,20,20};
				break;
			case 2:
				r= {342,330,20,35};
				break;
			case 3:
				r= {787,802,27,25};
				break;
			}
			int xp=0,yp=0;
			if(n==1 && bring==1)xp=44,yp=27;
			else if(n==3 && bring==1)xp=0,yp=27;
			else if(n==1 && bring==2)xp=44,yp=14;
			else if(n==3 && bring==2)xp=0,yp=14;
			else if(n==1 && bring==3)xp=39,yp=25;
			else if(n==3 && bring==3)xp=0,yp=25;
			showIMG((x+xp)*zoom+cx,(y+yp)*zoom+cy,r.w*zoom,r.h*zoom,textures,r);
		}
		SDL_Rect r= {c*64+256*(push || bring),n*64,64,64};
		if(push && n%2==0)move(5,n);
		if(push && n%2==1)move(15,n);
		showIMG(x*zoom+cx,y*zoom+cy,64*zoom,64*zoom,texture,r);
		if(push && n%2==0)move(-5,n);
		if(push && n%2==1)move(-15,n);
		if(bring && n==2) {
			SDL_Rect r;
			int xp,yp;
			switch(bring) {
			case 1:
				r= {920,278,20,20};
				xp=23;
				yp=35;
				break;
			case 2:
				r= {342,330,20,36};
				xp=23;
				yp=22;
				break;
			case 3:
				r= {787,802,27,25};
				xp=20;
				yp=25;
				break;
			}
			showIMG((x+xp)*zoom+cx,(y+yp)*zoom+cy,r.w*zoom,r.h*zoom,textures,r);
		}
	} else if(dietimer>0) {
		int player_anim=min((int)(timer-dietimer)/50,19)+n*20;
		SDL_Rect r= {(player_anim%8)*64,(player_anim/8)*64+256,64,64};
		showIMG(x*zoom+cx,y*zoom+cy,64*zoom,64*zoom,texture,r);
	}
}
void Bullet::show() {
	if((x+64)*zoom<-cx)return;
	if((y+64)*zoom<-cy)return;
	if(x*zoom>SW-cx)return;
	if(y*zoom>SH-cy)return;
	if(!light[(x+32)/64][(y+32)/64])return;
	if(type==0) {
		SDL_SetRenderDrawColor(ren,255,128,39,255);
		if(n==0 || n==2)SDL_RenderDrawLine(ren,(x+32)*zoom+cx,(y+11)*zoom+cy,(x+32)*zoom+cx,(y+55)*zoom+cy);
		else SDL_RenderDrawLine(ren,(x+11)*zoom+cx,(y+32)*zoom+cy,(x+55)*zoom+cx,(y+32)*zoom+cy);
	} else if(type==1) {
		SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_Rect r;
		if(n==0 || n==2)r= {int((x+31)*zoom+cx),int((y+28)*zoom+cy),int(3*zoom),int(8*zoom)};
		else r= {int((x+28)*zoom+cx),int((y+31)*zoom+cy),int(8*zoom),int(3*zoom)};
		SDL_RenderFillRect(ren,&r);
	} else if(type==2) {
		SDL_Rect r= {920,278,20,20};
		showIMG((x+22)*zoom+cx,(y+22)*zoom+cy,20*zoom,20*zoom,textures,r);
	}
}
void draw(bool player_sh,bool wires,bool hints) {
	{
		SDL_Rect rect = {tecno*64,0,64,64};
		for(int y=-cy/(64*zoom)-1; y<(-cy+SH)/(64*zoom)+2; ++y) {
			for(int x=-cx/(64*zoom)-1; x<(-cx+SW)/(64*zoom)+2; ++x) {
				bool ok=light[x][y];
				if(darkost && !ok){
						if(y>0		&&light[x][y-1])ok=1;
						if(x>0		&&light[x-1][y])ok=1;
						if(y<h-1	&&light[x][y+1])ok=1;
						if(x<w-1	&&light[x+1][y])ok=1;
				}
				if(x>=0 && y>=0 && x<w && y<h && ok)
					showIMG(cx+x*(zoom*64),cy+y*(zoom*64),(zoom*64),(zoom*64),flr,rect);
			}
		}
	}
	for(int q=0; q<(int)laser.size(); ++q)laser[q].show();
	for(int y=-cy/(64*zoom)-1; y<(-cy+SH)/(64*zoom)+2; ++y) {
		for(int x=-cx/(64*zoom)-1; x<(-cx+SW)/(64*zoom)+2; ++x) {
			bool ok=light[x][y];
			if(darkost && !ok){
					if(y>0		&&light[x][y-1])ok=1;
					if(x>0		&&light[x-1][y])ok=1;
					if(y<h-1	&&light[x][y+1])ok=1;
					if(x<w-1	&&light[x+1][y])ok=1;
			}
			if(x>=0 && y>=0 && x<w && y<h && level[x][y] && ok && (level[x][y]<75 || (level[x][y]>78 && level[x][y]<96) || level[x][y]>107)) {
				uint8_t j=(level[x][y])-1+(level[x][y]==52 && hints)+(level[x][y]==227 && hints)*5;
				SDL_Rect r= {64*(j%16), 64*(j/16), 64, 64};
				if((level[x][y]==10 || level[x][y]==52 || level[x][y]==181 || level[x][y]==227) && hints)SDL_SetTextureAlphaMod(textures,150);
				showIMG(cx+x*(zoom*64),cy+y*(zoom*64),(zoom*64),(zoom*64),textures,r);
				if((level[x][y]==10 || level[x][y]==52 || level[x][y]==181 || level[x][y]==227) && hints)SDL_SetTextureAlphaMod(textures,255);
				if(level[x][y]>=30 && level[x][y]<=35 && hints) {
					SDL_SetRenderDrawColor(ren,255,0,0,255);
					SDL_Rect r= {cx+(int)((x*64+10)*zoom),cy+(int)((y*64+10)*zoom),(int)(44*zoom),(int)(44*zoom)};
					SDL_RenderDrawRect(ren,&r);
				}
				if(level[x][y]==224) {
					bool s[4]= {0,0,0,0};
					if(y>0		&&level[x][y-1]==225)s[0]=1;
					if(x>0		&&level[x-1][y]==226)s[1]=1;
					if(y<h-1	&&level[x][y+1]==225)s[2]=1;
					if(x<w-1	&&level[x+1][y]==226)s[3]=1;
					for(int q=0; q<4; q++) {
						if(s[q]) {
							SDL_Rect r= {256+q*64, 576, 64, 64};
							showIMG(cx+x*(zoom*64),cy+y*(zoom*64),(zoom*64),(zoom*64),anim_tex,r);
						}
					}
				}
			}
		}
	}
	for(int q=0; q<(int)bullet.size(); ++q)bullet[q].show();
	if(lrd)lrd->show();
	if(contr)contr->show();
	if(player_sh){
		player->show();
		if(player!=&gg)gg.show();
	}
	for(int y=-cy/(64*zoom)-1; y<(-cy+SH)/(64*zoom)+2; ++y) {
		for(int x=-cx/(64*zoom)-1; x<(-cx+SW)/(64*zoom)+2; ++x) {
			if(x>=0 && y>=0 && x<w && y<h && light[x][y] && ((level[x][y]>=75 && level[x][y]<=78) || (level[x][y]>=96 && level[x][y]<=107))) {
				SDL_Rect r= {64*((level[x][y]-1)%16), 64*((level[x][y]-1)/16), 64, 64};
				showIMG(cx+x*(zoom*64),cy+y*(zoom*64),(zoom*64),(zoom*64),textures,r);
			}
		}
	}
	for(int q=0; q<(int)rock.size(); ++q)rock[q].show();
	if(darkost) {
		for(int y=-cy/(64*zoom)-3; y<(-cy+SH)/(64*zoom)+6; ++y) {
			for(int x=-cx/(64*zoom)-3; x<(-cx+SW)/(64*zoom)+6; ++x) {
				if(x<0 || y<0 || x>=w || y>=h){
					SDL_SetTextureAlphaMod(kvadrat,255);
					showIMG(cx+zoom*64*(x-1.5),cy+zoom*64*(y-1.5),zoom*256,zoom*256,kvadrat);
				}else if(light[x][y]!=255){
					SDL_SetTextureAlphaMod(kvadrat,(255-light[x][y]));
					showIMG(cx+zoom*64*(x-1.5),cy+zoom*64*(y-1.5),zoom*256,zoom*256,kvadrat);
				}
			}
		}
	}
	if(wires) {
		for(int q=0; q<(int)gate.size(); ++q)gate[q].show();
		for(int q=0; q<(int)wire.size(); ++q)wire[q].show();
	}
	if(hints) {
		for(uint8_t xp=0; xp<w; xp++) {
			for(uint8_t yp=0; yp<h; yp++) {
				if((level[xp][yp]>=36 && level[xp][yp]<=39) || (level[xp][yp]>=47 && level[xp][yp]<=50)) {
					uint8_t xc=xp,yc=yp;
					int n=level[xp][yp]-((level[xp][yp]>=36 && level[xp][yp]<=39)?36:47);
					while(1) {
						yc-=(n==0);
						yc+=(n==2);
						xc+=(n==1);
						xc-=(n==3);
						if(block_config[3][level[xc][yc]])break;
					}
					SDL_SetRenderDrawColor(ren,255,255,0,255);
					SDL_RenderDrawLine(ren,(xc*64+32)*zoom+cx,(yc*64+32)*zoom+cy,(xp*64+32)*zoom+cx,(yp*64+32)*zoom+cy);
				}
			}
		}
	}
}
#ifdef ANDROID
void sensor_draw() {
	sensor=0;
	int j350=iface_zoom*245;
	int j300=iface_zoom*210;
	int j250=iface_zoom*175;
	int j200=iface_zoom*140;
	int j150=iface_zoom*105;
	int j100=iface_zoom*70;
	int j50=iface_zoom*35;
	SDL_Rect b[]= {
		{j50,int(50*iface_zoom),j100,j100},
		{j150,SH-j250,j100,j100},
		{j250,SH-j150,j100,j100},
		{j150,SH-j150,j100,j100},
		{j50, SH-j150,j100,j100},
		{SW-j150,SH-j150,j100,j100},
		{SW-j150,SH-j250,j100,j100},
		{SW-j150,SH-j350,j100,j100}
	};
	for(int q=0; q<6+(!st||lidtoln(lid)>=33)*2; ++q) {
		SDL_Rect r= {q%4*50,q/4*50,50,50};
		showIMG(b[q],sensor_tex,r);
		if((e.type==SDL_FINGERDOWN || e.type==SDL_FINGERMOTION) && in_rect(b[q]))sensor=q+1;
	}
}
#endif
int Player::bar(bool fat,uint8_t n,bool pit) {
	uint8_t level2[255][255];
	memcpy(level2, level, sizeof(level2));
	if(!fat&&pit) {
		int xp=(x+32)/64;
		int yp=(y+32)/64;
		if(level[xp][yp]==52 ||
				level[xp][yp]==53 ||
				(level[xp][yp]>=91 && level[xp][yp]<=94)
			|| (level[xp][yp]>=227 && level[xp][yp]<=232)) {
			level2[xp-1][yp]=1;
			level2[xp+1][yp]=1;
			level2[xp][yp-1]=1;
			level2[xp][yp+1]=1;
		}
	}
	level2[(gg.x+32)/64][(gg.y+32)/64]=1;
	if(block_config[fat][level2[(short)x/64-(n==3)+(n==1)][(short)y/64-(n==0)+(n==2)]])return 1;
	for(unsigned q=0; q<rock.size(); ++q) {
		if(rock[q].x/64==x/64-(n==3)+(n==1)
				&& rock[q].y/64==y/64-(n==0)+(n==2) && rock[q].type!=1)return 2;
	}
	return 0;
}
uint8_t Player::block() {
	uint8_t block=0;
	switch(n) {
	case 0:
		block=level[(short)x/64][((short)y-1)/64];
		break;
	case 1:
		block=level[(short)x/64+1][(short)y/64];
		break;
	case 2:
		block=level[(short)x/64][(short)y/64+1];
		break;
	case 3:
		block=level[((short)x-1)/64][(short)y/64];
		break;
	}
	return block;
}
void Player::replace(uint8_t a) {
	switch(n) {
	case 0:
		level[(short)x/64][((short)y-1)/64]=a;
		break;
	case 1:
		level[(short)x/64+1][(short)y/64]=a;
		break;
	case 2:
		level[(short)x/64][(short)y/64+1]=a;
		break;
	case 3:
		level[((short)x-1)/64][(short)y/64]=a;
		break;
	}
}
void Player::move(int8_t c,uint8_t n) {
	switch(n) {
	case 0:
		y-=c;
		break;
	case 1:
		x+=c;
		break;
	case 2:
		y+=c;
		break;
	case 3:
		x-=c;
		break;
	}
}
bool Player::can_go(bool *ps,uint8_t n,bool pit) {
	uint8_t i=4;
	bool ok=0;
	for(int q=0; q<(int)rock.size(); ++q) {
		switch(n) {
		case 0:
			if(y-rock[q].y<=80 && y-rock[q].y>0 && rock[q].x==x && rock[q].type!=1)i=0;
			break;
		case 1:
			if(rock[q].x-x<=80 && rock[q].x-x>0 && rock[q].y==y && rock[q].type!=1)i=1;
			break;
		case 2:
			if(rock[q].y-y<=80 && rock[q].y-y>0 && rock[q].x==x && rock[q].type!=1)i=2;
			break;
		case 3:
			if(x-rock[q].x<=80 && x-rock[q].x>0 && rock[q].y==y && rock[q].type!=1)i=3;
			break;
		}
	}
	*ps=0;
	if(noclip || bar(0,n,pit)!=1) {
		if(i==n) {
			if(!bring) {
				*ps=1;
				move(64,n);
				if(noclip || !(bar(1,n,pit)))ok=1;
				move(-64,n);
			}
		} else ok=1;
	}
	return ok;
}
void Player::kill() {
	if(!infhealth && !dietimer && lives) {
		lives--;
		if(!lives) {
			dietimer=timer;
			if(!bar(1,n,1)) {
				switch(n) {
				case 1:
					x+=12;
					break;
				case 3:
					x-=12;
					break;
				}
			}
		} else dietimer=(-(int)(timer))-2000;
	}
}
void Player::clear() {
	for(float a=0; a<M_PI*2; a+=0.005) {
		float xp=x,yp=y;
		while(1) {
			float d=sqrt(pow(x-xp,2)+pow(y-yp,2))/64.0f;
			xp+=cos(a)*20;
			yp+=sin(a)*20;
			if(d>4)break;
			light[(int)(xp+32)/64][(int)(yp+32)/64]=255;
			if(block_config[5][level[(int)(xp+32)/64][(int)(yp+32)/64]])break;
		}
	}
	if(timer>timer_dark+25) {
		timer_dark=timer;
		for(int xp=0; xp<w; xp++) {
			for(int yp=0; yp<h; yp++) {
				if(light[xp][yp]){
                        if(light[xp][yp]>180)light[xp][yp]--;
				}
			}
		}
	}
}
//*******   SCROLLBAR   ********//
void Scrollbar::set(int xp,int yp,int hp) {
	x=xp*iface_zoom;
	y=yp*iface_zoom;
	h=hp*iface_zoom;
	p=0;
}
int Scrollbar::update(bool u) {
	SDL_Rect r= {x,y,int(20.0f*iface_zoom),h};
	if(u) {
		if(e.type==SDL_MOUSEWHEEL) {
			if(e.wheel.y>0)p-=10;
			if(e.wheel.y<0)p+=10;
		}
		if(mouse.state && in_rect(r))motion=1;
		if(!mouse.state)motion=0;
		if(motion)p=mouse.y-25;
		if(p<30*iface_zoom)p=30*iface_zoom;
		if(p>h-20*iface_zoom)p=h-20*iface_zoom;
	}
	SDL_Rect v= {int(x+3*iface_zoom),int(p+5*iface_zoom),int(14*iface_zoom),int(40*iface_zoom)};
	SDL_RenderDrawRect(ren,&v);
	return (p-30.0f*iface_zoom)/(h-50*iface_zoom)*100;
}
int Scrollbar::getp() {
	return (p-30.0f*iface_zoom)/(h-50*iface_zoom)*100;
}
inline float get_zoom() {
#ifdef ANDROID
	return 2;
#else
	return 1;
#endif
}
//*******   MOUSE SELECT   *******//
void Select::select() {
	mouse.update();
#ifdef ANDROID
	if(mouse.state && mouse.touch==1)
#else
	if(mouse.state && mouse.b==SDL_BUTTON_LEFT)
#endif
	{
		x2=test(((mouse.x-cx)/zoom+32)/64.0f,w+1);
		y2=test(((mouse.y-cy)/zoom+32)/64.0f,h+1);
		if(!drag) {
			x1=x2;
			y1=y2;
			drag=1;
		}
	} else {
		drag=0;
		if(x1==x2 || y1==y2 || x2>w || y2>h) {
			x1=0;
			y1=0;
			x2=w;
			y2=h;
		}
		if(x1>x2)swap(x1,x2);
		if(y1>y2)swap(y1,y2);
	}
}
//*******   GET MINIMAP CELL SIZE   *******//
int get_level_c(int w,int h) {
	int c=20;
	if(h>10 || w>10)c=15;
	if(h>13 || w>13)c=10;
	if(h>20 || w>20)c=8;
	if(h>25 || w>25)c=6;
	if(h>33 || w>33)c=5;
	if(h>40 || w>40)c=4;
	if(h>50 || w>50)c=3;
	if(h>66 || w>66)c=2;
	if(h>100 || w>100)c=1;
	return c;
}
//*******   LEVEL EDITOR HISTORY   *******//
History::History() {
	save();
}
void History::save() {
	wl=w;
	hl=h;
	for(int x=0; x<w; ++x) {
		for(int y=0; y<h; ++y) {
			l[x][y]=level[x][y];
		}
	}
	wir.resize(0);
	gat.resize(0);
	for(unsigned q=0; q<wire.size(); ++q)wir.push_back(wire[q]);
	for(unsigned q=0; q<gate.size(); ++q)gat.push_back(gate[q]);
	tecno=floor_type();
}
void History::load() {
	w=wl;
	h=hl;
	for(int x=0; x<wl; ++x) {
		for(int y=0; y<hl; ++y) {
			level[x][y]=l[x][y];
		}
	}
	wire.resize(0);
	gate.resize(0);
	for(unsigned q=0; q<wir.size(); ++q)wire.push_back(wir[q]);
	for(unsigned q=0; q<gat.size(); ++q)gate.push_back(gat[q]);
	tecno=floor_type();
}
bool in_range(int x1,int x2,int x3) {
	if(x3>x2 && x2>x1)return 1;
	if(x1>x2 && x2>x3)return 1;
	return 0;
}
bool in_rect(int x,int y,int w,int h,int x1,int y1) {
	if(x1>=x&&y1>=y&&y1<y+h&&x1<x+w)return 1;
	return 0;
}
bool p(int x1, int y1, int x2, int y2) {
	if(abs(x1-x2)<40 && abs(y1-y2)<40)return 1;
	return 0;
}
bool l(int x1, int y1, int x2, int y2) {
	if(abs(x1-x2)<64 && abs(y1-y2)<64)return 1;
	return 0;
}
bool Mouse::update() {
	int mx,my;
	SDL_Rect r;
	SDL_RenderGetViewport(ren,&r);
	mx=e.button.x-r.x;
	my=e.button.y-r.y;
	if(touch==2)touch=0;
	if(e.type==SDL_MOUSEBUTTONDOWN) {
		state=1;
		b=e.button.button;
		sx=x=mx;
		sy=y=my;
		touch=0;
		time=SDL_GetTicks();
	} else if(e.type==SDL_MOUSEMOTION) {
		if(state==1) {
			x=mx;
			y=my;
			if(timestamp()>300)touch=3;
			else {
				touch=1;
				time=0;
			}
		} else {
			time=0;
			touch=0;
		}
	} else if(e.type==SDL_MOUSEBUTTONUP) {
		state=0;
		if(!touch) {
			if(timestamp()>300)touch=3;
			else touch=2;
		}
	}
	return 0;
}
inline int Mouse::dx() {
	return x-sx;
}
inline int Mouse::dy() {
	return y-sy;
}
int Mouse::timestamp() {
	if(time==0)return 0;
	return max(0,(int)SDL_GetTicks()-time);
}
void Mouse::wait() {
	while(state) {
		SDL_WaitEvent(&e);
		update();
	}
	mouse.touch=1;
}
int test(int n,int m) {
	if(n>=0 && n<m)return n;
	return 0;
}
SDL_Surface *create_surface(int width,int height) {
	SDL_Surface *surface;
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	surface = SDL_CreateRGBSurface(0, width, height, 32,
								   rmask, gmask, bmask, amask);
	return surface;
}
void Profile::clear(uint8_t n) {
	level=0;
	name=string("Player-0"+to_string(n+1));


}
void Profile::new_game() {
	level=0;


}

bool Back() {
	if(key[SDL_SCANCODE_AC_BACK] || key[SDL_SCANCODE_ESCAPE]) {
		while(key[SDL_SCANCODE_AC_BACK] || key[SDL_SCANCODE_ESCAPE])SDL_PollEvent(&e);
		return 1;
	}
	return 0;
}

void Rock::kill(){
	if(!tm) {
		tm=timer;
	}
}
int Rock::update() {
	if(type!=1) {
		bool ok=1;
		if(player->n==1 && player->x+64>x && player->x<x && player->y==y)x=player->x+64;
		else if(player->n==2 && player->y+64>y && player->y<y && player->x==x)y=player->y+64;
		else if(player->n==3 && player->x<x+64 && player->x>x && player->y==y)x=player->x-64;
		else if(player->n==0 && player->y<y+64 && player->y>y && player->x==x)y=player->y-64;
		else ok=0;
		if(ok ) {
			for(unsigned w=0; w<rock.size(); ++w) {
				if(player->n==1 && x+64>rock[w].x && x<rock[w].x && player->y==rock[w].y)rock[w].x=x+64;
				if(player->n==2 && y+64>rock[w].y && y<rock[w].y && player->x==rock[w].x)rock[w].y=y+64;
				if(player->n==3 && x<rock[w].x+64 && x>rock[w].x && player->y==rock[w].y)rock[w].x=x-64;
				if(player->n==0 && y<rock[w].y+64 && y>rock[w].y && player->x==rock[w].x)rock[w].y=y-64;
			}
		}
		if(type==0) {
			unsigned short xp=(x+32)/64;
			unsigned short yp=(y+32)/64;
			if(level[xp][yp]==52)level[xp][yp]=91;
			if(level[xp][yp]==227)level[xp][yp]=228;
			if(x%64==0 && y%64==0){
				if(level[xp][yp]==53){
					if(!tm)
						level[xp][yp]=95;
					return 1;
				}else if(level[xp][yp]==232)
					kill();
			}
		} else if(type>1 && type%9!=2 && type%9!=3) {
			if(timer-tm>50) {
				tm=timer;
				if(type%9==1)type-=8;
				else type++;
				if(type%9==7) {
					bullet.push_back({x,y,uint8_t(type/9),(uint8_t)2});
					Mix_VolumeChunk(boom,sound_vol);
					Mix_PlayChannel(-1,boom,0);
				}
			}
		}
	}
	return 0;
}
Bullet::Bullet(int xp,int yp,int np,int tp) {
	x=xp;
	y=yp;
	n=np;
	type=tp;
}
Bullet::Bullet(unsigned short xp,unsigned short yp,uint8_t np,uint8_t tp) {
	x=xp;
	y=yp;
	n=np;
	type=tp;
}
void Controller::move() {
	if(timer>timerr+25) {
		x+=((n==1)-(n==3));
		y+=((n==2)-(n==0));
		timerr=timer;
	}
}
void Controller::show() {
	SDL_Rect r= {(timer%420/140)*64,n*64,64,64};
	showIMG(cx+zoom*x,cy+zoom*y,64*zoom,64*zoom,controller_tex,r);
}
bool game_end(bool boss) {
	if(st) {

		if(boss)profile.level=max(76,(int)profile.level);
		else profile.level=max(lidtoln(lid)+1,(int)profile.level);

		//if(*tm==0 || *tm>(timer-ltime)/100)*tm=(timer-ltime)/100;
		profile.save(profn);
	}
	if(end(boss,0,st))return 1;
	return 0;
}
void controller_update() {
	if(!contr)return;
	if(!(contr->x%64)&&!(contr->y%64)) {
		int x=contr->x/64;
		int y=contr->y/64;
		level[x][y]=220+(contr->n+2)%4;
		switch(contr->n) {
		case 0:
			y++;
			break;
		case 1:
			x--;
			break;
		case 2:
			y--;
			break;
		case 3:
			x++;
			break;
		}
		level[x][y]=0;
		delete contr;
		contr=0;
		return;
	}
	contr->move();
}
bool Player::update() {
	bool trap_en=0,ar_en=0,pm_en=0;
	int all_pm=0;
	if(timer>timer_trap+30) {
		trap_en=1;
		timer_trap=timer;
	}
	if(timer>timer_ar+100) {
		timer_ar=timer;
		ar_en=1;
	}
	if(timer>timer_pm+50) {
		timer_pm=timer;
		pm_en=1;
	}
	for(int xp=0; xp<w; ++xp) {
		for(int y=0; y<h; ++y) {
			if(pm_en&&(level[xp][y]==225 || level[xp][y]==226)) {
				level[xp][y]=0;
			}
		}
	}
	for(int xp=0; xp<w; ++xp) {
		for(int yp=0; yp<h; ++yp) {
			if(pm_en) {
				for(uint32_t q=0; q<rock.size(); ++q) {
					if(level[xp][yp]==12 && p(xp*64,yp*64,rock[q].x,rock[q].y))
						rock[q].kill();
				}
				if(level[xp][yp]>=128&&level[xp][yp]<=139) {
					float metres=sqrt(pow(x/64.0-xp,2)+pow(y/64.0-yp,2));
					float volume=max(10-metres,0.0f)/20.0*(MIX_MAX_VOLUME);
					bullet.push_back({xp*64,yp*64,(level[xp][yp]-128)/3,1});
					all_pm+=volume;
					if((level[xp][yp]-128)%3==2)
						level[xp][yp]-=2;
					else level[xp][yp]++;
				} else {
					switch(level[xp][yp]) {
					case 175:
					case 176:
					case 177:
					case 178:
					case 208:
					case 209:
						++level[xp][yp];
						break;
					case 179:
						level[xp][yp]=175;
						break;
					case 224:
						for(int xj=xp+1; xj<w; xj++) {
							bool ok=0;
							for(int q=0; q<gate.size(); q++) {
								if(gate[q].x==xj&&gate[q].y==yp&&gate[q].type==41&&gate[q].active==1) {
									ok=1;
									break;
								}
							}
							if(ok)break;
							if(level[xj][yp]==224) {
								for(int q=xp+1; q<xj; q++)
									level[q][yp]=226;
								break;
							} else if(level[xj][yp]!=0)break;
						}
						for(int yj=yp+1; yj<h; yj++) {
							bool ok=0;
							for(int q=0; q<gate.size(); q++) {
								if(gate[q].x==xp&&gate[q].y==yj&&gate[q].type==41&&gate[q].active==1) {
									ok=1;
									break;
								}
							}
							if(ok)break;
							if(level[xp][yj]==224) {
								for(int q=yp+1; q<yj; q++)
									level[xp][q]=225;
								break;
							} else if(level[xp][yj]!=0)break;
						}
						break;
					}
				}
			}
			if(trap_en) {
				switch(level[xp][yp]) {
				case 165:
				case 166:
				case 167:
				case 168:
				case 170:
				case 171:
				case 172:
				case 173:
					++level[xp][yp];
					break;
				case 169:
					level[xp][yp] = 147;
					break;
				case 174:
					level[xp][yp] = 149;
					break;
				}
			}
		}
	}
	if(player!=&gg && player->x%64==0 && player->y%64==0){
		if(level[player->x/64][player->y/64]==53){
			level[player->x/64][player->y/64]=233;
			delete player;
			player=&gg;
		}else if(level[player->x/64][player->y/64]==232){
			delete player;
			player=&gg;
		}
	}
	int j=3;
	for(int xp=max(0,x/64-j); xp<min((int)w,x/64+j); ++xp) {
		for(int yp=max(0,y/64-j); yp<min((int)h,y/64+j); ++yp) {
			if((x+32)/64==xp||(y+32)/64==yp) {
				bool pb=p(xp*64,yp*64,x,y);
				bool valun=0;
				for(uint32_t q=0; q<rock.size(); ++q) {
					if(p(xp*64,yp*64,rock[q].x,rock[q].y) && !rock[q].tm)valun=1;
				}
				switch(level[xp][yp]) {
				case 14:
					if(this==player && (pb || valun || p(xp*64,yp*64,player->x,player->y))) {
						level[xp][yp]=15;
						Mix_VolumeChunk(button,sound_vol);
						Mix_PlayChannel(-1,button,0);
					}
					break;
				case 15:
					if(this==player && !(pb || valun || p(xp*64,yp*64,player->x,player->y))) {
						level[xp][yp]=14;
						Mix_VolumeChunk(buttoff,sound_vol);
						Mix_PlayChannel(-1,buttoff,0);
					}
					break;
				case 8:
					if(pb) {
						level[xp][yp]=9;
						Mix_VolumeChunk(dopen,sound_vol);
						Mix_PlayChannel(-1,dopen,0);
					}
					break;
				case 9:
					if(!pb) {
						level[xp][yp]=8;
						Mix_VolumeChunk(dclose,sound_vol);
						Mix_PlayChannel(-1,dclose,0);
					}
					break;
				case 12:
					if(pb)
						kill();
					break;
				case 26:
					if(pb)
						if(game_end(0))return 1;
					break;
				case 52:
					if(trap_en && pb)
						level[xp][yp]=91;
					break;
				case 91:
				case 92:
				case 93:
				case 228:
				case 229:
				case 230:
				case 231:
					if(trap_en) level[xp][yp]++;
				case 232:
					if(pb && x%64==0 && y%64==0)
						kill();
					break;
					break;
				case 94:
					if(trap_en) level[xp][yp]=53;
					break;
				case 210:
					if(pb) {
						if(game_end(1))return 1;
					}
				case 227:
					if(trap_en && pb)
						level[xp][yp]=228;
					break;
				}
				if(pb) {
					bool valun=1;
					switch(level[xp][yp]) {
					case 16:
					case 17:
					case 18:
					case 19:
					case 20:
					case 21:
						door_key[level[xp][yp]-16]++;
						break;
					case 30:
					case 31:
					case 32:
					case 33:
					case 34:
					case 35:
						door_key[level[xp][yp]-24]++;
						break;
					case 150:
					case 151:
					case 152:
					case 153:
					case 154:
					case 155:
						door_key[level[xp][yp]-138]++;
						break;
					default:
						valun=0;
					}
					if(valun) {
						Mix_VolumeChunk(moneta,sound_vol);
						Mix_PlayChannel(-1,moneta,0);
						level[xp][yp]=0;
					}
				}
			}
		}
	}
	{
		uint8_t b=block();
		for(int q=0; q<6; ++q) {
			if(door_key[q] && b==2+q) {
				replace(8);
				Mix_VolumeChunk(dkey,sound_vol);
				Mix_PlayChannel(-1,dkey,0);
			}
			if(door_key[q+12] && b==141+q) {
				replace(165);
				Mix_VolumeChunk(dkey,sound_vol);
				Mix_PlayChannel(-1,dkey,0);
			}
		}
		if(b==10) {
			replace(8);
		}
	}
	gates();
	rocks();
	bullets();
	bombs();
	lasers();
	controller_update();
	int all_open=0;
	int all_close=0;
	int all_load=0;
	int all_fire=0;
	int alldopen=0;
	int alldclose=0;
	for(int q=0; q<(int)wire.size(); ++q) {

		uint8_t vx=wire[q].x1;
		uint8_t vy=wire[q].y1;
		uint8_t ux=wire[q].x2;
		uint8_t uy=wire[q].y2;

		bool ve=(x%64==0 && y%64==0 && x/64==vx && y/64==vy);

		auto enable=[&](bool en) {
			wire[q].active=en;
		};
		auto teleport=[=]() {
			if(wire[q].active) {
				x=ux*64;
				y=uy*64;
				sx=ux;
				sy=uy;
				if(!bar(0,n,1)) {
					timerr=timer;
					move(1,n);
				}
			}
		};

		float metres=sqrt(pow(x/64.0-wire[q].x2,2)+pow(y/64.0-wire[q].y2,2));
		float volume=max(10-metres,0.0f)/20.0*(MIX_MAX_VOLUME);

		switch(level[vx][vy]) {
		case 15:
		case 90:
		case 72:
		case 74:
		case 175:
		case 204:
			enable(1);
			break;
		case 14:
		case 71:
		case 73:
		case 158:
		case 203:
			enable(0);
			break;
		case 75:
		case 76:
		case 77:
		case 78:
			level[vx][vy]=(timer%400/100)+75;
			enable(ve);
			break;
		case 96:
		case 97:
		case 98:
		case 99:
			level[vx][vy]=(timer%400/100)+96;
			enable(ve);
			break;
		case 100:
		case 101:
		case 102:
		case 103:
			level[vx][vy]=(timer%400/100)+100;
			enable(ve);
			break;
		case 104:
		case 105:
		case 106:
		case 107:
			level[vx][vy]=(timer%400/100)+104;
			enable(ve);
			break;
		}
		switch(level[ux][uy]) {
		case 75:
		case 76:
		case 77:
		case 78:
			level[ux][uy]=(timer%400/100)+75;
			teleport();
			break;
		case 96:
		case 97:
		case 98:
		case 99:
			level[ux][uy]=(timer%400/100)+96;
			teleport();
			break;
		case 100:
		case 101:
		case 102:
		case 103:
			level[ux][uy]=(timer%400/100)+100;
			teleport();
			break;
		case 104:
		case 105:
		case 106:
		case 107:
			level[ux][uy]=(timer%400/100)+104;
			teleport();
			break;
		}
		if(ar_en) {
			switch(level[ux][uy]) {
			case 108:
			case 109:
			case 110:
			case 111:
			case 113:
			case 114:
			case 115:
			case 116:
			case 118:
			case 119:
			case 120:
			case 121:
			case 123:
			case 124:
			case 125:
			case 126:
				level[ux][uy]++;
				break;

			case 112:
				level[ux][uy]=36;
				all_load+=volume;
				break;
			case 117:
				level[ux][uy]=37;
				all_load+=volume;
				break;
			case 122:
				level[ux][uy]=38;
				all_load+=volume;
				break;
			case 127:
				level[ux][uy]=39;
				all_load+=volume;
				break;
			}
		}
		if(trap_en) {
			if(wire[q].active) {
				switch(level[ux][uy]) {
				case 156:
					level[ux][uy]=160;
					break;
				case 160:
				case 161:
				case 162:
				case 163:
					++level[ux][uy];
					break;
				case 164:
					level[ux][uy]=157;
					break;
				case 181:
					if(!level[ux+1][uy]&&!level[ux-1][uy]&&
							level[ux][uy+1]&& level[ux][uy-1])level[ux][uy]=182;
					else level[ux][uy]=193;
					break;
				case 182:
				case 183:
				case 184:
				case 185:
				case 186:
				case 187:
				case 188:
				case 189:
				case 190:
				case 191:
				case 193:
				case 194:
				case 195:
				case 196:
				case 197:
				case 198:
				case 199:
				case 200:
				case 201:
					++level[ux][uy];
					break;
				}
			} else {
				switch(level[ux][uy]) {
				case 157:
					level[ux][uy]=164;
					break;
				case 164:
				case 163:
				case 162:
				case 161:
					--level[ux][uy];
					break;
				case 160:
					level[ux][uy]=156;
					break;
				}
			}
		}
		if(wire[q].active) {
			switch(level[ux][uy]) {
			case 12:
				all_open+=volume;
				level[ux][uy]=11;
				break;
			case 28:
				alldopen+=volume;
				level[ux][uy]=29;
				break;
			case 69:
				level[ux][uy]=70;
				break;
			//arbalet
			case 36:
				level[ux][uy]=108;
				bullet.push_back({ux*64,uy*64,0,0});
				all_fire+=volume;
				break;
			case 37:
				level[ux][uy]=113;
				bullet.push_back({ux*64,uy*64,1,0});
				all_fire+=volume;
				break;
			case 38:
				level[ux][uy]=118;
				bullet.push_back({ux*64,uy*64,2,0});
				all_fire+=volume;
				break;
			case 39:
				level[ux][uy]=123;
				bullet.push_back({ux*64,uy*64,3,0});
				all_fire+=volume;
				break;
			//pulemet
			case 128:
			case 129:
			case 130:
				level[ux][uy]=47;
				break;
			case 131:
			case 132:
			case 133:
				level[ux][uy]=48;
				break;
			case 134:
			case 135:
			case 136:
				level[ux][uy]=49;
				break;
			case 137:
			case 138:
			case 139:
				level[ux][uy]=50;
				break;
			}
		} else {
			switch(level[ux][uy]) {
			case 11:
				all_close+=volume;
				level[ux][uy]=12;
				break;
			case 29:
				alldclose+=volume;
				level[ux][uy]=28;
				break;
			case 70:
				level[ux][uy]=69;
				break;
			//pulemet
			case 47:
				level[ux][uy]=128;
				break;
			case 48:
				level[ux][uy]=131;
				break;
			case 49:
				level[ux][uy]=134;
				break;
			case 50:
				level[ux][uy]=137;
				break;
			}
		}
		for(unsigned w=0; w<gate.size(); ++w) {
			if(gate[w].x==vx && gate[w].y==vy) wire[q].active=gate[w].active;
		}
	}
	if(all_close) {
		Mix_VolumeChunk(spike_close,min(all_close,MIX_MAX_VOLUME)/128.0*sound_vol);
		Mix_PlayChannel(-1,spike_close,0);
	}
	if(all_open) {
		Mix_VolumeChunk(spike_open,min(all_open,MIX_MAX_VOLUME)/128.0*sound_vol);
		Mix_PlayChannel(-1,spike_open,0);
	}
	if(alldclose) {
		Mix_VolumeChunk(dclose,min(alldclose,MIX_MAX_VOLUME)/128.0*sound_vol);
		Mix_PlayChannel(-1,dclose,0);
	}
	if(alldopen) {
		Mix_VolumeChunk(dopen,min(alldopen,MIX_MAX_VOLUME)/128.0*sound_vol);
		Mix_PlayChannel(-1,dopen,0);
	}
	if(all_fire) {
		Mix_VolumeChunk(crossbow_fire,min(all_fire,MIX_MAX_VOLUME)/128.0*sound_vol);
		Mix_PlayChannel(-1,crossbow_fire,0);
	}
	if(all_load) {
		Mix_VolumeChunk(crossbow_load,min(all_load,MIX_MAX_VOLUME)/128.0*sound_vol);
		Mix_PlayChannel(-1,crossbow_load,0);
	}
	if(all_pm) {
		Mix_VolumeChunk(pulemet,min(all_pm/2,MIX_MAX_VOLUME)/128.0*sound_vol);
		Mix_PlayChannel(-1,pulemet,0);
	}
	return 0;
}
void gates() {
	qbuf="";
	for(unsigned q=0; q<gate.size(); ++q) {
		switch(gate[q].type) {
		case 0: {
			bool ok=1;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(!wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)ok=0;
			}
			gate[q].active=ok;
		}
		break;
		case 1: {
			bool ok=0;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)ok=1;
			}
			gate[q].active=ok;
		}
		break;
		case 2: {
			int c=0;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)c+=wire[w].active;
			}
			gate[q].active=(c>0 && c!=(int)wire.size());
		}
		break;
		case 3: {
			bool ok=1;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(!wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)ok=0;
			}
			gate[q].active=!ok;
		}
		break;
		case 4: {
			bool ok=0;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)ok=1;
			}
			gate[q].active=!ok;
		}
		break;
		case 5: {
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)gate[q].active=!wire[w].active;
			}
		}
		break;
		case 6:
		case 7:
		case 8:
		case 9: {
			int t=0;
			if(gate[q].type==6)t=1000;
			if(gate[q].type==7)t=2000;
			if(gate[q].type==8)t=5000;
			if(gate[q].type==9)t=10000;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].x2==gate[q].x && wire[w].y2==gate[q].y && wire[w].active) {
					gate[q].value=timer;
				}
			}
			gate[q].active=!(gate[q].value+t<(int)timer);
		}
		break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14: {
			int t=2500;
			if(gate[q].type==10)t=250;
			else if(gate[q].type==11)t=500;
			else if(gate[q].type==12)t=1000;
			else if(gate[q].type==13)t=2000;
			if(gate[q].value+t<(int)timer) {
				gate[q].value=(int)timer;
				gate[q].active=!gate[q].active;
			}
		}
		break;
		case 15:
		case 16:
		case 17:
		case 18:
		case 19: {
			int t=5000;
			if(gate[q].type==15)t=500;
			else if(gate[q].type==16)t=1000;
			else if(gate[q].type==17)t=2000;
			else if(gate[q].type==18)t=4050;
			gate[q].active=0;
			if(gate[q].value+t<(int)timer) {
				gate[q].value=(int)timer;
				gate[q].active=1;
			}
		}
		break;
		case 20: {
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].x2==gate[q].x && wire[w].y2==gate[q].y && wire[w].active)gate[q].active=1;
			}
		}
		break;
		case 21: {
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].x2==gate[q].x && wire[w].y2==gate[q].y && wire[w].active)gate[q].active=0;
			}
		}
		break;
		case 22: {
			gate[q].active=0;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].x2==gate[q].x && wire[w].y2==gate[q].y && wire[w].active)gate[q].active=1;
			}
			if(gate[q].active) {
				uint8_t &v=level[gate[q].x+1][gate[q].y];
				if(v<108) {
					switch(v) {
					case 57:
						v=54;
						break;
					case 61:
						v=58;
						break;
					case 63:
						v=62;
						break;
					case 67:
						v=64;
						break;
					case 39:
						v=36;
						break;
					case 50:
						v=47;
						break;
					default:
						v++;
					}
				} else if(v<128) {
					if(v>=123)v-=15;
					else v+=5;
				} else if(v<140) {
					if(v>=137)v-=9;
					else v+=3;
				}
			}
		}
		break;
		case 23: {
			gate[q].active=0;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].x2==gate[q].x && wire[w].y2==gate[q].y && wire[w].active)gate[q].active=1;
			}
			if(gate[q].active) {
				uint8_t &v=level[gate[q].x+1][gate[q].y];
				if(v<108) {
					switch(v) {
					case 54:
						v=57;
						break;
					case 58:
						v=61;
						break;
					case 62:
						v=63;
						break;
					case 64:
						v=67;
						break;
					case 36:
						v=39;
						break;
					case 47:
						v=50;
						break;
					default:
						v--;
						break;
					}
				} else if(v<128) {
					if(v<=112)v+=15;
					else v-=5;
				} else if(v<140) {
					if(v<=130)v+=9;
					else v-=3;
				}
			}
		}
		break;
		case 24: {
			if(player->x/64==gate[q].x && player->y/64==gate[q].y)gate[q].active=1;
			else gate[q].active=0;
		}
		break;
		case 25: {
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].x2==gate[q].x && wire[w].y2==gate[q].y && wire[w].active && !gate[q].active) {
					gate[q].active=1;
					txt=*replies[gate[q].value];
					timer_sbt=timer;
					break;
				}
			}
		}
		break;
		case 26: {
			gate[q].active=0;
			for(unsigned w=0; w<rock.size(); ++w) {
				if(rock[w].x/64==gate[q].x && rock[w].y/64==gate[q].y)gate[q].active=1;
			}
		}
		break;
		case 27: {
			gate[q].active=(player->door_key[gate[q].value]==1);
		}
		break;
		case 28: {
			gate[q].active=(player->door_key[gate[q].value]==2);
		}
		break;
		case 29: {
			gate[q].active=(player->dietimer>0);
		}
		break;
		case 30: {
			for(unsigned w=0; w<wire.size(); ++w) {
				if(wire[w].x2==gate[q].x && wire[w].y2==gate[q].y && wire[w].active && !gate[q].active) {
					gate[q].active=1;
					gg.kill();
				}
			}
		}
		break;
		case 31:
		case 32:
		case 33:
		case 34: {
			int t=0;
			if(gate[q].type==31)t=1000;
			if(gate[q].type==32)t=2000;
			if(gate[q].type==33)t=5000;
			if(gate[q].type==34)t=10000;
			gate[q].active=0;
			bool ok=0;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)ok=1;
			}
			if(ok && !gate[q].value)gate[q].value=timer;
			if(timer>gate[q].value+t) {
				if(!ok)gate[q].value=0;
				if(ok)gate[q].active=1;
			}
		}
		break;
		case 35: {
			if(gate[q].value) {
				bool ok=0;
				for(int w=0; w<(int)wire.size(); ++w) {
					if(wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)ok=1;
				}
				if(!ok)break;
				int n=0;
				for(unsigned q=0; q<qbuf.size(); ++q)if(qbuf[q]==63)n++;
				gate[q].active=0;
				int h=20*iface_zoom;
				int y=50*iface_zoom+n*h;
#ifdef ANDROID
				int w=SW-230*iface_zoom;
				int x=115*iface_zoom;
#else
				int w=SW/8*6;
				int x=SW/8;
#endif
				SDL_Rect r= {x,y,w,h};
				if(key[SDL_SCANCODE_1+n] || (e.button.state && in_rect(r))) {
					gate[q].active=1;
					gate[q].value=0;
					while(key[SDL_SCANCODE_1+n])SDL_PollEvent(&e);
					while(e.button.state && in_rect(r))SDL_PollEvent(&e);
					break;
				}
				qbuf+=string((qbuf.size()?"\n":"")+to_string(n+1)+". "+*questions[gate[q].value]);
			}
		}
		break;
		case 36: {
			bool ok=0;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)ok=1;
			}

		}
		break;
		/*case 37: {
			if(st) {
				gate[q].active=(profile.die[lidtoln(lid)]==gate[q].value);
			}
		}
		break;*/
		case 38: {
			bool ok=0;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)ok=1;
			}
			if(ok && !gate[q].active) {
				gate[q].active=1;
				Mix_Music *music=Mix_LoadMUS(string(global_data_dir+"music/"+to_string(gate[q].value)+".mp3").c_str());
				Mix_VolumeMusic(music_vol);
				Mix_ResumeMusic();
				Mix_PlayMusic(music,-1);
			}
		}
		case 39:
			gate[q].active=1;
			break;
		case 41: {
			bool ok=0;
			for(int w=0; w<(int)wire.size(); ++w) {
				if(wire[w].active && wire[w].x2==gate[q].x && wire[w].y2==gate[q].y)ok=1;
			}
			gate[q].active=ok;
		}
		break;
		}
	}
}
void rocks() {
	for(int q=0; q<(int)rock.size(); ++q) {
		if(rock[q].update()) {
			rock.erase(rock.begin()+q);
		}
	}
}
//*******   LASERS   *******//
uint8_t Laser::n() {
	if(y2<y1 && x1==x2)return 0;
	if(y1==y2 && x2>x1)return 1;
	if(y2>y1 && x1==x2)return 2;
	return 3;
}
void create_laser(uint8_t x,uint8_t y,uint8_t n) {
	laser.push_back({x,y,(uint8_t)(x+(n==1)-(n==3)),(uint8_t)(y+(n==2)-(n==0))});
	Laser *l=&laser[laser.size()-1];
	uint8_t level2[255][255];
	memcpy(level2,level,sizeof(level2));
	for(unsigned q=0; q<rock.size(); ++q)level2[rock[q].x/64][rock[q].y/64]=1;
	if(player!=&gg)
		level2[(player->x+32)/64][(player->y+32)/64]=1;
	while(1) {
		if(block_config[4][level2[l->x2][l->y2]])break;
		l->y2-=(n==0);
		l->y2+=(n==2);
		l->x2+=(n==1);
		l->x2-=(n==3);
	}
}
void lasers() {
	laser.clear();
	for(int x=0; x<w; ++x) {
		for(int y=0; y<h; ++y) {
			if(level[x][y]==72)level[x][y]=71;
			if(level[x][y]>=54 && level[x][y]<=68) {
				bool b[4]= {0,0,0,0};
				switch(level[x][y]) {
				case 54:
					b[0]=1;
					break;
				case 55:
					b[1]=1;
					break;
				case 56:
					b[2]=1;
					break;
				case 57:
					b[3]=1;
					break;
				case 58:
					b[0]=1;
					b[1]=1;
					break;
				case 59:
					b[1]=1;
					b[2]=1;
					break;
				case 60:
					b[2]=1;
					b[3]=1;
					break;
				case 61:
					b[3]=1;
					b[0]=1;
					break;
				case 62:
					b[0]=1;
					b[2]=1;
					break;
				case 63:
					b[1]=1;
					b[3]=1;
					break;
				case 64:
					b[1]=1;
					b[2]=1;
					b[3]=3;
					break;
				case 65:
					b[0]=1;
					b[2]=1;
					b[3]=3;
					break;
				case 66:
					b[0]=1;
					b[1]=1;
					b[3]=3;
					break;
				case 67:
					b[0]=1;
					b[1]=1;
					b[2]=3;
					break;
				case 68:
					b[0]=1;
					b[1]=1;
					b[2]=3;
					b[3]=1;
					break;
				}
				for(int q=0; q<4; ++q) {
					if(b[q])create_laser(x,y,q);
				}
			}
		}
	}
	for(int q=0; q<(int)laser.size(); ++q) {
		if(level[laser[q].x2][laser[q].y2]==70) {
			switch(laser[q].n()) {
			case 0:
				create_laser(laser[q].x2,laser[q].y2,1);
				break;
			case 1:
				create_laser(laser[q].x2,laser[q].y2,0);
				break;
			case 2:
				create_laser(laser[q].x2,laser[q].y2,3);
				break;
			case 3:
				create_laser(laser[q].x2,laser[q].y2,2);
				break;
			}
		}
		if(level[laser[q].x2][laser[q].y2]==69) {
			switch(laser[q].n()) {
			case 0:
				create_laser(laser[q].x2,laser[q].y2,3);
				break;
			case 1:
				create_laser(laser[q].x2,laser[q].y2,2);
				break;
			case 2:
				create_laser(laser[q].x2,laser[q].y2,1);
				break;
			case 3:
				create_laser(laser[q].x2,laser[q].y2,0);
				break;
			}
		}

		if(level[laser[q].x2][laser[q].y2]==71)level[laser[q].x2][laser[q].y2]=72;
		if(((laser[q].x1==gg.x/64 && laser[q].x1==laser[q].x2 && in_range(laser[q].y1,gg.y/64,laser[q].y2)) ||
				(laser[q].y1==gg.y/64 && laser[q].y1==laser[q].y2 && in_range(laser[q].x1,gg.x/64,laser[q].x2)))
				&& !gg.dietimer && !(gg.x%64) && !(gg.y%64))gg.kill();
	}
}
//*******   BOMBS   *******//
void bombs() {
	bool ok=0;
	if(timer>timer_bomb+100) {
		timer_bomb=timer;
		ok=1;
	}
}
bool Bullet::p() {
	uint8_t level2[255][255];
	memcpy(level2,level,sizeof(level2));
	for(unsigned q=0; q<rock.size(); ++q) {
		if(rock[q].type==0) {
			level2[(rock[q].x+32)/64][(rock[q].y+32)/64]=1;
		}
	}
	if(block_config[3][level2[(x+32)/64][(y+32)/64]])return 1;
	return 0;
}
void Bullet::move() {
	int j=rand()%16+8;
	y-=(n==0)*j;
	x+=(n==1)*j;
	y+=(n==2)*j;
	x-=(n==3)*j;
}
void bullets() {
	if(timer>timer_bl+10) {
		timer_bl=timer;
		for(int q=0; q<(int)bullet.size(); ++q) {
			bullet[q].move();
			uint8_t *block=&level[(bullet[q].x+32)/64][(bullet[q].y+32)/64];
			if(bullet[q].type==2) {
				if(*block==87 || *block==69 || *block==70)*block=88;
			}
			if(bullet[q].p()) {
				if(bullet[q].type==2) {
					if(*block==84)*block=85;
					if(*block==1 || *block==40 || *block==42 || *block==43 ||
							*block==44 || *block==45 || *block==46)*block=84;
					for(unsigned w=0; w<rock.size(); ++w) {
						if(rock[w].type==0  &&
								rock[w].x/64==(bullet[q].x+32)/64  &&
								rock[w].y/64==(bullet[q].y+32)/64) {
							rock[w].tm=timer;
						}
					}
				}
				bullet.erase(bullet.begin()+q);
			}
			if(abs(gg.x-bullet[q].x)<32 && abs(gg.y-bullet[q].y)<32) {
				gg.kill();
				bullet.erase(bullet.begin()+q);
			}
			if(player != &gg && abs(player->x-bullet[q].x)<32 && abs(player->y-bullet[q].y)<32) {
				player->kill();
				bullet.erase(bullet.begin()+q);
			}
		}
	}
}
void game_init(bool restart) {
	SDL_RenderSetViewport(ren,0);
	Mix_Music *music=0;
	if(st && lidtoln(lid)%11==9) {
		music=Mix_LoadMUS(string(global_data_dir+"music/extra.mp3").c_str());
	} else if(!st||lidtoln(lid)%11!=10) {
		int c=rand()%3+1;
		music=Mix_LoadMUS(string(global_data_dir+"music/fon-"+to_string(c)+".mp3").c_str());
	}
	if(music) {
		Mix_VolumeMusic(music_vol);
		Mix_ResumeMusic();
		Mix_PlayMusic(music,-1);
	}
#ifdef ANDROID
	sensor=0;
#endif

	if(player!=&gg)delete player;
	player=&gg;
	player->bring=0;
	player->speed=3;
	player->lives=1;
	player->dietimer=0;
	player->push=0;
	player->n=1;
	player->bring=0;
	for(int q=0; q<18; ++q)player->door_key[q]=0;
	destroy_subt();
	load_subtitles();
	ltime=timer;
	for(int x=0; x<w; ++x)for(int y=0; y<h; ++y)light[x][y]=0;
	for(int q=0; q<(int)wire.size(); ++q)wire[q].active=0;
	for(int q=0; q<(int)gate.size(); ++q) {
		gate[q].active=(gate[q].type==21);
		if(gate[q].type!=25 && gate[q].type!=27 && gate[q].type!=28 && gate[q].type!=35 && gate[q].type!=36 && gate[q].type!=37 && gate[q].type!=38 && gate[q].type!=40)
			gate[q].value=0;
	}
	for(int x=0; x<w; ++x) {
		for(int y=0; y<h; ++y) {
			switch(level[x][y]) {
			case 27:
				player->x=x*64;
				player->y=y*64;
				break;
			case 13:
				rock.push_back({(uint16_t)(x*64),(uint16_t)(y*64),0,0});
				level[x][y]=0;
				break;
			case 80:
			case 81:
			case 82:
			case 83:
				rock.push_back({uint16_t(x*64),uint16_t(y*64),0,uint8_t(2+(level[x][y]-80)*9)});
				level[x][y]=0;
				break;
			case 47:
			case 48:
			case 49:
			case 50:
				level[x][y]=128+(level[x][y]-47)*3;
				break;
			}
		}
	}
	if(map)SDL_FreeSurface(map);
	if(lrd) {
		delete lrd;
		lrd=0;
	}
	load_passwords();
}

bool game() {
	game_init(0);
	bool ok=1;
	while(ok) {
		SDL_PollEvent(&e);
		if(e.type==SDL_QUIT)quit(1);
		if(Back()
#ifdef ANDROID
				|| sensor==1
#endif
		  ) {
			if(pause())return 1;
			SDL_RenderSetViewport(ren,0);
		}
		if(lrd) {
			if(lrd->fly()) {
				delete lrd;
				lrd=0;
			}
			if(!key_en)lrd->action();
		} else if(!gg.dietimer){
			player->go();
			if(!key_en)player->action();
		}
		if(e.type==SDL_KEYDOWN
#ifdef ANDROID
				|| sensor!=0
#endif
		  ) {
			key_en=1;
#ifdef DEV
			if(key[SDL_SCANCODE_C]) {
				console();
				SDL_RenderSetViewport(ren,0);
			}
#endif
		} else if(e.type==SDL_KEYUP
#ifdef ANDROID
				  || sensor==0
#endif
				 )key_en=0;
		if(player->lives && player->dietimer<0 && -player->dietimer<timer)player->dietimer=0;
		if(gg.dietimer && e.button.state==1)if(end(0,1,0))return 1;
		if(player->update())return 1;
		if(player!=&gg&&gg.update())return 1;
		if(lrd) {
			set_camera(lrd->x,lrd->y,0);
		} else {
			if(player->dietimer<=0) {
				set_camera(player->x,player->y,0);
			}
		}

		SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_RenderClear(ren);
		draw(1,0,0);
#ifdef ANDROID
		sensor_draw();
#endif
		if(sb_on)subtitres(0);
		SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_Rect r= {0,0,SW,int(50*iface_zoom)};
		SDL_RenderFillRect(ren,&r);
		FC_Draw(menu,ren,50,10*iface_zoom,"%d:%02d",(timer-ltime)/60000,(timer-ltime)%60000/1000);
		SDL_RenderPresent(ren);
	}
	return 0;
}
#ifdef ANDROID
char *RWget(const char *filename) {
	SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
	if (rw == NULL) return NULL;

	Sint64 res_size = SDL_RWsize(rw);
	char* res = (char*)malloc(res_size + 1);

	Sint64 nb_read_total = 0, nb_read = 1;
	char* buf = res;
	while (nb_read_total < res_size && nb_read != 0) {
		nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
		nb_read_total += nb_read;
		buf += nb_read;
	}
	SDL_RWclose(rw);
	if (nb_read_total != res_size) {
		free(res);
		return NULL;
	}
	res[nb_read_total] = '\0';
	return res;
}
stringstream RWstream(const char *filename) {
	stringstream a;
	char *b=RWget(filename);
	a<<b;
	delete[]b;
	return a;

}
#endif
template<typename T>
char in(T& s) {
	char c;
	s.read(reinterpret_cast<char*>(&c),1);
	return c;
}
template<typename T>
unsigned short in16(T& s) {
	uint16_t c;
	s.read(reinterpret_cast<char*>(&c),2);
	return SDL_Swap16(c);
}
template<typename T>
void out(T& s,int i) {
	s<<(char)i;
}
template<typename T>
void out16(T& s,int i) {
	s<<(char)(i/256)<<(char)(i%256);
}
void save(string path) {
	ofstream f(path,ios_base::out|ios_base::binary);
	out(f,w);
	out(f,h);
	for(int y=0; y<h; ++y) {
		for(int x=0; x<w; ++x) {
			out(f,level[x][y]);
		}
	}
	out16(f,gate.size());
	for(int q=0; q<(int)gate.size(); ++q) {
		out(f,gate[q].x);
		out(f,gate[q].y);
		out(f,gate[q].type);
		out16(f,gate[q].value);
	}
	out16(f,wire.size());
	for(int q=0; q<(int)wire.size(); ++q) {
		out(f,wire[q].x1);
		out(f,wire[q].y1);
		out(f,wire[q].x2);
		out(f,wire[q].y2);
	}
	f.close();
}
void open(string path) {
#ifdef ANDROID
	SDL_RWops *f=SDL_RWFromFile(path.c_str(),"rb");
	w=SDL_ReadU8(f);
	h=SDL_ReadU8(f);
	for(int y=0; y<h; ++y) {
		for(int x=0; x<w; ++x) {
			level[x][y]=SDL_ReadU8(f);
		}
	}
	gate.resize(SDL_ReadBE16(f));
	for(int q=0; q<(int)gate.size(); ++q) {
		gate[q].x=SDL_ReadU8(f);
		gate[q].y=SDL_ReadU8(f);
		gate[q].type=SDL_ReadU8(f);
		gate[q].value=SDL_ReadBE16(f);
	}
	wire.resize(SDL_ReadBE16(f));
	for(int q=0; q<(int)wire.size(); ++q) {
		wire[q].x1=SDL_ReadU8(f);
		wire[q].y1=SDL_ReadU8(f);
		wire[q].x2=SDL_ReadU8(f);
		wire[q].y2=SDL_ReadU8(f);
	}
	f->close(f);
#else
	ifstream f(path.c_str(),ios_base::in|ios_base::binary);
	w=in(f);
	h=in(f);
	for(int y=0; y<h; ++y) {
		for(int x=0; x<w; ++x) {
			level[x][y]=in(f);
		}
	}
	gate.resize(in16(f));
	for(int q=0; q<(int)gate.size(); ++q) {
		gate[q].x=in(f);
		gate[q].y=in(f);
		gate[q].type=in(f);
		gate[q].value=in16(f);
	}
	wire.resize(in16(f));
	for(int q=0; q<(int)wire.size(); ++q) {
		wire[q].x1=in(f);
		wire[q].y1=in(f);
		wire[q].x2=in(f);
		wire[q].y2=in(f);
	}
	f.close();
#endif
	rock.resize(0);
	bullet.resize(0);
	laser.resize(0);
	if(lrd) {
		delete lrd;
		lrd=0;
	}
	if(contr) {
		delete contr;
		contr=0;
	}
	tecno=floor_type();
}
void save_settings() {
	string path=save_data_dir+"settings.ini";
	IniFile ini;
	ini.Load(path);
	ini.SetIntValue("SCREEN","SCREEN_W",SW);
	ini.SetIntValue("SCREEN","SCREEN_H",SH);
	ini.SetBoolValue("SCREEN","FULLSCREEN",fullscreen);
	ini.SetBoolValue("SCREEN","QUALITY",darkost);

	ini.SetStringValue("COMMON","LANG",loc);
	ini.SetIntValue("COMMON","PROFILE",profn);

	ini.SetIntValue("SOUND","SOUND_VOLUME",sound_vol);
	ini.SetIntValue("SOUND","MUSIC_VOLUME",music_vol);

	ini.SetBoolValue("SUBTITLES","ENABLE",sb_on);
	ini.Save();
}
void load_settings() {
	string path=save_data_dir+"settings.ini";
	IniFile ini;
	if(ini.Load(path)==ERR_OPEN_FILE_FAILED)return;
	ini.GetIntValue("SCREEN","SCREEN_W",&SW);
	ini.GetIntValue("SCREEN","SCREEN_H",&SH);
	ini.GetBoolValue("SCREEN","FULLSCREEN",&fullscreen);
	ini.GetBoolValue("SCREEN","QUALITY",&darkost);

	ini.GetStringValue("COMMON","LANG",&loc);
	ini.GetIntValue("COMMON","PROFILE",&profn);

	ini.GetIntValue("SOUND","SOUND_VOLUME",&sound_vol);
	ini.GetIntValue("SOUND","MUSIC_VOLUME",&music_vol);

	ini.GetBoolValue("SUBTITLES","ENABLE",&sb_on);
}
bool Profile::save(uint8_t n) {
	system(string(mkdir_command+save_data_dir+"profiles").c_str());
	string str=save_data_dir+"profiles/"+(char)(n+'0')+".pfl";
	ofstream file(str.c_str(),ios_base::binary);
	if(!file)return 1;
	file<<name<<';';
	out(file,level);
//	out16(file,code);
	out(file,1);
	file.close();
	return 0;
}
bool Profile::load(uint8_t n) {
	string str=save_data_dir+"profiles/"+(char)(n+'0')+".pfl";
	ifstream file(str.c_str(),ios_base::binary);
	if(!file) {
#ifndef STEAM
		clear(n);
#endif
		return 1;
	}
#ifdef STEAM
	string s;
	getline(file,s,';');
#else
	getline(file,name,';');
#endif
	level=in(file);
//	code=in16(file);
	in(file);
	file.close();
	return 0;
}
void load_strings() {
	string path=global_data_dir+"locales/"+loc+"/strings.txt";
#ifdef ANDROID
	stringstream file=RWstream(path.c_str());
#else
	ifstream file(path.c_str());
#endif
	for(int q=0; q<STRINGS_COUNT; ++q) {
		getline(file,strings[q]);
		if(strings[q][strings[q].size()-1]=='\r')strings[q].pop_back();
	}
#ifndef ANDROID
	file.close();
#endif
}
#ifdef WIN32
std::vector<string>get_levels() {
	std::vector<string> names;
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(string(save_data_dir+"levels/custom/*").c_str(), &fd);
	if(hFind != INVALID_HANDLE_VALUE) {
		do {
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))names.push_back(fd.cFileName);
		} while(::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}
#else
std::vector<string>get_levels() {
	std::vector<string> names;
	char var[128];
	FILE *fp = popen(string("ls "+save_data_dir+"/levels/custom").c_str(),"r");
	while (fgets(var, sizeof(var), fp) != NULL) {
		names.push_back(string(var));
		names[names.size()-1].pop_back();
	}
	pclose(fp);
	return names;
}
#endif
bool CLEAR(SDL_Rect window, string cross) {
	if(cross!="null") {
		SDL_SetRenderDrawColor(ren,0,0,0,255);
#ifdef ANDROID
		SDL_RenderSetViewport(ren,0);
		SDL_RenderClear(ren);
#endif
		window.x=SW/2-window.w/2;
		window.y=SH/2-window.h/2;
		SDL_RenderSetViewport(ren,&window);
		SDL_RenderFillRect(ren,0);
		SDL_SetRenderDrawColor(ren,255,255,255,255);
		SDL_RenderDrawRect(ren,0);
	}
	if(cross.size()) {
		static SDL_Texture *cr=0;
		if(cr==0)cr=load(string(global_data_dir+"textures/cross.png").c_str());
		if(cross=="null") {
			SDL_DestroyTexture(cr);
			cr=0;
		} else {
			int j30=30.0f*iface_zoom;
			SDL_Rect r= {window.w-j30,0,j30,j30};
			showIMG(r,cr);
			SDL_RenderDrawLine(ren,0,j30,window.w,j30);
			if(e.type==SDL_MOUSEBUTTONDOWN&&in_rect(r))return 1;
			FC_DrawButtonLeft(def,ren, {j30/2,0,window.w-2*j30,j30},cross.c_str());
		}
	}
	return 0;
}
void RESIZE(void *data, int size) {
	int *d=(int*)data;
	for(int q=0; q<size; ++q,d++) {
		*d=int(*d*iface_zoom);
	}
}
bool gin(uint8_t* c) {
	bool ok=0;
	if(e.key.keysym.sym==SDLK_BACKSPACE && e.type==SDL_KEYDOWN && *c > 0) {
#ifndef ANDROID
		while(e.key.keysym.sym==SDLK_BACKSPACE && e.type==SDL_KEYDOWN)SDL_PollEvent(&e);
#endif
		*c/=10;
		ok=1;
	}
	if(e.text.type==SDL_TEXTINPUT) {
		if(e.text.text[0]>='0' && e.text.text[0]<='9') {
			*c*=10;
			*c+=(int)(e.text.text[0]-'0');
			ok=1;
#ifndef ANDROID
			while(e.text.type==SDL_TEXTINPUT)SDL_PollEvent(&e);
#endif
		}
	}
	return ok;
}
bool gin(int* c) {
	bool ok=0;
	if(e.key.keysym.sym==SDLK_BACKSPACE && e.type==SDL_KEYDOWN && *c > 0) {
#ifndef ANDROID
		while(e.key.keysym.sym==SDLK_BACKSPACE && e.type==SDL_KEYDOWN)SDL_PollEvent(&e);
#endif
		*c/=10;
		ok=1;
	}
	if(e.text.type==SDL_TEXTINPUT) {
		if(e.text.text[0]>='0' && e.text.text[0]<='9') {
			*c*=10;
			*c+=(int)(e.text.text[0]-'0');
			ok=1;
#ifndef ANDROID
			while(e.text.type==SDL_TEXTINPUT)SDL_PollEvent(&e);
#endif
		}
	}
	return ok;
}
bool gin(string* c) {
	bool ok=0;
	if(e.key.keysym.sym==SDLK_BACKSPACE && e.type==SDL_KEYDOWN && c->size() > 0) {
#ifndef ANDROID
		while(e.key.keysym.sym==SDLK_BACKSPACE && e.type==SDL_KEYDOWN)SDL_PollEvent(&e);
#endif
		int textlen=c->size();

		do {
			if (textlen==0) {
				break;
			}
			if (((*c)[textlen-1] & 0x80) == 0x00) {
				(*c)[textlen-1]=0x00;
				c->pop_back();
				break;
			}
			if (((*c)[textlen-1] & 0xC0) == 0x80) {
				(*c)[textlen-1]=0x00;
				textlen--;
				c->pop_back();
			}
			if (((*c)[textlen-1] & 0xC0) == 0xC0) {
				(*c)[textlen-1]=0x00;
				c->pop_back();
				break;
			}
		} while(1);
		ok=1;
	}
	if(e.text.type==SDL_TEXTINPUT) {
		*c+=e.text.text;
		ok=1;
#ifndef ANDROID
		while(e.text.type==SDL_TEXTINPUT)SDL_PollEvent(&e);
#endif
	}
	return ok;
}
bool alert() {
	SDL_Rect window= {0,0,200,150};
	SDL_Rect button[]= {{20,80,60,50},{110,80,60,50}};
	RESIZE(button,8);
	RESIZE(&window,4);
	while(1) {
		CLEAR(window,"");
		if(Back())return 0;
		FC_DrawAlign(def,ren,window.w/2,window.h/6,FC_ALIGN_CENTER,strings[14].c_str());
		for(int q=0; q<2; ++q) {
			SDL_RenderDrawRect(ren,&button[q]);
			FC_DrawButtonCenter(def,ren,button[q],strings[16-q].c_str());
		}
		SDL_RenderPresent(ren);
		SDL_WaitEvent(&e);
		mouse.update();
		if(e.type==SDL_QUIT)quit(1);
		else if(e.type==SDL_MOUSEBUTTONDOWN) {
			for(int q=0; q<2; ++q) {
				if(in_rect(button[q])) {
					mouse.wait();
					return !q;
				}
			}
		}
	}
}

bool inputwh(string namel,uint8_t wl,uint8_t hl) {
	SDL_Rect window= {0,0,400,300};
	RESIZE(&window,4);
	int ch=0;
	while(1) {
		if(e.type==SDL_QUIT) {
			quit(1);
		}
		if(CLEAR(window,strings[9]) || Back()) {
			SDL_StopTextInput();
			break;
		}
		SDL_Rect input[]= {{130,60,250,30},
			{320,110,60,30},
			{320,160,60,30},
			{100,250,200,30}
		};
		RESIZE(input,16);
		switch(ch) {
		case 0:
			gin(&namel);
			break;
		case 1:
			gin(&wl);
			break;
		case 2:
			gin(&hl);
			break;
		}
		for(int q=0; q<4; ++q) {
			SDL_RenderDrawRect(ren,&input[q]);
			if(q<3) {
				FC_Draw(def,ren,20*iface_zoom,input[q].y+5*iface_zoom,strings[10+q].c_str());
			} else FC_DrawButtonCenter(def,ren,input[q],strings[13].c_str());
			switch(q) {
			case 0:
				FC_DrawButtonLeft(def,ren,input[q],"%s%s",namel.c_str(),(ch==0?"_":""));
				break;
			case 1:
				FC_DrawButtonLeft(def,ren,input[q],"%d%s",wl,(ch==1?"_":""));
				break;
			case 2:
				FC_DrawButtonLeft(def,ren,input[q],"%d%s",hl,(ch==2?"_":""));
				break;
			}
			if(in_rect(input[q]) && e.button.state) {
				ch=q;
				if(ch<3)SDL_StartTextInput();
			}
			int k=namel[namel.size()-1];
			if(namel.size()>19 ||
					k=='\\' || k==':' || k=='*' ||
					k=='?' || k=='"' || k=='<' ||
					k=='>' || k=='|')namel.pop_back();
			if(wl>255)wl/=10;
			if(hl>255)hl/=10;
			if(ch==3 && wl>0 && hl>0) {
				mouse.wait();
				if(namel[namel.size()-1]==' ' || namel[namel.size()-1]=='.')namel.pop_back();
				if(namel[0]==' ')namel.erase(namel.begin());
				if(namel.size()>0) {
					w=wl;
					h=hl;
					lid=namel;
					if(namel[namel.size()-1]=='l'  &&
							namel[namel.size()-2]=='v'  &&
							namel[namel.size()-3]=='l'  &&
							namel[namel.size()-4]=='.')
						for(int q=0; q<4; ++q)lid.pop_back();
					SDL_StopTextInput();
					return 1;
				}
			}

		}
		SDL_RenderPresent(ren);
		SDL_WaitEvent(&e);
		mouse.update();
	}
	return 0;
}
void custom() {
	st=0;
	SDL_Rect window= {0,0,550,400};
	RESIZE(&window,4);
	Scrollbar scroll;
	scroll.set(530,30,290);
	scroll.update(1);
	int sh=-1;
	std::vector<string>names=get_levels();
	while(1) {
		if(e.type==SDL_QUIT) {
			quit(1);
		}
		if(CLEAR(window,strings[17]) || Back())break;
		SDL_Rect button[4]= {{30, 330,230,25},
			{290,330,230,25},
			{30, 365,230,25},
			{290,365,230,25}
		};
		RESIZE(button,16);
		bool j=0;
		for(unsigned q=0; q<names.size(); ++q) {
			if(q-scroll.getp()>=0 && q-scroll.getp()<9) {
				SDL_Rect show= {int(20*iface_zoom),int((q-scroll.getp())*30*iface_zoom+40*iface_zoom),int(510*iface_zoom),int(30*iface_zoom)};
				if(sh==(int)q)SDL_RenderDrawRect(ren,&show);
				FC_DrawButtonLeft(def,ren,show,names[q].c_str());
				if(in_rect(show) && mouse.state && !scroll.motion) {
					sh=q;
				}
			}
		}
		for(int w=0; w<2; ++w) {
			for(int q=0; q<4; ++q) {
				SDL_RenderDrawRect(ren,&button[q]);
				if(!w) {
					FC_DrawButtonCenter(def,ren,button[q],strings[18+q].c_str());
				}
				if(in_rect(button[q]) && mouse.state && w) {
					mouse.wait();
					j=1;
					switch(q) {
					case 0: {
						system(string(mkdir_command+save_data_dir+"levels").c_str());
						system(string(mkdir_command+save_data_dir+"levels/custom").c_str());
						if(inputwh("level",20,20)) {
							editor(1);
							return;
						}
					}
					break;
					case 1: {
						if(sh!=-1) {
							string path=save_data_dir+"levels/custom/"+names[sh];
#ifdef ANDROID
							stringstream f=RWstream(path.c_str());
#else
							ifstream f(path,ios_base::binary);
#endif
							int wk,hk;
							wk=in(f);
							hk=in(f);
#ifndef ANDROID
							f.close();
#endif
							if(inputwh(names[sh],wk,hk)) {
								open(path);
								editor(0);
								return;
							}
						}
					}
					break;
					case 2: {
						if(sh!=-1 && alert())remove(string(save_data_dir+"levels/custom/"+names[sh]).c_str());
						names=get_levels();
					}
					break;
					case 3: {
						if(sh!=-1) {
							open(string(save_data_dir+"levels/custom/"+names[sh]));
							lid=names[sh];
							for(int q=0; q<4; ++q)lid.pop_back();
							game();
							return;
						}
					}
					break;
					}
				}
			}
		}
		scroll.update(1);
		SDL_RenderPresent(ren);
		if(!j)SDL_WaitEvent(&e);
		mouse.update();
	}
}
uint8_t input_number(uint8_t ch_gt) {
	SDL_Rect window= {0,0,400,300};
	SDL_Point point[]= {{20,40},{20,90},{20,110}};
	RESIZE(&window,4);
	RESIZE(point,6);
	SDL_StartTextInput();
	uint8_t c=0;
	while(!(e.key.keysym.sym==SDLK_RETURN && e.type==SDL_KEYDOWN)) {
		if(e.type==SDL_QUIT) {
			quit(1);
		}
		if(CLEAR(window,strings[29]) || Back()) {
			SDL_StopTextInput();
			return 0xFF;
		}
		FC_DrawColumn(def,ren,point[0].x,point[0].y,380*iface_zoom,strings[30].c_str());
		FC_Draw(def,ren,point[1].x,point[1].y,"%d",c);
		if(ch_gt==25 || ch_gt==35) {
			if(c==0)txt=strings[31];
			FC_DrawColumn(def,ren,point[2].x,point[2].y,380*iface_zoom,txt.c_str());
		} else if(ch_gt==27 || ch_gt==28) {
			string t;
			switch(c) {
			case 0:
			case 6:
				t=strings[32];
				break;
			case 1:
			case 7:
				t=strings[33];
				break;
			case 2:
			case 8:
				t=strings[34];
				break;
			case 3:
			case 9:
				t=strings[35];
				break;
			case 4:
			case 10:
				t=strings[36];
				break;
			case 5:
			case 11:
				t=strings[37];
				break;
			default:
				t=strings[38];
				break;
			}
			if(c>=6 && c<12)t+=strings[39];
			FC_DrawColumn(def,ren,point[0].x,point[0].y,380*iface_zoom,t.c_str());
		}
		SDL_RenderPresent(ren);
		SDL_WaitEvent(&e);
		mouse.update();
		if(gin(&c)) {
			if(ch_gt==25 || ch_gt==35) {
				ifstream file(ch_gt==25?
							  string(global_data_dir+"locales/"+loc+"/replies.txt"):
							  string(global_data_dir+"locales/"+loc+"/questions.txt"));
				int k=0;
				while(k!=c) {
					getline(file,txt);
					k++;
				}
				file.close();
			}
		}
	}
	SDL_StopTextInput();

	return c;
}
bool console() {
	int time=SDL_GetTicks();
	SDL_Rect window= {0,0,550,400};
	RESIZE(&window,4);
	stringstream str;
	string in;
	SDL_StartTextInput();
	while(1) {
		if(e.type==SDL_QUIT) {
			quit(1);
		} else if(e.type==SDL_MOUSEBUTTONDOWN) {
			SDL_StartTextInput();
		}
		if(CLEAR(window,strings[65]) || Back()) {
			SDL_StopTextInput();
			break;
		}
		SDL_RenderDrawLine(ren,0,360*iface_zoom,550*iface_zoom,360*iface_zoom);
		gin(&in);
		FC_Draw(def,ren,15*iface_zoom,370*iface_zoom,string("> "+in+"_").c_str());
		SDL_Rect r= {0,int(30*iface_zoom),window.w,int(window.h-30*iface_zoom)};
		SDL_RenderSetClipRect(ren,&r);
		FC_DrawColumn(def,ren,15*iface_zoom,370*iface_zoom-FC_GetColumnHeight(def,520*iface_zoom,str.str().c_str()),520*iface_zoom,str.str().c_str());
		SDL_RenderSetClipRect(ren,0);
		bool j=0;
		if(e.key.keysym.sym==SDLK_RETURN && e.type==SDL_KEYDOWN) {
			while(e.key.keysym.sym==SDLK_RETURN && e.type==SDL_KEYDOWN)SDL_PollEvent(&e);
			str<<"> "<<in<<endl;
			string res=command(in);
			if(res.size())str<<res<<endl;
			in.clear();
			j=1;
		}
		SDL_RenderPresent(ren);
		if(!j)SDL_WaitEvent(&e);
		mouse.update();
	}
	timer_pause+=(SDL_GetTicks()-time);
	return 0;
}

void standart() {
	SDL_Texture *arrow  =   load(string(global_data_dir+"textures/arrows.png").c_str());
	st=1;
	SDL_Rect window= {0,0,550,400};
	SDL_Rect ar[]= {
		{0,30,30,30},
		{340,30,30,30},
	};
	RESIZE(&window,4);
	RESIZE(ar,8);
	int sh=0;
	string cnames[7],lnames[110];
	{
#ifdef ANDROID
		stringstream file=RWstream(string(global_data_dir+"locales/"+loc+"/cnames.txt").c_str());
#else
		ifstream file(string(global_data_dir+"locales/"+loc+"/cnames.txt").c_str());
#endif
		for(int q=0; q<7; ++q)getline(file,cnames[q]);
#ifndef ANDROID
		file.close();
#endif
	}
	{
#ifdef ANDROID
		stringstream file=RWstream(string(global_data_dir+"locales/"+loc+"/lnames.txt").c_str());
#else
		ifstream file(string(global_data_dir+"locales/"+loc+"/lnames.txt").c_str());
#endif
		for(int q=0; q<110; ++q)getline(file,lnames[q]);
#ifndef ANDROID
		file.close();
#endif
	}
	while(1) {
		if(e.type==SDL_QUIT) {
			SDL_DestroyTexture(arrow);
			quit(1);
		}
		if(CLEAR(window,strings[22]) || Back())break;
		SDL_RenderDrawLine(ren,370*iface_zoom,30*iface_zoom,370*iface_zoom,400*iface_zoom);
		SDL_RenderDrawLine(ren,0,60*iface_zoom,370*iface_zoom,60*iface_zoom);
		FC_DrawAlign(def,ren,185*iface_zoom,35*iface_zoom,FC_ALIGN_CENTER,cnames[sh/11].c_str());
		{
			bool ok=(sh<66
#ifndef DEV
					 && profile.level/11>sh/11+1
#endif
					);
			showIMG(ar[0],arrow,FC_MakeRect(0,(sh>10)*30,30,30));
			showIMG(ar[1],arrow,FC_MakeRect(30,    ok*30,30,30));
		}
		for(int q=0; q<11; ++q) {
			SDL_Rect r= {int(20*iface_zoom),int(65*iface_zoom+q*30*iface_zoom),int(330*iface_zoom),int(30*iface_zoom)};
			FC_DrawButtonLeft(def,ren,r,lnames[sh/11*11+q].c_str());
			if(q==sh%11)SDL_RenderDrawRect(ren,&r);
		}

		SDL_Rect b= {int(385*iface_zoom),int(350*iface_zoom),int(150*iface_zoom),int(40*iface_zoom)};
		SDL_RenderDrawRect(ren,&b);
		FC_DrawButtonCenter(def,ren,b,strings[28].c_str());
		bool j=0;
		if(mouse.state) {
			if(in_rect(ar[0]) &&  sh>10) {
				sh-=11;
				mouse.wait();
				j=1;
			}
			if(in_rect(ar[1]) && sh<66) {
#ifndef DEV
				if(profile.level/11>sh/11+1)
#endif
				{
					sh+=11;
					mouse.wait();
					j=1;
				}
			}
		}
		for(int q=0; q<11; ++q) {
			SDL_Rect r= {int(20*iface_zoom),int(65*iface_zoom+q*30*iface_zoom),int(330*iface_zoom),int(30*iface_zoom)};
			if(in_rect(r) && mouse.state)sh=sh/11*11+q;
		}
		if(in_rect(b) && mouse.state) {
			mouse.wait();
			j=1;
			lid=lntolid(sh);
			open(string(global_data_dir+"levels/standart/"+lid+".lvl"));
			game();
			return;
		}
		SDL_RenderPresent(ren);
		if(!j)SDL_WaitEvent(&e);
		mouse.update();
	}
	SDL_DestroyTexture(arrow);
}
void settings() {
	SDL_Rect window= {0,0,550,400};
	RESIZE(&window,4);
	SDL_DisplayMode c;
	SDL_GetCurrentDisplayMode(0, &c);
	int sh=0;
	int w=SW,h=SH;
	SDL_Rect button[]= {
		{335,45, 80,30},
		{445,45, 80,30},
		{495,85,30,30},
		{495,125,30,30},
		{445,165,80,30},
		{264,205,261,30},
		{264,245,261,30},
		{495,285,30,30},
		{25,330,225,50},
		{300,330,225,50}
	};
	SDL_Point txt[]= {
		{25,50},
		{25,90},
		{25,130},
		{25,170},
		{25,210},
		{25,250},
		{25,290},
	};
	RESIZE(&button,40);
	RESIZE(&txt,   14);
	while(1) {
		if(CLEAR(window,strings[5]) || Back())break;
		for(int q=0; q<10; ++q) {
			SDL_RenderDrawRect(ren,&button[q]);
			switch(q) {
			case 0:
				FC_DrawButtonLeft(def,ren,button[0],"%d%s",w,(sh==0?"_":""));
				break;
			case 1:
				FC_DrawButtonLeft(def,ren,button[1],"%d%s",h,(sh==1?"_":""));
				break;
			case 2:
				if(fullscreen)   {
					SDL_Rect r= {button[2].x+3,button[2].y+3,button[2].w-6,button[2].h-6};
					SDL_RenderFillRect(ren,&r);
				}
				break;
			case 3:
				if(sb_on) {
					SDL_Rect r= {button[3].x+3,button[3].y+3,button[3].w-6,button[3].h-6};
					SDL_RenderFillRect(ren,&r);
				}
				break;
			case 4:
				FC_DrawButtonCenter(def,ren,button[4],loc.c_str());
				break;
			case 5: {
				SDL_Rect r= {button[q].x+3,button[q].y+3,int(sound_vol*2.0f*iface_zoom),button[q].h-6};
				SDL_RenderFillRect(ren,&r);
			}
			break;
			case 6: {
				SDL_Rect r= {button[q].x+3,button[q].y+3,int(music_vol*2.0f*iface_zoom),button[q].h-6};
				SDL_RenderFillRect(ren,&r);
			}
			break;
			case 7:
				if(darkost) {
					SDL_Rect r= {button[7].x+3,button[7].y+3,button[7].w-6,button[7].h-6};
					SDL_RenderFillRect(ren,&r);
				}
				break;
			case 8:
			case 9:
				FC_DrawButtonCenter(def,ren,button[q],strings[32+q].c_str());
				break;
			}
		}
		if(w>c.w)w=c.w;
		if(h>c.h)h=c.h;
		for(int q=0; q<7; ++q) {
			FC_Draw(def,ren,txt[q].x,txt[q].y,strings[((q<4)?43:69)+q].c_str());
		}
		SDL_RenderPresent(ren);

		SDL_WaitEvent(&e);
		mouse.update();

		if(sh==0)gin(&w);
		else if(sh==1)gin(&h);

		if(e.type==SDL_QUIT) {
			quit(1);
		} else if(e.type==SDL_MOUSEBUTTONDOWN || e.type==SDL_MOUSEMOTION) {
			if(e.type==SDL_MOUSEBUTTONDOWN) {
				for(int q=0; q<10; ++q) {
					if(in_rect(button[q]) && sh!=q) {
						if(q!=5 && q!=6)mouse.wait();
						sh=q;
					}
				}
				if(sh==4) {
					if(loc=="ru")loc="en";
					else if(loc=="en")loc="ru";
					sh=100;
				} else if(sh==9) {
					SW=w;
					SH=h;
					if(SW<640)SW=640;
					if(SH<480)SH=480;
					load_strings();
					save_settings();
#ifndef ANDROID
					quit(0);
					init("Dark Podval");
					CLEAR(window,"null");
#endif
					create_kvadrat();
					break;
				} else if(sh==2) {
#ifndef ANDROID
					fullscreen=!fullscreen;
					sh=100;
#endif
				} else if(sh==3) {
					sb_on=!sb_on;
					sh=100;
				} else if(sh==7) {
					darkost=!darkost;
					sh=100;
				}
			}
			if(sh==5) {
				int t=(mouse.x-button[sh].x)/2/iface_zoom;
				if(t<0)t=0;
				if(t>128)t=128;
				sound_vol=t;
			} else if(sh==6) {
				int t=(mouse.x-button[sh].x)/2/iface_zoom;
				if(t<0)t=0;
				if(t>128)t=128;
				music_vol=t;
			} else if(sh==8) {
				about();
			}
		}
	}
}
bool pause() {
	Mix_PauseMusic();
	SDL_Rect window= {0,0,250,300};
	RESIZE(&window,4);
	int time=SDL_GetTicks();
	bool ok=1;
	while(ok) {
		if(e.type==SDL_QUIT)quit(1);
		else if(e.type==SDL_MOUSEBUTTONDOWN) {
#if defined(ANDROID) && !defined(DEV)
			for(int q=0; q<4; ++q) {
				SDL_Rect r= {0,int(q*60*iface_zoom+30*iface_zoom),int(250*iface_zoom),int(42*iface_zoom)};
#else
			for(int q=0; q<5; ++q) {
				SDL_Rect r= {0,int(q*50*iface_zoom+30*iface_zoom),int(250*iface_zoom),int(42*iface_zoom)};
#endif
				if(in_rect(r)) {
					mouse.wait();
					switch(q) {
					case 1:
						ok=0;
						Mix_ResumeMusic();
						break;
					case 2: {
						string path=string((st?global_data_dir+"levels/standart/":save_data_dir+"levels/custom/")+lid+".lvl");
						open(path);
						Mix_HaltMusic();
						game_init(1);
						return 0;
					}
					break;
					case 3: {
						Mix_HaltMusic();
						return 1;
					}
					break;
					case 4: {
#if defined(ANDROID) && defined (DEV)
						console();
						return 0;
#else
						if(alert()) {
							Mix_HaltMusic();
							quit(1);
						}
#endif
					}
					break;
					}
				}
			}
		} else if(Back()) {
			ok=0;
			Mix_ResumeMusic();
		}
		CLEAR(window,"");
#if defined(ANDROID) && !defined (DEV)
		for(int q=0; q<4; ++q) {
			SDL_Rect r= {0,int(q*60*iface_zoom+30*iface_zoom),int(250*iface_zoom),int(42*iface_zoom)};
#else
		for(int q=0; q<5; ++q) {
			SDL_Rect r= {0,int(q*50*iface_zoom+30*iface_zoom),int(250*iface_zoom),int(42*iface_zoom)};
#endif
#if defined(ANDROID) && defined (DEV)
			FC_DrawButtonCenter((q==0)?menu:def,ren,r,strings[(q==4)?65:47+q].c_str());
#else
			FC_DrawButtonCenter((q==0)?menu:def,ren,r,strings[47+q].c_str());
#endif
		}
		SDL_RenderPresent(ren);
		if(ok)SDL_WaitEvent(&e);
		mouse.update();
	}
	timer_pause+=(SDL_GetTicks()-time);
	return 0;
}
bool end(bool boss,bool die,bool b3) {
	Mix_HaltMusic();
	int tm=(timer-ltime)/100;
	SDL_Rect window= {0,0,400,300};
	SDL_Rect button[3]= {{b3?25:66,175,100,100},{b3?150:232,175,100,100},{275,175,100,100}};
	SDL_Point point[2]= {{200,25},{25,75}};
	RESIZE(&window,4);
	RESIZE(button,12);
	RESIZE(point,4);
	while(1) {
		if(e.type==SDL_QUIT)quit(1);
		else if(e.type==SDL_MOUSEBUTTONDOWN) {
			for(int q=0; q<2+b3; ++q) {
				if(in_rect(button[q])) {
					mouse.wait();
					switch(q) {
					case 0: {
						return 1;
					}
					break;
					case 1: {
						string path=string((st?global_data_dir+"levels/standart/":save_data_dir+"levels/custom/")+lid+".lvl");
						open(path);
						game_init(0);
						return 0;
					}
					break;
					case 2: {
						if(boss)lid=75;
						else lid=postlid(lid);
						string path=string(global_data_dir+"levels/standart/")+lid+(string)".lvl";
						open(path);
						game_init(0);
						return 0;
					}
					break;
					}
				}
			}
		}
		if(Back())return 1;
		CLEAR(window,"");
		if(die) FC_DrawAlign(def,ren,point[0].x,point[0].y,FC_ALIGN_CENTER,strings[52].c_str());
		else    FC_DrawAlign(def,ren,point[0].x,point[0].y,FC_ALIGN_CENTER,"%s %s %s",strings[53].c_str(),lid.c_str(),strings[54].c_str());
		FC_Draw(def,ren,point[1].x,point[1].y,"%s %d %s %d.%d %s\n%s: %d %s",
				strings[55].c_str(),
				tm/600,         strings[26].c_str(),
				tm/10%60,tm%10, strings[27].c_str(),
				strings[23].c_str(),       strings[24].c_str());
		for(int q=0; q<2+b3; ++q) {
			SDL_RenderDrawRect(ren,&button[q]);
			FC_DrawButtonCenter(def,ren,button[q],strings[56+q].c_str());
		}
		SDL_RenderPresent(ren);
		SDL_WaitEvent(&e);
		mouse.update();
	}
	return 0;
}
bool inputname(string *name) {
	SDL_Rect window= {0,0,400,120};
	SDL_Rect input[2]= {{10,40,380,30},
		{10,80,380,30}
	};
	RESIZE(&window,4);
	RESIZE(input,8);
	string backup=*name;
	SDL_StartTextInput();
	while(1) {
		if(e.type==SDL_QUIT) {
			quit(1);
		} else if(e.type==SDL_MOUSEBUTTONDOWN) {
			if(in_rect(input[1]) && name->size()>0)break;
		}
		gin(name);
		if(CLEAR(window,strings[59]) || Back()) {
			*name=backup;
			SDL_StopTextInput();
			break;
		}
		for(int q=0; q<2; ++q) {
			SDL_RenderDrawRect(ren,&input[q]);
			if(q==1) {
				FC_DrawButtonCenter(def,ren,input[q],strings[13].c_str());
			} else {
				FC_DrawButtonLeft(def,ren,input[q],string(*name+"_").c_str());
			}
		}
		SDL_RenderPresent(ren);
		SDL_WaitEvent(&e);
		mouse.update();
	}
	SDL_StopTextInput();
	return 0;
}
bool profiles() {
	SDL_Rect window= {0,0,550,400};
	SDL_Rect button[3]= {{25,360,150,30},{200,360,150,30},{375,360,150,30}};
	RESIZE(&window,4);
	RESIZE(button,12);
	int sh=profn;
	Profile profs[5];
	for(int q=0; q<5; ++q)profs[q].load(q);
	while(1) {
		if(e.type==SDL_MOUSEBUTTONDOWN) {
			for(int q=0; q<3; ++q) {
				if(in_rect(button[q])) {
					mouse.wait();
					switch(q) {
					case 0: {
						if(alert()) {
							profs[sh].clear(sh);
							profs[sh].save(sh);
							if(sh==profn)profile.load(sh);
						}
					}
					break;
					case 1: {
						inputname(&profs[sh].name);
						profs[sh].save(sh);
						profile.load(sh);
					}
					break;
					case 2: {
						profn=sh;
						profile.load(sh);
						save_settings();
						return 0;
					}
					break;
					}
				}
			}
			for(int q=0; q<5; ++q) {
				SDL_Rect r= {int(15*iface_zoom),int(65*iface_zoom+q*55*iface_zoom),int(520*iface_zoom),int(55*iface_zoom)};
				if(in_rect(r))sh=q;
			}
		} else if(e.type==SDL_QUIT) {
			quit(1);
		}
		if(CLEAR(window,strings[60]) || Back())break;
		SDL_RenderDrawLine(ren,0,350*iface_zoom,window.w,350*iface_zoom);
		SDL_RenderDrawLine(ren,0,60*iface_zoom,window.w,60*iface_zoom);
		FC_Draw(def,ren,25*iface_zoom,35*iface_zoom,strings[61].c_str());
		for(int q=0; q<5; ++q) {
			int j55=55*iface_zoom;
			int j80=80*iface_zoom;
			FC_Draw(def,ren, 25*iface_zoom,j80+q*j55,profs[q].name.c_str());
			FC_Draw(def,ren,291*iface_zoom,j80+q*j55,"%d");
			FC_Draw(def,ren,457*iface_zoom,j80+q*j55,lntolid(profs[q].level).c_str());
			SDL_Rect r= {int(15*iface_zoom),int(65*iface_zoom+q*j55),int(520*iface_zoom),j55};
			if(q==sh)SDL_RenderDrawRect(ren,&r);
		}
		for(int q=0; q<3; ++q) {
			SDL_RenderDrawRect(ren,&button[q]);
			FC_DrawButtonCenter(def,ren,button[q],strings[62+q].c_str());
		}
		SDL_RenderPresent(ren);
		SDL_WaitEvent(&e);
		mouse.update();
	}
	return 0;
}

void about() {
	SDL_Rect window= {0,0,550,400};
	RESIZE(&window,4);
	string str;
#ifdef ANDROID
	stringstream file=RWstream(string(global_data_dir+"locales/"+loc+"/about.txt").c_str());
#else
	ifstream file(global_data_dir+"locales/"+loc+"/about.txt");
#endif
	do {
		string buf;
		getline(file,buf);
		str+=buf;
		str+="\n";
	} while(!file.eof());
#ifndef ANDROID
	file.close();
#endif
	Scrollbar scroll;
	scroll.set(530,30,370);
	scroll.update(1);
	while(1) {
		if(e.type==SDL_QUIT) {
			quit(1);
		}
		if(CLEAR(window,strings[40]) || Back())break;
		int j30=30*iface_zoom;
		SDL_Rect r= {0,j30,window.w,window.h-j30};
		SDL_RenderSetClipRect(ren,&r);
		FC_DrawColumn(def,ren,20*iface_zoom,40*iface_zoom-scroll.getp()*3,500*iface_zoom,str.c_str());
		scroll.update(1);
		SDL_RenderSetClipRect(ren,0);
		SDL_RenderPresent(ren);
		SDL_WaitEvent(&e);
		mouse.update();
	}
	return;
}


void destroy_subt() {
	questions.clear();
	replies.clear();
	buf="";
	qbuf="";
	txt="";
}
bool showimage(string path) {
	int time=SDL_GetTicks();
	SDL_Texture* image=load(path.c_str());
	int xt,yt;
	SDL_QueryTexture(image,0,0,&xt,&yt);
	while(e.type!=SDL_MOUSEBUTTONDOWN && !key[SDL_SCANCODE_ESCAPE]) {
		SDL_WaitEvent(&e);
		if(e.type==SDL_QUIT)return 1;
		showIMG(SW/2,SH/2,xt,yt,image,1);
		SDL_RenderPresent(ren);
	}
	SDL_DestroyTexture(image);
#ifdef ANDROID
	sensor=0;
#endif
	mouse.wait();
	timer_pause+=(SDL_GetTicks()-time);
	return 0;
}
bool nadpis(string lid, int x,int y) {
	int c=0;
	bool ok=1;
	for(int yp=0; yp<h && ok; yp++) {
		for(int xp=0; xp<w && ok; xp++) {
			if(level[xp][yp]==40 || level[xp][yp]==41 || level[xp][yp]==42)c++;
			if(xp==x && yp==y)ok=0;
		}
	}
	string path=global_data_dir+"locales/"+loc+"/images/";
	path+=lid;
	path+='-';
	path+=(char)(c/10%10+'0');
	path+=(char)(c%10+'0');
	path+=".jpg";
	return showimage(path);
}
void subtitres(bool intro) {
	int c=0;
	bool b=0;
	bool fon=1;
	SDL_Color cl=black;
	if(txt[txt.size()-1]!=' ')txt+="$$$$ ";
	for(unsigned q=0; q<txt.size(); ++q) {
		if(txt[q]=='$' || q==0) {
			if(c++==(timer-timer_sbt)/delay) {
				int d=txt.find('$',q+1);
				string txt2;
				txt2.assign(txt,q,d-q);
				if(txt2[0]=='$')txt2.erase(txt2.begin());
				if(txt2.size())buf=txt2;
			}
		}
	}
	string s="";
	if(buf.size()>1 && buf[0]=='\\') {
		switch(buf[1]) {
		case 'b':
			b    =1;
			break;
		case 'r':
			cl   =red;
			break;
		case 'g':
			cl   =green;
			break;
		case 'y':
			cl   =yellow;
			break;
		case 'w':
			cl   =white;
			fon=0;
			break;
		case 'v':
			cl   =blue;
			break;
		}
		s+="\\";
		s+=buf[1];
		buf.erase(buf.begin(),buf.begin()+2);
	}
	if(buf!="" && buf!=" ") {
#ifdef ANDROID
		int w,x;
		if(intro) {
			w=SW/8*6;
			x=SW/8;
		} else {
			w=SW-380*iface_zoom;
			x=260*iface_zoom;
		}
#else
		int w=SW/8*6;
		int x=SW/8;
#endif
		int h=FC_GetColumnHeight(b?bold:text,w,buf.c_str());
		SDL_Rect r= {x,SH-50-h,w,h};
		if(fon) {
			SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(ren,255,255,255,100);
			SDL_RenderFillRect(ren,&r);
		}
		FC_DrawColumnColor(b?bold:text,ren,x,SH-50-h,w,cl,buf.c_str());
		SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_NONE);
	}
	buf=s+buf;
	if(qbuf!="" && qbuf!=" "&&!intro) {
		int y=50*iface_zoom;
#ifdef ANDROID
		int w=SW-230*iface_zoom;
		int x=115*iface_zoom;
#else
		int w=SW/8*6;
		int x=SW/8;
#endif
		int h=FC_GetColumnHeight(text,w,qbuf.c_str());
		SDL_Rect r= {x,y,w,h};
		SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(ren,255,255,255,100);
		SDL_RenderFillRect(ren,&r);
		FC_DrawColumnColor(text,ren,x,y,w,black,qbuf.c_str());
		SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_NONE);
	}
}
void intro() {
	int c=4;
	destroy_subt();
#ifdef ANDROID
	stringstream file=RWstream(string(global_data_dir+"locales/"+loc+"/intro.txt").c_str());
#else
	ifstream file(string(global_data_dir+"locales/"+loc+"/intro.txt").c_str());
#endif
	getline(file,txt);
#ifndef ANDROID
	file.close();
#endif
	for(unsigned q=0; q<txt.size(); ++q)if(txt[q]=='$')c++;
	timer_sbt=timer;
	int th=timer;
	while(th+c*delay>timer) {
		SDL_PollEvent(&e);
		if(e.type==SDL_QUIT)quit(1);
		if(e.type==SDL_KEYDOWN)break;
		SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_RenderClear(ren);
		subtitres(1);
		SDL_RenderPresent(ren);
	}
}
void set_camera(unsigned short x,unsigned short y,bool editor) {
	if(!editor) {
		cx=(-x-32)*zoom+SW/2;
		cy=(-y-32)*zoom+SH/2;
	}
	if(w*zoom*64<SW)cx=(SW-w*zoom*64)/2;
	else {
		if(cx>0)cx=0;
		if(cx<-(w*64*zoom-SW))cx=-(w*64*zoom-SW);
	}
	if(h*zoom*64<SH)cy=(SH-h*zoom*64)/2;
	else {
		if(cy>50*(editor?1:iface_zoom))cy=50*(editor?1:iface_zoom);
		if(cy<-(h*64*zoom-SH))cy=-(h*64*zoom-SH);
	}
}
void Player::go() {
	if(dietimer<=0) {
		if(x%64==0 && y%64==0) {
			uint8_t k[]= {SDL_SCANCODE_W,SDL_SCANCODE_D,SDL_SCANCODE_S,SDL_SCANCODE_A,SDL_SCANCODE_UP,SDL_SCANCODE_RIGHT,SDL_SCANCODE_DOWN,SDL_SCANCODE_LEFT};
			bool ok=0;
			for(int q=0; q<8; ++q) {
				if((key[k[q]]
#ifdef ANDROID
						|| (sensor==q+2 && q < 4)
#endif
				   ) && !ok) {
					n=q%4;
					if(can_go(&push,n,1)) {
						sx=x/64;
						sy=y/64;
						ok=1;
						timerr=timer;
						move(1,n);
					}
				}
			}
		} else {
			float block=(timer-timerr)/20.0*speed+1;
			switch(n) {
			case 0:
				y=sy*64-block;
				break;
			case 1:
				x=sx*64+block;
				break;
			case 2:
				y=sy*64+block;
				break;
			case 3:
				x=sx*64-block;
				break;
			}
			if(abs(sx*64-x)>=64 || abs(sy*64-y)>=64) {
				x=sx*64;
				y=sy*64;
				move(64,n);
			}
		}
	}
	clear();
}
string command(string command) {
	string result;
	stringstream str;
	str<<command;
	str>>command;
	if(command=="nofog") {
		for(int x=0; x<w; ++x) {
			for(int y=0; y<h; ++y) {
				light[x][y]=255;
			}
		}
		result="OK";
	} else if(command=="fog") {
		for(int x=0; x<w; ++x) {
			for(int y=0; y<h; ++y) {
				light[x][y]=0;
			}
		}
		result="OK";
	} else if(command=="speed") {
		int speed=0;
		str>>speed;
		if(speed>255)result="speed can`t be > 255";
		else if(speed==0)result="speed can`t be 0";
		else if(speed<0)result="speed can`t be < 0";
		else {
			result="speed changed from "+to_string(player->speed)+" to "+to_string(speed);
			player->speed=speed;
		}
	} else if(command=="noclip") {
		player->noclip=!player->noclip;
		result="noclip "+string(player->noclip?"ON":"OFF");
	} else if(command=="health") {
		player->infhealth=!player->infhealth;
		result="infinity health "+string(player->infhealth?"ON":"OFF");
	} else if(command=="kill") {
		if(gg.infhealth)result="You have infinity health YET!";
		else {
			result="You are suicidal!";
			gg.kill();
		}
	} else if(command=="setblock") {
		int x=0,y=0,b=0;
		str>>x>>y;
		if(x<0)  result="X can`t < 0";
		else if(x>=w) result="X can`t > level width";
		else if(y<0)  result="X can`t < 0";
		else if(y>=h) result="X can`t > level height";
		else if(b<0)  result="Block can`t < 0";
		else if(b>255)result="Block can`t > 255";
		else {
			result="OK";
			level[x][y]=b;
		}
	} else if(command=="skip") {
		for(int x=0; x<w; ++x) {
			for(int y=0; y<h; ++y) {
				if(level[x][y]==26) {
					result="OK";
					player->x=x*64;
					player->y=y*64;
					return result;
				}
			}
		}
		result="Level has not exit";
	} else if(command=="zoom") {
		float z;
		str>>z;
		result="OK";
		zoom=z;
	} else if(command=="darkost") {
		bool b;
		str>>b;
		result="OK";
		darkost=b&&1;
		create_kvadrat();
	}
	return result;
}
void load_subtitles() {
	timer_sbt=timer;
	if(st) {
#ifdef ANDROID
		stringstream file=RWstream(string(global_data_dir+"locales/"+loc+"/lnames.txt").c_str());
#else
		ifstream file(string(global_data_dir+"locales/"+loc+"/lnames.txt").c_str());
#endif
		int k=0;
		string str;
		while(k<=lidtoln(lid)) {
			getline(file,str);
			k++;
		}
		if(str[str.size()-1]=='\r')str.pop_back();
#ifndef ANDROID
		file.close();
#endif
		txt=string(strings[67])+" "+lid+"\n\""+str+"\"";
	} else txt=string(strings[67])+" "+lid;
	int max_question=0;
	int max_replies=0;
	for(unsigned q=0; q<gate.size(); ++q) {
		if(gate[q].type==35 && gate[q].value>max_question)max_question=gate[q].value+1;
		if(gate[q].type==25 && gate[q].value>max_replies)max_replies=gate[q].value+1;
	}
	questions.resize(max_question);
	replies.resize(max_replies);
	for(unsigned q=0; q<gate.size(); ++q) {
		if(gate[q].type==35) {
			questions[gate[q].value]=new string;
#ifdef ANDROID
			stringstream file=RWstream(string(global_data_dir+"locales/"+loc+"/questions.txt").c_str());
#else
			ifstream file(string(global_data_dir+"locales/"+loc+"/questions.txt").c_str());
#endif
			int k=0;

			while(k!=gate[q].value) {
				getline(file,*questions[gate[q].value]);
				k++;
			}
#ifndef ANDROID
			file.close();
#endif
		} else if(gate[q].type==25) {
			replies[gate[q].value]=new string;
#ifdef ANDROID
			stringstream file=RWstream(string(global_data_dir+"locales/"+loc+"/replies.txt").c_str());
#else
			ifstream file(string(global_data_dir+"locales/"+loc+"/replies.txt").c_str());
#endif
			int k=0;

			while(k!=gate[q].value) {
				getline(file,*replies[gate[q].value]);
				k++;
			}
#ifndef ANDROID
			file.close();
#endif
		}
	}
}
void Provodnik::action() {
	basic_action();
	if(((key[SDL_SCANCODE_Z])
#ifdef ANDROID
			|| sensor==8
#endif
	   ) && x%64==0 && y%64==0 && level[x/64][y/64]==0) {
		level[x/64][y/64]=212+n;
		delete this;
		player=&gg;
	}
	if(((key[SDL_SCANCODE_E])
#ifdef ANDROID
			|| sensor==6
#endif
	   ) && x%64==0 && y%64==0) {
		for(int xd=-1; xd<=1; ++xd) {
			for(int yd=-1; yd<=1; ++yd) {
				if((abs(xd)+abs(yd)==1) || (xd==0 && yd==0)) {
					int xp=x/64+xd,
						yp=y/64+yd;
					switch(level[xp][yp]) {
					case 212:
					case 213:
					case 214:
					case 215:
						level[x/64][y/64]=n+212;

						n=level[xp][yp]-212;
						level[xp][yp]=0;

						x=xp*64;
						y=yp*64;
						return;
						break;
					}
				}
			}
		}
	}
}
void Player::action() {
	basic_action();
	if(((key[SDL_SCANCODE_E])
#ifdef ANDROID
			|| sensor==6
#endif
	   ) && x%64==0 && y%64==0) {
		for(int xd=-1; xd<=1; ++xd) {
			for(int yd=-1; yd<=1; ++yd) {
				if((abs(xd)+abs(yd)==1) || (xd==0 && yd==0)) {
					int xp=x/64+xd,
						yp=y/64+yd;
					switch(level[xp][yp]) {
					case 212:
					case 213:
					case 214:
					case 215:
						player=new Provodnik;
						player->load_texture();
						player->n=level[xp][yp]-212;
						player->x=xp*64;
						player->y=yp*64;
						player->speed=5;
						level[xp][yp]=0;
						return;
						break;
					}
				}
			}
		}
	}
	if(((key[SDL_SCANCODE_Z])
#ifdef ANDROID
			|| sensor==8
#endif
	   ) && x%64==0 && y%64==0) {
		bool ok=1;
		for(int xp=-1; xp<=1; ++xp) {
			for(int yp=-1; yp<=1; ++yp) {
				if((abs(xp)+abs(yp)==1) || (xp==0 && yp==0)) {
					if(ok && !bring) {
						if(level[x/64+xp][y/64+yp]==79) {
							bring=1;
							ok=0;
						} else if(level[x/64+xp][y/64+yp]==205) {
							bring=3;
							ok=0;
						}
						if(ok==0) {
							level[x/64+xp][y/64+yp]=0;
						}
					}
				}
			}
		}
		if(ok) {
			uint8_t level2[255][255];
			memcpy(level2,level,sizeof(level2));
			for(unsigned q=0; q<rock.size(); ++q)level2[rock[q].x/64][rock[q].y/64]=1;
			uint8_t xp=x/64+(n==1)-(n==3);
			uint8_t yp=y/64+(n==2)-(n==0);
			if(ok && bring && level2[xp][yp]==0) {
				if(bring==1)level[xp][yp]=79;
				else if(bring==3)level[xp][yp]=205;
				bring=0;
				ok=0;
			} else if(ok && bring && level2[x/64][y/64]==0) {
				if(bring==1)level[x/64][y/64]=79;
				else if(bring==3)level[x/64][y/64]=205;
				bring=0;
				ok=0;
			}
		}
	}
}
void Player::basic_action() {
	if(((key[SDL_SCANCODE_E])
#ifdef ANDROID
			|| sensor==6
#endif
	   ) && x%64==0 && y%64==0) {
		if(harpoon && level[x/64][y/64]==53 && can_go(&push,n,0)) {
			harpoon=false;
			move(1,n);
			timerr=timer;
			sx=x/64;
			sy=y/64;
		}
		for(int xd=-1; xd<=1; ++xd) {
			for(int yd=-1; yd<=1; ++yd) {
				if((abs(xd)+abs(yd)==1) || (xd==0 && yd==0)) {
					int xp=x/64+xd,
						yp=y/64+yd;
					switch(level[xp][yp]) {
					case 40:
					case 41:
					case 42:
						nadpis(lid,xp,yp);
						break;
					case 73:
						level[xp][yp]=74;
						break;
					case 74:
						level[xp][yp]=73;
						break;
					case 89:
						if(lrd)delete lrd;
						lrd=new LRD(xp*64,yp*64);
						level[xp][yp]=0;
						return;
						break;
					case 90:
						if(lrd)delete lrd;
						lrd=new LRD(xp*64,yp*64);
						level[xp][yp]=14;
						return;
						break;
					case 148:
						if(code(password(xp,yp)))
							level[xp][yp]=170;
						break;
					case 158:
						level[xp][yp]=175;//NO BREAK!
					case 175:
					case 176:
					case 177:
					case 178:
					case 179:
					case 180: {
						int passwd=password(xp,yp);
						if(passwd>=1000) {
							txt="\\g"+strings[76]+": "+to_string(passwd);
							timer_sbt=timer;
						}
					}
					break;
					case 203:
						if(bring==3) {
							bring=0;
							level[xp][yp]=204;
						}

						break;
					case 204:
						if(bring==0) {
							bring=3;
							level[xp][yp]=203;
						}

						break;
					case 206:
						level[xp][yp]=0;
						profile.save(profn);
						break;

					}
				}
			}
		}
		bool ok=0;
		for(unsigned q=0; q<rock.size(); ++q) {
			if(abs(rock[q].x-x)/64+abs(rock[q].y-y)/64==1 && !ok) {
				if(rock[q].type%9==2 && bring==1) {
					rock[q].type++;
					bring=0;
					ok=1;
				} else if(rock[q].type%9==3) {
					rock[q].type++;
				}
			}
		}
	}
	if(((key[SDL_SCANCODE_R])
#ifdef ANDROID
			|| sensor==7
#endif
	   ) && x%64==0 && y%64==0) {
		for(unsigned q=0; q<rock.size(); ++q) {
			if(abs(rock[q].x-x)/64+abs(rock[q].y-y)/64==1 && rock[q].type>1) {
				if(rock[q].type>=29)rock[q].type-=27;
				else rock[q].type+=9;
			}
		}
	}
}

bool code(unsigned short c) {
	int tw,th;
	SDL_Texture *lock  =load(string(global_data_dir+"textures/lock.png").c_str());
	SDL_Texture *digits=load(string(global_data_dir+"textures/digits.png").c_str());
	SDL_QueryTexture(lock,0,0,&tw,&th);
	uint8_t ok=0;
	int time=SDL_GetTicks();
	int8_t d[4]= {-1,-1,-1,-1};
	SDL_Rect window= {SW/2-tw/2,SH/2-th/2,tw,th};
	SDL_Rect elem[]= {
		{124,357,38,38},
		{57, 154,38,38},
		{124,154,38,38},
		{191,154,38,38},
		{57, 221,38,38},
		{124,221,38,38},
		{191,221,38,38},
		{57, 289,38,38},
		{124,289,38,38},
		{191,289,38,38},
		{57, 357,38,38},
		{191,357,38,38},
		{76, 51,32,52},
		{118,51,32,52},
		{159,51,32,52},
		{201,51,32,52},
	};
	RESIZE(&window,4);
	RESIZE(&elem,64);
	auto normal=[&]()->bool{
		for(int q=0; q<4; ++q) {
			if(d[q]<0||d[q]>9) {
				return 0;
			}
		}
		return 1;
	};
	auto success=[&]() {
		d[0]=0;
		d[1]=12;
		d[2]=10;
		d[3]=13;
	};
	auto error=[&]() {
		d[0]=10;
		d[1]=11;
		d[2]=11;
		d[3]=-1;
	};
	auto press=[&](int key) {
		if(key<10) {
			if(!normal()) {
				for(int w=0; w<4; ++w) if(d[w]>9)d[w]=-1;
				for(int w=0; w<4; ++w) if(w!=3)  d[w]=d[w+1];
				d[3]=key;
			}
		} else if(key==10) {
			for(int w=0; w<4; ++w)d[w]=-1;
		} else if(normal()) {
			if(d[0]==0&&
					d[1]==12&&
					d[2]==10&&
					d[3]==13)return;
			int result=0;
			for(int w=0; w<4; ++w) {
				result*=10;
				result+=d[w];
			}
			if(result==c) {
				ok=3;
				success();
			} else error();
		} else error();
	};
	while(ok==0||ok==3) {
		SDL_WaitEvent(&e);
		if(e.type==SDL_QUIT)ok=2;
		else if(e.type==SDL_MOUSEBUTTONDOWN) {
			mouse.wait();
			if(in_rect({0,0,window.w,window.h})&&ok!=3) {
				for(int q=0; q<12; ++q) {
					if(in_rect(elem[q])) {
						press(q);
					}
				}
			} else ok=(ok==3)?4:1;
		} else if(Back())ok=(ok==3)?4:1;
		else if(e.type==SDL_KEYDOWN) {
			switch(e.key.keysym.scancode) {
			case SDL_SCANCODE_0:
			case SDL_SCANCODE_KP_0:
				press(0);
				break;
			case SDL_SCANCODE_1:
			case SDL_SCANCODE_KP_1:
				press(1);
				break;
			case SDL_SCANCODE_2:
			case SDL_SCANCODE_KP_2:
				press(2);
				break;
			case SDL_SCANCODE_3:
			case SDL_SCANCODE_KP_3:
				press(3);
				break;
			case SDL_SCANCODE_4:
			case SDL_SCANCODE_KP_4:
				press(4);
				break;
			case SDL_SCANCODE_5:
			case SDL_SCANCODE_KP_5:
				press(5);
				break;
			case SDL_SCANCODE_6:
			case SDL_SCANCODE_KP_6:
				press(6);
				break;
			case SDL_SCANCODE_7:
			case SDL_SCANCODE_KP_7:
				press(7);
				break;
			case SDL_SCANCODE_8:
			case SDL_SCANCODE_KP_8:
				press(8);
				break;
			case SDL_SCANCODE_9:
			case SDL_SCANCODE_KP_9:
				press(9);
				break;
			case SDL_SCANCODE_C:
			case SDL_SCANCODE_KP_COMMA:
			case SDL_SCANCODE_DELETE:
			case SDL_SCANCODE_BACKSPACE:
				press(10);
				break;
			case SDL_SCANCODE_RETURN:
			case SDL_SCANCODE_KP_ENTER:
				press(11);
				break;
			default:
				break;
			}
		}
		if(CLEAR(window,"") || Back())break;
		SDL_RenderCopy(ren,lock,0,0);
		for(int q=0; q<4; ++q) {
			if(d[q]!=-1) {
				SDL_Rect r= {d[q]*32,0,32,52};
				SDL_RenderCopy(ren,digits,&r,&elem[q+12]);
			}
		}
		SDL_RenderPresent(ren);
	}
	SDL_DestroyTexture(lock);
	SDL_DestroyTexture(digits);
	SDL_RenderSetViewport(ren,0);
	if(ok==2)quit(1);
	timer_pause+=(SDL_GetTicks()-time);
	return (ok==4);
}
void load_passwords() {
	int count=0;
	for(unsigned q=0; q<wire.size(); ++q) {
		if(is_terminal(wire[q].x1,wire[q].y1)&&is_password_door(wire[q].x2,wire[q].y2))++count;
	}
	passwords.resize(count);
	for(int q=0; q<count; ++q) {
		passwords[q]=1000+rand()%9000;
	}
}
unsigned short password(uint8_t x,uint8_t y) {
	int count=0;
	for(unsigned q=0; q<wire.size(); ++q) {
		if(is_password_door(x,y)&&wire[q].x2==x&&wire[q].y2==y&&is_terminal(wire[q].x1,wire[q].y1)) {
			return passwords[count];
		}
		if(is_terminal(x,y)&&wire[q].x1==x&&wire[q].y1==y&&is_password_door(wire[q].x2,wire[q].y2)) {
			return passwords[count];
		}
		if(is_terminal(wire[q].x1,wire[q].y1)&&is_password_door(wire[q].x2,wire[q].y2))++count;
	}
	return 123;
}
bool change_gate() {
	mouse.wait();
	int x,y;
	SDL_QueryTexture(gates_tex,0,0,&x,&y);
	SDL_SetRenderDrawColor(ren,0,128,0,255);
	SDL_RenderClear(ren);
	showIMG(0,0,x,y,gates_tex);
	SDL_RenderPresent(ren);
	while(!mouse.state) {
		SDL_WaitEvent(&e);
		mouse.update();
		if(e.type==SDL_QUIT)return 0;
	}
	ch_gt=(mouse.x/64+mouse.y/64*8);
	mouse.wait();
	return 1;
}
bool change_block() {
	mouse.wait();
	vector<uint8_t> blocks;
	{
#ifdef DEV
		string path=global_data_dir+"config/blocks-dev.txt";
#else
		string path=global_data_dir+"config/blocks.txt";
#endif
#ifdef ANDROID
		stringstream file=RWstream(path.c_str());
#else
		ifstream file(path.c_str());
#endif
		while(!file.eof()) {
			int c;
			file>>c;
			if(blocks.size()>0&&c==blocks[blocks.size()-1])break;
			blocks.push_back(c);
		}
#ifndef ANDROID
		file.close();
#endif
	}
	int wc=SW/64;
	SDL_SetRenderDrawColor(ren,0,128,0,255);
	SDL_RenderClear(ren);
	for(unsigned q=0; q<blocks.size(); ++q) {
		showIMG(q%wc*64,q/wc*64,64,64,textures, {(blocks[q]-1)%16*64,(blocks[q]-1)/16*64,64,64});
	}
	SDL_RenderPresent(ren);
	while(!mouse.state) {
		SDL_WaitEvent(&e);
		mouse.update();
		if(e.type==SDL_QUIT)return 0;
	}
	ch_bl=blocks[mouse.x/64+mouse.y/64*wc];
	mouse.wait();
	return 1;
}

void move(Select &sl,int dx,int dy) {
	int w1=sl.x2-sl.x1;
	int h1=sl.y2-sl.y1;
	uint8_t **level2=new uint8_t*[w1];
	for(int q=0; q<w1; q++)level2[q]=new uint8_t[h1];
	for(int x=0; x<w1; x++) {
		for(int y=0; y<h1; y++) {
			level2[x][y]=level[x+sl.x1][y+sl.y1];
			level[sl.x1+x][sl.y1+y]=0;
		}
	}
	for(int x=0; x<w1; x++) {
		for(int y=0; y<h1; y++) {
			int xp=x+sl.x1+dx;
			int yp=y+sl.y1+dy;
			if(xp>=0&&yp>=0&&xp<w&&yp<h)level[xp][yp]=level2[x][y];
		}
	}
	for(int q=0; q<gate.size(); q++) {
		if(!in_rect(0,0,w,h,gate[q].x+dx,gate[q].y+dy)) {
			gate.erase(gate.begin()+q);
			continue;
		}
		if(in_rect(sl.x1,sl.y1,w1,h1,gate[q].x,gate[q].y)) {
			gate[q].x+=dx;
			gate[q].y+=dy;
		}
	}
	for(int q=0; q<wire.size(); q++) {
		if(!in_rect(0,0,w,h,wire[q].x1+dx,wire[q].y1+dy)||
				!in_rect(0,0,w,h,wire[q].x2+dx,wire[q].y2+dy)) {
			wire.erase(wire.begin()+q);
			continue;
		}
		if(in_rect(sl.x1,sl.y1,w1,h1,wire[q].x1,wire[q].y1)) {
			wire[q].x1+=dx;
			wire[q].y1+=dy;
		}
		if(in_rect(sl.x1,sl.y1,w1,h1,wire[q].x2,wire[q].y2)) {
			wire[q].x2+=dx;
			wire[q].y2+=dy;
		}
	}
	sl.x1=max(dx+sl.x1,0);
	sl.y1=max(dy+sl.y1,0);
	sl.x2=min(dx+sl.x2,(int)w);
	sl.y2=min(dy+sl.y2,(int)h);
	for(int q=0; q<(sl.x2-sl.y2); q++)delete[] level2[q];
	delete[] level2;
	hs.push_back({});
}
void copy(Select &sl,int dx,int dy) {
	int w1=sl.x2-sl.x1;
	int h1=sl.y2-sl.y1;
	vector<vector<uint8_t>> level2 (w1, vector<uint8_t> (h1,0));
	for(int x=0; x<w1; x++) {
		for(int y=0; y<h1; y++) {
			level2[x][y]=level[x+sl.x1][y+sl.y1];
		}
	}
	for(int x=0; x<w1; x++) {
		for(int y=0; y<h1; y++) {
			int xp=x+sl.x1+dx;
			int yp=y+sl.y1+dy;
			if(xp>=0&&yp>=0&&xp<w&&yp<h)level[xp][yp]=level2[x][y];
		}
	}
	for(int q=0; q<gate.size(); q++) {
		if(!in_rect(0,0,w,h,gate[q].x+dx,gate[q].y+dy)) {
			continue;
		}
		if(in_rect(sl.x1,sl.y1,w1,h1,gate[q].x,gate[q].y)) {
			gate.insert(gate.begin(),Gate(gate[q].x+dx,gate[q].y+dy,gate[q].type));
			for(int e=1; e<gate.size(); e++) {
				if(gate[0].x==gate[e].x&&gate[0].y==gate[e].y) {
					gate.erase(gate.begin());
					q--;
					break;
				}
			}
			++q;
		}
	}
	for(int q=0; q<wire.size(); q++) {
		if(!in_rect(0,0,w,h,wire[q].x1+dx,wire[q].y1+dy)||
				!in_rect(0,0,w,h,wire[q].x2+dx,wire[q].y2+dy)) {
			continue;
		}
		bool ok=0;
		int x1=wire[q].x1;
		int y1=wire[q].y1;
		int x2=wire[q].x2;
		int y2=wire[q].y2;

		if(in_rect(sl.x1,sl.y1,w1,h1,wire[q].x1,wire[q].y1)) {
			ok=1;
			x1+=dx;
			y1+=dy;
		}
		if(in_rect(sl.x1,sl.y1,w1,h1,wire[q].x2,wire[q].y2)) {
			ok=1;
			x2+=dx;
			y2+=dy;
		}
		if(ok) {
			wire.insert(wire.begin(),Wire(x1,y1,x2,y2));
			for(int e=1; e<wire.size(); e++) {
				if(wire[0].x1==wire[e].x1&&wire[0].y1==wire[e].y1&&
						wire[0].x2==wire[e].x2&&wire[0].y2==wire[e].y2) {
					wire.erase(wire.begin());
					q--;
					break;
				}
			}
			++q;
		}
	}
	hs.push_back({});
}
bool editor(bool n) {
	gates_tex= load(string(global_data_dir+"textures/logic.png").c_str());
	SDL_Texture *cmenu  =   load(string(global_data_dir+"textures/editor.png").c_str());
	zoom=1;
	hs.clear();
	hs.push_back({});
	uint8_t buttons[21]= {1,1,1,0,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	rock.resize(0);
	bullet.resize(0);
	Select sl;
	if(lrd) {
		delete lrd;
		lrd=0;
	}
	if(n) {
		gate.resize(0);
		wire.resize(0);
	}
	for(int x=0; x<w; ++x) {
		for(int y=0; y<h; ++y) {
			if(n)level[x][y]=0;
			light[x][y]=255;
		}
	}
	ch_bl=1;
	ch_gt=0;
	mode=0;
	int xd=0,yd=0,xp=0,yp=0;
	sl.x1=0;
	sl.y1=0;
	sl.x2=w;
	sl.y2=h;
	sl.sx=1000;
	sl.sy=1000;
	function<void()> does[21]= {
		[&]() {
			gate.resize(0);
			wire.resize(0);
			for(int x=0; x<w; ++x) {
				for(int y=0; y<h; ++y) {
					level[x][y]=0;
					light[x][y]=255;
				}
			}
		},
		[&]() {
			open(string(save_data_dir+"levels/custom/"+lid+".lvl"));
			hs.push_back({});
		},
		[&]() {
			save(string(save_data_dir+"levels/custom/"+lid+".lvl"));
		},
		[&]() {
			if(hs.size()>1) {
				hs[hs.size()-2].load();
				hs.pop_back();
			}
		},
		[&](){mode=3;},
		[&](){mode=0;},
		[&](){mode=1;},
		[&](){mode=2;},
		[&]() {
			for(int q=sl.x1; q<sl.x2; ++q) {
				level[q][sl.y1]=tecno?140:1;
				level[q][sl.y2-1]=tecno?140:1;
			}
			for(int q=sl.y1; q<sl.y2; ++q) {
				level[sl.x1][q]=tecno?140:1;
				level[sl.x2-1][q]=tecno?140:1;
			}
			hs.push_back({});
			hs[hs.size()-1].save();
		},
		[&]() {
			int d=rand()%4;
			while(1) {
				int x=sl.x1+rand()%(sl.x2-sl.x1);
				int y=sl.y1+rand()%(sl.y2-sl.y1);
				if(level[x][y]==0) {
					level[x][y]=22+d;
					break;
				}
			}
			hs.push_back({});
			hs[hs.size()-1].save();
		},
		[&]() {
			int wl=sl.x2-sl.x1;
			int hl=sl.y2-sl.y1;
			vector<vector<uint8_t> >maze;
			maze=maze_generate(wl,hl);
			for(int x=0; x<wl; ++x) {
				for(int y=0; y<hl; ++y) {
					if(maze[x][y]==1)level[x+sl.x1][y+sl.y1]=ch_bl;
					if(maze[x][y]==2)level[x+sl.x1][y+sl.y1]=0;
				}
			}
			hs.push_back({});
			hs[hs.size()-1].save();
		},
		[&]() {
			if(mode==1)change_gate();
			else if(mode==0)change_block();
		},
		[&]() {
			save(string(save_data_dir+"levels/custom/"+lid+".lvl"));
			float z=zoom;
			game();
			zoom=z;
			open(string(save_data_dir+"levels/custom/"+lid+".lvl"));
			SDL_RenderSetViewport(ren,0);
			for(int x=0; x<w; ++x) {
				for(int y=0; y<h; ++y) {
					light[x][y]=255;
				}
			}
		},
		[&]() {
			hs.push_back({});
			inputwh(lid,w,h);
			for(int x=0; x<w; ++x) {
				for(int y=0; y<h; ++y) {
					light[x][y]=255;
				}
			}
		},
		[&](){move(sl,0,-1);},
		[&](){move(sl,1, 0);},
		[&](){move(sl,0, 1);},
		[&](){move(sl,-1,0);},
		[&]() {
			SDL_Surface *sur=create_surface(w*64,h*64);
			SDL_Surface *tex=IMG_Load(string(global_data_dir+"textures/all.png").c_str());
			SDL_Surface *flr=IMG_Load(string(global_data_dir+"textures/floor.png").c_str());
			for(int x=0; x<w; ++x) {
				for(int y=0; y<h; ++y) {
					SDL_Rect dest= {x*64,y*64,64,64};
					uint8_t j=(level[x][y])-1+(level[x][y]==52)+(level[x][y]==227)*5;
					SDL_Rect src= {64*(j%16), 64*(j/16), 64, 64};
					SDL_BlitSurface(flr,0,sur,&dest);
					if(level[x][y]==10 || level[x][y]==52 || level[x][y]==227)SDL_SetSurfaceAlphaMod(tex,150);
					SDL_BlitSurface(tex,&src,sur,&dest);
					if(level[x][y]==10 || level[x][y]==52 || level[x][y]==227)SDL_SetSurfaceAlphaMod(tex,255);
				}
			}
			time_t seconds = time(NULL);
			tm* timeinfo = localtime(&seconds);
			system(string(mkdir_command+save_data_dir+"screenshots").c_str());
			IMG_SavePNG(sur,string(save_data_dir+"screenshots/"+lid+".lvl     "+asctime(timeinfo)+".png").c_str());
			SDL_FreeSurface(tex);
			SDL_FreeSurface(sur);
			SDL_FreeSurface(flr);
		},
		[&]() {
			zoom*=1.1;
		},
		[&]() {
			zoom/=1.1;
		},
	};
	while(1) {
		SDL_RenderSetViewport(ren,0);
		if(e.type==SDL_QUIT) {
			SDL_DestroyTexture(cmenu);
			SDL_DestroyTexture(gates_tex);
			quit(1);
		} else if(e.type==SDL_KEYDOWN) {
			if(Back()) {
				SDL_DestroyTexture(cmenu);
				SDL_DestroyTexture(gates_tex);
				return 1;
			} else if(key[SDL_SCANCODE_M])mode=(mode+1)%3;
			else if(key[SDL_SCANCODE_R])does[13]();
			else if(key[SDL_SCANCODE_UP])does[14]();
			else if(key[SDL_SCANCODE_RIGHT])does[15]();
			else if(key[SDL_SCANCODE_DOWN])does[16]();
			else if(key[SDL_SCANCODE_LEFT])does[17]();
			else if(key[SDL_SCANCODE_W])cy+=10;
			else if(key[SDL_SCANCODE_A])cx+=10;
			else if(key[SDL_SCANCODE_S])cy-=10;
			else if(key[SDL_SCANCODE_D])cx-=10;
			else if(key[SDL_SCANCODE_P])does[18]();
			else if(key[SDL_SCANCODE_KP_PLUS])does[19]();
			else if(key[SDL_SCANCODE_KP_MINUS])does[20]();
		}
		if(e.button.x<SW&&e.button.y<SH) {
#ifdef ANDROID
			if(mouse.state && mouse.touch!=3 && mode!=3) {
#else
			if(mouse.state && mouse.b==SDL_BUTTON_MIDDLE) {
#endif
				cx=xd+(e.button.x-xp);
				cy=yd+(e.button.y-yp);
			} else {
				xd=cx;
				yd=cy;
				xp=e.button.x;
				yp=e.button.y;
			}
		}
		set_camera(cx,cy,1);
		lasers();
#ifndef ANDROID
		if(mouse.state&&mouse.y>50) {
#else
		if(mouse.y>50) {
#endif
			uint8_t x=test((mouse.x-cx)/64.0f/zoom,w);
			uint8_t y=test((mouse.y-cy)/64.0f/zoom,h);
#ifdef ANDROID
			if(mouse.touch==2) {
#else
			if(mouse.b==SDL_BUTTON_LEFT) {
#endif
				switch(mode) {
				case 0:
					if(level[x][y]!=ch_bl) {
						level[x][y]=ch_bl;
						drag=1;
#ifdef ANDROID
						hs.push_back({});
#endif
					}
					break;
				case 1: {
					bool ok=1;
					for(int q=0; q<(int)gate.size(); ++q) {
						if(gate[q].x==x && gate[q].y==y) {
							if(gate[q].type==ch_gt)ok=0;
							if(ok)gate.erase(gate.begin()+q);
						}
					}
					if(ok) {
						gate.push_back({x,y,ch_gt});
						hs.push_back({});
						if(ch_gt==25 || ch_gt==27 || ch_gt==28 || ch_gt==35 || ch_gt==36 || ch_gt==37 || ch_gt==38 || ch_gt==40) {
							int j=input_number(ch_gt);
							if(j!=255) {
								gate[gate.size()-1].value=j;
							} else gate.pop_back();
						}
					}
				}
				break;
				case 2: {
#ifdef ANDROID
					Wire *w;
					if(wire.size())w=&wire[wire.size()-1];
					if(wire.size()&&w->x1==w->x2 && w->y1==w->y2) {
						w->x2=x;
						w->y2=y;
						hs[hs.size()-1].save();
						if(w->x1==x&&w->y1==y)wire.pop_back();
					} else {
						wire.push_back({x,y,x,y,0});
						hs.push_back({});
					}
#else
					if(drag) {
						wire[wire.size()-1].x2=x;
						wire[wire.size()-1].y2=y;
						hs[hs.size()-1].save();
					} else {
						drag=1;
						wire.push_back({x,y,x,y,0});
						hs.push_back({});
					}
#endif
				}
				break;
				}
			}
#ifdef ANDROID
			if(mouse.touch==3) {
#else
			if(mouse.b==SDL_BUTTON_RIGHT) {
#endif
				switch(mode) {
				case 0:
					if(level[x][y]!=0) {
						level[x][y]=0;
						drag=1;
#ifdef ANDROID
						hs.push_back({});
#endif
					}
					break;
				case 1:
					for(int q=0; q<(int)gate.size(); ++q) {
						if(gate[q].x==x && gate[q].y==y) {
							gate.erase(gate.begin()+q);
							hs.push_back({});
						}
					}
					break;
				case 2:
					for(int q=0; q<(int)wire.size(); ++q) {
						if((wire[q].x1==x && wire[q].y1==y) || (wire[q].x2==x && wire[q].y2==y)) {
							wire.erase(wire.begin()+q);
							hs.push_back({});
						}
					}
					break;
				}
			}
		}
		if(e.type==SDL_MOUSEBUTTONUP) {
			if(mode==0&&drag) {
#ifdef ANDROID
				if(mouse.touch==2&&mouse.touch==3) {
					hs.push_back({});
				}
#else
				if(mouse.b==1||mouse.b==3) {
					hs.push_back({});
				}
#endif
			}
			drag=0;
		}
		if(mode==3 && mouse.y>50 && mouse.b==1)sl.select();
#ifdef ANDROID
		if(mode==3 && mouse.y>50 && mouse.touch==3)
#else
		if(mouse.state&&mode==3 && mouse.y>50 && mouse.b==3)
#endif
		{
			sl.sx=(mouse.x-cx)/64.0f/zoom-(sl.x2-sl.x1)/2;
			sl.sy=(mouse.y-cy)/64.0f/zoom-(sl.x2-sl.x1)/2;
		}
#ifdef ANDROID
		if(mode==3 && mouse.touch==3 && mouse.state==0 && (sl.sx!=1000 || sl.sy!=1000))
#else
		if(!mouse.state && mode==3 && (sl.sx!=1000 || sl.sy!=1000))
#endif
		{
			copy(sl,  sl.sx - sl.x1,  sl.sy - sl.y1);
			sl.sx=1000;
			sl.sy=1000;
		}
		SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_RenderClear(ren);
		draw(0,mode,1);
		sl.show();
		SDL_Rect r= {0,0,SW,50};
		SDL_SetRenderDrawColor(ren,255,255,255,255);
		SDL_RenderFillRect(ren,&r);
		buttons[3]=(hs.size()>1);
		buttons[4]=(mode==3)+1;
		buttons[5]=(mode==0)+1;
		buttons[6]=(mode==1)+1;
		buttons[7]=(mode==2)+1;
		buttons[11]=(mode==0 || mode==1);
		bool j=0;
		for(int q=0; q<21; ++q) {
			int k=buttons[q];
			if(in_rect(FC_MakeRect(q*50,0,50,50)) && k==1)k=2;
			SDL_Rect r= {q*50,k*50,50,50};
			showIMG(q*50,0,50,50,cmenu,r);
			if(in_rect(FC_MakeRect(q*50,0,50,50)) && e.button.state) {
				mouse.wait();
				j=1;
				does[q]();
			}
		}
		if(hs.size()>100)hs.erase(hs.begin());
		SDL_RenderPresent(ren);
		if(!j)SDL_WaitEvent(&e);
		mouse.update();
	}
	return 0;
}

std::random_device rd;
std::mt19937 mt(rd());
typedef struct cell {
	uint8_t x;
	uint8_t y;
} cell;

int visited(vector<vector<uint8_t> >maze,int w,int h) {
	int c=0;
	for(int x=0; x<w; ++x) {
		for(int y=0; y<h; ++y) {
			if(maze[x][y]==0)c++;
		}
	}
	return c;
}

int random_nb(vector<vector<uint8_t> >maze,int x,int y,int w,int h) {
	bool b[4]= {0,0,0,0};
	if(y > 2&&maze[x][y-2]==0)b[0]=1;
	if(x<w-3&&maze[x+2][y]==0)b[1]=1;
	if(y<h-3&&maze[x][y+2]==0)b[2]=1;
	if(x > 2&&maze[x-2][y]==0)b[3]=1;
	if(!(b[0]||b[1]||b[2]||b[3]))return 4;
	vector<uint8_t>n;
	for(int q=0; q<4; ++q)if(b[q])n.push_back(q);
	return n[rand()%n.size()];
}

vector<vector<uint8_t> > maze_generate(int w,int h) {
	vector<vector<uint8_t> >maze(w,vector<uint8_t>(h));
	vector<cell>cl;
	cell c= {1,1};
	srand(time(0));
	int av=0;
	for(int y = 0; y < h; ++y) {
		for(int x = 0; x < w; ++x) {
			if((x % 2 != 0  && y % 2 != 0) &&
					(y < h-1 && x < w-1)) {
				maze[x][y]=0;
				av++;
			} else maze[x][y]=1;
		}
	}
	maze[c.x][c.y]=2;
	while(visited(maze,w,h)) {
		int r=random_nb(maze,c.x,c.y,w,h);
		if(r!=4) {
			cl.push_back(c);
			cell ch= {(uint8_t)(c.x-(r==3)*2+(r==1)*2),(uint8_t)(c.y-(r==0)*2+(r==2)*2)};
			maze[(ch.x+c.x)/2][(ch.y+c.y)/2]=2;
			c=ch;
			maze[c.x][c.y]=2;
		} else if(cl.size()) {
			c=cl[cl.size()-1];
			cl.pop_back();
		}
	}
	return maze;
}

int randomInt(int exclusiveMax) {
	std::uniform_int_distribution<> dist(0, exclusiveMax - 1);
	return dist(mt);
}

int randomInt(int min, int max) { // inclusive min/max
	std::uniform_int_distribution<> dist(0, max - min);
	return dist(mt) + min;
}

bool randomBool(double probability = 0.5) {
	std::bernoulli_distribution dist(probability);
	return dist(mt);
}
struct Room {
	Room(int xp,int yp,int wp,int hp):x(xp),y(yp),width(wp),height(wp) {};
	int x, y;
	int width, height;
	//bool secret=0;
};

struct Dungeon {

	char  Unused	= 0,
			 Floor		= 254,
				  Corridor	= 255,
					 Wall		= 1,
						   ClosedDoor	= 8,
							SecretDoor	= 10,
							 UpStairs	= 27,
								DownStairs	= 26,
								 Money1      = 22,
								 Money2      = 23,
								 Money5      = 24,
								 Money10     = 25;
	enum Direction {
		North,
		South,
		West,
		East,
		DirectionCount
	};

	Dungeon(int w, int h, int f, int sf,int mc)
		: width(w)
		, height(h)
		, tiles(w,vector<char>(h,0))
		, rooms()
		, exits()
		, features(f)
		, money_count(mc)
		, secret_features(sf) {}

	void generate() {
		if (!makeRoom(width / 2, height / 2, static_cast<Direction>(randomInt(4), true)))return;
		for (int i = 1; i < features; ++i) {
			if (!createFeature(i))break;
			print();
		}

		//if (!placeObject(UpStairs))return;

		{
			Room &r=rooms[0];
			setTile(r.x+r.width/2,r.y+r.height/2,UpStairs);
		}

		{
			Room &r=rooms[rooms.size()-1-secret_features];
			setTile(r.x+r.width/2,r.y+r.height/2,DownStairs);
		}

		//if (!placeObject(DownStairs))return;

		/*for(Room &room : rooms){
			int sum=0;
			for()
		}*/

		for (vector<char> &t : tiles) {
			for(char &tile : t) {

				if (tile == Unused)
					tile = Wall;
				else if (tile == Floor || tile == Corridor)
					tile = Unused;
			}
		}
	}

	void print() {
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x)
				std::cout << getTile(x, y);

			std::cout << std::endl;
		}
	}

	inline char getTile(int x, int y) const {
		if (x < 0 || y < 0 || x >= width || y >= height)
			return Unused;

		return tiles[x][y];
	}

	inline void setTile(int x, int y, char tile) {
		tiles[x][y] = tile;
	}

	bool createFeature(int n) {
		for (int i = 0; i < 1000; ++i) {
			if (exits.empty())
				break;

			// choose a random side of a random room or corridor
			int r = randomInt(exits.size());
			int x = randomInt(exits[r].x, exits[r].x + exits[r].width - 1);
			int y = randomInt(exits[r].y, exits[r].y + exits[r].height - 1);

			// north, south, west, east
			for (int j = 0; j < DirectionCount; ++j) {
				if (createFeature(x, y, static_cast<Direction>(j),n)) {
					exits.erase(exits.begin() + r);
					return true;
				}
			}
		}

		return false;
	}

	bool createFeature(int x, int y, Direction dir, int n) {
		static const int roomChance = 50; // corridorChance = 100 - roomChance

		int dx = 0;
		int dy = 0;

		if (dir == North)
			dy = 1;
		else if (dir == South)
			dy = -1;
		else if (dir == West)
			dx = 1;
		else if (dir == East)
			dx = -1;

		if (getTile(x + dx, y + dy) != Floor && getTile(x + dx, y + dy) != Corridor)
			return false;

		if (randomInt(100) < roomChance) {
			if (makeRoom(x, y, dir)) {
				setTile(x, y, (features-n <= secret_features)?SecretDoor:ClosedDoor);

				return true;
			}
		}

		else {
			if (makeCorridor(x, y, dir)) {
				if (getTile(x + dx, y + dy) == Floor) {
					setTile(x, y, (features-n <= secret_features)?SecretDoor:ClosedDoor);
				} else { // don't place a door between corridors
					setTile(x, y, Corridor);
				}
				return true;
			}
		}

		return false;
	}

	bool makeRoom(int x, int y, Direction dir, bool firstRoom = false) {
		static const int minRoomSize = 3;
		static const int maxRoomSize = 6;

		Room room(0,0,
				  randomInt(minRoomSize, maxRoomSize),
				  randomInt(minRoomSize, maxRoomSize));

		if (dir == North) {
			room.x = x - room.width / 2;
			room.y = y - room.height;
		}

		else if (dir == South) {
			room.x = x - room.width / 2;
			room.y = y + 1;
		}

		else if (dir == West) {
			room.x = x - room.width;
			room.y = y - room.height / 2;
		}

		else if (dir == East) {
			room.x = x + 1;
			room.y = y - room.height / 2;
		}
		return placeRoom(room,dir,firstRoom);

	}
	bool placeRoom(Room &room,Direction dir,bool firstRoom) {
		if (placeRect(room, Floor)) {
			rooms.emplace_back(room);

			if (dir != South || firstRoom) // north side
				exits.emplace_back(Room{ room.x, room.y - 1, room.width, 1 });
			if (dir != North || firstRoom) // south side
				exits.emplace_back(Room{ room.x, room.y + room.height, room.width, 1 });
			if (dir != East || firstRoom) // west side
				exits.emplace_back(Room{ room.x - 1, room.y, 1, room.height });
			if (dir != West || firstRoom) // east side
				exits.emplace_back(Room{ room.x + room.width, room.y, 1, room.height });

			return true;
		}

		return false;
	}
	bool makeCorridor(int x, int y, Direction dir) {
		static const int minCorridorLength = 3;
		static const int maxCorridorLength = 6;

		Room corridor(x,y,1,1);

		if (randomBool()) { // horizontal corridor
			corridor.width = randomInt(minCorridorLength, maxCorridorLength);

			if (dir == North) {
				corridor.y = y - 1;

				if (randomBool()) // west
					corridor.x = x - corridor.width + 1;
			}

			else if (dir == South) {
				corridor.y = y + 1;

				if (randomBool()) // west
					corridor.x = x - corridor.width + 1;
			}

			else if (dir == West)
				corridor.x = x - corridor.width;

			else if (dir == East)
				corridor.x = x + 1;
		}

		else { // vertical corridor
			corridor.height = randomInt(minCorridorLength, maxCorridorLength);

			if (dir == North)
				corridor.y = y - corridor.height;

			else if (dir == South)
				corridor.y = y + 1;

			else if (dir == West) {
				corridor.x = x - 1;

				if (randomBool()) // north
					corridor.y = y - corridor.height + 1;
			}

			else if (dir == East) {
				corridor.x = x + 1;

				if (randomBool()) // north
					corridor.y = y - corridor.height + 1;
			}
		}

		if (placeRect(corridor, Corridor)) {
			rooms.emplace_back(corridor);
			if (dir != South && corridor.width != 1) // north side
				exits.emplace_back(Room{ corridor.x, corridor.y - 1, corridor.width, 1 });
			if (dir != North && corridor.width != 1) // south side
				exits.emplace_back(Room{ corridor.x, corridor.y + corridor.height, corridor.width, 1 });
			if (dir != East && corridor.height != 1) // west side
				exits.emplace_back(Room{ corridor.x - 1, corridor.y, 1, corridor.height });
			if (dir != West && corridor.height != 1) // east side
				exits.emplace_back(Room{ corridor.x + corridor.width, corridor.y, 1, corridor.height });

			return true;
		}

		return false;
	}

	bool placeRect(const Room& rect, char tile) {
		if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > width - 1 || rect.y + rect.height > height - 1)
			return false;

		for (int y = rect.y; y < rect.y + rect.height; ++y)
			for (int x = rect.x; x < rect.x + rect.width; ++x) {
				if (getTile(x, y) != Unused)
					return false; // the area already used
			}

		for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y)
			for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x) {
				if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height)
					setTile(x, y, Wall);
				else
					setTile(x, y, tile);
			}

		return true;
	}

	bool placeObject(char tile) {
		if (rooms.empty())
			return false;

		int r = randomInt(rooms.size()); // choose a random room
		int x = randomInt(rooms[r].x + 1, rooms[r].x + rooms[r].width - 2);
		int y = randomInt(rooms[r].y + 1, rooms[r].y + rooms[r].height - 2);

		if (getTile(x, y) == Floor) {
			setTile(x, y, tile);

			// place one object in one room (optional)
			rooms.erase(rooms.begin() + r);

			return true;
		}

		return false;
	}
	int width, height, features, secret_features, money_count;
	std::vector<std::vector<char>> tiles;
	std::vector<Room> rooms; // rooms for place stairs or monsters
	std::vector<Room> exits; // 4 sides of rooms or corridors
};
LRD::LRD(uint16_t xp,uint16_t yp) {
	x=xp;
	y=yp;
	timerr=timer;
	n=2;
	start=timer;
}
void LRD::clear() {
	for(float a=0; a<M_PI*2; a+=0.005) {
		float xp=x,yp=y;
		while(1) {
			float d=sqrt(pow(x-xp,2)+pow(y-yp,2))/64.0f;
			xp+=cos(a)*20;
			yp+=sin(a)*20;
			if(d>8)break;
			light[(int)(xp+32)/64][(int)(yp+32)/64]=255;
			if(block_config[5][level[(int)(xp+32)/64][(int)(yp+32)/64]])break;
		}
	}
}
void LRD::move(int c,uint8_t n) {
	switch(n) {
	case 0:
		y-=c;
		break;
	case 1:
		x+=c;
		break;
	case 2:
		y+=c;
		break;
	case 3:
		x-=c;
		break;
	}
}
bool LRD::bar() {
	uint8_t level2[255][255];
	memcpy(level2, level, sizeof(level2));
	level2[player->x/64][player->y/64]=1;
	if(block_config[2][level2[(short)x/64-(n==3)+(n==1)][(short)y/64-(n==0)+(n==2)]])return 1;
	for(unsigned q=0; q<rock.size(); ++q) {
		if(rock[q].x/64==x/64-(n==3)+(n==1)
				&& rock[q].y/64==y/64-(n==0)+(n==2) && rock[q].type!=1)return 1;
	}
	return 0;
}

bool LRD::fly() {
	if(timer>(int)timerr+20 && start>0) {
		timerr=timer;
		if(x%64==0 && y%64==0) {
			uint8_t k[]= {SDL_SCANCODE_W,SDL_SCANCODE_D,SDL_SCANCODE_S,SDL_SCANCODE_A,SDL_SCANCODE_UP,SDL_SCANCODE_RIGHT,SDL_SCANCODE_DOWN,SDL_SCANCODE_LEFT};
			bool ok=0;
			for(int q=0; q<8; ++q) {
				if((key[k[q]]
#ifdef ANDROID
						|| (sensor==q+2 && q < 4)
#endif
				   ) && !ok) {
					n=q%4;
					if(!bar()) {
						move(4,n);
						ok=1;
					}
				}
			}
		} else {
			move(4,n);
		}
	}
	clear();
	if(lrd->start<0 && timer+lrd->start>500) {
		uint8_t &block=level[lrd->x/64][lrd->y/64];
		if(block==14 || block==15)block=90;
		else block=89;
		return 1;
	}
	return 0;
}

void LRD::action() {
	if(((key[SDL_SCANCODE_E] && e.type==SDL_KEYDOWN)
#ifdef ANDROID
			|| sensor==6
#endif
	   ) && x%64==0 && y%64==0 && (level[x/64][y/64]==0 || level[x/64][y/64]==14)) {
		while(e.type==SDL_KEYDOWN)SDL_PollEvent(&e);
		start=-timer;
		n=2;
	}
}


void new_game() {
	bool ok=1;
	if(profile.level)ok=alert();
	if(ok) {
		intro();
		profile.new_game();
		profile.save(profn);
		lid=lntolid(profile.level);
		string path=string(global_data_dir+"levels/standart/"+lntolid(profile.level)+".lvl");
		open(path);
		st=1;
		game();
	}
}
void cont() {
	lid=lntolid(profile.level);
	string path=string(global_data_dir+"levels/standart/"+lntolid(profile.level)+".lvl");
	open(path);
	st=1;
	game();
}
void endmain() {
	quit(1);
}

int main(int argv, char** argc) {
#ifdef ANDROID
	save_data_dir=string(SDL_AndroidGetExternalStoragePath())+"/../../../../dark-podval/";
#endif
	srand(time(0));
#ifdef STEAM
	if (SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid ))return 1;
	if (!SteamAPI_Init()) {
		printf( "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n" );
		return 1;
	}
	ISteamApps* pSteamApps = SteamApps();
	const char *lang= pSteamApps->GetCurrentGameLanguage();
	if((string)lang=="russian")loc="ru";
	profile.name = SteamFriends()->GetPersonaName();
	SteamUserStats()->RequestCurrentStats();
#endif
	load_settings();
	save_settings();
	load_strings();
	profile.load(profn);
	profile.save(profn);
	init("Dark Podval");
	save_settings();
	SDL_Texture *image=load(string(global_data_dir+"textures/menu.png").c_str());
#if defined(linux_install) || defined(ANDROID)
	system(string(mkdir_command+save_data_dir).c_str());
#endif
	struct menu_item {
		void(*func)();
		std::string &str;
	};
	vector<menu_item>menu_items;

	auto update_menu_items=[&]() {
		menu_items.clear();
		menu_items.push_back({new_game,strings[69]});
#ifndef DEV
		if(profile.level!=0)
#endif
			menu_items.push_back({cont,strings[0]});
#ifndef DEV
		if(profile.level>10)
#endif
			menu_items.push_back({standart,strings[1]});

			menu_items.push_back({custom,strings[2]});
		menu_items.push_back({settings,strings[5]});
#ifndef ANDROID
		menu_items.push_back({endmain,strings[6]});
#endif
	};

	update_menu_items();

	while(1) {
		SDL_Rect r= {SW/3*2,SH/2+FC_GetHeight(def,"\n\n\n\n"),SW/3,int(25*iface_zoom)};
		SDL_RenderSetViewport(ren,0);
		SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_RenderClear(ren);
		showIMG(0,0,SW,SH,image);
		for(int q=0; q<menu_items.size(); ++q) {
			SDL_Rect r= {SW/32,int(SH/5+q*38*iface_zoom),int(400*iface_zoom),int(38*iface_zoom)};
			SDL_Color c=in_rect(r)?gray:white;
			FC_DrawBoxColor(menu,ren,r,c,menu_items[q].str.c_str());
		}
		FC_DrawColumn(menu,ren,SW/3*2,SH/2,SW/3,"%s,\n\n%s\n",strings[7].c_str(),profile.name.c_str());
#ifndef STEAM
		FC_DrawBoxColor(def,ren,r,in_rect(r)?gray:white,strings[8].c_str());
#endif
		SDL_RenderPresent(ren);
		SDL_WaitEvent(&e);
		mouse.update();
		if(e.type==SDL_QUIT)quit(1);
		else if(e.type==SDL_MOUSEBUTTONDOWN) {
			for(int q=0; q<menu_items.size(); q++) {
				SDL_Rect r= {SW/32,int(SH/5+q*38*iface_zoom),int(400*iface_zoom),int(38*iface_zoom)};
				if(in_rect(r)) {
					SDL_DestroyTexture(image);
					menu_items[q].func();
					SDL_RenderSetViewport(ren,0);
					mouse.update();
					mouse.x=mouse.y=0;
					mouse.wait();
					image=load(string(global_data_dir+"textures/menu.png").c_str());
					update_menu_items();
					continue;
				}
			}
#ifndef STEAM
			if(in_rect(r)) {
				profiles();
				update_menu_items();
				SDL_RenderSetViewport(ren,0);
			}
#endif
		}
	}
}
