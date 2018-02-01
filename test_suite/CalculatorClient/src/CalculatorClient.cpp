#include "CalculatorClient.h"
#include <dlt/dlt.h>
#include <sys/time.h>


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
		EstablishConnection();
		// Subscriptions();

		std::cerr << std::endl;
		std::cerr << "size of struct --> " << sizeof(Calculator::MetadataElement)<< "\n";


		DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST STARTED"));

		std::cerr << std::endl;
		std::cerr << "#################################################################" << std::endl;
		std::cerr << "#################################################################" << std::endl;
		std::cerr << "###################   TEST STARTED   ############################" << std::endl;
		std::cerr << "#################################################################" << std::endl;
		std::cerr << "#################################################################" << std::endl;
		std::cerr << std::endl;


		Test01();
		Test02();
		Test03();
		Test04();
		Test05();
		Test06(10);

		TestUint8Perf(10);
		TestUint16Perf(10);
		TestUint32Perf(10);
		TestUint64Perf(10);
		TestByteBufferPerf(10);
		TestStringPerf(10);

		TestUint8Perf(1024);
		TestUint16Perf(1024);
		TestUint32Perf(1024);
		TestUint64Perf(1024);
		TestByteBufferPerf(1024);
		TestStringPerf(1024);

		TestUint8Perf(102400);
		TestUint16Perf(102400);
		TestUint32Perf(102400);
		TestUint64Perf(102400);
		TestByteBufferPerf(102400);
		TestStringPerf(102400);

		TestUint8Perf(1048756);
		TestUint16Perf(1048756);
		TestUint32Perf(1048756);
		TestUint64Perf(1048756);
		TestByteBufferPerf(1048756);
		TestStringPerf(1048756);

		DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST COMPLETED"));

		std::cerr << std::endl;
		std::cerr << "#################################################################" << std::endl;
		std::cerr << "#################################################################" << std::endl;
		std::cerr << "###################   TEST COMPLETED   ##########################" << std::endl;
		std::cerr << "#################################################################" << std::endl;
		std::cerr << "#################################################################" << std::endl;
		std::cerr << std::endl;

/*
		while (true)
		{
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
*/

	//Exit Successfully
	return Application::EXIT_OK;
}

void CalculatorClient::EstablishConnection()
{
		std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();
		calculatorClntProxy = runtime->buildProxy<CalculatorProxy>("local","CalculatorServer","client-sample");

		DLT_LOG(CalcClient,	DLT_LOG_INFO, DLT_STRING("Checking availability!"));

		while ( calculatorClntProxy != NULL && !calculatorClntProxy->isAvailable() )
		{
			usleep(30);
		}
		int32_t retValue;
		calculatorClntProxy->getCalattributeAttribute().setValue( 12, callStatus, retValue);
		DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Calulator server availabilable"));
}

void CalculatorClient::Subscriptions()
{
	if(calculatorClntProxy == NULL)
		return;

		calculatorClntProxy->getOperation_statusEvent().subscribe([&](uint32_t status ){
			DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("getOperation_statusEvent:: "), DLT_INT(status));
		});

		calculatorClntProxy->getCalattributeAttribute().getChangedEvent().subscribe([&](int32_t status ){
			DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("getCalattributeAttribute:: "), DLT_INT(status));
		});
}

void CalculatorClient::Test01()
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: UInt8"));

	for(int i=0; i < TEST_ITERATION; i++)
	{
		if(calculatorClntProxy != NULL)
		{
			  uint8_t _input= 200, _output;
			  gettimeofday(&start, NULL);
				calculatorClntProxy->Test1(_input, callStatus, _output);
				gettimeofday(&end, NULL);
				t1 = start.tv_sec * 1000000 + start.tv_usec;
				t2 = end.tv_sec * 1000000 + end.tv_usec;

				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}

				// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(diff));
		}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));
}

void CalculatorClient::Test02()
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: UInt16"));
	for(int i=0; i < TEST_ITERATION; i++)
	{
			if(calculatorClntProxy != NULL)
			{
				  uint16_t _input= 65535, _output;
				  gettimeofday(&start, NULL);
					calculatorClntProxy->Test2(_input, callStatus, _output);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;

				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
					// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));

}

void CalculatorClient::Test03()
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: UInt32"));
	for(int i=0; i < TEST_ITERATION; i++)
	{
			if(calculatorClntProxy != NULL)
			{
				  uint32_t _input= 4294967295, _output;
				  gettimeofday(&start, NULL);
					calculatorClntProxy->Test3(_input, callStatus, _output);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
				diff = t2-t1;

				if(i == 0)
				{

					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
					// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));

}

void CalculatorClient::Test04()
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: UInt64"));
	for(int i=0; i < TEST_ITERATION; i++)
	{
			if(calculatorClntProxy != NULL)
			{
				  uint64_t _input= 18446744073709551614, _output;
				  gettimeofday(&start, NULL);
					calculatorClntProxy->Test4(_input, callStatus, _output);
					gettimeofday(&end, NULL);
					t1 = start.tv_sec * 1000000 + start.tv_usec;
					t2 = end.tv_sec * 1000000 + end.tv_usec;
				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
					// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));

}

void CalculatorClient::Test05()
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: Struct "));
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

				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
					// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
			}
		}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));

}

void CalculatorClient::Test06(int loop)
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: Struct Array- SIZE:: "),DLT_INT(loop));
	Calculator::MetadataElementList inputElementList, outputElementList;
	for(int i=0 ; i < loop;i++)
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
				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
				// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
		}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));

}

void CalculatorClient::TestStringPerf(int loop)
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: String- SIZE:: "),DLT_INT(loop));
	std::string _input= "", _output;
	for(int i=0; i < loop; i++)
	{
		_input = _input + "A";
	}

	for(int i=0; i < TEST_ITERATION; i++)
	{
		if(calculatorClntProxy != NULL)
		{
			  gettimeofday(&start, NULL);
				calculatorClntProxy->Test5(_input, callStatus, _output);
				gettimeofday(&end, NULL);
				t1 = start.tv_sec * 1000000 + start.tv_usec;
				t2 = end.tv_sec * 1000000 + end.tv_usec;
				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
				// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
		}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));

}

void CalculatorClient::TestUint8Perf(int loop)
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: UInt8Array- SIZE:: "),DLT_INT(loop));
	Calculator::MyArray01 input_array_uint8,output_array_uint8;
	for(int i=0; i < loop ;i++)
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
				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
				// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
		}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));

}

void CalculatorClient::TestUint16Perf(int loop)
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: UInt16Array- SIZE:: "),DLT_INT(loop));
	Calculator::MyArray02 input_array_uint16,output_array_uint16;

	for(int i=0; i < loop;i++)
	{
		input_array_uint16.push_back(65535);
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
				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
				// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
		}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));

}

void CalculatorClient::TestUint32Perf(int loop)
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: UInt32Array- SIZE:: "),DLT_INT(loop));
	Calculator::MyArray03 input_array_uint32,output_array_uint32;

	for(int i=0; i < loop;i++)
	{
		input_array_uint32.push_back(4294967295);
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
				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
				// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
		}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));
}

void CalculatorClient::TestUint64Perf(int loop)
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: UInt64Array- SIZE:: "),DLT_INT(loop));
	Calculator::MyArray04 input_array_uint64,output_array_uint64;

	for(int i=0; i < loop;i++)
	{
		input_array_uint64.push_back(4294967295455555);
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
				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
				// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
		}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));
}

void CalculatorClient::	TestByteBufferPerf(int loop)
{
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("TEST_CASE:: ByteBuffer- SIZE:: "),DLT_INT(loop));
	CommonAPI::ByteBuffer input_bytebuffer,output_bytebuffer;

	for(int i=0; i < loop;i++)
	{
		input_bytebuffer.push_back(23);
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
				diff = t2-t1;

				if(i == 0)
				{
					Avg = 0;
					min = diff;
					max = diff;
					Avg += diff;
				}
				else
				{
					Avg += diff;
				/* If current element of array is greater than max */
				if(diff > max)
        {
            max = diff;
        }

        /* If current element of array is smaller than min */
        if(diff<min)
        {
            min = diff;
        }
				}
				// DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Iteration--> "),DLT_INT(i),DLT_STRING(" <--"),DLT_STRING("Micro Seconds:: "), DLT_FLOAT64(t2-t1));
		}
	}
	DLT_LOG(CalcClient,DLT_LOG_INFO,DLT_STRING("Time in Microseconds min:: "), DLT_FLOAT64(min),DLT_STRING(" max:: "),DLT_FLOAT64(max),DLT_STRING(" Avg:: "),DLT_FLOAT64(Avg/100));
}

POCO_SERVER_MAIN(CalculatorClient)
