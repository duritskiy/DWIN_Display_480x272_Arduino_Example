#ifndef idgus_utilH
#define idgus_utilH
/**
 * @file dgus_util.h
 * @author Barry Carter
 * @date 01 Jan 2021
 * @brief DGUS II LCD Driver Utility functions
 */
// #include "dgus.h"
// #include "idgus_reg.h"
// #include <stddef.h>
// #include <stdint.h>
#include "utils/dgus_debug.h"


/* Base addresses and hard coded vars */
#define PIC_SET_PAGE_BASE ((uint32_t)0x5A010000) /**< Base address of the page change */
#define DGUS_RESET        ((uint32_t)0x55AA5AA5) /**< Magic reset command for the T5 */
#define DGUS_RESET_HARD   ((uint32_t)0x55AA5A5A) /**< Magic reset command for the T5 and all onboard periphs */



/**
 * @brief Layout of the VAR register
 *
 */
enum dgus_cmd_reg : uint16_t
{ // word sized registers
    dgus_CMDREG_DeviceId = 0x00,
    dgus_CMDREG_SystemReset = 0x04,
    dgus_CMDREG_OsUpdateCmd = 0x06,
    dgus_CMDREG_NorFlashRWCmd = 0x08,
    dgus_CMDREG_Reserved0C = 0x0C,
    dgus_CMDREG_Ver = 0x0F,
    dgus_CMDREG_Rtc = 0x10,
    dgus_CMDREG_PicGetPage = 0x14,
    dgus_CMDREG_GuiStatus = 0x15,
    dgus_CMDREG_TpStatus = 0x16,
    dgus_CMDREG_Reserved1A = 0x1A,
    dgus_CMDREG_Vcc = 0x30,
    dgus_CMDREG_Led = 0x31,
    dgus_CMDREG_Adc01 = 0x32,
    dgus_CMDREG_Reserved34 = 0x34,
    dgus_CMDREG_FolderName = 0x7C, // Max 8 chars like "DWIN_SET"
    dgus_CMDREG_SystemConfig = 0x80,
    dgus_CMDREG_LedConfig = 0x82,
    dgus_CMDREG_PicSetPage = 0x84,
    dgus_CMDREG_Pwm0Set = 0x86,
    dgus_CMDREG_Reserved88 = 0x88,
    dgus_CMDREG_Pwm0Out = 0x92,
    dgus_CMDREG_Reserved93 = 0x93,
    dgus_CMDREG_RTCSet = 0x9C,
    dgus_CMDREG_MusicPlaySet = 0xA0,
    dgus_CMDREG_BmpDownloadNotSupported = 0xA2,
    dgus_CMDREG_JpegDownload = 0xA6,
    dgus_CMDREG_NANDFlashRWCmd = 0xAA,
    dgus_CMDREG_TouchControl = 0xB0,
    dgus_CMDREG_SimTouchControl = 0xD4,
    dgus_CMDREG_PointerOverlay = 0xD8,
    dgus_CMDREG_ReservedDC = 0xDC,
    dgus_CMDREG_CrcMemoryCheck = 0xE0,
    dgus_CMDREG_ReservedE2 = 0xE2,
    dgus_CMDREG_MusicStreaming = 0xF0,
    dgus_CMDREG_PaintingInterface = 0xF4,
    dgus_CMDREG_DcsBusData = 0x100,
    dgus_CMDREG_Undefined200 = 0x200,
    dgus_CMDREG_Curve = 0x300,
    dgus_CMDREG_Reserved380 = 0x380,
};

#pragma pack(push, 1)
/**
 * @brief Layout of the music command register
 *
 * @return typedef struct
 */
typedef struct dgus_cmd_music
{
    uint8_t start_id;   /**< Start playback of the Wav Id */
    uint8_t section_id; /**< Play back on the segment id */
    uint8_t volume;     /**< Volume level to play 0-0x80 */
    uint8_t play_mode;  /**< 0 stop, 1 pause, 2 play */
} dgus_cmd_music;       /**< Music cmd */
#pragma pack(pop)



#pragma pack(push, 1)
/**
 * @brief Brightnedd LED configuration
 *
 * @return typedef struct
 */

typedef struct dgus_cmd_led_config
{
    uint8_t backlight_brightness_running; /* Brightness while not in idle (0...100) */
    uint8_t backlight_brightness_idle;    /* Brightness while in idle (0...100) */
    uint16_t_BigEndian dim_wait_multiple10ms;       /* Time before we idle /10ms */

 void Print(void)
    {
              debug_printf("dim_wait_multiple10ms=%d\n",  dim_wait_multiple10ms.Get_Swaped() );
              debug_printf("backlight_brightness_running=%d\n",  backlight_brightness_running);
              debug_printf("backlight_brightness_idle=%d\n",  backlight_brightness_idle);
    }

} dgus_cmd_led_config;                    /**< Led config */
#pragma pack(pop)



#pragma pack(push, 1)
/**
 * @brief System configuration information
 *
 * @return typedef struct
 */
typedef struct dgus_cmd_system_config
{                                       // 0x80
    uint8_t read_write_mode;            /**< 0x0 to read this register, 0x5A to write. Write data at your peril */
    uint8_t touch_panel_sensitivity_ro; /**< RO Current touchscreen sensitivility value */
    uint8_t touch_panel_mode_config_ro; /**< RO Touch Mode. Regular DGUS, raw or paint */
  
    unsigned int screen_orientation : 2;     /**< Current screen orientation. 0=0, 01 = 90, 10=180, 11=270 */  
    unsigned int backight_standby : 1;       /**< Enable or disbale backlight standby mode */
    unsigned int touch_audio_enabled : 1;    /**< Global audio control over button press audio */
  
    unsigned int var_auto_upload : 1;        /**< Global control over auto upload. Controls that auto-upload will be disabled) */
    unsigned int load_22_bin_ro : 1;         /**< RO Load the 22_.bin configuration file */
    unsigned int music_enabled : 1;          /**< Buzzer on (1)/off(0) */
    unsigned int crc_enabled : 1;            /**< Serial comms CRC Enabled */ 

    void Print(void)
        {
            if (this)
            {
                debug_printf("read_write_mode=%d\n", read_write_mode);
                debug_printf("touch_panel_sensitivity_ro=%d\n", touch_panel_sensitivity_ro);
                debug_printf("touch_panel_mode_config_ro=%d\n", touch_panel_mode_config_ro);
                debug_printf("crc_enabled=%d\n", (uint8_t)crc_enabled);
                debug_printf("music_enabled=%d\n", (uint8_t)music_enabled);
                debug_printf("load_22_bin_ro=%d\n", (uint8_t)load_22_bin_ro);
                debug_printf("var_auto_upload=%d\n", (uint8_t)var_auto_upload);
                debug_printf("touch_audio_enabled=%d\n", (uint8_t)touch_audio_enabled);
                debug_printf("backight_standby=%d\n", (uint8_t)backight_standby);
                debug_printf("screen_orientation=%u\n", (uint8_t)screen_orientation);
            }
        }

} dgus_cmd_system_config;            /**< sys config*/
#pragma pack(pop)

#endif