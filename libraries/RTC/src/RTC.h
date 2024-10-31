#ifndef RTC_H
#define RTC_H
/***************************************************************************/
/*    Include MCU depend defines.                                          */
/***************************************************************************/
#include <Arduino.h>
#include <utility/RLduino78_RTC.h>

extern "C"
{
#include "Config_RTC.h"
}

/***************************************************************************/
/*    Interrupt handler                                                    */
/***************************************************************************/


/***************************************************************************/
/*    Include Header Files                                                 */
/***************************************************************************/


/***************************************************************************/
/*    Macro Definitions                                                    */
/***************************************************************************/

#define PERIOD_TIME_NONE        0
#define PERIOD_TIME_HALFSEC     HALFSEC
#define PERIOD_TIME_ONESEC      ONESEC
#define PERIOD_TIME_ONEMIN      ONEMIN
#define PERIOD_TIME_ONEHOUR     ONEHOUR
#define PERIOD_TIME_ONEDAY      ONEDAY
#define PERIOD_TIME_ONEMON      ONEMONTH

/***************************************************************************/
/*    Type  Definitions                                                    */
/***************************************************************************/
/**
 * RTCクラス
 ***************************************************************************/
class RTCClass
{
private:

public:
    RTCClass();
    ~RTCClass();

    bool begin();
    bool end();
    bool setDateTime(int year, int mon, int day, int hour, int min, int sec, int week = RTC_WEEK_SUNDAY);
    bool getDateTime(int &year, int &mon, int &day, int &hour, int &min, int &sec, int &week);

    void attachAlarmHandler(void (*fFunction)(void));
    void setAlarmTime(int hour, int min, int week_flag = RTC_ALARM_EVERYDAY);
    void alarmOn();
    void alarmOff();

    void attachConstantPeriodHandler(void (*fFunction)(void));
    void constantPeriodOn(int cycle = PERIOD_TIME_ONESEC);
    void constantPeriodOff();
};

extern RTCClass RTC;

/***************************************************************************/
/*    Function prototypes                                                  */
/***************************************************************************/


/***************************************************************************/
/*    Global Variables                                                     */
/***************************************************************************/

extern "C"
{
extern voidFunc_t alarmUserCallback;
extern voidFunc_t periodTimeUserCallback;
}


/***************************************************************************/
/*    Local Variables                                                      */
/***************************************************************************/


/***************************************************************************/
/*    Global Routines                                                      */
/***************************************************************************/


/***************************************************************************/
/*    Local Routines                                                       */
/***************************************************************************/


/***************************************************************************/
/* End of module                                                           */
/***************************************************************************/
#endif /* RTC_H */

