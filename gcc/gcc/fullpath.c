/* fullpath.c - fully resolve a pathname.  */

#include "config.h"
#include "system.h"


#ifdef FULL_PATHS_IN_ERRORS
#if !(defined (VMS) || (defined(_WIN32) && !defined(__CYGWIN__)))

extern char *getpwd PROTO((void));

char *
convert_to_full_path(const char *file)
{
  static char *full_path_buffer = 0;
  const char *cwd;
  char *outp, *inp;

  if (file == NULL || file[0] == '/')    /* file already full path */
    return (char *)file;

  cwd = getpwd ();
  if (!cwd)
    return (char *)file;

  if (full_path_buffer == NULL)
    full_path_buffer = xmalloc (2 * MAXPATHLEN + 1);

  strcpy (full_path_buffer, cwd);
  strcat (full_path_buffer, "/");
  strcat (full_path_buffer, file);

  /* Now make a copy of full_path_buffer into full_path_buffer, shortening the
     filename (by taking out slashes and dots) as we go.  */

  outp = inp = full_path_buffer;
  *outp++ = *inp++;        	/* copy first slash */
  for (;;)
    {
      if (!inp[0])
	break;
      /* ??? FIXME: Care for POSIXly correct leading double slash.  */
      else if (inp[0] == '/' && outp[-1] == '/')
	{
	  inp++;
	  continue;
	}
      else if (inp[0] == '.' && outp[-1] == '/')
	{
	  if (!inp[1])
	    break;
	  else if (inp[1] == '/')
	    {
	      inp += 2;
	      continue;
	    }
	  else if ((inp[1] == '.') && (inp[2] == 0 || inp[2] == '/'))
	    {
	      inp += (inp[2] == '/') ? 3 : 2;
	      outp -= 2;
	      while (outp >= full_path_buffer && *outp != '/')
		outp--;
	      if (outp < full_path_buffer)
		{
		  /* Catch cases like /.. where we try to backup to a
		     point above the absolute root of the logical file
		     system.  */

		  return (char *)file;
		}
	      *++outp = '\0';
	      continue;
	    }
	}
      *outp++ = *inp++;
    }

  /* On exit, make sure that there is a trailing null, and make sure that
     the last character of the returned string is *not* a slash.  */

  *outp = '\0';
  if (outp[-1] == '/')
    *--outp  = '\0';

  return full_path_buffer;
}


#else	/* VMS || _WIN32 && !__CYGWIN__ */

char *
convert_to_full_path(const char *file)
{
  return (char *) file;
}

#endif /* VMS || _WIN32 && !__CYGWIN__ */
#endif /* FULL_PATHS_IN_ERRORS */
