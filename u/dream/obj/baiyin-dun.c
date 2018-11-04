// baiyin-dun.c
// by dream

#include <armor.h>
#include <ansi.h>

inherit DUNPAI;

void create()
{
        set_name(HIW "白银之盾" NOR, ({ "baiyin dun", "dun" }));
        set("long", "这是一面纯白银手工打造的精致白银盾。\n");
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "dunpai");
                set("unit", "面");
                set("armor_prop/armor", 60);
                set("value", 1500000);
        }
        setup();
}

