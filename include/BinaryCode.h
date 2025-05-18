template <typename T>
size_t encode(boost::asio::mutable_buffer& buffer, const T& value) {
    assert(boost::asio::buffer_size(buffer) >= sizeof(T));
    std::memcpy(buffer.data(), &value, sizeof(T));
    buffer = buffer + sizeof(T); // advance buffer
    return sizeof(T);
}

template <typename T>
size_t decode(boost::asio::const_buffer& buffer, T& value) {
    assert(boost::asio::buffer_size(buffer) >= sizeof(T));
    std::memcpy(&value, buffer.data(), sizeof(T));
    buffer = buffer + sizeof(T); // advance buffer
    return sizeof(T);
}
