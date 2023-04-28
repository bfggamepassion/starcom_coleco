/**************************************************/
/*** BOSCONIAN *************************************/
/**************************************************/
#include <coleco.h>
#include <getput1.h>
#include <comp.h>
//#include <bfglib.h>

#define chrtab  0x1800 /* écran en linéaire */
#define chrgen  0x0000 /* table des caractères */
#define coltab  0x2000 /* couleur des caractères */
#define sprtab  0x3800 /* sprite_pattern_table */
#define sprgen  0x1b00 /* sprite_attribute_table */
#define buffer  0x1c00 /* buffer screen 2 */

#define S_TRUE 1
#define S_FALSE 0

#define MAXSCROLLOBJ 8
#define MAXLEVEL 8

#define TILE_MOTHERSHIPV 0
#define TILE_MOTHERSHIPH 1
#define TILE_BLANK 2

/* 9 types graphiques d'étoiles (ANIMATION) */
#define TILE_STARFIELD1 10 
#define TILE_STARFIELD2 11 
#define TILE_STARFIELD3 12 
#define TILE_STARFIELD4 18 
#define TILE_STARFIELD5 19 
#define TILE_STARFIELD6 20 
#define TILE_STARFIELD7 26 
#define TILE_STARFIELD8 27 
#define TILE_STARFIELD9 28 

#define NOMOVE_MINE 22*4
#define NOMOVE_AST1 23*4
#define NOMOVE_AST2 24*4
#define NOMOVE_EXPLOSION 25*4
#define ALIEN_BOOMERANG 32
#define ALIEN_TRIANGLE 40

#define INACTIF 204
#define INVISIBLE 203

#define HAUT -1
#define BAS 1
#define GAUCHE -1
#define DROITE 1
#define STATIQUE 0


#define PLAYERSTARTX 94
#define PLAYERSTARTY 94

#define MAXENNEMYBULLET 5
#define MAXALIEN 5
#define MAXNOMOVE 5

#define BUL_ACTIVE 0x80
#define BUL_UP 0x1
#define BUL_LEFT 0x2

#define SHOW_SPLASH0 0
#define SHOW_STORY 1
#define SHOW_TITLE 2
#define	INGAME 3
#define NEXT_LEVEL 4
#define GAME_OVER 5
#define LOOSE_LIFE 6

extern const void music[];
extern const void music_go[];
extern const void snd_table[];

extern const byte tankAnimationV[];
extern const byte tankAnimationH[];

extern const byte SPLASH0_PATTERNDAN0[];
extern const byte SPLASH0_COLORDAN0[];
extern const byte SPLASH0_NAMEDAN0[];

extern const byte SPLASH1_PATTERNDAN0[];
extern const byte SPLASH1_COLORDAN0[];
extern const byte SPLASH1_NAMEDAN0[];

extern const byte SPLASH2_PATTERNDAN0[];
extern const byte SPLASH2_COLORDAN0[];
extern const byte SPLASH2_NAMEDAN0[];

extern const byte TITLE_PATTERNDAN0[];
extern const byte TITLE_COLORDAN0[];
extern const byte TITLE_NAMEDAN0[];

extern const byte PATTERNRLE[];
extern const byte COLORRLE[];
extern const byte SPATTERNRLE[];
extern const byte tiles_Init[];
extern const byte* const tiles_Pointer[];
extern const byte testTile[];
extern const byte pod_position[];
extern const byte collisionv[];
extern const byte collisionh[];
extern const byte fondRadar[];
extern const byte life[];

extern const char* const levels_Pointer[];

/* Variables de gestion de la difficultée */
byte difficulty;
byte mTirDirigeTimer;
int mTirDroitTimer;
int genEnnTimer;
byte genEnnShootTimer;
byte tankAnimationSpeed;
byte odd;
byte soundonoff;

char mynmi;
char nmiRenderRadar;
char nmiRenderScrollObj;
char nmiMoveStarfield;
char nmiInitRadar;
char nmiDetectCarShoot;
char workflow;

byte nb_source;
byte p_source;

byte tankAnimationPointer;


byte traceSprite;

// Position courante du point de référence
int refx;
int refy;
byte currentNmi;
byte tmp;

byte radarPosx;
byte radarPosy;
byte radarOldCar;

char currentStarAnim;

int cpt;

char motherShipVisible;

unsigned int timer;
byte oddNmi;

byte nbMothershipLevel;
byte currentLevel;
byte currentLevelAff;

sprite_t bsprites[32];

// Le static x est entre 0 et 26
// Le static y est entre 0 et 20
typedef struct
{
	byte p;	// Pattern à utiliser
	char staticx; // Position par rapport au point de référence
	char staticy; // Position par rapport au point de référence
	byte pod; // Pour les motherShips
} s_scrollObj;

s_scrollObj scrollObj[MAXSCROLLOBJ];

typedef struct
{
	char staticx; // Position par rapport au point de référence
	char staticy; // Position par rapport au point de référence
} s_star;

s_star stars[5];

typedef struct
{
	char directionH;
	char directionV;
	byte char_haut_gauche;
	byte char_haut_droite;
	byte char_bas_gauche;
	byte char_bas_droite;
	unsigned score;	
	unsigned hiscore;
	byte timerShoot;
	byte nbLives;
} s_player;

s_player player;

// Libre mvtx = 0 et mvt y = 0
typedef struct
{	
	char mvtx;
	char mvty;	
	byte sprno;
	byte currentChar;
} s_shoot;

s_shoot shoot[6];

typedef struct
{
	byte flags;
    byte sprno;
    byte dx,dy;
    int err;
} s_ennemyBullet ;

s_ennemyBullet ennemyBullet[MAXENNEMYBULLET];


typedef struct
{
	byte typeAlien;
	byte flags;
    byte sprno;
    byte dx,dy;
	byte finalx,finaly;
    int err;
	char triggerTimer;
} s_alien;

s_alien alien[MAXALIEN];	

typedef struct
{
	byte actif;
	byte sprno;
} s_nomoveObject;

s_nomoveObject nomoveObject[MAXNOMOVE]; // Objets qui ne bougent pas d'eux même.

byte matrix[3][3]={
				/* y= -1 , 0, +1 */
					{7,6,5},		/* x=-1 */
					{0,9,4},		/* x=0 */
					{1,2,3}			/* x=+1 */
};

byte matrixShoot[3][3]={
				/* y= -1 , 0, +1 */
					{18<<2,20<<2,17<<2},		/* x=-1 */
					{19<<2,19<<2,19<<2},		/* x=0 */
					{17<<2,20<<2,18<<2}			/* x=+1 */
};

byte get_char_protected(byte x,byte y)
{
	if (x>31) return 0;
	if (y>23) return 0;
	return get_char(x,y);
}

void put_char_protected(byte x,byte y,byte c)
{
	if (x>31) return;
	if (y>23) return;
	put_char(x,y,c);
}

void put_frame_crop_H24(byte *tile,char x,char y,char w,char h)
{
	char i;
	char cw; // calculated weight
	int offset_deplacement;
	char tmp;
	
	if (x>23) return;
	if (y>23) return;
	
	tmp = x+w;
	
	if (tmp<24) // Il n'y aura pas de clipping à droite
	{
		if ( (x>=0) && ((y+h)<24) && (y>=0) )  // Et il n'y aura pas de clipping tout court
		{
			put_frame0(tile,x,y,w,h);
		}
		else // Il y aura un clipping à gauche
		{
			put_frame(tile,x,y,w,h);
		}
		
		return;
	}
		offset_deplacement = 0;
	
		// Si on dépasse du crop
		// Il faut calculer la nouvelle largeur
		if ((tmp) > 24)
			cw = 24-x;
		else
			cw = w;
			
		if (cw>0)
		{
			
			for (i=0;i<h;i++)
			{
				tmp = y+i; // Ligne courant de l'écran à écrire
				if ((tmp)>23) return;
				if ((tmp)>=0)
				{				
					put_vram(chrtab+((tmp)<<5)+x,tile+offset_deplacement,cw);					
				}					 
				offset_deplacement += w;
			}
			
		}			
}


char getFreeSprite()
{
	byte i;
		
	odd+=8;
	if (odd>=32) odd = 0;
	
	for (i=odd;i<32;i++)
		if (sprites[i].y==INACTIF) 
			return i;	
	for (i=0;i<odd;i++)
		if (sprites[i].y==INACTIF) 
			return i;
	
	return -1;
}

void createEnnemyBullet(byte pattern,byte colour,int x0,int y0,int x1,int y1)
{
	int i;
	char s;
	
	for(i=0;i<MAXENNEMYBULLET;i++) {
		if(ennemyBullet[i].flags&BUL_ACTIVE) continue;
		/* found an unused bullet, so let's set it up.*/
		//bullet[i].sprite=newsprite(i,x0,y0);
		s = getFreeSprite();
		if (s!=-1)
		{
			ennemyBullet[i].sprno = s;		
			sprites[s].pattern=pattern;
			sprites[s].colour=colour;
			sprites[s].x=x0;
			sprites[s].y=y0;
			ennemyBullet[i].flags=BUL_ACTIVE;
			ennemyBullet[i].flags|=(x0<x1)?0:BUL_LEFT;
			ennemyBullet[i].flags|=(y0<y1)?0:BUL_UP;
			ennemyBullet[i].dx=(x0<x1)?x1-x0:x0-x1;
			ennemyBullet[i].dy=(y0<y1)?y1-y0:y0-y1;
			ennemyBullet[i].err=ennemyBullet[i].dx-ennemyBullet[i].dy;
		
		    stop_sound(14);
			play_sound(14);
			return;
		}
	}
}

void initAlien()
{
	byte i;
	
	for (i=0;i<MAXALIEN;i++)
	{
		alien[i].flags=0;
		alien[i].triggerTimer=-1;
	}
}

void reinitAlien(byte i,int x0,int y0,int x1,int y1)
{
			alien[i].finalx = x1;
			alien[i].finaly = y1;
			alien[i].flags=BUL_ACTIVE;
			alien[i].flags|=(x0<x1)?0:BUL_LEFT;
			alien[i].flags|=(y0<y1)?0:BUL_UP;
			alien[i].dx=(x0<x1)?x1-x0:x0-x1;
			alien[i].dy=(y0<y1)?y1-y0:y0-y1;
			alien[i].err=alien[i].dx-alien[i].dy;
}


void createAlien(byte typeAlien,int x0,int y0,int x1,int y1)
{
	int i;
	char s;
	byte c;
	
	for(i=0;i<MAXALIEN;i++) {
		if(alien[i].flags&BUL_ACTIVE) continue;
		
		s = getFreeSprite();
		if (s!=-1)
		{
			c = 3;
			if (typeAlien==ALIEN_TRIANGLE) c = 13;
		
			alien[i].sprno = s;		
			sprites[s].pattern=typeAlien<<2;
			sprites[s].colour=c;
			sprites[s].x=x0;
			sprites[s].y=y0;
			alien[i].typeAlien = typeAlien;
			
			reinitAlien(i,x0,y0,x1,y1);
			
			return;
		}
	}
}

/*
byte returnAlienPattern(byte typeAlien,char mvtx,char mvty)
{
		return (typeAlien+(matrix[1+mvtx][1+mvty]))<<2;
}
*/

void updateAlien(byte id)
{
	byte tour,i;
	
	s_alien *this_alien;
	byte *this_alien_typeAlien;
	byte *this_alien_flags;
    byte *this_alien_sprno;
    byte *this_alien_dx;
	byte *this_alien_dy;
    int  *this_alien_err;
	
	sprite_t *this_sprite;
	byte *this_sprite_x;
	byte *this_sprite_y;
	byte *this_sprite_pattern;
	
	int e2;
		
	this_alien = &alien[id];
	this_alien_sprno = &this_alien->sprno;
	this_alien_flags = &this_alien->flags;
	this_alien_err = &this_alien->err;
	this_alien_typeAlien = &this_alien->typeAlien;
	this_alien_dx = &this_alien->dx;
	this_alien_dy = &this_alien->dy;
	
	this_sprite = &sprites[(*this_alien_sprno)];
	this_sprite_x = &this_sprite->x;
	this_sprite_y = &this_sprite->y;
	this_sprite_pattern = &this_sprite->pattern;
	
	
	if(((*this_alien_flags)&BUL_ACTIVE)==0) return; // not active.
	
	if((*this_sprite_x)>192 || (*this_sprite_y)>191 ) {
		(*this_alien_flags)=0; // sprite inactive.
		(*this_sprite_y)=INACTIF; // off screen.
		return;
	}
	
	if ((timer&3)==0) tour=2; else tour=1;
	
	for (i=0;i<tour;i++)
	{
		e2=(*this_alien_err)<<1;
		if( e2 > -(*this_alien_dy)) {
			(*this_alien_err)-=(*this_alien_dy);
			(*this_sprite_x)+=((*this_alien_flags)&BUL_LEFT)?-1:1;
		}
		if( e2 < (*this_alien_dx) ) {
			(*this_alien_err)+=(*this_alien_dx);
			(*this_sprite_y)+=((*this_alien_flags)&BUL_UP)?-1:1;
		}
	}

	(*this_sprite_pattern) = ((*this_alien_typeAlien)+(matrix[1+(((*this_alien_flags)&BUL_LEFT)?-1:1)][1+(((*this_alien_flags)&BUL_UP)?-1:1)]))<<2;
	
	if ((timer&1)==0)
	{
	
		(*this_sprite_x)-=(player.directionH)<<1;
		(*this_sprite_y)-=(player.directionV)<<1;
	}
}

void gererAIAlien()
{	
	byte i;
	int deltax;
	int deltay;
	
	//byte newDestx;
	//byte newDesty;
	
	s_alien *this_alien;
	byte *this_alien_flags;
    byte *this_alien_sprno;
	byte *this_alien_finalx;
	byte *this_alien_finaly;
	char *this_alien_triggerTimer;
	
	sprite_t *this_sprite;
	byte *this_sprite_x;
	byte *this_sprite_y;
				
	// Ici on va gérer leur intelligence Artificielle
	
	for (i=0;i<MAXALIEN;i++)
	{
	
		this_alien = &alien[i];
		this_alien_sprno = &this_alien->sprno;
		this_alien_flags = &this_alien->flags;
		this_alien_finalx = &this_alien->finalx;
		this_alien_finaly = &this_alien->finaly;
		this_alien_triggerTimer = &this_alien->triggerTimer;

		
		this_sprite = &sprites[(*this_alien_sprno)];
		this_sprite_x = &this_sprite->x;
		this_sprite_y = &this_sprite->y;

		// Tout les 8 on remet l'alien sur le bon chemin
		if ( ((timer&15)==0) && (((*this_alien_flags)&BUL_ACTIVE)!=0) )
		{
			if ( (genEnnShootTimer>0) && ((timer&genEnnShootTimer)==0) )
			{
				createEnnemyBullet(21<<2,10,(*this_sprite_x)+8,(*this_sprite_y)+8,PLAYERSTARTX,PLAYERSTARTY);	
			}
			
		}
		
		if (((timer&7)==0) && (((*this_alien_flags)&BUL_ACTIVE)!=0)) reinitAlien(i,(*this_sprite_x),(*this_sprite_y),(*this_alien_finalx),(*this_alien_finaly));
		else
		// Si l'alien à atteind sa destination, on va lui en trouver une nouvelle
		if (((*this_alien_flags)&BUL_ACTIVE)!=0)
		{
			if ((*this_sprite_x)>(*this_alien_finalx))
				deltax = (*this_sprite_x)-(*this_alien_finalx);
			else
				deltax = (*this_alien_finalx)-(*this_sprite_x);
			
			if ((*this_sprite_y)>(*this_alien_finaly))
				deltay = (*this_sprite_y)-(*this_alien_finaly);
			else
				deltay = (*this_alien_finaly)-(*this_sprite_y);
					
			
			if ( (deltax<4) && (deltay<4) )
			{		
				reinitAlien(i,(*this_sprite_x),(*this_sprite_y),rnd_byte(0,200),rnd_byte(0,192));
			}
		}
			
		
		// On fait bouger
		updateAlien(i);
	}
}

void declencherAlien()
{	
	// Ici on va créer les aliens
	// --> Si il n'y à pas de motherShip à l'écran
	// --> On va créer selon le niveau de difficulté des aliens
	byte startx;
	byte starty;
	byte r;
	
	r=rnd_byte(0,100);
	
	startx = 0;
	starty = 0;
	
	//if (motherShipVisible==-1)
	if ( (genEnnTimer>0) && ((timer&genEnnTimer)==0) && (timer>0) )
	{

			if (player.directionH == DROITE)
				startx = 190;
			else
			if (player.directionH == GAUCHE)
				startx = 0;

			if (player.directionV == HAUT)
				starty = 0;
			else
			if (player.directionV == BAS)
				starty = 180;
			
			if (r<50) createAlien(ALIEN_BOOMERANG,startx,starty,150,150);
			else createAlien(ALIEN_TRIANGLE,startx,starty,50,50);
	}
	// Et on les fait réfléchir
	gererAIAlien();
}


void initNomoveObject()
{
	byte i;
	for (i=0;i<MAXNOMOVE;i++)
		nomoveObject[i].actif = 0;
}

void createNomoveObject(byte x,byte y,byte pattern)
{
	char s,i;
	byte c;
	
	s = getFreeSprite();
	if (s!=-1)
	{
		for (i=0;i<MAXNOMOVE;i++)
		{
			if (nomoveObject[i].actif==0)
			{
				//if (pattern==NOMOVE_EXPLOSION) center_string(0,str(i));
				//pause();
				nomoveObject[i].actif = 1;
				nomoveObject[i].sprno = s;
				sprites[s].x = x;
				sprites[s].y = y;
				sprites[s].pattern = pattern;
						
				if (pattern==NOMOVE_EXPLOSION) c = 6;
				else if (pattern==NOMOVE_AST1) c = 11;
				else if (pattern==NOMOVE_AST2) c = 12;
				else c = 5;	
				
				sprites[s].colour = c;
				break;
			}
		}
	}
}

void updateNomoveObject(byte i)
{
	char decalx;
	char decaly;
	
	sprite_t *this_sprite;
	byte *this_sprite_x;
	byte *this_sprite_y;	
	byte *this_sprite_pattern;
	
	s_nomoveObject *this_nomoveObject;
	byte *this_nomoveObject_actif;
	byte *this_nomoveObject_sprno;
	
	
	decalx=decaly=0;
	
	decalx=-player.directionH;
	decaly=-player.directionV;

	this_nomoveObject = &nomoveObject[i];
	this_nomoveObject_actif = &this_nomoveObject->actif;
	
		if ((*this_nomoveObject_actif) == 1)
		{
			this_nomoveObject_sprno = &this_nomoveObject->sprno;
			this_sprite = &sprites[(*this_nomoveObject_sprno)];
			this_sprite_x = &this_sprite->x;
			this_sprite_y = &this_sprite->y;
			this_sprite_pattern = &this_sprite->pattern;
						
			(*this_sprite_x)+=decalx;
			(*this_sprite_y)+=decaly;
				
			// Faire l'animation en cas d'explosion !!
			if ((*this_sprite_pattern)>24*4) //explosion !!
			{
				if ((*this_sprite_pattern)==100)
				{
					stop_sound(3);
					stop_sound(4);
					stop_sound(5);
					play_sound(4);
					play_sound(5);
				}
				if ((timer&7)==0)
				{
					if ((*this_sprite_pattern)<27*4)
					{
						(*this_sprite_pattern)+=4;
					}
					else
					{
						(*this_nomoveObject_actif)=0; // sprite inactive.
						(*this_sprite_y)=INACTIF; // off screen.
					}
				}
			}
			// Fin animation
				
			if((*this_sprite_x)>192 || (*this_sprite_y)>191 ) {
				(*this_nomoveObject_actif)=0; // sprite inactive.
				(*this_sprite_y)=INACTIF; // off screen.								
			}
		}
}

void gererAINoMoveObject()
{	
	byte i;
	// Ici on va gérer leur intelligence Artificielle
	
	for (i=0;i<MAXNOMOVE;i++)
	{
		// On fait bouger
		updateNomoveObject(i);
	}
}

void declencherNoMoveObject()
{	
	// Ici on va créer les nomoves
	// --> Si il n'y à pas de motherShip à l'écran
	// --> On va créer selon le niveau de difficulté, timer et la direction du joueur, des nomoves
	byte startx;
	byte starty;
	byte r,r2;
	startx = 0;
	starty = 0;
	
	r = rnd(0,160);
	r2 = rnd(0,100);
	
	if (motherShipVisible==-1)
	if ((timer&31)==0)
	{
		if (r2<80)
		{
			if ((player.directionV == BAS))
			{
				startx = r;
				starty = 191;
			}
			else
			if ((player.directionV == HAUT))
			{
				startx = r;
				starty = 0;
			}
			else
			if ((player.directionH == DROITE))
			{
				starty = r;
				startx = 190;
			}
			else
			if ((player.directionH == GAUCHE))
			{
				starty = r;
				startx = 0;
			}
			
			if (r2<33) createNomoveObject(startx,starty,NOMOVE_MINE);
			else if (r2<66) createNomoveObject(startx,starty,NOMOVE_AST1);
			else createNomoveObject(startx,starty,NOMOVE_AST2);
		}
		
		
	}
	// Et on les fait réfléchir
	gererAINoMoveObject();
}

void initEnnemyBullet()
{
	byte i;
	
	for (i=0;i<MAXENNEMYBULLET;i++)
		ennemyBullet[i].flags=0;
}

void updatebullet(byte id)
{
	s_ennemyBullet *this_bullet;
	byte *this_bullet_flags;
    byte *this_bullet_sprno;
    byte *this_bullet_dx;
	byte *this_bullet_dy;
    int  *this_bullet_err;
	
	sprite_t *this_sprite;
	byte *this_sprite_x;
	byte *this_sprite_y;
	byte *this_sprite_pattern;
	
	
	byte boucle;
	byte i;
	int e2;
	
	this_bullet = &ennemyBullet[id];
	this_bullet_sprno = &this_bullet->sprno;
	this_bullet_flags = &this_bullet->flags;
	this_bullet_err = &this_bullet->err;
	this_bullet_dx = &this_bullet->dx;
	this_bullet_dy = &this_bullet->dy;
	
	this_sprite = &sprites[(*this_bullet_sprno)];
	this_sprite_x = &this_sprite->x;
	this_sprite_y = &this_sprite->y;
	this_sprite_pattern = &this_sprite->pattern;

	

	//byte s=ennemyBullet[id].sprno;
	//byte p=sprites[s].pattern;
	//byte dx=ennemyBullet[id].dx;
	//byte dy=ennemyBullet[id].dy;
	

	
	boucle = 1;
	

	if(((*this_bullet_flags)&BUL_ACTIVE)==0) return; // not active.
	
	if (((*this_sprite_pattern)>=(28<<2)) && ((*this_sprite_pattern)<=(31<<2))) boucle = 3;
	
	for (i=0;i<boucle;i++)
	{
		if((*this_sprite_x)>192 || (*this_sprite_y)>191) {
			(*this_bullet_flags)=0; // sprite inactive.
			(*this_sprite_y)=INACTIF; // off screen.
			return;
		}
		e2=(*this_bullet_err)<<1;
		if( e2 > -(*this_bullet_dy)) {
			(*this_bullet_err)-=(*this_bullet_dy);
			(*this_sprite_x)+=((*this_bullet_flags)&BUL_LEFT)?-1:1;
		}
		if( e2 < (*this_bullet_dx) ) {
			(*this_bullet_err)+=(*this_bullet_dx);
			(*this_sprite_y)+=((*this_bullet_flags)&BUL_UP)?-1:1;
		}	
	}
	if ((timer&1)==0)
	{
		(*this_sprite_x)-=player.directionH;
		(*this_sprite_y)-=player.directionV;
				
		if((*this_sprite_x)>192 || (*this_sprite_y)>191) {
			(*this_bullet_flags)=0; // sprite inactive.
			(*this_sprite_y)=INACTIF; // off screen.
			return;
		}	
	}
}

void initShoot()
{
	byte i;
	
	for (i=0;i<6;i++) {shoot[i].mvtx = 0;shoot[i].mvty = 0;shoot[i].currentChar=0;}
}


void renderMotherShipSprites(char t,char n)
{
	byte p;
	int calcx;
	int calcy;
	byte spriteRef;
	int decalx;
	int decaly;
	int rx;
	int ry;
	byte l;
	

	decalx = 0;
	decaly = 0;
	spriteRef = 0;

	calcx = refx+((scrollObj[n].staticx)<<3);
	calcy = refy+((scrollObj[n].staticy)<<3);
				
	scrollObj[n].pod = scrollObj[n].pod & 127; // Le motherShip est invisible, les pod aussi !!
	
	if ( (calcx>-12) && (calcx<24) )			// Si le mothership est visible
	{			
		if ( (calcy>-12) && ((calcy)<24) )
		{	
			scrollObj[n].pod = scrollObj[n].pod | 128; // Le motherShip est visible, les pod aussi
			motherShipVisible = t;
			calcx = calcx<<3;
			calcy = calcy<<3;
				// Affichage des pods
				l = 1;
				for (p=0;p<6;p++)
				{
					if (t==TILE_MOTHERSHIPV) spriteRef = p+10; else spriteRef = p+16;
					
					if (((scrollObj[n].pod & l) == l) ) // Si le pod doit être affiché car non détruit
					{
						if (t==TILE_MOTHERSHIPV)
						{
							decalx = pod_position[(p<<1)];
							decaly = pod_position[(p<<1)+1];
						}
						else
						{
							decalx = pod_position[(p<<1)+12];
							decaly = pod_position[(p<<1)+12+1];
						}	
									
						rx = calcx+decalx;
						ry = calcy+decaly;
						
						if (
							(((rx)>=0) && ((rx)<=176)) // Si le sprite est dans l'écran
							&&
							(((ry)>=-16) && ((ry)<=196))
		
						)
						{
							sprites[spriteRef].x = rx;
							sprites[spriteRef].y = ry;
						}					
						else
						{
							sprites[spriteRef].y = INVISIBLE;
						}
					}
					else
					{
						sprites[spriteRef].y = INVISIBLE;
					}
					
					l = l<<1;
				}	
				
				// Affichage du cache tank
				// Gestion des tirs
						decalx = 40;
						if (t==TILE_MOTHERSHIPV)
						{							
							decaly = 32-1;
							rx = calcx+decalx;
							ry = calcy+decaly;
							if (
							(((rx)>=0) && ((rx)<=176)) // Si le sprite est dans l'écran
							&&
							(((ry)>=-16) && ((ry)<=196))
		
							)
							{
								sprites[23].x = rx;
								sprites[23].y = ry;
								
								// Tir droit ?
								if ( (mTirDroitTimer>0) && ((timer&mTirDroitTimer)==0) )
								{
									//center_string(0,str(rx));pause();
									if (ry<(94-16)) createEnnemyBullet(29<<2,15,rx-3,ry,rx-3,ry+16);
									else if (ry>(94+16)) createEnnemyBullet(28<<2,15,rx-3,ry,rx-3,ry-16);
								}
								
								if ( (mTirDirigeTimer>0) && ((timer&mTirDirigeTimer)==0) )
								{
									createEnnemyBullet(21<<2,10,rx,ry,PLAYERSTARTX,PLAYERSTARTY);	
								}
							}					
							else
							{
								sprites[23].y = INVISIBLE;
							}
						}
						else
						{
							/*decalx = 40;*/
							decaly = 40-1;
							rx = calcx+decalx;
							ry = calcy+decaly;
							if (
							(((rx)>=0) && ((rx)<=176)) // Si le sprite est dans l'écran
							&&
							(((ry)>=-16) && ((ry)<=196))
		
							)
							{
								sprites[22].x = rx;
								sprites[22].y = ry;
								
								// Tir droit ?
								if ( (mTirDroitTimer>0) && ((timer&mTirDroitTimer)==0) )
								{
									//center_string(0,str(rx));pause();
									if (rx<(94-16)) createEnnemyBullet(30<<2,15,rx,ry-3,rx+16,ry-3);
									else if (rx>(94+16)) createEnnemyBullet(31<<2,15,rx,ry-3,rx-16,ry-3);
								}
								
								if ( (mTirDirigeTimer>0) && ((timer&mTirDirigeTimer)==0) )
								{
									createEnnemyBullet(21<<2,10,rx,ry,PLAYERSTARTX,PLAYERSTARTY);	
								}
							}else
														{
								sprites[22].y = INVISIBLE;
							}
						}	
						

				
				
		}
	}	
}

void renderMotherShipScrollObj(char t,char n)
{
	int calcx;
	int calcy;
	byte spriteRef;
	int decalx;
	int decaly;

	decalx = 0;
	decaly = 0;
	spriteRef = 0;
	 
	calcx = refx+((scrollObj[n].staticx)<<3);
	calcy = refy+((scrollObj[n].staticy)<<3);
				
	/*scrollObj[n].pod = scrollObj[n].pod & 127;*/ // Le motherShip est invisible, les pod aussi !!
	
	if ( (calcx>-12) && (calcx<24) )			// Si le mothership est visible
	{			
		if ( (calcy>-12) && ((calcy)<24) )
		{	
			put_frame_crop_H24(tiles_Pointer[t],calcx,calcy,tiles_Init[(t<<2)+1],tiles_Init[(t<<2)+2]);	
			motherShipVisible = t;
		}
	}	
}

void renderHUD()
{
	byte i;
	
	print_at(24,0,"HI-SCORE");
	print_at(26,1,str(player.hiscore));
	print_at(31,1,"0");
	print_at(24,2,"SCORE");
	print_at(26,3,str(player.score));
	print_at(31,3,"0");
	print_at(27,23,str(currentLevelAff));
	print_at(24,23,"ROUND ");
	
	
	for (i=0;i<player.nbLives;i++)
		put_frame0(life,24+(i<<1),21,2,2);
}

/*
void majScore()
{
	byte i;
	print_at(26,1,str(player.hiscore));
	print_at(26,3,str(player.score));
	for (i=0;i<player.nbLives;i++)
		put_frame0(life,24+(i<<1),21,2,2);
}*/

void renderPlayerOnRadar()
{
	radarPosx = 24 + (((refx*-1)) /28);
	radarPosy =  7 + (((refy*-1)) /14);
	
	if (radarPosx>31) radarPosx = 31;
	if (radarPosy>23) radarPosy = 23;

	radarOldCar = get_char_protected(radarPosx,radarPosy);	
	put_char_protected(radarPosx,radarPosy,3);
}

void initRadar()
{
	byte x,y,so;	
	nbMothershipLevel=0;
	
	put_frame0(fondRadar,24,7,8,13);
	
	for (so=0;so<MAXSCROLLOBJ;so++)
	{
		if ( (scrollObj[so].p!=INACTIF) /*&&  (scrollObj[so].p<10)*/ )
		{
			// Position x + Position X sur scrollobject / ratio ecran (224 caractères pour 32 en x = 7+1 Ecrans --> 224/8 car de radar = 28 RATIO
			// Position Y + Position Y sur scrollobject / ratio ecran (168 caractères pour 24 en y = 7+1 Ecrans --> 168/12 car de radar = 14 RATIO	
			x = 24+((scrollObj[so].staticx<<3)/28);
			y = 7+((scrollObj[so].staticy<<3)/14);
			nbMothershipLevel++;
			
			put_char_protected(x,y,1);
		}
	}
	
	renderPlayerOnRadar();
}

void renderRadar()
{	
	put_char(radarPosx,radarPosy,radarOldCar);
	renderPlayerOnRadar();
}

void renderScrollObj()
{
	byte i;
	s_scrollObj *this_scrollObj;
	byte *this_scrollObj_p;
	
		for (i=0;i<MAXSCROLLOBJ;i++)
		{
			this_scrollObj = &scrollObj[i];
			this_scrollObj_p = &this_scrollObj->p;
			
			// On render les mothership en caractères
			if ( ((*this_scrollObj_p)!=INACTIF ))
			{
				renderMotherShipScrollObj((*this_scrollObj_p),i);				
			}
		}
}
void renderScrollSprites()
{
	byte i;
	s_scrollObj *this_scrollObj;
	byte *this_scrollObj_p;
	
		for (i=0;i<MAXSCROLLOBJ;i++)
		{
			this_scrollObj = &scrollObj[i];
			this_scrollObj_p = &this_scrollObj->p;
			
			// On render les mothership en sprites
			if ( ((*this_scrollObj_p)!=INACTIF) )
			{
				renderMotherShipSprites((*this_scrollObj_p),i);				
			}
		}
}
void initScrollObj()
{
	byte i;
	
	for (i=0;i<MAXSCROLLOBJ;i++) 
	{
		scrollObj[i].p = INACTIF;
		scrollObj[i].pod = 1+2+4+8+16+32;
	}
}

char getFreeScrollObj()
{
	byte i;
	
	for (i=0;i<MAXSCROLLOBJ;i++) 
		if (scrollObj[i].p == INACTIF) return i;

	return -1;
}

void initSprites()
{
	byte i;

	for (i=0;i<32;i++) {sprites[i].y = INACTIF;sprites[i].x = 0;}
	
	// Réservation des sprites de pods 10 à 21
	// Cache tank 22 --> H et 23 --> V
	for (i=10;i<24;i++)
	{
		sprites[i].x = 0;
		sprites[i].y = INVISIBLE;
		sprites[i].pattern = 16<<2;
		sprites[i].colour = 14;
	}
}

void initPlayer()
{
	sprites[0].x = PLAYERSTARTX;
	sprites[0].y = PLAYERSTARTY;
	sprites[0].pattern = 0;
	sprites[0].colour = 6;
	sprites[1].x = PLAYERSTARTX;
	sprites[1].y = PLAYERSTARTY;
	sprites[1].pattern = 4;
	sprites[1].colour = 15;
	player.directionV = STATIQUE;
	player.directionH = STATIQUE;
	
	player.timerShoot = 0;
}

char getFreeShoot()
{
	char i;
	
	for (i=0;i<6;i++)
	{
		if ( (shoot[i].mvtx==0) && (shoot[i].mvty==0) ) return i;
	}
	
	return -1;
}

void detectCarShoot()
{
	byte i;
	byte cx,cy;
	
	s_shoot *this_shoot;
	byte 	*this_shoot_sprno;
	char	*this_shoot_mvtx;
	char	*this_shoot_mvty;
	byte    *this_shoot_currentChar;
	
	sprite_t *this_sprite;
	byte 	 *this_sprite_x;
	byte 	 *this_sprite_y;
	
	for (i=0;i<6;i++)
	{
		this_shoot = &shoot[i];
		this_shoot_sprno = &this_shoot->sprno;
		this_shoot_mvtx = &this_shoot->mvtx;
		this_shoot_mvty = &this_shoot->mvty;
		this_shoot_currentChar = &this_shoot->currentChar;
		this_sprite = &sprites[(*this_shoot_sprno)];
		this_sprite_x = &this_sprite->x;
		this_sprite_y = &this_sprite->y;
		
		if ( ((*this_shoot_mvtx)==0) && ((*this_shoot_mvty)==0) ) continue;
		//if ( ((*this_shoot_mvtx)!=0) || ((*this_shoot_mvty)!=0) )
		//{		
		cx = ((*this_sprite_x)+8)>>3;
		cy = ((*this_sprite_y)+8)>>3;
		if ((cx<25) && (cy<23) )
			(*this_shoot_currentChar) = get_char(cx,cy);
		//}
	}
}

void moveShoot()
{
	byte i;
	
	s_shoot *this_shoot;
	byte 	*this_shoot_sprno;
	char	*this_shoot_mvtx;
	char	*this_shoot_mvty;
	
	sprite_t *this_sprite;
	byte 	 *this_sprite_x;
	byte 	 *this_sprite_y;
	
	for (i=0;i<6;i++)
	{
		this_shoot = &shoot[i];
		this_shoot_sprno = &this_shoot->sprno;
		this_shoot_mvtx = &this_shoot->mvtx;
		this_shoot_mvty = &this_shoot->mvty;
		this_sprite = &sprites[(*this_shoot_sprno)];
		this_sprite_x = &this_sprite->x;
		this_sprite_y = &this_sprite->y;
		
		if ( ((*this_shoot_mvtx)!=0) || ((*this_shoot_mvty)!=0) )
		{
			(*this_sprite_x) += ((*this_shoot_mvtx)<<1);
			(*this_sprite_y) += ((*this_shoot_mvty)<<1);
			
			// On va bouger également par rapport au scrolling
			if ((timer&7)==0)
			{			
			
					if ((*this_shoot_mvtx)==0) // Si le shoot ne bouge pas horizontalement
					{
						(*this_sprite_x)-=player.directionH<<3;
					}

					if ((*this_shoot_mvty)==0) // Si le shoot ne bouge pas verticalement
					{
						(*this_sprite_y)-=player.directionV<<3;
					}					
			}
						
			if (
				((*this_sprite_x) > 196)
			   || ((*this_sprite_y)> (192-8))			   
			   )
			{
				(*this_shoot_mvtx) = 0;
				(*this_shoot_mvty) = 0;
				(*this_sprite_y) = INACTIF;
			}			
		}
	}
}



// S_TRUE _ Collision  

byte isCollision(int x1,int y1,byte h1,byte l1,int x2,int y2,byte h2,byte l2)
{
	if(x1 > x2+l2) return S_FALSE;
	if(x1+l1 < x2) return S_FALSE;
	if(y1 > y2+h2) return S_FALSE;
	if(y1+h1 < y2) return S_FALSE;
	
	return S_TRUE;
}

void desactivatePod(byte p,byte v)
{
	int calcx;
	int calcy;
	byte spriteRef;
	byte i;

	scrollObj[p].pod = scrollObj[p].pod & v;
	
	// Si tout les pods sont détruits, on désactive le tout !!
	if ( ( scrollObj[p].pod & 63) == 0 ) 
	{
		calcx = refx+((scrollObj[p].staticx)<<3);
		calcy = refy+((scrollObj[p].staticy)<<3);

		if (scrollObj[p].p==TILE_MOTHERSHIPV) spriteRef = 10; else spriteRef = 16;
		for (i=0;i<6;i++)		
			sprites[spriteRef+i].y = INVISIBLE;
		
		if (scrollObj[p].p==TILE_MOTHERSHIPV) sprites[23].y = INVISIBLE;
		else sprites[22].y = INVISIBLE;
		
		scrollObj[p].p = INACTIF;
		// Grosseux magouille pour effacer l'objet de l'écran !!
		disable_nmi();
		put_frame_crop_H24(tiles_Pointer[TILE_BLANK],calcx,calcy,11,11);
		enable_nmi();
		createNomoveObject((calcx<<3)+22,(calcy<<3)+22,NOMOVE_EXPLOSION);
		createNomoveObject((calcx<<3)+44,(calcy<<3)+44,NOMOVE_EXPLOSION);
		createNomoveObject((calcx<<3)+66,(calcy<<3)+66,NOMOVE_EXPLOSION);
		createNomoveObject((calcx<<3)+22,(calcy<<3)+66,NOMOVE_EXPLOSION);
		createNomoveObject((calcx<<3)+66,(calcy<<3)+22,NOMOVE_EXPLOSION);	
		//nbMothershipLevel--;
		
		nmiInitRadar=1;
		/*initRadar();*/		
		
	}
	
}

void checkCollision()
{
	byte i,j,k,dx,dy,l;
	int calcx,calcy;

	s_shoot *this_shoot;
	byte 	*this_shoot_sprno;
	char	*this_shoot_mvtx;
	char	*this_shoot_mvty;
	byte	*this_shoot_currentChar;

	sprite_t *this_sprite;
	byte 	 *this_sprite_x;
	byte 	 *this_sprite_y;
	
	s_alien	*this_alien;
	byte	*this_alien_sprno;
	byte	*this_alien_flag;
	
	sprite_t *this_sprite_alien;
	byte	*this_sprite_alien_x;
	byte	*this_sprite_alien_y;

	s_nomoveObject *this_nomoveObject;
	byte *this_nomoveObject_sprno;
	byte *this_nomoveObject_actif;
	
	sprite_t *this_sprite_nomoveObject;
	byte	*this_sprite_nomoveObject_x;
	byte	*this_sprite_nomoveObject_y;
	byte	*this_sprite_nomoveObject_pattern;
	byte	*this_sprite_nomoveObject_colour;

	s_ennemyBullet *this_ebullet;
	byte *this_ebullet_sprno;
	byte *this_ebullet_flag;
	
	sprite_t *this_sprite_ebullet;
	byte *this_sprite_ebullet_x;
	byte *this_sprite_ebullet_y;
	byte *this_sprite_ebullet_pattern;
//	byte *this_sprite_ebullet_colour;
	

	// Collision des objets par rapport au joueur !!
	// Collision avec décors
	if (
		(player.char_haut_gauche > 94) ||
		(player.char_haut_droite > 94) ||
		(player.char_bas_gauche > 94) ||
		(player.char_bas_droite > 94)
	)
		workflow = LOOSE_LIFE;
	// Collision avec les sprites
	// Avec Alien
	for (j=0;j<MAXALIEN;j++)
	{
		this_alien = &alien[j];
		this_alien_flag = &this_alien->flags;
		if (((*this_alien_flag)&BUL_ACTIVE)!=0)
		{					
			this_alien_sprno = &this_alien->sprno;
			this_sprite_alien = &sprites[(*this_alien_sprno)];
			this_sprite_alien_x = &this_sprite_alien->x;
			this_sprite_alien_y = &this_sprite_alien->y;
					
			if (isCollision((*this_sprite_alien_x),(*this_sprite_alien_y),16,16,94+2,94+2,12,12) == S_TRUE)
			{
				workflow = LOOSE_LIFE;
			}
		}
	}
	// Avec les nomoves
	for (j=0;j<MAXNOMOVE;j++)
	{
		this_nomoveObject = &nomoveObject[j];
		this_nomoveObject_actif = &this_nomoveObject->actif;
				
		if (((*this_nomoveObject_actif))==1)
		{
			this_nomoveObject_sprno = &this_nomoveObject->sprno;
			this_sprite_nomoveObject = &sprites[(*this_nomoveObject_sprno)];
			this_sprite_nomoveObject_x = &this_sprite_nomoveObject->x;
			this_sprite_nomoveObject_y = &this_sprite_nomoveObject->y;
			this_sprite_nomoveObject_pattern = &this_sprite_nomoveObject->pattern;
			this_sprite_nomoveObject_colour = &this_sprite_nomoveObject->colour;
					
			if ((*this_sprite_nomoveObject_pattern)!=NOMOVE_EXPLOSION)
			if (isCollision((*this_sprite_nomoveObject_x),(*this_sprite_nomoveObject_y),16,16,94+2,94+2,12,12) == S_TRUE)
			{
				if ((*this_sprite_nomoveObject_colour)!=6) // si on ne touche pas une explosion
				{
					workflow = LOOSE_LIFE;
				}
			}
		}
	}
	// Avec les aliensbullet !!
	for (j=0;j<MAXENNEMYBULLET;j++)
	{
		this_ebullet = &ennemyBullet[j];
		this_ebullet_flag = &this_ebullet->flags;
		if (((*this_ebullet_flag)&BUL_ACTIVE)!=0)
		{		
			this_ebullet_sprno = &this_ebullet->sprno;
			this_sprite_ebullet = &sprites[(*this_ebullet_sprno)];
			this_sprite_ebullet_x = &this_sprite_ebullet->x;
			this_sprite_ebullet_y = &this_sprite_ebullet->y;	
			this_sprite_ebullet_pattern	= &this_sprite_ebullet->pattern;	
			
			if ((*this_sprite_ebullet_pattern)==(21<<2))
			{
				if (isCollision((*this_sprite_ebullet_x)+6,(*this_sprite_ebullet_y)+6,5,5,94+5,94+5,8,8) == S_TRUE)
				{
					workflow = LOOSE_LIFE;
				}			
			}
			else
			{
				if (isCollision((*this_sprite_ebullet_x)+4,(*this_sprite_ebullet_y)+4,8,8,94+5,94+5,12,12) == S_TRUE)
				{
					workflow = LOOSE_LIFE;
				}						
			}
			
		}		
	}
	
	
	// Collisions relative aux shoot du joueur
	dx=dy=0;
	for (i=0;i<6;i++)
	{
		this_shoot = &shoot[i];
		this_shoot_sprno = &this_shoot->sprno;
		this_shoot_mvtx = &this_shoot->mvtx;
		this_shoot_mvty = &this_shoot->mvty;
		this_shoot_currentChar = &this_shoot->currentChar;
		this_sprite = &sprites[(*this_shoot_sprno)];
		this_sprite_x = &this_sprite->x;
		this_sprite_y = &this_sprite->y;				

		if ( ((*this_shoot_mvtx)!=0) || ((*this_shoot_mvty)!=0) )
		{
			// Avec Alien
			for (j=0;j<MAXALIEN;j++)
			{
				this_alien = &alien[j];
				this_alien_flag = &this_alien->flags;
				if (((*this_alien_flag)&BUL_ACTIVE)!=0)
				{					
					this_alien_sprno = &this_alien->sprno;
					this_sprite_alien = &sprites[(*this_alien_sprno)];
					this_sprite_alien_x = &this_sprite_alien->x;
					this_sprite_alien_y = &this_sprite_alien->y;
					
					if (isCollision((*this_sprite_x),(*this_sprite_y),16,16,(*this_sprite_alien_x),(*this_sprite_alien_y),16,16) == S_TRUE)
					{
						player.score+=5;
						(*this_alien_flag)=0;
						createNomoveObject((*this_sprite_alien_x),(*this_sprite_alien_y),NOMOVE_EXPLOSION);
						(*this_sprite_alien_y) = INACTIF;
						(*this_shoot_mvtx) = 0;
						(*this_shoot_mvty) = 0;
						(*this_sprite_y) = INACTIF;	
					}
				}
			}
			
			for (j=0;j<MAXNOMOVE;j++)
			{
				this_nomoveObject = &nomoveObject[j];
				this_nomoveObject_actif = &this_nomoveObject->actif;
				
				if (((*this_nomoveObject_actif))==1)
				{
					this_nomoveObject_sprno = &this_nomoveObject->sprno;
					this_sprite_nomoveObject = &sprites[(*this_nomoveObject_sprno)];
					this_sprite_nomoveObject_x = &this_sprite_nomoveObject->x;
					this_sprite_nomoveObject_y = &this_sprite_nomoveObject->y;
					this_sprite_nomoveObject_pattern = &this_sprite_nomoveObject->pattern;
					this_sprite_nomoveObject_colour = &this_sprite_nomoveObject->colour;
					
					if ((*this_sprite_nomoveObject_pattern)!=NOMOVE_EXPLOSION)
					if (isCollision((*this_sprite_x),(*this_sprite_y),16,16,(*this_sprite_nomoveObject_x),(*this_sprite_nomoveObject_y),16,16) == S_TRUE)
					{
						if ((*this_sprite_nomoveObject_colour)!=6) // si on ne touche pas une explosion
						{
							player.score+=1;
							createNomoveObject((*this_sprite_nomoveObject_x),(*this_sprite_nomoveObject_y),NOMOVE_EXPLOSION);	
							(*this_nomoveObject_actif)=0;
							(*this_sprite_nomoveObject_y) = INACTIF;
							(*this_shoot_mvtx) = 0;
							(*this_shoot_mvty) = 0;
							(*this_sprite_y) = INACTIF;		
						}
					}
				}
			}
			}
			
			if ( ((*this_shoot_mvtx)!=0) || ((*this_shoot_mvty)!=0) )
			{
			if ((*this_shoot_currentChar)>94) // Avec élément du décor
			{				
				// Shoot direct
				if ((*this_shoot_currentChar) > 251)
				{
					if ((tankAnimationPointer<16)) // Tank visible
					{
						for (j=0;j<MAXSCROLLOBJ;j++)
						{						
							if ( (scrollObj[j].p == TILE_MOTHERSHIPV) || (scrollObj[j].p == TILE_MOTHERSHIPH) )
							{
								calcx = (refx+((scrollObj[j].staticx)<<3))<<3;
								calcy = (refy+((scrollObj[j].staticy)<<3))<<3;
									
								if (isCollision((*this_sprite_x),(*this_sprite_y),16,16,calcx,calcy,88,88) == S_TRUE)
								{				
									player.score+=100;
									l=1;
									for (k=0;k<6;k++)
									{
										desactivatePod(j,255-l);
										l = l <<1;
									}		
								}
							}
						}
					}
				}
				else
				if ((*this_shoot_currentChar)>207) // Avec élément du décor destructible !!
				{					
					// On va vérifier qu'on est en contact avec un pod ou directement avec le mother ship
					for (j=0;j<MAXSCROLLOBJ;j++)
					{
						if (scrollObj[j].p !=INACTIF ) 
						{
								if ((scrollObj[j].pod & 128) == 128) // l'object est visible
								{
									// Récupération du point en haut à gauche en pixel du mothership
									calcx = (refx+((scrollObj[j].staticx)<<3))<<3;
									calcy = (refy+((scrollObj[j].staticy)<<3))<<3;
									
									if (isCollision((*this_sprite_x),(*this_sprite_y),16,16,calcx,calcy,88,88) == S_TRUE)
									{
										if  (scrollObj[j].p == TILE_MOTHERSHIPV)
										{
											// Test en suite du shoot de pod !
											l=1;
											for (k=0;k<6;k++)
											{
												dx = collisionv[k<<1];
												dy = collisionv[(k<<1)+1];

												if (isCollision((*this_sprite_x)+4,(*this_sprite_y)+4,8,8,calcx+dx,calcy+dy,16,16))
												{
													player.score+=10;
													desactivatePod(j,255-l); 
													createNomoveObject((*this_sprite_x)+4,(*this_sprite_y)+4,NOMOVE_EXPLOSION);
													break;
												}

												l = l <<1;
											}
										}
										else
										if  (scrollObj[j].p == TILE_MOTHERSHIPH)
										{
											// Test ensuite du shoot de pod
											l=1;
											for (k=0;k<6;k++)
											{
												dx = collisionh[k<<1];
												dy = collisionh[(k<<1)+1];
											
												if (isCollision((*this_sprite_x)+4,(*this_sprite_y)+4,8,8,calcx+dx,calcy+dy,16,16))
												{
													player.score+=10;
													desactivatePod(j,255-l); 
													createNomoveObject((*this_sprite_x)+4,(*this_sprite_y)+4,NOMOVE_EXPLOSION);
													break;
												}

												l = l <<1;
											}
										}
									}
								}
						}
					}
				}

			// On désactive le shoot
			shoot[i].mvtx = 0;
			shoot[i].mvty = 0;
			sprites[shoot[i].sprno].y = INACTIF;										
			}

		}
	}
}

/*
byte returnShootPatternDirection(char mvtx,char mvty)
{
		return(matrixShoot[1+mvtx][1+mvty]);
}
*/


void changePlayer(char dh,char dv,byte p1,byte p2)
{
	player.directionH = dh;
	player.directionV = dv;
	sprites[0].pattern = p1;
	sprites[1].pattern = p2;
}

void initStarfield()
{
	currentStarAnim = 19;
	
	stars[0].staticx =0;stars[0].staticy =0;//stars[0].pod =0;
	stars[1].staticx =10;stars[1].staticy =10;//stars[1].pod =0;
	stars[2].staticx =12;stars[2].staticy =20;//stars[2].pod =0;
	stars[3].staticx =20;stars[3].staticy =7;//stars[3].pod =0;
	stars[4].staticx =5;stars[4].staticy =22;//stars[4].pod =0;
	
}

void moveStarfield()
{
	byte so;/*moveUp,moveDown,moveLeft,moveRight,moveGlobal;*/
	char moveV,moveH;
		
	s_star *this_scrollObj;
	char *this_scrollObj_staticx;
	char *this_scrollObj_staticy;
	byte current;
	byte current_char;
	
	/*
	moveUp = 0;
	moveDown = 0;
	moveLeft = 0;
	moveRight = 0;
	
	moveGlobal =0;	*/
	moveV = 0;
	moveH = 0;
	
	// On anime
	
	if (player.directionV==HAUT)  
	{	
		/*
		currentStarAnim++; 		
		if ((currentStarAnim==13) || (currentStarAnim==21) || (currentStarAnim==29))
		{
			currentStarAnim-=3;moveUp=1;moveGlobal=1;
		}
		*/
		
		if ((currentStarAnim==12) || (currentStarAnim==20) || (currentStarAnim==28))
		{
			currentStarAnim-=2;moveV=1;/*moveUp=1;moveGlobal=1;*/
		}
		else
			currentStarAnim++; 
		
	}
	else
	if (player.directionV==BAS) 
	{		
		/*
		currentStarAnim--; 
		if ((currentStarAnim==9) || (currentStarAnim==17) || (currentStarAnim==25))
		{
			currentStarAnim+=3;moveDown=1;moveGlobal=1;
		}
		*/
		
		if ((currentStarAnim==10) || (currentStarAnim==18) || (currentStarAnim==26))
		{
			currentStarAnim+=2;moveV=-1;/*moveDown=1;moveGlobal=1;*/
		}
		else
			currentStarAnim--;
	}
			
	if (player.directionH==DROITE)
	{		
		/*
		currentStarAnim-=8; 
		if ((currentStarAnim==2) || (currentStarAnim==3) || (currentStarAnim==4))
		{
			currentStarAnim+=24;moveRight=1;moveGlobal=1;
		}
		*/
		if ((currentStarAnim==10) || (currentStarAnim==11) || (currentStarAnim==12))
		{
			currentStarAnim+=16;moveH=-1;/*moveRight=1;moveGlobal=1;*/
		}
		else
			currentStarAnim-=8; 		
	}
	else		
	if (player.directionH==GAUCHE)
	{
		/*
		currentStarAnim+=8; 
		if ((currentStarAnim==34) || (currentStarAnim==35) || (currentStarAnim==36))
		{
			currentStarAnim-=24;moveLeft=1;moveGlobal=1;
		}*/
		
		if ((currentStarAnim==26) || (currentStarAnim==27) || (currentStarAnim==28))
		{
			currentStarAnim-=16;moveH=1;/*moveLeft=1;moveGlobal=1;*/
		}	
		else
			currentStarAnim+=8;
	}

	for (so=0;so<5;so++)
	{
			this_scrollObj = &stars[so];

			this_scrollObj_staticx = &this_scrollObj->staticx;
			this_scrollObj_staticy = &this_scrollObj->staticy;
		
			//if (moveGlobal==1) // On change la position de l'étoile
			if ( ((moveH)!=0) || ((moveV)!=0) )
			{
				// On efface à l'ancienne position le cas échéant
				current_char = get_char((*this_scrollObj_staticx),(*this_scrollObj_staticy));
				if ( (current_char>8) && (current_char<31) )
					put_char((*this_scrollObj_staticx),(*this_scrollObj_staticy),92);	
						
				(*this_scrollObj_staticy)+=moveV;
				(*this_scrollObj_staticx)+=moveH;
				// On calcule les nouvelles coordonnées
				/*
				if (moveDown==1)  (*this_scrollObj_staticy)--; 
				else
				if (moveUp==1) (*this_scrollObj_staticy)++;
			
				if (moveRight==1) (*this_scrollObj_staticx)--; 
				else
				if (moveLeft==1) (*this_scrollObj_staticx)++;
				*/

				// On évite les débordements
				if ((*this_scrollObj_staticy)<0) (*this_scrollObj_staticy)=23;
				else
				if ((*this_scrollObj_staticy)>23) (*this_scrollObj_staticy)=0;

				if ((*this_scrollObj_staticx)<0) (*this_scrollObj_staticx)=23;
				else
				if ((*this_scrollObj_staticx)>23) (*this_scrollObj_staticx)=0;
			}
				
			// On trace si possible.
			current = get_char((*this_scrollObj_staticx),(*this_scrollObj_staticy));			
			if (( (current>8) && (current<31) )	|| 	(current==92))			
			{
				put_char((*this_scrollObj_staticx),(*this_scrollObj_staticy),currentStarAnim);
			}
	}
}

void setLevel(byte tas,byte tdt,int tdrt,int gent,byte genst)
{
	tankAnimationSpeed=tas;
	mTirDirigeTimer=tdt;
	mTirDroitTimer=tdrt;
	genEnnTimer=gent;
	genEnnShootTimer=genst;
}

void initLevel(byte level,byte reinit)
{
	byte i;
	byte current;
	byte p;
	char v;
	char *levelTab;

	
	//difficulty = 0;
	
	if (difficulty==0)       setLevel(0,255,0,511,255);
	else if (difficulty==1)  setLevel(0,255,511,511,255);
	else if (difficulty==2)  setLevel(0,255,511,255,255);
	else if (difficulty==3)  setLevel(1,255,511,255,255);
	else if (difficulty==4)  setLevel(1,127,255,255,255);
	else if (difficulty==5)  setLevel(1,127,255,255,255);
	else if (difficulty==6)  setLevel(3,127,255,255,127);
	else if (difficulty==7)  setLevel(3,63,255,127,127);
	else if (difficulty==8)  setLevel(3,63,127,127,127);
	else if (difficulty==9)  setLevel(3,63,127,127,127);
	else if (difficulty==10) setLevel(3,63,63,127,63);
	else if (difficulty>=11) setLevel(7,63,63,127,63);
	
	/*
	mTirDirigeTimer = 63;
	mTirDroitTimer = 127;
	genEnnTimer = 511;
	genEnnShootTimer = 255;
	
	tankAnimationSpeed=1; //1,3,7,15 etc etc ...*/
	if (tankAnimationSpeed==0)
	{
		sprites[23].pattern = tankAnimationV[0];
		sprites[22].pattern = tankAnimationH[0];
	}
	
	nbMothershipLevel=0;
	tankAnimationPointer=0;
	
	motherShipVisible = -1;
	/*
	refx = -224/2;
	refy = -168/2;
	*/
	//refx = -112/2;
	refx = -100/2;
	refy = -84/2;
	timer = 0;


	if (reinit==0)
	{
		for (i=0;i<MAXSCROLLOBJ;i++)
			scrollObj[i].p = INACTIF;
		
		current = 0;
		p=0;
		v=0;
		levelTab = levels_Pointer[level-1];
		while (v!=-1)
		{
			scrollObj[current].p = *(levelTab+p);
			scrollObj[current].staticx = *(levelTab+p+1);
			scrollObj[current].staticy = *(levelTab+p+2);
			v = *(levelTab+p+3);	
			current++;			
			p+=3;
		}
	}
	player.directionH = STATIQUE;player.directionV = BAS;sprites[0].pattern = 8;sprites[1].pattern = 12;	
	//initRadar();
}

void main_loop()
{
	char sp,sh;	// Shoot pattern + shoot number
	char s;
	byte i;
	
	sp=s=sh=0;
	traceSprite = 1;
	while(workflow==INGAME) 
	{
		// Le point de référence se déplace à l'inverse d'un sprite

			if (keypad_1==0) {stop_music();soundonoff=0;}
			if (keypad_1==1) {play_music(music);soundonoff=1;}
		
			if ((joypad_1 & (UP|LEFT))==(UP|LEFT)) changePlayer(GAUCHE,HAUT,15<<2,14<<2);
			else
			if ((joypad_1 & (UP|RIGHT))==(UP|RIGHT)) changePlayer(DROITE,HAUT,9<<2,8<<2);
			else
			if ((joypad_1 & (DOWN|LEFT))==(DOWN|LEFT)) changePlayer(GAUCHE,BAS,13<<2,12<<2);
			else
			if ((joypad_1 & (DOWN|RIGHT))==(DOWN|RIGHT)) changePlayer(DROITE,BAS,11<<2,10<<2);
			else			
			if (joypad_1 & LEFT) changePlayer(GAUCHE,STATIQUE,24,28);
			else
			if (joypad_1 & RIGHT)  changePlayer(DROITE,STATIQUE,16,20);
			else
			if (joypad_1 & UP)  changePlayer(STATIQUE,HAUT,0,4);
			else
			if (joypad_1 & DOWN)  changePlayer(STATIQUE,BAS,8,12);
			
			if  ( (joypad_1 & (FIRE1|FIRE2) ) && (player.timerShoot==0) ) 
			{
				for (i=0;i<2;i++) // 2 shoots !
				{
					sh=getFreeShoot();
					if (sh==-1) break;
					s=getFreeSprite();
					if (s==-1) break;	
						if (i==0)
						{
							shoot[sh].mvtx = player.directionH;
							shoot[sh].mvty = player.directionV;
						}else
						{
							shoot[sh].mvtx = player.directionH*-1;
							shoot[sh].mvty = player.directionV*-1;						
						}
						stop_sound(3);
						play_sound(3);						
						sp = matrixShoot[1+player.directionH][1+player.directionV];
						// Réserver le sprite
						shoot[sh].sprno = s;
						sprites[s].colour = 14;
						sprites[s].x= sprites[0].x;
						sprites[s].y= sprites[0].y;						
						sprites[s].pattern = sp;
				}
			
				player.timerShoot = 25;
			}
			
			if (player.timerShoot>0) player.timerShoot--;
			
		if ((timer&1)==0) {nmiMoveStarfield=1;delay(1);}
		if ((timer&7)==0)
		{

			refx +=(-player.directionH);
			refy +=(-player.directionV);

			if (refx==-225) refx = 0;
			else
			if (refx==1) refx=-224;
			
			if (refy==-169) refy = 0;
			else
			if (refy==1) refy =-168;
			
			motherShipVisible = -1;
			/* On fait bouger les sprites avant de tracer les mothetship, pour pas tomber dans un nmi */
			renderScrollSprites();
			nmiRenderScrollObj=1;		
			if ((timer&15)==0) nmiRenderRadar = 1; 

		}
		
		//if ((timer&1)==0) nmiMoveStarfield=1;
		/*
		if ((timer&7)==0)
		{
			nmiRenderScrollObj=1;		
			if ((timer&15)==0) nmiRenderRadar = 1; 
		}
		*/
		traceSprite=1;
	
		//delay(1);
		
		moveShoot();
		nmiDetectCarShoot = 1;
		
		declencherNoMoveObject();
		declencherAlien();		
		for (i=0;i<MAXENNEMYBULLET;i++) updatebullet(i);
		
		if (((timer&tankAnimationSpeed)==0) && (motherShipVisible!=-1) && (tankAnimationSpeed>0))
		{	
			sprites[23].pattern = tankAnimationV[tankAnimationPointer];
			sprites[22].pattern = tankAnimationH[tankAnimationPointer];
						
			tankAnimationPointer++;
			if (tankAnimationPointer>47)
			{
				if (tankAnimationSpeed==1)
					tankAnimationPointer = 0;
				else if (tankAnimationSpeed==3)
					tankAnimationPointer = 8;
				else
					tankAnimationPointer = 12;
			}
		}

		if ((timer&3)==0) {checkCollision();}	
				
		
		timer++;
		
		if (nbMothershipLevel==0) workflow = NEXT_LEVEL;
		
		if (((player.score)==2000) && (player.nbLives<4)) 
		{
			player.score++;
			player.nbLives++;
			delay(1);
			renderHUD();	
			initRadar();
		} 
		
		if (player.score>player.hiscore)
		{
			player.hiscore = player.score;
		}

		
	}
}

/*
void LoadPatternAndshowAScreen(char* p,char *c,char *n,char show)
{
			disable_nmi();			
			screen_off();			
			cls();
			load_patternrle(p);			
			rle2vram(c,coltab);
			duplicate_pattern();
			if (show==1) rle2vram(n,chrtab);							
			screen_on();			
			enable_nmi();
}*/

void LoadPatternAndshowAScreenDan0(char* p,char *c,char *n,char show)
{
	disable_nmi();			
	screen_off();	
	if (show==1) dan0alt(chrtab,n);
	dan0alt(chrgen,p);	
	dan0alt(coltab,c);
	duplicate_pattern();
	screen_on();
	enable_nmi();			
}

void makeAPause()
{
		while ((!(joypad_1 & FIRE1)) && (!(joypad_1 & FIRE2)) ) {}
		while ((joypad_1 & FIRE1) || (joypad_2 & FIRE1)) {}
}

void initData(byte reinit)
{
			initEnnemyBullet();
			if (reinit==0) initScrollObj();
			initSprites();
			if (reinit==0) initNomoveObject();
			initStarfield();
			initPlayer();
			initAlien();
			initShoot();	
			initLevel(currentLevel,reinit); // Initialisation du level 1 (pas de réinit)
}

void secretCode(void)
{/*
	byte currentPos;
	byte nbOk,posx;
	char valSaisie;
	
	currentPos = 0;
	nbOk=0;
	valSaisie=-1;
	posx=12;
	
	delay(1);
	print_at(7,15,"ENTER ACCESS CODE");
	print_at(12,17,"- - - -");
	
	while(1)
	{
		if ((keypad_1)==0) valSaisie=0;
		else if ((keypad_1)==1) valSaisie=1;
		else if ((keypad_1)==2) valSaisie=2;
		else if ((keypad_1)==3) valSaisie=3;
		else if ((keypad_1)==4) valSaisie=4;
		else if ((keypad_1)==5) valSaisie=5;
		else if ((keypad_1)==6) valSaisie=6;
		else if ((keypad_1)==7) valSaisie=7;
		else if ((keypad_1)==8) valSaisie=8;
		else if ((keypad_1)==9) valSaisie=9;
		
		if (valSaisie!=-1)
		{
			if (currentPos==0) posx = 12;
			else if (currentPos==1) posx = 14;
			else if (currentPos==2) posx = 16;
			else if (currentPos==3) posx = 18;
			
			delay(1);
			if (valSaisie==0) put_char(posx,17,'0');
			else if (valSaisie==1) put_char(posx,17,'1');
			else if (valSaisie==2) put_char(posx,17,'2');
			else if (valSaisie==3) put_char(posx,17,'3');
			else if (valSaisie==4) put_char(posx,17,'4');
			else if (valSaisie==5) put_char(posx,17,'5');
			else if (valSaisie==6) put_char(posx,17,'6');
			else if (valSaisie==7) put_char(posx,17,'7');
			else if (valSaisie==8) put_char(posx,17,'8');
			else if (valSaisie==9) put_char(posx,17,'9');
			
			if ((currentPos==0) && (valSaisie==1)) nbOk++;
			if ((currentPos==1) && (valSaisie==9)) nbOk++;
			if ((currentPos==2) && (valSaisie==7)) nbOk++;
			if ((currentPos==3) && (valSaisie==4)) nbOk++;
			
			while ((keypad_1)<=9) {};
			
			currentPos++;
			if (currentPos>3)
			{
				currentPos=0;
				if (nbOk!=4) nbOk = 0;
				delay(1);
				print_at(12,17,"- - - -");
			}
			valSaisie=-1;
		}
		
		if (nbOk==4) break;
	}	
	
	print_at(7,15,"  ACCESS GRANTED ");
	delay(50);*/
	pause();

}

void main(void)
{	
	byte i,j;
	soundonoff=1;
	mynmi=0;
	oddNmi = 0;
	nmiRenderRadar = 0;
	nmiMoveStarfield = 0;
	nmiRenderScrollObj = 0;
	nmiDetectCarShoot = 0;
	nmiInitRadar = 0;
	player.score = 0;
	player.hiscore = 2000;
    set_snd_table(snd_table);
	stop_music();
	
	screen_mode_2_bitmap();
	vdp_out(3,0x9f); /* Pour empécher des bugs de dédoublonnage de sprite ? */
	vdp_out(4,0x3);
	
	while(1)
	{
		if (workflow==SHOW_SPLASH0)
		{
			LoadPatternAndshowAScreenDan0(SPLASH0_PATTERNDAN0,SPLASH0_COLORDAN0,SPLASH0_NAMEDAN0,1);
			center_string(20,"STARCOM IS A TRADEMARK OF");
			center_string(21,"COLLECTORVISION INDUSTRIES INC.");
			/* Saisie du code secret */
			secretCode();			
			/* Fin Saisie du code secret */			

			workflow = SHOW_STORY;
		
		}
		//else
		if (workflow==SHOW_STORY)
		{
			LoadPatternAndshowAScreenDan0(SPLASH1_PATTERNDAN0,SPLASH1_COLORDAN0,SPLASH1_NAMEDAN0,1);
			center_string(15,"STARCOM IS A SPECIAL UNIT");
			center_string(16,"IN THE GROWING");
			center_string(17,"PLANETARY COMMUNITY");
			center_string(19,"THE MAIN OBSTACLE TO PEACE IS");
			center_string(20,"...");
			makeAPause();
			LoadPatternAndshowAScreenDan0(SPLASH2_PATTERNDAN0,SPLASH2_COLORDAN0,SPLASH2_NAMEDAN0,1);
			center_string(15,"THE SHADOW FORCE, AN ARMY");
			center_string(16,"LEAD BY"); 
			center_string(17,"THE SINISTER EMPEROR DARK.");
			center_string(18,"HIS PLAN IS TO");
			center_string(19,"RULE THE SOLAR SYSTEM.");
			center_string(21,"NOW, STOP HIM !");
			makeAPause();		
			workflow = SHOW_TITLE;			
		}
		//else
		if (workflow==SHOW_TITLE)
		{
			player.score=0;
			stop_music();
			LoadPatternAndshowAScreenDan0(TITLE_PATTERNDAN0,TITLE_COLORDAN0,TITLE_NAMEDAN0,1);
			center_string(0,"DIFFICULTY LEVEL");
			center_string(1,"1");
			center_string(17,"MUSIC ON ");
			center_string(20,"(C) 2012 COLLECTORVISION");
			center_string(22,"(C) 1986 COLECO INDUSTRIES");
			difficulty = 0;
			
			while ((!(joypad_1 & FIRE1)) && (!(joypad_1 & FIRE2)) ) 
			{
				delay(5);
				center_string(12,"JOIN THE SPACE FORCE !");
				delay(5);
				center_string(12,"                      ");
				if ((keypad_1)==1) {difficulty=0;center_string(1,"1");}
				if ((keypad_1)==2) {difficulty=3;center_string(1,"2");}
				if ((keypad_1)==3) {difficulty=6;center_string(1,"3");}
				if ((keypad_1)==4) {difficulty=9;center_string(1,"4");}
				if ((joypad_1 & LEFT) && (soundonoff==0)) {soundonoff=1;center_string(17,"MUSIC ON ");}
				if ((joypad_1 & RIGHT) && (soundonoff==1)) {soundonoff=0;center_string(17,"MUSIC OFF");}
				//if ((keypad_1)==8) {center_string(3,"CODING BY MICHEL LOUVET");}
			}
			player.nbLives = 2;
									stop_sound(3);
						play_sound(3);
						delay(15);
			/*
			initEnnemyBullet();
			initScrollObj();
			initSprites();
			initNomoveObject();
			initStarfield();
			initPlayer();
			initAlien();
			initShoot();	
			initLevel(1,0); // Initialisation du level 1 (pas de réinit)*/
			currentLevel=1;
			currentLevelAff=1;
			initData(0);
			
			
			workflow = INGAME;
		}		
		//else
		if (workflow==INGAME)
		{		
			screen_off;
			disable_nmi();
			cls();
			load_patternrle(PATTERNRLE);
			rle2vram(COLORRLE,coltab);
			duplicate_pattern();
			for (i=0;i<32;i++)
			for(j=0;j<24;j++)
				put_char(i,j,92);
			rle2vram(SPATTERNRLE,sprtab);
	
			renderHUD();	
			initRadar();
			screen_on;
			enable_nmi();
			
			traceSprite=1;			
			mynmi=1;
			stop_music();
            if (soundonoff==1) play_music(music);
			main_loop();
		}
		//else
		if (workflow==NEXT_LEVEL)
		{
				stop_music();
				LoadPatternAndshowAScreenDan0(SPLASH1_PATTERNDAN0,SPLASH1_COLORDAN0,SPLASH1_COLORDAN0,0);
				screen_off();
				initSprites();	
				delay(1);
				screen_on();
				i=0;
				while ((joypad_1 & FIRE1) || (joypad_2 & FIRE1)) {}				
				while ((!(joypad_1 & FIRE1)) && (!(joypad_1 & FIRE2)) ) {
					delay(5);								
					mynmi=0;
					center_string(12,"GET READY FOR NEXT ZONE !");
					delay(5);
					center_string(12,"                         ");
					i++;
					if (i>5) break;
				}
				workflow=INGAME;
				currentLevel++;
				currentLevelAff++;
				if (currentLevel>MAXLEVEL) currentLevel=3;
				
				if ((currentLevel&1)==0) difficulty++;
				initData(0);
				// Augmenter le level !!
		}		
		
		if (workflow==LOOSE_LIFE)
		{
				// Enlever une vie, faire une animation ?
									stop_sound(3);
					stop_sound(4);
					stop_sound(5);
					play_sound(4);
					play_sound(5);
				for (i=2;i<32;i++) sprites[i].y = 204;
				j=25;
				while (j<28)
				{
					sprites[0].x-=2;
					sprites[0].pattern = (j<<2);
					sprites[1].pattern = (j<<2);
					sprites[1].x+=2;
					
					j+=1;
					delay(10);
				}
				
				sprites[0].y=203;
				sprites[1].y=203;
				delay(1);
				
				if (player.nbLives>0) 
				{
					player.nbLives--; 
					initData(1);
					workflow = INGAME;
				}
				else workflow = GAME_OVER;
		}
		//else
		if (workflow==GAME_OVER)
		{
				LoadPatternAndshowAScreenDan0(SPLASH1_PATTERNDAN0,SPLASH1_COLORDAN0,SPLASH1_COLORDAN0,0);
				screen_off();
				initSprites();	
				delay(1);
				disable_nmi();
				fill_vram(chrtab,32,32*24);
				enable_nmi();
				screen_on();
				
				stop_music();
				play_music(music_go);
			
				while ((joypad_1 & FIRE1) || (joypad_2 & FIRE1)) {}				
				while ((!(joypad_1 & FIRE1)) && (!(joypad_1 & FIRE2)) ) {
					delay(5);								
					mynmi=0;
					center_string(10,"GAME OVER");
					delay(5);
					center_string(10,"                         ");
					center_string(13,"FINAL SCORE");
					center_string(14,str(player.score));
					print_at(19,14,"0");
				}
				workflow=SHOW_TITLE;
		}		
	}

}


void nmi()
{		update_music();
		if (mynmi==1)
		{
				// Faire toujours le tracé de sprite en premier !! Evite glitch sprite !
			if (traceSprite)
			{

				if (oddNmi) {put_vram (0x1b00,sprites,128); oddNmi=0;}
				else 
				{
					memcpyb(bsprites,sprites+16,64);
					memcpyb(bsprites+16,sprites,64);
					put_vram (0x1b00,bsprites,128);	
					oddNmi=1;
				}
			}

			if (nmiRenderRadar)
			{
				nmiRenderRadar=0;
				renderRadar();
			}
			if (nmiInitRadar)
			{
				nmiInitRadar=0;
				initRadar();
			}
			if (nmiRenderScrollObj)
			{
				nmiRenderScrollObj=0;
				renderScrollObj();
				renderHUD();
			}
			if (nmiMoveStarfield)
			{ 
				nmiMoveStarfield=0;
				moveStarfield();
			}
			
			if (nmiDetectCarShoot)
			{
				nmiDetectCarShoot = 0;
				detectCarShoot();
			}
			
			player.char_haut_gauche = get_char(12,12);
			player.char_haut_droite = get_char(13,12);
			player.char_bas_gauche = get_char(12,13);
			player.char_bas_droite = get_char(13,13);
			
		}
					
}


