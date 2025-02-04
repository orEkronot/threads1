#include <iostream>
#include <thread>

using std::cout;
using std::endl;

void F(const std::string& color_code) {
    static short counter = 1;
    int ins = counter++; // save instance number

    int i = 10;
    while (i--) {
        cout << color_code << "Instance #" << ins << " is now running"  << endl;
    }

    cout << color_code << "Instance #" << ins << " is now exiting..." << endl;
}

int main() {
    std::thread t1([]() { F("\033[31m"); }); // Red
    std::thread t2([]() { F("\033[32m"); }); // Green

    t1.join();
    t2.join();

    // t1 & t2 are now running simultaneously

    system("PAUSE");
	
    return 0;
}
