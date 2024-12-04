#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
bool active = false;

void worker_thread() {
  while (active) {
    // wait until main() sends data
    std::unique_lock lk(m);
    cv.wait(lk, [] { return ready; });

    // after the wait, we own the lock
    std::cout << "Worker thread is processing data\n";
    std::cout << "data is: " + data;
    data = "";

    // send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    lk.unlock();
    cv.notify_one();
  }
}

void send(std::string message) {
  std::thread worker(worker_thread);

  data = message;
  // send data to the worker thread
  {
    std::lock_guard lk(m);
    ready = true;
    std::cout << "send() signals data ready for processing\n";
  }
  cv.notify_one();

  // wait for the worker
  {
    std::unique_lock lk(m);
    cv.wait(lk, [] { return processed; });
  }
  std::cout << "Back in send(), data = " << data << '\n';

  worker.join();
}

extern "C" void example() {
  std::thread worker(worker_thread);

  data = "Example data";
  // send data to the worker thread
  {
    std::lock_guard lk(m);
    ready = true;
    std::cout << "example() signals data ready for processing\n";
  }
  cv.notify_one();

  // wait for the worker
  {
    std::unique_lock lk(m);
    cv.wait(lk, [] { return processed; });
  }
  std::cout << "Back in example(), data = " << data << '\n';

  worker.join();
}
