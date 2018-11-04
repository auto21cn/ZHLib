// powerup.c 吸星大法加力

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用吸星大法来提升自己的战斗力。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        me->add("neili", -100);
        me->receive_damage("qi", 0);
        message_combatd(HIR "$N" HIR "一声冷笑，登时脸呈酱色，全身冒出缕缕"
                        "红色烟气，口中咝咝有声。\n" NOR, me);
        me->add_temp("apply/attack", skill * 4 / 8);
        me->add_temp("apply/parry", skill * 4 / 8);
        me->set_temp("powerup", 1);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me,
                           skill:), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("powerup"))
        {
                me->add_temp("apply/attack", -amount * 4 / 8);
                me->add_temp("apply/parry", -amount * 4 / 8);
                me->delete_temp("powerup");
                tell_object(me, "你的吸星大法运行完毕，将内力收回丹田。\n");
        }
}

