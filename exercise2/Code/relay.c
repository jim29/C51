#include <relay.h>
#include <global.h>


/*
 *		打开继电器到m2,灯亮
 *
 */
 void Relay_m2()
 {
	 LatchCtrl(ULN_ID, 0x10);
 }


/*
 *		打开继电器到m1,灯灭
 *
 */
  void Relay_m1()
 {
	 LatchCtrl(ULN_ID, 0x00);
 }
