#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("矿石", ({"kuangshi"}));
        set_weight(2000);
                set("no_sell",1);
                set("unit","块");
                set("material","metal");
                set("list",0);
         set("changed",1);
                set("value",1);
                set("level",0);
                set("long","一块矿石，可能在某个地方可以提纯。\n");

       if( clonep() )
              set_default_object(__FILE__);
        setup();
}

