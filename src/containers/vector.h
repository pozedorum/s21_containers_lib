#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <new>
#include <utility>

namespace s21 {
template <class T>
class Vector {
  // private attributes
 private:
  size_t size_;
  size_t capacity_;
  T *arr_ = nullptr;

  // public attribures
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // public methods
 public:
  // member functions
  Vector();
  Vector(size_type n);
  Vector(std::initializer_list<value_type> const &items);
  Vector(const Vector &v);
  Vector(Vector &&v);
  ~Vector();
  Vector<T> &operator=(Vector &&v);

  // element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  // iterators
  iterator begin();
  iterator end();

  // capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(const iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &other);
};
}  // namespace s21

// constructors
template <typename T>
s21::Vector<T>::Vector() : size_(0), capacity_(0), arr_(nullptr) {}

template <typename T>
s21::Vector<T>::Vector(size_type n) {
  if (!n)
    throw std::invalid_argument("Invalid argument");
  else {
    size_ = n;
    capacity_ = n;
    arr_ = new (std::nothrow) value_type[n];
    if (arr_ == nullptr) throw std::bad_alloc();
  }
}

template <typename T>
size_t s21::Vector<T>::size() {
  return size_;
}

template <typename T>
size_t s21::Vector<T>::capacity() {
  return capacity_;
}

template <typename T>
T &s21::Vector<T>::at(size_type pos) {
  if (pos > this->size_) throw std::out_of_range("Index out of range");
  return arr_[pos];
}

template <typename T>
s21::Vector<T>::Vector(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr_[i] = *it;
    i++;
  }
  size_ = items.size();
  capacity_ = items.size();
};

template <typename T>
s21::Vector<T>::Vector(const Vector &v)
    : size_(v.size_), capacity_(v.capacity_) {
  if (this->arr_ == nullptr) {
    arr_ = new value_type[size_];
  }
  for (size_t i = 0; i < v.size_; i++) arr_[i] = v.arr_[i];
};

template <typename T>
s21::Vector<T>::Vector(Vector &&v)
    : size_(v.size_), capacity_(v.capacity_), arr_(v.arr_) {
  v.arr_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
s21::Vector<T>::~Vector() {
  size_ = 0;
  capacity_ = 0;
  delete[] arr_;
  arr_ = nullptr;
}

template <typename T>
s21::Vector<T> &s21::Vector<T>::operator=(Vector &&v) {
  if (this->arr_ != v.arr_) {
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->arr_ = v.arr_;
  }
  v.size_ = 0;
  v.capacity_ = 0;
  v.arr_ = nullptr;
  return *this;
}

template <typename T>
T &s21::Vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T>
const T &s21::Vector<T>::front() {
  return arr_[0];
}

template <typename T>
const T &s21::Vector<T>::back() {
  return arr_[size_ - 1];
}

template <typename T>
bool s21::Vector<T>::empty() {
  bool result = true;
  if (size_ != 0) result = false;
  return result;
}

template <typename T>
T *s21::Vector<T>::data() {
  return arr_;
}

template <typename T>
size_t s21::Vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <typename T>
void s21::Vector<T>::clear() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
}

template <typename T>
void s21::Vector<T>::push_back(const T &v) {
  if (size_ == capacity_) {
    reserve(size_ + 1);
  }
  arr_[size_++] = v;
}

template <typename T>
void s21::Vector<T>::reserve(size_type size) {
  if (size > capacity_) {
    value_type *buff = new value_type[size];
    for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
    delete[] arr_;
    arr_ = buff;
    capacity_ = size;
  }
}

template <typename T>
void s21::Vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    value_type *buff = new value_type[size_];
    for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
    delete[] arr_;
    arr_ = buff;
    capacity_ = size_;
  }
}

template <typename T>
void s21::Vector<T>::pop_back() {
  size_ -= 1;
}

template <typename T>
void s21::Vector<T>::swap(Vector &other) {
  value_type *buff = arr_;
  size_t temp_size = size_;
  size_t temp_capacity = capacity_;
  arr_ = other.arr_;
  capacity_ = other.capacity_;
  size_ = other.size_;
  other.arr_ = buff;
  other.size_ = temp_size;
  other.capacity_ = temp_capacity;
}

template <typename T>
T *s21::Vector<T>::begin() {
  return arr_;
}

template <typename T>
T *s21::Vector<T>::end() {
  return arr_ + size_ - 1;
}

template <typename T>
void s21::Vector<T>::erase(const iterator pos) {
  if (pos == this->end())
    this->pop_back();
  else {
    size_type position = pos - this->begin();
    size_type j = 0;
    for (size_type i = 0; i < size_; ++i) {
      if (i != position) {
        arr_[j] = arr_[i];
        ++j;
      }
    }
    this->size_ -= 1;
  }
}

template <typename T>
T *s21::Vector<T>::insert(iterator pos, const_reference value) {
  size_t index = pos - this->begin();
  if (index > size_) throw std::invalid_argument("Invalid argument");
  if (size_ == capacity_) {
    reserve(size_ + 1);
  }
  iterator new_pos = arr_ + index;
  for (T *i = this->end(); i > new_pos; i--) {
    i = i - 1;
  }
  *new_pos = value;
  return new_pos;
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_H_