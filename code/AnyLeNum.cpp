#ifndef dAnyLeNumCpp
#define dAnyLeNumCpp
//headers
#include "AnyLeNum.hpp"
//-//external
#include "fmt/format.h"
//-//standard
#include <cstdlib>
#include <string_view>
#include <functional>
//-//-//template-library
#include <unordered_map>
//content
namespace nAnyLeNum
{
}
#if defined(dAnyLeNumMakeExe)
auto vCmdTab = std::unordered_map<std::string_view, std::function<bool(void)>>{
	{"tHello",
	 []()
	 {
		 fmt::println("HelloWorld");
		 return 1;
	 }},
};
int main(int vArgC, char **vArgV)
{
	if(vArgC > 1)
	{
		auto pCmdFun = vCmdTab.find(vArgV[1]);
		auto pCmdEnd = vCmdTab.end();
		if(pCmdFun == pCmdEnd)
		{
			return EXIT_FAILURE;
		}
		else
		{
			return pCmdFun->second() ? EXIT_SUCCESS : EXIT_FAILURE;
		}
	}
	else
	{
		return EXIT_FAILURE;
	}
}
#endif//ifd(dAnyLeNumMakeExe)
//actions
#endif//dAnyLeNumCpp
