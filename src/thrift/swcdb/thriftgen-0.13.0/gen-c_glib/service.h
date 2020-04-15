/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef SERVICE_H
#define SERVICE_H

#include <thrift/c_glib/processor/thrift_dispatch_processor.h>

#include "service_types.h"

/* Service service interface */
typedef struct _ServiceIf ServiceIf;  /* dummy object */

struct _ServiceIfInterface
{
  GTypeInterface parent;

  gboolean (*sql_mng_column) (ServiceIf *iface, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_list_columns) (ServiceIf *iface, Schemas ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_compact_columns) (ServiceIf *iface, CompactResults ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_select) (ServiceIf *iface, Cells ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_select_rslt_on_column) (ServiceIf *iface, CCells ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_select_rslt_on_key) (ServiceIf *iface, KCells ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_select_rslt_on_fraction) (ServiceIf *iface, FCells ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_query) (ServiceIf *iface, CellsGroup ** _return, const gchar * sql, const CellsResult rslt, Exception ** e, GError **error);
  gboolean (*sql_update) (ServiceIf *iface, const gchar * sql, const gint64 updater_id, Exception ** e, GError **error);
  gboolean (*updater_create) (ServiceIf *iface, gint64* _return, const gint32 buffer_size, Exception ** e, GError **error);
  gboolean (*updater_close) (ServiceIf *iface, const gint64 id, Exception ** e, GError **error);
  gboolean (*update) (ServiceIf *iface, const UCCells * cells, const gint64 updater_id, Exception ** e, GError **error);
};
typedef struct _ServiceIfInterface ServiceIfInterface;

GType service_if_get_type (void);
#define TYPE_SERVICE_IF (service_if_get_type())
#define SERVICE_IF(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SERVICE_IF, ServiceIf))
#define IS_SERVICE_IF(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SERVICE_IF))
#define SERVICE_IF_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), TYPE_SERVICE_IF, ServiceIfInterface))

gboolean service_if_sql_mng_column (ServiceIf *iface, const gchar * sql, Exception ** e, GError **error);
gboolean service_if_sql_list_columns (ServiceIf *iface, Schemas ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_if_sql_compact_columns (ServiceIf *iface, CompactResults ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_if_sql_select (ServiceIf *iface, Cells ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_if_sql_select_rslt_on_column (ServiceIf *iface, CCells ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_if_sql_select_rslt_on_key (ServiceIf *iface, KCells ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_if_sql_select_rslt_on_fraction (ServiceIf *iface, FCells ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_if_sql_query (ServiceIf *iface, CellsGroup ** _return, const gchar * sql, const CellsResult rslt, Exception ** e, GError **error);
gboolean service_if_sql_update (ServiceIf *iface, const gchar * sql, const gint64 updater_id, Exception ** e, GError **error);
gboolean service_if_updater_create (ServiceIf *iface, gint64* _return, const gint32 buffer_size, Exception ** e, GError **error);
gboolean service_if_updater_close (ServiceIf *iface, const gint64 id, Exception ** e, GError **error);
gboolean service_if_update (ServiceIf *iface, const UCCells * cells, const gint64 updater_id, Exception ** e, GError **error);

/* Service service client */
struct _ServiceClient
{
  GObject parent;

  ThriftProtocol *input_protocol;
  ThriftProtocol *output_protocol;
};
typedef struct _ServiceClient ServiceClient;

struct _ServiceClientClass
{
  GObjectClass parent;
};
typedef struct _ServiceClientClass ServiceClientClass;

GType service_client_get_type (void);
#define TYPE_SERVICE_CLIENT (service_client_get_type())
#define SERVICE_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SERVICE_CLIENT, ServiceClient))
#define SERVICE_CLIENT_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_SERVICE_CLIENT, ServiceClientClass))
#define SERVICE_IS_CLIENT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SERVICE_CLIENT))
#define SERVICE_IS_CLIENT_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_SERVICE_CLIENT))
#define SERVICE_CLIENT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SERVICE_CLIENT, ServiceClientClass))

gboolean service_client_sql_mng_column (ServiceIf * iface, const gchar * sql, Exception ** e, GError ** error);
gboolean service_client_send_sql_mng_column (ServiceIf * iface, const gchar * sql, GError ** error);
gboolean service_client_recv_sql_mng_column (ServiceIf * iface, Exception ** e, GError ** error);
gboolean service_client_sql_list_columns (ServiceIf * iface, Schemas ** _return, const gchar * sql, Exception ** e, GError ** error);
gboolean service_client_send_sql_list_columns (ServiceIf * iface, const gchar * sql, GError ** error);
gboolean service_client_recv_sql_list_columns (ServiceIf * iface, Schemas ** _return, Exception ** e, GError ** error);
gboolean service_client_sql_compact_columns (ServiceIf * iface, CompactResults ** _return, const gchar * sql, Exception ** e, GError ** error);
gboolean service_client_send_sql_compact_columns (ServiceIf * iface, const gchar * sql, GError ** error);
gboolean service_client_recv_sql_compact_columns (ServiceIf * iface, CompactResults ** _return, Exception ** e, GError ** error);
gboolean service_client_sql_select (ServiceIf * iface, Cells ** _return, const gchar * sql, Exception ** e, GError ** error);
gboolean service_client_send_sql_select (ServiceIf * iface, const gchar * sql, GError ** error);
gboolean service_client_recv_sql_select (ServiceIf * iface, Cells ** _return, Exception ** e, GError ** error);
gboolean service_client_sql_select_rslt_on_column (ServiceIf * iface, CCells ** _return, const gchar * sql, Exception ** e, GError ** error);
gboolean service_client_send_sql_select_rslt_on_column (ServiceIf * iface, const gchar * sql, GError ** error);
gboolean service_client_recv_sql_select_rslt_on_column (ServiceIf * iface, CCells ** _return, Exception ** e, GError ** error);
gboolean service_client_sql_select_rslt_on_key (ServiceIf * iface, KCells ** _return, const gchar * sql, Exception ** e, GError ** error);
gboolean service_client_send_sql_select_rslt_on_key (ServiceIf * iface, const gchar * sql, GError ** error);
gboolean service_client_recv_sql_select_rslt_on_key (ServiceIf * iface, KCells ** _return, Exception ** e, GError ** error);
gboolean service_client_sql_select_rslt_on_fraction (ServiceIf * iface, FCells ** _return, const gchar * sql, Exception ** e, GError ** error);
gboolean service_client_send_sql_select_rslt_on_fraction (ServiceIf * iface, const gchar * sql, GError ** error);
gboolean service_client_recv_sql_select_rslt_on_fraction (ServiceIf * iface, FCells ** _return, Exception ** e, GError ** error);
gboolean service_client_sql_query (ServiceIf * iface, CellsGroup ** _return, const gchar * sql, const CellsResult rslt, Exception ** e, GError ** error);
gboolean service_client_send_sql_query (ServiceIf * iface, const gchar * sql, const CellsResult rslt, GError ** error);
gboolean service_client_recv_sql_query (ServiceIf * iface, CellsGroup ** _return, Exception ** e, GError ** error);
gboolean service_client_sql_update (ServiceIf * iface, const gchar * sql, const gint64 updater_id, Exception ** e, GError ** error);
gboolean service_client_send_sql_update (ServiceIf * iface, const gchar * sql, const gint64 updater_id, GError ** error);
gboolean service_client_recv_sql_update (ServiceIf * iface, Exception ** e, GError ** error);
gboolean service_client_updater_create (ServiceIf * iface, gint64* _return, const gint32 buffer_size, Exception ** e, GError ** error);
gboolean service_client_send_updater_create (ServiceIf * iface, const gint32 buffer_size, GError ** error);
gboolean service_client_recv_updater_create (ServiceIf * iface, gint64* _return, Exception ** e, GError ** error);
gboolean service_client_updater_close (ServiceIf * iface, const gint64 id, Exception ** e, GError ** error);
gboolean service_client_send_updater_close (ServiceIf * iface, const gint64 id, GError ** error);
gboolean service_client_recv_updater_close (ServiceIf * iface, Exception ** e, GError ** error);
gboolean service_client_update (ServiceIf * iface, const UCCells * cells, const gint64 updater_id, Exception ** e, GError ** error);
gboolean service_client_send_update (ServiceIf * iface, const UCCells * cells, const gint64 updater_id, GError ** error);
gboolean service_client_recv_update (ServiceIf * iface, Exception ** e, GError ** error);
void service_client_set_property (GObject *object, guint property_id, const GValue *value, GParamSpec *pspec);
void service_client_get_property (GObject *object, guint property_id, GValue *value, GParamSpec *pspec);

/* Service handler (abstract base class) */
struct _ServiceHandler
{
  GObject parent;
};
typedef struct _ServiceHandler ServiceHandler;

struct _ServiceHandlerClass
{
  GObjectClass parent;

  gboolean (*sql_mng_column) (ServiceIf *iface, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_list_columns) (ServiceIf *iface, Schemas ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_compact_columns) (ServiceIf *iface, CompactResults ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_select) (ServiceIf *iface, Cells ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_select_rslt_on_column) (ServiceIf *iface, CCells ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_select_rslt_on_key) (ServiceIf *iface, KCells ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_select_rslt_on_fraction) (ServiceIf *iface, FCells ** _return, const gchar * sql, Exception ** e, GError **error);
  gboolean (*sql_query) (ServiceIf *iface, CellsGroup ** _return, const gchar * sql, const CellsResult rslt, Exception ** e, GError **error);
  gboolean (*sql_update) (ServiceIf *iface, const gchar * sql, const gint64 updater_id, Exception ** e, GError **error);
  gboolean (*updater_create) (ServiceIf *iface, gint64* _return, const gint32 buffer_size, Exception ** e, GError **error);
  gboolean (*updater_close) (ServiceIf *iface, const gint64 id, Exception ** e, GError **error);
  gboolean (*update) (ServiceIf *iface, const UCCells * cells, const gint64 updater_id, Exception ** e, GError **error);
};
typedef struct _ServiceHandlerClass ServiceHandlerClass;

GType service_handler_get_type (void);
#define TYPE_SERVICE_HANDLER (service_handler_get_type())
#define SERVICE_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SERVICE_HANDLER, ServiceHandler))
#define IS_SERVICE_HANDLER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SERVICE_HANDLER))
#define SERVICE_HANDLER_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_SERVICE_HANDLER, ServiceHandlerClass))
#define IS_SERVICE_HANDLER_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_SERVICE_HANDLER))
#define SERVICE_HANDLER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SERVICE_HANDLER, ServiceHandlerClass))

gboolean service_handler_sql_mng_column (ServiceIf *iface, const gchar * sql, Exception ** e, GError **error);
gboolean service_handler_sql_list_columns (ServiceIf *iface, Schemas ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_handler_sql_compact_columns (ServiceIf *iface, CompactResults ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_handler_sql_select (ServiceIf *iface, Cells ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_handler_sql_select_rslt_on_column (ServiceIf *iface, CCells ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_handler_sql_select_rslt_on_key (ServiceIf *iface, KCells ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_handler_sql_select_rslt_on_fraction (ServiceIf *iface, FCells ** _return, const gchar * sql, Exception ** e, GError **error);
gboolean service_handler_sql_query (ServiceIf *iface, CellsGroup ** _return, const gchar * sql, const CellsResult rslt, Exception ** e, GError **error);
gboolean service_handler_sql_update (ServiceIf *iface, const gchar * sql, const gint64 updater_id, Exception ** e, GError **error);
gboolean service_handler_updater_create (ServiceIf *iface, gint64* _return, const gint32 buffer_size, Exception ** e, GError **error);
gboolean service_handler_updater_close (ServiceIf *iface, const gint64 id, Exception ** e, GError **error);
gboolean service_handler_update (ServiceIf *iface, const UCCells * cells, const gint64 updater_id, Exception ** e, GError **error);

/* Service processor */
struct _ServiceProcessor
{
  ThriftDispatchProcessor parent;

  /* protected */
  ServiceHandler *handler;
  GHashTable *process_map;
};
typedef struct _ServiceProcessor ServiceProcessor;

struct _ServiceProcessorClass
{
  ThriftDispatchProcessorClass parent;

  /* protected */
  gboolean (*dispatch_call) (ThriftDispatchProcessor *processor,
                             ThriftProtocol *in,
                             ThriftProtocol *out,
                             gchar *fname,
                             gint32 seqid,
                             GError **error);
};
typedef struct _ServiceProcessorClass ServiceProcessorClass;

GType service_processor_get_type (void);
#define TYPE_SERVICE_PROCESSOR (service_processor_get_type())
#define SERVICE_PROCESSOR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SERVICE_PROCESSOR, ServiceProcessor))
#define IS_SERVICE_PROCESSOR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SERVICE_PROCESSOR))
#define SERVICE_PROCESSOR_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), TYPE_SERVICE_PROCESSOR, ServiceProcessorClass))
#define IS_SERVICE_PROCESSOR_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), TYPE_SERVICE_PROCESSOR))
#define SERVICE_PROCESSOR_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SERVICE_PROCESSOR, ServiceProcessorClass))

#endif /* SERVICE_H */
