#ifndef NEWPORT8742_H
#define NEWPORT8742_H

#include <io.h>
#include <ipc_usbdevice.h>
#include <ipc_tcp.h>
#include <ipc_exception.h>


class NewPort8742 : public Io
{
	public:
		NewPort8742(USBDevice* device);
		NewPort8742(TcpSocket* device);
		void write(string& in);
		void write(const char* in);
		void writeRead(const char* in, string& out);
		void writeRead(const char* in, int* out);
	private:
		void checkError();
		void emptyErrorQueue();
};

#endif
