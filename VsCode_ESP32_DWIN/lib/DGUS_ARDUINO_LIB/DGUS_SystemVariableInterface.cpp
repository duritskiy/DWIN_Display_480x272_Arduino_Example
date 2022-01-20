#include "DGUS_SystemVariableInterface.h"

bool DGUS_SystemVariableInterface::get_page(uint16_t &page)
{

    if (dgus.Read_RAM(dgus_CMDREG_PicGetPage, page))
    {
        page = swap_endian(page);
        return 1;
    }
    else
        return 0;
}

bool DGUS_SystemVariableInterface::set_page(uint16_t page)
{
    uint32_t cmd = PIC_SET_PAGE_BASE | page;
    cmd = swap_endian(cmd);
    return dgus.Write_VPs(dgus_CMDREG_PicSetPage, cmd);
}

bool DGUS_SystemVariableInterface::get_LedConfig(dgus_cmd_led_config &LedConfig)
{
    return dgus.Read_RAM(dgus_CMDREG_LedConfig, LedConfig);
}

bool DGUS_SystemVariableInterface::set_LedConfig(dgus_cmd_led_config &LedConfig)
{
    return dgus.Write_VPs(dgus_CMDREG_LedConfig, LedConfig);
}

bool DGUS_SystemVariableInterface::system_reset(uint8_t full_reset)
{
    int res = 0;
    if (full_reset)
        res = dgus.Write_VP_32Bit(dgus_CMDREG_SystemReset, DGUS_RESET_HARD);
    else
        res = dgus.Write_VP_32Bit(dgus_CMDREG_SystemReset, DGUS_RESET);

    uint32_t t1;
    t1 = millis();
    while (dgus.available_rx() == 0 && millis() - t1 < 1000)
        ;
    dgus.FlushRxBuffer();
    return res;
}

bool DGUS_SystemVariableInterface::get_system_config(dgus_cmd_system_config &config)
{
    return dgus.Read_RAM(dgus_CMDREG_SystemConfig, config);
}

bool DGUS_SystemVariableInterface::set_system_config(dgus_cmd_system_config &config)
{
    config.read_write_mode = 0x5A;
    return dgus.Write_VPs(dgus_CMDREG_SystemConfig, config);
}



bool DGUS_SystemVariableInterface::Setup_CRC_Mode(void)
{
    uint16_t page;
    if(!get_page(page))
    {
        dgus.CRC_Enable^=1;
        if(!get_page(page))
        {
            dgus.CRC_Enable^=1;
            return 0;
        }
    }
    
     return 1;
}