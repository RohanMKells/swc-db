/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swcdb_db_Cells_Result_h
#define swcdb_db_Cells_Result_h

#include "swcdb/db/Cells/Cell.h"
#include "swcdb/db/Cells/Interval.h"

namespace SWC { namespace DB { namespace Cells {


class Result final : private std::vector<Cell*> {
  public:

  using std::vector<Cell*>::empty;
  using std::vector<Cell*>::capacity;
  using std::vector<Cell*>::reserve;
  using std::vector<Cell*>::size;
  using std::vector<Cell*>::back;
  using std::vector<Cell*>::front;
  using std::vector<Cell*>::begin;
  using std::vector<Cell*>::end;
  using std::vector<Cell*>::operator[];

  size_t            bytes;
  uint64_t          ttl;

  SWC_CAN_INLINE
  explicit Result(const uint64_t ttl_ns=0) noexcept
                  : bytes(0), ttl(ttl_ns) {
  }

  SWC_CAN_INLINE
  explicit Result(Result&& other) noexcept
                  : std::vector<Cell*>(std::move(other)),
                    bytes(other.bytes), ttl(other.ttl) {
    other.bytes = 0;
  }

  Result(const Result& other) = delete;

  Result& operator=(const Result& other) = delete;

  SWC_CAN_INLINE
  ~Result() {
    if(!empty())
      free();
  }

  void free();

  SWC_CAN_INLINE
  size_t size_bytes() const noexcept {
    return bytes;
  }

  void take(Result& other);

  void add(const Cell& cell, bool no_value=false);

  size_t add(const uint8_t* ptr, size_t remain);


  Cell* takeout_begin(size_t idx);

  Cell* takeout_end(size_t idx);


  void write(DynamicBuffer& cells) const;

  void write_and_free(DynamicBuffer& cells, uint32_t& cell_count,
                      Interval& intval, uint32_t threshold,
                      uint32_t max_cells);


  void print(std::ostream& out, Types::Column col_type=Types::Column::PLAIN,
             bool with_cells=false) const;

};



SWC_CAN_INLINE
void Result::free() {
  for(auto cell : *this)
    if(cell)
      delete cell;
  clear();
  bytes = 0;
}

SWC_CAN_INLINE
void Result::take(Result& other) {
  if(empty()) {
    std::vector<Cell*>::operator=(std::move(other));
    bytes = other.bytes;
  } else {
    insert(end(), other.begin(), other.end());
    other.clear();
    bytes += other.bytes;
  }
  other.bytes = 0;
}

SWC_CAN_INLINE
void Result::add(const Cell& cell, bool no_value) {
  Cell* adding = new Cell(cell, no_value);
  push_back(adding);
  bytes += adding->encoded_length();
}

SWC_CAN_INLINE
size_t Result::add(const uint8_t* ptr, size_t remain) {
  size_t count = 0;
  bytes += remain;
  while(remain) {
    push_back(new Cell(&ptr, &remain, true));
    ++count;
  }
  return count;
}


SWC_CAN_INLINE
Cell* Result::takeout_begin(size_t idx) {
  auto it = begin() + idx;
  Cell* cell = *it;
  erase(it);
  bytes -= cell->encoded_length();
  return cell;
}

SWC_CAN_INLINE
Cell* Result::takeout_end(size_t idx) {
  auto it = end() - idx;
  Cell* cell = *it;
  erase(it);
  bytes -= cell->encoded_length();
  return cell;
}



}}}

#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Cells/Result.cc"
#endif

#endif // swcdb_db_Cells_Result_h
