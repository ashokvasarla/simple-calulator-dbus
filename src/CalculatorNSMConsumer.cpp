/*
 * CalculatorNSMConsumer.cpp
 *
 *  Created on: Jul 14, 2016
 *      Author: visteon
 */

#include "CalculatorNSMConsumer.h"
#include <dlt/dlt.h>

//Import Context
DLT_IMPORT_CONTEXT(CalcServer)
#define CALC_DBUS_OBJECT_PATH "/mch/calculator" /**< D-Bus object path**/

static gboolean OnLifecycleClientCb(NodeStateLifeCycleConsumer *pConsumer,
								  GDBusMethodInvocation      *pInvocation,
								  const guint32               u32LifeCycleRequest,
								  const guint32               u32RequestId,
								  gpointer                    pUserData)
{
	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("OnLifecycleClientCb Received"));
	gint error = NsmErrorStatus_NotSet;
	
	if( u32LifeCycleRequest == NSM_SHUTDOWNTYPE_NORMAL)
	{
		DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("NSM_SHUTDOWNTYPE_NORMAL Received from NSM"));
		if(pConsumer!= NULL)
		{
			DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("Send Lifecycle Complete Status to NSM") ,DLT_STRING(g_dbus_method_invocation_get_method_name(pInvocation)));
			node_state_life_cycle_consumer_complete_lifecycle_request(pConsumer,
																	  pInvocation,
																	  NsmErrorStatus_Ok);
	
	    }
		
	}
	else
	{
		DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("NSM_SHUTDOWNTYPE_NORMAL failed "));
	}
	
	return TRUE;
}


gboolean OnApplicationModeSignal(NodeStateConsumer *pObject,
								   const gint        i32ApplicationMode,
								   gpointer          pUserData)
{
	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("OnApplicationModeSignal Received"));
	return TRUE;
}


gboolean OnNodeStateSignal(NodeStateConsumer *pObject,
                                     const gint         i32NodeState,
                                     gpointer           pUserData)
{
	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("OnNodeStateSignal Received"));
	return TRUE;
}


static gboolean OnSessionSignal(NodeStateConsumer *pObject,
                                          const gchar       *sSessionName,
                                          const gint         i32SeatId,
                                          const gint         i32SessionState,
                                          gpointer           pUserData)
{
	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("OnSessionSignal Received"));
	return TRUE;
}

CalculatorNSMConsumer::CalculatorNSMConsumer()
{
	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer CTOR"));
}

CalculatorNSMConsumer::~CalculatorNSMConsumer()
{
	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer DTOR"));
}

gboolean CalculatorNSMConsumer::createDBusConnection()
{
	/* Function local variables                */
	gboolean  boRetVal = TRUE; /* Return value */
	GError   *pError   = NULL; /* DBus Error   */

	dbusConnection = g_bus_get_sync((GBusType)NSM_BUS_TYPE, NULL, &pError);

	if(pError == NULL)
	{
		dBusName = g_dbus_connection_get_unique_name(dbusConnection);
		DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createDBusConnection() get bus connection. Success."),
									    DLT_STRING(dBusName));

		if(dBusName != NULL)
		{
			  boRetVal = TRUE;
			  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createDBusConnection() get bus name Success."));
		}
		else
		{
			boRetVal = FALSE;
			DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createDBusConnection() Failed to get bus name."));
		}
	}
	else
	{
		boRetVal = FALSE;
		DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createDBusConnection() Failed to get bus connection."));
		g_error_free(pError);
	}

	return boRetVal;
}


gboolean CalculatorNSMConsumer::createConsumerProxy()
{
	  /* Function local variables                */
	  gboolean  boRetVal = TRUE; /* Return value */
	  GError   *pError   = NULL; /* DBus Error   */

	  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createConsumerProxy() Create NodeStateConsumer proxy."));

	  nodeStateConsumer = node_state_consumer_proxy_new_sync(dbusConnection,
																	  G_DBUS_PROXY_FLAGS_NONE,
																	  NSM_BUS_NAME,
																	  NSM_CONSUMER_OBJECT,
																	  NULL,
																	  &pError);

	  if(pError != NULL)
	  {
			boRetVal = FALSE;
			DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createConsumerProxy() failed to create NodeStateConsumer proxy."));
			g_error_free(pError);
	  }
	  else
	  {
			g_signal_connect(nodeStateConsumer, "node-state",            G_CALLBACK(OnNodeStateSignal),       NULL);
			g_signal_connect(nodeStateConsumer, "node-application-mode", G_CALLBACK(OnApplicationModeSignal), NULL);
			g_signal_connect(nodeStateConsumer, "session-state-changed", G_CALLBACK(OnSessionSignal),         NULL);

			DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createConsumerProxy() created NodeStateConsumer proxy."));
	  }

	  return boRetVal;
}

gboolean CalculatorNSMConsumer::createLifecycleStub()
{
	  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createLifecycleStub() "));
	  gboolean                    boRetVal           = FALSE;

	  pLifeCycleConsumer = node_state_life_cycle_consumer_skeleton_new();
	  

	  if(g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(pLifeCycleConsumer),
			  	  	  	  	  	  	  	  dbusConnection,
	                                      CALC_DBUS_OBJECT_PATH,
	                                      NULL) == TRUE)
	  {
		  boRetVal = TRUE;
		  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createLifecycleStub() Successful"));
		  (void)g_signal_connect(pLifeCycleConsumer, "handle-lifecycle-request", G_CALLBACK(OnLifecycleClientCb), NULL);
	  }
	  else
	  {
		  boRetVal = FALSE;
		  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::createLifecycleStub() Failed"));
	  }

	  return boRetVal;
}

gboolean CalculatorNSMConsumer::getNodeState()
{
  /* Function local variables                                   */
  gboolean          boRetVal            = TRUE; /* Return value */
  GError           *pError              = NULL;
  NsmErrorStatus_e  enReceivedNsmReturn = NsmErrorStatus_NotSet;
  NsmNodeState_e    enReceivedNodeState = NsmNodeState_NotSet;

  
  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::getNodeState()"));
  (void) node_state_consumer_call_get_node_state_sync(nodeStateConsumer,
                                                      (gint*) &enReceivedNodeState,
                                                      (gint*) &enReceivedNsmReturn,
                                                      NULL,
                                                      &pError);

  /* Evaluate result. Check if a D-Bus error occurred. */
  if(pError == NULL)
  {
	  
    /* D-Bus communication successful. Check if NSM returned with the expected value. */
    if(enReceivedNsmReturn == NsmErrorStatus_Ok) //, NsmNodeState_LucRunning
    {
	  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::getNodeState() NSM node state."),DLT_INT(enReceivedNodeState));
      
      switch(enReceivedNodeState)
      {
		  case NsmNodeState_NotSet:
			  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::getNodeState() NsmNodeState_NotSet"));
			  break;

		  case NsmNodeState_StartUp:
			  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::getNodeState() NsmNodeState_StartUp"));
			  break;

		  case NsmNodeState_BaseRunning:
			  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::getNodeState() NsmNodeState_BaseRunning"));
			  break;

		  case NsmNodeState_LucRunning:
			  DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::getNodeState() NsmNodeState_LucRunning"));
			  break;

		  default:
			  break;
		  
	  }
      
      
    }
    else
    {
      boRetVal = FALSE;
      DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("Did not receive expected NSM return value"));

    }
  }
  else
  {
    boRetVal = FALSE;
    DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("Failed to create access NSM via D-Bus"));
    
    g_error_free(pError);
  }

  return boRetVal;
}
gboolean CalculatorNSMConsumer::registerShutdownClient()
{
	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::registerShutdownClient()"));
  /* Function local variables                                       */
  gboolean              boRetVal            = TRUE; /* Return value */
  GError               *pError              = NULL;
  NsmErrorStatus_e      enReceivedNsmReturn = NsmErrorStatus_NotSet;
  
  
  
  (void) node_state_consumer_call_register_shutdown_client_sync(nodeStateConsumer,
                                                                dBusName,
                                                                CALC_DBUS_OBJECT_PATH,
                                                                NSM_SHUTDOWNTYPE_NORMAL,
                                                                2000,
                                                                (gint*) &enReceivedNsmReturn,
                                                                NULL,
                                                                &pError);

  /* Evaluate result. Check if a D-Bus error occurred. */
  if(pError == NULL)
  {
    /* D-Bus communication successful. Check if NSM returned with the expected value. */
    if(enReceivedNsmReturn == NsmErrorStatus_Ok)
    {
      boRetVal = TRUE;
      DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::registerShutdownClient() NsmErrorStatus_Ok" ));
    }
    else
    {
      boRetVal = FALSE;
      DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::registerShutdownClient() Did not receive expected NSM return value" ),DLT_INT(enReceivedNsmReturn));
      
    }
  }
  else
  {
    boRetVal = FALSE;
    DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorNSMConsumer::registerShutdownClient() Failed to create access NSM via D-Bus. Error msg.:" ),DLT_STRING(pError->message));
    
    g_error_free(pError);
  }

  return boRetVal;	
}


