#include "CalculatorClient.h"
#include "CommonAPI/CommonAPI.hpp"
#include "CalculatorProxy.hpp"
#include <dlt/dlt.h>
#include <sys/time.h>

using namespace v1_0::SimpleCalculator::CalculatorInterface;

#define TEST_ITERATION 100
//Declare context
DLT_DECLARE_CONTEXT(CalcClient)

/****************************************************************************
 Function Name     : CalculatorClient
 Description       : CalculatorClient Constructor
 Parameters        : none
 Return Type       : none
 ******************************************************************************/
CalculatorClient::CalculatorClient()
{
	//Register application with DLT
	DLT_REGISTER_APP("CALC","Calculator Client Application");

	//Register all context with DLT
	DLT_REGISTER_CONTEXT(CalcClient,"CLNT","Calculator Client Context");

	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("CalculatorClient CTOR"));
}

/****************************************************************************
 Function Name     : ~CalculatorClient
 Description       : CalculatorClient Destructor
 Parameters        : none
 Return Type       : none
 ******************************************************************************/
CalculatorClient::~CalculatorClient()
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("CalculatorClient DTOR"));

	//Unregister contexts
	DLT_UNREGISTER_CONTEXT(CalcClient);

	//Unregister application with DLT
	DLT_UNREGISTER_APP();
}

/****************************************************************************
 Function Name     : main
 Description       : Main function
 Parameters        : args - Command line arguments list
 Return Type       : int
 ******************************************************************************/
int CalculatorClient::main(__attribute__((unused)) const std::vector<std::string>& args)
{
  //   if (args.size() < 3)
  //   {
  //   	// We expect 3 arguments: Command param1 param2
  //       std::cerr << "Usage: Command param1 param2" << std::endl;
  //       std::cerr << "E.g.: CalculatorClient add 2 3" << std::endl;
  //   }
  //   else
  //   {
		// std::string 			cmd	= args[0];
		// uint32_t  				param1 = stoi(args[1]);
		// uint32_t  				param2 = stoi(args[2]);
		CommonAPI::CallStatus 	callStatus;
		uint32_t  result = 0;

		std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
		std::shared_ptr <CalculatorProxy<>> calculatorClntProxy = runtime->buildProxy<CalculatorProxy>("local","CalculatorServer","client-sample");

		DLT_LOG(CalcClient,	DLT_LOG_INFO, DLT_STRING("Checking availability!"));

		while ( calculatorClntProxy != NULL && !calculatorClntProxy->isAvailable() )
		{
			usleep(30);
		}

		DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Calulator server availabilable"));

		calculatorClntProxy->getOperation_statusEvent().subscribe([&](uint32_t status ){
			DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("getOperation_statusEvent:: "), DLT_INT(status));
		});

		calculatorClntProxy->getCalattributeAttribute().getChangedEvent().subscribe([&](int32_t status ){
			DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("getCalattributeAttribute:: "), DLT_INT(status));
		});

		// if(cmd == "add")
		// {
		// 	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Called add() public interface with input param1 = "),
		// 									DLT_INT(param1),
		// 									DLT_STRING("param2 = "),
		// 									DLT_INT(param2));
		// 	if(calculatorClntProxy != NULL)
		// 		calculatorClntProxy->add(param1,param2,callStatus,result);

		// 	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Add result = "),
		// 									DLT_INT(result));

		// }
		// else if(cmd == "div")
		// {
		// 	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Called div() public interface with input param1 = "),
		// 									DLT_INT(param1),
		// 									DLT_STRING("param2 = "),
		// 									DLT_INT(param2));
		// 	Calculator::DIVISION_ERROR error;
		// 	float rr;
		// 	if(calculatorClntProxy != NULL)
		// 		calculatorClntProxy->division(param1,param2,callStatus,error,rr);

		// 	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Div result = "),
		// 									DLT_INT(rr));

		// }
		// else
		// {
		// 	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Unhandled reques"));
		// }

		std::cerr << "size of struct:: " << sizeof(Calculator::MetadataElement);

		struct timeval start, end;
		double t1, t2;
		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
				  uint8_t _input= 200, _output;
					calculatorClntProxy->Test1(_input, callStatus, _output);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}
		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
				  uint16_t _input= 65535, _output;
					calculatorClntProxy->Test2(_input, callStatus, _output);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}

		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
				  uint32_t _input= 4294967295, _output;
					calculatorClntProxy->Test3(_input, callStatus, _output);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}

		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
				  uint64_t _input= 18446744073709551614, _output;
					calculatorClntProxy->Test4(_input, callStatus, _output);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}

		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
				  std::string _input= "Hi Welcome", _output;
					calculatorClntProxy->Test5(_input, callStatus, _output);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}

		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
					Calculator::MetadataElement _input, _output;
				  _input.setType(Calculator::MetadataType::MEDIA_METADATATYPE_TITLE);
				  _input.setFormat(Calculator::MetadataFormat::METADATAFORMAT_STRING);
				  _input.setStringValue("Test Title");
				  _input.setIntegerValue(2);
				  gettimeofday(&start, NULL);

					calculatorClntProxy->Test6(_input, callStatus, _output);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}
			Calculator::MetadataElementList inputElementList, outputElementList;
			for(int i=0 ; i < 10;i++)
			{
					Calculator::MetadataElement _input;
				  _input.setType(Calculator::MetadataType::MEDIA_METADATATYPE_TITLE);
				  _input.setFormat(Calculator::MetadataFormat::METADATAFORMAT_STRING);
				  _input.setStringValue("Test Title");
				  _input.setIntegerValue(2);
				  inputElementList.push_back(_input);
			}


		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
					calculatorClntProxy->Test7(inputElementList, callStatus, outputElementList);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}


		Calculator::MyArray01 input_array_uint8,output_array_uint8;

		for(int i=0; i< 10;i++)
		{
			input_array_uint8.push_back(200);
		}

		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
					calculatorClntProxy->Test8(input_array_uint8, callStatus, output_array_uint8);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}

		Calculator::MyArray02 input_array_uint16,output_array_uint16;

		for(int i=0; i< 10;i++)
		{
			input_array_uint8.push_back(65535);
		}

		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
					calculatorClntProxy->Test9(input_array_uint16, callStatus, output_array_uint16);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}

		Calculator::MyArray03 input_array_uint32,output_array_uint32;

		for(int i=0; i< 10;i++)
		{
			input_array_uint8.push_back(4294967295);
		}

		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
					calculatorClntProxy->Test10(input_array_uint32, callStatus, output_array_uint32);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}

		Calculator::MyArray04 input_array_uint64,output_array_uint64;

		for(int i=0; i< 10;i++)
		{
			input_array_uint8.push_back(4294967295455555);
		}

		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
					calculatorClntProxy->Test11(input_array_uint64, callStatus, output_array_uint64);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}

		CommonAPI::ByteBuffer input_bytebuffer,output_bytebuffer;

		for(int i=0; i< 10;i++)
		{
			input_array_uint8.push_back(23);
		}

		for(int i=0; i < TEST_ITERATION; i++)
		{
			if(calculatorClntProxy != NULL)
			{
				  gettimeofday(&start, NULL);
					calculatorClntProxy->Test12(input_bytebuffer, callStatus, output_bytebuffer);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
					DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Performance LOG Loop :: --> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}


		// while (true)
		// {
  //       std::this_thread::sleep_for(std::chrono::seconds(30));
  //   }
    // }

	//Exit Successfully
	return Application::EXIT_OK;
}

POCO_SERVER_MAIN(CalculatorClient)
