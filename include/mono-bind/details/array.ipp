#pragma  once

namespace MonoBind
{
    template<typename T>
    ArrayWrapper<T>::ArrayWrapper()
        : m_array(nullptr)
    {}

    template<typename T>
    ArrayWrapper<T>::ArrayWrapper(const Class &klass, uintptr_t n)
        : m_array(mono_array_new(mono_domain_get(), klass.raw(), n))
    {}

    template<typename T>
    const T *ArrayWrapper<T>::data() const
    {
        return reinterpret_cast<const T*>(mono_array_addr_with_size(m_array, sizeof(T), 0));
    }

    template<typename T>
    T *ArrayWrapper<T>::data()
    {
        return reinterpret_cast<T*>(mono_array_addr_with_size(m_array, sizeof(T), 0));
    }

    template<typename T>
    T &ArrayWrapper<T>::operator[](uintptr_t idx)
    {
        return *(data() + idx);
    }

    template<typename T>
    MonoArray *ArrayWrapper<T>::raw() const
    {
        return m_array;
    }

    template<typename T>
    uintptr_t ArrayWrapper<T>::length() const
    {
        return mono_array_length(m_array);
    }

    template<typename T>
    ArrayWrapper<T>::operator void *()
    {
        return m_array;
    }
}

