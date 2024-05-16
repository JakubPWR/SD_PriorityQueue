#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

class PriorityQueue {
private:
    std::vector<int> elements;
    bool isMaxPriority;

    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if ((isMaxPriority && elements[index] > elements[parentIndex]) ||
                (!isMaxPriority && elements[index] < elements[parentIndex])) {
                std::swap(elements[index], elements[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < elements.size() && ((isMaxPriority && elements[leftChild] > elements[largest]) ||
                                                (!isMaxPriority && elements[leftChild] < elements[largest]))) {
                largest = leftChild;
            }

            if (rightChild < elements.size() && ((isMaxPriority && elements[rightChild] > elements[largest]) ||
                                                 (!isMaxPriority && elements[rightChild] < elements[largest]))) {
                largest = rightChild;
            }

            if (largest != index) {
                std::swap(elements[index], elements[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    PriorityQueue(bool maxPriority = true) : isMaxPriority(maxPriority) {}

    void push(int value) {
        elements.push_back(value);
        heapifyUp(elements.size() - 1);
    }

    int pop() {
        if (elements.empty()) {
            return -1;
        }
        elements[0] = elements.back();
        elements.pop_back();
        heapifyDown(0);
        return elements[0];
    }

    int peek(int index) {
        if (index >= elements.size() || index < 0) {
            std::cerr << "Index out of range!" << std::endl;
            return -1; // Or throw an exception
        }
        return elements[index];
    }

    void setMaxPriority(bool maxPriority) {
        isMaxPriority = maxPriority;
    }

    void modifyPriority(int index, int newPriority) {
        if (index >= elements.size() || index < 0) {
            std::cerr << "Index out of range!" << std::endl;
            return;
        }
        int oldPriority = elements[index];
        elements[index] = newPriority;
        if ((isMaxPriority && newPriority > oldPriority) || (!isMaxPriority && newPriority < oldPriority)) {
            heapifyUp(index);
        } else {
            heapifyDown(index);
        }
    }

    int size() const {
        return elements.size();
    }
};

int main() {
    PriorityQueue maxPriorityQueue(true);
    PriorityQueue minPriorityQueue(false);

    // Wypełnienie kolejek
    for (int i = 0; i < 1000; ++i) {
        int x = 0;
        if(i%2 ==0)
        {
            x = i*3;
            maxPriorityQueue.push(x);
            minPriorityQueue.push(x);
            continue;
        }
        maxPriorityQueue.push(i);
        minPriorityQueue.push(i);
    }

    // Pomiar czasu dla operacji dodawania
    auto start = std::chrono::high_resolution_clock::now();
    maxPriorityQueue.push(1000);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Czas dodawania elementu do maxPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    minPriorityQueue.push(-1);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Czas dodawania elementu do minPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;

    // Pomiar czasu dla operacji usuwania
    start = std::chrono::high_resolution_clock::now();
    maxPriorityQueue.pop();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Czas usuwania elementu z maxPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    minPriorityQueue.pop();
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Czas usuwania elementu z minPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;

    // Pomiar czasu dla operacji peek
    start = std::chrono::high_resolution_clock::now();
    int peekedValueMax = maxPriorityQueue.peek(10);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Czas peek(10) w maxPriorityQueue: " << elapsed.count() * 1e9 << " ns, wartość: " << peekedValueMax << std::endl;

    start = std::chrono::high_resolution_clock::now();
    int peekedValueMin = minPriorityQueue.peek(10);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Czas peek(10) w minPriorityQueue: " << elapsed.count() * 1e9 << " ns, wartość: " << peekedValueMin << std::endl;

    // Pomiar czasu dla operacji modyfikacji priorytetu
    start = std::chrono::high_resolution_clock::now();
    maxPriorityQueue.modifyPriority(100, 2000);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Czas modyfikacji priorytetu w maxPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    minPriorityQueue.modifyPriority(500, -2000);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Czas modyfikacji priorytetu w minPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;

    std::cout << "Elementy w maxPriorityQueue: ";
    for (int i = 0; i < maxPriorityQueue.size(); ++i) {
        std::cout << maxPriorityQueue.pop() << " ";
    }
    std::cout << std::endl;
    std::cout << "Elementy w minPriorityQueue: ";
    for (int i = 0; i < minPriorityQueue.size(); ++i) {
        std::cout << minPriorityQueue.pop() << " ";
    }
        return 0;
}

