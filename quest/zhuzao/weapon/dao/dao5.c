#include <weapon.h>
#include <ansi.h>
inherit BLADE;
void create()
{
        set_name(RED"烈焰刀"NOR, ({ "lieyan dao", "dao", "lieyan", "blade" }) );        
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
           set("value", 80000);
           set("treasure",1);
           set("wield_neili", 100);
           set("wield_maxneili", 1000);
           set("wield_str", 22);
           set("unit", "把");
           set("long", RED"此刀刀面如有火光流动，刀鞘上镶著“烈焰”两个古篆，乃是明教的镇教宝物，平时都供奉在光明宝塔之内。\n"NOR);
           }
        init_blade(300);
        setup();
}

