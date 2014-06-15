#include <apngasm.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "mng.h"

std::string basename(std::string filename)
{
  std::size_t pos = filename.find_last_of("/\\:");
  pos = (pos!=std::string::npos) ? pos+1 : 0;
  return filename.substr(pos, filename.length() - pos - (filename.find_last_of("\"") != std::string::npos));
}


std::string removeExtension(std::string filename) {
  size_t lastdot = filename.find_last_of(".");

  if (lastdot == std::string::npos)
    return filename;

  return filename.substr(0, lastdot); 
}

int main(int argc, char* argv[])
{
  apngasm::APNGAsm assembler;
  std::cout << "Initializing apngasm " << assembler.version() << std::endl;

/*
#ifdef APNG_WRITE_SUPPORTED
  std::cout << "Test 1 - start" << std::endl;
  assembler.addFrame("samples/gold01.png", 15, 100);
  assembler.addFrame("samples/gold02.png", 15, 100);
  assembler.addFrame("samples/gold03.png", 15, 100);
  assembler.assemble("out/gold_anim.png");
  assembler.assemble("out/gold_anim2.png");
  std::cout << "frames=" << assembler.frameCount() << std::endl;
  std::cout << "Test 1 - finish" << std::endl;

  assembler.reset();

  std::cout << "Test 2 - start" << std::endl;
  assembler.addFrame("samples/clock1.png", 1, 1);
  assembler.addFrame("samples/clock2.png", 1, 1);
  assembler.addFrame("samples/clock3.png", 1, 1);
  assembler.addFrame("samples/clock4.png", 1, 1);
  assembler.assemble("out/clock_anim.png");
  assembler.assemble("out/clock_anim2.png");
  std::cout << "frames=" << assembler.frameCount() << std::endl;
  std::cout << "Test 2 - finish" << std::endl;
#endif
*/

  // APNG/PNG 8-Byte header
  static const char png_signature[8] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
  //      MNG 8-Byte header
  static const char mng_signature[8] = { 0x8A, 0x4D, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };

  char buf[255], destfname[255];
  FILE *fdest, *fsource;

  if( argc < 2 ) { // no arguments provided
    std::cout << "Error: not enough arguments\n\nUsage: apng2mng image.apng [image.mng]\n\n" << std::endl;
    exit(EXIT_FAILURE);
  } else if( (argc == 2) || (argc == 3) ) { // enough arguments
    if( argc == 3 ) strcpy(destfname, argv[2]); // both arguments supplied
  } else { // too many arguments
    std::cout << "Error: too many argument\n\nUsage: apng2mng image.apng [image.mng]\n\n" << std::endl;
    exit(EXIT_FAILURE);
  }

  // the next step
  // TODO check if file exists here
  fsource = fopen(argv[1], "rb");
  fread(buf, sizeof(char), 8, fsource);

  if( !memcmp(buf, png_signature, sizeof(png_signature)) ) { // apng2mng
    if( destfname == NULL ) {
      std::string _destfname = argv[1];
      _destfname = basename(_destfname);
      _destfname = removeExtension(_destfname);
      // << ".mng"
      strcpy(destfname, _destfname.c_str());
      std::cout << _destfname << std::endl;
    }

    std::cout << "Performing APNG-to-MNG conversion of argv[1] to destfname\n" << std::endl;
  } else if( !memcmp(buf, mng_signature, sizeof(mng_signature)) ) { // mng2apng
    if( destfname == NULL ) {
      std::string _destfname = argv[1];
      _destfname = basename(_destfname);
      _destfname = removeExtension(_destfname);
      // << ".apng"
      strcpy(destfname, _destfname.c_str());
      std::cout << _destfname << std::endl;
    }

    std::cout << "Performing MNG-to-APNG conversion of argv[1] to destfname\n" << std::endl;
  } else {
    std::cout << "Error: wrong input file\n\n" << std::endl;
    exit(EXIT_FAILURE);
  }

  // fdest = fopen(destfname, "wb"); // XXX creates empty files with trashy names

#ifdef APNG_READ_SUPPORTED
  // assembler.reset();

  // TODO determine the file type here (apng or mng)
  // XXX put a warning if it's just 1 frame (and/or a plain png)

  std::cout << "Converting APNG file penguins.apng to penguins.mng..." << std::endl;
  std::vector<apngasm::APNGFrame> frames = assembler.disassemble("penguins.apng");
  std::cout << frames.size() << " Frames" << std::endl;
  assembler.savePNGs("./"); // TODO stream the frames as a vector into libmng here
#if 0 // #ifdef APNG_SPECS_SUPPORTED
  assembler.saveJSON("penguins.json", "./");
  assembler.saveXML("penguins.xml", "./");
#endif
  std::cout << "Done!" << std::endl;
#endif

/*
#ifdef APNG_WRITE_SUPPORTED
  assembler.reset();

  std::cout << "Test 4 - start" << std::endl;
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
  std::cout << "Test 4 - finish" << std::endl;
#endif

  assembler.reset();

  std::cout << "Test 5 - start" << std::endl;
  {
    apngasm::APNGFrame frame1 = apngasm::APNGFrame("samples/gold01.png", 15, 100);
    apngasm::APNGFrame frame2 = apngasm::APNGFrame("samples/gold02.png", 15, 100);
    std::vector<apngasm::APNGFrame> frames;
    frames.push_back(frame1);
    frames.push_back(frame2);
    apngasm::APNGAsm test5Assembler(frames);
    std::cout << "frames=" << test5Assembler.frameCount() << std::endl;
    test5Assembler.assemble("out/test5_anim.png");
  }
  std::cout << "Test 5 - finish" << std::endl;
*/


  fclose(fsource);
  // fclose(fdest);

  exit(EXIT_SUCCESS);
}

