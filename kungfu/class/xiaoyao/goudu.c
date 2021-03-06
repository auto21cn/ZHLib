// goudu.c
// shilling 97.2

inherit NPC;
inherit F_GUARDER;

#include <ansi.h>

string ask_me();

void create()
{
	set_name("苟读", ({ "gou du", "gou" }));
	set("long", 
		"他看上去也是几十岁的人了，却是纯然一个书呆子的模样。\n");
	set("gender", "男性");
	set("age", 50);
	set("attitude", "friendly");
	set("class", "scholar");
	set("shen_type", 1);
	set("str", 25);
	set("int", 35);
	set("con", 25);
	set("dex", 25);

	set("inquiry", ([
		"论语":(:ask_me:),
	]) );

	set("max_qi", 1800);
	set("max_jing", 1800);
	set("neili", 900);
	set("max_neili", 2000);
	set("jiali", 30);
	set("combat_exp", 150000);

	set_skill("blade",80);
	set_skill("ruyi-dao",80);
	set_skill("force", 80);
	set_skill("dodge", 80);
	set_skill("hand", 80);
	set_skill("parry", 80);
	set_skill("feiyan-zoubi", 80);
	set_skill("xiaoyao-xinfa",80);
	set_skill("zhemei-shou", 80);
        set_skill("literate", 150);

	map_skill("hand", "zhemei-shou");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("force", "xiaoyao-xinfa");
	map_skill("blade", "ruyi-dao");

        prepare_skill("hand", "zhemei-shou");

        set("coagents", ({
                ([ "startroom" : "/d/xiaoyao/qingcaop",
                   "id"        : "su xinghe" ]),
        }));

	set("book_count", 1);

	create_family("逍遥派", 3, "弟子");
	set("title","逍遥派“函谷八友”");
	set("nickname","书呆子");

	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/blade")->wield();

}

string ask_me()
{
	object me,ob;
	ob=this_player(); 

	if (query("book_count") < 1)
                return "你来晚了，那本《论语》我已经赠送给别人了。";   
	add("book_count", -1);                  

	if(ob->query("family/master_id")=="xiaoyao zi")
	{
		command("say 师叔想要《论语》，拿去就是。");
		message_vision(HIY"苟读从怀里掏出一本旧书，交了给$N \n\n"NOR,ob);
		me=new("/clone/book/lbook4");
		me->move(ob);
		return "这本书可千万不要借给别人啊，他们一借就不还的了。\n";
	}
	command("say 哈哈，《论语》就没有了，这里有我派高手从少林盗来的书。");
	command("say 既然你那么好学，我就把它送给你吧。\n");
	message_vision(HIY"苟读翻箱倒柜找了半天，找出一本旧书，交了给$N \n\n"NOR,ob);
	if (random(2) == 1) me=new("/clone/book/strike_book");
	else me=new("/clone/book/book-paper");
	me->move(ob);

	return "这本书可千万不要借给别人啊，他们一借就不还的了。\n";
}
