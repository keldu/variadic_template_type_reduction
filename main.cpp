#include "./matching.h"

#include <string_view>

struct Foo {
	static constexpr std::string_view name = "Foo";
};

struct Bar {
	static constexpr std::string_view name = "Bar";
};

struct Baz {
	static constexpr std::string_view name = "Baz";
};

struct Banana {
	static constexpr std::string_view name = "Banana";
};

int main(){
	using duplicate_list = list<base<Foo,3>, base<Banana, 2>, base<Bar, 2>, base<Baz,5>, base<Foo,4>, base<Baz, -1>, base<Banana,-2>>;

	using reduced_list = typename duplicate_list::reduced_type;
	
	std::cout<<"Duplicate List"<<std::endl;

	duplicate_list::print();

	std::cout<<"\nReduced List"<<std::endl;
	
	reduced_list::print();

	return 0;
}
