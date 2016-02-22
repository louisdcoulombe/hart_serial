#ifndef HART_TYPE_H
#define HART_TYPE_H

#include <stdint.h>
#include <string>
#include <vector>

#include "status.h"

namespace hart
{
    typedef std::vector<uint8_t> hart_data_t;
	class IHartType
	{
	public:
		virtual	size_t size() const = 0;
		//virtual typename TypeIterator begin() const = 0;
		//virtual typename TypeIterator end() const = 0;
        // hart_data_t data() = 0;
		virtual uint8_t operator[](int i) = 0;
		virtual std::string serialize() = 0;
		virtual util::Status deserialize(std::string value) = 0;
	};
};
#endif
