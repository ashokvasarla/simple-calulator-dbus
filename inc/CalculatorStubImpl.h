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

File Name        :  CalculatorStubImpl.h
Module Short Name:  CalculatorStubImpl header
Description      :  Implements CalculatorStubImpl class

******************************************************************************/
#ifndef CALCULATORSTUBIMPL_H_
#define CALCULATORSTUBIMPL_H_

// Includes
#include "CalculatorStubDefault.hpp"
#include "CommonAPI/CommonAPI.hpp"
#include <v1/SimpleCalculator/CalculatorInterface/CalculatorStub.hpp>

using namespace v1::SimpleCalculator::CalculatorInterface;

// Class declaration
class CalculatorStubImpl: public v1_0::SimpleCalculator::CalculatorInterface::CalculatorStubDefault
{
public:
	//Constructor
	CalculatorStubImpl();

	//Destructor
	virtual ~CalculatorStubImpl();

	//Methods
	void add(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _param1, uint32_t _param2, addReply_t _reply);
	void division(const std::shared_ptr<CommonAPI::ClientId> _client, float _a, float _b, divisionReply_t _reply);
  void Test1(const std::shared_ptr<CommonAPI::ClientId> _client, uint8_t _param, Test1Reply_t _reply);
  void Test2(const std::shared_ptr<CommonAPI::ClientId> _client, uint16_t _param, Test2Reply_t _reply);
  void Test3(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _param, Test3Reply_t _reply);
  void Test4(const std::shared_ptr<CommonAPI::ClientId> _client, uint64_t _param, Test4Reply_t _reply);
  void Test5(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, Test5Reply_t _reply);
  void Test6(const std::shared_ptr<CommonAPI::ClientId> _client, Calculator::MetadataElement _param, Test6Reply_t _reply);
  void Test7(const std::shared_ptr<CommonAPI::ClientId> _client, Calculator::MetadataElementList _param, Test7Reply_t _reply);
  void Test8(const std::shared_ptr<CommonAPI::ClientId> _client, Calculator::MyArray01 _param, Test8Reply_t _reply);
  void Test9(const std::shared_ptr<CommonAPI::ClientId> _client, Calculator::MyArray02 _param, Test9Reply_t _reply);
  void Test10(const std::shared_ptr<CommonAPI::ClientId> _client, Calculator::MyArray03 _param, Test10Reply_t _reply);
  void Test11(const std::shared_ptr<CommonAPI::ClientId> _client, Calculator::MyArray04 _param, Test11Reply_t _reply);
  void Test12(const std::shared_ptr<CommonAPI::ClientId> _client, CommonAPI::ByteBuffer _name, Test12Reply_t _reply);
};

#endif /* CALCULATORSTUBIMPL_H_ */
