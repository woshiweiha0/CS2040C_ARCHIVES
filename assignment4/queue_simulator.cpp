#include "queue_simulator.h"
#include <stdexcept>

vector<Customer> QueueSimulator::simulateQueue(const vector<Customer>& customerList) {
    if (customerList.empty()) {
        throw std::out_of_range("No customers");
    }

    vector<Customer> servedCustomers;
    vector<int> serverEndTimes(_num_servers, 0);
    vector<Customer> unarrivedCustomers = customerList;
    Heap<Customer> customerHeap;

    // Sort customers by arrival time
    for (size_t i = 1; i < unarrivedCustomers.size(); i += 1) {
        Customer key = unarrivedCustomers[i];
        int j = i - 1;
        // Move customers with greater arrival time one position ahead
        while (j >= 0 && unarrivedCustomers[j].arrival_time() > key.arrival_time()) {
            unarrivedCustomers[j + 1] = unarrivedCustomers[j];
            j -= 1;
        }
        unarrivedCustomers[j + 1] = key;
    }

    int currentTime = 0;
    size_t unarrivedIndex = 0;

    while (servedCustomers.size() < customerList.size()) {
        // Move newly arrived customers into the heap
        while (unarrivedIndex < unarrivedCustomers.size() &&
            unarrivedCustomers[unarrivedIndex].arrival_time() <= currentTime) {
            Customer customer = unarrivedCustomers[unarrivedIndex];
            customer.set_compare_by_processing_time(_priority_order);
            customerHeap.insert(customer);
            unarrivedIndex += 1;
        }

        // Assign available servers to customers
        for (int server = 0; server < _num_servers; server += 1) {
            if (serverEndTimes[server] <= currentTime && !customerHeap.empty()) {
                Customer nextCustomer = customerHeap.extractMax();
                nextCustomer.set_service_time(currentTime);
                serverEndTimes[server] = currentTime + nextCustomer.processing_time();
                servedCustomers.push_back(nextCustomer);
            }
        }

        currentTime += 1;
    }

    return servedCustomers;
}


