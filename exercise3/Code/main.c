#include <STC15F2K60S2.h>
#include <system.h>


int main()
{
    SysInit();
    LatchCtrl(LED_ID, 0xFE);
    while (1)
    {
        /* code */
    }
}