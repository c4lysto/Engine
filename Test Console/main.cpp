#include <windows.h>
#include <iostream>
using namespace std;

#include <tchar.h>

#include <thread>
#include <list>

#include "Utilities\Timer.h"
#include "Math Lib\MathLib.h"
#include "Utilities\ThreadPool.h"
//#include "Utilities\SmartPointer.h"
#include "Utilities\Function.h"
#include "Utilities\HashString.h"
#include "Utilities/Mutex.h"
#include "Utilities/Event.h"
#include <mutex>
//#include "../Utilities/DebugHelp.h"

#include <DirectXMath.h>
#include <bitset>

using namespace recon;

#define TEST_SETS 1
#define TEST_REPS 1000000000

int TestThisBitch(int& nVal)
{
	//cout << "Val: " << nVal << endl;
	cout << "TestThisBitch() Called!" << endl;
	return -1;
}

struct TstThreadArgs
{
	int operation[256];
	char vals1[256];
	char vals2[256];

	TstThreadArgs()
	{
		for(int i = 0; i < 256; ++i)
		{
			operation[i] = rand() & 3;
			vals1[i] = (rand() & 15) + 1;
			vals2[i] = (rand() & 15) + 1;
		}
	}

	TstThreadArgs(const TstThreadArgs& rhs)
	{
		for(int i = 0; i < 256; ++i)
		{
			operation[i] = rand() & 3;
			vals1[i] = (rand() & 15) + 1;
			vals2[i] = (rand() & 15) + 1;
		}
	}

	int __cdecl TstMethod(int& nVal)
	{
		//cout << "Val: " << nVal << endl;
		cout << "TstMethod() Called!" << endl;
		nVal = -1;

		return -1;
	}

	int __cdecl TstMethodConst(int& nVal) const
	{
		//cout << "Val: " << nVal << endl;
		cout << "TstMethodConst() Called!" << endl;
		nVal = -1;

		return -1;
	}

	virtual void TstVirtual()
	{
		cout << "TstThreadArgs::TstVirtual()" << endl;
	}
};

struct TstDerivedClass : public TstThreadArgs
{
	virtual void TstVirtual()
	{
		cout << "TstDerivedClass::TstVirtual()" << endl;
	}
};

void TstThreadProc(void* pArgs);
float TstGlobal()
{
	cout << "TstGlobal() called !" << endl;
	return PI;
}

typedef float (TstThreadArgs::*tstFunc)(void);

void CallFuncPtr(Function<int(int&)> funcPtr)
{
	int val;
	funcPtr(val);
}

void IntelMatInverse(float* src)
{
	__m128 minor0, minor1, minor2, minor3;
	__m128 row0, row1, row2, row3;
	__m128 det, tmp1;

	tmp1 = _mm_setzero_ps();
	row1 = _mm_setzero_ps();
	row3 = _mm_setzero_ps();

	tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src)), (__m64*)(src + 4));
	row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src + 8)), (__m64*)(src + 12));
	row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
	row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);
	tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src + 2)), (__m64*)(src + 6));
	row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src + 10)), (__m64*)(src + 14));
	row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
	row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);
	// -----------------------------------------------
	tmp1 = _mm_mul_ps(row2, row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor0 = _mm_mul_ps(row1, tmp1);
	minor1 = _mm_mul_ps(row0, tmp1);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
	minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
	minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);
	// -----------------------------------------------
	tmp1 = _mm_mul_ps(row1, row2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
	minor3 = _mm_mul_ps(row0, tmp1);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
	minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
	minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);
	// -----------------------------------------------
	tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	row2 = _mm_shuffle_ps(row2, row2, 0x4E);
	minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
	minor2 = _mm_mul_ps(row0, tmp1);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
	minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
	minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);
	// -----------------------------------------------
	tmp1 = _mm_mul_ps(row0, row1);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
	minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));
	// -----------------------------------------------
	tmp1 = _mm_mul_ps(row0, row3);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
	minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
	minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));
	// -----------------------------------------------
	tmp1 = _mm_mul_ps(row0, row2);
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
	minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));
	tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
	minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);
	// -----------------------------------------------
	det = _mm_mul_ps(row0, minor0);
	det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
	det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
	tmp1 = _mm_rcp_ss(det);
	det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
	det = _mm_shuffle_ps(det, det, 0x00);
	minor0 = _mm_mul_ps(det, minor0);
	_mm_storel_pi((__m64*)(src), minor0);
	_mm_storeh_pi((__m64*)(src + 2), minor0);
	minor1 = _mm_mul_ps(det, minor1);
	_mm_storel_pi((__m64*)(src + 4), minor1);
	_mm_storeh_pi((__m64*)(src + 6), minor1);
	minor2 = _mm_mul_ps(det, minor2);
	_mm_storel_pi((__m64*)(src + 8), minor2);
	_mm_storeh_pi((__m64*)(src + 10), minor2);
	minor3 = _mm_mul_ps(det, minor3);
	_mm_storel_pi((__m64*)(src + 12), minor3);
	_mm_storeh_pi((__m64*)(src + 14), minor3);
}

class ScalarTstV
{
private:
	Vector row;

public:
	__forceinline explicit ScalarTstV(Vector vec) : row(vec){}

	__forceinline explicit ScalarTstV(eOneInitializer)
	{
		row = VectorSetConstant<(u32)FloatToIntRep::One, (u32)FloatToIntRep::One, (u32)FloatToIntRep::One, (u32)FloatToIntRep::One>();
	}

	__forceinline explicit ScalarTstV(eFiveInitializer)
	{
		row = VectorSetConstant<(u32)FloatToIntRep::Five, (u32)FloatToIntRep::Five, (u32)FloatToIntRep::Five, (u32)FloatToIntRep::Five>();
	}

	void operator=(ScalarTstV rhs)
	{
		row = rhs.row;
	}

	ScalarTstV operator*(ScalarTstV rhs)
	{
		return ScalarTstV(_mm_mul_ps(row, rhs.row));
	}
};

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);

	TstThreadArgs* pTstArgs = new TstThreadArgs;
	TstThreadArgs localTstArgs;

	ThreadPool tstThreadPool;//s[10];
	tstThreadPool.Init(100);

	//CallFuncPtr(TestThisBitch);

	int tstVal = 250;
	const TstThreadArgs* pConstTstArgs = pTstArgs;


	/*Vec2V five(5.0f), ten(I_ONE);
	Vec2V fifty = five * ten;*/

	//Vector myVec = VectorExp2(VectorSet(TWO_PI));
	//DirectX::XMVECTOR dxVec = DirectX::XMVectorExp2(DirectX::XMVectorSet(TWO_PI, TWO_PI, TWO_PI, TWO_PI));

	//std::function<int(int)> memFunc;

	//std::function<int(int&)> memFunc;

	//memFunc = std::bind(&TstThreadArgs::TstMethod, pTstArgs, std::placeholders::_1);
	//FunctionPointer<int, int&> memFunc;
	//memFunc = CreateFunctionPointer(pConstTstArgs, &TstThreadArgs::TstMethod);
	//pTstArgs = nullptr;
	//memFunc(tstVal);

	s8 tstA = 50, tstB = -100;
	s8 tstABResult = Abs(tstA);
	tstABResult = Abs(tstB);
	//Function<int(int&)> myMemFunc = &TstThreadArgs::TstMethod;

	int(*nullFuncPtr)(int&) = nullptr;

	std::function<int(int&)> globalFunc = [&](int passedVal) -> int {std::cout << "TstVal: " << tstVal << std::endl << "Passed Val: " << passedVal << std::endl; return passedVal; };

	//StaticFunctionPointer<int, int&> globalFunc = TestThisBitch;
	//memFunc = globalFunc;
	//memFunc(250);
	int tstVal2 = 50;
	globalFunc(tstVal2);

	globalFunc = &::TestThisBitch;
	globalFunc(tstVal2);

	globalFunc = [&](int& passedVal) -> int {std::cout << "TstVal: " << tstVal << std::endl << "Passed Val: " << passedVal << std::endl; return passedVal; };
	globalFunc(tstVal2);

	globalFunc = [](int& passedVal) -> int {std::cout << /*"TstVal: " << tstVal << std::endl << */"Passed Val: " << passedVal << std::endl; return passedVal; };
	globalFunc(tstVal2);

	globalFunc = [=](int& passedVal) -> int {std::cout << "TstVal: " << tstVal << std::endl << "Passed Val: " << passedVal << std::endl; return passedVal; };
	globalFunc(tstVal2);

	//globalFunc = nullFuncPtr;
	//globalFunc(tstVal2);

	system("cls");


	Function<int(int&)> myGlobalFunc = [&](int& passedVal) -> int {std::cout << "TstVal: " << tstVal << std::endl << "Passed Val: " << passedVal << std::endl; return passedVal; };
	myGlobalFunc(tstVal2);

	myGlobalFunc = &::TestThisBitch;
	myGlobalFunc(tstVal2);

	myGlobalFunc = std::move(Function<int(int&)>([&](int& passedVal) -> int {std::cout << "Move Tested" << std::endl; return passedVal; }));
	myGlobalFunc(tstVal2);

	myGlobalFunc = [&](int& passedVal) -> int {std::cout << "TstVal: " << tstVal << std::endl << "Passed Val: " << passedVal << std::endl; return passedVal; };
	myGlobalFunc(tstVal2);

	myGlobalFunc = [](int& passedVal) -> int {std::cout << /*"TstVal: " << tstVal << std::endl << */"Passed Val: " << passedVal << std::endl; return passedVal; };
	myGlobalFunc(tstVal2);

	myGlobalFunc = [=](int& passedVal) -> int {std::cout << "TstVal: " << tstVal << std::endl << "Passed Val: " << passedVal << std::endl; return passedVal; };
	myGlobalFunc(tstVal2);

	Function<int(int&)> myMemFunc = Function<int(int&)>(localTstArgs, &TstThreadArgs::TstMethod);
	//pTstArgs = nullptr;
	myMemFunc(tstVal2);

	myGlobalFunc = myMemFunc;
	myGlobalFunc(tstVal2);

	StaticFunction<int(int&)> staticFunc(TestThisBitch);
	staticFunc(tstVal2);

	staticFunc = [](int& passedVal) -> int {std::cout << /*"TstVal: " << tstVal << std::endl <<*/ "Passed Val: " << passedVal << std::endl; return passedVal; };
	staticFunc(tstVal2);

	myGlobalFunc = staticFunc;
	myGlobalFunc(tstVal2);

	myGlobalFunc = nullFuncPtr;
	if(myGlobalFunc)
	{
		myGlobalFunc(tstVal2);
	}

	myGlobalFunc = nullptr;
	if(myGlobalFunc)
	{
		myGlobalFunc(tstVal2);
	}

	MemberFunction<TstThreadArgs, int(int&)> memberFunc(pTstArgs, &TstThreadArgs::TstMethod);
	memberFunc(tstVal2);

	memberFunc = nullptr;

	memberFunc = MemberFunction<TstThreadArgs, int(int&)>(pConstTstArgs, &TstThreadArgs::TstMethodConst);
	memberFunc(tstVal2);

	memberFunc.SetInvokingObject(pTstArgs);
	memberFunc(tstVal2);

	memberFunc = MemberFunction<TstThreadArgs, int(int&)>(pTstArgs, &TstThreadArgs::TstMethodConst);
	memberFunc(tstVal2);

	memberFunc = nullptr;

	if(memberFunc)
	{
		memberFunc(tstVal2);
	}

	myGlobalFunc = Function<int(int&)>(memberFunc);

	if(myGlobalFunc)
		myGlobalFunc(tstVal2);


	//StaticFunctionPointer<int, int&> tmp = TestThisBitch;
	//tmp(tstVal);

	//(pTstArgs->*memFunc)(tstVal);

	//std::function<float(void)> pStdFunc;
	//pStdFunc = std::bind(TstGlobal);
	//pStdFunc();

	//TstThreadArgs* pVirtualTst = new TstDerivedClass;
	//pVirtualTst->TstVirtual();
	//delete pVirtualTst;

	for(int i = 0; i < 20; ++i)
	{
		Sleep(rand() % 1000);
		for(int j = 0; j < 400; ++j)
		{
			tstThreadPool.AddWork(TstThreadProc, pTstArgs);
		}
	}

	/*Mat44V convertTst(INIT_IDENTITY);
	Mat44 convTst1;
	convTst1 = MAT44V_TO_MAT44(convertTst);

int TstThreadProc(void* pArgs)
{
	TstThreadArgs* pThreadArgs = (TstThreadArgs*)pArgs;

	Vec3V vectst(2, 4, 6, 8);
	Vec3V vectst2(2, 4, 6, 8);
	vectst2 *= vectst;

	for(int i = 0; i < 256; ++i)
	{
		switch(pThreadArgs->operation[i])
		{
		case 0:
			{
				finalVal += pThreadArgs->vals1[i] + pThreadArgs->vals2[i];
			}
			break;

		case 1:
			{
				finalVal += pThreadArgs->vals1[i] - pThreadArgs->vals2[i];
			}
			break;
		
		case 2:
			{
				finalVal += pThreadArgs->vals1[i] * pThreadArgs->vals2[i];
			}
			break;

		case 3:
			{
				finalVal += pThreadArgs->vals1[i] / pThreadArgs->vals2[i];
			}
			break;
		}
	}

	cout << "Final Val: " << finalVal << endl;
	return 0;
}

	cout << vectst2.GetX() << ' ' << vectst2.GetY() << ' ' << vectst2.GetZ() << ' ' << vectst2.GetW() << endl;*/

	tstThreadPool.Shutdown();
	delete pTstArgs;
	std::system("pause");
	return 0;
}

void TstThreadProc(void* pArgs)
{
	/*testMutex.Lock();
	testMutex.Lock();
	std::cout << "I Am Printing Out This Large Message\nabcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ" << std::endl;
	testMutex.Unlock();
	testMutex.Unlock();*/

	/*TstThreadArgs* pTstThreadArgs = (TstThreadArgs*)pArgs;

	unsigned int finalVal = 0;

	for(int i = 0; i < 256; ++i)
	{
	switch(pTstThreadArgs->operation[i])
	{
	case 0:
	{
	finalVal += pTstThreadArgs->vals1[i] + pTstThreadArgs->vals2[i];
	}
	break;

	case 1:
	{
	finalVal += pTstThreadArgs->vals1[i] - pTstThreadArgs->vals2[i];
	}
	break;

	case 2:
	{
	finalVal += pTstThreadArgs->vals1[i] * pTstThreadArgs->vals2[i];
	}
	break;

	case 3:
	{
	finalVal += pTstThreadArgs->vals1[i] / pTstThreadArgs->vals2[i];
	}
	break;
	}

	}

	cout << "Final Val: " << finalVal << endl;*/
}