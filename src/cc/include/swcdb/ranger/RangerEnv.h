/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swcdb_ranger_RangerEnv_h
#define swcdb_ranger_RangerEnv_h

#include "swcdb/common/sys/Resources.h"
#include "swcdb/fs/Interface.h"
#include "swcdb/common/Files/RgrData.h"

#include "swcdb/db/client/Query/Select.h"
#include "swcdb/db/client/Query/Update.h"

namespace SWC {

namespace Ranger {
class Compaction;
class Columns;
}

class RangerEnv final {  
  public:

  static void init() {
    SWC_ASSERT(m_env == nullptr);
    m_env = std::make_shared<RangerEnv>();
  }

  static void start();

  static void shuttingdown();

  static Files::RgrData* rgr_data() {
    return &m_env->m_rgr_data;
  }

  static bool is_shuttingdown(){
    return m_env->m_shuttingdown;
  }

  static int64_t in_process(){
    return m_env->m_in_process;
  }

  static void in_process(int64_t count){
    m_env->m_in_process += count;
  }

  static RangerEnv* get() {
    return m_env.get();
  }

  static IoContext* maintenance_io() {
    return m_env->mnt_io.get();
  }

  template <typename T_Handler>
  SWC_CAN_INLINE
  static void maintenance_post(T_Handler&& handler)  {
    m_env->mnt_io->post(handler);
  }

  SWC_CAN_INLINE 
  static Resources& res() {
    return m_env->_resources;
  }

  static bool compaction_available();

  static void compaction_schedule(uint32_t ms);
  
  static Ranger::Columns* columns() {
    return m_env->_columns;
  }

  static client::Query::Update* updater() {
    return m_env->_updater.get();
  }

  const Config::Property::V_GUINT8::Ptr      cfg_cs_max;
  const Config::Property::V_GINT32::Ptr      cfg_cs_sz;
  
  const Config::Property::V_GUINT8::Ptr      cfg_log_rollout_ratio;
  
  const Config::Property::V_GUINT8::Ptr      cfg_compact_percent;
  const Config::Property::V_GUINT8::Ptr      cfg_cs_replication;

  const Config::Property::V_GINT32::Ptr      cfg_blk_size;
  const Config::Property::V_GINT32::Ptr      cfg_blk_cells;
  const Config::Property::V_GENUM::Ptr       cfg_blk_enc;
  
  IoContext::Ptr              mnt_io;
  Ranger::Compaction*         _compaction;
  Ranger::Columns*            _columns;
  client::Query::Update::Ptr  _updater;
  Resources                   _resources;

  explicit RangerEnv();

  ~RangerEnv();

  private:
  inline static std::shared_ptr<RangerEnv>  m_env           = nullptr;
  Files::RgrData                            m_rgr_data;
  std::atomic<bool>                         m_shuttingdown  = false;
  std::atomic<int64_t>                      m_in_process    = 0;

  
};

}


#include "swcdb/ranger/db/Columns.h"
#include "swcdb/ranger/db/Compaction.h"



namespace SWC {

RangerEnv::RangerEnv() 
    : cfg_cs_max(
        Env::Config::settings()->get<Config::Property::V_GUINT8>(
          "swc.rgr.Range.CellStore.count.max")),
      cfg_cs_sz(
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.rgr.Range.CellStore.size.max")),
      cfg_log_rollout_ratio(
        Env::Config::settings()->get<Config::Property::V_GUINT8>(
          "swc.rgr.Range.CommitLog.rollout.ratio")),
      cfg_compact_percent(
        Env::Config::settings()->get<Config::Property::V_GUINT8>(
          "swc.rgr.Range.compaction.percent")),
      cfg_cs_replication(
        Env::Config::settings()->get<Config::Property::V_GUINT8>(
          "swc.rgr.Range.CellStore.replication")),
      cfg_blk_size(
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.rgr.Range.block.size")),
      cfg_blk_cells(
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.rgr.Range.block.cells")),
      cfg_blk_enc(
        Env::Config::settings()->get<Config::Property::V_GENUM>(
          "swc.rgr.Range.block.encoding")),
      mnt_io(
        IoContext::make("Maintenance", 
        Env::Config::settings()->get_i32("swc.rgr.maintenance.handlers"))
      ),
      _compaction(nullptr),
      _columns(new Ranger::Columns()),
      _updater(std::make_shared<client::Query::Update>()),  
      _resources(
        Env::IoCtx::io()->ptr(),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.rgr.ram.allowed.percent"),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.rgr.ram.reserved.percent"),
        Env::Config::settings()->get<Config::Property::V_GINT32>(
          "swc.rgr.ram.release.rate"),
        [this](size_t bytes) { return _columns->release(bytes); }) {
}

RangerEnv::~RangerEnv() {
  if(_compaction) 
    delete _compaction;
  delete _columns;
}

void RangerEnv::start() {
  SWC_ASSERT(m_env != nullptr);

  m_env->_compaction = new Ranger::Compaction();
  m_env->_compaction->schedule();
}

void RangerEnv::shuttingdown() {
  m_env->_compaction->stop();
  m_env->mnt_io->stop();
  
  m_env->_updater->commit();
  m_env->_updater->wait();
  
  m_env->_columns->unload_all(false);

  m_env->_resources.stop();

  m_env->m_shuttingdown = true;
}


bool RangerEnv::compaction_available() {
  return m_env->_compaction->available();
}

void RangerEnv::compaction_schedule(uint32_t ms) {
  if(m_env && m_env->_compaction)
    m_env->_compaction->schedule(ms);
}

}

#endif // swcdb_ranger_RangerEnv_h