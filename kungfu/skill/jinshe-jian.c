// jinshe-jian.c

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([	"skill_name": "金光蛇影",
	"action": "$N使一招「金光蛇影」，手中的$w在一弹指间已向$n的$l连刺数剑",
	"force" : 190,
	"attack": 25,
	"dodge" : 20,
	"parry" : 10,
	"damage": 45,
	"damage_type": "刺伤"
]),
([	"skill_name": "蛇影万道",
	"action": "$N使一招「蛇影万道」，手中$w狂风骤雨般地向$n的$l连攻数剑",
	"force" : 220,
	"attack": 22,
	"dodge" : 10,
	"parry" : 20,
	"damage": 47,
	"damage_type": "刺伤"
]),
([	"skill_name": "雪地飞蛇",
	"action": "$N身形一转，陡地贴地跃起，手中$w灵动夭跃，一招「雪地飞蛇」疾刺$n的$l",
	"force" : 170,
	"attack": 26,
        "dodge" : 10,
        "parry" : 20,
	"damage": 45,
	"damage_type": "刺伤"
]),
([	"skill_name": "金蛇吞信",
	"action": "$N身形一转，一招「金蛇吞信」，手中的$w从左肋下向$n的$l戳了过去",
	"force" : 210,
	"attack": 18,
	"dodge" : 10,
	"parry" : 20,
	"damage": 52,
	"damage_type": "刺伤"
]),
([	"skill_name": "金蛇狂舞",
	"action": "$N手腕一抖，一招「金蛇狂舞」，$w挟著闪闪剑光，变幻无方逼向$n的$l",
	"force" : 180,
	"attack": 22,
	"dodge" : 10,
	"parry" : 20,
	"damage": 55,
	"damage_type": "刺伤"
]),
([	"skill_name": "灵蛇电闪",
	"action": "$N心念电闪手腕疾振处，一招「灵蛇电闪」，$w以无法形容的速度直射$n的$l",
	"force" : 250,
	"attack": 25,
	"dodge" : 10,
	"parry" : 20,
	"damage": 50,
	"damage_type": "刺伤"
]),
([	"skill_name": "蛇困愁城",
	"action": "$N身形一矮，一招「蛇困愁城」，手中的$w由下往上刺向$n的$l",
	"force" : 220,
	"attack": 24,
	"dodge" : 10,
	"parry" : 20,
	"damage": 45,
	"damage_type": "刺伤"
]),
([	"skill_name": "金蛇化龙",
	"action": "$N手中$w剑光暴长，一招「金蛇化龙」，如千年蛇蝎往$n$l咬去",
	"force" : 210,
	"attack": 31,
	"dodge" : 10,
	"parry" : 20,
	"damage": 60,
	"damage_type": "刺伤"
]),
});

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 700)
		return notify_fail("你的内力不够，没有办法练金蛇剑法。\n");

	if ((int)me->query_skill("force") < 90)
		return notify_fail("你的内功火候不够，没有办法练金蛇剑法。\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jinshe-jian", 1))
		return notify_fail("你的基本剑法水平有限，无法领会更高深的金蛇剑法。\n");

        return 1;
}

int valid_enable(string usage)
{
	return usage == "sword" || usage == "parry";
}

string query_skill_name(int level)
{
        return action[random(sizeof(action))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object ob;

	if (! (ob = me->query_temp("weapon")) ||
	    (string)ob->query("skill_type") != "sword")
		return notify_fail("你必须先找一把剑才能练剑法。\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("你的气不够，没有办法练习金蛇剑法。\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("你的内力不够，没有办法练习金蛇剑法。\n");

	me->receive_damage("qi", 50);
	me->add("neili", -48);
	return 1;
}

string *parry_msg = ({
        "$n不退反进，气走周天，手中的$v狠狠磕开了$N的$w。\n",
	"$n回剑自守，架住了$N的$w。\n",
	"$n手中的$v化作千百把，护住了全身。\n",
	"$n手中的$v自上削下，几乎将$N的$w削成两段。\n",
});

string *unarmed_parry_msg = ({
        "$n使动$v，在身前布起了一道铜墙铁壁，封住了$N的攻势。\n",
	"$n一抖手中的$v，护住了全身。\n",
	"$n将$v往地上一刺，$v反弹起来，刚好直刺$N的双臂。\n",
});

string query_parry_msg(object weapon)
{
        if (weapon)
                return parry_msg[random(sizeof(parry_msg))];
//        else
//                return unarmed_parry_msgrandom(sizeof(unarmed_parry_msg
}

string perform_action_file(string action)
{
        return __DIR__"jinshe-jian/" + action;
}
