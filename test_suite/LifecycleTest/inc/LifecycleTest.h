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

File Name        :  LifecycleTest.h
Module Short Name:  LifecycleTest header
Description      :  Implements CalculatorClient class

******************************************************************************/
#ifndef LIFECYCLETEST_H_
#define LIFECYCLETEST_H_

// Includes
#include "Poco/Util/ServerApplication.h"
#include "generated/NodeStateLifecycleControl.h"          /* Control  interface with safety relevant functions    */

// Class declaration
class LifecycleTest : public Poco::Util::ServerApplication
{
public:
	//Methods
	LifecycleTest();
	virtual ~LifecycleTest();
	int main(__attribute__((unused)) const std::vector<std::string>& args);
	gboolean createDBusConnection();
	gboolean createLifecycleProxy();
	gboolean SetNodeState(gboolean NewState);
	gboolean RestartNode();

private:
	GDBusConnection *dbusConnection 		= NULL;
	const gchar *dBusName           		= NULL;
	NodeStateLifecycleControl *nsLifecycle 	= NULL;
};

#endif /* LIFECYCLETEST_H_ */
