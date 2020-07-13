/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */


#include "swcdb/db/client/sql/QuerySelect.h"
#include "swcdb/core/Time.h"


namespace SWC { namespace client { namespace SQL {

namespace {
    
  static const char     TOKEN_SELECT[] = "select";
  static const uint8_t  LEN_SELECT = 6;
  static const char     TOKEN_DUMP[] = "dump";
  static const uint8_t  LEN_DUMP = 4;
  static const char     TOKEN_WHERE[] = "where";
  static const uint8_t  LEN_WHERE = 5;
  static const char     TOKEN_COL[] = "col";
  static const uint8_t  LEN_COL = 3;
  static const char     TOKEN_CELLS[] = "cells";
  static const uint8_t  LEN_CELLS = 5;

  
  static const char     TOKEN_RANGE[] = "range";
  static const uint8_t  LEN_RANGE = 5;
  static const char     TOKEN_KEY[] = "key";
  static const uint8_t  LEN_KEY = 3;
  static const char     TOKEN_VALUE[] = "value";
  static const uint8_t  LEN_VALUE = 5;
  static const char     TOKEN_TIMESTAMP[] = "timestamp";
  static const uint8_t  LEN_TIMESTAMP = 9;
  static const char     TOKEN_OFFSET_KEY[] = "offset_key";
  static const uint8_t  LEN_OFFSET_KEY = 10;
  static const char     TOKEN_OFFSET_REV[] = "offset_rev";
  static const uint8_t  LEN_OFFSET_REV = 10;

  static const char     TOKEN_LIMIT[] = "limit";
  static const uint8_t  LEN_LIMIT = 5;
  static const char     TOKEN_OFFSET[] = "offset";
  static const uint8_t  LEN_OFFSET = 6;
  static const char     TOKEN_MAX_VERS[] = "max_versions";
  static const uint8_t  LEN_MAX_VERS = 12;
  static const char     TOKEN_MAX_BUFF[] = "max_buffer";
  static const uint8_t  LEN_MAX_BUFF = 10;
  static const char     TOKEN_ONLY_DELETES[] = "only_deletes";
  static const uint8_t  LEN_ONLY_DELETES = 12;
  static const char     TOKEN_ONLY_KEYS[] = "only_keys";
  static const uint8_t  LEN_ONLY_KEYS = 9;

}

QuerySelect::QuerySelect(const std::string& sql, DB::Specs::Scan& specs, 
                         std::string& message)
                        : Reader(sql, message), specs(specs) {
}

int QuerySelect::parse_select() {

    bool token_cmd = false;
    bool token_where = false;

    while(remain && !err && (!token_cmd || !token_where)) {
      if(!token_cmd) {
        expect_token(TOKEN_SELECT, LEN_SELECT, token_cmd);
        continue;
      }
      if(!token_where) {
        expect_token(TOKEN_WHERE, LEN_WHERE, token_where);
        continue;
      }
      --remain;
      ++ptr;
    }

    if(remain && !err)
      read_columns_intervals();

    if(remain && !err) {
      read_flags(specs.flags);
      if(specs.flags.was_set) {
        // apply global-scope flags to cells_intervals
        for(auto& col : specs.columns) {
          for(auto& intval : col->intervals) {
            if(!intval->flags.was_set)
              intval->flags.copy(specs.flags);
          }
        }
      }
    } 
    return err;
}

int QuerySelect::parse_dump(std::string& filepath) {

    //dump col='ID|NAME' into 'filepath.ext'
    // where [cells=(Interval Flags) AND];
    bool token_cmd = false;
    bool token_col = false;

    while(remain && !err && found_space());
    expect_token(TOKEN_DUMP, LEN_DUMP, token_cmd);
    if(err) 
      return err;
    while(remain && !err && found_space());
    expect_token(TOKEN_COL, LEN_COL, token_col);
    if(err) 
      return err;

    expect_eq();
    if(err) 
      return err;
    std::string col;
    read(col);
    if(!err && col.empty())
      error_msg(Error::SQL_PARSE_ERROR, "missing col 'id|name'");
    if(err) 
      return err;
    cid_t cid = add_column(col);
    if(err) 
      return err;

    bool into = false;
    while(remain && !err && found_space());
    expect_token("into", 4, into);
    if(err) 
      return err;  
      
    read(filepath);
    if(!err && filepath.empty())
      error_msg(Error::SQL_PARSE_ERROR, "missing 'filepath'");
    if(err) 
      return err;  


    while(remain && !err && found_space());
    if(found_token(TOKEN_WHERE, LEN_WHERE)) {
      std::vector<cid_t> cols = {cid};
      read_cells_intervals(cols);
      
      for(auto& col : specs.columns)
        if(!col->intervals.size()) {
          error_msg(Error::SQL_PARSE_ERROR, "missing cells-intervals");
          return err;
        }

    } else {
      for(auto& col : specs.columns)
        col->intervals.push_back(DB::Specs::Interval::make_ptr());
    }

    return err;
}

void QuerySelect::parse_output_flags(uint8_t& output_flags) {
    bool any = true;
    while(any && remain && !err) {
      if(found_space())
        continue;    

      if((any = found_token("OUTPUT_NO_TS", 12))) {
        output_flags |= DB::OutputFlag::NO_TS;
        continue;
      }
      if((any = found_token("OUTPUT_NO_VALUE", 15))) {
        output_flags |= DB::OutputFlag::NO_VALUE;
        continue;
      }
    }
}

void QuerySelect::parse_display_flags(uint8_t& display_flags) {

    bool any = true;
    while(any && remain && !err) {
      if(found_space())
        continue;    

      if((any = found_token("DISPLAY_TIMESTAMP", 17))) {
        display_flags |= DB::DisplayFlag::TIMESTAMP;
        continue;
      }
      if((any = found_token("DISPLAY_DATETIME", 16))) {
        display_flags |= DB::DisplayFlag::DATETIME;
        continue;
      }
      if((any = found_token("DISPLAY_BINARY", 14))) {
        display_flags |= DB::DisplayFlag::BINARY;
        continue;
      }
      if((any = found_token("DISPLAY_SPECS", 13))) {
        display_flags |= DB::DisplayFlag::SPECS;
        continue;
      }
      if((any = found_token("DISPLAY_STATS", 13))) {
        display_flags |= DB::DisplayFlag::STATS;
        continue;
      }
      if((any = found_token("DISPLAY_COLUMN", 14))) {
        display_flags |= DB::DisplayFlag::COLUMN;
        continue;
      }
    }
}

QuerySelect::~QuerySelect() {}

void QuerySelect::read_columns_intervals() {
    bool token_col = false;
    bool bracket_round = false;
    bool eq = false;
    bool col_names_set = false;
    bool processed = false;
    bool possible_and = false;
    Condition::Comp comp;
    std::vector<DB::Schemas::Pattern> schema_patterns;

    std::string col_name;
    std::vector<cid_t> cols;

    while(remain && !err) {
      if(found_space())
        continue;
      if(possible_and) {
        if(found_token(TOKEN_AND, LEN_AND))
          possible_and = false;
        else
          break;
      }

      if(!token_col) {
        expect_token(TOKEN_COL, LEN_COL, token_col);
        continue;
      }

      if(token_col && !col_names_set) {
        //"col(, 1 2 ,re"aa$, =^"Ds", "3 4")" => ["1","2", [patterns], "3 4"]
        if(found_space())
          continue;
        
        if(!bracket_round) {
          expect_token("(", 1, bracket_round);
          continue;
        }
        
        if(found_char(','))
          continue;

        if(found_char(')')) {
          if(!schema_patterns.empty()) {
            add_column(schema_patterns, cols);
            schema_patterns.clear();
          }

          if(cols.empty()) {
            error_msg(Error::SQL_PARSE_ERROR, "missing col 'id|name'");
            break;
          }
          bracket_round = false;
          col_names_set = true;
          continue;

        } else if(remain <= 1) {
          error_msg(Error::SQL_PARSE_ERROR, "missing ')'");
          break;
        }

        found_comparator(comp = Condition::NONE, true);
        read(col_name, ",)", comp == Condition::RE);
        if(comp != Condition::NONE) {
          if(col_name.empty()) {
            error_msg(
              Error::SQL_PARSE_ERROR, 
              "expected column name(expression) after comparator"
            );
            break;
          }
          schema_patterns.emplace_back(comp, col_name);
        } else if(!col_name.empty()) {
          cols.push_back(add_column(col_name));
        }
        col_name.clear();
        continue;
      }
      
      if(col_names_set) {

        if(!processed) {
          
          if(!eq) {
            expect_token("=", 1, eq);
            continue;
          }
          if(!bracket_round) {
            expect_token("(", 1, bracket_round);
            continue;
          }

          read_cells_intervals(cols);
          cols.clear();

          bracket_round = false;
          eq = false;
          processed = true;
          continue;
        }
        
        if(!bracket_round) {
          expect_token(")", 1, bracket_round);
          continue;
        }

        col_names_set = false;
        bracket_round = false;
        processed = false;
        token_col = false;
        possible_and = true;
      }
      
    }

}

cid_t QuerySelect::add_column(const std::string& col) {
    auto schema = get_schema(col);
    if(err)
      return DB::Schema::NO_CID;
    for(auto& col : specs.columns) {
      if(schema->cid == col->cid) 
        return schema->cid;
    }
    specs.columns.push_back(DB::Specs::Column::make_ptr(schema->cid, {}));
    return schema->cid;
}

void QuerySelect::add_column(const std::vector<DB::Schemas::Pattern>& patterns, 
                             std::vector<cid_t>& cols) {
  auto schemas = get_schema(patterns);
  if(err)
    return;
    
  bool found;
  for(auto& schema : schemas) {
    found = false;
    for(auto& col : specs.columns) {
      if((found = schema->cid == col->cid)) 
        break;
    }
    if(!found)
      specs.columns.push_back(DB::Specs::Column::make_ptr(schema->cid, {}));
    cols.push_back(schema->cid);
  }
}

void QuerySelect::read_cells_intervals(const std::vector<cid_t>& cols) {

    bool token_cells = false;
    bool bracket_round = false;
    bool eq = false;
    bool processed = false;
    bool possible_and = false;

    while(remain && !err) {
      if(possible_and) {
        if(found_space())
          continue;
        if(found_token(TOKEN_AND, LEN_AND))
          possible_and = false;
        else
          break;
      }
      if(!token_cells) {
        expect_token(TOKEN_CELLS, LEN_CELLS, token_cells);
        continue;
      }
      
      if(!processed) {

        if(!eq) {
          expect_token("=", 1, eq);
          continue;
        }
        if(!bracket_round) {
          expect_token("(", 1, bracket_round);
          continue;
        }

        auto spec = DB::Specs::Interval::make_ptr();
        read_cells_interval(*spec.get());
        
        for(auto& col : specs.columns) {
          for(cid_t cid : cols) {
            if(col->cid == cid)
              col->intervals.push_back(DB::Specs::Interval::make_ptr(spec));
          }
        }

        bracket_round = false;
        eq = false;
        processed = true;
        continue;
      }
        
      if(!bracket_round) {
        expect_token(")", 1, bracket_round);
        continue;
      }
      bracket_round = false;
      processed = false;
      token_cells = false;
      possible_and = true;
    }

}
  
void QuerySelect::read_cells_interval(DB::Specs::Interval& spec) {

    uint32_t escape = 0;
    bool quote_1 = false;
    bool quote_2 = false;
    bool is_quoted = false;
    bool possible_and = false;
    bool found_any = false;
    bool flw_and = false;
    uint32_t base_remain = remain;
    const char* base_rptr = ptr;
    
    while(remain && !err) {

      if(possible_and) {        
        found_any = true;
        if(found_space())
          continue;
        if(found_token(TOKEN_AND, LEN_AND)) {
          possible_and = false;
          flw_and = true;
        } else
          break;
      }
      
      if(!escape && found_char('\\')) {
        escape = remain;
        continue;
      } else if(escape && escape != remain)
        escape = 0;

      if(!escape) {
        if(((!is_quoted || quote_1) && found_quote_single(quote_1)) || 
           ((!is_quoted || quote_2) && found_quote_double(quote_2))) {
          is_quoted = quote_1 || quote_2;
          continue;
        }
        if(found_space())
          continue;
      }
      
      if(is_quoted) {
        ++ptr;
        --remain;
        continue;
      }

      if(found_token(TOKEN_RANGE, LEN_RANGE)) {        
        read_range(spec.range_begin, spec.range_end, flw_and);
        possible_and = true;
        continue;
      }

      if(!found_token(TOKEN_ONLY_KEYS, LEN_ONLY_KEYS) && 
          found_token(TOKEN_KEY, LEN_KEY)) {
        read_key(spec.key_start, spec.key_finish, flw_and, spec.key_eq);
        possible_and = true;
        continue;
      }

      if(found_token(TOKEN_TIMESTAMP, LEN_TIMESTAMP)) {
        read_timestamp(spec.ts_start, spec.ts_finish, flw_and);
        possible_and = true;
        continue;
      }

      if(found_token(TOKEN_VALUE, LEN_VALUE)) {
        read_value(spec.value);
        possible_and = true;
        continue;
      }

      if(found_token(TOKEN_OFFSET_KEY, LEN_OFFSET_KEY)) {
        expect_eq();
        Reader::read_key(spec.offset_key);
        possible_and = true;
        continue;
      }

      if(found_token(TOKEN_OFFSET_REV, LEN_OFFSET_REV)) {
        expect_eq();
        std::string buf;
        read(buf);
        if(err) 
          return;
        spec.offset_rev = Time::parse_ns(err, buf);
        if(err) {
          error_msg(Error::SQL_PARSE_ERROR, "bad datetime format");
          return;
        }
        possible_and = true; 
        continue;
      }
      
      if(*ptr == ')') 
        break;
      ++ptr;
      --remain;

    }

    if(!found_any) {        
      remain = base_remain;
      ptr = base_rptr;
    }
    read_flags(spec.flags);
}

  
void QuerySelect::read_range(DB::Cell::Key& begin, DB::Cell::Key& end, 
                             bool flw) {
    uint32_t base_remain = remain;
    const char* base_ptr = ptr;

    Condition::Comp comp_right;
    expect_comparator(comp_right);
    if(comp_right != Condition::GE && comp_right != Condition::LE) {
      error_msg(
        Error::SQL_PARSE_ERROR, "unsupported 'comparator' allowed GE|LE");
      return;
    }

    if(comp_right == Condition::GE)
      Reader::read_key(begin);
    else 
      Reader::read_key(end);
    if(err) 
      return;

    uint32_t mark_remain = remain;
    const char* mark_ptr = ptr;

    uint32_t remain_start = sql.length()+1;

    ptr = base_ptr - LEN_RANGE;
    for(remain = 0; remain++ < remain_start; ) {
      --ptr;
      if(flw) {
        if(found_token(TOKEN_AND, LEN_AND))
          break;
      } else if(found_char('('))
        break;
    }
    
    while(remain && !err && found_space());
    if(*ptr != '[') {
      remain = mark_remain;
      ptr = mark_ptr;
      return;
    }

    if(comp_right == Condition::GE)
      Reader::read_key(end);
    else 
      Reader::read_key(begin);
    if(err) {
      remain = mark_remain;
      ptr = mark_ptr;
      return;
    }
   
    Condition::Comp comp_left = Condition::NONE;
    expect_comparator(comp_left);
    remain += base_remain;
    if(comp_left != Condition::GE && comp_left != Condition::LE) {
      error_msg(
        Error::SQL_PARSE_ERROR, "unsupported 'comparator' allowed GE|LE");
      return;
    }
    comp_left = comp_left == Condition::GE ? Condition::LE : Condition::GE;
    if(comp_left == comp_right) {
      error_msg(Error::SQL_PARSE_ERROR, "bad comparators pair");
      return;
    }

    remain = mark_remain;
    ptr = mark_ptr;
}

void QuerySelect::read_key(DB::Specs::Key& start, DB::Specs::Key& finish, 
                           bool flw, bool& eq) {
    uint32_t base_remain = remain;
    const char* base_ptr = ptr;

    Condition::Comp comp_right;
    expect_comparator(comp_right);
    if(comp_right != Condition::EQ && 
       comp_right != Condition::GE && comp_right != Condition::LE) {
      error_msg(
        Error::SQL_PARSE_ERROR, "unsupported 'comparator' allowed EQ|GE|LE");
      return;
    }

    if((eq = comp_right == Condition::EQ) || comp_right == Condition::GE)
      read_key(start);
    else 
      read_key(finish);

    if(err || comp_right == Condition::EQ) 
      return;

    uint32_t mark_remain = remain;
    const char* mark_ptr = ptr;

    uint32_t remain_start = sql.length()+1;

    ptr = base_ptr - LEN_KEY;
    for(remain = 0; remain++ < remain_start; ) {
      --ptr;
      if(flw) {
        if(found_token(TOKEN_AND, LEN_AND))
          break;
      } else if(found_char('('))
        break;
    }
    
    while(remain && !err && found_space());
    if(*ptr != '[') {
      remain = mark_remain;
      ptr = mark_ptr;
      return;
    }

    if(comp_right == Condition::GE)
      read_key(finish);
    else 
      read_key(start);
    if(err) {
      remain = mark_remain;
      ptr = mark_ptr;
      return;
    }
   
    Condition::Comp comp_left = Condition::NONE;
    expect_comparator(comp_left);
    remain += base_remain;
    if(comp_left != Condition::GE && comp_left != Condition::LE) {
      error_msg(
        Error::SQL_PARSE_ERROR, "unsupported 'comparator' allowed GE|LE");
      return;
    }
    comp_left = comp_left == Condition::GE ? Condition::LE : Condition::GE;
    if(comp_right == comp_left) {
      error_msg(Error::SQL_PARSE_ERROR, "bad comparators pair");
      return;
    }

    remain = mark_remain;
    ptr = mark_ptr;
}

void QuerySelect::read_key(DB::Specs::Key& key) {

    bool bracket_square = false;
    
    while(remain && !err && found_space());
    expect_token("[", 1, bracket_square);

    Condition::Comp comp = Condition::NONE;
    std::string fraction;
    while(remain && !err) {
      if(found_space())
        continue;
      
      found_comparator(comp);
      if(comp == Condition::NONE)
        comp = Condition::EQ;
      read(fraction, ",]");
      key.add(fraction, comp);
      fraction.clear();

      while(remain && !err && found_space());
      if(found_char(',')) 
        continue;
      break;
    }
    
    expect_token("]", 1, bracket_square);
}

void QuerySelect::read_value(DB::Specs::Value& value) {
    Condition::Comp comp;
    expect_comparator(comp, true);
    std::string buf;
    read(buf, 0, comp == Condition::RE);
    if(!err)
      value.set((uint8_t*)buf.data(), buf.length(), comp, true);
}
  
void QuerySelect::read_timestamp(DB::Specs::Timestamp& start, 
                                 DB::Specs::Timestamp& finish, bool flw) {
    uint32_t base_remain = remain;
    const char* base_ptr = ptr;

    Condition::Comp comp_right;
    expect_comparator(comp_right);
    if(comp_right != Condition::EQ && 
       comp_right != Condition::GE && 
       comp_right != Condition::GT &&  
       comp_right != Condition::LE && 
       comp_right != Condition::LT) {
      error_msg(
        Error::SQL_PARSE_ERROR, 
        "unsupported 'comparator' allowed EQ|GE|GT|LE|LT"
      );
      return;
    }

    std::string buf;
    read(buf);
    if(err) 
      return;
    int64_t ts = Time::parse_ns(err, buf);
    if(err) {
      error_msg(Error::SQL_PARSE_ERROR, "bad datetime format");
      return;
    }

    if(comp_right == Condition::EQ || comp_right == Condition::GE || 
       comp_right == Condition::GT)
      start.set(ts, comp_right);
    else 
      finish.set(ts, comp_right);

    if(comp_right == Condition::EQ)
      return;

    uint32_t mark_remain = remain;
    const char* mark_ptr = ptr;

    uint32_t end = sql.length()+1;

    ptr = base_ptr - LEN_TIMESTAMP;
    for(remain = 0; remain < end; ) {
      ++remain;
      --ptr;
      if(flw) {
        if(found_token(TOKEN_AND, LEN_AND))
          break;
      } else if(found_char('('))
        break;
    }
    
    buf.clear();
    read(buf);
    if(buf.empty()) {
      remain = mark_remain;
      ptr = mark_ptr;
      return;
    }
    if(err) 
      return;
    ts = Time::parse_ns(err, buf);
    if(err) {
      error_msg(Error::SQL_PARSE_ERROR, "bad datetime format");
      return;
    }

    Condition::Comp comp_left = Condition::NONE;
    expect_comparator(comp_left);
    remain += base_remain;
    if(comp_left != Condition::GE && 
       comp_left != Condition::GT && 
       comp_left != Condition::LE && 
       comp_left != Condition::LT) {
      error_msg(
        Error::SQL_PARSE_ERROR, 
        "unsupported 'comparator' allowed GE|GT|LE|LT"
      );
      return;
    }

    comp_left = comp_left == Condition::GE ? Condition::LE 
        : (comp_left == Condition::GT ? Condition::LT 
        : (comp_left == Condition::LE ? Condition::GE 
        : (comp_left == Condition::LT ? Condition::GT : comp_left)));

    if(comp_left == comp_right) {
      error_msg(Error::SQL_PARSE_ERROR, "bad comparators pair");
      return;
    }

    if(finish.was_set)
      start.set(ts, comp_left);
    else  
      finish.set(ts, comp_left);

    remain = mark_remain;
    ptr = mark_ptr;
}

void QuerySelect::read_flags(DB::Specs::Flags& flags) {

    bool any = true;
    bool was_set;
    while(any && remain && !err) {
      if(found_space())
        continue;    

      if((any = found_token(TOKEN_LIMIT, LEN_LIMIT))) {
        expect_eq();
        int64_t v;
        read_int64_t(v, was_set = false);
        if(was_set) {
          flags.limit = v;
          flags.was_set = was_set;
        }
        continue;
      }
      if((any = found_token(TOKEN_OFFSET, LEN_OFFSET))) {
        expect_eq();
        int64_t v;
        read_int64_t(v, was_set = false);
        if(was_set) {
          flags.offset = v;
          flags.was_set = was_set;
        }
        continue;
      }
      if((any = found_token(TOKEN_MAX_VERS, LEN_MAX_VERS))) {
        expect_eq();
        read_uint32_t(flags.max_versions, flags.was_set);
        continue;
      }
      if((any = found_token(TOKEN_MAX_BUFF, LEN_MAX_BUFF))) {
        expect_eq();
        read_uint32_t(flags.max_buffer, flags.was_set);
        continue;
      }

      if((any = found_token(TOKEN_ONLY_DELETES, LEN_ONLY_DELETES))) {
        flags.set_only_deletes();
        flags.was_set = true;
        continue;
      }
      if((any = found_token(TOKEN_ONLY_KEYS, LEN_ONLY_KEYS))) { 
        flags.set_only_keys();
        flags.was_set = true;
        continue;
      }
      // + LimitType limit_by, offset_by;
    }
}




}}} // SWC::client:SQL namespace
