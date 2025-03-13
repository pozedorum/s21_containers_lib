#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_H_

#include "tree.h"

namespace s21 {
template <typename K, typename V>
class map {
 public:
  using tree = Tree<K, V>;
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename tree::iterator;
  using const_iterator = typename tree::const_iterator;
  using size_type = size_t;

  // CONSTRUCTORS
  map() = default;
  map(std::initializer_list<value_type> const &items) {
    for (auto i = items.begin(); i != items.end(); ++i)
      if (!tree_.findNode(i->first)) tree_.insert(i->first, i->second);
  }

  map(const map &other) : tree_(other.tree_){};

  map(map &&other) : tree_(std::move(other.tree_)) {}

  // DESTRUCTOR
  ~map() = default;

  // OVERLOAD OPERATORS
  map &operator=(const map &other) {
    map cpy(other);
    *this = std::move(cpy);
    return *this;
  }
  map &operator=(map &&other) {
    tree_ = std::move(other.tree_);
    return *this;
  }
  mapped_type &operator[](const key_type &key) {
    if (!tree_.findNode(key)) tree_.insert(key, mapped_type());
    return tree_.findNode(key)->value_;
  }

  mapped_type &at(const key_type &key) {
    auto res = tree_.findNode(key);
    if (!res) std::out_of_range("Key does not exist");
    return res->value_;
  }

  // ITERATORS
  iterator begin() { return tree_.begin(); }
  const_iterator begin() const { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  const_iterator end() const { return tree_.end(); }

  // MAIN FUNCTIONS
  bool empty() const { return !tree_.count_; }
  iterator find(const key_type &key) const {
    return iterator(tree_.findNode(key));
  }
  bool contains(const key_type &key) const {
    return (tree_.findNode(key)) ? true : false;
  }
  void swap(map &other) { tree_ = std::move(other.tree_); }

  size_type size() const { return tree_.count_; }
  size_type max_size() const { return size_type(-1); }

  std::pair<iterator, bool> insert(const value_type &value) {
    bool exist = tree_.findNode(value.first);
    if (!exist) tree_.insert(value.first, value.second);
    iterator pos(tree_.findNode(value.first));
    return std::make_pair(pos, !exist);
  }
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    bool exist = tree_.findNode(key);
    if (!exist) tree_.insert(key, obj);
    iterator pos(tree_.findNode(key));
    return std::make_pair(pos, !exist);
  }
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    bool exist = tree_.findNode(key);
    if (!exist) {
      tree_.insert(key, obj);
    } else {
      tree_.findNode(key)->value_ = obj;
    }
    iterator pos(tree_.findNode(key));
    return std::make_pair(pos, !exist);
  }

  void erase(iterator pos) {
    if (pos != end())
      tree_.remove(pos->key_);
    else if (pos == end() and pos != nullptr)
      tree_.remove(pos->key_);
  }
  void merge(map &other) {
    for (auto it = other.begin(), et = other.end(); it != et; ++it)
      insert(it->key_, it->value_);
    if (other.end() != nullptr) insert(other.end()->key_, other.end()->value_);
    other.clear();
  }

  void clear() {
    if (tree_.root_) delete tree_.root_;
    tree_.root_ = nullptr;
    tree_.count_ = 0;
  }

 private:
  tree tree_;
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_H_