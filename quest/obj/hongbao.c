#include <ansi.h>
inherit ITEM;
void create()
{
    set_name( HIR "红包" NOR, ({ "hongbao" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "个");
            set("material", "cloth");
            set("long", "一个小小的红包，上面绣着：银钩赌场，黄\n");
          }
    setup();
}

