// zhenwu.c 太极剑法「真武除邪」

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage, acter;

        if (userp(me) && ! me->query("can_perform/taiji-jian/zhenwu"))
                return notify_fail("你还不会使用「真武除邪」这一绝技。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「真武除邪」只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("taiji-jian", 1) < 160)
                return notify_fail("你的太极剑法不够娴熟，不会使用「真武除邪」。\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你现在真气不够，无法使用「真武除邪」。\n");

        if (me->query_skill_mapped("sword") != "taiji-jian") 
                return notify_fail("你没有激发太极剑法，无法使用「真武除邪」！\n");

        msg = HIY "$N" HIY "平平挥出一剑，横扫$n" HIY "。\n" NOR;

        me->add("neili", -50);

        dp = (target->query_skill("force", 1) +  
             target->query_skill("parry", 1) + 
             target->query_skill("martial-cognize", 1)) / 3; 

        if (me->query("character") == "光明磊落" || me->query("character") == "狡黠多变") 
             acter = 3; 
        else 
             acter = 4; 

        ap = (me->query_skill("taiji-shengong", 1) + 
             me->query_skill("taiji-jian", 1) + 
             me->query_skill("martial-cognize", 1) +  
             me->query_skill("taoism", 1)) / acter;  

        if (target->is_bad()) ap += ap / 10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap + random(ap / 3);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIY "结果$p" HIY "没有把它放在心上，随"
                                           "手应了一招，却见$P" HIY "剑势忽然一变"
                                           "，\n气象万千，变幻无穷，极具王者风范！\n"
                                           HIR "$p" HIR "惊慌失措，呆在当场，被$P"
                                           HIR "这一剑击中要害！鲜血崩流，惨不忍睹！\n" NOR);
                target->receive_damage("jing", damage / 3, me);
                target->receive_wound("jing", damage / 6, me);
                me->start_busy(2);
        } else
        {
                msg += HIG "可是$p" HIG "看破了$P" HIG "的企图，镇"
                       "定逾恒，全神应对自如。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}

