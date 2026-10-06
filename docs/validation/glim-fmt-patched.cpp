#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <memory>
#include <string>
int main() {
  auto first = std::make_shared<int>(1);
  std::shared_ptr<int> second;
  auto text = fmt::format("neither frames[last]={} nor frames[last - 1]={} is released!!",
                          fmt::ptr(first.get()), fmt::ptr(second.get()));
  auto expected = fmt::format("neither frames[last]={} nor frames[last - 1]={} is released!!",
                              static_cast<const void*>(first.get()),
                              static_cast<const void*>(second.get()));
  return text == expected ? 0 : 1;
}
