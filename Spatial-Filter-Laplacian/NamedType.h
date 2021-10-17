#ifndef NAMEDTYPE_H
#define NAMEDTYPE_H

#include <iostream>
#include <sstream>

namespace dip
{
    template <typename T, typename Parameter>
    class NamedType
    {
    public:
        NamedType(T const& value) : value_(value) {}
        NamedType(T&& value) : value_(std::move(value)) {}
        T& get() { return value_; }
        T const& get() const { return value_; }
    private:
        T value_;
    };

    template <class Container>
    void split(const std::string& str, Container& cont, char delim = ' ')
    {
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, delim)) {
            cont.push_back(token);
        }
    }

    //Href :
    struct UpperBoundaryParameter;

    template <typename T>
    NamedType<T, struct UpperBoundaryParameter> Upper(T val)
    {
        return NamedType<T, struct UpperBoundaryParameter>(val);
    }

    struct LowerBoundaryParameter;
    template <typename T>
    NamedType<T, struct LowerBoundaryParameter> Lower(T val)
    {
        return NamedType<T, struct LowerBoundaryParameter>(val);
    }

    template<typename T ,typename U ,typename V>
    T stayInBoundaries(T val, NamedType<U , UpperBoundaryParameter> upper, NamedType<V , LowerBoundaryParameter> lower)
    {
        //Check upper boundary
        if (val > upper.get())
            return upper.get();

        //Check lower boundary
        if (val < lower.get())
            return lower.get();

        return val;
    }
}


#endif // NAMEDTYPE_H
