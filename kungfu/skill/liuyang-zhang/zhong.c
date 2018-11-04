// Code of ShenZhou
// zhongfu.c
// modified by xuanyuan 29/07/2001
/*
虚竹叫道：“不错！”右掌挥舞，不绝向丁春秋进攻，左掌掌心中暗运内功，逆转北冥真气，不多时已将掌中酒
水化成七八片寒冰，右掌飕飕飕连拍三掌。
*/
#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	int sp, dp, i;
        object obj;

	if( !target ) target = offensive_target(me);

	if( !objectp(target) || target == me )
		return notify_fail("你要往谁身上种生死符？\n");

	if (target->query("not_living"))
		return notify_fail("看清楚了，那不是活人。\n");

        if (environment(target)->query("no_fight"))
                return notify_fail("你不能在这里攻击别人。\n");
	if (!objectp(obj=present("jiudai", me)))
            return notify_fail("你身上没有酒袋，不能化水为冰。\n");

	if( target->query("zf")) 
		return notify_fail("此人已经被种下生死符了！\n");

	if( me->query("family/family_name") != "灵鹫宫")
		return notify_fail("只有灵鹫宫的人才能种生死符！\n");

	if ((int)me->query_skill("xiaowuxiang", 1)<150
		&& (int)me->query_skill("bahuang-gong", 1)<150
		&& (int)me->query_skill("beiming-shengong", 1)<150)
		return notify_fail("你的所用内功心法不正确，或者功力不够，不能种生死符！\n");

	if ( me->query_skill_mapped("force") != "xiaowuxiang"
		&& me->query_skill_mapped("force") != "bahuang-gong"
		&& me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("你没有运用逍遥派系列内功！\n");	

        if( (int)me->query_skill("liuyang-zhang",1) < 150 )
                return notify_fail("你的天山六阳掌功力不够，不能种生死符！n");
                
        if ( me->query_skill_mapped("strike") != "liuyang-zhang")
                return notify_fail("你没有备天山六阳掌！\n"); 

        if( (int)me->query("neili",1) < 1000 )
		return notify_fail("你的内力不够，不能种生死符。\n");

	message_vision(
		WHT "$N突然从背后掏出一个酒袋，往自己掌心倒了些酒水。

$N左掌掌心中暗运内功，逆转真气，不多时已将掌中酒水化成七八片寒冰，右掌
蕴出一缕白线，猛地向$n的胸口射了过去！\n\n" NOR,
		me, target );

	if( !target->is_killing(me) ) target->kill_ob(me);

	sp = me->query_skill("force") + me->query_skill("dodge") + me->query_kar()*50;
	dp = target->query_skill("force") + target->query_skill("dodge") + me->query_kar()*50;
	sp *= me->query("combat_exp")/1000;
	dp *= target->query("combat_exp")/1000;
	

        if( random(sp) > random(dp) || !living(target))
	{
		tell_object(target, HIR "你只觉胸口一闷，一丝凉意直入肺腑，脑中一片空白茫然不知所措！\n" NOR);
		tell_object(me, HIG "你指间的白线闪电般刺入" + target->name() + "的胸口，看来已经种下生死符了。\n" NOR);
	
                target->set("zf",me->query("id"));
                target->apply_condition("zf_poison",12);
		target->set("zf_lv",me->query_skill("liuyang-zhang",1));
		target->receive_wound("qi",1,me);
		me->start_busy(random(10));
		target->add("jingli", -random(50));
		target->start_busy(random(3));
		me->add("neili", -125);
		me->add("jingli", -5);
	}
	else
	{	
		message_vision(HIY "可是$p看破了$P的企图，猛一运力把白线逼了回去。\n" NOR, me, target);
		tell_object(me, HIG "你觉得手指一阵冰凉，暗叫一声不好，赶经运功抵抗！\n" NOR); 
		me->add("jingli", -15);
		me->add("neili", -125);
		me->add("qi", -200);
		me->start_busy(random(10));
		
		}

	return 1;
}


