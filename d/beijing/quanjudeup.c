inherit ROOM;

void create()
{
	set("short", "ȫ�۵¾�¥��¥");
	set("long", @LONG
����������������ѧʿ������������ʫ��������������Ҳ������߳Ժȱ�
�����ס�����Ҳ�ǳ���ٰ�ϲ�����ѳ����������������������ȫ�۵¿�Ѽ��
��վ��¥���������ǣ�ֻ�����Ŀ�������
LONG );
	set("exits", ([
		"down"   : __DIR__"quanjude",
	]));
	set("objects", ([
		__DIR__"npc/cheng" : 1,
	]));

	setup();
	replace_program(ROOM);
}
