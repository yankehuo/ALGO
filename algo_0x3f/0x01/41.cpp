#include <iostream>
#include <vector>

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        stkVal.push_back(x);
        if (stkMin.empty() || stkMin.back() >= x) {
            stkMin.push_back(x);
        }
    }
    
    void pop() {
        if (stkMin.back() == stkVal.back()) {
            stkMin.pop_back();
        }
        stkVal.pop_back();
    }
                                  
    int top() {
        return stkVal.back();
    }
    
    int getMin() {
        return stkMin.back();
    }
private:
    std::vector<int> stkVal, stkMin;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */

int main() {
    MinStack obj;
    int arr[] = {9, 2, 1, 5, 3, 0, 2};
    for (int i = 0; i < 7; ++i) {
        obj.push(arr[i]);
    }
    obj.pop();
    obj.pop();
    int param_3 = obj.top();
    int param_4 = obj.getMin();
    std::cout << param_3 << std::endl;
    std::cout << param_4 << std::endl;

    return 0;
}