// Standard
#include <stdint.h>
#include <iostream>
#include <thread>
#include <array>
#include <atomic>
#include <memory>

// Third party
#include "boost\lockfree\spsc_queue.hpp"
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

// Project
#include "Status.h"
#include "IReader.h"
#include "IWriter.h"
using namespace hts;

typedef boost::lockfree::spsc_queue<std::vector<uint8_t>, boost::lockfree::capacity<10> > MessageQueue;

template <typename T>
class WorkerWriter
{
public:
    WorkerWriter(MessageQueue& queue, std::atomic_bool& running) : m_queue(queue), m_writer(new T()), m_running(running) {}
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

template <typename T>
class WorkerReader
{
public:
    WorkerReader(MessageQueue& queue, std::atomic_bool& running) : m_reader(new T()), m_running(running), m_queue(queue) {}
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

int main(int argc, char *argv[])
{
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "hart_serial started.";

    // Create components
    std::atomic_bool running;
    MessageQueue queue;
    WorkerReader<ReaderConsole> reader(queue, running);
    WorkerWriter<WriterConsole> writer(queue, running);

    auto reader_thread = std::thread(reader);
    auto writer_thread = std::thread(writer);

    reader_thread.join();
    writer_thread.join();

    std::cout << "Done!";
    return 0;
}