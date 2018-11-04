// Code of ShenZhou
// Ryu, 11/20/96.
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIW"冰蚕"NOR, ({ "bing can"}) );
        set("race", "昆虫");
        set("subrace", "爬虫");
        set("age", 3);
        set("long", "这蚕虫纯白如玉，微戴青色。比寻常的蚕儿大了一倍有余，便如一条蚯蚓，身子透明直如水晶。\n");
        set("attitude", "peaceful");

//        set("limbs", ({ "头部", "身体", "触角", "前螯" }) );

        set("combat_exp", 900);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 6);
        set_temp("apply/armor", 1);

        set("insect_poison", ([
                "level"  : 200,
                "maximum": 80,
        ]));

        setup();
}