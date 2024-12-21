#include <iostream>
#include <my_array.hpp>

int main() {
  MyArray<int> a;
  for (int i = 0; i < 10; ++i)
    a.insert(i + 1);
  for (int i = 0; i < a.size(); ++i)
    a[i] *= 2;
  const MyArray<int> b(a);
  for (auto it = b.iterator(); it.hasNext(); it.next()) {
    std::cout << it.get() << std::endl;
  }
  for (auto it = a.reverseIterator(); it.hasNext(); it.next()) {
    std::cout << it.get() << std::endl;
  }
  return 0;
}
