// backleg.c

#include <weapon.h>

inherit HAMMER;
inherit F_FOOD;

void create()
{
        set_name("烤猪腿", ({ "back leg", "tui" }) );
        set_weight(350);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一只烤得香喷喷的野猪后腿。\n");
                set("unit", "根");
                set("value", 80);
                set("food_remaining", 4);
                set("food_supply", 15);
                set("wield_msg", "$N抓起一根$n，握在手中当武器。\n");
                set("material", "bone");
        }
        init_hammer(1);
        setup();
}

int finish_eat()
{
        if( !query("weapon_prop") ) return 0;
        set_name("啃得精光的猪腿骨头", ({ "bone" }) );
        set_weight(150);
        set("long", "一根啃得精光的猪腿骨头。\n");
        return 1;
}

