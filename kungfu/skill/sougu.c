//sougu.c 搜骨鹰爪功

inherit SKILL;
#include <combat.h>
#include <ansi.h>

int next_hit(object me, object victim, object weapon, int damage);

mapping *action = ({
([	"action" : "\n$N左爪虚扬，右爪迅速抓向$n，一虚一实，正是一招「幻爪式」",
	"force" : 120,
	"dodge" : 5,
	"damage_type" : "抓伤",
	"lvl" : 0,
	"damage" : 15,
        "post_action": (: next_hit :),  
	"skill_name" : "幻爪式"
]),
([	"action" : "\n$N身形飘忽，左右爪飘忽不定得从四面八方攻向$n，变化万千，正是一招「飘爪式」",
	"force" : 120,
	"dodge" : 5,
	"damage_type" : "抓伤",
	"lvl" : 0,
	"damage" : 15,
        "post_action": (: next_hit :),  
	"skill_name" : "飘爪式"
]),
([	"action" : "\n$N飞身而起，双爪如钩，带着呼啸的劲气直扑$n而去，攻势锐利，正是一招「铁爪式」",
	"force" : 120,
	"dodge" : 5,
	"damage_type" : "抓伤",
	"lvl" : 0,
	"damage" : 15,
        "post_action": (: next_hit :),  
	"skill_name" : "铁爪式"
]),
([	"action" : "\n$N双臂一拢，左爪直攻$n下盘，右爪却挟风雷之势推向$n腰间，一虚一实，正是一招「推爪式」",
	"force" : 120,
	"dodge" : 5,
	"damage_type" : "抓伤",
	"lvl" : 0,
	"damage" : 15,
        "post_action": (: next_hit :),  
	"skill_name" : "推爪式"
]),
([	"action" : "\n$N身形陡起，如雄鹰击日般“倏”地从$n头顶越过，使一招「盖爪式」双爪疾向$n脑后击下",
	"force" : 190,
	"dodge" : 20,
	"damage_type" : "抓伤",
	"damage" : 25,
	"lvl" : 40,
        "post_action": (: next_hit :),  
	"skill_name" : "盖爪式"
]),
([	"action" : "\n$N就地一滚，突然到了$n身前，使一招「掏爪式」，右爪直奔$n小腹",
	"force" : 225,
	"dodge" : 20,
	"damage_type" : "抓伤",
	"damage" : 35,
	"lvl" : 80,
        "post_action": (: next_hit :),  
	"skill_name" : "掏爪式"
]),
([	"action" : "\n$N左爪护胸，右爪凝劲后发，一招「托爪式」，缓缓托向$n的$l",
	"force" : 265,
	"dodge" : 5,
	"damage_type" : "抓伤",
	"damage" : 40 ,
	"lvl" : 100,
        "post_action": (: next_hit :),  
	"skill_name" : "托爪式"
]),
([	"action" : "\n$N身形诡异，疾速前扑，使一招「撩爪式」，直撩$n裆部",
	"force" : 310,
	"dodge" : 25,
	"damage_type" : "抓伤",
	"damage" : 45,
	"lvl" : 120,
        "post_action": (: next_hit :),  
	"skill_name" : "撩爪式"
]),
([	"action" : "\n$N身形飘忽，陡然转到$n身后，一招「锁爪式」，双爪直向$n咽喉插下",
	"force" : 320,
	"dodge" : 35,
	"damage_type" : "抓伤",
	"damage" : 50,
	"lvl" : 140,
        "post_action": (: next_hit :),  
	"skill_name" : "锁爪式"
]),
([	"action" : "\n$N一声厉啸，身形拔起，使出「千爪式」，由半空盘旋下击，$n顿觉漫天爪影，罩向全身死穴",
	"force" : 335,
	"dodge" : 40,
	"damage_type" : "抓伤",
	"damage" : 55,
	"lvl" : 160,
        "post_action": (: next_hit :),  
	"skill_name" : "千爪式"
]),
([	"action" : "\n$N身形冲天而起，如同九天鹰扬，双爪飞出，一招「飞爪式」，临空飞击向$n",
	"force" : 335,
	"dodge" : 40,
	"damage_type" : "抓伤",
	"damage" : 75,
	"lvl" : 160,
        "post_action": (: next_hit :),  
	"skill_name" : "飞爪式"
]),
});

int valid_enable(string usage) { return usage=="claw" ||  usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练搜骨鹰爪功必须空手。\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("你的内功火候不够，无法学搜骨鹰爪功。\n");

	if ((int)me->query("max_neili") < 600)
		return notify_fail("你的内力太弱，无法学搜骨鹰爪功。\n");

	if ((int)me->query_str() < 33)
		return notify_fail("你现在的膂力太差，还无法学搜骨鹰爪功。\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("sougu",1);

        if( me->query_temp("lzg_lianhuan"))
        {
		return action[me->query_temp("lzg_lianhuan")-1];
        }
	else {
		for(i = sizeof(action); i > 0; i--) 
			if(level > action[i-1]["lvl"])
        	        	return action[NewRandom(i, 20, level/5)];
	}
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("你的体力太低了。\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("你的内力不够练鹰爪功。\n");

	me->receive_damage("qi", 55);
	me->add("neili", -57);
	return 1;
}

int next_hit(object me, object victim, object weapon, int damage)
{
        string *msg;
        msg = ({
                HIR"\n$N一抓不中，次抓随至，来势更加迅捷刚猛！" NOR,
                HIR"\n$N搜骨飞鹰爪源源而出，一招落空，又即连续急攻！" NOR,
                HIR"\n$n才躲过这招，$N次招又至，抓法快极狠极！"NOR,
        });

        if(damage==RESULT_DODGE 
        && (int)me->query_skill("sougu",1) > 100 
        && 2>random(3)
        && !me->query_temp("lzg_lianhuan")
        && !me->query_temp("next_hit")) {
        message_vision(msg[random(sizeof(msg))] , me,victim );
        me->add("neili", -20);
        me->add_temp("next_hit",1);
        COMBAT_D->do_attack(me, victim, me->query_temp("weapon"));
        me->delete_temp("next_hit");
        }
        
}

string perform_action_file(string action)
{
	return __DIR__"sougu/" + action;
}
