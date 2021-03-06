#include <ansi.h>
inherit QUARRY;

void create()
{
	set_name(NOR + CYN "鳄鱼" NOR, ({ "e yu", "e", "yu" }));
	set("long", CYN "这是一只体形庞大的鳄鱼，相当的凶猛。\n" NOR);

	set("age", 3);
	set("str", 35);
	set("dex", 50);
	set("max_qi", 3000);
	set("max_jing", 3000);
        set("neili", 2000);
        set("max_neili", 2000);
	set("combat_exp", 600000);

        set("power", 50);
        set("item1", __DIR__"item/eyurou");
        set("item2", __DIR__"item/eyupi");

        set_temp("apply/parry", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/defense", 60);
        set_temp("apply/unarmed_damage", 30);
        set_temp("apply/armor", 30);

	setup();
}
