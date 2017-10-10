/*
 * LifecycleTest.cpp
 *
 *  Created on: Jul 19, 2016
 *      Author: visteon
 */

#include "LifecycleTest.h"
#include <dlt/dlt.h>
#include <iostream>
#include "NodeStateTypes.h"
#include "LifecycleTest.h"

//Declare context
DLT_DECLARE_CONTEXT(Lfct)

/****************************************************************************
 Function Name     : LifecycleTest
 Description       : LifecycleTest Constructor
 Parameters        : none
 Return Type       : none
 ******************************************************************************/
LifecycleTest::LifecycleTest()
{

	//Register application with DLT
	DLT_REGISTER_APP("CALC","LifecycleTest Application");

	//Register all context with DLT
	DLT_REGISTER_CONTEXT(Lfct,"LFCT","LifecycleTest Context");

	DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest CTOR"));
}

/****************************************************************************
 Function Name     : ~LifecycleTest
 Description       : LifecycleTest Destructor
 Parameters        : none
 Return Type       : none
 ******************************************************************************/
LifecycleTest::~LifecycleTest()
{

	DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest DTOR"));

	//Unregister contexts
	DLT_UNREGISTER_CONTEXT(Lfct);

	//Unregister application with DLT
	DLT_UNREGISTER_APP();
}


gboolean LifecycleTest::createDBusConnection()
{
  /* Function local variables                */
  gboolean  boRetVal = TRUE; /* Return value */
  GError   *pError   = NULL; /* DBus Error   */

  dbusConnection = g_bus_get_sync((GBusType)NSM_BUS_TYPE, NULL, &pError);

  if(pError == NULL)
  {
    dBusName = g_dbus_connection_get_unique_name(dbusConnection);
	DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::createDBusConnection() get bus connection. Success."));
    if(dBusName != NULL)
    {
      boRetVal = TRUE;
      DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::createDBusConnection() get bus name Success."));
    }
    else
    {
      boRetVal = FALSE;
      DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::createDBusConnection() Failed to get bus name."));
    }
  }
  else
  {
    boRetVal = FALSE;
    DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::createDBusConnection() Failed to get bus connection."));
    g_error_free(pError);
  }

  return boRetVal;
}

gboolean LifecycleTest::createLifecycleProxy()
{
  /* Function local variables                */
  gboolean  boRetVal = TRUE; /* Return value */
  GError   *pError   = NULL; /* DBus Error   */

  DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::createLifecycleProxy() Create NodeStateConsumer proxy."));

  nsLifecycle = node_state_lifecycle_control_proxy_new_sync(dbusConnection,
                                                                  G_DBUS_PROXY_FLAGS_NONE,
                                                                  NSM_BUS_NAME,
                                                                  NSM_LIFECYCLE_OBJECT,
                                                                  NULL,
                                                                  &pError);

  if(pError != NULL)
  {
    boRetVal = FALSE;
    DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::createLifecycleProxy() failed to create NodeStateConsumer proxy."));
    g_error_free(pError);
  }
  else
  {
	  DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::createLifecycleProxy() created NodeStateConsumer proxy."));
  }

  return boRetVal;
}

gboolean LifecycleTest::SetNodeState(gboolean NewState)
{
	DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::SetNodeState Called"));

	GError           *pError              = NULL;
	NsmErrorStatus_e  enReceivedNsmReturn = NsmErrorStatus_NotSet;

	if(NewState == false)
	{
		(void) node_state_lifecycle_control_call_set_node_state_sync (nsLifecycle,
															   (gint) (NsmNodeState_ShuttingDown),
															   (gint*) &enReceivedNsmReturn,
															   NULL,
															   &pError);
	}
	else
	{
		(void) node_state_lifecycle_control_call_set_node_state_sync (nsLifecycle,
															   (gint) (NsmNodeState_StartUp),
															   (gint*) &enReceivedNsmReturn,
															   NULL,
															   &pError);
	}
}

gboolean LifecycleTest::RestartNode()
{
	DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::RestartNode Called"));

	GError           *pError              = NULL;
	NsmErrorStatus_e  enReceivedNsmReturn = NsmErrorStatus_NotSet;



	(void) node_state_lifecycle_control_call_request_node_restart_sync (nsLifecycle,
																		NsmRestartReason_User,
																		NSM_SHUTDOWNTYPE_NORMAL,
																		(gint*) &enReceivedNsmReturn,
																		NULL,
																		&pError);

}

/****************************************************************************
 Function Name     : main
 Description       : Main function
 Parameters        : args - Command line arguments list
 Return Type       : int
 ******************************************************************************/
int LifecycleTest::main(__attribute__((unused)) const std::vector<std::string>& args)
{
	DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("LifecycleTest::main Called"));

	createDBusConnection();
	createLifecycleProxy();


	int option;
	bool loopStatus=true;

	while(loopStatus)
	{
		std::cout<<"Enter option \n 1) Power OFF \n 2) Power ON\n 3) Exit\n";
		std::cin>>option;

		switch(option)
		{
			case 1:
				DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("SetNodeState to off"));
				SetNodeState(false);
				//RestartNode();
				break;

			case 2:
				DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("SetNodeState to on"));
				SetNodeState(true);
				break;

			case 3 :
				DLT_LOG(Lfct,DLT_LOG_INFO,DLT_STRING("Exit"));
				loopStatus = false;
				break;
		}
	}

	//Exit Successfully
	return Application::EXIT_OK;
}

POCO_SERVER_MAIN(LifecycleTest)
