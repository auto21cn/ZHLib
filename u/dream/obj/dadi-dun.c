// dadi-dun.c
// by dream

#include <armor.h>
#include <ansi.h>

inherit DUNPAI;

void create()
{
        set_name(HIR "大地之岩石盾" NOR, ({ "dadi dun", "dun" }));
        set("long", "这是一面远古遗留下来的岩石盾，在它的上面遗留着奇异的真气。\n");
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "dunpai");
                set("unit", "面");
                set("armor_prop/armor", 200);
                set("wear_msg", HIR "只见一面血红的大地之岩石盾凭空出现在$N的手上，空气忽然凝重起来。\n" NOR);
        }
        setup();
}
mixed valid_damage(object me, object victim, int damage, object weapon)
{
        string result;
        if ( weapon )
                return damage*5/6;
        else {
                damage = damage/10;
                if (damage > 0)
                    me->receive_wound("qi", damage/10, victim);
                result = HIR"只见$N大叫一声急忙后退，可惜已被大地之岩石盾上面所附的奇异真气震的口吐鲜血。\n" NOR;
                result+= "( $N"+ COMBAT_D->eff_status_msg((int)me->query("qi")*100/(int)me->query("max_qi")) + " )\n";
                return ([ "result": result, "damage": damage+random(damage) ]);
        }
}

