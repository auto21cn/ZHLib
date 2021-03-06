// lingboweibu.c 凌波微步

#include <ansi.h>

inherit SKILL;

string *dodge_msg = ({
        "但是$n身形飘忽，轻轻一纵，早已避开。\n",
        "$n身随意转，倏地往一旁挪开了三尺，避过了这一招。\n",
        "可是$n侧身一让，$N这一招扑了个空。\n",
        "却见$n足不点地，往旁窜开数尺，躲了开去。\n",
        "$n身形微晃，有惊无险地避开了$N这一招。\n"
});

int valid_enable(string usage) 
{ 
        return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me) { return 1; }
int can_not_hubo() {return 1;}
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;

        if ((int)me->query_skill("lingbo-weibu", 1) < 100 )
                return;

        if (!living(me) || (me->is_busy() && random(3) == 0)) return;

        dp = ob->query_skill("force", 1); 
        ap = me->query_skill("lingbo-weibu",1);

          if (ap / 2 + random(ap) > dp)


        {
                result = ([ "damage" : -damage ]);

                   switch (random(2))
                {
                case 0:
                        result += (["msg" : HIW "只见$n" HIW "微微一笑，身子轻轻晃动，$N"
                                            HIW "眼前顿时出现了无数个$n" HIW "的幻影，令$N"
                                            HIW "完全无法辨出虚实。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "但见$n" HIW "轻轻一跃，已不见了踪影，$N"
                                            HIW "心中大骇，却又见$n" HIW "擦肩奔过，步法"
                                            "之奇巧，当真令人匪夷所思。\n" NOR]);
                        break;
                }
                return result;
        }
}


string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}


int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;
        if (lvl < 300) return 120;
        if (lvl < 350) return 140;
        return 150;
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力太差了，不能练凌波微步。\n");

        if ((int)me->query("neili") < 50)
                return notify_fail("你的内力太差了，不能练凌波微步。\n");

        me->receive_damage("qi", 50);
        me->add("neili", -30);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lingbo-weibu/" + action;
}


