#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"突骑营"NOR);
        set("long", @LONG
这里就是「蒙古」突骑军大营，营内军马嘶鸣，尘土飞扬，蒙古军为了
南征，早已调派了最精锐的蒙古骑兵，看见蒙古军迅疾如风的冲锋阵列，不
由不让人心惊胆寒。
LONG
);

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */   
               "west"  :   __DIR__"mying4",
        ]));    

        set("objects", ([

        ]));
    
        setup();
        replace_program(ROOM);
}

