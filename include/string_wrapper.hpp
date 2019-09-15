
#pragma once

namespace MonoBind
{
    class StringWrapper
    {
    public:
        StringWrapper(MonoString* mstr)
            : m_mstr(mstr)
        {}

        StringWrapper(std::string const& str)
            : m_mstr(mono_string_new_len(mono_domain_get(), str.data(), str.size()))
        {}

        StringWrapper(const char* str)
            : m_mstr(mono_string_new(mono_domain_get(), str))
        {}

        std::string toString()
        {
            auto cStr = mono_string_to_utf8(m_mstr);
            std::string str(cStr);
            mono_free(cStr);
            return str;
        }
    private:
        MonoString* m_mstr;
    };
}