
/*
 * Copyright Since 2019 SWC-DB© [author: Kashirin Alex kashirin.alex@gmail.com]
 * License details at <https://github.com/kashirin-alex/swc-db/#license>
 */ 


#ifndef swc_manager_ColumnHealthCheck_h
#define swc_manager_ColumnHealthCheck_h


namespace SWC { namespace Manager {


class ColumnHealthCheck final 
      : public std::enable_shared_from_this<ColumnHealthCheck> {
  public:
  
  typedef std::shared_ptr<ColumnHealthCheck>  Ptr;
  const Column::Ptr                           col;
  const int64_t                               check_ts;
  const int32_t                               check_intval;


  class RangerCheck final 
      : public std::enable_shared_from_this<RangerCheck> {
    public:
  
    typedef std::shared_ptr<RangerCheck>  Ptr;
    const ColumnHealthCheck::Ptr          col_checker;
    const Ranger::Ptr                     rgr;

    RangerCheck(const ColumnHealthCheck::Ptr& col_checker, 
                const Ranger::Ptr& rgr);
  
    virtual ~RangerCheck();

    void add_range(const Range::Ptr& range);
    
    bool add_ranges(uint8_t more);

    void handle(const Range::Ptr& range, int err);

    bool empty();

    private:

    void _add_range(const Range::Ptr& range);

    Mutex                     m_mutex;
    std::queue<Range::Ptr>    m_ranges;
    uint8_t                   m_checkings;
  };
  


  
  ColumnHealthCheck(const Column::Ptr& col, 
                    int64_t check_ts, uint32_t check_intval);
  
  virtual ~ColumnHealthCheck();

  void run();

  private:
  Mutex                         m_mutex;
  std::vector<RangerCheck::Ptr> m_checkers;
  
};


typedef std::vector<ColumnHealthCheck::Ptr> ColumnHealthChecks;


}}

#endif // swc_manager_ColumnHealthCheck_h
