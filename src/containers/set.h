#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_H_

#include "tree.h"

namespace s21 {
template <typename T>
class set {
 public:
  using tree = Tree<T, T>;
  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = typename tree::key_iterator;
  using const_iterator = typename tree::const_key_iterator;
  using size_type = size_t;

  // CONSTRUCTORS
  set() = default;
  set(std::initializer_list<value_type> const &items) {
    for (auto it = items.begin(); it != items.end(); ++it)
      if (!tree_.findNode(*it)) tree_.insert(*it, *it);
  }
  set(const set &other) : tree_(other.tree_) {}
  set(set &&other) : tree_(std::move(other.tree_)) {}

  // DESTRUCTOR
  ~set() = default;

  // OVERLOAD OPERATORS
  set &operator=(const set &other) {
    set copy(other);
    *this = std::move(copy);
    return *this;
  }
  set &operator=(set &&other) {
    tree_ = std::move(other.tree_);
    return *this;
  }

  // MAIN FUNCTIONS
  bool empty() const { return !tree_.count_; }
  size_type size() const { return tree_.count_; }
  // size_type max_size() const {return size_type(-1); }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(Tree<T, T>) / 5;
  }
  void swap(set &other) { tree_ = std::move(other.tree_); }
  void clear() {
    if (tree_.root_) delete tree_.root_;
    tree_.root_ = nullptr;
    tree_.count_ = 0;
  }

  iterator find(const value_type &key) {
    auto node = tree_.findNode(key);
    if (node) {
      return iterator(node);
    } else {
      return ++iterator(tree_.root_->findMax());
    }
  }
  bool contains(const value_type &key) {
    return tree_.findNode(key) ? true : false;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    bool exist = tree_.findNode(value);
    if (!exist) tree_.insert(value, value);
    iterator iter(tree_.findNode(value));
    return std::make_pair(iter, !exist);
  }
  void erase(iterator iter) {
    if (iter != end())
      tree_.remove(*iter);
    else if (iter == end() && iter != nullptr)
      tree_.remove(*iter);
  }
  void merge(set &other) {
    for (auto it = other.begin(); it != other.end(); ++it) insert(*it);
    clear(other);
  }

  // ITERATORS FUNCTIONS
  iterator begin() { return tree_.kbegin(); }
  const_iterator begin() const { return tree_.kbegin(); }
  iterator end() { return tree_.kend(); }
  const_iterator end() const { return tree_.kend(); }

 private:
  tree tree_;
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_H_