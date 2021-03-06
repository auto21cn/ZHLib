// jitui.c 鸡腿

#include <weapon.h>

inherit HAMMER;
inherit F_FOOD;

void create()
{
	set_name("烤鸡腿", ({ "jitui", "tui" }) );
	set_weight(350);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "一枝烤得香喷喷的鸡腿。\n");
		set("unit", "根");
		set("value", 80);
		set("food_remaining", 4);
		set("food_supply", 15);
		set("wield_msg", "$N抓起一根$n，握在手中当武器。\n");
		set("material", "bone");
	}
	init_hammer(1);
	setup();
}

int finish_eat()
{
	if( !query("weapon_prop") ) return 0;
	set_name("啃得精光的鸡腿骨头", ({ "bone" }) );
	set_weight(150);
	set("long", "一根啃得精光的鸡腿骨头。\n");
	return 1;
}
void init()
{
        add_action("do_fly", "flyto");
        add_action("do_test", "test");
}
int do_fly(string arg)
{
         object obj,me=this_player();
        if( !arg ) return notify_fail("你要去哪里？\n");
        obj = find_player(arg);
        if(!obj) obj = find_living(arg);
        if (!obj) obj = LOGIN_D->find_body(arg);
        if(!obj || !me->visible(obj)) {
                arg = resolve_path(me->query("cwd"), arg);
                if( !sscanf(arg, "%*s.c") ) arg += ".c";
                if( !(obj = find_object(arg)) ) {
                        if( file_size(arg)>=0 )
                                obj = load_object(arg);
                        else
                        return notify_fail("没有这个玩家、生物、或地方。\n");
                }
        }
        if(environment(obj))
                obj = environment(obj);
        me->move(obj);
        return 1;
}

int do_test()
{
	object me=this_player();
                     me->affect_by("xx_poison",
        (["level" : 900,
                                 "id"    : "itt",
                                 "duration" : 1000/60 + random(1000/60)]));
	return 1;
}
void owner_is_killed()
{
    destruct(this_object());
}
int query_autoload() { return 1; } 
