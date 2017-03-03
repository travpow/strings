

#ifndef sstring_HPP
#define sstring_HPP

#include <string>
#include <cstdint>
#include <iostream>

/**
 * sstring: shallow string
 *
 * This class does not own its string pointer, it's merely a wrapper around a char* and size
 * with some helper methods to facilitate easier comparison/copy/etc.
 */
class sstring {
public:
    sstring()
        : str_(nullptr), size_(0)
    {
    }

    sstring(const char* s, size_t l)
        : str_(s), size_(l)
    {
    }

    sstring(const char* s)
        : str_(s)
    {
        size_ = s ? strlen(s) : 0;
    }

    sstring(const std::string& s)
        : str_(s.c_str()), size_(s.size())
    {
    }

    inline const size_t size() const
    {
        return size_;
    }

    inline const size_t length() const
    {
        return size();
    }

    inline const char* c_str() const
    {
        return str_;
    }

    sstring& operator =(const char* str)
    {
        str_ = str;
        size_ = str ? strlen(str) : 0;

        return *this;
    }

    sstring& operator =(const sstring& str)
    {
        str_ = str.c_str();
        size_ = str.size();

        return *this;
    }

    char& operator [](size_t n)
    {
        return const_cast<char*>(str_)[n];
    }

    inline const char operator [](size_t n) const
    {
        return str_[n];
    }

    inline bool operator==(const char* s) const
    {
        // Cannot mutate the size -- so we're just going to do an unsafe compare
        // as our buffer will always be NUL-terminated.
        return strncmp(c_str(), s, size()) == 0;
    }

    inline bool operator==(const std::string& s) const
    {
        return strncmp(c_str(), s.c_str(), size()) == 0;
    }

    inline bool operator==(const sstring& s) const
    {
        return size() == s.size() &&
            strncmp(c_str(), s.c_str(), size()) == 0;
    }

    void substr(size_t from, size_t count)
    {
        str_ += from;
        size_ = count;
    }

    sstring&& substr(size_t from, size_t count) const
    {
        return std::move(sstring(c_str() + from, count));
    }

private:
    const char* str_;
    size_t size_;

    friend std::ostream& operator <<(std::ostream& os, const sstring& fs);
};

std::ostream& operator <<(std::ostream& os, const sstring& ss)
{
    return os << std::string(ss.c_str(), ss.size());
}

#endif // sstring_HPP
