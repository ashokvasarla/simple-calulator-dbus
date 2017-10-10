/*
 * CalculatorNSMConsumer.h
 *
 *  Created on: Jul 14, 2016
 *      Author: visteon
 */

#ifndef CALCULATORNSMCONSUMER_H_
#define CALCULATORNSMCONSUMER_H_

/* System header files                                                                          */
#include <gio/gio.h>                    /* Use glib to access dbus and communicate to NSM       */

#include "NodeStateTypes.h"
#include "generated/NodeStateConsumer.h"          /* Consumer interface with publicly available functions */
#include "generated/NodeStateLifecycleConsumer.h" /* Consumer interface to offer life cycle clients       */

class CalculatorNSMConsumer {
public:
	CalculatorNSMConsumer();
	virtual ~CalculatorNSMConsumer();
	gboolean createDBusConnection();
	gboolean createConsumerProxy();
	gboolean createLifecycleStub();
	gboolean getNodeState();
	gboolean registerShutdownClient();
private:
	GDBusConnection *dbusConnection = NULL;	
	const gchar *dBusName           = NULL;
	NodeStateConsumer *nodeStateConsumer = NULL;
	NodeStateLifeCycleConsumer *pLifeCycleConsumer = NULL;

};

#endif /* CALCULATORNSMCONSUMER_H_ */
