#ifndef CPP2_S21_CONTAINERS_SRC_CONTAINERS_TREE_H_
#define CPP2_S21_CONTAINERS_SRC_CONTAINERS_TREE_H_

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

namespace s21 {
template <typename K, typename V>
class Tree {
 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  class node {
   public:
    /* ----- CONSTRUCTORS AND DESTRUCTORS ----- */
    node(key_type key, mapped_type value) : key_(key), value_(value){};
    node(const node &other)
        : key_(other.key_), value_(other.value_), height(other.height){};
    node(node &&other) { *this = std::move(other); };
    node &operator=(const node &other) {
      node cpy(other);
      *this = std::swap(cpy);
      return *this;
    }
    node &operator=(node &&other) {
      std::swap(key_, other.key_);
      std::swap(value_, other.value_);
      std::swap(height, other.height);
      std::swap(parent, other.parent);
      std::swap(left, other.left);
      std::swap(right, other.right);
      return *this;
    }
    ~node() {
      delete left;
      delete right;
    }
    /* ----- ACCESSORS AND MUTATORS ----- */
    node *insertNode(key_type key, mapped_type value) {
      if (key < key_) {
        if (!left) {
          node *result = new node(key, value);
          result->parent = this;
          left = result;
          return balance();
        }
        left = left->insertNode(key, value);
      } else if (key > key_) {
        if (!right) {
          node *result = new node(key, value);
          result->parent = this;
          right = result;
          return balance();
        }
        right = right->insertNode(key, value);
      }
      return balance();
    }

    /* ----- TREE PRINTER ----- */
    void copyHelper(node *src) {
      if (src->left) {
        left = new node(*(src->left));
        left->parent = this;
        left->copyHelper(src->left);
      }
      if (src->right) {
        right = new node(*(src->right));
        right->parent = this;
        right->copyHelper(src->right);
      }
    };
    void printHelper(std::string indent, bool last, int depth) const {
      if (depth < 10) {
        std::cout << indent;
        if (last) {
          std::cout << "R----";
          indent += "     ";
        } else {
          std::cout << "L----";
          indent += "|    ";
        }
        std::cout << "(" << key_ << ")";
        std::cout << std::endl;
        if (left) left->printHelper(indent, false, depth + 1);
        if (right) right->printHelper(indent, true, depth + 1);
      }
    };
    /* ----- TREE BALANCING ----- */
    int getHeight() const { return height; }
    int bFactor() const {
      return (right ? right->getHeight() : 0) - (left ? left->getHeight() : 0);
    }
    void fixHeight() {
      size_t hl = left ? left->getHeight() : 0;
      size_t hr = right ? right->getHeight() : 0;
      height = (hl > hr ? hl : hr) + 1;
    }
    node *rotateRight() {
      node *result = left;
      if (result) {
        result->parent = parent;
        left = result->right;
      }
      if (left) left->parent = this;
      if (result) result->right = this;
      parent = result;
      fixHeight();
      if (result) result->fixHeight();
      return result;
    }
    node *rotateLeft() {
      node *result = right;
      if (result) {
        result->parent = parent;
        right = result->left;
      }
      if (right) right->parent = this;
      if (result) result->left = this;
      parent = result;
      fixHeight();
      if (result) result->fixHeight();
      return result;
    }
    node *balance() {
      fixHeight();
      if (bFactor() == 2) {
        if (right->bFactor() < 0) right = right->rotateRight();
        return rotateLeft();
      }
      if (bFactor() == -2) {
        if (left->bFactor() > 0) left = left->rotateLeft();
        return rotateRight();
      }
      return this;
    }

    node *findMin() const {
      return left ? left->findMin() : const_cast<node *>(this);
    }
    node *findMax() const {
      return right ? right->findMax() : const_cast<node *>(this);
    }
    node *removeMin() {
      if (!left) {
        if (right) right->parent = parent;
        return right;
      }
      left = left->removeMin();
      return balance();
    }
    node *removeNode(key_type key) {
      if (key < key_) {
        if (!left) return this;
        left = left->removeNode(key);
      } else if (key > key_) {
        if (!right) return this;
        right = right->removeNode(key);
      } else {
        if (!right) {
          node *result = left;
          if (result) result->parent = parent;
          left = nullptr;
          right = nullptr;
          parent = nullptr;
          delete this;
          return result ? result->balance() : nullptr;
        }
        node *min = right->findMin();
        min->right = right->removeMin();
        min->left = left;
        min->parent = parent;
        if (min->left) min->left->parent = min;
        if (min->right) min->right->parent = min;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        delete this;
        return min->balance();
      }
      return balance();
    }
    size_t countNodes() const {
      if (left && right) {
        return 1 + left->countNodes() + right->countNodes();
      } else if (left) {
        return 1 + left->countNodes();
      } else if (right) {
        return 1 + right->countNodes();
      } else {
        return 1;
      }
    }
    node *find(key_type key) const {
      if (key < key_) {
        if (!left) return nullptr;
        return left->find(key);
      } else if (key > key_) {
        if (!right) return nullptr;
        return right->find(key);
      } else {
        node *this_ = const_cast<node *>(this);
        return this_;
      }
    }
    node *findNext() const {
      node *this_ = const_cast<node *>(this);
      if (this_->right) return this_->right->findMin();
      if (this_->parent) {
        while (this_->parent && this_->parent->key_ < key_)
          this_ = this_->parent;
        if (!this_->parent) return nullptr;
        return this_->parent;
      }
      return nullptr;
    }
    node *findPrev() const {
      node *this_ = const_cast<node *>(this);
      if (this_->left) return this_->left->findMax();
      if (this_->parent) {
        while (this_->parent && this_->parent->key_ > key_)
          this_ = this_->parent;
        if (!this_->parent) return nullptr;
        return this_->parent;
      }
      return nullptr;
    }

    bool operator==(const node &other) const {
      return key_ == other.key_ && value_ == other.value_;
    }
    bool operator!=(const node &other) const {
      return key_ != other.key_ || value_ != other.value_;
    }

    const key_type key_;
    mapped_type value_;
    size_t height = 0;
    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;
  };

  template <typename T>
  class treeIterator {
   public:
    /* ----- TYPES ----- */
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = int32_t;
    using pointer = T *;
    using reference = T &;

    treeIterator() : ptr_(nullptr), prev_(nullptr), next_(nullptr){};
    treeIterator(T *ptr) : ptr_(ptr) {
      if (ptr_) {
        prev_ = ptr_->findPrev();
        next_ = ptr_->findNext();
      }
    };
    treeIterator(const treeIterator &other)
        : ptr_(other.ptr_), prev_(other.prev_), next_(other.next_){};

    // treeIterator operator=(treeIterator other) : ptr_(other.ptr_),
    // prev_(other.prev_), next_(other.next_) {};
    treeIterator &operator++() {
      prev_ = ptr_;
      ptr_ = next_;
      if (next_) next_ = next_->findNext();
      return *this;
    }

    treeIterator &operator--() {
      next_ = ptr_;
      ptr_ = prev_;
      if (prev_) prev_ = prev_->findPrev();
      return *this;
    }

    bool operator==(const treeIterator &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const treeIterator &other) const {
      return ptr_ != other.ptr_;
    }

    T &operator*() const { return *ptr_; }
    T *operator->() const { return ptr_; }

    operator treeIterator<const T>() const {
      return treeIterator<const T>(ptr_, prev_, next_);
    }

   protected:
    T *ptr_;
    T *prev_;
    T *next_;
  };

  template <typename T>
  class treeKeyIterator : public treeIterator<T> {
   public:
    /* ----- TYPES ----- */
    using base = treeIterator<T>;
    using iterator_category = typename treeIterator<T>::iterator_category;
    using value_type = T;
    using difference_type = int32_t;
    using pointer = T *;
    using reference = T &;

    treeKeyIterator() : base(){};
    treeKeyIterator(T *ptr) : base(ptr){};

    treeKeyIterator &operator++() {
      base::operator++();
      return *this;
    }
    treeKeyIterator &operator--() {
      base::operator--();
      return *this;
    }

    treeKeyIterator &operator++(int) {
      treeKeyIterator ret_it(*this);
      base::operator++();
      return ret_it;
    }
    treeKeyIterator &operator--(int) {
      treeKeyIterator ret_it(*this);
      base::operator--();
      return ret_it;
    }

    bool operator==(const treeKeyIterator &other) const {
      return base::ptr_ == other.ptr_;
    }
    bool operator!=(const treeKeyIterator &other) const {
      return base::ptr_ != other.ptr_;
    }

    typename std::conditional<std::is_const<T>::value, mapped_type,
                              mapped_type &>::type
    operator*() {
      return base::ptr_->value_;
    }

    operator treeKeyIterator<const T>() const {
      return treeKeyIterator<const T>(base::ptr_, base::prev_, base::next_);
    }
  };

  using iterator = treeIterator<node>;
  using const_iterator = treeIterator<const node>;
  using key_iterator = treeKeyIterator<node>;
  using const_key_iterator = treeKeyIterator<const node>;

  // CONSTRUCTORS AND DESTRUCTOR
  Tree() : root_(nullptr), count_(0){};
  Tree(key_type key, mapped_type value)
      : root_(new node(key, value)), count_(1){};
  Tree(const Tree &other)
      : root_(new node(other.root_->key_, other.root_->value_)),
        count_(other.count_) {
    root_->copyHelper(other.root_);
  }
  Tree(Tree &&other) : Tree() { *this = std::move(other); }
  Tree &operator=(const Tree &other) {
    Tree cpy(other);
    *this = std::move(cpy);
    return *this;
  }
  Tree &operator=(Tree &&other) {
    std::swap(root_, other.root_);
    std::swap(count_, other.count_);
    return *this;
  }

  ~Tree() { delete root_; };

  // MAIN FUNCTIONS
  void insert(key_type key, mapped_type value) {
    if (root_) {
      root_ = root_->insertNode(key, value);
      count_ = root_->countNodes();
    } else {
      root_ = new node(key, value);
      count_ = 1;
    }
  }
  void remove(key_type key) {
    root_ = root_->removeNode(key);
    if (root_) {
      count_ = root_->countNodes();
    } else {
      count_ = 0;
    }
  }
  size_type count() const { return root_ ? root_->countNodes() : 0; }
  size_type size() const { return count(); }
  node *findNode(key_type key) const {
    return root_ ? root_->find(key) : nullptr;
  }

  // ITERATORS FUNCTIONS

  iterator begin() {
    if (root_) return iterator(root_->findMin());
    return end();
  }
  iterator end() {
    if (root_) return iterator(root_->findMax());
    return iterator();
  }

  const_iterator begin() const {
    if (root_) return const_iterator(root_->findMin());
    return end();
  }
  const_iterator end() const {
    if (root_) return ++const_iterator(root_->findMax());
    return const_iterator();
  }

  key_iterator kbegin() {
    if (root_) return key_iterator(root_->findMin());
    return kend();
  }
  key_iterator kend() {
    if (root_) return key_iterator(root_->findMax());
    return key_iterator();
  }

  const_key_iterator kbegin() const {
    if (root_) return const_key_iterator(root_->findMin());
    return kend();
  }
  const_key_iterator kend() const {
    if (root_) return ++const_key_iterator(root_->findMax());
    return const_key_iterator();
  }

  // HELPER FUNCTIONS

  void print() const {
    if (root_) root_->printHelper("", true, 5);
  }

  node *root_;
  size_t count_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_CONTAINERS_TREE_H_