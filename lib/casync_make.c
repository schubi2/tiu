
#include <glib.h>
#include <gio/gio.h>

#include "tiu-internal.h"

gboolean
casync_make (const gchar *inputdir, const gchar *outfile,
	     const gchar *store, GError **error)
{
  g_autoptr (GSubprocess) sproc = NULL;
  GError *ierror = NULL;
  gboolean res = FALSE;
  GPtrArray *args = g_ptr_array_new_full(15, g_free);
  char *usrdir = g_strjoin ("/", inputdir, "usr", NULL);

  g_ptr_array_add(args, g_strdup("casync"));
  g_ptr_array_add(args, g_strdup("make"));
  g_ptr_array_add(args, g_strdup("--exclude-submounts=yes"));
  g_ptr_array_add(args, g_strdup("--compression=zstd"));
  g_ptr_array_add(args, g_strdup("--with=best"));
  if (store)
    {
      g_ptr_array_add(args, g_strdup("--store"));
      g_ptr_array_add(args, g_strdup(store));
    }
  g_ptr_array_add(args, g_strdup(outfile));
  g_ptr_array_add(args, g_strdup(usrdir));

  g_ptr_array_add(args, NULL);

  sproc = g_subprocess_newv((const gchar * const *)args->pdata,
			    G_SUBPROCESS_FLAGS_STDOUT_SILENCE, &ierror);
  if (sproc == NULL)
    {
      g_propagate_prefixed_error(error, ierror, "Failed to start casync: ");
      return FALSE;
    }

  res = g_subprocess_wait_check(sproc, NULL, &ierror);
  if (!res)
    {
      g_propagate_prefixed_error(
				 error,
				 ierror,
				 "Failed to run casync: ");
      return FALSE;
    }

  return TRUE;
}
