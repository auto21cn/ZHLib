// liumang.c 流氓

inherit BUNCH_NPC;

void create()
{
        set_name("钱庄老板", ({ "boss", "money", "laoban" }));
	set("gender", "男性");
	set("age", 19);
        set("long", "他曾经是一个成天游手好闲的流氓，后来不知道从那里发了一笔横财开了这个钱庄。\n");
	
	set("combat_exp", 1000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver",2);
}
