// qingtong-dun.c
// by dream

#include <armor.h>
#include <ansi.h>

 inherit DUNPAI;

void create()
{
        set_name(HIC "青铜之盾" NOR, ({ "qingtong dun", "dun" }));
        set("long", "这是一面纯青铜手工打造的精致青铜盾。\n");
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "dunpai");
                set("unit", "面");
                set("armor_prop/armor", 30);
                set("value", 1000000);
        }
        setup();
}

