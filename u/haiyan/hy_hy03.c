// hy_hy03.c 
inherit ROOM; 
void create() 
     { 
     set("short", "花  园"); 
     set("long", @LONG 
这里是海燕家的花园，一走进来，你就被这奇妙的景色迷住了。
左看看右看看，不禁心潮澎湃，留连忘返。
LONG); 
     set("exits", ([ 
         "east"     : __FILE__ ,  
         "west"     : __DIR__"hy_houting" ,
         "south"    : __DIR__"hy_hy02" ,
         "north"    : __DIR__"hy_hy01" ,
     ])); 
     set("no_sleep_room", "1"); 
     setup(); 
     replace_program(ROOM); 
     }

