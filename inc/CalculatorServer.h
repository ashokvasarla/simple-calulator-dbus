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

File Name        :  CalculatorServer.h
Module Short Name:  CalculatorServer header
Description      :  Implements CalculatorServer class

******************************************************************************/
#ifndef CALCULATORSERVER_H_
#define CALCULATORSERVER_H_

// Includes
#include "Poco/Util/ServerApplication.h"
#include "CalculatorStubImpl.h"

// Class declaration
class CalculatorServer : public Poco::Util::ServerApplication
{
private:
	//Calculator Stub instance
	std::shared_ptr<CalculatorStubImpl> itsCalculatorStub;

public:
	//Methods
	CalculatorServer();
	virtual ~CalculatorServer();
	int main(__attribute__((unused)) const std::vector<std::string>& args);
};


#endif /* CALCULATORSERVER_H_ */
