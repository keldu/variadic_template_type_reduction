#pragma once

#include <cstdint>

#include <type_traits>
#include <iostream>

namespace {
template<typename T, int64_t E>
class base {
};

template<typename... T>
struct list {};

template<typename T0, int64_t E0, typename... TL, int64_t... EL>
struct list<base<T0,E0>, base<TL,EL>...> {

	// static typename std::enable_if<sizeof...(TL) >::type print(){
	static void print(){
		std::cout<<T0::name<<" : "<<E0<<std::endl;

		if constexpr (sizeof...(TL) > 0){
			list<base<TL,EL>...>::print();
		}
	}
};

template<typename... T>
constexpr bool is_always_false = false;

template<typename T, typename U, typename V>
class matching_reduce {
public:
	static_assert(is_always_false<T, U, V>, "Template type not supported");
};

template<typename T, int64_t E, typename T0, int64_t E0, typename... TL, int64_t... EL, typename... TR, int64_t... ER>
class matching_reduce<base<T,E>, list<base<T0,E0>,base<TL,EL>...>, list<base<TR,ER>...>> {
public:
	static constexpr bool is_same = std::is_same_v<T,T0>;

	using match_reduce_type = typename std::conditional<is_same, base<T,E+E0>, base<T,E>>::type;
	using match_reduce_list = typename std::conditional<is_same, list<base<TR,ER>...>, list<base<TR,ER>..., base<T0,E0>>>::type;

	using value_type = typename matching_reduce<match_reduce_type, list<base<TL,EL>...>, match_reduce_list>::value_type;
	using list_type = typename matching_reduce<match_reduce_type, list<base<TL,EL>...>, match_reduce_list>::list_type;

	static constexpr int64_t value_num = matching_reduce<match_reduce_type, list<base<TL,EL>...>, match_reduce_list>::value_num;
};

template<typename T, int64_t E, typename... TR, int64_t... ER>
class matching_reduce<base<T,E>, list<>, list<base<TR,ER>...>> {
public:
	using value_type = base<T,E>;
	using list_type = list<base<TR,ER>...>;

	static constexpr int64_t value_num = E;
};

template<typename T, typename U>
class matching {
	static_assert(is_always_false<T, U>, "Template type not supported");
};

template<typename... T, int64_t... E>
class matching<list<>,list<base<T,E>...>> {
public:
	using type = list<base<T,E>...>;

};

template<typename T0, int64_t E0, typename... TL, int64_t... EL, typename... TR, int64_t... ER>
class matching<list<base<T0,E0>,base<TL,EL>...>, list<base<TR,ER>...>> {
public:
	using reduced_value_type = typename matching_reduce<base<T0,E0>, list<base<TL,EL>...>, list<>>::value_type;
	using reduced_list_type = typename matching_reduce<base<T0,E0>, list<base<TL,EL>...>, list<>>::list_type;

	static constexpr int64_t reduced_value_num = matching_reduce<base<T0,E0>, list<base<TL,EL>...>, list<>>::value_num;
	using reduced_result_list = typename std::conditional<reduced_value_num == 0, list<base<TR,ER>...>, list<base<TR,ER>...,reduced_value_type>>::type;

	using type = typename matching<reduced_list_type, reduced_result_list>::type;
};
}
