#ifndef LIBCPPA_UTIL_TYPE_LIST_HPP
#define LIBCPPA_UTIL_TYPE_LIST_HPP

#include "cppa/any_type.hpp"
#include "cppa/uniform_type_info.hpp"

#include "cppa/util/void_type.hpp"
#include "cppa/util/abstract_type_list.hpp"

namespace cppa { namespace util {

template<typename... Types> struct type_list;

template<>
struct type_list<>
{
	typedef void_type head_type;
	typedef type_list<> tail_type;
	static const std::size_t type_list_size = 0;
};

template<typename Head, typename... Tail>
struct type_list<Head, Tail...> : abstract_type_list
{

	typedef Head head_type;

	typedef type_list<Tail...> tail_type;

	static const std::size_t type_list_size = tail_type::type_list_size + 1;

	type_list() { init<type_list>(m_arr); }

	virtual const_iterator begin() const
	{
		return m_arr;
	}

	virtual const_iterator end() const
	{
		return m_arr + type_list_size;
	}

	const utype& operator[](std::size_t pos) const
	{
		return *m_arr[pos];
	}

	virtual const utype& at(std::size_t pos) const
	{
		return *m_arr[pos];
	}

	virtual type_list* copy() const
	{
		return new type_list;
	}

	template<typename TypeList>
	static void init(const utype** what)
	{
		what[0] = &uniform_type_info<typename TypeList::head_type>();
		if (TypeList::type_list_size > 1)
		{
			++what;
			init<typename TypeList::tail_type>(what);
		}
	}

 private:

	const utype* m_arr[type_list_size];

};

} } // namespace cppa::util

#endif // LIBCPPA_UTIL_TYPE_LIST_HPP
