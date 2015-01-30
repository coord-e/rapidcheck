#include "rapidcheck/detail/Any.h"

namespace rc {
namespace detail {

Any::Any() {}

Any::Any(const Any &other)
    : m_impl(other.m_impl
             ? other.m_impl->copy()
             : nullptr) {}

Any::Any(Any &&other)
    : m_impl(other.m_impl.release()) {}

Any &Any::operator=(const Any &rhs)
{
    if (rhs.m_impl)
        m_impl = rhs.m_impl->copy();
    else
        m_impl.reset();
    return *this;
}

Any &Any::operator=(Any &&rhs)
{
    m_impl.reset(rhs.m_impl.release());
    return *this;
}

void Any::reset() { m_impl.reset(); }

ValueDescription Any::describe() const
{
    assert(m_impl);
    return m_impl ? m_impl->describe() : ValueDescription();
}

Any::operator bool() const { return static_cast<bool>(m_impl); }

bool Any::isCopyable() const { return !m_impl || m_impl->isCopyable(); }

bool operator==(const Any &a1, const Any &a2)
{
    if (!a1.m_impl && !a2.m_impl)
        return true;

    if (!a1.m_impl || !a2.m_impl)
        return false;

    return a1.m_impl->equals(*a2.m_impl);
}

bool operator!=(const Any &a1, const Any &a2)
{
    return !(a1 == a2);
}

} // namespace detail
} // namespace rc
