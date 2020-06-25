/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 */


#include "swcdb/db/Columns/Schema.h"
#include "swcdb/core/Serialization.h"


namespace SWC { namespace DB {


SWC_SHOULD_INLINE
Schema::Ptr Schema::make() {
  return std::make_shared<Schema>();
}

SWC_SHOULD_INLINE
Schema::Ptr Schema::make(const Schema::Ptr& other) {
  return std::make_shared<Schema>(*other.get());
}

Schema::Schema()
      : cid(NO_CID), 
        col_seq(Types::KeySeq::LEXIC), col_type(Types::Column::PLAIN),
        cell_versions(1), cell_ttl(0),
        blk_encoding(Types::Encoding::DEFAULT), blk_size(0), blk_cells(0), 
        cs_replication(0), cs_size(0), cs_max(0), 
        log_rollout_ratio(0),
        compact_percent(0), 
        revision(0) {
}

Schema::Schema(const Schema& other)
      : cid(other.cid), col_name(other.col_name), 
        col_seq(other.col_seq), col_type(other.col_type),
        cell_versions(other.cell_versions), cell_ttl(other.cell_ttl),
        blk_encoding(other.blk_encoding), blk_size(other.blk_size), 
        blk_cells(other.blk_cells), 
        cs_replication(other.cs_replication), cs_size(other.cs_size), 
        cs_max(other.cs_max), 
        log_rollout_ratio(other.log_rollout_ratio),
        compact_percent(other.compact_percent), 
        revision(other.revision) {
}

Schema::Schema(const uint8_t** bufp, size_t* remainp)
  : cid(Serialization::decode_vi64(bufp, remainp)),
    col_name(Serialization::decode_vstr(bufp, remainp)),

    col_seq((Types::KeySeq)Serialization::decode_i8(bufp, remainp)),
    col_type((Types::Column)Serialization::decode_i8(bufp, remainp)),

    cell_versions(Serialization::decode_vi32(bufp, remainp)),
    cell_ttl(Serialization::decode_vi32(bufp, remainp)),

    blk_encoding((Types::Encoding)Serialization::decode_i8(bufp, remainp)),
    blk_size(Serialization::decode_vi32(bufp, remainp)),
    blk_cells(Serialization::decode_vi32(bufp, remainp)),

    cs_replication(Serialization::decode_i8(bufp, remainp)),
    cs_size(Serialization::decode_vi32(bufp, remainp)),
    cs_max(Serialization::decode_i8(bufp, remainp)),

    log_rollout_ratio(Serialization::decode_i8(bufp, remainp)),

    compact_percent(Serialization::decode_i8(bufp, remainp)),

    revision(Serialization::decode_vi64(bufp, remainp)) {
}

Schema::~Schema() {}

bool Schema::equal(const Ptr& other, bool with_rev) {
  return     cid == other->cid
          && col_seq == other->col_seq
          && col_type == other->col_type
          && cell_versions == other->cell_versions
          && cell_ttl == other->cell_ttl
          && blk_encoding == other->blk_encoding
          && blk_size == other->blk_size
          && blk_cells == other->blk_cells
          && cs_replication == other->cs_replication
          && cs_size == other->cs_size
          && cs_max == other->cs_max
          && log_rollout_ratio == other->log_rollout_ratio
          && compact_percent == other->compact_percent
          && col_name.compare(other->col_name) == 0
          && (!with_rev || revision == other->revision)
          ;
}

size_t Schema::encoded_length() const {
  return Serialization::encoded_length_vi64(cid)
       + Serialization::encoded_length_vstr(col_name.length())
       + 2
       + Serialization::encoded_length_vi32(cell_versions)
       + Serialization::encoded_length_vi32(cell_ttl)
       + 1 
       + Serialization::encoded_length_vi32(blk_size)
       + Serialization::encoded_length_vi32(blk_cells)
       + 1
       + Serialization::encoded_length_vi32(cs_size)
       + 3
       + Serialization::encoded_length_vi64(revision);
} 
 
void Schema::encode(uint8_t** bufp) const {
  Serialization::encode_vi64(bufp, cid);
  Serialization::encode_vstr(bufp, col_name.data(), col_name.length());
  
  Serialization::encode_i8(bufp, (uint8_t)col_seq);
  Serialization::encode_i8(bufp, (uint8_t)col_type);

  Serialization::encode_vi32(bufp, cell_versions);
  Serialization::encode_vi32(bufp, cell_ttl);

  Serialization::encode_i8(bufp, (uint8_t)blk_encoding);
  Serialization::encode_vi32(bufp, blk_size);
  Serialization::encode_vi32(bufp, blk_cells);
  
  Serialization::encode_i8(bufp, cs_replication);
  Serialization::encode_vi32(bufp, cs_size);
  Serialization::encode_i8(bufp, cs_max);

  Serialization::encode_i8(bufp, log_rollout_ratio);

  Serialization::encode_i8(bufp, compact_percent);

  Serialization::encode_vi64(bufp, revision);
}

std::string Schema::to_string() const {
  std::stringstream ss;
  display(ss);
  return ss.str();
}

void Schema::display(std::ostream& out) const {
  out 
    << "Schema(" 
    << "cid=" << std::to_string(cid)
    << " name=\"" << col_name << "\""
    << " seq=" << Types::to_string(col_seq)
    << " type=" << Types::to_string(col_type) 

    << " revision=" << std::to_string(revision)
    << " compact=" << std::to_string((int)compact_percent)
    
    << " cell_versions=" << std::to_string(cell_versions)
    << " cell_ttl=" << std::to_string(cell_ttl)
    
    << " blk_encoding=" << Types::to_string(blk_encoding)
    << " blk_size=" << std::to_string(blk_size)
    << " blk_cells=" << std::to_string(blk_cells)
    << " cs_replication=" << std::to_string((int)cs_replication)
    << " cs_size=" << std::to_string(cs_size)
    << " cs_max=" << std::to_string((int)cs_max)
    << " log_rollout=" << std::to_string((int)log_rollout_ratio)
    << ")" ;
}

}}
