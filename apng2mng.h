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

