//create by huarong 2004/2
//万能兵器  参见perform.c  huarong 2004/2
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("十八玲珑玉", ({"eighteen weapon", "eighteen", "weapon"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 100);
                set("unbreak", 1);
                set("material", "wood");
                set("long", "这是十八玲珑玉，是练武时用的。\n");
                set("wield_msg", "$N抽出一把$n握在手中。\n");
                set("unequip_msg", "$N将手中的$n别入腰后．\n");
        }
        init_sword(30);
        setup();
}

