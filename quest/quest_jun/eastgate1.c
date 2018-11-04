// Room: /d/xiangyang/eastgate1.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "青龙内门");
        set("long", 
"这里是襄阳城的东城门的内城门，只见城门上方是三个大字。近年来
蒙古屡次侵犯襄阳城，故这儿把守相当严密，一些官兵们正在盘查要离襄
阳城的人。两边是上城头的石阶，向西进入城区。\n\n"
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
    []==[]_|__|__|__|__|__|__| "HIG"青龙门"NOR" |__|__|__|__|__|__|_[]==[]
    []==[]__|__|__|__|__|__|_|        |__|__|__|__|__|__|_[]==[]
    []==[]_|__|__|__|__|__|__|        |_|__|__|__|__|__|__[]==[]\n\n"
);
        set("outdoors", "xiangyang");

        set("exits", ([
                "southup" : "/d/xiangyang/walle1",
                "northup" : "/d/xiangyang/walle2",
                "west"    : __DIR__"eastjie3",
                "east"    : __DIR__"eastgate2",
                "up"      : "/d/xiangyang/eastlou1",
        ]));
        set("objects", ([
                "/quest/quest5/job2/pi2"   : 1,
                "/d/xiangyang/npc/bing" : 2,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "up" && me->query_temp("guo_shoucheng/mark_jianlou") != 2)
                return notify_fail("守城士兵一把拦住你道：你没有得到郭大人的许可，不能上去！\n");

        return ::valid_leave(me, dir);
}

