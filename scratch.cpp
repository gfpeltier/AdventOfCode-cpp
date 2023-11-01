#include <iostream>

using namespace std;


class MyClass {
    private:
        int* nptr;
    public:
        MyClass(int* p): nptr(p) {
            cout << "Constuctor: " << p << endl;
        }

        int* getNptr() { return nptr; }
};

int main(int argc, char* argv[]) {
    int x = 21;
    int y = 42;
    int* xp = &x;
    MyClass mc = MyClass(xp);
    cout << "Post construct" << mc.getNptr() << endl;
    xp = &y;
    cout << "Post reassign" << mc.getNptr() << endl;
}