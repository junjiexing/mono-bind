#pragma once

#include <mono/metadata/object.h>
#include <mono/metadata/appdomain.h>

namespace MonoBind
{
    class Class;

    template<typename T>
    class Array
    {
    public:
        Array();

        Array(const Class& klass, uintptr_t n);
        //TODO: std::initializer_list
        //TODO: support range for

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