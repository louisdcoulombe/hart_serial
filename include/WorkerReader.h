#ifndef HTS_WORKERREADER_H
#define HTS_WORKERREADER_H

#include <stdint.h>
#include <iostream>
#include <vector>

#include "hts_types.h"
#include "IReader.h"

namespace hts
{
	class WorkerReader
	{
	public:
		WorkerReader(MessageQueue& queue, std::shared_ptr<IReader> reader, std::atomic_bool& running) : m_reader(reader), m_running(running), m_queue(queue) {}
		void operator()(void)
		{
			while (true)
			{
				auto data = m_reader->read();
				if (data.size() == 0)
				{
					m_running = false;
					break;
				}

				m_queue.push(data);
			}
		}
	private:
		std::atomic_bool& m_running;
		std::shared_ptr<IReader> m_reader;
		MessageQueue& m_queue;
	};
}


#endif // !HTS_WORKERREADER_H

