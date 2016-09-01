#ifndef HTS_TYPES
#define HTS_TYPES

#include <stdint.h>
#include <iostream>
#include <vector>

#include "boost\lockfree\spsc_queue.hpp"

namespace hts
{
typedef boost::lockfree::spsc_queue<std::vector<uint8_t>, boost::lockfree::capacity<10> > MessageQueue;
}
#endif // !HTS_TYPES

