/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2006 William Jon McCann <mccann@jhu.edu>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 */

#include "config.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>

#include <locale.h>

#include <glib.h>
#include <glib/gi18n.h>

#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-lowlevel.h>

#define CK_NAME      "org.freedesktop.ConsoleKit"
#define CK_PATH      "/org/freedesktop/ConsoleKit"
#define CK_INTERFACE "org.freedesktop.ConsoleKit"

#define CK_MANAGER_PATH      "/org/freedesktop/ConsoleKit/Manager"
#define CK_MANAGER_INTERFACE "org.freedesktop.ConsoleKit.Manager"
#define CK_SEAT_INTERFACE    "org.freedesktop.ConsoleKit.Seat"
#define CK_SESSION_INTERFACE "org.freedesktop.ConsoleKit.Session"

static gboolean
get_int (DBusGProxy *proxy,
         const char *method,
         int        *val)
{
        GError  *error;
        gboolean res;

        error = NULL;
	res = dbus_g_proxy_call (proxy,
				 method,
				 &error,
				 G_TYPE_INVALID,
                                 G_TYPE_INT, val,
                                 G_TYPE_INVALID);
        if (! res) {
                g_warning ("%s failed: %s", method, error->message);
                g_error_free (error);
        }

        return res;
}

static gboolean
get_path (DBusGProxy *proxy,
          const char *method,
          char      **str)
{
        GError  *error;
        gboolean res;

        error = NULL;
	res = dbus_g_proxy_call (proxy,
				 method,
				 &error,
				 G_TYPE_INVALID,
                                 DBUS_TYPE_G_OBJECT_PATH, str,
                                 G_TYPE_INVALID);
        if (! res) {
                g_warning ("%s failed: %s", method, error->message);
                g_error_free (error);
        }

        return res;
}

static gboolean
get_string (DBusGProxy *proxy,
            const char *method,
            char      **str)
{
        GError  *error;
        gboolean res;

        error = NULL;
	res = dbus_g_proxy_call (proxy,
				 method,
				 &error,
				 G_TYPE_INVALID,
                                 G_TYPE_STRING, str,
                                 G_TYPE_INVALID);
        if (! res) {
                g_warning ("%s failed: %s", method, error->message);
                g_error_free (error);
        }

        return res;
}

static gboolean
get_boolean (DBusGProxy *proxy,
             const char *method,
             gboolean   *value)
{
        GError  *error;
        gboolean res;

        error = NULL;
	res = dbus_g_proxy_call (proxy,
				 method,
				 &error,
				 G_TYPE_INVALID,
                                 G_TYPE_BOOLEAN, value,
                                 G_TYPE_INVALID);
        if (! res) {
                g_warning ("%s failed: %s", method, error->message);
                g_error_free (error);
        }

        return res;
}

static char *
get_real_name (uid_t uid)
{
        struct passwd *pwent;
        char          *realname;

        realname = NULL;

        pwent = getpwuid (uid);

        if (pwent != NULL) {
                realname = g_strdup (pwent->pw_gecos);
        }

        return realname;
}

static void
list_session (DBusGConnection *connection,
              const char      *ssid)
{
        DBusGProxy *proxy;
        int         uid;
        char       *realname;
        char       *sid;
        char       *session_type;
        char       *xdisplay;
        char       *display_device;
        char       *host_name;
        gboolean    is_active;
        gboolean    is_local;
        char       *short_sid;
        const char *short_ssid;

	proxy = dbus_g_proxy_new_for_name (connection,
                                           CK_NAME,
                                           ssid,
                                           CK_SESSION_INTERFACE);
        if (proxy == NULL) {
                return;
        }

        sid = NULL;
        session_type = NULL;
        xdisplay = NULL;
        host_name = NULL;

        get_int (proxy, "GetUser", &uid);
        get_path (proxy, "GetSeatId", &sid);
        get_string (proxy, "GetSessionType", &session_type);
        get_string (proxy, "GetX11Display", &xdisplay);
        get_string (proxy, "GetDisplayDevice", &display_device);
        get_string (proxy, "GetHostName", &host_name);
        get_boolean (proxy, "IsActive", &is_active);
        get_boolean (proxy, "IsLocal", &is_local);

        realname = get_real_name (uid);

        short_sid = sid;
        short_ssid = ssid;

        if (g_str_has_prefix (sid, CK_PATH "/")) {
                short_sid = sid + strlen (CK_PATH) + 1;
        }
        if (g_str_has_prefix (ssid, CK_PATH "/")) {
                short_ssid = ssid + strlen (CK_PATH) + 1;
        }

        printf ("uid='%d' realname='%s' seat='%s' session='%s' session-type='%s' active=%s x11-display='%s' display-device='%s' host-name='%s' is-local=%s\n",
                uid, realname, short_sid, short_ssid, session_type, is_active ? "TRUE" : "FALSE", xdisplay, display_device, host_name, is_local ? "TRUE" : "FALSE");

        g_free (realname);
        g_free (sid);
        g_free (session_type);
        g_free (xdisplay);
        g_free (display_device);
        g_object_unref (proxy);
}

static void
list_sessions (DBusGConnection *connection,
               const char      *sid)
{
        DBusGProxy *proxy;
        GError     *error;
        gboolean    res;
        GPtrArray  *sessions;
        int         i;

	proxy = dbus_g_proxy_new_for_name (connection,
                                           CK_NAME,
                                           sid,
                                           CK_SEAT_INTERFACE);
        if (proxy == NULL) {
                return;
        }

        sessions = NULL;

        error = NULL;
	res = dbus_g_proxy_call (proxy,
				 "GetSessions",
				 &error,
				 G_TYPE_INVALID,
                                 dbus_g_type_get_collection ("GPtrArray", DBUS_TYPE_G_OBJECT_PATH),
                                 &sessions,
				 G_TYPE_INVALID);
        if (! res) {
                g_warning ("Failed to get list of sessions for %s: %s", sid, error->message);
                g_error_free (error);
                goto out;
        }

        for (i = 0; i < sessions->len; i++) {
                char *ssid;

                ssid = g_ptr_array_index (sessions, i);

                list_session (connection, ssid);

                g_free (ssid);
        }

        g_ptr_array_free (sessions, TRUE);
 out:
        g_object_unref (proxy);
}

static void
list_seats (DBusGConnection *connection)
{
        DBusGProxy *proxy;
        GError     *error;
        gboolean    res;
        GPtrArray  *seats;
        int         i;

        proxy = dbus_g_proxy_new_for_name (connection,
                                           CK_NAME,
                                           CK_MANAGER_PATH,
                                           CK_MANAGER_INTERFACE);
        if (proxy == NULL) {
                return;
        }

        seats = NULL;

        error = NULL;
	res = dbus_g_proxy_call (proxy,
				 "GetSeats",
				 &error,
				 G_TYPE_INVALID,
                                 dbus_g_type_get_collection ("GPtrArray", DBUS_TYPE_G_OBJECT_PATH),
                                 &seats,
				 G_TYPE_INVALID);
        if (! res) {
                g_warning ("Failed to get list of seats: %s", error->message);
                g_error_free (error);
                goto out;
        }

        for (i = 0; i < seats->len; i++) {
                char *sid;

                sid = g_ptr_array_index (seats, i);

                list_sessions (connection, sid);

                g_free (sid);
        }

        g_ptr_array_free (seats, TRUE);
 out:
        g_object_unref (proxy);
}

int
main (int    argc,
      char **argv)
{
        DBusGConnection *connection;

        GOptionContext *context;
        gboolean        retval;
        GError         *error = NULL;
        static gboolean do_version = FALSE;
        static GOptionEntry entries [] = {
                { "version", 'V', 0, G_OPTION_ARG_NONE, &do_version, N_("Version of this application"), NULL },
                { NULL }
        };

        g_type_init ();

        context = g_option_context_new (NULL);
        g_option_context_add_main_entries (context, entries, NULL);
        retval = g_option_context_parse (context, &argc, &argv, &error);

        g_option_context_free (context);

        if (! retval) {
                g_warning ("%s", error->message);
                g_error_free (error);
                exit (1);
        }

        if (do_version) {
                g_print ("%s %s\n", argv [0], VERSION);
                exit (1);
        }

        error = NULL;
        connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
        if (connection == NULL) {
                g_message ("Failed to connect to the D-Bus daemon: %s", error->message);
                g_error_free (error);
                exit (1);
        }

        list_seats (connection);

	return 0;
}