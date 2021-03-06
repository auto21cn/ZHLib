// riyue-xinfa.c 日月心法
// written by haiyan

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
    return ::valid_learn(me);
}

int valid_force(string force)
{
    return force == "riyue-guanghua" ||
           force == "xixing-dafa"||
           force == "yijinjing";
}

int practice_skill(object me)
{
    return notify_fail("日月心法只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
    return SKILL_D("riyue-xinfa/") + func;
}

