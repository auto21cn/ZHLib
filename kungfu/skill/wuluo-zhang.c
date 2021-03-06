// wuluo-zhang.c 五罗轻烟掌
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action": "$N一掌轻出，一招「清风斜雨」直袭$n的$l，了无半点痕迹",
    "force" : 30,
    "dodge" : 30,
    "lvl"   : 0,
    "skill_name" : "清风斜雨",
    "damage_type": "瘀伤"
]),
([  "action": "$N转过身来，正是一招「垂钓江畔」，左脚轻点，右掌挥向$n的脸部",
    "force" : 50,
    "dodge" : 40,
    "damage": 5,
    "lvl"   : 10,
    "skill_name" : "垂钓江畔",
    "damage_type": "瘀伤"
]),
([  "action": "$N虚步侧身，一招「落叶雅意」，手腕一转，劈向$n",
    "force" : 60,
    "dodge" : 45,
    "damage": 10,
    "lvl"   : 20,
    "skill_name" : "落叶雅意",
    "damage_type": "瘀伤"
]),
([  "action": "$N一招「归路未晓」，双掌化作无数掌影，轻飘飘的拍向$n",    
    "force" : 70,
    "dodge" : 55,
    "damage": 15,
    "lvl"   : 34,
    "skill_name" : "归路未晓",
    "damage_type": "瘀伤"
]),
([  "action": "$N一招「春风拂柳」，左掌手指微微张开，拂向$n的手腕",
    "force" : 90,
    "dodge" : 70,
    "damage": 20,
    "lvl"   : 45,
    "skill_name" : "春风拂柳",
    "damage_type": "瘀伤"
]),
([  "action": "$N转身侧头，轻轻一笑，使出一招「逍遥世间」，一掌拍出，仿佛不食半点人间烟火",  
    "force" : 110,
    "dodge" : 75,
    "damage": 25,
    "lvl"   : 59,
    "skill_name" : "逍遥世间",
    "damage_type": "瘀伤"
]),
([  "action": "$N身形飘忽，一招「我心犹怜」，双掌软绵绵的拍向$n",
    "force" : 120,
    "dodge" : 80,
    "damage": 30,
    "lvl"   : 80,
    "skill_name" : "我心犹怜",
    "damage_type": "瘀伤"
]),
});

int valid_enable(string usage)
{
    	return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
    	return combo == "jinyu-quan";
}

mapping query_action(object me, object weapon)
{
        int i, j, pm, level;
       	object target;
	string *msg;

	level   = (int) me->query_skill("wuluo-zhang",1);
	pm = me->query_temp("piaomiao");
	target = me->select_opponent();
	weapon = me->query_temp("weapon");

	msg = ({ 
		HIM"\n$N脸色泛红，出招速突增快，一招快似一招。\n"NOR,
                HIW"\n$N左手掌散出的白烟突然转"NOR GRN"青"NOR HIW"，左手劲力也转化成另一种，两股内劲交错连击，威力渐增。\n"NOR,
                HIR"\n$N脸色渐渐转为暗红，身体四周由两股内劲所激发出的烟雾包围，双掌在烟雾中穿梭，所进招式也越增越多！\n"NOR,
                HBWHT BLK"\n只见$N脸上肌肉突然萎缩，形如枯木，身形灵动，出招速突陡然增快！\n"NOR,
	});

	if( pm > 1 && pm < 6 && !me->query_temp("piaomiao_attack")) {

		message_vision( msg[pm-2] , me, weapon);
		me->set_temp("piaomiao_attack", 1);
		for( j=0; j < pm-1; j++ )
		{
			me->add("neili", -50);
			COMBAT_D->do_attack(me, target, weapon);
		}
		me->delete_temp("piaomiao_attack", 1);
		me->add_temp("piaomiao", 1);

	}

        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int valid_learn(object me)
{
	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("wuluo-zhang", 1))
		return notify_fail("你的基本掌法火候有限，无法领会更高深的五罗轻烟掌。\n");

	return 1;
}

int practice_skill(object me)
{
    	if ((int)me->query("qi") < 50)
        	return notify_fail("你的体力太差了，不能练五罗轻烟掌。\n");

    	if ((int)me->query("neili") < 30)
        	return notify_fail("你的内力太差了，不能练五罗轻烟掌。\n");

    	me->receive_damage("qi", 40);
    	me->add("neili", -13);

    	return 1;
}
string perform_action_file(string action)
{
        return __DIR__"wuluo-zhang/" + action;
}

