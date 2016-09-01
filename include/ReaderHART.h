#ifndef HTS_READERHART_H
#define HTS_READERHART_H

#include <stdint.h>
#include <iostream>
#include <queue>

#include "hts_types.h"
#include "IReader.h"

namespace hts
{
	class ReaderHART : public IReader
	{
	public:
		virtual std::vector<uint8_t> read() override
		{
			for each(auto v in m_buffer)
			{
							
			}

		}
	private:
		std::queue<uint8_t> m_buffer;
	};
}


#endif // !HTS_READERHART_H

