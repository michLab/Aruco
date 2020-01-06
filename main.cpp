#include <iostream>
#include <aruco.h>

using namespace std;

int main()
{
    aruco_ns::Aruco aruco;

    for (int i = 0; i < 10; i++) {
        aruco.generate_marker(i);
    }
    return 0;
}
