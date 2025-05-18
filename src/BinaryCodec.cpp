#include <iostream>
#include <boost/asio.hpp>
#include <cstring>
#include <cassert>

struct Point {
    float x, y;
};

int main() {
    uint8_t raw_buffer[1024];
    boost::asio::mutable_buffer write_buf(raw_buffer, sizeof(raw_buffer));

    int a = 42;
    float b = 2.71f;
    Point p = {5.0f, 6.0f};

    encode(write_buf, a);
    encode(write_buf, b);
    encode(write_buf, p);

    // Reading back
    boost::asio::const_buffer read_buf(raw_buffer, sizeof(raw_buffer));

    int a2;
    float b2;
    Point p2;

    decode(read_buf, a2);
    decode(read_buf, b2);
    decode(read_buf, p2);

    std::cout << "a2: " << a2 << ", b2: " << b2 << "\n";
    std::cout << "p2: (" << p2.x << ", " << p2.y << ")\n";

    return 0;
}
