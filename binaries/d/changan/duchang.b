MUDB$tD�esD! include/globals.h include/ansi.h  d/changan/duchang.c\	  ���        h   }  ����������D  h  $  \  �  �  �  8	  H	  P	  \	  ����        �  ;  V    < ~K^< b-+ +  +  + A + A+ ++  .w� .�@ .9999B?\.w]=Z�	 l0 -<l 	  l0 -< h$ �!m=\=\=\
0	 "l0 -�0% �0% �0% �	0	 #l0 -�$^<]<	 %l0 -�A	 &l0 -��' 	 (l0 -�J	 )l0 -�+* <`�� 	 ,l0 -�.- 	 /l0 -�A	 0l0 -�21� �2-� �23� 4�l �+5 �+6 BD<l& ��'  <l  �7�i 8+	 � 8� +  8� +
 -.�  �.-  9�l& �;: ��, * -<*�k{h<]8 =]1 >]* ?]# @] A]  >ELSZa   ��l* .
+. ^-] < Bl* < Cl* +3  ?C\+3  ?C\ �+3  ?C\@�BA�B/ �@�B+2 �A�B+2 < D@�Bl ^A�Bl ^E^l* < Fl* ?\X8+ .] < Gl* < H@�Bl ^A�Bl ^I^l* < Jl* 
?\F@LAR.]<Kl* +3  < ?	C\���B+2 .L�.3 ^]�.- ]��`]<M< N<l �+5 �+6 D< l& <O<  .L�.3 ^]�.- ]P<l �+5 �+6 D< l& <l .]@�B@�B/% A�BA�B/ 
$]] � @�BA�B/% @�B
a
`@�B/ 
]] S @�BA�B^]�G 
]] 4 �C/$ �E/$ �I/$ �K/ 
]	] 	 ]Q] <% <R@�Bl ^A�Bl ^S^l* + <R@�Bl ^A�Bl ^T^��B^E^l* 8+	 ]<z]b ��B� V ��B
<= ��B.1 <  ��B<+7  ��B.1  ��B<+8 ��B;: #b <Ul* E.?\
�?\
�?	\	
 ?
\.(��  / 
       xx 0 R       h~ *       �r� 3 �      XC� 2 4      �� 8 �      �� 7 �      �S� 9 ;      �S� 6 |      8T� 5 &      (V� 4 �      �V� 1 �       Z� .         8b�  : �                       
  	         . * - -  ���  @ @ @  @  ! ! ! ! ! ! ! ! ! ! ! !         @@ @    @@            �͘��(�� �;� h�� �Y�(v� �Y�XY�Y��X��X��Z� �^"hB� HW��x�8�� ���q�T�X}�V�Hx�V�xV�(V�8T��S��S��U�HS��R��R�XR�R��a�Q�hQ�(�� Q��P�xȃ� XP�h��h�� ��a�aHqؑ� �M�xc�iH�� YX��L�XM�8º (m��k�X2�4��4��`�X��X������h�3�h1�z�Ⱦ� ���8��HO��H���T� ���h��H=��o�8	��� v���bXZ�XX� $ $  ���       �w inherit/room/room.c d/changan/duchang.c include/globals.h include/ansi.h tc ͷ�� sd ˫�� qx ���� sx ɢ�� short �ĳ� long� ������������СС�Ķ�����ֻҪ��˵�����Ķľߣ����ﶼ�С���
�����������������ľ�����Ů�ǳԳԵ�Ц���������ǵĴ�ţ����������
������������㼸���Ϳ��������������в���ص�������ǽ�Ϲ���һ
���ң�������
 exits south /d/changan/qixiang3	 item_desc sign&�����ӷ���:
bet <kind> <amount> <money> 

ֻ���������Ų���Ƿ��

kind:
    ͷ�� <tc>��������ÿ�ο���ǰȷ����      ��һӮ��ʮ��
    ˫�� <sd>����������ͬ����Ϊż����      ��һӮʮ��
    ���� <qx>������֮��Ϊ�ߣ�              ��һӮ��
    ɢ�� <sx>������֮��Ϊ�����壬�ţ�ʮһ����һӮ��
 objects /d/changan/npc/zhuangjia no_fight do_bet bet gamble_prepare gamble_start gamble_perform gamble_finish
 zhuang jia ׯ�Ҷ�û�У���Ҫ��˭�ģ�
 �㻹�ǵ�ׯ��������˵�ɣ�
 %s %d %s& ��ʹ�ã� bet <Ѻ������> <��Ŀ> <����>
 ��ҪѺ��һ������
 _money ������û������Ǯ��
 ���ѺһЩǮ��
 query_amount �����ϵ�Ǯ����Ѻ��
3 ׯ�Һ�������ô�����������ô�ࣿ������Ʊ������ע��

 base_value query ��ע���ʮ���ƽ�
 gamble_bet/amount
 query_temp ���Ѿ�Ѻ���ˡ�
 �������ڶ��أ��Ե�Ƭ�̡�
 gamble_bet/kind set_temp gamble_bet/money $N�ó�%s%s%s��Ѻ��%s�ϡ�
	 base_unit name
 add_amount better $N����Ѻ����Ǯ����Ҫ�ˡ�

 gamble_bet delete_temp7 ����������
����������
�����񡡩�
����������
����������
7 ����������
����������
���񡡡�
����������
����������
7 ����������
���񡡡���
�����񡡩�
��������
����������
7 ����������
���񡡡�
����������
���񡡡�
����������
7 ����������
���񡡡�
�����񡡩�
���񡡡�
����������
7 ����������
���񡡡�
���񡡡�
���񡡡�
����������
 ׯ�ҳ������¿��̣�Ԥ��ͷ�ʣ�
 ׯ�ҽ���ö������������һ����
 ׯ�ҽе���ͷ������ ��
3 ����ׯ��������˳�ֽ������������ջأ����ڿ���ѺǮ��
 ׯ�Һ���������ͣѺ��
 �ֲ���������ͷ�������� ��
1 Ȼ����ö�����ӽ��������ѣ�һ�ֳ�һ��ҡ��������
"  ���ѵ����������ϣ��������˳�����
 /clone/money/
 set_amount $NӮ��%s%s%s��
 move! ׯ�ҽ�$NѺ�������е�%s%s%s���ߡ�
 none of them
 ׯ�ҽе��� �������̣�
 ���� 
 room_status big res gutous create init valid_leave rdm display_bet player_loses player_wins gamble_finish gamble_perform gamble_start gamble_prepare do_bet random2 #global_init#��    �    N  [ 
M	Y	_bpt	vw{~����������	������������������������
�
�
��������
�
�
�����	�	�
�
�����
				 $	%"'())*	+,-.3	4556	78	9	:	;?	@
ABH
IJ
KOMNOPQW
X\Z[\]^ehjk"mopstvw xz{~������������������	�*�  