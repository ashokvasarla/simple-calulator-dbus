#include <iostream>
#include <thread>
#include "CalculatorServer.h"
#include "CommonAPI/CommonAPI.hpp"
#include <dlt/dlt.h>
// #include "CalculatorNSMConsumer.h"
// static GMainLoop                                 *g_pMainLoop                = NULL;
//Declare context
DLT_DECLARE_CONTEXT(CalcServer)

/****************************************************************************
 Function Name     : CalculatorServer
 Description       : CalculatorServer Constructor
 Parameters        : none
 Return Type       : none
 ******************************************************************************/
CalculatorServer::CalculatorServer()
{
	// //Register application with DLT
	DLT_REGISTER_APP("CALC","Calculator Server Application");

	// //Register all context with DLT
	DLT_REGISTER_CONTEXT(CalcServer,"SRVR","Calculator Server Context");

	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorServer CTOR"));
	// CalculatorNSMConsumer *calcNsmConsumer = new CalculatorNSMConsumer();
	// calcNsmConsumer->createDBusConnection();
	// calcNsmConsumer->createConsumerProxy();
	// calcNsmConsumer->createLifecycleStub();
	// calcNsmConsumer->getNodeState();
	// calcNsmConsumer->registerShutdownClient();

	// /* Create the main loop */
 //    g_pMainLoop = g_main_loop_new(NULL, FALSE);

 //    /* The main loop is only canceled if the Node is completely shut down or the D-Bus connection fails */
 //    g_main_loop_run(g_pMainLoop);

}

/****************************************************************************
 Function Name     : ~CalculatorServer
 Description       : CalculatorServer Destructor
 Parameters        : none
 Return Type       : none
 ******************************************************************************/
CalculatorServer::~CalculatorServer()
{
	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorServer DTOR"));

	//Unregister contexts
	DLT_UNREGISTER_CONTEXT(CalcServer);

	//Unregister application with DLT
	DLT_UNREGISTER_APP();
}

/****************************************************************************
 Function Name     : main
 Description       : Main function
 Parameters        : args - Command line arguments list
 Return Type       : int
 ******************************************************************************/
int CalculatorServer::main(__attribute__((unused)) const std::vector<std::string>& args)
{
	std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
	std::shared_ptr<CalculatorStubImpl> itsCalculatorStub = std::make_shared<CalculatorStubImpl>();

	runtime->registerService("local","CalculatorServer",itsCalculatorStub, "service-sample");
	DLT_LOG(CalcServer,DLT_LOG_INFO,DLT_STRING("CalculatorServer Registred"));

	while (true)
	{
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }

	//Exit Successfully
	return Application::EXIT_OK;
}

POCO_SERVER_MAIN(CalculatorServer)
