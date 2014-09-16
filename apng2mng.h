#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>

#include <apngasm.h>

/* libmng is all split by defines so you need to enable each part on the libmng.h to use */

#if !defined(MNG_SUPPORT_FULL)
#define MNG_SUPPORT_FULL 1
#endif

#if !defined(MNG_SUPPORT_READ)
#define MNG_SUPPORT_READ 1
#endif

#if !defined(MNG_SUPPORT_WRITE)
#define MNG_SUPPORT_WRITE 1
#endif

#if !defined(MNG_SUPPORT_DISPLAY)
#define MNG_SUPPORT_DISPLAY 1
#endif

#if !defined(MNG_ACCESS_CHUNKS)
#define MNG_ACCESS_CHUNKS 1
#endif

#include <libmng.h>

using namespace std;

/* libraries stuff */

/* apng library data */
apngasm::APNGAsm assembler;

/* libmng library handler */
mng_handle mng;

/* this baby will be compressing things for us */
z_stream zstream;
unsigned char* zbuffer = NULL;
unsigned int zbuffer_len = 0;

/* structure for keeping track of our mng stream inside the callbacks */
typedef struct {
  FILE       *file;     /* pointer to the file we're decoding */
  char       *mode;     /* string for fopen mode param */
  char       *filename; /* pointer to the file's path/name */
  mng_uint32  delay;    /* ticks to wait before resuming decode */
} mngstuff;

/* datatype for color */
typedef union
{
	struct
	{
		unsigned char r, g, b, a;
	} bchan;
	unsigned char channels[4];
	unsigned int value;
} RGBA;

/* structure for mng file info */
typedef struct _mng_file_info
{
	FILE* f;
	char* fname;
	char* fmode;
	int w, h;
	int x, y;
	RGBA* image;
	unsigned char* indimg;
	int delay;
	int identical;
	unsigned short objid;
	unsigned short cloneid;
	int clone;
	unsigned short precloneid;
	int preclone;
	struct _mng_file_info* next;
} mng_file_info;

/* pointer to mng_file_info linked list */
mng_file_info* Infos = NULL;



//1982	MNG_EXT mng_retcode MNG_DECL mng_putchunk_mhdr (mng_handle hHandle,
//1983	mng_uint32 iWidth,
//1984	mng_uint32 iHeight,
//1985	mng_uint32 iTicks,
//1986	mng_uint32 iLayercount,
//1987	mng_uint32 iFramecount,
//1988	mng_uint32 iPlaytime,
//1989	mng_uint32 iSimplicity);


//  MNG_EXT mng_retcode MNG_DECL mng_getchunk_srgb     (mng_handle       hHandle,
//                                                      mng_handle       hChunk,
//                                                      mng_bool         *bEmpty,
//                                                      mng_uint8        *iRenderingintent);


//  MNG_EXT mng_retcode MNG_DECL mng_putchunk_defi     (mng_handle       hHandle,
//                                                      mng_uint16       iObjectid,
//                                                      mng_uint8        iDonotshow,
//                                                      mng_uint8        iConcrete,
//                                                      mng_bool         bHasloca,
//                                                      mng_int32        iXlocation,
//                                                      mng_int32        iYlocation,
//                                                      mng_bool         bHasclip,
//                                                      mng_int32        iLeftcb,
//                                                      mng_int32        iRightcb,
//                                                      mng_int32        iTopcb,
//                                                      mng_int32        iBottomcb);


//MNG_EXT mng_retcode MNG_DECL mng_putchunk_ihdr       (mng_handle       hHandle,
//                                                      mng_uint32       iWidth,
//                                                      mng_uint32       iHeight,
//                                                      mng_uint8        iBitdepth,
//                                                      mng_uint8        iColortype,
//                                                      mng_uint8        iCompression,
//                                                      mng_uint8        iFilter,
//                                                      mng_uint8        iInterlace);



/*
#ifdef APNG_WRITE_SUPPORTED
  assembler.reset();

  cout << "Test 4 - start" << endl;
  {
    unsigned char * pData=(unsigned char *)malloc(RES*RES*3);

    apngasm::rgb trans_color = {0, 48, 128};
    Fill(pData, 0, 48, 128);

    Circle(pData, RES, RES, RES, 64, 212, 32);
    Circle(pData, RES, RES-RES/5, RES/5, 255, 0, 0);
    apngasm::APNGFrame frame1 = apngasm::APNGFrame((apngasm::rgb *)pData, RES, RES, &trans_color, 50, 100);
    assembler.addFrame(frame1);

    Circle(pData, RES, RES, RES, 64, 212, 32);
    Circle(pData, RES+RES/5, RES, RES/5, 255, 0, 0);
    apngasm::APNGFrame frame2 = apngasm::APNGFrame((apngasm::rgb *)pData, RES, RES, &trans_color, 50, 100);
    assembler.addFrame(frame2);

    Circle(pData, RES, RES, RES, 64, 212, 32);
    Circle(pData, RES, RES+RES/5, RES/5, 255, 0, 0);
    apngasm::APNGFrame frame3 = apngasm::APNGFrame((apngasm::rgb *)pData, RES, RES, &trans_color, 50, 100);
    assembler.addFrame(frame3);

    Circle(pData, RES, RES, RES, 64, 212, 32);
    Circle(pData, RES-RES/5, RES, RES/5, 255, 0, 0);
    apngasm::APNGFrame frame4 = apngasm::APNGFrame((apngasm::rgb *)pData, RES, RES, &trans_color, 50, 100);
    assembler.addFrame(frame4);

    assembler.assemble("out/circle_anim.png");
    assembler.assemble("out/circle_anim2.png");

    free(pData);
  }
  cout << "Test 4 - finish" << endl;
#endif

  assembler.reset();

  cout << "Test 5 - start" << endl;
  {
    apngasm::APNGFrame frame1 = apngasm::APNGFrame("samples/gold01.png", 15, 100);
    apngasm::APNGFrame frame2 = apngasm::APNGFrame("samples/gold02.png", 15, 100);
    vector<apngasm::APNGFrame> frames;
    frames.push_back(frame1);
    frames.push_back(frame2);
    apngasm::APNGAsm test5Assembler(frames);
    cout << "frames=" << test5Assembler.frameCount() << endl;
    test5Assembler.assemble("out/test5_anim.png");
  }
  cout << "Test 5 - finish" << endl;
*/


