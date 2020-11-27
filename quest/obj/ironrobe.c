#include <ansi.h>
#include <armor.h>
inherit CLOTH;
void create()
{
        set_name(CYN"铁甲袍"NOR, ({ "ironrobe" }) );
        set_weight(300000);
        if( clonep() )
                set_default_object(__FILE__);
        else {  
                set("long","一件极为沉重的铁制铠甲.\n"); 
                set("unit", "件");
                set("material", "steel");
                set("armor_prop/armor", 50);
                set("armor_prop/spells", 1);
        }
        setup();
}

