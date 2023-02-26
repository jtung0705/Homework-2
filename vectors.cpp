#include <iostream>
using namespace std;



class Vec
{
private:
    int size;
    int cap;
    int* arr;
public:
    int grab_Size() {
        return size;
    }
    int grab_Capacity() {
        return cap;
    }
    int* grab_Arr() {
        return arr;
    }
    int idxFirst(int number) {
        for (int i = 0; i < size; i++) {
            // if (number == *( grab_Arr() + i ) ){ // if the number is found
            if (number == grab_Arr()[i]) {
                return i;
            }
        }
        throw "Not Available\n";
    }

    // example: remove(8), do I rremove index slot 8 or do i remove all numbers that are 8
    void removeIndex(int num) {
        for (int i = num; i < (size - 1); i++) {
            grab_Arr()[i] = grab_Arr()[i + 1];
            // failsafe allows if its out of bounds to just be zero
        }
        grab_Arr()[size - 1] = 0;
        // the data is now overwritten as zero so as to not mess with addition operator
        size--;
    }

    void idxAll(int number) {
        cout << "The number " << number << " is found at";
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (number == grab_Arr()[i]) {
                if (!found) {
                    cout << " slot ";
                }
                cout << i << ", ";
                found = true;
            }
        }
        cout << ((found) ? "in this vector." : " nowhere.");
    }

    Vec()
    {
        size = 0;
        cap = 4;
        arr = new int[cap];
    }

    void insert(int slot, int x)
    {
        for (int i = size - 1; i >= slot; i--)
        {
            arr[i + 1] = arr[i];   // pushes everything up     
        }
        arr[slot] = x;
        size++;
    }

    void reserve(int new_cap)
    {
        if (new_cap > cap)
        {
            cap = new_cap;
            int* tmp = new int[cap];
            for (int i = 0; i < size; i++)
            {
                tmp[i] = arr[i];
            }
            delete[] arr;
            arr = tmp;
        }
    }

    void push_back(int x)
    {
        if (size == cap)
        {
            cap *= 2;
            reserve(cap);
        }
        arr[size++] = x;
    }

    void pop() {
        if (size > 0) {
            size--;
        }
    }

    int& at(int idx)
    {
        if (idx >= size || idx < 0)
        {
            throw "[Vector] Index out of bound!";
        }
        return arr[idx];
    }

    int& operator[](int idx)
    {
        if (idx >= size || idx < 0)
        {
            throw "[Vector] Index out of bound!";
        }
        return arr[idx];
    }

    ~Vec()
    {
        delete[] arr;
    }

    //The C++ function std::vector::operator== tests whether two vectors are equal or not. Operator == first checks the size of both container, if sizes are same then it compares elements sequentially and comparison stops at first mismatch.
    bool operator<(Vec& rhs) {
        if (size != rhs.size)
        {
            return (size < rhs.size);
        }
        else {
            for (int i = 0; i < size; i++) {
                if ((grab_Arr()[i]) < rhs[i]) {
                    return true;
                }
            }
            return false;
        }
    }

    bool operator>(Vec& rhs) {
        return (rhs < *this);
    }


    bool operator==(Vec& rhs) {
        if ((!(*this > rhs) && !(*this < rhs))) {
            for (int i = 0; i < size; i++) {
                if ((this->grab_Arr()[i]) != rhs[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool operator!=(Vec& rhs) {
        return (!(*this == rhs));
    }
    bool operator >=(Vec& rhs) {
        return ((*this > rhs) || (*this == rhs)); // can i just use ! >

    }
    bool operator <=(Vec& rhs) {
        return ((*this < rhs) || (*this == rhs)); //|| (*this == rhs) (*this > rhs)
    }


    Vec operator+(const Vec& rhs) const {
        Vec total;
        total.size = ((this->size < rhs.size) ? rhs.size : this->size);
        total.cap = ((this->cap < rhs.cap) ? rhs.cap : this->cap);
        for (int i = 0; i < total.cap; i++) {
            total.arr[i] = this->arr[i] + rhs.arr[i];
        }
        return total;
    }

    friend ostream& operator<<(ostream& os, Vec& v);

};


ostream& operator<<(ostream& os, Vec& v) {
    os << "[";
    for (int i = 0; i < v.grab_Size() - 1; i++)
    {
        os << v.grab_Arr()[i] << ", ";
    }
    os << v.grab_Arr()[v.grab_Size() - 1] << "]";
    return os;
}

int main()
{
    Vec v;
    v.push_back(3);
    v.push_back(23);
    v.push_back(0);
    v.push_back(8);
    v.push_back(93);


    Vec k;
    k.push_back(3);
    k.push_back(23);
    k.push_back(0);
    k.push_back(8);
    k.push_back(93);
    k.push_back(93333);
    cout << "Vector V: " << v << endl;
    cout << "Vector K: " << k << endl;
    cout << "First appearance of 3 in v is at index " << v.idxFirst(3) << endl;
    cout << "First appearance of 3 in k is at index " << k.idxFirst(3) << endl;
    v.idxAll(3);
    cout << "\nVector V: " << v << " pre-removed.";
    v.removeIndex(2);
    cout << "\nVector V: " << v << " post-removed.";
    cout << "\nVector K: " << k << " pre-inserted.\n";
    k.insert(1, 234);
    cout << "Vector K: " << k << " post-inserted.\n";
    cout << v << endl;
    v.insert(2, 0);
    v.insert(1, 234);
    cout << v << endl;
    cout << k << endl;
    cout << "\nIs v the same as k? " << ((v == k) ? "true" : "false"); // 0 means false it isnt
    cout << "\nIs v greater than k? " << ((v > k) ? "true" : "false"); // true
    cout << "\nIs v greater or equal than k? " << ((v >= k) ? "true" : "false");
    cout << "\nIs v less or equal than k? " << ((v <= k) ? "true" : "false"); // problemm
    Vec j = v + k;
    cout << "\nVector V: " << v << "\n + \nVector K: " << k << "\n = \nVector J: " << j;
    cout << v.grab_Arr()[6];
    return 0;
}