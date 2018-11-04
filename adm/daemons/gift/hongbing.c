// hongbing.c 肃州烘饼
// By Alf, Last Update 2001.10

#include <ansi.h>
inherit ITEM;

void init();
inherit F_FOOD;

void create()
{
    set_name(HIW"烘饼"NOR,({"hong bing", "bing" }));
    set_weight(50);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", "烘饼是西北一带出名的土产，弱似春绵，白如秋练，又软又脆。\n");
        set("unit", "块");
        set("value", 50);
        set("food_remaining", 8);
        set("food_supply", 40);
    }
}


