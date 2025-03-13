#ifndef S21_CONTAINERS_S21_CONTAINERS_S21_LIST_H_
#define S21_CONTAINERS_S21_CONTAINERS_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <utility>

namespace s21 {
template <typename Type>
class list {
 private:
  struct ListNode;
  struct ListIterator;
  struct ListIteratorConst;

  // List Member type
 public:
  using value_type = Type;
  using reference = Type&;
  using const_reference = const Type&;
  using iterator = ListIterator;
  using const_iterator = ListIteratorConst;
  using size_type = std::size_t;

  using node_type = ListNode;

  // --------------------------
  // List Functions
 public:
  // default constructor, creates empty list
  list() : head_(new node_type{}), size_(0U) {}
  // parameterized constructor, creates the list of size n
  explicit list(size_type n) : list() {
    while (n > 0) {
      push_back(value_type{});
      --n;
    }
  }
  // initializer list constructor, creates list initizialized using
  // std::initializer_list
  list(std::initializer_list<value_type> const& items) : list() {
    for (auto item : items) {
      push_back(item);
    }
  }
  // copy constructor
  list(const list& other) : list() {
    for (auto list_element : other) {
      push_back(list_element);
    }
  }
  // move constructor
  list(list&& other) noexcept : list() { splice(begin(), other); }
  // assignment operator overload for const object
  list& operator=(const list& other) {
    if (this != &other) {
      iterator this_begin = begin();
      iterator this_end = end();
      const_iterator other_begin = other.begin();
      const_iterator other_end = other.end();

      while (this_begin != this_end && other_begin != other_end) {
        *this_begin = *other_begin;
        ++this_begin;
        ++other_begin;
      }

      while (this_begin != this_end) {
        iterator tmp = this_begin;
        ++this_begin;
        erase(tmp);
      }

      while (other_begin != other_end) {
        push_back(*other_begin);
        ++other_begin;
      }
    }

    return *this;
  }
  // assignment operator overload for moving object
  list& operator=(list&& other) noexcept {
    if (this != &other) {
      clear();
      splice(begin(), other);
    }
    return *this;
  }
  // destructor
  ~list() {
    clear();
    delete head_;
    head_ = nullptr;
  }

  // --------------------------
  // List Element access
 public:
  // access the first element
  reference front() noexcept { return *begin(); }
  // access the first element (const)
  const_reference front() const noexcept { return *begin(); }
  // access the last element
  reference back() noexcept { return *std::prev(end()); }
  // access the last element (const)
  const_reference back() const noexcept { return *std::prev(end()); }
  // returns an iterator to the beginning
  iterator begin() noexcept { return iterator{head_->next_}; }

  // --------------------------
  // List Iterators
 public:
  // returns an iterator to the beginning
  const_iterator begin() const noexcept { return const_iterator{head_->next_}; }
  // returns an iterator to the end
  iterator end() noexcept { return iterator{head_}; }
  // returns an iterator to the end (const)
  const_iterator end() const noexcept { return const_iterator{head_}; }

  // --------------------------
  // List Capacity
 public:
  // checks whether the container is empty
  bool empty() const noexcept { return size_ == 0; }
  // returns the number of elements
  size_type size() const noexcept { return size_; };
  // returns the maximum possible number of elements
  size_type max_size() const noexcept {
    return ((std::numeric_limits<size_type>::max() / 2) / sizeof(node_type));
  }

  // --------------------------
  // List Modifiers
 public:
  // clears the contents
  void clear() noexcept {
    while (size_ > 0) {
      erase(begin());
    }
  }
  // inserts element into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value) {
    node_type* new_node = new node_type(value);

    pos.node_->AttachPrev(new_node);
    ++size_;

    return iterator(new_node);
  }
  // erases element at pos
  void erase(iterator pos) noexcept {
    if (pos != end()) {
      pos.node_->UnAttach();
      delete pos.node_;
      --size_;
    }
  }
  // adds an element to the end
  void push_back(const_reference value) { insert(end(), value); }
  // removes the last element
  void pop_back() noexcept { erase(--end()); }
  // adds an element to the head
  void push_front(const_reference value) { insert(begin(), value); }
  // adds an element to the head
  void pop_front() noexcept { erase(begin()); }
  // swaps the contents
  void swap(list& other) noexcept {
    if (this != &other) {
      std::swap(head_, other.head_);
      std::swap(size_, other.size_);
    }
  }
  // merges two sorted lists
  void merge(list& other) {
    if (this != &other) {
      iterator this_begin = begin();
      iterator this_end = end();
      iterator other_begin = other.begin();
      iterator other_end = other.end();

      while (this_begin != this_end && other_begin != other_end) {
        if (*other_begin < *this_begin) {
          node_type* tmp = other_begin.node_;
          ++other_begin;
          tmp->UnAttach();
          --other.size_;
          this_begin.node_->AttachPrev(tmp);
          ++size_;
        } else {
          ++this_begin;
        }
      }

      splice(end(), other);
    }
  }
  // transfers elements from list other starting from pos
  void splice(const_iterator pos, list& other) noexcept {
    if (!other.empty()) {
      iterator it_current{const_cast<node_type*>(pos.node_)};
      iterator it_other = other.end();

      it_other.node_->next_->prev_ = it_current.node_->prev_;
      it_other.node_->prev_->next_ = it_current.node_;

      it_current.node_->prev_->next_ = it_other.node_->next_;
      it_current.node_->prev_ = it_other.node_->prev_;

      size_ += other.size();

      other.size_ = 0;
      other.head_->next_ = other.head_;
      other.head_->prev_ = other.head_;
    }
  }
  // reverses the order of the elements
  void reverse() noexcept {
    iterator begin_iterator = begin();
    iterator end_iterator = end();
    while (begin_iterator != end_iterator) {
      begin_iterator.node_->SwapNextPrev();
      --begin_iterator;
    }
    head_->SwapNextPrev();
  }
  // removes consecutive duplicate elements
  void unique() {
    iterator begin_iterator = begin();
    iterator end_iterator = end();
    iterator prev_iterator = begin_iterator;

    ++begin_iterator;
    while (begin_iterator != end_iterator) {
      if (*begin_iterator == *prev_iterator) {
        erase(begin_iterator);
        begin_iterator = prev_iterator;
      } else {
        ++prev_iterator;
      }
      ++begin_iterator;
    }
  }
  // sorts the elements
  void sort() { quick_sort(begin(), --end(), size_); }

  // for sorting
 private:
  void quick_sort(iterator left, iterator right, size_type list_size) {
    if (left != right && list_size > 1) {
      iterator swap_iterator = left;
      iterator pivot_iterator = left;
      iterator tmp_left = left;
      iterator tmp_right = right;
      --swap_iterator;
      --pivot_iterator;
      size_type ishift = 0;
      while (ishift < list_size / 2) {
        ++pivot_iterator;
        ++ishift;
      }
      value_type pivot = *pivot_iterator;
      ishift = 0;

      pivot_iterator.node_->SwapValues(right.node_);
      while (tmp_left != tmp_right) {
        if (*tmp_left < pivot) {
          ++swap_iterator;
          ++ishift;
          tmp_left.node_->SwapValues(swap_iterator.node_);
          ++tmp_left;
        } else if (*tmp_left == pivot) {
          --tmp_right;
          tmp_left.node_->SwapValues(tmp_right.node_);
        } else {
          ++tmp_left;
        }
      }

      iterator next_step_left = swap_iterator;
      size_type next_step_left_size = ishift;
      size_type next_step_right_size = list_size - ishift - 1;

      ++swap_iterator;
      while (tmp_right != right) {
        swap_iterator.node_->SwapValues(tmp_right.node_);
        ++swap_iterator;
        ++tmp_right;
        --next_step_right_size;
      }

      swap_iterator.node_->SwapValues(right.node_);
      ++swap_iterator;

      iterator next_step_right = swap_iterator;

      quick_sort(left, next_step_left, next_step_left_size);
      quick_sort(next_step_right, right, next_step_right_size);
    }
  }

  struct ListNode {
    ListNode() noexcept : next_(this), prev_(this), value_(value_type{}) {}

    explicit ListNode(const_reference value) noexcept
        : next_(nullptr), prev_(nullptr), value_(value) {}

    explicit ListNode(value_type&& value) noexcept
        : next_(nullptr), prev_(nullptr), value_(std::move(value)) {}

    void AttachPrev(node_type* new_node) noexcept {
      new_node->next_ = this;
      new_node->prev_ = prev_;
      prev_->next_ = new_node;
      prev_ = new_node;
    }

    void UnAttach() noexcept {
      prev_->next_ = next_;
      next_->prev_ = prev_;
      next_ = this;
      prev_ = this;
    }

    void SwapValues(node_type* other_node) noexcept {
      std::swap(value_, other_node->value_);
    }

    void SwapNextPrev() noexcept { std::swap(next_, prev_); }

    node_type* next_;
    node_type* prev_;
    value_type value_;
  };

  struct ListIterator {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = list::value_type;
    using pointer = value_type*;
    using reference = value_type&;

    ListIterator() = delete;

    explicit ListIterator(node_type* node) noexcept : node_(node) {}

    reference operator*() const noexcept { return node_->value_; }

    iterator& operator++() noexcept {
      node_ = node_->next_;
      return *this;
    }

    iterator operator++(int) noexcept {
      iterator tmp{node_};
      ++(*this);
      return tmp;
    }

    iterator& operator--() noexcept {
      node_ = node_->prev_;
      return *this;
    }

    iterator operator--(int) noexcept {
      iterator tmp{node_};
      --(*this);
      return tmp;
    }

    bool operator==(const iterator& other) const noexcept {
      return node_ == other.node_;
    }

    bool operator!=(const iterator& other) const noexcept {
      return node_ != other.node_;
    }

    ListIterator& operator+=(std::ptrdiff_t n) noexcept {
      if (n > 0) {
        for (std::ptrdiff_t i = 0; i < n; ++i) {
          node_ = node_->next_;
        }
      } else {
        for (std::ptrdiff_t i = 0; i < -n; ++i) {
          node_ = node_->prev_;
        }
      }
      return *this;
    }

    ListIterator& operator-=(std::ptrdiff_t n) noexcept {
      if (n > 0) {
        for (std::ptrdiff_t i = 0; i < n; ++i) {
          node_ = node_->prev_;
        }
      } else {
        for (std::ptrdiff_t i = 0; i < -n; ++i) {
          node_ = node_->next_;
        }
      }
      return *this;
    }

    ListIterator operator+(std::ptrdiff_t n) const noexcept {
      ListIterator temp = *this;
      if (n > 0) {
        for (std::ptrdiff_t i = 0; i < n; ++i) {
          temp.node_ = temp.node_->next_;
        }
      } else {
        for (std::ptrdiff_t i = 0; i < -n; ++i) {
          temp.node_ = temp.node_->prev_;
        }
      }
      return temp;
    }

    ListIterator operator-(std::ptrdiff_t n) const noexcept {
      ListIterator temp = *this;
      if (n > 0) {
        for (std::ptrdiff_t i = 0; i < n; ++i) {
          temp.node_ = temp.node_->prev_;
        }
      } else {
        for (std::ptrdiff_t i = 0; i < -n; ++i) {
          temp.node_ = temp.node_->next_;
        }
      }
      return temp;
    }

    node_type* node_;
  };

  // same as ListIterator, only const
  struct ListIteratorConst {
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = list::value_type;
    using pointer = const value_type*;
    using reference = const value_type&;

    ListIteratorConst() = delete;

    explicit ListIteratorConst(const node_type* node) : node_(node) {}

    ListIteratorConst(const iterator& it) : node_(it.node_) {}

    reference operator*() const noexcept { return node_->value_; }

    const_iterator& operator++() noexcept {
      node_ = node_->next_;
      return *this;
    }

    const_iterator operator++(int) noexcept {
      const_iterator tmp{node_};
      ++(*this);
      return tmp;
    }

    const_iterator& operator--() noexcept {
      node_ = node_->prev_;
      return *this;
    }

    const_iterator operator--(int) noexcept {
      const_iterator tmp{node_};
      --(*this);
      return tmp;
    }

    friend bool operator==(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ == it2.node_;
    }

    friend bool operator!=(const const_iterator& it1,
                           const const_iterator& it2) noexcept {
      return it1.node_ != it2.node_;
    }

    const node_type* node_;
  };

  node_type* head_;
  size_type size_;
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_CONTAINERS_S21_LIST_H_
