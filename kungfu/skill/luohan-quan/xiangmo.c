// xiangmo.c 罗汉降魔

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int damage;
	string msg;
        int ap, dp;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("「罗汉降魔」只能对战斗中的对手使用。\n");

	if ((int)me->query_skill("luohan-quan", 1) < 20)
		return notify_fail("你的罗汉拳法不够娴熟，现在还无法使用「罗汉降魔」。\n");

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你使用的非少林内功，无法施展「罗汉降魔」！\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("你现在真气不够，无法运用「罗汉降魔」。\n");
			
	if (me->query_skill_mapped("cuff") != "luohan-quan") 
		return notify_fail("你没有激发罗汉拳，无法使用罗汉降魔！\n");

	msg = HIY "$N" HIY "嗨的一声，一拳平平朝$n"
              HIY "打出，姿势有板有眼，颇具风范。\n" NOR;

        ap = me->query_skill("cuff");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp || !living(target))
	{
		damage = 60 + ap / 5 + random(ap / 5);
		me->add("neili", -30);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                           HIR "只见$n" HIR "一个招架失误，登时"
                                           "被这拳打了个正着，闷哼一声，退了一步。\n" NOR);
		me->start_busy(2);
                target->start_busy(1 + random(2));
	} else 
	{
		msg += CYN "可是$p" CYN "轻轻一格，架住了$P"
                       CYN "的来拳。\n" NOR;
		me->add("neili", -10);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
