// /clone/board/wudao_b.c

inherit BULLETIN_BOARD;

void create()
{
        set_name("经验交流板", ({ "board" }) );
        set("location", "/d/city/wumiao");
        set("board_id", "wumiao_b");
        set("long", "这是一个专供玩家经验交流，其他灌水杀无赦。\n" );
	setup();
	set("capacity", 100);
	replace_program(BULLETIN_BOARD);
}

