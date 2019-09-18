#pragma once

namespace MonoBind
{
    StringWrapper::StringWrapper()
        :m_mstr(nullptr)
    {}

    StringWrapper::StringWrapper(MonoString *mstr)
        : m_mstr(mstr)
    {}

    StringWrapper::StringWrapper(std::string const &str)
        : m_mstr(mono_string_new_len(mono_domain_get(), str.data(), str.size()))
    {}

    StringWrapper::StringWrapper(const char *str)
        : m_mstr(mono_string_new(mono_domain_get(), str))
    {}

    std::string StringWrapper::toString()
    {
        auto cStr = mono_string_to_utf8(m_mstr);
        std::string str(cStr);
        mono_free(cStr);
        return str;
    }

}