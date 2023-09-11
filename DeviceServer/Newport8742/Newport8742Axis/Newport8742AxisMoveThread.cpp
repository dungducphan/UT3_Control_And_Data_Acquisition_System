#include  <tango.h>
#include <Newport8742AxisMoveThread.h>


Newport8742AxisMoveThread::Newport8742AxisMoveThread(const char* devname, const char* attname, Tango::DevShort axisnumber)
 :  omni_thread(), dev_name(devname), att_name(attname), axis_number(axisnumber)
{
	start_undetached();
}

void* Newport8742AxisMoveThread::run_undetached(void* ptr)
{
	
	try
	{
		Tango::DevString msg;
		stringstream cmd;
		Tango::DeviceData devin, devout;
		Tango::DevLong moving, currentPos;
		Tango::DeviceProxy dproxy(dev_name);
		cmd << axis_number << "MD?";
		msg = (char*) cmd.str().c_str();
		devin << msg;

		for(;;)
		{
			devout = dproxy.command_inout("WriteReadLong", devin);
			devout >> moving;
			if(moving == 1)
			{
				break;
			}
			sleep(0, 50000000);
		}
		cmd.str("");
		cmd << axis_number << "TP?";
		msg = (char*) cmd.str().c_str();
		devin << msg;
		devout = dproxy.command_inout("WriteReadLong", devin);
		devout >> currentPos;



		// write current position to StoredPosition
		Tango::AttributeProxy aproxy(att_name);
		Tango::DeviceAttribute da("StoredPosition", currentPos);
		aproxy.write(da);

	}
	catch(Tango::DevFailed &e)
	{
		string tmp(e.errors[0].desc);
		Tango::Except::throw_exception( "Read error",
										tmp,
										"Newport8742Axis::writeCmd",
										Tango::WARN);
	}
	return (void*) 0;
}

