#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIG"天山神杖"NOR,({ "tianshan-shenzhang" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("material", "steel");
                set("long", "这是一根用特殊材料做成的乌黑手杖。\n");
        }
}

