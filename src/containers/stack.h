#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_STACK_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_STACK_H_

#include <iostream>
#include <limits>
#include <utility>

namespace s21 {

template <typename T, typename list = s21::list<T>>
class stack {
  // stack Member type
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  // stack Member functions
 public:
  // default constructor
  stack() noexcept : list_{} {}

  // initializer list constructor
  explicit stack(std::initializer_list<value_type> const &items)
      : list_{items} {}

  // copy constructor
  stack(const stack &rhs) : list_{rhs.list_} {}

  // move constructor
  stack(stack &&rhs) noexcept : list_{std::move(rhs.list_)} {}

  // destructor
  ~stack() noexcept = default;

  // 	assignment operator overload for const object
  stack &operator=(const stack &other) noexcept {
    list_ = other.list_;
    return *this;
  }
  // 	assignment operator overload for moving object
  stack &operator=(stack &&other) noexcept {
    list_ = std::move(other.list_);
    return *this;
  }

  // ----------------------------------------------------
  // stack Element access
 public:
  // accesses the top element
  const_reference top() const noexcept { return list_.back(); }

  // ----------------------------------------------------
  // stack Capacity
 public:
  // checks whether the container is empty
  bool empty() const noexcept { return list_.empty(); }
  // returns the number of elements
  size_type size() const noexcept { return list_.size(); }

  // ----------------------------------------------------
  // stack Modifiers
 public:
  // inserts element at the top
  void push(const_reference value) { list_.push_back(value); }
  // removes the top element
  void pop() noexcept { list_.pop_back(); }
  // swaps the contents
  void swap(stack &other) noexcept { std::swap(list_, other.list_); }

 private:
  list list_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_STACK_H_
