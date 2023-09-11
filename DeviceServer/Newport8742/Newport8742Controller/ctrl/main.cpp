#include <iostream>
#include <newport8742.h>

int main(int argc, char** argv)
{
	try
	{
		NewPort8742 ctrl(new USBDevice("/dev/newport0"));
		string out;
		int val;
		char buf[1024];
		ctrl.consoleDebug(true);
		ctrl.setEOTS("\r\n");
		
		ctrl.writeRead( "*IDN?", out);
		cerr << out << endl;

		ctrl.writeRead( "TB?", out);
		cerr << out << endl;
		
		ctrl.writeRead("1DH?", &val);
		cerr << val << endl;
		
	}
	catch(IpcException& e)
	{
		e.print();
	}
}
