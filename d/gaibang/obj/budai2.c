// budai.c 布袋

#include <armor.h>

inherit SHIELD;

static int amount;
private void destruct_me() { destruct(this_object()); }


void create()
{
        set_name("布袋", ({ "bu dai", "dai", "bag" }));
        set_weight(500);
        set_max_encumbrance(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("base_unit", "个");
                set("base_weight", 500);
                set("equiped",1);
                set("armor_prop/armor", 2); 
                        set("armor_prop/defense", 1); 

                set("long", "一只用粗麻布织成的袋子，身上所带布袋的多少，是丐帮弟子江湖地位的标志。\n");
                set("material", "cloth");
                set("base_armor", 5);
                set("no_drop", "身为丐帮弟子，袋在则人在，袋亡则人亡。\n");
                set("no_get",  "这个布袋紧紧地绑在他身上，你拿不到手。\n");
                set("no_steal", "这个布袋紧紧地绑在他身上，你偷不到手。\n");
        }

        setup();
}

void init()
{
        add_action("do_remove", "remove");
}

int is_container() { return 1; }

int do_remove(string arg)
{
        if( (arg && present(arg, this_player()) == this_object())
          || arg == "all" ) {
                tell_object(this_player(), "丐帮弟子，袋在人在，袋亡人亡，你不能解除布袋！\n");
                return 1;
        }

        return 0;
}

