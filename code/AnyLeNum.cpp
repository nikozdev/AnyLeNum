#ifndef dAnyLeNum_Cpp
#define dAnyLeNum_Cpp
//headers
#include "AnyLeNum.hpp"
//-//external
#include "fmt/format.h"
//-//standard
#include <cstdlib>
//content
namespace nAnyLeNum
{
}
#if defined(dAnyLeNum_MakeTexe)
//headers
#include <string_view>
#include <functional>
#include <iostream>
#include <unordered_map>
//typedef
using tTestOut = int;
using tTestKey = std::string_view;
using tTestFun = std::function<tTestOut(void)>;
using tTestTab = std::unordered_map<tTestKey, tTestFun>;
using tTestRef = tTestTab::iterator;
//datadef
extern tTestTab vTestTab;
//actions
int main(int vArgC, char **vArgV)
{
	if(vArgC == 3 && std::string_view(vArgV[1]) == "test")
	{
		tTestKey vTestKey = vArgV[2];
		tTestRef vTestRef = vTestTab.find(vTestKey);
		tTestRef vTestEnd = vTestTab.end();
		if(vTestRef == vTestEnd)
		{
			fmt::println(stderr, "test was not found ! {}", vTestKey);
			return EXIT_FAILURE;
		}
		else
		{
			fmt::println(stderr, "{}=", vTestKey);
			tTestOut vTestOut = vTestRef->second();
			fmt::println(stderr, "={}", vTestKey);
			return vTestOut;
		}
	}
	else
	{
		std::copy(
			vArgV, vArgV + vArgC, std::ostream_iterator<char *>(std::cout, "\n")
		);
	}
	return EXIT_SUCCESS;
}//main
tTestTab vTestTab = {
	{"HelloWorld",
	 []()
	 {
		 fmt::println(stdout, "HelloWorld");
		 return 1;
	 }},
};		//vTestTab
#endif//ifd(dAnyLeNum_MakeTexe)
//actions
#endif//dAnyLeNum_Cpp
