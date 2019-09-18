#pragma once

namespace MonoBind
{
    Type::Type(MonoType *type)
            :m_type(type)
    {}

    MonoType *Type::raw()
    {
        return m_type;
    }

    std::string Type::fullName()
    {
        return mono_type_full_name(m_type);
    }

    std::string Type::name()
    {
        return mono_type_get_name(m_type);
    }

    MonoTypeEnum Type::getType()
    {
        return static_cast<MonoTypeEnum>(mono_type_get_type(m_type));
    }

    bool Type::operator==(const std::string &name)
    {
        return name == this->name();
    }

    bool Type::operator==(MonoTypeEnum type)
    {
        return type == getType();
    }
}