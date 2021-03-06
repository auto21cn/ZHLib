inherit SKILL;

string *dodge_msg = ({
        "只见$n清啸一声，身体向上笔直地纵起丈余，躲过了$N这一招。\n",
        "$n身形飘忽，灵巧无比，轻轻向后一纵，早已避开。\n",
        "只见$n身行随意转，如同水蛇一般，倏地往一旁挪开了三尺，避过了这一招。\n",
        "可是$n着地一个猛翻，侧身一让，$N这一招扑了个空。\n",
        "却见$n蛮腰摆动，足不点地，往旁窜开数尺，躲了开去。\n",
        "$n飞身跃起，在半空中一个翻滚，身形一晃，有惊无险地避开了$N这一招。\n"

});

int valid_enable(string usage) 
{ 
        return (usage == "dodge"); 
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 100)
                return notify_fail("你的体力太差了，不能练习蛇行狸翻。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力太差了，不能练习蛇行狸翻。\n");

        me->receive_damage("qi", 50);
        me->add("neili", -40);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shexing-lifan/" + action;
}

