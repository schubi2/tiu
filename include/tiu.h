/*  Copyright (C) 2022  Thorsten Kukuk <kukuk@suse.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TIUBundle TIUBundle;

typedef enum {
  TIU_USR_BTRFS,
  TIU_USR_AB
} TIUPartSchema;

extern gboolean extract_image(TIUBundle *bundle, const gchar *outputdir,
			      const gchar *store, GError **error);
extern gboolean create_image (const gchar *input, GError **error);
extern gboolean install_system (TIUBundle *bundle, const gchar *device,
                                TIUPartSchema schema,
				const gchar *disk_layout,
				const gchar *store,
				GError **error);
extern gboolean update_system (TIUBundle *bundle,
			       const gchar *store,
			       GError **error);
extern gboolean download_tiu_archive (const gchar *tiuname,
				      const gchar *archive_md5sum,
				      TIUBundle **bundle,
				      GError **error);
extern gboolean check_md5sum(const gchar *filename, const gchar *md5sum);
extern gboolean check_tiu_archive(TIUBundle *bundle, GError **error);
extern gboolean umount_tiu_archive (TIUBundle *bundle, GError **error);
extern gboolean mount_tiu_archive(TIUBundle *bundle, GError **error);

#ifdef __cplusplus
}
#endif
