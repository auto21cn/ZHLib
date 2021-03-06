// chan.c 日月鞭法「缠绕」诀

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int bs;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("牵制攻击只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "whip")
                return notify_fail("你没有拿着鞭子。\n");
                
        if (me->query_skill_mapped("force") != "hunyuan-yiqi" && 
            me->query_skill_mapped("force") != "yijinjing" && 
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong") 
                return notify_fail("你使用的非少林内功，无法施展「缠绕」诀！\n"); 

        if (me->query("neili") < 80)
                return notify_fail("你现在真气不够，无法施展「缠绕」诀！\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("你没有激发日月鞭法，无法施展「缠绕」诀！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，不必再施展「缠绕」诀！\n");

        msg = HIC "$N" HIC "使出日月鞭法「缠绕」诀，连挥数鞭企图把$n"
              HIC "的全身缠绕起来。\n";

        me->start_busy(1);
        bs = (int)me->query_skill("riyue-bian") / 20 + 2;
        if (bs > 8)  bs = 8;

        if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2)
        {
                msg += HIR "结果$p" HIR "被$P" HIR "攻了个措手不及！\n" NOR;
                target->start_busy(bs);
        } else {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企图，小心应对，并没有上当。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

