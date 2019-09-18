
#pragma once

namespace MonoBind
{
    class StringWrapper
    {
    public:
        inline StringWrapper();
        inline StringWrapper(MonoString* mstr);
        inline StringWrapper(std::string const& str);
        inline StringWrapper(const char* str);

        inline std::string toString();
    private:
        MonoString* m_mstr;
    };

}