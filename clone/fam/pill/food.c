// 干粮

#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
    set_name(NOR + WHT "干粮" NOR, ({ "gan liang", "gan", "liang" }));
    set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
        set("long", NOR + WHT "这是一块便于携带的干粮。\n" NOR);
		set("unit", "块");
		set("value", 50);
		set("food_remaining", 20);
		set("food_supply", 500);
	}
}



