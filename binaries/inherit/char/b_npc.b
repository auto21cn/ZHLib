MUDB$tD�esD! include/globals.h include/ansi.h  inherit/char/b_npc.c�  �>        h     ��p������  p  p  �  0  0  0  �  �  �  �  �          x  �	 d 2    -C~^+	 , � A.  �� - h%% �
	  /$ �
  / �� -�
  /$ �
  / �� -. h%% �
  /% �
	  / <  -.] < �h$
 < 
=Zh -�  .�l  �
 � .�
 < l  .�
 
d�
  ]�+ � 
da]<v	���>vu

`^]<
d 
d]+  =Z� �@B `+	 !��  `+	 "�
�`+	 #��  `+	 $��  `+	 %�Ja+	 &�G`+	 '�+�(�+�)�+�*�+�+�+�,�+�-�+�.�+�/�+�0�+�1�+�'-+ (/+ */+ ).+ +1+ ,0+ +1+�,0+�-<�]] ��B<+�"��z -.��, �=Z <-  2�� - h%% �
	  /$ �
  / 2�� -�
  /$ �
  / 2�� -�
 +  3�.+  456 ^7^�.+ 
� 8+ <  95:� ^;^� ^<^�.�
=  45> ^?^�.<@ A+ 

` BA+ �  al ^C^�.+ % + �
D 4 E�.< +�-+ 
� 8+ ]<�   ]<�]�
F < G56 ^� ^H^�.�
F <BIm=\=\��
 0$ ��
F 07 45:� ^J^<^K^<^L^�
 ^K^�
F ^M^�.+ % + �
D 4 N�.< +�-.�
 =Z� O�.�+  P�.
l ]+ =Z� Q�� R5:� ^S^56 ^T^�U<^V^l& W�� 8+ 	 8+ X+	 -.
] �  ,  -< l +  ,  -�
Y F+  ,  -+ � ,  -�
Z ]�J~^_]�T 
]�Z< < [
 < \ ]^+ ^_^< ` ^a^<^b^c^l"  l. ,  -., � .8��  �       X��  �      (� ��      �� �       H� ��       �� �      H� ��       �� �        8b�  �q                         �	� ���������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������@      @    @  @@ @@  @@@  @!    	! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !                         ! ! ! ! ! ! ! ! ! ! ! !     ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !        @@@                       ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !      ! ! ! ! ! ! ! ! ! ! ! !      ! ! ! ! ! ! ! ! ! ! ! ! ! !  ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !      @@      @      ! ! ! ! ! ! ! ! ! ! ! !        ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !  ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !      ! ! ! ! ! ! ! ! ! ! ! !  ! !   ! ! ! ! ! ! ! ! ! ! ! ! ! ! @!  ! ! ! ! ! ! ! ! ! ! ! ! ! ! !   !  !     @@!   !  ! !    ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !        !                                      ���>(�� �;� ��H�H��������ȃ� H�� h��ȅx�(�؄��H�x=���ú (�H����x�(�(�(tؒ(� �h(i�g�� �� H*�U� x+� (� �� �׹ Xٹ H�� ��� ��� ��� �� (�x�8q� Xؾ �� �ȑx��� 8����x�� ��菻 H�����H����
� ��H��D� ����� ��x����H���(L��h������h� 8���Hú 8W� ��H���Z� ��~X�� (��       �w inherit/char/npc.c inherit/char/b_npc.c include/globals.h include/ansi.h bunch/zhengzhao init_area_npc
 is_quester /adm/daemons/questd
 accept_ask	 is_waiter ultra_quest/next_npc query name ultra_quest/npc /adm/daemons/ultra_questd ask_information xquest/target_npc xquest/init_npc /u/sanben/xquest/xquest ultra_quest/quest/obj need_accede is_area_room bunch/area_file set bunch/bunch_name bunch/npc_file
 bunch_name max_zhongcheng
 zhongcheng bunch/zhongcheng bunch /adm/daemons/bunchd query_bunch_fame
 combat_exp max_qi max_jing	 max_neili neili level jiali force parry dodge sword cuff strike huashan-neigong feiyan-huixiang huashan-jianfa hunyuan-zhang	 poyu-quan accept_object! say ���ǰ����ֵܣ��α���˿�����
 say  /adm/daemons/rankd
 query_self ֻ���书����Ȥ������һ����̸��
 invite/target say �޹�����»����֪ query_respect ���� �к����⣿
 money_id query_self_rude% ֻ��Ǯ����Ȥ������������Լ����Űɡ�
 value invite/money say �Ҳ���˵������ ���ƽ���һ����Ҳ���У�
 meili/ say �����������Ǯ������ζԵ�������������֣�
 id say �����ز���ʶ��Ϊ�θ� ��
 %s:%s ������Ҫ���� ( )������ )��
1 say ����������Ķ���������ζԵ�������������֣�
) say �ף���û�м����ᣬ������μ����أ�
% say ���Ƕ���ͬ����֣����º������
 remove_area_into_bunch say ��Ȼ
 ��˿����� ������Ҳ���ܶԲ����㰡��
 $N���������ᡸ ����
 add_area_into_bunch no_clean_up bunch/npc_id bunch/kaifa add save channel:rumor [1;35m��ҥ������ĳ�ˣ����� ��ɱ�� short �Ŀ����Ƚ�Ϊ ��
 [2;37;0m setup die accept_object
 accept_ask need_accede do_join_bunch init_area_npc is_bunch_npc #global_init#��    �    N  9   PQR
WXZ[\]^_`fghisuxz|���	������������	�	�	�	�	�	�	�	�	�	�	�	�	�	�	�	�	�	��������
�����������
���������	���
	"#%)1379
=JKMNPQS	UVXb
deghjk
mnp
qsuvwzyz|  