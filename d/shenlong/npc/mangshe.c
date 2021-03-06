//mangshe.c

inherit SNAKE;

void create()
{
	set_name("蟒蛇", ({ "mang she", "she" }) );
	set("race", "蛇类");
	set("age", 5);
	set("long", "一只昂首直立，吐着长舌芯的大蟒蛇。\n");
	set("attitude", "peaceful");

	set("str", 26);
	set("con", 30);
	set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
	set("verbs", ({ "bite" }) );

	set("combat_exp", 5000);

        set("chat_chance",50);
	set("chat_msg", ({
		"大蟒蛇虎视眈眈地注视着你，想把你一口吞下！\n",
		"大蟒蛇张了一下血盆大口，好象饿了。\n"
	}) );

	set_temp("apply/attack", 25);
	set_temp("apply/damage", 20);
	set_temp("apply/armor", 18);
	set_temp("apply/defence",20);

	setup();
}

void die()
{
	object ob;
	message_vision("$N倒在地上，死了！\n", this_object());
	ob = new("/d/baituo/obj/shepi");
	ob->move(environment(this_object()));
	destruct(this_object());
}

int convert(string arg)
{
	object me = this_player();
	object ob;

	if (arg!="snake" && arg!="she" && arg!="mang she") return 0;
	if (me->query("family/family_name") != "欧阳世家") 
		return notify_fail("你不能化蛇为杖。\n");

	return notify_fail("蟒蛇身子太过粗大，无法化为蛇杖。\n");
}