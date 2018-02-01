/*****************************************************************************
*                                                                            *
*              CONFIDENTIAL VISTEON CORPORATION                              *
*                                                                            *
* This is an unpublished work of authorship, which contains trade            *
* secrets, created in 2010. Visteon Corporation owns all rights to           *
* this work and intends to maintain it in confidence to preserve             *
* its trade secret status. Visteon Corporation reserves the right,           *
* under the copyright laws of the United States or those of any              *
* other country that may have jurisdiction, to protect this work             *
* as an unpublished work, in the event of an inadvertent or                  *
* deliberate unauthorized publication. Visteon Corporation also              *
* reserves its rights under all copyright laws to protect this               *
* work as a published work, when appropriate. Those having access            *
* to this work may not copy it, use it, modify it or disclose the            *
* information contained in it without the written authorization              *
* of Visteon Corporation.                                                    *
*                                                                            *
******************************************************************************/

/*****************************************************************************

File Name        :  CalculatorClient.h
Module Short Name:  CalculatorClient header
Description      :  Implements CalculatorClient class

******************************************************************************/
#ifndef CALCULATORCLIENT_H_
#define CALCULATORCLIENT_H_

// Includes
#include "Poco/Util/ServerApplication.h"
#include "CommonAPI/CommonAPI.hpp"
#include "CalculatorProxy.hpp"

using namespace v1_0::SimpleCalculator::CalculatorInterface;

// Class declaration
class CalculatorClient : public Poco::Util::ServerApplication
{
public:
	//Methods
	CalculatorClient();
	virtual ~CalculatorClient();
	int main(__attribute__((unused)) const std::vector<std::string>& args);
private:
  std::shared_ptr <CalculatorProxy<>> calculatorClntProxy;
  struct timeval start, end;
  double t1, t2, diff, Avg, min, max;
  CommonAPI::CallStatus   callStatus;
  uint32_t  result = 0;

  void TestByteBufferPerf(int loop);
  void TestUint64Perf(int loop);
  void TestUint32Perf(int loop);
  void TestUint16Perf(int loop);
  void TestUint8Perf(int loop);
  void EstablishConnection();
  void Subscriptions();
  void Test01();
  void Test02();
  void Test03();
  void Test04();
  void Test05();
  void Test06(int loop);
  void TestStringPerf(int loop);
};


#endif /* CALCULATOCALCULATORCLIENT_H_ */
