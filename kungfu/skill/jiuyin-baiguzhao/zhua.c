// Code of JHSH
// Modified by haiyan@huaxia

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object report;
        int damage,lvl,lvl1,k,l,ap,dp;
        string str;

        if (!target ) target = offensive_target(me);

        if (!target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("「九阴神爪」只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你手中拿着武器，如何使出「九阴神爪」？\n");

        if ((lvl=(int)me->query_skill("jiuyin-baiguzhao",1))< 200)
                return notify_fail("你的九阴白骨爪修为不够。\n");

        if ((lvl1=(int)me->query_skill("cuixin-zhang",1))< 150)
                return notify_fail("你的摧心掌修为不够。\n");

        if (userp(me) && !me->query("can_perform/jiuyin-baiguzhao/shenzhao"))
                return notify_fail("你不会使用「九阴神爪」这个绝招！\n");

        if (me->query("jiali") < 50)
                return notify_fail("你的出手这么轻，又何必痛下杀手呢？\n");

        if (me->query("neili")<=lvl*4) return notify_fail("你的内力不够！\n");

        if (me->query("jingli")<=lvl) return notify_fail("你的精力不够！\n");

        message_vision(HIW "\n$N突然凌空虚劈一掌，右手疾伸。五根手指后发先至，带着嗤嗤的劲气扣向$n的天灵。\n\n" NOR, me,target);

        ap = me->query_skill("claw") + me->query_skill("force") + me->query_str()*10; 
        ap += me->query("jiali")*2/3;
        dp = target->query_skill("dodge") + target->query_skill("force") + target->query_con()*10; 

        me->add("neili", -lvl);
        if (!target->is_killing(me->query("id"))) target->kill_ob(me);

        //the accurate is decied by dex and used times and exp
        if (!living(target))
        {
                message_vision(HIR "只听噗的一声响，$N的五根手指已插入了$n的头顶。\n\n" NOR, me,target);
                target->die(me);
                return 1;
        }

        if (ap / 2 + random(ap) < dp ){  
                message_vision(CYN "$n自知无幸，不料$N功力尚浅，虽然一击命中，却已是强弩之末，再也无力按下去了。\n\n" NOR, me,target);
                me->start_busy(2);
                return 1;
        }

        if (ap / 2 + random(ap) > dp || !living(target)) 
        {
                damage = (lvl + lvl1)*2 + me->query_str()*me->query("jiali")*3/target->query_con();
                if (damage<=100) 
                        message_vision(BLU "$n心知此招厉害，竭力向后闪躲。虽是堪堪避过，早已惊出了一身冷汗。\n\n" NOR, me,target);
                else {
                        if ((int)damage >= target->query("eff_qi")) 
                        {
                                message_vision(HIR "只听噗的一声响，$N的五根手指已插入了$n的头顶。\n\n" NOR, me,target);
                                target->receive_wound("qi",1,me);
                                target->die(me);
                                return 1;
                        }
                        message_vision(MAG "$n心知此招厉害，竭力向后闪躲。虽然避过了天灵要害，脸上却给抓了五道血痕。\n\n" NOR, me,target);
                        target->receive_wound("qi",damage,me);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        message_vision("($N"+str+")\n", target);
                }
                target->start_busy(1+random(3));
                me->add("neili", -lvl);
                me->start_busy(4);
                return 1;
        }
        if (ap / 2 + random(ap) > dp * 3/2 || !living(target)){  
                damage=(2+random((me->query_str()*2+me->query("jiali"))/100))*lvl;
                if ((int)damage >= target->query("eff_qi")) {
                        message_vision(HIR "只听噗的一声响，$N的五根手指已插入了$n的头顶。\n\n" NOR, me,target);
                        target->die(me);
                        return 1;
                }
                if ((int)damage/target->query("eff_qi")*100>=50&&(int)damage/target->query("eff_qi")*100<100)
                        message_vision(HIR "只听唰的一声，$n的天灵盖已被扯下一大块头皮，顿时血流如注。\n\n" NOR, me,target);
                if ((int)damage/target->query("eff_qi")*100<50)
                        message_vision(HIR "只听哧的一声，$n的脑门已被抓出了五条鲜血淋漓的爪痕。\n\n" NOR, me,target);
                target->receive_wound("qi", damage, me);
                str = COMBAT_D->status_msg((int)target->query("eff_qi") * 100 /(int)target->query("max_qi"));
                message_vision("($N"+str+")\n", target);
                target->start_busy(1+random(3));
                me->add("neili", -lvl*2);
                me->start_busy(4);
                return 1;
        }
        message_vision(HIC "$n早有提防，从容地向后退了半步，便已避开了$N的致命一击！\n\n" NOR, me,target);
        tell_object(me, HIR"你奋力一击，只道就此得手。不想却被对手轻易闪过，背后登时露出了极大的空门。\n\n"NOR);
        me->start_busy(3+random(3));
        return 1;
}

