//
// Created by Ja_Vani on 1.12.2024.
//

#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <array>
#include <cstdlib>
#include <iterator>

template<typename T>
class MyArray final {
  T *data_;
  int size_ = 0;
  int capacity_;

public:
  MyArray() {
    this->data_ = (T *) malloc(16 * sizeof(T));
    this->capacity_ = 16;
  }

  MyArray(int capacity) {
    this->data_ = (T *) malloc(capacity * sizeof(T));
    this->capacity_ = capacity;
  }

  MyArray(const MyArray &other) {
    this->data_ = (T *) malloc(other.capacity_ * sizeof(T));
    for (int i = 0; i < other.size(); i++) {
      this->data_[i] = other.data_[i];
    }
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
  }

  MyArray &operator=(const MyArray &other) {
    if (this == &other) return *this;
    this->data_ = (T *) malloc(other.capacity_ * sizeof(T));
    for (int i = 0; i < other.size(); i++) {
      this->data_[i] = other.data_[i];
    }
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    return *this;
  }

  MyArray(MyArray &&other) {
    this->data_ = other.data_;
    other.data_ = nullptr;
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    other.capacity_ = 0;
    other.size_ = 0;
  }

  MyArray &operator=(MyArray &&other) {
    if (this == &other) return *this;
    this->data_ = other.data_;
    other.data_ = nullptr;
    this->size_ = other.size_;
    this->capacity_ = other.capacity_;
    other.capacity_ = 0;
    other.size_ = 0;
    return *this;
  }

  ~MyArray() {
    for (int i = 0; i < this->size_; i++)
      data_[i].~T();
    free(this->data_);
  }

  int insert(const T &value) { return insert(size_, value); }

  int insert(int index, const T &value) {
    if (size_ < capacity_) {
      T next = value;
      for (int i = index; i <= size_; i++) {
        T temp = std::move(this->data_[i]);
        data_[i] = std::move(next);
        next = std::move(temp);
      }
    } else {
      capacity_ *= 2;
      T *newData = (T *) malloc(capacity_ * sizeof(T));
      for (int i = 0; i < index; i++) {
        newData[i] = std::move(this->data_[i]);
      }
      newData[index] = value;
      for (int i = index + 1; i <= size_; i++) {
        newData[i] = std::move(this->data_[i - 1]);
      }
      for (int i = 0; i < this->size_; i++)
        data_[i].~T();
      free(this->data_);
      this->data_ = newData;
    }
    size_++;
    return index;
  }

  void remove(int index) {
    size_--;
    for (int i = index; i < size_; i++) {
      data_[i] = data_[i + 1];
    }
  }

  const T &operator[](int index) const { return static_cast<const T &>(data_[index]); }
  T &operator[](int index) { return data_[index]; }
  int size() const { return size_; }

  class MyConstIterator : public std::iterator<std::random_access_iterator_tag, T> {
    int index_;
    bool is_reverse_;
    const MyArray<T> *array_;

  public:
    MyConstIterator(const MyArray<T> *array, bool is_reverse) : index_(is_reverse ? (*array).size() - 1 : 0), is_reverse_(is_reverse), array_(array) {
    }

    const T &get() const {
      if (is_reverse_) {
        if (index_ < 0)return (*array_)[0];
      } else if (index_ > (*array_).size()) return (*array_)[(*array_).size() - 1];
      return (*array_)[index_];
    }

    void next() {
      if (!hasNext()) return;
      if (is_reverse_)index_--;
      else index_++;
    }

    bool hasNext() const {
      if (is_reverse_) {
        if (index_ <= 0)return false;
      } else if (index_ >= (*array_).size()) return false;
      return true;
    }
  };

  class MyIterator : public std::iterator<std::random_access_iterator_tag, T> {
    int index_;
    bool is_reverse_;
    MyArray<T> *array_;

  public:
    MyIterator(MyArray<T> *array, bool is_reverse) : index_(is_reverse ? (*array).size() - 1 : 0), is_reverse_(is_reverse), array_(array) {
    }

    void set(const T &value) {
      if (is_reverse_) {
        if (index_ < 0)return;
      } else if (index_ > MyConstIterator::array_.size()) return;
      array_[index_] = value;
    }

    const T &get() const {
      if (is_reverse_) {
        if (index_ < 0)return (*array_)[0];
      } else if (index_ > (*array_).size()) return (*array_)[(*array_).size() - 1];
      return (*array_)[index_];
    }

    void next() {
      if (!hasNext()) return;
      if (is_reverse_)index_--;
      else index_++;
    }

    bool hasNext() const {
      if (is_reverse_) {
        if (index_ <= 0)return false;
      } else if (index_ >= (*array_).size()) return false;
      return true;
    }
  };

  MyIterator iterator() {
    return MyIterator(this, false);
  }

  MyConstIterator iterator() const {
    return MyConstIterator(this, false);
  }

  MyIterator reverseIterator() {
    return MyIterator(this, true);
  }

  MyConstIterator reverseIterator() const {
    return MyConstIterator(this, true);
  }
};

#endif // MY_ARRAY_H
