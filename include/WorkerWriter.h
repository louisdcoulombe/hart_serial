#ifndef HTW_WORKERWRITER_H
#define HTW_WORKERWRITER_H

#include <stdint.h>
#include <iostream>
#include <vector>
#include <thread>
#include <memory>

#include "hts_types.h"
#include "IWriter.h"

namespace hts
{
	class WorkerWriter
	{
	public:
		WorkerWriter(MessageQueue& queue, std::shared_ptr<IWriter> writer, std::atomic_bool& running) : m_queue(queue), m_writer(writer), m_running(running) {}
		void operator()(void)
		{
			while (true)
			{
				std::vector<uint8_t> msg;
				if (m_queue.pop(msg))
				{
					m_writer->write(msg);
				}
				else
				{
					if (!m_running) break;
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			}
		}

	private:
		MessageQueue& m_queue;
		std::shared_ptr<IWriter> m_writer;
		std::atomic_bool& m_running;
	};
}


#endif // !HTW_WORKERWRITER_H

