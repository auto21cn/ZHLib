// feng.c 破玉拳「封闭手」

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("破玉拳「封闭手」只能对战斗中的对手使用。\n");

	if (me->query_temp("weapon"))
		return notify_fail("只有空手才能使用破玉拳。\n");

	if (target->is_busy())
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
		
	if ((int)me->query_skill("poyu-quan", 1) < 80)
		return notify_fail("你的破玉拳法不够娴熟，不会使用「封闭手」。\n");

        if (me->query_skill_mapped("cuff") != "poyu-quan")
                return notify_fail("你没有激发破玉拳为拳法，无法使用「封闭手」。\n");

        if (me->query("neili") < 80)
                return notify_fail("你现在真气不够，无法使用「封闭手」。\n");

        msg = HIC "只见$N" HIC "左掌虚探，右拳飕的一声从掌风中"
              "猛穿过来，正是破玉拳法的绝招之一“封闭手”。\n" NOR;

        me->add("neili", -30);
        if (random(me->query_skill("cuff")) > (int)target->query_skill("force") / 2 || !living(target))
        {
		msg += HIR "结果$p" HIR "运力招架，一时却觉得"
                       "内力不济，被$P" HIR "抢住手腕一拉，顿时立足"
                       "不稳，滴溜溜打了两个圈子。\n" NOR;
		target->start_busy((int)me->query_skill("cuff") / 20 + 2);
	} else
        {
		msg += CYN "可是$p" CYN "奋力一架，硬生生格开了$P"
                       CYN "这一拳。\n" NOR;
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}
