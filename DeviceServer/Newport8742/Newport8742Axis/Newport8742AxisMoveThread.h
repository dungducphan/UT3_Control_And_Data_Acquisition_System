#ifndef NEWPORT8742AXIS_MOVE_THREAD_H
#define  NEWPORT8742AXIS_RESTORE_THREAD_H

#include <Newport8742Axis.h>

using namespace Newport8742Axis_ns;

class Newport8742AxisMoveThread : public omni_thread
{
	public:
		Newport8742AxisMoveThread(const char* devname, const char* attname, Tango::DevShort axisnumber);
		~Newport8742AxisMoveThread() {}
	private:
		void* run_undetached(void* ptr);
		string dev_name;
		string att_name;
		Tango::DevShort axis_number;
};
		


#endif //HEXASMARCTRL_HOME_THREAD_H


