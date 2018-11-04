// 这是玩家自创武功程序 原由maxim@nju_fengxue编写，现由xgchen@zzfy修改
// xgchen
// 长孙无情
// 布衣平民
// 8000000
// 男性
// blade
// 无情刀





inherit SKILL;

////////////////////////////////

mapping *action = ({

// ZHAOSHI :0

([
"action" :"$N纵身一跃，手中$w一招「刀刀要命」对准的$l斜斜刺出一剑",
"force" :50,
"dodge" :20,
"damage_type": "割伤",
"attack" : 50,
"parry" : 50,
"lvl" : 0,
"skill_name" : "刀刀要命"
]),
 });
// ZHAOSHI :1
int valid_learn(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon"))
     || (string)weapon->query("skill_type") != "blade") return notify_fail("你使用的武器不对。\n");
        if( (int)me->query("max_neili") < 2500 )
                return notify_fail("你的内力太弱，无法练"+"无情刀"+"。\n");
        return 1;
}
int valid_enable(string usage) { return usage=="blade" || usage=="parry"; }
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
    level = (int)me->query_skill("xgchen-blade",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
object weapon; if (!objectp(weapon = me->query_temp("weapon")) || (string)weapon->query("skill_type") != "blade") return notify_fail("你使用的武器不对。\n");    if( (int)me->query("qi") < 100 )
                return notify_fail("你的体力不够了，休息一下再练吧。\n");
        if( (int)me->query("neili") < 100 )
                return notify_fail("你的内力不够了，休息一下再练吧。\n");
        me->receive_damage("qi", 90);
        me->add("neili", -70);
        return 1;
} //total 34 lines!
string perform_action_file(string action)
{
        return __DIR__"meskill/" + action;
}
