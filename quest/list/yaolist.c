// for quest npc (yao)
// update by sun
#include <ansi.h>
//mapping *quest = ({
string *quest = ({
        ([      "quest": HIR "õ��" NOR,
                "bouns": 10,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": HIY "��˿��" NOR,
                "bouns": 88,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": HIY "����" NOR,
                "bouns": 30,
                "help" : "�����ӻ���"
        ]),        	
        ([      "quest": YEL "Ь��" NOR,
                "bouns": 10,
                "help" : "�����ӻ���"
        ]),        	
        ([      "quest": WHT "����˿" NOR,
                "bouns": 50,
                "help" : "�����ӻ���"
        ]),        	
        ([      "quest": WHT "ľ��" NOR,
                "bouns": 15,
                "help" : "�����ӻ���"
        ]),        	
        ([      "quest": "��Ь",
                "bouns": 5,
                "help" : "�����ӻ���"
        ]),        	
        ([      "quest": "�Ǵ�",
                "bouns": 15,
                "help" : "�����ӻ���"
        ]),        	
        ([      "quest": "����",
                "bouns": 17,
                "help" : "�����ӻ���"
        ]),        	
        ([      "quest": "����",
                "bouns": 22,
                "help" : "�����ӻ���"
        ]), 
        ([      "quest": "����",
                "bouns": 10,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "�鲼��",
                "bouns": 10,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "ţƤ��",
                "bouns": 15,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "Ƥ����",
                "bouns": 16,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "Ƥ����",
                "bouns": 10,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "Ƥѥ",
                "bouns": 30,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "ˢ��",
                "bouns": 15,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "������",
                "bouns": 20,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "ͷ��",
                "bouns": 20,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "������Ȧ",
                "bouns": 25,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "ָ��",
                "bouns": 20,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": "˯��",
                "bouns": 45,
                "help" : "�����ӻ���"
        ]),
        ([      "quest": YEL "�ټ���" NOR,
                "bouns": 15,
                "help" : "������Ժ"
        ]),
        ([      "quest": YEL "ǧ����" NOR,
                "bouns": 75,
                "help" : "������Ժ"
        ]),
        ([      "quest": YEL "���־�" NOR,
                "bouns": 35,
                "help" : "������Ժ"
        ]),
        ([      "quest": "����",
                "bouns": 15,
                "help" : "���ݳ���"
        ]),
        ([      "quest": HIR "�컨" NOR,
                "bouns": 10,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIR "�ܵ�" NOR,
                "bouns": 85,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIG "����" NOR,
                "bouns": 45,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIG "��֥" NOR,
                "bouns": 55,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIY "���" NOR,
                "bouns": 35,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIY "�ջ�" NOR,
                "bouns": 5,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIY "¹��" NOR,
                "bouns": 40,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIY "ţ��" NOR,
                "bouns": 30,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIY "ǧ����" NOR,
                "bouns": 55,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIB "����" NOR,
                "bouns": 25,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIB "����" NOR,
                "bouns": 15,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIB "����" NOR,
                "bouns": 15,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIB "Զ־" NOR,
                "bouns": 20,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIM "Ы��" NOR,
                "bouns": 5,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIW "������" NOR,
                "bouns": 50,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIW "����" NOR,
                "bouns": 40,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIW "�˲�" NOR,
                "bouns": 77,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIW "����" NOR,
                "bouns": 50,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIW "ѩ��" NOR,
                "bouns": 100,
                "help" : "����ҩ��"
        ]),
        ([      "quest": HIW "�����" NOR,
                "bouns": 60,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": RED "���" NOR,
                "bouns": 5,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": GRN "ɽ��" NOR,
                "bouns": 20,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": YEL "��Ƥ" NOR,
                "bouns": 10,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": YEL "����" NOR,
                "bouns": 18,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": YEL "���" NOR,
                "bouns": 5,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": MAG "����" NOR,
                "bouns": 20,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": MAG "����" NOR,
                "bouns": 20,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": MAG "����֬" NOR,
                "bouns": 20,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": MAG "�ϻ�" NOR,
                "bouns": 20,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": CYN "���" NOR,
                "bouns": 25,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": CYN "��ʯ��" NOR,
                "bouns": 5,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": CYN "ţϥ" NOR,
                "bouns": 20,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": CYN "������" NOR,
                "bouns": 40,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": WHT "����" NOR,
                "bouns": 5,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": WHT "����" NOR,
                "bouns": 10,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": WHT "��β" NOR,
                "bouns": 30,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": WHT "ûҩ" NOR,
                "bouns": 5,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": WHT "ɽ�軨" NOR,
                "bouns": 5,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": WHT "����" NOR,
                "bouns": 5,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": WHT "��ľ" NOR,
                "bouns": 50,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": WHT "����" NOR,
                "bouns": 25,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": "�в�",
                "bouns": 5,
                "help" : "����ҩ��"
        ]),      
        ([      "quest": WHT "��������" NOR,
                "bouns": 50,
                "help" : "���ݴ�����"
        ]),      
        ([      "quest": "����",
                "bouns": 20,
                "help" : "���ݴ�����"
        ]),      
        ([      "quest": "�ֵ�",
                "bouns": 10,
                "help" : "���ݴ�����"
        ]),      
        ([      "quest": "��ͨذ��",
                "bouns": 5,
                "help" : "���ݴ�����"
        ]),      
        ([      "quest": "����",
                "bouns": 5,
                "help" : "���ݴ�����"
        ]),      
        ([      "quest": "����",
                "bouns": 5,
                "help" : "���ݴ�����"
        ]),      
        ([      "quest": "����",
                "bouns": 20,
                "help" : "���ݴ�����"
        ]),      
        ([      "quest": "����",
                "bouns": 20,
                "help" : "���ݴ�����"
        ]),      
        ([      "quest": "����",
                "bouns": 5,
                "help" : "���˳�����¥"
        ]),      
        ([      "quest": "��Ѽ��",
                "bouns": 5,
                "help" : "���˳�����¥"
        ]),      
        ([      "quest": "������",
                "bouns": 5,
                "help" : "���˳�����¥"
        ]),      
        ([      "quest": "ţƤ�ƴ�",
                "bouns": 5,
                "help" : "���˳�����¥"
        ]),      
        ([      "quest": "����",
                "bouns": 5,
                "help" : "���˳�����¥"
        ]),      
        ([      "quest": HIY "��ҩ" NOR,
                "bouns": 5,
                "help" : "���˳�������"
        ]),      
        ([      "quest": HIG "��Ҷ������" NOR,
                "bouns": 5,
                "help" : "���ݳǴ���¥"
        ]),      
        ([      "quest": RED "ӣ�һ���" NOR,
                "bouns": 5,
                "help" : "���ݳǴ���¥"
        ]),      
        ([      "quest": WHT "���Ϻ��" NOR,
                "bouns": 5,
                "help" : "���ݳǴ���¥"
        ]),      
        ([      "quest": "��«",
                "bouns": 25,
                "help" : "���ݳǸ���"
        ]),      
        ([      "quest": HIR "����" NOR,
                "bouns": 5,
                "help" : "�ɶ�������"
        ]),      
        ([      "quest": HIG "��Ҷ" NOR,
                "bouns": 5,
                "help" : "�ɶ�������"
        ]),      
        ([      "quest": HIW "�ɻ�ʯ" NOR,
                "bouns": 5,
                "help" : "�ɶ�������"
        ]),      
        ([      "quest": "��Ь",
                "bouns": 15,
                "help" : "�ɶ��Ǹ���"
        ]),      
        ([      "quest": "ˮ��",
                "bouns": 15,
                "help" : "�ɶ��Ǹ���"
        ]),      
        ([      "quest": "�����Ҷ��",
                "bouns": 15,
                "help" : "�ɶ��Ǹ���"
        ]),      
        ([      "quest": HIG "������" NOR,
                "bouns": 15,
                "help" : "������ҩ��"
        ]),      
        ([      "quest": HIY "�˺���" NOR,
                "bouns": 15,
                "help" : "������ҩ��"
        ]),      
        ([      "quest": HIY "������" NOR,
                "bouns": 15,
                "help" : "������ҩ��"
        ]),      
        ([      "quest": HIY "������" NOR,
                "bouns": 15,
                "help" : "������ҩ��"
        ]),      
        ([      "quest": HIY "ֹ��ҩ" NOR,
                "bouns": 25,
                "help" : "������ҩ��"
        ]),      
        ([      "quest": HIC "��ʬ��" NOR,
                "bouns": 35,
                "help" : "������ҩ��"
        ]),      
        ([      "quest": HIC "���" NOR,
                "bouns": 15,
                "help" : "������ҩ��"
        ]),      
        ([      "quest": "�ۻ�",
                "bouns": 10,
                "help" : "������ҩ��"
        ]),      
        ([      "quest": "ľ��",
                "bouns": 15,
                "help" : "������ľ����"
        ]),      
        ([      "quest": "ľ��",
                "bouns": 25,
                "help" : "������ľ����"
        ]),      
        ([      "quest": "ľ��",
                "bouns": 15,
                "help" : "������ľ����"
        ]),      
        ([      "quest": "�м�����",
                "bouns": 35,
                "help" : "���������"
        ]),      
        ([      "quest": HIR "ɽ�軨" NOR,
                "bouns": 100,
                "help" : "��������"
        ]),      
        ([      "quest": HIR "��������" NOR,
                "bouns": 35,
                "help" : "������̫�;�"
        ]),      
        ([      "quest": HIG "Ҷ����" NOR,
                "bouns": 25,
                "help" : "������̫�;�"
        ]),      
        ([      "quest": "���",
                "bouns": 15,
                "help" : "������̫�;�"
        ]),      
        ([      "quest": "��������",
                "bouns": 15,
                "help" : "������̫�;�"
        ]),      
        ([      "quest": "������",
                "bouns": 5,
                "help" : "������̫�;�"
        ]),      
        ([      "quest": "��ɴ�������ȹ",
                "bouns": 35,
                "help" : "������Ѧ�ǳ�����"
        ]),      
        ([      "quest": "����",
                "bouns": 15,
                "help" : "������Ѧ�ǳ�����"
        ]),      
        ([      "quest": "���ƹ���",
                "bouns": 25,
                "help" : "������Ѧ�ǳ�����"
        ]),      
        ([      "quest": "�廨СЬ",
                "bouns": 25,
                "help" : "������Ѧ�ǳ�����"
        ]),      
        ([      "quest": "խ�̰�",
                "bouns": 25,
                "help" : "������Ѧ�ǳ�����"
        ]),      
        ([      "quest": HIW "�׺ϻ�" NOR,
                "bouns": 95,
                "help" : "��ɽ����"
        ]),      
        ([      "quest": HIW "ʯ��" NOR,
                "bouns": 55,
                "help" : "��ɽ����"
        ]),      
        ([      "quest": HIR "ɯ须�"NOR,
                "bouns": 65,
                "help" : "��ɽ����"
        ]),      
        ([      "quest": HIB "ޥ����" NOR,
                "bouns": 45,
                "help" : "��ɽ����"
        ]),      
        ([      "quest": "���㻨��",
                "bouns": 15,
                "help" : "�������"
        ]),      
        ([      "quest": "��䶹��",
                "bouns": 15,
                "help" : "�������"
        ]),      
        ([      "quest": "���Ӿ�ƿ",
                "bouns": 15,
                "help" : "������С�ƹ�"
        ]),      
        ([      "quest": HIG "����" NOR,
                "bouns": 15,
                "help" : "�������ӻ���"
        ]),      
        ([      "quest": HIM "������" NOR,
                "bouns": 5,
                "help" : "�������ӻ���"
        ]),      
        ([      "quest": "���",
                "bouns": 5,
                "help" : "�������ӻ���"
        ]),      
        ([      "quest": "ľ��",
                "bouns": 35,
                "help" : "�������ӻ���"
        ]),      
        ([      "quest": HIY "��õ��" NOR,
                "bouns": 15,
                "help" : "�����ǻ���"
        ]),      
        ([      "quest": HIR "��õ��" NOR,
                "bouns": 45,
                "help" : "�����ǻ���"
        ]),      
        ([      "quest": HIB "�����" NOR,
                "bouns": 35,
                "help" : "�����ǻ���"
        ]),      
        ([      "quest": HIM "������" NOR,
                "bouns": 35,
                "help" : "�����ǻ���"
        ]),      
        ([      "quest": HIW "�ײ軨" NOR,
                "bouns": 15,
                "help" : "�����ǻ���"
        ]),      
        ([      "quest": BLU "��ĵ��" NOR,
                "bouns": 35,
                "help" : "�����ǻ���"
        ]),      
        ([      "quest": "������",
                "bouns": 45,
                "help" : "���������"
        ]),      
        ([      "quest": "����",
                "bouns": 5,
                "help" : "���������"
        ]),      
        ([      "quest": "ţ����",
                "bouns": 35,
                "help" : "���������"
        ]),      
        ([      "quest": "�Ź���",
                "bouns": 15,
                "help" : "���������"
        ]),      
        ([      "quest": "���ʰ���",
                "bouns": 5,
                "help" : "�����ǰ�����"
        ]),      
        ([      "quest": "�ز˰���",
                "bouns": 10,
                "help" : "�����ǰ�����"
        ]),      
        ([      "quest": "�������",
                "bouns": 15,
                "help" : "�����ǰ�����"
        ]),      
});
/*
mapping query_quest(int num)
{
        return quest[random(num)];
}
*/
string query_quest()
{
	return quest[random(sizeof(quest))];
}

                                                                                                               	                                                                        	