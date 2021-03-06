#ifndef APNG2MNG_H
#define APNG2MNG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>
#include <zlib.h>

#include <apngasm.h>

/* libmng is all split by defines so you need to enable each part on the libmng.h to use */

#if !defined(MNG_SUPPORT_FULL)
#define MNG_SUPPORT_FULL
#endif

#if !defined(MNG_SUPPORT_READ)
#define MNG_SUPPORT_READ
#endif

#if !defined(MNG_SUPPORT_WRITE)
#define MNG_SUPPORT_WRITE
#endif

#if !defined(MNG_SUPPORT_DISPLAY)
#define MNG_SUPPORT_DISPLAY
#endif

#if !defined(MNG_ACCESS_CHUNKS)
#define MNG_ACCESS_CHUNKS
#endif

#include <libmng.h>

using namespace std;

/* Structure for keeping track of our mng stream inside the callbacks */
typedef struct {
  FILE       *file;     /* pointer to the file we're decoding */
  const char *mode;     /* string for fopen mode param */
  char       *filename; /* pointer to the file's path/name */
  mng_uint32  delay;    /* ticks to wait before resuming decode */
} mngstuff;

/* Datatype for color */
typedef union
{
    struct
    {
        unsigned char r, g, b, a;
    } bchan;
    unsigned char channels[4];
    unsigned int value;
} RGBA;

/* Structure for MNG file info */
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

/* private application data */
const unsigned char format_png = 1; /* file is apng */
const unsigned char format_mng = 2; /* file is mng  */
const unsigned char format_jng = 3; /* file is jng  */
// (A)PNG 8-Byte header
static const char png_signature[8] = {(char)0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
// MNG 8-Byte header
static const char mng_signature[8] = {(char)0x8A, 0x4D, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
// MNG 8-Byte header
static const char jng_signature[8] = {(char)0x8B, 0x4A, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

string basename(string filename);
string removeExtension(string filename);

bool init_libs();
int identify_file(FILE *fsource);
int apng2mng(string source, string dest);
int mng2apng(string source, string dest);

#endif



























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
