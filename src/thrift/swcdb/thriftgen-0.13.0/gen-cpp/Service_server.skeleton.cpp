// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Service.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace  ::SWC::Thrift;

class ServiceHandler : virtual public ServiceIf {
 public:
  ServiceHandler() {
    // Your initialization goes here
  }

  /**
   * The direct SQL method to Manage Column
   * 
   * @param sql
   */
  void sql_mng_column(const std::string& sql) {
    // Your implementation goes here
    printf("sql_mng_column\n");
  }

  /**
   * The direct SQL method to List Columns
   * 
   * @param sql
   */
  void sql_list_columns(Schemas& _return, const std::string& sql) {
    // Your implementation goes here
    printf("sql_list_columns\n");
  }

  /**
   * The direct SQL method to Compact Columns
   * 
   * @param sql
   */
  void sql_compact_columns(CompactResults& _return, const std::string& sql) {
    // Your implementation goes here
    printf("sql_compact_columns\n");
  }

  /**
   * The direct SQL method to select cells with result in Cells List.
   * 
   * @param sql
   */
  void sql_select(Cells& _return, const std::string& sql) {
    // Your implementation goes here
    printf("sql_select\n");
  }

  /**
   * The direct SQL method to select cells with result in Columns Cells map.
   * 
   * @param sql
   */
  void sql_select_rslt_on_column(CCells& _return, const std::string& sql) {
    // Your implementation goes here
    printf("sql_select_rslt_on_column\n");
  }

  /**
   * The direct SQL method to select cells with result in Key Cells list.
   * 
   * @param sql
   */
  void sql_select_rslt_on_key(KCells& _return, const std::string& sql) {
    // Your implementation goes here
    printf("sql_select_rslt_on_key\n");
  }

  /**
   * The direct SQL method to select cells with result in Fractons Cells.
   * 
   * @param sql
   */
  void sql_select_rslt_on_fraction(FCells& _return, const std::string& sql) {
    // Your implementation goes here
    printf("sql_select_rslt_on_fraction\n");
  }

  /**
   * The SQL method to select cells with result set by the request's type of CellsResult.
   * 
   * @param sql
   * @param rslt
   */
  void sql_query(CellsGroup& _return, const std::string& sql, const CellsResult::type rslt) {
    // Your implementation goes here
    printf("sql_query\n");
  }

  /**
   * The direct SQL method to update cells optionally to work with updater-id.
   * 
   * @param sql
   * @param updater_id
   */
  void sql_update(const std::string& sql, const int64_t updater_id) {
    // Your implementation goes here
    printf("sql_update\n");
  }

  /**
   * The method to Create an Updater ID with buffering size in bytes.
   * 
   * @param buffer_size
   */
  int64_t updater_create(const int32_t buffer_size) {
    // Your implementation goes here
    printf("updater_create\n");
  }

  /**
   * The method to Close an Updater ID.
   * 
   * @param id
   */
  void updater_close(const int64_t id) {
    // Your implementation goes here
    printf("updater_close\n");
  }

  /**
   * The direct method to update cells with cell in Update-Columns-Cells, optionally to work with updater-id.
   * 
   * @param cells
   * @param updater_id
   */
  void update(const UCCells& cells, const int64_t updater_id) {
    // Your implementation goes here
    printf("update\n");
  }

  /**
   * The direct method to Manage Column
   * 
   * @param func
   * @param schema
   */
  void mng_column(const SchemaFunc::type func, const Schema& schema) {
    // Your implementation goes here
    printf("mng_column\n");
  }

  /**
   * The direct method to List Columns
   * 
   * @param spec
   */
  void list_columns(Schemas& _return, const SpecSchemas& spec) {
    // Your implementation goes here
    printf("list_columns\n");
  }

  /**
   * The direct method to Compact Columns
   * 
   * @param spec
   */
  void compact_columns(CompactResults& _return, const SpecSchemas& spec) {
    // Your implementation goes here
    printf("compact_columns\n");
  }

  /**
   * The direct method to select cells with result in Cells List.
   * 
   * @param spec
   */
  void scan(Cells& _return, const SpecScan& spec) {
    // Your implementation goes here
    printf("scan\n");
  }

  /**
   * The direct method to select cells with result in Columns Cells map.
   * 
   * @param spec
   */
  void scan_rslt_on_column(CCells& _return, const SpecScan& spec) {
    // Your implementation goes here
    printf("scan_rslt_on_column\n");
  }

  /**
   * The direct method to select cells with result in Key Cells list.
   * 
   * @param spec
   */
  void scan_rslt_on_key(KCells& _return, const SpecScan& spec) {
    // Your implementation goes here
    printf("scan_rslt_on_key\n");
  }

  /**
   * The direct method to select cells with result in Fractons Cells.
   * 
   * @param spec
   */
  void scan_rslt_on_fraction(FCells& _return, const SpecScan& spec) {
    // Your implementation goes here
    printf("scan_rslt_on_fraction\n");
  }

  /**
   * The method to select cells with result set by the request's type of CellsResult.
   * 
   * @param spec
   * @param rslt
   */
  void scan_rslt_on(CellsGroup& _return, const SpecScan& spec, const CellsResult::type rslt) {
    // Your implementation goes here
    printf("scan_rslt_on\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<ServiceHandler> handler(new ServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new ServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

