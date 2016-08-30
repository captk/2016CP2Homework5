#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// definition

#define MAX_LENGTH 100
#define INIT_VALUE 0

class Array {
public:
    Array(int length);
    Array(const Array& other);
    Array(const string& inString);
    Array& operator=(const Array& other);

    int length() const;
    operator std::string() const;
    int& operator[](int index);

    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;
    friend ostream& operator<<(std::ostream&, const Array&);
    friend istream& operator>>(std::istream&, const Array&);


private:
    int length_;
    int elements_[MAX_LENGTH];
};

// implementation

ostream& operator<<(std::ostream& os, const Array& array) {
    return os << "{" << string(array) << "}";
}

Array& operator>>(std::istream& is, Array& array) {
    string inString;
    stringstream sstream;
    if (is.get() != '{'){
        return array;
    }
    int number;
    while(is.peek() != '}'){
        is >> number;
        sstream << number;
        if (is.peek() != '}')
            sstream << " ";
    }
    getline(sstream, inString);
    array = Array(inString);
    return array;
}

Array::Array(int length) {
    length_ = length;
    if (length_ > MAX_LENGTH) length_ = MAX_LENGTH;
    for (int i = 0; i < length_; ++i) {
        elements_[i] = INIT_VALUE;
    }
}

Array::Array(const Array& other) {
    length_ = other.length_;
    if (length_ > MAX_LENGTH) length_ = MAX_LENGTH;
    for (int i = 0; i < length_; ++i) {
        elements_[i] = other.elements_[i];
    }
}

Array::Array(const string& inString) {
    stringstream aStream;
    aStream << inString;
    int count = 0;
    while (!aStream.eof()) {
        aStream >> elements_[count];
        count++;
        length_ = count;
    }

}

Array& Array::operator=(const Array& other) {
    this->length_ = other.length_;
    for (int i = 0; i < other.length_; i++) {
        this->elements_[i] = other.elements_[i];
    }
    return *this;
}

Array::operator std::string() const {
    stringstream aStream;
    for (int i = 0; i < this->length_; i++) {
        aStream << this->elements_[i];
        if (i != this->length_ -1){
            aStream << " ";
        }
    }
    string output;
    getline(aStream, output);
    return output;
}

int Array::length() const {
    return length_;
}

int& Array::operator[](int index) {
    if (length_ - 1 < index) return elements_[length_ - 1];
    if (index < 0) return elements_[0];
    return elements_[index];
}

bool Array::operator==(const Array& other) const {
    if (length_ != other.length_) return false;
    for (int i = 0; i < other.length_; ++i) {
        if (elements_[i] != other.elements_[i]) return false;
    }
    return true;
}

bool Array::operator!=(const Array& other) const {
    // replace with Q1 code
    if (length_ != other.length_) return true;
    for (int i = 0; i < other.length_; ++i) {
        if (elements_[i] != other.elements_[i]) return true;
    }
    return false;
}

// testing

int main() {
    Array x(10);
    x[3] = 42;
    cout << "x contains ";
    for (int i = 0; i < x.length(); ++i) {
        cout << x[i] << " ";
    }
    cout << endl;

    Array y(5);
    cout << boolalpha;
    cout << "x equals y? " << (x == y) << endl;

    //q1
    cout << "x notequals y? " << (x != y) << endl;

    //q2
    y = x;

    //q3
    y[0] = 1;
    y[9] = 9;
    for (int i = -10; i < 12; i++) {
        cout << "i = " << i << " y = " << y[i] << endl;
    }
    cout << "x equals y? " << (x == y) << endl;

    //q4
    Array z(y);
    y[0] += 1;
    cout << "x equals z? " << (x == z) << endl;
    cout << "y equals z? " << (y == z) << endl;

    //q5
    Array t("1 2 3 4 5");
    cout << "t contains the values " << string(t) << endl;

    //q6
    cout << "Enter a value for t: ";
    cin >> t;
    cout << "You entered " << t << endl;
}
