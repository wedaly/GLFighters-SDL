#include "game.h"
#include "input.h"
#include "models.h"
#include "print.h"
#include "sound.h"
#include "textures.h"
#include <GL/gl.h>
#include <cstdio>

bool light;
bool lp;
bool fp;
bool sp;
bool constantswordtrail;
bool AIOffensive;
bool autorespawn;
bool unlimitedammo;
bool nodraw;

float M[16];
float display;
float targetz;
float holding[16];
float holdingtype[16];
float lightningdelay[17];
float swordtraildelay[17];
int attacker[17];
int pathfindsteps;
int firstperson;
int firstshot[17];
int oldguy[17];
int oldnum[17];
int goneplayers;
int exists[17];
int cube;
int itemtype[17];
int attach[17];
int blendtype;
int blendtype2;
int computercontrolled[17];
int computertarget[17];
int computertargetxlocation[17];
int computertargetylocation[17];
int compxstep[17][100];
int compystep[17][100];
int compxsteptest[17][100];
int compysteptest[17][100];
int screenwidth;
int screenheight;
bool pathfound[17];
float sabrespin[17];
int abouttobehit[17];

float jetsmokedelay[17];

int swordtrailtoggle[17][2];
int health[17];
int oldhealth[17];
int delaytime[17];
int lighting;
int showinfo;
int deathcount[17];
float speedmult[17];
int jetglownum[17];
int usingjetpack[17];
int changablejump;
int fake[17];
float size[17];
float ammo[17];
int jetpack[17];
int numplayers;
int part1;
int part2;
int facing[17];
int p1 = 0;
int p2 = 1;
int frame[17];
int targetframe[17];
int activity[17];
int fogtoggle;
int fallin[17];
int themebasenum;
int themeropenum;
int themebacknum;
int verydeadshow;
float litx[6];
float lity[6];
float lightbrightness[6];
int lighton[6];
int freezetime;
int oldtime[17];
int invisible[17];
int trail;
int mapeditor;
int randomint2;
int whichhurt;
float cloaktime[17];
float slide = 0;
int randomint;
int escapekeydown;
int theme;
int nosound;
int unusedsprite;
GLfloat lightx;
GLfloat lighty;
GLfloat lightz;
int HelmetNum[17];
int LowerLegNum[17];
int UpperArmNum[17];
int ShoesNum[17];
int TorsoNum[17];
float xrot;         // X Rotation
float yrot;         // Y Rotation
GLfloat xspeed;     // X Rotation Speed
GLfloat yspeed;     // Y Rotation Speed
GLfloat z = -10.0f; // Depth Into The Screen
GLfloat boomy;
int uppressed[17];
int rightshootpressed[17];
int attackpressed[17];
int leftshootpressed[17];
int dead[17];
float gravity;
float multiplier, multiplier2, multiplier3, multiplier4, multiplier5, end, start, timetaken, framespersecond;
struct
{
  unsigned long mm_timer_start;
  unsigned long mm_timer_elapsed;
} timer;

#define kMaxLightning 30
int unusedlightning;
float lightningfxdelay[17];
class LightningBolt {
public:
  float LightningPoint[100][4];
  float brightness;
  int tesselation;
  float yrotation;
  float zrotation;
  float x, y, z;
};

LightningBolt Lightning[kMaxLightning];

float smokingbody[17][16];
float smokingbodydelay[17][16];
float rotation[17];
float targetrotation[17];
long leftlowarm[3][20][50];
long lefthigharm[3][20][50];
long lefthand[3][20][50];
long rightlowarm[3][20][50];
long righthigharm[3][20][50];
long righthand[3][20][50];
long torsorotation[3][20][50];
long hippos[3][20][50];
long hiprot[3][20][50];
long torsorot[3][20][50];
long leftfoot[3][20][50];
long leftlowleg[3][20][50];
long lefthighleg[3][20][50];
long rightfoot[3][20][50];
long rightlowleg[3][20][50];
long righthighleg[3][20][50];
long head[3][20][50];
long speed[20][50];
GLuint Map[100][100];
GLuint Walls[100][100];
int selected;
float time[17];
long framenum[17];
int timedirection[17];
int anim[51];
int targetanim[51];
int scalenormals;
int guytrack;
int slowdown;
int wireframe;
int selectedx;
int selectedy;
int skin[17];
int itemnum[17];

#define maxsprites 300
#define maxswordtrail 30
struct
{
  float x, y, z;
  float oldx, oldy, oldz;
  float velx, vely, velz;
  float brightness, size, spin, spin2, type;
  int fading;
  int stage;
  int type2;
  float delay;
  float life;
  int owner;
} sprite[maxsprites];

class SwordTrail {
public:
  float TrailPoint[maxswordtrail][6];
  float brightness[maxswordtrail][4];
};

int unusedswordtrail[17];
SwordTrail SwordTrail[17][2];

struct
{
  int up, left, right, down, front, back;
} environment[10];

class Point3D {
public:
  float x;
  float y;
  float z;
};

Point3D point;
Point3D righthandpoint;
Point3D lefthandpoint;
GLUquadricObj *quadratic; // Storage For Our Quadratic Objects

GLuint gFontList;

GLfloat LightAmbient[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat LightPosition[] = {0.0f, 0.0f, 10.0f, 0.0f};

GLfloat LightDiffuse2[] = {1.0f, 0.5f, 0.0f, 0.9f};
GLfloat LightPosition2[] = {0.0f, 1.0f, 0.0f, 1.0f};

GLuint base;
GLuint filter;       // Which Filter To Use
GLuint texture[100]; // Storage For 6 Textures (MODIFIED)
// TK_RGBImageRec	*tempTexture;
GLuint object = 1; // Which Object To Draw
GLfloat boomstage;
GLfloat boomsize;
GLfloat boomx;
GLfloat shockx;
GLfloat shockx2;
GLfloat fogColor[4] = {0.5f, 0.5f, 0.5f, 1.0f}; // Fog Color
short sFile = 0;
float guyx[17];
float guyy[17];
float oldguyx[17];
float oldguyy[17];
int guymapx[17];
int guymapy[17];
int startplacex[17];
int startplacey[17];
int playerstartnum;
float guyvely[17];
float guyvelx[17];

float cameray;
float camerax;
float cameraz;
float targetcameray;
float targetcamerax;
float jumpstrength;
SndCommand sndCommand;
SndChannelPtr psndChannel[41];
Handle hSound[50];
GLuint unusedchannel;
bool gQuit = false;

int kRightShootKey[17];
int kLeftShootKey[17];
int kRightKey[17];
int kLeftKey[17];
int kUpKey[17];
int kDownKey[17];
int kAttackKey[17];
int kBlockKey[17];

int kRightShootKeydown[17];
int kLeftShootKeydown[17];
int kRightKeydown[17];
int kLeftKeydown[17];
int kUpKeydown[17];
int kDownKeydown[17];
int kAttackKeydown[17];
int kBlockKeydown[17];

float gamespeed;

#define Pstr unsigned char *
#define Cstr char *

#define FILE_ERROR_ALERT 138
#define OLD_SAVE_VERSION 139
#define UNREADABLE_SCORES_ALERT 140

#define SAVE_WARNING_ID 132
#define PB_SAVE 1
#define PB_CANCEL 2
#define PB_DONT_SAVE 3

#define FILE_ERROR_STRINGS 129
#define FILE_ERROR_PREFIX 1
#define FILE_ERROR_SUFFIX 2

#define SAVE_WARNING_STRINGS 132

#define FILE_STRINGS 130
#define SAVE_GAME_STRING 1
#define SAVE_SCORES_STRING 2
#define SCORES_NAME_STRING 3
#define SAVE_JOURNAL_STRING 4
#define JOURNAL_NAME_STRING 5
#define UNTITLED_STRING 6
#define SAVE_FORM_STRING 7
#define FORM_NAME_STRING 8

#define REGISTRATION_FORM 136

#define FILE_NAME_SIZE 32
#define ERROR_LENGTH 80

#define idle1 1
#define idle2 2
#define runleft 3
#define runright 4
#define ducking 5
#define falling 6
#define climbrope 7
#define onrope 8
#define downrope 9
#define jumpstraight 10
#define leftflip 11
#define rightflip 12
#define leftroll 13
#define rightroll 14
#define splat 15
#define shootleft 16
#define wallhit 17
#define shootright 18
#define deadfacedown 19
#define fallbackwardsright 20
#define landonback 21
#define deadfaceup 22
#define fallbackwardsleft 23
#define hitwallleft 24
#define hitwallright 25
#define breakneckleft 26
#define brokeneckleft 27
#define breakneckright 28
#define brokeneckright 29
#define impaleleft 30
#define impaledleft 31
#define impaleright 32
#define impaledright 33
#define swordthrowleft 34
#define swordthrownleft 35
#define swordthrowright 36
#define swordthrownright 37
#define painoneleft 38
#define paintwoleft 39
#define painoneright 40
#define paintworight 41
#define getupfromback 42
#define getupfromfront 43
#define swordidleleft 44
#define swordidleright 45
#define swordrightthrust 46
#define swordleftthrust 47
#define swordrightparry 48
#define swordleftparry 49
#define jetleft 50
#define jetright 51
#define jetup 52
#define jetidle 53
#define jetdown 56
#define jetimpaleleft 57
#define jetimpaledleft 58
#define jetimpaleright 59
#define jetimpaledright 60
#define duckimpaleleft 61
#define duckimpaledleft 62
#define duckimpaleright 63
#define duckimpaledright 64
#define swordrightspin 65
#define swordleftspin 66
#define fallforwardsright 67
#define landonfront 68
#define fallforwardsleft 69
#define painthreeleft 70
#define painthreeright 71
#define grenidleleft 72
#define grenidleright 73
#define grenshootleft 74
#define grenshootright 75

#define marbletheme 0
#define trontheme 1
#define woodtheme 2
#define metaltheme 3
#define matrixtheme 4
#define islandtheme 5
#define lavatheme 6
#define snowtheme 7
#define shinytheme 8

#define nothing 0
#define spawnstars 1
#define deletestars 2
#define invisiblestars 3
#define invisiblestars2 4
#define lasersprite 5
#define tracersprite 6
#define muzzleflashstars 7
#define wallsparks 8
#define bouncesprite 9
#define JetPackGlow 10
#define smokesprite 11
#define water 12
#define bloodsparks 13
#define lasersparks 14
#define grenade 15
#define exploflamer 16
#define exploflame 17
#define chunk 18
#define lightningflashstars 19

#define kHip 0
#define kTorso 1
#define kHead 2
#define kRightUpperArm 3
#define kRightLowerArm 4
#define kRightHand 5
#define kLeftUpperArm 6
#define kLeftLowerArm 7
#define kLeftHand 8
#define kRightUpperLeg 9
#define kRightLowerLeg 10
#define kRightFoot 11
#define kLeftUpperLeg 12
#define kLeftLowerLeg 13
#define kLeftFoot 14
#define kRightGun 15

char szSavedGameName[FILE_NAME_SIZE + 1];
short sSavedGameVolume;
SFReply sfReply;
Boolean bGameSaved;

int CheckAIKey(int whichguy, int which);
void MakeSprite(float x, float y, float z, float brightness, float type, float spin, float size, float spin2, float velx, float vely, float velz);
GLfloat RangedRandom(GLfloat low, GLfloat high);
Point3D FindRightGunPoint(int whichguy);
Point3D FindLeftGunPoint(int whichguy);
Point3D DoRotation(Point3D thePoint, float xang, float yang, float zang);
Point3D FindJetPackPos(int whichguy);
void Explode(int which);
void DrawGuy(int whichguy, int sabre);
void restartRound();
Point3D FindEyeRot(int whichguy);
Point3D FindEyePoint(int whichguy);
void WallBounds(int toggle);
Point3D FindBodyPart(int whichguy, int whichpart);
/********************> LoadGLTextures() <*****/
//-----------------------------------------------------------------------------------------------------------------------
float absolute(float num) {
  if (num < 0)
    num *= -1;
  return num;
}

void LoadNamedMap(Str255 Name) {
  Boolean bLoaded = false;
  long lSize;
  long lLongSize = sizeof(long);

  int x, y, kl;
  sSavedGameVolume = 0;
  sprintf(szSavedGameName, "%s", Name);
  SetVol(nil, sSavedGameVolume);

  CtoPstr(szSavedGameName);

  FSOpen((Pstr)szSavedGameName, sSavedGameVolume, &sFile);

  PtoCstr((Pstr)szSavedGameName);

  if (sFile) {
    for (x = 0; x < 100; x++) {
      for (y = 0; y < 100; y++) {
        Map[x][y] = 0;
      }
    }
    for (x = 0; x < 100; x++) {
      for (y = 0; y < 100; y++) {
        lSize = sizeof(Map[x][y]);
        FSRead(sFile, &lLongSize, &Map[x][y]);
        FSRead(sFile, &lLongSize, &Walls[x][y]);
      }
    }
    for (x = 0; x < 16; x++) {
      FSRead(sFile, &lLongSize, &startplacex[x]);
      FSRead(sFile, &lLongSize, &startplacey[x]);
    }
    FSClose(sFile);
  }
}

void LoadGame(Str255 Name, int animnum);
void LoadGame(Str255 Name, int animnum) {
  Boolean bLoaded = false;
  long lSize;
  long lLongSize = sizeof(long);
  int localframenum;
  int x, y, kl;
  sFile = OpenSavedGame(Name);
  FSRead(sFile, &lLongSize, &localframenum);

  if (sFile) {
    for (x = 0; x < 3; x++) {
      for (y = 0; y < 20; y++) {
        leftlowarm[x][y][animnum] = 0;
        lefthigharm[x][y][animnum] = 0;
        rightlowarm[x][y][animnum] = 0;
        righthigharm[x][y][animnum] = 0;
        torsorotation[x][y][animnum] = 0;
        hippos[x][y][animnum] = 0;
        hiprot[x][y][animnum] = 0;
        torsorot[x][y][animnum] = 0;
        leftlowleg[x][y][animnum] = 0;
        lefthighleg[x][y][animnum] = 0;
        rightlowleg[x][y][animnum] = 0;
        righthighleg[x][y][animnum] = 0;
        hippos[2][y][animnum] = 60;
        lefthand[x][y][animnum] = 0;
        leftfoot[x][y][animnum] = 0;
        righthand[x][y][animnum] = 0;
        rightfoot[x][y][animnum] = 0;
        head[x][y][animnum] = 0;
      }
    }
  }
  for (x = 0; x < 3; x++) {
    for (y = 0; y < localframenum; y++) {
      lSize = sizeof(leftlowarm[x][y][animnum]);
      FSRead(sFile, &lLongSize, &leftlowarm[x][y][animnum]);
      lSize = sizeof(lefthigharm[x][y][animnum]);
      FSRead(sFile, &lLongSize, &lefthigharm[x][y][animnum]);
      lSize = sizeof(rightlowarm[x][y][animnum]);
      FSRead(sFile, &lLongSize, &rightlowarm[x][y][animnum]);
      lSize = sizeof(righthigharm[x][y][animnum]);
      FSRead(sFile, &lLongSize, &righthigharm[x][y][animnum]);
      lSize = sizeof(lefthand[x][y][animnum]);
      FSRead(sFile, &lLongSize, &lefthand[x][y][animnum]);
      lSize = sizeof(leftfoot[x][y][animnum]);
      FSRead(sFile, &lLongSize, &leftfoot[x][y][animnum]);
      lSize = sizeof(righthand[x][y][animnum]);
      FSRead(sFile, &lLongSize, &righthand[x][y][animnum]);
      lSize = sizeof(rightfoot[x][y][animnum]);
      FSRead(sFile, &lLongSize, &rightfoot[x][y][animnum]);
      lSize = sizeof(head[x][y][animnum]);
      FSRead(sFile, &lLongSize, &head[x][y][animnum]);
      lSize = sizeof(torsorotation[x][y][animnum]);
      FSRead(sFile, &lLongSize, &torsorotation[x][y][animnum]);
      lSize = sizeof(hippos[x][y][animnum]);
      FSRead(sFile, &lLongSize, &hippos[x][y][animnum]);
      lSize = sizeof(hiprot[x][y][animnum]);
      FSRead(sFile, &lLongSize, &hiprot[x][y][animnum]);
      lSize = sizeof(torsorot[x][y][animnum]);
      FSRead(sFile, &lLongSize, &torsorot[x][y][animnum]);
      lSize = sizeof(leftlowleg[x][y][animnum]);
      FSRead(sFile, &lLongSize, &leftlowleg[x][y][animnum]);
      lSize = sizeof(lefthighleg[x][y][animnum]);
      FSRead(sFile, &lLongSize, &lefthighleg[x][y][animnum]);
      lSize = sizeof(rightlowleg[x][y][animnum]);
      FSRead(sFile, &lLongSize, &rightlowleg[x][y][animnum]);
      lSize = sizeof(righthighleg[x][y][animnum]);
      FSRead(sFile, &lLongSize, &righthighleg[x][y][animnum]);
      lSize = sizeof(speed[y][animnum]);
      FSRead(sFile, &lLongSize, &speed[y][animnum]);
    }
  }
  FSClose(sFile);
  if (localframenum == 20) {
    righthighleg[0][0][0] = 100;
  }
}

void LoadMap() {
  Boolean bLoaded = false;
  long lSize;
  long lLongSize = sizeof(long);

  int x, y, kl;
  sFile = OpenMap();

  if (sFile) {
    for (x = 0; x < 100; x++) {
      for (y = 0; y < 100; y++) {
        Map[x][y] = 0;
      }
    }
    for (x = 0; x < 100; x++) {
      for (y = 0; y < 100; y++) {
        lSize = sizeof(Map[x][y]);
        FSRead(sFile, &lLongSize, &Map[x][y]);
        FSRead(sFile, &lLongSize, &Walls[x][y]);
      }
    }
    for (x = 0; x < 16; x++) {
      FSRead(sFile, &lLongSize, &startplacex[x]);
      FSRead(sFile, &lLongSize, &startplacey[x]);
    }
    FSClose(sFile);
  }
}

void Save();
void Save() {
  int x, y;
  SFReply sfReply;
  short sFile = 0;
  long lSize;
  long lLongSize = sizeof(long);

  CtoPstr(szSavedGameName);

  sFile = PromptForSaveAS(SAVE_GAME_STRING, 0, (Pstr)szSavedGameName, 'DAVD', 'DMAP', &sfReply);

  PtoCstr((Pstr)szSavedGameName);

  if (sFile) {
    sSavedGameVolume = sfReply.vRefNum;
    PtoCstr(sfReply.fName);
    strcpy(szSavedGameName, (Cstr)sfReply.fName);
  }

  else {
    sfReply.vRefNum = sSavedGameVolume;
    strcpy((Cstr)sfReply.fName, szSavedGameName);
    CtoPstr((Cstr)sfReply.fName);

    sFile = OpenNewFile(&sfReply, 'DAVD', 'DMAP');
  }

  if (sFile)
    for (x = 0; x < 100; x++) {
      for (y = 0; y < 100; y++) {
        lSize = sizeof(Map[x][y]);
        FSWrite(sFile, &lLongSize, &Map[x][y]);
        FSWrite(sFile, &lLongSize, &Walls[x][y]);
      }
    }
  for (x = 0; x < 16; x++) {
    FSWrite(sFile, &lLongSize, &startplacex[x]);
    FSWrite(sFile, &lLongSize, &startplacey[x]);
  }
  {

    FSClose(sFile);

    /*if ( !bGameSaved )
    {
      CtoPstr( szSavedGameName );
      FSDelete( (Pstr) szSavedGameName, sSavedGameVolume );
      PtoCstr((Pstr) szSavedGameName );
    }*/
  }
}

/********************> ReSizeGLScene() <*****/
GLvoid ReSizeGLScene(GLsizei width, GLsizei height, float fov) // Resize And Initialize The GL Window
{
  if (height == 0) // Prevent A Divide By Zero By
  {
    height = 1; // Making Height Equal One
  }

  glViewport(0, 0, width, height); // Reset The Current Viewport

  glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
  glLoadIdentity();            // Reset The Projection Matrix

  // Calculate The Aspect Ratio Of The Window
  gluPerspective(fov, (GLfloat)width / (GLfloat)height, 0.1f, 1000000.0f);

  glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
  glLoadIdentity();           // Reset The Modelview Matrix
}

/********************> InitGL() <*****/
void MovePlayerData(int first, int second) {
  int x;
  for (x = 0; x < maxsprites; x++) {
    if (sprite[x].owner == first) {
      sprite[x].owner = second;
    }
  }
  swordtrailtoggle[first][0] = swordtrailtoggle[second][0];
  swordtrailtoggle[first][1] = swordtrailtoggle[second][1];
  SwordTrail[first][0] = SwordTrail[second][0];
  SwordTrail[first][1] = SwordTrail[second][1];
  computercontrolled[first] = computercontrolled[second];
  lightningdelay[first] = lightningdelay[second];
  attacker[first] = attacker[second];
  jetpack[first] = jetpack[second];
  oldnum[first] = oldnum[second];
  kBlockKey[first] = kBlockKey[second];
  kAttackKey[first] = kAttackKey[second];
  kRightShootKey[first] = kRightShootKey[second];
  kLeftShootKey[first] = kLeftShootKey[second];
  kLeftKey[first] = kLeftKey[second];
  kRightKey[first] = kRightKey[second];
  kUpKey[first] = kUpKey[second];
  kDownKey[first] = kDownKey[second];
  ammo[first] = ammo[second];
  itemnum[first] = itemnum[second];
  itemtype[first] = itemtype[second];
  attach[first] = attach[second];
  sabrespin[first] = sabrespin[second];
  jetsmokedelay[first] = jetsmokedelay[second];
  health[first] = health[second];
  oldhealth[first] = oldhealth[second];
  delaytime[first] = delaytime[second];
  // deathcount[first]=deathcount[second];
  speedmult[first] = speedmult[second];
  jetglownum[first] = jetglownum[second];
  usingjetpack[first] = usingjetpack[second];
  fake[first] = fake[second];
  size[first] = size[second];
  ammo[first] = ammo[second];
  jetpack[first] = jetpack[second];
  facing[first] = facing[second];
  frame[first] = frame[second];
  targetframe[first] = targetframe[second];
  activity[first] = activity[second];
  fallin[first] = fallin[second];
  oldtime[first] = oldtime[second];
  invisible[first] = invisible[second];
  cloaktime[first] = cloaktime[second];
  HelmetNum[first] = HelmetNum[second];
  LowerLegNum[first] = LowerLegNum[second];
  UpperArmNum[first] = UpperArmNum[second];
  ShoesNum[first] = ShoesNum[second];
  TorsoNum[first] = TorsoNum[second];
  uppressed[first] = uppressed[second];
  rightshootpressed[first] = rightshootpressed[second];
  leftshootpressed[first] = leftshootpressed[second];
  dead[first] = dead[second];
  rotation[first] = rotation[second];
  targetrotation[first] = targetrotation[second];
  time[first] = time[second];
  framenum[first] = framenum[second];
  anim[first] = anim[second];
  targetanim[first] = targetanim[second];
  timedirection[first] = timedirection[second];
  skin[first] = skin[second];
  itemnum[first] = itemnum[second];
  guyx[first] = guyx[second];
  guyy[first] = guyy[second];
  oldguyx[first] = oldguyx[second];
  oldguyy[first] = oldguyy[second];
  guymapx[first] = guymapx[second];
  guymapy[first] = guymapy[second];
  guyvely[first] = guyvely[second];
  guyvelx[first] = guyvelx[second];
}

void RemovePlayer(int x) {
  int a, b;
  if (exists[x]) {
    b = oldnum[x];
    goneplayers++;
    MovePlayerData(16, x);
    exists[numplayers - 1] = 0;
    if (jetglownum[x]) {
      sprite[jetglownum[x]].type = 0;
    }
    if (x < numplayers - 1) {
      for (a = x; a < numplayers - 1; a++) {
        if (jetglownum[a]) {
          sprite[jetglownum[a]].type = 0;
        }
        if (jetglownum[a + 1]) {
          sprite[jetglownum[a + 1]].type = 0;
        }
        MovePlayerData(a, a + 1);
        /*kBlockKey[a]=kBlockKey[a+1];
        kAttackKey[a]=kAttackKey[a+1];
        kRightShootKey[a]=kRightShootKey[a+1];
        kLeftShootKey[a]=kLeftShootKey[a+1];
        kLeftKey[a]=kLeftKey[a+1];
        kRightKey[a]=kRightKey[a+1];
        kUpKey[a]=kUpKey[a+1];
        kDownKey[a]=kDownKey[a+1];
        ammo[a]=ammo[a+1];
        itemnum[a]=itemnum[a+1];
        itemtype[a]=itemtype[a+1];
        attach[a]=attach[a+1];
        sabrespin[a]=sabrespin[a+1];
        jetsmokedelay[a]=jetsmokedelay[a+1];
        health[a]=health[a+1];
        oldhealth[a]=oldhealth[a+1];
        delaytime[a]=delaytime[a+1];
        deathcount[a]=deathcount[a+1];
        speedmult[a]=speedmult[a+1];
        jetglownum[a]=jetglownum[a+1];
        usingjetpack[a]=usingjetpack[a+1];
        fake[a]=fake[a+1];
        size[a]=size[a+1];
        ammo[a]=ammo[a+1];
        jetpack[a]=jetpack[a+1];
        facing[a]=facing[a+1];
        frame[a]=frame[a+1];
        targetframe[a]=targetframe[a+1];
        activity[a]=activity[a+1];
        fallin[a]=fallin[a+1];
        oldtime[a]=oldtime[a+1];
        invisible[a]=invisible[a+1];
        cloaktime[a]=cloaktime[a+1];
        HelmetNum[a]=HelmetNum[a+1];
        LowerLegNum[a]=LowerLegNum[a+1];
        UpperArmNum[a]=UpperArmNum[a+1];
        ShoesNum[a]=ShoesNum[a+1];
        TorsoNum[a]=TorsoNum[a+1];
        uppressed[a]=uppressed[a+1];
        rightshootpressed[a]=rightshootpressed[a+1];
        leftshootpressed[a]=leftshootpressed[a+1];
        dead[a]=dead[a+1];
        rotation[a]=rotation[a+1];
        targetrotation[a]=targetrotation[a+1];
        time[a]=time[a+1];
        framenum[a]=framenum[a+1];
        timedirection[a]=timedirection[a+1];
        skin[a]=skin[a+1];
        itemnum[a]=itemnum[a+1];
        guyx[a]=guyx[a+1];
        guyy[a]=guyy[a+1];
        oldguyx[a]=oldguyx[a+1];
        oldguyy[a]=oldguyy[a+1];
        guymapx[a]=guymapx[a+1];
        guymapy[a]=guymapy[a+1];
        guyvely[a]=guyvely[a+1];
        guyvelx[a]=guyvelx[a+1];*/
      }
    }
    MovePlayerData(16 - goneplayers, 16);
    oldguy[b] = 16 - goneplayers;
    if (numplayers >= 1) {
      numplayers--;
    }
  }
}

void MakeLineLightning(int howmany, float endoffset, float x1, float y1, float z1, float x2, float y2, float z2) {
  int counter;
  float arc;
  float distance;
  arc = 0;
  distance = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
  if (x2 < x1) {
    arc = x2;
    x2 = x1;
    x1 = arc;
    arc = y2;
    y2 = y1;
    y1 = arc;
    arc = z2;
    z2 = z1;
    z1 = arc;
  }
  unusedlightning++;
  if (unusedlightning >= kMaxLightning) {
    unusedlightning = 0;
  }
  Lightning[unusedlightning].x = x1;
  Lightning[unusedlightning].y = y1;
  Lightning[unusedlightning].z = z1;
  Lightning[unusedlightning].brightness = RangedRandom(.6, 1);
  Lightning[unusedlightning].tesselation = howmany;
  Lightning[unusedlightning].tesselation = (int)distance * 2;
  if (Lightning[unusedlightning].tesselation <= 5) {
    Lightning[unusedlightning].tesselation = 5;
  }
  if (Lightning[unusedlightning].tesselation >= 95) {
    Lightning[unusedlightning].tesselation = 95;
  }
  if (Lightning[unusedlightning].tesselation > 20 /*&&(int)RangedRandom(0,3)==2*/) {
    arc = RangedRandom(20, Lightning[unusedlightning].tesselation + 20);
  }
  Lightning[unusedlightning].LightningPoint[0][0] = 0;
  Lightning[unusedlightning].LightningPoint[0][1] = 0;
  Lightning[unusedlightning].LightningPoint[0][2] = 0;

  for (counter = 1; counter < Lightning[unusedlightning].tesselation; counter++) {
    Lightning[unusedlightning].LightningPoint[counter][0] = (float)counter / Lightning[unusedlightning].tesselation * distance;
    Lightning[unusedlightning].LightningPoint[counter][1] = (Lightning[unusedlightning].LightningPoint[counter - 1][1] + (RangedRandom(-100, 100) + 100) / 10000) * (Lightning[unusedlightning].tesselation / 2 - absolute(Lightning[unusedlightning].tesselation / 2 - counter)) / (Lightning[unusedlightning].tesselation / 2) + (RangedRandom(-100, 100) + 100) / 10000;
    if (absolute(counter - arc) < 10 && arc != 0) {
      Lightning[unusedlightning].LightningPoint[counter][1] += ((int)RangedRandom(0, 1) * 2 - 1) * absolute(counter - arc) / 600;
    }
    Lightning[unusedlightning].LightningPoint[counter][2] = (Lightning[unusedlightning].LightningPoint[counter - 1][2] + (RangedRandom(-100, 100) + 100) / 10000) * (Lightning[unusedlightning].tesselation / 2 - absolute(Lightning[unusedlightning].tesselation / 2 - counter)) / (Lightning[unusedlightning].tesselation / 2) + (RangedRandom(-100, 100) + 100) / 10000;
    if (absolute(counter - arc) < 10 && arc != 0) {
      Lightning[unusedlightning].LightningPoint[counter][2] += ((int)RangedRandom(0, 1) * 2 - 1) * absolute(counter - arc) / 600;
    }
    Lightning[unusedlightning].LightningPoint[counter][3] = Lightning[unusedlightning].LightningPoint[counter][1] + counter * counter * endoffset * .00001;
  }

  for (counter = 1; counter < Lightning[unusedlightning].tesselation; counter++) {
    Lightning[unusedlightning].LightningPoint[counter][2] *= 30;
    Lightning[unusedlightning].LightningPoint[counter][3] *= 30;
  }

  if (z2 != z1) {
    Lightning[unusedlightning].yrotation = atan((x2 - x1) / (z2 - z1)) / 6.28 * 360 + 180;
  }

  if (z2 < z1)
    Lightning[unusedlightning].yrotation += 180;
  else if (z2 == z1) {
    if (x2 < x1)
      Lightning[unusedlightning].yrotation = 90;
    else
      Lightning[unusedlightning].yrotation = 270;
  }
  Lightning[unusedlightning].yrotation += 90;

  if (y2 != y1) {
    Lightning[unusedlightning].zrotation = atan((x2 - x1) / (y2 - y1)) / 6.28 * 360 + 180;
  }

  if (y2 < y1)
    Lightning[unusedlightning].zrotation += 180;
  else if (y2 == y1) {
    if (x2 < x1)
      Lightning[unusedlightning].zrotation = 90;
    else
      Lightning[unusedlightning].zrotation = 270;
  }
  Lightning[unusedlightning].zrotation *= -1;
  Lightning[unusedlightning].zrotation -= 90;
}

void ChangeLightning(int howmany, float endoffset, int which) {
  int counter;
  float arc;
  arc = 0;
  // Lightning[unusedlightning].tesselation=howmany;
  if (Lightning[unusedlightning].tesselation > 20 /*&&(int)RangedRandom(0,3)==2*/) {
    arc = RangedRandom(20, Lightning[unusedlightning].tesselation + 20);
  }
  Lightning[unusedlightning].LightningPoint[0][0] = 0;
  Lightning[unusedlightning].LightningPoint[0][1] = 0;
  Lightning[unusedlightning].LightningPoint[0][2] = 0;
  for (counter = 1; counter < Lightning[unusedlightning].tesselation - 1; counter++) {
    Lightning[unusedlightning].LightningPoint[counter][1] = (Lightning[unusedlightning].LightningPoint[counter - 1][1] + (RangedRandom(-100, 100) + 100) / 10000) * (Lightning[unusedlightning].tesselation / 2 - absolute(Lightning[unusedlightning].tesselation / 2 - counter)) / (Lightning[unusedlightning].tesselation / 2) + (RangedRandom(-100, 100) + 100) / 10000;
    if (absolute(counter - arc) < 10 && arc != 0) {
      Lightning[unusedlightning].LightningPoint[counter][1] += ((int)RangedRandom(0, 1) * 2 - 1) * absolute(counter - arc) / 600;
    }
    Lightning[unusedlightning].LightningPoint[counter][2] = (Lightning[unusedlightning].LightningPoint[counter - 1][2] + (RangedRandom(-100, 100) + 100) / 10000) * (Lightning[unusedlightning].tesselation / 2 - absolute(Lightning[unusedlightning].tesselation / 2 - counter)) / (Lightning[unusedlightning].tesselation / 2) + (RangedRandom(-100, 100) + 100) / 10000;
    if (absolute(counter - arc) < 10 && arc != 0) {
      Lightning[unusedlightning].LightningPoint[counter][2] += ((int)RangedRandom(0, 1) * 2 - 1) * absolute(counter - arc) / 600;
    }
    Lightning[unusedlightning].LightningPoint[counter][3] = Lightning[unusedlightning].LightningPoint[counter][1] + counter * counter * endoffset * .00001;
  }
}

int InitGL(GLvoid) // All Setup For OpenGL Goes Here
{
  int num = 0;
  short fNum;
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_LINE_SMOOTH);
  cube = 1;
  gamespeed = 1;
  // glmSetMode(GLM_APPLICATION_HEAP_MODE);
  glEnable(GL_NORMALIZE);
  fogtoggle = 1;
  qd.randSeed = TickCount();
  // infoshowing
  showinfo = 3;
  blendtype = 0;
  blendtype2 = 0;
  computercontrolled[1] = 1;
  for (num = 0; num < 16; num++) {
    oldnum[num] = num;
    targetanim[num] = 0;
    anim[num] = 0;
    framenum[num] = 1;
    timedirection[num] = 1;
    activity[num] = 1;
    time[num] = 0;
    cloaktime[num] = 100;
    rotation[num] = 0;
    targetrotation[num] = 0;
    dead[num] = 0;
    health[num] = 100;
    size[num] = 1;
    delaytime[num] = 0;
    deathcount[num] = 0;
    speedmult[num] = 1;
    jetpack[num] = 0;
    jetglownum[num] = 0;
    exists[num] = 1;
  }
  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For T To Sphere Mapping (NEW)
  // speedmult[0]=10;  //Megaspeed!
  jetpack[0] = 1;
  jetpack[1] = 1;
  // speedmult[0]=200;
  // speedmult[1]=.5;
  for (num = 0; num < 6; num++) {
    lighton[num] = 0;
  }
  /*item[0].type=1;
  item[0].x=0;
  item[0].y=0;
  item[0].z=0;
  item[0].vely=.01;*/
  lighting = 1;
  changablejump = 0;
  // MakeSprite(0,0,0,200,bouncesprite, 1, 10, 0,0,.1,0);
  /*kLeftKey[1]=MAC_ARROW_LEFT_KEY;
  kRightKey[1]=MAC_ARROW_RIGHT_KEY;
  kUpKey[1]=MAC_ARROW_UP_KEY;
  kDownKey[1]=MAC_ARROW_DOWN_KEY;*/
  numplayers = 2;
  guyx[0] = 0;
  guyy[0] = 0;
  slide = 1000;
  guytrack = 1;

  selected = 0;
  cameray = 0;
  scalenormals = 0;
  // gravity=.1;
  gravity = .1;
  slowdown = 0;
  // jumpstrength=.8;
  jumpstrength = 1;

  camerax = -100;
  cameray = -200;
  themebasenum = 4;
  themebacknum = 4;
  themeropenum = 11;
  wireframe = 0;
  selectedx = 50;
  selectedy = 50;
  HelmetNum[0] = 6;
  TorsoNum[0] = 4;
  ShoesNum[0] = 9;
  HelmetNum[0] = 6;
  UpperArmNum[0] = 7;
  LowerLegNum[0] = 8;
  TorsoNum[1] = 13;
  ShoesNum[1] = 14;
  HelmetNum[1] = 15;
  UpperArmNum[1] = 16;
  LowerLegNum[1] = 17;
  skin[0] = 0;
  skin[1] = 1;
  sprite[0].x = 0;
  sprite[0].y = 0;
  sprite[0].z = 0;
  sprite[0].brightness = 200;
  sprite[0].size = 10;
  sprite[0].type = deletestars;
  unusedsprite = 1;
  glDisable(GL_CLIP_PLANE0);
  GetFNum("\pMonaco", &fNum); // build font
  gFontList = BuildFontGL(gOpenGLContext, fNum, normal, 9);
  glMatrixMode(GL_MODELVIEW);
  int x, y, kl;
  for (x = 0; x < 3; x++) {
    for (kl = 0; kl < 50; kl++) {
      for (y = 0; y < 20; y++) {
        leftlowarm[x][y][kl] = 0;
        lefthigharm[x][y][kl] = 0;
        rightlowarm[x][y][kl] = 0;
        righthigharm[x][y][kl] = 0;
        torsorotation[x][y][kl] = 0;
        hippos[x][y][kl] = 0;
        hiprot[x][y][kl] = 0;
        torsorot[x][y][kl] = 0;
        leftlowleg[x][y][kl] = 0;
        lefthighleg[x][y][kl] = 0;
        rightlowleg[x][y][kl] = 0;
        righthighleg[x][y][kl] = 0;
        hippos[2][y][kl] = 60;
        lefthand[x][y][kl] = 0;
        leftfoot[x][y][kl] = 0;
        righthand[x][y][kl] = 0;
        rightfoot[x][y][kl] = 0;
        head[x][y][kl] = 0;
        speed[y][kl] = 1000;
      }
    }
  }

  for (x = 0; x < 100; x++) {
    for (y = 0; y < 100; y++) {
      Map[x][y] = 0;
      Walls[x][y] = 0;
    }
  }
  for (x = 57; x < 63; x++) {
    Map[x][41] = 1;
  }
  for (x = 54; x < 58; x++) {
    Map[x][42] = 1;
  }
  for (x = 61; x < 67; x++) {
    Map[x][42] = 1;
  }
  for (x = 20; x < 80; x++) {
    Map[x][64] = 1;
  }

  Map[66][42] = 2;
  Map[66][41] = 3;
  Map[66][40] = 1;
  Map[57][44] = 1;
  Map[58][44] = 1;
  Map[59][44] = 1;
  Map[59][43] = 3;
  Map[59][42] = 3;
  Map[60][44] = 2;
  Map[60][43] = 1;
  // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  unusedchannel = 0;
  for (num = 0; num < 41; num++) {
    SndNewChannel(&psndChannel[num], sampledSynth, initMono, nil);
  }
  hSound[0] = GetResource('snd ', 128);
  hSound[1] = GetResource('snd ', 129);
  hSound[2] = GetResource('snd ', 130);
  hSound[3] = GetResource('snd ', 131);
  hSound[4] = GetResource('snd ', 132);
  hSound[5] = GetResource('snd ', 133);
  hSound[6] = GetResource('snd ', 134);
  hSound[7] = GetResource('snd ', 135);
  hSound[8] = GetResource('snd ', 136);
  hSound[9] = GetResource('snd ', 137);
  hSound[10] = GetResource('snd ', 138);
  hSound[11] = GetResource('snd ', 139);
  hSound[12] = GetResource('snd ', 140);
  hSound[13] = GetResource('snd ', 141);
  hSound[14] = GetResource('snd ', 142);
  hSound[15] = GetResource('snd ', 143);
  hSound[16] = GetResource('snd ', 144);
  hSound[17] = GetResource('snd ', 145);
  hSound[18] = GetResource('snd ', 146);
  hSound[19] = GetResource('snd ', 147);
  hSound[20] = GetResource('snd ', 148);
  hSound[21] = GetResource('snd ', 149);
  hSound[22] = GetResource('snd ', 150);
  hSound[23] = GetResource('snd ', 151);
  hSound[24] = GetResource('snd ', 152);
  hSound[25] = GetResource('snd ', 153);
  hSound[26] = GetResource('snd ', 154);
  hSound[27] = GetResource('snd ', 155);
  hSound[28] = GetResource('snd ', 156);
  hSound[29] = GetResource('snd ', 157);
  hSound[30] = GetResource('snd ', 158);
  MoveHHi(hSound[0]);
  HLock(hSound[0]);
  MoveHHi(hSound[1]);
  HLock(hSound[1]);
  MoveHHi(hSound[2]);
  HLock(hSound[2]);
  MoveHHi(hSound[3]);
  HLock(hSound[3]);
  MoveHHi(hSound[4]);
  HLock(hSound[4]);
  MoveHHi(hSound[5]);
  HLock(hSound[5]);
  MoveHHi(hSound[6]);
  HLock(hSound[6]);
  MoveHHi(hSound[7]);
  HLock(hSound[7]);
  MoveHHi(hSound[8]);
  HLock(hSound[8]);
  MoveHHi(hSound[9]);
  HLock(hSound[9]);
  MoveHHi(hSound[10]);
  HLock(hSound[10]);
  MoveHHi(hSound[11]);
  HLock(hSound[11]);
  MoveHHi(hSound[12]);
  HLock(hSound[12]);
  MoveHHi(hSound[13]);
  HLock(hSound[13]);
  MoveHHi(hSound[14]);
  HLock(hSound[14]);
  MoveHHi(hSound[15]);
  HLock(hSound[15]);
  MoveHHi(hSound[16]);
  HLock(hSound[16]);
  MoveHHi(hSound[17]);
  HLock(hSound[17]);
  MoveHHi(hSound[18]);
  HLock(hSound[18]);
  MoveHHi(hSound[19]);
  HLock(hSound[19]);
  MoveHHi(hSound[20]);
  HLock(hSound[20]);
  MoveHHi(hSound[21]);
  HLock(hSound[21]);
  // LoadGLTextures();							// Jump To Texture Loading Routine
  LoadGLTexture(":Data:PenguinBody.tga", 0);
  LoadGLTexture(":Data:PenguinFeet.tga", 1);
  // LoadGLTexture(":Data:Smoke.tga",2);
  LoadGLTexture(":Data:Smoke.tga", 2);
  LoadGLTexture(":Data:Marble.tga", 3);

  LoadGLTexture(":Data:Blue:Torso.tga", 4);
  LoadGLTexture(":Data:Bluepurple.tga", 5);
  LoadGLTexture(":Data:Blue:Helmet.tga", 6);
  LoadGLTexture(":Data:Blue:Upperarm.tga", 7);
  LoadGLTexture(":Data:Blue:Lowerleg.tga", 8);
  LoadGLTexture(":Data:Blue:Shoes.tga", 9);

  LoadGLTexture(":Data:Rope.tga", 10);
  LoadGLTexture(":Data:Grid.tga", 11);
  LoadGLTexture(":Data:Star.tga", 12);

  LoadGLTexture(":Data:Red:Torso.tga", 13);
  LoadGLTexture(":Data:Red:Shoes.tga", 14);
  LoadGLTexture(":Data:Red:Helmet.tga", 15);
  LoadGLTexture(":Data:Red:Upperarm.tga", 16);
  LoadGLTexture(":Data:Red:Lowerleg.tga", 17);

  LoadGLTexture(":Data:Green:Torso.tga", 18);
  LoadGLTexture(":Data:Green:Shoes.tga", 19);
  LoadGLTexture(":Data:Green:Helmet.tga", 20);
  LoadGLTexture(":Data:Green:Upperarm.tga", 21);
  LoadGLTexture(":Data:Green:Lowerleg.tga", 22);

  LoadGLTexture(":Data:Yellow:Torso.tga", 23);
  LoadGLTexture(":Data:Yellow:Shoes.tga", 24);
  LoadGLTexture(":Data:Yellow:Helmet.tga", 25);
  LoadGLTexture(":Data:Yellow:Upperarm.tga", 26);
  LoadGLTexture(":Data:Yellow:Lowerleg.tga", 27);

  LoadGLTexture(":Data:Metal.tga", 28);
  LoadGLTexture(":Data:Matrix.tga", 29);
  LoadGLTexture(":Data:MatrixDark.tga", 30);
  LoadGLTexture(":Data:MetalMesh.tga", 31);
  LoadGLTexture(":Data:LaserRifle.tga", 32);

  LoadGLTexture(":Data:Black:Torso.tga", 33);
  LoadGLTexture(":Data:Black:Shoes.tga", 34);
  LoadGLTexture(":Data:Black:Helmet.tga", 35);
  LoadGLTexture(":Data:Black:Upperarm.tga", 36);
  LoadGLTexture(":Data:Black:Lowerleg.tga", 37);

  LoadGLTexture(":Data:Laser.tga", 38);
  LoadGLTexture(":Data:LaserFront.tga", 39);

  LoadGLTexture(":Data:MachineGun.tga", 40);
  LoadGLTexture(":Data:Sword.tga", 41);
  LoadGLTexture(":Data:Rifle.tga", 42);

  LoadGLTexture(":Data:Island:Right.tga", 43);
  LoadGLTexture(":Data:Island:Back.tga", 44);
  LoadGLTexture(":Data:Island:Left.tga", 45);
  LoadGLTexture(":Data:Island:Front.tga", 46);
  LoadGLTexture(":Data:Island:Down.tga", 47);
  LoadGLTexture(":Data:Island:Up.tga", 48);

  LoadGLTexture(":Data:Jetpack.tga", 49);

  LoadGLTexture(":Data:LightSabre.tga", 50);

  LoadGLTexture(":Data:LightBlade.tga", 51);
  LoadGLTexture(":Data:LightBladeFront.tga", 52);

  LoadGLTexture(":Data:SmokePuff.tga", 53);

  LoadGLTexture(":Data:Lava:Right.tga", 54);
  LoadGLTexture(":Data:Lava:Back.tga", 55);
  LoadGLTexture(":Data:Lava:Left.tga", 56);
  LoadGLTexture(":Data:Lava:Front.tga", 57);
  LoadGLTexture(":Data:Lava:Down.tga", 58);
  LoadGLTexture(":Data:Lava:Up.tga", 59);

  LoadGLTexture(":Data:Snowy:Right.tga", 60);
  LoadGLTexture(":Data:Snowy:Back.tga", 61);
  LoadGLTexture(":Data:Snowy:Left.tga", 62);
  LoadGLTexture(":Data:Snowy:Front.tga", 63);
  LoadGLTexture(":Data:Snowy:Down.tga", 64);
  LoadGLTexture(":Data:Snowy:Up.tga", 65);

  LoadGLTexture(":Data:Grenskin.tga", 66);
  LoadGLTexture(":Data:Grenade.tga", 67);

  LoadGLTexture(":Data:LightningGun.tga", 68);

  LoadGLTexture(":Data:Lightning.tga", 69);

  LoadGLTexture(":Data:BladeTrail.tga", 70);

  LoadGLTexture(":Data:Font.tga", 71);

  BuildFont();

  environment[0].right = 44;
  environment[0].back = 45;
  environment[0].left = 46;
  environment[0].front = 47;
  environment[0].down = 48;
  environment[0].up = 49;

  environment[1].right = 55;
  environment[1].back = 56;
  environment[1].left = 57;
  environment[1].front = 58;
  environment[1].down = 59;
  environment[1].up = 60;

  environment[2].right = 61;
  environment[2].back = 62;
  environment[2].left = 63;
  environment[2].front = 64;
  environment[2].down = 65;
  environment[2].up = 66;

  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glEnable(GL_TEXTURE_2D);              // Enable Texture Mapping
  glShadeModel(GL_SMOOTH);              // Enable Smooth Shading
  glClearColor(0.0f, 0.1f, 0.1f, 0.0f); // Black Background
  glClearDepth(10.0f);                  // Depth Buffer Setup
  glEnable(GL_DEPTH_TEST);              // Enables Depth Testing
  glDepthFunc(GL_LEQUAL);               // The Type Of Depth Testing To Do
  // glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
  z = -100;
  lightz = 100;
  lightx = -100;
  LightPosition[0] = lightx;
  LightPosition[1] = lighty;
  LightPosition[2] = lightz;
  glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);    // Setup The Ambient Light
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);    // Setup The Diffuse Light
  glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);  // Position The Light
  glEnable(GL_LIGHT1);                               // Enable Light One
  glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse2);   // Setup The Diffuse Light
  glLightfv(GL_LIGHT2, GL_POSITION, LightPosition2); // Position The Light
  glDisable(GL_LIGHT2);                              // Enable Light One
  glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse2);   // Setup The Diffuse Light
  glLightfv(GL_LIGHT3, GL_POSITION, LightPosition2); // Position The Light
  glDisable(GL_LIGHT3);
  // glEnable(GL_AUTO_NORMAL);
  quadratic = gluNewQuadric();              // Create A Pointer To The Quadric Object (Return 0 If No Memory)
  gluQuadricNormals(quadratic, GLU_SMOOTH); // Create Smooth Normals
  gluQuadricTexture(quadratic, GL_TRUE);    // Create Texture Coords

  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For S To Sphere Mapping (NEW)
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For T To Sphere Mapping (NEW)
  glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); // Set The Texture Generation Mode For T To Sphere Mapping (NEW)
  glEnable(GL_LIGHTING);

  if (fogtoggle) {
    glEnable(GL_FOG);
  }                                // Enables GL_FOG
  glFogi(GL_FOG_MODE, GL_EXP);     // Fog Mode
  glFogfv(GL_FOG_COLOR, fogColor); // Set Fog Color
  glFogf(GL_FOG_DENSITY, 0.001f);  // How Dense Will The Fog Be
  // glHint(GL_FOG_HINT, GL_NICEST);			// Fog Hint Value
  glHint(GL_FOG_HINT, GL_FASTEST);
  glFogf(GL_FOG_START, 500.0f); // Fog Start Depth
  glFogf(GL_FOG_END, 1000.0f);

  LoadGame((unsigned char *)":Animations:Idle", 0);
  LoadGame((unsigned char *)":Animations:Idle2", 1);
  LoadGame((unsigned char *)":Animations:Run", 2);
  LoadGame((unsigned char *)":Animations:Duck", 3);
  LoadGame((unsigned char *)":Animations:Falling", 4);
  LoadGame((unsigned char *)":Animations:RopeClimb", 5);
  LoadGame((unsigned char *)":Animations:JumpStraight", 6);
  LoadGame((unsigned char *)":Animations:Flip", 7);
  LoadGame((unsigned char *)":Animations:Roll", 8);
  LoadGame((unsigned char *)":Animations:Splat", 9);
  LoadGame((unsigned char *)":Animations:Shoot Left w/ right hand", 10);
  LoadGame((unsigned char *)":Animations:Wallhit", 11);
  LoadGame((unsigned char *)":Animations:Gah", 12);
  LoadGame((unsigned char *)":Animations:FallBackwards", 13);
  LoadGame((unsigned char *)":Animations:LandBackwards", 14);
  LoadGame((unsigned char *)":Animations:Die", 15);
  LoadGame((unsigned char *)":Animations:NeckBreaker", 16);
  LoadGame((unsigned char *)":Animations:NeckBreakee", 17);
  LoadGame((unsigned char *)":Animations:Stabber", 18);
  LoadGame((unsigned char *)":Animations:Stabbee", 19);
  LoadGame((unsigned char *)":Animations:Thrower", 20);
  LoadGame((unsigned char *)":Animations:Throwee", 21);
  LoadGame((unsigned char *)":Animations:Pain1", 22);
  LoadGame((unsigned char *)":Animations:Pain2", 23);
  LoadGame((unsigned char *)":Animations:GetUpFromBack", 24);
  LoadGame((unsigned char *)":Animations:GetUpFromFront", 25);
  LoadGame((unsigned char *)":Animations:SwordIdle", 26);
  LoadGame((unsigned char *)":Animations:SwordRightThrust", 27);
  LoadGame((unsigned char *)":Animations:SwordRightThrustBlocked", 28);
  LoadGame((unsigned char *)":Animations:SwordRightParry", 29);
  LoadGame((unsigned char *)":Animations:Shoot In Air", 30);
  LoadGame((unsigned char *)":Animations:Shoot Left w/ right hand M16", 31);
  LoadGame((unsigned char *)":Animations:Gah M16", 32);
  LoadGame((unsigned char *)":Animations:JetUp", 33);
  LoadGame((unsigned char *)":Animations:JetFront", 34);
  LoadGame((unsigned char *)":Animations:JetIdle", 35);
  LoadGame((unsigned char *)":Animations:JetStabber", 36);
  LoadGame((unsigned char *)":Animations:JetStabbee", 37);
  LoadGame((unsigned char *)":Animations:DuckStabber", 38);
  LoadGame((unsigned char *)":Animations:DuckStabbee", 39);
  LoadGame((unsigned char *)":Animations:SpinAttack", 40);
  LoadGame((unsigned char *)":Animations:FallForwards", 41);
  LoadGame((unsigned char *)":Animations:Pain3", 42);
  LoadGame((unsigned char *)":Animations:Grenidle", 43);
  LoadGame((unsigned char *)":Animations:Grenlaunch", 44);

  LoadNamedMap((unsigned char *)":Maps:NormalMap");
  // set keys
  kBlockKey[0] = 17;
  kAttackKey[0] = 15;
  kRightShootKey[0] = 14;
  kLeftShootKey[0] = 12;
  kLeftKey[0] = 0;
  kRightKey[0] = 2;
  kUpKey[0] = 13;
  kDownKey[0] = 1;
  ammo[0] = 30;
  itemnum[0] = 1;
  kRightShootKey[2] = 60;
  kLeftShootKey[2] = 60;
  kLeftKey[2] = 60;
  kRightKey[2] = 60;
  kUpKey[2] = 60;
  kDownKey[2] = 60;
  ammo[2] = 30;
  itemnum[0] = 1;
  kBlockKey[1] = 76;
  kAttackKey[1] = 82;
  kRightShootKey[1] = 92;
  kLeftShootKey[1] = 89;
  kLeftKey[1] = 86;
  kRightKey[1] = 88;
  kUpKey[1] = 91;
  kDownKey[1] = 87;
  ammo[1] = 30;
  itemnum[1] = 1;
  restartRound();
  WallBounds(cube);
  // glEnable(GL_CULL_FACE);
  // LoadGame((unsigned char *)":Animations:Shoot Right w/ right hand", 12);
  return TRUE; // Initialization Went OK
}

void DrawSabreGlow(int whichguy);
void DrawSabreGlow(int whichguy) {
  float spin = -90, size = 16, brightness = 255;
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glDisable(GL_CULL_FACE);
  glPushMatrix();
  glTranslatef(0.0, 5.0, 0.0);
  glColor4f(255, 255, 255, brightness / 255);
  if (whichguy == 0) {
    glColor4f(1, .5, .5, brightness / 255);
  }
  if (whichguy == 1) {
    glColor4f(.5, 1, .5, brightness / 255);
  }
  if (whichguy == 2) {
    glColor4f(.5, .5, 1, brightness / 255);
  }
  glDisable(GL_LIGHTING);
  glEnable(GL_BLEND);
  if (fogtoggle) {
    glDisable(GL_FOG);
  }
  glDepthMask(0);
  glRotatef(spin, 0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glRotatef(sabrespin[whichguy], 1.0f, 0.0f, 0.0f);
  glBindTexture(GL_TEXTURE_2D, texture[51]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-.3f * size, -.05f * size, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(.3f * size, -.05f * size, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(.3f * size, .05f * size, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-.3f * size, .05f * size, 0.0f);
  glEnd();
  glPushMatrix();
  glRotatef(90, 1.0, 0.0, 0.0);
  glBindTexture(GL_TEXTURE_2D, texture[51]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-.3f * size, -.05f * size, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(.3f * size, -.05f * size, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(.3f * size, .05f * size, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-.3f * size, .05f * size, 0.0f);
  glEnd();
  glPopMatrix();
  glRotatef(sabrespin[whichguy], 2.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-.3f * size, -.05f * size, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(.3f * size, -.05f * size, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(.3f * size, .05f * size, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-.3f * size, .05f * size, 0.0f);
  glEnd();
  glPushMatrix();
  glRotatef(90, 1.0, 0.0, 0.0);
  glBindTexture(GL_TEXTURE_2D, texture[51]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-.3f * size, -.05f * size, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(.3f * size, -.05f * size, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(.3f * size, .05f * size, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-.3f * size, .05f * size, 0.0f);
  glEnd();
  glPopMatrix();
  glPopMatrix();
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture[52]);
  glTranslatef(3.0f, 0.0f, 0.0f);
  glPushMatrix();
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  glLoadIdentity();
  glTranslatef(M[12], M[13], M[14]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-.020f * size, -.020f * size, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(.020f * size, -.020f * size, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(.020f * size, .020f * size, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-.020f * size, .020f * size, 0.0f);
  glEnd();
  glPopMatrix();
  glTranslatef(-6.0f, 0.0f, 0.0f);
  glPushMatrix();
  /*glRotatef(yrot,0.0f,1.0f,0.0f);
  glRotatef(-xrot,1.0f,0.0f,0.0f);*/
  // glRotatef(90,0.0,1.0,0.0);
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  glLoadIdentity();
  glTranslatef(M[12], M[13], M[14]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-.013f * size, -.013f * size, 0.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(.013f * size, -.013f * size, 0.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(.013f * size, .013f * size, 0.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-.013f * size, .013f * size, 0.0f);
  glEnd();
  glPopMatrix();
  glPopMatrix();
  if (invisible[whichguy] == 0) {
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
  }
  glDepthMask(1);
  glColor4f(0, 0, 0, 0);
  glPopMatrix();
  glEnable(GL_CULL_FACE);
}

void DrawBody(int whichguy);
void DrawBody(int whichguy) {
  float hipfloat[3][2];
  glTranslatef(0, .1, 0);
  glScalef(size[whichguy], size[whichguy], size[whichguy]);
  hipfloat[1][0] = (float)(hippos[1][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[2][0] = (float)(hippos[2][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[0][0] = (float)(hippos[0][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[1][1] = (float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[2][1] = (float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[0][1] = (float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  glPushMatrix();
  glRotatef(((hiprot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((hiprot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((hiprot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(((hipfloat[1][0] * (100 - time[whichguy])) + (hipfloat[1][1] * (time[whichguy]))) / 100, ((hipfloat[2][0] * (100 - time[whichguy])) + (hipfloat[2][1] * (time[whichguy]))) / 100, ((hipfloat[0][0] * (100 - time[whichguy])) + (hipfloat[0][1] * (time[whichguy]))) / 100);
  glBindTexture(GL_TEXTURE_2D, texture[TorsoNum[whichguy]]);
  Hip();
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glRotatef(((torsorot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((torsorot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((torsorot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[TorsoNum[whichguy]]);
  Torso();
  if (jetpack[whichguy] == 1) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[49]);
    glTranslatef(0, 0, -1.5);
    glRotatef(-90, 0, 1, 0);
    glScalef(3, 3, 3);
    JetPack();
    glPopMatrix();
  }
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture[HelmetNum[whichguy]]);
  glTranslatef(0.0f, 3.5f, 0.0f);
  glRotatef(((head[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((head[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((head[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichguy != firstperson - 1 || firstperson == 0) {
    if (skin[whichguy] == 4) {
      glScalef(.8, .8, .8);
      Head2();
    }
    if (skin[whichguy] != 4) {
      Head();
    }
  }
  glPopMatrix();
  glDisable(GL_CULL_FACE);
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture[UpperArmNum[whichguy]]);
  glTranslatef(1.5f, 3.0f, 0.0f);
  glScalef(.8, .8, .8);
  glRotatef(((lefthigharm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((lefthigharm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((lefthigharm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  Upperarm();
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((leftlowarm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((leftlowarm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((leftlowarm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[UpperArmNum[whichguy]]);
  Lowerarm();
  glTranslatef(0.0f, -1.8f, 0.0f);
  glRotatef(((lefthand[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthand[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((lefthand[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthand[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((lefthand[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthand[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[UpperArmNum[whichguy]]);
  Hand();
  glBindTexture(GL_TEXTURE_2D, texture[32]);
  if (itemnum[whichguy] == 3) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(-0.3f, -1.0f, 0.8f);
    glRotatef(90, 0.0, 1.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, texture[50]);
    if (itemtype[whichguy] == 1) {
      glScalef(100, 100, 100);
      LightSabre();
    }
    glBindTexture(GL_TEXTURE_2D, texture[41]);
    if (itemtype[whichguy] == 0) {
      Sword();
    }
  }
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  lefthandpoint.x = M[12];
  lefthandpoint.y = M[13];
  lefthandpoint.z = M[14];
  glPopMatrix();
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture[UpperArmNum[whichguy]]);
  glTranslatef(-1.5f, 3.0f, 0.0f);
  glScalef(-.8, .8, .8);
  glRotatef(((righthigharm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((righthigharm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((righthigharm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  Upperarm();
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((rightlowarm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((rightlowarm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((rightlowarm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[UpperArmNum[whichguy]]);
  Lowerarm();
  glTranslatef(0.0f, -1.8f, 0.0f);
  glRotatef(((righthand[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((righthand[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((righthand[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[UpperArmNum[whichguy]]);
  Hand();
  glBindTexture(GL_TEXTURE_2D, texture[32]);
  if (itemnum[whichguy] == 1) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(-0.3f, 0.7f, 3.8f);
    glScalef(.8, .8, .8);
    LaserRifle();
  }
  if (itemnum[whichguy] == 5) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(0.0f, -0.2f, 0.1f);
    glBindTexture(GL_TEXTURE_2D, texture[42]);
    Rifle();
  }
  if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(-0.3f, -1.0f, 0.8f);
    glRotatef(90, 0.0, 1.0, 0.0);
    // DrawSabreGlow(whichguy);
    glBindTexture(GL_TEXTURE_2D, texture[50]);
    if (itemtype[whichguy] == 1) {
      glScalef(100, 100, 100);
      LightSabre();
    }
    glBindTexture(GL_TEXTURE_2D, texture[41]);
    if (itemtype[whichguy] == 0) {
      Sword();
    }
  }
  if (itemnum[whichguy] == 4) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(180, 0.0, 1.0, 0.0);
    glTranslatef(0.3f, 0.3f, -1.2f);
    glScalef(2, 2, 2);
    glBindTexture(GL_TEXTURE_2D, texture[40]);
    Machinegun();
  }
  if (itemnum[whichguy] == 6) {
    glTranslatef(-0.2f, -2.2f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, texture[66]);
    glRotatef(180, 0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glScalef(2, 2, 2);
    Grenlauncher();
  }
  if (itemnum[whichguy] == 7) {
    glTranslatef(-0.2f, -2.2f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, texture[68]);
    glRotatef(180, 0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glScalef(2, 2, 2);
    LightningGun();
  }
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  righthandpoint.x = M[12];
  righthandpoint.y = M[13];
  righthandpoint.z = M[14];
  glPopMatrix();
  glRotatef(-torsorot[0][frame[whichguy]][anim[whichguy]], 1.0f, 0.0f, 0.0f);
  glRotatef(-torsorot[1][frame[whichguy]][anim[whichguy]], 0.0f, 1.0f, 0.0f);
  glRotatef(-torsorot[2][frame[whichguy]][anim[whichguy]], 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -0.5f, 0.0f);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.8f, 0.0f, 0.0f);
  glRotatef(((lefthighleg[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthighleg[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((lefthighleg[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthighleg[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((lefthighleg[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthighleg[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[UpperArmNum[whichguy]]);
  Upperarm();
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((leftlowleg[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowleg[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((leftlowleg[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowleg[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((leftlowleg[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowleg[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[LowerLegNum[whichguy]]);
  Lowerleg();
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((leftfoot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftfoot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((leftfoot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftfoot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((leftfoot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftfoot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[ShoesNum[whichguy]]);
  glScalef(.8, .8, .8);
  Foot();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-0.8f, 0.0f, 0.0f);
  glRotatef(((righthighleg[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthighleg[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((righthighleg[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthighleg[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((righthighleg[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthighleg[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[UpperArmNum[whichguy]]);
  Upperarm();
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((rightlowleg[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowleg[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((rightlowleg[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowleg[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((rightlowleg[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowleg[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[LowerLegNum[whichguy]]);
  Lowerleg();
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((rightfoot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightfoot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((rightfoot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightfoot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((rightfoot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightfoot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture[ShoesNum[whichguy]]);
  glScalef(.8, .8, .8);
  Foot();
  glPopMatrix();
  glPopMatrix();
  glEnable(GL_CULL_FACE);
}

void DrawSabreBody(int whichguy);
void DrawSabreBody(int whichguy) {
  float hipfloat[3][2];
  glPushMatrix();
  glTranslatef(0, .1, 0);
  glScalef(size[whichguy], size[whichguy], size[whichguy]);
  hipfloat[1][0] = (float)(hippos[1][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[2][0] = (float)(hippos[2][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[0][0] = (float)(hippos[0][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[1][1] = (float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[2][1] = (float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[0][1] = (float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  glPushMatrix();
  glRotatef(((hiprot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((hiprot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((hiprot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(((hipfloat[1][0] * (100 - time[whichguy])) + (hipfloat[1][1] * (time[whichguy]))) / 100, ((hipfloat[2][0] * (100 - time[whichguy])) + (hipfloat[2][1] * (time[whichguy]))) / 100, ((hipfloat[0][0] * (100 - time[whichguy])) + (hipfloat[0][1] * (time[whichguy]))) / 100);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glRotatef(((torsorot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((torsorot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((torsorot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glTranslatef(1.5f, 3.0f, 0.0f);
  glScalef(.8, .8, .8);
  glRotatef(((lefthigharm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((lefthigharm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((lefthigharm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  ;
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((leftlowarm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((leftlowarm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((leftlowarm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -1.8f, 0.0f);
  glRotatef(((lefthand[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthand[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((lefthand[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthand[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((lefthand[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthand[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (itemnum[whichguy] == 3) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(-0.3f, -1.0f, 0.8f);
    glRotatef(90, 0.0, 1.0, 0.0);
    DrawSabreGlow(whichguy);
    glBindTexture(GL_TEXTURE_2D, texture[41]);
                        /*Sword();*/}
                        glPopMatrix();
                        glPushMatrix();
                        glTranslatef(-1.5f, 3.0f, 0.0f);
                        glScalef(-.8, .8, .8);
                        glRotatef(((righthigharm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
                        glRotatef(((righthigharm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
                        glRotatef(((righthigharm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
                        glTranslatef(0.0f, -2.5f, 0.0f);
                        glRotatef(((rightlowarm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
                        glRotatef(((rightlowarm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
                        glRotatef(((rightlowarm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
                        glTranslatef(0.0f, -1.8f, 0.0f);
                        glRotatef(((righthand[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
                        glRotatef(((righthand[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
                        glRotatef(((righthand[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
                        if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
                          glRotatef(90, 1.0, 0.0, 0.0);
                          glTranslatef(-0.3f, -1.0f, 0.8f);
                          glRotatef(90, 0.0, 1.0, 0.0);
                          DrawSabreGlow(whichguy);
                          glBindTexture(GL_TEXTURE_2D, texture[41]);
                        /*Sword();*/}
                        glPopMatrix();
                        glRotatef(-torsorot[0][frame[whichguy]][anim[whichguy]], 1.0f, 0.0f, 0.0f);
                        glRotatef(-torsorot[1][frame[whichguy]][anim[whichguy]], 0.0f, 1.0f, 0.0f);
                        glRotatef(-torsorot[2][frame[whichguy]][anim[whichguy]], 0.0f, 0.0f, 1.0f);
                        glTranslatef(0.0f, -0.5f, 0.0f);
                        glPopMatrix();
                        glPopMatrix();
                        glPopMatrix();
}

void DrawGuys(int whichguy);
void DrawGuys(int whichguy, int sabre) {
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, texture[3]);
  glTranslatef(100.0f, 200.0f, 0.0f);
  glTranslatef(guyx[whichguy], guyy[whichguy], 0.0f);
  glPushMatrix();
  if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    targetrotation[whichguy] = 0;
  }
  if (activity[whichguy] == runleft || activity[whichguy] == leftflip || activity[whichguy] == leftroll || activity[whichguy] == fallbackwardsright || activity[whichguy] == fallforwardsleft || activity[whichguy] == hitwallright || activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == painthreeleft || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleleft || activity[whichguy] == swordleftthrust || activity[whichguy] == jetleft) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == painthreeleft || activity[whichguy] == swordleftthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleleft || activity[whichguy] == jetimpaledleft || activity[whichguy] == swordleftspin || activity[whichguy] == grenshootleft) {
    rotation[whichguy] = -90;
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == runright || activity[whichguy] == rightflip || activity[whichguy] == rightroll || activity[whichguy] == fallbackwardsleft || activity[whichguy] == fallforwardsright || activity[whichguy] == hitwallleft || activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordidleright || activity[whichguy] == grenidleright || activity[whichguy] == swordrightthrust || activity[whichguy] == jetright) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == painthreeright || activity[whichguy] == swordrightthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaledright || activity[whichguy] == swordrightspin || activity[whichguy] == grenshootright) {
    rotation[whichguy] = 90;
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] > 0) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] < 0) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    glTranslatef(0.0f, 0.0f, -1.0f);
    targetrotation[whichguy] = 0;
    rotation[whichguy] = 0;
  }
  glRotatef(((rotation[whichguy] * (100 - time[whichguy])) + (targetrotation[whichguy] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  DrawGuy(whichguy, sabre);
  glPopMatrix();
  /*
  glTranslatef(0.0f,0.2f,0.0f);
  glScalef(1.0f,0.01f,1.0f);
  glRotatef(-45,0.0f,0.0f,-1.0f);
  if (activity==runleft){glRotatef(-90,0.0f,1.0f,0.0f);}
  if (activity==runright){glRotatef(90,0.0f,1.0f,0.0f);}
  if (activity==falling&&guyvelx>0){glRotatef(90,0.0f,1.0f,0.0f);}
  if (activity==falling&&guyvelx<0){glRotatef(-90,0.0f,1.0f,0.0f);}
  if (activity==climbrope||activity==onrope||activity==downrope){glTranslatef(0.0f,0.0f,-1.0f);}
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  DrawShadow();*/
  glPopMatrix();
}

void DrawGuy(int whichguy, int sabre) {
  if ((cloaktime[whichguy] < 100) || (invisible[whichguy] == 1 && cloaktime[whichguy] < 200)) {
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_LIGHTING);
    glColor4f(0.0, 0.0, 0.0, 0.0);
    if (fogtoggle) {
      glDisable(GL_FOG);
    }

    DrawBody(whichguy);

    glEnable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_BLEND);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
  }

  if (invisible[whichguy] & cloaktime[whichguy] >= 200) {
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    glDisable(GL_LIGHTING);
    glColor4f(0.0, 0.0, 0.0, 0.0);
    if (fogtoggle) {
      glDisable(GL_FOG);
    }

    if (sabre == 0) {
      DrawBody(whichguy);
    }
    if (sabre == 1) {
      DrawSabreBody(whichguy);
    }
    glEnable(GL_LIGHTING);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_BLEND);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
  }

  if (invisible[whichguy] == 0 || cloaktime[whichguy] < 100) {

    glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE_MINUS_DST_COLOR);
    if (cloaktime[whichguy] < 100) {
      glEnable(GL_BLEND);
      if (fogtoggle) {
        glDisable(GL_FOG);
      }
      glDisable(GL_LIGHTING);
      if (invisible[whichguy] == 1) {
        glColor4f(1.0, 1.0, 1.0, cloaktime[whichguy] / 100);
      }
      if (invisible[whichguy] == 0) {
        glColor4f(1.0, 1.0, 1.0, 1 - cloaktime[whichguy] / 100);
      }
    }
    if (sabre == 0) {
      DrawBody(whichguy);
    }
    if (sabre == 1) {
      DrawSabreBody(whichguy);
    }
    glDisable(GL_BLEND);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
    glEnable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  }
  glEnable(GL_CULL_FACE);
}

void HandleSpriteTypes(int x) {
  int spritetype, a, b, c, d;
  spritetype = sprite[x].type;
  switch (spritetype) {
  case spawnstars:
    glRotatef(sprite[x].spin, 0.0f, 1.0f, 0.0f);
    glTranslatef(0, 0, sprite[x].spin2);
    glRotatef(-sprite[x].spin, 0.0f, 1.0f, 0.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(0, 255, 255, sprite[x].brightness / 255);
    break;
  case deletestars:
    glRotatef(sprite[x].spin, 0.0f, 1.0f, 0.0f);
    glTranslatef(0, 0, sprite[x].spin2);
    glRotatef(-sprite[x].spin, 0.0f, 1.0f, 0.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(255, 150, 0, sprite[x].brightness / 255);
    break;
  case muzzleflashstars:
    glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
    // glTranslatef(0,0,sprite[x].spin2);
    // glRotatef(-sprite[x].spin,0.0f,1.0f,0.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(255, 150, 0, sprite[x].brightness / 255);
    break;
  case lightningflashstars:
    glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
    // glTranslatef(0,0,sprite[x].spin2);
    // glRotatef(-sprite[x].spin,0.0f,1.0f,0.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(50, 50, 255, sprite[x].brightness / 255);
    break;
  case bouncesprite:
    glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(255, 150, 0, sprite[x].brightness / 255);
    break;
  case water:
    glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(0, 0, 255, sprite[x].brightness / 255);
    break;
  case grenade:
    glRotatef(sprite[x].spin + 90, 0.0f, 0.0f, 1.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    break;
  case chunk:
    glRotatef(sprite[x].spin + 90, 0.0f, 0.0f, 1.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    break;
  case wallsparks:
    glRotatef(sprite[x].spin, 0.0f, 1.0f, 0.0f);
    glTranslatef(0, 0, sprite[x].spin2);
    glRotatef(-sprite[x].spin, 0.0f, 1.0f, 0.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(255, 150, 0, sprite[x].brightness / 255);
    sprite[x].size = sprite[x].brightness / 30;
    break;
  case bloodsparks:
    // glRotatef(sprite[x].spin,0.0f,1.0f,0.0f);
    glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
    // glRotatef(-sprite[x].spin,0.0f,1.0f,0.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(255, 0, 0, sprite[x].brightness / 255);
    sprite[x].size = sprite[x].brightness / 30;
    break;
  case lasersparks:
    // glRotatef(sprite[x].spin,0.0f,1.0f,0.0f);
    glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
    // glRotatef(-sprite[x].spin,0.0f,1.0f,0.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(255, 255, 0, sprite[x].brightness / 255);
    sprite[x].size = sprite[x].brightness / 24;
    break;
  case invisiblestars:
    sprite[x].x = guyx[0];
    sprite[x].y = RangedRandom(guyy[0] + 5, guyy[0] + 20);
    glRotatef(sprite[x].spin, 0.0f, 1.0f, 0.0f);
    glTranslatef(0, 0, sprite[x].spin2);
    glRotatef(-sprite[x].spin, 0.0f, 1.0f, 0.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(0, 150, 0, sprite[x].brightness / 255);
    break;
  case invisiblestars2:
    sprite[x].x = guyx[1];
    sprite[x].y = RangedRandom(guyy[1] + 5, guyy[1] + 20);
    glRotatef(sprite[x].spin, 0.0f, 1.0f, 0.0f);
    glTranslatef(0, 0, sprite[x].spin2);
    glRotatef(-sprite[x].spin, 0.0f, 1.0f, 0.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(0, 150, 0, sprite[x].brightness / 255);
    break;
  case lasersprite:
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(255, 255, 255, sprite[x].brightness / 255);
    break;
  case JetPackGlow:
    glRotatef(sprite[x].spin, 0.0f, 1.0f, 0.0f);
    glColor4f(255, 150, 0, sprite[x].brightness / 255);
    break;
  case smokesprite:
    glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(255, 255, 255, sprite[x].brightness / 255);
    if (sprite[x].type2 == 1) {
      sprite[x].size += multiplier * gamespeed / 120 * 2;
    }
    break;
  case exploflame:
    glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
    // glRotatef(sprite[x].spin,0.0f,-1.0f,0.0f);
    glColor4f(255, 150, 0, sprite[x].brightness / 255);
    sprite[x].size += multiplier * gamespeed / 20;
    break;
  }
}

/*********************> BoundCamera() <*****/
void BoundCamera();
void BoundCamera() {
  if (cameray + (sin((-xrot) / 360 * 6.28) * -(z - 6)) < -560) {
    cameray = -560 - (sin((-xrot) / 360 * 6.28) * -(z - 6));
  }
}

/*********************> DrawGLScene() <*****/

void glDrawBigCube(float xWidth, float yWidth, float zWidth, int tesselation, float movement);
void glDrawBigCube(float xWidth, float yWidth, float zWidth, int tesselation, float movement) {
  int normallength = .3;
  if (theme == matrixtheme) {
    normallength = 1.0;
  }
  glBegin(GL_QUADS);
  // Front Face
  glNormal3f(0.0f, 0.0f, -normallength);
  glTexCoord2f(0.0f, movement);
  glVertex3f(-xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(-xWidth, yWidth, zWidth);
  // Back Face
  glNormal3f(0.0f, 0.0f, normallength);
  glTexCoord2f(tesselation, movement);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, movement);
  glVertex3f(xWidth, -yWidth, -zWidth);
  // Top Face
  glNormal3f(0.0f, -normallength, 0.0f);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, movement);
  glVertex3f(-xWidth, yWidth, zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(xWidth, yWidth, -zWidth);
  // Bottom Face
  glNormal3f(0.0f, normallength, 0.0f);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(xWidth, -yWidth, -zWidth);
  glTexCoord2f(0.0f, movement);
  glVertex3f(xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(-xWidth, -yWidth, zWidth);
  // Right face
  glNormal3f(-normallength, 0.0f, 0.0f);
  glTexCoord2f(tesselation, movement);
  glVertex3f(xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(xWidth, yWidth, -zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(0.0f, movement);
  glVertex3f(xWidth, -yWidth, zWidth);
  // Left Face
  glNormal3f(normallength, 0.0f, 0.0f);
  glTexCoord2f(0.0f, movement);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(-xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(-xWidth, yWidth, zWidth);
  glTexCoord2f(0.0f, tesselation + movement);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glEnd();
}

void glEnvironmentCube(int front, int left, int back, int right, int up, int down, int size);
void glEnvironmentCube(int front, int left, int back, int right, int up, int down, int size) {
  int normallength = 1;
  int a;
  float movement = 0.0009;
  float tesselation = .9981;
  float beginningmargin = .0009;
  float xWidth = 200 * size;
  float yWidth = 200 * size;
  float zWidth = 200 * size;
  float realyrot;

  movement = 0.000;
  tesselation = 1;
  beginningmargin = .0000;

  realyrot = yrot;

  /*tesselation=guyy[0];
  movement=guyx[0];
  beginningmargin=guyx[1];*/

  for (a = 0; a <= 20; a++) {
    if (xrot >= 360) {
      xrot -= 360;
    }
    if (xrot < 0) {
      xrot += 360;
    }
  }

  for (a = 0; a <= 20; a++) {
    if (yrot >= 360) {
      yrot -= 360;
    }
    if (yrot < 0) {
      yrot += 360;
    }
  }

  if (xrot >= 90 && xrot <= 270) {
    yrot += 180;
  }

  if (yrot >= 360) {
    yrot -= 360;
  }
  if (yrot < 0) {
    yrot += 360;
  }

  glDepthMask(0);
  glDisable(GL_BLEND);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  if ((yrot >= 90 && yrot <= 270) || (firstperson == 1)) {
    glBindTexture(GL_TEXTURE_2D, front);
  }
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  // glBindTexture(GL_TEXTURE_2D, 44);
  glBegin(GL_QUADS);
  // Front Face
  glNormal3f(0.0f, 0.0f, -normallength);
  glTexCoord2f(beginningmargin, movement);
  glVertex3f(-xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(beginningmargin, tesselation + movement);
  glVertex3f(-xWidth, yWidth, zWidth);
  glEnd();
  if (yrot >= 270 || yrot <= 90 || firstperson == 3 || firstperson == 0) {
    glBindTexture(GL_TEXTURE_2D, back);
  }
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glBegin(GL_QUADS);
  // Back Face
  glNormal3f(0.0f, 0.0f, normallength);
  glTexCoord2f(tesselation, movement);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glTexCoord2f(beginningmargin, tesselation + movement);
  glVertex3f(xWidth, yWidth, -zWidth);
  glTexCoord2f(beginningmargin, movement);
  glVertex3f(xWidth, -yWidth, -zWidth);
  glEnd();
  if ((xrot >= 180 && xrot <= 360) || (firstperson == 1 || firstperson == 2)) {
    glBindTexture(GL_TEXTURE_2D, up);
  }
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glBegin(GL_QUADS);
  // Top Face
  glNormal3f(0.0f, -normallength, 0.0f);
  glTexCoord2f(beginningmargin, tesselation + movement);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glTexCoord2f(beginningmargin, movement);
  glVertex3f(-xWidth, yWidth, zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(xWidth, yWidth, -zWidth);
  glEnd();
  if ((xrot <= 180 && xrot >= 0) || (firstperson == 1 || firstperson == 2)) {
    glBindTexture(GL_TEXTURE_2D, down);
  }
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glBegin(GL_QUADS);
  // Bottom Face
  glNormal3f(0.0f, normallength, 0.0f);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(beginningmargin, tesselation + movement);
  glVertex3f(xWidth, -yWidth, -zWidth);
  glTexCoord2f(beginningmargin, movement);
  glVertex3f(xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(-xWidth, -yWidth, zWidth);
  glEnd();
  if ((yrot >= 0 && yrot <= 180) || (firstperson == 1 || firstperson == 2)) {
    glBindTexture(GL_TEXTURE_2D, right);
  }
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glBegin(GL_QUADS);
  // Right face
  glNormal3f(-normallength, 0.0f, 0.0f);
  glTexCoord2f(tesselation, movement);
  glVertex3f(xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(xWidth, yWidth, -zWidth);
  glTexCoord2f(beginningmargin, tesselation + movement);
  glVertex3f(xWidth, yWidth, zWidth);
  glTexCoord2f(beginningmargin, movement);
  glVertex3f(xWidth, -yWidth, zWidth);
  // Left Face
  glEnd();
  if ((yrot >= 180 && yrot <= 360) || (firstperson == 1 || firstperson == 2)) {
    glBindTexture(GL_TEXTURE_2D, left);
  }
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glBegin(GL_QUADS);
  glNormal3f(normallength, 0.0f, 0.0f);
  glTexCoord2f(beginningmargin, movement);
  glVertex3f(-xWidth, -yWidth, -zWidth);
  glTexCoord2f(tesselation, movement);
  glVertex3f(-xWidth, -yWidth, zWidth);
  glTexCoord2f(tesselation, tesselation + movement);
  glVertex3f(-xWidth, yWidth, zWidth);
  glTexCoord2f(beginningmargin, tesselation + movement);
  glVertex3f(-xWidth, yWidth, -zWidth);
  glEnd();
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glDepthMask(1);
  yrot = realyrot;
}

int DrawGLScene(GLvoid) // Here's Where We Do All The Drawing
{
  int x, y, a, b, c, d, e, f;
  float g;
  float ydist, dist, longestdist, longestydist, targetxrot;
  float xpos, ypos;
  static char aChar[256] = "";

  glLoadIdentity(); // Reset The View

  if (firstperson && guytrack == 0) {
    guytrack = 1;
  }
  if (guytrack && numplayers > 0) {
    xpos = 0;
    ypos = 0;
    for (a = 0; a < numplayers; a++) {
      xpos += -guyx[a] - 100;
      ypos += -guyy[a] - 200;
    }
    xpos /= numplayers;
    ypos /= numplayers;
    targetcamerax = xpos;
    targetcameray = ypos;
    targetcameray -= xrot;
    camerax = (camerax * 5 + targetcamerax * multiplier / 10) / (5 + multiplier / 10);
    cameray = (cameray * 5 + targetcameray * multiplier / 10) / (5 + multiplier / 10);
    longestdist = 0;
    if (numplayers > 1) {
      for (a = 0; a < numplayers; a++) {
        for (b = 0; b < numplayers - 1; b++) {
          dist = std::sqrt(absolute(guyx[a] - guyx[b]) * absolute(guyx[a] - guyx[b]) + absolute(guyy[a] - guyy[b]) * absolute(guyy[a] - guyy[b]));
          ydist = absolute(guyy[a] - guyy[b]);
          if (dist > longestdist) {
            longestdist = dist;
            longestydist = ydist;
          }
        }
      }
    }
    if (numplayers == 1) {
      longestdist = 30 + absolute(guyvelx[0] * 100) + absolute(guyvely[0] * 100);
      longestydist = 0;
    }
    // z=-60-fast_sqrt(absolute(guyx[0]-guyx[1])*absolute(guyx[0]-guyx[1])+absolute(guyy[0]-guyy[1])*absolute(guyy[0]-guyy[1]));
    targetz = -40 - longestdist * 1.5;
    if (firstperson == 0 || firstperson == 3) {
      xrot = 0;
      if (firstperson == 3) {
        yrot = 0;
        camerax = xpos;
        cameray = ypos;
        if (targetz > -450) {
          z = targetz / 2;
        }
      }
      if (longestydist >= 100) {
        xrot = (longestydist - 100) / 5;
        if (targetxrot > 65) {
          targetxrot = 65;
        }
        if (xrot > 65) {
          xrot = 65;
        }
      }
      if (targetz < -400) {
        targetz = -400;
      }
      z = (z * 10 + targetz * multiplier / 10) / (10 + multiplier / 10);
      cameraz = 0;
      if (cube) {
        BoundCamera();
      }
    }
    if (firstperson == 1) {
      point = FindEyePoint(0);
      camerax = -point.x - 100;
      cameray = -point.y - 195.2;
      cameraz = -point.z;
      z = 0;
      point = FindEyeRot(0);
      yrot = point.y;
      xrot = point.x;
      // yrot=point.y;
      guytrack = 1;
    }
    if (firstperson == 2) {
      point = FindEyePoint(1);
      camerax = -point.x - 100;
      cameray = -point.y - 195.2;
      cameraz = -point.z;
      z = 0;
      point = FindEyeRot(1);
      yrot = point.y;
      xrot = point.x;
      // yrot=point.y;
      guytrack = 1;
    }
  }
  // glEnable(GL_TEXTURE_GEN_S);							// Enable Texture Coord Generation For S (NEW)
  // glEnable(GL_TEXTURE_GEN_T);							// Enable Texture Coord Generation For T (NEW)
  if (cube && guytrack) {
    BoundCamera();
  }
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, z);
  glRotatef(xrot, 1.0f, 0.0f, 0.0f);
  glRotatef(yrot, 0.0f, 1.0f, 0.0f);
  glTranslatef(camerax, cameray, cameraz);
  lightz = 1000;
  lightx = -1000;
  lighty = 1000;
  LightPosition[0] = lightx;
  LightPosition[1] = lighty;
  LightPosition[2] = lightz;
  glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
  glTranslatef(0.0f, -6.0f, 0.0f);
  glColor4f(0.1, 0.1, 0.1, 0.1);
  glDisable(GL_CULL_FACE);
  glPushMatrix();
  glTranslatef(0.0f, 152.0f, 0.0f);
  glBindTexture(GL_TEXTURE_2D, themebacknum);
  if (theme == marbletheme) {
    glDrawBigCube(470, 465, 465, 3, 10);
  }
  if (theme == trontheme) {
    glDrawBigCube(467, 464, 464, 30, 10);
  }
  if (theme == woodtheme) {
    glDrawBigCube(470, 465, 465, 4, 10);
  }
  if (theme == metaltheme) {
    glDrawBigCube(470, 465, 465, 1, 10);
  }
  if (theme == matrixtheme) {
    // glDisable(GL_LIGHTING);
    glColor4f(200.0, 200.0, 200.0, 1.0);
    glDrawBigCube(546, 546, 546, 10, slide + 1);
    // glEnable(GL_LIGHTING);
  }
  if (theme == islandtheme) {
    glPushMatrix();
    glLoadIdentity();
    glRotatef(xrot + .1, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot + .1, 0.0f, 1.0f, 0.0f);
    glDisable(GL_LIGHTING);
    glColor4f(255.0, 255.0, 255.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, 44);
    // glScalef(10,10,10);
    glDisable(GL_FOG);
    glEnvironmentCube(environment[0].front, environment[0].left, environment[0].back, environment[0].right, environment[0].up, environment[0].down, 5);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }
  if (theme == lavatheme) {
    glPushMatrix();
    glLoadIdentity();
    glRotatef(xrot + .1, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot + .1, 0.0f, 1.0f, 0.0f);
    glDisable(GL_LIGHTING);
    glColor4f(255.0, 255.0, 255.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, 44);
    // glScalef(10,10,10);
    glDisable(GL_FOG);
    glEnvironmentCube(environment[1].front, environment[1].left, environment[1].back, environment[1].right, environment[1].up, environment[1].down, 5);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }
  if (theme == snowtheme) {
    glPushMatrix();
    glLoadIdentity();
    glRotatef(xrot + .1, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot + .1, 0.0f, 1.0f, 0.0f);
    glDisable(GL_LIGHTING);
    glColor4f(255.0, 255.0, 255.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, 44);
    // glScalef(10,10,10);
    glDisable(GL_FOG);
    glEnvironmentCube(environment[2].front, environment[2].left, environment[2].back, environment[2].right, environment[2].up, environment[2].down, 5);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }
  glPopMatrix();
  glEnable(GL_CULL_FACE);
  glPushMatrix();

  glColor4f(1.0, 1.0, 1.0, 1.0);
  glBindTexture(GL_TEXTURE_2D, themebasenum);
  glTranslatef(300.0f, 1000.0f, 0.0f);
  if (theme == shinytheme) {
    glEnable(GL_TEXTURE_GEN_S); // Enable Texture Coord Generation For S (NEW)
    glEnable(GL_TEXTURE_GEN_T);
  }
  for (x = 20; x < 80; x++) {
    glPushMatrix();
    glTranslatef(-600.0f, -20 * (x + 1), 0.0f);
    for (y = 20; y < 80; y++) {
      glTranslatef(10.0f, 0.0f, 0.0f);
      if (x != 64 || Map[y][x] != 1) {
        if (Map[y][x] == 1) {
          if (theme == matrixtheme || theme == shinytheme) {
            glDisable(GL_LIGHTING);
            glColor4f(255.0, 255.0, 255.0, 1.0);
            glDrawFloor(5, .9, 5, slide);
            glEnable(GL_LIGHTING);
          }
          if (theme != matrixtheme && theme != shinytheme) {
            Floor(0);
          }
        }
        if (Map[y][x] == 2) {
          if (theme == matrixtheme || theme == shinytheme) {
            glDisable(GL_LIGHTING);
            glColor4f(300.0, 300.0, 300.0, 1.0);
            glDrawFloor(5, .9, 5, slide);
            glEnable(GL_LIGHTING);
          }
          if (theme != matrixtheme && theme != shinytheme) {
            Floor(0);
          }
          glPushMatrix();
          glScalef(1.2, 1.355, 1.2);
          glBindTexture(GL_TEXTURE_2D, themeropenum);
          Rope();
          glBindTexture(GL_TEXTURE_2D, themebasenum);
          glPopMatrix();
        }
        if (Map[y][x] == 3) {
          glPushMatrix();
          glScalef(1.2, 1.355, 1.2);
          glBindTexture(GL_TEXTURE_2D, themeropenum);
          Rope();
          glBindTexture(GL_TEXTURE_2D, themebasenum);
          glPopMatrix();
        }
        if (Walls[y][x] != 0) {
          glPushMatrix();
          glTranslatef(4.5f, 9.0f, 0.0f);
          glBindTexture(GL_TEXTURE_2D, themebasenum);
          if (theme == matrixtheme) {
            glDisable(GL_LIGHTING);
            glColor4f(255.0, 255.0, 255.0, 1.0);
            glDrawFloor(1, 10, 4.5, slide);
            glEnable(GL_LIGHTING);
          }
          if (theme != matrixtheme) {
            Wall();
          }
          glBindTexture(GL_TEXTURE_2D, themebasenum);
          glPopMatrix();
        }
      }
    }
    glPopMatrix();
  }
  glPopMatrix();
  // glDisable(GL_CULL_FACE);
  if (theme == shinytheme) {
    glDisable(GL_TEXTURE_GEN_S); // Enable Texture Coord Generation For S (NEW)
    glDisable(GL_TEXTURE_GEN_T);
  }
  for (x = 0; x < numplayers; x++) {
    if (invisible[x] == 0) {
      DrawGuys(x, 0);
    }
  }
  for (x = 0; x < numplayers; x++) {
    if (invisible[x] == 1) {
      DrawGuys(x, 0);
    }
  }

  glDisable(GL_CULL_FACE);
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, themebacknum);
  glTranslatef(0.0f, 152.0f, 0.0f);
  if (theme == marbletheme) {
    glDrawBigCube(455, 451.5, 450, 3, 0);
  }
  if (theme == trontheme) {
    glDrawBigCube(455, 451.5, 450, 30, 0);
  }
  if (theme == woodtheme) {
    glDrawBigCube(455, 451.5, 450, 4, 0);
  }
  if (theme == metaltheme) {
    glDrawBigCube(455, 451.5, 450, 1, 0);
  }
  if (theme == matrixtheme) {
    // glDisable(GL_LIGHTING);
    glColor4f(200.0, 200.0, 200.0, 1.0);
    glDrawBigCube(455, 451.5, 450, 10, slide);
    // glEnable(GL_LIGHTING);
  }
  if (theme == islandtheme) {
    glPushMatrix();
    glLoadIdentity();
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glDisable(GL_LIGHTING);
    glColor4f(255.0, 255.0, 255.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, 44);
    // glScalef(10,10,10);
    glDisable(GL_FOG);
    glEnvironmentCube(environment[0].front, environment[0].left, environment[0].back, environment[0].right, environment[0].up, environment[0].down, 5);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }
  if (theme == lavatheme) {
    glPushMatrix();
    glLoadIdentity();
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glDisable(GL_LIGHTING);
    glColor4f(255.0, 255.0, 255.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, 44);
    // glScalef(10,10,10);
    glDisable(GL_FOG);
    glEnvironmentCube(environment[1].front, environment[1].left, environment[1].back, environment[1].right, environment[1].up, environment[1].down, 5);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }
  if (theme == snowtheme) {
    glPushMatrix();
    glLoadIdentity();
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glDisable(GL_LIGHTING);
    glColor4f(255.0, 255.0, 255.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, 44);
    // glScalef(10,10,10);
    glDisable(GL_FOG);
    glEnvironmentCube(environment[2].front, environment[2].left, environment[2].back, environment[2].right, environment[2].up, environment[2].down, 5);
    if (fogtoggle) {
      glEnable(GL_FOG);
    }
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }
  glPopMatrix();
  glEnable(GL_CULL_FACE);
  glPushMatrix();
  glTranslatef(500.0f, 1000.0f, 0.0f);
  for (x = 0; x < 100; x++) {
    glPushMatrix();
    glTranslatef(-1000.0f, -20 * (x + 1), 0.0f);
    for (y = 0; y < 100; y++) {
      glTranslatef(10.0f, 0.0f, 0.0f);
      if (selectedx == y && selectedy == x && mapeditor == 1) {
        glDepthMask(0);
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glTranslatef(0.0f, 11.0f, 0.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        if (fogtoggle) {
          glDisable(GL_FOG);
        }
        glColor4f(300.0, 300.0, 300.0, 1.0);
        glDrawCube(6, 11, 6, 1);
        if (wireframe == 0) {
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glColor4f(1.0, 1.0, 1.0, 0.1);
        glDrawCube(6, 11, 6, 1);
        if (fogtoggle) {
          glEnable(GL_FOG);
        }
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
        glTranslatef(0.0f, -11.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, themebasenum);
        glDepthMask(1);
      }
      for (a = 2; a < 13; a++) {
        if (compxstep[1][a] == y && compystep[1][a] == x && showinfo == 2 && compxstep[1][a] != -1000) {
          g = a;
          glDepthMask(0);
          glBindTexture(GL_TEXTURE_2D, texture[1]);
          glTranslatef(0.0f, 11.0f, 0.0f);
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
          glDisable(GL_LIGHTING);
          glEnable(GL_BLEND);
          if (fogtoggle) {
            glDisable(GL_FOG);
          }
          glColor4f(300.0, 000.0, 300.0, 1.0);
          glDrawCube(6 - g / 2, 11 - g / 2, 6 - g / 2, 1);
          if (wireframe == 0) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
          }
          glColor4f(1.0, 0.0, 1.0, 0.1);
          glDrawCube(6 - g / 2, 11 - g / 2, 6 - g / 2, 1);
          if (fogtoggle) {
            glEnable(GL_FOG);
          }
          glDisable(GL_BLEND);
          glEnable(GL_LIGHTING);
          glTranslatef(0.0f, -11.0f, 0.0f);
          glBindTexture(GL_TEXTURE_2D, themebasenum);
          glDepthMask(1);
        }
      }
    }
    glPopMatrix();
  }
  glPopMatrix();

  for (x = 0; x < numplayers; x++) {
    if (itemtype[x] == 1) {
      DrawGuys(x, 1);
    }
  }

  glPushMatrix();
  // glTranslatef(100.0f,200.0f,0.0f);
  // glTranslatef(litx[0],lity[0],0);
  LightPosition[0] = litx[0] + 100;
  LightPosition[1] = lity[0] + 200;
  LightPosition[2] = 0;
  LightPosition[3] = 1;
  LightDiffuse[3] = lightbrightness[0] / 25500;
  LightDiffuse[3] = 0;
  // LightDiffuse[3] = 1;
  LightDiffuse[2] = 0;
  LightDiffuse[1] = lightbrightness[0] / 255;
  LightDiffuse[0] = lightbrightness[0] / 255;
  if (lightbrightness[0] <= 0) {
    lighton[0] = 0;
  }
  if (lightbrightness[0] > 0) {
    lightbrightness[0] -= multiplier * 3 * gamespeed;
  }
  if (lighton[0] == 1) {
    glEnable(GL_LIGHT2);
  }
  if (lighton[0] == 0) {
    glDisable(GL_LIGHT2);
  }
  glLightfv(GL_LIGHT2, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse);
  // glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, .01);
  glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, .01);
  glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, .01);
  /*glTranslatef(litx[0]+100,lity[0]+200,0);
  glColor4f(300.0, 300.0, 300.0, 1.0);
                  glDrawCube(1,1,1,1);*/
  glPopMatrix();
  glPushMatrix();
  LightPosition[0] = litx[1] + 100;
  LightPosition[1] = lity[1] + 200;
  LightPosition[2] = 0;
  LightPosition[3] = 1;
  LightDiffuse[3] = lightbrightness[1] / 25500;
  LightDiffuse[3] = 0;
  // LightDiffuse[3] = 1;
  LightDiffuse[2] = lightbrightness[1] / 255;
  LightDiffuse[1] = 0;
  LightDiffuse[0] = 0;
  if (lightbrightness[1] <= 0) {
    lighton[1] = 0;
  }
  if (lightbrightness[1] > 0) {
    lightbrightness[1] -= multiplier * gamespeed;
  }
  if (lighton[1] == 1) {
    glEnable(GL_LIGHT3);
  }
  if (lighton[1] == 0) {
    glDisable(GL_LIGHT3);
  }
  glLightfv(GL_LIGHT3, GL_POSITION, LightPosition);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, LightDiffuse);
  // glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, .01);
  glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, .01);
  glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, .01);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, texture[69]);
  glDisable(GL_LIGHTING);
  glEnable(GL_BLEND);
  if (fogtoggle) {
    glDisable(GL_FOG);
  }
  glDepthMask(0);
  for (y = 0; y < kMaxLightning; y++) {
    if (Lightning[y].brightness > 0) {
      glColor4f(.6, .6, .8, Lightning[y].brightness);
      glPushMatrix();
      glTranslatef(100, 200, 0);
      glTranslatef(-.5, 0, 0);
      glTranslatef(Lightning[y].x, Lightning[y].y, Lightning[y].z);
      glRotatef(Lightning[y].yrotation, 0, 1, 0);
      glRotatef(Lightning[y].zrotation, 0, 0, 1);
      for (x = 0; x < Lightning[y].tesselation - 2; x++) {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0, 0);
        glVertex3f(Lightning[y].LightningPoint[x][0], Lightning[y].LightningPoint[x][3] - .4, Lightning[y].LightningPoint[x][2]);
        glTexCoord2f(1, 0);
        glVertex3f(Lightning[y].LightningPoint[x + 1][0], Lightning[y].LightningPoint[x + 1][3] - .4, Lightning[y].LightningPoint[x + 1][2]);
        glTexCoord2f(0, 1);
        glVertex3f(Lightning[y].LightningPoint[x][0], Lightning[y].LightningPoint[x][3] + .4, Lightning[y].LightningPoint[x][2]);
        glTexCoord2f(1, 1);
        glVertex3f(Lightning[y].LightningPoint[x + 1][0], Lightning[y].LightningPoint[x + 1][3] + .4, Lightning[y].LightningPoint[x + 1][2]);
        glEnd();
      }
      glRotatef(60, 1, 0, 0);
      for (x = 0; x < Lightning[y].tesselation - 2; x++) {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0, 0);
        glVertex3f(Lightning[y].LightningPoint[x][0], Lightning[y].LightningPoint[x][3] + .4, Lightning[y].LightningPoint[x][2]);
        glTexCoord2f(1, 0);
        glVertex3f(Lightning[y].LightningPoint[x + 1][0], Lightning[y].LightningPoint[x + 1][3] + .4, Lightning[y].LightningPoint[x + 1][2]);
        glTexCoord2f(0, 1);
        glVertex3f(Lightning[y].LightningPoint[x][0], Lightning[y].LightningPoint[x][3] - .4, Lightning[y].LightningPoint[x][2]);
        glTexCoord2f(1, 1);
        glVertex3f(Lightning[y].LightningPoint[x + 1][0], Lightning[y].LightningPoint[x + 1][3] - .4, Lightning[y].LightningPoint[x + 1][2]);
        glEnd();
      }
      glRotatef(60, 1, 0, 0);
      for (x = 0; x < Lightning[y].tesselation - 2; x++) {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0, 0);
        glVertex3f(Lightning[y].LightningPoint[x][0], Lightning[y].LightningPoint[x][3] + .4, Lightning[y].LightningPoint[x][2]);
        glTexCoord2f(1, 0);
        glVertex3f(Lightning[y].LightningPoint[x + 1][0], Lightning[y].LightningPoint[x + 1][3] + .4, Lightning[y].LightningPoint[x + 1][2]);
        glTexCoord2f(0, 1);
        glVertex3f(Lightning[y].LightningPoint[x][0], Lightning[y].LightningPoint[x][3] - .4, Lightning[y].LightningPoint[x][2]);
        glTexCoord2f(1, 1);
        glVertex3f(Lightning[y].LightningPoint[x + 1][0], Lightning[y].LightningPoint[x + 1][3] - .4, Lightning[y].LightningPoint[x + 1][2]);
        glEnd();
      }
      glPopMatrix();
    }
  }

  glDisable(GL_CULL_FACE);
  glDepthMask(1);
  glBindTexture(GL_TEXTURE_2D, texture[70]);
  for (y = 0; y < numplayers; y++) {
    glPushMatrix();
    glTranslatef(100, 200, 0);
    glTranslatef(-.5, 0, 0);
    for (x = 0; x < maxswordtrail - 1; x++) {
      a = x + 1;
      if (a == maxswordtrail - 1) {
        a = 0;
      }
      if (x != unusedswordtrail[y] && SwordTrail[y][0].brightness[a][3] != 0 && SwordTrail[y][0].brightness[x][3] != 0) {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0, 0);
        glColor4f(SwordTrail[y][0].brightness[x][0], SwordTrail[y][0].brightness[x][1], SwordTrail[y][0].brightness[x][2], SwordTrail[y][0].brightness[x][3]);
        glVertex3f(SwordTrail[y][0].TrailPoint[x][0], SwordTrail[y][0].TrailPoint[x][1], SwordTrail[y][0].TrailPoint[x][2]);
        glTexCoord2f(1, 0);
        glColor4f(SwordTrail[y][0].brightness[a][0], SwordTrail[y][0].brightness[a][1], SwordTrail[y][0].brightness[a][2], SwordTrail[y][0].brightness[a][3]);
        glVertex3f(SwordTrail[y][0].TrailPoint[a][0], SwordTrail[y][0].TrailPoint[a][1], SwordTrail[y][0].TrailPoint[a][2]);
        glTexCoord2f(0, 1);
        glColor4f(SwordTrail[y][0].brightness[x][0], SwordTrail[y][0].brightness[x][1], SwordTrail[y][0].brightness[x][2], SwordTrail[y][0].brightness[x][3]);
        glVertex3f(SwordTrail[y][0].TrailPoint[x][3], SwordTrail[y][0].TrailPoint[x][4], SwordTrail[y][0].TrailPoint[x][5]);
        glTexCoord2f(1, 1);
        glColor4f(SwordTrail[y][0].brightness[a][0], SwordTrail[y][0].brightness[a][1], SwordTrail[y][0].brightness[a][2], SwordTrail[y][0].brightness[a][3]);
        glVertex3f(SwordTrail[y][0].TrailPoint[a][3], SwordTrail[y][0].TrailPoint[a][4], SwordTrail[y][0].TrailPoint[a][5]);
        glEnd();
      }
    }
    for (x = 0; x < maxswordtrail - 1; x++) {
      a = x + 1;
      if (a == maxswordtrail - 1) {
        a = 0;
      }
      if (x != unusedswordtrail[y] && SwordTrail[y][1].brightness[a][3] != 0 && SwordTrail[y][1].brightness[x][3] != 0) {
        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0, 0);
        glColor4f(SwordTrail[y][1].brightness[x][0], SwordTrail[y][1].brightness[x][1], SwordTrail[y][1].brightness[x][2], SwordTrail[y][1].brightness[x][3]);
        glVertex3f(SwordTrail[y][1].TrailPoint[x][0], SwordTrail[y][1].TrailPoint[x][1], SwordTrail[y][1].TrailPoint[x][2]);
        glTexCoord2f(1, 0);
        glColor4f(SwordTrail[y][1].brightness[a][0], SwordTrail[y][1].brightness[a][1], SwordTrail[y][1].brightness[a][2], SwordTrail[y][1].brightness[a][3]);
        glVertex3f(SwordTrail[y][1].TrailPoint[a][0], SwordTrail[y][1].TrailPoint[a][1], SwordTrail[y][1].TrailPoint[a][2]);
        glTexCoord2f(0, 1);
        glColor4f(SwordTrail[y][1].brightness[x][0], SwordTrail[y][1].brightness[x][1], SwordTrail[y][1].brightness[x][2], SwordTrail[y][1].brightness[x][3]);
        glVertex3f(SwordTrail[y][1].TrailPoint[x][3], SwordTrail[y][1].TrailPoint[x][4], SwordTrail[y][1].TrailPoint[x][5]);
        glTexCoord2f(1, 1);
        glColor4f(SwordTrail[y][1].brightness[a][0], SwordTrail[y][1].brightness[a][1], SwordTrail[y][1].brightness[a][2], SwordTrail[y][1].brightness[a][3]);
        glVertex3f(SwordTrail[y][1].TrailPoint[a][3], SwordTrail[y][1].TrailPoint[a][4], SwordTrail[y][1].TrailPoint[a][5]);
        glEnd();
      }
    }
    glPopMatrix();
  }
  glEnable(GL_CULL_FACE);
  for (x = 0; x < maxsprites; x++) {
    if (sprite[x].type != nothing) {
      if (sprite[x].type == grenade || sprite[x].type == chunk) {
        glPushMatrix();
        glColor4f(255, 255, 255, sprite[x].brightness / 255);
        glTranslatef(100.0f, 200.0f, 0.0f);
        glTranslatef(sprite[x].x, sprite[x].y, sprite[x].z);
        if (sprite[x].type != bouncesprite && sprite[x].type != water && sprite[x].type != grenade && sprite[x].type != chunk && sprite[x].type != exploflame && sprite[x].type != muzzleflashstars && sprite[x].type != lightningflashstars && sprite[x].type != smokesprite && sprite[x].type != invisiblestars2) {
          HandleSpriteTypes(x);
        }
        if (sprite[x].type != lasersprite && sprite[x].type != tracersprite && sprite[x].type != grenade && sprite[x].type != chunk) {
          glGetFloatv(GL_MODELVIEW_MATRIX, M);
          point.x = M[12];
          point.y = M[13];
          point.z = M[14];
          glLoadIdentity();
          glTranslatef(point.x, point.y, point.z);
        }
        if (sprite[x].type == bouncesprite || sprite[x].type == water || sprite[x].type == grenade || sprite[x].type == chunk || sprite[x].type == exploflame || sprite[x].type == muzzleflashstars || sprite[x].type == lightningflashstars || sprite[x].type == smokesprite || sprite[x].type == invisiblestars2) {
          HandleSpriteTypes(x);
        }
        // glRotatef(sprite[x].spin,0.0f,0.0f,1.0f);
        if (sprite[x].type != lasersprite && sprite[x].type != tracersprite && sprite[x].type != grenade && sprite[x].type != chunk) {
          glBindTexture(GL_TEXTURE_2D, texture[12]);
          if (sprite[x].type == smokesprite || sprite[x].type == exploflame) {
            glBindTexture(GL_TEXTURE_2D, texture[53]);
            glBlendFunc(GL_ZERO, GL_DST_ALPHA);
          }
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-.3f * sprite[x].size, -.3f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(.3f * sprite[x].size, -.3f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(.3f * sprite[x].size, .3f * sprite[x].size, 0.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-.3f * sprite[x].size, .3f * sprite[x].size, 0.0f);
          glEnd();
          if (sprite[x].type == smokesprite) {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
          }
        }
        if (sprite[x].type == grenade) {
          glEnable(GL_LIGHTING);
          glDisable(GL_BLEND);
          if (fogtoggle) {
            glEnable(GL_FOG);
          }
          glDepthMask(1);

          glBindTexture(GL_TEXTURE_2D, texture[67]);
          Grenade();

          glDisable(GL_LIGHTING);
          glEnable(GL_BLEND);
          if (fogtoggle) {
            glDisable(GL_FOG);
          }
          glDepthMask(0);
        }
        if (sprite[x].type == chunk) {
          glEnable(GL_LIGHTING);
          glDisable(GL_BLEND);
          if (fogtoggle) {
            glEnable(GL_FOG);
          }
          glDepthMask(1);

          glBindTexture(GL_TEXTURE_2D, themebasenum);
          Chunk();

          glDisable(GL_LIGHTING);
          glEnable(GL_BLEND);
          if (fogtoggle) {
            glDisable(GL_FOG);
          }
          glDepthMask(0);
        }
        if (sprite[x].type == lasersprite) {
          glPushMatrix();
          glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
          if (sprite[x].velx > 0) {
            glRotatef(180, 0.0, 1.0, 0.0);
          }
          glBindTexture(GL_TEXTURE_2D, texture[38]);
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-.6f * sprite[x].size, -.2f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(.6f * sprite[x].size, -.2f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(.6f * sprite[x].size, .2f * sprite[x].size, 0.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-.6f * sprite[x].size, .2f * sprite[x].size, 0.0f);
          glEnd();
          glPushMatrix();
          glRotatef(90, 1.0, 0.0, 0.0);
          glBindTexture(GL_TEXTURE_2D, texture[38]);
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-.6f * sprite[x].size, -.2f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(.6f * sprite[x].size, -.2f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(.6f * sprite[x].size, .2f * sprite[x].size, 0.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-.6f * sprite[x].size, .2f * sprite[x].size, 0.0f);
          glEnd();
          glPopMatrix();
          glPushMatrix();
          glBindTexture(GL_TEXTURE_2D, texture[39]);
          // glRotatef(90,0.0,1.0,0.0);
          glTranslatef(2.0f, 0.0f, 0.0f);
          glPushMatrix();
          glRotatef(yrot, 0.0f, 1.0f, 0.0f);
          glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-.1f * sprite[x].size, -.1f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(.1f * sprite[x].size, -.1f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(.1f * sprite[x].size, .1f * sprite[x].size, 0.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-.1f * sprite[x].size, .1f * sprite[x].size, 0.0f);
          glEnd();
          glPopMatrix();
          glTranslatef(-4.0f, 0.0f, 0.0f);
          glPushMatrix();
          glRotatef(yrot, 0.0f, 1.0f, 0.0f);
          glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-.1f * sprite[x].size, -.1f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(.1f * sprite[x].size, -.1f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(.1f * sprite[x].size, .1f * sprite[x].size, 0.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-.1f * sprite[x].size, .1f * sprite[x].size, 0.0f);
          glEnd();
          glPopMatrix();
          glPopMatrix();
          glPopMatrix();
        }
        if (sprite[x].type == tracersprite) {
          glPushMatrix();
          glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
          if (sprite[x].velx > 0) {
            glRotatef(180, 0.0, 1.0, 0.0);
          }
          glBindTexture(GL_TEXTURE_2D, texture[38]);
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-.6f * sprite[x].size, -.05f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(.6f * sprite[x].size, -.05f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(.6f * sprite[x].size, .05f * sprite[x].size, 0.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-.6f * sprite[x].size, .05f * sprite[x].size, 0.0f);
          glEnd();
          glPushMatrix();
          glRotatef(90, 1.0, 0.0, 0.0);
          glBindTexture(GL_TEXTURE_2D, texture[38]);
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-.6f * sprite[x].size, -.05f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(.6f * sprite[x].size, -.05f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(.6f * sprite[x].size, .05f * sprite[x].size, 0.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-.6f * sprite[x].size, .05f * sprite[x].size, 0.0f);
          glEnd();
          glPopMatrix();
          glPushMatrix();
          glBindTexture(GL_TEXTURE_2D, texture[39]);
          // glRotatef(90,0.0,1.0,0.0);
          glTranslatef(2.0f, 0.0f, 0.0f);
          glPushMatrix();
          glRotatef(yrot, 0.0f, 1.0f, 0.0f);
          glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-.025f * sprite[x].size, -.025f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(.025f * sprite[x].size, -.025f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(.025f * sprite[x].size, .025f * sprite[x].size, 0.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-.025f * sprite[x].size, .025f * sprite[x].size, 0.0f);
          glEnd();
          glPopMatrix();
          glTranslatef(-4.0f, 0.0f, 0.0f);
          glPushMatrix();
          glRotatef(yrot, 0.0f, 1.0f, 0.0f);
          glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
          glBegin(GL_QUADS);
          glTexCoord2f(0.0f, 0.0f);
          glVertex3f(-.025f * sprite[x].size, -.025f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 0.0f);
          glVertex3f(.025f * sprite[x].size, -.025f * sprite[x].size, 0.0f);
          glTexCoord2f(1.0f, 1.0f);
          glVertex3f(.025f * sprite[x].size, .025f * sprite[x].size, 0.0f);
          glTexCoord2f(0.0f, 1.0f);
          glVertex3f(-.025f * sprite[x].size, .025f * sprite[x].size, 0.0f);
          glEnd();
          glPopMatrix();
          glPopMatrix();
          glPopMatrix();
        }
        glPopMatrix();
      }
    }
  }

  glDisable(GL_LIGHTING);
  glEnable(GL_BLEND);
  if (fogtoggle) {
    glDisable(GL_FOG);
  }
  glDepthMask(0);
  for (x = 0; x < maxsprites; x++) {
    if (sprite[x].type != nothing && sprite[x].type != grenade && sprite[x].type != chunk) {
      glPushMatrix();
      glColor4f(255, 255, 255, sprite[x].brightness / 255);
      glTranslatef(100.0f, 200.0f, 0.0f);
      glTranslatef(sprite[x].x, sprite[x].y, sprite[x].z);
      if (sprite[x].type != bouncesprite && sprite[x].type != water && sprite[x].type != grenade && sprite[x].type != chunk && sprite[x].type != exploflame && sprite[x].type != muzzleflashstars && sprite[x].type != lightningflashstars && sprite[x].type != smokesprite && sprite[x].type != invisiblestars2) {
        HandleSpriteTypes(x);
      }
      if (sprite[x].type != lasersprite && sprite[x].type != tracersprite && sprite[x].type != grenade && sprite[x].type != chunk) {
        glGetFloatv(GL_MODELVIEW_MATRIX, M);
        point.x = M[12];
        point.y = M[13];
        point.z = M[14];
        glLoadIdentity();
        glTranslatef(point.x, point.y, point.z);
      }
      if (sprite[x].type == bouncesprite || sprite[x].type == water || sprite[x].type == grenade || sprite[x].type == chunk || sprite[x].type == exploflame || sprite[x].type == muzzleflashstars || sprite[x].type == lightningflashstars || sprite[x].type == smokesprite || sprite[x].type == invisiblestars2) {
        HandleSpriteTypes(x);
      }
      // glRotatef(sprite[x].spin,0.0f,0.0f,1.0f);
      if (sprite[x].type != lasersprite && sprite[x].type != tracersprite && sprite[x].type != grenade && sprite[x].type != chunk) {
        glBindTexture(GL_TEXTURE_2D, texture[12]);
        if (sprite[x].type == smokesprite || sprite[x].type == exploflame) {
          glBindTexture(GL_TEXTURE_2D, texture[53]);
          // glBlendFunc(GL_ONE_MIUNUS, GL_SRC_COLOR);
        }
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.3f * sprite[x].size, -.3f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(.3f * sprite[x].size, -.3f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(.3f * sprite[x].size, .3f * sprite[x].size, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.3f * sprite[x].size, .3f * sprite[x].size, 0.0f);
        glEnd();
        // if(sprite[x].type==smokesprite){glBlendFunc( GL_SRC_ALPHA, GL_ONE );}
      }
      if (sprite[x].type == grenade) {
        glEnable(GL_LIGHTING);
        glDisable(GL_BLEND);
        if (fogtoggle) {
          glEnable(GL_FOG);
        }
        glDepthMask(1);

        glBindTexture(GL_TEXTURE_2D, texture[67]);
        Grenade();

        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        if (fogtoggle) {
          glDisable(GL_FOG);
        }
        glDepthMask(0);
      }
      if (sprite[x].type == chunk) {
        glEnable(GL_LIGHTING);
        glDisable(GL_BLEND);
        if (fogtoggle) {
          glEnable(GL_FOG);
        }
        glDepthMask(1);

        glBindTexture(GL_TEXTURE_2D, themebasenum);
        Chunk();

        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        if (fogtoggle) {
          glDisable(GL_FOG);
        }
        glDepthMask(0);
      }
      if (sprite[x].type == lasersprite) {
        glDisable(GL_CULL_FACE);
        glPushMatrix();
        glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
        if (sprite[x].velx > 0) {
          glRotatef(180, 0.0, 1.0, 0.0);
        }
        glBindTexture(GL_TEXTURE_2D, texture[38]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.6f * sprite[x].size, -.2f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(.6f * sprite[x].size, -.2f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(.6f * sprite[x].size, .2f * sprite[x].size, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.6f * sprite[x].size, .2f * sprite[x].size, 0.0f);
        glEnd();
        glPushMatrix();
        glRotatef(90, 1.0, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, texture[38]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.6f * sprite[x].size, -.2f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(.6f * sprite[x].size, -.2f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(.6f * sprite[x].size, .2f * sprite[x].size, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.6f * sprite[x].size, .2f * sprite[x].size, 0.0f);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[39]);
        // glRotatef(90,0.0,1.0,0.0);
        glTranslatef(2.0f, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(yrot, 0.0f, 1.0f, 0.0f);
        glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.1f * sprite[x].size, -.1f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(.1f * sprite[x].size, -.1f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(.1f * sprite[x].size, .1f * sprite[x].size, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.1f * sprite[x].size, .1f * sprite[x].size, 0.0f);
        glEnd();
        glPopMatrix();
        glTranslatef(-4.0f, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(yrot, 0.0f, 1.0f, 0.0f);
        glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.1f * sprite[x].size, -.1f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(.1f * sprite[x].size, -.1f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(.1f * sprite[x].size, .1f * sprite[x].size, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.1f * sprite[x].size, .1f * sprite[x].size, 0.0f);
        glEnd();
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
      }
      if (sprite[x].type == tracersprite) {
        glDisable(GL_CULL_FACE);
        glPushMatrix();
        glRotatef(sprite[x].spin, 0.0f, 0.0f, 1.0f);
        if (sprite[x].velx > 0) {
          glRotatef(180, 0.0, 1.0, 0.0);
        }
        glBindTexture(GL_TEXTURE_2D, texture[38]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.6f * sprite[x].size, -.05f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(.6f * sprite[x].size, -.05f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(.6f * sprite[x].size, .05f * sprite[x].size, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.6f * sprite[x].size, .05f * sprite[x].size, 0.0f);
        glEnd();
        glPushMatrix();
        glRotatef(90, 1.0, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, texture[38]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.6f * sprite[x].size, -.05f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(.6f * sprite[x].size, -.05f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(.6f * sprite[x].size, .05f * sprite[x].size, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.6f * sprite[x].size, .05f * sprite[x].size, 0.0f);
        glEnd();
        glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[39]);
        // glRotatef(90,0.0,1.0,0.0);
        glTranslatef(2.0f, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(yrot, 0.0f, 1.0f, 0.0f);
        glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.025f * sprite[x].size, -.025f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(.025f * sprite[x].size, -.025f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(.025f * sprite[x].size, .025f * sprite[x].size, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.025f * sprite[x].size, .025f * sprite[x].size, 0.0f);
        glEnd();
        glPopMatrix();
        glTranslatef(-4.0f, 0.0f, 0.0f);
        glPushMatrix();
        glRotatef(yrot, 0.0f, 1.0f, 0.0f);
        glRotatef(-xrot, 1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-.025f * sprite[x].size, -.025f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(.025f * sprite[x].size, -.025f * sprite[x].size, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(.025f * sprite[x].size, .025f * sprite[x].size, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-.025f * sprite[x].size, .025f * sprite[x].size, 0.0f);
        glEnd();
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
      }
      glEnable(GL_CULL_FACE);
      glPopMatrix();
    }
  }
  glDepthMask(1);
  if (fogtoggle) {
    glEnable(GL_FOG);
  }
  glDisable(GL_BLEND);
  glBindTexture(GL_TEXTURE_2D, texture[71]);
  glEnable(GL_BLEND);
  glColor4f(255.0f, 255.0f, 255.0f, .5f);
  if (showinfo == 3) {
    glColor3f(1, 1, 1);

    if (changablejump) {
      glPrint(2, 320, "Gravity and jump strength are CHANGABLE.", 0, .8);
    }
    if (!changablejump) {
      glPrint(2, 320, "Gravity and jump strength are NOT CHANGABLE.", 0, .8);
    }
    sprintf(aChar, "Jump strength is at %dx.", (int)jumpstrength);
    glPrint(2, 300, aChar, 0, .8);
    sprintf(aChar, "Gravity is at %d%.", (int)(gravity * 1000));
    glPrint(2, 280, aChar, 0, .8);

    if (unlimitedammo) {
      glPrint(2, 240, "Unlimited ammo is ENABLED.", 0, .8);
    }
    if (!unlimitedammo) {
      glPrint(2, 240, "Unlimited ammo is NOT ENABLED.", 0, .8);
    }

    glColor3f(1, 1, 1);
    glColor3f(1, 1, 1);
    if (itemnum[1] == 0) {
      sprintf(aChar, "Player two is unarmed.");
    }
    if (itemnum[1] == 1) {
      sprintf(aChar, "Player two has a laser rifle with %d shots left.", (int)ammo[1]);
    }
    if (itemnum[1] == 2 && itemtype[1] == 0) {
      sprintf(aChar, "Player two has a sword.");
    }
    if (itemnum[1] == 3 && itemtype[1] == 0) {
      sprintf(aChar, "Player two has two swords.");
    }
    if (itemnum[1] == 2 && itemtype[1] == 1) {
      sprintf(aChar, "Player two has a lightsaber.");
    }
    if (itemnum[1] == 3 && itemtype[1] == 1) {
      sprintf(aChar, "Player two has two lightsabers.");
    }
    if (itemnum[1] == 4) {
      sprintf(aChar, "Player two has a spread machinegun with %d shots left.", (int)ammo[1]);
    }
    if (itemnum[1] == 5) {
      sprintf(aChar, "Player two has an assault rifle with %d shots left.", (int)ammo[1]);
    }
    if (itemnum[1] == 6 && itemtype[1] == 0) {
      sprintf(aChar, "Player two has an impact grenade launcher with %d shots left.", (int)(ammo[1] + 4) / 5);
    }
    if (itemnum[1] == 6 && itemtype[1] == 1) {
      sprintf(aChar, "Player two has a remote-detonated grenade launcher with %d shots left.", (int)(ammo[1] + 4) / 5);
    }
    if (itemnum[1] == 7) {
      sprintf(aChar, "Player two has a lightning gun with %f ammo left.", ammo[1]);
    }
    glPrint(2, 200, aChar, 0, .8);

    if (computercontrolled[1] == 1 && AIOffensive == 1) {
      glColor3f(1, .7, .7);
      sprintf(aChar, "Player two is controlled by the computer and is HOSTILE.");
    }
    if (computercontrolled[1] == 1 && AIOffensive == 0) {
      glColor3f(1, 1, .7);
      sprintf(aChar, "Player two is controlled by the computer and is PEACEFUL.");
    }
    if (computercontrolled[1] == 0) {
      glColor3f(1, 1, 1);
      sprintf(aChar, "Player two is NOT controlled by the computer.");
    }
    glPrint(2, 180, aChar, 0, .8);

    if (health[1] > 0) {
      glColor3f(1, (float)health[1] / 100, (float)health[1] / 100);
      sprintf(aChar, "Player two has %d health.", health[1]);
      glPrint(2, 160, aChar, 0, .8);
    }
    if (health[1] <= 0 && health[1] > -400) {
      glColor3f(1, 0, 0);
      sprintf(aChar, "Player two is DEAD.");
      glPrint(2, 160, aChar, 0, .8);
    }
    if (health[1] <= -400 || exists[1] == 0) {
      glColor3f(1, 0, 1);
      sprintf(aChar, "Player two is VAPORIZED.");
      glPrint(2, 160, aChar, 0, .8);
    }

    glColor3f(.8, .8, 1);
    sprintf(aChar, "Player two is at the position %d,%d.", guymapx[1], guymapy[1]);
    glPrint(2, 140, aChar, 0, .8);

    glColor3f(1, 1, 1);
    if (itemnum[0] == 0) {
      sprintf(aChar, "Player one is unarmed.");
    }
    if (itemnum[0] == 1) {
      sprintf(aChar, "Player one has a laser rifle with %d shots left.", (int)ammo[0]);
    }
    if (itemnum[0] == 2 && itemtype[0] == 0) {
      sprintf(aChar, "Player one has a sword.");
    }
    if (itemnum[0] == 3 && itemtype[0] == 0) {
      sprintf(aChar, "Player one has two swords.");
    }
    if (itemnum[0] == 2 && itemtype[0] == 1) {
      sprintf(aChar, "Player one has a lightsaber.");
    }
    if (itemnum[0] == 3 && itemtype[0] == 1) {
      sprintf(aChar, "Player one has two lightsabers.");
    }
    if (itemnum[0] == 4) {
      sprintf(aChar, "Player one has a spread machinegun with %d shots left.", (int)ammo[0]);
    }
    if (itemnum[0] == 5) {
      sprintf(aChar, "Player one has an assault rifle with %d shots left.", (int)ammo[0]);
    }
    if (itemnum[0] == 6 && itemtype[0] == 0) {
      sprintf(aChar, "Player one has an impact grenade launcher with %d shots left.", (int)(ammo[0] + 4) / 5);
    }
    if (itemnum[0] == 6 && itemtype[0] == 1) {
      sprintf(aChar, "Player one has a remote-detonated grenade launcher with %d shots left.", (int)(ammo[0] + 4) / 5);
    }
    if (itemnum[0] == 7) {
      sprintf(aChar, "Player one has a lightning gun with %f ammo left.", ammo[0]);
    }
    glPrint(2, 100, aChar, 0, .8);

    if (computercontrolled[0] == 1 && AIOffensive == 1) {
      glColor3f(1, .7, .7);
      sprintf(aChar, "Player one is controlled by the computer and is HOSTILE.");
    }
    if (computercontrolled[0] == 1 && AIOffensive == 0) {
      glColor3f(1, 1, .7);
      sprintf(aChar, "Player one is controlled by the computer and is PEACEFUL.");
    }
    if (computercontrolled[0] == 0) {
      glColor3f(1, 1, 1);
      sprintf(aChar, "Player one is NOT controlled by the computer.");
    }
    glPrint(2, 80, aChar, 0, .8);

    if (health[0] > 0) {
      glColor3f(1, (float)health[0] / 100, (float)health[0] / 100);
      sprintf(aChar, "Player one has %d health.", health[0]);
      glPrint(2, 60, aChar, 0, .8);
    }
    if (health[0] <= 0 && health[0] > -400) {
      glColor3f(1, 0, 0);
      sprintf(aChar, "Player one is DEAD.");
      glPrint(2, 60, aChar, 0, .8);
    }
    if (health[0] <= -400 || exists[0] == 0) {
      glColor3f(1, 0, 1);
      sprintf(aChar, "Player one is VAPORIZED.");
      glPrint(2, 60, aChar, 0, .8);
    }

    glColor3f(.8, .8, 1);
    sprintf(aChar, "Player one is at the position %d,%d.", guymapx[0], guymapy[0]);
    glPrint(2, 40, aChar, 0, .8);

    glColor3f(1, 1, 1);
    sprintf(aChar, "Frames per second is about %d.", (int)framespersecond);
    glPrint(2, 2, aChar, 0, 1);
  }
  glDisable(GL_BLEND);
  glEnable(GL_LIGHTING);

  //*************************************//
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glLoadIdentity();

  glLoadIdentity();
  glTranslatef(-36.0f, 3.0f, -70);
  sprintf(aChar, "FramesPerSecond:    %f", framespersecond);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, 8.0f, -70);
  sprintf(aChar, "Guymapx:    %d", guymapx[1]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 2)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -13.0f, -70);
  sprintf(aChar, "StartNum:    %d", playerstartnum);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -12.0f, -70);
  sprintf(aChar, "RandomNumbers: %d", randomint);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, 2.0f, -70);
  sprintf(aChar, "Activity:    %d", activity[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, 1.0f, -70);
  sprintf(aChar, "Anim:       %d", anim[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, 0.0f, -70);
  sprintf(aChar, "TargetAnim:  %d", targetanim[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -1.0f, -70);
  sprintf(aChar, "Frame:  %d", frame[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -2.0f, -70);
  sprintf(aChar, "TargetFrame:  %d", targetframe[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -3.0f, -70);
  sprintf(aChar, "Multiplier:  %f", multiplier);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -4.0f, -70);
  sprintf(aChar, "YVelocity:  %f", guyvely[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -5.0f, -70);
  sprintf(aChar, "Camerax:  %f", camerax);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -6.0f, -70);
  sprintf(aChar, "Cameray:  %f", cameray);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -7.0f, -70);
  sprintf(aChar, "Guymapx:  %d", guymapx[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -8.0f, -70);
  sprintf(aChar, "Guymapy:  %d", guymapy[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -9.0f, -70);
  sprintf(aChar, "Selectedx:  %d", selectedx);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -10.0f, -70);
  sprintf(aChar, "Selectedy:  %d", selectedy);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -11.0f, -70);
  sprintf(aChar, "Time:  %f", time[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -14.0f, -70);
  sprintf(aChar, "XVelocity:  %f", guyvelx[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -15.0f, -70);
  sprintf(aChar, "Whichhurt:  %d", whichhurt);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -16.0f, -70);
  sprintf(aChar, "Health1:  %d", health[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -17.0f, -70);
  sprintf(aChar, "Health2:  %d", health[1]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -18.0f, -70);
  sprintf(aChar, "Verydead:  %d", verydeadshow);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -19.0f, -70);
  sprintf(aChar, "Gravity:  %f", gravity);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -20.0f, -70);
  sprintf(aChar, "Jumpstrength:  %f", jumpstrength);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -21.0f, -70);
  sprintf(aChar, "Delaytime:  %f", delaytime[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -22.0f, -70);
  sprintf(aChar, "Player1 score:  %d", deathcount[1]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -23.0f, -70);
  sprintf(aChar, "Player2 score:  %d", deathcount[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -24.0f, -70);
  sprintf(aChar, "yrot:  %f", yrot);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -25.0f, -70);
  sprintf(aChar, "xrot:  %f", xrot);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -26.0f, -70);
  sprintf(aChar, "oldguy0:  %d", oldguy[0]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, -27.0f, -70);
  sprintf(aChar, "oldguy1:  %d", oldguy[1]);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  // display=blendtype;

  glLoadIdentity();
  glTranslatef(-36.0f, -28.0f, -70);
  sprintf(aChar, "display:  %f", display);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glLoadIdentity();
  glTranslatef(-36.0f, 8.0f, -70);
  sprintf(aChar, "z:  %f", z);
  glColor3d(1.0, 1.0, 1.0);
  glRasterPos3d(.1, 0, 0);
  if (showinfo == 1)
    DrawCSringGL(aChar, gFontList);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
}

/********************> HandleKeyDown() <*****/
void restartRound() {
  int x;
  int y;
  for (x = 0; x < maxsprites; x++) {
    sprite[x].type = 0;
  }
  for (x = 0; x < kMaxLightning; x++) {
    Lightning[x].brightness = 0;
  }
  for (x = 0; x < 2; x++) {
    for (y = 0; y < 16; y++) {
      smokingbody[x][y] = 0;
    }
  }
  if (exists[1] == 1) {
    RemovePlayer(1);
  }
  if (exists[0] == 1) {
    RemovePlayer(0);
  }
  if (exists[0] == 0) {
    MovePlayerData(0, oldguy[0]);
  }
  if (exists[1] == 0) {
    MovePlayerData(1, oldguy[1]);
  }
  goneplayers = 0;
  holding[0] = 0;
  holding[1] = 0;
  exists[0] = 1;
  exists[1] = 1;
  ammo[0] = 30;
  ammo[2] = 30;
  ammo[1] = 30;
  numplayers = 2;
  /*item[0].type=1;
  item[0].x=0;
  item[0].y=0;
  item[0].z=0;
  item[0].vely=.01;*/
  guyvelx[0] = 0;
  guyvely[0] = 0;
  randomint = RangedRandom(0, 15) + 7;
  guyx[0] = startplacex[randomint] * 10 - 590;
  guyy[0] = (startplacey[randomint] - 39) * -20 + .5;
  activity[0] = 1;
  dead[0] = 0;
  anim[0] = 1;
  frame[0] = 0;
  targetanim[0] = 1;
  targetframe[0] = 0;
  time[0] = 0;
  ammo[0] = 30;
  usingjetpack[0] = 0;
  health[0] = 100;
  for (x = 0; x < 50; x++) {
    MakeSprite(guyx[0], RangedRandom(guyy[0] + 5, guyy[0] + 20), 0, 200, spawnstars, RangedRandom(1, 360), 10, RangedRandom(2, 5), 0, 0, 0);
  }
  guyvelx[1] = 0;
  guyvely[1] = 0;
  randomint2 = RangedRandom(0, 14) + 7;
  if (randomint2 >= randomint) {
    randomint2++;
  }
  guyx[1] = startplacex[randomint2] * 10 - 590;
  guyy[1] = (startplacey[randomint2] - 39) * -20 + .5;
  activity[1] = 1;
  dead[1] = 0;
  anim[1] = 1;
  frame[1] = 0;
  targetanim[1] = 1;
  targetframe[1] = 0;
  time[1] = 0;
  ammo[1] = 30;
  usingjetpack[1] = 0;
  for (x = 0; x < 50; x++) {
    MakeSprite(guyx[1], RangedRandom(guyy[1] + 5, guyy[1] + 20), 0, 200, spawnstars, RangedRandom(1, 360), 10, RangedRandom(2, 5), 0, 0, 0);
  }
  health[1] = 100;
}

void WallBounds(int toggle) {
  int x;
  if (toggle == 1) {
    for (x = 4; x < 95; x++) {
      Map[x][64] = 1;
    }
    for (x = 0; x < 100; x++) {
      Walls[3][x] = 1;
    }
    for (x = 0; x < 100; x++) {
      Walls[94][x] = 1;
    }
    cube = 1;
  }
  if (toggle == 0) {
    for (x = 0; x < 100; x++) {
      Map[x][64] = 0;
    }
    for (x = 0; x < 100; x++) {
      Walls[3][x] = 0;
    }
    for (x = 0; x < 100; x++) {
      Walls[94][x] = 0;
    }
    cube = 0;
  }
}

void HandleKeyDown(char theChar) {
  int x;
  int y;
  // The key presses handled here don't need register quite as quickly, so we'll let the
  // MacOS event handler get them for use, they do need to be recognized as only hit once
  // because they toggle variables (in this case), key presses gotten with IsKeyDown()
  // will be registered every time it is called, therefor they register faster, but may register
  // as multiple hits (because of the frequency of calls to it) which is very annoying when
  // only trying to toggle variables.
  if (mapeditor) {
    switch (theChar) {
    case '8':
      if (selectedy > 0) {
        selectedy--;
      }
      break;
    case '5':
      if (selectedy < 99) {
        selectedy++;
      }
      break;
    case '4':
      if (selectedx > 0) {
        selectedx--;
      }
      break;
    case '6':
      if (selectedx < 99) {
        selectedx++;
      }
      break;
    case '1':
      if (Map[selectedx][selectedy] != 1) {
        Map[selectedx][selectedy] = 1;
        for (x = 0; x < 20; x++) {
          MakeSprite(selectedx * 10 - 590, RangedRandom((selectedy - 39) * -20, (selectedy - 39) * -20 + .5 + 5), 0, 200, spawnstars, RangedRandom(1, 360), 10, RangedRandom(2, 3), 0, -.1, 0);
        }
      }
      break;
    case '2':
      if (Map[selectedx][selectedy] != 2) {
        Map[selectedx][selectedy] = 2;
        for (x = 0; x < 50; x++) {
          MakeSprite(selectedx * 10 - 590, RangedRandom((selectedy - 39) * -20 + 10, (selectedy - 39) * -20 + .5 + 30), 0, 200, spawnstars, RangedRandom(1, 360), 10, RangedRandom(2, 3), 0, -.1, 0);
        }
      }
      break;
    case '3':
      if (Map[selectedx][selectedy] != 3) {
        Map[selectedx][selectedy] = 3;
        for (x = 0; x < 50; x++) {
          MakeSprite(selectedx * 10 - 590, RangedRandom((selectedy - 39) * -20 + 10, (selectedy - 39) * -20 + .5 + 30), 0, 200, spawnstars, RangedRandom(1, 360), 10, RangedRandom(2, 3), 0, -.1, 0);
        }
      }
      break;
    case '7':
      playerstartnum++;
      if (playerstartnum >= 16) {
        playerstartnum = 0;
      }
      break;
    case '9':
      startplacex[playerstartnum] = selectedx;
      startplacey[playerstartnum] = selectedy;
      for (x = 0; x < 50; x++) {
        MakeSprite(selectedx * 10 - 590, RangedRandom((selectedy - 39) * -20 + 10, (selectedy - 39) * -20 + .5 + 30), 0, 200, spawnstars, RangedRandom(1, 360), 10, RangedRandom(2, 3), 0, -.1, 0);
      }
      break;
    case '+':
      if (Walls[selectedx][selectedy] != 1) {
        Walls[selectedx][selectedy] = 1;
        for (x = 0; x < 50; x++) {
          MakeSprite(selectedx * 10 - 590, RangedRandom((selectedy - 39) * -20 + 10, (selectedy - 39) * -20 + .5 + 30), 0, 200, spawnstars, RangedRandom(1, 360), 10, RangedRandom(2, 3), 0, -.1, 0);
        }
      }
      break;
    case '0':
      if (Map[selectedx][selectedy] == 2 || Map[selectedx][selectedy] == 3 || Walls[selectedx][selectedy] != 0) {
        for (x = 0; x < 50; x++) {
          MakeSprite(selectedx * 10 - 590, RangedRandom((selectedy - 39) * -20 + 10, (selectedy - 39) * -20 + .5 + 30), 0, 200, deletestars, RangedRandom(1, 360), 10, RangedRandom(2, 3), 0, -.1, 0);
        }
      }
      if (Map[selectedx][selectedy] == 1) {
        for (x = 0; x < 20; x++) {
          MakeSprite(selectedx * 10 - 590, RangedRandom((selectedy - 39) * -20, (selectedy - 39) * -20 + .5 + 5), 0, 200, deletestars, RangedRandom(1, 360), 10, RangedRandom(2, 3), 0, -.1, 0);
        }
      }
      Map[selectedx][selectedy] = 0;
      Walls[selectedx][selectedy] = 0;
      break;
    }
  }

  if (mapeditor == 0) {
    switch (theChar) {
    case '1':
      /*if (invisible==0){invisible=2;}
      if (invisible==1){invisible=0;}
      if (invisible==2){invisible=1;}*/
      if (dead[1] == 0) {
        for (x = 0; x < 50; x++) {
          MakeSprite(guyx[1], RangedRandom(guyy[1] + 5, guyy[1] + 20), 0, 200, invisiblestars2, RangedRandom(1, 360), 10, RangedRandom(2, 5), 0, 0, 0);
        }
        cloaktime[1] = 0;
      }
      break;
    }
  }

  // display=theChar;

  switch (theChar) {
  case 'S':
    showinfo++;
    if (showinfo >= 4) {
      showinfo = 0;
    }
    break;
  case 'I':
    health[0] = 10000;
    health[1] = 10000;
    break;
  case 'o':
    AIOffensive = 1 - AIOffensive;
    break;
  case 'O':
    autorespawn = 1 - autorespawn;
    break;
  case 'A':
    constantswordtrail = 1 - constantswordtrail;
    break;
  case 9:
    if (firstperson == 1) {
      firstperson = 2;
    }
    if (firstperson == 0) {
      firstperson = 1;
      ReSizeGLScene(screenwidth, screenheight, 90);
    }
    if (firstperson == 2) {
      firstperson = 0;
      ReSizeGLScene(screenwidth, screenheight, 45);
      yrot = 0;
    }
    break;
  case '-':
    if (changablejump == 1) {
      jumpstrength++;
    }
    break;
  case '*':
    if (changablejump == 1) {
      jumpstrength--;
    }
    break;
  case '=':
    if (changablejump == 1) {
      gravity -= .005;
    }
    break;
  case '/':
    if (changablejump == 1) {
      gravity += .005;
    }
    break;
  case 'L':
    if (lighting == 1) {
      lighting = 2;
    }
    if (lighting == 0) {
      lighting = 1;
    }
    if (lighting == 2) {
      lighting = 0;
    }
    if (lighting == 1) {
      glEnable(GL_LIGHT1);
    }
    if (lighting == 0) {
      glDisable(GL_LIGHT1);
    }
    break;
  case 'c':
    if (changablejump == 1) {
      changablejump = 2;
    }
    if (changablejump == 0) {
      changablejump = 1;
    }
    if (changablejump == 2) {
      changablejump = 0;
    }
    break;
  case 'C':
    computercontrolled[1] = 1 - computercontrolled[1];
    break;
  case 'D':
    computercontrolled[0] = 1 - computercontrolled[0];
    break;
  case 'z':
    restartRound();
    break;
  case 'Z':
    // for(x=0;x<numplayers;x++){
    itemnum[0]++;
    if (itemnum[0] == 4 && itemtype[0] == 0) {
      itemnum[0] = 2;
      itemtype[0] = 1;
    }
    if (itemnum[0] == 4 && itemtype[0] == 1) {
      itemtype[0] = 0;
    }
    if (itemnum[0] == 7 && itemtype[0] == 0) {
      itemtype[0] = 1;
      itemnum[0] = 6;
    }
    if (itemnum[0] == 7 && itemtype[0] == 1) {
      itemtype[0] = 0;
    }
    if (itemnum[0] > 7) {
      itemnum[0] = 0;
    }
    //}
    break;
  case 'V':
    // for(x=0;x<numplayers;x++){
    itemnum[1]++;
    if (itemnum[1] == 4 && itemtype[1] == 0) {
      itemnum[1] = 2;
      itemtype[1] = 1;
    }
    if (itemnum[1] == 4 && itemtype[1] == 1) {
      itemtype[1] = 0;
    }
    if (itemnum[1] == 7 && itemtype[1] == 0) {
      itemtype[1] = 1;
      itemnum[1] = 6;
    }
    if (itemnum[1] == 7 && itemtype[1] == 1) {
      itemtype[1] = 0;
    }
    if (itemnum[1] > 7) {
      itemnum[1] = 0;
    }
    //}
    break;

  /*case 'c':
          if (scalenormals==0){scalenormals=2;}
          if (scalenormals==1){scalenormals=0;}
          if (scalenormals==2){scalenormals=1;}
          break;*/
  case 'F':
    if (fogtoggle == 0) {
      fogtoggle = 2;
    }
    if (fogtoggle == 1) {
      fogtoggle = 0;
      glDisable(GL_FOG);
    }
    if (fogtoggle == 2) {
      fogtoggle = 1;
      glEnable(GL_FOG);
    }
    break;
  case 'x':
    /*if (invisible==0){invisible=2;}
    if (invisible==1){invisible=0;}
    if (invisible==2){invisible=1;}*/
    if (dead[0] == 0) {
      for (x = 0; x < 50; x++) {
        MakeSprite(guyx[0], RangedRandom(guyy[0] + 5, guyy[0] + 20), 0, 200, invisiblestars, RangedRandom(1, 360), 10, RangedRandom(2, 5), 0, 0, 0);
      }
      cloaktime[0] = 0;
    }
    break;
  case 'u':
    if (jetpack[0] == 0) {
      jetpack[0] = 2;
    }
    if (jetpack[0] == 1) {
      jetpack[0] = 0;
      usingjetpack[0] = 0;
      if (activity[0] == jetidle || activity[0] == jetleft || activity[0] == jetup || activity[0] == jetright) {
        activity[0] = falling;
      }
    }
    if (jetpack[0] == 2) {
      jetpack[0] = 1;
    }
    if (jetpack[1] == 0) {
      jetpack[1] = 2;
    }
    if (jetpack[1] == 1) {
      jetpack[1] = 0;
      usingjetpack[1] = 0;
      if (activity[1] == jetidle || activity[1] == jetleft || activity[1] == jetup || activity[1] == jetright) {
        activity[1] = falling;
      }
    }
    if (jetpack[1] == 2) {
      jetpack[1] = 1;
    }
    break;
  case 'U':
    unlimitedammo = 1 - unlimitedammo;
    break;
  case 'y':
    usingjetpack[0] = 0;
    if (activity[0] == jetidle || activity[0] == jetleft || activity[0] == jetup || activity[0] == jetright) {
      activity[0] = falling;
    }
    break;
  case '3':
    usingjetpack[1] = 0;
    if (activity[1] == jetidle || activity[1] == jetleft || activity[1] == jetup || activity[1] == jetright) {
      activity[1] = falling;
    }
    break;
  case 'X':
    if (trail == 0) {
      trail = 2;
    }
    if (trail == 1) {
      trail = 0;
    }
    if (trail == 2) {
      trail = 1;
    }
    break;
  case 'v':
    if (guytrack == 0) {
      guytrack = 2;
    }
    if (guytrack == 1) {
      guytrack = 0;
    }
    if (guytrack == 2) {
      guytrack = 1;
    }
    break;
  case 'b':
    if (slowdown == 0) {
      slowdown = 2;
    }
    if (slowdown == 1) {
      slowdown = 0;
    }
    if (slowdown == 2) {
      slowdown = 1;
    }
    break;
  case 'B':
    if (freezetime == 0) {
      freezetime = 2;
    }
    if (freezetime == 1) {
      freezetime = 0;
    }
    if (freezetime == 2) {
      freezetime = 1;
    }
    break;
  case 'm':
    if (wireframe == 0) {
      wireframe = 2;
    }
    if (wireframe == 1) {
      wireframe = 0;
    }
    if (wireframe == 2) {
      wireframe = 1;
    }
    if (wireframe == 1) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (wireframe == 0) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    break;
  case 'M':
    if (mapeditor == 0) {
      mapeditor = 2;
    }
    if (mapeditor == 1) {
      mapeditor = 0;
    }
    if (mapeditor == 2) {
      mapeditor = 1;
    }
    break;
  case 'n':
    theme++;
    if (theme > 7) {
      theme = 0;
    }
    if (theme == marbletheme) {
      themebasenum = 4;
      themebacknum = 4;
      themeropenum = 11;
      fogColor[0] = 0.5f;
      fogColor[1] = 0.5f;
      fogColor[2] = 0.5f;
      fogColor[3] = 1.0f;
      glFogfv(GL_FOG_COLOR, fogColor);
      WallBounds(1);
    }
    if (theme == trontheme) {
      themebasenum = 12;
      themebacknum = 12;
      themeropenum = 2;
      fogColor[0] = 0.0f;
      fogColor[1] = 0.0f;
      fogColor[2] = 0.0f;
      fogColor[3] = 1.0f;
      glFogfv(GL_FOG_COLOR, fogColor);
      WallBounds(1);
    }
    if (theme == woodtheme) {
      themebasenum = 11;
      themebacknum = 11;
      themeropenum = 11;
      fogColor[0] = 0.5f;
      fogColor[1] = 0.5f;
      fogColor[2] = 0.5f;
      fogColor[3] = 1.0f;
      glFogfv(GL_FOG_COLOR, fogColor);
      WallBounds(1);
    }
    if (theme == metaltheme) {
      themebasenum = 29;
      themebacknum = 32;
      themeropenum = 29;
      fogColor[0] = 0.5f;
      fogColor[1] = 0.5f;
      fogColor[2] = 0.5f;
      fogColor[3] = 1.0f;
      glFogfv(GL_FOG_COLOR, fogColor);
      WallBounds(1);
    }
    if (theme == matrixtheme) {
      themebacknum = 31;
      themebasenum = 30;
      themeropenum = 2;
      fogColor[0] = 0.0f;
      fogColor[1] = 0.0f;
      fogColor[2] = 0.0f;
      fogColor[3] = 1.0f;
      glFogfv(GL_FOG_COLOR, fogColor);
      WallBounds(1);
    }
    if (theme == islandtheme) {
      themebasenum = 4;
      themebacknum = 4;
      themeropenum = 11;
      WallBounds(0);
    }
    if (theme == lavatheme) {
      themebasenum = 29;
      themebacknum = 29;
      themeropenum = 29;
      WallBounds(0);
    }
    if (theme == snowtheme) {
      themebasenum = 29;
      themebacknum = 32;
      themeropenum = 29;
      WallBounds(0);
    }
    break;
  case 'N':
    for (x = 0; x < numplayers; x++) {
      skin[x]++;
      if (skin[x] > 4) {
        skin[x] = 0;
      }
      if (skin[x] == 0) {
        TorsoNum[x] = 4;
        ShoesNum[x] = 9;
        HelmetNum[x] = 6;
        UpperArmNum[x] = 7;
        LowerLegNum[x] = 8;
      }
      if (skin[x] == 1) {
        TorsoNum[x] = 13;
        ShoesNum[x] = 14;
        HelmetNum[x] = 15;
        UpperArmNum[x] = 16;
        LowerLegNum[x] = 17;
      }
      if (skin[x] == 2) {
        TorsoNum[x] = 18;
        ShoesNum[x] = 19;
        HelmetNum[x] = 20;
        UpperArmNum[x] = 21;
        LowerLegNum[x] = 22;
      }
      if (skin[x] == 3) {
        TorsoNum[x] = 23;
        ShoesNum[x] = 24;
        HelmetNum[x] = 25;
        UpperArmNum[x] = 26;
        LowerLegNum[x] = 27;
      }
      if (skin[x] == 4) {
        TorsoNum[x] = 33;
        ShoesNum[x] = 34;
        HelmetNum[x] = 35;
        UpperArmNum[x] = 36;
        LowerLegNum[x] = 37;
      }
    }
    break;
  case ',':
    Save();
    break;
  case '.':
    nodraw = 1;
    LoadMap();
    WallBounds(cube);
    nodraw = 0;
    break;
  case '?':
    for (x = 0; x < 100; x++) {
      for (y = 0; y < 100; y++) {
        Map[x][y] = 0;
      }
    }
    for (x = 20; x < 80; x++) {
      Map[x][64] = 1;
    }
    break;
  }
}

/********************> DoEvent() <*****/

void MakeSprite(float x, float y, float z, float brightness, float type, float spin, float size, float spin2, float velx, float vely, float velz) {
  int a;
  a = unusedsprite + 1;
  while (((sprite[a].type == grenade || a == lasersprite || a == tracersprite) || (sprite[a].type != 0 && type == smokesprite)) && a != unusedsprite) {
    a++;
    if (a >= maxsprites) {
      a = 0;
    }
  }
  unusedsprite = a;
  if (unusedsprite >= maxsprites) {
    unusedsprite = 0;
  }
  sprite[unusedsprite].life = 0;
  sprite[unusedsprite].x = x;
  sprite[unusedsprite].y = y;
  sprite[unusedsprite].z = z;
  sprite[unusedsprite].brightness = brightness;
  sprite[unusedsprite].type = type;
  sprite[unusedsprite].spin = spin;
  sprite[unusedsprite].size = size;
  sprite[unusedsprite].spin2 = spin2;
  sprite[unusedsprite].velx = velx;
  sprite[unusedsprite].vely = vely;
  sprite[unusedsprite].velz = velz;
  sprite[unusedsprite].fading = 0;
  sprite[unusedsprite].stage = 0;
  sprite[unusedsprite].type2 = 0;
  sprite[unusedsprite].delay = 0;
  for (a = 0; a < 16; a++) {
    if (jetglownum[a] == unusedsprite) {
      jetglownum[a] = 0;
    }
  }
}

GLfloat RangedRandom(GLfloat low, GLfloat high) {
  GLfloat range, randomNumber;
  range = absolute(high - low);
  randomNumber = Random();
  return ((randomNumber * range) / 65535) + low + .9;
}

void UpdateSwordTrail(int whichguy, int which) {
  Point3D point2;
  if (swordtrailtoggle[whichguy][0] == 1) {
    point = FindRightGunPoint(whichguy);
    point2 = FindBodyPart(whichguy, kRightHand);
    SwordTrail[whichguy][0].TrailPoint[unusedswordtrail[whichguy]][0] = point.x;
    SwordTrail[whichguy][0].TrailPoint[unusedswordtrail[whichguy]][1] = point.y;
    SwordTrail[whichguy][0].TrailPoint[unusedswordtrail[whichguy]][2] = point.z;
    SwordTrail[whichguy][0].TrailPoint[unusedswordtrail[whichguy]][3] = point2.x;
    SwordTrail[whichguy][0].TrailPoint[unusedswordtrail[whichguy]][4] = point2.y;
    SwordTrail[whichguy][0].TrailPoint[unusedswordtrail[whichguy]][5] = point2.z;
  }
  if (swordtrailtoggle[whichguy][1] == 1) {
    point = FindLeftGunPoint(whichguy);
    point2 = FindBodyPart(whichguy, kLeftHand);
    SwordTrail[whichguy][1].TrailPoint[unusedswordtrail[whichguy]][0] = point.x;
    SwordTrail[whichguy][1].TrailPoint[unusedswordtrail[whichguy]][1] = point.y;
    SwordTrail[whichguy][1].TrailPoint[unusedswordtrail[whichguy]][2] = point.z;
    SwordTrail[whichguy][1].TrailPoint[unusedswordtrail[whichguy]][3] = point2.x;
    SwordTrail[whichguy][1].TrailPoint[unusedswordtrail[whichguy]][4] = point2.y;
    SwordTrail[whichguy][1].TrailPoint[unusedswordtrail[whichguy]][5] = point2.z;
  }
}

void MakeNewSwordTrail(int whichguy) {
  if (swordtrailtoggle[whichguy][0] == 1 || swordtrailtoggle[whichguy][1] == 1) {
    unusedswordtrail[whichguy]++;
    if (unusedswordtrail[whichguy] >= maxswordtrail - 1) {
      UpdateSwordTrail(whichguy, unusedswordtrail[whichguy]);
      unusedswordtrail[whichguy] = 0;
    }
    UpdateSwordTrail(whichguy, unusedswordtrail[whichguy]);
    if (swordtrailtoggle[whichguy][0] == 1) {
      SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][0] = .8;
      SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][1] = .7;
      SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][2] = 1;
      SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][3] = 1;
      if (oldnum[whichguy] == 0 && itemtype[whichguy] == 1) {
        SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][0] = 1;
        SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][1] = .4;
        SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][2] = .4;
      }
      if (oldnum[whichguy] == 1 && itemtype[whichguy] == 1) {
        SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][0] = 0;
        SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][1] = 1;
        SwordTrail[whichguy][0].brightness[unusedswordtrail[whichguy]][2] = .4;
      }
    }
    if (swordtrailtoggle[whichguy][1] == 1) {
      SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][0] = .8;
      SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][1] = .7;
      SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][2] = 1;
      SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][3] = 1;
      if (oldnum[whichguy] == 0 && itemtype[whichguy] == 1) {
        SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][0] = 1;
        SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][1] = .4;
        SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][2] = .4;
      }
      if (oldnum[whichguy] == 1 && itemtype[whichguy] == 1) {
        SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][0] = 0;
        SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][1] = 1;
        SwordTrail[whichguy][1].brightness[unusedswordtrail[whichguy]][2] = .4;
      }
    }
  }
}

void DoStabFX(int whichguy, int b) {
  Point3D point2;
  int d;
  if (itemtype[attacker[b]] == 0) {
    point = FindBodyPart(b, kTorso);
    point2 = FindBodyPart(b, kHead);
    point2.x = (point2.x + point.x) / 2;
    point2.y = (point2.y + point.y) / 2;
    point2.z = (point2.z + point.z) / 2;
    for (d = 0; d < 4; d++) {
      MakeSprite(point2.x, point2.y, point2.z, 255, bloodsparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
    }
  }
  if (itemtype[attacker[b]] == 1) {
    point = FindBodyPart(b, kTorso);
    point2 = FindBodyPart(b, kHead);
    point2.x = (point2.x + point.x) / 2;
    point2.y = (point2.y + point.y) / 2;
    point2.z = (point2.z + point.z) / 2;
    for (d = 0; d < 4; d++) {
      MakeSprite(point2.x, point2.y, point2.z, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
    }
  }
}

void SwitchFrame(int whichguy);
void SwitchFrame(int whichguy) {
  int x, y, a, b, c, d, e, f, g;
  float randomjohn;
  unsigned char theKeyMap[16];
  Point3D point2;
  guymapx[whichguy] = (guyx[whichguy] + 595) / 10;
  guymapy[whichguy] = guyy[whichguy] / -20 - .5 + 40;
  c = ((guyx[whichguy] + 595) / 10) + .2;
  d = ((guyx[whichguy] + 595) / 10) + .9;
  randomjohn = (RangedRandom(1000, -1000) - 1000) / 100;
  time[whichguy] -= 100;
  frame[whichguy] = targetframe[whichguy];
  rotation[whichguy] = targetrotation[whichguy];
  anim[whichguy] = targetanim[whichguy];
  framenum[whichguy] = 1;
  for (x = 0; x < 3; x++) {
    for (y = 0; y < 20; y++) {
      if (leftlowarm[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (lefthigharm[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (rightlowarm[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (righthigharm[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (torsorotation[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (hiprot[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (torsorot[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (leftlowleg[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (lefthighleg[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (rightlowleg[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (righthighleg[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (hippos[2][y][targetanim[whichguy]] != 60) {
        framenum[whichguy] = y + 1;
      }
      if (lefthand[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (leftfoot[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (righthand[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (rightfoot[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (head[x][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (hippos[1][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
      if (hippos[0][y][targetanim[whichguy]] != 0) {
        framenum[whichguy] = y + 1;
      }
    }
  }

  if (invisible[whichguy] == 0) {
    if (frame[whichguy] == 2 && activity[whichguy] == leftroll) {
      playSound(SND_ROLL_ID, 100);
    }
    if (frame[whichguy] == 2 && activity[whichguy] == rightroll) {
      playSound(SND_ROLL_ID, 100);
    }
    if (frame[whichguy] == 2 && activity[whichguy] == runleft) {
      playSound(SND_STEP_ID, 100);
    }
    if (frame[whichguy] == 2 && activity[whichguy] == runright) {
      playSound(SND_STEP_ID, 100);
    }
    if (frame[whichguy] == 0 && activity[whichguy] == runleft) {
      playSound(SND_STEP_ID, 100);
    }
    if (frame[whichguy] == 0 && activity[whichguy] == runright) {
      playSound(SND_STEP_ID, 100);
    }
  }
  targetframe[whichguy] = frame[whichguy] + 1;
  targetanim[whichguy] = anim[whichguy];
  timedirection[whichguy] = 1;

  // if(activity[whichguy]==swordrightthrust||activity[whichguy]==swordleftthrust)
  MakeNewSwordTrail(whichguy);

  if (anim[whichguy] == 40 && frame[whichguy] == 5) {
    frame[whichguy]++;
    targetframe[whichguy]++;
  }
  if (activity[whichguy] == idle1 || activity[whichguy] == idle2) {
    targetframe[whichguy] += RangedRandom(0, 1) * 2;
  }
  if (targetframe[whichguy] >= framenum[whichguy]) {
    targetframe[whichguy] = 0;
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2) {
      activity[whichguy] = RangedRandom(1, 2);
    }
  }
  if (activity[whichguy] == leftroll && frame[whichguy] == 5 && anim[whichguy] == 8) {
    frame[whichguy] = 6;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == leftroll && targetframe[whichguy] == 0 && anim[whichguy] == 8 && isKeyDown(kLeftKey[whichguy]) == 0 && guyvely[whichguy] == 0 && guyvelx[whichguy] == 0) {
    activity[whichguy] = ducking;
    targetframe[whichguy] = 2;
    time[whichguy] = 0;
  }
  if (activity[whichguy] == leftroll && targetframe[whichguy] == 0 && anim[whichguy] == 8 && isKeyDown(kLeftKey[whichguy]) == 1 && isKeyDown(kDownKey[whichguy]) == 0 && guyvely[whichguy] == 0 && guyvelx[whichguy] == 0) {
    activity[whichguy] = runleft;
    targetframe[whichguy] = 1;
    time[whichguy] = 0;
  }
  if (activity[whichguy] == leftroll && targetframe[whichguy] == 0 && anim[whichguy] == 8 && guyvely[whichguy] != 0) {
    activity[whichguy] = falling;
    targetframe[whichguy] = 1;
    time[whichguy] = 0;
    guyvelx[whichguy] = -.1;
  }
  if (activity[whichguy] == rightroll && frame[whichguy] == 5 && anim[whichguy] == 8) {
    frame[whichguy] = 6;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == rightroll && targetframe[whichguy] == 0 && anim[whichguy] == 8 && isKeyDown(kRightKey[whichguy]) == 0 && guyvely[whichguy] == 0 && guyvelx[whichguy] == 0) {
    activity[whichguy] = ducking;
    targetframe[whichguy] = 2;
    time[whichguy] = 0;
  }
  if (activity[whichguy] == rightroll && targetframe[whichguy] == 0 && anim[whichguy] == 8 && isKeyDown(kRightKey[whichguy]) == 1 && isKeyDown(kDownKey[whichguy]) == 0 && guyvely[whichguy] == 0 && guyvelx[whichguy] == 0) {
    activity[whichguy] = runright;
    targetframe[whichguy] = 1;
    time[whichguy] = 0;
  }
  if (activity[whichguy] == rightroll && targetframe[whichguy] == 0 && anim[whichguy] == 8 && guyvely[whichguy] != 0) {
    activity[whichguy] = falling;
    targetframe[whichguy] = 1;
    time[whichguy] = 0;
    guyvelx[whichguy] = .1;
  }
  if (activity[whichguy] == falling && frame[whichguy] == 4) {
    targetframe[whichguy] = 2;
  }
  if (activity[whichguy] == splat && targetframe[whichguy] == 0) {
    time[whichguy] = 0;
    activity[whichguy] = deadfacedown;
  }
  if (activity[whichguy] == impaledright && anim[whichguy] == 19 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfacedown;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == impaledleft && anim[whichguy] == 19 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfacedown;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == duckimpaledright && anim[whichguy] == 39 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfacedown;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == duckimpaledleft && anim[whichguy] == 39 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfacedown;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == jetimpaledright && anim[whichguy] == 37 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfaceup;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == jetimpaledleft && anim[whichguy] == 37 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfaceup;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == brokeneckright && anim[whichguy] == 17 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfacedown;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == brokeneckleft && anim[whichguy] == 17 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfacedown;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == swordthrownleft && anim[whichguy] == 21 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfaceup;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == swordthrownright && anim[whichguy] == 21 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = deadfaceup;
    time[whichguy] = 0;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == landonback && targetframe[whichguy] == 0 && anim[whichguy] == 14) {
    time[whichguy] = 0;
    activity[whichguy] = deadfaceup;
  }

  if (activity[whichguy] == getupfromback && targetframe[whichguy] == 0 && anim[whichguy] == 24 && frame[whichguy] > 0) {
    time[whichguy] = 0;
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == getupfromfront && targetframe[whichguy] == 0 && anim[whichguy] == 25 && frame[whichguy] > 0) {
    time[whichguy] = 0;
    activity[whichguy] = idle1;
  }

  if (activity[whichguy] == painoneright && anim[whichguy] == 22 && frame[whichguy] == 5) {
    guyx[whichguy] += 3;
  }
  if (activity[whichguy] == paintworight && anim[whichguy] == 23 && frame[whichguy] == 5) {
    guyx[whichguy] += 2;
  }
  if (activity[whichguy] == painoneright && anim[whichguy] == 22 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
    targetanim[whichguy] = 1;
    targetframe[whichguy] = 0;
    time[whichguy] = 0;
  }
  if (activity[whichguy] == paintworight && anim[whichguy] == 23 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
    targetanim[whichguy] = 1;
    targetframe[whichguy] = 0;
    time[whichguy] = 0;
  }
  if (activity[whichguy] == painthreeright && anim[whichguy] == 42 && frame[whichguy] == 5) {
    guyx[whichguy] += 4;
  }
  if (activity[whichguy] == painthreeright && anim[whichguy] == 42 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
    targetanim[whichguy] = 1;
    targetframe[whichguy] = 0;
    time[whichguy] = 0;
  }

  if (activity[whichguy] == painoneleft && anim[whichguy] == 22 && frame[whichguy] == 5) {
    guyx[whichguy] -= 3;
  }
  if (activity[whichguy] == paintwoleft && anim[whichguy] == 23 && frame[whichguy] == 5) {
    guyx[whichguy] -= 2;
  }
  if (activity[whichguy] == painoneleft && anim[whichguy] == 22 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
    targetanim[whichguy] = 1;
    targetframe[whichguy] = 0;
    time[whichguy] = 0;
  }
  if (activity[whichguy] == paintwoleft && anim[whichguy] == 23 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
    targetanim[whichguy] = 1;
    targetframe[whichguy] = 0;
    time[whichguy] = 0;
  }
  if (activity[whichguy] == painthreeleft && anim[whichguy] == 42 && frame[whichguy] == 5) {
    guyx[whichguy] -= 3;
  }
  if (activity[whichguy] == painthreeleft && anim[whichguy] == 42 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
    targetanim[whichguy] = 1;
    targetframe[whichguy] = 0;
    time[whichguy] = 0;
  }

  if (activity[whichguy] == breakneckleft && anim[whichguy] == 16 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == breakneckright && anim[whichguy] == 16 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == swordrightthrust && anim[whichguy] == 27 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = swordidleright;
  }
  if (activity[whichguy] == swordleftthrust && anim[whichguy] == 27 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = swordidleleft;
  }
  if (activity[whichguy] == swordrightspin && anim[whichguy] == 40 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = swordidleright;
  }
  if (activity[whichguy] == swordleftspin && anim[whichguy] == 40 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = swordidleleft;
  }
  if (activity[whichguy] == swordrightthrust && anim[whichguy] == 28 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = swordidleright;
  }
  if (activity[whichguy] == swordleftthrust && anim[whichguy] == 28 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = swordidleleft;
  }
  if (activity[whichguy] == swordrightparry && anim[whichguy] == 29 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = swordidleright;
  }
  if (activity[whichguy] == swordleftparry && anim[whichguy] == 29 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = swordidleleft;
  }
  if (activity[whichguy] == impaleleft && anim[whichguy] == 18 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == impaleright && anim[whichguy] == 18 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == duckimpaleleft && anim[whichguy] == 38 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == duckimpaleright && anim[whichguy] == 38 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == jetimpaleleft && anim[whichguy] == 36 && targetframe[whichguy] == 0 && frame[whichguy] > 2) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == jetimpaleright && anim[whichguy] == 36 && targetframe[whichguy] == 0 && frame[whichguy] > 2) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }

  if (activity[whichguy] == fallbackwardsright && anim[whichguy] == 13 && targetframe[whichguy] == 0) {
    activity[whichguy] = landonback;
    if (Walls[guymapx[whichguy]][guymapy[whichguy]] == 0 /*||Map[guymapx[whichguy]][guymapy[whichguy]]==1||Map[guymapx[whichguy]][guymapy[whichguy]]==2*/) {
      guyx[whichguy] += 7 * size[whichguy];
    }
    if (Walls[guymapx[whichguy]][guymapy[whichguy]] == 1 /*&&Map[guymapx[whichguy]][guymapy[whichguy]]!=1&&Map[guymapx[whichguy]][guymapy[whichguy]]!=2*/) {
      guyvelx[whichguy] = -.1;
    }
    targetanim[whichguy] = 14;
    anim[whichguy] = 14;
    targetframe[whichguy] = 0;
    frame[whichguy] = 0;
    time[whichguy] = 100;
    if (Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 3 && activity[whichguy] != climbrope && activity[whichguy] != onrope && activity[whichguy] != downrope) {
      playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
      playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
    }
  }
  if (activity[whichguy] == fallbackwardsleft && anim[whichguy] == 13 && targetframe[whichguy] == 0) {
    activity[whichguy] = landonback;
    if (Walls[guymapx[whichguy] - 1][guymapy[whichguy]] == 0 /*||Map[guymapx[whichguy]][guymapy[whichguy]]==1||Map[guymapx[whichguy]][guymapy[whichguy]]==2*/) {
      guyx[whichguy] -= 7 * size[whichguy];
    }
    if (Walls[guymapx[whichguy] - 1][guymapy[whichguy]] == 1 /*&&Map[guymapx[whichguy]][guymapy[whichguy]]!=1&&Map[guymapx[whichguy]][guymapy[whichguy]]!=2*/) {
      guyvelx[whichguy] = .1;
    }
    targetanim[whichguy] = 14;
    anim[whichguy] = 14;
    targetframe[whichguy] = 0;
    frame[whichguy] = 0;
    time[whichguy] = 100;
    if (Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 3 && activity[whichguy] != climbrope && activity[whichguy] != onrope && activity[whichguy] != downrope) {
      playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
      playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
    }
  }
  if (activity[whichguy] == fallforwardsright && anim[whichguy] == 41 && targetframe[whichguy] == 4) {
    if (Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 3 && activity[whichguy] != climbrope && activity[whichguy] != onrope && activity[whichguy] != downrope) {
      playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
      playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
    }
  }
  if (activity[whichguy] == fallforwardsleft && anim[whichguy] == 41 && targetframe[whichguy] == 4) {
    if (Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 3 && activity[whichguy] != climbrope && activity[whichguy] != onrope && activity[whichguy] != downrope) {
      playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
      playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
    }
  }

  if (activity[whichguy] == fallforwardsright && anim[whichguy] == 41 && targetframe[whichguy] == 0) {
    activity[whichguy] = deadfacedown;
    if (Walls[guymapx[whichguy]][guymapy[whichguy]] == 1 && Map[guymapx[whichguy]][guymapy[whichguy]] != 1 && Map[guymapx[whichguy]][guymapy[whichguy]] != 2) {
      guyvelx[whichguy] = -.1;
    }
  }
  if (activity[whichguy] == fallforwardsleft && anim[whichguy] == 41 && targetframe[whichguy] == 0) {
    activity[whichguy] = deadfacedown;
    if (Walls[guymapx[whichguy] - 1][guymapy[whichguy]] == 1 && Map[guymapx[whichguy]][guymapy[whichguy]] != 1 && Map[guymapx[whichguy]][guymapy[whichguy]] != 2) {
      guyvelx[whichguy] = .1;
    }
  }

  if (activity[whichguy] == grenshootright && anim[whichguy] == 44 && targetframe[whichguy] == 0 && frame[whichguy] > 1) {
    activity[whichguy] = grenidleright;
  }
  if (activity[whichguy] == grenshootleft && anim[whichguy] == 44 && targetframe[whichguy] == 0 && frame[whichguy] > 1) {
    activity[whichguy] = grenidleleft;
  }

  if (activity[whichguy] == swordrightthrust && anim[whichguy] == 27 && targetframe[whichguy] == 3) {
    b = -1;
    for (a = 0; a < numplayers; a++) {
      if (absolute(guyx[whichguy] - guyx[a]) < 15 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
        b = a;
      }
    }
    if (b != -1 && activity[b] != swordleftparry) {
      delaytime[b] = 0;
      delaytime[whichguy] = 0;
      e = (guyx[b] + 595) / 10;
      f = guyy[b] / -20 - .5 + 40;
      health[b] -= 53;
      DoStabFX(whichguy, b);
      if (itemtype[whichguy] == 0) {
        playSound(SND_METALSLIDE_ID, 80);
      }
      if (itemtype[whichguy] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
      if (health[b] > 0) {
        whichhurt = 0;
        if (health[b] > 0) {
          if (activity[b] != painoneright && activity[b] != paintworight && activity[b] != painthreeright) {
            targetframe[b] = 0;
            frame[b] = 0;
          }
          if (activity[b] == painoneright || activity[b] == paintworight || activity[b] == painthreeright) {
            guyx[b] += 2;
            if (frame[b] > 2) {
              targetframe[b] = 2;
              frame[b] = 2;
            }
          }
          if (whichhurt == 1) {
            activity[b] = painoneright;
            anim[b] = 22;
            targetanim[b] = 22;
          }
          if (activity[b] != painoneright) {
            activity[b] = paintworight;
            anim[b] = 23;
            targetanim[b] = 23;
          }
          if (facing[b] == 1) {
            activity[b] = painthreeright;
            anim[b] = 42;
            targetanim[b] = 42;
          }
          if (Walls[e][f]) {
            activity[b] = hitwallright;
            guyx[b] = e * 10 - 590;
            anim[b] = 15;
            targetanim[b] = 15;
          }
          time[b] = 100;
        }
      }
      if (health[b] <= 0) {
        activity[b] = fallbackwardsright;
        targetframe[b] = 0;
        frame[b] = 0;
        anim[b] = 13;
        targetanim[b] = 13;
        if (facing[b] == 1) {
          activity[b] = fallforwardsright;
          anim[b] = 41;
          targetanim[b] = 41;
        }
        if (Walls[e][f]) {
          activity[b] = hitwallright;
          guyx[b] = e * 10 - 590;
          anim[b] = 15;
          targetanim[b] = 15;
        }
        time[b] = 100;
      }
    }
    if (b != -1 && activity[b] == swordleftparry) {
      delaytime[b] = 0;
      delaytime[whichguy] = 0;
      if (itemtype[b] == 0) {
        playSound(SND_METALSLIDE2_ID, 80);
      }
      if (itemtype[b] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
      for (d = 0; d < 4; d++) {
        MakeSprite((guyx[b] + guyx[whichguy]) / 2, guyy[b] + 8, 0, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
      }
      frame[b] = frame[whichguy];
      targetframe[b] = targetframe[whichguy];
      time[b] = time[whichguy] - 5;
      anim[whichguy] = 28;
      targetanim[whichguy] = 28;
    }
  }
  if (activity[whichguy] == swordrightspin && anim[whichguy] == 40 && targetframe[whichguy] == 4) {
    b = -1;
    for (a = 0; a < numplayers; a++) {
      if (absolute(guyx[whichguy] - guyx[a]) < 15 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
        b = a;
      }
    }
    if (b != -1 && activity[b] != swordleftparry) {
      delaytime[b] = 0;
      delaytime[whichguy] = 0;
      e = (guyx[b] + 595) / 10;
      f = guyy[b] / -20 - .5 + 40;
      health[b] -= 53;
      DoStabFX(whichguy, b);
      if (itemtype[whichguy] == 0) {
        playSound(SND_METALSLIDE_ID, 80);
      }
      if (itemtype[whichguy] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
      if (health[b] > 0) {
        whichhurt = 0;
        if (health[b] > 0) {
          if (activity[b] != painoneright && activity[b] != paintworight && activity[b] != painthreeright) {
            targetframe[b] = 0;
            frame[b] = 0;
          }
          if (activity[b] == painoneright || activity[b] == paintworight || activity[b] == painthreeright) {
            guyx[b] += 2;
            if (frame[b] > 2) {
              targetframe[b] = 2;
              frame[b] = 2;
            }
          }
          if (whichhurt == 1) {
            activity[b] = painoneright;
            anim[b] = 22;
            targetanim[b] = 22;
          }
          if (activity[b] != painoneright) {
            activity[b] = paintworight;
            anim[b] = 23;
            targetanim[b] = 23;
          }
          if (facing[b] == 1) {
            activity[b] = painthreeright;
            anim[b] = 42;
            targetanim[b] = 42;
          }
          if (Walls[e][f]) {
            activity[b] = hitwallright;
            guyx[b] = e * 10 - 590;
            anim[b] = 15;
            targetanim[b] = 15;
          }
          time[b] = 100;
        }
      }
      if (health[b] <= 0) {
        activity[b] = fallbackwardsright;
        targetframe[b] = 0;
        frame[b] = 0;
        anim[b] = 13;
        targetanim[b] = 13;
        if (facing[b] == 1) {
          activity[b] = fallforwardsright;
          anim[b] = 41;
          targetanim[b] = 41;
        }
        if (Walls[e][f]) {
          activity[b] = hitwallright;
          guyx[b] = e * 10 - 590;
          anim[b] = 15;
          targetanim[b] = 15;
        }
        time[b] = 100;
      }
    }
    if (b != -1 && activity[b] == swordleftparry) {
      delaytime[b] = 0;
      delaytime[whichguy] = 0;
      if (itemtype[b] == 0) {
        playSound(SND_METALSLIDE2_ID, 80);
      }
      if (itemtype[b] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
      for (d = 0; d < 4; d++) {
        MakeSprite((guyx[b] + guyx[whichguy]) / 2, guyy[b] + 8, 0, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
      }
      frame[b] = frame[whichguy];
      targetframe[b] = targetframe[whichguy];
      time[b] = time[whichguy] - 5;
      anim[whichguy] = 28;
      targetanim[whichguy] = 28;
      activity[whichguy] = swordrightthrust;
    }
  }
  if (activity[whichguy] == swordleftthrust && anim[whichguy] == 27 && targetframe[whichguy] == 3) {
    b = -1;
    for (a = 0; a < numplayers; a++) {
      if (absolute(guyx[whichguy] - guyx[a]) < 15 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] <= guyx[whichguy]) {
        b = a;
      }
    }
    if (b != -1 && activity[b] != swordrightparry) {
      delaytime[b] = 0;
      delaytime[whichguy] = 0;
      e = (guyx[b] + 595) / 10;
      f = guyy[b] / -20 - .5 + 40;
      health[b] -= 53;
      DoStabFX(whichguy, b);
      if (itemtype[whichguy] == 0) {
        playSound(SND_METALSLIDE_ID, 80);
      }
      if (itemtype[whichguy] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
      if (health[b] > 0) {
        whichhurt = 0;
        if (health[b] > 0) {
          if (activity[b] != painoneleft && activity[b] != paintwoleft && activity[b] != painthreeleft) {
            targetframe[b] = 0;
            frame[b] = 0;
          }
          if (activity[b] == painoneleft || activity[b] == paintwoleft || activity[b] == painthreeleft) {
            guyx[b] -= 2;
            if (frame[b] > 2) {
              targetframe[b] = 2;
              frame[b] = 2;
            }
          }
          if (whichhurt == 1) {
            activity[b] = painoneleft;
            anim[b] = 22;
            targetanim[b] = 22;
          }
          if (activity[b] != painoneleft) {
            activity[b] = paintwoleft;
            anim[b] = 23;
            targetanim[b] = 23;
          }
          if (facing[b] == 0) {
            activity[b] = painthreeleft;
            anim[b] = 42;
            targetanim[b] = 42;
          }
          if (Walls[e - 1][f]) {
            activity[b] = hitwallleft;
            guyx[b] = e * 10 - 590;
            anim[b] = 15;
            targetanim[b] = 15;
          }
          time[b] = 100;
        }
      }
      if (health[b] <= 0) {
        activity[b] = fallbackwardsleft;
        targetframe[b] = 0;
        frame[b] = 0;
        anim[b] = 13;
        targetanim[b] = 13;
        if (facing[b] == 0) {
          activity[b] = fallforwardsleft;
          anim[b] = 41;
          targetanim[b] = 41;
        }
        if (Walls[e - 1][f]) {
          activity[b] = hitwallleft;
          guyx[b] = e * 10 - 590;
          anim[b] = 15;
          targetanim[b] = 15;
        }
        time[b] = 100;
      }
    }
    if (b != -1 && activity[b] == swordrightparry) {
      delaytime[b] = 0;
      delaytime[whichguy] = 0;
      if (itemtype[b] == 0) {
        playSound(SND_METALSLIDE2_ID, 80);
      }
      if (itemtype[b] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
      for (d = 0; d < 4; d++) {
        MakeSprite((guyx[b] + guyx[whichguy]) / 2, guyy[b] + 8, 0, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
      }
      frame[b] = frame[whichguy];
      targetframe[b] = targetframe[whichguy];
      time[b] = time[whichguy] - 5;
      anim[whichguy] = 28;
      targetanim[whichguy] = 28;
    }
  }
  if (activity[whichguy] == swordleftspin && anim[whichguy] == 40 && targetframe[whichguy] == 4) {
    b = -1;
    for (a = 0; a < numplayers; a++) {
      if (absolute(guyx[whichguy] - guyx[a]) < 15 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] <= guyx[whichguy]) {
        b = a;
      }
    }
    if (b != -1 && activity[b] != swordrightparry) {
      delaytime[b] = 0;
      delaytime[whichguy] = 0;
      e = (guyx[b] + 595) / 10;
      f = guyy[b] / -20 - .5 + 40;
      health[b] -= 53;
      DoStabFX(whichguy, b);
      if (itemtype[whichguy] == 0) {
        playSound(SND_METALSLIDE_ID, 80);
      }
      if (itemtype[whichguy] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
      if (health[b] > 0) {
        whichhurt = 0;
        if (health[b] > 0) {
          if (activity[b] != painoneleft && activity[b] != paintwoleft && activity[b] != painthreeleft) {
            targetframe[b] = 0;
            frame[b] = 0;
          }
          if (activity[b] == painoneleft || activity[b] == paintwoleft || activity[b] == painthreeleft) {
            guyx[b] -= 2;
            if (frame[b] > 2) {
              targetframe[b] = 2;
              frame[b] = 2;
            }
          }
          if (whichhurt == 1) {
            activity[b] = painoneleft;
            anim[b] = 22;
            targetanim[b] = 22;
          }
          if (activity[b] != painoneleft) {
            activity[b] = paintwoleft;
            anim[b] = 23;
            targetanim[b] = 23;
          }
          if (facing[b] == 0) {
            activity[b] = painthreeleft;
            anim[b] = 42;
            targetanim[b] = 42;
          }
          if (Walls[e - 1][f]) {
            activity[b] = hitwallleft;
            guyx[b] = e * 10 - 590;
            anim[b] = 15;
            targetanim[b] = 15;
          }
          time[b] = 100;
        }
      }
      if (health[b] <= 0) {
        activity[b] = fallbackwardsleft;
        targetframe[b] = 0;
        frame[b] = 0;
        anim[b] = 13;
        targetanim[b] = 13;
        if (facing[b] == 0) {
          activity[b] = fallforwardsleft;
          anim[b] = 41;
          targetanim[b] = 41;
        }
        if (Walls[e - 1][f]) {
          activity[b] = hitwallleft;
          guyx[b] = e * 10 - 590;
          anim[b] = 15;
          targetanim[b] = 15;
        }
        time[b] = 100;
      }
    }
    if (b != -1 && activity[b] == swordrightparry) {
      delaytime[b] = 0;
      delaytime[whichguy] = 0;
      if (itemtype[b] == 0) {
        playSound(SND_METALSLIDE2_ID, 80);
      }
      if (itemtype[b] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
      for (d = 0; d < 4; d++) {
        MakeSprite((guyx[b] + guyx[whichguy]) / 2, guyy[b] + 8, 0, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
      }
      frame[b] = frame[whichguy];
      targetframe[b] = targetframe[whichguy];
      time[b] = time[whichguy] - 5;
      anim[whichguy] = 28;
      targetanim[whichguy] = 28;
      activity[whichguy] = swordleftthrust;
    }
  }
  if (activity[whichguy] == shootleft && targetframe[whichguy] == 3 && Walls[guymapx[whichguy]][guymapy[whichguy]] == 0 && Walls[c][guymapy[whichguy]] == 0) {
    point = FindRightGunPoint(whichguy);
    if (freezetime == 0 && itemnum[whichguy] == 1) {
      playSound(SND_ZAP_ID, 200);
      MakeSprite(point.x + 2, point.y, point.z, 255, lasersprite, 0, 10, 0, 110, 0, 0);
      for (x = 0; x < 13; x++) {
        a = (point.x + x + 585) / 10;
        if (Walls[a][guymapy[whichguy]] == 0) {
          MakeSprite(point.x + (x * .666), point.y, point.z, 255, spawnstars, 0, 10 - (x * .666), 0, 0, 0, 0);
        }
      }
      ammo[whichguy]--;
      litx[1] = point.x;
      lity[1] = point.y;
      lighton[1] = 1;
      lightbrightness[1] = 255;
      if (targetanim[whichguy] == 30) {
        guyvelx[whichguy] -= .2;
      }
    }
    if (freezetime == 0 && itemnum[whichguy] == 4) {
      g = RangedRandom(14, 16) + 1;
      // display=g;
      if (smokingbody[whichguy][kRightGun] < 40) {
        smokingbody[whichguy][kRightGun] += 20;
      }
      playsound(g, 200);
      MakeSprite(point.x + 2, point.y, point.z, 255, tracersprite, 0, 10, 0, 100, randomjohn, 0);
      for (x = 0; x < 9; x++) {
        a = (point.x + x + 585) / 10;
        if (Walls[a][guymapy[whichguy]] == 0) {
          MakeSprite(point.x + (x * .6), point.y + randomjohn / 100 * x, point.z, 255, muzzleflashstars, RangedRandom(0, 360), 10 - x, RangedRandom(0, 360), 0, 0, 0);
        }
      }
      ammo[whichguy]--;
      litx[0] = point.x;
      lity[0] = point.y;
      lighton[0] = 1;
      lightbrightness[0] = 255;
      if (targetanim[whichguy] == 30) {
        guyvelx[whichguy] -= .05;
      }
    }
    if (freezetime == 0 && itemnum[whichguy] == 7) {
      while (lightningdelay[whichguy] <= 0) {
        if (firstshot[whichguy] == 1) {
          firstshot[whichguy] = 0;
          lightningdelay[whichguy] = 0;
        }
        g = (int)RangedRandom(0, 5);
        b = -1;
        for (a = 0; a < numplayers; a++) {
          if (absolute(guyx[whichguy] - guyx[a]) < 30 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) && absolute(guyy[whichguy] - guyy[a]) < 6 + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
            b = a;
          }
        }
        if (b != -1) {

          point = FindRightGunPoint(whichguy);
          if (g == 0) {
            point2 = FindBodyPart(b, kHead);
            smokingbody[b][kHead] = 200;
          }
          if (g == 1) {
            point2 = FindBodyPart(b, kTorso);
            smokingbody[b][kTorso] = 200;
          }
          if (g == 2) {
            point2 = FindBodyPart(b, kRightLowerArm);
            smokingbody[b][kRightLowerArm] = 200;
          }
          if (g != 0 && g != 1 && g != 2) {
            point2 = FindBodyPart(b, kLeftLowerArm);
            smokingbody[b][kLeftLowerArm] = 200;
          }
          if (lightningfxdelay[whichguy] < 5) {
            MakeSprite(point.x, point.y, point.z, 255, lightningflashstars, RangedRandom(0, 360), 10, RangedRandom(0, 360), 0, 0, 0);
            MakeLineLightning(100, 0, point.x, point.y, point.z, point2.x, point2.y, point2.z);
          }

          if (lightningfxdelay[whichguy] < 5) {
            MakeSprite(point2.x, point2.y, point2.z, 255, lightningflashstars, RangedRandom(0, 360), 14, RangedRandom(0, 360), 0, 0, 0);
          }

          f = guyy[b] / -20 - .5 + 40;
          e = (guyx[b] + 595 - .1) / 10;
          usingjetpack[b] = 0;
          if (activity[b] != fallbackwardsright) {
            activity[b] = fallbackwardsright;
            targetframe[b] = 0;
            frame[b] = 0;
            anim[b] = 13;
            targetanim[b] = 13;
            if (Walls[e][f]) {
              activity[b] = hitwallright;
              guyx[b] = e * 10 - 590;
              anim[b] = 15;
              targetanim[b] = 15;
            }
            time[b] = 100;
          }
          if (facing[b] == 1) {
            activity[b] = fallforwardsright;
            anim[b] = 41;
            targetanim[b] = 41;
          }
          if (Walls[e][f]) {
            activity[b] = hitwallright;
            guyx[b] = e * 10 - 590;
            anim[b] = 15;
            targetanim[b] = 15;
          }
          if (Walls[e][f] == 0) {
            guyvelx[b] = .2;
            guyvely[b] = .1;
          }
          ammo[whichguy] -= 2;
          health[b] -= 10;

          ammo[whichguy] -= .1;
          litx[0] = point.x;
          lity[0] = point.y;
          lighton[0] = 1;
          lightbrightness[0] = 255;
          litx[1] = point.x;
          lity[1] = point.y;
          lighton[1] = 1;
          lightbrightness[1] = 255;
        }
        g = RangedRandom(22, 24) + 1;
        if (b != -1) {
          playsound(g, 100);
        }
        if (b == -1) {
          if (lightningfxdelay[whichguy] < 5) {
            MakeSprite(point.x, point.y, point.z, 255, lightningflashstars, RangedRandom(0, 360), 3, RangedRandom(0, 360), 0, 0, 0);
            MakeLineLightning(100, 0, point.x, point.y, point.z, point.x + RangedRandom(0, 1), point.y + RangedRandom(-1, 1), point.z + RangedRandom(-1, 1));
          }
          ammo[whichguy] -= .04;
          lightningfxdelay[whichguy] += 5;
        }
        lightningdelay[whichguy] += 5;
      }
    }
    if (freezetime == 0 && itemnum[whichguy] == 5) {
      g = RangedRandom(18, 20) + 1;
      playsound(g, 200);
      if (smokingbody[whichguy][kRightGun] < 40) {
        smokingbody[whichguy][kRightGun] += 20;
      }
      MakeSprite(point.x + 2, point.y, point.z, 255, tracersprite, 0, 10, 0, 100, randomjohn / 4, 0);
      sprite[unusedsprite].stage = 1;
      for (x = 0; x < 9; x++) {
        a = (point.x + x + 585) / 10;
        if (Walls[a][guymapy[whichguy]] == 0) {
          MakeSprite(point.x + (x * .8), point.y + randomjohn / 100 * x, point.z, 255, muzzleflashstars, RangedRandom(0, 360), 10 - x, RangedRandom(0, 360), 0, 0, 0);
        }
      }
      ammo[whichguy]--;
      litx[0] = point.x;
      lity[0] = point.y;
      lighton[0] = 1;
      lightbrightness[0] = 255;
      if (targetanim[whichguy] == 30) {
        guyvelx[whichguy] -= .05;
      }
    }
  }
  if (activity[whichguy] == shootright && targetframe[whichguy] == 3 && Walls[guymapx[whichguy] - 1][guymapy[whichguy]] == 0 && Walls[d - 2][guymapy[whichguy]] == 0) {
    point = FindRightGunPoint(whichguy);
    if (freezetime == 0 && itemnum[whichguy] == 1) {
      playSound(SND_ZAP_ID, 200);
      MakeSprite(point.x - 2, point.y, point.z, 255, lasersprite, 0, 10, 0, -110, 0, 0);
      for (x = 0; x < 13; x++) {
        a = (point.x - x + 595) / 10;
        if (Walls[a][guymapy[whichguy]] == 0) {
          MakeSprite(point.x - (x * .666), point.y, point.z, 255, spawnstars, 0, 10 - (x * .666), 0, 0, 0, 0);
        }
      }
      ammo[whichguy]--;
      litx[1] = point.x;
      lity[1] = point.y;
      lighton[1] = 1;
      lightbrightness[1] = 255;
      if (targetanim[whichguy] == 30) {
        guyvelx[whichguy] += .2;
      }
    }
    if (freezetime == 0 && itemnum[whichguy] == 4) {
      g = RangedRandom(14, 16) + 1;
      if (smokingbody[whichguy][kRightGun] < 40) {
        smokingbody[whichguy][kRightGun] += 20;
      }
      playsound(g, 200);
      MakeSprite(point.x - 2, point.y, point.z, 255, tracersprite, 0, 10, 0, -100, randomjohn, 0);
      for (x = 0; x < 9; x++) {
        a = (point.x - x + 595) / 10;
        if (Walls[a][guymapy[whichguy]] == 0) {
          MakeSprite(point.x - (x * .6), point.y + randomjohn / 100 * x, point.z, 255, muzzleflashstars, RangedRandom(0, 360), 10 - x, RangedRandom(0, 360), 0, 0, 0);
        }
      }
      ammo[whichguy]--;
      litx[0] = point.x;
      lity[0] = point.y;
      lighton[0] = 1;
      lightbrightness[0] = 255;
      if (targetanim[whichguy] == 30) {
        guyvelx[whichguy] += .05;
      }
    }
    if (freezetime == 0 && itemnum[whichguy] == 7) {
      while (lightningdelay[whichguy] <= 0) {
        if (firstshot[whichguy] == 1) {
          firstshot[whichguy] = 0;
          lightningdelay[whichguy] = 0;
        }
        g = (int)RangedRandom(0, 5);
        b = -1;
        for (a = 0; a < numplayers; a++) {
          if (absolute(guyx[whichguy] - guyx[a]) < 30 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) && absolute(guyy[whichguy] - guyy[a]) < 6 + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && dead[a] == 0 && a != whichguy && guyx[a] < guyx[whichguy]) {
            b = a;
          }
        }
        if (b != -1) {
          if (g == 0) {
            point2 = FindBodyPart(b, kHead);
            smokingbody[b][kHead] = 200;
          }
          if (g == 1) {
            point2 = FindBodyPart(b, kTorso);
            smokingbody[b][kTorso] = 200;
          }
          if (g == 2) {
            point2 = FindBodyPart(b, kRightLowerArm);
            smokingbody[b][kRightLowerArm] = 200;
          }
          if (g != 0 && g != 1 && g != 2) {
            point2 = FindBodyPart(b, kLeftLowerArm);
            smokingbody[b][kLeftLowerArm] = 200;
          }
          if (lightningfxdelay[whichguy] < 5) {
            MakeLineLightning(100, 0, point.x, point.y, point.z, point2.x, point2.y, point2.z);
          }

          if (lightningfxdelay[whichguy] < 5) {
            MakeSprite(point2.x, point2.y, point2.z, 255, lightningflashstars, RangedRandom(0, 360), 14, RangedRandom(0, 360), 0, 0, 0);
          }

          f = guyy[b] / -20 - .5 + 40;
          e = (guyx[b] + 595 - .1) / 10;
          usingjetpack[b] = 0;
          activity[b] = fallbackwardsleft;
          targetframe[b] = 0;
          frame[b] = 0;
          anim[b] = 13;
          targetanim[b] = 13;
          if (Walls[e][f]) {
            activity[b] = hitwallleft;
            guyx[b] = e * 10 - 590;
            anim[b] = 15;
            targetanim[b] = 15;
          }
          time[b] = 100;
          if (facing[b] == 0) {
            activity[b] = fallforwardsleft;
            anim[b] = 41;
            targetanim[b] = 41;
          }
          if (Walls[e - 1][f]) {
            activity[b] = hitwallleft;
            guyx[b] = e * 10 - 590;
            anim[b] = 15;
            targetanim[b] = 15;
          }
          if (Walls[e - 1][f] == 0) {
            guyvelx[b] = -.2;
            guyvely[b] = .1;
          }
          health[b] -= 10;
          ammo[whichguy] -= 2;

          MakeSprite(point.x, point.y, point.z, 255, lightningflashstars, RangedRandom(0, 360), 10, RangedRandom(0, 360), 0, 0, 0);
          ammo[whichguy] -= .1;
          litx[0] = point.x;
          lity[0] = point.y;
          lighton[0] = 1;
          lightbrightness[0] = 255;
          litx[1] = point.x;
          lity[1] = point.y;
          lighton[1] = 1;
          lightbrightness[1] = 255;
        }
        g = RangedRandom(22, 24) + 1;
        if (b != -1) {
          playsound(g, 100);
        }
        if (b == -1) {
          if (lightningfxdelay[whichguy] < 5) {
            MakeSprite(point.x, point.y, point.z, 255, lightningflashstars, RangedRandom(0, 360), 3, RangedRandom(0, 360), 0, 0, 0);
            MakeLineLightning(100, 0, point.x, point.y, point.z, point.x + RangedRandom(0, 1), point.y + RangedRandom(-1, 1), point.z + RangedRandom(-1, 1));
          }
          ammo[whichguy] -= .04;
          lightningfxdelay[whichguy] += 5;
        }
        lightningdelay[whichguy] += 5;
      }
    }
    if (freezetime == 0 && itemnum[whichguy] == 5 && anim[whichguy] != 30) {
      if (smokingbody[whichguy][kRightGun] < 40) {
        smokingbody[whichguy][kRightGun] += 20;
      }
      g = RangedRandom(18, 20) + 1;
      playsound(g, 200);
      MakeSprite(point.x - 2, point.y, point.z, 255, tracersprite, 0, 10, 0, -100, randomjohn / 4, 0);
      sprite[unusedsprite].stage = 1;
      for (x = 0; x < 9; x++) {
        a = (point.x - x + 595) / 10;
        if (Walls[a][guymapy[whichguy]] == 0) {
          MakeSprite(point.x - (x * .8), point.y + randomjohn / 100 * x, point.z, 255, muzzleflashstars, RangedRandom(0, 360), 10 - x, RangedRandom(0, 360), 0, 0, 0);
        }
      }
      ammo[whichguy]--;
      litx[0] = point.x;
      lity[0] = point.y + 1;
      lighton[0] = 1;
      lightbrightness[0] = 255;
      if (targetanim[whichguy] == 30) {
        guyvelx[whichguy] += .05;
      }
    }
    if (freezetime == 0 && itemnum[whichguy] == 5 && anim[whichguy] == 30) {
      if (smokingbody[whichguy][kRightGun] < 40) {
        smokingbody[whichguy][kRightGun] += 20;
      }
      playSound(SND_MACHINEGUN_ID, 200);
      MakeSprite(point.x, point.y, point.z + 1, 255, tracersprite, 0, 10, 0, -100, randomjohn / 4, 0);
      for (x = 0; x < 8; x++) {
        a = (point.x - x + 595) / 10;
        if (Walls[a][guymapy[whichguy]] == 0) {
          MakeSprite(point.x - x, point.y + randomjohn / 100 * x, point.z + 1, 255, muzzleflashstars, RangedRandom(0, 360), 10 - x, RangedRandom(0, 360), 0, 0, 0);
        }
      }
      ammo[whichguy]--;
      litx[0] = point.x;
      lity[0] = point.y + 1;
      lighton[0] = 1;
      lightbrightness[0] = 255;
      if (targetanim[whichguy] == 30) {
        guyvelx[whichguy] += .05;
      }
    }
  }
  if (activity[whichguy] == hitwallright || activity[whichguy] == hitwallleft) {
    if (frame[whichguy] == 9 && Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 3) {
      playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
      playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
    }
  }
  if (activity[whichguy] == hitwallright || activity[whichguy] == hitwallleft) {
    if (frame[whichguy] == 4) {
      playSound(SND_LAND_ID, 30);
    }
  }
  if (activity[whichguy] == brokeneckleft || activity[whichguy] == brokeneckright) {
    if (frame[whichguy] == 8) {
      if (Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 0) {
        playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
        playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
      }
    }
    if (frame[whichguy] == 4) {
      playSound(SND_SNAP_ID, 60);
      health[whichguy] -= 120;
    }
  }
  if (activity[whichguy] == impaledleft || activity[whichguy] == impaledright) {
    if (frame[whichguy] == 8) {
      health[whichguy] -= 120;
      if (Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 0) {
        playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
        playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
      }
    }
    if (frame[whichguy] == 2) {
      DoStabFX(0, whichguy);
    }
  }
  if (activity[whichguy] == impaleleft || activity[whichguy] == impaleright) {
    if (frame[whichguy] == 2 && fake[whichguy] != 1) {
      if (itemtype[whichguy] == 0) {
        playSound(SND_METALSLIDE_ID, 80);
      }
      if (itemtype[whichguy] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
    }
  }
  if (activity[whichguy] == duckimpaledleft || activity[whichguy] == duckimpaledright) {
    if (frame[whichguy] == 6) {
      if (Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 0) {
        playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
        playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
      }
      health[whichguy] -= 120;
    }
    if (frame[whichguy] == 2) {
      DoStabFX(0, whichguy);
    }
  }
  if (activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaleright) {
    if (frame[whichguy] == 2 && fake[whichguy] != 1) {
      if (itemtype[whichguy] == 0) {
        playSound(SND_METALSLIDE_ID, 80);
      }
      if (itemtype[whichguy] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
    }
  }
  if (activity[whichguy] == jetimpaleleft || activity[whichguy] == jetimpaleright) {
    if (frame[whichguy] == 4 && fake[whichguy] != 1) {
      if (itemtype[whichguy] == 0) {
        playSound(SND_METALSLIDE_ID, 80);
      }
      if (itemtype[whichguy] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
    }
  }
  if (activity[whichguy] == jetimpaledleft || activity[whichguy] == jetimpaledright) {
    if (frame[whichguy] == 4) {
      DoStabFX(0, whichguy);
      health[whichguy] -= 120;
    }
  }
  if (activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrowright) {
    if (frame[whichguy] == 3) {
      if (itemtype[whichguy] == 0) {
        playSound(SND_METALSLIDE_ID, 80);
      }
      if (itemtype[whichguy] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
    }
    if (frame[whichguy] == 4) {
      if (itemtype[whichguy] == 0) {
        playSound(SND_METALSLIDE2_ID, 80);
      }
      if (itemtype[whichguy] == 1) {
        playSound(SND_LIGHTSABRE_ID, 80);
      }
    }
  }
  if (activity[whichguy] == swordthrownleft || activity[whichguy] == swordthrownright) {
    if (frame[whichguy] == 11) {
      playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
      playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
      health[whichguy] -= 120;
      /*if(activity[whichguy]==swordthrownleft){if(Map[guymapx[whichguy]-2][guymapy[whichguy]]!=0&&Map[guymapx[whichguy]-1][guymapy[whichguy]]!=0&&activity[whichguy]==swordthrownright&&Map[guymapx[whichguy]+1][guymapy[whichguy]]!=0){playSound(SND_BREAK_ID,-guyvely[whichguy]*50+50); playSound(SND_BREAK2_ID,-guyvely[whichguy]*50+50);}}
      if(activity[whichguy]==swordthrownright){if(Map[guymapx[whichguy]+2][guymapy[whichguy]]!=0&&Map[guymapx[whichguy]+1][guymapy[whichguy]]!=0&&activity[whichguy]==swordthrownleft&&Map[guymapx[whichguy]-1][guymapy[whichguy]]!=0){playSound(SND_BREAK_ID,-guyvely[whichguy]*50+50); playSound(SND_BREAK2_ID,-guyvely[whichguy]*50+50);}}*/
    }
    if (frame[whichguy] == 3 || frame[whichguy] == 4) {
      DoStabFX(0, whichguy);
    }
  }
  if (activity[whichguy] == impaleleft || activity[whichguy] == impaleright) {
    if (frame[whichguy] == 3 && fake[whichguy] == 1) {
      activity[whichguy] = idle1;
      fake[whichguy] = 0;
    }
  }
  if (activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaleright) {
    if (frame[whichguy] == 3 && fake[whichguy] == 1) {
      activity[whichguy] = idle1;
      fake[whichguy] = 0;
    }
  }
  if (activity[whichguy] == jetimpaleleft || activity[whichguy] == jetimpaleright) {
    if (frame[whichguy] == 3 && fake[whichguy] == 1) {
      activity[whichguy] = jetidle;
      targetanim[whichguy] = 35;
      fake[whichguy] = 0;
    }
  }
  if (activity[whichguy] == breakneckright || activity[whichguy] == breakneckleft) {
    if (frame[whichguy] == 6 && fake[whichguy] == 1) {
      activity[whichguy] = idle1;
      fake[whichguy] = 0;
    }
  }
  if (activity[whichguy] == impaleright || activity[whichguy] == impaleleft ||
      activity[whichguy] == swordrightthrust || activity[whichguy] == swordleftthrust ||
      activity[whichguy] == swordrightspin || activity[whichguy] == swordleftspin || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrowleft ||
      activity[whichguy] == swordrightparry || activity[whichguy] == swordleftparry ||
      activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaleleft ||
      activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaleleft) {
    if (frame[whichguy] == 2 && itemtype[whichguy] == 0) {
      g = RangedRandom(25, 27) + 1;
      playsound(g, 200);
    }
    if (frame[whichguy] == 2 && itemtype[whichguy] == 1) {
      g = RangedRandom(28, 30) + 1;
      playsound(g, 200);
    }
    if (frame[whichguy] == 7 && itemtype[whichguy] == 0 && (activity[whichguy] == swordthrowright || activity[whichguy] == swordthrowleft)) {
      g = RangedRandom(25, 27) + 1;
      playsound(g, 200);
    }
    if (frame[whichguy] == 7 && itemtype[whichguy] == 1 && (activity[whichguy] == swordthrowright || activity[whichguy] == swordthrowleft)) {
      g = RangedRandom(28, 30) + 1;
      playsound(g, 200);
    }
  }
}

void NextFrame(int whichguy);
void NextFrame(int whichguy) {
  int x, y;

  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
  if (time[whichguy] >= 100) {
    SwitchFrame(whichguy);
  }
}

void CheckWallHit(int a, int b, int c, int x);
void CheckWallHit(int a, int b, int c, int x) {
  int d, e, f;
  float g;
  e = a + (sprite[x].velx * multiplier / 1000);
  if (sprite[x].type == water && sprite[x].velx > 0) {
    g = (sprite[x].x + 595) / 10;
    e = g + (sprite[x].velx * multiplier / 1000);
  }
  if (sprite[x].type == water && sprite[x].velx < 0) {
    g = (sprite[x].x + 595) / 10;
    e = g + (sprite[x].velx * multiplier / 1000);
  }

  // e=a+(sprite[x].velx*multiplier/1000);
  if (sprite[x].velx > 0) {
    for (f = a; f <= e; f++) {
      if (Walls[f][b] == 1 && sprite[x].type == lasersprite) {
        sprite[x].type = 0;
        sprite[x].velx = 0;
        sprite[x].vely = 0;
        sprite[x].x = f * 10 - 590 + 2;
        playSound(SND_BOOM_ID, 200);
        for (d = 0; d < 6; d++) {
          MakeSprite(sprite[x].x, sprite[x].y, sprite[x].z, 255, wallsparks, 0, 2, 0, RangedRandom(10, 0) - 10, RangedRandom(10, -10) - 10, RangedRandom(10, -10) - 10);
        }
      }
      if (Walls[f][b] == 1 && sprite[x].type == tracersprite) {
        sprite[x].type = 0;
        sprite[x].velx = 0;
        sprite[x].vely = 0;
        sprite[x].x = f * 10 - 590 + 2;
        playSound(SND_BOOM_ID, 200);
        for (d = 0; d < 3; d++) {
          MakeSprite(sprite[x].x, sprite[x].y, sprite[x].z, 255, wallsparks, 0, 2, 0, RangedRandom(10, 0) - 10, RangedRandom(10, -10) - 10, RangedRandom(10, -10) - 10);
        }
      }
    }
  }
  if (sprite[x].velx < 0) {
    for (f = e; f <= a; f++) {
      if (Walls[f][b] == 1 && sprite[x].type == lasersprite) {
        sprite[x].type = 0;
        sprite[x].velx = 0;
        sprite[x].vely = 0;
        sprite[x].x = f * 10 - 590 + 6;
        playSound(SND_BOOM_ID, 200);
        for (d = 0; d < 6; d++) {
          MakeSprite(sprite[x].x, sprite[x].y, sprite[x].z, 255, wallsparks, 0, 2, 0, RangedRandom(10, 0) - 10, RangedRandom(10, -10) - 10, RangedRandom(10, -10) - 10);
        }
      }
      if (Walls[f][b] == 1 && sprite[x].type == tracersprite) {
        sprite[x].type = 0;
        sprite[x].velx = 0;
        sprite[x].vely = 0;
        sprite[x].x = f * 10 - 590 + 6;
        playSound(SND_BOOM_ID, 200);
        for (d = 0; d < 3; d++) {
          MakeSprite(sprite[x].x, sprite[x].y, sprite[x].z, 255, wallsparks, 0, 2, 0, RangedRandom(10, 0) - 10, RangedRandom(10, -10) - 10, RangedRandom(10, -10) - 10);
        }
      }
    }
  }
}

void CheckBounceWallHit(int a, int b, int c, int x);
void CheckBounceWallHit(int a, int b, int c, int x) {
  int d, e, f;
  float g;
  if (sprite[x].type == water && sprite[x].velx > 0) {
    g = (sprite[x].x + 595) / 10;
    e = g + (sprite[x].velx * multiplier / 1000);
  }
  if (sprite[x].type == water && sprite[x].velx < 0) {
    g = (sprite[x].x + 595) / 10;
    e = g + (sprite[x].velx * multiplier / 1000);
  }
  if (sprite[x].type == grenade && sprite[x].velx > 0) {
    g = (sprite[x].x + 595) / 10;
    e = g + (sprite[x].velx * multiplier / 1000);
  }
  if (sprite[x].type == grenade && sprite[x].velx < 0) {
    g = (sprite[x].x + 595) / 10;
    e = g + (sprite[x].velx * multiplier / 1000);
  }
  if (sprite[x].type == chunk && sprite[x].velx > 0) {
    g = (sprite[x].x + 595) / 10;
    e = g + (sprite[x].velx * multiplier / 1000);
  }
  if (sprite[x].type == chunk && sprite[x].velx < 0) {
    g = (sprite[x].x + 595) / 10;
    e = g + (sprite[x].velx * multiplier / 1000);
  }
  // e=a+(sprite[x].velx*multiplier/1000);
  if (sprite[x].velx > 0) {
    for (f = a; f < e; f++) {
      if (Walls[f][b] == 1 && sprite[x].type == water) {
        sprite[x].velx *= -1;
        sprite[x].x = f * 10 - 590 + 1;
      }
      if (Walls[f][b] == 1 && sprite[x].type == grenade) {
        sprite[x].velx *= -1;
        sprite[x].x = f * 10 - 590 + 1;
        if (sprite[x].stage == 1) {
          sprite[x].stage = 3;
        }
        if (sprite[x].stage == 0 || sprite[x].stage == 2) {
          sprite[x].stage = 1;
        }
        if (sprite[x].stage == 3) {
          sprite[x].stage = 2;
        }
        if (sprite[x].type2 != 0) {
          playSound(SND_BINK_ID, 20 + absolute(sprite[x].velx) * 10);
        }
        if (sprite[x].type2 == 0) {
          Explode(x);
        }
      }
      if (Walls[f][b] == 1 && sprite[x].type == chunk) {
        playSound(SND_BOOM_ID, 10 + sprite[x].velx * 5);
        sprite[x].velx *= -1;
        sprite[x].x = f * 10 - 590 + 1;
        if (sprite[x].stage == 1) {
          sprite[x].stage = 3;
        }
        if (sprite[x].stage == 0 || sprite[x].stage == 2) {
          sprite[x].stage = 1;
        }
        if (sprite[x].stage == 3) {
          sprite[x].stage = 2;
        }
      }
    }
  }
  if (sprite[x].velx < 0) {
    for (f = e; f < a; f++) {
      if (Walls[f][b] == 1 && sprite[x].type == water) {
        sprite[x].velx *= -1;
        sprite[x].x *= -1;
        sprite[x].x = f * 10 - 590 + 6;
      }
      if (Walls[f][b] == 1 && sprite[x].type == grenade) {
        sprite[x].velx *= -1;
        sprite[x].x *= -1;
        sprite[x].x = f * 10 - 590 + 6;
        if (sprite[x].stage == 1) {
          sprite[x].stage = 3;
        }
        if (sprite[x].stage == 0 || sprite[x].stage == 2) {
          sprite[x].stage = 1;
        }
        if (sprite[x].stage == 3) {
          sprite[x].stage = 2;
        }
        if (sprite[x].type2 != 0) {
          playSound(SND_BINK_ID, 20 + absolute(sprite[x].velx) * 10);
        }
        if (sprite[x].type2 == 0) {
          Explode(x);
        }
      }
      if (Walls[f][b] == 1 && sprite[x].type == chunk) {
        playSound(SND_BOOM_ID, 10 + absolute(sprite[x].velx) * 5);
        sprite[x].velx *= -1;
        sprite[x].x *= -1;
        sprite[x].x = f * 10 - 590 + 6;
        if (sprite[x].stage == 1) {
          sprite[x].stage = 3;
        }
        if (sprite[x].stage == 0 || sprite[x].stage == 2) {
          sprite[x].stage = 1;
        }
        if (sprite[x].stage == 3) {
          sprite[x].stage = 2;
        }
      }
    }
  }
}

void Explode(int which) {
  int a, b, e, f, y;
  playSound(SND_BIGBOOM_ID, 200);
  a = (sprite[which].x + 595) / 10;
  b = (sprite[which].oldy) / -20 + 40;
  // if(Map[a][b]==1||Map[a][b]==2||Walls[a][b]==1||Walls[a-1][b]==1){
  sprite[which].type = 0;
  for (e = 0; e < RangedRandom(10, 16); e++) {
    MakeSprite(sprite[which].x + RangedRandom(-100, 100) / 50 + 1, sprite[which].y + RangedRandom(-100, 100) / 50 + 1, sprite[which].z + RangedRandom(-100, 100) / 50 + 1, RangedRandom(140, 160) + 50, exploflame, RangedRandom(0, 360), RangedRandom(4, 8) + 6, 0, 0, -.1, 0);
    sprite[unusedsprite].velx = (-1 - (sprite[unusedsprite].x - sprite[which].x)) * 2;
    sprite[unusedsprite].vely = (-1 - (sprite[unusedsprite].y - sprite[which].y)) * 2;
    sprite[unusedsprite].velz = (-1 - (sprite[unusedsprite].z - sprite[which].z)) * 2;
  }
  if (sprite[which].type2 == 0) {
    for (e = 0; e < RangedRandom(7, 10); e++) {
      MakeSprite(sprite[which].x + RangedRandom(-100, 100) / 20 + 5, sprite[which].y + RangedRandom(-100, 100) / 20 + 5, sprite[which].z + RangedRandom(-100, 100) / 20 + 5, RangedRandom(140, 160) + 50, smokesprite, RangedRandom(0, 360), RangedRandom(15, 20) + 6, 0, RangedRandom(100, 300) / 140, RangedRandom(100, 200) / 100, 0);
      sprite[unusedsprite].type2 = 1;
    }
  }
  if (sprite[which].type2 == 1) {
    for (e = 0; e < RangedRandom(1, 2); e++) {
      MakeSprite(sprite[which].x + RangedRandom(-100, 100) / 20 + 5, sprite[which].y + RangedRandom(-100, 100) / 20 + 5, sprite[which].z + RangedRandom(-100, 100) / 20 + 5, RangedRandom(140, 160) + 50, smokesprite, RangedRandom(0, 360), RangedRandom(15, 20) + 6, 0, RangedRandom(100, 300) / 140, RangedRandom(100, 200) / 100, 0);
      sprite[unusedsprite].type2 = 1;
    }
  }
  if (Map[a][b] == 1 || Map[a][b] == 2) {
    if (b != 64) {
      Map[a][b] = 0;
    }
    for (e = 0; e < RangedRandom(6, 9); e++) {
      MakeSprite(a * 10 - 590 + RangedRandom(-100, 100) / 10 + 5, RangedRandom((b - 39) * -20, (b - 39) * -20 + .5 + 5), sprite[which].z + RangedRandom(-100, 100) / 50 + 1, RangedRandom(140, 160) + 50, chunk, RangedRandom(0, 360), RangedRandom(4, 8) + 6, 0, 0, -.1, 0);
      sprite[unusedsprite].velx = (1 + (sprite[unusedsprite].x - sprite[which].x)) * 4;
      sprite[unusedsprite].vely = (1 + (sprite[unusedsprite].y - sprite[which].y)) * 4;
      if (b == 64) {
        sprite[unusedsprite].vely = absolute(sprite[unusedsprite].vely);
      }
      sprite[unusedsprite].velz = (1 + (sprite[unusedsprite].z - sprite[which].z)) / 4;
    }
  }
  if (Walls[a][b] == 1) {
    if (a != 2 && a != 3 && a != 4 && a != 94) {
      Walls[a][b] = 0;
    }
    for (e = 0; e < RangedRandom(6, 9); e++) {
      MakeSprite(a * 10 - 585, RangedRandom((b - 39) * -20, (b - 39) * -20 + .5 + 20), sprite[which].z + RangedRandom(-100, 100) / 50 + 1, RangedRandom(140, 160) + 50, chunk, RangedRandom(0, 360), RangedRandom(4, 8) + 6, 0, 0, -.1, 0);
      sprite[unusedsprite].velx = (1 + (sprite[unusedsprite].x - sprite[which].x)) * 4;
      if (a == 94) {
        sprite[unusedsprite].velx = 0 - absolute(sprite[unusedsprite].velx);
      }
      if (a == 94) {
        sprite[unusedsprite].x -= 5;
      }
      sprite[unusedsprite].vely = (1 + (sprite[unusedsprite].y - sprite[which].y)) * 4;
      sprite[unusedsprite].velz = (1 + (sprite[unusedsprite].z - sprite[which].z)) / 4;
    }
  }
  if (Walls[a - 1][b] == 1) {
    if (a != 2 && a != 3 && a != 4 && a != 94) {
      Walls[a - 1][b] = 0;
    }
    for (e = 0; e < RangedRandom(6, 9); e++) {
      MakeSprite(a * 10 - 595, RangedRandom((b - 39) * -20, (b - 39) * -20 + .5 + 20), sprite[which].z + RangedRandom(-100, 100) / 50 + 1, RangedRandom(140, 160) + 50, chunk, RangedRandom(0, 360), RangedRandom(4, 8) + 6, 0, 0, -.1, 0);
      sprite[unusedsprite].velx = (1 + (sprite[unusedsprite].x - sprite[which].x)) * 4;
      if (a == 3) {
        sprite[unusedsprite].velx = absolute(sprite[unusedsprite].velx);
      }
      sprite[unusedsprite].vely = (1 + (sprite[unusedsprite].y - sprite[which].y)) * 4;
      sprite[unusedsprite].velz = (1 + (sprite[unusedsprite].z - sprite[which].z)) / 4;
    }
  }

  for (y = 0; y < numplayers; y++) {
    f = guyy[y] / -20 - .5 + 40;
    e = (guyx[y] + 595 - .1) / 10;
    if (absolute(guyx[y] - sprite[which].x) < 40 && absolute(guyy[y] - sprite[which].y) < 40) {
      if (guyx[y] >= sprite[which].x) {
        usingjetpack[y] = 0;
        activity[y] = fallbackwardsright;
        targetframe[y] = 0;
        frame[y] = 0;
        anim[y] = 13;
        targetanim[y] = 13;
        if (Walls[e][f]) {
          activity[y] = hitwallright;
          guyx[y] = e * 10 - 590;
          anim[y] = 15;
          targetanim[y] = 15;
        }
        time[y] = 100;
        if (facing[y] == 1) {
          activity[y] = fallforwardsright;
          anim[y] = 41;
          targetanim[y] = 41;
        }
        if (Walls[e][f]) {
          activity[y] = hitwallright;
          guyx[y] = e * 10 - 590;
          anim[y] = 15;
          targetanim[y] = 15;
        }
      }
      if (guyx[y] < sprite[which].x) {
        usingjetpack[y] = 0;
        activity[y] = fallbackwardsleft;
        targetframe[y] = 0;
        frame[y] = 0;
        anim[y] = 13;
        targetanim[y] = 13;
        if (Walls[e][f]) {
          activity[y] = hitwallleft;
          guyx[y] = e * 10 - 590;
          anim[y] = 15;
          targetanim[y] = 15;
        }
        time[y] = 100;
        if (facing[y] == 0) {
          activity[y] = fallforwardsleft;
          anim[y] = 41;
          targetanim[y] = 41;
        }
        if (Walls[e - 1][f]) {
          activity[y] = hitwallleft;
          guyx[y] = e * 10 - 590;
          anim[y] = 15;
          targetanim[y] = 15;
        }
      }
      if (absolute(guyx[y] - sprite[which].x) < 30 && absolute(guyy[y] - sprite[which].y) < 30) {
        health[y] -= 300 - (absolute(guyx[y] - sprite[which].x) + absolute(guyy[y] - sprite[which].y)) * 5;
        if (health[y] < -400) {
          RemovePlayer(y);
        }
        guyvely[y] += .5 - (absolute(guyx[y] - sprite[which].x) + absolute(guyy[y] - sprite[which].y)) / 120;
        if (guyx[y] >= sprite[which].x) {
          guyvelx[y] = guyvely[y];
        }
        if (guyx[y] < sprite[which].x) {
          guyvelx[y] = -guyvely[y];
        }
      }
    }
  }
  //}
}

void HandleSprites();
void HandleSprites() {
  int x, y, a, b, c, d, e, f, hit, wallintheway;
  for (x = 0; x < 2; x++) {
    abouttobehit[x] = 0;
  }
  for (x = 0; x < maxsprites; x++) {
    sprite[x].delay -= multiplier;
    sprite[x].life += multiplier;
    if (sprite[x].type == grenade && sprite[x].delay < 0 && sprite[x].life < 10000) {
      while (sprite[x].delay < 0) {
        sprite[x].delay += 10;
      }
      MakeSprite(sprite[x].x, sprite[x].y, sprite[x].z, RangedRandom(80, 100) + 20 - sprite[x].life / 5, smokesprite, RangedRandom(0, 360), RangedRandom(0, 4) + 6, 0, 0, -.1, 0);
    }
    if (sprite[x].type == chunk && sprite[x].delay < 0 && sprite[x].life < 100000) {
      while (sprite[x].delay < 0) {
        sprite[x].delay += 10;
      }
      MakeSprite(sprite[x].x, sprite[x].y, sprite[x].z, RangedRandom(80, 100) + 20 - sprite[x].life / 50, smokesprite, RangedRandom(0, 360), RangedRandom(0, 4) + 6, 0, 0, -.1, 0);
    }
    if (sprite[x].type == chunk && (sprite[x].life > 100000 || sprite[x].velx == 0)) {
      sprite[x].type = 0;
    }
    if (sprite[x].type == exploflame) {
      if (absolute(sprite[x].velx) < multiplier / 10) {
        sprite[x].velx = 0;
      }
      if (sprite[x].velx > 0) {
        sprite[x].velx -= multiplier / 10;
      }
      if (sprite[x].velx < 0) {
        sprite[x].velx += multiplier / 10;
      }
      if (absolute(sprite[x].vely) < multiplier / 10) {
        sprite[x].vely = 0;
      }
      if (sprite[x].vely > 0) {
        sprite[x].vely -= multiplier / 10;
      }
      if (sprite[x].vely < 0) {
        sprite[x].vely += multiplier / 10;
      }
      if (absolute(sprite[x].velz) < multiplier / 10) {
        sprite[x].velz = 0;
      }
      if (sprite[x].velz > 0) {
        sprite[x].velz -= multiplier / 10;
      }
      if (sprite[x].velz < 0) {
        sprite[x].velz += multiplier / 10;
      }
    }
    /*a=(sprite[x].x+595)/10;
    b=sprite[x].y/-20+40;
    c=(sprite[x].y+sprite[x].vely*multiplier/100)/-20+40;
    if(sprite[x].type==bouncesprite&&c!=b&&Map[a][b]!=3&&Map[a][b]!=0&&sprite[x].vely<0){
            sprite[x].vely*=-1;
            sprite[x].y=(b-39)*-20+.5;
    }
    if(sprite[x].type==grenade&&c!=b&&Map[a][b]!=3&&Map[a][b]!=0&&sprite[x].vely<0){
            sprite[x].vely*=-1;
            sprite[x].y=(b-39)*-20+.5;
    }*/
    if (sprite[x].type == bouncesprite || sprite[x].type == water || sprite[x].type == grenade || sprite[x].type == chunk) {
      if (sprite[x].type == water) {
        sprite[x].size -= multiplier / 200;
        if (sprite[x].size < .1) {
          sprite[x].type = 0;
        }
      }
      a = (sprite[x].x + 595) / 10;
      b = (sprite[x].oldy - 1.5) / -20 + 40;
      c = (sprite[x].y - 1.5) / -20 + 40;
      d = (sprite[x].y - .5) / -20 + 40;
      if (c >= 99 || a >= 99 || a <= 1) {
        sprite[x].type = 0;
      }
      if (c != b && Map[a][b] != 3 && Map[a][b] != 0 && sprite[x].vely < 0 && c < 99) {
        if (absolute(sprite[x].z) < 5 || d == 64 || c == 64 || b == 64) {
          sprite[x].vely *= -.5;
          sprite[x].y = (b - 39) * -20 + 1.5;
          if (sprite[x].vely <= 2) {
            for (f = 0; f < 10; f++) {
              if (sprite[x].spin < 0) {
                sprite[x].spin += 360;
              }
              if (sprite[x].spin >= 360) {
                sprite[x].spin -= 360;
              }
            }
            sprite[x].vely = 0;
            sprite[x].velx = 0;
            sprite[x].velz = 0;
            sprite[x].y -= .5;
            if (sprite[x].spin < 90 || sprite[x].spin > 270) {
              sprite[x].spin = 0;
            }
            if (sprite[x].spin > 90 && sprite[x].spin < 270) {
              sprite[x].spin = 180;
            }
          }
          if (sprite[x].type == grenade) {
            if (sprite[x].stage == 1) {
              sprite[x].stage = 3;
            }
            if (sprite[x].stage == 0 || sprite[x].stage == 2) {
              sprite[x].stage = 1;
            }
            if (sprite[x].stage == 3) {
              sprite[x].stage = 2;
            }
            if (sprite[x].type2 == 1) {
              playSound(SND_BINK_ID, 20 + sprite[x].vely * 10);
            }
            if (sprite[x].type2 == 0) {
              Explode(x);
            }
          }
          if (sprite[x].type == chunk) {
            playSound(SND_BOOM_ID, 10 + sprite[x].vely * 5);
            if (sprite[x].stage == 1) {
              sprite[x].stage = 3;
            }
            if (sprite[x].stage == 0 || sprite[x].stage == 2) {
              sprite[x].stage = 1;
            }
            if (sprite[x].stage == 3) {
              sprite[x].stage = 2;
            }
          }
          if (sprite[x].type == water) {
            for (e = 0; e < 3; e++) {
              MakeSprite(sprite[x].x, sprite[x].y, sprite[x].z, 255, water, 0, sprite[x].size / 2, 0, (sprite[x].velx + (RangedRandom(400, -400) - 400) / 100) / 2, sprite[x].vely, sprite[x].velz);
            }
            sprite[x].type = 0;
          }
        }
      }
      if (Map[a][d] == 3 || Map[a][d] == 0) {
        if (sprite[x].vely == 0) {
          sprite[x].vely = 0.00001;
        }
      }
    }
    if (sprite[x].type == lasersprite || sprite[x].type == tracersprite || sprite[x].type == water || sprite[x].type == grenade || sprite[x].type == chunk) {
      if (absolute(sprite[x].z) < 5 || a <= 4 || a >= 93) {
        if (sprite[x].type != water) {
          if (sprite[x].type != grenade || sprite[x].stage == 0) {
            sprite[x].spin = atan((0 - sprite[x].vely) / (0 - sprite[x].velx)) / 6.28 * 360 + 180;
            if (sprite[x].type == grenade && sprite[x].velx < 0) {
              sprite[x].spin += 180;
            }
          }
        }
        if (sprite[x].type == grenade && sprite[x].stage == 1 && sprite[x].vely != 0) {
          sprite[x].spin += multiplier;
        }
        if (sprite[x].type == grenade && sprite[x].stage == 2 && sprite[x].vely != 0) {
          sprite[x].spin -= multiplier;
        }
        if (sprite[x].type == chunk && sprite[x].stage == 1 && sprite[x].vely != 0) {
          sprite[x].spin += multiplier;
        }
        if (sprite[x].type == chunk && sprite[x].stage == 2 && sprite[x].vely != 0) {
          sprite[x].spin -= multiplier;
        }
        if (sprite[x].type == chunk && sprite[x].stage == 0 && sprite[x].vely != 0) {
          sprite[x].spin -= multiplier;
        }
        if (sprite[x].velx > 0 && sprite[x].type != chunk && sprite[x].type != grenade) {
          sprite[x].x += 2;
        }
        if (sprite[x].velx < 0 && sprite[x].type != chunk && sprite[x].type != grenade) {
          sprite[x].x -= 2;
        }
        for (y = 0; y < numplayers; y++) {
          abouttobehit[y] = 0;
          e = (guyx[y] + 595) / 10;
          f = guyy[y] / -20 - .5 + 40;
          a = (sprite[x].x + 595) / 10;
          c = (sprite[x].x + 595 + sprite[x].velx * multiplier / 100) / 10;
          if (dead[y] == 0 || health[y] > 0) {
            wallintheway = 0;
            if (Walls[e - 1][f] == 1 && sprite[x].velx > 0 && e > a) {
              wallintheway = 1;
            }
            if (Walls[e][f] == 1 && sprite[x].velx < 0 && e < a) {
              wallintheway = 1;
            }
            e = (guyx[y] + 595 - .1) / 10;
            if (Walls[e - 1][f] == 1 && sprite[x].velx > 0 && e > a) {
              wallintheway = 1;
            }
            if (Walls[e][f] == 1 && sprite[x].velx < 0 && e < a) {
              wallintheway = 1;
            }
            a = (sprite[x].x + 595) / 10;
            b = sprite[x].y / -20 + 40;
            c = (sprite[x].x + 595 - sprite[x].velx) / 10;
            if (sprite[x].type != water) {
              if (activity[y] != ducking && activity[y] != leftroll && activity[y] != rightroll && activity[y] != splat && wallintheway == 0) {
                if (a > c && sprite[x].x + absolute(guyvelx[y]) + (sprite[x].velx * multiplier / 100) > guyx[y] - 5 && sprite[x].x < guyx[y] - 5 && absolute(sprite[x].y - guyy[y] - 7) < 7 * size[y] && activity[y] != fallforwardsleft && activity[y] != fallforwardsright && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != landonback) {
                  if (activity[y] != swordleftparry || frame[y] > 3 || itemtype[y] != 1) {
                    if (sprite[x].type == lasersprite) {
                      health[y] -= 56;
                    }
                    if (sprite[x].type == tracersprite) {
                      health[y] -= 23;
                      if (sprite[x].stage == 1) {
                        health[y] -= 15;
                      }
                    }
                    if (health[y] > 0 && activity[y] != climbrope && activity[y] != onrope && activity[y] != downrope && activity[y] != falling && activity[y] != leftflip && activity[y] != rightflip) {
                      whichhurt = RangedRandom(0, 2);
                      if (health[y] > 0) {
                        if (activity[y] != painoneright && activity[y] != paintworight && activity[y] != painthreeright) {
                          targetframe[y] = 0;
                          frame[y] = 0;
                        }
                        if (activity[y] == painoneright || activity[y] == paintworight || activity[y] == painthreeright) {
                          guyx[y] += 2;
                          if (frame[y] > 2) {
                            targetframe[y] = 2;
                            frame[y] = 2;
                          }
                        }
                        if (whichhurt == 1) {
                          activity[y] = painoneright;
                          anim[y] = 22;
                          targetanim[y] = 22;
                        }
                        if (activity[y] != painoneright) {
                          activity[y] = paintworight;
                          anim[y] = 23;
                          targetanim[y] = 23;
                        }
                        if (facing[y] == 1) {
                          activity[y] = painthreeright;
                          anim[y] = 42;
                          targetanim[y] = 42;
                        }
                        if (Walls[e][f]) {
                          activity[y] = hitwallright;
                          guyx[y] = e * 10 - 590;
                          anim[y] = 15;
                          targetanim[y] = 15;
                        }
                        time[y] = 100;
                      }
                    }
                    if (sprite[x].type == chunk) {
                      sprite[x].velx *= -1;
                      sprite[x].x = guyx[y];
                      health[y] -= 37;
                    }
                    if (health[y] <= 0 || activity[y] == climbrope || usingjetpack[y] == 1 || sprite[x].type == lasersprite || activity[y] == onrope || activity[y] == downrope || activity[y] == falling || activity[y] == leftflip || activity[y] == rightflip || Map[e][f] == 0 || Map[e][f] == 3) {
                      usingjetpack[y] = 0;
                      activity[y] = fallbackwardsright;
                      targetframe[y] = 0;
                      frame[y] = 0;
                      anim[y] = 13;
                      targetanim[y] = 13;
                      if (Walls[e][f]) {
                        activity[y] = hitwallright;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                      time[y] = 100;
                      if (facing[y] == 1) {
                        activity[y] = fallforwardsright;
                        anim[y] = 41;
                        targetanim[y] = 41;
                      }
                      if (Walls[e][f]) {
                        activity[y] = hitwallright;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                    }
                    for (d = 0; d < 4; d++) {
                      if (sprite[x].type == tracersprite) {
                        MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, bloodsparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                      }
                      if (sprite[x].type == lasersprite) {
                        MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                      }
                    }
                    if (sprite[x].type == grenade) {
                      sprite[x].velx *= -1;
                      sprite[x].x = guyx[y] - .1;
                      if (sprite[x].type2 == 0) {
                        Explode(x);
                      }
                    }
                    if (sprite[x].type != grenade && sprite[x].type != chunk) {
                      sprite[x].type = 0;
                      sprite[x].velx = 0;
                      sprite[x].x = guyx[y];
                      sprite[x].vely = 0;
                    }
                    playSound(SND_BOOM_ID, 200);
                  }
                  if (activity[y] == swordleftparry && frame[y] <= 3 && itemtype[y] == 1) {
                    for (d = 0; d < 3; d++) {
                      MakeSprite(guyx[y] - 5, sprite[x].y, sprite[x].z, 255, wallsparks, 0, 2, 0, RangedRandom(20, 0) - 20, RangedRandom(10, -10) - 10, RangedRandom(10, -10) - 10);
                    }
                    if (itemtype[y] == 0) {
                      playSound(SND_METALSLIDE_ID, 80);
                    }
                    if (itemtype[y] == 1) {
                      playSound(SND_LIGHTSABRE_ID, 80);
                    }
                    sprite[x].velx *= -1;
                  }
                }
                if (a < c && sprite[x].x - absolute(guyvelx[y]) + (sprite[x].velx * multiplier / 100) < guyx[y] + 5 && sprite[x].x > guyx[y] + 5 && absolute(sprite[x].y - guyy[y] - 7) < 7 * size[y] && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != fallforwardsleft && activity[y] != fallforwardsright && activity[y] != landonback) {
                  if (activity[y] != swordrightparry || frame[y] > 3 || itemtype[y] != 1) {
                    if (sprite[x].type == lasersprite) {
                      health[y] -= 56;
                    }
                    if (sprite[x].type == tracersprite) {
                      health[y] -= 23;
                      if (sprite[x].stage == 1) {
                        health[y] -= 15;
                      }
                    }
                    if (health[y] > 0 && activity[y] != climbrope && activity[y] != onrope && activity[y] != downrope && activity[y] != falling && activity[y] != leftflip && activity[y] != rightflip) {
                      whichhurt = RangedRandom(0, 2);
                      if (health[y] > 0) {
                        if (activity[y] != painoneleft && activity[y] != paintwoleft && activity[y] != painthreeleft) {
                          targetframe[y] = 0;
                          frame[y] = 0;
                        }
                        if (activity[y] == painoneleft || activity[y] == paintwoleft || activity[y] == painthreeleft) {
                          guyx[y] -= 2;
                          if (frame[y] > 2) {
                            targetframe[y] = 2;
                            frame[y] = 2;
                          }
                        }
                        if (whichhurt == 1) {
                          activity[y] = painoneleft;
                          anim[y] = 22;
                          targetanim[y] = 22;
                        }
                        if (activity[y] != painoneleft) {
                          activity[y] = paintwoleft;
                          anim[y] = 23;
                          targetanim[y] = 23;
                        }
                        if (facing[y] == 0) {
                          activity[y] = painthreeleft;
                          anim[y] = 42;
                          targetanim[y] = 42;
                        }
                        if (Walls[e - 1][f]) {
                          activity[y] = hitwallleft;
                          guyx[y] = e * 10 - 590;
                          anim[y] = 15;
                          targetanim[y] = 15;
                        }
                        time[y] = 100;
                      }
                    }
                    if (sprite[x].type == chunk) {
                      sprite[x].velx *= -1;
                      sprite[x].x = guyx[y] + .1;
                      health[y] -= 37;
                    }
                    if (health[y] <= 0 || activity[y] == climbrope || sprite[x].type == lasersprite || activity[y] == onrope || activity[y] == downrope || activity[y] == falling || activity[y] == leftflip || activity[y] == rightflip || usingjetpack[y] == 1 || Map[e][f] == 0 || Map[e][f] == 3) {
                      usingjetpack[y] = 0;
                      activity[y] = fallbackwardsleft;
                      targetframe[y] = 0;
                      frame[y] = 0;
                      anim[y] = 13;
                      targetanim[y] = 13;
                      if (Walls[e][f]) {
                        activity[y] = hitwallleft;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                      time[y] = 100;
                      if (facing[y] == 0) {
                        activity[y] = fallforwardsleft;
                        anim[y] = 41;
                        targetanim[y] = 41;
                      }
                      if (Walls[e - 1][f]) {
                        activity[y] = hitwallleft;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                    }
                    for (d = 0; d < 4; d++) {
                      if (sprite[x].type == tracersprite) {
                        MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, bloodsparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                      }
                      if (sprite[x].type == lasersprite) {
                        MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                      }
                    }
                    if (sprite[x].type == grenade) {
                      if (sprite[x].type2 == 0) {
                        Explode(x);
                      }
                      sprite[x].velx *= -1;
                      sprite[x].x = guyx[y];
                    }
                    if (sprite[x].type != grenade && sprite[x].type != chunk) {
                      sprite[x].type = 0;
                      sprite[x].velx = 0;
                      sprite[x].x = guyx[y];
                      sprite[x].vely = 0;
                    }
                    playSound(SND_BOOM_ID, 200);
                  }
                  if (activity[y] == swordrightparry && frame[y] <= 3 && itemtype[y] == 1) {
                    for (d = 0; d < 3; d++) {
                      MakeSprite(guyx[y] + 5, sprite[x].y, sprite[x].z, 255, wallsparks, 0, 2, 0, RangedRandom(20, 0) - 20, RangedRandom(10, -10) - 10, RangedRandom(10, -10) - 10);
                    }
                    if (itemtype[y] == 0) {
                      playSound(SND_METALSLIDE_ID, 80);
                    }
                    if (itemtype[y] == 1) {
                      playSound(SND_LIGHTSABRE_ID, 80);
                    }
                    sprite[x].velx *= -1;
                  }
                }
              }
              if (activity[y] == ducking || activity[y] == leftroll || activity[y] == rightroll || activity[y] == splat) {
                if (a > c && sprite[x].x + absolute(guyvelx[y]) + (sprite[x].velx * multiplier / 100) > guyx[y] && sprite[x].x < guyx[y] && absolute(sprite[x].y - guyy[y] - 3) < 3 * size[y] && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != fallforwardsleft && activity[y] != fallforwardsright && activity[y] != landonback) {
                  if (sprite[x].type == lasersprite) {
                    health[y] -= 56;
                  }
                  if (sprite[x].type == tracersprite) {
                    health[y] -= 23;
                    if (sprite[x].stage == 1) {
                      health[y] -= 15;
                    }
                  }
                  if (health[y] > 0 && activity[y] != climbrope && activity[y] != onrope && activity[y] != downrope && activity[y] != falling && activity[y] != leftflip && activity[y] != rightflip) {
                    whichhurt = RangedRandom(0, 2);
                    if (health[y] > 0) {
                      if (activity[y] != painoneright && activity[y] != paintworight && activity[y] != painthreeright) {
                        targetframe[y] = 0;
                        frame[y] = 0;
                      }
                      if (activity[y] == painoneright || activity[y] == paintworight || activity[y] == painthreeright) {
                        guyx[y] += 2;
                        if (frame[y] > 2) {
                          targetframe[y] = 2;
                          frame[y] = 2;
                        }
                      }
                      if (whichhurt == 1) {
                        activity[y] = painoneright;
                        anim[y] = 22;
                        targetanim[y] = 22;
                      }
                      if (activity[y] != painoneright) {
                        activity[y] = paintworight;
                        anim[y] = 23;
                        targetanim[y] = 23;
                      }
                      if (facing[y] == 1) {
                        activity[y] = painthreeright;
                        anim[y] = 42;
                        targetanim[y] = 42;
                      }
                      if (Walls[e][f]) {
                        activity[y] = hitwallright;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                      time[y] = 100;
                    }
                  }
                  if (sprite[x].type == chunk) {
                    sprite[x].velx *= -1;
                    sprite[x].x = guyx[y];
                    health[y] -= 37;
                  }
                  if (health[y] <= 0 || activity[y] == climbrope || usingjetpack[y] == 1 || sprite[x].type == lasersprite || activity[y] == onrope || activity[y] == downrope || activity[y] == falling || activity[y] == leftflip || activity[y] == rightflip || Map[e][f] == 0 || Map[e][f] == 3) {
                    usingjetpack[y] = 0;
                    activity[y] = fallbackwardsright;
                    targetframe[y] = 0;
                    frame[y] = 0;
                    anim[y] = 13;
                    targetanim[y] = 13;
                    if (Walls[e][f]) {
                      activity[y] = hitwallright;
                      guyx[y] = e * 10 - 590;
                      anim[y] = 15;
                      targetanim[y] = 15;
                    }
                    time[y] = 100;
                    if (facing[y] == 0) {
                      activity[y] = fallforwardsleft;
                      anim[y] = 41;
                      targetanim[y] = 41;
                    }
                    if (Walls[e][f]) {
                      activity[y] = hitwallright;
                      guyx[y] = e * 10 - 590;
                      anim[y] = 15;
                      targetanim[y] = 15;
                    }
                  }
                  for (d = 0; d < 4; d++) {
                    if (sprite[x].type == tracersprite) {
                      MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, bloodsparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                    }
                    if (sprite[x].type == lasersprite) {
                      MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                    }
                  }
                  if (sprite[x].type == grenade) {
                    if (sprite[x].type2 == 0) {
                      Explode(x);
                    }
                    sprite[x].velx *= -1;
                    sprite[x].x = guyx[y] - .1;
                  }
                  if (sprite[x].type != grenade && sprite[x].type != chunk) {
                    sprite[x].type = 0;
                    sprite[x].velx = 0;
                    sprite[x].x = guyx[y];
                    sprite[x].vely = 0;
                  }
                  playSound(SND_BOOM_ID, 200);
                }
                if (a < c && sprite[x].x - absolute(guyvelx[y]) + (sprite[x].velx * multiplier / 100) < guyx[y] && sprite[x].x > guyx[y] && absolute(sprite[x].y - guyy[y] - 3) < 3 * size[y] && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != landonback) {
                  if (sprite[x].type == lasersprite) {
                    health[y] -= 56;
                  }
                  if (sprite[x].type == tracersprite) {
                    health[y] -= 23;
                    if (sprite[x].stage == 1) {
                      health[y] -= 15;
                    }
                  }
                  if (health[y] > 0 && activity[y] != climbrope && activity[y] != onrope && activity[y] != downrope && activity[y] != falling && activity[y] != leftflip && activity[y] != rightflip) {
                    whichhurt = RangedRandom(0, 2);
                    if (health[y] > 0) {
                      if (activity[y] != painoneleft && activity[y] != paintwoleft && activity[y] != painthreeleft) {
                        targetframe[y] = 0;
                        frame[y] = 0;
                      }
                      if (activity[y] == painoneleft || activity[y] == paintwoleft || activity[y] == painthreeleft) {
                        guyx[y] -= 2;
                        if (frame[y] > 2) {
                          targetframe[y] = 2;
                          frame[y] = 2;
                        }
                      }
                      if (whichhurt == 1) {
                        activity[y] = painoneleft;
                        anim[y] = 22;
                        targetanim[y] = 22;
                      }
                      if (activity[y] != painoneleft) {
                        activity[y] = paintwoleft;
                        anim[y] = 23;
                        targetanim[y] = 23;
                      }
                      if (facing[y] == 0) {
                        activity[y] = painthreeleft;
                        anim[y] = 42;
                        targetanim[y] = 42;
                      }
                      if (Walls[e - 1][f]) {
                        activity[y] = hitwallleft;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                      time[y] = 100;
                    }
                  }
                  if (sprite[x].type == chunk) {
                    sprite[x].velx *= -1;
                    sprite[x].x = guyx[y];
                    health[y] -= 37;
                  }
                  if (health[y] <= 0 || activity[y] == climbrope || usingjetpack[y] == 1 || sprite[x].type == lasersprite || activity[y] == onrope || activity[y] == downrope || activity[y] == falling || activity[y] == leftflip || activity[y] == rightflip || Map[e][f] == 0 || Map[e][f] == 3) {
                    usingjetpack[y] = 0;
                    activity[y] = fallbackwardsleft;
                    targetframe[y] = 0;
                    frame[y] = 0;
                    anim[y] = 13;
                    targetanim[y] = 13;
                    if (Walls[e][f]) {
                      activity[y] = hitwallleft;
                      guyx[y] = e * 10 - 590;
                      anim[y] = 15;
                      targetanim[y] = 15;
                    }
                    time[y] = 100;
                    if (facing[y] == 0) {
                      activity[y] = fallforwardsleft;
                      anim[y] = 41;
                      targetanim[y] = 41;
                    }
                    if (Walls[e - 1][f]) {
                      activity[y] = hitwallleft;
                      guyx[y] = e * 10 - 590;
                      anim[y] = 15;
                      targetanim[y] = 15;
                    }
                  }
                  for (d = 0; d < 4; d++) {
                    if (sprite[x].type == tracersprite) {
                      MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, bloodsparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                    }
                    if (sprite[x].type == lasersprite) {
                      MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                    }
                  }
                  if (sprite[x].type == grenade) {
                    if (sprite[x].type2 == 0) {
                      Explode(x);
                    }
                    sprite[x].velx *= -1;
                    sprite[x].x = guyx[y] + .1;
                  }
                  if (sprite[x].type != grenade && sprite[x].type != chunk) {
                    sprite[x].type = 0;
                    sprite[x].velx = 0;
                    sprite[x].x = guyx[y];
                    sprite[x].vely = 0;
                  }
                  playSound(SND_BOOM_ID, 200);
                }
              }
            }
          }
        }
        if (sprite[x].velx > 0 && sprite[x].type != chunk && sprite[x].type != grenade) {
          sprite[x].x -= 2;
        }
        if (sprite[x].velx < 0 && sprite[x].type != chunk && sprite[x].type != grenade) {
          sprite[x].x += 2;
        }
        d = 0;
        if (hit == 0) {
          if (sprite[x].velx > 0) {
            sprite[x].x -= 4;
          }
          if (sprite[x].velx < 0) {
            sprite[x].x += 4;
          }
          for (y = 0; y < numplayers; y++) {
            e = (guyx[y] + 595) / 10;
            f = guyy[y] / -20 - .5 + 40;
            a = (sprite[x].x + 595) / 10;
            c = (sprite[x].x + 595 + sprite[x].velx * multiplier / 100) / 10;
            if (dead[y] == 0 || health[y] > 0) {
              wallintheway = 0;
              if (Walls[e - 1][f] == 1 && sprite[x].velx > 0 && e > a) {
                wallintheway = 1;
              }
              if (Walls[e][f] == 1 && sprite[x].velx < 0 && e < a) {
                wallintheway = 1;
              }
              e = (guyx[y] + 595 - .1) / 10;
              if (Walls[e - 1][f] == 1 && sprite[x].velx > 0 && e > a) {
                wallintheway = 1;
              }
              if (Walls[e][f] == 1 && sprite[x].velx < 0 && e < a) {
                wallintheway = 1;
              }
              a = (sprite[x].x + 595) / 10;
              b = sprite[x].y / -20 + 40;
              c = (sprite[x].x + 595 - sprite[x].velx) / 10;
              if (sprite[x].type != water) {
                if (activity[y] != ducking && activity[y] != leftroll && activity[y] != rightroll && activity[y] != splat && wallintheway == 0) {
                  if (a > c && sprite[x].x + guyvelx[y] + (sprite[x].velx * multiplier / 100) > guyx[y] - 5 && sprite[x].x < guyx[y] - 5 && absolute(sprite[x].y - guyy[y] - 7) < 7 * size[y] && activity[y] != fallforwardsleft && activity[y] != fallforwardsright && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != landonback) {
                    hit = 1;
                    if (activity[y] != swordleftparry || frame[y] > 3 || itemtype[y] != 1) {
                      if (sprite[x].type == lasersprite) {
                        health[y] -= 56;
                      }
                      if (sprite[x].type == tracersprite) {
                        health[y] -= 23;
                        if (sprite[x].stage == 1) {
                          health[y] -= 15;
                        }
                      }
                      if (health[y] > 0 && activity[y] != climbrope && activity[y] != onrope && activity[y] != downrope && activity[y] != falling && activity[y] != leftflip && activity[y] != rightflip) {
                        whichhurt = RangedRandom(0, 2);
                        if (health[y] > 0) {
                          if (activity[y] != painoneright && activity[y] != paintworight && activity[y] != painthreeright) {
                            targetframe[y] = 0;
                            frame[y] = 0;
                          }
                          if (activity[y] == painoneright || activity[y] == paintworight || activity[y] == painthreeright) {
                            guyx[y] += 2;
                            if (frame[y] > 2) {
                              targetframe[y] = 2;
                              frame[y] = 2;
                            }
                          }
                          if (whichhurt == 1) {
                            activity[y] = painoneright;
                            anim[y] = 22;
                            targetanim[y] = 22;
                          }
                          if (activity[y] != painoneright) {
                            activity[y] = paintworight;
                            anim[y] = 23;
                            targetanim[y] = 23;
                          }
                          if (facing[y] == 1) {
                            activity[y] = painthreeright;
                            anim[y] = 42;
                            targetanim[y] = 42;
                          }
                          if (Walls[e][f]) {
                            activity[y] = hitwallright;
                            guyx[y] = e * 10 - 590;
                            anim[y] = 15;
                            targetanim[y] = 15;
                          }
                          time[y] = 100;
                        }
                      }
                      if (sprite[x].type == chunk) {
                        sprite[x].velx *= -1;
                        sprite[x].x = guyx[y];
                        health[y] -= 37;
                      }
                      if (health[y] <= 0 || activity[y] == climbrope || usingjetpack[y] == 1 || sprite[x].type == lasersprite || activity[y] == onrope || activity[y] == downrope || activity[y] == falling || activity[y] == leftflip || activity[y] == rightflip || Map[e][f] == 0 || Map[e][f] == 3) {
                        usingjetpack[y] = 0;
                        activity[y] = fallbackwardsright;
                        targetframe[y] = 0;
                        frame[y] = 0;
                        anim[y] = 13;
                        targetanim[y] = 13;
                        if (Walls[e][f]) {
                          activity[y] = hitwallright;
                          guyx[y] = e * 10 - 590;
                          anim[y] = 15;
                          targetanim[y] = 15;
                        }
                        time[y] = 100;
                        if (facing[y] == 1) {
                          activity[y] = fallforwardsright;
                          anim[y] = 41;
                          targetanim[y] = 41;
                        }
                        if (Walls[e][f]) {
                          activity[y] = hitwallright;
                          guyx[y] = e * 10 - 590;
                          anim[y] = 15;
                          targetanim[y] = 15;
                        }
                      }
                      for (d = 0; d < 4; d++) {
                        if (sprite[x].type == tracersprite) {
                          MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, bloodsparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                        }
                        if (sprite[x].type == lasersprite) {
                          MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                        }
                      }
                      if (sprite[x].type == grenade) {
                        sprite[x].velx *= -1;
                        sprite[x].x = guyx[y];
                        if (sprite[x].type2 == 0) {
                          Explode(x);
                        }
                      }
                      if (sprite[x].type != grenade && sprite[x].type != chunk) {
                        sprite[x].type = 0;
                        sprite[x].velx = 0;
                        sprite[x].x = guyx[y];
                        sprite[x].vely = 0;
                      }
                      playSound(SND_BOOM_ID, 200);
                    }
                    if (activity[y] == swordleftparry && frame[y] <= 3 && itemtype[y] == 1) {
                      for (d = 0; d < 3; d++) {
                        MakeSprite(guyx[y] - 5, sprite[x].y, sprite[x].z, 255, wallsparks, 0, 2, 0, RangedRandom(20, 0) - 20, RangedRandom(10, -10) - 10, RangedRandom(10, -10) - 10);
                      }
                      if (itemtype[y] == 0) {
                        playSound(SND_METALSLIDE_ID, 80);
                      }
                      if (itemtype[y] == 1) {
                        playSound(SND_LIGHTSABRE_ID, 80);
                      }
                      sprite[x].velx *= -1;
                    }
                  }
                  if (a < c && sprite[x].x - guyvelx[y] + (sprite[x].velx * multiplier / 100) < guyx[y] + 5 && sprite[x].x > guyx[y] + 5 && absolute(sprite[x].y - guyy[y] - 7) < 7 * size[y] && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != fallforwardsleft && activity[y] != fallforwardsright && activity[y] != landonback) {
                    hit = 1;
                    if (activity[y] != swordrightparry || frame[y] > 3 || itemtype[y] != 1) {
                      if (sprite[x].type == lasersprite) {
                        health[y] -= 56;
                      }
                      if (sprite[x].type == tracersprite) {
                        health[y] -= 23;
                        if (sprite[x].stage == 1) {
                          health[y] -= 15;
                        }
                      }
                      if (health[y] > 0 && activity[y] != climbrope && activity[y] != onrope && activity[y] != downrope && activity[y] != falling && activity[y] != leftflip && activity[y] != rightflip) {
                        whichhurt = RangedRandom(0, 2);
                        if (health[y] > 0) {
                          if (activity[y] != painoneleft && activity[y] != paintwoleft && activity[y] != painthreeleft) {
                            targetframe[y] = 0;
                            frame[y] = 0;
                          }
                          if (activity[y] == painoneleft || activity[y] == paintwoleft || activity[y] == painthreeleft) {
                            guyx[y] -= 2;
                            if (frame[y] > 2) {
                              targetframe[y] = 2;
                              frame[y] = 2;
                            }
                          }
                          if (whichhurt == 1) {
                            activity[y] = painoneleft;
                            anim[y] = 22;
                            targetanim[y] = 22;
                          }
                          if (activity[y] != painoneleft) {
                            activity[y] = paintwoleft;
                            anim[y] = 23;
                            targetanim[y] = 23;
                          }
                          if (facing[y] == 0) {
                            activity[y] = painthreeleft;
                            anim[y] = 42;
                            targetanim[y] = 42;
                          }
                          if (Walls[e - 1][f]) {
                            activity[y] = hitwallleft;
                            guyx[y] = e * 10 - 590;
                            anim[y] = 15;
                            targetanim[y] = 15;
                          }
                          time[y] = 100;
                        }
                      }
                      if (sprite[x].type == chunk) {
                        sprite[x].velx *= -1;
                        sprite[x].x = guyx[y];
                        health[y] -= 37;
                      }
                      if (health[y] <= 0 || activity[y] == climbrope || sprite[x].type == lasersprite || activity[y] == onrope || activity[y] == downrope || activity[y] == falling || activity[y] == leftflip || activity[y] == rightflip || usingjetpack[y] == 1 || Map[e][f] == 0 || Map[e][f] == 3) {
                        usingjetpack[y] = 0;
                        activity[y] = fallbackwardsleft;
                        targetframe[y] = 0;
                        frame[y] = 0;
                        anim[y] = 13;
                        targetanim[y] = 13;
                        if (Walls[e][f]) {
                          activity[y] = hitwallleft;
                          guyx[y] = e * 10 - 590;
                          anim[y] = 15;
                          targetanim[y] = 15;
                        }
                        time[y] = 100;
                        if (facing[y] == 0) {
                          activity[y] = fallforwardsleft;
                          anim[y] = 41;
                          targetanim[y] = 41;
                        }
                        if (Walls[e - 1][f]) {
                          activity[y] = hitwallleft;
                          guyx[y] = e * 10 - 590;
                          anim[y] = 15;
                          targetanim[y] = 15;
                        }
                      }
                      for (d = 0; d < 4; d++) {
                        if (sprite[x].type == tracersprite) {
                          MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, bloodsparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                        }
                        if (sprite[x].type == lasersprite) {
                          MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                        }
                      }
                      if (sprite[x].type == grenade) {
                        if (sprite[x].type2 == 0) {
                          Explode(x);
                        }
                        sprite[x].velx *= -1;
                        sprite[x].x = guyx[y];
                      }
                      if (sprite[x].type != grenade && sprite[x].type != chunk) {
                        sprite[x].type = 0;
                        sprite[x].velx = 0;
                        sprite[x].x = guyx[y];
                        sprite[x].vely = 0;
                      }
                      playSound(SND_BOOM_ID, 200);
                    }
                    if (activity[y] == swordrightparry && frame[y] <= 3 && itemtype[y] == 1) {
                      for (d = 0; d < 3; d++) {
                        MakeSprite(guyx[y] + 5, sprite[x].y, sprite[x].z, 255, wallsparks, 0, 2, 0, RangedRandom(20, 0) - 20, RangedRandom(10, -10) - 10, RangedRandom(10, -10) - 10);
                      }
                      if (itemtype[y] == 0) {
                        playSound(SND_METALSLIDE_ID, 80);
                      }
                      if (itemtype[y] == 1) {
                        playSound(SND_LIGHTSABRE_ID, 80);
                      }
                      sprite[x].velx *= -1;
                    }
                  }
                  if (activity[y] != ducking && activity[y] != leftroll && activity[y] != rightroll && activity[y] != splat && wallintheway == 0) {
                    if (a > c && sprite[x].x + guyvelx[y] + (sprite[x].velx * multiplier * 100) > guyx[y] - 5 && sprite[x].x < guyx[y] - 5 && absolute(sprite[x].y - guyy[y] - 7) < 7 * size[y] && activity[y] != fallforwardsleft && activity[y] != fallforwardsright && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != landonback) {
                      abouttobehit[y] = 1;
                    }
                    if (a < c && sprite[x].x - guyvelx[y] + (sprite[x].velx * multiplier * 100) < guyx[y] + 5 && sprite[x].x > guyx[y] + 5 && absolute(sprite[x].y - guyy[y] - 7) < 7 * size[y] && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != fallforwardsleft && activity[y] != fallforwardsright && activity[y] != landonback) {
                      abouttobehit[y] = 1;
                    }
                  }
                }
                if (activity[y] == ducking || activity[y] == leftroll || activity[y] == rightroll || activity[y] == splat) {
                  hit = 1;
                  if (a > c && sprite[x].x + guyvelx[y] + (sprite[x].velx * multiplier / 100) > guyx[y] && sprite[x].x < guyx[y] && absolute(sprite[x].y - guyy[y] - 3) < 3 * size[y] && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != fallforwardsleft && activity[y] != fallforwardsright && activity[y] != landonback) {
                    if (sprite[x].type == lasersprite) {
                      health[y] -= 56;
                    }
                    if (sprite[x].type == tracersprite) {
                      health[y] -= 23;
                      if (sprite[x].stage == 1) {
                        health[y] -= 15;
                      }
                    }
                    if (health[y] > 0 && activity[y] != climbrope && activity[y] != onrope && activity[y] != downrope && activity[y] != falling && activity[y] != leftflip && activity[y] != rightflip) {
                      whichhurt = RangedRandom(0, 2);
                      if (health[y] > 0) {
                        if (activity[y] != painoneright && activity[y] != paintworight && activity[y] != painthreeright) {
                          targetframe[y] = 0;
                          frame[y] = 0;
                        }
                        if (activity[y] == painoneright || activity[y] == paintworight || activity[y] == painthreeright) {
                          guyx[y] += 2;
                          if (frame[y] > 2) {
                            targetframe[y] = 2;
                            frame[y] = 2;
                          }
                        }
                        if (whichhurt == 1) {
                          activity[y] = painoneright;
                          anim[y] = 22;
                          targetanim[y] = 22;
                        }
                        if (activity[y] != painoneright) {
                          activity[y] = paintworight;
                          anim[y] = 23;
                          targetanim[y] = 23;
                        }
                        if (facing[y] == 1) {
                          activity[y] = painthreeright;
                          anim[y] = 42;
                          targetanim[y] = 42;
                        }
                        if (Walls[e][f]) {
                          activity[y] = hitwallright;
                          guyx[y] = e * 10 - 590;
                          anim[y] = 15;
                          targetanim[y] = 15;
                        }
                        time[y] = 100;
                      }
                    }
                    if (sprite[x].type == chunk) {
                      sprite[x].velx *= -1;
                      sprite[x].x = guyx[y];
                      health[y] -= 37;
                    }
                    if (health[y] <= 0 || activity[y] == climbrope || usingjetpack[y] == 1 || sprite[x].type == lasersprite || activity[y] == onrope || activity[y] == downrope || activity[y] == falling || activity[y] == leftflip || activity[y] == rightflip || Map[e][f] == 0 || Map[e][f] == 3) {
                      usingjetpack[y] = 0;
                      activity[y] = fallbackwardsright;
                      targetframe[y] = 0;
                      frame[y] = 0;
                      anim[y] = 13;
                      targetanim[y] = 13;
                      if (Walls[e][f]) {
                        activity[y] = hitwallright;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                      time[y] = 100;
                      if (facing[y] == 0) {
                        activity[y] = fallforwardsleft;
                        anim[y] = 41;
                        targetanim[y] = 41;
                      }
                      if (Walls[e][f]) {
                        activity[y] = hitwallright;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                    }
                    for (d = 0; d < 4; d++) {
                      if (sprite[x].type == tracersprite) {
                        MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, bloodsparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                      }
                      if (sprite[x].type == lasersprite) {
                        MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                      }
                    }
                    if (sprite[x].type == grenade) {
                      if (sprite[x].type2 == 0) {
                        Explode(x);
                      }
                      sprite[x].velx *= -1;
                      sprite[x].x = guyx[y];
                    }
                    if (sprite[x].type != grenade && sprite[x].type != chunk) {
                      sprite[x].type = 0;
                      sprite[x].velx = 0;
                      sprite[x].x = guyx[y];
                      sprite[x].vely = 0;
                    }
                    playSound(SND_BOOM_ID, 200);
                  }
                  if (a < c && sprite[x].x - guyvelx[y] + (sprite[x].velx * multiplier / 100) < guyx[y] && sprite[x].x > guyx[y] && absolute(sprite[x].y - guyy[y] - 3) < 3 * size[y] && activity[y] != fallbackwardsleft && activity[y] != fallbackwardsright && activity[y] != landonback) {
                    hit = 1;
                    if (sprite[x].type == lasersprite) {
                      health[y] -= 56;
                    }
                    if (sprite[x].type == tracersprite) {
                      health[y] -= 23;
                      if (sprite[x].stage == 1) {
                        health[y] -= 15;
                      }
                    }
                    if (health[y] > 0 && activity[y] != climbrope && activity[y] != onrope && activity[y] != downrope && activity[y] != falling && activity[y] != leftflip && activity[y] != rightflip) {
                      whichhurt = RangedRandom(0, 2);
                      if (health[y] > 0) {
                        if (activity[y] != painoneleft && activity[y] != paintwoleft && activity[y] != painthreeleft) {
                          targetframe[y] = 0;
                          frame[y] = 0;
                        }
                        if (activity[y] == painoneleft || activity[y] == paintwoleft || activity[y] == painthreeleft) {
                          guyx[y] -= 2;
                          if (frame[y] > 2) {
                            targetframe[y] = 2;
                            frame[y] = 2;
                          }
                        }
                        if (whichhurt == 1) {
                          activity[y] = painoneleft;
                          anim[y] = 22;
                          targetanim[y] = 22;
                        }
                        if (activity[y] != painoneleft) {
                          activity[y] = paintwoleft;
                          anim[y] = 23;
                          targetanim[y] = 23;
                        }
                        if (facing[y] == 0) {
                          activity[y] = painthreeleft;
                          anim[y] = 42;
                          targetanim[y] = 42;
                        }
                        if (Walls[e - 1][f]) {
                          activity[y] = hitwallleft;
                          guyx[y] = e * 10 - 590;
                          anim[y] = 15;
                          targetanim[y] = 15;
                        }
                        time[y] = 100;
                      }
                    }
                    if (sprite[x].type == chunk) {
                      sprite[x].velx *= -1;
                      sprite[x].x = guyx[y];
                      health[y] -= 37;
                    }
                    if (health[y] <= 0 || activity[y] == climbrope || usingjetpack[y] == 1 || sprite[x].type == lasersprite || activity[y] == onrope || activity[y] == downrope || activity[y] == falling || activity[y] == leftflip || activity[y] == rightflip || Map[e][f] == 0 || Map[e][f] == 3) {
                      usingjetpack[y] = 0;
                      activity[y] = fallbackwardsleft;
                      targetframe[y] = 0;
                      frame[y] = 0;
                      anim[y] = 13;
                      targetanim[y] = 13;
                      if (Walls[e][f]) {
                        activity[y] = hitwallleft;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                      time[y] = 100;
                      if (facing[y] == 0) {
                        activity[y] = fallforwardsleft;
                        anim[y] = 41;
                        targetanim[y] = 41;
                      }
                      if (Walls[e - 1][f]) {
                        activity[y] = hitwallleft;
                        guyx[y] = e * 10 - 590;
                        anim[y] = 15;
                        targetanim[y] = 15;
                      }
                    }
                    for (d = 0; d < 4; d++) {
                      if (sprite[x].type == tracersprite) {
                        MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, bloodsparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                      }
                      if (sprite[x].type == lasersprite) {
                        MakeSprite(guyx[y], sprite[x].y, sprite[x].z, 255, lasersparks, 0, 2, 0, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5, RangedRandom(5, -5) - 5);
                      }
                    }
                    if (sprite[x].type == grenade) {
                      if (sprite[x].type2 == 0) {
                        Explode(x);
                      }
                      sprite[x].velx *= -1;
                      sprite[x].x = guyx[y];
                    }
                    if (sprite[x].type != grenade && sprite[x].type != chunk) {
                      sprite[x].type = 0;
                      sprite[x].velx = 0;
                      sprite[x].x = guyx[y];
                      sprite[x].vely = 0;
                    }
                    playSound(SND_BOOM_ID, 200);
                  }
                }
              }
            }
          }
          d = 0;
          if (sprite[x].velx > 0) {
            sprite[x].x += 4;
          }
          if (sprite[x].velx < 0) {
            sprite[x].x -= 4;
          }
        }
        if (sprite[x].velx > 0) {
          a = (sprite[x].x + 595) / 10;
          b = sprite[x].y / -20 + 40;
          c = (sprite[x].oldx + 595) / 10;
          if (sprite[x].type == water || sprite[x].type == grenade || sprite[x].type == chunk) {
            a = (sprite[x].x + 595) / 10;
            b = sprite[x].y / -20 + 40;
            c = (sprite[x].oldx + 595) / 10;
            CheckBounceWallHit(a, b, c, x);
          }
          CheckWallHit(a, b, c, x);
          d = 1;
        }
        if (sprite[x].velx < 0 && d == 0) {
          a = (sprite[x].x + 595) / 10;
          b = sprite[x].y / -20 + 40;
          c = (sprite[x].oldx + 595) / 10;
          if (sprite[x].type == water || sprite[x].type == grenade || sprite[x].type == chunk) {
            a = (sprite[x].x + 595) / 10;
            b = sprite[x].y / -20 + 40;
            c = (sprite[x].oldx + 595) / 10;
            CheckBounceWallHit(a, b, c, x);
          }
          CheckWallHit(a, b, c, x);
        }
      }
    }
    if (sprite[x].type == spawnstars) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == spawnstars) {
      sprite[x].brightness -= multiplier / 2;
    }
    if (sprite[x].type == deletestars) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == deletestars) {
      sprite[x].brightness -= multiplier / 2;
    }
    if (sprite[x].type == muzzleflashstars) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == muzzleflashstars && sprite[x].fading >= 6) {
      sprite[x].brightness -= multiplier * 12;
    }
    if (sprite[x].type == muzzleflashstars) {
      sprite[x].fading++;
    }
    if (sprite[x].type == lightningflashstars) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == lightningflashstars && sprite[x].fading >= 6) {
      sprite[x].brightness -= multiplier * 4;
    }
    if (sprite[x].type == lightningflashstars) {
      sprite[x].fading++;
    }
    if (sprite[x].type == bouncesprite) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == water) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == wallsparks) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == wallsparks) {
      sprite[x].brightness -= multiplier * 4;
    }
    if (sprite[x].type == bloodsparks) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == bloodsparks) {
      sprite[x].brightness -= multiplier * 2;
    }
    if (sprite[x].type == lasersparks) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == lasersparks) {
      sprite[x].brightness -= multiplier * 2;
    }
    if (sprite[x].type == invisiblestars) {
      sprite[x].brightness -= multiplier;
    }
    if (sprite[x].type == invisiblestars2) {
      sprite[x].brightness -= multiplier;
    }
    if (sprite[x].type == smokesprite && sprite[x].type2 == 0) {
      sprite[x].spin += multiplier * 3;
    }
    if (sprite[x].type == smokesprite && sprite[x].type2 == 0) {
      sprite[x].brightness -= multiplier;
    }
    if (sprite[x].type == smokesprite && sprite[x].type2 == 1) {
      sprite[x].spin += multiplier / 4;
    }
    if (sprite[x].type == smokesprite && sprite[x].type2 == 1) {
      sprite[x].brightness -= multiplier / 20 * 2;
    }
    if (sprite[x].type == exploflame) {
      sprite[x].spin += multiplier * 2;
    }
    if (sprite[x].type == exploflame) {
      sprite[x].brightness -= multiplier / 2;
    }
    if (sprite[x].type == JetPackGlow) {
      sprite[x].brightness = 200;
    }
    if (sprite[x].brightness <= 0) {
      sprite[x].type = 0;
    }
    if (sprite[x].vely != 0 && sprite[x].type != tracersprite && sprite[x].type != smokesprite && sprite[x].type != exploflame) {
      sprite[x].vely -= 1 * multiplier * gravity;
      if (sprite[x].vely == 0) {
        sprite[x].vely += .00001;
      }
    }
    sprite[x].oldx = sprite[x].x;
    sprite[x].oldy = sprite[x].y;
    sprite[x].oldz = sprite[x].z;
    sprite[x].x += sprite[x].velx * multiplier / 100;
    sprite[x].y += sprite[x].vely * multiplier / 100;
    sprite[x].z += sprite[x].velz * multiplier / 100;
  }
}

Point3D DoRotation(Point3D thePoint, float xang, float yang, float zang) {
  Point3D newpoint;
  Point3D oldpoint;
  xang *= 6.283185;
  xang /= 360;
  yang *= 6.283185;
  yang /= 360;
  zang *= 6.283185;
  zang /= 360;

  oldpoint = thePoint;

  newpoint.z = oldpoint.z * cos(yang) - oldpoint.x * sin(yang);
  newpoint.x = oldpoint.z * sin(yang) + oldpoint.x * cos(yang);
  oldpoint.z = newpoint.z;
  oldpoint.x = newpoint.x;

  newpoint.x = oldpoint.x * cos(zang) - oldpoint.y * sin(zang);
  newpoint.y = oldpoint.y * cos(zang) + oldpoint.x * sin(zang);
  oldpoint.x = newpoint.x;
  oldpoint.y = newpoint.y;

  newpoint.y = oldpoint.y * cos(xang) - oldpoint.z * sin(xang);
  newpoint.z = oldpoint.y * sin(xang) + oldpoint.z * cos(xang);
  oldpoint.z = newpoint.z;
  oldpoint.y = newpoint.y;

  return oldpoint;
}

Point3D FindRightGunPoint(int whichguy) {
  float hipfloat[3][2];
  Point3D GunPoint;
  glPushMatrix();
  glLoadIdentity();
  // glTranslatef(40.0f,30.0f,70.0f);
  glTranslatef(guyx[whichguy], guyy[whichguy], 0.0f);
  if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    targetrotation[whichguy] = 0;
  }
  if (activity[whichguy] == runleft || activity[whichguy] == leftflip || activity[whichguy] == leftroll || activity[whichguy] == fallbackwardsright || activity[whichguy] == hitwallright || activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordidleleft || activity[whichguy] == swordleftthrust || activity[whichguy] == jetleft) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordleftthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleleft || activity[whichguy] == jetimpaledleft) {
    rotation[whichguy] = -90;
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == runright || activity[whichguy] == rightflip || activity[whichguy] == rightroll || activity[whichguy] == fallbackwardsleft || activity[whichguy] == hitwallleft || activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordidleright || activity[whichguy] == swordrightthrust || activity[whichguy] == jetright) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordrightthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaledright) {
    rotation[whichguy] = 90;
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] > 0) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] < 0) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    glTranslatef(0.0f, 0.0f, -1.0f);
    targetrotation[whichguy] = 0;
    rotation[whichguy] = 0;
  }
  glRotatef(((rotation[whichguy] * (100 - time[whichguy])) + (targetrotation[whichguy] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glTranslatef(0, .1, 0);
  glScalef(size[whichguy], size[whichguy], size[whichguy]);
  hipfloat[1][0] = (float)(hippos[1][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[2][0] = (float)(hippos[2][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[0][0] = (float)(hippos[0][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[1][1] = (float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[2][1] = (float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[0][1] = (float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  glPushMatrix();
  glRotatef(((hiprot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((hiprot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((hiprot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(((hipfloat[1][0] * (100 - time[whichguy])) + (hipfloat[1][1] * (time[whichguy]))) / 100, ((hipfloat[2][0] * (100 - time[whichguy])) + (hipfloat[2][1] * (time[whichguy]))) / 100, ((hipfloat[0][0] * (100 - time[whichguy])) + (hipfloat[0][1] * (time[whichguy]))) / 100);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glRotatef(((torsorot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((torsorot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((torsorot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  /*glPushMatrix();
          glTranslatef(1.5f,3.0f,0.0f);
          glScalef(.8,.8,.8);
          glRotatef(((lefthigharm[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthigharm[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,1.0f,0.0f,0.0f); glRotatef(((lefthigharm[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthigharm[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,1.0f,0.0f); glRotatef(((lefthigharm[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthigharm[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,0.0f,1.0f);;
          glTranslatef(0.0f,-2.5f,0.0f);
          glRotatef(((leftlowarm[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(leftlowarm[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,1.0f,0.0f,0.0f); glRotatef(((leftlowarm[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(leftlowarm[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,1.0f,0.0f); glRotatef(((leftlowarm[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(leftlowarm[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,0.0f,1.0f);
          glTranslatef(0.0f,-1.8f,0.0f);
          glRotatef(((lefthand[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthand[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,1.0f,0.0f,0.0f); glRotatef(((lefthand[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthand[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,1.0f,0.0f); glRotatef(((lefthand[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthand[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,0.0f,1.0f);
          if(itemnum[whichguy]==3){
          glRotatef(90,1.0,0.0,0.0);
          glTranslatef(-0.3f,-1.0f,0.8f);
          glRotatef(90,0.0,1.0,0.0);
          glBindTexture(GL_TEXTURE_2D, texture[41]);
          }
  glPopMatrix();*/
  glPushMatrix();
  glTranslatef(-1.5f, 3.0f, 0.0f);
  glScalef(-.8, .8, .8);
  glRotatef(((righthigharm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((righthigharm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((righthigharm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((rightlowarm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((rightlowarm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((rightlowarm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -1.8f, 0.0f);
  glRotatef(((righthand[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((righthand[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((righthand[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (itemnum[whichguy] == 1) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(-0.3f, 0.7f, 3.8f);
    glTranslatef(0.0f, 0.0f, 3.5f);
    glScalef(.8, .8, .8);
  }
  if (itemnum[whichguy] == 5) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(0.0f, -0.2f, 0.1f);
    glTranslatef(0.0f, 1.0f, 7.5f);
  }
  if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(-0.3f, -1.0f, 0.8f);
    glRotatef(90, 0.0, 1.0, 0.0);
    glTranslatef(0.0f, 8.0f, 0.0f);
  }
  if (itemnum[whichguy] == 4) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(180, 0.0, 1.0, 0.0);
    glTranslatef(0.3f, 0.3f, -1.2f);
    glTranslatef(0.0f, 0.0f, -4.2f);
    glScalef(2, 2, 2);
  }
  if (itemnum[whichguy] == 6) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(180, 0.0, 1.0, 0.0);
    glTranslatef(0.3f, 0.3f, -1.2f);
    glTranslatef(0.0f, 0.0f, -3.2f);
    glScalef(2, 2, 2);
  }
  if (itemnum[whichguy] == 7) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(180, 0.0, 1.0, 0.0);
    glTranslatef(0.3f, 0.3f, -1.2f);
    glTranslatef(0.0f, 0.0f, -3.2f);
    glScalef(2, 2, 2);
  }
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  glPopMatrix();
  glRotatef(-torsorot[0][frame[whichguy]][anim[whichguy]], 1.0f, 0.0f, 0.0f);
  glRotatef(-torsorot[1][frame[whichguy]][anim[whichguy]], 0.0f, 1.0f, 0.0f);
  glRotatef(-torsorot[2][frame[whichguy]][anim[whichguy]], 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -0.5f, 0.0f);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  GunPoint.x = M[12];
  GunPoint.y = M[13];
  GunPoint.z = M[14];
  return GunPoint;
}

Point3D FindEyePoint(int whichguy) {
  float hipfloat[3][2];
  Point3D EyePoint;
  glPushMatrix();
  glLoadIdentity();
  // glTranslatef(40.0f,30.0f,70.0f);
  glTranslatef(guyx[whichguy], guyy[whichguy], 0.0f);
  if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    targetrotation[whichguy] = 0;
  }
  if (activity[whichguy] == runleft || activity[whichguy] == leftflip || activity[whichguy] == leftroll || activity[whichguy] == fallbackwardsright || activity[whichguy] == hitwallright || activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordidleleft || activity[whichguy] == swordleftthrust || activity[whichguy] == jetleft) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordleftthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleleft || activity[whichguy] == jetimpaledleft) {
    rotation[whichguy] = -90;
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == runright || activity[whichguy] == rightflip || activity[whichguy] == rightroll || activity[whichguy] == fallbackwardsleft || activity[whichguy] == hitwallleft || activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordidleright || activity[whichguy] == swordrightthrust || activity[whichguy] == jetright) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordrightthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaledright) {
    rotation[whichguy] = 90;
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] > 0) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] < 0) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    glTranslatef(0.0f, 0.0f, -1.0f);
    targetrotation[whichguy] = 0;
    rotation[whichguy] = 0;
  }
  glRotatef(((rotation[whichguy] * (100 - time[whichguy])) + (targetrotation[whichguy] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glTranslatef(0, .1, 0);
  glScalef(size[whichguy], size[whichguy], size[whichguy]);
  hipfloat[1][0] = (float)(hippos[1][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[2][0] = (float)(hippos[2][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[0][0] = (float)(hippos[0][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[1][1] = (float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[2][1] = (float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[0][1] = (float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  glPushMatrix();
  glRotatef(((hiprot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((hiprot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((hiprot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(((hipfloat[1][0] * (100 - time[whichguy])) + (hipfloat[1][1] * (time[whichguy]))) / 100, ((hipfloat[2][0] * (100 - time[whichguy])) + (hipfloat[2][1] * (time[whichguy]))) / 100, ((hipfloat[0][0] * (100 - time[whichguy])) + (hipfloat[0][1] * (time[whichguy]))) / 100);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glRotatef(((torsorot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((torsorot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((torsorot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glTranslatef(0.0f, 3.5f, 0.0f);
  glRotatef(((head[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((head[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((head[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  EyePoint.x = M[12];
  EyePoint.y = M[13];
  EyePoint.z = M[14];
  return EyePoint;
}

Point3D FindEyeRot(int whichguy) {
  float hipfloat[3][2];
  Point3D EyePoint;
  Point3D EyePoint2;
  Point3D Angle;
  glPushMatrix();
  glLoadIdentity();
  // glTranslatef(40.0f,30.0f,70.0f);
  glTranslatef(guyx[whichguy], guyy[whichguy], 0.0f);
  if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    targetrotation[whichguy] = 0;
  }
  if (activity[whichguy] == runleft || activity[whichguy] == leftflip || activity[whichguy] == leftroll || activity[whichguy] == fallbackwardsright || activity[whichguy] == hitwallright || activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordidleleft || activity[whichguy] == swordleftthrust || activity[whichguy] == jetleft) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordleftthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleleft || activity[whichguy] == jetimpaledleft) {
    rotation[whichguy] = -90;
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == runright || activity[whichguy] == rightflip || activity[whichguy] == rightroll || activity[whichguy] == fallbackwardsleft || activity[whichguy] == hitwallleft || activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordidleright || activity[whichguy] == swordrightthrust || activity[whichguy] == jetright) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordrightthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaledright) {
    rotation[whichguy] = 90;
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] > 0) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] < 0) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    glTranslatef(0.0f, 0.0f, -1.0f);
    targetrotation[whichguy] = 0;
    rotation[whichguy] = 0;
  }
  glRotatef(((rotation[whichguy] * (100 - time[whichguy])) + (targetrotation[whichguy] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glTranslatef(0, .1, 0);
  glScalef(size[whichguy], size[whichguy], size[whichguy]);
  hipfloat[1][0] = (float)(hippos[1][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[2][0] = (float)(hippos[2][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[0][0] = (float)(hippos[0][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[1][1] = (float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[2][1] = (float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[0][1] = (float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  glPushMatrix();
  glRotatef(((hiprot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((hiprot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((hiprot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(((hipfloat[1][0] * (100 - time[whichguy])) + (hipfloat[1][1] * (time[whichguy]))) / 100, ((hipfloat[2][0] * (100 - time[whichguy])) + (hipfloat[2][1] * (time[whichguy]))) / 100, ((hipfloat[0][0] * (100 - time[whichguy])) + (hipfloat[0][1] * (time[whichguy]))) / 100);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glRotatef(((torsorot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((torsorot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((torsorot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glTranslatef(0.0f, 3.5f, 0.0f);
  glRotatef(((head[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((head[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((head[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  EyePoint.x = M[12];
  EyePoint.y = M[13];
  EyePoint.z = M[14];
  glTranslatef(0.0f, 0.0f, 1.0f);
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  EyePoint2.x = M[12];
  EyePoint2.y = M[13];
  EyePoint2.z = M[14];
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();

  // EyePoint.x=((rotation[whichguy]*(100-time[whichguy]))+(targetrotation[whichguy]*(time[whichguy])))/100+((hiprot[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy]))/100)+((torsorot[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100+((head[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(head[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100;
  // EyePoint.y=((hiprot[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100+((head[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(head[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100+((torsorot[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100;

  if (EyePoint2.z != EyePoint.z) {
    Angle.y = atan((EyePoint2.x - EyePoint.x) / (EyePoint2.z - EyePoint.z)) / 6.28 * 360 + 180;
  }

  if (EyePoint2.z < EyePoint.z)
    Angle.y += 180;
  else if (EyePoint2.z == EyePoint.z) {
    if (EyePoint2.x < EyePoint.x)
      Angle.y = 90;
    else
      Angle.y = 270;
  }
  Angle.y *= -1;
  Angle.x = ((hiprot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100 + ((torsorot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100 + ((head[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (head[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100;
  // EyePoint2=DoRotation(EyePoint2,0,-Angle.y,0);
  // EyePoint=DoRotation(EyePoint,0,-Angle.y,0);

  /*if(EyePoint2.z!=EyePoint.z){ Angle.x = atan((EyePoint2.y - EyePoint.y) / (EyePoint2.y - EyePoint.z))/6.28*360+180;}

       if (EyePoint2.z < EyePoint.z)
       Angle.x += 180;
   else if (EyePoint2.z == EyePoint.z)
   {
   if (EyePoint2.y < EyePoint.y)
       Angle.x = 90;
   else
       Angle.x = 270;
   }*/
  // Angle.x*=-1;
  // Angle.x+=270;
  return Angle;
}
/*
Point3D FindRightGunPoint(int whichguy){
        Point3D newpoint;
        Point3D oldpoint;
        newpoint.x=0; newpoint.y=0; newpoint.z=0;
        oldpoint.x=0; oldpoint.y=0; oldpoint.z=0;
        float hipfloat[3][2];

        hipfloat[1][0]=(float)(hippos[1][frame[whichguy]][anim[whichguy]])/10;
        hipfloat[2][0]=(float)(hippos[2][frame[whichguy]][anim[whichguy]])/10;
        hipfloat[0][0]=(float)(hippos[0][frame[whichguy]][anim[whichguy]])/10;
        hipfloat[1][1]=(float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]])/10;
        hipfloat[2][1]=(float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]])/10;
        hipfloat[0][1]=(float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]])/10;

        if(itemnum[whichguy]==1){
                        newpoint.y-=11.9;
                        newpoint.z-=4;
                        newpoint.x*=.8;
                        newpoint.y*=.8;
                        newpoint.z*=.8;
                        newpoint.x-=.3;
                        newpoint.y+=.7;
                        newpoint.z+=3.8;
                        DoRotation(newpoint,90,0,0);
        }

        if(itemnum[whichguy]==5){
                        newpoint.y-=9.9;
                        newpoint.z-=4;
                        newpoint.x*=.8;
                        newpoint.y*=.8;
                        newpoint.z*=.8;
                        newpoint.x-=.3;
                        newpoint.y+=0.7;
                        newpoint.z+=4.5;
                        DoRotation(newpoint,90,0,0);
        }

        if(itemnum[whichguy]==4){
                        newpoint.y-=8;
                        newpoint.z-=4;
                        newpoint.x*=.8;
                        newpoint.y*=.8;
                        newpoint.z*=.8;
                        newpoint.x-=.3;
                        newpoint.y+=.7;
                        newpoint.z+=3.8;
                        DoRotation(newpoint,90,0,0);
        }


        newpoint=DoRotation(newpoint,((righthand[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(righthand[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((righthand[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(righthand[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((righthand[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(righthand[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
        newpoint.y-=1.8;
        newpoint=DoRotation(newpoint,((rightlowarm[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(rightlowarm[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((rightlowarm[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(rightlowarm[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((rightlowarm[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(rightlowarm[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
        newpoint.y-=2.5;
        newpoint=DoRotation(newpoint,((righthigharm[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(righthigharm[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((righthigharm[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(righthigharm[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((righthigharm[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(righthigharm[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
        newpoint.x*=-.8;
        newpoint.y*=.8;
        newpoint.z*=.8;
        newpoint.y+=3;
        newpoint.x-=1.5;
        newpoint=DoRotation(newpoint,((torsorot[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((torsorot[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((torsorot[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
        newpoint.y+=.5;
        newpoint.x+=((hipfloat[1][0]*(100-time[whichguy]))+(hipfloat[1][1]*(time[whichguy])))/100;
        newpoint.y+=((hipfloat[2][0]*(100-time[whichguy]))+(hipfloat[2][1]*(time[whichguy])))/100;
        newpoint.z+=((hipfloat[0][0]*(100-time[whichguy]))+(hipfloat[0][1]*(time[whichguy])))/100;

        newpoint=DoRotation(newpoint,((hiprot[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((hiprot[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((hiprot[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
        newpoint=DoRotation(newpoint,0,((rotation[whichguy]*(100-time[whichguy]))+(targetrotation[whichguy]*(time[whichguy])))/100,0);
        newpoint.x*=size[whichguy];newpoint.y*=size[whichguy];newpoint.z*=size[whichguy];
        newpoint.x +=guyx[whichguy];
        newpoint.y +=guyy[whichguy];
        if (activity[whichguy]==climbrope||activity[whichguy]==onrope||activity[whichguy]==downrope){newpoint.z-=1.0;}
        return newpoint;
}
*/

Point3D FindJetPackPos(int whichguy) {
  float hipfloat[3][2];
  Point3D GunPoint;
  glPushMatrix();
  glLoadIdentity();
  // glTranslatef(40.0f,30.0f,70.0f);
  glTranslatef(guyx[whichguy], guyy[whichguy], 0.0f);
  if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    targetrotation[whichguy] = 0;
  }
  if (activity[whichguy] == runleft || activity[whichguy] == leftflip || activity[whichguy] == leftroll || activity[whichguy] == fallbackwardsright || activity[whichguy] == hitwallright || activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleleft || activity[whichguy] == swordleftthrust || activity[whichguy] == jetleft) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordleftthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleleft || activity[whichguy] == jetimpaledleft || activity[whichguy] == grenshootleft) {
    rotation[whichguy] = -90;
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == runright || activity[whichguy] == rightflip || activity[whichguy] == rightroll || activity[whichguy] == fallbackwardsleft || activity[whichguy] == hitwallleft || activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordidleright || activity[whichguy] == grenidleright || activity[whichguy] == swordrightthrust || activity[whichguy] == jetright) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordrightthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaledright || activity[whichguy] == grenshootright) {
    rotation[whichguy] = 90;
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] > 0) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] < 0) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    glTranslatef(0.0f, 0.0f, -1.0f);
    targetrotation[whichguy] = 0;
    rotation[whichguy] = 0;
  }
  glRotatef(((rotation[whichguy] * (100 - time[whichguy])) + (targetrotation[whichguy] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glTranslatef(0, .1, 0);
  glScalef(size[whichguy], size[whichguy], size[whichguy]);
  hipfloat[1][0] = (float)(hippos[1][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[2][0] = (float)(hippos[2][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[0][0] = (float)(hippos[0][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[1][1] = (float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[2][1] = (float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[0][1] = (float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  glPushMatrix();
  glRotatef(((hiprot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((hiprot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((hiprot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(((hipfloat[1][0] * (100 - time[whichguy])) + (hipfloat[1][1] * (time[whichguy]))) / 100, ((hipfloat[2][0] * (100 - time[whichguy])) + (hipfloat[2][1] * (time[whichguy]))) / 100, ((hipfloat[0][0] * (100 - time[whichguy])) + (hipfloat[0][1] * (time[whichguy]))) / 100);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glRotatef(((torsorot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((torsorot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((torsorot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -1.0f, -2.0f);
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  GunPoint.x = M[12];
  GunPoint.y = M[13];
  GunPoint.z = M[14];
  return GunPoint;
}

Point3D FindBodyPart(int whichguy, int whichpart) {
  float hipfloat[3][2];
  Point3D GunPoint;
  glPushMatrix();
  glLoadIdentity();
  // glTranslatef(40.0f,30.0f,70.0f);
  glTranslatef(guyx[whichguy], guyy[whichguy], 0.0f);
  if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    targetrotation[whichguy] = 0;
  }
  if (activity[whichguy] == runleft || activity[whichguy] == leftflip || activity[whichguy] == leftroll || activity[whichguy] == fallbackwardsright || activity[whichguy] == hitwallright || activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleleft || activity[whichguy] == swordleftthrust || activity[whichguy] == jetleft) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordleftthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleleft || activity[whichguy] == jetimpaledleft || activity[whichguy] == grenshootleft) {
    rotation[whichguy] = -90;
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == runright || activity[whichguy] == rightflip || activity[whichguy] == rightroll || activity[whichguy] == fallbackwardsleft || activity[whichguy] == hitwallleft || activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordidleright || activity[whichguy] == grenidleright || activity[whichguy] == swordrightthrust || activity[whichguy] == jetright) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordrightthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaledright || activity[whichguy] == grenshootright) {
    rotation[whichguy] = 90;
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] > 0) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] < 0) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    glTranslatef(0.0f, 0.0f, -1.0f);
    targetrotation[whichguy] = 0;
    rotation[whichguy] = 0;
  }
  glRotatef(((rotation[whichguy] * (100 - time[whichguy])) + (targetrotation[whichguy] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glTranslatef(0, .1, 0);
  glScalef(size[whichguy], size[whichguy], size[whichguy]);
  hipfloat[1][0] = (float)(hippos[1][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[2][0] = (float)(hippos[2][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[0][0] = (float)(hippos[0][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[1][1] = (float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[2][1] = (float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[0][1] = (float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  glPushMatrix();
  glRotatef(((hiprot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((hiprot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((hiprot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(((hipfloat[1][0] * (100 - time[whichguy])) + (hipfloat[1][1] * (time[whichguy]))) / 100, ((hipfloat[2][0] * (100 - time[whichguy])) + (hipfloat[2][1] * (time[whichguy]))) / 100, ((hipfloat[0][0] * (100 - time[whichguy])) + (hipfloat[0][1] * (time[whichguy]))) / 100);
  if (whichpart == kHip) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glTranslatef(0.0f, 0.5f, 0.0f);
  glRotatef(((torsorot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((torsorot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((torsorot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kTorso) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glPushMatrix();
  glTranslatef(0.0f, 3.5f, 0.0f);
  if (whichpart == kHead) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glPopMatrix();
  glPushMatrix();
  glTranslatef(1.5f, 3.0f, 0.0f);
  glScalef(.8, .8, .8);
  glRotatef(((lefthigharm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((lefthigharm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((lefthigharm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kLeftUpperArm) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((leftlowarm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((leftlowarm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((leftlowarm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kLeftLowerArm) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glTranslatef(0.0f, -1.8f, 0.0f);
  glRotatef(90, 1.0, 0.0, 0.0);
  glTranslatef(-0.3f, -1.0f, 0.8f);
  if (whichpart == kLeftHand) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-1.5f, 3.0f, 0.0f);
  glScalef(-.8, .8, .8);
  glRotatef(((righthigharm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((righthigharm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((righthigharm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthigharm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kRightUpperArm) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((rightlowarm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((rightlowarm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((rightlowarm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowarm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kRightLowerArm) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glTranslatef(0.0f, -1.8f, 0.0f);
  glRotatef(((righthand[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((righthand[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((righthand[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthand[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glRotatef(90, 1.0, 0.0, 0.0);
  glTranslatef(-0.3f, -1.0f, 0.8f);
  if (whichpart == kRightHand) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glPopMatrix();
  glRotatef(-torsorot[0][frame[whichguy]][anim[whichguy]], 1.0f, 0.0f, 0.0f);
  glRotatef(-torsorot[1][frame[whichguy]][anim[whichguy]], 0.0f, 1.0f, 0.0f);
  glRotatef(-torsorot[2][frame[whichguy]][anim[whichguy]], 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -0.5f, 0.0f);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.8f, 0.0f, 0.0f);
  glRotatef(((lefthighleg[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthighleg[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((lefthighleg[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthighleg[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((lefthighleg[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthighleg[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kLeftUpperLeg) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((leftlowleg[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowleg[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((leftlowleg[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowleg[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((leftlowleg[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowleg[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kLeftLowerLeg) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glTranslatef(0.0f, -1.5f, 0.0f);
  glRotatef(((leftfoot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftfoot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((leftfoot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftfoot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((leftfoot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftfoot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kLeftFoot) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-0.8f, 0.0f, 0.0f);
  glRotatef(((righthighleg[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthighleg[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((righthighleg[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthighleg[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((righthighleg[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (righthighleg[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kRightUpperLeg) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((rightlowleg[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowleg[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((rightlowleg[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowleg[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((rightlowleg[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightlowleg[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kRightLowerLeg) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glTranslatef(0.0f, -1.5f, 0.0f);
  glRotatef(((rightfoot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightfoot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((rightfoot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightfoot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((rightfoot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (rightfoot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  if (whichpart == kRightFoot) {
    glGetFloatv(GL_MODELVIEW_MATRIX, M);
  }
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  GunPoint.x = M[12];
  GunPoint.y = M[13];
  GunPoint.z = M[14];
  if (whichpart == kRightGun) {
    GunPoint = FindRightGunPoint(whichguy);
  }
  return GunPoint;
}
/*
Point3D FindJetPackPos(int whichguy){
        Point3D newpoint;
        Point3D oldpoint;
        newpoint.x=0; newpoint.y=0; newpoint.z=0;
        oldpoint.x=0; oldpoint.y=0; oldpoint.z=0;
        float hipfloat[3][2];

        hipfloat[1][0]=(float)(hippos[1][frame[whichguy]][anim[whichguy]])/10;
        hipfloat[2][0]=(float)(hippos[2][frame[whichguy]][anim[whichguy]])/10;
        hipfloat[0][0]=(float)(hippos[0][frame[whichguy]][anim[whichguy]])/10;
        hipfloat[1][1]=(float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]])/10;
        hipfloat[2][1]=(float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]])/10;
        hipfloat[0][1]=(float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]])/10;

        newpoint.z-=2;
        newpoint.y-=1;
        newpoint=DoRotation(newpoint,((torsorot[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((torsorot[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((torsorot[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
        newpoint.y+=.5;
        newpoint.x+=((hipfloat[1][0]*(100-time[whichguy]))+(hipfloat[1][1]*(time[whichguy])))/100;
        newpoint.y+=((hipfloat[2][0]*(100-time[whichguy]))+(hipfloat[2][1]*(time[whichguy])))/100;
        newpoint.z+=((hipfloat[0][0]*(100-time[whichguy]))+(hipfloat[0][1]*(time[whichguy])))/100;

        newpoint=DoRotation(newpoint,((hiprot[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((hiprot[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((hiprot[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
        newpoint=DoRotation(newpoint,0,((rotation[whichguy]*(100-time[whichguy]))+(targetrotation[whichguy]*(time[whichguy])))/100,0);
        newpoint.x*=size[whichguy];newpoint.y*=size[whichguy];newpoint.z*=size[whichguy];
        newpoint.x +=guyx[whichguy];
        newpoint.y +=guyy[whichguy];
        if (activity[whichguy]==climbrope||activity[whichguy]==onrope||activity[whichguy]==downrope){newpoint.z-=1.0;}
        return newpoint;
}
*/
/*Point3D FindLeftGunPoint(int whichguy){
        Point3D newpoint;
        Point3D oldpoint;
        newpoint.x=0; newpoint.y=0; newpoint.z=0;
        oldpoint.x=0; oldpoint.y=0; oldpoint.z=0;
        float hipfloat[3][2];

        hipfloat[1][0]=(float)(hippos[1][frame[whichguy]][anim[whichguy]])/10;
        hipfloat[2][0]=(float)(hippos[2][frame[whichguy]][anim[whichguy]])/10;
        hipfloat[0][0]=(float)(hippos[0][frame[whichguy]][anim[whichguy]])/10;
        hipfloat[1][1]=(float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]])/10;
        hipfloat[2][1]=(float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]])/10;
        hipfloat[0][1]=(float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]])/10;

        /*if(itemnum==2||itemnum==3){
                        newpoint.y-=10;
                        newpoint.z-=4;
                        newpoint.x*=.8;
                        newpoint.y*=.8;
                        newpoint.z*=.8;
                        newpoint.x-=.3;
                        newpoint.y+=.7;
                        newpoint.z+=3.8;
                        DoRotation(newpoint,90,0,0);
        }*/
/*
newpoint=DoRotation(newpoint,((lefthand[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthand[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((lefthand[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthand[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((lefthand[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthand[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
newpoint.y-=1.8;
newpoint=DoRotation(newpoint,((leftlowarm[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(leftlowarm[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((leftlowarm[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(leftlowarm[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((leftlowarm[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(leftlowarm[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
newpoint.y-=2.5;
newpoint=DoRotation(newpoint,((lefthigharm[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthigharm[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((lefthigharm[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthigharm[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((lefthigharm[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthigharm[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
newpoint.x*=.8;
newpoint.y*=.8;
newpoint.z*=.8;
newpoint.y+=3;
newpoint.x+=1.5;
newpoint=DoRotation(newpoint,((torsorot[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((torsorot[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((torsorot[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(torsorot[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
newpoint.y+=.5;
newpoint.x+=((hipfloat[1][0]*(100-time[whichguy]))+(hipfloat[1][1]*(time[whichguy])))/100;
newpoint.y+=((hipfloat[2][0]*(100-time[whichguy]))+(hipfloat[2][1]*(time[whichguy])))/100;
newpoint.z+=((hipfloat[0][0]*(100-time[whichguy]))+(hipfloat[0][1]*(time[whichguy])))/100;

newpoint=DoRotation(newpoint,((hiprot[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((hiprot[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,((hiprot[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(hiprot[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100);
newpoint=DoRotation(newpoint,0,((rotation[whichguy]*(100-time[whichguy]))+(targetrotation[whichguy]*(time[whichguy])))/100,0);
newpoint.x*=size[whichguy];newpoint.y*=size[whichguy];newpoint.z*=size[whichguy];
newpoint.x +=guyx[whichguy];
newpoint.y +=guyy[whichguy];
if (activity[whichguy]==climbrope||activity[whichguy]==onrope||activity[whichguy]==downrope){newpoint.z-=1.0;}
return newpoint;
}*/

Point3D FindLeftGunPoint(int whichguy) {
  float hipfloat[3][2];
  Point3D GunPoint;
  glPushMatrix();
  glLoadIdentity();
  // glTranslatef(40.0f,30.0f,70.0f);
  glTranslatef(guyx[whichguy], guyy[whichguy], 0.0f);
  if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    targetrotation[whichguy] = 0;
  }
  if (activity[whichguy] == runleft || activity[whichguy] == leftflip || activity[whichguy] == leftroll || activity[whichguy] == fallbackwardsright || activity[whichguy] == hitwallright || activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordidleleft || activity[whichguy] == swordleftthrust || activity[whichguy] == jetleft) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == brokeneckleft || activity[whichguy] == breakneckleft || activity[whichguy] == impaleleft || activity[whichguy] == impaledleft || activity[whichguy] == duckimpaleleft || activity[whichguy] == duckimpaledleft || activity[whichguy] == swordthrowleft || activity[whichguy] == swordthrownleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight || activity[whichguy] == swordleftthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleleft || activity[whichguy] == jetimpaledleft) {
    rotation[whichguy] = -90;
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == runright || activity[whichguy] == rightflip || activity[whichguy] == rightroll || activity[whichguy] == fallbackwardsleft || activity[whichguy] == hitwallleft || activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordidleright || activity[whichguy] == swordrightthrust || activity[whichguy] == jetright) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == brokeneckright || activity[whichguy] == breakneckright || activity[whichguy] == impaleright || activity[whichguy] == impaledright || activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaledright || activity[whichguy] == swordthrowright || activity[whichguy] == swordthrownright || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == swordrightthrust || activity[whichguy] == swordrightparry || activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaledright) {
    rotation[whichguy] = 90;
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] > 0) {
    targetrotation[whichguy] = 90;
  }
  if (activity[whichguy] == falling && guyvelx[whichguy] < 0) {
    targetrotation[whichguy] = -90;
  }
  if (activity[whichguy] == climbrope || activity[whichguy] == onrope || activity[whichguy] == downrope) {
    glTranslatef(0.0f, 0.0f, -1.0f);
    targetrotation[whichguy] = 0;
    rotation[whichguy] = 0;
  }
  glRotatef(((rotation[whichguy] * (100 - time[whichguy])) + (targetrotation[whichguy] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glTranslatef(0, .1, 0);
  glScalef(size[whichguy], size[whichguy], size[whichguy]);
  hipfloat[1][0] = (float)(hippos[1][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[2][0] = (float)(hippos[2][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[0][0] = (float)(hippos[0][frame[whichguy]][anim[whichguy]]) / 10;
  hipfloat[1][1] = (float)(hippos[1][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[2][1] = (float)(hippos[2][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  hipfloat[0][1] = (float)(hippos[0][targetframe[whichguy]][targetanim[whichguy]]) / 10;
  glPushMatrix();
  glRotatef(((hiprot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((hiprot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((hiprot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (hiprot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(((hipfloat[1][0] * (100 - time[whichguy])) + (hipfloat[1][1] * (time[whichguy]))) / 100, ((hipfloat[2][0] * (100 - time[whichguy])) + (hipfloat[2][1] * (time[whichguy]))) / 100, ((hipfloat[0][0] * (100 - time[whichguy])) + (hipfloat[0][1] * (time[whichguy]))) / 100);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glPushMatrix();
  glTranslatef(0.0f, 0.5f, 0.0f);
  glRotatef(((torsorot[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((torsorot[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((torsorot[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (torsorot[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  /*glPushMatrix();
          glTranslatef(1.5f,3.0f,0.0f);
          glScalef(.8,.8,.8);
          glRotatef(((lefthigharm[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthigharm[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,1.0f,0.0f,0.0f); glRotatef(((lefthigharm[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthigharm[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,1.0f,0.0f); glRotatef(((lefthigharm[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthigharm[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,0.0f,1.0f);;
          glTranslatef(0.0f,-2.5f,0.0f);
          glRotatef(((leftlowarm[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(leftlowarm[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,1.0f,0.0f,0.0f); glRotatef(((leftlowarm[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(leftlowarm[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,1.0f,0.0f); glRotatef(((leftlowarm[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(leftlowarm[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,0.0f,1.0f);
          glTranslatef(0.0f,-1.8f,0.0f);
          glRotatef(((lefthand[0][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthand[0][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,1.0f,0.0f,0.0f); glRotatef(((lefthand[1][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthand[1][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,1.0f,0.0f); glRotatef(((lefthand[2][frame[whichguy]][anim[whichguy]]*(100-time[whichguy]))+(lefthand[2][targetframe[whichguy]][targetanim[whichguy]]*(time[whichguy])))/100,0.0f,0.0f,1.0f);
          if(itemnum[whichguy]==3){
          glRotatef(90,1.0,0.0,0.0);
          glTranslatef(-0.3f,-1.0f,0.8f);
          glRotatef(90,0.0,1.0,0.0);
          glBindTexture(GL_TEXTURE_2D, texture[41]);
          }
  glPopMatrix();*/
  glPushMatrix();
  glTranslatef(1.5f, 3.0f, 0.0f);
  glScalef(.8, .8, .8);
  glRotatef(((lefthigharm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((lefthigharm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((lefthigharm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthigharm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -2.5f, 0.0f);
  glRotatef(((leftlowarm[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((leftlowarm[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((leftlowarm[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (leftlowarm[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -1.8f, 0.0f);
  glRotatef(((lefthand[0][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthand[0][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 1.0f, 0.0f, 0.0f);
  glRotatef(((lefthand[1][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthand[1][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 1.0f, 0.0f);
  glRotatef(((lefthand[2][frame[whichguy]][anim[whichguy]] * (100 - time[whichguy])) + (lefthand[2][targetframe[whichguy]][targetanim[whichguy]] * (time[whichguy]))) / 100, 0.0f, 0.0f, 1.0f);
  /*if(itemnum[whichguy]==1){
  glRotatef(90,1.0,0.0,0.0);
  glTranslatef(-0.3f,0.7f,3.8f);
  glTranslatef(0.0f,0.0f,3.5f);
  glScalef(.8,.8,.8);}
  if(itemnum[whichguy]==5){
  glRotatef(90,1.0,0.0,0.0);
  glTranslatef(0.0f,-0.2f,0.1f);
  glTranslatef(0.0f,1.0f,7.5f);}*/
  if (itemnum[whichguy] == 3) {
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(-0.3f, -1.0f, 0.8f);
    glRotatef(90, 0.0, 1.0, 0.0);
    glTranslatef(0.0f, 8.0f, 0.0f);
  }
  /*if(itemnum[whichguy]==4){
  glRotatef(90,1.0,0.0,0.0);
  glRotatef(180,0.0,1.0,0.0);
  glTranslatef(0.3f,0.3f,-1.2f);
  glTranslatef(0.0f,0.0f,-4.2f);
  glScalef(2,2,2);}
  if(itemnum[whichguy]==6){
  glRotatef(90,1.0,0.0,0.0);
  glRotatef(180,0.0,1.0,0.0);
  glTranslatef(0.3f,0.3f,-1.2f);
  glTranslatef(0.0f,0.0f,-3.2f);
  glScalef(2,2,2);}
  if(itemnum[whichguy]==7){
  glRotatef(90,1.0,0.0,0.0);
  glRotatef(180,0.0,1.0,0.0);
  glTranslatef(0.3f,0.3f,-1.2f);
  glTranslatef(0.0f,0.0f,-3.2f);
  glScalef(2,2,2);}*/
  glGetFloatv(GL_MODELVIEW_MATRIX, M);
  glPopMatrix();
  glRotatef(-torsorot[0][frame[whichguy]][anim[whichguy]], 1.0f, 0.0f, 0.0f);
  glRotatef(-torsorot[1][frame[whichguy]][anim[whichguy]], 0.0f, 1.0f, 0.0f);
  glRotatef(-torsorot[2][frame[whichguy]][anim[whichguy]], 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, -0.5f, 0.0f);
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  GunPoint.x = M[12];
  GunPoint.y = M[13];
  GunPoint.z = M[14];
  return GunPoint;
}
/********************> EventLoop() <*****/
void DoPlayerStuff(int whichguy);
void DoAIPlayerStuff(int whichguy) {
  unsigned char theKeyMap[16];
  lightningfxdelay[whichguy] -= multiplier;
  int x, y, a, b, c, d, e, f, g, verydead = 0;
  int slowspeed = 500;
  if (unlimitedammo) {
    ammo[whichguy] = 1000;
  }
  if (ammo[whichguy] < 0) {
    ammo[whichguy] = 0;
  }
  for (x = 0; x < maxswordtrail; x++) {
    SwordTrail[whichguy][0].brightness[x][3] -= multiplier / 30;
    if (SwordTrail[whichguy][0].brightness[x][3] < 0) {
      SwordTrail[whichguy][0].brightness[x][3] = 0;
    }
  }
  for (x = 0; x < maxswordtrail; x++) {
    SwordTrail[whichguy][1].brightness[x][3] -= multiplier / 30;
    if (SwordTrail[whichguy][1].brightness[x][3] < 0) {
      SwordTrail[whichguy][1].brightness[x][3] = 0;
    }
  }
  swordtraildelay[whichguy] -= multiplier / 5;
  if (swordtraildelay[whichguy] <= 0) {
    MakeNewSwordTrail(whichguy);
    swordtraildelay[whichguy] = .3;
  }

  if (activity[whichguy] == impaleright || activity[whichguy] == impaleleft ||
      activity[whichguy] == swordrightthrust || activity[whichguy] == swordleftthrust ||
      activity[whichguy] == swordrightspin || activity[whichguy] == swordleftspin) {
    swordtrailtoggle[whichguy][0] = 1;
    swordtrailtoggle[whichguy][1] = 0;
  } else {
    swordtrailtoggle[whichguy][0] = 0;
    swordtrailtoggle[whichguy][1] = 0;
  }

  if (activity[whichguy] == swordthrowright || activity[whichguy] == swordthrowleft ||
      activity[whichguy] == swordrightparry || activity[whichguy] == swordleftparry ||
      activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaleleft ||
      activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaleleft) {
    swordtrailtoggle[whichguy][0] = 1;
    if (itemnum[whichguy] == 3) {
      swordtrailtoggle[whichguy][1] = 1;
    }
  }

  if (constantswordtrail) {
    swordtrailtoggle[whichguy][0] = 1;
    swordtrailtoggle[whichguy][1] = 1;
  }

  UpdateSwordTrail(whichguy, unusedswordtrail[whichguy]);
  for (x = 0; x < 16; x++) {
    smokingbodydelay[whichguy][x] -= multiplier * RangedRandom(50, 100) / 100;
    if (smokingbody[whichguy][x] > 0) {
      if (smokingbodydelay[whichguy][x] < 0) {
        point = FindBodyPart(whichguy, x);
        MakeSprite(point.x, point.y, point.z, RangedRandom(10, 20) + smokingbody[whichguy][x] / 5, smokesprite, RangedRandom(0, 360), RangedRandom(0, 4) + 6, 0, .1, .4, 0);
        smokingbodydelay[whichguy][x] = RangedRandom(8, 15);
        smokingbody[whichguy][x] -= 2;
        sprite[unusedsprite].type2 = 1;
      }
    }
  }
  if (frame[whichguy] == 2) {
    lightningdelay[whichguy] -= multiplier;
  }
  delaytime[whichguy] -= multiplier;
  int guywillbe;
  oldguyx[whichguy] = guyx[whichguy];
  oldguyy[whichguy] = guyy[whichguy];
  if (cloaktime[whichguy] < 100) {
    cloaktime[whichguy] += multiplier;
    if (cloaktime[whichguy] >= 100 && invisible[whichguy] == 1) {
      invisible[whichguy] = 2;
    }
    if (cloaktime[whichguy] >= 100 && invisible[whichguy] == 0) {
      invisible[whichguy] = 1;
    }
    if (invisible[whichguy] == 2) {
      invisible[whichguy] = 0;
    }
  }
  if (cloaktime[whichguy] > 100) {
    cloaktime[whichguy] += multiplier;
  }
  if (activity[whichguy] == deadfacedown && dead[whichguy] == 1 && health[whichguy] <= 0) {
    verydead = 1;
  }
  if (activity[whichguy] == deadfaceup && dead[whichguy] == 1 && health[whichguy] <= 0) {
    verydead = 1;
  }
  if (dead[whichguy] == 1 && health[whichguy] <= 0 && invisible[whichguy] == 1 && cloaktime[whichguy] >= 100) {
    cloaktime[whichguy] = 0;
  }
  if (whichguy == 0) {
    verydeadshow = verydead;
  }
  if (verydead == 0 && activity[whichguy] != onrope && activity[whichguy] != downrope) {
    oldtime[whichguy] = time[whichguy];
    if (anim[whichguy] == 7 || anim[whichguy] == 8) {
      time[whichguy] += (((float)speed[frame[whichguy]][anim[whichguy]] / 1000)) * multiplier / 3;
    }
    if (anim[whichguy] == 7) {
      time[whichguy] += (((float)speed[frame[whichguy]][anim[whichguy]] / 1000)) * multiplier / 2;
    }
    if (time[whichguy] < 100 && timedirection[whichguy] == 1) {
      time[whichguy] += (((float)speed[frame[whichguy]][anim[whichguy]] / 1000)) * multiplier / 3;
    }
    if (time[whichguy] < 100 && timedirection[whichguy] == -1) {
      time[whichguy] += ((float)speed[targetframe[whichguy]][targetanim[whichguy]] / 1000);
    }
    NextFrame(whichguy);
  }
  while (time[whichguy] < 0) {
    time[whichguy] += 100;
  }
  while (time[whichguy] > 100) {
    time[whichguy] -= 100;
  }
  sabrespin[whichguy] += multiplier;
  if (activity[whichguy] != climbrope && activity[whichguy] != onrope && activity[whichguy] != downrope) {
    if (activity[whichguy] == idle1) {
      targetanim[whichguy] = 0;
    }
    if (activity[whichguy] == idle2) {
      targetanim[whichguy] = 1;
    }
    if (activity[whichguy] == runleft && CheckAIKey(whichguy, kLeftKey[whichguy]) == 0) {
      activity[whichguy] = RangedRandom(1, 2);
      time[whichguy] = 0;
    }
    if (activity[whichguy] == runright && CheckAIKey(whichguy, kRightKey[whichguy]) == 0) {
      activity[whichguy] = RangedRandom(1, 2);
      time[whichguy] = 0;
    }
    if (activity[whichguy] == ducking && CheckAIKey(whichguy, kDownKey[whichguy]) == 0) {
      activity[whichguy] = RangedRandom(1, 2);
      time[whichguy] = 0;
    }
    if (activity[whichguy] == runleft) {
      targetanim[whichguy] = 2;
      guyx[whichguy] -= .6 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == runright) {
      targetanim[whichguy] = 2;
      guyx[whichguy] += .6 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == swordleftspin && frame[whichguy] <= 2) {
      guyx[whichguy] -= .3 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == swordrightspin && frame[whichguy] <= 2) {
      guyx[whichguy] += .3 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == leftroll && guyvely[whichguy] == 0 && guyvelx[whichguy] == 0) {
      targetanim[whichguy] = 8;
      guyx[whichguy] -= .6 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == rightroll && guyvely[whichguy] == 0 && guyvelx[whichguy] == 0) {
      targetanim[whichguy] = 8;
      guyx[whichguy] += .6 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == ducking) {
      targetanim[whichguy] = 3;
    }
    if (activity[whichguy] == falling) {
      targetanim[whichguy] = 4;
    }
  }

  if (activity[whichguy] == idle1 || activity[whichguy] == idle2) {
    if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
      if (facing[whichguy] == 1) {
        activity[whichguy] = swordidleright;
      }
      if (facing[whichguy] != 1) {
        activity[whichguy] = swordidleleft;
      }
      targetanim[whichguy] = 26;
    }
    if (itemnum[whichguy] == 6) {
      if (facing[whichguy] == 1) {
        activity[whichguy] = grenidleright;
      }
      if (facing[whichguy] != 1) {
        activity[whichguy] = grenidleleft;
      }
      targetanim[whichguy] = 43;
    }
  }
  guywillbe = guymapy[whichguy] - .2;
  // if (activity[whichguy]==shootleft&&targetframe[whichguy]==0&&anim[whichguy]==10){point=FindGunPoint(); MakeSprite(point.x, point.y, point.z, 255, spawnstars, 0, 2, 0, 0,0,0);}
  guymapx[whichguy] = (guyx[whichguy] + 595) / 10;
  guymapy[whichguy] = guyy[whichguy] / -20 - .5 + 40;
  a = (guyx[whichguy] + 595) / 10 + 1.2;
  b = (guyx[whichguy] + 595) / 10 - 1.2;

  if (activity[whichguy] == jetidle) {
    if (CheckAIKey(whichguy, kDownKey[whichguy]) == 0) {
      if (absolute(guyvely[whichguy]) < multiplier / slowspeed) {
        guyvely[whichguy] = 0;
      }
      if (guyvely[whichguy] < 0) {
        guyvely[whichguy] += multiplier / slowspeed;
      }
      if (guyvely[whichguy] > 0) {
        guyvely[whichguy] -= multiplier / slowspeed;
      }
    }
    if (absolute(guyvelx[whichguy]) < multiplier / slowspeed) {
      guyvelx[whichguy] = 0;
    }
    if (guyvelx[whichguy] < 0) {
      guyvelx[whichguy] += multiplier / slowspeed;
    }
    if (guyvelx[whichguy] > 0) {
      guyvelx[whichguy] -= multiplier / slowspeed;
    }
  }
  if (holding[whichguy] != 0) {
    holding[whichguy] += multiplier / 10;
  }
  if (activity[whichguy] == fallforwardsleft && targetframe[whichguy] <= 5 && guyvelx[whichguy] == 0) {
    guyx[whichguy] -= .6 * multiplier / 5 * size[whichguy];
  }
  if (activity[whichguy] == fallforwardsright && targetframe[whichguy] <= 5 && guyvelx[whichguy] == 0) {
    guyx[whichguy] += .6 * multiplier / 5 * size[whichguy];
  }
  if (activity[whichguy] == jetright) {
    guyvelx[whichguy] = (.4 + guyvelx[whichguy] / multiplier * 100) / (1 / multiplier * 100 + 1);
    if (CheckAIKey(whichguy, kUpKey[whichguy]) == 0 && CheckAIKey(whichguy, kDownKey[whichguy]) == 0) {
      if (absolute(guyvely[whichguy]) < multiplier / slowspeed) {
        guyvely[whichguy] = 0;
      }
      if (guyvely[whichguy] < 0) {
        guyvely[whichguy] += multiplier / slowspeed;
      }
      if (guyvely[whichguy] > 0) {
        guyvely[whichguy] -= multiplier / slowspeed;
      }
    }
  }
  if (activity[whichguy] == jetleft) {
    guyvelx[whichguy] = (-.4 + guyvelx[whichguy] / multiplier * 100) / (1 / multiplier * 100 + 1);
    if (CheckAIKey(whichguy, kUpKey[whichguy]) == 0 && CheckAIKey(whichguy, kDownKey[whichguy]) == 0) {
      if (absolute(guyvely[whichguy]) < multiplier / slowspeed) {
        guyvely[whichguy] = 0;
      }
      if (guyvely[whichguy] < 0) {
        guyvely[whichguy] += multiplier / slowspeed;
      }
      if (guyvely[whichguy] > 0) {
        guyvely[whichguy] -= multiplier / slowspeed;
      }
    }
  }
  if (activity[whichguy] == jetup || activity[whichguy] == jetright || activity[whichguy] == jetleft || activity[whichguy] == jetidle) {
    if (CheckAIKey(whichguy, kUpKey[whichguy]) == 1) {
      guyvely[whichguy] = (.4 + guyvely[whichguy] / multiplier * 100) / (1 / multiplier * 100 + 1);
    }
  }
  if (activity[whichguy] == jetup) {
    if (absolute(guyvely[whichguy]) < multiplier / slowspeed) {
      guyvelx[whichguy] = 0;
    }
    if (guyvelx[whichguy] < 0) {
      guyvelx[whichguy] += multiplier / slowspeed;
    }
    if (guyvelx[whichguy] > 0) {
      guyvelx[whichguy] -= multiplier / slowspeed;
    }
  }
  if (activity[whichguy] == jetright || activity[whichguy] == jetleft || activity[whichguy] == jetidle) {
    if (CheckAIKey(whichguy, kDownKey[whichguy]) == 1 && CheckAIKey(whichguy, kUpKey[whichguy]) == 0) {
      guyvely[whichguy] = (-.4 + guyvely[whichguy] / multiplier * 100) / (1 / multiplier * 100 + 1);
    }
  }
  if (activity[whichguy] == jetup && CheckAIKey(whichguy, kUpKey[whichguy]) == 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == jetright && CheckAIKey(whichguy, kRightKey[whichguy]) == 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == jetleft && CheckAIKey(whichguy, kLeftKey[whichguy]) == 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == jetup || activity[whichguy] == jetright || activity[whichguy] == jetleft || activity[whichguy] == jetidle) {
    usingjetpack[whichguy] = 1;
  }
  if (activity[whichguy] == jetup && activity[whichguy] == jetright && activity[whichguy] == jetleft && activity[whichguy] == jetidle) {
    usingjetpack[whichguy] = 0;
  }
  if (activity[whichguy] == deadfaceup && health[whichguy] > 0) {
    activity[whichguy] = getupfromback;
    targetframe[whichguy] = 1;
    frame[whichguy] = 0;
    targetanim[whichguy] = 24;
    anim[whichguy] = 24;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == deadfacedown && health[whichguy] > 0) {
    activity[whichguy] = getupfromfront;
    targetframe[whichguy] = 1;
    frame[whichguy] = 0;
    targetanim[whichguy] = 25;
    anim[whichguy] = 25;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 10) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 12) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 10 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 12 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && anim[whichguy] == 10 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && lightningdelay[whichguy] <= 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && anim[whichguy] == 12 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && lightningdelay[whichguy] <= 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 10 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 12 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 10 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 12 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 10) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootright && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 12) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 31) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 32) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 31 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 32 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 31 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 32 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 31 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 32 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 31) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootright && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 32) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && usingjetpack[whichguy] == 0) {
    activity[whichguy] = falling;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && usingjetpack[whichguy] == 0) {
    activity[whichguy] = falling;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && usingjetpack[whichguy] != 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && usingjetpack[whichguy] != 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 30 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 30 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && anim[whichguy] == 30 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && lightningdelay[whichguy] <= 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && anim[whichguy] == 30 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && lightningdelay[whichguy] <= 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 3 && anim[whichguy] == 30 && itemnum[whichguy] == 5 && ammo[whichguy] > 0 && time[whichguy] >= 70) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 3 && anim[whichguy] == 30 && itemnum[whichguy] == 5 && ammo[whichguy] > 0 && time[whichguy] >= 70) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30) {
    activity[whichguy] = falling;
    if (usingjetpack[whichguy] == 1) {
      activity[whichguy] = jetidle;
      targetanim[whichguy] = 35;
    }
  }
  if (activity[whichguy] == shootright && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30) {
    activity[whichguy] = falling;
    if (usingjetpack[whichguy] == 1) {
      activity[whichguy] = jetidle;
      targetanim[whichguy] = 35;
    }
  }
  if (activity[whichguy] == climbrope && CheckAIKey(whichguy, kUpKey[whichguy]) == 0) {
    activity[whichguy] = onrope;
  }
  if (activity[whichguy] == downrope && CheckAIKey(whichguy, kDownKey[whichguy]) == 0) {
    activity[whichguy] = onrope;
  }
  if (activity[whichguy] == climbrope) {
    guyy[whichguy] += multiplier / 20 * size[whichguy];
  }
  // if (activity[whichguy]==painoneleft&&anim[whichguy]==13&&targetframe[whichguy]==0){activity[whichguy]=landonback; guyx[whichguy]-=7*size[whichguy]; targetanim[whichguy]=14; anim[whichguy]=14; targetframe[whichguy]=0; frame[whichguy]=0; time[whichguy]=100; if(Map[guymapx[whichguy]][guymapy[whichguy]]!=0&&Map[guymapx[whichguy]][guymapy[whichguy]]!=3&&activity[whichguy]!=climbrope&&activity[whichguy]!=onrope&&activity[whichguy]!=downrope){playSound(SND_BREAK_ID,-guyvely[whichguy]*50+50); playSound(SND_BREAK2_ID,-guyvely[whichguy]*50+50);}}
  /*if (activity[whichguy]==swordthrownleft&&anim[whichguy]==21&&frame[whichguy]>=10&&Map[guymapx[whichguy]+2][guymapy[whichguy]]==0){activity[whichguy]=landonback; dead[whichguy]=1; time[whichguy]=0; guyx[whichguy]+=12; anim[whichguy]=14; targetanim[whichguy]=14; frame[whichguy]=1; targetframe[whichguy]=1;time[whichguy]=100; rotation[whichguy]*=-1; targetrotation[whichguy]*=-1; guyvelx[whichguy]=.06; guyvely[whichguy]=-.3;}
  if (activity[whichguy]==swordthrownleft&&anim[whichguy]==21&&frame[whichguy]>=10&&Map[guymapx[whichguy]+2][guymapy[whichguy]]!=0&&Map[guymapx[whichguy]+1][guymapy[whichguy]]==0){activity[whichguy]=landonback; dead[whichguy]=1; time[whichguy]=0; guyx[whichguy]+=12; anim[whichguy]=14; targetanim[whichguy]=14; frame[whichguy]=1; targetframe[whichguy]=1;time[whichguy]=100; rotation[whichguy]*=-1; targetrotation[whichguy]*=-1; guyvelx[whichguy]=.06; guyvely[whichguy]=-.3;}
  if (activity[whichguy]==swordthrownright&&anim[whichguy]==21&&frame[whichguy]>=10&&Map[guymapx[whichguy]-2][guymapy[whichguy]]==0){activity[whichguy]=landonback; dead[whichguy]=1; time[whichguy]=0; guyx[whichguy]-=12; anim[whichguy]=14; targetanim[whichguy]=14; frame[whichguy]=1; targetframe[whichguy]=1;time[whichguy]=100; rotation[whichguy]*=-1; targetrotation[whichguy]*=-1; guyvelx[whichguy]=-.06; guyvely[whichguy]=-.3;}
  if (activity[whichguy]==swordthrownright&&anim[whichguy]==21&&frame[whichguy]>=10&&Map[guymapx[whichguy]-2][guymapy[whichguy]]!=0&&Map[guymapx[whichguy]-1][guymapy[whichguy]]==0){activity[whichguy]=landonback; dead[whichguy]=1; time[whichguy]=0; guyx[whichguy]-=12; anim[whichguy]=14; targetanim[whichguy]=14; frame[whichguy]=1; targetframe[whichguy]=1;time[whichguy]=100; rotation[whichguy]*=-1; targetrotation[whichguy]*=-1; guyvelx[whichguy]=-.06; guyvely[whichguy]=-.3;}*/
  if (activity[whichguy] == swordthrownleft && anim[whichguy] == 21 && frame[whichguy] >= 10 /*&&Map[a][guymapy[whichguy]]!=1&&Map[a][guymapy[whichguy]]!=2*/) {
    activity[whichguy] = landonback;
    time[whichguy] = 0;
    guyx[whichguy] += 12;
    anim[whichguy] = 14;
    targetanim[whichguy] = 14;
    frame[whichguy] = 1;
    targetframe[whichguy] = 1;
    time[whichguy] = 100;
    rotation[whichguy] *= -1;
    targetrotation[whichguy] *= -1;
    guyvelx[whichguy] = .06;
    guyvely[whichguy] = -.3;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == swordthrownright && anim[whichguy] == 21 && frame[whichguy] >= 10 /*&&Map[b][guymapy[whichguy]]!=1&&Map[b][guymapy[whichguy]]!=2*/) {
    activity[whichguy] = landonback;
    time[whichguy] = 0;
    guyx[whichguy] -= 12;
    anim[whichguy] = 14;
    targetanim[whichguy] = 14;
    frame[whichguy] = 1;
    targetframe[whichguy] = 1;
    time[whichguy] = 100;
    rotation[whichguy] *= -1;
    targetrotation[whichguy] *= -1;
    guyvelx[whichguy] = -.06;
    guyvely[whichguy] = -.3;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == swordthrowleft && anim[whichguy] == 20 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }

  if (activity[whichguy] == swordthrowright && anim[whichguy] == 20 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == jumpstraight) {
    targetanim[whichguy] = 6;
  }
  if (activity[whichguy] == wallhit && targetframe[whichguy] == 0 && anim[whichguy] == 11) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == jumpstraight && targetframe[whichguy] == 0 && anim[whichguy] == 6) {
    activity[whichguy] = falling;
    guyvely[whichguy] = jumpstrength / 5;
  }
  if (activity[whichguy] == leftflip && targetframe[whichguy] < 4 && guyvely[whichguy] == 0) {
    guyvely[whichguy] = jumpstrength / 5;
    guyvelx[whichguy] = -.2;
  }
  if (activity[whichguy] == leftflip && targetframe[whichguy] == 0 && anim[whichguy] == 7 && frame[whichguy] == 12) {
    activity[whichguy] = falling;
    targetframe[whichguy] = 2;
    targetanim[whichguy] = 4;
  }
  if (activity[whichguy] == leftflip && targetframe[whichguy] == 12 && anim[whichguy] == 7 && frame[whichguy] == 11) {
    frame[whichguy] = 12;
    targetframe[whichguy] = 12;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == rightflip && targetframe[whichguy] < 4 && guyvely[whichguy] == 0) {
    guyvely[whichguy] = jumpstrength / 5;
    guyvelx[whichguy] = .2;
  }
  if (activity[whichguy] == rightflip && targetframe[whichguy] == 0 && anim[whichguy] == 7 && frame[whichguy] == 12) {
    activity[whichguy] = falling;
    targetframe[whichguy] = 2;
    targetanim[whichguy] = 4;
  }
  if (activity[whichguy] == rightflip && targetframe[whichguy] == 12 && anim[whichguy] == 7 && frame[whichguy] == 11) {
    frame[whichguy] = 12;
    targetframe[whichguy] = 12;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == hitwallright && targetframe[whichguy] == 0) {
    time[whichguy] = 0;
    activity[whichguy] = deadfacedown;
    if (health[whichguy] > 0 && verydead == 0) {
      activity[whichguy] = getupfromfront;
      targetframe[whichguy] = 1;
      frame[whichguy] = 0;
      targetanim[whichguy] = 25;
      anim[whichguy] = 25;
      time[whichguy] = 100;
    }
  }
  if (activity[whichguy] == hitwallleft && targetframe[whichguy] == 0) {
    time[whichguy] = 0;
    activity[whichguy] = deadfacedown;
    if (health[whichguy] > 0 && verydead == 0) {
      activity[whichguy] = getupfromfront;
      targetframe[whichguy] = 1;
      frame[whichguy] = 0;
      targetanim[whichguy] = 25;
      anim[whichguy] = 25;
      time[whichguy] = 100;
    }
  }
  if (activity[whichguy] == deadfacedown || activity[whichguy] == deadfaceup) {
    if (health[whichguy] > 0) {
      time[whichguy] = 0;
      targetframe[whichguy] = 2;
      targetanim[whichguy] = 3;
      activity[whichguy] = ducking;
    }
  }
  if (activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft) {
    targetanim[whichguy] = 26;
  }
  if (activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
    targetanim[whichguy] = 43;
  }
  // going down rope stuff
  if (activity[whichguy] == downrope) {
    guyy[whichguy] -= multiplier / 7 * size[whichguy];
    if (Map[guymapx[whichguy]][guymapy[whichguy]] == 1 && Map[guymapx[whichguy]][guywillbe] == 3) {
      activity[whichguy] = falling;
      guyvely[whichguy] = -.2;
      targetframe[whichguy] = 0;
    }
    b = -1;
    for (a = 0; a < numplayers; a++) {
      if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a] - 5) < 5 && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
        b = a;
      }
    }
    if (b != -1) {
      activity[b] = falling;
      targetframe[b] = 0;
      guyvely[b] = -.1;
      guyy[b] -= .2;
    }
  }

  if (guyy[whichguy] > 390 && guyvely[whichguy] >= 0 && cube == 1) {
    guyvely[whichguy] *= -.1;
    guyy[whichguy] = 390;
  }
  // if(guyy[whichguy]>390&&guyvely[whichguy]>=0&&cube==0){jetpack[whichguy]=0;}
  guymapx[whichguy] = (guyx[whichguy] + 595) / 10;
  guymapy[whichguy] = guyy[whichguy] / -20 - .5 + 40;
  guywillbe = (guyy[whichguy] - guyvely[whichguy] + 8) / -20 - .5 + 40;
  // guywillbe=guymapy[whichguy];
  // height=initialvelocity*time-gravity*time^2
  if (activity[whichguy] != climbrope && activity[whichguy] != onrope && activity[whichguy] != downrope && guymapx[whichguy] < 100 && guymapx[whichguy] >= 0 && guymapy[whichguy] < 100 && guymapy[whichguy] >= 0) {
    if (activity[whichguy] != jetidle && activity[whichguy] != jetleft && activity[whichguy] != jetright && activity[whichguy] != jetup && usingjetpack[whichguy] == 0 && activity[whichguy] != jetimpaledright && activity[whichguy] != jetimpaledleft) {
      if (activity[whichguy] == runleft || activity[whichguy] == leftroll || activity[whichguy] == swordleftspin) {
        if (Map[guymapx[whichguy]][guymapy[whichguy]] == 0 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3) {
          guyvelx[whichguy] = -.1;
        }
      }
      if (activity[whichguy] == runright || activity[whichguy] == rightroll || activity[whichguy] == swordrightspin) {
        if (Map[guymapx[whichguy]][guymapy[whichguy]] == 0 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3) {
          guyvelx[whichguy] = .1;
        }
      }
      if (Map[guymapx[whichguy]][guywillbe] == 0 || Map[guymapx[whichguy]][guymapy[whichguy]] == 0 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3 || Map[guymapx[whichguy]][guywillbe] == 3 || guyvely[whichguy] > 0 || guywillbe != guymapy[whichguy] || fallin[whichguy] == 1 || guyy[whichguy] != (guymapy[whichguy] - 39) * -20 + .5) {
        guyvely[whichguy] -= gravity * multiplier / 40;
        if (activity[whichguy] != falling && anim[whichguy] != 7 && anim[whichguy] != 8) {
          if (activity[whichguy] != deadfaceup && activity[whichguy] != landonback && activity[whichguy] != deadfacedown && activity[whichguy] != jetimpaledright && activity[whichguy] != jetimpaledleft && activity[whichguy] != fallbackwardsright && activity[whichguy] != fallbackwardsleft && activity[whichguy] != fallforwardsright && activity[whichguy] != fallforwardsleft && activity[whichguy] != splat && activity[whichguy] != hitwallright && activity[whichguy] != hitwallleft && anim[whichguy] != 30 && targetanim[whichguy] != 30) {
            activity[whichguy] = falling;
            targetframe[whichguy] = 0;
          }
          fallin[whichguy] = 1;
        }
        if (activity[whichguy] == landonback && rotation[whichguy] == -90 && guyvelx[whichguy] == 0 && Walls[guymapx[whichguy]][guymapy[whichguy]] == 0) {
          guyvelx[whichguy] = .1;
        }
        if (activity[whichguy] == landonback && rotation[whichguy] == 90 && guyvelx[whichguy] == 0 && Walls[guymapx[whichguy] - 1][guymapy[whichguy]] == 0) {
          guyvelx[whichguy] = -.1;
        }
      }
    }
    b = -1;
    for (a = 0; a < numplayers; a++) {
      if (absolute(guyx[whichguy] - guyx[a]) < 5 && absolute(guyy[whichguy] - guyy[a]) < guyvely[whichguy] * multiplier / 10 + 10 && a != whichguy && guyvely[whichguy] < 0 && guyvely[whichguy] < guyvely[a] && guyvely[whichguy] < -.1 && guyy[whichguy] > guyy[a] && activity[a] != falling) {
        b = a;
      }
    }
    if (b == whichguy) {
      b = -1;
    }
    /*if (b!=-1){
            if(activity[b]==deadfaceup||activity[b]==deadfacedown){
            if(Map[guymapx[b]][guymapy[b]]==1||Map[guymapx[b]][guymapy[b]]==2){
                    usingjetpack[b]=0;
                    time[b]=0;
                    frame[b]=3;
                    targetframe[b]=2;
                    targetanim[b]=2;
                    anim[b]=3;
                    guyy[b]=(guymapy[b]-39)*-20+.5;
                    nosound=0;
                    fallin[b]=0;
                    if(activity[b]==deadfacedown){health[b]+=guyvely[b]*70; activity[b]=splat;anim[b]=9; targetframe[b]=3; frame[b]=3; time[b]=100; targetanim[b]=9; playSound(SND_BREAK_ID,-guyvely[b]*50+50); playSound(SND_BREAK2_ID,-guyvely[b]*50+50);}
                    if(activity[b]==deadfaceup){health[b]+=guyvely[b]*70; activity[b]=landonback;anim[b]=14; targetframe[b]=1; frame[b]=1; time[b]=100; targetanim[b]=14; playSound(SND_BREAK_ID,-guyvely[b]*50+50); playSound(SND_BREAK2_ID,-guyvely[b]*50+50);}
                    guyvelx[b]=0;
                    guyvely[b]=0;
            }
            }
    }*/
    if (b != -1 && guyvely[whichguy] < -.3 && dead[b] == 0 && attach[whichguy] == -1) {
      guyvely[b] = guyvely[whichguy];
      guyvely[whichguy] /= 2;
      activity[b] = falling;
      usingjetpack[b] = 0;
      guyy[b] = guyy[whichguy] - 10;
      if (Map[guymapx[b]][guymapy[b]] == 1 || Map[guymapx[b]][guymapy[b]] == 2) {
        usingjetpack[b] = 0;
        time[b] = 0;
        frame[b] = 3;
        targetframe[b] = 3;
        targetanim[b] = 3;
        anim[b] = 3;
        guyy[b] = (guymapy[b] - 39) * -20 + .5;
        nosound = 0;
        fallin[b] = 0;
        if (guyvelx[whichguy] > 0) {
          targetrotation[b] = 90;
        }
        if (guyvelx[whichguy] < 0) {
          targetrotation[b] = -90;
        }
        health[b] += guyvely[b] * 70;
        activity[b] = splat;
        anim[b] = 9;
        targetframe[b] = 0;
        frame[b] = 0;
        time[b] = 100;
        targetanim[b] = 9;
        playSound(SND_BREAK_ID, -guyvely[b] * 50 + 50);
        playSound(SND_BREAK2_ID, -guyvely[b] * 50 + 50);
        guyvelx[b] = 0;
        guyvely[b] = 0;
      }
    }
    for (x = 0; x < 10; x++) {
      guyy[whichguy] += guyvely[whichguy] * multiplier / 10;
      guymapx[whichguy] = (guyx[whichguy] + 595) / 10;
      guymapy[whichguy] = guyy[whichguy] / -20 - .5 + 40;
      guywillbe = (guyy[whichguy] - guyvely[whichguy] / 10 + 8) / -20 - .5 + 40;

      if (activity[whichguy] == falling || activity[whichguy] == leftflip || activity[whichguy] == rightflip || activity[whichguy] == rightroll || activity[whichguy] == leftroll || fallin[whichguy] == 1 || activity[whichguy] == jetup || activity[whichguy] == jetright || activity[whichguy] == jetleft || activity[whichguy] == jetidle || usingjetpack[whichguy] == 1) {
        if (Map[guymapx[whichguy]][guywillbe] != 0 && Map[guymapx[whichguy]][guywillbe] != 3 && Map[guymapx[whichguy]][guywillbe] != 3 && guyvely[whichguy] < 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 3 && guywillbe == guymapy[whichguy]) {
          /*if(activity[whichguy]==falling){
                  frame[whichguy]=2;
                  anim[whichguy]=3;
                  time=70;
          }*/
          if (activity[whichguy] != jetimpaleright && activity[whichguy] != jetimpaleleft) {
            b = -1;
            for (a = 0; a < numplayers; a++) {
              if (absolute(guyx[whichguy] - guyx[a]) < 7 && absolute(guyy[whichguy] - guyy[a]) < guyvely[whichguy] * multiplier / 10 + 10 && a != whichguy && guyvely[whichguy] < 0 && guyvely[whichguy] < guyvely[a] && guyvely[whichguy] < -.1 && guyy[whichguy] > guyy[a] && activity[a] != falling) {
                b = a;
              }
            }
            if (b == whichguy) {
              b = -1;
            }
            if (b != -1 && activity[b] != jetimpaleleft && activity[b] != jetimpaleright) {
              if (activity[b] == deadfaceup || activity[b] == deadfacedown) {
                if (Map[guymapx[b]][guymapy[b]] == 1 || Map[guymapx[b]][guymapy[b]] == 2) {
                  guyvely[b] = guyvely[whichguy];
                  guyvely[whichguy] *= .5;
                  usingjetpack[b] = 0;
                  time[b] = 0;
                  frame[b] = 3;
                  targetframe[b] = 2;
                  targetanim[b] = 2;
                  anim[b] = 3;
                  guyy[b] = (guymapy[b] - 39) * -20 + .5;
                  nosound = 0;
                  fallin[b] = 0;
                  if (activity[b] == deadfacedown) {
                    health[b] += guyvely[b] * 70;
                    activity[b] = splat;
                    anim[b] = 9;
                    targetframe[b] = 3;
                    frame[b] = 3;
                    time[b] = 100;
                    targetanim[b] = 9;
                    playSound(SND_BREAK_ID, -guyvely[b] * 50 + 50);
                    playSound(SND_BREAK2_ID, -guyvely[b] * 50 + 50);
                  }
                  if (activity[b] == deadfaceup) {
                    health[b] += guyvely[b] * 70;
                    activity[b] = landonback;
                    anim[b] = 14;
                    targetframe[b] = 1;
                    frame[b] = 1;
                    time[b] = 100;
                    targetanim[b] = 14;
                    playSound(SND_BREAK_ID, -guyvely[b] * 50 + 50);
                    playSound(SND_BREAK2_ID, -guyvely[b] * 50 + 50);
                  }
                  guyvelx[b] = 0;
                  guyvely[b] = 0;
                }
              }
            }
            usingjetpack[whichguy] = 0;
            time[whichguy] = 0;
            a = anim[whichguy];
            c = activity[whichguy];
            if (activity[whichguy] != fallforwardsright && activity[whichguy] != fallforwardsleft) {
              frame[whichguy] = 2;
              targetframe[whichguy] = 2;
              targetanim[whichguy] = 3;
              anim[whichguy] = 3;
            }
            if (activity[whichguy] != deadfaceup && activity[whichguy] != deadfacedown && activity[whichguy] != landonback && activity[whichguy] != splat && activity[whichguy] != fallbackwardsright && activity[whichguy] != fallbackwardsleft && activity[whichguy] != fallforwardsright && activity[whichguy] != fallforwardsleft && activity[whichguy] != hitwallleft && activity[whichguy] != hitwallright && activity[whichguy] != jetimpaledleft && activity[whichguy] != jetimpaledright) {
              activity[whichguy] = ducking;
            }
            // if(CheckAIKey( whichguy, kLeftKey[whichguy] )&&dead[whichguy]==0){activity[whichguy]=leftroll;targetframe[whichguy]=2;}
            // if(CheckAIKey( whichguy, kRightKey[whichguy] )&&dead[whichguy]==0){activity[whichguy]=rightroll;targetframe[whichguy]=2;}
            if (guyvely[whichguy] < -.7 && c != jetimpaleleft && c != jetimpaleright && guyvelx[whichguy] < 0 && dead[whichguy] == 0) {
              activity[whichguy] = leftroll;
              targetframe[whichguy] = 2;
            }
            if (guyvely[whichguy] < -.7 && c != jetimpaleleft && c != jetimpaleright && guyvelx[whichguy] > 0 && dead[whichguy] == 0) {
              activity[whichguy] = rightroll;
              targetframe[whichguy] = 2;
            }
            if (guyvely[whichguy] < -1) {
              health[whichguy] += guyvely[whichguy] * 70;
              activity[whichguy] = splat;
              anim[whichguy] = 9;
              targetframe[whichguy] = 0;
              frame[whichguy] = 0;
              time[whichguy] = 100;
              targetanim[whichguy] = 9;
              playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
              playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
            }
            if (activity[whichguy] == deadfacedown || activity[whichguy] == fallforwardsright || activity[whichguy] == fallforwardsleft || activity[whichguy] == hitwallright || activity[whichguy] == hitwallleft) {
              health[whichguy] -= 10;
              if (activity[whichguy] != fallforwardsright && activity[whichguy] != fallforwardsleft) {
                activity[whichguy] = splat;
                anim[whichguy] = 9;
                targetframe[whichguy] = 2;
                frame[whichguy] = 0;
                time[whichguy] = 100;
                targetanim[whichguy] = 9;
              }
              playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
              playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
            }
            if (activity[whichguy] == deadfaceup || activity[whichguy] == fallbackwardsright || activity[whichguy] == fallbackwardsleft || activity[whichguy] == landonback) {
              activity[whichguy] = landonback;
              if (a == 37) {
                targetrotation[whichguy] *= -1;
                rotation[whichguy] *= -1;
              }
              anim[whichguy] = 14;
              targetframe[whichguy] = 1;
              frame[whichguy] = 0;
              time[whichguy] = 100;
              targetanim[whichguy] = 14;
              playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
              playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
            }
            if (activity[whichguy] == ducking && nosound == 0 && invisible[whichguy] == 0) {
              playSound(SND_LAND_ID, -guyvely[whichguy] * 100 + 100);
            }
            if (activity[whichguy] == ducking && nosound == 0 && invisible[whichguy] == 1) {
              playSound(SND_LAND_ID, -guyvely[whichguy] * 10 + 10);
            }
            guyvelx[whichguy] = 0;
            guyvely[whichguy] = 0;
          }
          if (c == jetimpaleright || c == jetimpaleleft || activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaleleft) {
            guyvely[whichguy] = .005;
            if (c == jetimpaleleft || c == jetimpaleright) {
              activity[whichguy] = c;
            }
          }
          // if(activity[whichguy]!=landonback&&activity[whichguy]!=fallbackwardsright){
          guyy[whichguy] = (guymapy[whichguy] - 39) * -20 + .5;
          nosound = 0;
          fallin[whichguy] = 0;
        }
      }
    }
  }
  slide += multiplier / 100;
  if (slide > 2000) {
    slide = 1000;
  }
  guyx[whichguy] += guyvelx[whichguy] * multiplier;
  if (dead[whichguy] == 0 /*&&activity[whichguy]!=fallbackwardsright&&activity[whichguy]!=fallbackwardsleft&&activity[whichguy]!=landonback&&activity[whichguy]!=deadfaceup&&activity[whichguy]!=deadfacedown*/) {
    a = (guyx[whichguy] + 595) / 10 - .55;
    b = guyy[whichguy] / -20 - .5 + 40;
    c = (oldguyx[whichguy] + 595) / 10 - .55;
    d = (guyy[whichguy] - 10) / -20 - .5 + 40;
    f = 0;
    g = a - c;
    if (g == 1) {
      g = 0;
    }
    for (e = 0; e <= g; e++) {
      if (a > c && Walls[c + e + 1][b] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] -= .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] == 0) {
          targetanim[whichguy] = 11;
          activity[whichguy] = wallhit;
          targetframe[whichguy] = 0;
          time[whichguy] = 100;
        }
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = leftroll;
          anim[whichguy] = 8;
          targetanim[whichguy] = 8;
          guyvelx[whichguy] = guyvelx[whichguy] * -.5;
          targetframe[whichguy] = 1;
          frame[whichguy] = 1;
          time[whichguy] = 100;
        }
        f = 1;
      }
      if (a > c && Walls[c + e + 1][d] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] -= .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] == 0) {
          targetanim[whichguy] = 11;
          activity[whichguy] = wallhit;
          targetframe[whichguy] = 0;
          time[whichguy] = 100;
        }
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = leftroll;
          anim[whichguy] = 8;
          targetanim[whichguy] = 8;
          guyvelx[whichguy] = guyvelx[whichguy] * -.5;
          targetframe[whichguy] = 1;
          frame[whichguy] = 1;
          time[whichguy] = 100;
        }
        f = 1;
      }
    }
    a = (guyx[whichguy] + 595) / 10 - .3;
    b = guyy[whichguy] / -20 - .5 + 40;
    c = (oldguyx[whichguy] + 595) / 10 - .3;
    d = (guyy[whichguy] - 10) / -20 - .5 + 40;
    f = 0;
    g = c - a;
    if (g == 1) {
      g = 0;
    }
    for (e = 0; e <= g; e++) {
      if (a < c && Walls[c - e - 1][b] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] += .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] == 0) {
          targetanim[whichguy] = 11;
          activity[whichguy] = wallhit;
          targetframe[whichguy] = 0;
          time[whichguy] = 100;
        }
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = rightroll;
          anim[whichguy] = 8;
          targetanim[whichguy] = 8;
          guyvelx[whichguy] = guyvelx[whichguy] * -.5;
          targetframe[whichguy] = 1;
          frame[whichguy] = 1;
          time[whichguy] = 100;
        }
        f = 1;
      }
      if (a < c && Walls[c - e - 1][d] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] += .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] == 0) {
          targetanim[whichguy] = 11;
          activity[whichguy] = wallhit;
          targetframe[whichguy] = 0;
          time[whichguy] = 100;
        }
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = rightroll;
          anim[whichguy] = 8;
          targetanim[whichguy] = 8;
          guyvelx[whichguy] = guyvelx[whichguy] * -.5;
          targetframe[whichguy] = 1;
          frame[whichguy] = 1;
          time[whichguy] = 100;
        }
        f = 1;
      }
    }
  }
  if (dead[whichguy] == 1) {
    a = (guyx[whichguy] + 595) / 10 - .55;
    b = guyy[whichguy] / -20 - .5 + 40;
    c = (oldguyx[whichguy] + 595) / 10 - .55;
    d = (guyy[whichguy] - 10) / -20 - .5 + 40;
    f = 0;
    g = a - c;
    if (g == 1) {
      g = 0;
    }
    for (e = 0; e <= g; e++) {
      if (a > c && Walls[c + e + 1][b] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] -= .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = fallbackwardsright;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          anim[whichguy] = 13;
          targetanim[whichguy] = 13;
        }
        time[whichguy] = 100;
        guyvelx[whichguy] = guyvelx[whichguy] * -.5;
        f = 1;
      }
      if (a > c && Walls[c + e + 1][d] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] -= .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = fallbackwardsright;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          anim[whichguy] = 13;
          targetanim[whichguy] = 13;
        }
        time[whichguy] = 100;
        guyvelx[whichguy] = guyvelx[whichguy] * -.5;
        f = 1;
      }
    }
    a = (guyx[whichguy] + 595) / 10 - .3;
    b = guyy[whichguy] / -20 - .5 + 40;
    c = (oldguyx[whichguy] + 595) / 10 - .3;
    d = (guyy[whichguy] - 10) / -20 - .5 + 40;
    f = 0;
    g = c - a;
    if (g == 1) {
      g = 0;
    }
    for (e = 0; e <= g; e++) {
      if (a < c && Walls[a][b] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] += .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = fallbackwardsleft;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          anim[whichguy] = 13;
          targetanim[whichguy] = 13;
        }
        time[whichguy] = 100;
        guyvelx[whichguy] = guyvelx[whichguy] * -.5;
        f = 1;
      }
      if (a < c && Walls[a][d] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] += .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = fallbackwardsleft;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          anim[whichguy] = 13;
          targetanim[whichguy] = 13;
        }
        time[whichguy] = 100;
        guyvelx[whichguy] = guyvelx[whichguy] * -.5;
        f = 1;
      }
    }
  }
  if (health[whichguy] <= 0) {
    dead[whichguy] = 1;
  }
  // if (guyx<-395){guyx+=multiplier/3; activity=rightroll; anim=8; targetanim=8; if(guyvelx[whichguy]!=0){guyvelx=.1;} targetframe=1; frame=1; time=100;}
  if (health[whichguy] <= 0 && oldhealth[whichguy] > 0) {
    deathcount[oldnum[whichguy]]++;
    if (autorespawn == 1) {
      restartRound();
    }
  }
  if (health[whichguy] < oldhealth[whichguy]) {
    usingjetpack[whichguy] = 0;
  }
  if (guymapy[whichguy] >= 99 || guymapx[whichguy] >= 99 || guymapx[whichguy] <= 1 || guyy[whichguy] > 390) {
    if (exists[whichguy] && cube == 0) {
      for (x = 0; x < 50; x++) {
        MakeSprite(guyx[whichguy], RangedRandom(guyy[whichguy] + 5, guyy[whichguy] + 20), 0, 200, deletestars, RangedRandom(1, 360), 10, RangedRandom(2, 5), 0, 0, 0);
      }
      deathcount[oldnum[whichguy]]++;
      RemovePlayer(whichguy);
      health[whichguy] -= 1000;
    }
  }
  oldhealth[whichguy] = health[whichguy];
  if (trail) {
    point = FindLeftGunPoint(whichguy);
    if (freezetime == 0)
      MakeSprite(point.x, point.y, point.z, 255, spawnstars, 0, 2, 0, 0, 0, 0);
    point = FindRightGunPoint(whichguy);
    if (freezetime == 0)
      MakeSprite(point.x, point.y, point.z, 255, spawnstars, 0, 2, 0, 0, 0, 0);
    /*if(jetpack[whichguy]==1){
            point=FindJetPackPos(whichguy);
            if(jetglownum[whichguy]==0){MakeSprite(point.x, point.y, point.z, 255, JetPackGlow, 0, 10, 0, 0,0,0); jetglownum[whichguy]=unusedsprite;}
            sprite[jetglownum[whichguy]].x=point.x;
            sprite[jetglownum[whichguy]].y=point.y;
            sprite[jetglownum[whichguy]].z=point.z;
    }*/
  }
  if (jetpack[whichguy] == 1 && usingjetpack[whichguy] == 1) {
    point = FindJetPackPos(whichguy);
    if (jetglownum[whichguy] == 0) {
      MakeSprite(point.x, point.y, point.z, 255, JetPackGlow, 0, 10, 0, 0, 0, 0);
      jetglownum[whichguy] = unusedsprite;
    }
    sprite[jetglownum[whichguy]].x = point.x;
    sprite[jetglownum[whichguy]].y = point.y;
    sprite[jetglownum[whichguy]].z = point.z;
    sprite[jetglownum[whichguy]].brightness = RangedRandom(50, 100);
    if (usingjetpack[whichguy] == 1) {
      sprite[jetglownum[whichguy]].brightness = RangedRandom(200, 255);
    }
    if (usingjetpack[whichguy] == 1 && activity[whichguy] == jetidle) {
      sprite[jetglownum[whichguy]].brightness = RangedRandom(100, 150);
    }
    jetsmokedelay[whichguy] -= multiplier;
  }
  if (jetpack[whichguy] == 0 || usingjetpack[whichguy] == 0) {
    if (jetglownum[whichguy] != 0) {
      sprite[jetglownum[whichguy]].type = 0;
      jetglownum[whichguy] = 0;
    }
  }
  // if(lightningfxdelay[whichguy]<=0){lightningfxdelay[whichguy]=7;}
  for (x = 0; x < numplayers; x++) {
    if (activity[x] != jetimpaledright && activity[x] != jetimpaledleft && attach[x] == whichguy) {
      attach[x] = -1;
    }
  }
}

void DoPlayerStuff(int whichguy);
void DoPlayerStuff(int whichguy) {
  unsigned char theKeyMap[16];
  lightningfxdelay[whichguy] -= multiplier;
  int x, y, a, b, c, d, e, f, g, verydead = 0;
  int slowspeed = 500;
  if (unlimitedammo) {
    ammo[whichguy] = 1000;
  }
  if (ammo[whichguy] < 0) {
    ammo[whichguy] = 0;
  }
  for (x = 0; x < maxswordtrail; x++) {
    SwordTrail[whichguy][0].brightness[x][3] -= multiplier / 30;
    if (SwordTrail[whichguy][0].brightness[x][3] < 0) {
      SwordTrail[whichguy][0].brightness[x][3] = 0;
    }
  }
  for (x = 0; x < maxswordtrail; x++) {
    SwordTrail[whichguy][1].brightness[x][3] -= multiplier / 30;
    if (SwordTrail[whichguy][1].brightness[x][3] < 0) {
      SwordTrail[whichguy][1].brightness[x][3] = 0;
    }
  }
  swordtraildelay[whichguy] -= multiplier / 5;
  if (swordtraildelay[whichguy] <= 0) {
    MakeNewSwordTrail(whichguy);
    swordtraildelay[whichguy] = .3;
  }

  if (health[whichguy] <= 0 && (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == jetidle || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == swordidleleft || activity[whichguy] == swordidleright)) {
    activity[whichguy] = splat;
    anim[whichguy] = 9;
    targetframe[whichguy] = 0;
    frame[whichguy] = 0;
    time[whichguy] = 100;
    targetanim[whichguy] = 9;
    playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
    playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
  }
  if (activity[whichguy] == impaleright || activity[whichguy] == impaleleft ||
      activity[whichguy] == swordrightthrust || activity[whichguy] == swordleftthrust ||
      activity[whichguy] == swordrightspin || activity[whichguy] == swordleftspin) {
    swordtrailtoggle[whichguy][0] = 1;
    swordtrailtoggle[whichguy][1] = 0;
  } else {
    swordtrailtoggle[whichguy][0] = 0;
    swordtrailtoggle[whichguy][1] = 0;
  }

  if (activity[whichguy] == swordthrowright || activity[whichguy] == swordthrowleft ||
      activity[whichguy] == swordrightparry || activity[whichguy] == swordleftparry ||
      activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaleleft ||
      activity[whichguy] == duckimpaleright || activity[whichguy] == duckimpaleleft) {
    swordtrailtoggle[whichguy][0] = 1;
    if (itemnum[whichguy] == 3) {
      swordtrailtoggle[whichguy][1] = 1;
    }
  }

  if (constantswordtrail) {
    swordtrailtoggle[whichguy][0] = 1;
    swordtrailtoggle[whichguy][1] = 1;
  }

  UpdateSwordTrail(whichguy, unusedswordtrail[whichguy]);
  for (x = 0; x < 16; x++) {
    smokingbodydelay[whichguy][x] -= multiplier * RangedRandom(50, 100) / 100;
    if (smokingbody[whichguy][x] > 0) {
      if (smokingbodydelay[whichguy][x] < 0) {
        point = FindBodyPart(whichguy, x);
        MakeSprite(point.x, point.y, point.z, RangedRandom(10, 20) + smokingbody[whichguy][x] / 5, smokesprite, RangedRandom(0, 360), RangedRandom(0, 4) + 6, 0, .1, .4, 0);
        smokingbodydelay[whichguy][x] = RangedRandom(8, 15);
        smokingbody[whichguy][x] -= 2;
        sprite[unusedsprite].type2 = 1;
      }
    }
  }
  if (frame[whichguy] == 2) {
    lightningdelay[whichguy] -= multiplier;
  }
  delaytime[whichguy] -= multiplier;
  int guywillbe;
  oldguyx[whichguy] = guyx[whichguy];
  oldguyy[whichguy] = guyy[whichguy];
  if (cloaktime[whichguy] < 100) {
    cloaktime[whichguy] += multiplier;
    if (cloaktime[whichguy] >= 100 && invisible[whichguy] == 1) {
      invisible[whichguy] = 2;
    }
    if (cloaktime[whichguy] >= 100 && invisible[whichguy] == 0) {
      invisible[whichguy] = 1;
    }
    if (invisible[whichguy] == 2) {
      invisible[whichguy] = 0;
    }
  }
  if (cloaktime[whichguy] > 100) {
    cloaktime[whichguy] += multiplier;
  }
  if (activity[whichguy] == deadfacedown && dead[whichguy] == 1 && health[whichguy] <= 0) {
    verydead = 1;
  }
  if (activity[whichguy] == deadfaceup && dead[whichguy] == 1 && health[whichguy] <= 0) {
    verydead = 1;
  }
  if (dead[whichguy] == 1 && health[whichguy] <= 0 && invisible[whichguy] == 1 && cloaktime[whichguy] >= 100) {
    cloaktime[whichguy] = 0;
  }
  if (whichguy == 0) {
    verydeadshow = verydead;
  }
  if (verydead == 0 && activity[whichguy] != onrope && activity[whichguy] != downrope) {
    oldtime[whichguy] = time[whichguy];
    if (anim[whichguy] == 7 || anim[whichguy] == 8) {
      time[whichguy] += (((float)speed[frame[whichguy]][anim[whichguy]] / 1000)) * multiplier / 3;
    }
    if (anim[whichguy] == 7) {
      time[whichguy] += (((float)speed[frame[whichguy]][anim[whichguy]] / 1000)) * multiplier / 2;
    }
    if (time[whichguy] < 100 && timedirection[whichguy] == 1) {
      time[whichguy] += (((float)speed[frame[whichguy]][anim[whichguy]] / 1000)) * multiplier / 3;
    }
    if (time[whichguy] < 100 && timedirection[whichguy] == -1) {
      time[whichguy] += ((float)speed[targetframe[whichguy]][targetanim[whichguy]] / 1000);
    }
    NextFrame(whichguy);
  }
  while (time[whichguy] < 0) {
    time[whichguy] += 100;
  }
  while (time[whichguy] > 100) {
    time[whichguy] -= 100;
  }
  sabrespin[whichguy] += multiplier;
  if (activity[whichguy] != climbrope && activity[whichguy] != onrope && activity[whichguy] != downrope) {
    if (activity[whichguy] == idle1) {
      targetanim[whichguy] = 0;
    }
    if (activity[whichguy] == idle2) {
      targetanim[whichguy] = 1;
    }
    if (activity[whichguy] == runleft && isKeyDown(kLeftKey[whichguy]) == 0) {
      activity[whichguy] = RangedRandom(1, 2);
      time[whichguy] = 0;
    }
    if (activity[whichguy] == runright && isKeyDown(kRightKey[whichguy]) == 0) {
      activity[whichguy] = RangedRandom(1, 2);
      time[whichguy] = 0;
    }
    if (activity[whichguy] == ducking && isKeyDown(kDownKey[whichguy]) == 0) {
      activity[whichguy] = RangedRandom(1, 2);
      time[whichguy] = 0;
    }
    if (activity[whichguy] == runleft) {
      targetanim[whichguy] = 2;
      guyx[whichguy] -= .6 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == runright) {
      targetanim[whichguy] = 2;
      guyx[whichguy] += .6 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == swordleftspin && frame[whichguy] <= 2) {
      guyx[whichguy] -= .3 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == swordrightspin && frame[whichguy] <= 2) {
      guyx[whichguy] += .3 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == leftroll && guyvely[whichguy] == 0 && guyvelx[whichguy] == 0) {
      targetanim[whichguy] = 8;
      guyx[whichguy] -= .6 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == rightroll && guyvely[whichguy] == 0 && guyvelx[whichguy] == 0) {
      targetanim[whichguy] = 8;
      guyx[whichguy] += .6 * multiplier / 5 * size[whichguy];
    }
    if (activity[whichguy] == ducking) {
      targetanim[whichguy] = 3;
    }
    if (activity[whichguy] == falling) {
      targetanim[whichguy] = 4;
    }
  }

  if (activity[whichguy] == idle1 || activity[whichguy] == idle2) {
    if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
      if (facing[whichguy] == 1) {
        activity[whichguy] = swordidleright;
      }
      if (facing[whichguy] != 1) {
        activity[whichguy] = swordidleleft;
      }
      targetanim[whichguy] = 26;
    }
    if (itemnum[whichguy] == 6) {
      if (facing[whichguy] == 1) {
        activity[whichguy] = grenidleright;
      }
      if (facing[whichguy] != 1) {
        activity[whichguy] = grenidleleft;
      }
      targetanim[whichguy] = 43;
    }
  }
  guywillbe = guymapy[whichguy] - .2;
  // if (activity[whichguy]==shootleft&&targetframe[whichguy]==0&&anim[whichguy]==10){point=FindGunPoint(); MakeSprite(point.x, point.y, point.z, 255, spawnstars, 0, 2, 0, 0,0,0);}
  guymapx[whichguy] = (guyx[whichguy] + 595) / 10;
  guymapy[whichguy] = guyy[whichguy] / -20 - .5 + 40;
  a = (guyx[whichguy] + 595) / 10 + 1.2;
  b = (guyx[whichguy] + 595) / 10 - 1.2;

  if (activity[whichguy] == jetidle) {
    if (isKeyDown(kDownKey[whichguy]) == 0) {
      if (absolute(guyvely[whichguy]) < multiplier / slowspeed) {
        guyvely[whichguy] = 0;
      }
      if (guyvely[whichguy] < 0) {
        guyvely[whichguy] += multiplier / slowspeed;
      }
      if (guyvely[whichguy] > 0) {
        guyvely[whichguy] -= multiplier / slowspeed;
      }
    }
    if (absolute(guyvelx[whichguy]) < multiplier / slowspeed) {
      guyvelx[whichguy] = 0;
    }
    if (guyvelx[whichguy] < 0) {
      guyvelx[whichguy] += multiplier / slowspeed;
    }
    if (guyvelx[whichguy] > 0) {
      guyvelx[whichguy] -= multiplier / slowspeed;
    }
  }
  if (holding[whichguy] != 0) {
    holding[whichguy] += multiplier / 10;
  }
  if (activity[whichguy] == fallforwardsleft && targetframe[whichguy] <= 5 && guyvelx[whichguy] == 0) {
    guyx[whichguy] -= .6 * multiplier / 5 * size[whichguy];
  }
  if (activity[whichguy] == fallforwardsright && targetframe[whichguy] <= 5 && guyvelx[whichguy] == 0) {
    guyx[whichguy] += .6 * multiplier / 5 * size[whichguy];
  }
  if (activity[whichguy] == jetright) {
    guyvelx[whichguy] = (.4 + guyvelx[whichguy] / multiplier * 100) / (1 / multiplier * 100 + 1);
    if (isKeyDown(kUpKey[whichguy]) == 0 && isKeyDown(kDownKey[whichguy]) == 0) {
      if (absolute(guyvely[whichguy]) < multiplier / slowspeed) {
        guyvely[whichguy] = 0;
      }
      if (guyvely[whichguy] < 0) {
        guyvely[whichguy] += multiplier / slowspeed;
      }
      if (guyvely[whichguy] > 0) {
        guyvely[whichguy] -= multiplier / slowspeed;
      }
    }
  }
  if (activity[whichguy] == jetleft) {
    guyvelx[whichguy] = (-.4 + guyvelx[whichguy] / multiplier * 100) / (1 / multiplier * 100 + 1);
    if (isKeyDown(kUpKey[whichguy]) == 0 && isKeyDown(kDownKey[whichguy]) == 0) {
      if (absolute(guyvely[whichguy]) < multiplier / slowspeed) {
        guyvely[whichguy] = 0;
      }
      if (guyvely[whichguy] < 0) {
        guyvely[whichguy] += multiplier / slowspeed;
      }
      if (guyvely[whichguy] > 0) {
        guyvely[whichguy] -= multiplier / slowspeed;
      }
    }
  }
  if (activity[whichguy] == jetup || activity[whichguy] == jetright || activity[whichguy] == jetleft || activity[whichguy] == jetidle) {
    if (isKeyDown(kUpKey[whichguy]) == 1) {
      guyvely[whichguy] = (.4 + guyvely[whichguy] / multiplier * 100) / (1 / multiplier * 100 + 1);
    }
  }
  if (activity[whichguy] == jetup) {
    if (absolute(guyvely[whichguy]) < multiplier / slowspeed) {
      guyvelx[whichguy] = 0;
    }
    if (guyvelx[whichguy] < 0) {
      guyvelx[whichguy] += multiplier / slowspeed;
    }
    if (guyvelx[whichguy] > 0) {
      guyvelx[whichguy] -= multiplier / slowspeed;
    }
  }
  if (activity[whichguy] == jetright || activity[whichguy] == jetleft || activity[whichguy] == jetidle) {
    if (isKeyDown(kDownKey[whichguy]) == 1 && isKeyDown(kUpKey[whichguy]) == 0) {
      guyvely[whichguy] = (-.4 + guyvely[whichguy] / multiplier * 100) / (1 / multiplier * 100 + 1);
    }
  }
  if (activity[whichguy] == jetup && isKeyDown(kUpKey[whichguy]) == 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == jetright && isKeyDown(kRightKey[whichguy]) == 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == jetleft && isKeyDown(kLeftKey[whichguy]) == 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == jetup || activity[whichguy] == jetright || activity[whichguy] == jetleft || activity[whichguy] == jetidle) {
    usingjetpack[whichguy] = 1;
  }
  if (activity[whichguy] == jetup && activity[whichguy] == jetright && activity[whichguy] == jetleft && activity[whichguy] == jetidle) {
    usingjetpack[whichguy] = 0;
  }
  if (activity[whichguy] == deadfaceup && health[whichguy] > 0) {
    activity[whichguy] = getupfromback;
    targetframe[whichguy] = 1;
    frame[whichguy] = 0;
    targetanim[whichguy] = 24;
    anim[whichguy] = 24;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == deadfacedown && health[whichguy] > 0) {
    activity[whichguy] = getupfromfront;
    targetframe[whichguy] = 1;
    frame[whichguy] = 0;
    targetanim[whichguy] = 25;
    anim[whichguy] = 25;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 10) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 12) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 10 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 12 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && anim[whichguy] == 10 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && lightningdelay[whichguy] <= 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && anim[whichguy] == 12 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && lightningdelay[whichguy] <= 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 10 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 12 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 10 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 12 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 10) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootright && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 12) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 31) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 32) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 31 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 32 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 31 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 32 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 31 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 32 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 31) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootright && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 32) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && usingjetpack[whichguy] == 0) {
    activity[whichguy] = falling;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && usingjetpack[whichguy] == 0) {
    activity[whichguy] = falling;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && usingjetpack[whichguy] != 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && usingjetpack[whichguy] != 0) {
    activity[whichguy] = jetidle;
    targetanim[whichguy] = 35;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 0 && anim[whichguy] == 30 && itemnum[whichguy] == 4 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 30 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] > 3 && anim[whichguy] == 30 && itemnum[whichguy] == 5 && ammo[whichguy] > 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && anim[whichguy] == 30 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && lightningdelay[whichguy] <= 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && anim[whichguy] == 30 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && lightningdelay[whichguy] <= 0) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && isKeyDown(kRightShootKey[whichguy]) == 1 && targetframe[whichguy] == 3 && anim[whichguy] == 30 && itemnum[whichguy] == 5 && ammo[whichguy] > 0 && time[whichguy] >= 70) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootleft;
  }
  if (activity[whichguy] == shootright && isKeyDown(kLeftShootKey[whichguy]) == 1 && targetframe[whichguy] == 3 && anim[whichguy] == 30 && itemnum[whichguy] == 5 && ammo[whichguy] > 0 && time[whichguy] >= 70) {
    targetframe[whichguy] = 2;
    frame[whichguy] = 3;
    time[whichguy] = 100;
    activity[whichguy] = shootright;
  }
  if (activity[whichguy] == shootleft && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30) {
    activity[whichguy] = falling;
    if (usingjetpack[whichguy] == 1) {
      activity[whichguy] = jetidle;
      targetanim[whichguy] = 35;
    }
  }
  if (activity[whichguy] == shootright && ammo[whichguy] <= 0 && targetframe[whichguy] == 0 && anim[whichguy] == 30) {
    activity[whichguy] = falling;
    if (usingjetpack[whichguy] == 1) {
      activity[whichguy] = jetidle;
      targetanim[whichguy] = 35;
    }
  }
  if (activity[whichguy] == climbrope && isKeyDown(kUpKey[whichguy]) == 0) {
    activity[whichguy] = onrope;
  }
  if (activity[whichguy] == downrope && isKeyDown(kDownKey[whichguy]) == 0) {
    activity[whichguy] = onrope;
  }
  if (activity[whichguy] == climbrope) {
    guyy[whichguy] += multiplier / 20 * size[whichguy];
  }
  // if (activity[whichguy]==painoneleft&&anim[whichguy]==13&&targetframe[whichguy]==0){activity[whichguy]=landonback; guyx[whichguy]-=7*size[whichguy]; targetanim[whichguy]=14; anim[whichguy]=14; targetframe[whichguy]=0; frame[whichguy]=0; time[whichguy]=100; if(Map[guymapx[whichguy]][guymapy[whichguy]]!=0&&Map[guymapx[whichguy]][guymapy[whichguy]]!=3&&activity[whichguy]!=climbrope&&activity[whichguy]!=onrope&&activity[whichguy]!=downrope){playSound(SND_BREAK_ID,-guyvely[whichguy]*50+50); playSound(SND_BREAK2_ID,-guyvely[whichguy]*50+50);}}
  /*if (activity[whichguy]==swordthrownleft&&anim[whichguy]==21&&frame[whichguy]>=10&&Map[guymapx[whichguy]+2][guymapy[whichguy]]==0){activity[whichguy]=landonback; dead[whichguy]=1; time[whichguy]=0; guyx[whichguy]+=12; anim[whichguy]=14; targetanim[whichguy]=14; frame[whichguy]=1; targetframe[whichguy]=1;time[whichguy]=100; rotation[whichguy]*=-1; targetrotation[whichguy]*=-1; guyvelx[whichguy]=.06; guyvely[whichguy]=-.3;}
  if (activity[whichguy]==swordthrownleft&&anim[whichguy]==21&&frame[whichguy]>=10&&Map[guymapx[whichguy]+2][guymapy[whichguy]]!=0&&Map[guymapx[whichguy]+1][guymapy[whichguy]]==0){activity[whichguy]=landonback; dead[whichguy]=1; time[whichguy]=0; guyx[whichguy]+=12; anim[whichguy]=14; targetanim[whichguy]=14; frame[whichguy]=1; targetframe[whichguy]=1;time[whichguy]=100; rotation[whichguy]*=-1; targetrotation[whichguy]*=-1; guyvelx[whichguy]=.06; guyvely[whichguy]=-.3;}
  if (activity[whichguy]==swordthrownright&&anim[whichguy]==21&&frame[whichguy]>=10&&Map[guymapx[whichguy]-2][guymapy[whichguy]]==0){activity[whichguy]=landonback; dead[whichguy]=1; time[whichguy]=0; guyx[whichguy]-=12; anim[whichguy]=14; targetanim[whichguy]=14; frame[whichguy]=1; targetframe[whichguy]=1;time[whichguy]=100; rotation[whichguy]*=-1; targetrotation[whichguy]*=-1; guyvelx[whichguy]=-.06; guyvely[whichguy]=-.3;}
  if (activity[whichguy]==swordthrownright&&anim[whichguy]==21&&frame[whichguy]>=10&&Map[guymapx[whichguy]-2][guymapy[whichguy]]!=0&&Map[guymapx[whichguy]-1][guymapy[whichguy]]==0){activity[whichguy]=landonback; dead[whichguy]=1; time[whichguy]=0; guyx[whichguy]-=12; anim[whichguy]=14; targetanim[whichguy]=14; frame[whichguy]=1; targetframe[whichguy]=1;time[whichguy]=100; rotation[whichguy]*=-1; targetrotation[whichguy]*=-1; guyvelx[whichguy]=-.06; guyvely[whichguy]=-.3;}*/
  if (activity[whichguy] == swordthrownleft && anim[whichguy] == 21 && frame[whichguy] >= 10 /*&&Map[a][guymapy[whichguy]]!=1&&Map[a][guymapy[whichguy]]!=2*/) {
    activity[whichguy] = landonback;
    time[whichguy] = 0;
    guyx[whichguy] += 12;
    anim[whichguy] = 14;
    targetanim[whichguy] = 14;
    frame[whichguy] = 1;
    targetframe[whichguy] = 1;
    time[whichguy] = 100;
    rotation[whichguy] *= -1;
    targetrotation[whichguy] *= -1;
    guyvelx[whichguy] = .06;
    guyvely[whichguy] = -.3;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == swordthrownright && anim[whichguy] == 21 && frame[whichguy] >= 10 /*&&Map[b][guymapy[whichguy]]!=1&&Map[b][guymapy[whichguy]]!=2*/) {
    activity[whichguy] = landonback;
    time[whichguy] = 0;
    guyx[whichguy] -= 12;
    anim[whichguy] = 14;
    targetanim[whichguy] = 14;
    frame[whichguy] = 1;
    targetframe[whichguy] = 1;
    time[whichguy] = 100;
    rotation[whichguy] *= -1;
    targetrotation[whichguy] *= -1;
    guyvelx[whichguy] = -.06;
    guyvely[whichguy] = -.3;
    health[whichguy] -= 120;
  }
  if (activity[whichguy] == swordthrowleft && anim[whichguy] == 20 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }

  if (activity[whichguy] == swordthrowright && anim[whichguy] == 20 && targetframe[whichguy] == 0 && frame[whichguy] > 3) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == jumpstraight) {
    targetanim[whichguy] = 6;
  }
  if (activity[whichguy] == wallhit && targetframe[whichguy] == 0 && anim[whichguy] == 11) {
    activity[whichguy] = idle1;
  }
  if (activity[whichguy] == jumpstraight && targetframe[whichguy] == 0 && anim[whichguy] == 6) {
    activity[whichguy] = falling;
    guyvely[whichguy] = jumpstrength / 5;
  }
  if (activity[whichguy] == leftflip && targetframe[whichguy] < 4 && guyvely[whichguy] == 0) {
    guyvely[whichguy] = jumpstrength / 5;
    guyvelx[whichguy] = -.2;
  }
  if (activity[whichguy] == leftflip && targetframe[whichguy] == 0 && anim[whichguy] == 7 && frame[whichguy] == 12) {
    activity[whichguy] = falling;
    targetframe[whichguy] = 2;
    targetanim[whichguy] = 4;
  }
  if (activity[whichguy] == leftflip && targetframe[whichguy] == 12 && anim[whichguy] == 7 && frame[whichguy] == 11) {
    frame[whichguy] = 12;
    targetframe[whichguy] = 12;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == rightflip && targetframe[whichguy] < 4 && guyvely[whichguy] == 0) {
    guyvely[whichguy] = jumpstrength / 5;
    guyvelx[whichguy] = .2;
  }
  if (activity[whichguy] == rightflip && targetframe[whichguy] == 0 && anim[whichguy] == 7 && frame[whichguy] == 12) {
    activity[whichguy] = falling;
    targetframe[whichguy] = 2;
    targetanim[whichguy] = 4;
  }
  if (activity[whichguy] == rightflip && targetframe[whichguy] == 12 && anim[whichguy] == 7 && frame[whichguy] == 11) {
    frame[whichguy] = 12;
    targetframe[whichguy] = 12;
    time[whichguy] = 100;
  }
  if (activity[whichguy] == hitwallright && targetframe[whichguy] == 0) {
    time[whichguy] = 0;
    activity[whichguy] = deadfacedown;
    if (health[whichguy] > 0 && verydead == 0) {
      activity[whichguy] = getupfromfront;
      targetframe[whichguy] = 1;
      frame[whichguy] = 0;
      targetanim[whichguy] = 25;
      anim[whichguy] = 25;
      time[whichguy] = 100;
    }
  }
  if (activity[whichguy] == hitwallleft && targetframe[whichguy] == 0) {
    time[whichguy] = 0;
    activity[whichguy] = deadfacedown;
    if (health[whichguy] > 0 && verydead == 0) {
      activity[whichguy] = getupfromfront;
      targetframe[whichguy] = 1;
      frame[whichguy] = 0;
      targetanim[whichguy] = 25;
      anim[whichguy] = 25;
      time[whichguy] = 100;
    }
  }
  if (activity[whichguy] == deadfacedown || activity[whichguy] == deadfaceup) {
    if (health[whichguy] > 0) {
      time[whichguy] = 0;
      targetframe[whichguy] = 2;
      targetanim[whichguy] = 3;
      activity[whichguy] = ducking;
    }
  }
  if (activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft) {
    targetanim[whichguy] = 26;
  }
  if (activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
    targetanim[whichguy] = 43;
  }
  // going down rope stuff
  if (activity[whichguy] == downrope) {
    guyy[whichguy] -= multiplier / 7 * size[whichguy];
    if (Map[guymapx[whichguy]][guymapy[whichguy]] == 1 && Map[guymapx[whichguy]][guywillbe] == 3) {
      activity[whichguy] = falling;
      guyvely[whichguy] = -.2;
      targetframe[whichguy] = 0;
    }
    b = -1;
    for (a = 0; a < numplayers; a++) {
      if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a] - 5) < 5 && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
        b = a;
      }
    }
    if (b != -1) {
      activity[b] = falling;
      targetframe[b] = 0;
      guyvely[b] = -.1;
      guyy[b] -= .2;
    }
  }

  if (guyy[whichguy] > 390 && guyvely[whichguy] >= 0 && cube == 1) {
    guyvely[whichguy] *= -.1;
    guyy[whichguy] = 390;
  }
  // if(guyy[whichguy]>390&&guyvely[whichguy]>=0&&cube==0){jetpack[whichguy]=0;}
  guymapx[whichguy] = (guyx[whichguy] + 595) / 10;
  guymapy[whichguy] = guyy[whichguy] / -20 - .5 + 40;
  guywillbe = (guyy[whichguy] - guyvely[whichguy] + 8) / -20 - .5 + 40;
  // guywillbe=guymapy[whichguy];
  // height=initialvelocity*time-gravity*time^2
  if (activity[whichguy] != climbrope && activity[whichguy] != onrope && activity[whichguy] != downrope && guymapx[whichguy] < 100 && guymapx[whichguy] >= 0 && guymapy[whichguy] < 100 && guymapy[whichguy] >= 0) {
    if (activity[whichguy] != jetidle && activity[whichguy] != jetleft && activity[whichguy] != jetright && activity[whichguy] != jetup && usingjetpack[whichguy] == 0 && activity[whichguy] != jetimpaledright && activity[whichguy] != jetimpaledleft) {
      if (activity[whichguy] == runleft || activity[whichguy] == leftroll || activity[whichguy] == swordleftspin) {
        if (Map[guymapx[whichguy]][guymapy[whichguy]] == 0 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3) {
          guyvelx[whichguy] = -.1;
        }
      }
      if (activity[whichguy] == runright || activity[whichguy] == rightroll || activity[whichguy] == swordrightspin) {
        if (Map[guymapx[whichguy]][guymapy[whichguy]] == 0 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3) {
          guyvelx[whichguy] = .1;
        }
      }
      if (Map[guymapx[whichguy]][guywillbe] == 0 || Map[guymapx[whichguy]][guymapy[whichguy]] == 0 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3 || Map[guymapx[whichguy]][guywillbe] == 3 || guyvely[whichguy] > 0 || guywillbe != guymapy[whichguy] || fallin[whichguy] == 1 || guyy[whichguy] != (guymapy[whichguy] - 39) * -20 + .5) {
        guyvely[whichguy] -= gravity * multiplier / 40;
        if (activity[whichguy] != falling && anim[whichguy] != 7 && anim[whichguy] != 8) {
          if (activity[whichguy] != deadfaceup && activity[whichguy] != landonback && activity[whichguy] != deadfacedown && activity[whichguy] != jetimpaledright && activity[whichguy] != jetimpaledleft && activity[whichguy] != fallbackwardsright && activity[whichguy] != fallbackwardsleft && activity[whichguy] != fallforwardsright && activity[whichguy] != fallforwardsleft && activity[whichguy] != splat && activity[whichguy] != hitwallright && activity[whichguy] != hitwallleft && anim[whichguy] != 30 && targetanim[whichguy] != 30) {
            activity[whichguy] = falling;
            targetframe[whichguy] = 0;
          }
          fallin[whichguy] = 1;
        }
        if (activity[whichguy] == landonback && rotation[whichguy] == -90 && guyvelx[whichguy] == 0 && Walls[guymapx[whichguy]][guymapy[whichguy]] == 0) {
          guyvelx[whichguy] = .1;
        }
        if (activity[whichguy] == landonback && rotation[whichguy] == 90 && guyvelx[whichguy] == 0 && Walls[guymapx[whichguy] - 1][guymapy[whichguy]] == 0) {
          guyvelx[whichguy] = -.1;
        }
      }
    }
    b = -1;
    for (a = 0; a < numplayers; a++) {
      if (absolute(guyx[whichguy] - guyx[a]) < 5 && absolute(guyy[whichguy] - guyy[a]) < guyvely[whichguy] * multiplier / 10 + 10 && a != whichguy && guyvely[whichguy] < 0 && guyvely[whichguy] < guyvely[a] && guyvely[whichguy] < -.1 && guyy[whichguy] > guyy[a] && activity[a] != falling) {
        b = a;
      }
    }
    if (b == whichguy) {
      b = -1;
    }
    /*if (b!=-1){
            if(activity[b]==deadfaceup||activity[b]==deadfacedown){
            if(Map[guymapx[b]][guymapy[b]]==1||Map[guymapx[b]][guymapy[b]]==2){
                    usingjetpack[b]=0;
                    time[b]=0;
                    frame[b]=3;
                    targetframe[b]=2;
                    targetanim[b]=2;
                    anim[b]=3;
                    guyy[b]=(guymapy[b]-39)*-20+.5;
                    nosound=0;
                    fallin[b]=0;
                    if(activity[b]==deadfacedown){health[b]+=guyvely[b]*70; activity[b]=splat;anim[b]=9; targetframe[b]=3; frame[b]=3; time[b]=100; targetanim[b]=9; playSound(SND_BREAK_ID,-guyvely[b]*50+50); playSound(SND_BREAK2_ID,-guyvely[b]*50+50);}
                    if(activity[b]==deadfaceup){health[b]+=guyvely[b]*70; activity[b]=landonback;anim[b]=14; targetframe[b]=1; frame[b]=1; time[b]=100; targetanim[b]=14; playSound(SND_BREAK_ID,-guyvely[b]*50+50); playSound(SND_BREAK2_ID,-guyvely[b]*50+50);}
                    guyvelx[b]=0;
                    guyvely[b]=0;
            }
            }
    }*/
    if (b != -1 && guyvely[whichguy] < -.3 && dead[b] == 0 && attach[whichguy] == -1) {
      guyvely[b] = guyvely[whichguy];
      guyvely[whichguy] /= 2;
      activity[b] = falling;
      usingjetpack[b] = 0;
      guyy[b] = guyy[whichguy] - 10;
      if (Map[guymapx[b]][guymapy[b]] == 1 || Map[guymapx[b]][guymapy[b]] == 2) {
        usingjetpack[b] = 0;
        time[b] = 0;
        frame[b] = 3;
        targetframe[b] = 3;
        targetanim[b] = 3;
        anim[b] = 3;
        guyy[b] = (guymapy[b] - 39) * -20 + .5;
        nosound = 0;
        fallin[b] = 0;
        if (guyvelx[whichguy] > 0) {
          targetrotation[b] = 90;
        }
        if (guyvelx[whichguy] < 0) {
          targetrotation[b] = -90;
        }
        health[b] += guyvely[b] * 70;
        activity[b] = splat;
        anim[b] = 9;
        targetframe[b] = 0;
        frame[b] = 0;
        time[b] = 100;
        targetanim[b] = 9;
        playSound(SND_BREAK_ID, -guyvely[b] * 50 + 50);
        playSound(SND_BREAK2_ID, -guyvely[b] * 50 + 50);
        guyvelx[b] = 0;
        guyvely[b] = 0;
      }
    }
    for (x = 0; x < 10; x++) {
      guyy[whichguy] += guyvely[whichguy] * multiplier / 10;
      guymapx[whichguy] = (guyx[whichguy] + 595) / 10;
      guymapy[whichguy] = guyy[whichguy] / -20 - .5 + 40;
      guywillbe = (guyy[whichguy] - guyvely[whichguy] / 10 + 8) / -20 - .5 + 40;

      if (activity[whichguy] == falling || activity[whichguy] == leftflip || activity[whichguy] == rightflip || activity[whichguy] == rightroll || activity[whichguy] == leftroll || fallin[whichguy] == 1 || activity[whichguy] == jetup || activity[whichguy] == jetright || activity[whichguy] == jetleft || activity[whichguy] == jetidle || usingjetpack[whichguy] == 1) {
        if (Map[guymapx[whichguy]][guywillbe] != 0 && Map[guymapx[whichguy]][guywillbe] != 3 && Map[guymapx[whichguy]][guywillbe] != 3 && guyvely[whichguy] < 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy]] != 3 && guywillbe == guymapy[whichguy] && attach[whichguy] == -1) {
          /*if(activity[whichguy]==falling){
                  frame[whichguy]=2;
                  anim[whichguy]=3;
                  time=70;
          }*/
          if (activity[whichguy] != jetimpaleright && activity[whichguy] != jetimpaleleft) {
            b = -1;
            for (a = 0; a < numplayers; a++) {
              if (absolute(guyx[whichguy] - guyx[a]) < 7 && absolute(guyy[whichguy] - guyy[a]) < guyvely[whichguy] * multiplier / 10 + 10 && a != whichguy && guyvely[whichguy] < 0 && guyvely[whichguy] < guyvely[a] && guyvely[whichguy] < -.1 && guyy[whichguy] > guyy[a] && activity[a] != falling) {
                b = a;
              }
            }
            if (b == whichguy) {
              b = -1;
            }
            if (b != -1 && activity[b] != jetimpaleleft && activity[b] != jetimpaleright) {
              if (activity[b] == deadfaceup || activity[b] == deadfacedown) {
                if (Map[guymapx[b]][guymapy[b]] == 1 || Map[guymapx[b]][guymapy[b]] == 2) {
                  guyvely[b] = guyvely[whichguy];
                  guyvely[whichguy] *= .5;
                  usingjetpack[b] = 0;
                  time[b] = 0;
                  frame[b] = 3;
                  targetframe[b] = 2;
                  targetanim[b] = 2;
                  anim[b] = 3;
                  guyy[b] = (guymapy[b] - 39) * -20 + .5;
                  nosound = 0;
                  fallin[b] = 0;
                  if (activity[b] == deadfacedown) {
                    health[b] += guyvely[b] * 70;
                    activity[b] = splat;
                    anim[b] = 9;
                    targetframe[b] = 3;
                    frame[b] = 3;
                    time[b] = 100;
                    targetanim[b] = 9;
                    playSound(SND_BREAK_ID, -guyvely[b] * 50 + 50);
                    playSound(SND_BREAK2_ID, -guyvely[b] * 50 + 50);
                  }
                  if (activity[b] == deadfaceup) {
                    health[b] += guyvely[b] * 70;
                    activity[b] = landonback;
                    anim[b] = 14;
                    targetframe[b] = 1;
                    frame[b] = 1;
                    time[b] = 100;
                    targetanim[b] = 14;
                    playSound(SND_BREAK_ID, -guyvely[b] * 50 + 50);
                    playSound(SND_BREAK2_ID, -guyvely[b] * 50 + 50);
                  }
                  guyvelx[b] = 0;
                  guyvely[b] = 0;
                }
              }
            }
            usingjetpack[whichguy] = 0;
            time[whichguy] = 0;
            a = anim[whichguy];
            c = activity[whichguy];
            if (activity[whichguy] != fallforwardsright && activity[whichguy] != fallforwardsleft) {
              frame[whichguy] = 2;
              targetframe[whichguy] = 2;
              targetanim[whichguy] = 3;
              anim[whichguy] = 3;
            }
            if (activity[whichguy] != deadfaceup && activity[whichguy] != deadfacedown && activity[whichguy] != landonback && activity[whichguy] != splat && activity[whichguy] != fallbackwardsright && activity[whichguy] != fallbackwardsleft && activity[whichguy] != fallforwardsright && activity[whichguy] != fallforwardsleft && activity[whichguy] != hitwallleft && activity[whichguy] != hitwallright && activity[whichguy] != jetimpaledleft && activity[whichguy] != jetimpaledright) {
              activity[whichguy] = ducking;
            }
            if (isKeyDown(kLeftKey[whichguy]) && dead[whichguy] == 0) {
              activity[whichguy] = leftroll;
              targetframe[whichguy] = 2;
            }
            if (isKeyDown(kRightKey[whichguy]) && dead[whichguy] == 0) {
              activity[whichguy] = rightroll;
              targetframe[whichguy] = 2;
            }
            if (guyvely[whichguy] < -.7 && c != jetimpaleleft && c != jetimpaleright && guyvelx[whichguy] < 0 && dead[whichguy] == 0) {
              activity[whichguy] = leftroll;
              targetframe[whichguy] = 2;
            }
            if (guyvely[whichguy] < -.7 && c != jetimpaleleft && c != jetimpaleright && guyvelx[whichguy] > 0 && dead[whichguy] == 0) {
              activity[whichguy] = rightroll;
              targetframe[whichguy] = 2;
            }
            if (guyvely[whichguy] < -1) {
              health[whichguy] += guyvely[whichguy] * 70;
              activity[whichguy] = splat;
              anim[whichguy] = 9;
              targetframe[whichguy] = 0;
              frame[whichguy] = 0;
              time[whichguy] = 100;
              targetanim[whichguy] = 9;
              playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
              playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
            }
            if (activity[whichguy] == deadfacedown || activity[whichguy] == fallforwardsright || activity[whichguy] == fallforwardsleft || activity[whichguy] == hitwallright || activity[whichguy] == hitwallleft) {
              health[whichguy] -= 10;
              if (activity[whichguy] != fallforwardsright && activity[whichguy] != fallforwardsleft) {
                activity[whichguy] = splat;
                anim[whichguy] = 9;
                targetframe[whichguy] = 2;
                frame[whichguy] = 0;
                time[whichguy] = 100;
                targetanim[whichguy] = 9;
              }
              playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
              playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
            }
            if (activity[whichguy] == deadfaceup || activity[whichguy] == fallbackwardsright || activity[whichguy] == fallbackwardsleft || activity[whichguy] == landonback) {
              activity[whichguy] = landonback;
              if (a == 37) {
                targetrotation[whichguy] *= -1;
                rotation[whichguy] *= -1;
              }
              anim[whichguy] = 14;
              targetframe[whichguy] = 1;
              frame[whichguy] = 0;
              time[whichguy] = 100;
              targetanim[whichguy] = 14;
              playSound(SND_BREAK_ID, -guyvely[whichguy] * 50 + 50);
              playSound(SND_BREAK2_ID, -guyvely[whichguy] * 50 + 50);
            }
            if (activity[whichguy] == ducking && nosound == 0 && invisible[whichguy] == 0) {
              playSound(SND_LAND_ID, -guyvely[whichguy] * 100 + 100);
            }
            if (activity[whichguy] == ducking && nosound == 0 && invisible[whichguy] == 1) {
              playSound(SND_LAND_ID, -guyvely[whichguy] * 10 + 10);
            }
            guyvelx[whichguy] = 0;
            guyvely[whichguy] = 0;
          }
          if (c == jetimpaleright || c == jetimpaleleft || activity[whichguy] == jetimpaleright || activity[whichguy] == jetimpaleleft) {
            guyvely[whichguy] = .005;
            if (c == jetimpaleleft || c == jetimpaleright) {
              activity[whichguy] = c;
            }
          }
          // if(activity[whichguy]!=landonback&&activity[whichguy]!=fallbackwardsright){
          guyy[whichguy] = (guymapy[whichguy] - 39) * -20 + .5;
          nosound = 0;
          fallin[whichguy] = 0;
        }
      }
    }
  }
  slide += multiplier / 100;
  if (slide > maxsprites) {
    slide = 1000;
  }
  guyx[whichguy] += guyvelx[whichguy] * multiplier;
  if (dead[whichguy] == 0 /*&&activity[whichguy]!=fallbackwardsright&&activity[whichguy]!=fallbackwardsleft&&activity[whichguy]!=landonback&&activity[whichguy]!=deadfaceup&&activity[whichguy]!=deadfacedown*/) {
    a = (guyx[whichguy] + 595) / 10 - .55;
    b = guyy[whichguy] / -20 - .5 + 40;
    c = (oldguyx[whichguy] + 595) / 10 - .55;
    d = (guyy[whichguy] - 10) / -20 - .5 + 40;
    f = 0;
    g = a - c;
    if (g == 1) {
      g = 0;
    }
    for (e = 0; e <= g; e++) {
      if (a > c && Walls[c + e + 1][b] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] -= .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] == 0) {
          targetanim[whichguy] = 11;
          activity[whichguy] = wallhit;
          targetframe[whichguy] = 0;
          time[whichguy] = 100;
        }
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = leftroll;
          anim[whichguy] = 8;
          targetanim[whichguy] = 8;
          guyvelx[whichguy] = guyvelx[whichguy] * -.5;
          targetframe[whichguy] = 1;
          frame[whichguy] = 1;
          time[whichguy] = 100;
        }
        f = 1;
      }
      if (a > c && Walls[c + e + 1][d] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] -= .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] == 0) {
          targetanim[whichguy] = 11;
          activity[whichguy] = wallhit;
          targetframe[whichguy] = 0;
          time[whichguy] = 100;
        }
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = leftroll;
          anim[whichguy] = 8;
          targetanim[whichguy] = 8;
          guyvelx[whichguy] = guyvelx[whichguy] * -.5;
          targetframe[whichguy] = 1;
          frame[whichguy] = 1;
          time[whichguy] = 100;
        }
        f = 1;
      }
    }
    a = (guyx[whichguy] + 595) / 10 - .3;
    b = guyy[whichguy] / -20 - .5 + 40;
    c = (oldguyx[whichguy] + 595) / 10 - .3;
    d = (guyy[whichguy] - 10) / -20 - .5 + 40;
    f = 0;
    g = c - a;
    if (g == 1) {
      g = 0;
    }
    for (e = 0; e <= g; e++) {
      if (a < c && Walls[c - e - 1][b] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] += .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] == 0) {
          targetanim[whichguy] = 11;
          activity[whichguy] = wallhit;
          targetframe[whichguy] = 0;
          time[whichguy] = 100;
        }
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = rightroll;
          anim[whichguy] = 8;
          targetanim[whichguy] = 8;
          guyvelx[whichguy] = guyvelx[whichguy] * -.5;
          targetframe[whichguy] = 1;
          frame[whichguy] = 1;
          time[whichguy] = 100;
        }
        f = 1;
      }
      if (a < c && Walls[c - e - 1][d] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] += .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] == 0) {
          targetanim[whichguy] = 11;
          activity[whichguy] = wallhit;
          targetframe[whichguy] = 0;
          time[whichguy] = 100;
        }
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = rightroll;
          anim[whichguy] = 8;
          targetanim[whichguy] = 8;
          guyvelx[whichguy] = guyvelx[whichguy] * -.5;
          targetframe[whichguy] = 1;
          frame[whichguy] = 1;
          time[whichguy] = 100;
        }
        f = 1;
      }
    }
  }
  if (dead[whichguy] == 1) {
    a = (guyx[whichguy] + 595) / 10 - .55;
    b = guyy[whichguy] / -20 - .5 + 40;
    c = (oldguyx[whichguy] + 595) / 10 - .55;
    d = (guyy[whichguy] - 10) / -20 - .5 + 40;
    f = 0;
    g = a - c;
    if (g == 1) {
      g = 0;
    }
    for (e = 0; e <= g; e++) {
      if (a > c && Walls[c + e + 1][b] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] -= .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = fallbackwardsright;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          anim[whichguy] = 13;
          targetanim[whichguy] = 13;
        }
        time[whichguy] = 100;
        guyvelx[whichguy] = guyvelx[whichguy] * -.5;
        f = 1;
      }
      if (a > c && Walls[c + e + 1][d] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] -= .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = fallbackwardsright;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          anim[whichguy] = 13;
          targetanim[whichguy] = 13;
        }
        time[whichguy] = 100;
        guyvelx[whichguy] = guyvelx[whichguy] * -.5;
        f = 1;
      }
    }
    a = (guyx[whichguy] + 595) / 10 - .3;
    b = guyy[whichguy] / -20 - .5 + 40;
    c = (oldguyx[whichguy] + 595) / 10 - .3;
    d = (guyy[whichguy] - 10) / -20 - .5 + 40;
    f = 0;
    g = c - a;
    if (g == 1) {
      g = 0;
    }
    for (e = 0; e <= g; e++) {
      if (a < c && Walls[a][b] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] += .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = fallbackwardsleft;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          anim[whichguy] = 13;
          targetanim[whichguy] = 13;
        }
        time[whichguy] = 100;
        guyvelx[whichguy] = guyvelx[whichguy] * -.5;
        f = 1;
      }
      if (a < c && Walls[a][d] == 1 && f == 0) {
        usingjetpack[whichguy] = 0;
        guyx[whichguy] += .3 + .6 * multiplier / 5;
        playSound(SND_LAND_ID, 30);
        if (guyvelx[whichguy] != 0) {
          activity[whichguy] = fallbackwardsleft;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          anim[whichguy] = 13;
          targetanim[whichguy] = 13;
        }
        time[whichguy] = 100;
        guyvelx[whichguy] = guyvelx[whichguy] * -.5;
        f = 1;
      }
    }
  }
  if (health[whichguy] <= 0) {
    dead[whichguy] = 1;
  }
  // if (guyx<-395){guyx+=multiplier/3; activity=rightroll; anim=8; targetanim=8; if(guyvelx[whichguy]!=0){guyvelx=.1;} targetframe=1; frame=1; time=100;}
  if (health[whichguy] <= 0 && oldhealth[whichguy] > 0) {
    deathcount[oldnum[whichguy]]++;
  }
  if (health[whichguy] < oldhealth[whichguy]) {
    usingjetpack[whichguy] = 0;
  }
  if (guymapy[whichguy] >= 99 || guymapx[whichguy] >= 99 || guymapx[whichguy] <= 1 || guyy[whichguy] > 390) {
    if (exists[whichguy] && cube == 0) {
      for (x = 0; x < 50; x++) {
        MakeSprite(guyx[whichguy], RangedRandom(guyy[whichguy] + 5, guyy[whichguy] + 20), 0, 200, deletestars, RangedRandom(1, 360), 10, RangedRandom(2, 5), 0, 0, 0);
      }
      deathcount[oldnum[whichguy]]++;
      health[whichguy] -= 1000;
      RemovePlayer(whichguy);
    }
  }
  oldhealth[whichguy] = health[whichguy];
  if (trail) {
    point = FindLeftGunPoint(whichguy);
    if (freezetime == 0)
      MakeSprite(point.x, point.y, point.z, 255, spawnstars, 0, 2, 0, 0, 0, 0);
    point = FindRightGunPoint(whichguy);
    if (freezetime == 0)
      MakeSprite(point.x, point.y, point.z, 255, spawnstars, 0, 2, 0, 0, 0, 0);
    /*if(jetpack[whichguy]==1){
            point=FindJetPackPos(whichguy);
            if(jetglownum[whichguy]==0){MakeSprite(point.x, point.y, point.z, 255, JetPackGlow, 0, 10, 0, 0,0,0); jetglownum[whichguy]=unusedsprite;}
            sprite[jetglownum[whichguy]].x=point.x;
            sprite[jetglownum[whichguy]].y=point.y;
            sprite[jetglownum[whichguy]].z=point.z;
    }*/
  }
  if (jetpack[whichguy] == 1 && usingjetpack[whichguy] == 1) {
    point = FindJetPackPos(whichguy);
    if (jetglownum[whichguy] == 0) {
      MakeSprite(point.x, point.y, point.z, 255, JetPackGlow, 0, 10, 0, 0, 0, 0);
      jetglownum[whichguy] = unusedsprite;
    }
    sprite[jetglownum[whichguy]].x = point.x;
    sprite[jetglownum[whichguy]].y = point.y;
    sprite[jetglownum[whichguy]].z = point.z;
    sprite[jetglownum[whichguy]].brightness = RangedRandom(50, 100);
    if (usingjetpack[whichguy] == 1) {
      sprite[jetglownum[whichguy]].brightness = RangedRandom(200, 255);
    }
    if (usingjetpack[whichguy] == 1 && activity[whichguy] == jetidle) {
      sprite[jetglownum[whichguy]].brightness = RangedRandom(100, 150);
    }
    jetsmokedelay[whichguy] -= multiplier;
  }
  if (jetpack[whichguy] == 0 || usingjetpack[whichguy] == 0) {
    if (jetglownum[whichguy] != 0) {
      sprite[jetglownum[whichguy]].type = 0;
      jetglownum[whichguy] = 0;
    }
  }
  // if(lightningfxdelay[whichguy]<=0){lightningfxdelay[whichguy]=7;}
  if (activity[whichguy] != jetimpaledright && activity[whichguy] != jetimpaledleft) {
    attach[whichguy] = -1;
  }
}

void ShootGrenade();
void ShootGrenade(int whichguy) {
  int a, b, c, d, e, f, g, h, x;
  float soundvolume;
  soundvolume = holding[whichguy] * 10 + 50;
  if (soundvolume > 200) {
    soundvolume = 200;
  }
  if (activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
    guymapy[whichguy] = guyy[whichguy] / -20 - .5 + 40;
    c = guyy[whichguy] / -20 - .5 + 40;
    g = ((guyx[whichguy] + 595) / 10) + .2;
    h = ((guyx[whichguy] + 595) / 10) + .9;
    if (facing[whichguy] == 1 && Walls[g][c] == 0) {
      e = 1;
    }
    if (facing[whichguy] == 0 && Walls[h - 2][c] == 0) {
      e = 1;
    }
    if (facing[whichguy] == 1) {
      b = -1;
      for (a = 0; a < numplayers; a++) {
        if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
          b = a;
        }
      }
    }
    if (facing[whichguy] == 0) {
      b = -1;
      for (a = 0; a < numplayers; a++) {
        if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] <= guyx[whichguy]) {
          b = a;
        }
      }
    }
    if (b != -1) {
      d = (guyx[b] + 595) / 10;
    }
    if (b != -1 && facing[whichguy] == 1) {
      if (a == d || Walls[a][c] == 0) {
        fake[whichguy] = 0;
        guyx[b] = guyx[whichguy];
        attacker[b] = whichguy;
        guyy[b] = guyy[whichguy];
        usingjetpack[b] = 0;
        guyvelx[b] = 0;
        guyvely[b] = 0;
        fallin[b] = 0;
        activity[whichguy] = breakneckright;
        anim[whichguy] = 16;
        targetanim[whichguy] = 16;
        activity[b] = brokeneckright;
        anim[b] = 17;
        targetanim[b] = 17;
        usingjetpack[b] = 0;
        targetframe[whichguy] = 1;
        targetframe[b] = 1;
        frame[whichguy] = 0;
        frame[b] = 0;
        time[whichguy] = 0;
        time[b] = 0;
      }
    }
    if (b == -1 && ammo[whichguy] <= 0 && facing[whichguy] == 1) {
      activity[whichguy] = breakneckright;
      anim[whichguy] = 16;
      targetanim[whichguy] = 16;
      targetframe[whichguy] = 1;
      frame[whichguy] = 0;
      time[whichguy] = 0;
      fake[whichguy] = 1;
    }
    if (b != -1 && facing[whichguy] == 0) {
      if (a == d || Walls[d][c] == 0) {
        fake[whichguy] = 0;
        guyx[b] = guyx[whichguy];
        attacker[b] = whichguy;
        guyy[b] = guyy[whichguy];
        usingjetpack[whichguy] = 0;
        guyvelx[b] = 0;
        guyvely[b] = 0;
        fallin[b] = 0;
        activity[whichguy] = breakneckleft;
        anim[whichguy] = 16;
        targetanim[whichguy] = 16;
        activity[b] = brokeneckleft;
        anim[b] = 17;
        targetanim[b] = 17;
        targetframe[whichguy] = 1;
        targetframe[b] = 1;
        frame[whichguy] = 0;
        frame[b] = 0;
        time[whichguy] = 0;
        time[b] = 0;
        usingjetpack[b] = 0;
      }
    }
    if (b == -1 && ammo[whichguy] <= 0 && facing[whichguy] == 0) {
      activity[whichguy] = breakneckleft;
      anim[whichguy] = 16;
      targetanim[whichguy] = 16;
      targetframe[whichguy] = 1;
      frame[whichguy] = 0;
      time[whichguy] = 0;
      fake[whichguy] = 1;
    }
    if (itemnum[whichguy] == 6 && ammo[whichguy] > 0 && usingjetpack[whichguy] == 0 && e == 1 && b == -1) {
      playSound(SND_GRENLAUNCH2_ID, soundvolume);
      anim[whichguy] = 44;
      targetanim[whichguy] = 44;
      frame[whichguy] = 0;
      targetframe[whichguy] = 0;
      time[whichguy] = 0;
      if (smokingbody[whichguy][kRightGun] < 100) {
        smokingbody[whichguy][kRightGun] += 50;
      }
      if (facing[whichguy] == 1) {
        targetrotation[whichguy] = 90;
        rotation[whichguy] = 90;
        activity[whichguy] = grenshootright;
        point = FindRightGunPoint(whichguy);
        if (freezetime == 0) {
          for (x = 0; x < 16; x++) {
            // a=(point.x+x+585)/10;
            // if(Walls[a][guymapy[whichguy]]==0){
            MakeSprite((float)(point.x + (float)(x / 4)), point.y, point.z, soundvolume, muzzleflashstars, RangedRandom(0, 360), 10 - (float)(x / 2), RangedRandom(0, 360), 0, 0, 0);
            //}
          }
        }
      }
      if (facing[whichguy] == 0) {
        targetrotation[whichguy] = -90;
        rotation[whichguy] = -90;
        activity[whichguy] = grenshootleft;
        point = FindRightGunPoint(whichguy);
        if (freezetime == 0) {
          for (x = 0; x < 16; x++) {
            // a=(point.x-x+595)/10;
            // if(Walls[a][guymapy[whichguy]]==0){
            MakeSprite((float)(point.x - (float)(x / 4)), point.y, point.z, soundvolume, muzzleflashstars, RangedRandom(0, 360), 10 - (float)(x / 2), RangedRandom(0, 360), 0, 0, 0);
            //}
          }
        }
      }
      point = FindRightGunPoint(whichguy);
      if (holding[whichguy] > 100) {
        holding[whichguy] = 100;
      }
      MakeSprite(point.x, point.y, point.z, 200, grenade, 1, 10, 0, -holding[whichguy] + (facing[whichguy] * holding[whichguy] * 2), .1, 0);
      if (itemtype[whichguy] == 0) {
        ammo[whichguy] -= 5;
      }
      if (itemtype[whichguy] == 1) {
        ammo[whichguy] -= 5;
        sprite[unusedsprite].type2 = 1; /*ammo[whichguy]-=0;*/
        sprite[unusedsprite].owner = whichguy;
      }
    }
  }
  if (itemnum[whichguy] == 6 && anim[whichguy] != 30 && ammo[whichguy] > 0 && usingjetpack[whichguy] == 1 && (activity[whichguy] == jetidle || activity[whichguy] == jetleft || activity[whichguy] == jetright || activity[whichguy] == jetup || activity[whichguy] == jetdown)) {
    playSound(SND_GRENLAUNCH2_ID, soundvolume);
    anim[whichguy] = 44;
    targetanim[whichguy] = 44;
    frame[whichguy] = 0;
    targetframe[whichguy] = 0;
    time[whichguy] = 0;
    if (smokingbody[whichguy][kRightGun] < 100) {
      smokingbody[whichguy][kRightGun] += 50;
    }
    if (facing[whichguy] == 1) {
      guyvelx[whichguy] -= holding[whichguy] / 200;
      activity[whichguy] = shootright;
      targetframe[whichguy] = 3;
      frame[whichguy] = 2;
      targetanim[whichguy] = 30;
      anim[whichguy] = 30;
      time[whichguy] = 0;
      targetrotation[whichguy] = 0;
      targetrotation[whichguy] = 90;
      rotation[whichguy] = 90;
      point = FindRightGunPoint(whichguy);
      if (freezetime == 0) {
        for (x = 0; x < 16; x++) {
          // a=(point.x+x+585)/10;
          // if(Walls[a][guymapy[whichguy]]==0){
          MakeSprite((float)(point.x + (float)(x / 4)), point.y, point.z, soundvolume, muzzleflashstars, RangedRandom(0, 360), 10 - (float)(x / 2), RangedRandom(0, 360), 0, 0, 0);
          //}
        }
      }
    }
    if (facing[whichguy] == 0) {
      guyvelx[whichguy] += holding[whichguy] / 200;
      activity[whichguy] = shootleft;
      targetframe[whichguy] = 3;
      frame[whichguy] = 2;
      targetanim[whichguy] = 30;
      anim[whichguy] = 30;
      time[whichguy] = 0;
      targetrotation[whichguy] = 0;
      targetrotation[whichguy] = -90;
      rotation[whichguy] = -90;
      point = FindRightGunPoint(whichguy);
      if (freezetime == 0) {
        for (x = 0; x < 16; x++) {
          // a=(point.x-x+595)/10;
          // if(Walls[a][guymapy[whichguy]]==0){
          MakeSprite((float)(point.x - (float)(x / 4)), point.y, point.z, soundvolume, muzzleflashstars, RangedRandom(0, 360), 10 - (float)(x / 2), RangedRandom(0, 360), 0, 0, 0);
          //}
        }
      }
    }
    point = FindRightGunPoint(whichguy);
    if (holding[whichguy] > 100) {
      holding[whichguy] = 100;
    }
    MakeSprite(point.x, point.y, point.z, 200, grenade, 1, 10, 0, -holding[whichguy] + (facing[whichguy] * holding[whichguy] * 2), .1, 0);
    if (itemtype[whichguy] == 0) {
      ammo[whichguy] -= 5;
    }
    if (itemtype[whichguy] == 1) {
      ammo[whichguy] -= 5;
      sprite[unusedsprite].type2 = 1; /*ammo[whichguy]-=0;*/
      sprite[unusedsprite].owner = whichguy;
    }
  }
}

int CheckPaths(int whichguy, int num) {
  int a, c, haschecked;
  float e, f;
  if (compxsteptest[whichguy][num] == computertargetxlocation[whichguy] && compysteptest[whichguy][num] == computertargetylocation[whichguy] && num < pathfindsteps) {
    pathfound[whichguy] = 1;
    pathfindsteps = num;
    for (a = 0; a <= 100; a++) {
      compxstep[whichguy][a] = -1000;
      compystep[whichguy][a] = -1000;
    }
    for (a = 0; a <= pathfindsteps + 1; a++) {
      compxstep[whichguy][a] = compxsteptest[whichguy][a];
      compystep[whichguy][a] = compysteptest[whichguy][a];
    }
  }
  if (Map[computertargetxlocation[whichguy]][computertargetylocation[whichguy]] == 0) {
    pathfound[whichguy] = 0;
    return 0;
  }
  if ((Map[compxsteptest[whichguy][num] + 1][compysteptest[whichguy][num]] == 1 || Map[compxsteptest[whichguy][num] + 1][compysteptest[whichguy][num]] == 2 || Map[compxsteptest[whichguy][num] + 1][compysteptest[whichguy][num]] == 3) && Walls[compxsteptest[whichguy][num]][compysteptest[whichguy][num]] == 0) {
    compxsteptest[whichguy][num + 1] = compxsteptest[whichguy][num] + 1;
    compysteptest[whichguy][num + 1] = compysteptest[whichguy][num];
    haschecked = 0;
    for (a = 0; a < num; a++) {
      if (compxsteptest[whichguy][a] == compxsteptest[whichguy][num + 1] && compysteptest[whichguy][a] == compysteptest[whichguy][num + 1]) {
        haschecked = 1;
      }
    }
    if (num < 90 && num < pathfindsteps && haschecked == 0 && compxsteptest[whichguy][num + 1] != compxsteptest[whichguy][num - 1]) {
      CheckPaths(whichguy, num + 1);
    }
  }
  if ((Map[compxsteptest[whichguy][num] - 1][compysteptest[whichguy][num]] == 1 || Map[compxsteptest[whichguy][num] - 1][compysteptest[whichguy][num]] == 2 || Map[compxsteptest[whichguy][num] - 1][compysteptest[whichguy][num]] == 3) && Walls[compxsteptest[whichguy][num] - 1][compysteptest[whichguy][num]] == 0) {
    compxsteptest[whichguy][num + 1] = compxsteptest[whichguy][num] - 1;
    compysteptest[whichguy][num + 1] = compysteptest[whichguy][num];
    haschecked = 0;
    for (a = 0; a < num; a++) {
      if (compxsteptest[whichguy][a] == compxsteptest[whichguy][num + 1] && compysteptest[whichguy][a] == compysteptest[whichguy][num + 1]) {
        haschecked = 1;
      }
    }
    if (num < 90 && num < pathfindsteps && haschecked == 0 && compxsteptest[whichguy][num + 1] != compxsteptest[whichguy][num - 1]) {
      CheckPaths(whichguy, num + 1);
    }
  }
  if (Map[compxsteptest[whichguy][num]][compysteptest[whichguy][num] + 1] == 3 || Map[compxsteptest[whichguy][num]][compysteptest[whichguy][num] + 1] == 2) {
    compxsteptest[whichguy][num + 1] = compxsteptest[whichguy][num];
    compysteptest[whichguy][num + 1] = compysteptest[whichguy][num] + 1;
    haschecked = 0;
    for (a = 0; a < num; a++) {
      if (compxsteptest[whichguy][a] == compxsteptest[whichguy][num + 1] && compysteptest[whichguy][a] == compysteptest[whichguy][num + 1]) {
        haschecked = 1;
      }
    }
    if (num < 90 && num < pathfindsteps && haschecked == 0 && compysteptest[whichguy][num + 1] != compysteptest[whichguy][num - 1]) {
      CheckPaths(whichguy, num + 1);
    }
  }
  if (Map[compxsteptest[whichguy][num]][compysteptest[whichguy][num]] == 3 || Map[compxsteptest[whichguy][num]][compysteptest[whichguy][num]] == 2) {
    compxsteptest[whichguy][num + 1] = compxsteptest[whichguy][num];
    compysteptest[whichguy][num + 1] = compysteptest[whichguy][num] - 1;
    haschecked = 0;
    for (a = 0; a < num; a++) {
      if (compxsteptest[whichguy][a] == compxsteptest[whichguy][num + 1] && compysteptest[whichguy][a] == compysteptest[whichguy][num + 1]) {
        haschecked = 1;
      }
    }
    if (num < 90 && num < pathfindsteps && haschecked == 0 && compysteptest[whichguy][num + 1] != compysteptest[whichguy][num - 1]) {
      CheckPaths(whichguy, num + 1);
    }
  }
}

void DoPathFinding(int whichguy) {
  int a = 0, b, c;
  bool done = 0;
  bool possible;
  pathfindsteps = 1000;
  pathfound[whichguy] = 0;
  for (a = 0; a < 100; a++) {
    compxsteptest[whichguy][a] = -1000;
    compysteptest[whichguy][a] = -1000;
    compxstep[whichguy][a] = -1000;
    compystep[whichguy][a] = -1000;
  }

  compxsteptest[whichguy][0] = guymapx[whichguy];
  compysteptest[whichguy][0] = guymapy[whichguy];
  compxsteptest[whichguy][1] = guymapx[whichguy];
  compysteptest[whichguy][1] = guymapy[whichguy];
  compxsteptest[whichguy][2] = guymapx[whichguy];
  compysteptest[whichguy][2] = guymapy[whichguy];
  done = 0;
  a = 0;
  CheckPaths(whichguy, 1);
  if (pathfound[whichguy] == 0) {
    compxstep[whichguy][0] = guymapx[whichguy];
    compystep[whichguy][0] = guymapy[whichguy];
    compxstep[whichguy][1] = guymapx[whichguy];
    compystep[whichguy][1] = guymapy[whichguy];
    compxstep[whichguy][2] = guymapx[whichguy];
    compystep[whichguy][2] = guymapy[whichguy];
  }
}

void DoAI(int whichguy) {
  int a = 0, b = 0, c = 0, clearshot, clearshot2;
  float distance = 1234567;
  float olddistance = 1234567;
  float targetxstep;
  float targetystep;
  kRightShootKeydown[whichguy] = 0;
  kLeftShootKeydown[whichguy] = 0;
  kRightKeydown[whichguy] = 0;
  kLeftKeydown[whichguy] = 0;
  kUpKeydown[whichguy] = 0;
  kDownKeydown[whichguy] = 0;
  kAttackKeydown[whichguy] = 0;
  kBlockKeydown[whichguy] = 0;

  if (!computertarget[whichguy]) {
    for (a = 0; a < numplayers; a++) {
      distance = std::sqrt((guyx[a] - guyx[whichguy]) * (guyx[a] - guyx[whichguy]) + (guyy[a] - guyy[whichguy]) + (guyy[a] - guyy[whichguy]));
      if ((olddistance = 1234567 || distance < olddistance) && a != whichguy && health[a] > 0) {
        olddistance = distance;
        computertarget[whichguy] = a;
      }
    }
  }
  distance = std::sqrt((guyx[computertarget[whichguy]] - guyx[whichguy]) * (guyx[computertarget[whichguy]] - guyx[whichguy]) + (guyy[computertarget[whichguy]] - guyy[whichguy]) + (guyy[computertarget[whichguy]] - guyy[whichguy]));
  computertargetxlocation[whichguy] = guymapx[computertarget[whichguy]];
  computertargetylocation[whichguy] = guymapy[computertarget[whichguy]];

  DoPathFinding(whichguy);

  if (health[computertarget[whichguy]] <= 0) {
    computertargetxlocation[whichguy] = 0;
    computertargetylocation[whichguy] = 0;
  }
  targetxstep = compxstep[whichguy][2] * 10 - 590;
  targetystep = (compystep[whichguy][2] - 39) * -20 + .5;
  if (AIOffensive) {
    if (usingjetpack[whichguy] == 0) {
      if (guyx[whichguy] < targetxstep - 2) {
        kRightKeydown[whichguy] = 1;
      }
      if (guyx[whichguy] > targetxstep + 2) {
        kLeftKeydown[whichguy] = 1;
      }
      if (guyy[whichguy] == guyy[computertarget[whichguy]] && guymapx[whichguy] >= computertargetxlocation[whichguy] - 1 && guymapx[whichguy] <= computertargetxlocation[whichguy] + 1 && guyx[whichguy] < guyx[computertarget[whichguy]] - 2) {
        kRightKeydown[whichguy] = 1;
      }
      if (guyy[whichguy] == guyy[computertarget[whichguy]] && guymapx[whichguy] >= computertargetxlocation[whichguy] - 1 && guymapx[whichguy] <= computertargetxlocation[whichguy] + 1 && guyx[whichguy] > guyx[computertarget[whichguy]] + 2) {
        kLeftKeydown[whichguy] = 1;
      }
      if (guyy[whichguy] > targetystep + 2 && kLeftKeydown[whichguy] == 0 && kRightKeydown[whichguy] == 0) {
        kRightKeydown[whichguy] = 0;
        kLeftKeydown[whichguy] = 0;
        if (activity[whichguy] != runleft && activity[whichguy] != runright && activity[whichguy] != ducking) {
          kDownKeydown[whichguy] = 1;
        }
      }
      if (guyy[whichguy] < targetystep - 2 && kLeftKeydown[whichguy] == 0 && kRightKeydown[whichguy] == 0) {
        kRightKeydown[whichguy] = 0;
        kLeftKeydown[whichguy] = 0;
        if (activity[whichguy] != runleft && activity[whichguy] != runright) {
          kUpKeydown[whichguy] = 1;
        }
      }
      display = distance;
    }
    if (jetpack[whichguy] == 1) {
      if (usingjetpack[whichguy] == 0 && uppressed[whichguy] == 0 && (usingjetpack[computertarget[whichguy]] == 1 || pathfound[whichguy] == 0)) {
        kRightKeydown[whichguy] = 0;
        kLeftKeydown[whichguy] = 0;
        kDownKeydown[whichguy] = 0;
        kUpKeydown[whichguy] = 1;
        if (activity[whichguy] == onrope || activity[whichguy] == climbrope || activity[whichguy] == downrope) {
          if (Walls[guymapx[whichguy]][guymapy[whichguy]] == 0) {
            kRightKeydown[whichguy] = 1;
            kLeftKeydown[whichguy] = 0;
            kDownKeydown[whichguy] = 0;
            kUpKeydown[whichguy] = 0;
          }
          if (Walls[guymapx[whichguy] - 1][guymapy[whichguy]] == 0) {
            kRightKeydown[whichguy] = 0;
            kLeftKeydown[whichguy] = 1;
            kDownKeydown[whichguy] = 0;
            kUpKeydown[whichguy] = 0;
          }
        }
      }
      if (usingjetpack[whichguy] == 1) {
        if (guyx[whichguy] > guyx[computertarget[whichguy]]) {
          kLeftKeydown[whichguy] = 1;
        }
        if (guyx[whichguy] < guyx[computertarget[whichguy]]) {
          kRightKeydown[whichguy] = 1;
        }
        if (guyy[whichguy] > guyy[computertarget[whichguy]]) {
          kDownKeydown[whichguy] = 1;
        }
        if (guyy[whichguy] < guyy[computertarget[whichguy]]) {
          kUpKeydown[whichguy] = 1;
        }
      }
    }
    if (guymapy[whichguy] == computertargetylocation[whichguy] && guyx[whichguy] <= guyx[computertarget[whichguy]] && dead[computertarget[whichguy]] == 0 && ammo[whichguy] > 0) {
      if ((itemnum[whichguy] == 1 || itemnum[whichguy] == 4 || itemnum[whichguy] == 5) && activity[whichguy] != onrope && activity[whichguy] != climbrope && activity[whichguy] != downrope && distance > 15) {
        if ((itemnum[whichguy] == 4 && distance > 30) || (activity[computertarget[whichguy]] != ducking && activity[computertarget[whichguy]] != leftroll && activity[computertarget[whichguy]] != rightroll)) {
          clearshot = 1;
          for (a = 0; a < 100; a++) {
            if (guymapx[whichguy] + a < 100 && guymapx[whichguy] + a < guymapx[computertarget[whichguy]]) {
              if (Walls[guymapx[whichguy] + a][guymapy[whichguy]] == 1) {
                clearshot = 0;
              }
            }
          }
          if (clearshot == 1 || guymapx[whichguy] == computertargetxlocation[whichguy]) {
            if (usingjetpack[whichguy] == 0) {
              kRightKeydown[whichguy] = 0;
              kLeftKeydown[whichguy] = 0;
              kUpKeydown[whichguy] = 0;
              kDownKeydown[whichguy] = 0;
            }
            kRightShootKeydown[whichguy] = 1;
          }
        }
      }
      if ((itemnum[whichguy] == 2 || itemnum[whichguy] == 3) && activity[whichguy] != onrope && activity[whichguy] != climbrope && activity[whichguy] != downrope && distance < 15) {
        clearshot = 1;
        for (a = 0; a < 2; a++) {
          if (guymapx[whichguy] - a - 1 >= 0 && guymapx[whichguy] - a - 1 > guymapx[computertarget[whichguy]]) {
            if (Walls[guymapx[whichguy] - a - 1][guymapy[whichguy]] == 1) {
              clearshot = 0;
            }
          }
        }
        leftshootpressed[whichguy] = 0;
        if (/*(clearshot==1||guymapx[whichguy]==guymapx[computertarget[whichguy]])&&*/ leftshootpressed[whichguy] == 0) {
          kRightKeydown[whichguy] = 1;
          kUpKeydown[whichguy] = 0;
          kDownKeydown[whichguy] = 0;
          kAttackKeydown[whichguy] = 1;
        }
      }
      if ((itemnum[whichguy] == 1 || itemnum[whichguy] == 4 || itemnum[whichguy] == 5 || itemnum[whichguy] == 2 || itemnum[whichguy] == 3 || itemnum[whichguy] == 0 || itemnum[whichguy] == 5) && activity[whichguy] != onrope && activity[whichguy] != climbrope && activity[whichguy] != downrope && distance < 10) {
        clearshot = 1;
        for (a = 0; a < 2; a++) {
          if (guymapx[whichguy] - a - 1 >= 0 && guymapx[whichguy] - a - 1 > guymapx[computertarget[whichguy]]) {
            if (Walls[guymapx[whichguy] - a - 1][guymapy[whichguy]] == 1) {
              clearshot = 0;
            }
          }
        }
        rightshootpressed[whichguy] = 0;
        if (/*(clearshot==1||guymapx[whichguy]==guymapx[computertarget[whichguy]])&&*/ rightshootpressed[whichguy] == 0) {
          if (usingjetpack[whichguy] == 0) {
            kRightKeydown[whichguy] = 0;
            kLeftKeydown[whichguy] = 0;
            kUpKeydown[whichguy] = 0;
            kDownKeydown[whichguy] = 0;
          }
          kRightShootKeydown[whichguy] = 1;
        }
      }
    }
    if (guymapy[whichguy] == computertargetylocation[whichguy] && guyx[whichguy] >= guyx[computertarget[whichguy]] && dead[computertarget[whichguy]] == 0 && ammo[whichguy] > 0) {
      if ((itemnum[whichguy] == 1 || itemnum[whichguy] == 4 || itemnum[whichguy] == 5) && activity[whichguy] != onrope && activity[whichguy] != climbrope && activity[whichguy] != downrope && distance > 15) {
        if ((itemnum[whichguy] == 4 && distance > 30) || (activity[computertarget[whichguy]] != ducking && activity[computertarget[whichguy]] != leftroll && activity[computertarget[whichguy]] != rightroll)) {
          clearshot = 1;
          for (a = 0; a < 100; a++) {
            if (guymapx[whichguy] - a - 1 >= 0 && guymapx[whichguy] - a - 1 > guymapx[computertarget[whichguy]]) {
              if (Walls[guymapx[whichguy] - a - 1][guymapy[whichguy]] == 1) {
                clearshot = 0;
              }
            }
          }
          if (clearshot == 1 || guymapx[whichguy] == computertargetxlocation[whichguy]) {
            if (usingjetpack[whichguy] == 0) {
              kRightKeydown[whichguy] = 0;
              kLeftKeydown[whichguy] = 0;
              kUpKeydown[whichguy] = 0;
              kDownKeydown[whichguy] = 0;
            }
            kLeftShootKeydown[whichguy] = 1;
          }
        }
      }
      if ((itemnum[whichguy] == 2 || itemnum[whichguy] == 3) && activity[whichguy] != onrope && activity[whichguy] != climbrope && activity[whichguy] != downrope && distance < 15) {
        clearshot = 1;
        for (a = 0; a < 2; a++) {
          if (guymapx[whichguy] - a - 1 >= 0 && guymapx[whichguy] - a - 1 > guymapx[computertarget[whichguy]]) {
            if (Walls[guymapx[whichguy] - a - 1][guymapy[whichguy]] == 1) {
              clearshot = 0;
            }
          }
        }
        leftshootpressed[whichguy] = 0;
        if (/*(clearshot==1||guymapx[whichguy]==guymapx[computertarget[whichguy]])&&*/ leftshootpressed[whichguy] == 0) {
          kLeftKeydown[whichguy] = 1;
          kUpKeydown[whichguy] = 0;
          kDownKeydown[whichguy] = 0;
          kAttackKeydown[whichguy] = 1;
        }
      }
      b = -1;
      for (a = 0; a < numplayers; a++) {
        if (absolute(guyx[whichguy] - guyx[a]) < 30 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) && absolute(guyy[whichguy] - guyy[a]) < 6 + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && dead[a] == 0 && a != whichguy) {
          b = a;
        }
      }
      if (itemnum[whichguy] == 7 && b != -1) {
        kRightKeydown[whichguy] = 0;
        kLeftKeydown[whichguy] = 0;
        kUpKeydown[whichguy] = 0;
        kDownKeydown[whichguy] = 0;

        if (guyx[b] >= guyx[whichguy]) {
          kRightShootKeydown[whichguy] = 1;
        }
        if (guyx[b] < guyx[whichguy]) {
          kLeftShootKeydown[whichguy] = 1;
        }
      }
      if ((itemnum[whichguy] == 1 || itemnum[whichguy] == 4 || itemnum[whichguy] == 5 || itemnum[whichguy] == 2 || itemnum[whichguy] == 3 || itemnum[whichguy] == 0 || itemnum[whichguy] == 5 || itemnum[whichguy] == 7) && activity[whichguy] != onrope && activity[whichguy] != climbrope && activity[whichguy] != downrope && distance < 10) {
        clearshot = 1;
        for (a = 0; a < 2; a++) {
          if (guymapx[whichguy] - a - 1 >= 0 && guymapx[whichguy] - a - 1 > guymapx[computertarget[whichguy]]) {
            if (Walls[guymapx[whichguy] - a - 1][guymapy[whichguy]] == 1) {
              clearshot = 0;
            }
          }
        }
        leftshootpressed[whichguy] = 0;
        if (/*(clearshot==1||guymapx[whichguy]==guymapx[computertarget[whichguy]])&&*/ leftshootpressed[whichguy] == 0) {
          if (usingjetpack[whichguy] == 0) {
            kRightKeydown[whichguy] = 0;
            kLeftKeydown[whichguy] = 0;
            kUpKeydown[whichguy] = 0;
            kDownKeydown[whichguy] = 0;
          }
          kLeftShootKeydown[whichguy] = 1;
        }
      }
    }
  }
  clearshot = 1;
  for (a = 0; a < 100; a++) {
    if (guymapx[whichguy] + a < 100 && guymapx[whichguy] + a < guymapx[computertarget[whichguy]]) {
      if (Walls[guymapx[whichguy] + a][guymapy[whichguy]] == 1) {
        clearshot = 0;
      }
    }
  }
  clearshot2 = 1;
  for (a = 0; a < 100; a++) {
    if (guymapx[whichguy] - a - 1 >= 0 && guymapx[whichguy] - a - 1 > guymapx[computertarget[whichguy]]) {
      if (Walls[guymapx[whichguy] - a - 1][guymapy[whichguy]] == 1) {
        clearshot2 = 0;
      }
    }
  }
  if (abouttobehit[whichguy] || (clearshot2 == 1 && activity[computertarget[whichguy]] == shootleft && guyx[computertarget[whichguy]] < guyx[whichguy] && guymapy[whichguy] == guymapy[computertarget[whichguy]]) || (clearshot == 1 && activity[computertarget[whichguy]] == shootright && guyx[computertarget[whichguy]] > guyx[whichguy] && guymapy[whichguy] == guymapy[computertarget[whichguy]])) {
    kUpKeydown[whichguy] = 0;
    kDownKeydown[whichguy] = 1;
  }
  if (clearshot2 && guymapy[whichguy] == guymapy[computertarget[whichguy]] && (activity[computertarget[whichguy]] == swordrightthrust || activity[computertarget[whichguy]] == swordrightspin) && distance < 15) {
    facing[whichguy] = 0;
    kBlockKeydown[whichguy] = 1;
  }
  if (clearshot && guymapy[whichguy] == guymapy[computertarget[whichguy]] && (activity[computertarget[whichguy]] == swordleftthrust || activity[computertarget[whichguy]] == swordleftspin) && distance < 15) {
    facing[whichguy] = 1;
    kBlockKeydown[whichguy] = 1;
  }
}

int CheckAIKey(int whichguy, int which) {
  if (which == kDownKey[whichguy]) {
    if (kDownKeydown[whichguy]) {
      return 1;
    }
  }
  if (which == kUpKey[whichguy]) {
    if (kUpKeydown[whichguy]) {
      return 1;
    }
  }
  if (which == kLeftKey[whichguy]) {
    if (kLeftKeydown[whichguy]) {
      return 1;
    }
  }
  if (which == kRightKey[whichguy]) {
    if (kRightKeydown[whichguy]) {
      return 1;
    }
  }
  if (which == kBlockKey[whichguy]) {
    if (kBlockKeydown[whichguy]) {
      return 1;
    }
  }
  if (which == kAttackKey[whichguy]) {
    if (kAttackKeydown[whichguy]) {
      return 1;
    }
  }
  if (which == kRightShootKey[whichguy]) {
    if (kRightShootKeydown[whichguy]) {
      return 1;
    }
  }
  if (which == kLeftShootKey[whichguy]) {
    if (kLeftShootKeydown[whichguy]) {
      return 1;
    }
  }
  return 0;
}

void DoAIKeys(int whichguy) {
  unsigned char theKeyMap[16];
  int a, b, c, d, e, f, g, h, x, y;
  int guywillbe;

  //*************BLOCK KEY**************//
  if (CheckAIKey(whichguy, kBlockKey[whichguy]) && delaytime[whichguy] <= 0) {
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight) {
      if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
        if (facing[whichguy] == 1) {
          activity[whichguy] = swordrightparry;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 29;
          time[whichguy] = 100;
        }
        if (facing[whichguy] != 1) {
          activity[whichguy] = swordleftparry;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 29;
          time[whichguy] = 100;
        }
        delaytime[whichguy] = 400;
        if (itemnum[whichguy] == 3) {
          delaytime[whichguy] = 240;
        }
      }
    }
    if (itemnum[whichguy] == 6 && itemtype[whichguy] == 1 && health[whichguy] > 0) {
      for (x = 0; x < maxsprites; x++) {
        if (sprite[x].owner == whichguy && sprite[x].type == grenade && sprite[x].type2 == 1) {
          Explode(x);
        }
      }
    }
  }
  //*************ATTACK KEY**************//
  if (CheckAIKey(whichguy, kAttackKey[whichguy])) {
    if (holding[whichguy] == 0) {
      holding[whichguy] = 1;
    }
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
      if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
        if (facing[whichguy] == 1 && attackpressed[whichguy] == 0) {
          a = (guyx[whichguy] + 595) / 10;
          c = guyy[whichguy] / -20 - .5 + 40;
          d = (guyx[whichguy] + 595) / 10 + .3;
          if (Walls[a][c] == 0 && Walls[d][c] == 0) {
            activity[whichguy] = swordrightthrust;
            targetframe[whichguy] = 0;
            targetanim[whichguy] = 27;
            time[whichguy] = 100;
          }
        }
        if (facing[whichguy] == 0 && attackpressed[whichguy] == 0) {
          a = (guyx[whichguy] + 595) / 10 - .95;
          c = guyy[whichguy] / -20 - .5 + 40;
          d = (guyx[whichguy] + 595) / 10 - .95 - .2;
          if (Walls[a][c] == 0 && Walls[d][c] == 0) {
            activity[whichguy] = swordleftthrust;
            targetframe[whichguy] = 0;
            targetanim[whichguy] = 27;
            time[whichguy] = 100;
          }
        }
      }
      /*if(itemnum[whichguy]==6){
              point=FindRightGunPoint(whichguy);
              MakeSprite(point.x,point.y,point.z,200,grenade, 1, 10, 0,-10+(facing[whichguy]*20),.1,0);
      }*/
    }
    if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
      if (activity[whichguy] == runright) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        d = (guyx[whichguy] + 595) / 10 + .3;
        if (Walls[a][c] == 0 && Walls[d][c] == 0 && attackpressed[whichguy] == 0) {
          activity[whichguy] = swordrightspin;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 40;
          time[whichguy] = 100;
        }
      }
      if (activity[whichguy] == runleft) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        d = (guyx[whichguy] + 595) / 10 - .95 - .2;
        if (Walls[a][c] == 0 && Walls[d][c] == 0 && attackpressed[whichguy] == 0) {
          activity[whichguy] = swordleftspin;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 40;
          time[whichguy] = 100;
        }
      }
    }
    if (activity[whichguy] == jetidle || activity[whichguy] == jetleft || activity[whichguy] == jetright || activity[whichguy] == jetup) {
      if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
        if (facing[whichguy] == 1) {
          b = -1;
          for (a = 0; a < numplayers; a++) {
            if (absolute(guyx[whichguy] - guyx[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && absolute(guyy[whichguy] - guyy[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
              b = a;
            }
          }
          if (b == whichguy) {
            b = -1;
          }
          a = (guyx[whichguy] + 595) / 10;
          c = guyy[whichguy] / -20 - .5 + 40;
          d = (guyx[b] + 595) / 10;
          e = guyy[b] / -20 - .5 + 40;
          if (b != -1 && rightshootpressed[whichguy] == 0 && attackpressed[whichguy] == 0) {
            if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
              if (a == d || Walls[a][c] == 0) {
                fake[whichguy] = 0;
                guyx[b] = guyx[whichguy];
                attacker[b] = whichguy;
                guyy[b] = guyy[whichguy];
                attach[b] = whichguy;
                guyvelx[b] = guyvelx[whichguy];
                guyvely[b] = guyvely[whichguy];
                activity[whichguy] = jetimpaleright;
                anim[whichguy] = 36;
                targetanim[whichguy] = 36;
                activity[b] = jetimpaledright;
                anim[b] = 37;
                targetanim[b] = 37;
                targetframe[whichguy] = 1;
                targetframe[b] = 1;
                frame[whichguy] = 0;
                frame[b] = 0;
                time[whichguy] = 0;
                time[b] = 0;
              }
            }
          }
          if (b == -1 && rightshootpressed[whichguy] == 0 && attackpressed[whichguy] == 0) {
            if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
              activity[whichguy] = jetimpaleright;
              anim[whichguy] = 36;
              targetanim[whichguy] = 36;
              targetframe[whichguy] = 1;
              frame[whichguy] = 0;
              time[whichguy] = 0;
              fake[whichguy] = 1;
            }
          }
        }
        if (facing[whichguy] == 0) {
          b = -1;
          for (a = 0; a < numplayers; a++) {
            if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] <= guyx[whichguy]) {
              b = a;
            }
          }
          a = (guyx[whichguy] + 595) / 10;
          c = guyy[whichguy] / -20 - .5 + 40;
          d = (guyx[b] + 595) / 10;
          e = guyy[b] / -20 - .5 + 40;
          if (b == whichguy) {
            b = -1;
          }
          if (b != -1 && leftshootpressed[whichguy] == 0 && attackpressed[whichguy] == 0) {
            if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
              if (a == d || Walls[a][c] == 0) {
                fake[whichguy] = 0;
                guyx[b] = guyx[whichguy];
                attacker[b] = whichguy;
                guyy[b] = guyy[whichguy];
                attach[b] = whichguy;
                guyvelx[b] = guyvelx[whichguy];
                guyvely[b] = guyvely[whichguy];
                activity[whichguy] = jetimpaleleft;
                anim[whichguy] = 36;
                targetanim[whichguy] = 36;
                activity[b] = jetimpaledleft;
                anim[b] = 37;
                targetanim[b] = 37;
                targetframe[whichguy] = 1;
                targetframe[b] = 1;
                frame[whichguy] = 0;
                frame[b] = 0;
                time[whichguy] = 0;
                time[b] = 0;
              }
            }
          }
          if (b == -1 && leftshootpressed[whichguy] == 0 && attackpressed[whichguy] == 0) {
            if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
              activity[whichguy] = jetimpaleleft;
              anim[whichguy] = 36;
              targetanim[whichguy] = 36;
              targetframe[whichguy] = 1;
              frame[whichguy] = 0;
              time[whichguy] = 0;
              fake[whichguy] = 1;
            }
          }
        }
      }
    }
    attackpressed[whichguy] = 1;
  }
  if (CheckAIKey(whichguy, kAttackKey[whichguy]) == 0 && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 0 && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 0) {
    if (holding[whichguy] != 0) {
      if (holdingtype[whichguy] == -1) {
        facing[whichguy] = 0;
      }
      if (holdingtype[whichguy] == 1) {
        facing[whichguy] = 1;
      }
      ShootGrenade(whichguy);
    }
    holding[whichguy] = 0;
  }
  if (CheckAIKey(whichguy, kAttackKey[whichguy]) == 0) {
    attackpressed[whichguy] = 0;
  }
  if (CheckAIKey(whichguy, kRightShootKey[whichguy]) == 1 && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 0) {
    holdingtype[whichguy] = 1;
  }
  if (CheckAIKey(whichguy, kAttackKey[whichguy]) == 1 && CheckAIKey(whichguy, kRightShootKey[whichguy]) == 0 && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 0) {
    holdingtype[whichguy] = 0;
  }
  if (CheckAIKey(whichguy, kRightShootKey[whichguy]) == 0 && CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 1) {
    holdingtype[whichguy] = -1;
  }
  //**********RIGHT SHOOT KEY************//
  if (CheckAIKey(whichguy, kRightShootKey[whichguy])) {
    if (usingjetpack[whichguy] == 0) {
      facing[whichguy] = 1;
    }
    if (activity[whichguy] == jetleft || activity[whichguy] == jetright || activity[whichguy] == jetup) {
      if (itemnum[whichguy] >= 1 && itemnum[whichguy] <= 5) {
        activity[whichguy] = jetidle;
      }
    }
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == jetidle || activity[whichguy] == ducking || activity[whichguy] == falling) {
      b = -1;
      for (a = 0; a < numplayers; a++) {
        if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
          b = a;
        }
      }
      if (b == whichguy) {
        b = -1;
      }
      a = (guyx[whichguy] + 595) / 10;
      c = guyy[whichguy] / -20 - .5 + 40;
      d = (guyx[b] + 595) / 10;
      e = guyy[b] / -20 - .5 + 40;
      f = (guyx[whichguy] + 605) / 10;
      g = ((guyx[whichguy] + 595) / 10) + .2;
      h = ((guyx[whichguy] + 595) / 10) + .9;
      if (b == -1 && ammo[whichguy] > 0 && itemnum[whichguy] == 1 && Walls[g][c] == 0) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 10;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
      }
      if (b == -1 && ammo[whichguy] > 0 && itemnum[whichguy] == 4 && Walls[g][c] == 0) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 10;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
      }
      if (b == -1 && ammo[whichguy] > 0 && itemnum[whichguy] == 7 && Walls[g][c] == 0 && lightningdelay[whichguy] <= 0) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        lightningdelay[whichguy] = 0;
        firstshot[whichguy] = 1;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 10;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
      }
      if (b == -1 && ammo[whichguy] > 0 && itemnum[whichguy] == 5 && Walls[g][c] == 0) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 31;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
      }
      if (itemnum[whichguy] == 6) {
        if (holding[whichguy] == 0) {
          holding[whichguy] = 1;
        }
      }
      if (activity[whichguy] == jetidle) {
        b = -1;
        for (a = 0; a < numplayers; a++) {
          if (absolute(guyx[whichguy] - guyx[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && absolute(guyy[whichguy] - guyy[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
            b = a;
          }
        }
        if (b == whichguy) {
          b = -1;
        }
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        d = (guyx[b] + 595) / 10;
        e = guyy[b] / -20 - .5 + 40;
        if (b != -1 && rightshootpressed[whichguy] == 0) {
          if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
            if (a == d || Walls[a][c] == 0) {
              fake[whichguy] = 0;
              guyx[b] = guyx[whichguy];
              attacker[b] = whichguy;
              guyy[b] = guyy[whichguy];
              attach[b] = whichguy;
              guyvelx[b] = guyvelx[whichguy];
              guyvely[b] = guyvely[whichguy];
              activity[whichguy] = jetimpaleright;
              anim[whichguy] = 36;
              targetanim[whichguy] = 36;
              activity[b] = jetimpaledright;
              anim[b] = 37;
              targetanim[b] = 37;
              targetframe[whichguy] = 1;
              targetframe[b] = 1;
              frame[whichguy] = 0;
              frame[b] = 0;
              time[whichguy] = 0;
              time[b] = 0;
            }
          }
        }
        if (b == -1 && rightshootpressed[whichguy] == 0 && activity[whichguy] == jetidle) {
          if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
            activity[whichguy] = jetimpaleright;
            anim[whichguy] = 36;
            targetanim[whichguy] = 36;
            targetframe[whichguy] = 1;
            frame[whichguy] = 0;
            time[whichguy] = 0;
            fake[whichguy] = 1;
          }
        }
      }
      if (activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != jetimpaleright) {
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] >= 0 && itemnum[whichguy] <= 1) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            fallin[b] == 1;
            activity[whichguy] = breakneckright;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckright;
            anim[b] = 17;
            targetanim[b] = 17;
            usingjetpack[b] = 0;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
          }
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 4) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckright;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckright;
            anim[b] = 17;
            targetanim[b] = 17;
            usingjetpack[b] = 0;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if ((b != -1 || ammo[whichguy] <= 0) && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 7) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            if (b != -1) {
              guyx[b] = guyx[whichguy];
              attacker[b] = whichguy;
              guyy[b] = guyy[whichguy];
              usingjetpack[b] = 0;
              guyvelx[b] = 0;
              guyvely[b] = 0;
              fallin[b] = 0;
              activity[b] = brokeneckright;
              anim[b] = 17;
              targetanim[b] = 17;
              usingjetpack[b] = 0;
              targetframe[b] = 1;
              frame[b] = 0;
              time[b] = 0;
            }
            activity[whichguy] = breakneckright;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            targetframe[whichguy] = 1;
            frame[whichguy] = 0;
            time[whichguy] = 0;
            if (b == -1) {
              fake[whichguy] = 1;
            }
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 5) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckright;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckright;
            anim[b] = 17;
            targetanim[b] = 17;
            usingjetpack[b] = 0;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 2 && activity[whichguy] != ducking) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            usingjetpack[b] = 0;
            activity[whichguy] = impaleright;
            anim[whichguy] = 18;
            targetanim[whichguy] = 18;
            activity[b] = impaledright;
            anim[b] = 19;
            targetanim[b] = 19;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 3 && activity[whichguy] != ducking) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            usingjetpack[b] = 0;
            activity[whichguy] = swordthrowright;
            anim[whichguy] = 20;
            targetanim[whichguy] = 20;
            activity[b] = swordthrownright;
            anim[b] = 21;
            targetanim[b] = 21;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            c = (guyx[whichguy] + 595) / 10;
            f = guyy[whichguy] / -20 - .5 + 40;
            if (Walls[c - 1][f] == 1 || Walls[c - 2][f] == 1) {
              activity[whichguy] = impaleright;
              anim[whichguy] = 18;
              targetanim[whichguy] = 18;
              activity[b] = impaledright;
              anim[b] = 19;
              targetanim[b] = 19;
            }
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] >= 2 && itemnum[whichguy] <= 3 && activity[whichguy] != ducking) {
          activity[whichguy] = impaleright;
          anim[whichguy] = 18;
          targetanim[whichguy] = 18;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] <= 3 && itemnum[whichguy] >= 2 && activity[whichguy] == ducking) {
          fake[whichguy] = 0;
          guyx[b] = guyx[whichguy];
          attacker[b] = whichguy;
          guyy[b] = guyy[whichguy];
          usingjetpack[b] = 0;
          guyvelx[b] = 0;
          guyvely[b] = 0;
          fallin[b] = 0;
          usingjetpack[b] = 0;
          activity[whichguy] = duckimpaleright;
          anim[whichguy] = 38;
          targetanim[whichguy] = 38;
          activity[b] = duckimpaledright;
          anim[b] = 39;
          targetanim[b] = 39;
          targetframe[whichguy] = 1;
          targetframe[b] = 1;
          frame[whichguy] = 0;
          frame[b] = 0;
          time[whichguy] = 0;
          time[b] = 0;
          c = (guyx[whichguy] + 595) / 10;
          f = guyy[whichguy] / -20 - .5 + 40;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] >= 2 && itemnum[whichguy] <= 3 && activity[whichguy] == ducking) {
          activity[whichguy] = duckimpaleright;
          anim[whichguy] = 38;
          targetanim[whichguy] = 38;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] == 0 && rightshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckright;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] == 1 && ammo[whichguy] <= 0 && rightshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckright;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] >= 4 && itemnum[whichguy] <= 5 && ammo[whichguy] <= 0 && rightshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckright;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
      }
    }
    rightshootpressed[whichguy] = 1;
  }

  if (CheckAIKey(whichguy, kRightShootKey[whichguy]) == 0) {
    rightshootpressed[whichguy] = 0;
  }
  //**********LEFT SHOOT KEY************//
  if (CheckAIKey(whichguy, kLeftShootKey[whichguy])) {
    if (usingjetpack[whichguy] == 0) {
      facing[whichguy] = 0;
    }
    if (activity[whichguy] == jetleft || activity[whichguy] == jetright || activity[whichguy] == jetup) {
      if (itemnum[whichguy] >= 1 && itemnum[whichguy] <= 5) {
        activity[whichguy] = jetidle;
      }
    }
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == falling || activity[whichguy] == jetidle || activity[whichguy] == ducking) {
      b = -1;
      for (a = 0; a < numplayers; a++) {
        if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] <= guyx[whichguy]) {
          b = a;
        }
      }
      a = (guyx[whichguy] + 595) / 10;
      c = guyy[whichguy] / -20 - .5 + 40;
      d = (guyx[b] + 595) / 10;
      e = guyy[b] / -20 - .5 + 40;
      f = (guyx[whichguy] + 585) / 10;
      g = ((guyx[whichguy] + 595) / 10) + .2;
      h = ((guyx[whichguy] + 595) / 10) + .9;
      if (b == whichguy) {
        b = -1;
      }
      if (b == -1 && ammo[whichguy] && itemnum[whichguy] == 1 && Walls[h - 2][c] == 0) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 12;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
      }
      if (b == -1 && itemnum[whichguy] == 4 && ammo[whichguy] > 0 && Walls[h - 2][c] == 0) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 12;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
      }
      if (b == -1 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && Walls[h - 2][c] == 0 && lightningdelay[whichguy] <= 0) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        lightningdelay[whichguy] = 0;
        firstshot[whichguy] = 1;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 12;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
      }
      if (b == -1 && itemnum[whichguy] == 5 && ammo[whichguy] > 0 && Walls[h - 2][c] == 0) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 32;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
      }
      if (itemnum[whichguy] == 6) {
        if (holding[whichguy] == 0) {
          holding[whichguy] = 1;
        }
      }
      if (activity[whichguy] == jetidle) {
        b = -1;
        for (a = 0; a < numplayers; a++) {
          if (absolute(guyx[whichguy] - guyx[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && absolute(guyy[whichguy] - guyy[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && dead[a] == 0 && a != whichguy && guyx[a] <= guyx[whichguy]) {
            b = a;
          }
        }
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        d = (guyx[b] + 595) / 10;
        e = guyy[b] / -20 - .5 + 40;
        if (b == whichguy) {
          b = -1;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0) {
          if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
            if (a == d || Walls[a][c] == 0) {
              fake[whichguy] = 0;
              guyx[b] = guyx[whichguy];
              attacker[b] = whichguy;
              guyy[b] = guyy[whichguy];
              attach[b] = whichguy;
              guyvelx[b] = guyvelx[whichguy];
              guyvely[b] = guyvely[whichguy];
              activity[whichguy] = jetimpaleleft;
              anim[whichguy] = 36;
              targetanim[whichguy] = 36;
              activity[b] = jetimpaledleft;
              anim[b] = 37;
              targetanim[b] = 37;
              targetframe[whichguy] = 1;
              targetframe[b] = 1;
              frame[whichguy] = 0;
              frame[b] = 0;
              time[whichguy] = 0;
              time[b] = 0;
            }
          }
        }
        if (b == -1 && leftshootpressed[whichguy] == 0 && activity[whichguy] == jetidle) {
          if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
            activity[whichguy] = jetimpaleleft;
            anim[whichguy] = 36;
            targetanim[whichguy] = 36;
            targetframe[whichguy] = 1;
            frame[whichguy] = 0;
            time[whichguy] = 0;
            fake[whichguy] = 1;
          }
        }
      }
      if (activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != jetimpaleleft) {
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] >= 0 && itemnum[whichguy] <= 1) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckleft;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckleft;
            anim[b] = 17;
            targetanim[b] = 17;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            usingjetpack[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 4) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckleft;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckleft;
            anim[b] = 17;
            targetanim[b] = 17;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            usingjetpack[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if ((b != -1 || ammo[whichguy] <= 0) && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 7) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            if (b != -1) {
              guyx[b] = guyx[whichguy];
              attacker[b] = whichguy;
              guyy[b] = guyy[whichguy];
              usingjetpack[whichguy] = 0;
              guyvelx[b] = 0;
              guyvely[b] = 0;
              fallin[b] = 0;
              time[b] = 0;
              activity[b] = brokeneckleft;
              anim[b] = 17;
              targetanim[b] = 17;
              targetframe[b] = 1;
              frame[b] = 0;
              usingjetpack[b] = 0;
            }
            activity[whichguy] = breakneckleft;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            targetframe[whichguy] = 1;
            frame[whichguy] = 0;
            time[whichguy] = 0;
            if (b == -1) {
              fake[whichguy] = 1;
            }
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 5) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckleft;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckleft;
            anim[b] = 17;
            targetanim[b] = 17;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            usingjetpack[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 2 && activity[whichguy] != ducking) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = impaleleft;
            anim[whichguy] = 18;
            targetanim[whichguy] = 18;
            activity[b] = impaledleft;
            anim[b] = 19;
            targetanim[b] = 19;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            usingjetpack[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] >= 2 && itemnum[whichguy] <= 3 && activity[whichguy] != ducking) {
          activity[whichguy] = impaleleft;
          anim[whichguy] = 18;
          targetanim[whichguy] = 18;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 3 && activity[whichguy] != ducking) {
          if (a == d || Walls[d][e] == 0) {
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = swordthrowleft;
            anim[whichguy] = 20;
            targetanim[whichguy] = 20;
            activity[b] = swordthrownleft;
            anim[b] = 21;
            targetanim[b] = 21;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            c = (guyx[whichguy] + 595) / 10;
            f = guyy[whichguy] / -20 - .5 + 40;
            if (Walls[c][f] == 1 || Walls[c + 1][f] == 1) {
              activity[whichguy] = impaleleft;
              anim[whichguy] = 18;
              targetanim[whichguy] = 18;
              activity[b] = impaledleft;
              anim[b] = 19;
              targetanim[b] = 19;
            }
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] <= 3 && itemnum[whichguy] >= 2 && activity[whichguy] == ducking) {
          guyx[b] = guyx[whichguy];
          attacker[b] = whichguy;
          guyy[b] = guyy[whichguy];
          usingjetpack[b] = 0;
          guyvelx[b] = 0;
          guyvely[b] = 0;
          fallin[b] = 0;
          usingjetpack[b] = 0;
          activity[whichguy] = duckimpaleleft;
          anim[whichguy] = 38;
          targetanim[whichguy] = 38;
          activity[b] = duckimpaledleft;
          anim[b] = 39;
          targetanim[b] = 39;
          targetframe[whichguy] = 1;
          targetframe[b] = 1;
          frame[whichguy] = 0;
          frame[b] = 0;
          time[whichguy] = 0;
          time[b] = 0;
          c = (guyx[whichguy] + 595) / 10;
          f = guyy[whichguy] / -20 - .5 + 40;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] >= 2 && itemnum[whichguy] <= 3 && activity[whichguy] == ducking) {
          activity[whichguy] = duckimpaleleft;
          anim[whichguy] = 38;
          targetanim[whichguy] = 38;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] == 0 && leftshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckleft;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] == 1 && ammo[whichguy] <= 0 && leftshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckleft;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] >= 4 && itemnum[whichguy] <= 5 && ammo[whichguy] <= 0 && leftshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckleft;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
      }
    }
    leftshootpressed[whichguy] = 1;
  }
  if (CheckAIKey(whichguy, kLeftShootKey[whichguy]) == 0) {
    leftshootpressed[whichguy] = 0;
  }
  //**********LEFT KEY************//
  if (CheckAIKey(whichguy, kLeftKey[whichguy])) {
    facing[whichguy] = 0;
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
      if (anim[whichguy] != 3) {
        activity[whichguy] = runleft;
        targetframe[whichguy] = 1;
        frame[whichguy] = 0;
        anim[whichguy] = 2;
        targetanim[whichguy] = 2;
        time[whichguy] = 100;
      }
    }
    if (activity[whichguy] == onrope) {
      activity[whichguy] = falling;
      targetframe[whichguy] = 0;
      guyvelx[whichguy] = -.1;
      guyvely[whichguy] = -.1;
    }
    if (activity[whichguy] == ducking) {
      activity[whichguy] = leftroll;
      targetframe[whichguy] = 1;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == jetidle || activity[whichguy] == falling || activity[whichguy] == jetup) {
      if (jetpack[whichguy]) {
        activity[whichguy] = jetleft;
        targetframe[whichguy] = 0;
        time[whichguy] = 0;
        targetanim[whichguy] = 34;
      }
    }
  }
  //**********RIGHT KEY************//
  if (CheckAIKey(whichguy, kRightKey[whichguy])) {
    facing[whichguy] = 1;
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
      if (anim[whichguy] != 3) {
        activity[whichguy] = runright;
        targetframe[whichguy] = 1;
        frame[whichguy] = 0;
        anim[whichguy] = 2;
        targetanim[whichguy] = 2;
        time[whichguy] = 100;
      }
    }
    if (activity[whichguy] == onrope) {
      activity[whichguy] = falling;
      targetframe[whichguy] = 0;
      guyvelx[whichguy] = .1;
      guyvely[whichguy] = -.1;
    }
    if (activity[whichguy] == ducking) {
      activity[whichguy] = rightroll;
      targetframe[whichguy] = 1;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == jetidle || activity[whichguy] == falling || activity[whichguy] == jetup) {
      if (jetpack[whichguy]) {
        activity[whichguy] = jetright;
        targetframe[whichguy] = 0;
        time[whichguy] = 0;
        targetanim[whichguy] = 34;
      }
    }
  }
  //**********DOWN KEY************//
  if (CheckAIKey(whichguy, kDownKey[whichguy])) {
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == getupfromback || activity[whichguy] == getupfromfront) {
      if (Map[guymapx[whichguy]][guymapy[whichguy] + 1] != 2 && Map[guymapx[whichguy]][guymapy[whichguy] + 1] != 3) {
        activity[whichguy] = ducking;
        targetframe[whichguy] = 1;
        frame[whichguy] = 0;
        targetanim[whichguy] = 3;
        anim[whichguy] = 3;
        time[whichguy] = 100;
      }
      if (Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 2 || Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 3) {
        frame[whichguy] = 0;
        targetframe[whichguy] = 2;
        guyy[whichguy] -= 4;
        activity[whichguy] = downrope;
        anim[whichguy] = 5;
        targetanim[whichguy] = 5;
        guyx[whichguy] = guymapx[whichguy] * 10 - 590;
        time[whichguy] = 80;
      }
    }
    if (activity[whichguy] == ducking && frame[whichguy] == 2) {
      targetframe[whichguy] = 2;
    }
    if (activity[whichguy] == onrope) {
      if (Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 2 || Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 3 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3 || Map[guymapx[whichguy]][guymapy[whichguy]] == 2) {
        guyvelx[whichguy] = 0;
        guyvely[whichguy] = 0;
        frame[whichguy] = 2;
        targetframe[whichguy] = 2;
        activity[whichguy] = downrope;
        targetanim[whichguy] = 5;
        anim[whichguy] = 5;
        targetframe[whichguy] = 2;
        guyx[whichguy] = guymapx[whichguy] * 10 - 590;
        time[whichguy] = 0;
      }
    }
    if (activity[whichguy] == falling || activity[whichguy] == leftflip || activity[whichguy] == rightflip) {
      if (guyvelx[whichguy] != 0) {
        if (Map[guymapx[whichguy]][guymapy[whichguy]] == 3 || Map[guymapx[whichguy]][guymapy[whichguy]] == 2) {
          if (activity[whichguy] != onrope) {
            frame[whichguy] = 2;
            targetframe[whichguy] = 2;
          }
          guyvelx[whichguy] = 0;
          guyvely[whichguy] = 0;
          activity[whichguy] = downrope;
          targetanim[whichguy] = 5;
          anim[whichguy] = 5;
          targetframe[whichguy] = 2;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          time[whichguy] = 0;
          rotation[whichguy] = 0;
        }
      }
    }
    if (activity[whichguy] == onrope || activity[whichguy] == downrope) {
      guywillbe = (guyy[whichguy] - 15) / -20 - .5 + 40;
      if (Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 0) {
        activity[whichguy] = falling;
        guyvely[whichguy] = -.2;
        targetframe[whichguy] = 0;
      }
      if (Map[guymapx[whichguy]][guywillbe] == 2 && Map[guymapx[whichguy]][guymapy[whichguy]] == 2) {
        activity[whichguy] = falling;
        guyvely[whichguy] = -.2;
        targetframe[whichguy] = 0;
      }
    }
    if (activity[whichguy] == runleft) {
      activity[whichguy] = leftroll;
      targetframe[whichguy] = 0;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == runright) {
      activity[whichguy] = rightroll;
      targetframe[whichguy] = 0;
      time[whichguy] = 0;
    }
  }
  //**********UP KEY************//
  if (CheckAIKey(whichguy, kUpKey[whichguy])) {
    guywillbe = (guyy[whichguy] - 7) / -20 - .5 + 40;
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == onrope || activity[whichguy] == falling || activity[whichguy] == leftflip || activity[whichguy] == rightflip) {
      if (Map[guymapx[whichguy]][guymapy[whichguy]] == 2 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3 || Map[guymapx[whichguy]][guywillbe] == 2 || Map[guymapx[whichguy]][guywillbe] == 3) {
        if (activity[whichguy] != onrope) {
          frame[whichguy] = 0;
          targetframe[whichguy] = 1;
        }
        guyvelx[whichguy] = 0;
        guyvely[whichguy] = 0;
        activity[whichguy] = climbrope;
        targetanim[whichguy] = 5;
        time[whichguy] = 100;
        guyx[whichguy] = guymapx[whichguy] * 10 - 590;
      }
    }
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
      if (uppressed[whichguy] == 0) {
        activity[whichguy] = jumpstraight;
        frame[whichguy] = 1;
        anim[whichguy] = 6;
        targetanim[whichguy] = 6;
        targetframe[whichguy] = 2;
        time[whichguy] = 0;
      }
    }
    if (activity[whichguy] == runleft && uppressed[whichguy] == 0) {
      activity[whichguy] = leftflip;
      anim[whichguy] = 7;
      targetanim[whichguy] = 7;
      frame[whichguy] = 0;
      targetframe[whichguy] = 1;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == runright && uppressed[whichguy] == 0) {
      activity[whichguy] = rightflip;
      anim[whichguy] = 7;
      targetanim[whichguy] = 7;
      frame[whichguy] = 0;
      targetframe[whichguy] = 1;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == falling && jetpack[whichguy] == 1) {
      if (jetpack[whichguy]) {
        activity[whichguy] = jetup;
        targetanim[whichguy] = 33;
        targetframe[whichguy] = 0;
        time[whichguy] = 100;
      }
    }
    if (activity[whichguy] == jetidle && jetpack[whichguy] == 1) {
      if (jetpack[whichguy]) {
        activity[whichguy] = jetup;
        targetanim[whichguy] = 33;
        targetframe[whichguy] = 0;
        time[whichguy] = 100;
      }
    }
    uppressed[whichguy] = 1;
    if (activity[whichguy] == climbrope && Map[guymapx[whichguy]][guymapy[whichguy]] == 0) {
      activity[whichguy] = onrope;
    }
    if (activity[whichguy] == climbrope && Map[guymapx[whichguy]][guywillbe] == 1 && Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy] + 1] != 1) {
      activity[whichguy] = falling;
      nosound = 1;
      guyvely[whichguy] = -.1;
      frame[whichguy] = 0;
    }
  }
  if (CheckAIKey(whichguy, kUpKey[whichguy]) == 0) {
    uppressed[whichguy] = 0;
  }
}

void DoKeys(int whichguy) {
  unsigned char theKeyMap[16];
  int a, b, c, d, e, f, g, h, x, y;
  int guywillbe;

  //*************BLOCK KEY**************//
  if (isKeyDown(kBlockKey[whichguy]) && delaytime[whichguy] <= 0) {
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == painoneleft || activity[whichguy] == paintwoleft || activity[whichguy] == painoneright || activity[whichguy] == paintworight) {
      if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
        if (facing[whichguy] == 1) {
          activity[whichguy] = swordrightparry;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 29;
          time[whichguy] = 100;
        }
        if (facing[whichguy] != 1) {
          activity[whichguy] = swordleftparry;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 29;
          time[whichguy] = 100;
        }
        delaytime[whichguy] = 400;
        if (itemnum[whichguy] == 3) {
          delaytime[whichguy] = 240;
        }
      }
    }
    if (itemnum[whichguy] == 6 && itemtype[whichguy] == 1 && health[whichguy] > 0) {
      for (x = 0; x < maxsprites; x++) {
        if (sprite[x].owner == whichguy && sprite[x].type == grenade && sprite[x].type2 == 1) {
          Explode(x);
        }
      }
    }
  }
  //*************ATTACK KEY**************//
  if (isKeyDown(kAttackKey[whichguy])) {
    if (holding[whichguy] == 0) {
      holding[whichguy] = 1;
    }
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
      if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
        if (facing[whichguy] == 1 && attackpressed[whichguy] == 0) {
          a = (guyx[whichguy] + 595) / 10;
          c = guyy[whichguy] / -20 - .5 + 40;
          d = (guyx[whichguy] + 595) / 10 + .3;
          if (Walls[a][c] == 0 && Walls[d][c] == 0) {
            activity[whichguy] = swordrightthrust;
            targetframe[whichguy] = 0;
            targetanim[whichguy] = 27;
            time[whichguy] = 100;
          }
        }
        if (facing[whichguy] == 0 && attackpressed[whichguy] == 0) {
          a = (guyx[whichguy] + 595) / 10 - .95;
          c = guyy[whichguy] / -20 - .5 + 40;
          d = (guyx[whichguy] + 595) / 10 - .95 - .2;
          if (Walls[a][c] == 0 && Walls[d][c] == 0) {
            activity[whichguy] = swordleftthrust;
            targetframe[whichguy] = 0;
            targetanim[whichguy] = 27;
            time[whichguy] = 100;
          }
        }
      }
      /*if(itemnum[whichguy]==6){
              point=FindRightGunPoint(whichguy);
              MakeSprite(point.x,point.y,point.z,200,grenade, 1, 10, 0,-10+(facing[whichguy]*20),.1,0);
      }*/
    }
    if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
      if (activity[whichguy] == runright) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        d = (guyx[whichguy] + 595) / 10 + .3;
        if (Walls[a][c] == 0 && Walls[d][c] == 0 && attackpressed[whichguy] == 0) {
          activity[whichguy] = swordrightspin;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 40;
          time[whichguy] = 100;
        }
      }
      if (activity[whichguy] == runleft) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        d = (guyx[whichguy] + 595) / 10 - .95 - .2;
        if (Walls[a][c] == 0 && Walls[d][c] == 0 && attackpressed[whichguy] == 0) {
          activity[whichguy] = swordleftspin;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 40;
          time[whichguy] = 100;
        }
      }
    }
    if (activity[whichguy] == jetidle || activity[whichguy] == jetleft || activity[whichguy] == jetright || activity[whichguy] == jetup) {
      if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
        if (facing[whichguy] == 1) {
          b = -1;
          for (a = 0; a < numplayers; a++) {
            if (absolute(guyx[whichguy] - guyx[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && absolute(guyy[whichguy] - guyy[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
              b = a;
            }
          }
          if (b == whichguy) {
            b = -1;
          }
          a = (guyx[whichguy] + 595) / 10;
          c = guyy[whichguy] / -20 - .5 + 40;
          d = (guyx[b] + 595) / 10;
          e = guyy[b] / -20 - .5 + 40;
          if (b != -1 && rightshootpressed[whichguy] == 0 && attackpressed[whichguy] == 0) {
            if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
              if (a == d || Walls[a][c] == 0) {
                fake[whichguy] = 0;
                guyx[b] = guyx[whichguy];
                attacker[b] = whichguy;
                guyy[b] = guyy[whichguy];
                attach[b] = whichguy;
                attacker[b] = whichguy;
                guyvelx[b] = guyvelx[whichguy];
                guyvely[b] = guyvely[whichguy];
                activity[whichguy] = jetimpaleright;
                anim[whichguy] = 36;
                targetanim[whichguy] = 36;
                activity[b] = jetimpaledright;
                anim[b] = 37;
                targetanim[b] = 37;
                targetframe[whichguy] = 1;
                targetframe[b] = 1;
                frame[whichguy] = 0;
                frame[b] = 0;
                time[whichguy] = 0;
                time[b] = 0;
              }
            }
          }
          if (b == -1 && rightshootpressed[whichguy] == 0 && attackpressed[whichguy] == 0) {
            if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
              activity[whichguy] = jetimpaleright;
              anim[whichguy] = 36;
              targetanim[whichguy] = 36;
              targetframe[whichguy] = 1;
              frame[whichguy] = 0;
              time[whichguy] = 0;
              fake[whichguy] = 1;
            }
          }
        }
        if (facing[whichguy] == 0) {
          b = -1;
          for (a = 0; a < numplayers; a++) {
            if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] <= guyx[whichguy]) {
              b = a;
            }
          }
          a = (guyx[whichguy] + 595) / 10;
          c = guyy[whichguy] / -20 - .5 + 40;
          d = (guyx[b] + 595) / 10;
          e = guyy[b] / -20 - .5 + 40;
          if (b == whichguy) {
            b = -1;
          }
          if (b != -1 && leftshootpressed[whichguy] == 0 && attackpressed[whichguy] == 0) {
            if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
              if (a == d || Walls[a][c] == 0) {
                fake[whichguy] = 0;
                guyx[b] = guyx[whichguy];
                attacker[b] = whichguy;
                guyy[b] = guyy[whichguy];
                attach[b] = whichguy;
                guyvelx[b] = guyvelx[whichguy];
                guyvely[b] = guyvely[whichguy];
                activity[whichguy] = jetimpaleleft;
                anim[whichguy] = 36;
                targetanim[whichguy] = 36;
                activity[b] = jetimpaledleft;
                anim[b] = 37;
                targetanim[b] = 37;
                targetframe[whichguy] = 1;
                targetframe[b] = 1;
                frame[whichguy] = 0;
                frame[b] = 0;
                time[whichguy] = 0;
                time[b] = 0;
              }
            }
          }
          if (b == -1 && leftshootpressed[whichguy] == 0 && attackpressed[whichguy] == 0) {
            if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
              activity[whichguy] = jetimpaleleft;
              anim[whichguy] = 36;
              targetanim[whichguy] = 36;
              targetframe[whichguy] = 1;
              frame[whichguy] = 0;
              time[whichguy] = 0;
              fake[whichguy] = 1;
            }
          }
        }
      }
    }
    attackpressed[whichguy] = 1;
  }
  if (isKeyDown(kAttackKey[whichguy]) == 0 && isKeyDown(kRightShootKey[whichguy]) == 0 && isKeyDown(kLeftShootKey[whichguy]) == 0) {
    if (holding[whichguy] != 0) {
      if (holdingtype[whichguy] == -1) {
        facing[whichguy] = 0;
      }
      if (holdingtype[whichguy] == 1) {
        facing[whichguy] = 1;
      }
      ShootGrenade(whichguy);
    }
    holding[whichguy] = 0;
  }
  if (isKeyDown(kAttackKey[whichguy]) == 0) {
    attackpressed[whichguy] = 0;
  }
  if (isKeyDown(kRightShootKey[whichguy]) == 1 && isKeyDown(kLeftShootKey[whichguy]) == 0) {
    holdingtype[whichguy] = 1;
  }
  if (isKeyDown(kAttackKey[whichguy]) == 1 && isKeyDown(kRightShootKey[whichguy]) == 0 && isKeyDown(kLeftShootKey[whichguy]) == 0) {
    holdingtype[whichguy] = 0;
  }
  if (isKeyDown(kRightShootKey[whichguy]) == 0 && isKeyDown(kLeftShootKey[whichguy]) == 1) {
    holdingtype[whichguy] = -1;
  }
  //**********RIGHT SHOOT KEY************//
  if (isKeyDown(kRightShootKey[whichguy])) {
    if (usingjetpack[whichguy] == 0) {
      facing[whichguy] = 1;
    }
    if (activity[whichguy] == jetleft || activity[whichguy] == jetright || activity[whichguy] == jetup) {
      if (itemnum[whichguy] >= 1 && itemnum[whichguy] <= 5) {
        activity[whichguy] = jetidle;
      }
    }
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == jetidle || activity[whichguy] == ducking || activity[whichguy] == falling) {
      b = -1;
      for (a = 0; a < numplayers; a++) {
        if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
          b = a;
        }
      }
      if (b == whichguy) {
        b = -1;
      }
      a = (guyx[whichguy] + 595) / 10;
      c = guyy[whichguy] / -20 - .5 + 40;
      d = (guyx[b] + 595) / 10;
      e = guyy[b] / -20 - .5 + 40;
      f = (guyx[whichguy] + 605) / 10;
      g = ((guyx[whichguy] + 595) / 10) + .2;
      h = ((guyx[whichguy] + 595) / 10) + .9;
      if (b == -1 && ammo[whichguy] > 0 && itemnum[whichguy] == 1 && Walls[g][c] == 0) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 10;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
      }
      if (b == -1 && ammo[whichguy] > 0 && itemnum[whichguy] == 4 && Walls[g][c] == 0) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 10;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
      }
      if (b == -1 && ammo[whichguy] > 0 && itemnum[whichguy] == 7 && Walls[g][c] == 0 && lightningdelay[whichguy] <= 0) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        lightningdelay[whichguy] = 0;
        firstshot[whichguy] = 1;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 10;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
      }
      if (b == -1 && ammo[whichguy] > 0 && itemnum[whichguy] == 5 && Walls[g][c] == 0) {
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 31;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootleft;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = 0;
          targetrotation[whichguy] = 90;
        }
      }
      if (itemnum[whichguy] == 6) {
        if (holding[whichguy] == 0) {
          holding[whichguy] = 1;
        }
      }
      if (activity[whichguy] == jetidle) {
        b = -1;
        for (a = 0; a < numplayers; a++) {
          if (absolute(guyx[whichguy] - guyx[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && absolute(guyy[whichguy] - guyy[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && dead[a] == 0 && a != whichguy && guyx[a] >= guyx[whichguy]) {
            b = a;
          }
        }
        if (b == whichguy) {
          b = -1;
        }
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        d = (guyx[b] + 595) / 10;
        e = guyy[b] / -20 - .5 + 40;
        if (b != -1 && rightshootpressed[whichguy] == 0) {
          if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
            if (a == d || Walls[a][c] == 0) {
              fake[whichguy] = 0;
              guyx[b] = guyx[whichguy];
              attacker[b] = whichguy;
              guyy[b] = guyy[whichguy];
              attach[b] = whichguy;
              guyvelx[b] = guyvelx[whichguy];
              guyvely[b] = guyvely[whichguy];
              activity[whichguy] = jetimpaleright;
              anim[whichguy] = 36;
              targetanim[whichguy] = 36;
              activity[b] = jetimpaledright;
              anim[b] = 37;
              targetanim[b] = 37;
              targetframe[whichguy] = 1;
              targetframe[b] = 1;
              frame[whichguy] = 0;
              frame[b] = 0;
              time[whichguy] = 0;
              time[b] = 0;
            }
          }
        }
        if (b == -1 && rightshootpressed[whichguy] == 0 && activity[whichguy] == jetidle) {
          if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
            activity[whichguy] = jetimpaleright;
            anim[whichguy] = 36;
            targetanim[whichguy] = 36;
            targetframe[whichguy] = 1;
            frame[whichguy] = 0;
            time[whichguy] = 0;
            fake[whichguy] = 1;
          }
        }
      }
      if (activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != jetimpaleright) {
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] >= 0 && itemnum[whichguy] <= 1) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            fallin[b] == 1;
            activity[whichguy] = breakneckright;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckright;
            anim[b] = 17;
            targetanim[b] = 17;
            usingjetpack[b] = 0;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
          }
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 4) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckright;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckright;
            anim[b] = 17;
            targetanim[b] = 17;
            usingjetpack[b] = 0;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if ((b != -1 || ammo[whichguy] <= 0) && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 7) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            if (b != -1) {
              guyx[b] = guyx[whichguy];
              attacker[b] = whichguy;
              guyy[b] = guyy[whichguy];
              usingjetpack[b] = 0;
              guyvelx[b] = 0;
              guyvely[b] = 0;
              fallin[b] = 0;
              activity[b] = brokeneckright;
              anim[b] = 17;
              targetanim[b] = 17;
              usingjetpack[b] = 0;
              targetframe[b] = 1;
              frame[b] = 0;
              time[b] = 0;
            }
            activity[whichguy] = breakneckright;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            targetframe[whichguy] = 1;
            frame[whichguy] = 0;
            time[whichguy] = 0;
            if (b == -1) {
              fake[whichguy] = 1;
            }
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 5) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckright;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckright;
            anim[b] = 17;
            targetanim[b] = 17;
            usingjetpack[b] = 0;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 2 && activity[whichguy] != ducking) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            usingjetpack[b] = 0;
            activity[whichguy] = impaleright;
            anim[whichguy] = 18;
            targetanim[whichguy] = 18;
            activity[b] = impaledright;
            anim[b] = 19;
            targetanim[b] = 19;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] == 3 && activity[whichguy] != ducking) {
          if (a == d || Walls[a][c] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[b] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            usingjetpack[b] = 0;
            activity[whichguy] = swordthrowright;
            anim[whichguy] = 20;
            targetanim[whichguy] = 20;
            activity[b] = swordthrownright;
            anim[b] = 21;
            targetanim[b] = 21;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            c = (guyx[whichguy] + 595) / 10;
            f = guyy[whichguy] / -20 - .5 + 40;
            if (Walls[c - 1][f] == 1 || Walls[c - 2][f] == 1) {
              activity[whichguy] = impaleright;
              anim[whichguy] = 18;
              targetanim[whichguy] = 18;
              activity[b] = impaledright;
              anim[b] = 19;
              targetanim[b] = 19;
            }
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] >= 2 && itemnum[whichguy] <= 3 && activity[whichguy] != ducking) {
          activity[whichguy] = impaleright;
          anim[whichguy] = 18;
          targetanim[whichguy] = 18;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] <= 3 && itemnum[whichguy] >= 2 && activity[whichguy] == ducking) {
          fake[whichguy] = 0;
          guyx[b] = guyx[whichguy];
          attacker[b] = whichguy;
          guyy[b] = guyy[whichguy];
          usingjetpack[b] = 0;
          guyvelx[b] = 0;
          guyvely[b] = 0;
          fallin[b] = 0;
          usingjetpack[b] = 0;
          activity[whichguy] = duckimpaleright;
          anim[whichguy] = 38;
          targetanim[whichguy] = 38;
          activity[b] = duckimpaledright;
          anim[b] = 39;
          targetanim[b] = 39;
          targetframe[whichguy] = 1;
          targetframe[b] = 1;
          frame[whichguy] = 0;
          frame[b] = 0;
          time[whichguy] = 0;
          time[b] = 0;
          c = (guyx[whichguy] + 595) / 10;
          f = guyy[whichguy] / -20 - .5 + 40;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && rightshootpressed[whichguy] == 0 && itemnum[whichguy] >= 2 && itemnum[whichguy] <= 3 && activity[whichguy] == ducking) {
          activity[whichguy] = duckimpaleright;
          anim[whichguy] = 38;
          targetanim[whichguy] = 38;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] == 0 && rightshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckright;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] == 1 && ammo[whichguy] <= 0 && rightshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckright;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] >= 4 && itemnum[whichguy] <= 5 && ammo[whichguy] <= 0 && rightshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckright;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
      }
    }
    rightshootpressed[whichguy] = 1;
  }

  if (isKeyDown(kRightShootKey[whichguy]) == 0) {
    rightshootpressed[whichguy] = 0;
  }
  //**********LEFT SHOOT KEY************//
  if (isKeyDown(kLeftShootKey[whichguy])) {
    if (usingjetpack[whichguy] == 0) {
      facing[whichguy] = 0;
    }
    if (activity[whichguy] == jetleft || activity[whichguy] == jetright || activity[whichguy] == jetup) {
      if (itemnum[whichguy] >= 1 && itemnum[whichguy] <= 5) {
        activity[whichguy] = jetidle;
      }
    }
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == falling || activity[whichguy] == jetidle || activity[whichguy] == ducking) {
      b = -1;
      for (a = 0; a < numplayers; a++) {
        if (absolute(guyx[whichguy] - guyx[a]) < 10 && absolute(guyy[whichguy] - guyy[a]) < 5 && dead[a] == 0 && a != whichguy && guyx[a] <= guyx[whichguy]) {
          b = a;
        }
      }
      a = (guyx[whichguy] + 595) / 10;
      c = guyy[whichguy] / -20 - .5 + 40;
      d = (guyx[b] + 595) / 10;
      e = guyy[b] / -20 - .5 + 40;
      f = (guyx[whichguy] + 585) / 10;
      g = ((guyx[whichguy] + 595) / 10) + .2;
      h = ((guyx[whichguy] + 595) / 10) + .9;
      if (b == whichguy) {
        b = -1;
      }
      if (b == -1 && ammo[whichguy] && itemnum[whichguy] == 1 && Walls[h - 2][c] == 0) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 12;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
      }
      if (b == -1 && itemnum[whichguy] == 4 && ammo[whichguy] > 0 && Walls[h - 2][c] == 0) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 12;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
      }
      if (b == -1 && itemnum[whichguy] == 7 && ammo[whichguy] > 0 && Walls[h - 2][c] == 0 && lightningdelay[whichguy] <= 0) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        lightningdelay[whichguy] = 0;
        firstshot[whichguy] = 1;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 12;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
      }
      if (b == -1 && itemnum[whichguy] == 5 && ammo[whichguy] > 0 && Walls[h - 2][c] == 0) {
        a = (guyx[whichguy] + 595) / 10 - .95;
        c = guyy[whichguy] / -20 - .5 + 40;
        if (Walls[a][c] == 0 && activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != ducking) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 32;
          time[whichguy] = 70;
          targetrotation[whichguy] = 0;
        }
        if (Walls[a][c] == 0 && activity[whichguy] == falling) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
        if (Walls[a][c] == 0 && Walls[f][c] == 0 && activity[whichguy] == jetidle) {
          activity[whichguy] = shootright;
          targetframe[whichguy] = 0;
          targetanim[whichguy] = 30;
          time[whichguy] = 100;
          targetrotation[whichguy] = -90;
        }
      }
      if (itemnum[whichguy] == 6) {
        if (holding[whichguy] == 0) {
          holding[whichguy] = 1;
        }
      }
      if (activity[whichguy] == jetidle) {
        b = -1;
        for (a = 0; a < numplayers; a++) {
          if (absolute(guyx[whichguy] - guyx[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && absolute(guyy[whichguy] - guyy[a]) < 5 + absolute(guyvelx[whichguy] * 40) + absolute(guyvelx[a] * 40) + absolute(guyvely[whichguy] * 40) + absolute(guyvely[a] * 40) && dead[a] == 0 && a != whichguy && guyx[a] <= guyx[whichguy]) {
            b = a;
          }
        }
        a = (guyx[whichguy] + 595) / 10;
        c = guyy[whichguy] / -20 - .5 + 40;
        d = (guyx[b] + 595) / 10;
        e = guyy[b] / -20 - .5 + 40;
        if (b == whichguy) {
          b = -1;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0) {
          if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
            if (a == d || Walls[a][c] == 0) {
              fake[whichguy] = 0;
              guyx[b] = guyx[whichguy];
              attacker[b] = whichguy;
              guyy[b] = guyy[whichguy];
              attach[b] = whichguy;
              guyvelx[b] = guyvelx[whichguy];
              guyvely[b] = guyvely[whichguy];
              activity[whichguy] = jetimpaleleft;
              anim[whichguy] = 36;
              targetanim[whichguy] = 36;
              activity[b] = jetimpaledleft;
              anim[b] = 37;
              targetanim[b] = 37;
              targetframe[whichguy] = 1;
              targetframe[b] = 1;
              frame[whichguy] = 0;
              frame[b] = 0;
              time[whichguy] = 0;
              time[b] = 0;
            }
          }
        }
        if (b == -1 && leftshootpressed[whichguy] == 0 && activity[whichguy] == jetidle) {
          if (itemnum[whichguy] == 2 || itemnum[whichguy] == 3) {
            activity[whichguy] = jetimpaleleft;
            anim[whichguy] = 36;
            targetanim[whichguy] = 36;
            targetframe[whichguy] = 1;
            frame[whichguy] = 0;
            time[whichguy] = 0;
            fake[whichguy] = 1;
          }
        }
      }
      if (activity[whichguy] != falling && activity[whichguy] != jetidle && activity[whichguy] != jetimpaleleft) {
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] >= 0 && itemnum[whichguy] <= 1) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckleft;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckleft;
            anim[b] = 17;
            targetanim[b] = 17;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            usingjetpack[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 4) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckleft;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckleft;
            anim[b] = 17;
            targetanim[b] = 17;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            usingjetpack[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if ((b != -1 || ammo[whichguy] <= 0) && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 7) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            if (b != -1) {
              guyx[b] = guyx[whichguy];
              attacker[b] = whichguy;
              guyy[b] = guyy[whichguy];
              usingjetpack[whichguy] = 0;
              guyvelx[b] = 0;
              guyvely[b] = 0;
              fallin[b] = 0;
              time[b] = 0;
              activity[b] = brokeneckleft;
              anim[b] = 17;
              targetanim[b] = 17;
              targetframe[b] = 1;
              frame[b] = 0;
              usingjetpack[b] = 0;
            }
            activity[whichguy] = breakneckleft;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            targetframe[whichguy] = 1;
            frame[whichguy] = 0;
            time[whichguy] = 0;
            if (b == -1) {
              fake[whichguy] = 1;
            }
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 5) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = breakneckleft;
            anim[whichguy] = 16;
            targetanim[whichguy] = 16;
            activity[b] = brokeneckleft;
            anim[b] = 17;
            targetanim[b] = 17;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            usingjetpack[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 2 && activity[whichguy] != ducking) {
          if (a == d || Walls[d][e] == 0) {
            fake[whichguy] = 0;
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = impaleleft;
            anim[whichguy] = 18;
            targetanim[whichguy] = 18;
            activity[b] = impaledleft;
            anim[b] = 19;
            targetanim[b] = 19;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            usingjetpack[b] = 0;
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] >= 2 && itemnum[whichguy] <= 3 && activity[whichguy] != ducking) {
          activity[whichguy] = impaleleft;
          anim[whichguy] = 18;
          targetanim[whichguy] = 18;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] == 3 && activity[whichguy] != ducking) {
          if (a == d || Walls[d][e] == 0) {
            guyx[b] = guyx[whichguy];
            attacker[b] = whichguy;
            guyy[b] = guyy[whichguy];
            usingjetpack[whichguy] = 0;
            guyvelx[b] = 0;
            guyvely[b] = 0;
            fallin[b] = 0;
            activity[whichguy] = swordthrowleft;
            anim[whichguy] = 20;
            targetanim[whichguy] = 20;
            activity[b] = swordthrownleft;
            anim[b] = 21;
            targetanim[b] = 21;
            targetframe[whichguy] = 1;
            targetframe[b] = 1;
            frame[whichguy] = 0;
            frame[b] = 0;
            time[whichguy] = 0;
            time[b] = 0;
            c = (guyx[whichguy] + 595) / 10;
            f = guyy[whichguy] / -20 - .5 + 40;
            if (Walls[c][f] == 1 || Walls[c + 1][f] == 1) {
              activity[whichguy] = impaleleft;
              anim[whichguy] = 18;
              targetanim[whichguy] = 18;
              activity[b] = impaledleft;
              anim[b] = 19;
              targetanim[b] = 19;
            }
          }
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b != -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] <= 3 && itemnum[whichguy] >= 2 && activity[whichguy] == ducking) {
          guyx[b] = guyx[whichguy];
          attacker[b] = whichguy;
          guyy[b] = guyy[whichguy];
          usingjetpack[b] = 0;
          guyvelx[b] = 0;
          guyvely[b] = 0;
          fallin[b] = 0;
          usingjetpack[b] = 0;
          activity[whichguy] = duckimpaleleft;
          anim[whichguy] = 38;
          targetanim[whichguy] = 38;
          activity[b] = duckimpaledleft;
          anim[b] = 39;
          targetanim[b] = 39;
          targetframe[whichguy] = 1;
          targetframe[b] = 1;
          frame[whichguy] = 0;
          frame[b] = 0;
          time[whichguy] = 0;
          time[b] = 0;
          c = (guyx[whichguy] + 595) / 10;
          f = guyy[whichguy] / -20 - .5 + 40;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && leftshootpressed[whichguy] == 0 && itemnum[whichguy] >= 2 && itemnum[whichguy] <= 3 && activity[whichguy] == ducking) {
          activity[whichguy] = duckimpaleleft;
          anim[whichguy] = 38;
          targetanim[whichguy] = 38;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] == 0 && leftshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckleft;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] == 1 && ammo[whichguy] <= 0 && leftshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckleft;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
        if (b == -1 && itemnum[whichguy] >= 4 && itemnum[whichguy] <= 5 && ammo[whichguy] <= 0 && leftshootpressed[whichguy] == 0) {
          activity[whichguy] = breakneckleft;
          anim[whichguy] = 16;
          targetanim[whichguy] = 16;
          targetframe[whichguy] = 1;
          frame[whichguy] = 0;
          time[whichguy] = 0;
          fake[whichguy] = 1;
          // activity[whichguy]=shootright; targetframe[whichguy]=0; targetanim[whichguy]=12; time[whichguy]=70; targetrotation[whichguy]=0;
        }
      }
    }
    leftshootpressed[whichguy] = 1;
  }
  if (isKeyDown(kLeftShootKey[whichguy]) == 0) {
    leftshootpressed[whichguy] = 0;
  }
  //**********LEFT KEY************//
  if (isKeyDown(kLeftKey[whichguy])) {
    facing[whichguy] = 0;
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
      if (anim[whichguy] != 3) {
        activity[whichguy] = runleft;
        targetframe[whichguy] = 1;
        frame[whichguy] = 0;
        anim[whichguy] = 2;
        targetanim[whichguy] = 2;
        time[whichguy] = 100;
      }
    }
    if (activity[whichguy] == onrope) {
      activity[whichguy] = falling;
      targetframe[whichguy] = 0;
      guyvelx[whichguy] = -.1;
      guyvely[whichguy] = -.1;
    }
    if (activity[whichguy] == ducking) {
      activity[whichguy] = leftroll;
      targetframe[whichguy] = 1;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == jetidle || activity[whichguy] == falling || activity[whichguy] == jetup) {
      if (jetpack[whichguy]) {
        activity[whichguy] = jetleft;
        targetframe[whichguy] = 0;
        time[whichguy] = 0;
        targetanim[whichguy] = 34;
      }
    }
  }
  //**********RIGHT KEY************//
  if (isKeyDown(kRightKey[whichguy])) {
    facing[whichguy] = 1;
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
      if (anim[whichguy] != 3) {
        activity[whichguy] = runright;
        targetframe[whichguy] = 1;
        frame[whichguy] = 0;
        anim[whichguy] = 2;
        targetanim[whichguy] = 2;
        time[whichguy] = 100;
      }
    }
    if (activity[whichguy] == onrope) {
      activity[whichguy] = falling;
      targetframe[whichguy] = 0;
      guyvelx[whichguy] = .1;
      guyvely[whichguy] = -.1;
    }
    if (activity[whichguy] == ducking) {
      activity[whichguy] = rightroll;
      targetframe[whichguy] = 1;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == jetidle || activity[whichguy] == falling || activity[whichguy] == jetup) {
      if (jetpack[whichguy]) {
        activity[whichguy] = jetright;
        targetframe[whichguy] = 0;
        time[whichguy] = 0;
        targetanim[whichguy] = 34;
      }
    }
  }
  //**********DOWN KEY************//
  if (isKeyDown(kDownKey[whichguy])) {
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == getupfromback || activity[whichguy] == getupfromfront) {
      if (Map[guymapx[whichguy]][guymapy[whichguy] + 1] != 2 && Map[guymapx[whichguy]][guymapy[whichguy] + 1] != 3) {
        activity[whichguy] = ducking;
        targetframe[whichguy] = 1;
        frame[whichguy] = 0;
        targetanim[whichguy] = 3;
        anim[whichguy] = 3;
        time[whichguy] = 100;
      }
      if (Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 2 || Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 3) {
        frame[whichguy] = 0;
        targetframe[whichguy] = 2;
        guyy[whichguy] -= 4;
        activity[whichguy] = downrope;
        anim[whichguy] = 5;
        targetanim[whichguy] = 5;
        guyx[whichguy] = guymapx[whichguy] * 10 - 590;
        time[whichguy] = 80;
      }
    }
    if (activity[whichguy] == ducking && frame[whichguy] == 2) {
      targetframe[whichguy] = 2;
    }
    if (activity[whichguy] == onrope) {
      if (Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 2 || Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 3 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3 || Map[guymapx[whichguy]][guymapy[whichguy]] == 2) {
        guyvelx[whichguy] = 0;
        guyvely[whichguy] = 0;
        frame[whichguy] = 2;
        targetframe[whichguy] = 2;
        activity[whichguy] = downrope;
        targetanim[whichguy] = 5;
        anim[whichguy] = 5;
        targetframe[whichguy] = 2;
        guyx[whichguy] = guymapx[whichguy] * 10 - 590;
        time[whichguy] = 0;
      }
    }
    if (activity[whichguy] == falling || activity[whichguy] == leftflip || activity[whichguy] == rightflip) {
      if (guyvelx[whichguy] != 0) {
        if (Map[guymapx[whichguy]][guymapy[whichguy]] == 3 || Map[guymapx[whichguy]][guymapy[whichguy]] == 2) {
          if (activity[whichguy] != onrope) {
            frame[whichguy] = 2;
            targetframe[whichguy] = 2;
          }
          guyvelx[whichguy] = 0;
          guyvely[whichguy] = 0;
          activity[whichguy] = downrope;
          targetanim[whichguy] = 5;
          anim[whichguy] = 5;
          targetframe[whichguy] = 2;
          guyx[whichguy] = guymapx[whichguy] * 10 - 590;
          time[whichguy] = 0;
          rotation[whichguy] = 0;
        }
      }
    }
    if (activity[whichguy] == onrope || activity[whichguy] == downrope) {
      guywillbe = (guyy[whichguy] - 15) / -20 - .5 + 40;
      if (Map[guymapx[whichguy]][guymapy[whichguy] + 1] == 0) {
        activity[whichguy] = falling;
        guyvely[whichguy] = -.2;
        targetframe[whichguy] = 0;
      }
      if (Map[guymapx[whichguy]][guywillbe] == 2 && Map[guymapx[whichguy]][guymapy[whichguy]] == 2) {
        activity[whichguy] = falling;
        guyvely[whichguy] = -.2;
        targetframe[whichguy] = 0;
      }
    }
    if (activity[whichguy] == runleft) {
      activity[whichguy] = leftroll;
      targetframe[whichguy] = 0;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == runright) {
      activity[whichguy] = rightroll;
      targetframe[whichguy] = 0;
      time[whichguy] = 0;
    }
  }
  //**********UP KEY************//
  if (isKeyDown(kUpKey[whichguy])) {
    guywillbe = (guyy[whichguy] - 7) / -20 - .5 + 40;
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft || activity[whichguy] == onrope || activity[whichguy] == falling || activity[whichguy] == leftflip || activity[whichguy] == rightflip) {
      if (Map[guymapx[whichguy]][guymapy[whichguy]] == 2 || Map[guymapx[whichguy]][guymapy[whichguy]] == 3 || Map[guymapx[whichguy]][guywillbe] == 2 || Map[guymapx[whichguy]][guywillbe] == 3) {
        if (activity[whichguy] != onrope) {
          frame[whichguy] = 0;
          targetframe[whichguy] = 1;
        }
        guyvelx[whichguy] = 0;
        guyvely[whichguy] = 0;
        activity[whichguy] = climbrope;
        targetanim[whichguy] = 5;
        time[whichguy] = 100;
        guyx[whichguy] = guymapx[whichguy] * 10 - 590;
      }
    }
    if (activity[whichguy] == idle1 || activity[whichguy] == idle2 || activity[whichguy] == swordidleright || activity[whichguy] == swordidleleft || activity[whichguy] == grenidleright || activity[whichguy] == grenidleleft) {
      if (uppressed[whichguy] == 0) {
        activity[whichguy] = jumpstraight;
        frame[whichguy] = 1;
        anim[whichguy] = 6;
        targetanim[whichguy] = 6;
        targetframe[whichguy] = 2;
        time[whichguy] = 0;
      }
    }
    if (activity[whichguy] == runleft && uppressed[whichguy] == 0) {
      activity[whichguy] = leftflip;
      anim[whichguy] = 7;
      targetanim[whichguy] = 7;
      frame[whichguy] = 0;
      targetframe[whichguy] = 1;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == runright && uppressed[whichguy] == 0) {
      activity[whichguy] = rightflip;
      anim[whichguy] = 7;
      targetanim[whichguy] = 7;
      frame[whichguy] = 0;
      targetframe[whichguy] = 1;
      time[whichguy] = 0;
    }
    if (activity[whichguy] == falling && jetpack[whichguy] == 1) {
      if (jetpack[whichguy]) {
        activity[whichguy] = jetup;
        targetanim[whichguy] = 33;
        targetframe[whichguy] = 0;
        time[whichguy] = 100;
      }
    }
    if (activity[whichguy] == jetidle && jetpack[whichguy] == 1) {
      if (jetpack[whichguy]) {
        activity[whichguy] = jetup;
        targetanim[whichguy] = 33;
        targetframe[whichguy] = 0;
        time[whichguy] = 100;
      }
    }
    uppressed[whichguy] = 1;
    if (activity[whichguy] == climbrope && Map[guymapx[whichguy]][guymapy[whichguy]] == 0) {
      activity[whichguy] = onrope;
    }
    if (activity[whichguy] == climbrope && Map[guymapx[whichguy]][guywillbe] == 1 && Map[guymapx[whichguy]][guymapy[whichguy]] != 0 && Map[guymapx[whichguy]][guymapy[whichguy] + 1] != 1) {
      activity[whichguy] = falling;
      nosound = 1;
      guyvely[whichguy] = -.1;
      frame[whichguy] = 0;
    }
  }
  if (isKeyDown(kUpKey[whichguy]) == 0) {
    uppressed[whichguy] = 0;
  }
}

/********************** WIDALY PORT **********************/
// Everything below this line has been ported and should work.
// Everything above this line has not yet been ported.
const Uint32 TARGET_TICKS_PER_FRAME = 16; // About 60fps

void runGameLoop(SDL_Window *window) {
  SDL_Event e;
  int x, y, a, b, c, d;
  int guywillbe;
  float oldmult;
  gQuit = false;

  // Keep doing the event loop while not gQuit
  while (!gQuit) {
    Point3D point2;
    Uint32 startTicks = SDL_GetTicks(); // milliseconds

    while (SDL_PollEvent(&e)) {
      switch (e.type) {
      case SDL_QUIT:
        return;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        int keyID = translateSDLEventToKeyID(e.key);
        if (keyID >= 0) {
          setKeyState(keyID, bool(e.key.state == SDL_PRESSED));
          if (e.key.state == SDL_PRESSED) {
            HandleKeyDown(keyID);
          }
        }
        break;
      }
    }

    // Swap buffers (double buffering)
    if (!nodraw) {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      if (DrawGLScene()) {
        SDL_GL_SwapWindow(window);
      } else {
        gQuit = true;
      }
      oldmult = multiplier;

      gamespeed = 1;
      if (slowdown) {
        gamespeed = .05;
      } // slowmotion toggle
      if (freezetime) {
        gamespeed = 0;
      } // freeze time toggle

      multiplier = oldmult * gamespeed;

      for (x = 0; x < kMaxLightning; x++) {
        Lightning[x].brightness -= multiplier / 100;
        if (Lightning[x].brightness <= 0) {
          Lightning[x].brightness = 0;
        }
      }

      for (x = 0; x < numplayers; x++) {
        multiplier = oldmult * gamespeed;
        multiplier *= speedmult[x];
        multiplier /= 10;
        for (a = 0; a < 10; a++) {
          if (freezetime == 0 && computercontrolled[x] == 0) {
            DoPlayerStuff(x);
          }
          if (freezetime == 0 && computercontrolled[x] != 0) {
            DoAIPlayerStuff(x);
          }
        }
        if (x != 1 || mapeditor == 0) {
          if (dead[x] == 0 || activity[x] != deadfacedown || activity[x] != deadfaceup || health[x] >= 0) {
            if (computercontrolled[x] == 0) {
              DoKeys(x);
            }
            if (computercontrolled[x]) {
              DoAI(x);
              DoAIKeys(x);
            }
          }
        }
      }

      multiplier = oldmult * gamespeed;
      multiplier /= 5;

      for (a = 0; a < 5; a++) {
        if (freezetime == 0) {
          HandleSprites();
        }
      }

      for (a = 0; a < numplayers; a++) {
        while (jetsmokedelay[a] <= 0 && usingjetpack[a] == 1) {
          playSound(SND_JETPACK_ID, absolute(guyvelx[a]) * 20 + absolute(guyvely[a]) * 20 + 14);
          point = FindJetPackPos(a);
          MakeSprite(point.x, point.y, point.z, RangedRandom(50, 100) + 50, smokesprite, RangedRandom(0, 360), RangedRandom(0, 4) + 6, 0, RangedRandom(0, 30) / 10 + (guyvelx[a] * 80), (RangedRandom(10, 20) - 20) / 4 + (guyvely[a] * 100), 0);
          jetsmokedelay[a] += 10;
        }
      }

      multiplier = oldmult * gamespeed;

      // HandleSmokeSprites();

      for (x = 0; x < numplayers; x++) {
        if (activity[x] == jetimpaledright || activity[x] == jetimpaledleft && attach[x] != -1) {
          guyx[x] = guyx[attach[x]];
          guyy[x] = guyy[attach[x]];
          guyvelx[x] = guyvelx[attach[x]];
          guyvely[x] = guyvely[attach[x]];
        }
      }

      multiplier = oldmult;
    }

    Uint32 endTicks = SDL_GetTicks(); // milliseconds
    Uint32 elapsedTicks = endTicks - startTicks;
    if (elapsedTicks < TARGET_TICKS_PER_FRAME) {
      SDL_Delay(TARGET_TICKS_PER_FRAME - elapsedTicks);
    }
    timetaken = endTicks - startTicks;

    framespersecond = 600000000 / timetaken;
    multiplier5 = multiplier4;
    multiplier4 = multiplier3;
    multiplier3 = multiplier2;
    multiplier2 = 300 / framespersecond;
    multiplier = (multiplier2 + multiplier3 + multiplier4 + multiplier5) / 4;

    //**********CAMERA KEYS************//
    if (isKeyDown(KEY_CAMERA_ZOOM_OUT_ID)) {
      z -= 0.3 * multiplier;
      if (freezetime == 1) {
        z -= 1;
      }
    }
    if (isKeyDown(KEY_CAMERA_ZOOM_IN_ID)) {
      z += 0.3 * multiplier;
      if (freezetime == 1) {
        z += 1;
      }
    }
    if (isKeyDown(KEY_CAMERA_ROTATE_UP_ID)) {
      xrot -= 1.0 * multiplier / 4;
      if (freezetime == 1) {
        xrot -= 5;
      }
    }
    if (isKeyDown(KEY_CAMERA_ROTATE_DOWN_ID)) {
      xrot += 1.0 * multiplier / 4;
      if (freezetime == 1) {
        xrot += 5;
      }
    }
    if (isKeyDown(KEY_CAMERA_ROTATE_RIGHT_ID)) {
      yrot += 1.0 * multiplier / 4;
      if (freezetime == 1) {
        yrot += 5;
      }
    }
    if (isKeyDown(KEY_CAMERA_ROTATE_LEFT_ID)) {
      yrot -= 1.0 * multiplier / 4;
      if (freezetime == 1) {
        yrot -= 5;
      }
    }
    if (isKeyDown(KEY_QUIT_ID)) {
      gQuit = true;
    }
    if (isKeyDown(KEY_CAMERA_DOWN_ID)) {
      cameray -= 0.3 * multiplier;
      if (freezetime == 1) {
        cameray -= multiplier / 3;
      }
    }
    if (isKeyDown(KEY_CAMERA_UP_ID)) {
      cameray += 0.3 * multiplier;
      if (freezetime == 1) {
        cameray += multiplier / 3;
      }
    }
    if (isKeyDown(KEY_CAMERA_RIGHT_ID)) {
      camerax += 0.3 * multiplier;
      if (freezetime == 1) {
        camerax += multiplier / 3;
      }
    }
    if (isKeyDown(KEY_CAMERA_LEFT_ID)) {
      camerax -= 0.3 * multiplier;
      if (freezetime == 1) {
        camerax -= multiplier / 3;
      }
    }
    for (a = 0; a <= 20; a++) {
      if (xrot >= 360) {
        xrot -= 360;
      }
      if (xrot < 0) {
        xrot += 360;
      }
    }

    for (a = 0; a <= 20; a++) {
      if (yrot >= 360) {
        yrot -= 360;
      }
      if (yrot < 0) {
        yrot += 360;
      }
    }
  }
}

bool initGame(int screenwidth, int screenheight) {
  glEnable(GL_TEXTURE_2D);

  if (!loadTextures()) {
    printf("Failed loading textures\n");
    return false;
  }

  if (!createFont(TEX_FONT_ID)) {
    printf("Failed creating font\n");
    return false;
  }

  if (!loadSounds()) {
    printf("Failed loading sounds\n");
    return false;
  }

  return true;
}

void disposeGame() {
  freeSounds();
  freeFont();
  freeTextures();
}
