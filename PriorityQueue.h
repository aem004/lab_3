
#ifndef LAB3_PRIORITYQUEUE_H

#include <cstdio>
#include <cstdlib>

using namespace std;

template<typename T, typename Cmp>
class TPQueue {
private:
    T *arr;
    size_t count{};
    size_t capacity{};
    Cmp comparator;
public:

    TPQueue() : arr(NULL), count(0), capacity(16) {}

    ~TPQueue() {
        this->clear();
    }

public:
    bool push(const T &val) {
        size_t i, p;
        T temporary_element;

        if (!this->_alloc())
            return false;
        arr[count] = val;

        i = count;
        p = (!i) ? 0 : (i - 1) >> 1;

        while ((i > 0) && !comparator(arr[p], arr[i])) {
            temporary_element = arr[i];
            arr[i] = arr[p];
            arr[p] = temporary_element;

            i = p--;
            if (!i)
                break;
            p >>= 1;
        }
        ++count;
        return true;
    }

    void pop() {
        if (count > 1) {
            arr[0] = arr[--count];
            this->this_heapify(0);
        } else
            count = 0;
    }

    void merge(TPQueue<T, Cmp> &queue) {
        while (!queue.empty()) {
            this->push(queue.top());
            queue.pop();
        }
    }

    TPQueue<T, Cmp> getRange(size_t i, size_t j) {
        TPQueue<T, Cmp> temp;
        if (i > j) {
            i = i + j;
            j = i - j;
            i = i - j;
        }
        if (j >= count)
            j = count - 1;
        if (i < 0)
            i = 0;
        auto arr_cur = new T[j + 1];
        for (size_t k = 0; k <= j; ++k) {
            if (k >= i)
                temp.push(this->top());
            arr_cur[k] = this->top();
            this->pop();
        }
        for (size_t k = 0; k <= j; ++k)
            this->push(arr_cur[k]);
        delete[] arr_cur;
        return temp;
    }


    std::string toString(TPQueue<T, Cmp> &tpQueue) {
        std::string builder;
        size_t size_cur = tpQueue.size();
        auto arr_cur = new T[size_cur];

        for (int i = 0; i < size_cur; ++i) {
            builder += to_string(tpQueue.top());
            builder += " ";
            arr_cur[i] = tpQueue.top();
            tpQueue.pop();
        }
        for (int i = 0; i < size_cur; ++i) {
            tpQueue.push(arr_cur[i]);
        }
        builder += "\r\n";
        delete[] arr_cur;
        return builder;
    }

    friend std::ostream &operator<<(std::ostream &out, TPQueue<T, Cmp> &tpQueue) {
        size_t size_cur = tpQueue.size();
        auto arr_cur = new T[size_cur];


        for (int i = 0; i < size_cur; ++i) {
            out << tpQueue.top() << " ";
            arr_cur[i] = tpQueue.top();
            tpQueue.pop();
        }
        for (int i = 0; i < size_cur; ++i) {
            tpQueue.push(arr_cur[i]);
        }
        out << std::endl;
        delete[] arr_cur;
        return out;
    }


    friend bool operator==(const TPQueue<T, Cmp> &tpQueue1 ,const TPQueue<T, Cmp> &tpQueue2) {
        if(tpQueue1.count != tpQueue2.count)
            return false;
        for(size_t i = 0; i < tpQueue1.count; ++i){
            if(tpQueue1.arr[i] != tpQueue2.arr[i]){
                return false;
            }
        }
        return true;
    }


    T &top() { return arr[0]; }

    T &top() const { return arr[0]; }

    bool empty() const { return !count; }

    size_t size() const { return count; }

    void clear() {
        if (arr != NULL)
            delete[] arr;
        arr = NULL;
        count = 0;
        capacity = 16;
    }

    template<class F>
    void map(F func) {
        int count_cur = count;
        T *temp = new T[count_cur];
        for (size_t i = 0; i < count_cur; i++) {
            temp[i] = (*func)(this->top());
            this->pop();
        }
        for (size_t i = 0; i < count_cur; ++i) {
            this->push(temp[i]);
        }
        delete[] temp;
    }

    template<class F>
    T reduce(F func) {
        int count_cur = count;
        T *temp = new T[count_cur];
        T result;
        if (count_cur == 0)
            return 0;
        if (count_cur == 1)
            return arr[0];
        T first = this->top();
        temp[0] = first;
        this->pop();
        T second;
        for (size_t i = 1; i < count_cur; i++) {
            second = this->top();
            this->pop();
            result = (*func)(first, second);
            temp[i] = second;
            first = result;
        }
        for (size_t i = 0; i < count_cur; ++i) {
            this->push(temp[i]);
        }
        delete[] temp;
        return result;
    }

    template<class F>
    void where(F func) {
        int count_cur = count;
        T *temp = new T[count_cur];
        size_t true_size = 0;
        for (size_t i = 0; i < count_cur; i++) {
            if ((*func)(this->top())) {
                temp[true_size] = this->top();
                ++true_size;
            }
            this->pop();
        }
        for (size_t i = 0; i < true_size; ++i) {
            this->push(temp[i]);
        }
        delete[] temp;
    }

private:

    bool _alloc() {
        size_t temp_mem;
        T *tmp;


        if (arr == NULL) {
            arr = new T[capacity];
            if (arr == NULL)
                return false;
        }

        if ((count + 1) >= capacity) {
            temp_mem = count + 1 + count / 3;
            tmp = new T[temp_mem];
            if (tmp == NULL)
                return false;
            for (size_t i = 0u; i < count; ++i)
                tmp[i] = arr[i];
            delete[] arr;
            arr = tmp;
            capacity = temp_mem;
        }
        return true;
    }

    void this_heapify(size_t index) {
        size_t l, r, big;
        T tmp;

        while (true) {
            l = (index << 1) + 1u;
            r = (index << 1) + 2u;

            if ((l < count) && comparator(arr[l], arr[index]))
                big = l;
            else
                big = index;

            if ((r < count) && comparator(arr[r], arr[big]))
                big = r;

            if (big != index) {
                tmp = arr[index];
                arr[index] = arr[big];
                arr[big] = tmp;
                index = big;
            } else
                break;
        }
    }
};

#define LAB3_PRIORITYQUEUE_H

#endif //LAB3_PRIORITYQUEUE_H
