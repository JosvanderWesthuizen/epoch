#ifndef EP_TEST_SUITE_H_
#define EP_TEST_SUITE_H_

#include "core/ehm/ehm.h"

// epoch test
// epoch/src/test/test.h

#include "core/types/EPObj.h"

#include "test/EPTest.h"

#include <map>

#define EP_TESTS_START RESULT AddTests() override {				\
	RESULT r = R::OK;												

#define EP_ADD_TEST(test_name) do {													\
	EPTest<RESULT()> pfnTest = nullptr;												\
	CBM(FindTest(#test_name) == nullptr, "Test " #test_name " already exists");		\
	pfnTest = EPTest<RESULT()>(#test_name, [&]() -> RESULT {							\
		return this->##test_name();													\
	});																				\
	CRM(Add(#test_name, pfnTest), "Failed to add test " #test_name);					\
} while (0);


#define EP_TESTS_END Error:		\
	return r;						\
}		


class EPTestSuiteBase :
	public EPObj
{
protected:
	EPTestSuiteBase() = default;

public:
	virtual ~EPTestSuiteBase() = default;

public:
	RESULT Add(std::string strTestName, EPTest<RESULT()> eptest);
	RESULT Run(std::string strTestName);

	EPTest<RESULT()> FindTest(std::string strTestName);

	RESULT RunAllTests();

protected:
	virtual RESULT AddTests() = 0;

private:
	std::map<std::string, EPTest<RESULT()>> m_tests;
};

template <typename TTestSuite>
class EPTestSuite :
	public EPTestSuiteBase
{


public:
	static TTestSuite *make() {
		RESULT r = R::OK;

		TTestSuite *pTestSuite = new TTestSuite();
		CNR(pTestSuite, R::MEMORY_ALLOCATION_FAILED);

		CRM(pTestSuite->AddTests(), "Adding tests failed");

	Success:
		return pTestSuite;

	Error:
		if (pTestSuite != nullptr) {
			delete pTestSuite;
			pTestSuite = nullptr;
		}

		return pTestSuite;
	}
};

#endif // !EP_TEST_SUITE_H_