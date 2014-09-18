#include "apng2mng.h"

string basename(string filename)
{
  size_t pos = filename.find_last_of("/\\:");
  pos = (pos != string::npos) ? pos+1 : 0;
  return filename.substr(pos, filename.length() - pos - (filename.find_last_of("\"") != string::npos));
}

string removeExtension(string filename)
{
  size_t lastdot = filename.find_last_of(".");

  if (lastdot == string::npos)
    return filename;

  return filename.substr(0, lastdot);
}

int main(int argc, char* argv[])
{ 
  char sourceformat;   /* 0 = apng2mng, 1 = mng2apng */
  FILE *fsource;       /* source file */
  string _destfname;   /* destination file name, should write a MNG file */
  string _sourcefname; /* source file name, should be APNG format */

  if ( argc < 2 ) { // no arguments provided
    cout << "Error: not enough arguments\n\nUsage: apng2mng image.apng [image.mng]\n\n" << endl;
    exit(EXIT_FAILURE);
  } else if ( (argc == 2) || (argc == 3) ) { // enough arguments
    _sourcefname = argv[1];
  } else { // too many arguments
    cout << "Error: too many arguments\n\nUsage: apng2mng image.apng [image.mng]\n\n" << endl;
    exit(EXIT_FAILURE);
  }

  init_libs();

  fsource = fopen(_sourcefname.c_str(), "rb");
  /* if file could not be opened, die */
  if(fsource == NULL) {
    cout << "Coud not open file '" << _sourcefname << "'" << endl;
    exit(EXIT_FAILURE);
  }

  /* everything is groovy, carry on */
  sourceformat = identify_file(fsource);

  /* write MNG or APNG file */
  switch(sourceformat)
  {
    case format_png:
      _destfname = ((argv[2]) ? argv[2] : removeExtension(basename(_sourcefname))) + ".mng";
      apng2mng(_sourcefname, _destfname);
      break;

    case format_mng:
      _destfname = ((argv[2]) ? argv[2] : removeExtension(basename(_sourcefname))) + ".png";
      mng2apng(_sourcefname, _destfname);
      break;

    default:
      cout << "Error: " << _sourcefname << " seems to be neither APNG nor MNG file" << endl;
      exit(EXIT_FAILURE);
      break;
  }

  exit(EXIT_SUCCESS);
}

