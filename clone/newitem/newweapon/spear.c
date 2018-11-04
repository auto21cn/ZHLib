// hammer.c

#include <weapon.h>

inherit SPEAR;

void create()
{
        set_name("枪", ({"spear"}));
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "这是一把长枪，枪尖略显毫光，");
                set("value", 500);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_spear(25);
        setup();
}

