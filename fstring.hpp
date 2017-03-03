

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
template<size_t SIZE, typename CHAR = char>
class fstring {
public:
    fstring()
        : size_(0), sizeDirty_(false)
    {
    }

    fstring(const CHAR* s, size_t l)
        : size_(0), sizeDirty_(false)
    {
        copy(s, l);
    }

    fstring(const CHAR* s)
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

    inline const size_t length()
    {
        return size();
    }

    inline const CHAR* c_str() const
    {
        return buf_;
    }

    fstring<SIZE>& operator =(const CHAR* str)
    {
        size_ = 0;
        copy(str, maxlen());

        return *this;
    }

    template<size_t N>
    fstring<SIZE>& operator =(const fstring<N>& str)
    {
        size_ = 0;
        copy(str.c_str(), maxlen());
    }

    template<size_t N>
    void operator +=(fstring<N>& str)
    {
        copy(str.c_str(), maxlen());
    }

    void operator +=(const CHAR* str)
    {
        copy(str, maxlen());
    }

    CHAR& operator [](size_t n)
    {
        sizeDirty_ = true;
        return buf_[n];
    }

    inline const CHAR operator [](size_t n) const
    {
        return buf_[n];
    }

    template<size_t N>
    inline fstring<SIZE>&& operator +(const fstring<N>& rhs) const
    {
        fstring<SIZE> ret;
        ret.copy(c_str(), maxlen());
        ret.copy(rhs.c_str(), maxlen());

        return std::move(ret);
    }

    inline bool operator==(const CHAR * s) const
    {
        // Cannot mutate the size -- so we're just going to do an unsafe compare
        // as our buffer will always be NUL-terminated.
        return strcmp(c_str(), s) == 0;
    }

    inline bool operator==(const std::string& s) const
    {
        return strcmp(c_str(), s.c_str()) == 0;
    }

    template<size_t N>
    inline bool operator==(const fstring<N>& s) const
    {
        return strcmp(c_str(), s.c_str()) == 0;
    }

private:
    size_t size_;
    bool sizeDirty_;
    CHAR buf_[SIZE + 1];

    template<size_t N, typename C>
    friend std::basic_ostream<C>& operator <<(std::basic_ostream<C>& os, const fstring<N, C>& fs);

    void copy(const CHAR* s, size_t maxlen)
    {
        for (; *s && size_ < maxlen; s++, size_++)
        {
            buf_[size_] = *s;
        }

        buf_[size_] = 0;
    }
};

template<size_t SIZE, typename CHAR>
std::basic_ostream<CHAR>& operator <<(std::basic_ostream<CHAR>& os, const fstring<SIZE, CHAR>& fs)
{
    return os << fs.c_str();
}

#endif // FSTRING_HPP
