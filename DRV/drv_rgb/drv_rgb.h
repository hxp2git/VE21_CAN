/*
 * File:   drv_rgb.h
 * Author: Administrator
 *
 * Created on 2023��9��16��, ����8:13
 */

#ifndef DRV_RGB_H
#define DRV_RGB_H
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        COLOUR_LIGHT_PINK = 0xFFB6C1,          ///< 浅粉红
        COLOUR_PINK = 0xFFC0CB,                ///< 粉红
        COLOUR_CRIMSON = 0xDC143C,             ///< 深红/猩红
        COLOUR_LAVENDER_BLUSH = 0xFFF0F5,      ///< 淡紫红
        COLOUR_PALE_VIOLET_RED = 0xDB7093,     ///< 弱紫罗兰红
        COLOUR_HOY_PINK = 0xFF69B4,            ///< 热情的粉红
        COLOUR_DEEP_PINK = 0xFF1493,           ///< 深粉红
        COLOUR_MEDIUM_VIOLET_RED = 0xC71585,   ///< 中紫罗兰红
        COLOUR_ORCHID = 0xDA70D6,              ///< 暗紫色/兰花紫
        COLOUR_THISTLE = 0xD8BFD8,             ///< 蓟色
        COLOUR_PLUM = 0xDDA0DD,                ///< 洋李色/李子紫
        COLOUR_VIOLET = 0xEE82EE,              ///< 紫罗兰
        COLOUR_MAGENTA = 0xFF00FF,             ///< 洋红/玫瑰红
        COLOUR_FUCHSIA = 0xFF00FF,             ///< 紫红/灯笼海棠
        COLOUR_DARK_MAGENTA = 0x8B008B,        ///< 深洋红
        COLOUR_PURPLE = 0x800080,              ///< 紫色
        COLOUR_MEDIUM_ORCHID = 0xBA55D3,       ///< 中兰花紫
        COLOUR_DARK_VIOLET = 0x9400D3,         ///< 暗紫罗兰
        COLOUR_DARK_ORCHID = 0x9932CC,         ///< 暗兰花紫
        COLOUR_INDIGO = 0x4B0082,              ///< 靛青/紫兰色
        COLOUR_BLUE_VIOLET = 0x8A2BE2,         ///< 蓝紫罗兰
        COLOUR_MEDIUM_PURPLE = 0x9370DB,       ///< 中紫色
        COLOUR_MEDIUM_SLATE_BLUE = 0x7B68EE,   ///< 中暗蓝色/中板岩蓝
        COLOUR_SLATE_BLUE = 0x6A5ACD,          ///< 石蓝色/板岩蓝
        COLOUR_DARK_SLATE_BLUE = 0x483D8B,     ///< 暗灰蓝色/暗板岩蓝
        COLOUR_LAVENDER = 0xE6E6FA,            ///< 淡紫色/熏衣草淡紫
        COLOUR_GHOST_WRITE = 0xF8F8FF,         ///< 幽灵白
        COLOUR_BLUE = 0x0000FF,                ///< 纯蓝
        COLOUR_MEDIUM_BLUE = 0x0000CD,         ///< 中蓝色
        COLOUR_MIDNIGHT_BLUE = 0x191970,       ///< 午夜蓝
        COLOUR_DRAK_BLUE = 0x00008B,           ///< 暗蓝色
        COLOUR_NAVY = 0x000080,                ///< 海军蓝
        COLOUR_ROYAL_BLUE = 0x4169E1,          ///< 皇家蓝/宝蓝
        COLOUR_CORNFLOWER_BLUE = 0x6495ED,     ///< 矢车菊蓝
        COLOUR_LIGHT_STEE_BLUE = 0xB0C4DE,     ///< 亮钢蓝
        COLOUR_LIGHT_SLATE_GRAY = 0x778899,    ///< 亮蓝灰/亮石板灰
        COLOUR_SLATE_GRAY = 0x708090,          ///< 灰石色/石板灰
        COLOUR_DODGER_BLUE = 0x1E90FF,         ///< 闪兰色/道奇蓝
        COLOUR_ALICE_BLUE = 0xF0F8FF,          ///< 爱丽丝蓝
        COLOUR_STEEL_BLUE = 0x4682B4,          ///< 钢蓝/铁青
        COLOUR_LIGHT_SKY_BLUE = 0x87CEFA,      ///< 亮天蓝色
        COLOUR_SKY_BLUE = 0x87CEEB,            ///< 天蓝色
        COLOUR_DEEP_SKY_BLUE = 0x00BFFF,       ///< 深天蓝
        COLOUR_LIGHT_BLUE = 0xADD8E6,          ///< 亮蓝
        COLOUR_POWDER_BLUE = 0xB0E0E6,         ///< 粉蓝色/火药青
        COLOUR_CADET_BLUE = 0x5F9EA0,          ///< 军兰色/军服蓝
        COLOUR_AZURE = 0xF0FFFF,               ///< 蔚蓝色
        COLOUR_LIGHT_CYAN = 0xE0FFFF,          ///< 淡青色
        COLOUR_PALE_TURQYOISE = 0xAFEEEE,      ///< 弱绿宝石
        COLOUR_CYAN = 0x00FFFF,                ///< 青色
        COLOUR_DARK_TURQUOISE = 0x00CED1,      ///< 暗绿宝石
        COLOUR_DARK_SLATE_GRAY = 0x2F4F4F,     ///< 暗瓦灰色/暗石板灰
        COLOUR_DARK_CYAN = 0x008B8B,           ///< 暗青色
        COLOUR_TEAL = 0x008080,                ///< 水鸭色
        COLOUR_MEDIUM_TURQYOISE = 0x48D1CC,    ///< 中绿宝石
        COLOUR_LIGHT_SEA_GREEN = 0x20B2AA,     ///< 浅海洋绿
        COLOUR_TURQUOISE = 0x40E0D0,           ///< 绿宝石
        COLOUR_AQUAMARINE = 0x7FFFD4,          ///< 宝石碧绿
        COLOUR_MEDIUM_AQUAMARINE = 0x66CDAA,   ///< 中宝石碧绿
        COLOUR_MEDIUM_SPRING_GREEN = 0x00FA9A, ///< 中春绿色
        COLOUR_MINT_CREAM = 0xF5FFFA,          ///< 薄荷奶油
        COLOUR_SPRING_GREEN = 0x00FF7F,        ///< 春绿色
        COLOUR_MEDIUM_SEA_GREEN = 0x3CB371,    ///< 中海洋绿
        COLOUR_SEA_GREEN = 0x2E8B57,           ///< 海洋绿
        COLOUR_HONEYDEW = 0xF0FFF0,            ///< 蜜色/蜜瓜色
        COLOUR_LIGHT_GREEN = 0x90EE90,         ///< 淡绿色
        COLOUR_PALE_GREEN = 0x98FB98,
        COLOUR_DARK_SEA_GREEN = 0x8FBC8F,         ///< 暗海洋绿
        COLOUR_LIME_GREEN = 0x32CD32,             ///< 闪光深绿
        COLOUR_LIME = 0x00FF00,                   ///< 闪光绿
        COLOUR_FOREST_GREEN = 0x228B22,           ///< 森林绿
        COLOUR_GREEN = 0x008000,                  ///< 纯绿
        COLOUR_DARK_GREEN = 0x006400,             ///< 暗绿色
        COLOUR_CHARTREUSE = 0x7FFF00,             ///< 黄绿色/查特酒绿
        COLOUR_LAWN_GREEN = 0x7CFC00,             ///< 草绿色/草坪绿
        COLOUR_GREEN_YELLOW = 0xADFF2F,           ///< 绿黄色
        COLOUR_DARK_OLIVE_GREEN = 0x556B2F,       ///< 暗橄榄绿
        COLOUR_YELLOW_GREEN = 0x9ACD32,           ///< 黄绿色
        COLOUR_OLIVE_DRAB = 0x6B8E23,             ///< 橄榄褐色
        COLOUR_BEIGE = 0xF5F5DC,                  ///< 米色/灰棕色
        COLOUR_LIGHT_GOLDENROD_YELLOW = 0xFAFAD2, ///< 亮菊黄
        COLOUR_IVORY = 0xFFFFF0,                  ///< 象牙色
        COLOUR_LIGHT_YELLOW = 0xFFFFE0,           ///< 浅黄色
        COLOUR_YELLOW = 0xFFFF00,                 ///< 纯黄
        COLOUR_OLIVE = 0x808000,                  ///< 橄榄
        COLOUR_DARK_KHAKI = 0xBDB76B,             ///< 暗黄褐色/深卡叽布
        COLOUR_LEMON_CHIFFON = 0xFFFACD,          ///< 柠檬绸
        COLOUR_PALE_GOLDENROD = 0xEEE8AA,         ///< 灰菊黄/苍麒麟色
        COLOUR_KHANKI = 0xF0E68C,                 ///< 黄褐色/卡叽布
        COLOUR_GOLD = 0xFFD700,                   ///< 金色
        COLOUR_CORNSILK = 0xFFF8DC,               ///< 玉米丝色
        COLOUR_GOLDENROD = 0xDAA520,              ///< 金菊黄
        COLOUR_RARK_GOLDENROD = 0xB8860B,         ///< 暗金菊黄
        COLOUR_FLORAL_WHITE = 0xFFFAF0,           ///< 花的白色
        COLOUR_OLD_LACE = 0xFDF5E6,               ///< 老花色/旧蕾丝
        COLOUR_WHEAT = 0xF5DEB3,                  ///< 浅黄色/小麦色
        COLOUR_MOCCASIN = 0xFFE4B5,               ///< 鹿皮色/鹿皮靴
        COLOUR_ORANGE = 0xFF4400,                 ///< 橙色
        COLOUR_PAPAYA_WHIP = 0xFFEFD5,            ///< 番木色/番木瓜
        COLOUR_BLANCHED_ALMOND = 0xFFEBCD,        ///< 白杏色
        COLOUR_NAVAJO_WHITE = 0xFFDEAD,           ///< 纳瓦白/土著白
        COLOUR_ANTIQUE_WHITE = 0xFAEBD7,          ///< 古董白
        COLOUR_TAN = 0xD2B48C,                    ///< 茶色
        COLOUR_BURLY_WOOD = 0xDEB887,             ///< 硬木色
        COLOUR_BISQUE = 0xFFE4C4,                 ///< 陶坯黄
        COLOUR_DARK_ORANGE = 0xFF8C00,            ///< 深橙色
        COLOUR_LINEN = 0xFAF0E6,                  ///< 亚麻布
        COLOUR_PERU = 0xCD853F,                   ///< 秘鲁色
        COLOUR_PEACH_PUFF = 0xFFDAB9,             ///< 桃肉色
        COLOUR_SANDY_BROWN = 0xF4A460,            ///< 沙棕色
        COLOUR_CHOCOLATE = 0xD2691E,              ///< 巧克力色
        COLOUR_SADDLE_BROWN = 0x8B4513,           ///< 重褐色/马鞍棕色
        COLOUR_SEASHELL = 0xFFF5EE,               ///< 海贝壳
        COLOUR_SIENNA = 0xA0522D,                 ///< 黄土赭色
        COLOUR_LIGHT_SALMON = 0xFFA07A,           ///< 浅鲑鱼肉色
        COLOUR_CORAL = 0xFF7F50,                  ///< 珊瑚
        COLOUR_ORANGE_RED = 0xFF4500,             ///< 橙红色
        COLOUR_DARK_SALMON = 0xE9967A,            ///< 深鲜肉/鲑鱼色
        COLOUR_TOMATO = 0xFF6347,                 ///< 番茄红
        COLOUR_MISTY_ROSE = 0xFFE4E1,             ///< 浅玫瑰色/薄雾玫瑰
        COLOUR_SALMON = 0xFA8072,                 ///< 鲜肉/鲑鱼色
        COLOUR_SNOW = 0xFFFAFA,                   ///< 雪白色
        COLOUR_LIGHT_CORAL = 0xF08080,            ///< 淡珊瑚色
        COLOUR_ROSY_BROWN = 0xBC8F8F,             ///< 玫瑰棕色
        COLOUR_INDIAN_RED = 0xCD5C5C,             ///< 印度红
        COLOUR_RED = 0xFF0000,                    ///< 纯红
        COLOUR_BROWN = 0xA52A2A,                  ///< 棕色
        COLOUR_FIRE_BRICK = 0xB22222,             ///< 火砖色/耐火砖
        COLOUR_DARK_RED = 0x8B0000,               ///< 深红色
        COLOUR_MAROON = 0x800000,                 ///< 栗色
        COLOUR_WHITE = 0xFFFFFF,                  ///< 纯白
        COLOUR_WHITE_SMOKE = 0xF5F5F5,            ///< 白烟
        COLOUR_GAINSBORO = 0xDCDCDC,              ///< 淡灰色
        COLOUR_LIGHT_GREY = 0xD3D3D3,             ///< 浅灰色
        COLOUR_SILVER = 0xC0C0C0,                 ///< 银灰色
        COLOUR_DARK_GRAY = 0xA9A9A9,              ///< 深灰色
        COLOUR_GRAY = 0x808080,                   ///< 灰色
        COLOUR_DIM_GRAY = 0x696969,               ///< 暗淡灰
        COLOUR_BLACK = 0x000000,                  ///< 纯黑
    } DrvRgbColourEnum;
    typedef struct
    {
        uint8_t r_data;
        uint8_t g_data;
        uint8_t b_data;
    } DrvRgbDataStruct;

    typedef struct RgbStruct
    {
        DrvRgbDataStruct *drv_rgb_data;
        uint8_t rgb_length;
        void (*set_gpio_h)(void); ///< rgb高电平 600nsH 300nsL
        void (*set_gpio_l)(void); ///< rgb低电平 300nsH 600nsL
    } DrvRgbStruct;
    typedef struct
    {
        void (*set_gpio_h)(void);
        void (*set_gpio_l)(void);
        DrvRgbDataStruct *buf;
        uint8_t len;
    } DrvRgbDefInPutStruct;

    typedef struct
    {
        /**
         * @brief 运行功能函数
         * @param[in] void
         * @return None
         * @par self:  对象实体地址
         * @code
         * @endcode utf-8
         * @see :
         */
        void (*run)(DrvRgbStruct *self);
        /**
         * @brief 设置该对象的参数
         * @param[in] void
         * @return None
         * @par self:  对象实体地址
         * @par def_dat:  设置的数据地址
         * @code
         * @endcode utf-8
         * @see :
         */
        void (*set_def)(DrvRgbStruct *self, DrvRgbDefInPutStruct *def_dat);
        /**
         * @brief 获取颜色对应的RGB数据
         * @param[in] void
         * @return DrvRgbDataStruct: 返回颜色对应的RGB数据
         * @par colour_tab:  颜色
         * @code
         * @endcode utf-8
         * @see :
         */
        DrvRgbDataStruct (*get_colour_data)(DrvRgbColourEnum colour_tab);
    } DrvRgbInterfaceStruct;

    extern const DrvRgbInterfaceStruct g_drv_rgb_interface;

#ifdef __cplusplus
}
#endif

#endif /* DRV_RGB_H */
