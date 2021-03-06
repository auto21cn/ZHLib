// mian.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("粗瓷碗", ({ "wan" }));
	set_weight(900);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "一个用土窑烧制的花边瓷碗。\n");
		set("unit", "个");
		set("value", 50);
		set("food_supply", 10);
		set("water_supply", 25);
		set("max_liquid", 10);
        }

	set("liquid", ([
		"type": "water",
		"name": "米粥",
		"remaining": 6,
		"drunk_supply": 10,
	]));

        //setup();
}

void init()
{
	add_action("do_eat", "eat");
        add_action("do_eat", "drink");
}


int do_eat(string arg)
{
        if ( !(int)query("liquid/remaining") ||
             query("liquid/name") != "米粥" )
                return 0;

        if( !this_object()->id(arg) ) return 0;
        if( this_player()->is_busy() )
                return notify_fail("你上一个动作还没有完成。\n");

        if( (int)this_player()->query("food")
           >= (int)this_player()->max_food_capacity() * 150 / 100)
                return notify_fail("你已经吃太饱了，再也吃不下了。\n");

        this_player()->add("food", (int)query("food_supply"));
        if( (int)this_player()->query("water") <
            (int)this_player()->max_water_capacity()-(int)query("water_supply"))
                this_player()->add("water", (int)query("water_supply"));

        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        add("liquid/remaining", -1);
	if ( query("liquid/remaining") )
   		 message_vision("$N端起碗来，猛喝了几口粥。\n", this_player());
	else
   		 message_vision("$N端起碗来，把剩下的粥喝得干干净净。\n",this_player());

	return 1;
}
