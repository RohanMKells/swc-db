/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/Cells/Result.h"


namespace SWC { namespace DB { namespace Cells {


Result::Result(const uint32_t max_revs, const uint64_t ttl_ns, 
               const Types::Column type)
              : bytes(0), type(type), max_revs(max_revs), 
                ttl(ttl_ns) {
}

Result::Result(Result& other)
              : std::vector<Cell*>(other), bytes(other.bytes), 
                type(other.type), 
                max_revs(other.max_revs), ttl(other.ttl) {
  other.clear();
  other.bytes = 0;
}

Result::~Result() {
  free();
}

void Result::free() {
  for(auto cell : *this)
    if(cell)
      delete cell;
  clear();
  bytes = 0;
}

void Result::reset(const uint32_t revs, const uint64_t ttl_ns, 
                   const Types::Column typ) {
  free();
  configure(revs, ttl_ns, typ);
}

void Result::configure(const uint32_t revs, const uint64_t ttl_ns, 
                       const Types::Column typ) {
  type = typ;
  max_revs = revs;
  ttl = ttl_ns;
}


size_t Result::size_bytes() const {
  return bytes;
}

void Result::take(Result& other) {
  bytes += other.bytes;
  insert(end(), other.begin(), other.end());
  
  other.clear();
  other.bytes = 0;
}

void Result::add(const Cell& cell, bool no_value) {
  Cell* adding;
  push_back(adding = new Cell(cell, no_value));
  bytes += adding->encoded_length();
}

size_t Result::add(const uint8_t* ptr, size_t remain) {
  size_t count = 0;
  bytes += remain;
  while(remain) {
    push_back(new Cell(&ptr, &remain, true));
    ++count;
  }
  return count;
}


Cell* Result::takeout_begin(size_t idx) {
  auto it = begin() + idx;
  Cell* cell = *it;
  erase(it);
  bytes -= cell->encoded_length();
  return cell;
}

Cell* Result::takeout_end(size_t idx) {
  auto it = end() - idx;
  Cell* cell = *it;
  erase(it);
  bytes -= cell->encoded_length();
  return cell;
}


void Result::write(DynamicBuffer& cells) const {
  cells.ensure(bytes);
  for(auto cell : *this) {
    if(!cell->has_expired(ttl))
      cell->write(cells);
  }
}

void Result::write_and_free(DynamicBuffer& cells, uint32_t& cell_count,
                            Interval& intval, uint32_t threshold, 
                            uint32_t max_cells) {
  if(empty())
    return;

  cells.ensure(bytes < threshold? bytes: threshold);
  Cell* first = nullptr;
  Cell* last = nullptr;
  auto it = begin();
  for(Cell* cell; it < end() && (
                  (!threshold || threshold > cells.fill()) && 
                  (!max_cells || max_cells > cell_count) ); ++it) {
    if((cell = *it)->has_expired(ttl))
      continue;

    cell->write(cells);
    intval.expand(cell->timestamp);
    intval.align(cell->key);
    (first ? last : first) = cell;
    ++cell_count;
  }

  if(first) {
    intval.expand_begin(*first);
    intval.expand_end(*(last ? last : first));
  }
  
  if(it == end()) {
    free();
    return;
  }
  auto it_end = it;
  do {
    --it;
    bytes -= (*it)->encoded_length();
    delete *it; 
  } while(it > begin());
  erase(begin(), it_end);
}

void Result::print(std::ostream& out, bool with_cells) const {
  out << "CellsResult(size=" << size()
      << " bytes=" << bytes
      << " type=" << Types::to_string(type)
      << " max_revs=" << max_revs
      << " ttl=" << ttl;
  if(with_cells) {
    out << " cells=[";
    for(auto cell : *this)
      cell->print(out << '\n', type);
    out << "\n]";
  }
  out << ')';
}


}}}