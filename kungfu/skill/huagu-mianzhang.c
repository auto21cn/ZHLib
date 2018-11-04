// huagu-mianzhang 化骨绵掌

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([  "action" : "$N身形微晃，一招「长恨深入骨」，十指如戟，插向$n的双肩锁骨",
    "force" : 200,
    "dodge" : 10,
    "damage_type" : "内伤",
    "lvl"   : 0,
    "skill_name" : "长恨深入骨" ,
]),
([  "action" : "$N出手如风，十指微微抖动，一招「素手裂红裳」抓向$n的前胸",  
    "force" : 220,
    "dodge" : 20,
    "damage_type" : "内伤",
    "lvl"   : 20,
    "skill_name" : "素手裂红裳" ,
]),
([  "action" : "$N双手忽隐忽现，一招「长风吹落尘」，鬼魅般地抓向$n的肩头",  
    "force" : 250,
    "dodge" : 30,
    "damage_type" : "内伤",
    "lvl"   : 40,
    "skill_name" : "长风吹落尘" ,
]),
([  "action" : "$N左手当胸画弧，右手疾出，一招「明月映流沙」，猛地抓向$n的额
头",
    "force" : 290,
    "dodge" : 25,
    "damage_type" : "内伤",
    "lvl"   : 60,
    "skill_name" : "明月映流沙" ,
]),
([  "action" : "$N使一招「森然动四方」，激起漫天的劲风，撞向$n",
    "force" : 340,
    "dodge" : 40,
    "damage_type" : "内伤",
    "lvl"   : 80,
    "skill_name" : "森然动四方" ,
]),
([  "action" : "$N面无表情，双臂忽左忽右地疾挥，使出「黯黯侵骨寒」，十指    
忽伸忽缩，迅猛无比地袭向$n全身各处大穴",
    "force" : 460,
    "parry" : 5,
    "dodge" : 30,
    "damage_type" : "内伤",
    "lvl"   : 100,
    "skill_name" : "黯黯侵骨寒" ,
]),
([  "action" : "$N使出「黄沙飘惊雨」，蓦然游身而上，绕着$n疾转数圈，$n正眼  
花缭乱间，$N已悄然停在$n身后，右手划出一道光圈，接着右手冲出光圈猛抓$n的后背",  
    "force" : 430,
    "parry" : 20,
    "dodge" : 20,
    "damage_type" : "内伤",
    "lvl"   : 120,
    "skill_name" : "黄沙飘惊雨" ,
]),
([  "action" : "$N突然双手平举，$n一呆，正在猜测间，便见$N嗖的一下将双手    
收回胸前，接着一招「白骨无限寒」，五指如钩，直抓向$n的腰间",
    "force" : 400,
    "dodge" : 35,
    "damage_type" : "内伤",
    "lvl"   : 140,
    "skill_name" : "白骨无限寒" ,
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }  

int valid_combine(string combo) { return combo=="shenlong-bashi"; }

int valid_learn(object me)
{
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
   return notify_fail("练化骨绵掌必须空手。\n");
        if (2*(int)me->query_skill("shenlong-xinfa",1) <(int)me->query_skill("shenlong-bashi",1))
                return notify_fail("你的神龙心法火候不够，无法继续学化骨绵掌。\n");
    if ((int)me->query_skill("force", 1) < 50)
   return notify_fail("你的内功心法火候不够，练化骨绵掌会走火入魔。\n");
    if ((int)me->query("max_neili") < 300)
   return notify_fail("你的内力太弱，无法练化骨绵掌。\n");
    return 1;
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
    if(level >= action[i-1]["lvl"])
        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int)me->query_skill("huagu-mianzhang",1);
    for(i = sizeof(action); i > 0; i--)
    if(level > action[i-1]["lvl"])
        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 30)
        return notify_fail("你的体力太低了。\n");
    if ((int)me->query("neili") < 8)
        return notify_fail("你的内力不够练化骨绵掌。\n");
    if (me->query_skill("jiuyin-zhua", 1) < 60)
        me->receive_damage("qi", 15);
    else
    me->receive_damage("qi", 30);
    me->add("neili", -5);
    return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int level;
        level = me->query_skill("huagu-mianzhang", 1);
        if(me->query_skill_mapped("force") != "busi-shenlong") return 0;
        if (damage_bonus < 300) return 0;
        if ( level >= 200) 
        {  
                victim->receive_damage("qi",1,me);
                victim->affect_by("sl_poison",
                        ([ "level" : level + random(level/2),
                           "id"    : me->query("id"),
                           "duration" : level/30 ]));
                
                tell_object(me, HIB "你暗自运匀内劲，借由掌力拍去，只听“啪啪”几声轻响，你不由地得意一笑！\n" NOR );
                tell_object(victim, HIB "你觉得一股阴力被拍入身体，不由地头晕目眩，几欲呕吐！\n" NOR );
        }
        return 0;
}


string perform_action_file(string action)
{
    return __DIR__"huagu-mianzhang/" + action;
}



