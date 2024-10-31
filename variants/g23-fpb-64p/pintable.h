#ifndef _PINTABLE_H_
#define _PINTABLE_H_

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define getPortModeRegisterAddr(port)		    ((volatile uint8_t*)(ADDR_PORT_MODE_REG + port))			/*!< Base Address of Port Mode Register	*/
#define getPortPullUpRegisterAddr(port)		    ((volatile uint8_t*)(ADDR_PORT_PULL_UP_REG + port))			/*!< Base Address of Port Pull-up Register	*/
#define getPortInputModeRegisterAddr(port)	    ((volatile uint8_t*)(ADDR_PORT_IN_MODE_REG + port))			/*!< Base Address of Port Input Mode Register	*/
#define getPortOutputModeRegisterAddr(port)	    ((volatile uint8_t*)(ADDR_PORT_OUT_MODE_REG + port))		/*!< Base Address of Port Output Mode Register	*/
#define getPortRegisterAddr(port)		        ((volatile uint8_t*)(ADDR_PORT_REG + port))					/*!< Base Address of Port Register	*/

/* Add for G23 */
#define getPortModeControlARegisterAddr(port)	((volatile uint8_t*)(ADDR_PORT_MODE_CONTROL_A_REG + port))	/*!< Base Address of Port Mode Control-A Register	*/
#define getPortModeControlTRegisterAddr(port)	((volatile uint8_t*)(ADDR_PORT_MODE_CONTROL_T_REG + port))	/*!< Base Address of Port Mode Control-T Register	*/
#define getPortModeControlERegisterAddr(port)	((volatile uint8_t*)(ADDR_PORT_MODE_CONTROL_E_REG + port))	/*!< Base Address of Port Mode Control-E Register	*/
#define getPortOutCurControlRegisterAddr()		((volatile uint8_t*)(ADDR_PORT_OUT_CUR_CONTROL_REG))		/*!< Base Address of Port Output Current Control Register	*/
#define getPortDigInputDisRegisterAddr(port)	((volatile uint8_t*)(ADDR_PORT_DIG_INPUT_DIS_REG + port))	/*!< Base Address of Port Digital Input Disable Register	*/
/* Add for G23 */

typedef struct {
    uint8_t mask;
    uint8_t bit;
    uint8_t timer;  // currently no use for G23
    uint8_t pmca;
    /* Add for G23 */
    uint8_t pmct;
    uint8_t pmce;
    uint8_t ccde;
    uint8_t pdidis;
    uint8_t pm;
    uint8_t pu;
    uint8_t pim;
    uint8_t pom;
    /* Add for G23 */
    volatile uint8_t* portModeRegisterAddr;
    volatile uint8_t* portPullUpRegisterAddr;
    volatile uint8_t* portInputModeRegisterAddr;
    volatile uint8_t* portOutputModeRegisterAddr;
    volatile uint8_t* portRegisterAddr;
    /* Add for G23 */
    volatile uint8_t* portModeControlARegisterAddr;
    volatile uint8_t* portModeControlTRegisterAddr;
    volatile uint8_t* portModeControlERegisterAddr;
    volatile uint8_t* portOutCurControlRegisterAddr;
    volatile uint8_t* portDigInputDisRegisterAddr;
    /* Add for G23 */
} PinTableType;


#ifdef __cplusplus
};
#endif

#endif/*_PINTABLE_H_*/
