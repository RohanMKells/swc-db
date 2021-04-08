/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */

#ifndef swcdb_db_client_Query_UpdateHandlerBaseColumnMutable_h
#define swcdb_db_client_Query_UpdateHandlerBaseColumnMutable_h


#include "swcdb/db/client/Query/UpdateHandlerBase.h"
#include "swcdb/core/MutexSptd.h"
#include "swcdb/db/Cells/Mutable.h"


namespace SWC { namespace client { namespace Query { namespace Update {

namespace Handlers {


class ColumnMutable : public Base::Column {
  public:
  typedef std::shared_ptr<ColumnMutable>     Ptr;

  Core::Atomic<int> state_error;
  const cid_t       cid;

  ColumnMutable(const cid_t cid, DB::Types::KeySeq seq,
                uint32_t versions, uint32_t ttl_secs,
                DB::Types::Column type);

  ColumnMutable(const Column&) = delete;

  ColumnMutable(const Column&&) = delete;

  ColumnMutable& operator=(const Column&) = delete;

  virtual ~ColumnMutable() { }

  virtual void print(std::ostream& out) override;

  virtual cid_t get_cid() const noexcept override {
    return cid;
  }

  virtual DB::Types::KeySeq get_sequence() const noexcept override {
    return m_cells.key_seq;
  }

  virtual bool empty() noexcept override;

  virtual size_t size() noexcept override;

  virtual size_t size_bytes() noexcept override;

  virtual DB::Cell::Key::Ptr get_first_key() override;

  virtual DB::Cell::Key::Ptr get_key_next(const DB::Cell::Key& eval_key,
                                          bool start_key=false) override;

  virtual size_t add(const DynamicBuffer& cells,
                     const DB::Cell::Key& upto_key,
                     const DB::Cell::Key& from_key,
                     uint32_t skip, bool malformed) override;

  virtual size_t add(const DynamicBuffer& cells) override;

  virtual void add(const DB::Cells::Cell& cell) override;

  virtual DynamicBuffer::Ptr get_buff(const DB::Cell::Key& key_start,
                                      const DB::Cell::Key& key_end,
                                      size_t buff_sz, bool& more) override;

  virtual void error(int err) noexcept override {
    int at = Error::OK;
    state_error.compare_exchange_weak(at, err);
  }

  virtual bool error() noexcept override {
    return state_error;
  }

  private:
  Core::MutexSptd     m_mutex;
  DB::Cells::Mutable  m_cells;
};




}}}}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/client/Query/UpdateHandlerBaseColumnMutable.cc"
#endif


#endif // swcdb_db_client_Query_UpdateHandlerBaseColumnMutable_h
