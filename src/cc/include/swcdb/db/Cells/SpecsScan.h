/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#ifndef swcdb_db_cells_SpecsScan_h
#define swcdb_db_cells_SpecsScan_h

#include "swcdb/core/Serializable.h"
#include "swcdb/db/Cells/SpecsColumn.h"


namespace SWC { namespace DB { namespace Specs {


class Scan final : public Serializable {
  public:

  typedef std::vector<Column::Ptr> Columns;

  explicit Scan(uint32_t reserve=0);

  explicit Scan(Columns& columns);
       
  explicit Scan(const uint8_t** bufp, size_t* remainp);

  void copy(const Scan &other);
  
  ~Scan();

  void free();

  bool equal(const Scan &other);

  size_t internal_encoded_length() const;

  void internal_encode(uint8_t** bufp) const;

  void internal_decode(const uint8_t** bufp, size_t* remainp);

  std::string to_string() const;

  void print(std::ostream& out) const;
  
  void display(std::ostream& out, bool pretty=true, 
               std::string offset = "") const;

  Columns   columns;
  Flags     flags;

};

}}}


#ifdef SWC_IMPL_SOURCE
#include "swcdb/db/Cells/SpecsScan.cc"
#endif 

#endif // swcdb_db_cells_SpecsScan_h
