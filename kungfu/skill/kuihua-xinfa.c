// kuihua-xinfa.c �����ķ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("kuihua-xinfa", 1);
        return lvl * lvl * 15 * 10 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query("gender") != "����")
                return notify_fail("�����񹦣��ӵ��Թ���\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("�����ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"kuihua-xinfa/" + func;
}