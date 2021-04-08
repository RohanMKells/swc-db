
/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swcdb_db_client_Query_Update_h
#define swcdb_db_client_Query_Update_h


#include "swcdb/db/client/Query/UpdateHandlerBase.h"
#include "swcdb/db/Types/Range.h"
#include "swcdb/db/Protocol/Mngr/req/RgrGet.h"
#include "swcdb/db/Protocol/Rgr/req/RangeLocate.h"


namespace SWC { namespace client { namespace Query { namespace Update {



void commit(const Handlers::Base::Ptr& hdlr);

void commit(const Handlers::Base::Ptr& hdlr, const cid_t cid);

void commit(const Handlers::Base::Ptr& hdlr, Handlers::Base::Column* colp);



class Committer final : public std::enable_shared_from_this<Committer> {
  public:
  const DB::Types::Range    type;
  const cid_t               cid;
  Handlers::Base::Column*   colp;
  DB::Cell::Key::Ptr        key_start;
  Handlers::Base::Ptr       hdlr;
  ReqBase::Ptr              parent;
  const rid_t               rid;
  const DB::Cell::Key       key_finish;

  Committer(const DB::Types::Range type,
            const cid_t cid,
            Handlers::Base::Column* colp,
            const DB::Cell::Key::Ptr& key_start,
            const Handlers::Base::Ptr& hdlr,
            const ReqBase::Ptr& parent=nullptr,
            const rid_t rid=0) noexcept;

  Committer(const DB::Types::Range type,
            const cid_t cid,
            Handlers::Base::Column* colp,
            const DB::Cell::Key::Ptr& key_start,
            const Handlers::Base::Ptr& hdlr,
            const ReqBase::Ptr& parent,
            const rid_t rid,
            const DB::Cell::Key& key_finish);

  virtual ~Committer() { }

  void print(std::ostream& out);

  void locate_on_manager();

  private:

  void located_on_manager(
      const ReqBase::Ptr& base,
      const Comm::Protocol::Mngr::Params::RgrGetRsp& rsp);

  void locate_on_ranger(
      const Comm::EndPoints& endpoints);

  void located_on_ranger(
      const Comm::EndPoints& endpoints,
      const ReqBase::Ptr& base,
      const Comm::Protocol::Rgr::Params::RangeLocateRsp& rsp);

  void resolve_on_manager();

  void located_ranger(
      const ReqBase::Ptr& base,
      const Comm::Protocol::Mngr::Params::RgrGetRsp& rsp);

  void proceed_on_ranger(
      const ReqBase::Ptr& base,
      const Comm::Protocol::Mngr::Params::RgrGetRsp& rsp);

  void commit_data(
      const Comm::EndPoints& endpoints,
      const ReqBase::Ptr& base);

};


}}}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/client/Query/Update.cc"
#endif


#endif // swcdb_db_client_Query_Update_h
