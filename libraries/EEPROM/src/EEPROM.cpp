#include "Arduino.h"

extern "C"
{
    #include "utility/include/rfd/r_rfd.h"
    #include "utility/include/r_rfd_common_api.h"
    #include "utility/include/r_rfd_common_control_api.h"
    #include "utility/include/r_rfd_data_flash_api.h"

    #include "utility/eeprom_sub/include/eeprom_types.h"
    #include "utility/eeprom_sub/include/eeprom_defines.h"
    #include "utility/eeprom_sub/RL78_G23/config/eeprom_dataflash_config.h"
    #include "utility/eeprom_sub/include/eeprom_control_common.h"
}

#define E2END 0x1FFF
#define WRITE_DATA_BLOCK_SIZE 256
extern R_RFD_FAR_FUNC e_eeprom_ret_t CheckCFDFSeqEndSub(void);

uint8_t eeprom_read_byte(uint16_t& index  )
{
    uint8_t u8ReadData = 0;
    if((DFLCTL & 0xFFFE) == 0)
    {
        DFLCTL |= 0x0001;
        for(int i=0;i<10;i++)
        {
            NOP();
        }
    }
    index %= (E2END + 1);
    u8ReadData = *(uint8_t __far *)(DF_WRITE_ADDRESS + (index) );
    return u8ReadData;
}

/*********************************************************************************************************************/
/**
 *  Check the state of the code/data flash memory sequencer and result.
 *  
 *  @param[in]      -
 *  @return         Execution result status
 *                  - SAMPLE_ENUM_RET_STS_OK             : Successful completion
 *                  - SAMPLE_ENUM_RET_ERR_CFDF_SEQUENCER : CF/DF sequencer error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_ERASE      : Erase action error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_WRITE      : Write action error
 *                  - SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK : Blankcheck action error
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_eeprom_ret_t CheckCFDFSeqEndSub(void)
{
    /* Local variable definition */
    e_eeprom_ret_t l_e_sam_ret_value;
    uint8_t        l_u08_status_flag;
    
    /* Set local variables */
    l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK;
    
    /* Sequencer busy loop step1 */
    while (R_RFD_ENUM_RET_STS_BUSY == R_RFD_CheckCFDFSeqEndStep1())
    {
        /* No operation */
        /* It is possible to write the program for detecting timeout here as necessity requires */
    }
    
    /* Sequencer busy loop step2 */
    while (R_RFD_ENUM_RET_STS_BUSY == R_RFD_CheckCFDFSeqEndStep2())
    {
        /* No operation */
        /* It is possible to write the program for detecting timeout here as necessity requires */
    }
    
    /* Action error check */
    R_RFD_GetSeqErrorStatus(&l_u08_status_flag);
    
    /* Check error status */
    if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_CFDF_SEQUENCER))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_CFDF_SEQUENCER;
    }
    else if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_ERASE))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_ERASE;
    }
    else if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_WRITE))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_WRITE;
    }
    else if (EEPROM_VALUE_U08_MASK0_8BIT != (l_u08_status_flag & EEPROM_VALUE_U08_MASK1_FSQ_STATUS_ERR_BLANKCHECK))
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK;
    }
    else
    {
        /* Set return value */
        l_e_sam_ret_value = SAMPLE_ENUM_RET_STS_OK;
    }
    
    /* Clear sequencer registers */
    R_RFD_ClearSeqRegister();
    
    return (l_e_sam_ret_value);
}


/*********************************************************************************************************************/
/**
 *  Sample function for data flash control.
 *  BlankCheck -> Erase -> Write
 *  
 *  @param[in]      i_u32_data_addr : 
 *                    Command start address (The start address of the block)
 *  @param[in]      i_u16_write_data_length : 
 *                    Write data length (MAX : 1 block size)
 *  @param[in]      inp_u08_write_data : 
 *                    Write data pointer
 *  @return         Execution result status
 *                  - SAMPLE_ENUM_RET_STS_OK               : Successful completion
 *                  - SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED  : Mode mismatched error
 *                  - SAMPLE_ENUM_RET_ERR_CHECK_WRITE_DATA : Check write data error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_ERASE        : Erase command error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_WRITE        : Write command error
 *                  - SAMPLE_ENUM_RET_ERR_CMD_BLANKCHECK   : Blankcheck command error
 */
/*********************************************************************************************************************/
R_RFD_FAR_FUNC e_eeprom_ret_t DataFlashControlSub(uint32_t i_u32_data_addr, uint8_t inp_u08_write_data)
{
    /* Local variable definition */
    e_rfd_ret_t    l_e_rfd_ret_status;
    e_eeprom_ret_t l_e_sam_ret_status;
    e_eeprom_ret_t l_e_sam_ret_value;
    bool           l_e_sam_error_flag;
    uint8_t        l_u08_block_number;
    uint32_t       l_u32_check_write_data_addr;
    uint8_t        l_u08_block_erase = false;
    uint16_t       l_u16_count;
    uint16_t       l_u16_relative_addr;
    uint32_t       i_u32_start_addr;
    uint32_t       l_u32_write_data_addr;
    uint8_t        l_u8_temp_write_data;
    
    uint8_t* eeprom_data_buffer =  new uint8_t[WRITE_DATA_BLOCK_SIZE];

    if (eeprom_data_buffer == nullptr)
    {
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_ALLOCATE_MEMORY;
        return (l_e_sam_ret_value);
    }

    /* Set local variables */
    l_e_sam_ret_value           = SAMPLE_ENUM_RET_STS_OK;
    l_e_sam_error_flag          = false;
    
    /* This expression (actual block number) never exceeds the range of casting uint8_t */
    l_u08_block_number          = (uint8_t)((i_u32_data_addr - EEPROM_VALUE_U32_DF_BASE_ADDR) 
                                  >> EEPROM_VALUE_U08_SHIFT_ADDR_TO_BLOCK_DF);

    l_u32_check_write_data_addr = i_u32_data_addr;
    l_u16_relative_addr = (uint16_t)(i_u32_data_addr - DF_WRITE_ADDRESS - l_u08_block_number * 256);

    /* ERASE (1 block) */
    // need data copy before erase
    i_u32_start_addr = DF_WRITE_ADDRESS + l_u08_block_number * 256;

    if((DFLCTL & 0xFFFE) == 0)
    {
        DFLCTL |= 0x0001;
        for(int i=0;i<10;i++)
        {
            NOP();
        }
    }
    for(uint16_t i =0;i<256;i++)
    {
    	eeprom_data_buffer[i] = *(uint8_t __far *)(i_u32_start_addr+i);
    }
    eeprom_data_buffer[l_u16_relative_addr] = inp_u08_write_data;

    /******************************************************************************************************************
     * Enable data flash access
     *****************************************************************************************************************/
    R_RFD_SetDataFlashAccessMode(R_RFD_ENUM_DF_ACCESS_ENABLE);
    
    /******************************************************************************************************************
     * Set the data flash programming mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_DATA_PROGRAMMING);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
    /******************************************************************************************************************
     * BLANKCHECK -> ERASE
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
        /* BLANKCHECK (changed 1 block -> 1 byte) */
//        R_RFD_BlankCheckDataFlashReq(l_u08_block_number);
        R_RFD_BlankCheckDataFlashReq(i_u32_data_addr, DF_WRITE_DATA_LENGTH_1);
        l_e_sam_ret_status = CheckCFDFSeqEndSub();
        if (SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK == l_e_sam_ret_status)
        {
            // erase
            R_RFD_EraseDataFlashReq(l_u08_block_number);
            l_e_sam_ret_status = CheckCFDFSeqEndSub();
            
            if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
            {
                l_e_sam_error_flag = true;
                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_ERASE;
            }
            else
            {
                l_u08_block_erase = true;
                /* No operation */
            }
        }
        else if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
        {
            l_e_sam_error_flag = true;
            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_BLANKCHECK;
        }
        else
        {
            /* No operation */
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }
    
    /******************************************************************************************************************
     * WRITE
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
        if (false == l_u08_block_erase)
        {
            R_RFD_WriteDataFlashReq(i_u32_data_addr, &inp_u08_write_data);
            l_e_sam_ret_status = CheckCFDFSeqEndSub();
            if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
            {
                l_e_sam_error_flag = true;
                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_WRITE;
            }
            else
            {
                /* No operation */
            }
        }
        else  // need one block data (256Bytes) write
        {
            for (l_u16_count = 0u; l_u16_count < 256; l_u16_count++)
            {
                l_u32_write_data_addr = i_u32_start_addr + l_u16_count;
                if(eeprom_data_buffer[l_u16_count] != 0xFF)
                {
                    l_u8_temp_write_data = eeprom_data_buffer[l_u16_count];
                    R_RFD_WriteDataFlashReq(l_u32_write_data_addr, &l_u8_temp_write_data);
                    l_e_sam_ret_status = Eeprom_CheckCFDFSeqEnd();
                    if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
                    {
                        l_e_sam_error_flag = true;
                        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_WRITE;
                        break;
                    }
                    else
                    {
                        /* No operation */
                    }
                }
            }
        }

    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }
    
    /******************************************************************************************************************
     * Set non-programmable mode
     *****************************************************************************************************************/
    l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_UNPROGRAMMABLE);
    
    if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
    {
        l_e_sam_error_flag = true;
        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
    }
    else
    {
        /* No operation */
    }
    /******************************************************************************************************************
     * Check write data
     *****************************************************************************************************************/
    if (false == l_e_sam_error_flag)
    {
        if (inp_u08_write_data != (*(uint8_t __far *)l_u32_check_write_data_addr))
        {
            l_e_sam_error_flag = true;
            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CHECK_WRITE_DATA;
        }
        else
        {
            /* No operation */
        }
    }
    else /* true == l_e_sam_error_flag */
    {
        /* No operation */
    }
    /******************************************************************************************************************
     * Disable data flash access
     *****************************************************************************************************************/
    R_RFD_SetDataFlashAccessMode(R_RFD_ENUM_DF_ACCESS_DISABLE);
    delete[] eeprom_data_buffer;
    return (l_e_sam_ret_value);
}


void eeprom_write_byte( uint16_t& index, uint8_t value )
{
    /* Local variable definition */
    e_rfd_ret_t    l_e_rfd_status_flag;
    uint32_t       l_mclk_freq;

    /* Disable RAM parity error reset. */
    RPERDIS = 1u;

    l_mclk_freq = R_BSP_GetFclkFreqHz();
    l_mclk_freq = (l_mclk_freq + L_MCLK_ROUNDUP_VALUE)/L_MCLK_FREQ_1MHz;

    /* Check whether HOCO is already started */
    if (EEPROM_VALUE_U01_MASK0_1BIT == HIOSTOP)
    {
        /* Initialize RFD */
        l_e_rfd_status_flag = R_RFD_Init((uint8_t)l_mclk_freq);

        if (R_RFD_ENUM_RET_STS_OK == l_e_rfd_status_flag)
        {
            index %= (E2END + 1);
            /* Data flash blankcheck, erase, and write */
            DataFlashControlSub((DF_WRITE_ADDRESS + index), value);
        }
        else
        {
            /* Failed to initialize RFD */
        }
    }
    else
    {
        /* HOCO is not started */
    }
    return;
}

R_RFD_FAR_FUNC e_eeprom_ret_t DataFlashMultipleByteWrite(uint32_t i_u32_data_addr,  uint16_t i_u16_write_data_length, const uint8_t  *ptr )
{
       /* Local variable definition */
        e_rfd_ret_t    l_e_rfd_ret_status;
        e_eeprom_ret_t l_e_sam_ret_status;
        e_eeprom_ret_t l_e_sam_ret_value;
        bool           l_e_sam_error_flag;
        uint8_t        l_u08_block_number;
        uint8_t        l_u08_block_erase = false;
        uint16_t       l_u16_count;
        uint32_t       i_u32_start_addr;
        uint32_t       l_u32_write_data_addr;
        uint8_t        l_u8_temp_write_data;
        uint8_t        l_au08_write_block_index;

        uint8_t* eeprom_data_buffer =  new uint8_t[WRITE_DATA_BLOCK_SIZE];

        if (eeprom_data_buffer == nullptr)
        {
            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_ALLOCATE_MEMORY;
            return (l_e_sam_ret_value);
        }

        /* Set local variables */
        l_e_sam_ret_value           = SAMPLE_ENUM_RET_STS_OK;
        l_e_sam_error_flag          = false;

        /* This expression (actual block number) never exceeds the range of casting uint8_t */
        l_u08_block_number          = (uint8_t)((i_u32_data_addr - EEPROM_VALUE_U32_DF_BASE_ADDR)
                                      >> EEPROM_VALUE_U08_SHIFT_ADDR_TO_BLOCK_DF);

        l_au08_write_block_index = (uint8_t)(i_u32_data_addr % WRITE_DATA_BLOCK_SIZE);

        // need data copy before erase
        i_u32_start_addr = DF_WRITE_ADDRESS + l_u08_block_number * 256;

        for(uint16_t i =0;i<256;i++)
        {
        	eeprom_data_buffer[i] = *(uint8_t __far *)(i_u32_start_addr+i);
        }
        for(uint16_t i = 0; i < i_u16_write_data_length ; ++i)
        {
            eeprom_data_buffer[(uint8_t)(l_au08_write_block_index+i)] = *ptr++;
        }


        /******************************************************************************************************************
         * Enable data flash access
         *****************************************************************************************************************/
        R_RFD_SetDataFlashAccessMode(R_RFD_ENUM_DF_ACCESS_ENABLE);

        /******************************************************************************************************************
         * Set the data flash programming mode
         *****************************************************************************************************************/
        l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_DATA_PROGRAMMING);

        if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
        {
            l_e_sam_error_flag = true;
            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
        }
        else
        {
            /* No operation */
        }
        /******************************************************************************************************************
         * BLANKCHECK -> ERASE
         *****************************************************************************************************************/
        if (false == l_e_sam_error_flag)
        {
            /* BLANKCHECK (changed 1 block) */
            R_RFD_BlankCheckDataFlashReq(i_u32_data_addr,i_u16_write_data_length);

            l_e_sam_ret_status = CheckCFDFSeqEndSub();
            if (SAMPLE_ENUM_RET_ERR_ACT_BLANKCHECK == l_e_sam_ret_status)
            {
                // erase
                R_RFD_EraseDataFlashReq(l_u08_block_number);
                l_e_sam_ret_status = CheckCFDFSeqEndSub();

                if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
                {
                    l_e_sam_error_flag = true;
                    l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_ERASE;
                }
                else
                {
                    l_u08_block_erase = true;
                    /* No operation */
                }
            }
            else if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
            {
                l_e_sam_error_flag = true;
                l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_BLANKCHECK;
            }
            else
            {
                /* No operation */
            }
        }
        else /* true == l_e_sam_error_flag */
        {
            /* No operation */
        }

        /******************************************************************************************************************
         * WRITE
         *****************************************************************************************************************/
        if (false == l_e_sam_error_flag)
        {
            if (false == l_u08_block_erase)
            {
                for(uint16_t i = 0; i < i_u16_write_data_length ; ++i)
                {
                    l_u8_temp_write_data = eeprom_data_buffer[(uint8_t)(l_au08_write_block_index+i)];
                    R_RFD_WriteDataFlashReq(i_u32_data_addr+i, &l_u8_temp_write_data);
                    l_e_sam_ret_status = CheckCFDFSeqEndSub();
                    if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
                    {
                        l_e_sam_error_flag = true;
                        l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_WRITE;
                    }
                    else
                    {
                        /* No operation */
                    }
                }
            }
            else  // need one block data (256Bytes) write
            {
                for (l_u16_count = 0u; l_u16_count < 256; l_u16_count++)
                {
                    l_u32_write_data_addr = i_u32_start_addr + l_u16_count;
                    if(eeprom_data_buffer[l_u16_count] != 0xFF)
                    {
                        l_u8_temp_write_data = eeprom_data_buffer[l_u16_count];
                        R_RFD_WriteDataFlashReq(l_u32_write_data_addr, &l_u8_temp_write_data);
                        l_e_sam_ret_status = Eeprom_CheckCFDFSeqEnd();
                        if (SAMPLE_ENUM_RET_STS_OK != l_e_sam_ret_status)
                        {
                            l_e_sam_error_flag = true;
                            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_CMD_WRITE;
                            break;
                        }
                        else
                        {
                            /* No operation */
                        }
                    }
                }
            }

        }
        else /* true == l_e_sam_error_flag */
        {
            /* No operation */
        }

        /******************************************************************************************************************
         * Set non-programmable mode
         *****************************************************************************************************************/
        l_e_rfd_ret_status = R_RFD_SetFlashMemoryMode(R_RFD_ENUM_FLASH_MODE_UNPROGRAMMABLE);

        if (R_RFD_ENUM_RET_STS_OK != l_e_rfd_ret_status)
        {
            l_e_sam_error_flag = true;
            l_e_sam_ret_value  = SAMPLE_ENUM_RET_ERR_MODE_MISMATCHED;
        }
        else
        {
            /* No operation */
        }

        /******************************************************************************************************************
         * Disable data flash access
         *****************************************************************************************************************/
        R_RFD_SetDataFlashAccessMode(R_RFD_ENUM_DF_ACCESS_DISABLE);
        delete[] eeprom_data_buffer;
        return (l_e_sam_ret_value);
}


void eeprom_write_block( uint16_t& index, uint16_t i_u16_write_data_length, const uint8_t *ptr )
{
    /* Local variable definition */
    e_rfd_ret_t    l_e_rfd_status_flag;
    uint32_t       l_mclk_freq;

    /* Disable RAM parity error reset. */
    RPERDIS = 1u;

    l_mclk_freq = R_BSP_GetFclkFreqHz();
    l_mclk_freq = (l_mclk_freq + L_MCLK_ROUNDUP_VALUE)/L_MCLK_FREQ_1MHz;

    /* Check whether HOCO is already started */
    if (EEPROM_VALUE_U01_MASK0_1BIT == HIOSTOP)
    {
        /* Initialize RFD */
        l_e_rfd_status_flag = R_RFD_Init((uint8_t)l_mclk_freq);
        
        if (R_RFD_ENUM_RET_STS_OK == l_e_rfd_status_flag)
        {
            index %= (E2END + 1);
            /* Data flash blankcheck, erase, and write */
            DataFlashMultipleByteWrite((DF_WRITE_ADDRESS + index), i_u16_write_data_length, ptr );
        }
        else
        {
            /* Failed to initialize RFD */
        }
    }
    else
    {
        /* HOCO is not started */
    }
    return;
}

