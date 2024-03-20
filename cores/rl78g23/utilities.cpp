#include "wiring_private.h"
#include "wiring_variant.h"
#include "pins_arduino.h"
#include "pintable.h"
#include "r_cg_interrupt_handlers.h"

#define    ADS_TEMP_SENSOR            (0x80)
#define    ADS_REF_VOLTAGE            (0x81)

uint8_t g_u8ResetFlag;
uint8_t g_u8PowerManagementMode = PM_NORMAL_MODE;
uint8_t g_u8OperationClockMode = CLK_HIGH_SPEED_MODE;

extern uint8_t g_u8ResetFlag;
extern uint8_t g_u8PowerManagementMode;
extern uint8_t g_u8OperationClockMode;
extern volatile unsigned long g_u32delay_timer;

extern uint8_t g_delay_cnt_flg;
extern uint8_t g_delay_cnt_micros_flg;
extern volatile unsigned long g_u32delay_micros_timer;

extern uint16_t g_u16ADUL;
extern uint16_t g_u16ADLL;

volatile unsigned long g_u32timer_periodic = 0u;
#if 0
volatile unsigned long g_u32microtimer_periodic = 0u;
#endif

extern "C" {
#include "r_smc_entry.h"
// #include "Config_TAU0_7_MSTimer2.h"
}


// 周期起動ハンドラ関数テーブル
static struct {
    fITInterruptFunc_t afCyclicHandler;
    uint32_t au32CyclicTime;
    uint32_t au32RemainTime;
    uint32_t au32LastTime;
} g_CyclicHandlerTable[MAX_CYCLIC_HANDLER] = {
    {NULL, 0, 0, 0},
};
fITInterruptFunc_t    g_fITInterruptFunc = NULL;    //!< ユーザー定義インターバルタイマハンドラ

fInterruptFunc_t g_fMicroInterruptFunc = NULL;
#if 0
extern volatile unsigned long g_u32timer_periodic;

static void PeriodicMillisIntervalFunc()
{
    if (g_u32timer_periodic > 0) {
        if (g_fITInterruptFunc) {
            g_fITInterruptFunc(g_u32timer_periodic);
        }
        g_u32timer_periodic = 0;
    }
}
#endif

/**
 * タイマーアレイユニットの停止
 *
* @return なし
 *
 * @attention なし
 ***************************************************************************/
void _stopTAU0()
{
    // タイマ・アレイ・ユニットが動作しているか？
    if (TAU0EN != 0) {
        if (TE0 == 0x00000) {
#ifdef WORKAROUND_READ_MODIFY_WRITE
            CBI2(SFR2_PER0, SFR2_BIT_TAU0EN);// タイマ・アレイ・ユニットにクロック供
#else    /* WORKAROUND_READ_MODIFY_WRITE*/
            TAU0EN    = 0;               // タイマ・アレイ・ユニットにクロック供給停止
#endif
        }
    }
}

/**
 * タイマー周期の変更
 *
 * @param[in] u8Timer 変更するタイマ番号
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void _modifyTimerPeriodic(uint8_t u8TimerChannel, uint16_t u16Interval)
{
    switch (u8TimerChannel) {
    case 1:
        TDR01 = u16Interval;    // インターバル（周期）の設定
        break;

    case 2:
        TDR02 = u16Interval;    // インターバル（周期）の設定
        break;

    case 3:
        TDR03 = u16Interval;    // インターバル（周期）の設定
        break;

    case 4:
        TDR04 = u16Interval;    // インターバル（周期）の設定
        break;

    case 5:
        TDR05 = u16Interval;    // インターバル（周期）の設定
        break;

    case 6:
        TDR06 = u16Interval;    // インターバル（周期）の設定
        break;

    case 7:
        TDR07 = u16Interval;    // インターバル（周期）の設定
        break;
    }

}

/**
 * タイマーチャンネルの停止
 *
 * @param[in] u8Timer 停止するタイマ番号
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void _stopTimerChannel(uint8_t u8TimerChannel)
{
    TT0   |=  (1 << u8TimerChannel);    // タイマ動作停止
    TOE0 &=  ~(1 << u8TimerChannel);    // タイマ出力禁止の設定
    TO0   &= ~(1 << u8TimerChannel);    // タイマ出力の設定
    // 割り込みマスクを禁止に設定
    switch (u8TimerChannel) {
    case 1:    TMMK01  = 1; break;
    case 2:    TMMK02  = 1; break;
    case 3:    TMMK03  = 1; break;
    case 4:    TMMK04  = 1; break;
    case 5:    TMMK05  = 1; break;
    case 6:    TMMK06  = 1; break;
    case 7:    TMMK07  = 1; break;
    }
    if (!(TE0 & 0x009E)) {
        TT0 |= 0x0001;        // Master チャンネルの停止
    }
}

/**
 * Software Reset
 *
 * Generate software reset.
 *
 * @return なし
 *
 * @attention:  This function uses trap instruction.
 *              So RESF register in MCU is set to 0x80 after reset.
 *              Unable to use when using debugger.
 *
 ***************************************************************************/

void softwareReset(void) {
    __asm __volatile(" .byte 0xff");
}

/**
 * Get Reset Flag
 *
 * Get the flag why reset occur.
 *
 * @return 0x00: External reset or Power on reset
 *         0x01: Low voltage detection
 *         0x02: Illegal memory access
 *         0x04: RAM parity error ( read from no initialized area )
 *         0x10: Watch dog timer
 *         0x80: Illegal instruction
 *
 * @attention:
 *
 ***************************************************************************/

uint8_t getResetFlag() {
    return g_u8ResetFlag;
}

/**
 * RLduino78のバージョン情報を取得します。
 *
 * @return バージョン情報を返却します。
 *
 * @attention なし
 ***************************************************************************/
uint16_t getVersion()
{
    return RLDUINO78_VERSION;
}
#if defined(G22_FPB) || defined(G23_FPB)
#define USE_POWER_MANAGEMENT (1) // Set 1 when issue was solved. //KAD change from 0 to 1
#else
#define USE_POWER_MANAGEMENT (0) // Set 1 when issue was solved.
#endif // defined(G22_FPB) || defined(G23_FPB)

#if USE_POWER_MANAGEMENT == 1
/** @} group14 その他 */

/** ************************************************************************
 * @defgroup group15 パワーマネージメント/クロック制御関数
 *
 * @{
 ***************************************************************************/
/**
 * パワーマネージメントモードを取得します。
 *
 * 現在のパワーマネージメントモードを取得します。
 * - 通常モード：PM_NORMAL_MODE
 * - 省電力(HALT)モード：PM_HALT_MODE
 * - 省電力(STOP)モード：PM_STOP_MODE
 * - 省電力(SNOOZE)モード：PM_SNOOZE_MODE
 *
 * @return パワーマネージメントモードを返却します。
 *
 * @attention なし
 ***************************************************************************/
uint8_t getPowerManagementMode()
{
    return g_u8PowerManagementMode;
}

/**
 * パワーマネージメントモードを設定します。
 *
 * パワーマネージメントモードを設定します。
 * - 通常モード：PM_NORMAL_MODE
 * - 省電力(HALT)モード  ：PM_HALT_MODE
 * - 省電力(STOP)モード  ：PM_STOP_MODE
 * - 省電力(SNOOZE)モード：PM_SNOOZE_MODE
 *
 * パワーマネージメントモードに省電力(HALT/STOP/SNOOZE)モードを指定して delay()
 * 関数を呼び出すと、一時停止期間中はHALT/STOP命令によりスタンバイ状態になります。
 * また、パワーマネージメントモードに省電力(SNOOZE)モード指定して、 analogRead()
 * 関数を呼び出すと、SNOOZE状態になります。
 *
 * @param[in] u8PowerManagementMode パワーマネージメントモードを指定します。
 * @param[in] u16ADLL               A/D変換結果範囲の下限値を指定します。省略した場合デフォルト値（0）が設定されます。
 * @param[in] u16ADUL               A/D変換結果範囲の上限値を指定します。省略した場合デフォルト値（1023）が設定されます。
 *
 * @return なし
 *
 * @attention
 * - 動作クロックの状態によっては、パワーマネージメントモードが変更されない
 *   場合があります。
 * - A/D変換結果下限値/上限値には0から1023の範囲を指定してください。
 *   なお、下限値/上限値の下位2bitは無視されます。
 ***************************************************************************/
void setPowerManagementMode(uint8_t u8PowerManagementMode, uint16_t u16ADLL, uint16_t u16ADUL)
{

    switch (u8PowerManagementMode) {
    case PM_NORMAL_MODE:
    case PM_HALT_MODE:
        g_u16ADLL = 0;
        g_u16ADUL = 1023;
        g_u8PowerManagementMode = u8PowerManagementMode;
        break;

    case PM_STOP_MODE:
        if (CLS == 0) {
            g_u16ADLL = 0;
            g_u16ADUL = 1023;
            g_u8PowerManagementMode = u8PowerManagementMode;
        }
        break;

    case PM_SNOOZE_MODE:
        if ((CLS == 0) && (MCS == 0)) {
            if (u16ADLL > 1023) {
                u16ADLL = 1023;
            }
            if (u16ADUL > 1023) {
                u16ADUL = 1023;
            }
            if (u16ADLL > u16ADUL) {
                u16ADLL = 0;
                u16ADUL = 1023;
            }
            g_u16ADLL = u16ADLL;
            g_u16ADUL = u16ADUL;
            g_u8PowerManagementMode = u8PowerManagementMode;
        }
        break;

    default:
        break;
    }
}


/**
 * 動作クロックモードを取得します。
 *
 * CPU/周辺ハードウェアの動作クロックモードを取得します。
 * - 高速動作モード(高速オンチップ・オシレータ)：CLK_HIGH_SPEED_MODE
 * - 低速動作モード(XT1発信回路)               ：CLK_LOW_SPEED_MODE
 *
 * @return 動作クロックモードを返却します。
 *
 * @attention なし
 ***************************************************************************/
uint8_t getOperationClockMode()
{
    return g_u8OperationClockMode;
}


/**
 * 動作クロックを設定します。
 *
 * CPU/周辺ハードウェアの動作クロックを設定します。
 * - 高速動作モード(高速オンチップ・オシレータ)：CLK_HIGH_SPEED_MODE
 * - 低速動作モード(XT1発信回路)               ：CLK_LOW_SPEED_MODE
 *
 * 高速動作モードを指定すると、CPU/周辺ハードウェアに供給するクロックに
 * メイン・システム・クロック（高速オンチップ・オシレータ）を設定します。
 * 低速動作モードを指定すると、CPU/周辺ハードウェアに供給するクロックに
 * サブシステム・クロック（XT1発信回路）を設定します。
 *
 * @param[in] u8ClockMode 動作クロックを指定します。
 *
 * @return なし
 *
 * @attention
 * - パワーマネージメントモードが省電力(STOP/SNOOZE)の場合は低速動作モード
 *   を設定することができません。
 * - GR-KURUMIの場合、高速動作モード（CLK_HIGH_SPEED_MODE）を指定すると
 *   32 MHzで動作し、低速動作モード（CLK_LOW_SPEED_MODE）を指定すると 32.768
 *   kHzで動作します。
 ***************************************************************************/
void setOperationClockMode(uint8_t u8ClockMode)
{
    if (g_u8OperationClockMode == u8ClockMode)
    {
        // If there is no change from the existing mode, it will not be processed.
        return;
    }
    else
    if (u8ClockMode == CLK_HIGH_SPEED_MODE)
    {
        // The high-speed on-chip oscillator starts operating.
        R_BSP_StartClock (HIOCLK);
        // Switch to a high-speed on-chip oscillator.
        if (BSP_OK == R_BSP_SetClockSource (HIOCLK))
        {
            g_u8OperationClockMode = CLK_HIGH_SPEED_MODE;
        }
        else
        {
            /* not implementation */
        }
    }
    else
    if (u8ClockMode == CLK_LOW_SPEED_MODE)
    {
        // Stops the operation of the high-speed on-chip oscillator.
        R_BSP_StopClock (HIOCLK);
        // Switch to a low-speed on-chip oscillator.
        if (BSP_OK == R_BSP_SetClockSource (LOCLK))
        {
            g_u8OperationClockMode = CLK_LOW_SPEED_MODE;
        }
        else
        {
            /* not implementation */
        }
    }

}
/** @} group15 パワーマネージメント/クロック制御関数 */
#endif // USE_POWER_MANAGEMENT == 1


// *************************************************************************
// * @defgroup group16 割込みハンドラ/周期起動関数
//  *
//  * @{
//  **************************************************************************

/*
 * インターバル・タイマ割り込みハンドラ内から実行するコールバック関数を登録します。
 *
 * コールバック関数を登録すると1[ms]のインターバル・タイマ割り込み毎に登録した
 * コールバック関数が呼び出されます。また、コールバック関数呼び出し時にはシステム
 * 開始からの時間（ms）が引数として渡されます。
 *
 * @param[in] fFunction インターバル・タイマ割り込み時に実行するハンドラを指定します。
 *
 * @return なし
 *
 * @attention
 * - コールバック関数内では時間のかかる処理は行わないでください。
 * - コールバック関数内では以下の関数が呼び出し可能です。
 *
 * pinMode()、 digitalWrite()、 digitalRead()、 millis()、 micros()、 delayMicroseconds()、
 * min()、 max()、 constrain()、 map()、 lowByte()、 highByte()、 bitRead()、 bitWrite()、
 * bitSet()、 bitClear()、 bit()、 randomSeed()、 random()
 * - pinMode()関数と digitalWrite()関数は、 loop()関数内とコールバック関数内で同じピン
 * 番号を指定すると誤動作する可能性があります。
 ************************************************************************** */

void attachIntervalTimerHandler(void (*fFunction)(unsigned long u32Milles))
{
    g_fITInterruptFunc = fFunction;
}

/**
 * インターバル・タイマ割り込みハンドラ内から実行するコールバック関数の登録を解除します。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void detachIntervalTimerHandler()
{
    g_fITInterruptFunc = NULL;
}

void attachMicroIntervalTimerHandler(void (*fFunction)(void), uint16_t interval)
{
    (void)interval;  //Warning measures
    g_fMicroInterruptFunc = fFunction;
//    R_Config_TAU0_7_MSTimer2_Create();
//    R_Config_TAU0_7_MSTimer2_SetPeriod(interval);
//    R_Config_TAU0_7_MSTimer2_Start();
}

/**
 * 周期起動コールバック関数を登録します。
 *
 * 登録したコールバック関数は、u32CyclicTimeで指定した周期間隔[ms]で呼び出されます。
 * また、コールバック関数呼び出し時にはシステム開始からの時間(ms)が引数として渡されます。
 *
 * @param[in] u8HandlerNumber 周期起動コールバック関数の識別番号(0~7)を指定します。
 * @param[in] fFunction       インターバル・タイマ割り込み時に実行するハンドラを指定します。
 * @param[in] u32CyclicTime   周期起動する間隔[ms]を指定します。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void attachCyclicHandler(uint8_t u8HandlerNumber, void (*fFunction)(unsigned long u32Milles), uint32_t u32CyclicTime)
{
    if (u8HandlerNumber < MAX_CYCLIC_HANDLER) {
        detachCyclicHandler(u8HandlerNumber);
        g_CyclicHandlerTable[u8HandlerNumber].au32CyclicTime  = u32CyclicTime;
        g_CyclicHandlerTable[u8HandlerNumber].au32RemainTime = u32CyclicTime;
        g_CyclicHandlerTable[u8HandlerNumber].au32LastTime = millis();
        g_CyclicHandlerTable[u8HandlerNumber].afCyclicHandler = fFunction;
    }
}


/**
 * 周期起動コールバック関数の登録を解除します。
 *
 * @param[in] u8HandlerNumber 周期起動コールバック関数の識別番号( 0 ～ 7 )を指定します。
 *
 * @return なし
 *
 * @attention
 ***************************************************************************/
void detachCyclicHandler(uint8_t u8HandlerNumber)
{
    if (u8HandlerNumber < MAX_CYCLIC_HANDLER) {
        g_CyclicHandlerTable[u8HandlerNumber].afCyclicHandler = NULL;
        g_CyclicHandlerTable[u8HandlerNumber].au32CyclicTime  = 0;
        g_CyclicHandlerTable[u8HandlerNumber].au32RemainTime = 0;
        g_CyclicHandlerTable[u8HandlerNumber].au32LastTime = 0;
    }
}

extern "C" {
/**
 * 周期起動コールバック関数を起動します。
 *
 * @return なし
 *
 * @attention
 ***************************************************************************/
void execCyclicHandler(void)
{
    int i;

    for (i = 0; i < MAX_CYCLIC_HANDLER; i++) {
        if (g_CyclicHandlerTable[i].afCyclicHandler != NULL) {
            unsigned long currentTime = millis();
            unsigned long elapsedTime = currentTime - g_CyclicHandlerTable[i].au32LastTime;
            g_CyclicHandlerTable[i].au32LastTime = currentTime;
            bool exec = g_CyclicHandlerTable[i].au32RemainTime <= elapsedTime;
            g_CyclicHandlerTable[i].au32RemainTime -= elapsedTime;
            if (exec) {
                g_CyclicHandlerTable[i].au32RemainTime += g_CyclicHandlerTable[i].au32CyclicTime;
                g_CyclicHandlerTable[i].afCyclicHandler(currentTime);
            }
        }
    }
}

}
#if defined(G22_FPB) || defined(G23_FPB)
/**
 * MCUに内蔵されている温度センサから温度（摂氏/華氏）を取得します。
 *
 * @param[in] u8Mode 摂氏/華氏を指定します。
 *            @arg TEMP_MODE_CELSIUS    ： 摂氏
 *            @arg TEMP_MODE_FAHRENHEIT ： 華氏
  *
 * @return 温度を返却します。
 *
 ***************************************************************************/
int getTemperature(uint8_t u8Mode)
{
    extern volatile uint8_t  g_adc_int_flg;
    uint8_t u8count;
    uint16_t u16temp;
    uint16_t u16temp1; //温度センサ出力の値を入れる変数
    uint16_t u16temp2; //内部基準電圧出力の値を入れる変数
    int32_t s32Temp;
    int s16Result = 0;

    //温度センサ出力電圧で値を取得するためのレジスタの設定をします。
    R_Config_ADC_Set_TemperatureSensor();

    R_Config_ADC_Set_OperationOn();

    for (u8count = 0; u8count < 2; u8count ++)
    {
        g_adc_int_flg = 0;
        R_Config_ADC_Start();
        while(1)
        {
            if(g_adc_int_flg == 1)
            {
                R_Config_ADC_Get_Result_10bit(&u16temp);
                u16temp1 = u16temp;//温度センサ出力の値を入れる
                g_adc_int_flg = 0;
                break;
            }
        }
     }

    //内部基準電圧出力で値を取得します。
    R_Config_ADC_Set_InternalReferenceVoltage();
    R_Config_ADC_Set_OperationOn();

    for (u8count = 0; u8count < 2; u8count ++)
    {
        g_adc_int_flg = 0;
        R_Config_ADC_Start();
        while(1)
        {
            if(g_adc_int_flg == 1)
            {
                R_Config_ADC_Get_Result_10bit(&u16temp);
                u16temp2 = u16temp;//内部基準電圧出力の値を入れる
                g_adc_int_flg = 0;
                break;
            }
        }
    }

    //取得した値を使用し、温度を導きます。
    volatile long n14800L = 14800L;
    s32Temp = n14800L *u16temp1 / u16temp2 - 10500L;
    if (u8Mode == TEMP_MODE_FAHRENHEIT)
    {
        //華氏
        s16Result = s32Temp / -33 * 18 / 10;
        s16Result += 77;
    }
    else
    {
        //摂氏
        s16Result = s32Temp/ -33;
        s16Result += 25;
    }
    return s16Result;

}
#endif // defined(G22_FPB) || defined(G23_FPB)


void enterPowerManagementMode(unsigned long u32ms)
{
    uint8_t u8PMmode;

    /* Check the set power saving mode and the status of RL78,
       and determine the instruction that can be actually issued.
     */
    u8PMmode = g_u8PowerManagementMode;

    if (u32ms == 0xFFFFFFFF)
    {
//        ITLMK = 1;            // Mask Interval Timer
        /* When the interrupt of TML32 is masked and the mode is changed to STOP mode,
           the interrupt mask is not applied as a temporary measure because the
           implementation that clears ITLS0 to 0 has not been completed.
         */
        _STOP();
//        ITLMK = 0;            // Unmask Interval Timer
    }
    else
    {
        if (1U == g_delay_cnt_flg)
        {
            while (g_u32delay_timer < u32ms) {
                if (u8PMmode == PM_STOP_MODE) {
                    _STOP();
                }
                else if (u8PMmode == PM_HALT_MODE){
                    _HALT();
                }
                else
                {
                    NOP();
                }
            }
        }
        else
        if (1U == g_delay_cnt_micros_flg)
        {
            while (g_u32delay_micros_timer < u32ms) {
                if (u8PMmode == PM_STOP_MODE) {
                    _STOP();
                }
                else if (u8PMmode == PM_HALT_MODE){
                    _HALT();
                }
                else
                {
                    NOP();
                }
            }
        }
    }
}

/* リセット要因の読み出し */
void _readResetFlag()
{
    uint8_t resetflag;

    resetflag = RESF;
    RESF = 0x00;

    if(resetflag == 0x80)             /* 不正命令の実行によるリセット */
    {
        g_u8ResetFlag = 0x80;
    }
    else if(resetflag == 0x10)        /* ウォッチドックタイマによるリセット */
    {
        g_u8ResetFlag = 0x10;
    }
    else if(resetflag == 0x04)        /* RAMパリティエラーによるリセット */
    {
        g_u8ResetFlag = 0x04;
    }
    else if(resetflag == 0x02)        /* 不正メモリアクセスによるリセット */
    {
        g_u8ResetFlag = 0x02;
    }
    else if(resetflag == 0x01)        /* 低電圧検出によるリセット */
    {
        g_u8ResetFlag = 0x01;
    }
    else                              /* 外部リセットorパワーオンリセットによるリセット */
    {
        g_u8ResetFlag = 0x00;
    }

    return;
}

