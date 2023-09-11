/*
 * StanfordDG645Common.h
 *
 *  Created on: Jan 16, 2019
 *      Author: janmeyer
 */

#ifndef STANFORDDG645COMMON_H_
#define STANFORDDG645COMMON_H_

#define DG645_BUFFER_SIZE 255
#define DG645_REMOTE_PORT "5024"
#define DG645_TIMEOUT_S 1
#define DG645_TASK_WAIT_TRIALS 10
#define DG645_TASK_WAIT_INTERVAL_NS 300000000
#define DG645_CHANNEL_T0 0

#define DG645_ERR_NO_ERROR 0
#define DG645_ERR_ILLEGAL_VALUE -10
#define DG645_ERR_ILLEGAL_MODE -11
#define DG645_ERR_ILLEGAL_DELAY -12
#define DG645_ERR_ILLEGAL_LINK -13
#define DG645_ERR_RECALL_FAILED -14
#define DG645_ERR_NOT_ALLOWED -15
#define DG645_ERR_FAILED_SELF_TEST -16
#define DG645_ERR_FAILED_AUTO_CALIBRATION -17
#define DG645_ERR_LOST_DATA -30
#define DG645_ERR_NO_LISTENER -32
#define DG645_ERR_FAILED_ROM_CHECK -40
#define DG645_ERR_FAILED_OFFSET_T0_TEST -41
#define DG645_ERR_FAILED_OFFSET_AB_TEST -42
#define DG645_ERR_FAILED_OFFSET_CD_TEST -43
#define DG645_ERR_FAILED_OFFSET_EF_TEST -44
#define DG645_ERR_FAILED_OFFSET_GH_TEST -45
#define DG645_ERR_FAILED_AMPLITUDE_T0_TEST -46
#define DG645_ERR_FAILED_AMPLITUDE_AB_TEST -47
#define DG645_ERR_FAILED_AMPLITUDE_CD_TEST -48
#define DG645_ERR_FAILED_AMPLITUDE_EF_TEST -49
#define DG645_ERR_FAILED_AMPLITUDE_GH_TEST -50
#define DG645_ERR_FAILED_FPGA_COMMUNICATIONS_TEST -51
#define DG645_ERR_FAILED_GPIB_COMMUNICATIONS_TEST -52
#define DG645_ERR_FAILED_DDS_COMMUNICATIONS_TEST -53
#define DG645_ERR_FAILED_SERIAL_EEPROM_COMMUNICATIONS_TEST -54
#define DG645_ERR_FAILED_TEMPERATURE_SENSOR_COMMUNICATIONS_TEST -55
#define DG645_ERR_FAILED_PLL_COMMUNICATIONS_TEST -56
#define DG645_ERR_FAILED_DAC_0_COMMUNICATIONS_TEST -57
#define DG645_ERR_FAILED_DAC_1_COMMUNICATIONS_TEST -58
#define DG645_ERR_FAILED_DAC_2_COMMUNICATIONS_TEST -59
#define DG645_ERR_FAILED_SAMPLE_AND_HOLD_OPERATIONS_TEST -60
#define DG645_ERR_FAILED_VJITTER_OPERATIONS_TEST -61
#define DG645_ERR_FAILED_CHANNEL_T0_ANALOG_DELAY_TEST -62
#define DG645_ERR_FAILED_CHANNEL_T1_ANALOG_DELAY_TEST -63
#define DG645_ERR_FAILED_CHANNEL_A_ANALOG_DELAY_TEST -64
#define DG645_ERR_FAILED_CHANNEL_B_ANALOG_DELAY_TEST -65
#define DG645_ERR_FAILED_CHANNEL_C_ANALOG_DELAY_TEST -66
#define DG645_ERR_FAILED_CHANNEL_D_ANALOG_DELAY_TEST -67
#define DG645_ERR_FAILED_CHANNEL_E_ANALOG_DELAY_TEST -68
#define DG645_ERR_FAILED_CHANNEL_F_ANALOG_DELAY_TEST -69
#define DG645_ERR_FAILED_CHANNEL_G_ANALOG_DELAY_TEST -70
#define DG645_ERR_FAILED_CHANNEL_H_ANALOG_DELAY_TEST -71
#define DG645_ERR_FAILED_SAMPLE_AND_HOLD_CALIBRATION -80
#define DG645_ERR_FAILED_T0_CALIBRATION -81
#define DG645_ERR_FAILED_T1_CALIBRATION -82
#define DG645_ERR_FAILED_A_CALIBRATION -83
#define DG645_ERR_FAILED_B_CALIBRATION -84
#define DG645_ERR_FAILED_C_CALIBRATION -85
#define DG645_ERR_FAILED_D_CALIBRATION -86
#define DG645_ERR_FAILED_E_CALIBRATION -87
#define DG645_ERR_FAILED_F_CALIBRATION -88
#define DG645_ERR_FAILED_G_CALIBRATION -89
#define DG645_ERR_FAILED_H_CALIBRATION -90
#define DG645_ERR_FAILED_VJITTER_CALIBRATION -91
#define DG645_ERR_ILLEGAL_COMMAND -110
#define DG645_ERR_UNDEFINED_COMMAND -111
#define DG645_ERR_ILLEGAL_QUERY -112
#define DG645_ERR_ILLEGAL_SET -113
#define DG645_ERR_NULL_PARAMETER -114
#define DG645_ERR_EXTRA_PARAMETERS -115
#define DG645_ERR_MISSING_PARAMETERS -116
#define DG645_ERR_PARAMETER_OVERFLOW -117
#define DG645_ERR_INVALID_FLOATING_POINT_NUMBER -118
#define DG645_ERR_INVALID_INTEGER -120
#define DG645_ERR_INTEGER_OVERFLOW -121
#define DG645_ERR_INVALID_HEXADECIMAL -122
#define DG645_ERR_SYNTAX_ERROR -126
#define DG645_ERR_COMMUNICATION_ERROR -170
#define DG645_ERR_OVER_RUN -171
#define DG645_ERR_TOO_MANY_ERRORS -254

#define DG645_ERR_UNKNOWN -256
#define DG645_ERR_UNEXPECTED_ANSWER -257
#define DG645_ERR_VALUE_OUT_OF_RANGE -258
#define DG645_ERR_OUT_OF_MEMORY -259
#define DG645_ERR_THREAD -260
#define DG645_ERR_CONTROLLER -261
#define DG645_ERR_CHANNEL -262
#define DG645_ERR_ILLEGAL_CHANNEL -263

enum DG645_HOOKS
{
	DG645_HOOK_STATE_CHANGE,
	DG645_HOOK_CONNECTION_START,
	DG645_HOOK_CONNECTION_STOP,
	DG645_HOOK_CONTROLLER_INIT,
	DG645_HOOK_CONTROLLER_DELETE,
	DG645_HOOKS_SIZE
};

namespace StanfordDG645Common_ns
{

const inline char *DG645ErrorMsgs(int err)
{
	const char *msgs_dev[] =
	{
		/*  0*/ "No Error",
		/*  1*/ "",
		/*  2*/ "",
		/*  3*/ "",
		/*  4*/ "",
		/*  5*/ "",
		/*  6*/ "",
		/*  7*/ "",
		/*  8*/ "",
		/*  9*/ "",
		/* 10*/ "Illegal Value",
		/* 11*/ "Illegal Mode",
		/* 12*/ "Illegal Delay",
		/* 13*/ "Illegal Link",
		/* 14*/ "Recall Failed",
		/* 15*/ "Not Allowed",
		/* 16*/ "Failed Self Test",
		/* 17*/ "Failed Auto Calibration",
		/* 18*/ "",
		/* 19*/ "",
		/* 20*/ "",
		/* 21*/ "",
		/* 22*/ "",
		/* 23*/ "",
		/* 24*/ "",
		/* 25*/ "",
		/* 26*/ "",
		/* 27*/ "",
		/* 28*/ "",
		/* 29*/ "",
		/* 30*/ "Lost Data",
		/* 31*/ "",
		/* 32*/ "No Listener",
		/* 33*/ "",
		/* 34*/ "",
		/* 35*/ "",
		/* 36*/ "",
		/* 37*/ "",
		/* 38*/ "",
		/* 39*/ "",
		/* 40*/ "Failed ROM Check",
		/* 41*/ "Failed Offset T0 Test",
		/* 42*/ "Failed Offset AB Test",
		/* 43*/ "Failed Offset CD Test",
		/* 44*/ "Failed Offset EF Test",
		/* 45*/ "Failed Offset GH Test",
		/* 46*/ "Failed Amplitude T0 Test",
		/* 47*/ "Failed Amplitude AB Test",
		/* 48*/ "Failed Amplitude CD Test",
		/* 49*/ "Failed Amplitude EF Test",
		/* 50*/ "Failed Amplitude GH Test",
		/* 51*/ "Failed FPGA Communications Test",
		/* 52*/ "Failed GPIB Communications Test",
		/* 53*/ "Failed DDS Communications Test",
		/* 54*/ "Failed Serial EEPROM Communications Test",
		/* 55*/ "Failed Temperature Sensor Communications Test",
		/* 56*/ "Failed PLL Communications Test",
		/* 57*/ "Failed DAC 0 Communications Test",
		/* 58*/ "Failed DAC 1 Communications Test",
		/* 59*/ "Failed DAC 2 Communications Test",
		/* 60*/ "Failed Sample and Hold Operations Test",
		/* 61*/ "Failed Vjitter Operations Test",
		/* 62*/ "Failed Channel T0 Analog Delay Test",
		/* 63*/ "Failed Channel T1 Analog Delay Test",
		/* 64*/ "Failed Channel A Analog Delay Test",
		/* 65*/ "Failed Channel B Analog Delay Test",
		/* 66*/ "Failed Channel C Analog Delay Test",
		/* 67*/ "Failed Channel D Analog Delay Test",
		/* 68*/ "Failed Channel E Analog Delay Test",
		/* 69*/ "Failed Channel F Analog Delay Test",
		/* 70*/ "Failed Channel G Analog Delay Test",
		/* 71*/ "Failed Channel H Analog Delay Test",
		/* 72*/ "",
		/* 73*/ "",
		/* 74*/ "",
		/* 75*/ "",
		/* 76*/ "",
		/* 77*/ "",
		/* 78*/ "",
		/* 79*/ "",
		/* 80*/ "Failed Sample and Hold Calibration",
		/* 81*/ "Failed T0 Calibration",
		/* 82*/ "Failed T1 Calibration",
		/* 83*/ "Failed A Calibration",
		/* 84*/ "Failed B Calibration",
		/* 85*/ "Failed C Calibration",
		/* 86*/ "Failed D Calibration",
		/* 87*/ "Failed E Calibration",
		/* 88*/ "Failed F Calibration",
		/* 89*/ "Failed G Calibration",
		/* 90*/ "Failed H Calibration",
		/* 91*/ "Failed Vjitter Calibration",
		/* 92*/ "",
		/* 93*/ "",
		/* 94*/ "",
		/* 95*/ "",
		/* 96*/ "",
		/* 97*/ "",
		/* 98*/ "",
		/* 99*/ "",
		/*100*/ "",
		/*101*/ "",
		/*102*/ "",
		/*103*/ "",
		/*104*/ "",
		/*105*/ "",
		/*106*/ "",
		/*107*/ "",
		/*108*/ "",
		/*109*/ "",
		/*110*/ "Illegal Command",
		/*111*/ "Undefined Command",
		/*112*/ "Illegal Query",
		/*113*/ "Illegal Set",
		/*114*/ "Null Parameter",
		/*115*/ "Extra Parameters",
		/*116*/ "Missing Parameters",
		/*117*/ "Parameter Overflow",
		/*118*/ "Invalid Floating Point Number",
		/*119*/ "",
		/*120*/ "Invalid Integer",
		/*121*/ "Integer Overflow",
		/*122*/ "Invalid Hexadecimal",
		/*123*/ "",
		/*124*/ "",
		/*125*/ "",
		/*126*/ "Syntax Error",
		/*127*/ ""
	};
	const char *msgs_ctrl[] =
	{
		/*256*/ "An unknown error occurred",
		/*257*/ "Received unexpected answer",
		/*258*/ "Value out of range",
		/*259*/ "Out of memory",
		/*260*/ "Thread error",
		/*261*/ "Controller device not found",
		/*262*/ "Invalid channel number",
		/*263*/ "Illegal action for channel 0"
	};

	switch(err)
	{
	case DG645_ERR_COMMUNICATION_ERROR:
		return /*170*/ "Communication Error";

	case DG645_ERR_OVER_RUN:
		return /*171*/ "Over run";

	case DG645_ERR_TOO_MANY_ERRORS:
		return /*254*/ "Too Many Errors";

	default:
		if(-err < 128)
			return msgs_dev[-err];
		else if(-err > 255 && -err < 264)
			return msgs_ctrl[-err-256];
	}
	return "";
}

}
#endif /* STANFORDDG645COMMON_H_ */
