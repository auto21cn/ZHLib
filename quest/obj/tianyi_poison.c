#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW"天一神水"NOR, ({ "tianyi poison", "poison" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
        "这是一种无色，无味，奇毒无比的液体，可以滴在(di)在酒水之中害人。\n" );
                set("unit", "滴");
                set("base_value", 700);
                set("base_unit", "滴");
                set("base_weight", 30);
        }
}

