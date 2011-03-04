#include <string>
#include <typeinfo>
#include <type_traits>

#include "cppa/util.hpp"
#include "cppa/test.hpp"
#include "cppa/uniform_type_info.hpp"

using std::cout;
using std::endl;
using std::is_same;

using namespace cppa::util;

template <typename T, template <typename> class What>
struct apply
{
	typedef typename What<T>::type type;
};

void test__type_list()
{

	CPPA_TEST(test__type_list);

	typedef apply<const int&, remove_const_reference>::type int_typedef;

	CPPA_CHECK((is_same<int, int_typedef>::value));

	typedef type_list<int, float, std::string> l1;
	typedef reverse_type_list<l1>::type r1;

	CPPA_CHECK((is_same<int, type_at<0, l1>::type>::value));
	CPPA_CHECK((is_same<float, type_at<1, l1>::type>::value));
	CPPA_CHECK((is_same<std::string, type_at<2, l1>::type>::value));

	CPPA_CHECK_EQUAL(l1::type_list_size, 3);
	CPPA_CHECK_EQUAL(l1::type_list_size, r1::type_list_size);
	CPPA_CHECK((is_same<type_at<0, l1>::type, type_at<2, r1>::type>::value));
	CPPA_CHECK((is_same<type_at<1, l1>::type, type_at<1, r1>::type>::value));
	CPPA_CHECK((is_same<type_at<2, l1>::type, type_at<0, r1>::type>::value));

	typedef concat_type_lists<type_list<int>, l1>::type l2;

	CPPA_CHECK((is_same<int, l2::head_type>::value));
	CPPA_CHECK((is_same<l1, l2::tail_type>::value));

}
