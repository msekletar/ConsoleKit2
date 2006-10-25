/* Generated by dbus-binding-tool; do not edit! */


#ifndef __dbus_glib_marshal_ck_session_MARSHAL_H__
#define __dbus_glib_marshal_ck_session_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_char (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* BOOLEAN:POINTER,POINTER (/tmp/dbus-binding-tool-c-marshallers.FCHLHT:1) */
extern void dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER (GClosure     *closure,
                                                                   GValue       *return_value,
                                                                   guint         n_param_values,
                                                                   const GValue *param_values,
                                                                   gpointer      invocation_hint,
                                                                   gpointer      marshal_data);
void
dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER (GClosure     *closure,
                                                       GValue       *return_value,
                                                       guint         n_param_values,
                                                       const GValue *param_values,
                                                       gpointer      invocation_hint,
                                                       gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__POINTER_POINTER) (gpointer     data1,
                                                             gpointer     arg_1,
                                                             gpointer     arg_2,
                                                             gpointer     data2);
  register GMarshalFunc_BOOLEAN__POINTER_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__POINTER_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_pointer (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* NONE:POINTER (/tmp/dbus-binding-tool-c-marshallers.FCHLHT:2) */
#define dbus_glib_marshal_ck_session_VOID__POINTER	g_cclosure_marshal_VOID__POINTER
#define dbus_glib_marshal_ck_session_NONE__POINTER	dbus_glib_marshal_ck_session_VOID__POINTER

G_END_DECLS

#endif /* __dbus_glib_marshal_ck_session_MARSHAL_H__ */

#include <dbus/dbus-glib.h>
static const DBusGMethodInfo dbus_glib_ck_session_methods[] = {
  { (GCallback) ck_session_get_id, dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER, 0 },
  { (GCallback) ck_session_get_seat_id, dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER, 57 },
  { (GCallback) ck_session_get_session_type, dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER, 117 },
  { (GCallback) ck_session_get_user, dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER, 183 },
  { (GCallback) ck_session_get_x11_display, dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER, 241 },
  { (GCallback) ck_session_get_display_device, dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER, 309 },
  { (GCallback) ck_session_get_host_name, dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER, 387 },
  { (GCallback) ck_session_is_active, dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER, 455 },
  { (GCallback) ck_session_is_local, dbus_glib_marshal_ck_session_BOOLEAN__POINTER_POINTER, 517 },
  { (GCallback) ck_session_activate, dbus_glib_marshal_ck_session_NONE__POINTER, 577 },
  { (GCallback) ck_session_lock, dbus_glib_marshal_ck_session_NONE__POINTER, 624 },
  { (GCallback) ck_session_unlock, dbus_glib_marshal_ck_session_NONE__POINTER, 667 },
};

const DBusGObjectInfo dbus_glib_ck_session_object_info = {
  0,
  dbus_glib_ck_session_methods,
  12,
"org.freedesktop.ConsoleKit.Session\0GetId\0S\0ssid\0O\0F\0N\0o\0\0org.freedesktop.ConsoleKit.Session\0GetSeatId\0S\0sid\0O\0F\0N\0o\0\0org.freedesktop.ConsoleKit.Session\0GetSessionType\0S\0type\0O\0F\0N\0s\0\0org.freedesktop.ConsoleKit.Session\0GetUser\0S\0uid\0O\0F\0N\0i\0\0org.freedesktop.ConsoleKit.Session\0GetX11Display\0S\0display\0O\0F\0N\0s\0\0org.freedesktop.ConsoleKit.Session\0GetDisplayDevice\0S\0display_device\0O\0F\0N\0s\0\0org.freedesktop.ConsoleKit.Session\0GetHostName\0S\0host_name\0O\0F\0N\0s\0\0org.freedesktop.ConsoleKit.Session\0IsActive\0S\0active\0O\0F\0N\0b\0\0org.freedesktop.ConsoleKit.Session\0IsLocal\0S\0local\0O\0F\0N\0b\0\0org.freedesktop.ConsoleKit.Session\0Activate\0A\0\0org.freedesktop.ConsoleKit.Session\0Lock\0A\0\0org.freedesktop.ConsoleKit.Session\0Unlock\0A\0\0\0",
"org.freedesktop.ConsoleKit.Session\0ActiveChanged\0org.freedesktop.ConsoleKit.Session\0Lock\0org.freedesktop.ConsoleKit.Session\0Unlock\0\0",
"\0"
};
