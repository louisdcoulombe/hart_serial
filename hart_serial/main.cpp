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
#include "hts_types.h"
#include "Status.h"
#include "WorkerReader.h"
#include "WorkerWriter.h"
using namespace hts;


int main(int argc, char *argv[])
{
    START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "hart_serial started.";

    // Create components
    MessageQueue queue;
    std::atomic_bool running;
    WorkerReader reader(queue, std::make_shared<ReaderConsole>(), running);
    WorkerWriter writer(queue, std::make_shared<WriterConsole>(), running);

    // Start threads
    auto reader_thread = std::thread(reader);
    auto writer_thread = std::thread(writer);
    
    // Wait to finish
    reader_thread.join();
    writer_thread.join();

    std::cout << "Done!";
    return 0;
}