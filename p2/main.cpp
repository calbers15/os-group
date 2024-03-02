#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

// Define the monitor class
class Monitor {
private:
    queue<int> buffer;
    int size;
    mutex mtx;
    condition_variable bufferNotEmpty;
    condition_variable bufferNotFull;

public:
    Monitor(int bufferSize) : size(bufferSize) {}

    // Function to add value to the buffer
    void add(int value) {
        unique_lock<mutex> lock(mtx);
        bufferNotFull.wait(lock, [this] { return buffer.size() < size; });
        buffer.push(value);
        cout << "Value " << value << " added to buffer (size: " << buffer.size() << "/" << size << ")\n";
        bufferNotEmpty.notify_all();
    }

    // Function to remove value from the buffer
    int remove() {
        unique_lock<mutex> lock(mtx);
        bufferNotEmpty.wait(lock, [this] { return !buffer.empty(); });
        int value = buffer.front();
        buffer.pop();
        cout << "Value " << value << " removed from buffer (size: " << buffer.size() << "/" << size << ")\n";
        bufferNotFull.notify_all();
        return value;
    }
};

// Define the producer thread function
void producer(Monitor& monitor, int id, int numValues) {
    srand(time(nullptr));
    cout << "Producer " << id << " created\n";
    for (int i = 0; i < numValues; ++i) {
        int value = rand() % 10 + 1; // Generate random value between 1 and 10
        monitor.add(value);
    }
    cout << "Producer " << id << " finished\n";
}

// Define the consumer thread function
void consumer(Monitor& monitor, int id, int numValues) {
    cout << "Consumer " << id << " created\n";
    for (int i = 0; i < numValues; ++i) {
        int value = monitor.remove();
    }
    cout << "Consumer " << id << " finished\n";
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " buffer_size num_producers num_consumers\n";
        return 1;
    }

    int bufferSize = stoi(argv[1]);
    int numProducers = stoi(argv[2]);
    int numConsumers = stoi(argv[3]);

    Monitor monitor(bufferSize);

    vector<std::thread> producerThreads;
    vector<std::thread> consumerThreads;

    for (int i = 0; i < numProducers; ++i) {
        int numValues = bufferSize / numProducers + (i < bufferSize % numProducers ? 1 : 0);
        producerThreads.emplace_back(producer, ref(monitor), i, numValues);
    }

    for (int i = 0; i < numConsumers; ++i) {
        int numValues = bufferSize / numConsumers + (i < bufferSize % numConsumers ? 1 : 0);
        consumerThreads.emplace_back(consumer, ref(monitor), i, numValues);
    }

    for (auto& thread : producerThreads) {
        thread.join();
    }

    for (auto& thread : consumerThreads) {
        thread.join();
    }

    cout << "All threads finished\n";

    return 0;
}
