#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

// Define the monitor class
class Monitor {
private:
    std::queue<int> buffer;
    int size;
    std::mutex mtx;
    std::condition_variable bufferNotEmpty;
    std::condition_variable bufferNotFull;

public:
    Monitor(int bufferSize) : size(bufferSize) {}

    // Function to add value to the buffer
    void add(int value) {
        std::unique_lock<std::mutex> lock(mtx);
        bufferNotFull.wait(lock, [this] { return buffer.size() < size; });
        buffer.push(value);
        std::cout << "Value " << value << " added to buffer (size: " << buffer.size() << "/" << size << ")\n";
        bufferNotEmpty.notify_all();
    }

    // Function to remove value from the buffer
    int remove() {
        std::unique_lock<std::mutex> lock(mtx);
        bufferNotEmpty.wait(lock, [this] { return !buffer.empty(); });
        int value = buffer.front();
        buffer.pop();
        std::cout << "Value " << value << " removed from buffer (size: " << buffer.size() << "/" << size << ")\n";
        bufferNotFull.notify_all();
        return value;
    }
};

// Define the producer thread function
void producer(Monitor& monitor, int id, int numValues) {
    std::srand(std::time(nullptr));
    std::cout << "Producer " << id << " created\n";
    for (int i = 0; i < numValues; ++i) {
        int value = std::rand() % 10 + 1; // Generate random value between 1 and 10
        monitor.add(value);
    }
    std::cout << "Producer " << id << " finished\n";
}

// Define the consumer thread function
void consumer(Monitor& monitor, int id, int numValues) {
    std::cout << "Consumer " << id << " created\n";
    for (int i = 0; i < numValues; ++i) {
        int value = monitor.remove();
    }
    std::cout << "Consumer " << id << " finished\n";
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " buffer_size num_producers num_consumers\n";
        return 1;
    }

    int bufferSize = std::stoi(argv[1]);
    int numProducers = std::stoi(argv[2]);
    int numConsumers = std::stoi(argv[3]);

    Monitor monitor(bufferSize);

    std::vector<std::thread> producerThreads;
    std::vector<std::thread> consumerThreads;

    for (int i = 0; i < numProducers; ++i) {
        int numValues = bufferSize / numProducers + (i < bufferSize % numProducers ? 1 : 0);
        producerThreads.emplace_back(producer, std::ref(monitor), i, numValues);
    }

    for (int i = 0; i < numConsumers; ++i) {
        int numValues = bufferSize / numConsumers + (i < bufferSize % numConsumers ? 1 : 0);
        consumerThreads.emplace_back(consumer, std::ref(monitor), i, numValues);
    }

    for (auto& thread : producerThreads) {
        thread.join();
    }

    for (auto& thread : consumerThreads) {
        thread.join();
    }

    std::cout << "All threads finished\n";

    return 0;
}
