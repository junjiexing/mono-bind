#pragma once

namespace MonoBind
{
    class Class;

    template<typename T>
    class ArrayWrapper
    {
    public:
        ArrayWrapper();
        ArrayWrapper(const Class& klass, uintptr_t n);

        MonoArray* raw() const;

        uintptr_t length() const;

        const T* data() const;
        T* data();

        T& operator[](uintptr_t idx);

        explicit operator void *();

    private:
        MonoArray* m_array;
    };


}