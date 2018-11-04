// qingcaop.c
// by shilling 97.2

inherit ROOM;

void create()
{
        set("short", "���ƺ");
        set("long", @LONG
�����������е�һƬ�Ƚϴ�Ŀյأ���Ի�����ƺ����Ϊ��������֮��
��������ƽʱ���������������ǲ�֪��Ϊʲô����������ȴ�в����ˡ��㿴��
��һ�����ˡ�
LONG );
	set("exits", ([
		"north" : __DIR__"xiaodao3",
		"south" : __DIR__"xiaodao5",
		"east"  : __DIR__"xiaodao4",
		"west"  : __DIR__"xiaodao1",
                "enter" : __DIR__"midao",
	]));
	set("outdoors", "xiaoyao");
	set("objects", ([
		CLASS_D("xiaoyao") + "/suxingh" : 1,
                CLASS_D("duan") + "/duanyq" : 1,
                CLASS_D("duan") + "/duanyu" : 1,
                __DIR__"npc/wangyuyan" : 1,
	]));
        set("zhenlong", 1);
	set("valid_startroom", 1);
	setup();
	"/clone/board/xiaoyao_b"->foo();
}

int valid_leave(object me, string dir)
{
        object su;

        if (dir != "enter")
                return ::valid_leave(me, dir);

        if (! (su = present("su xinghe", this_object())) || ! living(su))
                return ::valid_leave(me, dir);

        if (! su->permit_pass(me, dir))
                return 0;

        return ::valid_leave(me, dir);
}

string long()
{
        string msg;
        int i;

        if (query("zhenlong"))
        {
                msg = "    �յ��м����һ�����̣�������˲��ٵ��ӡ�һ"
                      "��Χ�Ų��ٵ����ڹۿ����е�ڤ��˼�����еĿ�����"
                      "�����ġ�";
        } else
                msg = "    ";
        if (present("duan yanqing", this_object()))
        {
                msg += "�Ա�һ�ֿ�һϮ��������ò��ª������쳣������"
                       "�Ŀ���" + (query("zhenlong") ? "���̡�" : "���ˡ�");
        }
        if (present("duan yu", this_object()))
        {
                if (present("wang yuyan", this_object()))
                        msg += "��һ���������أ����÷�����棬�ľ�"
                               "�������࣬ȴ���ǳ�������һŮ�ӣ�ɫ��"
                               "�Ե�������������������Ц��";
                else
                        msg += "��һ��ȴ��ʧ�����ǣ������������·�"
                               "������ʲô��Ҫ�����Ƶġ�";
        }

        return query("long") + sort_string(msg, 66);
}