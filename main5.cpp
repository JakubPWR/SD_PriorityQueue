//#include <iostream>
//#include <chrono>
//
//class Node {
//public:
//    int data;
//    Node* next;
//
//    Node(int value) : data(value), next(nullptr) {}
//};
//
//class PriorityQueue {
//private:
//    Node* head;
//    bool isMaxPriority;
//
//public:
//    PriorityQueue(bool maxPriority = true) : head(nullptr), isMaxPriority(maxPriority) {}
//
//    void push(int value) {
//        Node* newNode = new Node(value);
//        if (!head || ((isMaxPriority && value > head->data) || (!isMaxPriority && value < head->data))) {
//            newNode->next = head;
//            head = newNode;
//        } else {
//            Node* current = head;
//            while (current->next && ((isMaxPriority && value <= current->next->data) || (!isMaxPriority && value >= current->next->data))) {
//                current = current->next;
//            }
//            newNode->next = current->next;
//            current->next = newNode;
//        }
//    }
//
//    int pop() {
//        if (!head) {
//            return -1;
//        }
//        int value = head->data;
//        Node* temp = head;
//        head = head->next;
//        delete temp;
//        return value;
//    }
//
//    int peek(int index) {
//        Node* current = head;
//        int count = 0;
//        while (current && count < index) {
//            current = current->next;
//            count++;
//        }
//        if (!current) {
//            std::cerr << "Index out of range!" << std::endl;
//            return -1;
//        }
//        return current->data;
//    }
//
//    void setMaxPriority(bool maxPriority) {
//        isMaxPriority = maxPriority;
//    }
//
//    void modifyPriority(int index, int newPriority) {
//        if (index == 0) {
//            pop();
//            push(newPriority);
//            return;
//        }
//        Node* current = head;
//        int count = 0;
//        while (current && count < index) {
//            current = current->next;
//            count++;
//        }
//        if (!current) {
//            std::cerr << "Index out of range!" << std::endl;
//            return;
//        }
//        current->data = newPriority;
//        if ((isMaxPriority && newPriority < current->next->data) || (!isMaxPriority && newPriority > current->next->data)) {
//            pop();
//            push(newPriority);
//        } else if ((isMaxPriority && newPriority > current->data) || (!isMaxPriority && newPriority < current->data)) {
//            Node* temp = current->next;
//            current->next = current->next->next;
//            push(temp->data);
//            delete temp;
//        }
//    }
//
//    int size() const {
//        int count = 0;
//        Node* current = head;
//        while (current) {
//            count++;
//            current = current->next;
//        }
//        return count;
//    }
//
//    ~PriorityQueue() {
//        while (head) {
//            Node* temp = head;
//            head = head->next;
//            delete temp;
//        }
//    }
//};
//
//int main() {
//    PriorityQueue maxPriorityQueue(true);
//    PriorityQueue minPriorityQueue(false);
//
//    // Fill queues
//    for (int i = 0; i < 1000; ++i) {
//        maxPriorityQueue.push(i);
//        minPriorityQueue.push(i);
//    }
//
//    // Measure time for push operation
//    auto start = std::chrono::high_resolution_clock::now();
//    maxPriorityQueue.push(1000);
//    auto end = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> elapsed = end - start;
//    std::cout << "Time to push element into maxPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;
//
//    start = std::chrono::high_resolution_clock::now();
//    minPriorityQueue.push(-1);
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = end - start;
//    std::cout << "Time to push element into minPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;
//
//    // Measure time for pop operation
//    start = std::chrono::high_resolution_clock::now();
//    maxPriorityQueue.pop();
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = end - start;
//    std::cout << "Time to pop element from maxPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;
//
//    start = std::chrono::high_resolution_clock::now();
//    minPriorityQueue.pop();
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = end - start;
//    std::cout << "Time to pop element from minPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;
//
//    // Measure time for peek operation
//    start = std::chrono::high_resolution_clock::now();
//    int peekedValueMax = maxPriorityQueue.peek(10);
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = end - start;
//    std::cout << "Time for peek(10) in maxPriorityQueue: " << elapsed.count() * 1e9 << " ns, value: " << peekedValueMax << std::endl;
//
//    start = std::chrono::high_resolution_clock::now();
//    int peekedValueMin = minPriorityQueue.peek(10);
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = end - start;
//    std::cout << "Time for peek(10) in minPriorityQueue: " << elapsed.count() * 1e9 << " ns, value: " << peekedValueMin << std::endl;
//
//    // Measure time for modify priority operation
//    start = std::chrono::high_resolution_clock::now();
//    maxPriorityQueue.modifyPriority(100, 2000);
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = end - start;
//    std::cout << "Time to modify priority in maxPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;
//
//    start = std::chrono::high_resolution_clock::now();
//    minPriorityQueue.modifyPriority(500, -2000);
//    end = std::chrono::high_resolution_clock::now();
//    elapsed = end - start;
//    std::cout << "Time to modify priority in minPriorityQueue: " << elapsed.count() * 1e9 << " ns" << std::endl;
//
//    std::cout << "Elements in maxPriorityQueue: ";
//    while (maxPriorityQueue.size() > 0) {
//        std::cout << maxPriorityQueue.pop() << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "Elements in minPriorityQueue: ";
//    while (minPriorityQueue.size() > 0) {
//        std::cout << minPriorityQueue.pop() << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}
