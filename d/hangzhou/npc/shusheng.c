// shusheng
// by ruri
inherit NPC;
#include <ansi.h>;
inherit F_DEALER;

void create()
{
	set_name("月下书生", ({ "yuexia shusheng","shusheng","sheng" }));
	set("str", 27);
	set("title", HIC"翻云覆雨"NOR);
	set("nickname", HIG"竹梅共侣"NOR);
	set("shen_type", 1);
	set("gender", "男性");
	set("age", 28);
	set("per", 28);
	set("long", "一个眉目俊秀的青年书生，闲来好替人解签，有些疯颠。\n");
	set("combat_exp", 15000);
	set("attitude", "friendly");
	set("chat_chance", 1);
	set("chat_msg", ({
		"月下书生摇头晃脑地吟道：“著以长相思，缘以结不解？同心而离居，忧伤以终老。”\n"
	}));

	set("inquiry", ([
		"解签" : "巫师还没写好呢，你去问剑意那小娘皮吧！\n"
		]));
	
	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_skill("parry", 60);

	setup();
	carry_object(__DIR__"obj/baibu-qingshan.c")->wear();
}