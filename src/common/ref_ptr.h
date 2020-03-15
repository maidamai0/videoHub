#pragma once

/**
 * @file ref_ptr.h
 * @author tonghao.yuan (yuantonghao@gmail.com)
 * @brief   reference pointer, hold a reference to a raw pointer, no ownship
 * @version 0.1
 * @date 2020-03-08
 *
 * @copyright Copyright (c) 2020
 *
 */

template <typename T>
class RefPtr {
 public:
  explicit RefPtr(T* raw_ptr) : raw_ptr_(raw_ptr) {}
  RefPtr() = default;
  T* operator->() { return raw_ptr_; }
  T operator*() { return *raw_ptr_; }
  bool operator!() { return raw_ptr_ == nullptr; }

 private:
  T* raw_ptr_ = nullptr;
};