// bamboo_sword.c

#include <weapon.h>

inherit SWORD;

void create()
{
        set_name( "纪念品" ,({ "jinian pin", "jinin", "pin" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("material", "bamboo");
                set("long", "这里画着〖地狱〗社社长「就是无聊没事干」风狐(wfoxd)。
可以看到他英俊潇洒，气宇轩昂，风度翩翩，面目俊朗，貌似潘安。\n" );
                set("wield_msg", "$N从腰间慢慢地拿出一张$n，轻轻地握在手中。\n" );
                set("unequip_msg","$N随意的把$n放 在腰间。\n" );
        }
        init_sword(1);
        setup();
}

