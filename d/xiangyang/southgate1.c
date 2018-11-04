// Room: /d/xiangyang/southgate1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "朱雀内门");
        set("long", 
"这里是襄阳城的南城门的内城门，只见城门上方是三个大字。因近年
来蒙古屡次侵犯襄阳城，故这儿把守相当严密，一些官兵们正在盘查要离
襄阳城的人。两边是上城头的石阶，向北进入城区。\n\n"
"                         s________________s         
                        /LLLLLLLLLLLLLLLLLL\\      
    []__[]             ^^||======||======||^^             []__[] 
    []==[]_[]__[]__[]__[]||[]__[]||[]__[]||[]__[]__[]__[]_[]==[]
    []==[]|__|__|__|__|__|__|┏━━━┓_|__|__|__|__|__|__[]==[]    
    []==[]__|__|__|__|__|__|_┃"HIY"襄阳城"NOR"┃__|__|__|__|__|__|_[]==[]  
    []==[]|__|__|__|__|__|__|┗━━━┛_|__|__|__|__|__|__[]==[]
    []==[]__|__|__|__|__|__|__/      \\|__|__|__|__|__|__|_[]==[]
    []==[]|__|__|__|__|__|__||        |__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__| "HIR"朱雀门"NOR" |__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]"
"\n\n");
        set("outdoors", "xiangyang");

        set("exits", ([
                "eastup" : __DIR__"walls2",
                "westup" : __DIR__"walls1",
                "south"  : __DIR__"southgate2",
                "north"  : __DIR__"southjie3",
        ]));
        set("objects", ([
                "/quest/quest5/job2/pi3"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        setup();
        replace_program(ROOM);
}

