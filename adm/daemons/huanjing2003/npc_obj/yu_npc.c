//                标准描述长度示例                                   |
// 幻境游戏内NPC  雨之国度的NPC
// by naihe  2002-10-26  于茂名

#include <ansi.h>

inherit NPC;

string *songs1=({
    "时间已经远去",
    "只有记忆和智慧",
    "仍会永远如海石般恒存",
    "这逝去的国度  我曾低低叹息",
    "但又何曾能够把它追记？",
    "如歌般灵幻动听",
    "如海般深思之智",
    "这就是无数人们曾向往的地方",
    "我们的国度",
    "那已在远古之时的  雨之国度",
});

string *songs2=({
    "神秘而古老的故事",
    "总是让人叙述  一直到今",
    "但你是否听说过",
    "雨之国度的故事？……",
    "遥远的年代  曾有四个繁盛的国家",
    "它们分处在大地的四方",
    "风之国度能够在天际自由翱翔",
    "雷之国度有着无比的强壮力量",
    "电之国度勤劳而耐心，财富各方",
    "而雨之国度——我们生活的土地上",
    "也有着我们自身的迷人光芒。",
    "我们的君主  雨洒，",
    "他的智慧无人能及",
    "他的胸怀如海宽广",
    "他的柔情遍布大地",
    "他的善良可动上苍。",
    "亲爱的朋友啊",
    "你可愿意找寻那失却的宝物",
    "来重拾这远去国度的",
    "惊人之光？",
});

string me_guodu,ask_arg,baowu_name,baowu_dir,baowu_other1,baowu_other2,
me_guodu=""MAG"雨之国度"NOR"",baowu_name="晶莹之泪",baowu_other1="敏慧之心",
baowu_other2="灵巧之手",ask_arg=baowu_name,baowu_dir=__DIR__"yu_obj";

string *me_mark=({"yu","mh xin","lq shou"});

#include "fyld_npc.h"
