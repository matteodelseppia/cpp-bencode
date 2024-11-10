#include "bencode/decoder.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size == 0)
    return -1;
  std::string str{(const char*)Data, Size};
  bencode::decoder decoder{str};
  while (decoder.has_next()) {
    try {
      bencode::object obj = decoder.next();
    } catch(...) {
      break;
    }
  }
  return 0;
}