// huangjin-dun.c
// by dream

#include <armor.h>
#include <ansi.h>

inherit DUNPAI;

void create()
{
        set_name(HIY "黄金之盾" NOR, ({ "huangjin dun", "dun" }));
        set("long", "这是一面纯黄金手工打造的精致黄金盾。\n");
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "dunpai");
                set("unit", "面");
                set("armor_prop/armor", 90);
                set("value", 2000000);
        }
        setup();
}

