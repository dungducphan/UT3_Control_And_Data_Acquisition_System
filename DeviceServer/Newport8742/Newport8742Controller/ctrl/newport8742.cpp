#include <newport8742.h>
#include <ipc_exception.h>

void NewPort8742::emptyErrorQueue()
{
	*this << "TB?" << getEOTS();
	vector<string> out;
	again:
	tokenize(out, true, ",");
	if(out[0] != "0")
	{
		goto again;
	}
}
NewPort8742::NewPort8742(USBDevice* device)
	: Io(device)
{
	readSelect(false);
	writeSelect(false);
	setEOTS("\r\n");
	emptyErrorQueue();
}

NewPort8742::NewPort8742(TcpSocket* device)
	: Io(device)
{
	setEOTS("\r\n");
	string tmp;
	long sec, nsec;
	readTimeout(&sec, &nsec);
	readTimeout(0, 9999999);
	try
	{
		readLine(tmp);
	}
	catch(IpcTimeOutException)
	{
	}
	readTimeout(sec, nsec);
	emptyErrorQueue();
	
}

void NewPort8742::writeRead(const char* in, string& out)
{
	int repeat = 10;
	*this << in << getEOTS();
	again:
	readLine(out);
	if(!out.size())
	{
		if(repeat > 0)
		{
			--repeat;
			::usleep(20000);
			goto again;
		}
		checkError();
	}
	
}

void NewPort8742::writeRead(const char* in, int* out)
{
	string reply;
	int repeat = 10;
	*this << in << getEOTS();
	again:
	readLine(reply);
	if(!reply.size())
	{
		if(repeat > 0)
		{
			--repeat;
			::usleep(20000);
			goto again;
		}
		checkError();
	}
	*out = toLong(reply.c_str());
}
	

void NewPort8742::write(string& in)
{
	*this << in << getEOTS();
	checkError();
}

void NewPort8742::write(const char* in)
{
	*this << in << getEOTS();
	checkError();
}

void NewPort8742::checkError()
{
	*this << "TB?" << getEOTS();
	vector<string> out;
	size_t n;
	int repeat = 10;
	again:
	if((n = tokenize(out, true, ",")) != 2)
	{
		if(repeat > 0)
		{
			--repeat;
			::usleep(20000);
			goto again;
		}
		throw(IpcException("Invalid number of tokens when checking error", __FILE__, __LINE__));
	}
	if(out[0] != "0")
	{
		int error = toLong(out[0]);
		if(error < 99)
		{
			throw(IpcException(out[1], __FILE__, __LINE__));
		}
		else
		{
			stringstream msg;
			msg << "Error on axis " << (error / 100) << ':' << out[1];
			throw(IpcException(msg.str(), __FILE__, __LINE__));
		}
	}
}
	
	
