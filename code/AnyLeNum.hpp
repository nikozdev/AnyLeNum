#ifndef dAnyLeNum_Hpp
#define dAnyLeNum_Hpp
//headers
#include <limits>
#include <numeric>
//content
namespace nNikoZDev
{
namespace nAnyLeNum
{
class tGrowingStandard
{
public://typedef

	using tNumElem = uint8_t;
  using tStrElem = char8_t;
	using tNumData = tNumElem *;
  using tStrData = tStrElem *;

	using tAnySize = size_t;

	using tStrSign = char8_t;
	using tNumSign = uint8_t;

public://codetor

	tGrowingStandard(tStrData vStrData): vData{vData}, vSize(std::strlen(vData) - 1)
	{
		//obfuscation for shortification ?
		if((this->vSize <= 1) ? 1 : (this->fVetSign(this->vData[0]) == 0))
		{
			this->vData = "+0";
			this->vSize = 1;
		}
		for(tIter vIter = 0; vIter < this->vSize; vIter++)
		{
			tElem vElem = this->fGetElem(vIter);
			if(this->fVetElem(vElem) == 0)
			{
				this->vData = "+0";
				this->vSize = 1;
				break;
			}
		}
	}
	~tGrowingStandard();

public://getters

  auto fGetStringSign() -> tSign
  {
    return this->vData[0];
  }
	auto fGetStringElem(tIter vIter) const -> tElem
	{
		return this->vData[(vIter % this->vSize) + 1];
	}
	auto fGetStringData() const
	{
		return vData;
	}//fGetSize
	auto fGetStringSize() const
	{
		return vSize;
	}//fGetSize

public://setters

  auto fSetData(tStrData vData)
  {
    return *this;
  }

public://vetters

	static bool fVetStrElemDec(tStrElem vStrElem)
	{
		return (vStrElem >= '0' && vStrElem <= '9');
	}
	static bool fVetStrElemHex(tStrElem vStrElem)
	{
		return (vStrElem >= 'a' && vStrElem <= 'f') || (vStrElem >= 'A' && vStrElem <= 'F');
	}
	static bool fVetStrElemNum(tStrElem vStrElem)
	{
    return fVetStrElemDec(vStrElem) || fVetStrElemHex(vStrElem);
	}
	static bool fVetStrSign(tStrSign vStrSign)
	{
		return vStrSign == '-' || vStrSign == '+';
	}

public://actions

public://datadef

	tStrData vStrData;
	tAnySize vAnySize;

	tNumSign vNumSign;

};//tGrowingStandard
class tGrowingUnsigned
{
};//tGrowingUnsigned
class tGrowingFloating
{
};//tGrowingFloating
}//namespace nAnyLeNum
}//namespace nNikoZDev
#endif//dAnyLeNum_Hpp
