// zhua.c 九阴神抓

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int damage;
	string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("九阴神抓只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("jiuyin-shengong", 1) < 120)
		return notify_fail("你的九阴神功还不够娴熟，不能使用九阴神抓。\n");
	                        
        if ((int)me->query("neili", 1) < 200)
		return notify_fail("你现在内力太弱，不能使用九阴神抓。\n");
			
	msg = HIY "$N" HIY "微微一笑，右手成爪，忽的抓向$n"
	      HIY "的要穴！\n" NOR;
	me->add("neili", -20);

        ap = me->query_skill("jiuyin-shengong", 1) * 3 / 2 +
             me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") +
             target->query_skill("martial-cognize", 1);

	me->want_kill(target);
        if (ap / 2 + random(ap ) > dp)
        {
		me->start_busy(2);
                me->add("neili", -180);
                damage = 0;

                if (me->query("max_neili") > target->query("max_neili") * 2)
                {
                        msg += HIR "$N" HIR "这一爪来势好快，正抓中$n"
			       HIR "的檀中大穴，$n" HIR
			       "一声惨叫，软绵绵的瘫了下去。\n" NOR;
                        damage = -1;
                } else
                {
        		target->start_busy(1 + random(3));
        
        		damage = ap + (int)me->query_skill("force");
                        damage = damage / 2 + random(damage / 2);
        		
                        if (arrayp(limbs = target->query("limbs")))
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";
                        pmsg = HIR "$n连忙腾挪躲闪，然而“扑哧”一声，$N"
			       HIR "五指正插入$n" HIR "的" + limb + "，$n"
			       HIR "一声惨叫，血溅五步。\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70, pmsg);
                }
	} else 
	{
		me->start_busy(2);
		msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的来势，接应得法，避开了这一抓。\n"NOR;
	}

	message_combatd(msg, me, target);
        if (damage < 0) target->die(me);

	return 1;
}
