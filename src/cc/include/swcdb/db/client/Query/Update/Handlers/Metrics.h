/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swcdb_db_client_Query_Update_Handlers_Metrics_h
#define swcdb_db_client_Query_Update_Handlers_Metrics_h


#include "swcdb/core/Compat.h"
#include "swcdb/db/Cells/CellValueSerialFields.h"
#include "swcdb/db/client/Query/UpdateHandlerBaseSingleColumn.h"


namespace SWC { namespace client { namespace Query { namespace Update {

namespace Handlers {


//! The SWC-DB Update Metric Handler C++ namespace 'SWC::client::Query::Update::Handlers::Metric'
namespace Metric {



static const uint24_t FIELD_ID_MIN   = uint24_t(0);
static const uint24_t FIELD_ID_MAX   = uint24_t(1);
static const uint24_t FIELD_ID_AVG   = uint24_t(2);
static const uint24_t FIELD_ID_COUNT = uint24_t(3);



struct Base {
  typedef std::unique_ptr<Base> Ptr;

  virtual ~Base() { }

  virtual void report(Handlers::Base::Column* colp,
                      const DB::Cell::KeyVec& parent_key) = 0;

  virtual void reset() = 0;

};



class Level : public Base {
  public:
  typedef std::unique_ptr<Level> Ptr;

  const std::string      name;
  std::vector<Base::Ptr> metrics;

  Level(const char* name) : name(name) { }

  virtual ~Level() { }

  virtual void report(Handlers::Base::Column* colp,
                      const DB::Cell::KeyVec& parent_key) override;

  virtual void reset() override;

};



class Item_MinMaxAvgCount : public Base {
  public:
  typedef std::unique_ptr<Item_MinMaxAvgCount> Ptr;

  const std::string name;

  Item_MinMaxAvgCount(const char* name)
      : name(name), m_min(0), m_max(0), m_total(0), m_count(0) { }

  virtual ~Item_MinMaxAvgCount() { }

  void add(uint64_t v);

  virtual void report(Handlers::Base::Column* colp,
                      const DB::Cell::KeyVec& parent_key) override;

  virtual void reset() override;

  protected:

  Core::MutexAtomic m_mutex;
  uint64_t          m_min;
  uint64_t          m_max;
  uint64_t          m_total;
  uint64_t          m_count;

};





class Reporting : public BaseSingleColumn {
  public:

  typedef std::shared_ptr<Reporting> Ptr;

  const Comm::IoContextPtr           io;
  Config::Property::V_GINT32::Ptr    cfg_intval_ms;
  std::vector<Metric::Base::Ptr>     metrics;
  Core::AtomicBool                   running;

  Reporting(const Comm::IoContextPtr& io,
            Config::Property::V_GINT32::Ptr cfg_intval_ms);

  virtual ~Reporting() { }

  virtual void start() {
    bool at = false;
    if(running.compare_exchange_weak(at, true))
      schedule();
  }

  virtual void stop();


  protected:

  Core::MutexSptd m_mutex;

  virtual bool valid() noexcept override {
    return running;
  }

  virtual void response(int err=Error::OK) override;


  private:

  void report();

  void schedule();

  asio::high_resolution_timer m_timer;

};




}}}}}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/client/Query/Update/Handlers/Metrics.cc"
#endif


#endif // swcdb_db_client_Query_Update_Handlers_Metrics_h
