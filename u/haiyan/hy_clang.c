:// hy_clang.c 
#include <ansi.h>
inherit ROOM; 
void create() 
{ 
     set("short", "长  廊"); 
     set("long", @LONG 
这里是后院的一条弯弯曲曲的长廊，两边不时能听到阵阵鸟儿在
啾啾鸣叫，竹林在微风中摇曳，小溪淙淙流淌。北面隐约可见到一片
花园，你不禁加快了脚步。
LONG); 
     set("exits", ([ 
         "south"    : __DIR__"hy_houyuan",  
         "north"    : __DIR__"hy_hy01",
     ])); 
     set("no_sleep_room", "1"); 
     setup(); 
}

int valid_leave(object me, string dir)
{
    if (! userp(me) && dir == "south")
        return notify_fail("闲人免进。\n");
    return ::valid_leave(me, dir);
}

