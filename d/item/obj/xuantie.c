// xuantie.c 玄铁石

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(CYN "玄铁石" NOR, ({"xuan tie", "tie"}));
	set_weight(50000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一块黑黝黝有些泛光石头，掂在手中感到极为沉重，尤胜铜铁。\n");
		set("unit", "块");
		set("value", 30000);
                set("item_origin", 1);
                set("material_attrib", "steel");
                set("material_name", CYN "玄铁" NOR);
                set("can_make", "all");
                set("not_make", ({ "护甲", "战衣", "靴子", "腰带", "护腕" }));
                set("power_point", 70);
	}
}
