#include <apngasm.h>
#include <iostream>
#include <cstdlib>
#include <mng.h>

int main(int argc, char* argv[])
{
  apngasm::APNGAsm assembler;
  std::cout << "Initializing assembler " << assembler.version() << std::endl;

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

#ifdef APNG_READ_SUPPORTED
  // assembler.reset();

  // TODO determine the file type here (apng or mng)
  // XXX put a warning if it's just 1 frame (or plain png)

  std::cout << "Converting APNG file penguins.apng to penguins.mng..." << std::endl;
  std::vector<apngasm::APNGFrame> frames = assembler.disassemble("penguins.apng");
  std::cout << frames.size() << " Frames" << std::endl;
  assembler.savePNGs("./"); // "out"
#ifdef APNG_SPECS_SUPPORTED
  // XXX add the -s flag to the cli for the spec. files to be saved
  assembler.saveJSON("penguins.json", "./"); // "out"
  assembler.saveXML("penguins.xml", "./"); // "out"
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

  return 0;
}