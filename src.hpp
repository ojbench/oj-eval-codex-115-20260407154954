// Problem 115 - sjtu::unique_ptr implementation
#pragma once
#include <new>
#include <utility>
// You must not include any other headers

namespace sjtu {

template <typename _Tp>
class unique_ptr {
 private:
  _Tp *ptr;

 public:
  // default construct to nullptr
  unique_ptr() : ptr(nullptr) {}

  // disallow copy
  unique_ptr(const unique_ptr &) = delete;
  unique_ptr &operator=(const unique_ptr &) = delete;

  // construct from raw pointer, taking ownership
  explicit unique_ptr(_Tp *p) : ptr(p) {}

  // move construct: transfer ownership and null out other
  unique_ptr(unique_ptr &&other) : ptr(other.ptr) { other.ptr = nullptr; }

  // move assign: delete current, take other's, null other
  unique_ptr &operator=(unique_ptr &&other) {
    if (this != &other) {
      delete ptr;
      ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  }

  // destructor: delete managed pointer (safe for nullptr)
  ~unique_ptr() { delete ptr; }

  // reset to nullptr, deleting current
  void reset() {
    delete ptr;
    ptr = nullptr;
  }

  // release ownership and return raw pointer; set to nullptr
  _Tp *release() {
    _Tp *p = ptr;
    ptr = nullptr;
    return p;
  }

  // get raw pointer without transferring ownership
  _Tp *get() const { return ptr; }

  // dereference operators
  _Tp &operator*() { return *ptr; }
  const _Tp &operator*() const { return *ptr; }
  _Tp *operator->() { return ptr; }
  const _Tp *operator->() const { return ptr; }
};

static_assert(sizeof(unique_ptr<int>) <= sizeof(void *));

// create a unique_ptr managing a new _Tp constructed from a const reference
template <typename _Tp>
unique_ptr<_Tp> make_unique(const _Tp &value) {
  return unique_ptr<_Tp>(new _Tp(value));
}

// Bonus perfect-forwarding overload (optional per problem statement)
// Uncomment to replace the const-ref version above if desired.
// template <typename _Tp, typename... Args>
// unique_ptr<_Tp> make_unique(Args &&... args) {
//   return unique_ptr<_Tp>(new _Tp(std::forward<Args>(args)...));
// }

} // namespace sjtu

