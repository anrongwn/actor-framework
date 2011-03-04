#ifndef COMPARE_TUPLES_HPP
#define COMPARE_TUPLES_HPP

#include "cppa/get.hpp"
#include "cppa/util/type_list.hpp"
#include "cppa/util/is_comparable.hpp"
#include "cppa/util/eval_type_lists.hpp"

namespace cppa { namespace detail {

template<std::size_t N, template<typename...> class Tuple, typename... Types>
const typename util::type_at<N, util::type_list<Types...>>::type&
do_get(const Tuple<Types...>& t)
{
	return ::cppa::get<N, Types...>(t);
}

template<std::size_t N, typename LhsTuple, typename RhsTuple>
struct cmp_helper
{
	inline static bool cmp(const LhsTuple& lhs, const RhsTuple& rhs)
	{
		return    do_get<N>(lhs) == do_get<N>(rhs)
			   && cmp_helper<N-1, LhsTuple, RhsTuple>::cmp(lhs, rhs);
	}
};

template<typename LhsTuple, typename RhsTuple>
struct cmp_helper<0, LhsTuple, RhsTuple>
{
	inline static bool cmp(const LhsTuple& lhs, const RhsTuple& rhs)
	{
		return do_get<0>(lhs) == do_get<0>(rhs);
	}
};

} } // namespace cppa::detail

namespace cppa { namespace util {

template<template<typename...> class LhsTuple, typename... LhsTypes,
		 template<typename...> class RhsTuple, typename... RhsTypes>
bool compare_tuples(const LhsTuple<LhsTypes...>& lhs,
					const RhsTuple<RhsTypes...>& rhs)
{
	static_assert(   LhsTuple<LhsTypes...>::type_list_size
				  == RhsTuple<RhsTypes...>::type_list_size,
				  "could not compare tuples of different size");
	static_assert(util::eval_type_lists<util::type_list<LhsTypes...>,
										util::type_list<RhsTypes...>,
										util::is_comparable>::value,
				  "types of lhs are not comparable to the types of rhs");
	return detail::cmp_helper<(LhsTuple<LhsTypes...>::type_list_size - 1),
							  LhsTuple<LhsTypes...>,
							  RhsTuple<RhsTypes...>>::cmp(lhs, rhs);
}

} } // namespace cppa::util

#endif // COMPARE_TUPLES_HPP
