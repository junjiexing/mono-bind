
#include "array.hpp"

namespace MonoBind
{
    template<typename T>
    Array<T>::Array()
        : m_array(nullptr)
    {}

    template<typename T>
    Array<T>::Array(const Class &klass, uintptr_t n)
        : m_array(mono_array_new(mono_domain_get(), klass.raw(), n))
    {}

    template<typename T>
    const T *Array<T>::data() const
    {
        return reinterpret_cast<const T*>(mono_array_addr_with_size(m_array, sizeof(T), 0));
    }

    template<typename T>
    T *Array<T>::data()
    {
        return reinterpret_cast<T*>(mono_array_addr_with_size(m_array, sizeof(T), 0));
    }

    template<typename T>
    T &Array<T>::operator[](uintptr_t idx)
    {
        return *(data() + idx);
    }

    template<typename T>
    MonoArray *Array<T>::raw() const
    {
        return m_array;
    }

    template<typename T>
    uintptr_t Array<T>::length() const
    {
        return mono_array_length(m_array);
    }

    template<typename T>
    Array<T>::operator void *()
    {
        return m_array;
    }
}

