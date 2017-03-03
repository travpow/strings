

#ifndef FSTRING_HPP
#define FSTRING_HPP

#include <string>
#include <cstdint>
#include <iostream>

/**
 * fstring: fixed length string
 *
 * > Guaranteed to be null-terminated
 *   - All mutations append a NUL byte to the end of the buffer
 *   - All array access (operator[]) marks the size bit as dirty
 *
 * > Supports assignment, copy, concatenation, and streams.
 */
template<size_t SIZE>
class fstring {
public:
    fstring()
        : size_(0), sizeDirty_(false)
    {
    }

    fstring(const char* s, size_t l)
        : size_(0), sizeDirty_(false)
    {
        copy(s, l);
    }

    fstring(const char* s)
        : size_(0), sizeDirty_(false)
    {
        copy(s, maxlen());
    }

    fstring(const std::string& s)
        : size_(0), sizeDirty_(false)
    {
        copy(s.c_str(), s.length());
    }

    inline const size_t maxlen() const
    {
        return SIZE;
    }

    inline const size_t size()
    {
        if (sizeDirty_)
        {
            size_ = strlen(buf_);
            sizeDirty_ = false;
        }

        return size_;
    }

    inline const size_t size() const
    {
        return strlen(size_);
    }

    inline const size_t length()
    {
        return size();
    }

    inline const char* c_str() const
    {
        return buf_;
    }

    const fstring<SIZE>& operator =(const char* str)
    {
        size_ = 0;
        copy(str, maxlen());
    }

    void operator +=(fstring& str)
    {
        copy(str.c_str(), str.length());
    }

    void operator +=(const char* str)
    {
        copy(str, maxlen());
    }

    char& operator [](size_t n)
    {
        sizeDirty_ = true;
        return buf_[n];
    }

    inline const char operator [](size_t n) const
    {
        return buf_[n];
    }

    inline fstring<SIZE>&& operator +(const fstring& rhs) const
    {
        fstring<SIZE> ret;
        ret.copy(c_str(), maxlen());
        ret.copy(rhs.c_str(), rhs.maxlen());

        return std::move(ret);
    }

    inline bool operator==(const char* 

private:
    size_t size_;
    bool sizeDirty_;
    char buf_[SIZE + 1];

    template<size_t SIZE_OS>
    friend std::ostream& operator <<(std::ostream& os, const fstring<SIZE_OS>& fs);

    size_t lazySize() const
    {
        return strlen(c_str());
    }

    void copy(const char* s, size_t maxlen)
    {
        for (; *s && size_ < maxlen; s++, size_++)
        {
            buf_[size_] = *s;
        }

        buf_[size_] = 0;
    }
};

template<size_t SIZE>
std::ostream& operator <<(std::ostream& os, const fstring<SIZE>& fs)
{
    return os << fs.c_str();
}

#endif // FSTRING_HPP
