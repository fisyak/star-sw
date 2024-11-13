#!/usr/bin/perl
use strict;
use warnings;
our @Runs = ( # onl CURRENT | SortRun.pl 
'0000'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5008155',	 last => '5008155',	 list => '',  beginTime => '20040109.005425'}, # 	2004-01-09	00:54:25	2004-01-09	01:05:43	timestamp = productionMinBias_RF
'0001'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5008157',	 last => '5008161',	 list => '',  beginTime => '20040109.010543'}, # 	2004-01-09	01:05:43	2004-01-09	02:00:24
'0002'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5008163',	 last => '5008163',	 list => '',  beginTime => '20040109.020024'}, # 	2004-01-09	02:00:24	2004-01-09	06:19:29
'0003'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009003',	 last => '5009009',	 list => '',  beginTime => '20040109.061929'}, # 	2004-01-09	06:19:29	2004-01-09	07:03:11
'0004'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009014',	 last => '5009022',	 list => '',  beginTime => '20040109.070311'}, # 	2004-01-09	07:03:11	2004-01-09	08:16:05
'0005'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009024',	 last => '5009024',	 list => '',  beginTime => '20040109.081605'}, # 	2004-01-09	08:16:05	2004-01-09	08:30:01
'0006'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009028',	 last => '5009028',	 list => '',  beginTime => '20040109.083001'}, # 	2004-01-09	08:30:01	2004-01-09	08:54:56
'0007'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009031',	 last => '5009032',	 list => '',  beginTime => '20040109.085456'}, # 	2004-01-09	08:54:56	2004-01-09	09:32:12
'0008'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009035',	 last => '5009036',	 list => '',  beginTime => '20040109.093212'}, # 	2004-01-09	09:32:12	2004-01-09	10:33:23
'0009'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009040',	 last => '5009040',	 list => '',  beginTime => '20040109.103323'}, # 	2004-01-09	10:33:23	2004-01-09	10:41:21
'0010'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009042',	 last => '5009042',	 list => '',  beginTime => '20040109.104121'}, # 	2004-01-09	10:41:21	2004-01-09	11:39:07
'0011'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009049',	 last => '5009051',	 list => '',  beginTime => '20040109.113907'}, # 	2004-01-09	11:39:07	2004-01-09	22:57:25
'0012'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009134',	 last => '5009135',	 list => '',  beginTime => '20040109.225725'}, # 	2004-01-09	22:57:25	2004-01-09	23:11:03
'0013'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009138',	 last => '5009139',	 list => '',  beginTime => '20040109.231103'}, # 	2004-01-09	23:11:03	2004-01-10	02:49:59
'0014'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009145',	 last => '5009149',	 list => '',  beginTime => '20040110.024959'}, # 	2004-01-10	02:49:59	2004-01-10	03:19:08
'0015'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009156',	 last => '5009157',	 list => '',  beginTime => '20040110.031908'}, # 	2004-01-10	03:19:08	2004-01-10	03:31:40
'0016'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009159',	 last => '5009160',	 list => '',  beginTime => '20040110.033140'}, # 	2004-01-10	03:31:40	2004-01-10	03:41:07
'0017'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009162',	 last => '5009166',	 list => '',  beginTime => '20040110.034107'}, # 	2004-01-10	03:41:07	2004-01-10	04:56:25
'0018'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5009169',	 last => '5009169',	 list => '',  beginTime => '20040110.045625'}, # 	2004-01-10	04:56:25	2004-01-11	02:35:09
'0019'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5010086',	 last => '5010087',	 list => '',  beginTime => '20040111.023509'}, # 	2004-01-11	02:35:09	2004-01-11	06:41:43
'0020'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011003',	 last => '5011004',	 list => '',  beginTime => '20040111.064143'}, # 	2004-01-11	06:41:43	2004-01-11	11:20:31
'0021'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011012',	 last => '5011012',	 list => '',  beginTime => '20040111.112031'}, # 	2004-01-11	11:20:31	2004-01-11	11:55:58
'0022'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011014',	 last => '5011014',	 list => '',  beginTime => '20040111.115558'}, # 	2004-01-11	11:55:58	2004-01-11	12:15:35
'0023'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011016',	 last => '5011017',	 list => '',  beginTime => '20040111.121535'}, # 	2004-01-11	12:15:35	2004-01-11	12:47:41
'0024'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011019',	 last => '5011020',	 list => '',  beginTime => '20040111.124741'}, # 	2004-01-11	12:47:41	2004-01-11	13:35:03
'0025'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011022',	 last => '5011022',	 list => '',  beginTime => '20040111.133503'}, # 	2004-01-11	13:35:03	2004-01-12	00:30:29
'0026'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011035',	 last => '5011035',	 list => '',  beginTime => '20040112.003029'}, # 	2004-01-12	00:30:29	2004-01-12	00:51:06
'0027'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011040',	 last => '5011041',	 list => '',  beginTime => '20040112.005106'}, # 	2004-01-12	00:51:06	2004-01-12	01:29:02
'0028'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011044',	 last => '5011044',	 list => '',  beginTime => '20040112.012902'}, # 	2004-01-12	01:29:02	2004-01-12	01:45:43
'0029'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011046',	 last => '5011048',	 list => '',  beginTime => '20040112.014543'}, # 	2004-01-12	01:45:43	2004-01-12	02:50:01
'0030'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011050',	 last => '5011051',	 list => '',  beginTime => '20040112.025001'}, # 	2004-01-12	02:50:01	2004-01-12	03:15:46
'0031'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011054',	 last => '5011058',	 list => '',  beginTime => '20040112.031546'}, # 	2004-01-12	03:15:46	2004-01-12	03:59:02
'0032'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5011060',	 last => '5011062',	 list => '',  beginTime => '20040112.035902'}, # 	2004-01-12	03:59:02	2004-01-12	07:57:14
'0033'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5012006',	 last => '5012008',	 list => '',  beginTime => '20040112.075714'}, # 	2004-01-12	07:57:14	2004-01-12	08:32:24
'0034'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5012010',	 last => '5012010',	 list => '',  beginTime => '20040112.083224'}, # 	2004-01-12	08:32:24	2004-01-12	09:28:44
'0035'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5012018',	 last => '5012020',	 list => '',  beginTime => '20040112.092844'}, # 	2004-01-12	09:28:44	2004-01-12	09:54:08
'0036'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5012022',	 last => '5012023',	 list => '',  beginTime => '20040112.095408'}, # 	2004-01-12	09:54:08	2004-01-12	10:45:17
'0037'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5012028',	 last => '5012028',	 list => '',  beginTime => '20040112.104517'}, # 	2004-01-12	10:45:17	2004-01-12	10:53:56
'0038'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5012030',	 last => '5012031',	 list => '',  beginTime => '20040112.105356'}, # 	2004-01-12	10:53:56	2004-01-13	04:46:51
'0039'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5012141',	 last => '5012141',	 list => '',  beginTime => '20040113.044651'}, # 	2004-01-13	04:46:51	2004-01-13	05:29:04
'0040'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5012143',	 last => '5012143',	 list => '',  beginTime => '20040113.052904'}, # 	2004-01-13	05:29:04	2004-01-13	08:28:09
'0041'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5013007',	 last => '5013007',	 list => '',  beginTime => '20040113.082809'}, # 	2004-01-13	08:28:09	2004-01-13	09:01:52
'0042'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5013011',	 last => '5013011',	 list => '',  beginTime => '20040113.090152'}, # 	2004-01-13	09:01:52	2004-01-13	09:45:08
'0043'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5013013',	 last => '5013014',	 list => '',  beginTime => '20040113.094508'}, # 	2004-01-13	09:45:08	2004-01-15	05:41:10
'0044'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5014073',	 last => '5014074',	 list => '',  beginTime => '20040115.054110'}, # 	2004-01-15	05:41:10	2004-01-15	06:07:08
'0045'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5015002',	 last => '5015003',	 list => '',  beginTime => '20040115.060708'}, # 	2004-01-15	06:07:08	2004-01-15	07:06:04
'0046'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5015006',	 last => '5015006',	 list => '',  beginTime => '20040115.070604'}, # 	2004-01-15	07:06:04	2004-01-15	12:24:54
'0047'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5015012',	 last => '5015013',	 list => '',  beginTime => '20040115.122454'}, # 	2004-01-15	12:24:54	2004-01-16	03:22:31
'0048'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5015053',	 last => '5015053',	 list => '',  beginTime => '20040116.032231'}, # 	2004-01-16	03:22:31	2004-01-16	12:06:07
'0049'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5016006',	 last => '5016007',	 list => '',  beginTime => '20040116.120607'}, # 	2004-01-16	12:06:07	2004-01-17	03:37:15
'0050'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5016032',	 last => '5016033',	 list => '',  beginTime => '20040117.033715'}, # 	2004-01-17	03:37:15	2004-01-17	04:53:37
'0051'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5016035',	 last => '5016037',	 list => '',  beginTime => '20040117.045337'}, # 	2004-01-17	04:53:37	2004-01-17	06:08:44
'0052'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5017001',	 last => '5017002',	 list => '',  beginTime => '20040117.060844'}, # 	2004-01-17	06:08:44	2004-01-17	09:18:05
'0053'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5017004',	 last => '5017005',	 list => '',  beginTime => '20040117.091805'}, # 	2004-01-17	09:18:05	2004-01-17	10:47:13
'0054'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5017008',	 last => '5017013',	 list => '',  beginTime => '20040117.104713'}, # 	2004-01-17	10:47:13	2004-01-17	14:41:50
'0055'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5017016',	 last => '5017018',	 list => '',  beginTime => '20040117.144150'}, # 	2004-01-17	14:41:50	2004-01-18	09:46:34
'0056'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5018003',	 last => '5018005',	 list => '',  beginTime => '20040118.094634'}, # 	2004-01-18	09:46:34	2004-01-18	20:48:29
'0057'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5018021',	 last => '5018028',	 list => '',  beginTime => '20040118.204829'}, # 	2004-01-18	20:48:29	2004-01-19	03:15:49
'0058'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5018031',	 last => '5018031',	 list => '',  beginTime => '20040119.031549'}, # 	2004-01-19	03:15:49	2004-01-19	03:45:38
'0059'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5018033',	 last => '5018033',	 list => '',  beginTime => '20040119.034538'}, # 	2004-01-19	03:45:38	2004-01-19	04:43:44
'0060'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5018035',	 last => '5018035',	 list => '',  beginTime => '20040119.044344'}, # 	2004-01-19	04:43:44	2004-01-19	05:04:07
'0061'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5018037',	 last => '5018039',	 list => '',  beginTime => '20040119.050407'}, # 	2004-01-19	05:04:07	2004-01-19	08:15:09
'0062'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5019003',	 last => '5019004',	 list => '',  beginTime => '20040119.081509'}, # 	2004-01-19	08:15:09	2004-01-19	09:07:41
'0063'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5019007',	 last => '5019008',	 list => '',  beginTime => '20040119.090741'}, # 	2004-01-19	09:07:41	2004-01-19	09:41:02
'0064'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5019010',	 last => '5019016',	 list => '',  beginTime => '20040119.094102'}, # 	2004-01-19	09:41:02	2004-01-19	11:37:45
'0065'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5019018',	 last => '5019019',	 list => '',  beginTime => '20040119.113745'}, # 	2004-01-19	11:37:45	2004-01-19	12:12:36
'0066'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5019021',	 last => '5019027',	 list => '',  beginTime => '20040119.121236'}, # 	2004-01-19	12:12:36	2004-01-19	22:54:38
'0067'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5019033',	 last => '5019034',	 list => '',  beginTime => '20040119.225438'}, # 	2004-01-19	22:54:38	2004-01-20	00:15:44
'0068'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5019036',	 last => '5019036',	 list => '',  beginTime => '20040120.001544'}, # 	2004-01-20	00:15:44	2004-01-20	00:42:14
'0069'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5019038',	 last => '5019048',	 list => '',  beginTime => '20040120.004214'}, # 	2004-01-20	00:42:14	2004-01-20	04:39:18
'0070'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5019050',	 last => '5019050',	 list => '',  beginTime => '20040120.043918'}, # 	2004-01-20	04:39:18	2004-01-20	13:33:26
'0071'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5020017',	 last => '5020021',	 list => '',  beginTime => '20040120.133326'}, # 	2004-01-20	13:33:26	2004-01-20	14:44:18
'0072'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5020024',	 last => '5020024',	 list => '',  beginTime => '20040120.144418'}, # 	2004-01-20	14:44:18	2004-01-20	14:58:51
'0073'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5020028',	 last => '5020031',	 list => '',  beginTime => '20040120.145851'}, # 	2004-01-20	14:58:51	2004-01-22	23:26:38
'0074'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5022033',	 last => '5022033',	 list => '',  beginTime => '20040122.232638'}, # 	2004-01-22	23:26:38	2004-01-23	01:40:15
'0075'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5022036',	 last => '5022036',	 list => '',  beginTime => '20040123.014015'}, # 	2004-01-23	01:40:15	2004-01-23	04:03:49
'0076'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5022048',	 last => '5022049',	 list => '',  beginTime => '20040123.040349'}, # 	2004-01-23	04:03:49	2004-01-23	04:20:50
'0077'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5022051',	 last => '5022052',	 list => '',  beginTime => '20040123.042050'}, # 	2004-01-23	04:20:50	2004-01-23	05:09:42
'0078'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5022055',	 last => '5022055',	 list => '',  beginTime => '20040123.050942'}, # 	2004-01-23	05:09:42	2004-01-23	06:07:17
'0079'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023001',	 last => '5023001',	 list => '',  beginTime => '20040123.060717'}, # 	2004-01-23	06:07:17	2004-01-23	06:38:18
'0080'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023004',	 last => '5023008',	 list => '',  beginTime => '20040123.063818'}, # 	2004-01-23	06:38:18	2004-01-23	08:46:43
'0081'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023010',	 last => '5023010',	 list => '',  beginTime => '20040123.084643'}, # 	2004-01-23	08:46:43	2004-01-23	11:23:59
'0082'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023016',	 last => '5023020',	 list => '',  beginTime => '20040123.112359'}, # 	2004-01-23	11:23:59	2004-01-23	12:41:30
'0083'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023023',	 last => '5023038',	 list => '',  beginTime => '20040123.124130'}, # 	2004-01-23	12:41:30	2004-01-23	14:28:15
'0084'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023041',	 last => '5023047',	 list => '',  beginTime => '20040123.142815'}, # 	2004-01-23	14:28:15	2004-01-23	17:04:21
'0085'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023058',	 last => '5023060',	 list => '',  beginTime => '20040123.170421'}, # 	2004-01-23	17:04:21	2004-01-23	21:29:53
'0086'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023099',	 last => '5023100',	 list => '',  beginTime => '20040123.212953'}, # 	2004-01-23	21:29:53	2004-01-23	21:44:48
'0087'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023102',	 last => '5023103',	 list => '',  beginTime => '20040123.214448'}, # 	2004-01-23	21:44:48	2004-01-23	22:20:54
'0088'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023107',	 last => '5023109',	 list => '',  beginTime => '20040123.222054'}, # 	2004-01-23	22:20:54	2004-01-23	23:21:50
'0089'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023114',	 last => '5023116',	 list => '',  beginTime => '20040123.232150'}, # 	2004-01-23	23:21:50	2004-01-23	23:57:18
'0090'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023118',	 last => '5023119',	 list => '',  beginTime => '20040123.235718'}, # 	2004-01-23	23:57:18	2004-01-24	00:45:31
'0091'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023126',	 last => '5023130',	 list => '',  beginTime => '20040124.004531'}, # 	2004-01-24	00:45:31	2004-01-24	03:46:47
'0092'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023132',	 last => '5023132',	 list => '',  beginTime => '20040124.034647'}, # 	2004-01-24	03:46:47	2004-01-24	04:05:19
'0093'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023134',	 last => '5023136',	 list => '',  beginTime => '20040124.040519'}, # 	2004-01-24	04:05:19	2004-01-24	04:40:51
'0094'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023139',	 last => '5023139',	 list => '',  beginTime => '20040124.044051'}, # 	2004-01-24	04:40:51	2004-01-24	05:05:50
'0095'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023144',	 last => '5023144',	 list => '',  beginTime => '20040124.050550'}, # 	2004-01-24	05:05:50	2004-01-24	05:46:20
'0096'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5023146',	 last => '5023146',	 list => '',  beginTime => '20040124.054620'}, # 	2004-01-24	05:46:20	2004-01-24	06:30:01
'0097'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024001',	 last => '5024001',	 list => '',  beginTime => '20040124.063001'}, # 	2004-01-24	06:30:01	2004-01-24	06:40:02
'0098'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024005',	 last => '5024005',	 list => '',  beginTime => '20040124.064002'}, # 	2004-01-24	06:40:02	2004-01-24	12:31:07
'0099'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024009',	 last => '5024009',	 list => '',  beginTime => '20040124.123107'}, # 	2004-01-24	12:31:07	2004-01-24	13:31:16
'0100'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024012',	 last => '5024014',	 list => '',  beginTime => '20040124.133116'}, # 	2004-01-24	13:31:16	2004-01-24	14:32:03
'0101'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024016',	 last => '5024017',	 list => '',  beginTime => '20040124.143203'}, # 	2004-01-24	14:32:03	2004-01-24	15:00:19
'0102'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024020',	 last => '5024022',	 list => '',  beginTime => '20040124.150019'}, # 	2004-01-24	15:00:19	2004-01-24	17:26:36
'0103'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024024',	 last => '5024024',	 list => '',  beginTime => '20040124.172636'}, # 	2004-01-24	17:26:36	2004-01-24	20:12:59
'0104'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024050',	 last => '5024056',	 list => '',  beginTime => '20040124.201259'}, # 	2004-01-24	20:12:59	2004-01-24	21:41:54
'0105'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024058',	 last => '5024059',	 list => '',  beginTime => '20040124.214154'}, # 	2004-01-24	21:41:54	2004-01-24	22:04:22
'0106'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024062',	 last => '5024062',	 list => '',  beginTime => '20040124.220422'}, # 	2004-01-24	22:04:22	2004-01-24	22:18:23
'0107'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024064',	 last => '5024066',	 list => '',  beginTime => '20040124.221823'}, # 	2004-01-24	22:18:23	2004-01-24	23:00:36
'0108'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024068',	 last => '5024072',	 list => '',  beginTime => '20040124.230036'}, # 	2004-01-24	23:00:36	2004-01-25	01:39:07
'0109'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024075',	 last => '5024079',	 list => '',  beginTime => '20040125.013907'}, # 	2004-01-25	01:39:07	2004-01-25	02:22:04
'0110'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024081',	 last => '5024087',	 list => '',  beginTime => '20040125.022204'}, # 	2004-01-25	02:22:04	2004-01-25	03:12:53
'0111'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024090',	 last => '5024090',	 list => '',  beginTime => '20040125.031253'}, # 	2004-01-25	03:12:53	2004-01-25	03:20:22
'0112'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024092',	 last => '5024093',	 list => '',  beginTime => '20040125.032022'}, # 	2004-01-25	03:20:22	2004-01-25	04:31:15
'0113'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024095',	 last => '5024095',	 list => '',  beginTime => '20040125.043115'}, # 	2004-01-25	04:31:15	2004-01-25	04:54:37
'0114'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5024097',	 last => '5024098',	 list => '',  beginTime => '20040125.045437'}, # 	2004-01-25	04:54:37	2004-01-25	08:19:23
'0115'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025003',	 last => '5025003',	 list => '',  beginTime => '20040125.081923'}, # 	2004-01-25	08:19:23	2004-01-25	08:41:27
'0116'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025005',	 last => '5025009',	 list => '',  beginTime => '20040125.084127'}, # 	2004-01-25	08:41:27	2004-01-25	09:44:02
'0117'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025011',	 last => '5025012',	 list => '',  beginTime => '20040125.094402'}, # 	2004-01-25	09:44:02	2004-01-25	10:19:50
'0118'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025015',	 last => '5025020',	 list => '',  beginTime => '20040125.101950'}, # 	2004-01-25	10:19:50	2004-01-25	11:08:54
'0119'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025022',	 last => '5025025',	 list => '',  beginTime => '20040125.110854'}, # 	2004-01-25	11:08:54	2004-01-25	11:24:34
'0120'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025028',	 last => '5025028',	 list => '',  beginTime => '20040125.112434'}, # 	2004-01-25	11:24:34	2004-01-25	11:32:59
'0121'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025033',	 last => '5025039',	 list => '',  beginTime => '20040125.113259'}, # 	2004-01-25	11:32:59	2004-01-25	12:33:40
'0122'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025041',	 last => '5025041',	 list => '',  beginTime => '20040125.123340'}, # 	2004-01-25	12:33:40	2004-01-25	15:34:00
'0123'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025048',	 last => '5025050',	 list => '',  beginTime => '20040125.153400'}, # 	2004-01-25	15:34:00	2004-01-25	16:22:12
'0124'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025054',	 last => '5025055',	 list => '',  beginTime => '20040125.162212'}, # 	2004-01-25	16:22:12	2004-01-25	17:38:53
'0125'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025067',	 last => '5025068',	 list => '',  beginTime => '20040125.173853'}, # 	2004-01-25	17:38:53	2004-01-25	18:14:44
'0126'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025070',	 last => '5025070',	 list => '',  beginTime => '20040125.181444'}, # 	2004-01-25	18:14:44	2004-01-25	18:44:02
'0127'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025072',	 last => '5025074',	 list => '',  beginTime => '20040125.184402'}, # 	2004-01-25	18:44:02	2004-01-25	23:13:26
'0128'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025118',	 last => '5025121',	 list => '',  beginTime => '20040125.231326'}, # 	2004-01-25	23:13:26	2004-01-26	01:21:33
'0129'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025123',	 last => '5025126',	 list => '',  beginTime => '20040126.012133'}, # 	2004-01-26	01:21:33	2004-01-26	04:04:46
'0130'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5025129',	 last => '5025130',	 list => '',  beginTime => '20040126.040446'}, # 	2004-01-26	04:04:46	2004-01-26	09:09:55
'0131'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026003',	 last => '5026004',	 list => '',  beginTime => '20040126.090955'}, # 	2004-01-26	09:09:55	2004-01-26	10:32:52
'0132'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026006',	 last => '5026006',	 list => '',  beginTime => '20040126.103252'}, # 	2004-01-26	10:32:52	2004-01-26	17:39:37
'0133'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026037',	 last => '5026038',	 list => '',  beginTime => '20040126.173937'}, # 	2004-01-26	17:39:37	2004-01-26	18:58:57
'0134'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026040',	 last => '5026040',	 list => '',  beginTime => '20040126.185857'}, # 	2004-01-26	18:58:57	2004-01-26	19:14:10
'0135'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026042',	 last => '5026042',	 list => '',  beginTime => '20040126.191410'}, # 	2004-01-26	19:14:10	2004-01-26	19:23:31
'0136'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026045',	 last => '5026052',	 list => '',  beginTime => '20040126.192331'}, # 	2004-01-26	19:23:31	2004-01-26	21:15:20
'0137'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026055',	 last => '5026060',	 list => '',  beginTime => '20040126.211520'}, # 	2004-01-26	21:15:20	2004-01-26	22:16:12
'0138'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026062',	 last => '5026063',	 list => '',  beginTime => '20040126.221612'}, # 	2004-01-26	22:16:12	2004-01-26	22:56:16
'0139'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026066',	 last => '5026066',	 list => '',  beginTime => '20040126.225616'}, # 	2004-01-26	22:56:16	2004-01-27	02:03:39
'0140'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026079',	 last => '5026081',	 list => '',  beginTime => '20040127.020339'}, # 	2004-01-27	02:03:39	2004-01-27	02:28:10
'0141'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026083',	 last => '5026084',	 list => '',  beginTime => '20040127.022810'}, # 	2004-01-27	02:28:10	2004-01-27	03:30:29
'0142'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026086',	 last => '5026090',	 list => '',  beginTime => '20040127.033029'}, # 	2004-01-27	03:30:29	2004-01-27	04:45:09
'0143'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5026092',	 last => '5026095',	 list => '',  beginTime => '20040127.044509'}, # 	2004-01-27	04:45:09	2004-01-27	06:52:35
'0144'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5027002',	 last => '5027004',	 list => '',  beginTime => '20040127.065235'}, # 	2004-01-27	06:52:35	2004-01-27	08:29:45
'0145'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5027021',	 last => '5027021',	 list => '',  beginTime => '20040127.082945'}, # 	2004-01-27	08:29:45	2004-01-27	08:49:03
'0146'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5027024',	 last => '5027024',	 list => '',  beginTime => '20040127.084903'}, # 	2004-01-27	08:49:03	2004-01-27	09:06:43
'0147'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5027027',	 last => '5027027',	 list => '',  beginTime => '20040127.090643'}, # 	2004-01-27	09:06:43	2004-01-27	09:38:22
'0148'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5027029',	 last => '5027029',	 list => '',  beginTime => '20040127.093822'}, # 	2004-01-27	09:38:22	2004-01-27	11:18:38
'0149'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5027034',	 last => '5027034',	 list => '',  beginTime => '20040127.111838'}, # 	2004-01-27	11:18:38	2004-01-27	11:39:07
'0150'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5027037',	 last => '5027039',	 list => '',  beginTime => '20040127.113907'}, # 	2004-01-27	11:39:07	2004-01-27	13:13:25
'0151'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5027044',	 last => '5027044',	 list => '',  beginTime => '20040127.131325'}, # 	2004-01-27	13:13:25	2004-01-28	20:25:10
'0152'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028057',	 last => '5028057',	 list => '',  beginTime => '20040128.202510'}, # 	2004-01-28	20:25:10	2004-01-28	22:02:25	timestamp = productionMinBias_FF
'0153'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028066',	 last => '5028071',	 list => '',  beginTime => '20040128.220225'}, # 	2004-01-28	22:02:25	2004-01-28	23:05:42
'0154'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028074',	 last => '5028075',	 list => '',  beginTime => '20040128.230542'}, # 	2004-01-28	23:05:42	2004-01-28	23:25:44
'0155'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028077',	 last => '5028081',	 list => '',  beginTime => '20040128.232544'}, # 	2004-01-28	23:25:44	2004-01-29	02:19:00
'0156'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028090',	 last => '5028090',	 list => '',  beginTime => '20040129.021900'}, # 	2004-01-29	02:19:00	2004-01-29	02:47:55
'0157'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028093',	 last => '5028093',	 list => '',  beginTime => '20040129.024755'}, # 	2004-01-29	02:47:55	2004-01-29	02:59:45
'0158'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028097',	 last => '5028097',	 list => '',  beginTime => '20040129.025945'}, # 	2004-01-29	02:59:45	2004-01-29	03:02:00
'0159'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028099',	 last => '5028099',	 list => '',  beginTime => '20040129.030200'}, # 	2004-01-29	03:02:00	2004-01-29	03:03:44
'0160'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028101',	 last => '5028102',	 list => '',  beginTime => '20040129.030344'}, # 	2004-01-29	03:03:44	2004-01-29	03:59:30
'0161'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028112',	 last => '5028113',	 list => '',  beginTime => '20040129.035930'}, # 	2004-01-29	03:59:30	2004-01-29	04:16:19
'0162'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028115',	 last => '5028115',	 list => '',  beginTime => '20040129.041619'}, # 	2004-01-29	04:16:19	2004-01-29	04:41:30
'0163'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028118',	 last => '5028119',	 list => '',  beginTime => '20040129.044130'}, # 	2004-01-29	04:41:30	2004-01-29	05:54:23
'0164'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5028122',	 last => '5028122',	 list => '',  beginTime => '20040129.055423'}, # 	2004-01-29	05:54:23	2004-01-29	06:29:18
'0165'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029004',	 last => '5029004',	 list => '',  beginTime => '20040129.062918'}, # 	2004-01-29	06:29:18	2004-01-29	06:56:18
'0166'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029006',	 last => '5029006',	 list => '',  beginTime => '20040129.065618'}, # 	2004-01-29	06:56:18	2004-01-29	10:48:59
'0167'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029010',	 last => '5029015',	 list => '',  beginTime => '20040129.104859'}, # 	2004-01-29	10:48:59	2004-01-29	13:42:18
'0168'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029019',	 last => '5029019',	 list => '',  beginTime => '20040129.134218'}, # 	2004-01-29	13:42:18	2004-01-29	18:09:26
'0169'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029042',	 last => '5029044',	 list => '',  beginTime => '20040129.180926'}, # 	2004-01-29	18:09:26	2004-01-29	23:35:10
'0170'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029081',	 last => '5029081',	 list => '',  beginTime => '20040129.233510'}, # 	2004-01-29	23:35:10	2004-01-29	23:54:40
'0171'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029087',	 last => '5029087',	 list => '',  beginTime => '20040129.235440'}, # 	2004-01-29	23:54:40	2004-01-30	00:02:03
'0172'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029091',	 last => '5029092',	 list => '',  beginTime => '20040130.000203'}, # 	2004-01-30	00:02:03	2004-01-30	01:42:28
'0173'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029100',	 last => '5029100',	 list => '',  beginTime => '20040130.014228'}, # 	2004-01-30	01:42:28	2004-01-30	02:03:08
'0174'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029107',	 last => '5029110',	 list => '',  beginTime => '20040130.020308'}, # 	2004-01-30	02:03:08	2004-01-30	04:26:27
'0175'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029115',	 last => '5029115',	 list => '',  beginTime => '20040130.042627'}, # 	2004-01-30	04:26:27	2004-01-30	04:53:40
'0176'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5029118',	 last => '5029118',	 list => '',  beginTime => '20040130.045340'}, # 	2004-01-30	04:53:40	2004-01-30	07:52:54
'0177'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030006',	 last => '5030006',	 list => '',  beginTime => '20040130.075254'}, # 	2004-01-30	07:52:54	2004-01-30	08:08:35
'0178'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030008',	 last => '5030008',	 list => '',  beginTime => '20040130.080835'}, # 	2004-01-30	08:08:35	2004-01-30	08:15:25
'0179'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030010',	 last => '5030012',	 list => '',  beginTime => '20040130.081525'}, # 	2004-01-30	08:15:25	2004-01-30	09:45:09
'0180'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030018',	 last => '5030021',	 list => '',  beginTime => '20040130.094509'}, # 	2004-01-30	09:45:09	2004-01-30	14:06:06
'0181'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030025',	 last => '5030028',	 list => '',  beginTime => '20040130.140606'}, # 	2004-01-30	14:06:06	2004-01-30	15:00:24
'0182'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030034',	 last => '5030034',	 list => '',  beginTime => '20040130.150024'}, # 	2004-01-30	15:00:24	2004-01-30	16:19:46
'0183'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030042',	 last => '5030045',	 list => '',  beginTime => '20040130.161946'}, # 	2004-01-30	16:19:46	2004-01-30	17:16:21
'0184'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030047',	 last => '5030048',	 list => '',  beginTime => '20040130.171621'}, # 	2004-01-30	17:16:21	2004-01-30	22:19:18
'0185'=> {trig=>'productionMinBiasHT',   	field => 'FF',	first=> '5030092',	 last => '5030092',	 list => '',  beginTime => '20040130.221918'}, # 	2004-01-30	22:19:18	2004-01-30	22:43:40	timestamp = productionMinBiasHT_FF
'0186'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030098',	 last => '5030100',	 list => '',  beginTime => '20040130.224340'}, # 	2004-01-30	22:43:40	2004-01-30	23:32:17	timestamp = productionMinBias_FF
'0187'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030102',	 last => '5030106',	 list => '',  beginTime => '20040130.233217'}, # 	2004-01-30	23:32:17	2004-01-31	00:50:01
'0188'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5030111',	 last => '5030114',	 list => '',  beginTime => '20040131.005001'}, # 	2004-01-31	00:50:01	2004-01-31	06:40:32
'0189'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031002',	 last => '5031004',	 list => '',  beginTime => '20040131.064032'}, # 	2004-01-31	06:40:32	2004-01-31	07:09:24
'0190'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031007',	 last => '5031007',	 list => '',  beginTime => '20040131.070924'}, # 	2004-01-31	07:09:24	2004-01-31	07:44:35
'0191'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031009',	 last => '5031012',	 list => '',  beginTime => '20040131.074435'}, # 	2004-01-31	07:44:35	2004-01-31	14:56:28
'0192'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031015',	 last => '5031016',	 list => '',  beginTime => '20040131.145628'}, # 	2004-01-31	14:56:28	2004-01-31	15:28:39
'0193'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031019',	 last => '5031019',	 list => '',  beginTime => '20040131.152839'}, # 	2004-01-31	15:28:39	2004-01-31	16:20:40
'0194'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031027',	 last => '5031027',	 list => '',  beginTime => '20040131.162040'}, # 	2004-01-31	16:20:40	2004-01-31	17:56:15
'0195'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031034',	 last => '5031037',	 list => '',  beginTime => '20040131.175615'}, # 	2004-01-31	17:56:15	2004-01-31	22:15:28
'0196'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031046',	 last => '5031049',	 list => '',  beginTime => '20040131.221528'}, # 	2004-01-31	22:15:28	2004-02-01	00:16:10
'0197'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031051',	 last => '5031052',	 list => '',  beginTime => '20040201.001610'}, # 	2004-02-01	00:16:10	2004-02-01	00:30:04
'0198'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031055',	 last => '5031055',	 list => '',  beginTime => '20040201.003004'}, # 	2004-02-01	00:30:04	2004-02-01	01:24:03
'0199'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031057',	 last => '5031058',	 list => '',  beginTime => '20040201.012403'}, # 	2004-02-01	01:24:03	2004-02-01	05:48:34
'0200'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5031066',	 last => '5031067',	 list => '',  beginTime => '20040201.054834'}, # 	2004-02-01	05:48:34	2004-02-01	06:43:25
'0201'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032001',	 last => '5032001',	 list => '',  beginTime => '20040201.064325'}, # 	2004-02-01	06:43:25	2004-02-01	07:33:40
'0202'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032005',	 last => '5032009',	 list => '',  beginTime => '20040201.073340'}, # 	2004-02-01	07:33:40	2004-02-01	10:00:34
'0203'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032011',	 last => '5032011',	 list => '',  beginTime => '20040201.100034'}, # 	2004-02-01	10:00:34	2004-02-01	11:31:58
'0204'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032016',	 last => '5032018',	 list => '',  beginTime => '20040201.113158'}, # 	2004-02-01	11:31:58	2004-02-01	13:33:45
'0205'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032022',	 last => '5032022',	 list => '',  beginTime => '20040201.133345'}, # 	2004-02-01	13:33:45	2004-02-01	15:13:39
'0206'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032026',	 last => '5032027',	 list => '',  beginTime => '20040201.151339'}, # 	2004-02-01	15:13:39	2004-02-01	17:52:15
'0207'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032039',	 last => '5032039',	 list => '',  beginTime => '20040201.175215'}, # 	2004-02-01	17:52:15	2004-02-01	18:57:26
'0208'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032048',	 last => '5032050',	 list => '',  beginTime => '20040201.185726'}, # 	2004-02-01	18:57:26	2004-02-02	00:45:53
'0209'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032054',	 last => '5032056',	 list => '',  beginTime => '20040202.004553'}, # 	2004-02-02	00:45:53	2004-02-02	02:16:45
'0210'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5032058',	 last => '5032059',	 list => '',  beginTime => '20040202.021645'}, # 	2004-02-02	02:16:45	2004-02-02	06:36:28
'0211'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5033002',	 last => '5033004',	 list => '',  beginTime => '20040202.063628'}, # 	2004-02-02	06:36:28	2004-02-02	07:58:54
'0212'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5033008',	 last => '5033008',	 list => '',  beginTime => '20040202.075854'}, # 	2004-02-02	07:58:54	2004-02-02	08:37:49
'0213'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5033016',	 last => '5033017',	 list => '',  beginTime => '20040202.083749'}, # 	2004-02-02	08:37:49	2004-02-02	10:00:00
'0214'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5033020',	 last => '5033023',	 list => '',  beginTime => '20040202.100000'}, # 	2004-02-02	10:00:00	2004-02-02	12:23:07
'0215'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5033028',	 last => '5033030',	 list => '',  beginTime => '20040202.122307'}, # 	2004-02-02	12:23:07	2004-02-02	13:32:33
'0216'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5033047',	 last => '5033051',	 list => '',  beginTime => '20040202.133233'}, # 	2004-02-02	13:32:33	2004-02-02	19:51:02
'0217'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5033084',	 last => '5033084',	 list => '',  beginTime => '20040202.195102'}, # 	2004-02-02	19:51:02	2004-02-02	20:13:24
'0218'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5033087',	 last => '5033091',	 list => '',  beginTime => '20040202.201324'}, # 	2004-02-02	20:13:24	2004-02-03	00:19:41
'0219'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5033118',	 last => '5033121',	 list => '',  beginTime => '20040203.001941'}, # 	2004-02-03	00:19:41	2004-02-03	01:35:34
'0220'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5033122',	 last => '5033122',	 list => '',  beginTime => '20040203.013534'}, # 	2004-02-03	01:35:34	2004-02-03	02:00:13	timestamp = productionHigh_FF
'0221'=> {trig=>'productionMid',         	field => 'FF',	first=> '5033126',	 last => '5033127',	 list => '',  beginTime => '20040203.020013'}, # 	2004-02-03	02:00:13	2004-02-03	02:30:24	timestamp = productionMid_FF
'0222'=> {trig=>'productionLow',         	field => 'FF',	first=> '5033130',	 last => '5033130',	 list => '',  beginTime => '20040203.023024'}, # 	2004-02-03	02:30:24	2004-02-03	02:39:53	timestamp = productionLow_FF
'0223'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5033131',	 last => '5033131',	 list => '',  beginTime => '20040203.023953'}, # 	2004-02-03	02:39:53	2004-02-03	02:49:11	timestamp = productionCentral_FF
'0224'=> {trig=>'productionLow',         	field => 'FF',	first=> '5033132',	 last => '5033133',	 list => '',  beginTime => '20040203.024911'}, # 	2004-02-03	02:49:11	2004-02-03	04:00:56	timestamp = productionLow_FF
'0225'=> {trig=>'productionLow',         	field => 'FF',	first=> '5033135',	 last => '5033135',	 list => '',  beginTime => '20040203.040056'}, # 	2004-02-03	04:00:56	2004-02-03	15:15:37
'0226'=> {trig=>'productionLow',         	field => 'FF',	first=> '5034025',	 last => '5034025',	 list => '',  beginTime => '20040203.151537'}, # 	2004-02-03	15:15:37	2004-02-03	15:41:12
'0227'=> {trig=>'productionLow',         	field => 'FF',	first=> '5034027',	 last => '5034027',	 list => '',  beginTime => '20040203.154112'}, # 	2004-02-03	15:41:12	2004-02-03	23:04:36
'0228'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5034095',	 last => '5034095',	 list => '',  beginTime => '20040203.230436'}, # 	2004-02-03	23:04:36	2004-02-03	23:13:39	timestamp = productionHigh_FF
'0229'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5034097',	 last => '5034098',	 list => '',  beginTime => '20040203.231339'}, # 	2004-02-03	23:13:39	2004-02-04	00:23:03
'0230'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5034102',	 last => '5034102',	 list => '',  beginTime => '20040204.002303'}, # 	2004-02-04	00:23:03	2004-02-04	13:22:31	timestamp = productionMinBias_FF
'0231'=> {trig=>'productionHigh',        	field => 'ZF',	first=> '5035002',	 last => '5035002',	 list => '',  beginTime => '20040204.132231'}, # 	2004-02-04	13:22:31	2004-02-04	14:05:00	timestamp = productionHigh_ZF
'0232'=> {trig=>'productionHigh',        	field => 'ZF',	first=> '5035006',	 last => '5035006',	 list => '',  beginTime => '20040204.140500'}, # 	2004-02-04	14:05:00	2004-02-05	14:43:51
'0233'=> {trig=>'productionLow',         	field => 'FF',	first=> '5036042',	 last => '5036042',	 list => '',  beginTime => '20040205.144351'}, # 	2004-02-05	14:43:51	2004-02-06	05:38:46	timestamp = productionLow_FF
'0234'=> {trig=>'productionMid',         	field => 'FF',	first=> '5036136',	 last => '5036136',	 list => '',  beginTime => '20040206.053846'}, # 	2004-02-06	05:38:46	2004-02-06	05:45:00	timestamp = productionMid_FF
'0235'=> {trig=>'productionMid',         	field => 'FF',	first=> '5036138',	 last => '5036138',	 list => '',  beginTime => '20040206.054500'}, # 	2004-02-06	05:45:00	2004-02-06	05:57:32
'0236'=> {trig=>'productionLow',         	field => 'FF',	first=> '5036140',	 last => '5036140',	 list => '',  beginTime => '20040206.055732'}, # 	2004-02-06	05:57:32	2004-02-06	06:06:33	timestamp = productionLow_FF
'0237'=> {trig=>'productionLow',         	field => 'FF',	first=> '5037001',	 last => '5037003',	 list => '',  beginTime => '20040206.060633'}, # 	2004-02-06	06:06:33	2004-02-06	10:19:54
'0238'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5037012',	 last => '5037012',	 list => '',  beginTime => '20040206.101954'}, # 	2004-02-06	10:19:54	2004-02-06	10:33:48	timestamp = productionHigh_FF
'0239'=> {trig=>'productionMid',         	field => 'FF',	first=> '5037013',	 last => '5037013',	 list => '',  beginTime => '20040206.103348'}, # 	2004-02-06	10:33:48	2004-02-06	10:47:29	timestamp = productionMid_FF
'0240'=> {trig=>'productionMid',         	field => 'FF',	first=> '5037017',	 last => '5037017',	 list => '',  beginTime => '20040206.104729'}, # 	2004-02-06	10:47:29	2004-02-06	11:27:09
'0241'=> {trig=>'productionLow',         	field => 'FF',	first=> '5037030',	 last => '5037031',	 list => '',  beginTime => '20040206.112709'}, # 	2004-02-06	11:27:09	2004-02-06	14:14:05	timestamp = productionLow_FF
'0242'=> {trig=>'productionMid',         	field => 'FF',	first=> '5037034',	 last => '5037036',	 list => '',  beginTime => '20040206.141405'}, # 	2004-02-06	14:14:05	2004-02-06	14:33:49	timestamp = productionMid_FF
'0243'=> {trig=>'productionMid',         	field => 'FF',	first=> '5037038',	 last => '5037038',	 list => '',  beginTime => '20040206.143349'}, # 	2004-02-06	14:33:49	2004-02-06	15:25:25
'0244'=> {trig=>'productionLow',         	field => 'FF',	first=> '5037047',	 last => '5037047',	 list => '',  beginTime => '20040206.152525'}, # 	2004-02-06	15:25:25	2004-02-06	15:47:47	timestamp = productionLow_FF
'0245'=> {trig=>'productionLow',         	field => 'FF',	first=> '5037051',	 last => '5037053',	 list => '',  beginTime => '20040206.154747'}, # 	2004-02-06	15:47:47	2004-02-06	16:10:29
'0246'=> {trig=>'productionLow',         	field => 'FF',	first=> '5037057',	 last => '5037058',	 list => '',  beginTime => '20040206.161029'}, # 	2004-02-06	16:10:29	2004-02-06	16:58:35
'0247'=> {trig=>'productionLow',         	field => 'FF',	first=> '5037075',	 last => '5037075',	 list => '',  beginTime => '20040206.165835'}, # 	2004-02-06	16:58:35	2004-02-06	17:17:41
'0248'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5037077',	 last => '5037078',	 list => '',  beginTime => '20040206.171741'}, # 	2004-02-06	17:17:41	2004-02-07	08:07:03	timestamp = productionMinBias_FF
'0249'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5038009',	 last => '5038009',	 list => '',  beginTime => '20040207.080703'}, # 	2004-02-07	08:07:03	2004-02-07	08:37:13	timestamp = productionHigh_FF
'0250'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5038012',	 last => '5038012',	 list => '',  beginTime => '20040207.083713'}, # 	2004-02-07	08:37:13	2004-02-07	08:51:24
'0251'=> {trig=>'productionMid',         	field => 'FF',	first=> '5038013',	 last => '5038013',	 list => '',  beginTime => '20040207.085124'}, # 	2004-02-07	08:51:24	2004-02-07	09:00:14	timestamp = productionMid_FF
'0252'=> {trig=>'productionMid',         	field => 'FF',	first=> '5038015',	 last => '5038015',	 list => '',  beginTime => '20040207.090014'}, # 	2004-02-07	09:00:14	2004-02-07	09:33:56
'0253'=> {trig=>'productionMid',         	field => 'FF',	first=> '5038023',	 last => '5038024',	 list => '',  beginTime => '20040207.093356'}, # 	2004-02-07	09:33:56	2004-02-07	09:53:32
'0254'=> {trig=>'productionLow',         	field => 'FF',	first=> '5038025',	 last => '5038025',	 list => '',  beginTime => '20040207.095332'}, # 	2004-02-07	09:53:32	2004-02-07	10:04:33	timestamp = productionLow_FF
'0255'=> {trig=>'productionLow',         	field => 'FF',	first=> '5038027',	 last => '5038028',	 list => '',  beginTime => '20040207.100433'}, # 	2004-02-07	10:04:33	2004-02-07	20:13:39
'0256'=> {trig=>'productionMid',         	field => 'FF',	first=> '5038051',	 last => '5038051',	 list => '',  beginTime => '20040207.201339'}, # 	2004-02-07	20:13:39	2004-02-07	20:22:25	timestamp = productionMid_FF
'0257'=> {trig=>'productionMid',         	field => 'FF',	first=> '5038054',	 last => '5038057',	 list => '',  beginTime => '20040207.202225'}, # 	2004-02-07	20:22:25	2004-02-07	23:14:45
'0258'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5038064',	 last => '5038064',	 list => '',  beginTime => '20040207.231445'}, # 	2004-02-07	23:14:45	2004-02-07	23:23:34	timestamp = productionHigh_FF
'0259'=> {trig=>'productionMid',         	field => 'FF',	first=> '5038065',	 last => '5038065',	 list => '',  beginTime => '20040207.232334'}, # 	2004-02-07	23:23:34	2004-02-07	23:46:09	timestamp = productionMid_FF
'0260'=> {trig=>'productionMid',         	field => 'FF',	first=> '5038067',	 last => '5038067',	 list => '',  beginTime => '20040207.234609'}, # 	2004-02-07	23:46:09	2004-02-07	23:58:55
'0261'=> {trig=>'productionLow',         	field => 'FF',	first=> '5038068',	 last => '5038068',	 list => '',  beginTime => '20040207.235855'}, # 	2004-02-07	23:58:55	2004-02-08	00:43:03	timestamp = productionLow_FF
'0262'=> {trig=>'productionLow',         	field => 'FF',	first=> '5038071',	 last => '5038073',	 list => '',  beginTime => '20040208.004303'}, # 	2004-02-08	00:43:03	2004-02-08	02:34:28
'0263'=> {trig=>'productionLow',         	field => 'FF',	first=> '5038076',	 last => '5038076',	 list => '',  beginTime => '20040208.023428'}, # 	2004-02-08	02:34:28	2004-02-08	04:28:08
'0264'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5038081',	 last => '5038081',	 list => '',  beginTime => '20040208.042808'}, # 	2004-02-08	04:28:08	2004-02-08	04:38:41	timestamp = productionHigh_FF
'0265'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5038083',	 last => '5038084',	 list => '',  beginTime => '20040208.043841'}, # 	2004-02-08	04:38:41	2004-02-08	05:52:54
'0266'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5038085',	 last => '5038085',	 list => '',  beginTime => '20040208.055254'}, # 	2004-02-08	05:52:54	2004-02-08	06:08:50	timestamp = productionMinBias_FF
'0267'=> {trig=>'productionMid',         	field => 'FF',	first=> '5039002',	 last => '5039002',	 list => '',  beginTime => '20040208.060850'}, # 	2004-02-08	06:08:50	2004-02-08	06:19:22	timestamp = productionMid_FF
'0268'=> {trig=>'productionMid',         	field => 'FF',	first=> '5039004',	 last => '5039004',	 list => '',  beginTime => '20040208.061922'}, # 	2004-02-08	06:19:22	2004-02-08	06:47:19
'0269'=> {trig=>'productionLow',         	field => 'FF',	first=> '5039005',	 last => '5039008',	 list => '',  beginTime => '20040208.064719'}, # 	2004-02-08	06:47:19	2004-02-08	18:54:53	timestamp = productionLow_FF
'0270'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5039032',	 last => '5039033',	 list => '',  beginTime => '20040208.185453'}, # 	2004-02-08	18:54:53	2004-02-08	19:51:47	timestamp = productionHigh_FF
'0271'=> {trig=>'productionMid',         	field => 'FF',	first=> '5039035',	 last => '5039035',	 list => '',  beginTime => '20040208.195147'}, # 	2004-02-08	19:51:47	2004-02-08	20:07:54	timestamp = productionMid_FF
'0272'=> {trig=>'productionMid',         	field => 'FF',	first=> '5039037',	 last => '5039037',	 list => '',  beginTime => '20040208.200754'}, # 	2004-02-08	20:07:54	2004-02-08	20:33:38
'0273'=> {trig=>'productionLow',         	field => 'FF',	first=> '5039038',	 last => '5039039',	 list => '',  beginTime => '20040208.203338'}, # 	2004-02-08	20:33:38	2004-02-08	21:50:01	timestamp = productionLow_FF
'0274'=> {trig=>'productionLow',         	field => 'FF',	first=> '5039047',	 last => '5039048',	 list => '',  beginTime => '20040208.215001'}, # 	2004-02-08	21:50:01	2004-02-08	22:40:58
'0275'=> {trig=>'productionLow',         	field => 'FF',	first=> '5039050',	 last => '5039050',	 list => '',  beginTime => '20040208.224058'}, # 	2004-02-08	22:40:58	2004-02-09	00:16:45
'0276'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5039066',	 last => '5039066',	 list => '',  beginTime => '20040209.001645'}, # 	2004-02-09	00:16:45	2004-02-09	16:10:43	timestamp = productionHigh_FF
'0277'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5040025',	 last => '5040025',	 list => '',  beginTime => '20040209.161043'}, # 	2004-02-09	16:10:43	2004-02-09	16:57:37
'0278'=> {trig=>'productionMid',         	field => 'FF',	first=> '5040027',	 last => '5040028',	 list => '',  beginTime => '20040209.165737'}, # 	2004-02-09	16:57:37	2004-02-09	17:42:14	timestamp = productionMid_FF
'0279'=> {trig=>'productionLow',         	field => 'FF',	first=> '5040035',	 last => '5040035',	 list => '',  beginTime => '20040209.174214'}, # 	2004-02-09	17:42:14	2004-02-09	18:09:04	timestamp = productionLow_FF
'0280'=> {trig=>'productionLow',         	field => 'FF',	first=> '5040038',	 last => '5040043',	 list => '',  beginTime => '20040209.180904'}, # 	2004-02-09	18:09:04	2004-02-09	22:44:26
'0281'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5040069',	 last => '5040072',	 list => '',  beginTime => '20040209.224426'}, # 	2004-02-09	22:44:26	2004-02-10	00:12:02	timestamp = productionHigh_FF
'0282'=> {trig=>'productionMid',         	field => 'FF',	first=> '5040076',	 last => '5040077',	 list => '',  beginTime => '20040210.001202'}, # 	2004-02-10	00:12:02	2004-02-10	00:45:40	timestamp = productionMid_FF
'0283'=> {trig=>'productionLow',         	field => 'FF',	first=> '5040080',	 last => '5040080',	 list => '',  beginTime => '20040210.004540'}, # 	2004-02-10	00:45:40	2004-02-10	00:58:40	timestamp = productionLow_FF
'0284'=> {trig=>'productionLow',         	field => 'FF',	first=> '5040084',	 last => '5040086',	 list => '',  beginTime => '20040210.005840'}, # 	2004-02-10	00:58:40	2004-02-10	02:13:22
'0285'=> {trig=>'productionLow',         	field => 'FF',	first=> '5040088',	 last => '5040088',	 list => '',  beginTime => '20040210.021322'}, # 	2004-02-10	02:13:22	2004-02-10	02:28:55
'0286'=> {trig=>'productionLow',         	field => 'FF',	first=> '5040092',	 last => '5040092',	 list => '',  beginTime => '20040210.022855'}, # 	2004-02-10	02:28:55	2004-02-10	05:31:27
'0287'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5040131',	 last => '5040131',	 list => '',  beginTime => '20040210.053127'}, # 	2004-02-10	05:31:27	2004-02-10	06:22:37	timestamp = productionHigh_FF
'0288'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5041002',	 last => '5041002',	 list => '',  beginTime => '20040210.062237'}, # 	2004-02-10	06:22:37	2004-02-10	09:03:39
'0289'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5041005',	 last => '5041005',	 list => '',  beginTime => '20040210.090339'}, # 	2004-02-10	09:03:39	2004-02-10	09:50:24
'0290'=> {trig=>'productionMid',         	field => 'FF',	first=> '5041007',	 last => '5041008',	 list => '',  beginTime => '20040210.095024'}, # 	2004-02-10	09:50:24	2004-02-10	10:43:32	timestamp = productionMid_FF
'0291'=> {trig=>'productionLow',         	field => 'FF',	first=> '5041009',	 last => '5041009',	 list => '',  beginTime => '20040210.104332'}, # 	2004-02-10	10:43:32	2004-02-10	12:04:45	timestamp = productionLow_FF
'0292'=> {trig=>'productionLow',         	field => 'FF',	first=> '5041013',	 last => '5041013',	 list => '',  beginTime => '20040210.120445'}, # 	2004-02-10	12:04:45	2004-02-10	12:23:25
'0293'=> {trig=>'productionLow',         	field => 'FF',	first=> '5041016',	 last => '5041016',	 list => '',  beginTime => '20040210.122325'}, # 	2004-02-10	12:23:25	2004-02-10	14:34:14
'0294'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5041047',	 last => '5041047',	 list => '',  beginTime => '20040210.143414'}, # 	2004-02-10	14:34:14	2004-02-10	14:57:30	timestamp = productionHigh_FF
'0295'=> {trig=>'productionMid',         	field => 'FF',	first=> '5041048',	 last => '5041048',	 list => '',  beginTime => '20040210.145730'}, # 	2004-02-10	14:57:30	2004-02-10	15:10:22	timestamp = productionMid_FF
'0296'=> {trig=>'productionMid',         	field => 'FF',	first=> '5041051',	 last => '5041051',	 list => '',  beginTime => '20040210.151022'}, # 	2004-02-10	15:10:22	2004-02-10	15:26:06
'0297'=> {trig=>'productionMid',         	field => 'FF',	first=> '5041054',	 last => '5041054',	 list => '',  beginTime => '20040210.152606'}, # 	2004-02-10	15:26:06	2004-02-10	15:40:06
'0298'=> {trig=>'productionMid',         	field => 'FF',	first=> '5041056',	 last => '5041056',	 list => '',  beginTime => '20040210.154006'}, # 	2004-02-10	15:40:06	2004-02-10	16:04:55
'0299'=> {trig=>'productionLow',         	field => 'FF',	first=> '5041058',	 last => '5041058',	 list => '',  beginTime => '20040210.160455'}, # 	2004-02-10	16:04:55	2004-02-10	16:37:07	timestamp = productionLow_FF
'0300'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5041059',	 last => '5041059',	 list => '',  beginTime => '20040210.163707'}, # 	2004-02-10	16:37:07	2004-02-10	17:03:36	timestamp = productionMinBias_FF
'0301'=> {trig=>'productionLow',         	field => 'FF',	first=> '5041062',	 last => '5041064',	 list => '',  beginTime => '20040210.170336'}, # 	2004-02-10	17:03:36	2004-02-11	01:08:27	timestamp = productionLow_FF
'0302'=> {trig=>'productionMid',         	field => 'FF',	first=> '5041097',	 last => '5041097',	 list => '',  beginTime => '20040211.010827'}, # 	2004-02-11	01:08:27	2004-02-11	01:40:54	timestamp = productionMid_FF
'0303'=> {trig=>'productionLow',         	field => 'FF',	first=> '5041099',	 last => '5041104',	 list => '',  beginTime => '20040211.014054'}, # 	2004-02-11	01:40:54	2004-02-11	07:03:29	timestamp = productionLow_FF
'0304'=> {trig=>'productionMid',         	field => 'FF',	first=> '5042003',	 last => '5042003',	 list => '',  beginTime => '20040211.070329'}, # 	2004-02-11	07:03:29	2004-02-11	09:30:34	timestamp = productionMid_FF
'0305'=> {trig=>'productionMid',         	field => 'FF',	first=> '5042007',	 last => '5042007',	 list => '',  beginTime => '20040211.093034'}, # 	2004-02-11	09:30:34	2004-02-11	10:12:09
'0306'=> {trig=>'productionLow',         	field => 'FF',	first=> '5042012',	 last => '5042013',	 list => '',  beginTime => '20040211.101209'}, # 	2004-02-11	10:12:09	2004-02-11	10:59:51	timestamp = productionLow_FF
'0307'=> {trig=>'productionLow',         	field => 'FF',	first=> '5042015',	 last => '5042015',	 list => '',  beginTime => '20040211.105951'}, # 	2004-02-11	10:59:51	2004-02-12	00:34:42
'0308'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5042077',	 last => '5042077',	 list => '',  beginTime => '20040212.003442'}, # 	2004-02-12	00:34:42	2004-02-12	01:28:45	timestamp = productionHigh_FF
'0309'=> {trig=>'productionMid',         	field => 'FF',	first=> '5042078',	 last => '5042078',	 list => '',  beginTime => '20040212.012845'}, # 	2004-02-12	01:28:45	2004-02-12	02:16:00	timestamp = productionMid_FF
'0310'=> {trig=>'productionLow',         	field => 'FF',	first=> '5042082',	 last => '5042083',	 list => '',  beginTime => '20040212.021600'}, # 	2004-02-12	02:16:00	2004-02-12	03:28:38	timestamp = productionLow_FF
'0311'=> {trig=>'productionLow',         	field => 'FF',	first=> '5042085',	 last => '5042086',	 list => '',  beginTime => '20040212.032838'}, # 	2004-02-12	03:28:38	2004-02-12	03:55:53
'0312'=> {trig=>'productionLow',         	field => 'FF',	first=> '5042089',	 last => '5042089',	 list => '',  beginTime => '20040212.035553'}, # 	2004-02-12	03:55:53	2004-02-12	04:11:44
'0313'=> {trig=>'productionLow',         	field => 'FF',	first=> '5042091',	 last => '5042091',	 list => '',  beginTime => '20040212.041144'}, # 	2004-02-12	04:11:44	2004-02-12	05:37:03
'0314'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5042098',	 last => '5042098',	 list => '',  beginTime => '20040212.053703'}, # 	2004-02-12	05:37:03	2004-02-12	06:21:55	timestamp = productionHigh_FF
'0315'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5043004',	 last => '5043004',	 list => '',  beginTime => '20040212.062155'}, # 	2004-02-12	06:21:55	2004-02-12	07:02:51
'0316'=> {trig=>'productionMid',         	field => 'FF',	first=> '5043006',	 last => '5043007',	 list => '',  beginTime => '20040212.070251'}, # 	2004-02-12	07:02:51	2004-02-12	07:44:23	timestamp = productionMid_FF
'0317'=> {trig=>'productionLow',         	field => 'FF',	first=> '5043008',	 last => '5043009',	 list => '',  beginTime => '20040212.074423'}, # 	2004-02-12	07:44:23	2004-02-12	08:59:48	timestamp = productionLow_FF
'0318'=> {trig=>'productionLow',         	field => 'FF',	first=> '5043011',	 last => '5043012',	 list => '',  beginTime => '20040212.085948'}, # 	2004-02-12	08:59:48	2004-02-12	11:42:24
'0319'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5043020',	 last => '5043020',	 list => '',  beginTime => '20040212.114224'}, # 	2004-02-12	11:42:24	2004-02-12	12:16:36	timestamp = productionHigh_FF
'0320'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5043022',	 last => '5043022',	 list => '',  beginTime => '20040212.121636'}, # 	2004-02-12	12:16:36	2004-02-12	12:36:37
'0321'=> {trig=>'productionMid',         	field => 'FF',	first=> '5043023',	 last => '5043025',	 list => '',  beginTime => '20040212.123637'}, # 	2004-02-12	12:36:37	2004-02-12	13:42:26	timestamp = productionMid_FF
'0322'=> {trig=>'productionLow',         	field => 'FF',	first=> '5043027',	 last => '5043027',	 list => '',  beginTime => '20040212.134226'}, # 	2004-02-12	13:42:26	2004-02-12	13:51:29	timestamp = productionLow_FF
'0323'=> {trig=>'productionLow',         	field => 'FF',	first=> '5043029',	 last => '5043032',	 list => '',  beginTime => '20040212.135129'}, # 	2004-02-12	13:51:29	2004-02-12	15:45:43
'0324'=> {trig=>'productionLow',         	field => 'FF',	first=> '5043036',	 last => '5043037',	 list => '',  beginTime => '20040212.154543'}, # 	2004-02-12	15:45:43	2004-02-12	18:53:08
'0325'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5043065',	 last => '5043065',	 list => '',  beginTime => '20040212.185308'}, # 	2004-02-12	18:53:08	2004-02-12	19:04:43	timestamp = productionHigh_FF
'0326'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5043069',	 last => '5043069',	 list => '',  beginTime => '20040212.190443'}, # 	2004-02-12	19:04:43	2004-02-12	19:17:51
'0327'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5043073',	 last => '5043073',	 list => '',  beginTime => '20040212.191751'}, # 	2004-02-12	19:17:51	2004-02-12	20:01:14
'0328'=> {trig=>'productionMid',         	field => 'FF',	first=> '5043075',	 last => '5043075',	 list => '',  beginTime => '20040212.200114'}, # 	2004-02-12	20:01:14	2004-02-12	20:59:41	timestamp = productionMid_FF
'0329'=> {trig=>'productionLow',         	field => 'FF',	first=> '5043078',	 last => '5043084',	 list => '',  beginTime => '20040212.205941'}, # 	2004-02-12	20:59:41	2004-02-13	02:30:39	timestamp = productionLow_FF
'0330'=> {trig=>'productionLow',         	field => 'FF',	first=> '5043121',	 last => '5043122',	 list => '',  beginTime => '20040213.023039'}, # 	2004-02-13	02:30:39	2004-02-13	03:40:11
'0331'=> {trig=>'productionLow',         	field => 'FF',	first=> '5043125',	 last => '5043126',	 list => '',  beginTime => '20040213.034011'}, # 	2004-02-13	03:40:11	2004-02-13	06:09:58
'0332'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5044002',	 last => '5044004',	 list => '',  beginTime => '20040213.060958'}, # 	2004-02-13	06:09:58	2004-02-13	07:05:42	timestamp = productionHigh_FF
'0333'=> {trig=>'productionMid',         	field => 'FF',	first=> '5044006',	 last => '5044008',	 list => '',  beginTime => '20040213.070542'}, # 	2004-02-13	07:05:42	2004-02-13	08:06:05	timestamp = productionMid_FF
'0334'=> {trig=>'productionLow',         	field => 'FF',	first=> '5044011',	 last => '5044012',	 list => '',  beginTime => '20040213.080605'}, # 	2004-02-13	08:06:05	2004-02-13	09:24:08	timestamp = productionLow_FF
'0335'=> {trig=>'productionLow',         	field => 'FF',	first=> '5044014',	 last => '5044014',	 list => '',  beginTime => '20040213.092408'}, # 	2004-02-13	09:24:08	2004-02-13	11:30:49
'0336'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5044026',	 last => '5044026',	 list => '',  beginTime => '20040213.113049'}, # 	2004-02-13	11:30:49	2004-02-13	12:05:00	timestamp = productionHigh_FF
'0337'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5044029',	 last => '5044029',	 list => '',  beginTime => '20040213.120500'}, # 	2004-02-13	12:05:00	2004-02-13	12:33:00
'0338'=> {trig=>'productionMid',         	field => 'FF',	first=> '5044033',	 last => '5044033',	 list => '',  beginTime => '20040213.123300'}, # 	2004-02-13	12:33:00	2004-02-13	13:38:10	timestamp = productionMid_FF
'0339'=> {trig=>'productionLow',         	field => 'FF',	first=> '5044037',	 last => '5044038',	 list => '',  beginTime => '20040213.133810'}, # 	2004-02-13	13:38:10	2004-02-13	14:58:10	timestamp = productionLow_FF
'0340'=> {trig=>'productionLow',         	field => 'FF',	first=> '5044042',	 last => '5044042',	 list => '',  beginTime => '20040213.145810'}, # 	2004-02-13	14:58:10	2004-02-13	17:42:29
'0341'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5044066',	 last => '5044066',	 list => '',  beginTime => '20040213.174229'}, # 	2004-02-13	17:42:29	2004-02-13	18:15:49	timestamp = productionHigh_FF
'0342'=> {trig=>'productionMid',         	field => 'FF',	first=> '5044069',	 last => '5044069',	 list => '',  beginTime => '20040213.181549'}, # 	2004-02-13	18:15:49	2004-02-13	18:46:24	timestamp = productionMid_FF
'0343'=> {trig=>'productionLow',         	field => 'FF',	first=> '5044071',	 last => '5044071',	 list => '',  beginTime => '20040213.184624'}, # 	2004-02-13	18:46:24	2004-02-13	19:46:29	timestamp = productionLow_FF
'0344'=> {trig=>'productionLow',         	field => 'FF',	first=> '5044079',	 last => '5044084',	 list => '',  beginTime => '20040213.194629'}, # 	2004-02-13	19:46:29	2004-02-13	20:26:39
'0345'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5044085',	 last => '5044086',	 list => '',  beginTime => '20040213.202639'}, # 	2004-02-13	20:26:39	2004-02-13	20:54:04	timestamp = productionMinBias_FF
'0346'=> {trig=>'productionLow',         	field => 'FF',	first=> '5044088',	 last => '5044088',	 list => '',  beginTime => '20040213.205404'}, # 	2004-02-13	20:54:04	2004-02-13	22:56:34	timestamp = productionLow_FF
'0347'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5044102',	 last => '5044102',	 list => '',  beginTime => '20040213.225634'}, # 	2004-02-13	22:56:34	2004-02-13	23:16:42	timestamp = productionHigh_FF
'0348'=> {trig=>'productionMid',         	field => 'FF',	first=> '5044104',	 last => '5044104',	 list => '',  beginTime => '20040213.231642'}, # 	2004-02-13	23:16:42	2004-02-13	23:27:04	timestamp = productionMid_FF
'0349'=> {trig=>'productionMid',         	field => 'FF',	first=> '5044107',	 last => '5044107',	 list => '',  beginTime => '20040213.232704'}, # 	2004-02-13	23:27:04	2004-02-13	23:35:56
'0350'=> {trig=>'productionMid',         	field => 'FF',	first=> '5044109',	 last => '5044109',	 list => '',  beginTime => '20040213.233556'}, # 	2004-02-13	23:35:56	2004-02-13	23:56:04
'0351'=> {trig=>'productionMid',         	field => 'FF',	first=> '5044112',	 last => '5044112',	 list => '',  beginTime => '20040213.235604'}, # 	2004-02-13	23:56:04	2004-02-14	00:18:19
'0352'=> {trig=>'productionLow',         	field => 'FF',	first=> '5044113',	 last => '5044114',	 list => '',  beginTime => '20040214.001819'}, # 	2004-02-14	00:18:19	2004-02-14	01:11:54	timestamp = productionLow_FF
'0353'=> {trig=>'productionLow',         	field => 'FF',	first=> '5044116',	 last => '5044120',	 list => '',  beginTime => '20040214.011154'}, # 	2004-02-14	01:11:54	2004-02-14	05:15:08
'0354'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5044126',	 last => '5044126',	 list => '',  beginTime => '20040214.051508'}, # 	2004-02-14	05:15:08	2004-02-14	05:37:53	timestamp = productionHigh_FF
'0355'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5044128',	 last => '5044128',	 list => '',  beginTime => '20040214.053753'}, # 	2004-02-14	05:37:53	2004-02-14	05:50:44
'0356'=> {trig=>'productionMid',         	field => 'FF',	first=> '5044129',	 last => '5044129',	 list => '',  beginTime => '20040214.055044'}, # 	2004-02-14	05:50:44	2004-02-14	06:00:38	timestamp = productionMid_FF
'0357'=> {trig=>'productionMid',         	field => 'FF',	first=> '5045002',	 last => '5045002',	 list => '',  beginTime => '20040214.060038'}, # 	2004-02-14	06:00:38	2004-02-14	06:52:08
'0358'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045006',	 last => '5045007',	 list => '',  beginTime => '20040214.065208'}, # 	2004-02-14	06:52:08	2004-02-14	07:20:42	timestamp = productionLow_FF
'0359'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045010',	 last => '5045012',	 list => '',  beginTime => '20040214.072042'}, # 	2004-02-14	07:20:42	2004-02-14	08:02:12
'0360'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045015',	 last => '5045017',	 list => '',  beginTime => '20040214.080212'}, # 	2004-02-14	08:02:12	2004-02-14	10:57:58
'0361'=> {trig=>'productionMid',         	field => 'FF',	first=> '5045027',	 last => '5045027',	 list => '',  beginTime => '20040214.105758'}, # 	2004-02-14	10:57:58	2004-02-14	11:44:35	timestamp = productionMid_FF
'0362'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045029',	 last => '5045031',	 list => '',  beginTime => '20040214.114435'}, # 	2004-02-14	11:44:35	2004-02-14	18:50:44	timestamp = productionLow_FF
'0363'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5045058',	 last => '5045058',	 list => '',  beginTime => '20040214.185044'}, # 	2004-02-14	18:50:44	2004-02-14	19:18:53	timestamp = productionCentral_FF
'0364'=> {trig=>'productionMid',         	field => 'FF',	first=> '5045060',	 last => '5045060',	 list => '',  beginTime => '20040214.191853'}, # 	2004-02-14	19:18:53	2004-02-14	19:47:13	timestamp = productionMid_FF
'0365'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045062',	 last => '5045065',	 list => '',  beginTime => '20040214.194713'}, # 	2004-02-14	19:47:13	2004-02-14	21:26:04	timestamp = productionLow_FF
'0366'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045067',	 last => '5045067',	 list => '',  beginTime => '20040214.212604'}, # 	2004-02-14	21:26:04	2004-02-14	21:43:45
'0367'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045069',	 last => '5045069',	 list => '',  beginTime => '20040214.214345'}, # 	2004-02-14	21:43:45	2004-02-14	23:15:17
'0368'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5045076',	 last => '5045076',	 list => '',  beginTime => '20040214.231517'}, # 	2004-02-14	23:15:17	2004-02-15	00:08:08	timestamp = productionHigh_FF
'0369'=> {trig=>'productionMid',         	field => 'FF',	first=> '5045078',	 last => '5045078',	 list => '',  beginTime => '20040215.000808'}, # 	2004-02-15	00:08:08	2004-02-15	00:35:25	timestamp = productionMid_FF
'0370'=> {trig=>'productionMid',         	field => 'FF',	first=> '5045080',	 last => '5045080',	 list => '',  beginTime => '20040215.003525'}, # 	2004-02-15	00:35:25	2004-02-15	00:53:05
'0371'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045081',	 last => '5045081',	 list => '',  beginTime => '20040215.005305'}, # 	2004-02-15	00:53:05	2004-02-15	02:01:04	timestamp = productionLow_FF
'0372'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045083',	 last => '5045083',	 list => '',  beginTime => '20040215.020104'}, # 	2004-02-15	02:01:04	2004-02-15	02:09:45
'0373'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045085',	 last => '5045085',	 list => '',  beginTime => '20040215.020945'}, # 	2004-02-15	02:09:45	2004-02-15	02:59:43
'0374'=> {trig=>'productionLow',         	field => 'FF',	first=> '5045087',	 last => '5045087',	 list => '',  beginTime => '20040215.025943'}, # 	2004-02-15	02:59:43	2004-02-15	05:26:06
'0375'=> {trig=>'productionMid',         	field => 'FF',	first=> '5045096',	 last => '5045097',	 list => '',  beginTime => '20040215.052606'}, # 	2004-02-15	05:26:06	2004-02-15	05:44:14	timestamp = productionMid_FF
'0376'=> {trig=>'productionMid',         	field => 'FF',	first=> '5045100',	 last => '5045101',	 list => '',  beginTime => '20040215.054414'}, # 	2004-02-15	05:44:14	2004-02-15	06:12:32
'0377'=> {trig=>'productionLow',         	field => 'FF',	first=> '5046001',	 last => '5046001',	 list => '',  beginTime => '20040215.061232'}, # 	2004-02-15	06:12:32	2004-02-15	06:50:43	timestamp = productionLow_FF
'0378'=> {trig=>'productionLow',         	field => 'FF',	first=> '5046004',	 last => '5046004',	 list => '',  beginTime => '20040215.065043'}, # 	2004-02-15	06:50:43	2004-02-15	07:22:04
'0379'=> {trig=>'productionLow',         	field => 'FF',	first=> '5046010',	 last => '5046010',	 list => '',  beginTime => '20040215.072204'}, # 	2004-02-15	07:22:04	2004-02-15	09:51:25
'0380'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5046017',	 last => '5046018',	 list => '',  beginTime => '20040215.095125'}, # 	2004-02-15	09:51:25	2004-02-15	10:07:52	timestamp = productionHigh_FF
'0381'=> {trig=>'productionMid',         	field => 'FF',	first=> '5046019',	 last => '5046019',	 list => '',  beginTime => '20040215.100752'}, # 	2004-02-15	10:07:52	2004-02-15	10:35:13	timestamp = productionMid_FF
'0382'=> {trig=>'productionMid',         	field => 'FF',	first=> '5046023',	 last => '5046023',	 list => '',  beginTime => '20040215.103513'}, # 	2004-02-15	10:35:13	2004-02-15	11:02:28
'0383'=> {trig=>'productionLow',         	field => 'FF',	first=> '5046025',	 last => '5046027',	 list => '',  beginTime => '20040215.110228'}, # 	2004-02-15	11:02:28	2004-02-15	12:29:12	timestamp = productionLow_FF
'0384'=> {trig=>'productionLow',         	field => 'FF',	first=> '5046029',	 last => '5046029',	 list => '',  beginTime => '20040215.122912'}, # 	2004-02-15	12:29:12	2004-02-16	18:16:34
'0385'=> {trig=>'productionMid',         	field => 'FF',	first=> '5047032',	 last => '5047032',	 list => '',  beginTime => '20040216.181634'}, # 	2004-02-16	18:16:34	2004-02-16	18:23:00	timestamp = productionMid_FF
'0386'=> {trig=>'productionMid',         	field => 'FF',	first=> '5047034',	 last => '5047034',	 list => '',  beginTime => '20040216.182300'}, # 	2004-02-16	18:23:00	2004-02-16	18:52:49
'0387'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5047037',	 last => '5047037',	 list => '',  beginTime => '20040216.185249'}, # 	2004-02-16	18:52:49	2004-02-16	19:10:34	timestamp = productionCentral_FF
'0388'=> {trig=>'productionLow',         	field => 'FF',	first=> '5047039',	 last => '5047039',	 list => '',  beginTime => '20040216.191034'}, # 	2004-02-16	19:10:34	2004-02-16	19:50:31	timestamp = productionLow_FF
'0389'=> {trig=>'productionLow',         	field => 'FF',	first=> '5047041',	 last => '5047041',	 list => '',  beginTime => '20040216.195031'}, # 	2004-02-16	19:50:31	2004-02-16	22:30:04
'0390'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5047061',	 last => '5047063',	 list => '',  beginTime => '20040216.223004'}, # 	2004-02-16	22:30:04	2004-02-17	21:27:45	timestamp = productionHigh_FF
'0391'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5048018',	 last => '5048018',	 list => '',  beginTime => '20040217.212745'}, # 	2004-02-17	21:27:45	2004-02-17	21:44:51
'0392'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5048024',	 last => '5048024',	 list => '',  beginTime => '20040217.214451'}, # 	2004-02-17	21:44:51	2004-02-17	22:09:16
'0393'=> {trig=>'productionMid',         	field => 'FF',	first=> '5048025',	 last => '5048025',	 list => '',  beginTime => '20040217.220916'}, # 	2004-02-17	22:09:16	2004-02-17	22:17:16	timestamp = productionMid_FF
'0394'=> {trig=>'productionMid',         	field => 'FF',	first=> '5048027',	 last => '5048027',	 list => '',  beginTime => '20040217.221716'}, # 	2004-02-17	22:17:16	2004-02-17	22:57:12
'0395'=> {trig=>'productionMid',         	field => 'FF',	first=> '5048030',	 last => '5048030',	 list => '',  beginTime => '20040217.225712'}, # 	2004-02-17	22:57:12	2004-02-17	23:17:38
'0396'=> {trig=>'productionLow',         	field => 'FF',	first=> '5048033',	 last => '5048033',	 list => '',  beginTime => '20040217.231738'}, # 	2004-02-17	23:17:38	2004-02-18	00:18:43	timestamp = productionLow_FF
'0397'=> {trig=>'productionLow',         	field => 'FF',	first=> '5048045',	 last => '5048047',	 list => '',  beginTime => '20040218.001843'}, # 	2004-02-18	00:18:43	2004-02-19	06:52:25
'0398'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5050006',	 last => '5050007',	 list => '',  beginTime => '20040219.065225'}, # 	2004-02-19	06:52:25	2004-02-19	07:21:41	timestamp = productionHigh_FF
'0399'=> {trig=>'productionMid',         	field => 'FF',	first=> '5050009',	 last => '5050009',	 list => '',  beginTime => '20040219.072141'}, # 	2004-02-19	07:21:41	2004-02-19	07:44:59	timestamp = productionMid_FF
'0400'=> {trig=>'productionMid',         	field => 'FF',	first=> '5050011',	 last => '5050011',	 list => '',  beginTime => '20040219.074459'}, # 	2004-02-19	07:44:59	2004-02-19	08:22:29
'0401'=> {trig=>'productionLow',         	field => 'FF',	first=> '5050014',	 last => '5050015',	 list => '',  beginTime => '20040219.082229'}, # 	2004-02-19	08:22:29	2004-02-19	23:29:03	timestamp = productionLow_FF
'0402'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5050059',	 last => '5050060',	 list => '',  beginTime => '20040219.232903'}, # 	2004-02-19	23:29:03	2004-02-19	23:55:40	timestamp = productionHigh_FF
'0403'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5050062',	 last => '5050062',	 list => '',  beginTime => '20040219.235540'}, # 	2004-02-19	23:55:40	2004-02-20	00:39:24
'0404'=> {trig=>'productionMid',         	field => 'FF',	first=> '5050064',	 last => '5050065',	 list => '',  beginTime => '20040220.003924'}, # 	2004-02-20	00:39:24	2004-02-20	01:18:31	timestamp = productionMid_FF
'0405'=> {trig=>'productionLow',         	field => 'FF',	first=> '5050069',	 last => '5050070',	 list => '',  beginTime => '20040220.011831'}, # 	2004-02-20	01:18:31	2004-02-20	01:55:06	timestamp = productionLow_FF
'0406'=> {trig=>'productionLow',         	field => 'FF',	first=> '5050072',	 last => '5050073',	 list => '',  beginTime => '20040220.015506'}, # 	2004-02-20	01:55:06	2004-02-20	03:13:40
'0407'=> {trig=>'productionLow',         	field => 'FF',	first=> '5050076',	 last => '5050076',	 list => '',  beginTime => '20040220.031340'}, # 	2004-02-20	03:13:40	2004-02-20	09:53:45
'0408'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5051025',	 last => '5051026',	 list => '',  beginTime => '20040220.095345'}, # 	2004-02-20	09:53:45	2004-02-20	10:55:53	timestamp = productionHigh_FF
'0409'=> {trig=>'productionMid',         	field => 'FF',	first=> '5051028',	 last => '5051029',	 list => '',  beginTime => '20040220.105553'}, # 	2004-02-20	10:55:53	2004-02-20	11:47:42	timestamp = productionMid_FF
'0410'=> {trig=>'productionLow',         	field => 'FF',	first=> '5051030',	 last => '5051032',	 list => '',  beginTime => '20040220.114742'}, # 	2004-02-20	11:47:42	2004-02-20	14:40:04	timestamp = productionLow_FF
'0411'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5051042',	 last => '5051044',	 list => '',  beginTime => '20040220.144004'}, # 	2004-02-20	14:40:04	2004-02-20	15:38:04	timestamp = productionHigh_FF
'0412'=> {trig=>'productionMid',         	field => 'FF',	first=> '5051046',	 last => '5051046',	 list => '',  beginTime => '20040220.153804'}, # 	2004-02-20	15:38:04	2004-02-20	16:19:33	timestamp = productionMid_FF
'0413'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5051055',	 last => '5051055',	 list => '',  beginTime => '20040220.161933'}, # 	2004-02-20	16:19:33	2004-02-20	16:24:19	timestamp = productionMinBias_FF
'0414'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5051057',	 last => '5051057',	 list => '',  beginTime => '20040220.162419'}, # 	2004-02-20	16:24:19	2004-02-20	16:41:11
'0415'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5051060',	 last => '5051060',	 list => '',  beginTime => '20040220.164111'}, # 	2004-02-20	16:41:11	2004-02-20	16:56:49
'0416'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5051062',	 last => '5051062',	 list => '',  beginTime => '20040220.165649'}, # 	2004-02-20	16:56:49	2004-02-20	18:28:14
'0417'=> {trig=>'productionLow',         	field => 'FF',	first=> '5051067',	 last => '5051068',	 list => '',  beginTime => '20040220.182814'}, # 	2004-02-20	18:28:14	2004-02-20	20:02:13	timestamp = productionLow_FF
'0418'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5051082',	 last => '5051086',	 list => '',  beginTime => '20040220.200213'}, # 	2004-02-20	20:02:13	2004-02-20	21:04:12	timestamp = productionHigh_FF
'0419'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5051088',	 last => '5051088',	 list => '',  beginTime => '20040220.210412'}, # 	2004-02-20	21:04:12	2004-02-20	21:52:12
'0420'=> {trig=>'productionMid',         	field => 'FF',	first=> '5051089',	 last => '5051092',	 list => '',  beginTime => '20040220.215212'}, # 	2004-02-20	21:52:12	2004-02-20	22:55:14	timestamp = productionMid_FF
'0421'=> {trig=>'productionLow',         	field => 'FF',	first=> '5051093',	 last => '5051098',	 list => '',  beginTime => '20040220.225514'}, # 	2004-02-20	22:55:14	2004-02-21	01:10:21	timestamp = productionLow_FF
'0422'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5051110',	 last => '5051111',	 list => '',  beginTime => '20040221.011021'}, # 	2004-02-21	01:10:21	2004-02-21	02:40:42	timestamp = productionHigh_FF
'0423'=> {trig=>'productionMid',         	field => 'FF',	first=> '5051113',	 last => '5051114',	 list => '',  beginTime => '20040221.024042'}, # 	2004-02-21	02:40:42	2004-02-21	03:18:06	timestamp = productionMid_FF
'0424'=> {trig=>'productionLow',         	field => 'FF',	first=> '5051115',	 last => '5051120',	 list => '',  beginTime => '20040221.031806'}, # 	2004-02-21	03:18:06	2004-02-21	06:28:48	timestamp = productionLow_FF
'0425'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5052004',	 last => '5052004',	 list => '',  beginTime => '20040221.062848'}, # 	2004-02-21	06:28:48	2004-02-21	06:33:45	timestamp = productionHigh_FF
'0426'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5052007',	 last => '5052009',	 list => '',  beginTime => '20040221.063345'}, # 	2004-02-21	06:33:45	2004-02-21	07:48:10
'0427'=> {trig=>'productionMid',         	field => 'FF',	first=> '5052012',	 last => '5052014',	 list => '',  beginTime => '20040221.074810'}, # 	2004-02-21	07:48:10	2004-02-21	09:02:32	timestamp = productionMid_FF
'0428'=> {trig=>'productionLow',         	field => 'FF',	first=> '5052016',	 last => '5052019',	 list => '',  beginTime => '20040221.090232'}, # 	2004-02-21	09:02:32	2004-02-21	12:43:11	timestamp = productionLow_FF
'0429'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5052031',	 last => '5052033',	 list => '',  beginTime => '20040221.124311'}, # 	2004-02-21	12:43:11	2004-02-21	13:55:58	timestamp = productionHigh_FF
'0430'=> {trig=>'productionMid',         	field => 'FF',	first=> '5052035',	 last => '5052036',	 list => '',  beginTime => '20040221.135558'}, # 	2004-02-21	13:55:58	2004-02-21	14:38:05	timestamp = productionMid_FF
'0431'=> {trig=>'productionLow',         	field => 'FF',	first=> '5052038',	 last => '5052039',	 list => '',  beginTime => '20040221.143805'}, # 	2004-02-21	14:38:05	2004-02-21	15:42:10	timestamp = productionLow_FF
'0432'=> {trig=>'productionLow',         	field => 'FF',	first=> '5052041',	 last => '5052043',	 list => '',  beginTime => '20040221.154210'}, # 	2004-02-21	15:42:10	2004-02-21	17:59:10
'0433'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5052059',	 last => '5052062',	 list => '',  beginTime => '20040221.175910'}, # 	2004-02-21	17:59:10	2004-02-21	18:51:23	timestamp = productionHigh_FF
'0434'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5052064',	 last => '5052064',	 list => '',  beginTime => '20040221.185123'}, # 	2004-02-21	18:51:23	2004-02-21	19:27:17
'0435'=> {trig=>'productionMid',         	field => 'FF',	first=> '5052072',	 last => '5052072',	 list => '',  beginTime => '20040221.192717'}, # 	2004-02-21	19:27:17	2004-02-21	19:49:08	timestamp = productionMid_FF
'0436'=> {trig=>'productionMid',         	field => 'FF',	first=> '5052075',	 last => '5052076',	 list => '',  beginTime => '20040221.194908'}, # 	2004-02-21	19:49:08	2004-02-21	20:04:17
'0437'=> {trig=>'productionLow',         	field => 'FF',	first=> '5052078',	 last => '5052085',	 list => '',  beginTime => '20040221.200417'}, # 	2004-02-21	20:04:17	2004-02-21	21:25:05	timestamp = productionLow_FF
'0438'=> {trig=>'productionLow',         	field => 'FF',	first=> '5052087',	 last => '5052088',	 list => '',  beginTime => '20040221.212505'}, # 	2004-02-21	21:25:05	2004-02-22	01:51:44
'0439'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5052100',	 last => '5052101',	 list => '',  beginTime => '20040222.015144'}, # 	2004-02-22	01:51:44	2004-02-22	02:57:00	timestamp = productionHigh_FF
'0440'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5052107',	 last => '5052107',	 list => '',  beginTime => '20040222.025700'}, # 	2004-02-22	02:57:00	2004-02-22	03:52:51	timestamp = productionCentral_FF
'0441'=> {trig=>'productionMid',         	field => 'FF',	first=> '5052114',	 last => '5052114',	 list => '',  beginTime => '20040222.035251'}, # 	2004-02-22	03:52:51	2004-02-22	04:17:51	timestamp = productionMid_FF
'0442'=> {trig=>'productionLow',         	field => 'FF',	first=> '5052118',	 last => '5052120',	 list => '',  beginTime => '20040222.041751'}, # 	2004-02-22	04:17:51	2004-02-22	05:18:21	timestamp = productionLow_FF
'0443'=> {trig=>'productionLow',         	field => 'FF',	first=> '5052122',	 last => '5052122',	 list => '',  beginTime => '20040222.051821'}, # 	2004-02-22	05:18:21	2004-02-22	07:33:42
'0444'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5053010',	 last => '5053010',	 list => '',  beginTime => '20040222.073342'}, # 	2004-02-22	07:33:42	2004-02-22	07:44:19	timestamp = productionHigh_FF
'0445'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5053012',	 last => '5053012',	 list => '',  beginTime => '20040222.074419'}, # 	2004-02-22	07:44:19	2004-02-22	07:55:12
'0446'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5053014',	 last => '5053015',	 list => '',  beginTime => '20040222.075512'}, # 	2004-02-22	07:55:12	2004-02-22	08:39:17
'0447'=> {trig=>'productionMid',         	field => 'FF',	first=> '5053016',	 last => '5053020',	 list => '',  beginTime => '20040222.083917'}, # 	2004-02-22	08:39:17	2004-02-22	09:27:43	timestamp = productionMid_FF
'0448'=> {trig=>'productionLow',         	field => 'FF',	first=> '5053024',	 last => '5053024',	 list => '',  beginTime => '20040222.092743'}, # 	2004-02-22	09:27:43	2004-02-22	10:21:41	timestamp = productionLow_FF
'0449'=> {trig=>'productionLow',         	field => 'FF',	first=> '5053026',	 last => '5053026',	 list => '',  beginTime => '20040222.102141'}, # 	2004-02-22	10:21:41	2004-02-22	13:52:48
'0450'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5053035',	 last => '5053035',	 list => '',  beginTime => '20040222.135248'}, # 	2004-02-22	13:52:48	2004-02-22	14:45:08	timestamp = productionHigh_FF
'0451'=> {trig=>'productionMid',         	field => 'FF',	first=> '5053037',	 last => '5053037',	 list => '',  beginTime => '20040222.144508'}, # 	2004-02-22	14:45:08	2004-02-22	14:49:23	timestamp = productionMid_FF
'0452'=> {trig=>'productionMid',         	field => 'FF',	first=> '5053039',	 last => '5053040',	 list => '',  beginTime => '20040222.144923'}, # 	2004-02-22	14:49:23	2004-02-22	15:20:03
'0453'=> {trig=>'productionLow',         	field => 'FF',	first=> '5053042',	 last => '5053042',	 list => '',  beginTime => '20040222.152003'}, # 	2004-02-22	15:20:03	2004-02-22	15:42:35	timestamp = productionLow_FF
'0454'=> {trig=>'productionLow',         	field => 'FF',	first=> '5053044',	 last => '5053044',	 list => '',  beginTime => '20040222.154235'}, # 	2004-02-22	15:42:35	2004-02-22	17:04:05
'0455'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5053057',	 last => '5053059',	 list => '',  beginTime => '20040222.170405'}, # 	2004-02-22	17:04:05	2004-02-22	18:52:28	timestamp = productionMinBias_FF
'0456'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5053074',	 last => '5053074',	 list => '',  beginTime => '20040222.185228'}, # 	2004-02-22	18:52:28	2004-02-22	19:11:07	timestamp = productionCentral_FF
'0457'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5053078',	 last => '5053078',	 list => '',  beginTime => '20040222.191107'}, # 	2004-02-22	19:11:07	2004-02-22	19:36:07
'0458'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5053080',	 last => '5053080',	 list => '',  beginTime => '20040222.193607'}, # 	2004-02-22	19:36:07	2004-02-22	19:41:36
'0459'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5053082',	 last => '5053082',	 list => '',  beginTime => '20040222.194136'}, # 	2004-02-22	19:41:36	2004-02-22	20:18:01
'0460'=> {trig=>'productionMid',         	field => 'FF',	first=> '5053085',	 last => '5053085',	 list => '',  beginTime => '20040222.201801'}, # 	2004-02-22	20:18:01	2004-02-22	20:55:06	timestamp = productionMid_FF
'0461'=> {trig=>'productionLow',         	field => 'FF',	first=> '5053087',	 last => '5053088',	 list => '',  beginTime => '20040222.205506'}, # 	2004-02-22	20:55:06	2004-02-22	21:23:18	timestamp = productionLow_FF
'0462'=> {trig=>'productionLow',         	field => 'FF',	first=> '5053091',	 last => '5053092',	 list => '',  beginTime => '20040222.212318'}, # 	2004-02-22	21:23:18	2004-02-22	22:02:00
'0463'=> {trig=>'productionLow',         	field => 'FF',	first=> '5053094',	 last => '5053095',	 list => '',  beginTime => '20040222.220200'}, # 	2004-02-22	22:02:00	2004-02-23	02:28:46
'0464'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5053106',	 last => '5053106',	 list => '',  beginTime => '20040223.022846'}, # 	2004-02-23	02:28:46	2004-02-23	02:37:08	timestamp = productionCentral_FF
'0465'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5053108',	 last => '5053108',	 list => '',  beginTime => '20040223.023708'}, # 	2004-02-23	02:37:08	2004-02-23	03:01:02
'0466'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5053110',	 last => '5053110',	 list => '',  beginTime => '20040223.030102'}, # 	2004-02-23	03:01:02	2004-02-23	03:12:19
'0467'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5053112',	 last => '5053112',	 list => '',  beginTime => '20040223.031219'}, # 	2004-02-23	03:12:19	2004-02-23	04:10:18	timestamp = productionHigh_FF
'0468'=> {trig=>'productionMid',         	field => 'FF',	first=> '5053113',	 last => '5053113',	 list => '',  beginTime => '20040223.041018'}, # 	2004-02-23	04:10:18	2004-02-23	04:33:39	timestamp = productionMid_FF
'0469'=> {trig=>'productionMid',         	field => 'FF',	first=> '5053115',	 last => '5053115',	 list => '',  beginTime => '20040223.043339'}, # 	2004-02-23	04:33:39	2004-02-23	04:51:41
'0470'=> {trig=>'productionLow',         	field => 'FF',	first=> '5053116',	 last => '5053116',	 list => '',  beginTime => '20040223.045141'}, # 	2004-02-23	04:51:41	2004-02-23	05:07:36	timestamp = productionLow_FF
'0471'=> {trig=>'productionLow',         	field => 'FF',	first=> '5053118',	 last => '5053119',	 list => '',  beginTime => '20040223.050736'}, # 	2004-02-23	05:07:36	2004-02-23	07:17:53
'0472'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5054005',	 last => '5054006',	 list => '',  beginTime => '20040223.071753'}, # 	2004-02-23	07:17:53	2004-02-23	07:41:21	timestamp = productionHigh_FF
'0473'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5054008',	 last => '5054008',	 list => '',  beginTime => '20040223.074121'}, # 	2004-02-23	07:41:21	2004-02-23	08:24:31
'0474'=> {trig=>'productionMid',         	field => 'FF',	first=> '5054010',	 last => '5054010',	 list => '',  beginTime => '20040223.082431'}, # 	2004-02-23	08:24:31	2004-02-23	08:32:54	timestamp = productionMid_FF
'0475'=> {trig=>'productionMid',         	field => 'FF',	first=> '5054012',	 last => '5054013',	 list => '',  beginTime => '20040223.083254'}, # 	2004-02-23	08:32:54	2004-02-23	09:23:10
'0476'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054016',	 last => '5054016',	 list => '',  beginTime => '20040223.092310'}, # 	2004-02-23	09:23:10	2004-02-23	09:36:37	timestamp = productionLow_FF
'0477'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054018',	 last => '5054018',	 list => '',  beginTime => '20040223.093637'}, # 	2004-02-23	09:36:37	2004-02-23	09:44:49
'0478'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054020',	 last => '5054020',	 list => '',  beginTime => '20040223.094449'}, # 	2004-02-23	09:44:49	2004-02-23	10:38:29
'0479'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054024',	 last => '5054024',	 list => '',  beginTime => '20040223.103829'}, # 	2004-02-23	10:38:29	2004-02-23	13:56:36
'0480'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054047',	 last => '5054048',	 list => '',  beginTime => '20040223.135636'}, # 	2004-02-23	13:56:36	2004-02-23	14:59:20
'0481'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054051',	 last => '5054051',	 list => '',  beginTime => '20040223.145920'}, # 	2004-02-23	14:59:20	2004-02-23	18:19:21
'0482'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5054071',	 last => '5054072',	 list => '',  beginTime => '20040223.181921'}, # 	2004-02-23	18:19:21	2004-02-23	19:18:24	timestamp = productionHigh_FF
'0483'=> {trig=>'productionMid',         	field => 'FF',	first=> '5054074',	 last => '5054074',	 list => '',  beginTime => '20040223.191824'}, # 	2004-02-23	19:18:24	2004-02-23	19:36:25	timestamp = productionMid_FF
'0484'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5054076',	 last => '5054076',	 list => '',  beginTime => '20040223.193625'}, # 	2004-02-23	19:36:25	2004-02-23	19:56:32	timestamp = productionMinBias_FF
'0485'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054078',	 last => '5054079',	 list => '',  beginTime => '20040223.195632'}, # 	2004-02-23	19:56:32	2004-02-23	20:34:41	timestamp = productionLow_FF
'0486'=> {trig=>'productionMinBias',     	field => 'FF',	first=> '5054080',	 last => '5054081',	 list => '',  beginTime => '20040223.203441'}, # 	2004-02-23	20:34:41	2004-02-23	20:42:58	timestamp = productionMinBias_FF
'0487'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054082',	 last => '5054084',	 list => '',  beginTime => '20040223.204258'}, # 	2004-02-23	20:42:58	2004-02-23	22:04:22	timestamp = productionLow_FF
'0488'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054086',	 last => '5054086',	 list => '',  beginTime => '20040223.220422'}, # 	2004-02-23	22:04:22	2004-02-23	23:21:38
'0489'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5054096',	 last => '5054097',	 list => '',  beginTime => '20040223.232138'}, # 	2004-02-23	23:21:38	2004-02-24	00:40:31	timestamp = productionHigh_FF
'0490'=> {trig=>'productionMid',         	field => 'FF',	first=> '5054100',	 last => '5054101',	 list => '',  beginTime => '20040224.004031'}, # 	2004-02-24	00:40:31	2004-02-24	01:31:06	timestamp = productionMid_FF
'0491'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054103',	 last => '5054105',	 list => '',  beginTime => '20040224.013106'}, # 	2004-02-24	01:31:06	2004-02-24	03:22:54	timestamp = productionLow_FF
'0492'=> {trig=>'productionLow',         	field => 'FF',	first=> '5054107',	 last => '5054107',	 list => '',  beginTime => '20040224.032254'}, # 	2004-02-24	03:22:54	2004-02-24	04:29:35
'0493'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5054112',	 last => '5054114',	 list => '',  beginTime => '20040224.042935'}, # 	2004-02-24	04:29:35	2004-02-24	05:33:15	timestamp = productionHigh_FF
'0494'=> {trig=>'productionMid',         	field => 'FF',	first=> '5054115',	 last => '5054115',	 list => '',  beginTime => '20040224.053315'}, # 	2004-02-24	05:33:15	2004-02-24	06:23:34	timestamp = productionMid_FF
'0495'=> {trig=>'productionLow',         	field => 'FF',	first=> '5055002',	 last => '5055003',	 list => '',  beginTime => '20040224.062334'}, # 	2004-02-24	06:23:34	2004-02-24	07:49:20	timestamp = productionLow_FF
'0496'=> {trig=>'productionLow',         	field => 'FF',	first=> '5055006',	 last => '5055007',	 list => '',  beginTime => '20040224.074920'}, # 	2004-02-24	07:49:20	2004-02-24	09:25:10
'0497'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5055017',	 last => '5055018',	 list => '',  beginTime => '20040224.092510'}, # 	2004-02-24	09:25:10	2004-02-24	10:32:02	timestamp = productionHigh_FF
'0498'=> {trig=>'productionMid',         	field => 'FF',	first=> '5055021',	 last => '5055022',	 list => '',  beginTime => '20040224.103202'}, # 	2004-02-24	10:32:02	2004-02-24	11:31:54	timestamp = productionMid_FF
'0499'=> {trig=>'productionLow',         	field => 'FF',	first=> '5055024',	 last => '5055025',	 list => '',  beginTime => '20040224.113154'}, # 	2004-02-24	11:31:54	2004-02-24	13:40:55	timestamp = productionLow_FF
'0500'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5055032',	 last => '5055032',	 list => '',  beginTime => '20040224.134055'}, # 	2004-02-24	13:40:55	2004-02-24	14:47:41	timestamp = productionHigh_FF
'0501'=> {trig=>'productionMid',         	field => 'FF',	first=> '5055036',	 last => '5055038',	 list => '',  beginTime => '20040224.144741'}, # 	2004-02-24	14:47:41	2004-02-24	15:34:28	timestamp = productionMid_FF
'0502'=> {trig=>'productionLow',         	field => 'FF',	first=> '5055040',	 last => '5055043',	 list => '',  beginTime => '20040224.153428'}, # 	2004-02-24	15:34:28	2004-02-25	02:30:18	timestamp = productionLow_FF
'0503'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5055095',	 last => '5055095',	 list => '',  beginTime => '20040225.023018'}, # 	2004-02-25	02:30:18	2004-02-25	03:41:33	timestamp = productionHigh_FF
'0504'=> {trig=>'productionMid',         	field => 'FF',	first=> '5055097',	 last => '5055099',	 list => '',  beginTime => '20040225.034133'}, # 	2004-02-25	03:41:33	2004-02-25	04:33:28	timestamp = productionMid_FF
'0505'=> {trig=>'productionLow',         	field => 'FF',	first=> '5055100',	 last => '5055101',	 list => '',  beginTime => '20040225.043328'}, # 	2004-02-25	04:33:28	2004-02-25	05:36:47	timestamp = productionLow_FF
'0506'=> {trig=>'productionLow',         	field => 'FF',	first=> '5055103',	 last => '5055104',	 list => '',  beginTime => '20040225.053647'}, # 	2004-02-25	05:36:47	2004-02-25	05:59:18
'0507'=> {trig=>'productionLow',         	field => 'FF',	first=> '5055106',	 last => '5055106',	 list => '',  beginTime => '20040225.055918'}, # 	2004-02-25	05:59:18	2004-02-25	06:13:17
'0508'=> {trig=>'productionLow',         	field => 'FF',	first=> '5056001',	 last => '5056001',	 list => '',  beginTime => '20040225.061317'}, # 	2004-02-25	06:13:17	2004-02-25	07:15:32
'0509'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5056006',	 last => '5056006',	 list => '',  beginTime => '20040225.071532'}, # 	2004-02-25	07:15:32	2004-02-25	07:34:15	timestamp = productionHigh_FF
'0510'=> {trig=>'productionCentral',     	field => 'FF',	first=> '5056007',	 last => '5056007',	 list => '',  beginTime => '20040225.073415'}, # 	2004-02-25	07:34:15	2004-02-25	07:47:18	timestamp = productionCentral_FF
'0511'=> {trig=>'productionMid',         	field => 'FF',	first=> '5056010',	 last => '5056011',	 list => '',  beginTime => '20040225.074718'}, # 	2004-02-25	07:47:18	2004-02-25	09:13:30	timestamp = productionMid_FF
'0512'=> {trig=>'productionLow',         	field => 'FF',	first=> '5056013',	 last => '5056015',	 list => '',  beginTime => '20040225.091330'}, # 	2004-02-25	09:13:30	2004-02-26	01:10:27	timestamp = productionLow_FF
'0513'=> {trig=>'productionHigh',        	field => 'FF',	first=> '5056050',	 last => '5056051',	 list => '',  beginTime => '20040226.011027'}, # 	2004-02-26	01:10:27	2004-02-26	02:38:41	timestamp = productionHigh_FF
'0514'=> {trig=>'productionMid',         	field => 'FF',	first=> '5056055',	 last => '5056056',	 list => '',  beginTime => '20040226.023841'}, # 	2004-02-26	02:38:41	2004-02-26	03:28:39	timestamp = productionMid_FF
'0515'=> {trig=>'productionLow',         	field => 'FF',	first=> '5056057',	 last => '5056059',	 list => '',  beginTime => '20040226.032839'}, # 	2004-02-26	03:28:39	2004-02-26	13:45:48	timestamp = productionLow_FF
'0516'=> {trig=>'productionMid',         	field => 'FF',	first=> '5057032',	 last => '5057033',	 list => '',  beginTime => '20040226.134548'}, # 	2004-02-26	13:45:48	2004-02-26	14:02:25	timestamp = productionMid_FF
'0517'=> {trig=>'productionLow',         	field => 'FF',	first=> '5057034',	 last => '5057034',	 list => '',  beginTime => '20040226.140225'}, # 	2004-02-26	14:02:25	2004-02-26	14:53:23	timestamp = productionLow_FF
'0518'=> {trig=>'productionLow',         	field => 'FF',	first=> '5057036',	 last => '5057036',	 list => '',  beginTime => '20040226.145323'}, # 	2004-02-26	14:53:23	2004-02-26	15:31:49
'0519'=> {trig=>'productionLow',         	field => 'FF',	first=> '5057038',	 last => '5057039',	 list => '',  beginTime => '20040226.153149'}, # 	2004-02-26	15:31:49	2004-02-26	17:16:36
'0520'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5057048',	 last => '5057048',	 list => '',  beginTime => '20040226.171636'}, # 	2004-02-26	17:16:36	2004-02-26	17:21:29	timestamp = productionHalfHigh_FHF
'0521'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5057049',	 last => '5057049',	 list => '',  beginTime => '20040226.172129'}, # 	2004-02-26	17:21:29	2004-02-26	17:27:28	timestamp = productionHalfLow_FHF
'0522'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5057050',	 last => '5057054',	 list => '',  beginTime => '20040226.172728'}, # 	2004-02-26	17:27:28	2004-02-26	18:38:37	timestamp = productionHalfHigh_FHF
'0523'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5057055',	 last => '5057057',	 list => '',  beginTime => '20040226.183837'}, # 	2004-02-26	18:38:37	2004-02-26	19:02:01	timestamp = productionHalfLow_FHF
'0524'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5057062',	 last => '5057062',	 list => '',  beginTime => '20040226.190201'}, # 	2004-02-26	19:02:01	2004-02-26	19:53:28	timestamp = productionHalfHigh_FHF
'0525'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5057064',	 last => '5057064',	 list => '',  beginTime => '20040226.195328'}, # 	2004-02-26	19:53:28	2004-02-26	20:53:41	timestamp = productionHalfLow_FHF
'0526'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5057066',	 last => '5057066',	 list => '',  beginTime => '20040226.205341'}, # 	2004-02-26	20:53:41	2004-02-26	20:57:26
'0527'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5057068',	 last => '5057071',	 list => '',  beginTime => '20040226.205726'}, # 	2004-02-26	20:57:26	2004-02-27	00:07:32
'0528'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5057083',	 last => '5057084',	 list => '',  beginTime => '20040227.000732'}, # 	2004-02-27	00:07:32	2004-02-27	01:11:23	timestamp = productionHalfHigh_FHF
'0529'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5057087',	 last => '5057087',	 list => '',  beginTime => '20040227.011123'}, # 	2004-02-27	01:11:23	2004-02-27	12:32:49	timestamp = productionHalfLow_FHF
'0530'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5058021',	 last => '5058023',	 list => '',  beginTime => '20040227.123249'}, # 	2004-02-27	12:32:49	2004-02-27	13:42:23
'0531'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5058026',	 last => '5058033',	 list => '',  beginTime => '20040227.134223'}, # 	2004-02-27	13:42:23	2004-02-27	23:20:28
'0532'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5058057',	 last => '5058058',	 list => '',  beginTime => '20040227.232028'}, # 	2004-02-27	23:20:28	2004-02-27	23:49:47	timestamp = productionHalfHigh_FHF
'0533'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5058060',	 last => '5058060',	 list => '',  beginTime => '20040227.234947'}, # 	2004-02-27	23:49:47	2004-02-28	00:23:14
'0534'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5058062',	 last => '5058062',	 list => '',  beginTime => '20040228.002314'}, # 	2004-02-28	00:23:14	2004-02-28	01:03:19	timestamp = productionHalfLow_FHF
'0535'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5058065',	 last => '5058068',	 list => '',  beginTime => '20040228.010319'}, # 	2004-02-28	01:03:19	2004-02-28	05:00:09
'0536'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5058076',	 last => '5058076',	 list => '',  beginTime => '20040228.050009'}, # 	2004-02-28	05:00:09	2004-02-28	05:36:53	timestamp = productionHalfHigh_FHF
'0537'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5058077',	 last => '5058079',	 list => '',  beginTime => '20040228.053653'}, # 	2004-02-28	05:36:53	2004-02-28	06:21:50	timestamp = productionHalfLow_FHF
'0538'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5059003',	 last => '5059008',	 list => '',  beginTime => '20040228.062150'}, # 	2004-02-28	06:21:50	2004-02-28	10:39:49
'0539'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5059013',	 last => '5059013',	 list => '',  beginTime => '20040228.103949'}, # 	2004-02-28	10:39:49	2004-02-28	11:25:51	timestamp = productionHalfHigh_FHF
'0540'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5059015',	 last => '5059015',	 list => '',  beginTime => '20040228.112551'}, # 	2004-02-28	11:25:51	2004-02-28	12:31:39
'0541'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5059020',	 last => '5059022',	 list => '',  beginTime => '20040228.123139'}, # 	2004-02-28	12:31:39	2004-02-28	20:49:37	timestamp = productionHalfLow_FHF
'0542'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5059036',	 last => '5059036',	 list => '',  beginTime => '20040228.204937'}, # 	2004-02-28	20:49:37	2004-02-28	21:35:42	timestamp = productionHalfHigh_FHF
'0543'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5059038',	 last => '5059039',	 list => '',  beginTime => '20040228.213542'}, # 	2004-02-28	21:35:42	2004-02-29	02:30:53	timestamp = productionHalfLow_FHF
'0544'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5059048',	 last => '5059048',	 list => '',  beginTime => '20040229.023053'}, # 	2004-02-29	02:30:53	2004-02-29	02:47:12	timestamp = productionHalfHigh_FHF
'0545'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5059053',	 last => '5059053',	 list => '',  beginTime => '20040229.024712'}, # 	2004-02-29	02:47:12	2004-02-29	03:04:32
'0546'=> {trig=>'productionHalfHigh',    	field => 'FHF',	first=> '5059055',	 last => '5059055',	 list => '',  beginTime => '20040229.030432'}, # 	2004-02-29	03:04:32	2004-02-29	03:49:41
'0547'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5059058',	 last => '5059061',	 list => '',  beginTime => '20040229.034941'}, # 	2004-02-29	03:49:41	2004-02-29	17:28:11	timestamp = productionHalfLow_FHF
'0548'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5060043',	 last => '5060044',	 list => '',  beginTime => '20040229.172811'}, # 	2004-02-29	17:28:11	2004-02-29	18:34:02
'0549'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5060046',	 last => '5060050',	 list => '',  beginTime => '20040229.183402'}, # 	2004-02-29	18:34:02	2004-02-29	23:04:16
'0550'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5060058',	 last => '5060058',	 list => '',  beginTime => '20040229.230416'}, # 	2004-02-29	23:04:16	2004-02-29	23:30:13
'0551'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5060060',	 last => '5060060',	 list => '',  beginTime => '20040229.233013'}, # 	2004-02-29	23:30:13	2004-03-01	00:07:03
'0552'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5060063',	 last => '5060066',	 list => '',  beginTime => '20040301.000703'}, # 	2004-03-01	00:07:03	2004-03-01	03:07:26
'0553'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5060074',	 last => '5060074',	 list => '',  beginTime => '20040301.030726'}, # 	2004-03-01	03:07:26	2004-03-01	03:47:43
'0554'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5060076',	 last => '5060078',	 list => '',  beginTime => '20040301.034743'}, # 	2004-03-01	03:47:43	2004-03-01	05:20:04
'0555'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5060080',	 last => '5060080',	 list => '',  beginTime => '20040301.052004'}, # 	2004-03-01	05:20:04	2004-03-01	08:58:29
'0556'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061009',	 last => '5061010',	 list => '',  beginTime => '20040301.085829'}, # 	2004-03-01	08:58:29	2004-03-01	09:51:43
'0557'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061012',	 last => '5061015',	 list => '',  beginTime => '20040301.095143'}, # 	2004-03-01	09:51:43	2004-03-01	14:06:14
'0558'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061031',	 last => '5061031',	 list => '',  beginTime => '20040301.140614'}, # 	2004-03-01	14:06:14	2004-03-01	14:31:03
'0559'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061034',	 last => '5061036',	 list => '',  beginTime => '20040301.143103'}, # 	2004-03-01	14:31:03	2004-03-01	16:35:00
'0560'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061044',	 last => '5061046',	 list => '',  beginTime => '20040301.163500'}, # 	2004-03-01	16:35:00	2004-03-01	20:15:07
'0561'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061059',	 last => '5061059',	 list => '',  beginTime => '20040301.201507'}, # 	2004-03-01	20:15:07	2004-03-01	21:31:37
'0562'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061063',	 last => '5061068',	 list => '',  beginTime => '20040301.213137'}, # 	2004-03-01	21:31:37	2004-03-02	00:25:00
'0563'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061071',	 last => '5061072',	 list => '',  beginTime => '20040302.002500'}, # 	2004-03-02	00:25:00	2004-03-02	02:56:04
'0564'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061084',	 last => '5061086',	 list => '',  beginTime => '20040302.025604'}, # 	2004-03-02	02:56:04	2004-03-02	03:46:51
'0565'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061088',	 last => '5061088',	 list => '',  beginTime => '20040302.034651'}, # 	2004-03-02	03:46:51	2004-03-02	04:07:23
'0566'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5061090',	 last => '5061094',	 list => '',  beginTime => '20040302.040723'}, # 	2004-03-02	04:07:23	2004-03-02	06:06:01
'0567'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5062001',	 last => '5062001',	 list => '',  beginTime => '20040302.060601'}, # 	2004-03-02	06:06:01	2004-03-02	13:52:30
'0568'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5062008',	 last => '5062010',	 list => '',  beginTime => '20040302.135230'}, # 	2004-03-02	13:52:30	2004-03-02	15:59:04
'0569'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5062013',	 last => '5062013',	 list => '',  beginTime => '20040302.155904'}, # 	2004-03-02	15:59:04	2004-03-02	19:48:16
'0570'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5062026',	 last => '5062028',	 list => '',  beginTime => '20040302.194816'}, # 	2004-03-02	19:48:16	2004-03-02	20:35:59
'0571'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5062031',	 last => '5062031',	 list => '',  beginTime => '20040302.203559'}, # 	2004-03-02	20:35:59	2004-03-02	21:24:19
'0572'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5062034',	 last => '5062034',	 list => '',  beginTime => '20040302.212419'}, # 	2004-03-02	21:24:19	2004-03-02	21:59:42
'0573'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5062037',	 last => '5062037',	 list => '',  beginTime => '20040302.215942'}, # 	2004-03-02	21:59:42	2004-03-02	22:07:57
'0574'=> {trig=>'productionHalfLow',     	field => 'FHF',	first=> '5062040',	 last => '5062041',	 list => '',  beginTime => '20040302.220757'}, # 	2004-03-02	22:07:57	2004-03-04	06:54:28
'0575'=> {trig=>'productionMid',         	field => 'RF',	first=> '5064008',	 last => '5064008',	 list => '',  beginTime => '20040304.065428'}, # 	2004-03-04	06:54:28	2004-03-04	07:11:04	timestamp = productionMid_RF
'0576'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5064010',	 last => '5064011',	 list => '',  beginTime => '20040304.071104'}, # 	2004-03-04	07:11:04	2004-03-04	08:33:48	timestamp = productionMinBias_RF
'0577'=> {trig=>'productionLow',         	field => 'RF',	first=> '5064021',	 last => '5064022',	 list => '',  beginTime => '20040304.083348'}, # 	2004-03-04	08:33:48	2004-03-04	10:39:17	timestamp = productionLow_RF
'0578'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5064030',	 last => '5064030',	 list => '',  beginTime => '20040304.103917'}, # 	2004-03-04	10:39:17	2004-03-04	11:47:38	timestamp = productionHigh_RF
'0579'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5064039',	 last => '5064043',	 list => '',  beginTime => '20040304.114738'}, # 	2004-03-04	11:47:38	2004-03-04	13:13:19	timestamp = productionMinBias_RF
'0580'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5064045',	 last => '5064045',	 list => '',  beginTime => '20040304.131319'}, # 	2004-03-04	13:13:19	2004-03-04	17:23:01
'0581'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5064067',	 last => '5064068',	 list => '',  beginTime => '20040304.172301'}, # 	2004-03-04	17:23:01	2004-03-04	17:38:33	timestamp = productionHigh_RF
'0582'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5064071',	 last => '5064071',	 list => '',  beginTime => '20040304.173833'}, # 	2004-03-04	17:38:33	2004-03-04	18:01:05
'0583'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5064074',	 last => '5064075',	 list => '',  beginTime => '20040304.180105'}, # 	2004-03-04	18:01:05	2004-03-04	18:14:01
'0584'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5064077',	 last => '5064077',	 list => '',  beginTime => '20040304.181401'}, # 	2004-03-04	18:14:01	2004-03-04	18:27:08
'0585'=> {trig=>'productionMid',         	field => 'RF',	first=> '5064078',	 last => '5064078',	 list => '',  beginTime => '20040304.182708'}, # 	2004-03-04	18:27:08	2004-03-04	19:07:49	timestamp = productionMid_RF
'0586'=> {trig=>'productionLow',         	field => 'RF',	first=> '5064082',	 last => '5064082',	 list => '',  beginTime => '20040304.190749'}, # 	2004-03-04	19:07:49	2004-03-04	19:44:03	timestamp = productionLow_RF
'0587'=> {trig=>'productionLow',         	field => 'RF',	first=> '5064085',	 last => '5064086',	 list => '',  beginTime => '20040304.194403'}, # 	2004-03-04	19:44:03	2004-03-05	02:00:15
'0588'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5064104',	 last => '5064106',	 list => '',  beginTime => '20040305.020015'}, # 	2004-03-05	02:00:15	2004-03-05	03:27:36	timestamp = productionHigh_RF
'0589'=> {trig=>'productionMid',         	field => 'RF',	first=> '5064110',	 last => '5064110',	 list => '',  beginTime => '20040305.032736'}, # 	2004-03-05	03:27:36	2004-03-05	04:01:24	timestamp = productionMid_RF
'0590'=> {trig=>'productionLow',         	field => 'RF',	first=> '5064111',	 last => '5064112',	 list => '',  beginTime => '20040305.040124'}, # 	2004-03-05	04:01:24	2004-03-05	04:48:20	timestamp = productionLow_RF
'0591'=> {trig=>'productionLow',         	field => 'RF',	first=> '5064114',	 last => '5064114',	 list => '',  beginTime => '20040305.044820'}, # 	2004-03-05	04:48:20	2004-03-05	05:01:40
'0592'=> {trig=>'productionLow',         	field => 'RF',	first=> '5064117',	 last => '5064117',	 list => '',  beginTime => '20040305.050140'}, # 	2004-03-05	05:01:40	2004-03-05	09:39:50
'0593'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5065006',	 last => '5065006',	 list => '',  beginTime => '20040305.093950'}, # 	2004-03-05	09:39:50	2004-03-05	10:22:02	timestamp = productionHigh_RF
'0594'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5065010',	 last => '5065010',	 list => '',  beginTime => '20040305.102202'}, # 	2004-03-05	10:22:02	2004-03-05	11:00:16
'0595'=> {trig=>'productionMid',         	field => 'RF',	first=> '5065011',	 last => '5065012',	 list => '',  beginTime => '20040305.110016'}, # 	2004-03-05	11:00:16	2004-03-05	11:50:46	timestamp = productionMid_RF
'0596'=> {trig=>'productionLow',         	field => 'RF',	first=> '5065014',	 last => '5065015',	 list => '',  beginTime => '20040305.115046'}, # 	2004-03-05	11:50:46	2004-03-05	12:25:48	timestamp = productionLow_RF
'0597'=> {trig=>'productionLow',         	field => 'RF',	first=> '5065017',	 last => '5065018',	 list => '',  beginTime => '20040305.122548'}, # 	2004-03-05	12:25:48	2004-03-05	15:52:27
'0598'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5065046',	 last => '5065047',	 list => '',  beginTime => '20040305.155227'}, # 	2004-03-05	15:52:27	2004-03-05	21:55:49	timestamp = productionHigh_RF
'0599'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5065066',	 last => '5065067',	 list => '',  beginTime => '20040305.215549'}, # 	2004-03-05	21:55:49	2004-03-05	22:24:00
'0600'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5065069',	 last => '5065070',	 list => '',  beginTime => '20040305.222400'}, # 	2004-03-05	22:24:00	2004-03-05	22:47:30
'0601'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5065073',	 last => '5065073',	 list => '',  beginTime => '20040305.224730'}, # 	2004-03-05	22:47:30	2004-03-05	23:18:39
'0602'=> {trig=>'productionMid',         	field => 'RF',	first=> '5065074',	 last => '5065074',	 list => '',  beginTime => '20040305.231839'}, # 	2004-03-05	23:18:39	2004-03-05	23:32:13	timestamp = productionMid_RF
'0603'=> {trig=>'productionLow',         	field => 'RF',	first=> '5065075',	 last => '5065075',	 list => '',  beginTime => '20040305.233213'}, # 	2004-03-05	23:32:13	2004-03-05	23:35:10	timestamp = productionLow_RF
'0604'=> {trig=>'productionLow',         	field => 'RF',	first=> '5065077',	 last => '5065080',	 list => '',  beginTime => '20040305.233510'}, # 	2004-03-05	23:35:10	2004-03-06	01:15:56
'0605'=> {trig=>'productionLow',         	field => 'RF',	first=> '5065082',	 last => '5065082',	 list => '',  beginTime => '20040306.011556'}, # 	2004-03-06	01:15:56	2004-03-06	01:21:51
'0606'=> {trig=>'productionLow',         	field => 'RF',	first=> '5065084',	 last => '5065084',	 list => '',  beginTime => '20040306.012151'}, # 	2004-03-06	01:21:51	2004-03-06	03:48:16
'0607'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5065095',	 last => '5065095',	 list => '',  beginTime => '20040306.034816'}, # 	2004-03-06	03:48:16	2004-03-06	04:01:17	timestamp = productionHigh_RF
'0608'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5065097',	 last => '5065098',	 list => '',  beginTime => '20040306.040117'}, # 	2004-03-06	04:01:17	2004-03-06	04:44:02
'0609'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5065100',	 last => '5065100',	 list => '',  beginTime => '20040306.044402'}, # 	2004-03-06	04:44:02	2004-03-06	07:04:40
'0610'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5066014',	 last => '5066014',	 list => '',  beginTime => '20040306.070440'}, # 	2004-03-06	07:04:40	2004-03-06	08:05:09
'0611'=> {trig=>'productionMid',         	field => 'RF',	first=> '5066016',	 last => '5066016',	 list => '',  beginTime => '20040306.080509'}, # 	2004-03-06	08:05:09	2004-03-06	08:22:29	timestamp = productionMid_RF
'0612'=> {trig=>'productionMid',         	field => 'RF',	first=> '5066019',	 last => '5066019',	 list => '',  beginTime => '20040306.082229'}, # 	2004-03-06	08:22:29	2004-03-06	09:13:44
'0613'=> {trig=>'productionLow',         	field => 'RF',	first=> '5066022',	 last => '5066024',	 list => '',  beginTime => '20040306.091344'}, # 	2004-03-06	09:13:44	2004-03-06	12:11:57	timestamp = productionLow_RF
'0614'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5066034',	 last => '5066034',	 list => '',  beginTime => '20040306.121157'}, # 	2004-03-06	12:11:57	2004-03-06	12:53:49	timestamp = productionHigh_RF
'0615'=> {trig=>'productionLow',         	field => 'RF',	first=> '5066037',	 last => '5066037',	 list => '',  beginTime => '20040306.125349'}, # 	2004-03-06	12:53:49	2004-03-06	13:26:41	timestamp = productionLow_RF
'0616'=> {trig=>'productionLow',         	field => 'RF',	first=> '5066041',	 last => '5066041',	 list => '',  beginTime => '20040306.132641'}, # 	2004-03-06	13:26:41	2004-03-06	13:45:15
'0617'=> {trig=>'productionLow',         	field => 'RF',	first=> '5066045',	 last => '5066045',	 list => '',  beginTime => '20040306.134515'}, # 	2004-03-06	13:45:15	2004-03-06	14:08:48
'0618'=> {trig=>'productionLow',         	field => 'RF',	first=> '5066047',	 last => '5066048',	 list => '',  beginTime => '20040306.140848'}, # 	2004-03-06	14:08:48	2004-03-07	02:37:04
'0619'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5066080',	 last => '5066081',	 list => '',  beginTime => '20040307.023704'}, # 	2004-03-07	02:37:04	2004-03-07	03:19:48	timestamp = productionHigh_RF
'0620'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5066083',	 last => '5066083',	 list => '',  beginTime => '20040307.031948'}, # 	2004-03-07	03:19:48	2004-03-07	03:35:16
'0621'=> {trig=>'productionMid',         	field => 'RF',	first=> '5066084',	 last => '5066086',	 list => '',  beginTime => '20040307.033516'}, # 	2004-03-07	03:35:16	2004-03-07	05:20:54	timestamp = productionMid_RF
'0622'=> {trig=>'productionLow',         	field => 'RF',	first=> '5066092',	 last => '5066092',	 list => '',  beginTime => '20040307.052054'}, # 	2004-03-07	05:20:54	2004-03-07	05:51:47	timestamp = productionLow_RF
'0623'=> {trig=>'productionLow',         	field => 'RF',	first=> '5066094',	 last => '5066094',	 list => '',  beginTime => '20040307.055147'}, # 	2004-03-07	05:51:47	2004-03-07	06:28:22
'0624'=> {trig=>'productionLow',         	field => 'RF',	first=> '5067001',	 last => '5067002',	 list => '',  beginTime => '20040307.062822'}, # 	2004-03-07	06:28:22	2004-03-07	08:03:08
'0625'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5067012',	 last => '5067014',	 list => '',  beginTime => '20040307.080308'}, # 	2004-03-07	08:03:08	2004-03-07	09:08:56	timestamp = productionHigh_RF
'0626'=> {trig=>'productionMid',         	field => 'RF',	first=> '5067016',	 last => '5067018',	 list => '',  beginTime => '20040307.090856'}, # 	2004-03-07	09:08:56	2004-03-07	10:09:20	timestamp = productionMid_RF
'0627'=> {trig=>'productionLow',         	field => 'RF',	first=> '5067019',	 last => '5067019',	 list => '',  beginTime => '20040307.100920'}, # 	2004-03-07	10:09:20	2004-03-07	10:50:33	timestamp = productionLow_RF
'0628'=> {trig=>'productionLow',         	field => 'RF',	first=> '5067022',	 last => '5067024',	 list => '',  beginTime => '20040307.105033'}, # 	2004-03-07	10:50:33	2004-03-07	13:26:14
'0629'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5067038',	 last => '5067038',	 list => '',  beginTime => '20040307.132614'}, # 	2004-03-07	13:26:14	2004-03-07	14:04:39	timestamp = productionHigh_RF
'0630'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5067041',	 last => '5067041',	 list => '',  beginTime => '20040307.140439'}, # 	2004-03-07	14:04:39	2004-03-07	14:55:56
'0631'=> {trig=>'productionMid',         	field => 'RF',	first=> '5067043',	 last => '5067045',	 list => '',  beginTime => '20040307.145556'}, # 	2004-03-07	14:55:56	2004-03-07	16:01:19	timestamp = productionMid_RF
'0632'=> {trig=>'productionLow',         	field => 'RF',	first=> '5067046',	 last => '5067046',	 list => '',  beginTime => '20040307.160119'}, # 	2004-03-07	16:01:19	2004-03-07	20:23:16	timestamp = productionLow_RF
'0633'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5067056',	 last => '5067059',	 list => '',  beginTime => '20040307.202316'}, # 	2004-03-07	20:23:16	2004-03-07	20:55:06	timestamp = productionHigh_RF
'0634'=> {trig=>'productionMid',         	field => 'RF',	first=> '5067060',	 last => '5067060',	 list => '',  beginTime => '20040307.205506'}, # 	2004-03-07	20:55:06	2004-03-07	21:02:20	timestamp = productionMid_RF
'0635'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5067061',	 last => '5067062',	 list => '',  beginTime => '20040307.210220'}, # 	2004-03-07	21:02:20	2004-03-07	21:12:26	timestamp = productionHigh_RF
'0636'=> {trig=>'productionMid',         	field => 'RF',	first=> '5067063',	 last => '5067064',	 list => '',  beginTime => '20040307.211226'}, # 	2004-03-07	21:12:26	2004-03-07	21:45:57	timestamp = productionMid_RF
'0637'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5067065',	 last => '5067065',	 list => '',  beginTime => '20040307.214557'}, # 	2004-03-07	21:45:57	2004-03-07	21:48:43	timestamp = productionHigh_RF
'0638'=> {trig=>'productionLow',         	field => 'RF',	first=> '5067066',	 last => '5067066',	 list => '',  beginTime => '20040307.214843'}, # 	2004-03-07	21:48:43	2004-03-08	03:56:34	timestamp = productionLow_RF
'0639'=> {trig=>'productionLow',         	field => 'RF',	first=> '5067104',	 last => '5067104',	 list => '',  beginTime => '20040308.035634'}, # 	2004-03-08	03:56:34	2004-03-08	04:02:37
'0640'=> {trig=>'productionCentral',     	field => 'RF',	first=> '5067105',	 last => '5067105',	 list => '',  beginTime => '20040308.040237'}, # 	2004-03-08	04:02:37	2004-03-08	04:11:23	timestamp = productionCentral_RF
'0641'=> {trig=>'productionCentral',     	field => 'RF',	first=> '5067107',	 last => '5067107',	 list => '',  beginTime => '20040308.041123'}, # 	2004-03-08	04:11:23	2004-03-08	05:27:09
'0642'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5067109',	 last => '5067109',	 list => '',  beginTime => '20040308.052709'}, # 	2004-03-08	05:27:09	2004-03-08	07:30:56	timestamp = productionMinBias_RF
'0643'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5068017',	 last => '5068019',	 list => '',  beginTime => '20040308.073056'}, # 	2004-03-08	07:30:56	2004-03-08	08:21:30	timestamp = productionHigh_RF
'0644'=> {trig=>'productionMid',         	field => 'RF',	first=> '5068021',	 last => '5068021',	 list => '',  beginTime => '20040308.082130'}, # 	2004-03-08	08:21:30	2004-03-08	08:56:39	timestamp = productionMid_RF
'0645'=> {trig=>'productionLow',         	field => 'RF',	first=> '5068022',	 last => '5068024',	 list => '',  beginTime => '20040308.085639'}, # 	2004-03-08	08:56:39	2004-03-08	11:46:41	timestamp = productionLow_RF
'0646'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5068029',	 last => '5068031',	 list => '',  beginTime => '20040308.114641'}, # 	2004-03-08	11:46:41	2004-03-08	12:37:02	timestamp = productionHigh_RF
'0647'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5068034',	 last => '5068034',	 list => '',  beginTime => '20040308.123702'}, # 	2004-03-08	12:37:02	2004-03-08	13:14:47
'0648'=> {trig=>'productionMid',         	field => 'RF',	first=> '5068035',	 last => '5068035',	 list => '',  beginTime => '20040308.131447'}, # 	2004-03-08	13:14:47	2004-03-08	15:01:54	timestamp = productionMid_RF
'0649'=> {trig=>'productionMid',         	field => 'RF',	first=> '5068041',	 last => '5068041',	 list => '',  beginTime => '20040308.150154'}, # 	2004-03-08	15:01:54	2004-03-08	15:03:40
'0650'=> {trig=>'productionLow',         	field => 'RF',	first=> '5068042',	 last => '5068043',	 list => '',  beginTime => '20040308.150340'}, # 	2004-03-08	15:03:40	2004-03-08	22:32:21	timestamp = productionLow_RF
'0651'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5068118',	 last => '5068119',	 list => '',  beginTime => '20040308.223221'}, # 	2004-03-08	22:32:21	2004-03-08	23:02:24	timestamp = productionHigh_RF
'0652'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5068121',	 last => '5068122',	 list => '',  beginTime => '20040308.230224'}, # 	2004-03-08	23:02:24	2004-03-08	23:54:07
'0653'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5068125',	 last => '5068127',	 list => '',  beginTime => '20040308.235407'}, # 	2004-03-08	23:54:07	2004-03-09	00:54:55
'0654'=> {trig=>'productionCentral',     	field => 'RF',	first=> '5068128',	 last => '5068128',	 list => '',  beginTime => '20040309.005455'}, # 	2004-03-09	00:54:55	2004-03-09	01:18:31	timestamp = productionCentral_RF
'0655'=> {trig=>'productionCentral',     	field => 'RF',	first=> '5068132',	 last => '5068133',	 list => '',  beginTime => '20040309.011831'}, # 	2004-03-09	01:18:31	2004-03-09	02:14:08
'0656'=> {trig=>'productionLow',         	field => 'RF',	first=> '5068136',	 last => '5068136',	 list => '',  beginTime => '20040309.021408'}, # 	2004-03-09	02:14:08	2004-03-09	04:16:46	timestamp = productionLow_RF
'0657'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5068143',	 last => '5068145',	 list => '',  beginTime => '20040309.041646'}, # 	2004-03-09	04:16:46	2004-03-09	05:29:27	timestamp = productionHigh_RF
'0658'=> {trig=>'productionMid',         	field => 'RF',	first=> '5068150',	 last => '5068151',	 list => '',  beginTime => '20040309.052927'}, # 	2004-03-09	05:29:27	2004-03-09	06:13:13	timestamp = productionMid_RF
'0659'=> {trig=>'productionLow',         	field => 'RF',	first=> '5069001',	 last => '5069002',	 list => '',  beginTime => '20040309.061313'}, # 	2004-03-09	06:13:13	2004-03-09	08:36:54	timestamp = productionLow_RF
'0660'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5069009',	 last => '5069010',	 list => '',  beginTime => '20040309.083654'}, # 	2004-03-09	08:36:54	2004-03-09	08:54:16	timestamp = productionHigh_RF
'0661'=> {trig=>'productionMid',         	field => 'RF',	first=> '5069011',	 last => '5069012',	 list => '',  beginTime => '20040309.085416'}, # 	2004-03-09	08:54:16	2004-03-09	09:53:04	timestamp = productionMid_RF
'0662'=> {trig=>'productionLow',         	field => 'RF',	first=> '5069014',	 last => '5069015',	 list => '',  beginTime => '20040309.095304'}, # 	2004-03-09	09:53:04	2004-03-09	12:16:42	timestamp = productionLow_RF
'0663'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5069023',	 last => '5069026',	 list => '',  beginTime => '20040309.121642'}, # 	2004-03-09	12:16:42	2004-03-09	12:58:48	timestamp = productionHigh_RF
'0664'=> {trig=>'productionLow',         	field => 'RF',	first=> '5069028',	 last => '5069028',	 list => '',  beginTime => '20040309.125848'}, # 	2004-03-09	12:58:48	2004-03-09	13:31:44	timestamp = productionLow_RF
'0665'=> {trig=>'productionLow',         	field => 'RF',	first=> '5069031',	 last => '5069034',	 list => '',  beginTime => '20040309.133144'}, # 	2004-03-09	13:31:44	2004-03-10	00:49:54
'0666'=> {trig=>'productionHigh',        	field => 'ZF',	first=> '5069089',	 last => '5069093',	 list => '',  beginTime => '20040310.004954'}, # 	2004-03-10	00:49:54	2004-03-10	02:11:49	timestamp = productionHigh_ZF
'0667'=> {trig=>'productionMid',         	field => 'RF',	first=> '5069099',	 last => '5069101',	 list => '',  beginTime => '20040310.021149'}, # 	2004-03-10	02:11:49	2004-03-10	02:41:54	timestamp = productionMid_RF
'0668'=> {trig=>'productionLow',         	field => 'RF',	first=> '5069102',	 last => '5069103',	 list => '',  beginTime => '20040310.024154'}, # 	2004-03-10	02:41:54	2004-03-10	03:25:34	timestamp = productionLow_RF
'0669'=> {trig=>'productionLow',         	field => 'RF',	first=> '5069105',	 last => '5069105',	 list => '',  beginTime => '20040310.032534'}, # 	2004-03-10	03:25:34	2004-03-10	09:00:26
'0670'=> {trig=>'productionHigh',        	field => 'ZF',	first=> '5070010',	 last => '5070010',	 list => '',  beginTime => '20040310.090026'}, # 	2004-03-10	09:00:26	2004-03-10	09:36:17	timestamp = productionHigh_ZF
'0671'=> {trig=>'productionHigh',        	field => 'ZF',	first=> '5070014',	 last => '5070014',	 list => '',  beginTime => '20040310.093617'}, # 	2004-03-10	09:36:17	2004-03-10	12:14:41
'0672'=> {trig=>'productionHigh',        	field => 'ZF',	first=> '5070023',	 last => '5070025',	 list => '',  beginTime => '20040310.121441'}, # 	2004-03-10	12:14:41	2004-03-10	13:45:00
'0673'=> {trig=>'productionMid',         	field => 'ZF',	first=> '5070028',	 last => '5070028',	 list => '',  beginTime => '20040310.134500'}, # 	2004-03-10	13:45:00	2004-03-10	14:01:06	timestamp = productionMid_ZF
'0674'=> {trig=>'productionMid',         	field => 'ZF',	first=> '5070031',	 last => '5070031',	 list => '',  beginTime => '20040310.140106'}, # 	2004-03-10	14:01:06	2004-03-10	14:31:04
'0675'=> {trig=>'productionLow',         	field => 'ZF',	first=> '5070032',	 last => '5070032',	 list => '',  beginTime => '20040310.143104'}, # 	2004-03-10	14:31:04	2004-03-10	14:45:02	timestamp = productionLow_ZF
'0676'=> {trig=>'productionLow',         	field => 'ZF',	first=> '5070035',	 last => '5070036',	 list => '',  beginTime => '20040310.144502'}, # 	2004-03-10	14:45:02	2004-03-10	15:41:15
'0677'=> {trig=>'productionLow',         	field => 'RF',	first=> '5070037',	 last => '5070037',	 list => '',  beginTime => '20040310.154115'}, # 	2004-03-10	15:41:15	2004-03-10	15:41:15	timestamp = productionLow_RF
'0678'=> {trig=>'productionLow',         	field => 'ZF',	first=> '5070037',	 last => '5070037',	 list => '',  beginTime => '20040310.154115'}, # 	2004-03-10	15:41:15	2004-03-10	16:24:16	timestamp = productionLow_ZF
'0679'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5070039',	 last => '5070040',	 list => '',  beginTime => '20040310.162416'}, # 	2004-03-10	16:24:16	2004-03-10	19:30:40	timestamp = productionMinBias_RF
'0680'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5070059',	 last => '5070059',	 list => '',  beginTime => '20040310.193040'}, # 	2004-03-10	19:30:40	2004-03-10	20:13:40	timestamp = productionHigh_RF
'0681'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5070061',	 last => '5070061',	 list => '',  beginTime => '20040310.201340'}, # 	2004-03-10	20:13:40	2004-03-10	20:50:05
'0682'=> {trig=>'productionMid',         	field => 'RF',	first=> '5070064',	 last => '5070065',	 list => '',  beginTime => '20040310.205005'}, # 	2004-03-10	20:50:05	2004-03-10	21:41:21	timestamp = productionMid_RF
'0683'=> {trig=>'productionLow',         	field => 'RF',	first=> '5070066',	 last => '5070070',	 list => '',  beginTime => '20040310.214121'}, # 	2004-03-10	21:41:21	2004-03-11	01:50:45	timestamp = productionLow_RF
'0684'=> {trig=>'productionMid',         	field => 'RF',	first=> '5070079',	 last => '5070079',	 list => '',  beginTime => '20040311.015045'}, # 	2004-03-11	01:50:45	2004-03-11	02:11:15	timestamp = productionMid_RF
'0685'=> {trig=>'productionMid',         	field => 'RF',	first=> '5070081',	 last => '5070081',	 list => '',  beginTime => '20040311.021115'}, # 	2004-03-11	02:11:15	2004-03-11	02:24:56
'0686'=> {trig=>'productionLow',         	field => 'RF',	first=> '5070082',	 last => '5070082',	 list => '',  beginTime => '20040311.022456'}, # 	2004-03-11	02:24:56	2004-03-11	03:01:40	timestamp = productionLow_RF
'0687'=> {trig=>'productionLow',         	field => 'RF',	first=> '5070084',	 last => '5070087',	 list => '',  beginTime => '20040311.030140'}, # 	2004-03-11	03:01:40	2004-03-11	08:36:23
'0688'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5071006',	 last => '5071006',	 list => '',  beginTime => '20040311.083623'}, # 	2004-03-11	08:36:23	2004-03-11	08:50:02	timestamp = productionHigh_RF
'0689'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5071008',	 last => '5071008',	 list => '',  beginTime => '20040311.085002'}, # 	2004-03-11	08:50:02	2004-03-11	09:15:23
'0690'=> {trig=>'productionMid',         	field => 'RF',	first=> '5071010',	 last => '5071010',	 list => '',  beginTime => '20040311.091523'}, # 	2004-03-11	09:15:23	2004-03-11	09:41:28	timestamp = productionMid_RF
'0691'=> {trig=>'productionLow',         	field => 'RF',	first=> '5071011',	 last => '5071013',	 list => '',  beginTime => '20040311.094128'}, # 	2004-03-11	09:41:28	2004-03-11	12:21:54	timestamp = productionLow_RF
'0692'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5071015',	 last => '5071020',	 list => '',  beginTime => '20040311.122154'}, # 	2004-03-11	12:21:54	2004-03-11	13:42:35	timestamp = productionMinBias_RF
'0693'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5071022',	 last => '5071023',	 list => '',  beginTime => '20040311.134235'}, # 	2004-03-11	13:42:35	2004-03-12	01:00:34
'0694'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5071050',	 last => '5071051',	 list => '',  beginTime => '20040312.010034'}, # 	2004-03-12	01:00:34	2004-03-12	01:27:48	timestamp = productionHigh_RF
'0695'=> {trig=>'productionMid',         	field => 'RF',	first=> '5071052',	 last => '5071053',	 list => '',  beginTime => '20040312.012748'}, # 	2004-03-12	01:27:48	2004-03-12	02:05:48	timestamp = productionMid_RF
'0696'=> {trig=>'productionLow',         	field => 'RF',	first=> '5071054',	 last => '5071054',	 list => '',  beginTime => '20040312.020548'}, # 	2004-03-12	02:05:48	2004-03-12	02:44:05	timestamp = productionLow_RF
'0697'=> {trig=>'productionLow',         	field => 'RF',	first=> '5071058',	 last => '5071059',	 list => '',  beginTime => '20040312.024405'}, # 	2004-03-12	02:44:05	2004-03-12	05:00:30
'0698'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5071070',	 last => '5071073',	 list => '',  beginTime => '20040312.050030'}, # 	2004-03-12	05:00:30	2004-03-12	10:31:27	timestamp = productionHigh_RF
'0699'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5072005',	 last => '5072005',	 list => '',  beginTime => '20040312.103127'}, # 	2004-03-12	10:31:27	2004-03-12	11:09:12
'0700'=> {trig=>'productionMid',         	field => 'RF',	first=> '5072009',	 last => '5072009',	 list => '',  beginTime => '20040312.110912'}, # 	2004-03-12	11:09:12	2004-03-12	11:44:52	timestamp = productionMid_RF
'0701'=> {trig=>'productionLow',         	field => 'RF',	first=> '5072010',	 last => '5072010',	 list => '',  beginTime => '20040312.114452'}, # 	2004-03-12	11:44:52	2004-03-12	12:12:40	timestamp = productionLow_RF
'0702'=> {trig=>'productionLow',         	field => 'RF',	first=> '5072012',	 last => '5072014',	 list => '',  beginTime => '20040312.121240'}, # 	2004-03-12	12:12:40	2004-03-12	14:04:19
'0703'=> {trig=>'productionLow',         	field => 'RF',	first=> '5072016',	 last => '5072016',	 list => '',  beginTime => '20040312.140419'}, # 	2004-03-12	14:04:19	2004-03-12	14:17:09
'0704'=> {trig=>'productionLow',         	field => 'RF',	first=> '5072019',	 last => '5072019',	 list => '',  beginTime => '20040312.141709'}, # 	2004-03-12	14:17:09	2004-03-12	15:58:34
'0705'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5072028',	 last => '5072029',	 list => '',  beginTime => '20040312.155834'}, # 	2004-03-12	15:58:34	2004-03-12	17:13:44	timestamp = productionHigh_RF
'0706'=> {trig=>'productionMid',         	field => 'RF',	first=> '5072032',	 last => '5072032',	 list => '',  beginTime => '20040312.171344'}, # 	2004-03-12	17:13:44	2004-03-12	17:41:36	timestamp = productionMid_RF
'0707'=> {trig=>'productionMid',         	field => 'RF',	first=> '5072034',	 last => '5072034',	 list => '',  beginTime => '20040312.174136'}, # 	2004-03-12	17:41:36	2004-03-12	17:55:33
'0708'=> {trig=>'productionLow',         	field => 'RF',	first=> '5072035',	 last => '5072037',	 list => '',  beginTime => '20040312.175533'}, # 	2004-03-12	17:55:33	2004-03-13	05:33:41	timestamp = productionLow_RF
'0709'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5072073',	 last => '5072073',	 list => '',  beginTime => '20040313.053341'}, # 	2004-03-13	05:33:41	2004-03-13	06:19:14	timestamp = productionHigh_RF
'0710'=> {trig=>'productionMid',         	field => 'RF',	first=> '5073001',	 last => '5073001',	 list => '',  beginTime => '20040313.061914'}, # 	2004-03-13	06:19:14	2004-03-13	07:21:14	timestamp = productionMid_RF
'0711'=> {trig=>'productionLow',         	field => 'RF',	first=> '5073003',	 last => '5073006',	 list => '',  beginTime => '20040313.072114'}, # 	2004-03-13	07:21:14	2004-03-13	10:14:59	timestamp = productionLow_RF
'0712'=> {trig=>'productionMid',         	field => 'RF',	first=> '5073013',	 last => '5073013',	 list => '',  beginTime => '20040313.101459'}, # 	2004-03-13	10:14:59	2004-03-13	10:36:23	timestamp = productionMid_RF
'0713'=> {trig=>'productionLow',         	field => 'RF',	first=> '5073014',	 last => '5073016',	 list => '',  beginTime => '20040313.103623'}, # 	2004-03-13	10:36:23	2004-03-13	14:11:41	timestamp = productionLow_RF
'0714'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5073023',	 last => '5073023',	 list => '',  beginTime => '20040313.141141'}, # 	2004-03-13	14:11:41	2004-03-13	14:35:34	timestamp = productionHigh_RF
'0715'=> {trig=>'productionMid',         	field => 'RF',	first=> '5073024',	 last => '5073024',	 list => '',  beginTime => '20040313.143534'}, # 	2004-03-13	14:35:34	2004-03-13	18:22:06	timestamp = productionMid_RF
'0716'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5073037',	 last => '5073037',	 list => '',  beginTime => '20040313.182206'}, # 	2004-03-13	18:22:06	2004-03-13	19:09:21	timestamp = productionHigh_RF
'0717'=> {trig=>'productionMid',         	field => 'RF',	first=> '5073039',	 last => '5073039',	 list => '',  beginTime => '20040313.190921'}, # 	2004-03-13	19:09:21	2004-03-13	19:38:34	timestamp = productionMid_RF
'0718'=> {trig=>'productionLow',         	field => 'RF',	first=> '5073040',	 last => '5073042',	 list => '',  beginTime => '20040313.193834'}, # 	2004-03-13	19:38:34	2004-03-13	23:35:16	timestamp = productionLow_RF
'0719'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5073050',	 last => '5073051',	 list => '',  beginTime => '20040313.233516'}, # 	2004-03-13	23:35:16	2004-03-14	00:26:23	timestamp = productionHigh_RF
'0720'=> {trig=>'productionMid',         	field => 'RF',	first=> '5073052',	 last => '5073052',	 list => '',  beginTime => '20040314.002623'}, # 	2004-03-14	00:26:23	2004-03-14	01:18:01	timestamp = productionMid_RF
'0721'=> {trig=>'productionLow',         	field => 'RF',	first=> '5073054',	 last => '5073056',	 list => '',  beginTime => '20040314.011801'}, # 	2004-03-14	01:18:01	2004-03-14	08:32:27	timestamp = productionLow_RF
'0722'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5074010',	 last => '5074010',	 list => '',  beginTime => '20040314.083227'}, # 	2004-03-14	08:32:27	2004-03-14	09:08:51	timestamp = productionHigh_RF
'0723'=> {trig=>'productionMid',         	field => 'RF',	first=> '5074011',	 last => '5074012',	 list => '',  beginTime => '20040314.090851'}, # 	2004-03-14	09:08:51	2004-03-14	10:06:44	timestamp = productionMid_RF
'0724'=> {trig=>'productionLow',         	field => 'RF',	first=> '5074014',	 last => '5074017',	 list => '',  beginTime => '20040314.100644'}, # 	2004-03-14	10:06:44	2004-03-14	16:31:06	timestamp = productionLow_RF
'0725'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5074025',	 last => '5074025',	 list => '',  beginTime => '20040314.163106'}, # 	2004-03-14	16:31:06	2004-03-14	16:45:12	timestamp = productionHigh_RF
'0726'=> {trig=>'productionMid',         	field => 'RF',	first=> '5074026',	 last => '5074026',	 list => '',  beginTime => '20040314.164512'}, # 	2004-03-14	16:45:12	2004-03-14	17:15:12	timestamp = productionMid_RF
'0727'=> {trig=>'productionMid',         	field => 'RF',	first=> '5074028',	 last => '5074028',	 list => '',  beginTime => '20040314.171512'}, # 	2004-03-14	17:15:12	2004-03-14	17:28:25
'0728'=> {trig=>'productionLow',         	field => 'RF',	first=> '5074029',	 last => '5074031',	 list => '',  beginTime => '20040314.172825'}, # 	2004-03-14	17:28:25	2004-03-14	21:37:33	timestamp = productionLow_RF
'0729'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5074042',	 last => '5074042',	 list => '',  beginTime => '20040314.213733'}, # 	2004-03-14	21:37:33	2004-03-14	22:19:32	timestamp = productionHigh_RF
'0730'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5074044',	 last => '5074044',	 list => '',  beginTime => '20040314.221932'}, # 	2004-03-14	22:19:32	2004-03-14	23:33:39
'0731'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5074051',	 last => '5074052',	 list => '',  beginTime => '20040314.233339'}, # 	2004-03-14	23:33:39	2004-03-15	00:38:42
'0732'=> {trig=>'productionMid',         	field => 'RF',	first=> '5074054',	 last => '5074054',	 list => '',  beginTime => '20040315.003842'}, # 	2004-03-15	00:38:42	2004-03-15	01:02:19	timestamp = productionMid_RF
'0733'=> {trig=>'productionLow',         	field => 'RF',	first=> '5074055',	 last => '5074057',	 list => '',  beginTime => '20040315.010219'}, # 	2004-03-15	01:02:19	2004-03-15	10:33:36	timestamp = productionLow_RF
'0734'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5075044',	 last => '5075044',	 list => '',  beginTime => '20040315.103336'}, # 	2004-03-15	10:33:36	2004-03-15	10:40:38	timestamp = productionHigh_RF
'0735'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5075046',	 last => '5075046',	 list => '',  beginTime => '20040315.104038'}, # 	2004-03-15	10:40:38	2004-03-15	10:57:44
'0736'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5075048',	 last => '5075048',	 list => '',  beginTime => '20040315.105744'}, # 	2004-03-15	10:57:44	2004-03-15	11:23:30
'0737'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5075051',	 last => '5075051',	 list => '',  beginTime => '20040315.112330'}, # 	2004-03-15	11:23:30	2004-03-15	11:36:37
'0738'=> {trig=>'productionMid',         	field => 'RF',	first=> '5075052',	 last => '5075053',	 list => '',  beginTime => '20040315.113637'}, # 	2004-03-15	11:36:37	2004-03-15	12:30:58	timestamp = productionMid_RF
'0739'=> {trig=>'productionLow',         	field => 'RF',	first=> '5075055',	 last => '5075055',	 list => '',  beginTime => '20040315.123058'}, # 	2004-03-15	12:30:58	2004-03-15	19:49:51	timestamp = productionLow_RF
'0740'=> {trig=>'productionMid',         	field => 'RF',	first=> '5075069',	 last => '5075069',	 list => '',  beginTime => '20040315.194951'}, # 	2004-03-15	19:49:51	2004-03-15	20:20:53	timestamp = productionMid_RF
'0741'=> {trig=>'productionLow',         	field => 'RF',	first=> '5075070',	 last => '5075071',	 list => '',  beginTime => '20040315.202053'}, # 	2004-03-15	20:20:53	2004-03-15	21:14:15	timestamp = productionLow_RF
'0742'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5075075',	 last => '5075079',	 list => '',  beginTime => '20040315.211415'}, # 	2004-03-15	21:14:15	2004-03-15	21:56:01	timestamp = productionMinBias_RF
'0743'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5075081',	 last => '5075083',	 list => '',  beginTime => '20040315.215601'}, # 	2004-03-15	21:56:01	2004-03-16	00:02:43
'0744'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5075089',	 last => '5075089',	 list => '',  beginTime => '20040316.000243'}, # 	2004-03-16	00:02:43	2004-03-16	00:44:26	timestamp = productionHigh_RF
'0745'=> {trig=>'productionMid',         	field => 'RF',	first=> '5075090',	 last => '5075090',	 list => '',  beginTime => '20040316.004426'}, # 	2004-03-16	00:44:26	2004-03-16	01:17:51	timestamp = productionMid_RF
'0746'=> {trig=>'productionLow',         	field => 'RF',	first=> '5075093',	 last => '5075098',	 list => '',  beginTime => '20040316.011751'}, # 	2004-03-16	01:17:51	2004-03-16	06:41:52	timestamp = productionLow_RF
'0747'=> {trig=>'productionLow',         	field => 'RF',	first=> '5076018',	 last => '5076019',	 list => '',  beginTime => '20040316.064152'}, # 	2004-03-16	06:41:52	2004-03-16	08:03:57
'0748'=> {trig=>'productionLow',         	field => 'RF',	first=> '5076021',	 last => '5076022',	 list => '',  beginTime => '20040316.080357'}, # 	2004-03-16	08:03:57	2004-03-16	10:59:49
'0749'=> {trig=>'productionCentral',     	field => 'RF',	first=> '5076030',	 last => '5076030',	 list => '',  beginTime => '20040316.105949'}, # 	2004-03-16	10:59:49	2004-03-16	11:55:29	timestamp = productionCentral_RF
'0750'=> {trig=>'productionMid',         	field => 'RF',	first=> '5076032',	 last => '5076032',	 list => '',  beginTime => '20040316.115529'}, # 	2004-03-16	11:55:29	2004-03-16	12:34:23	timestamp = productionMid_RF
'0751'=> {trig=>'productionLow',         	field => 'RF',	first=> '5076033',	 last => '5076034',	 list => '',  beginTime => '20040316.123423'}, # 	2004-03-16	12:34:23	2004-03-16	15:24:50	timestamp = productionLow_RF
'0752'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5076048',	 last => '5076049',	 list => '',  beginTime => '20040316.152450'}, # 	2004-03-16	15:24:50	2004-03-16	17:45:23	timestamp = productionHigh_RF
'0753'=> {trig=>'productionMinBias',     	field => 'ZF',	first=> '5076061',	 last => '5076062',	 list => '',  beginTime => '20040316.174523'}, # 	2004-03-16	17:45:23	2004-03-16	19:59:28	timestamp = productionMinBias_ZF
'0754'=> {trig=>'productionLow',         	field => 'RF',	first=> '5076070',	 last => '5076070',	 list => '',  beginTime => '20040316.195928'}, # 	2004-03-16	19:59:28	2004-03-16	21:49:18	timestamp = productionLow_RF
'0755'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5076084',	 last => '5076084',	 list => '',  beginTime => '20040316.214918'}, # 	2004-03-16	21:49:18	2004-03-16	23:09:48	timestamp = productionHigh_RF
'0756'=> {trig=>'productionLow',         	field => 'RF',	first=> '5076094',	 last => '5076096',	 list => '',  beginTime => '20040316.230948'}, # 	2004-03-16	23:09:48	2004-03-18	12:15:29	timestamp = productionLow_RF
'0757'=> {trig=>'productionLow',         	field => 'RF',	first=> '5078030',	 last => '5078030',	 list => '',  beginTime => '20040318.121529'}, # 	2004-03-18	12:15:29	2004-03-18	13:30:41
'0758'=> {trig=>'productionLow',         	field => 'RF',	first=> '5078033',	 last => '5078033',	 list => '',  beginTime => '20040318.133041'}, # 	2004-03-18	13:30:41	2004-03-19	04:14:48
'0759'=> {trig=>'productionMid',         	field => 'RF',	first=> '5078078',	 last => '5078078',	 list => '',  beginTime => '20040319.041448'}, # 	2004-03-19	04:14:48	2004-03-19	04:38:16	timestamp = productionMid_RF
'0760'=> {trig=>'productionLow',         	field => 'RF',	first=> '5078079',	 last => '5078080',	 list => '',  beginTime => '20040319.043816'}, # 	2004-03-19	04:38:16	2004-03-19	05:20:29	timestamp = productionLow_RF
'0761'=> {trig=>'productionLow',         	field => 'RF',	first=> '5078082',	 last => '5078083',	 list => '',  beginTime => '20040319.052029'}, # 	2004-03-19	05:20:29	2004-03-19	06:12:34
'0762'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079001',	 last => '5079004',	 list => '',  beginTime => '20040319.061234'}, # 	2004-03-19	06:12:34	2004-03-19	09:02:36
'0763'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5079012',	 last => '5079012',	 list => '',  beginTime => '20040319.090236'}, # 	2004-03-19	09:02:36	2004-03-19	10:20:20	timestamp = productionHigh_RF
'0764'=> {trig=>'productionMid',         	field => 'RF',	first=> '5079014',	 last => '5079014',	 list => '',  beginTime => '20040319.102020'}, # 	2004-03-19	10:20:20	2004-03-19	11:02:10	timestamp = productionMid_RF
'0765'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079015',	 last => '5079016',	 list => '',  beginTime => '20040319.110210'}, # 	2004-03-19	11:02:10	2004-03-19	13:46:03	timestamp = productionLow_RF
'0766'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5079026',	 last => '5079026',	 list => '',  beginTime => '20040319.134603'}, # 	2004-03-19	13:46:03	2004-03-19	14:07:36	timestamp = productionHigh_RF
'0767'=> {trig=>'productionMid',         	field => 'RF',	first=> '5079027',	 last => '5079027',	 list => '',  beginTime => '20040319.140736'}, # 	2004-03-19	14:07:36	2004-03-19	14:59:00	timestamp = productionMid_RF
'0768'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079030',	 last => '5079030',	 list => '',  beginTime => '20040319.145900'}, # 	2004-03-19	14:59:00	2004-03-19	15:37:28	timestamp = productionLow_RF
'0769'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079032',	 last => '5079032',	 list => '',  beginTime => '20040319.153728'}, # 	2004-03-19	15:37:28	2004-03-19	16:14:16
'0770'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079034',	 last => '5079034',	 list => '',  beginTime => '20040319.161416'}, # 	2004-03-19	16:14:16	2004-03-19	16:22:01
'0771'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079036',	 last => '5079036',	 list => '',  beginTime => '20040319.162201'}, # 	2004-03-19	16:22:01	2004-03-19	20:45:09
'0772'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5079047',	 last => '5079047',	 list => '',  beginTime => '20040319.204509'}, # 	2004-03-19	20:45:09	2004-03-19	20:54:24	timestamp = productionHigh_RF
'0773'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5079049',	 last => '5079049',	 list => '',  beginTime => '20040319.205424'}, # 	2004-03-19	20:54:24	2004-03-19	21:04:46
'0774'=> {trig=>'productionMid',         	field => 'RF',	first=> '5079050',	 last => '5079050',	 list => '',  beginTime => '20040319.210446'}, # 	2004-03-19	21:04:46	2004-03-19	21:20:48	timestamp = productionMid_RF
'0775'=> {trig=>'productionMid',         	field => 'RF',	first=> '5079052',	 last => '5079052',	 list => '',  beginTime => '20040319.212048'}, # 	2004-03-19	21:20:48	2004-03-19	21:55:08
'0776'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079056',	 last => '5079061',	 list => '',  beginTime => '20040319.215508'}, # 	2004-03-19	21:55:08	2004-03-20	02:35:25	timestamp = productionLow_RF
'0777'=> {trig=>'productionMid',         	field => 'RF',	first=> '5079070',	 last => '5079070',	 list => '',  beginTime => '20040320.023525'}, # 	2004-03-20	02:35:25	2004-03-20	03:36:09	timestamp = productionMid_RF
'0778'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079073',	 last => '5079073',	 list => '',  beginTime => '20040320.033609'}, # 	2004-03-20	03:36:09	2004-03-20	03:56:16	timestamp = productionLow_RF
'0779'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079075',	 last => '5079076',	 list => '',  beginTime => '20040320.035616'}, # 	2004-03-20	03:56:16	2004-03-20	04:39:24
'0780'=> {trig=>'productionLow',         	field => 'RF',	first=> '5079079',	 last => '5079080',	 list => '',  beginTime => '20040320.043924'}, # 	2004-03-20	04:39:24	2004-03-20	06:36:55
'0781'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5080006',	 last => '5080006',	 list => '',  beginTime => '20040320.063655'}, # 	2004-03-20	06:36:55	2004-03-20	08:09:54	timestamp = productionHigh_RF
'0782'=> {trig=>'productionMid',         	field => 'RF',	first=> '5080008',	 last => '5080008',	 list => '',  beginTime => '20040320.080954'}, # 	2004-03-20	08:09:54	2004-03-20	08:54:54	timestamp = productionMid_RF
'0783'=> {trig=>'productionLow',         	field => 'RF',	first=> '5080009',	 last => '5080010',	 list => '',  beginTime => '20040320.085454'}, # 	2004-03-20	08:54:54	2004-03-20	10:37:03	timestamp = productionLow_RF
'0784'=> {trig=>'productionLow',         	field => 'RF',	first=> '5080012',	 last => '5080014',	 list => '',  beginTime => '20040320.103703'}, # 	2004-03-20	10:37:03	2004-03-20	14:41:16
'0785'=> {trig=>'productionLow',         	field => 'RF',	first=> '5080017',	 last => '5080017',	 list => '',  beginTime => '20040320.144116'}, # 	2004-03-20	14:41:16	2004-03-20	17:26:21
'0786'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5080027',	 last => '5080029',	 list => '',  beginTime => '20040320.172621'}, # 	2004-03-20	17:26:21	2004-03-20	18:39:43	timestamp = productionHigh_RF
'0787'=> {trig=>'productionMid',         	field => 'RF',	first=> '5080031',	 last => '5080031',	 list => '',  beginTime => '20040320.183943'}, # 	2004-03-20	18:39:43	2004-03-20	19:28:08	timestamp = productionMid_RF
'0788'=> {trig=>'productionLow',         	field => 'RF',	first=> '5080032',	 last => '5080033',	 list => '',  beginTime => '20040320.192808'}, # 	2004-03-20	19:28:08	2004-03-20	22:44:33	timestamp = productionLow_RF
'0789'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5080044',	 last => '5080044',	 list => '',  beginTime => '20040320.224433'}, # 	2004-03-20	22:44:33	2004-03-20	23:47:24	timestamp = productionHigh_RF
'0790'=> {trig=>'productionMid',         	field => 'RF',	first=> '5080047',	 last => '5080047',	 list => '',  beginTime => '20040320.234724'}, # 	2004-03-20	23:47:24	2004-03-21	00:18:47	timestamp = productionMid_RF
'0791'=> {trig=>'productionLow',         	field => 'RF',	first=> '5080048',	 last => '5080051',	 list => '',  beginTime => '20040321.001847'}, # 	2004-03-21	00:18:47	2004-03-21	03:38:06	timestamp = productionLow_RF
'0792'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5080057',	 last => '5080057',	 list => '',  beginTime => '20040321.033806'}, # 	2004-03-21	03:38:06	2004-03-21	04:10:37	timestamp = productionHigh_RF
'0793'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5080059',	 last => '5080060',	 list => '',  beginTime => '20040321.041037'}, # 	2004-03-21	04:10:37	2004-03-21	05:32:51
'0794'=> {trig=>'productionMid',         	field => 'RF',	first=> '5080063',	 last => '5080063',	 list => '',  beginTime => '20040321.053251'}, # 	2004-03-21	05:32:51	2004-03-21	06:18:05	timestamp = productionMid_RF
'0795'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081001',	 last => '5081001',	 list => '',  beginTime => '20040321.061805'}, # 	2004-03-21	06:18:05	2004-03-21	07:28:25	timestamp = productionLow_RF
'0796'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081003',	 last => '5081003',	 list => '',  beginTime => '20040321.072825'}, # 	2004-03-21	07:28:25	2004-03-21	08:25:22
'0797'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5081011',	 last => '5081014',	 list => '',  beginTime => '20040321.082522'}, # 	2004-03-21	08:25:22	2004-03-21	09:55:43	timestamp = productionHigh_RF
'0798'=> {trig=>'productionMid',         	field => 'RF',	first=> '5081015',	 last => '5081016',	 list => '',  beginTime => '20040321.095543'}, # 	2004-03-21	09:55:43	2004-03-21	11:14:05	timestamp = productionMid_RF
'0799'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081018',	 last => '5081019',	 list => '',  beginTime => '20040321.111405'}, # 	2004-03-21	11:14:05	2004-03-21	13:28:14	timestamp = productionLow_RF
'0800'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5081031',	 last => '5081032',	 list => '',  beginTime => '20040321.132814'}, # 	2004-03-21	13:28:14	2004-03-21	14:59:59	timestamp = productionHigh_RF
'0801'=> {trig=>'productionMid',         	field => 'RF',	first=> '5081034',	 last => '5081034',	 list => '',  beginTime => '20040321.145959'}, # 	2004-03-21	14:59:59	2004-03-21	15:47:46	timestamp = productionMid_RF
'0802'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081035',	 last => '5081036',	 list => '',  beginTime => '20040321.154746'}, # 	2004-03-21	15:47:46	2004-03-21	17:04:43	timestamp = productionLow_RF
'0803'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081044',	 last => '5081044',	 list => '',  beginTime => '20040321.170443'}, # 	2004-03-21	17:04:43	2004-03-21	18:32:22
'0804'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5081053',	 last => '5081053',	 list => '',  beginTime => '20040321.183222'}, # 	2004-03-21	18:32:22	2004-03-21	19:27:37	timestamp = productionHigh_RF
'0805'=> {trig=>'productionMid',         	field => 'RF',	first=> '5081055',	 last => '5081056',	 list => '',  beginTime => '20040321.192737'}, # 	2004-03-21	19:27:37	2004-03-21	19:43:40	timestamp = productionMid_RF
'0806'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081057',	 last => '5081058',	 list => '',  beginTime => '20040321.194340'}, # 	2004-03-21	19:43:40	2004-03-21	21:25:58	timestamp = productionLow_RF
'0807'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081061',	 last => '5081062',	 list => '',  beginTime => '20040321.212558'}, # 	2004-03-21	21:25:58	2004-03-21	23:35:31
'0808'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081064',	 last => '5081065',	 list => '',  beginTime => '20040321.233531'}, # 	2004-03-21	23:35:31	2004-03-22	00:03:21
'0809'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081067',	 last => '5081068',	 list => '',  beginTime => '20040322.000321'}, # 	2004-03-22	00:03:21	2004-03-22	03:16:14
'0810'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5081081',	 last => '5081081',	 list => '',  beginTime => '20040322.031614'}, # 	2004-03-22	03:16:14	2004-03-22	03:28:01	timestamp = productionHigh_RF
'0811'=> {trig=>'productionMid',         	field => 'RF',	first=> '5081082',	 last => '5081082',	 list => '',  beginTime => '20040322.032801'}, # 	2004-03-22	03:28:01	2004-03-22	04:18:00	timestamp = productionMid_RF
'0812'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081083',	 last => '5081083',	 list => '',  beginTime => '20040322.041800'}, # 	2004-03-22	04:18:00	2004-03-22	05:30:25	timestamp = productionLow_RF
'0813'=> {trig=>'productionLow',         	field => 'RF',	first=> '5081085',	 last => '5081085',	 list => '',  beginTime => '20040322.053025'}, # 	2004-03-22	05:30:25	2004-03-22	09:31:33
'0814'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5082015',	 last => '5082015',	 list => '',  beginTime => '20040322.093133'}, # 	2004-03-22	09:31:33	2004-03-22	10:36:04	timestamp = productionHigh_RF
'0815'=> {trig=>'productionMid',         	field => 'RF',	first=> '5082016',	 last => '5082016',	 list => '',  beginTime => '20040322.103604'}, # 	2004-03-22	10:36:04	2004-03-22	11:35:11	timestamp = productionMid_RF
'0816'=> {trig=>'productionLow',         	field => 'RF',	first=> '5082018',	 last => '5082018',	 list => '',  beginTime => '20040322.113511'}, # 	2004-03-22	11:35:11	2004-03-22	12:44:17	timestamp = productionLow_RF
'0817'=> {trig=>'productionLow',         	field => 'RF',	first=> '5082020',	 last => '5082021',	 list => '',  beginTime => '20040322.124417'}, # 	2004-03-22	12:44:17	2004-03-22	16:26:46
'0818'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5082035',	 last => '5082035',	 list => '',  beginTime => '20040322.162646'}, # 	2004-03-22	16:26:46	2004-03-22	16:51:12	timestamp = productionHigh_RF
'0819'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5082037',	 last => '5082037',	 list => '',  beginTime => '20040322.165112'}, # 	2004-03-22	16:51:12	2004-03-22	17:21:42
'0820'=> {trig=>'productionMid',         	field => 'RF',	first=> '5082040',	 last => '5082040',	 list => '',  beginTime => '20040322.172142'}, # 	2004-03-22	17:21:42	2004-03-22	22:44:57	timestamp = productionMid_RF
'0821'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5082051',	 last => '5082052',	 list => '',  beginTime => '20040322.224457'}, # 	2004-03-22	22:44:57	2004-03-22	23:46:03	timestamp = productionHigh_RF
'0822'=> {trig=>'productionMid',         	field => 'RF',	first=> '5082053',	 last => '5082053',	 list => '',  beginTime => '20040322.234603'}, # 	2004-03-22	23:46:03	2004-03-23	00:37:43	timestamp = productionMid_RF
'0823'=> {trig=>'productionLow',         	field => 'RF',	first=> '5082056',	 last => '5082056',	 list => '',  beginTime => '20040323.003743'}, # 	2004-03-23	00:37:43	2004-03-23	13:43:30	timestamp = productionLow_RF
'0824'=> {trig=>'productionHigh',        	field => 'RF',	first=> '5083011',	 last => '5083012',	 list => '',  beginTime => '20040323.134330'}, # 	2004-03-23	13:43:30	2004-03-23	14:48:01	timestamp = productionHigh_RF
'0825'=> {trig=>'productionMid',         	field => 'RF',	first=> '5083013',	 last => '5083013',	 list => '',  beginTime => '20040323.144801'}, # 	2004-03-23	14:48:01	2004-03-23	15:09:29	timestamp = productionMid_RF
'0826'=> {trig=>'productionMid',         	field => 'RF',	first=> '5083016',	 last => '5083016',	 list => '',  beginTime => '20040323.150929'}, # 	2004-03-23	15:09:29	2004-03-23	15:36:34
'0827'=> {trig=>'productionLow',         	field => 'RF',	first=> '5083017',	 last => '5083017',	 list => '',  beginTime => '20040323.153634'}, # 	2004-03-23	15:36:34	2004-03-23	15:56:10	timestamp = productionLow_RF
'0828'=> {trig=>'productionLow',         	field => 'RF',	first=> '5083021',	 last => '5083021',	 list => '',  beginTime => '20040323.155610'}, # 	2004-03-23	15:56:10	2004-03-23	16:44:56
'0829'=> {trig=>'productionLow',         	field => 'RF',	first=> '5083023',	 last => '5083025',	 list => '',  beginTime => '20040323.164456'}, # 	2004-03-23	16:44:56	2004-03-24	09:25:47
'0830'=> {trig=>'productionMinBias',     	field => 'RF',	first=> '5084009',	 last => '5084012',	 list => '',  beginTime => '20040324.092547'}, # 	2004-03-24	09:25:47	2004-03-24	10:06:37	timestamp = productionMinBias_RF
'0831'=> {trig=>'productionMid',         	field => 'RF',	first=> '5084015',	 last => '5084015',	 list => '',  beginTime => '20040324.100637'}, # 	2004-03-24	10:06:37	2004-03-25	02:32:17	timestamp = productionMid_RF
'0832'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5084045',	 last => '5084049',	 list => '',  beginTime => '20040325.023217'}, # 	2004-03-25	02:32:17	2004-03-25	19:11:57	timestamp = production62GeV_RF
'0833'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5085017',	 last => '5085018',	 list => '',  beginTime => '20040325.191157'}, # 	2004-03-25	19:11:57	2004-03-25	20:21:45
'0834'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5085020',	 last => '5085020',	 list => '',  beginTime => '20040325.202145'}, # 	2004-03-25	20:21:45	2004-03-25	21:10:40
'0835'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5085022',	 last => '5085022',	 list => '',  beginTime => '20040325.211040'}, # 	2004-03-25	21:10:40	2004-03-25	21:59:51
'0836'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5085025',	 last => '5085025',	 list => '',  beginTime => '20040325.215951'}, # 	2004-03-25	21:59:51	2004-03-26	07:06:18
'0837'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086008',	 last => '5086009',	 list => '',  beginTime => '20040326.070618'}, # 	2004-03-26	07:06:18	2004-03-26	09:11:55
'0838'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086014',	 last => '5086014',	 list => '',  beginTime => '20040326.091155'}, # 	2004-03-26	09:11:55	2004-03-26	10:10:25
'0839'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086016',	 last => '5086016',	 list => '',  beginTime => '20040326.101025'}, # 	2004-03-26	10:10:25	2004-03-26	16:11:57
'0840'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086037',	 last => '5086040',	 list => '',  beginTime => '20040326.161157'}, # 	2004-03-26	16:11:57	2004-03-26	17:43:53
'0841'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086043',	 last => '5086044',	 list => '',  beginTime => '20040326.174353'}, # 	2004-03-26	17:43:53	2004-03-26	18:29:14
'0842'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086046',	 last => '5086047',	 list => '',  beginTime => '20040326.182914'}, # 	2004-03-26	18:29:14	2004-03-26	22:50:19
'0843'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086054',	 last => '5086055',	 list => '',  beginTime => '20040326.225019'}, # 	2004-03-26	22:50:19	2004-03-27	00:50:22
'0844'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086064',	 last => '5086064',	 list => '',  beginTime => '20040327.005022'}, # 	2004-03-27	00:50:22	2004-03-27	01:21:43
'0845'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086067',	 last => '5086067',	 list => '',  beginTime => '20040327.012143'}, # 	2004-03-27	01:21:43	2004-03-27	02:27:39
'0846'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5086072',	 last => '5086073',	 list => '',  beginTime => '20040327.022739'}, # 	2004-03-27	02:27:39	2004-03-27	06:18:29
'0847'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087005',	 last => '5087005',	 list => '',  beginTime => '20040327.061829'}, # 	2004-03-27	06:18:29	2004-03-27	07:26:12
'0848'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087007',	 last => '5087010',	 list => '',  beginTime => '20040327.072612'}, # 	2004-03-27	07:26:12	2004-03-27	11:27:26
'0849'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087023',	 last => '5087023',	 list => '',  beginTime => '20040327.112726'}, # 	2004-03-27	11:27:26	2004-03-27	12:30:02
'0850'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087025',	 last => '5087027',	 list => '',  beginTime => '20040327.123002'}, # 	2004-03-27	12:30:02	2004-03-27	16:08:37
'0851'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087044',	 last => '5087045',	 list => '',  beginTime => '20040327.160837'}, # 	2004-03-27	16:08:37	2004-03-27	21:30:36
'0852'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087058',	 last => '5087058',	 list => '',  beginTime => '20040327.213036'}, # 	2004-03-27	21:30:36	2004-03-27	22:35:38
'0853'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087060',	 last => '5087063',	 list => '',  beginTime => '20040327.223538'}, # 	2004-03-27	22:35:38	2004-03-28	02:08:38
'0854'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087073',	 last => '5087073',	 list => '',  beginTime => '20040328.020838'}, # 	2004-03-28	02:08:38	2004-03-28	03:06:56
'0855'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087075',	 last => '5087076',	 list => '',  beginTime => '20040328.030656'}, # 	2004-03-28	03:06:56	2004-03-28	05:28:15
'0856'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5087079',	 last => '5087079',	 list => '',  beginTime => '20040328.052815'}, # 	2004-03-28	05:28:15	2004-03-28	07:29:15
'0857'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088007',	 last => '5088007',	 list => '',  beginTime => '20040328.072915'}, # 	2004-03-28	07:29:15	2004-03-28	08:04:16
'0858'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088010',	 last => '5088010',	 list => '',  beginTime => '20040328.080416'}, # 	2004-03-28	08:04:16	2004-03-28	09:08:16
'0859'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088012',	 last => '5088012',	 list => '',  beginTime => '20040328.090816'}, # 	2004-03-28	09:08:16	2004-03-28	10:14:13
'0860'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088014',	 last => '5088014',	 list => '',  beginTime => '20040328.101413'}, # 	2004-03-28	10:14:13	2004-03-28	12:26:51
'0861'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088027',	 last => '5088027',	 list => '',  beginTime => '20040328.122651'}, # 	2004-03-28	12:26:51	2004-03-28	13:29:36
'0862'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088029',	 last => '5088031',	 list => '',  beginTime => '20040328.132936'}, # 	2004-03-28	13:29:36	2004-03-28	18:29:49
'0863'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088046',	 last => '5088046',	 list => '',  beginTime => '20040328.182949'}, # 	2004-03-28	18:29:49	2004-03-28	19:26:21
'0864'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088048',	 last => '5088050',	 list => '',  beginTime => '20040328.192621'}, # 	2004-03-28	19:26:21	2004-03-28	23:26:34
'0865'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088060',	 last => '5088060',	 list => '',  beginTime => '20040328.232634'}, # 	2004-03-28	23:26:34	2004-03-29	00:28:15
'0866'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5088062',	 last => '5088065',	 list => '',  beginTime => '20040329.002815'}, # 	2004-03-29	00:28:15	2004-03-29	13:26:38
'0867'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5089022',	 last => '5089024',	 list => '',  beginTime => '20040329.132638'}, # 	2004-03-29	13:26:38	2004-03-29	14:49:47
'0868'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5089027',	 last => '5089029',	 list => '',  beginTime => '20040329.144947'}, # 	2004-03-29	14:49:47	2004-03-29	15:35:06
'0869'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5089031',	 last => '5089032',	 list => '',  beginTime => '20040329.153506'}, # 	2004-03-29	15:35:06	2004-03-29	16:18:08
'0870'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5089035',	 last => '5089036',	 list => '',  beginTime => '20040329.161808'}, # 	2004-03-29	16:18:08	2004-03-29	18:41:01
'0871'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5089048',	 last => '5089048',	 list => '',  beginTime => '20040329.184101'}, # 	2004-03-29	18:41:01	2004-03-29	19:35:21
'0872'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5089050',	 last => '5089053',	 list => '',  beginTime => '20040329.193521'}, # 	2004-03-29	19:35:21	2004-03-30	00:00:15
'0873'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5089066',	 last => '5089067',	 list => '',  beginTime => '20040330.000015'}, # 	2004-03-30	00:00:15	2004-03-30	01:40:38
'0874'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5089069',	 last => '5089071',	 list => '',  beginTime => '20040330.014038'}, # 	2004-03-30	01:40:38	2004-03-30	12:50:22
'0875'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090009',	 last => '5090009',	 list => '',  beginTime => '20040330.125022'}, # 	2004-03-30	12:50:22	2004-03-30	13:47:12
'0876'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090012',	 last => '5090012',	 list => '',  beginTime => '20040330.134712'}, # 	2004-03-30	13:47:12	2004-03-30	14:41:41
'0877'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090015',	 last => '5090016',	 list => '',  beginTime => '20040330.144141'}, # 	2004-03-30	14:41:41	2004-03-30	16:18:09
'0878'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090018',	 last => '5090018',	 list => '',  beginTime => '20040330.161809'}, # 	2004-03-30	16:18:09	2004-03-30	17:46:18
'0879'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090029',	 last => '5090029',	 list => '',  beginTime => '20040330.174618'}, # 	2004-03-30	17:46:18	2004-03-30	18:49:37
'0880'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090032',	 last => '5090032',	 list => '',  beginTime => '20040330.184937'}, # 	2004-03-30	18:49:37	2004-03-30	20:51:33
'0881'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090035',	 last => '5090035',	 list => '',  beginTime => '20040330.205133'}, # 	2004-03-30	20:51:33	2004-03-30	21:15:43
'0882'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090038',	 last => '5090038',	 list => '',  beginTime => '20040330.211543'}, # 	2004-03-30	21:15:43	2004-03-31	01:15:57
'0883'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090058',	 last => '5090060',	 list => '',  beginTime => '20040331.011557'}, # 	2004-03-31	01:15:57	2004-03-31	02:30:47
'0884'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090064',	 last => '5090064',	 list => '',  beginTime => '20040331.023047'}, # 	2004-03-31	02:30:47	2004-03-31	02:56:33
'0885'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5090070',	 last => '5090071',	 list => '',  beginTime => '20040331.025633'}, # 	2004-03-31	02:56:33	2004-03-31	06:11:00
'0886'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091003',	 last => '5091003',	 list => '',  beginTime => '20040331.061100'}, # 	2004-03-31	06:11:00	2004-03-31	07:11:13
'0887'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091005',	 last => '5091006',	 list => '',  beginTime => '20040331.071113'}, # 	2004-03-31	07:11:13	2004-03-31	08:33:41
'0888'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091008',	 last => '5091008',	 list => '',  beginTime => '20040331.083341'}, # 	2004-03-31	08:33:41	2004-03-31	12:05:33
'0889'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091026',	 last => '5091026',	 list => '',  beginTime => '20040331.120533'}, # 	2004-03-31	12:05:33	2004-03-31	13:11:45
'0890'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091028',	 last => '5091028',	 list => '',  beginTime => '20040331.131145'}, # 	2004-03-31	13:11:45	2004-03-31	13:52:12
'0891'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091031',	 last => '5091033',	 list => '',  beginTime => '20040331.135212'}, # 	2004-03-31	13:52:12	2004-03-31	16:48:10
'0892'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091052',	 last => '5091052',	 list => '',  beginTime => '20040331.164810'}, # 	2004-03-31	16:48:10	2004-03-31	17:52:56
'0893'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091061',	 last => '5091061',	 list => '',  beginTime => '20040331.175256'}, # 	2004-03-31	17:52:56	2004-03-31	18:09:21
'0894'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091063',	 last => '5091063',	 list => '',  beginTime => '20040331.180921'}, # 	2004-03-31	18:09:21	2004-03-31	18:37:46
'0895'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091065',	 last => '5091066',	 list => '',  beginTime => '20040331.183746'}, # 	2004-03-31	18:37:46	2004-03-31	22:53:26
'0896'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091082',	 last => '5091082',	 list => '',  beginTime => '20040331.225326'}, # 	2004-03-31	22:53:26	2004-04-01	00:21:08
'0897'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5091087',	 last => '5091089',	 list => '',  beginTime => '20040401.002108'}, # 	2004-04-01	00:21:08	2004-04-01	18:33:16
'0898'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5092020',	 last => '5092020',	 list => '',  beginTime => '20040401.183316'}, # 	2004-04-01	18:33:16	2004-04-01	19:57:09
'0899'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5092023',	 last => '5092024',	 list => '',  beginTime => '20040401.195709'}, # 	2004-04-01	19:57:09	2004-04-02	06:42:23
'0900'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5093007',	 last => '5093007',	 list => '',  beginTime => '20040402.064223'}, # 	2004-04-02	06:42:23	2004-04-02	07:50:01
'0901'=> {trig=>'production62GeV',       	field => 'RF',	first=> '5093010',	 last => '5093010',	 list => '',  beginTime => '20040402.075001'}, # 	2004-04-02	07:50:01	2004-04-26	23:06:02
'0902'=> {trig=>'productionPP',          	field => 'RF',	first=> '5117052',	 last => '5117054',	 list => '',  beginTime => '20040426.230602'}, # 	2004-04-26	23:06:02	2004-04-27	00:03:40	timestamp = productionPP_RF
'0903'=> {trig=>'productionPP',          	field => 'RF',	first=> '5117056',	 last => '5117056',	 list => '',  beginTime => '20040427.000340'}, # 	2004-04-27	00:03:40	2004-04-27	00:28:00
'0904'=> {trig=>'productionPP',          	field => 'RF',	first=> '5117059',	 last => '5117061',	 list => '',  beginTime => '20040427.002800'}, # 	2004-04-27	00:28:00	2004-04-27	01:45:39
'0905'=> {trig=>'productionPP',          	field => 'RF',	first=> '5117065',	 last => '5117067',	 list => '',  beginTime => '20040427.014539'}, # 	2004-04-27	01:45:39	2004-04-27	02:36:07
'0906'=> {trig=>'productionPP',          	field => 'RF',	first=> '5117069',	 last => '5117073',	 list => '',  beginTime => '20040427.023607'}, # 	2004-04-27	02:36:07	2004-04-27	08:11:12
'0907'=> {trig=>'productionPP',          	field => 'RF',	first=> '5118006',	 last => '5118007',	 list => '',  beginTime => '20040427.081112'}, # 	2004-04-27	08:11:12	2004-04-27	09:22:48
'0908'=> {trig=>'productionPP',          	field => 'RF',	first=> '5118009',	 last => '5118009',	 list => '',  beginTime => '20040427.092248'}, # 	2004-04-27	09:22:48	2004-04-27	10:15:28
'0909'=> {trig=>'productionPP',          	field => 'RF',	first=> '5118011',	 last => '5118011',	 list => '',  beginTime => '20040427.101528'}, # 	2004-04-27	10:15:28	2004-04-27	22:30:28
'0910'=> {trig=>'productionPP',          	field => 'RF',	first=> '5118042',	 last => '5118044',	 list => '',  beginTime => '20040427.223028'}, # 	2004-04-27	22:30:28	2004-04-28	00:03:54
'0911'=> {trig=>'productionPP',          	field => 'RF',	first=> '5118046',	 last => '5118046',	 list => '',  beginTime => '20040428.000354'}, # 	2004-04-28	00:03:54	2004-04-28	03:25:56
'0912'=> {trig=>'productionPP',          	field => 'RF',	first=> '5118053',	 last => '5118053',	 list => '',  beginTime => '20040428.032556'}, # 	2004-04-28	03:25:56	2004-04-28	04:01:14
'0913'=> {trig=>'productionPP',          	field => 'RF',	first=> '5118055',	 last => '5118057',	 list => '',  beginTime => '20040428.040114'}, # 	2004-04-28	04:01:14	2004-04-28	10:51:47
'0914'=> {trig=>'productionPP',          	field => 'RF',	first=> '5119003',	 last => '5119003',	 list => '',  beginTime => '20040428.105147'}, # 	2004-04-28	10:51:47	2004-04-29	02:20:49
'0915'=> {trig=>'productionPP',          	field => 'RF',	first=> '5119029',	 last => '5119029',	 list => '',  beginTime => '20040429.022049'}, # 	2004-04-29	02:20:49	2004-04-29	03:01:32
'0916'=> {trig=>'productionPP',          	field => 'RF',	first=> '5119033',	 last => '5119036',	 list => '',  beginTime => '20040429.030132'}, # 	2004-04-29	03:01:32	2004-04-29	08:39:08
'0917'=> {trig=>'productionPP',          	field => 'RF',	first=> '5120006',	 last => '5120006',	 list => '',  beginTime => '20040429.083908'}, # 	2004-04-29	08:39:08	2004-04-29	09:03:10
'0918'=> {trig=>'productionPP',          	field => 'RF',	first=> '5120009',	 last => '5120013',	 list => '',  beginTime => '20040429.090310'}, # 	2004-04-29	09:03:10	2004-05-05	17:00:28
'0919'=> {trig=>'productionPP',          	field => 'RF',	first=> '5126048',	 last => '5126048',	 list => '',  beginTime => '20040505.170028'}, # 	2004-05-05	17:00:28	2004-05-05	17:11:25
'0920'=> {trig=>'productionPP',          	field => 'RF',	first=> '5126050',	 last => '5126051',	 list => '',  beginTime => '20040505.171125'}, # 	2004-05-05	17:11:25	2004-05-05	18:26:04
'0921'=> {trig=>'productionPP',          	field => 'RF',	first=> '5126056',	 last => '5126056',	 list => '',  beginTime => '20040505.182604'}, # 	2004-05-05	18:26:04	2004-05-05	18:45:25
'0922'=> {trig=>'productionPP',          	field => 'RF',	first=> '5126058',	 last => '5126058',	 list => '',  beginTime => '20040505.184525'}, # 	2004-05-05	18:45:25	2004-05-06	00:34:48
'0923'=> {trig=>'productionPP',          	field => 'RF',	first=> '5126104',	 last => '5126105',	 list => '',  beginTime => '20040506.003448'}, # 	2004-05-06	00:34:48	2004-05-06	01:00:27
'0924'=> {trig=>'productionPP',          	field => 'RF',	first=> '5126107',	 last => '5126107',	 list => '',  beginTime => '20040506.010027'}, # 	2004-05-06	01:00:27	2004-05-06	01:05:33
'0925'=> {trig=>'productionPP',          	field => 'RF',	first=> '5126109',	 last => '5126109',	 list => '',  beginTime => '20040506.010533'}, # 	2004-05-06	01:05:33	2004-05-06	01:13:27
'0926'=> {trig=>'productionPPnoEndcap',  	field => 'RF',	first=> '5126110',	 last => '5126110',	 list => '',  beginTime => '20040506.011327'}, # 	2004-05-06	01:13:27	2004-05-06	01:16:01	timestamp = productionPPnoEndcap_RF
'0927'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5126111',	 last => '5126111',	 list => '',  beginTime => '20040506.011601'}, # 	2004-05-06	01:16:01	2004-05-06	01:18:52	timestamp = productionPPnoBarrel_RF
'0928'=> {trig=>'productionPP',          	field => 'RF',	first=> '5126112',	 last => '5126112',	 list => '',  beginTime => '20040506.011852'}, # 	2004-05-06	01:18:52	2004-05-06	01:35:53	timestamp = productionPP_RF
'0929'=> {trig=>'productionPP',          	field => 'RF',	first=> '5126114',	 last => '5126117',	 list => '',  beginTime => '20040506.013553'}, # 	2004-05-06	01:35:53	2004-05-06	08:47:13
'0930'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5127010',	 last => '5127010',	 list => '',  beginTime => '20040506.084713'}, # 	2004-05-06	08:47:13	2004-05-06	09:02:20	timestamp = productionPPnoBarrel_RF
'0931'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5127012',	 last => '5127012',	 list => '',  beginTime => '20040506.090220'}, # 	2004-05-06	09:02:20	2004-05-06	09:34:26
'0932'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5127014',	 last => '5127014',	 list => '',  beginTime => '20040506.093426'}, # 	2004-05-06	09:34:26	2004-05-06	09:51:46
'0933'=> {trig=>'productionPP',          	field => 'RF',	first=> '5127015',	 last => '5127015',	 list => '',  beginTime => '20040506.095146'}, # 	2004-05-06	09:51:46	2004-05-07	09:37:46	timestamp = productionPP_RF
'0934'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5128006',	 last => '5128017',	 list => '',  beginTime => '20040507.093746'}, # 	2004-05-07	09:37:46	2004-05-07	12:02:21	timestamp = productionPPnoBarrel_RF
'0935'=> {trig=>'productionPP',          	field => 'RF',	first=> '5128023',	 last => '5128023',	 list => '',  beginTime => '20040507.120221'}, # 	2004-05-07	12:02:21	2004-05-07	12:18:28	timestamp = productionPP_RF
'0936'=> {trig=>'productionPP',          	field => 'RF',	first=> '5128025',	 last => '5128025',	 list => '',  beginTime => '20040507.121828'}, # 	2004-05-07	12:18:28	2004-05-07	13:09:17
'0937'=> {trig=>'productionPP',          	field => 'RF',	first=> '5128034',	 last => '5128036',	 list => '',  beginTime => '20040507.130917'}, # 	2004-05-07	13:09:17	2004-05-07	14:12:21
'0938'=> {trig=>'productionPP',          	field => 'RF',	first=> '5128038',	 last => '5128048',	 list => '',  beginTime => '20040507.141221'}, # 	2004-05-07	14:12:21	2004-05-11	01:01:57
'0939'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5131015',	 last => '5131017',	 list => '',  beginTime => '20040511.010157'}, # 	2004-05-11	01:01:57	2004-05-11	01:15:04	timestamp = productionPPnoBarrel_RF
'0940'=> {trig=>'productionPP',          	field => 'RF',	first=> '5131018',	 last => '5131020',	 list => '',  beginTime => '20040511.011504'}, # 	2004-05-11	01:15:04	2004-05-11	02:06:33	timestamp = productionPP_RF
'0941'=> {trig=>'productionPP',          	field => 'RF',	first=> '5131023',	 last => '5131025',	 list => '',  beginTime => '20040511.020633'}, # 	2004-05-11	02:06:33	2004-05-11	21:42:06
'0942'=> {trig=>'productionPP',          	field => 'RF',	first=> '5132051',	 last => '5132051',	 list => '',  beginTime => '20040511.214206'}, # 	2004-05-11	21:42:06	2004-05-11	21:57:36
'0943'=> {trig=>'productionPP',          	field => 'RF',	first=> '5132053',	 last => '5132054',	 list => '',  beginTime => '20040511.215736'}, # 	2004-05-11	21:57:36	2004-05-11	22:29:46
'0944'=> {trig=>'productionPP',          	field => 'RF',	first=> '5132056',	 last => '5132062',	 list => '',  beginTime => '20040511.222946'}, # 	2004-05-11	22:29:46	2004-05-12	11:29:36
'0945'=> {trig=>'productionPP',          	field => 'RF',	first=> '5133007',	 last => '5133010',	 list => '',  beginTime => '20040512.112936'}, # 	2004-05-12	11:29:36	2004-05-12	12:37:18
'0946'=> {trig=>'productionPP',          	field => 'RF',	first=> '5133014',	 last => '5133014',	 list => '',  beginTime => '20040512.123718'}, # 	2004-05-12	12:37:18	2004-05-12	13:17:19
'0947'=> {trig=>'productionPP',          	field => 'RF',	first=> '5133017',	 last => '5133021',	 list => '',  beginTime => '20040512.131719'}, # 	2004-05-12	13:17:19	2004-05-12	14:51:53
'0948'=> {trig=>'productionPP',          	field => 'RF',	first=> '5133023',	 last => '5133024',	 list => '',  beginTime => '20040512.145153'}, # 	2004-05-12	14:51:53	2004-05-12	22:53:58
'0949'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5133036',	 last => '5133036',	 list => '',  beginTime => '20040512.225358'}, # 	2004-05-12	22:53:58	2004-05-12	23:34:53	timestamp = productionPPnoBarrel_RF
'0950'=> {trig=>'productionPP',          	field => 'RF',	first=> '5133041',	 last => '5133042',	 list => '',  beginTime => '20040512.233453'}, # 	2004-05-12	23:34:53	2004-05-13	00:10:41	timestamp = productionPP_RF
'0951'=> {trig=>'productionPP',          	field => 'RF',	first=> '5133044',	 last => '5133045',	 list => '',  beginTime => '20040513.001041'}, # 	2004-05-13	00:10:41	2004-05-13	02:35:17
'0952'=> {trig=>'productionPP',          	field => 'RF',	first=> '5133052',	 last => '5133053',	 list => '',  beginTime => '20040513.023517'}, # 	2004-05-13	02:35:17	2004-05-13	02:54:37
'0953'=> {trig=>'productionPP',          	field => 'RF',	first=> '5133055',	 last => '5133057',	 list => '',  beginTime => '20040513.025437'}, # 	2004-05-13	02:54:37	2004-05-13	04:28:38
'0954'=> {trig=>'productionPP',          	field => 'RF',	first=> '5133067',	 last => '5133070',	 list => '',  beginTime => '20040513.042838'}, # 	2004-05-13	04:28:38	2004-05-13	05:02:51
'0955'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134001',	 last => '5134001',	 list => '',  beginTime => '20040513.050251'}, # 	2004-05-13	05:02:51	2004-05-13	05:08:57
'0956'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134003',	 last => '5134016',	 list => '',  beginTime => '20040513.050857'}, # 	2004-05-13	05:08:57	2004-05-13	10:03:01
'0957'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134022',	 last => '5134026',	 list => '',  beginTime => '20040513.100301'}, # 	2004-05-13	10:03:01	2004-05-13	14:19:14
'0958'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134051',	 last => '5134053',	 list => '',  beginTime => '20040513.141914'}, # 	2004-05-13	14:19:14	2004-05-13	22:14:33
'0959'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134061',	 last => '5134061',	 list => '',  beginTime => '20040513.221433'}, # 	2004-05-13	22:14:33	2004-05-13	22:35:51
'0960'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134063',	 last => '5134064',	 list => '',  beginTime => '20040513.223551'}, # 	2004-05-13	22:35:51	2004-05-13	23:24:50
'0961'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134068',	 last => '5134068',	 list => '',  beginTime => '20040513.232450'}, # 	2004-05-13	23:24:50	2004-05-13	23:30:31
'0962'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5134069',	 last => '5134069',	 list => '',  beginTime => '20040513.233031'}, # 	2004-05-13	23:30:31	2004-05-13	23:41:10	timestamp = productionPPnoBarrel_RF
'0963'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134070',	 last => '5134070',	 list => '',  beginTime => '20040513.234110'}, # 	2004-05-13	23:41:10	2004-05-13	23:48:20	timestamp = productionPP_RF
'0964'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134072',	 last => '5134073',	 list => '',  beginTime => '20040513.234820'}, # 	2004-05-13	23:48:20	2004-05-14	00:29:07
'0965'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134075',	 last => '5134075',	 list => '',  beginTime => '20040514.002907'}, # 	2004-05-14	00:29:07	2004-05-14	01:06:08
'0966'=> {trig=>'productionPP',          	field => 'RF',	first=> '5134079',	 last => '5134079',	 list => '',  beginTime => '20040514.010608'}, # 	2004-05-14	01:06:08	2004-05-14	06:01:15
'0967'=> {trig=>'productionPP',          	field => 'RF',	first=> '5135004',	 last => '5135011',	 list => '',  beginTime => '20040514.060115'}, # 	2004-05-14	06:01:15	2004-05-14	07:26:25
'0968'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5135017',	 last => '5135018',	 list => '',  beginTime => '20040514.072625'}, # 	2004-05-14	07:26:25	2004-05-14	08:22:09	timestamp = productionPPnoBarrel_RF
'0969'=> {trig=>'productionPPnoEndcap',  	field => 'RF',	first=> '5135024',	 last => '5135024',	 list => '',  beginTime => '20040514.082209'}, # 	2004-05-14	08:22:09	2004-05-14	08:42:48	timestamp = productionPPnoEndcap_RF
'0970'=> {trig=>'productionPP',          	field => 'RF',	first=> '5135026',	 last => '5135027',	 list => '',  beginTime => '20040514.084248'}, # 	2004-05-14	08:42:48	2004-05-14	09:06:56	timestamp = productionPP_RF
'0971'=> {trig=>'productionPPnoBarrel',  	field => 'RF',	first=> '5135028',	 last => '5135033',	 list => '',  beginTime => '20040514.090656'}, # 	2004-05-14	09:06:56	2004-05-14	19:21:22	timestamp = productionPPnoBarrel_RF
'0972'=> {trig=>'productionPP',          	field => 'RF',	first=> '5135048',	 last => '5135048',	 list => '',  beginTime => '20040514.192122'}, # 	2004-05-14	19:21:22	2004-05-14	19:35:56	timestamp = productionPP_RF
'0973'=> {trig=>'productionPP',          	field => 'RF',	first=> '5135050',	 last => '5135050',	 list => '',  beginTime => '20040514.193556'}, # 	2004-05-14	19:35:56	2004-05-14	19:35:56
);
1;
