//huifeng-jian.c 回风拂柳剑
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "skill_name" : "清风袭月",
        "action": "$N剑尖剑芒暴长，一招「清风袭月」，手中$w自左下大开大阖，"
                  "一剑向右上向$n的$l",
        "force" : 100,
        "attack": 15,
        "dodge" : 5,
        "damage": 30,
        "lvl"   : 0,
        "damage_type" : "刺伤"
]),
([      "skill_name" : "飘雪穿云",
        "action": "$N长剑圈转，一招「飘雪穿云」，手中$w平展下刺，一剑轻轻划"
                  "过$n的$l",
        "force" : 120,
        "attack": 19,
        "dodge" : 10,
        "damage": 40,
        "lvl"   : 20,
        "damage_type" : "刺伤"
]),
([      "skill_name" : "千峰竞秀",
        "action": "$N长剑轻灵跳动，剑随身长，右手$w使出一式「千峰竞秀」刺向$n的$l",
        "force" : 150,
        "attack": 21,
        "dodge" : 10,
        "damage": 50,
        "lvl"   : 40,
        "damage_type" : "刺伤"
]),
([      "skill_name" : "万流归宗",
        "action": "$N长剑下指，剑意流转，一招「万流归宗」直取$n的$l",
        "force" : 170,
        "attack": 25,
        "dodge" : 10,
        "damage": 55,
        "lvl"   : 60,
        "damage_type" : "刺伤"
]),
([      "skill_name" : "乌龙搅柱",
        "action": "$N剑芒吞吐，幻若灵蛇，右手$w使出一式「乌龙搅柱」，剑势曼妙，"
                  "刺向$n的$l",
        "force" : 200,
        "attack": 34,
        "dodge" : 10,
        "damage": 60,
        "lvl"  : 90,
        "damage_type" : "刺伤"
]),
([      "skill_name" : "大雁啼沙",
        "action": "$N屈腕云剑，剑光如彩碟纷飞，幻出点点星光，右手$w使出一式"
                  "「大雁啼沙」跃跃洒洒飘向$n的$l",
        "force" : 230,
        "attack": 37,
        "dodge" : 15,
        "damage": 65,
        "lvl"   : 100,
        "damage_type" : "刺伤"
]),
([      "skill_name" : "进退龙游",
        "action": "$N挥剑分击，剑势自胸前跃出，右手$w一式「进退龙游」，毫无"
                  "留恋之势，刺向$n的$l",
        "force" : 250,
        "attack": 41,
        "dodge" : 15,
        "lvl"   : 110,
        "damage": 65,
        "damage_type" : "刺伤"
]),
([      "skill_name" : "天地鹤翔",
        "action": "$N退步，左手剑指划转，腰部一扭，右手$w一记「天地鹤翔」自下"
                  "而上刺向$n的$l",
        "force" : 275,
        "attack": 45,
        "dodge" : 25,
        "damage": 70,
        "lvl"   : 120,
        "damage_type" : "刺伤"
]),
});

int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 200)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的内功火候太浅。\n");

        if (me->query_skill("sword", 1) < me->query_skill("huifeng-jian"))
                return notify_fail("你的基本剑法水平有限，无法领会更高深的回风剑。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

string *juejian_msg = ({ 
	"蓦地里$N$w疾闪，青光闪处，剑尖已指到了$n$l，恰似雷震电掣，剑招狠辣之极",
	"$N$w一晃，径往$n$l削去，剑势夭矫飞舞，忽分忽合，有如天神行法，凌厉无端",
	"却见$N飘身而上，半空中举剑上挑，剑光已封住了$n身周数尺之地，攻得精巧无比",
	"$N纵前抢攻，剑势如风，剑招愈来愈奇，$w颤动，飕飕飕向$n连环三剑，皆是极凌厉的攻势",
	"$N一个箭步纵到$n身前，手腕微颤，挥剑斜撩，横削$n$l，剑法极尽灵动轻捷",
});

mapping query_action(object me, object weapon)
{
	int i, level;
	object target;
	level = (int)me->query_skill("huifeng-jian", 1);

	// add checking target in the if condition, if there is no target,then don't use these special
	// jue attack msg,instead, the system will use normal attack msg.
	// xiaojian, May 25,2001

	target = me->select_opponent();

	if( me->query_temp("perform/juejian") && target )
	{
		return (["action": juejian_msg[random(sizeof(juejian_msg))],
			 "force" : 500,
			 "dodge" : 50,
			 "damage": 250,
			 "damage_type": random(2)?"刺伤":"割伤" ]);
	} else for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                       return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 60)
                return notify_fail("你的体力不够练回风拂柳剑。\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("你的内力不够练回风拂柳剑。\n");

        me->receive_damage("qi", 45);
        me->add("neili", -58);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huifeng-jian/" + action;
}
