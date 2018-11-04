// fangyi.c
#include <ansi.h>

inherit NPC;

void create()
{
	set_name("方怡", ({"fang yi", "fang","yi"}));
	set("title",HIY"神龙教"HIR"赤龙使"NOR"座下弟子");
	set("long",
	"她原来是沐王府家将，现在是神龙教赤龙门女弟子，长得活泼可爱。\n"
	);

	set("gender", "女性");
	set("attitude", "peaceful");

	set("age", 10+random(10));
	set("shen_type", -1);
	set("str", 25+random(10));
	set("dex", 25+random(10));
	set("max_qi", 200);
	set("max_jing", 150);
	set("neili", 200);
	set("max_neili", 200);
	set("jiaji", 5+random(5));
	set("combat_exp", 20000+random(10000));

	set_skill("force", 40);
	set_skill("dodge", 40);
	set_skill("unarmed", 40);
	set_skill("parry", 40);
	set_skill("sword", 60);
	set_skill("shedao-qigong", 30);
	map_skill("sword","shedao-qigong");

	setup();
	carry_object("/d/shenlong/obj/xionghuang")->wield();
        carry_object("/d/city/obj/duanjian")->wield();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver",5);
        create_family("神龙教", 3, "赤龙门弟子");
}

void init()
{
	object ob;

	::init();

	if( interactive(ob = this_player()) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}

void greeting(object ob)
{
	object obj;
	if (! objectp(ob))
		return;

        if (interactive(ob))
        {
		if (obj = present("used gao", ob))          
			unconcious();
	}
	return;
}
