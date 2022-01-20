#ifndef dgus_display_textH
#define dgus_display_textH

#include "Arduino.h"
#include "display/dgus_display.h"
#include "idgusWidget.h"
#include "utils/dtostrf.h"

#pragma pack(push, 1)
typedef struct dgus_display_Text_SPData
{
    uint16_t_BigEndian VP;
    dgus_control_position Pos;
    uint16_t_BigEndian Color;
    dgus_control_size size;
    uint16_t_BigEndian text_len;
    uint8_t font_0_id;
    uint8_t font_1_id;

    /*
    Font width, in pixels. Must be even. In encoding modes 0x01 -0x04,
    must be twice the Width. Must be more 4.
    */
    uint8_t font_x_dots;
    uint8_t font_y_dots; // Font height, in pixels. Must be even.
    union
    {
        uint8_t encode_mode;
        struct
        {
            /*
            Font encoding:
            0: 8bit
            1: GB2312
            2: GBK
            3: BIG5
            4: SJIS
            5: UNICODE
            */
            unsigned int encode_mode_Font_encoding : 7;
            /*
                Character spacing mode is defined
                0: Automatic spacing.
                1: Fixed spacing.
            */
            unsigned int encode_mode_SpacingMode : 1;
        };
    };
    uint8_t hor_distance;
    uint8_t ver_distance;
    uint8_t reserved0;

    void Print(void)
    {
        if (this)
        {
            debug_printf("VP=0x%04X\n", VP.Get_Swaped());
            debug_printf("Pos.x=%d\n", Pos.x.Get_Swaped());
            debug_printf("Pos.y=%d\n", Pos.y.Get_Swaped());
            debug_printf("Color=0x%04X\n", Color.Get_Swaped());
            debug_printf("size.x_top=%d\n", size.x_top.Get_Swaped());
            debug_printf("size.y_top=%d\n", size.y_top.Get_Swaped());
            debug_printf("size.x_bottom=%d\n", size.x_bottom.Get_Swaped());
            debug_printf("size.y_bottom=%d\n", size.y_bottom.Get_Swaped());
            debug_printf("text_len=%d\n", text_len.Get_Swaped());
            debug_printf("font_0_id=%d\n", font_0_id);
            debug_printf("font_1_id=%d\n", font_1_id);
            debug_printf("font_x_dots=%d\n", font_x_dots);
            debug_printf("font_y_dots=%d\n", font_y_dots);
            debug_printf("encode_mode=0x%02X\n", encode_mode);
            debug_printf("hor_distance=%d\n", hor_distance);
            debug_printf("ver_distance=%d\n", ver_distance);
        }
    }

} dgus_display_Text_SPData; /**< Register layout for the text SP register */
#pragma pack(pop)

enum dgus_display_TextENUM
{
    AS_TEXT,
    AS_NUMBER
};

/*
SP Data Size = 29bytes = 0x1D
*/
template <unsigned int LengthOfText, dgus_display_TextENUM As> 
class dgus_display_Text
{

  public:
    idgusWidget<char[LengthOfText + 1], dgus_display_Text_SPData> Regs;

  private:
    char *FloatToString(char *buf, int bufSize, double value, signed char FloatStringLength, unsigned char NumAfterPoint, const char *Units)
    {
        FloatStringLength = MIN(bufSize, FloatStringLength);
        int UnitsLength = MIN(bufSize - FloatStringLength, strlen(Units));

        // uint32_t t = micros();
        _dtostrf(value, FloatStringLength, NumAfterPoint, buf);
        // t = micros() - t;
        // debug_printf("t=%d\n", t);
        // strncpy(buf+FloatStringLength, Units, UnitsLength);

        return buf;
    }

    void SetFFto00(void)
    {
        for (size_t i = 0; i < Regs.VP_Data_Size; i++)
        {
            if (Regs.VP_DataAs.String[i] == 0xFF) {Regs.VP_DataAs.String[i] = 0; break;}
        }
    }

  public:
    int32_t GetAsINT32()
    {
        int32_t value = INT32_MIN;
        SetFFto00();
        sscanf(Regs.VP_DataAs.String, "%ld", &value);
        return value;
    }

    bool WriteAsINT32(int32_t value)
    {
        if (Regs.VP_DataAs.String)
        {
            memset(Regs.VP_DataAs.String, 0, Regs.VP_Data_Size);
            snprintf(Regs.VP_DataAs.String, Regs.VP_Data_Size, "%ld", value);
            // return Regs.VP_Write();
            return Regs.dgus.Write_VPs(Regs.VP, (uint8_t *)Regs.VP_DataAs.String, Regs.VP_Data_Size - 1);
        }
        else
        {
            // Regs.VP_DataAs.String = new char[Regs.VP_Data_Size];
            memset(Regs.VP_DataAs.String, 0, Regs.VP_Data_Size);
            snprintf(Regs.VP_DataAs.String, Regs.VP_Data_Size, "%ld", value);
            // bool result = Regs.VP_Write();
            bool result = Regs.dgus.Write_VPs(Regs.VP, (uint8_t *)Regs.VP_DataAs.String, Regs.VP_Data_Size - 1);
            // Regs.VP_Data_Free();
            return result;
        }
    }

    float GetAsFloat()
    {
        // float value = -infinityf();
        float value = 0;
        SetFFto00();
        if (Regs.VP_DataAs.String) sscanf(Regs.VP_DataAs.String, "%f", &value);
        return value;
    }

    bool WriteAsFloat(double value)
    {
        if (Regs.VP_DataAs.String)
        {
            memset(Regs.VP_DataAs.String, 0, Regs.VP_Data_Size);
            FloatToString(Regs.VP_DataAs.String, Regs.VP_Data_Size, value, 8, 3, "mm");
            return Regs.dgus.Write_VPs(Regs.VP, (uint8_t *)Regs.VP_DataAs.String, Regs.VP_Data_Size - 1);
        }
        else
        {
            // Regs.VP_DataAs.String = new char[Regs.VP_Data_Size];
            memset(Regs.VP_DataAs.String, 0, Regs.VP_Data_Size);
            // debug_printf("\nvalue=%f\n", value);
            FloatToString(Regs.VP_DataAs.String, Regs.VP_Data_Size - 1, value, 10, 0, "");
            // debug_printf("Regs.VP_DataAs.String=%s\n", Regs.VP_DataAs.String);
            // bool result = Regs.VP_Write();
            bool result = Regs.dgus.Write_VPs(Regs.VP, (uint8_t *)Regs.VP_DataAs.String, Regs.VP_Data_Size - 1);

            // debug_printf("\nRegs.VP_Data=%d %d \n", (int)Regs.VP_DataAs.String,(int)&Regs.VP_DataAs.String);
            // Regs.VP_Data_Free();
            // debug_printf("Regs.VP_Data=%d\n", (int)Regs.VP_DataAs.String);
            return result;
        }

        return 0;
    }

    char *GetAsText(void)
    {
        SetFFto00();        
        return Regs.VP_DataAs.String; 
        
    }

    bool Read(void)
    {
        // debug_printf("r=%d\n", r);

        if ( Regs.VP_Read())
        {
            // Regs.VP_DataAs.String = new char[Regs.VP_Data_Size];
            // memset(Regs.VP_DataAs.String, 0, Regs.VP_Data_Size);
            SetFFto00();
            Regs.VP_DataAs.String[Regs.VP_Data_Size - 1] = 0;
            // return Regs.VP_DataAs.String;
            return 1;
        }
        return 0;
    }

    bool WriteAsText(const char *str)
    {
        bool result;
        uint8_t strLength = strlen(str);
        strLength = MIN(Regs.VP_Data_Size - 1, strLength);

        if (Regs.VP_DataAs.String)
        {
            memset(Regs.VP_DataAs.String, 0, Regs.VP_Data_Size);
            strncpy(Regs.VP_DataAs.String, str, strLength);
            result = Regs.dgus.Write_VPs(Regs.VP, (uint8_t *)Regs.VP_DataAs.String, Regs.VP_Data_Size - 1);
        }
        else
        {
            // Regs.VP_DataAs.String = new char[Regs.VP_Data_Size];
            memset(Regs.VP_DataAs.String, 0, Regs.VP_Data_Size);
            strncpy(Regs.VP_DataAs.String, str, strLength);
            result = Regs.dgus.Write_VPs(Regs.VP, (uint8_t *)Regs.VP_DataAs.String, Regs.VP_Data_Size - 1);
            // Regs.VP_Data_Free();
        }

        return result;
    }

    dgus_display_Text(DwinT5LProtocol &_dgus, uint16_t _VP, uint16_t _SP): 
    Regs(_dgus, _VP, _SP)
    {
     //   Regs.dgus.addByteArea(Regs.dgus.ID, _VP, &Regs.VP_Data);
        
        --Regs.VP_Data_Size;
        if(As==AS_TEXT) Regs.dgus.ListText.Add((idgusWidget<uint16_t, void>*)&Regs);
        if(As==AS_NUMBER)  Regs.dgus.ListTextAsNum.Add((idgusWidget<uint16_t, void>*)&Regs);

    };
    ~dgus_display_Text()
    {
        // Regs.VP_Data_Free();
        Regs.SP_Data_Free();
    };
};

#endif