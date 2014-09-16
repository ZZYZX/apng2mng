#include <apng2mng.h>

/* set up mng_file_info structure */
void
mng_file_info_init (mng_file_info* ms)
{
	memset(ms, 0, sizeof(*ms));
	ms->identical = -1;
	ms->clone = -1;
	ms->preclone = -1;
}

/* delete single structure mng_file_info */
void mng_file_info_cleanup(mng_file_info* ms)
{
	mng_file_info* fi = ms;

	while (fi)
	{
		mng_file_info* tempi = fi;

		if (fi->image)
		{
			free(fi->image);
			fi->image = 0;
		}

		if (fi->indimg)
		{
			free(fi->indimg);
			fi->indimg = 0;
		}

		if (fi->f)
		{
			fclose(fi->f);
			fi->f = 0;
		}

		fi = fi->next;
		if (tempi != ms)
			free(tempi);
	}
} /* void mng_file_info_cleanup(mng_file_info* ms) */

/* recursively delete mng_file_info */
void mng_file_info_free()
{
	int i;

	if (Infos)
	{
//		for (i = 0; i < cFiles; i++)
		for (i = 0; i < 1; i++) // i < 1 should be i < infoslength
			mng_file_info_cleanup (Infos + i);

		free (Infos);
		Infos = 0;
	}
} /* void mng_file_info_free() */


/* teh codez */

string basename(string filename)
{
  size_t pos = filename.find_last_of("/\\:");
  pos = (pos!=string::npos) ? pos+1 : 0;
  return filename.substr(pos, filename.length() - pos - (filename.find_last_of("\"") != string::npos));
}


string removeExtension(string filename) {
  size_t lastdot = filename.find_last_of(".");

  if (lastdot == string::npos)
    return filename;

  return filename.substr(0, lastdot);
}

/* callbacks for the mng decoder */

/* memory allocation; data must be zeroed */
mng_ptr mymngalloc(mng_size_t len)
{
  return calloc(1, len);
}/* mng_ptr mymngalloc(mng_size_t len) */

/* memory deallocation */
void mymngfree(mng_ptr p, mng_size_t len)
{
  free(p);
} /* void mymngfree(mng_ptr p, mng_size_t len) */

mng_bool mymngopenstream(mng_handle mng)
{
  mngstuff  *mymng;

  /* look up our stream struct */
  mymng = (mngstuff*)mng_get_userdata(mng);

  /* open the file */
  mymng->file = fopen(mymng->filename, mymng->mode);
  if (mymng->file == NULL) {
    fprintf(stderr, "unable to open '%s' for %s\n", mymng->filename, (mymng->mode[0] == 'r' ? "read" : "write"));
    return MNG_FALSE;
  }

  return MNG_TRUE;
} /* mng_bool mymngopenstream(mng_handle mng) */

mng_bool mng_write_stream(mng_handle mng, mng_ptr buffer, mng_uint32 size, mng_uint32p bytes)
{
	mng_file_info* ms;

	ms = (mng_file_info*) mng_get_userdata(mng);

	*bytes = fwrite(buffer, 1, size, ms->f);

	return MNG_TRUE;
} /* mng_bool mng_write_stream(..) */

mng_bool mymngclosestream(mng_handle handle)
{
  /* look up our stream struct */
  mngstuff *mymng = (mngstuff*)mng_get_userdata(handle);

  /* close the file */
  fclose(mymng->file);
  mymng->file = NULL; /* for safety */

  return MNG_TRUE;
} /* mng_bool mymngclosestream(mng_handle handle) */

/* feed data to the decoder */
mng_bool mymngreadstream(mng_handle mng, mng_ptr buffer, mng_uint32 size, mng_uint32 *bytesread)
{
  mngstuff *mymng;

  /* look up our stream struct */
  mymng = (mngstuff*)mng_get_userdata(mng);

  /* read the requested amount of data from the file */
  *bytesread = fread(buffer, 1, size, mymng->file);

  return MNG_TRUE;
}/* mng_bool mymngreadstream(..) */

/* the header's been read. set up the display stuff */
mng_bool mymngprocessheader(mng_handle mng, mng_uint32 width, mng_uint32 height)
{
  mngstuff  *mymng;
  char    title[256];

//  fprintf(stderr, "our mng is %dx%d\n", width,height);

  /* retreive our user data */
  mymng = (mngstuff*)mng_get_userdata(mng);

  /* do stuff to MNG data here */
  return MNG_TRUE;
} /* mng_bool mymngprocessheader(..) */

/* return a row pointer for the decoder to fill */
mng_ptr mymnggetcanvasline(mng_handle mng, mng_uint32 line)
{
  mngstuff  *mymng;
  mng_ptr   row;

  /* dereference our structure */
  mymng = (mngstuff*)mng_get_userdata(mng);

  return row;
} /* mng_ptr mymnggetcanvasline(mng_handle mng, mng_uint32 line) */

/* timer */
mng_uint32 mymnggetticks(mng_handle mng)
{
  mng_uint32 ticks;

//  fprintf(stderr, "  %d\t(returning tick count)\n",ticks);

  return ticks;
} /* mng_uint32 mymnggetticks(mng_handle mng) */

mng_bool mymngrefresh(mng_handle mng, mng_uint32 x, mng_uint32 y, mng_uint32 w, mng_uint32 h)
{
  mngstuff  *mymng;

  /* dereference our structure */
        mymng = (mngstuff*)mng_get_userdata(mng);

  return MNG_TRUE;
} /* mng_bool mymngrefresh(..) */

/* interframe delay callback */
mng_bool mymngsettimer(mng_handle mng, mng_uint32 msecs)
{
  mngstuff  *mymng;

//  fprintf(stderr,"  pausing for %d ms\n", msecs);

  /* look up our stream struct */
        mymng = (mngstuff*)mng_get_userdata(mng);

  return MNG_TRUE;
} /* mng_bool mymngsettimer(mng_handle mng, mng_uint32 msecs) */

mng_bool mymngerror(mng_handle mng, mng_int32 code, mng_int8 severity,
  mng_chunkid chunktype, mng_uint32 chunkseq,
  mng_int32 extra1, mng_int32 extra2, mng_pchar text)
{
  mngstuff  *mymng;
  char    chunk[5];

        /* dereference our data so we can get the filename */
        mymng = (mngstuff*)mng_get_userdata(mng);

  /* pull out the chuck type as a string */
  // FIXME: does this assume unsigned char?
  chunk[0] = (char)((chunktype >> 24) & 0xFF);
  chunk[1] = (char)((chunktype >> 16) & 0xFF);
  chunk[2] = (char)((chunktype >>  8) & 0xFF);
  chunk[3] = (char)((chunktype      ) & 0xFF);
  chunk[4] = '\0';

  /* output the error */
  fprintf(stderr, "error playing '%s' chunk %s (%d):\n",
    mymng->filename, chunk, chunkseq);
  fprintf(stderr, "%s\n", text);

  return (0);
} /* mng_bool mymngerror(..) */

int mymngquit(mng_handle mng)
{
  mngstuff  *mymng;

  /* dereference our data so we can free it */
  mymng = (mngstuff*)mng_get_userdata(mng);

  /* cleanup. this will call mymngclosestream */
  mng_cleanup(&mng);

  /* free our data */
  free(mymng);

} /* int mymngquit(mng_handle mng) */

// int init_mnglib(){
// 
// } /* int init_mnglib() */

int init_libs(){
  cout << "Initializing apngasm " << assembler.version() << endl;

  cout << "Initializing libmng " << MNG_VERSION_TEXT << endl;

  mngstuff   *mymng;

  /* allocate our stream data structure */
  mymng = (mngstuff*)calloc(1, sizeof(*mymng));
  if (mymng == NULL) {
    fprintf(stderr, "could not allocate mng stream structure.\n");
    return false;
  }

  /* set up the mng decoder for our stream */
  mng = mng_initialize(mymng, mymngalloc, mymngfree, MNG_NULL);
  if (mng == MNG_NULL) {
    fprintf(stderr, "could not initialize libmng.\n");
    return false;
  }

  /* set the reading callbacks */
  mng_setcb_errorproc(mng, mymngerror);
  mng_setcb_openstream(mng, mymngopenstream);
  mng_setcb_closestream(mng, mymngclosestream);
  mng_setcb_readdata(mng, mymngreadstream);
  mng_setcb_processheader(mng, mymngprocessheader);

  /* set the writing callbacks */
  mng_setcb_writedata(mng, mng_write_stream);

	mng_set_userdata(mng, &mymng);
  return true;
}/* int init_libs() */

void printerror(){
//MNG_EXT mng_retcode MNG_DECL mng_getlasterror    (mng_handle    hHandle,
  mng_int8     iSeverity;
  mng_chunkid  iChunkname;
  mng_uint32   iChunkseq;
  mng_int32    iExtra1;
  mng_int32    iExtra2;
  mng_pchar    zErrortext;
  mng_getlasterror(mng, &iSeverity, &iChunkname, &iChunkseq, &iExtra1, &iExtra2, &zErrortext);
  cout << "error: " << zErrortext << endl;
}


/* open a APNG file and write the frames into the MNG file pointed by dest */
int apng2mng(string source, string dest){
  string xmlpath = "./" + removeExtension(basename(source)) + ".xml";
  cout << "Performing APNG-to-MNG conversion from " << source << " to " << dest << endl;

#ifdef APNG_READ_SUPPORTED
  vector<apngasm::APNGFrame> frames = assembler.disassemble(source);
  cout << frames.size() << " Frames" << endl;
  cout << "XML file is " << xmlpath << endl;
  assembler.savePNGs("./"); // TODO stream the frames as a vector into libmng here
  assembler.saveXML(xmlpath, "./");
#endif

  mngstuff  *mymng;
  mymng = (mngstuff*)mng_get_userdata(mng);
  mymng->filename = const_cast<char*>(dest.c_str()); /* mng is C-based */
  mymng->mode = "wb"; /* fopen arg */

  int ret;
  ret = mng_create(mng);
  if (ret != MNG_NOERROR)
    //cout << "Could not create " << dest << endl;
    printerror();
  else
    cout << "writing MNG file " << dest << endl;

  //printerror();

  apngasm::APNGFrame *f = &frames[0];

/* create mng file with defaults from the first frame of apng */
  mng_uint32 canvas_width, canvas_height, ticks, layers, framecount;
  canvas_width  = (mng_uint32) f->width();
  canvas_height = (mng_uint32) f->height();
  ticks         = (mng_uint32) ((frames.size() > 1) ? f->delayNum() : 0 ); /* if apng is not static, set mng ticks as the first frame */
  layers        = (mng_uint32) frames.size();
  framecount    = (mng_uint32) frames.size();
//cout << "ticks dn " << f->delayNum() << " dd " <<f->delayDen() << " tix " << 1000*(f->delayNum() / f->delayDen())  << endl;;

  cout << "Adding MHDR ";
  ret = mng_putchunk_mhdr(
      mng, canvas_width, canvas_height, ticks, layers, framecount, ticks*framecount,
      /* file simplicity profile */
      MNG_SIMPLICITY_VALID |
      MNG_SIMPLICITY_SIMPLEFEATURES |
      MNG_SIMPLICITY_COMPLEXFEATURES |
      MNG_SIMPLICITY_DELTAPNG |
      0x240 /* bit6 validity, bit9 Stored object buffers*/
  );
  if(ret != MNG_NOERROR) printerror();

  { /* lets not pollute the namespace */
    //Greyscale 	          0
    //Truecolour 	          2
    //Indexed-colour      	3
    //Greyscale with alpha 	4
    //Truecolour with alpha 6
    string type;
    switch(f->colorType()){
      case 0: type = "Greyscale"; break;
      case 2: type = "Truecolor"; break;
      case 3: type = "Indexed-color"; break;
      case 4: type = "Greyscale w alpha"; break;
      case 6: type = "Truecolor w alpha"; break;
      default: type = "Type unknown"; break;
    }
    cout << "color_type=" << type << "(" << (int)f->colorType() << ")\n";
  } /* colour type information */

  unsigned char ctype = f->colorType();
  if(ctype == 3){ /* PNG specs say PLTE chunk goes 3, 2 and 6 but for 2 and is optional so lets omit those */
    cout << "Adding PLTE size=" << f->paletteSize() << "\n";
    mng_palette8e mng_pal[256];
    apngasm::rgb *apng_pal = f->palette();
    int i;
    for(i = 0; i != 256; i++) {
      mng_pal[i].iRed   = apng_pal->r;
      mng_pal[i].iGreen = apng_pal->g;
      mng_pal[i].iBlue  = apng_pal->b;
      //alpha
    } /* for palette */
    ret = mng_putchunk_plte(mng, f->paletteSize(), mng_pal);
    if(ret != MNG_NOERROR) printerror();
  }/* PNG color type needs PLTE chunk */

  cout << "Adding sRGB\n";
  ret = mng_putchunk_srgb(mng, 0, 0);
  if(ret != MNG_NOERROR) printerror();

  cout << "Adding DEFI objid=" << 1 << endl;
  ret = mng_putchunk_defi(mng, 1, 0, 1, false, 0, 0, false, 0, f->width(), 0, f->height());
  if(ret != MNG_NOERROR) printerror();

  cout << "Adding IHDR w=" << f->width() << ", h=" << f->height() << "\n";
  ret = mng_putchunk_ihdr(mng, f->width(), f->height(), MNG_BITDEPTH_8, f->colorType(),
                          MNG_COMPRESSION_DEFLATE, MNG_FILTER_ADAPTIVE, MNG_INTERLACE_NONE);
                          /* apngasm says those are the default @ apngasm.cpp:1311 */
  if(ret != MNG_NOERROR) printerror();

  zstream.zalloc = Z_NULL;
  zstream.zfree = Z_NULL;
  zstream.opaque = Z_NULL;

  if(deflateInit(&zstream, /* Z_BEST_COMPRESSION */ Z_DEFAULT_COMPRESSION) != Z_OK)
  {
    // synfig::error("%s:%d deflateInit()", __FILE__, __LINE__);
    return false;
  }

  if(zbuffer == NULL)
  {
    zbuffer_len = deflateBound(&zstream,((4*f->width())+1)*f->height());
    zbuffer = (unsigned char*)realloc(zbuffer, zbuffer_len);
  }

  zstream.avail_out = zbuffer_len;
  zstream.next_out  = zbuffer;

//  MNG_EXT mng_retcode MNG_DECL mng_putchunk_idat     (mng_handle       hHandle,
//                                                      mng_uint32       iRawlen,
//                                                      mng_ptr          pRawdata);


  if (deflate(&zstream,Z_FINISH) != Z_STREAM_END)
  {
    // synfig::error("%s:%d deflate()", __FILE__, __LINE__);
    // return;
  }
  if (deflateEnd(&zstream) != Z_OK)
  {
    // synfig::error("%s:%d deflateEnd()", __FILE__, __LINE__);
    // return;
  }
  if (mng != MNG_NULL)
  {
    // mng_putchunk_idat(mng, zstream.next_out-zbuffer, zbuffer);
    // mng_putchunk_iend(mng);
  }

  zstream.next_in = f->pixels();
  zstream.avail_in = (4*f->height())+1;

  if (deflate(&zstream, Z_NO_FLUSH) != Z_OK) {
  }

  cout << "Adding IDAT len=" << zstream.next_out-zbuffer << "\n";
    mng_putchunk_idat(mng, zstream.next_out-zbuffer, zbuffer);
  // ret = mng_putchunk_idat(mng, f->width() * f->height(), f->pixels());
  if(ret != MNG_NOERROR) printerror();

  cout << "Adding IEND\n";
  // ret = mng_putchunk_mend(mng);
  ret = mng_putchunk_iend(mng);
  if(ret != MNG_NOERROR) printerror();

  cout << "Writing.\n";
  ret = mng_write(mng);
  if(ret != MNG_NOERROR) printerror();
  mng_cleanup(&mng);
  if (zbuffer != NULL) { free(zbuffer); zbuffer = NULL; zbuffer_len = 0; }

  if(ret == MNG_NOERROR)
    cout << "Finished." << endl;
  else
    cout << "Something went wrong." << endl;

  return ret;

  // fclose(fdest);

  return true;
} /* int apng2mng() */

int mng2apng(string source, string dest){
  cout << "Performing MNG-to-APNG conversion from " << source << " to " << dest << endl;

  return true;
} /* int mng2apng() */

int identify_file( FILE *fsource){
  char buf[255]; /* buffer for reading source file */
  char format = -1;   /* format of the fsource file */
  fread(buf, sizeof(char), 8, fsource);

  /* file is valid APNG ? */
  if( !memcmp(buf, png_signature, sizeof(png_signature)) ) { // apng2mng
    format = format_apng;
  /* file is not APNG, is it a valid MNG ? */
  } else if( !memcmp(buf, mng_signature, sizeof(mng_signature)) ) { // mng2apng
    format = format_mng;
  /* file is neither APNG nor MNG, die.*/
  }

  fclose(fsource);

  return format;
} /* int identify_file() */


int main(int argc, char* argv[])
{ 
  char sourceformat, outputformat; /* 0 = apng2mng, 1 = mng2apng */
  FILE *fsource;                   /* source file */
  string _destfname;          /* destination file name, should write a MNG file */
  string _sourcefname;        /* source file name, should be APNG format */

  if ( argc < 2 ) { // no arguments provided
    cout << "Error: not enough arguments\n\nUsage: apng2mng image.apng [image.mng]\n\n" << endl;
    exit(EXIT_FAILURE);
  } else if ( (argc == 2) || (argc == 3) ) { // enough arguments
    _sourcefname = argv[1]; 
    _destfname   = (argv[2] ? argv[2] : removeExtension(basename(_sourcefname)) + ".mng") ; /* simple check to get a proper output file string */
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
    case format_apng:
      apng2mng(_sourcefname, _destfname);
      break;

    case format_mng:
      mng2apng(_sourcefname, _destfname);
      break;

    default:
      cout << "Error: " << _sourcefname << " seems to be neither APNG nor MNG file" << endl;
      exit(EXIT_FAILURE);
      break;
  }

  exit(EXIT_SUCCESS);
}

