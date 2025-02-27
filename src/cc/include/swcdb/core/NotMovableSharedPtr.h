/*
 * SWC-DB© Copyright since 2019 Alex Kashirin <kashirin.alex@gmail.com>
*/

#ifndef swcdb_core_NotMovableSharedPtr_h
#define swcdb_core_NotMovableSharedPtr_h


namespace SWC { namespace Core {


template<class T>
class NotMovableSharedPtr : public std::shared_ptr<T> {
  public:

  constexpr SWC_CAN_INLINE
  NotMovableSharedPtr() noexcept { }

  SWC_CAN_INLINE
  NotMovableSharedPtr(T* other) noexcept : std::shared_ptr<T>(other) { }

  SWC_CAN_INLINE
  NotMovableSharedPtr(const std::shared_ptr<T>& other) noexcept
                    : std::shared_ptr<T>(other) {
  }

  NotMovableSharedPtr(const std::shared_ptr<T>&&) = delete;

  ~NotMovableSharedPtr() noexcept { }

  NotMovableSharedPtr<T>& operator=(const std::shared_ptr<T>&) = delete;

};


}}

#endif // swcdb_core_NotMovableSharedPtr_h
