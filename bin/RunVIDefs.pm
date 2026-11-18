#!/usr/bin/perl
use strict;
use warnings;
our @Runs = ( # onl CURRENT | SortRun.pl 
'0000'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6013101',	 last => '6013101',	 list => '',  beginTime => '20050114.004607'}, # 	2005-01-14	00:46:07	2005-01-14	01:08:24	timestamp = cuProductionMinBias_RF
'0001'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6013103',	 last => '6013108',	 list => '',  beginTime => '20050114.010824'}, # 	2005-01-14	01:08:24	2005-01-14	02:30:32
'0002'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6013120',	 last => '6013120',	 list => '',  beginTime => '20050114.023032'}, # 	2005-01-14	02:30:32	2005-01-14	02:40:44
'0003'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6013124',	 last => '6013124',	 list => '',  beginTime => '20050114.024044'}, # 	2005-01-14	02:40:44	2005-01-14	03:04:53
'0004'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6013129',	 last => '6013132',	 list => '',  beginTime => '20050114.030453'}, # 	2005-01-14	03:04:53	2005-01-14	04:34:25
'0005'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6013134',	 last => '6013134',	 list => '',  beginTime => '20050114.043425'}, # 	2005-01-14	04:34:25	2005-01-14	05:27:01
'0006'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014001',	 last => '6014002',	 list => '',  beginTime => '20050114.052701'}, # 	2005-01-14	05:27:01	2005-01-15	02:59:49
'0007'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014088',	 last => '6014089',	 list => '',  beginTime => '20050115.025949'}, # 	2005-01-15	02:59:49	2005-01-15	03:24:39
'0008'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014091',	 last => '6014091',	 list => '',  beginTime => '20050115.032439'}, # 	2005-01-15	03:24:39	2005-01-15	03:44:39
'0009'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014093',	 last => '6014093',	 list => '',  beginTime => '20050115.034439'}, # 	2005-01-15	03:44:39	2005-01-15	03:50:50
'0010'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014095',	 last => '6014095',	 list => '',  beginTime => '20050115.035050'}, # 	2005-01-15	03:50:50	2005-01-15	03:57:45
'0011'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014097',	 last => '6014097',	 list => '',  beginTime => '20050115.035745'}, # 	2005-01-15	03:57:45	2005-01-15	04:22:58
'0012'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014103',	 last => '6014103',	 list => '',  beginTime => '20050115.042258'}, # 	2005-01-15	04:22:58	2005-01-15	04:29:49
'0013'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014105',	 last => '6014105',	 list => '',  beginTime => '20050115.042949'}, # 	2005-01-15	04:29:49	2005-01-15	04:34:58
'0014'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014107',	 last => '6014107',	 list => '',  beginTime => '20050115.043458'}, # 	2005-01-15	04:34:58	2005-01-15	04:40:29
'0015'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014109',	 last => '6014109',	 list => '',  beginTime => '20050115.044029'}, # 	2005-01-15	04:40:29	2005-01-15	04:47:37
'0016'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014111',	 last => '6014111',	 list => '',  beginTime => '20050115.044737'}, # 	2005-01-15	04:47:37	2005-01-15	04:53:43
'0017'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014113',	 last => '6014113',	 list => '',  beginTime => '20050115.045343'}, # 	2005-01-15	04:53:43	2005-01-15	05:00:08
'0018'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6014115',	 last => '6014115',	 list => '',  beginTime => '20050115.050008'}, # 	2005-01-15	05:00:08	2005-01-15	05:07:50
'0019'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015001',	 last => '6015008',	 list => '',  beginTime => '20050115.050750'}, # 	2005-01-15	05:07:50	2005-01-15	10:49:41
'0020'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015019',	 last => '6015021',	 list => '',  beginTime => '20050115.104941'}, # 	2005-01-15	10:49:41	2005-01-15	11:55:38
'0021'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015023',	 last => '6015024',	 list => '',  beginTime => '20050115.115538'}, # 	2005-01-15	11:55:38	2005-01-15	12:28:51
'0022'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015027',	 last => '6015032',	 list => '',  beginTime => '20050115.122851'}, # 	2005-01-15	12:28:51	2005-01-15	14:24:56
'0023'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015034',	 last => '6015035',	 list => '',  beginTime => '20050115.142456'}, # 	2005-01-15	14:24:56	2005-01-15	23:07:41
'0024'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015043',	 last => '6015044',	 list => '',  beginTime => '20050115.230741'}, # 	2005-01-15	23:07:41	2005-01-15	23:46:02
'0025'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015047',	 last => '6015047',	 list => '',  beginTime => '20050115.234602'}, # 	2005-01-15	23:46:02	2005-01-16	00:19:00
'0026'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015050',	 last => '6015051',	 list => '',  beginTime => '20050116.001900'}, # 	2005-01-16	00:19:00	2005-01-16	00:58:19
'0027'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015053',	 last => '6015053',	 list => '',  beginTime => '20050116.005819'}, # 	2005-01-16	00:58:19	2005-01-16	01:14:09
'0028'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015055',	 last => '6015059',	 list => '',  beginTime => '20050116.011409'}, # 	2005-01-16	01:14:09	2005-01-16	03:04:32
'0029'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6015061',	 last => '6015062',	 list => '',  beginTime => '20050116.030432'}, # 	2005-01-16	03:04:32	2005-01-16	12:56:55
'0030'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016006',	 last => '6016010',	 list => '',  beginTime => '20050116.125655'}, # 	2005-01-16	12:56:55	2005-01-16	14:30:26
'0031'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016012',	 last => '6016015',	 list => '',  beginTime => '20050116.143026'}, # 	2005-01-16	14:30:26	2005-01-16	15:30:14
'0032'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016017',	 last => '6016023',	 list => '',  beginTime => '20050116.153014'}, # 	2005-01-16	15:30:14	2005-01-16	17:39:57
'0033'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016027',	 last => '6016027',	 list => '',  beginTime => '20050116.173957'}, # 	2005-01-16	17:39:57	2005-01-16	20:32:28
'0034'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016035',	 last => '6016035',	 list => '',  beginTime => '20050116.203228'}, # 	2005-01-16	20:32:28	2005-01-16	20:39:46
'0035'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016037',	 last => '6016037',	 list => '',  beginTime => '20050116.203946'}, # 	2005-01-16	20:39:46	2005-01-16	20:49:48
'0036'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016041',	 last => '6016041',	 list => '',  beginTime => '20050116.204948'}, # 	2005-01-16	20:49:48	2005-01-16	20:56:21
'0037'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016043',	 last => '6016043',	 list => '',  beginTime => '20050116.205621'}, # 	2005-01-16	20:56:21	2005-01-16	21:04:08
'0038'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016045',	 last => '6016045',	 list => '',  beginTime => '20050116.210408'}, # 	2005-01-16	21:04:08	2005-01-16	21:16:57
'0039'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016047',	 last => '6016047',	 list => '',  beginTime => '20050116.211657'}, # 	2005-01-16	21:16:57	2005-01-16	22:05:20
'0040'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016055',	 last => '6016056',	 list => '',  beginTime => '20050116.220520'}, # 	2005-01-16	22:05:20	2005-01-16	22:20:16
'0041'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016058',	 last => '6016060',	 list => '',  beginTime => '20050116.222016'}, # 	2005-01-16	22:20:16	2005-01-16	23:02:27
'0042'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016062',	 last => '6016062',	 list => '',  beginTime => '20050116.230227'}, # 	2005-01-16	23:02:27	2005-01-16	23:17:18
'0043'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016064',	 last => '6016066',	 list => '',  beginTime => '20050116.231718'}, # 	2005-01-16	23:17:18	2005-01-17	00:14:53
'0044'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6016068',	 last => '6016072',	 list => '',  beginTime => '20050117.001453'}, # 	2005-01-17	00:14:53	2005-01-17	05:36:45
'0045'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6017004',	 last => '6017009',	 list => '',  beginTime => '20050117.053645'}, # 	2005-01-17	05:36:45	2005-01-17	07:01:00
'0046'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6017012',	 last => '6017013',	 list => '',  beginTime => '20050117.070100'}, # 	2005-01-17	07:01:00	2005-01-17	07:43:34
'0047'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6017016',	 last => '6017021',	 list => '',  beginTime => '20050117.074334'}, # 	2005-01-17	07:43:34	2005-01-17	09:25:42
'0048'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6017024',	 last => '6017027',	 list => '',  beginTime => '20050117.092542'}, # 	2005-01-17	09:25:42	2005-01-17	16:29:20
'0049'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6017046',	 last => '6017053',	 list => '',  beginTime => '20050117.162920'}, # 	2005-01-17	16:29:20	2005-01-17	17:24:00
'0050'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6017056',	 last => '6017058',	 list => '',  beginTime => '20050117.172400'}, # 	2005-01-17	17:24:00	2005-01-17	18:01:47
'0051'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6017060',	 last => '6017065',	 list => '',  beginTime => '20050117.180147'}, # 	2005-01-17	18:01:47	2005-01-17	19:14:22
'0052'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6017067',	 last => '6017080',	 list => '',  beginTime => '20050117.191422'}, # 	2005-01-17	19:14:22	2005-01-18	09:31:26
'0053'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6018005',	 last => '6018007',	 list => '',  beginTime => '20050118.093126'}, # 	2005-01-18	09:31:26	2005-01-18	10:21:57
'0054'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6018010',	 last => '6018012',	 list => '',  beginTime => '20050118.102157'}, # 	2005-01-18	10:21:57	2005-01-18	13:00:02
'0055'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6018014',	 last => '6018014',	 list => '',  beginTime => '20050118.130002'}, # 	2005-01-18	13:00:02	2005-01-18	13:57:58
'0056'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6018016',	 last => '6018018',	 list => '',  beginTime => '20050118.135758'}, # 	2005-01-18	13:57:58	2005-01-18	23:19:46
'0057'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6018032',	 last => '6018033',	 list => '',  beginTime => '20050118.231946'}, # 	2005-01-18	23:19:46	2005-01-18	23:55:53
'0058'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6018041',	 last => '6018042',	 list => '',  beginTime => '20050118.235553'}, # 	2005-01-18	23:55:53	2005-01-19	00:34:40
'0059'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6018044',	 last => '6018045',	 list => '',  beginTime => '20050119.003440'}, # 	2005-01-19	00:34:40	2005-01-19	02:12:09
'0060'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6018065',	 last => '6018067',	 list => '',  beginTime => '20050119.021209'}, # 	2005-01-19	02:12:09	2005-01-20	19:08:13
'0061'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020014',	 last => '6020014',	 list => '',  beginTime => '20050120.190813'}, # 	2005-01-20	19:08:13	2005-01-20	19:19:59
'0062'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020016',	 last => '6020017',	 list => '',  beginTime => '20050120.191959'}, # 	2005-01-20	19:19:59	2005-01-20	19:45:40
'0063'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020020',	 last => '6020021',	 list => '',  beginTime => '20050120.194540'}, # 	2005-01-20	19:45:40	2005-01-20	20:44:49
'0064'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020028',	 last => '6020028',	 list => '',  beginTime => '20050120.204449'}, # 	2005-01-20	20:44:49	2005-01-20	20:48:55
'0065'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020030',	 last => '6020031',	 list => '',  beginTime => '20050120.204855'}, # 	2005-01-20	20:48:55	2005-01-21	00:04:42
'0066'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020037',	 last => '6020037',	 list => '',  beginTime => '20050121.000442'}, # 	2005-01-21	00:04:42	2005-01-21	00:50:03
'0067'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020039',	 last => '6020039',	 list => '',  beginTime => '20050121.005003'}, # 	2005-01-21	00:50:03	2005-01-21	01:13:18
'0068'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020042',	 last => '6020042',	 list => '',  beginTime => '20050121.011318'}, # 	2005-01-21	01:13:18	2005-01-21	01:29:28
'0069'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020044',	 last => '6020044',	 list => '',  beginTime => '20050121.012928'}, # 	2005-01-21	01:29:28	2005-01-21	01:45:15
'0070'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020046',	 last => '6020046',	 list => '',  beginTime => '20050121.014515'}, # 	2005-01-21	01:45:15	2005-01-21	01:55:31
'0071'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020048',	 last => '6020048',	 list => '',  beginTime => '20050121.015531'}, # 	2005-01-21	01:55:31	2005-01-21	02:10:03
'0072'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020050',	 last => '6020050',	 list => '',  beginTime => '20050121.021003'}, # 	2005-01-21	02:10:03	2005-01-21	02:25:42
'0073'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020053',	 last => '6020056',	 list => '',  beginTime => '20050121.022542'}, # 	2005-01-21	02:25:42	2005-01-21	03:04:35
'0074'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020059',	 last => '6020059',	 list => '',  beginTime => '20050121.030435'}, # 	2005-01-21	03:04:35	2005-01-21	03:17:28
'0075'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020062',	 last => '6020062',	 list => '',  beginTime => '20050121.031728'}, # 	2005-01-21	03:17:28	2005-01-21	03:48:44
'0076'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6020064',	 last => '6020068',	 list => '',  beginTime => '20050121.034844'}, # 	2005-01-21	03:48:44	2005-01-21	08:55:49
'0077'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6021004',	 last => '6021007',	 list => '',  beginTime => '20050121.085549'}, # 	2005-01-21	08:55:49	2005-01-21	10:09:47
'0078'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6021009',	 last => '6021010',	 list => '',  beginTime => '20050121.100947'}, # 	2005-01-21	10:09:47	2005-01-21	10:31:45
'0079'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6021012',	 last => '6021012',	 list => '',  beginTime => '20050121.103145'}, # 	2005-01-21	10:31:45	2005-01-22	00:31:03
'0080'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6021042',	 last => '6021042',	 list => '',  beginTime => '20050122.003103'}, # 	2005-01-22	00:31:03	2005-01-22	00:48:40
'0081'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6021044',	 last => '6021045',	 list => '',  beginTime => '20050122.004840'}, # 	2005-01-22	00:48:40	2005-01-22	01:30:35
'0082'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6021047',	 last => '6021047',	 list => '',  beginTime => '20050122.013035'}, # 	2005-01-22	01:30:35	2005-01-22	02:06:54
'0083'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6021051',	 last => '6021054',	 list => '',  beginTime => '20050122.020654'}, # 	2005-01-22	02:06:54	2005-01-22	08:26:52
'0084'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022004',	 last => '6022007',	 list => '',  beginTime => '20050122.082652'}, # 	2005-01-22	08:26:52	2005-01-22	09:28:50
'0085'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022010',	 last => '6022015',	 list => '',  beginTime => '20050122.092850'}, # 	2005-01-22	09:28:50	2005-01-22	11:58:59
'0086'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022017',	 last => '6022019',	 list => '',  beginTime => '20050122.115859'}, # 	2005-01-22	11:58:59	2005-01-22	13:20:03
'0087'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022030',	 last => '6022030',	 list => '',  beginTime => '20050122.132003'}, # 	2005-01-22	13:20:03	2005-01-22	17:02:29
'0088'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022034',	 last => '6022035',	 list => '',  beginTime => '20050122.170229'}, # 	2005-01-22	17:02:29	2005-01-22	17:20:30
'0089'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022037',	 last => '6022038',	 list => '',  beginTime => '20050122.172030'}, # 	2005-01-22	17:20:30	2005-01-22	17:46:15
'0090'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022041',	 last => '6022042',	 list => '',  beginTime => '20050122.174615'}, # 	2005-01-22	17:46:15	2005-01-22	18:26:06
'0091'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022048',	 last => '6022049',	 list => '',  beginTime => '20050122.182606'}, # 	2005-01-22	18:26:06	2005-01-22	19:40:00
'0092'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022051',	 last => '6022054',	 list => '',  beginTime => '20050122.194000'}, # 	2005-01-22	19:40:00	2005-01-22	20:41:03
'0093'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022056',	 last => '6022056',	 list => '',  beginTime => '20050122.204103'}, # 	2005-01-22	20:41:03	2005-01-22	20:54:57
'0094'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022060',	 last => '6022060',	 list => '',  beginTime => '20050122.205457'}, # 	2005-01-22	20:54:57	2005-01-22	21:23:27
'0095'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022066',	 last => '6022067',	 list => '',  beginTime => '20050122.212327'}, # 	2005-01-22	21:23:27	2005-01-23	00:04:13
'0096'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022080',	 last => '6022080',	 list => '',  beginTime => '20050123.000413'}, # 	2005-01-23	00:04:13	2005-01-23	00:12:55
'0097'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022085',	 last => '6022085',	 list => '',  beginTime => '20050123.001255'}, # 	2005-01-23	00:12:55	2005-01-23	00:45:29
'0098'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022087',	 last => '6022087',	 list => '',  beginTime => '20050123.004529'}, # 	2005-01-23	00:45:29	2005-01-23	00:57:37
'0099'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022089',	 last => '6022089',	 list => '',  beginTime => '20050123.005737'}, # 	2005-01-23	00:57:37	2005-01-23	01:29:42
'0100'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022092',	 last => '6022092',	 list => '',  beginTime => '20050123.012942'}, # 	2005-01-23	01:29:42	2005-01-23	02:04:24
'0101'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022094',	 last => '6022096',	 list => '',  beginTime => '20050123.020424'}, # 	2005-01-23	02:04:24	2005-01-23	03:22:10
'0102'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022100',	 last => '6022100',	 list => '',  beginTime => '20050123.032210'}, # 	2005-01-23	03:22:10	2005-01-23	03:37:07
'0103'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022102',	 last => '6022104',	 list => '',  beginTime => '20050123.033707'}, # 	2005-01-23	03:37:07	2005-01-23	03:56:01
'0104'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6022106',	 last => '6022110',	 list => '',  beginTime => '20050123.035601'}, # 	2005-01-23	03:56:01	2005-01-23	06:27:09
'0105'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6023006',	 last => '6023009',	 list => '',  beginTime => '20050123.062709'}, # 	2005-01-23	06:27:09	2005-01-23	08:04:49
'0106'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6023011',	 last => '6023014',	 list => '',  beginTime => '20050123.080449'}, # 	2005-01-23	08:04:49	2005-01-23	08:43:35
'0107'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6023016',	 last => '6023018',	 list => '',  beginTime => '20050123.084335'}, # 	2005-01-23	08:43:35	2005-01-23	09:46:01
'0108'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6023020',	 last => '6023021',	 list => '',  beginTime => '20050123.094601'}, # 	2005-01-23	09:46:01	2005-01-23	10:16:35
'0109'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6023023',	 last => '6023026',	 list => '',  beginTime => '20050123.101635'}, # 	2005-01-23	10:16:35	2005-01-23	11:05:30
'0110'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6023028',	 last => '6023028',	 list => '',  beginTime => '20050123.110530'}, # 	2005-01-23	11:05:30	2005-01-25	05:32:23
'0111'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025005',	 last => '6025005',	 list => '',  beginTime => '20050125.053223'}, # 	2005-01-25	05:32:23	2005-01-25	06:12:16
'0112'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025010',	 last => '6025010',	 list => '',  beginTime => '20050125.061216'}, # 	2005-01-25	06:12:16	2005-01-25	06:35:38
'0113'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025013',	 last => '6025013',	 list => '',  beginTime => '20050125.063538'}, # 	2005-01-25	06:35:38	2005-01-25	06:53:51
'0114'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025015',	 last => '6025015',	 list => '',  beginTime => '20050125.065351'}, # 	2005-01-25	06:53:51	2005-01-25	07:09:21
'0115'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025017',	 last => '6025017',	 list => '',  beginTime => '20050125.070921'}, # 	2005-01-25	07:09:21	2005-01-25	07:25:55
'0116'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025019',	 last => '6025019',	 list => '',  beginTime => '20050125.072555'}, # 	2005-01-25	07:25:55	2005-01-25	07:36:33
'0117'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025021',	 last => '6025021',	 list => '',  beginTime => '20050125.073633'}, # 	2005-01-25	07:36:33	2005-01-25	07:49:15
'0118'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025024',	 last => '6025024',	 list => '',  beginTime => '20050125.074915'}, # 	2005-01-25	07:49:15	2005-01-25	08:00:39
'0119'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025026',	 last => '6025026',	 list => '',  beginTime => '20050125.080039'}, # 	2005-01-25	08:00:39	2005-01-25	08:17:00
'0120'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025029',	 last => '6025029',	 list => '',  beginTime => '20050125.081700'}, # 	2005-01-25	08:17:00	2005-01-25	08:26:54
'0121'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025031',	 last => '6025031',	 list => '',  beginTime => '20050125.082654'}, # 	2005-01-25	08:26:54	2005-01-25	08:38:19
'0122'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025033',	 last => '6025033',	 list => '',  beginTime => '20050125.083819'}, # 	2005-01-25	08:38:19	2005-01-25	08:45:15
'0123'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025035',	 last => '6025035',	 list => '',  beginTime => '20050125.084515'}, # 	2005-01-25	08:45:15	2005-01-25	08:54:51
'0124'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025037',	 last => '6025037',	 list => '',  beginTime => '20050125.085451'}, # 	2005-01-25	08:54:51	2005-01-25	09:18:11
'0125'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025041',	 last => '6025042',	 list => '',  beginTime => '20050125.091811'}, # 	2005-01-25	09:18:11	2005-01-25	11:29:45
'0126'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025047',	 last => '6025048',	 list => '',  beginTime => '20050125.112945'}, # 	2005-01-25	11:29:45	2005-01-25	12:43:05
'0127'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025052',	 last => '6025056',	 list => '',  beginTime => '20050125.124305'}, # 	2005-01-25	12:43:05	2005-01-25	23:52:05
'0128'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025109',	 last => '6025112',	 list => '',  beginTime => '20050125.235205'}, # 	2005-01-25	23:52:05	2005-01-26	00:46:36
'0129'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025115',	 last => '6025116',	 list => '',  beginTime => '20050126.004636'}, # 	2005-01-26	00:46:36	2005-01-26	01:17:43
'0130'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025118',	 last => '6025120',	 list => '',  beginTime => '20050126.011743'}, # 	2005-01-26	01:17:43	2005-01-26	02:06:59
'0131'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025123',	 last => '6025124',	 list => '',  beginTime => '20050126.020659'}, # 	2005-01-26	02:06:59	2005-01-26	03:30:59
'0132'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6025128',	 last => '6025128',	 list => '',  beginTime => '20050126.033059'}, # 	2005-01-26	03:30:59	2005-01-26	05:41:53
'0133'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026009',	 last => '6026009',	 list => '',  beginTime => '20050126.054153'}, # 	2005-01-26	05:41:53	2005-01-26	05:57:46
'0134'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026015',	 last => '6026015',	 list => '',  beginTime => '20050126.055746'}, # 	2005-01-26	05:57:46	2005-01-26	06:15:58
'0135'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026017',	 last => '6026017',	 list => '',  beginTime => '20050126.061558'}, # 	2005-01-26	06:15:58	2005-01-26	06:58:36
'0136'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026021',	 last => '6026022',	 list => '',  beginTime => '20050126.065836'}, # 	2005-01-26	06:58:36	2005-01-26	08:10:02
'0137'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026024',	 last => '6026026',	 list => '',  beginTime => '20050126.081002'}, # 	2005-01-26	08:10:02	2005-01-26	09:42:09
'0138'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026028',	 last => '6026030',	 list => '',  beginTime => '20050126.094209'}, # 	2005-01-26	09:42:09	2005-01-26	10:15:41
'0139'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026033',	 last => '6026033',	 list => '',  beginTime => '20050126.101541'}, # 	2005-01-26	10:15:41	2005-01-26	11:29:14
'0140'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026040',	 last => '6026040',	 list => '',  beginTime => '20050126.112914'}, # 	2005-01-26	11:29:14	2005-01-26	11:51:26
'0141'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026042',	 last => '6026042',	 list => '',  beginTime => '20050126.115126'}, # 	2005-01-26	11:51:26	2005-01-26	12:30:27
'0142'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026045',	 last => '6026046',	 list => '',  beginTime => '20050126.123027'}, # 	2005-01-26	12:30:27	2005-01-26	13:43:29
'0143'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026051',	 last => '6026055',	 list => '',  beginTime => '20050126.134329'}, # 	2005-01-26	13:43:29	2005-01-26	14:44:44
'0144'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026057',	 last => '6026058',	 list => '',  beginTime => '20050126.144444'}, # 	2005-01-26	14:44:44	2005-01-26	19:20:20
'0145'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026075',	 last => '6026078',	 list => '',  beginTime => '20050126.192020'}, # 	2005-01-26	19:20:20	2005-01-26	21:40:09
'0146'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026084',	 last => '6026085',	 list => '',  beginTime => '20050126.214009'}, # 	2005-01-26	21:40:09	2005-01-27	02:14:08
'0147'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026097',	 last => '6026098',	 list => '',  beginTime => '20050127.021408'}, # 	2005-01-27	02:14:08	2005-01-27	02:59:30
'0148'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026100',	 last => '6026101',	 list => '',  beginTime => '20050127.025930'}, # 	2005-01-27	02:59:30	2005-01-27	03:49:17
'0149'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026103',	 last => '6026107',	 list => '',  beginTime => '20050127.034917'}, # 	2005-01-27	03:49:17	2005-01-27	04:58:46
'0150'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6026112',	 last => '6026112',	 list => '',  beginTime => '20050127.045846'}, # 	2005-01-27	04:58:46	2005-01-27	05:58:08
'0151'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027001',	 last => '6027002',	 list => '',  beginTime => '20050127.055808'}, # 	2005-01-27	05:58:08	2005-01-27	09:34:51
'0152'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027008',	 last => '6027008',	 list => '',  beginTime => '20050127.093451'}, # 	2005-01-27	09:34:51	2005-01-27	09:43:00
'0153'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027010',	 last => '6027018',	 list => '',  beginTime => '20050127.094300'}, # 	2005-01-27	09:43:00	2005-01-27	23:53:30
'0154'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027058',	 last => '6027059',	 list => '',  beginTime => '20050127.235330'}, # 	2005-01-27	23:53:30	2005-01-28	00:20:26
'0155'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027062',	 last => '6027062',	 list => '',  beginTime => '20050128.002026'}, # 	2005-01-28	00:20:26	2005-01-28	00:41:54
'0156'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027064',	 last => '6027064',	 list => '',  beginTime => '20050128.004154'}, # 	2005-01-28	00:41:54	2005-01-28	01:01:12
'0157'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027066',	 last => '6027066',	 list => '',  beginTime => '20050128.010112'}, # 	2005-01-28	01:01:12	2005-01-28	01:31:45
'0158'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027070',	 last => '6027072',	 list => '',  beginTime => '20050128.013145'}, # 	2005-01-28	01:31:45	2005-01-28	02:10:04
'0159'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027077',	 last => '6027090',	 list => '',  beginTime => '20050128.021004'}, # 	2005-01-28	02:10:04	2005-01-28	03:18:22
'0160'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6027092',	 last => '6027095',	 list => '',  beginTime => '20050128.031822'}, # 	2005-01-28	03:18:22	2005-01-28	09:19:02
'0161'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6028003',	 last => '6028004',	 list => '',  beginTime => '20050128.091902'}, # 	2005-01-28	09:19:02	2005-01-28	10:37:00
'0162'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6028006',	 last => '6028011',	 list => '',  beginTime => '20050128.103700'}, # 	2005-01-28	10:37:00	2005-01-28	13:54:57
'0163'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6028013',	 last => '6028014',	 list => '',  beginTime => '20050128.135457'}, # 	2005-01-28	13:54:57	2005-01-28	22:34:19
'0164'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6028038',	 last => '6028038',	 list => '',  beginTime => '20050128.223419'}, # 	2005-01-28	22:34:19	2005-01-28	23:30:15
'0165'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6028051',	 last => '6028051',	 list => '',  beginTime => '20050128.233015'}, # 	2005-01-28	23:30:15	2005-01-29	00:55:07
'0166'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6028076',	 last => '6028076',	 list => '',  beginTime => '20050129.005507'}, # 	2005-01-29	00:55:07	2005-01-29	01:14:05
'0167'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6028078',	 last => '6028078',	 list => '',  beginTime => '20050129.011405'}, # 	2005-01-29	01:14:05	2005-01-29	01:45:29
'0168'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6028090',	 last => '6028097',	 list => '',  beginTime => '20050129.014529'}, # 	2005-01-29	01:45:29	2005-01-29	02:36:40	timestamp = cuProductionHighTower_RF
'0169'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6028099',	 last => '6028099',	 list => '',  beginTime => '20050129.023640'}, # 	2005-01-29	02:36:40	2005-01-29	05:36:40	timestamp = cuProductionMinBias_RF
'0170'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029004',	 last => '6029005',	 list => '',  beginTime => '20050129.053640'}, # 	2005-01-29	05:36:40	2005-01-29	06:59:00
'0171'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029007',	 last => '6029010',	 list => '',  beginTime => '20050129.065900'}, # 	2005-01-29	06:59:00	2005-01-29	11:16:34
'0172'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029016',	 last => '6029019',	 list => '',  beginTime => '20050129.111634'}, # 	2005-01-29	11:16:34	2005-01-29	12:54:33
'0173'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029021',	 last => '6029024',	 list => '',  beginTime => '20050129.125433'}, # 	2005-01-29	12:54:33	2005-01-29	15:24:11
'0174'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029027',	 last => '6029028',	 list => '',  beginTime => '20050129.152411'}, # 	2005-01-29	15:24:11	2005-01-30	02:23:52
'0175'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029047',	 last => '6029047',	 list => '',  beginTime => '20050130.022352'}, # 	2005-01-30	02:23:52	2005-01-30	02:50:10
'0176'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029052',	 last => '6029052',	 list => '',  beginTime => '20050130.025010'}, # 	2005-01-30	02:50:10	2005-01-30	03:06:14
'0177'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029056',	 last => '6029056',	 list => '',  beginTime => '20050130.030614'}, # 	2005-01-30	03:06:14	2005-01-30	03:24:33
'0178'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029058',	 last => '6029058',	 list => '',  beginTime => '20050130.032433'}, # 	2005-01-30	03:24:33	2005-01-30	04:15:02
'0179'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029066',	 last => '6029066',	 list => '',  beginTime => '20050130.041502'}, # 	2005-01-30	04:15:02	2005-01-30	04:42:50
'0180'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6029067',	 last => '6029067',	 list => '',  beginTime => '20050130.044250'}, # 	2005-01-30	04:42:50	2005-01-30	04:50:55	timestamp = cuProductionHighTower_RF
'0181'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6029068',	 last => '6029068',	 list => '',  beginTime => '20050130.045055'}, # 	2005-01-30	04:50:55	2005-01-30	05:41:03	timestamp = cuProductionMinBias_RF
'0182'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030001',	 last => '6030001',	 list => '',  beginTime => '20050130.054103'}, # 	2005-01-30	05:41:03	2005-01-30	06:56:12
'0183'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030006',	 last => '6030006',	 list => '',  beginTime => '20050130.065612'}, # 	2005-01-30	06:56:12	2005-01-30	07:20:13
'0184'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030010',	 last => '6030011',	 list => '',  beginTime => '20050130.072013'}, # 	2005-01-30	07:20:13	2005-01-30	07:41:32
'0185'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030013',	 last => '6030013',	 list => '',  beginTime => '20050130.074132'}, # 	2005-01-30	07:41:32	2005-01-30	08:24:40
'0186'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030015',	 last => '6030015',	 list => '',  beginTime => '20050130.082440'}, # 	2005-01-30	08:24:40	2005-01-30	09:13:47
'0187'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030017',	 last => '6030026',	 list => '',  beginTime => '20050130.091347'}, # 	2005-01-30	09:13:47	2005-01-30	11:31:22
'0188'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030028',	 last => '6030028',	 list => '',  beginTime => '20050130.113122'}, # 	2005-01-30	11:31:22	2005-01-30	13:59:36
'0189'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030032',	 last => '6030032',	 list => '',  beginTime => '20050130.135936'}, # 	2005-01-30	13:59:36	2005-01-30	14:17:16
'0190'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030037',	 last => '6030038',	 list => '',  beginTime => '20050130.141716'}, # 	2005-01-30	14:17:16	2005-01-30	14:35:44
'0191'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030040',	 last => '6030040',	 list => '',  beginTime => '20050130.143544'}, # 	2005-01-30	14:35:44	2005-01-30	14:43:14
'0192'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030042',	 last => '6030043',	 list => '',  beginTime => '20050130.144314'}, # 	2005-01-30	14:43:14	2005-01-30	17:43:53
'0193'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030051',	 last => '6030051',	 list => '',  beginTime => '20050130.174353'}, # 	2005-01-30	17:43:53	2005-01-30	17:49:12
'0194'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030053',	 last => '6030053',	 list => '',  beginTime => '20050130.174912'}, # 	2005-01-30	17:49:12	2005-01-30	18:07:53
'0195'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030059',	 last => '6030061',	 list => '',  beginTime => '20050130.180753'}, # 	2005-01-30	18:07:53	2005-01-30	20:10:14
'0196'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030074',	 last => '6030074',	 list => '',  beginTime => '20050130.201014'}, # 	2005-01-30	20:10:14	2005-01-30	20:12:37
'0197'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030076',	 last => '6030076',	 list => '',  beginTime => '20050130.201237'}, # 	2005-01-30	20:12:37	2005-01-30	20:39:10
'0198'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030079',	 last => '6030086',	 list => '',  beginTime => '20050130.203910'}, # 	2005-01-30	20:39:10	2005-01-31	00:07:12
'0199'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030090',	 last => '6030090',	 list => '',  beginTime => '20050131.000712'}, # 	2005-01-31	00:07:12	2005-01-31	00:20:09
'0200'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030093',	 last => '6030094',	 list => '',  beginTime => '20050131.002009'}, # 	2005-01-31	00:20:09	2005-01-31	01:18:39
'0201'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030096',	 last => '6030096',	 list => '',  beginTime => '20050131.011839'}, # 	2005-01-31	01:18:39	2005-01-31	03:39:59
'0202'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030114',	 last => '6030115',	 list => '',  beginTime => '20050131.033959'}, # 	2005-01-31	03:39:59	2005-01-31	04:07:28
'0203'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6030118',	 last => '6030118',	 list => '',  beginTime => '20050131.040728'}, # 	2005-01-31	04:07:28	2005-01-31	06:40:04
'0204'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6031005',	 last => '6031006',	 list => '',  beginTime => '20050131.064004'}, # 	2005-01-31	06:40:04	2005-01-31	08:23:43
'0205'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6031008',	 last => '6031011',	 list => '',  beginTime => '20050131.082343'}, # 	2005-01-31	08:23:43	2005-01-31	10:32:37
'0206'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6031013',	 last => '6031015',	 list => '',  beginTime => '20050131.103237'}, # 	2005-01-31	10:32:37	2005-01-31	12:47:20
'0207'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6031025',	 last => '6031025',	 list => '',  beginTime => '20050131.124720'}, # 	2005-01-31	12:47:20	2005-01-31	13:01:14
'0208'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6031031',	 last => '6031033',	 list => '',  beginTime => '20050131.130114'}, # 	2005-01-31	13:01:14	2005-01-31	14:47:25
'0209'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6031038',	 last => '6031040',	 list => '',  beginTime => '20050131.144725'}, # 	2005-01-31	14:47:25	2005-01-31	16:27:15
'0210'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6031053',	 last => '6031053',	 list => '',  beginTime => '20050131.162715'}, # 	2005-01-31	16:27:15	2005-01-31	21:57:46
'0211'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6031077',	 last => '6031077',	 list => '',  beginTime => '20050131.215746'}, # 	2005-01-31	21:57:46	2005-02-01	02:48:10	timestamp = cuProductionHighTower_RF
'0212'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6031103',	 last => '6031106',	 list => '',  beginTime => '20050201.024810'}, # 	2005-02-01	02:48:10	2005-02-01	04:10:16
'0213'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6031113',	 last => '6031113',	 list => '',  beginTime => '20050201.041016'}, # 	2005-02-01	04:10:16	2005-02-01	05:13:53
'0214'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6032001',	 last => '6032001',	 list => '',  beginTime => '20050201.051353'}, # 	2005-02-01	05:13:53	2005-02-01	05:34:00
'0215'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6032003',	 last => '6032005',	 list => '',  beginTime => '20050201.053400'}, # 	2005-02-01	05:34:00	2005-02-01	07:58:22
'0216'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6032011',	 last => '6032011',	 list => '',  beginTime => '20050201.075822'}, # 	2005-02-01	07:58:22	2005-02-03	10:22:26
'0217'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6034007',	 last => '6034009',	 list => '',  beginTime => '20050203.102226'}, # 	2005-02-03	10:22:26	2005-02-03	11:54:21
'0218'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6034014',	 last => '6034017',	 list => '',  beginTime => '20050203.115421'}, # 	2005-02-03	11:54:21	2005-02-04	00:08:32
'0219'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6034108',	 last => '6034108',	 list => '',  beginTime => '20050204.000832'}, # 	2005-02-04	00:08:32	2005-02-04	05:20:38
'0220'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035005',	 last => '6035007',	 list => '',  beginTime => '20050204.052038'}, # 	2005-02-04	05:20:38	2005-02-04	06:23:13
'0221'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035009',	 last => '6035016',	 list => '',  beginTime => '20050204.062313'}, # 	2005-02-04	06:23:13	2005-02-04	11:00:46
'0222'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035023',	 last => '6035023',	 list => '',  beginTime => '20050204.110046'}, # 	2005-02-04	11:00:46	2005-02-04	11:12:03
'0223'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035026',	 last => '6035028',	 list => '',  beginTime => '20050204.111203'}, # 	2005-02-04	11:12:03	2005-02-04	12:36:59
'0224'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035030',	 last => '6035030',	 list => '',  beginTime => '20050204.123659'}, # 	2005-02-04	12:36:59	2005-02-04	12:59:48
'0225'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035032',	 last => '6035032',	 list => '',  beginTime => '20050204.125948'}, # 	2005-02-04	12:59:48	2005-02-04	13:39:20
'0226'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035036',	 last => '6035036',	 list => '',  beginTime => '20050204.133920'}, # 	2005-02-04	13:39:20	2005-02-04	14:34:46
'0227'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035042',	 last => '6035042',	 list => '',  beginTime => '20050204.143446'}, # 	2005-02-04	14:34:46	2005-02-04	22:32:52
'0228'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035105',	 last => '6035105',	 list => '',  beginTime => '20050204.223252'}, # 	2005-02-04	22:32:52	2005-02-04	22:35:55
'0229'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6035106',	 last => '6035106',	 list => '',  beginTime => '20050204.223555'}, # 	2005-02-04	22:35:55	2005-02-04	22:41:43	timestamp = cuProductionMinBias_RF
'0230'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035108',	 last => '6035108',	 list => '',  beginTime => '20050204.224143'}, # 	2005-02-04	22:41:43	2005-02-04	23:51:44	timestamp = cuProductionHighTower_RF
'0231'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035111',	 last => '6035111',	 list => '',  beginTime => '20050204.235144'}, # 	2005-02-04	23:51:44	2005-02-05	02:48:00
'0232'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6035131',	 last => '6035131',	 list => '',  beginTime => '20050205.024800'}, # 	2005-02-05	02:48:00	2005-02-05	05:40:46
'0233'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036004',	 last => '6036004',	 list => '',  beginTime => '20050205.054046'}, # 	2005-02-05	05:40:46	2005-02-05	05:56:04
'0234'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036005',	 last => '6036006',	 list => '',  beginTime => '20050205.055604'}, # 	2005-02-05	05:56:04	2005-02-05	06:32:31	timestamp = cuProductionMinBias_RF
'0235'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036010',	 last => '6036010',	 list => '',  beginTime => '20050205.063231'}, # 	2005-02-05	06:32:31	2005-02-05	06:39:32
'0236'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036012',	 last => '6036013',	 list => '',  beginTime => '20050205.063932'}, # 	2005-02-05	06:39:32	2005-02-05	06:51:34
'0237'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036014',	 last => '6036014',	 list => '',  beginTime => '20050205.065134'}, # 	2005-02-05	06:51:34	2005-02-05	07:05:23	timestamp = cuProductionHighTower_RF
'0238'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036016',	 last => '6036017',	 list => '',  beginTime => '20050205.070523'}, # 	2005-02-05	07:05:23	2005-02-05	07:44:38
'0239'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036019',	 last => '6036021',	 list => '',  beginTime => '20050205.074438'}, # 	2005-02-05	07:44:38	2005-02-05	08:53:45
'0240'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036022',	 last => '6036022',	 list => '',  beginTime => '20050205.085345'}, # 	2005-02-05	08:53:45	2005-02-05	09:09:55	timestamp = cuProductionMinBias_RF
'0241'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036024',	 last => '6036025',	 list => '',  beginTime => '20050205.090955'}, # 	2005-02-05	09:09:55	2005-02-05	10:04:22
'0242'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036028',	 last => '6036028',	 list => '',  beginTime => '20050205.100422'}, # 	2005-02-05	10:04:22	2005-02-05	12:54:01
'0243'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036033',	 last => '6036033',	 list => '',  beginTime => '20050205.125401'}, # 	2005-02-05	12:54:01	2005-02-05	13:09:54	timestamp = cuProductionHighTower_RF
'0244'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036036',	 last => '6036036',	 list => '',  beginTime => '20050205.130954'}, # 	2005-02-05	13:09:54	2005-02-05	13:45:04
'0245'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036038',	 last => '6036038',	 list => '',  beginTime => '20050205.134504'}, # 	2005-02-05	13:45:04	2005-02-05	13:48:21	timestamp = cuProductionMinBias_RF
'0246'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036039',	 last => '6036039',	 list => '',  beginTime => '20050205.134821'}, # 	2005-02-05	13:48:21	2005-02-05	13:51:27	timestamp = cuProductionHighTower_RF
'0247'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036040',	 last => '6036040',	 list => '',  beginTime => '20050205.135127'}, # 	2005-02-05	13:51:27	2005-02-05	14:32:09	timestamp = cuProductionMinBias_RF
'0248'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036043',	 last => '6036045',	 list => '',  beginTime => '20050205.143209'}, # 	2005-02-05	14:32:09	2005-02-05	18:41:47	timestamp = cuProductionHighTower_RF
'0249'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036069',	 last => '6036069',	 list => '',  beginTime => '20050205.184147'}, # 	2005-02-05	18:41:47	2005-02-05	19:16:43
'0250'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036073',	 last => '6036074',	 list => '',  beginTime => '20050205.191643'}, # 	2005-02-05	19:16:43	2005-02-05	19:44:13
'0251'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036082',	 last => '6036083',	 list => '',  beginTime => '20050205.194413'}, # 	2005-02-05	19:44:13	2005-02-05	20:43:32
'0252'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036086',	 last => '6036086',	 list => '',  beginTime => '20050205.204332'}, # 	2005-02-05	20:43:32	2005-02-06	00:24:34	timestamp = cuProductionMinBias_RF
'0253'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6036096',	 last => '6036096',	 list => '',  beginTime => '20050206.002434'}, # 	2005-02-06	00:24:34	2005-02-06	00:37:12
'0254'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036098',	 last => '6036098',	 list => '',  beginTime => '20050206.003712'}, # 	2005-02-06	00:37:12	2005-02-06	02:12:11	timestamp = cuProductionHighTower_RF
'0255'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6036102',	 last => '6036105',	 list => '',  beginTime => '20050206.021211'}, # 	2005-02-06	02:12:11	2005-02-06	06:33:33
'0256'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6037006',	 last => '6037006',	 list => '',  beginTime => '20050206.063333'}, # 	2005-02-06	06:33:33	2005-02-06	06:49:33
'0257'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6037009',	 last => '6037010',	 list => '',  beginTime => '20050206.064933'}, # 	2005-02-06	06:49:33	2005-02-06	08:07:11
'0258'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6037013',	 last => '6037016',	 list => '',  beginTime => '20050206.080711'}, # 	2005-02-06	08:07:11	2005-02-06	09:54:28
'0259'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6037017',	 last => '6037019',	 list => '',  beginTime => '20050206.095428'}, # 	2005-02-06	09:54:28	2005-02-06	12:06:59	timestamp = cuProductionMinBias_RF
'0260'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6037022',	 last => '6037022',	 list => '',  beginTime => '20050206.120659'}, # 	2005-02-06	12:06:59	2005-02-06	12:18:51	timestamp = cuProductionHighTower_RF
'0261'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6037025',	 last => '6037026',	 list => '',  beginTime => '20050206.121851'}, # 	2005-02-06	12:18:51	2005-02-06	12:43:44
'0262'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6037028',	 last => '6037031',	 list => '',  beginTime => '20050206.124344'}, # 	2005-02-06	12:43:44	2005-02-06	14:21:17
'0263'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6037033',	 last => '6037033',	 list => '',  beginTime => '20050206.142117'}, # 	2005-02-06	14:21:17	2005-02-06	15:50:54
'0264'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6037039',	 last => '6037040',	 list => '',  beginTime => '20050206.155054'}, # 	2005-02-06	15:50:54	2005-02-06	18:12:35	timestamp = cuProductionMinBias_RF
'0265'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6037045',	 last => '6037048',	 list => '',  beginTime => '20050206.181235'}, # 	2005-02-06	18:12:35	2005-02-06	19:37:44	timestamp = cuProductionHighTower_RF
'0266'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6037049',	 last => '6037050',	 list => '',  beginTime => '20050206.193744'}, # 	2005-02-06	19:37:44	2005-02-06	20:36:49	timestamp = cuProductionMinBias_RF
'0267'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6037053',	 last => '6037054',	 list => '',  beginTime => '20050206.203649'}, # 	2005-02-06	20:36:49	2005-02-07	01:37:32
'0268'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6037061',	 last => '6037061',	 list => '',  beginTime => '20050207.013732'}, # 	2005-02-07	01:37:32	2005-02-07	05:30:38	timestamp = cuProductionHighTower_RF
'0269'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6038001',	 last => '6038001',	 list => '',  beginTime => '20050207.053038'}, # 	2005-02-07	05:30:38	2005-02-07	06:58:51	timestamp = cuProductionMinBias_RF
'0270'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6038006',	 last => '6038006',	 list => '',  beginTime => '20050207.065851'}, # 	2005-02-07	06:58:51	2005-02-07	07:08:27	timestamp = cuProductionHighTower_RF
'0271'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6038008',	 last => '6038009',	 list => '',  beginTime => '20050207.070827'}, # 	2005-02-07	07:08:27	2005-02-07	08:25:56
'0272'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6038011',	 last => '6038011',	 list => '',  beginTime => '20050207.082556'}, # 	2005-02-07	08:25:56	2005-02-07	08:54:00
'0273'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6038013',	 last => '6038013',	 list => '',  beginTime => '20050207.085400'}, # 	2005-02-07	08:54:00	2005-02-07	09:20:54
'0274'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6038015',	 last => '6038020',	 list => '',  beginTime => '20050207.092054'}, # 	2005-02-07	09:20:54	2005-02-08	03:09:55	timestamp = cuProductionMinBias_RF
'0275'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6038073',	 last => '6038073',	 list => '',  beginTime => '20050208.030955'}, # 	2005-02-08	03:09:55	2005-02-08	03:36:45	timestamp = cuProductionHighTower_RF
'0276'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6038085',	 last => '6038085',	 list => '',  beginTime => '20050208.033645'}, # 	2005-02-08	03:36:45	2005-02-08	04:19:26
'0277'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6038087',	 last => '6038088',	 list => '',  beginTime => '20050208.041926'}, # 	2005-02-08	04:19:26	2005-02-08	05:31:11
'0278'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6039004',	 last => '6039004',	 list => '',  beginTime => '20050208.053111'}, # 	2005-02-08	05:31:11	2005-02-08	05:41:08	timestamp = cuProductionMinBias_RF
'0279'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6039006',	 last => '6039006',	 list => '',  beginTime => '20050208.054108'}, # 	2005-02-08	05:41:08	2005-02-08	05:47:23
'0280'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6039009',	 last => '6039009',	 list => '',  beginTime => '20050208.054723'}, # 	2005-02-08	05:47:23	2005-02-08	05:59:28
'0281'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6039012',	 last => '6039012',	 list => '',  beginTime => '20050208.055928'}, # 	2005-02-08	05:59:28	2005-02-08	06:14:09
'0282'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6039014',	 last => '6039017',	 list => '',  beginTime => '20050208.061409'}, # 	2005-02-08	06:14:09	2005-02-08	09:35:28
'0283'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6039027',	 last => '6039029',	 list => '',  beginTime => '20050208.093528'}, # 	2005-02-08	09:35:28	2005-02-08	11:02:22	timestamp = cuProductionHighTower_RF
'0284'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6039031',	 last => '6039034',	 list => '',  beginTime => '20050208.110222'}, # 	2005-02-08	11:02:22	2005-02-08	12:24:48
'0285'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6039040',	 last => '6039040',	 list => '',  beginTime => '20050208.122448'}, # 	2005-02-08	12:24:48	2005-02-08	13:02:22
'0286'=> {trig=>'cuTestMinBias',         	field => 'RF',	first=> '6039042',	 last => '6039042',	 list => '',  beginTime => '20050208.130222'}, # 	2005-02-08	13:02:22	2005-02-08	13:16:04	timestamp = cuTestMinBias_RF
'0287'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6039045',	 last => '6039046',	 list => '',  beginTime => '20050208.131604'}, # 	2005-02-08	13:16:04	2005-02-08	22:15:03	timestamp = cuProductionMinBias_RF
'0288'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6039131',	 last => '6039132',	 list => '',  beginTime => '20050208.221503'}, # 	2005-02-08	22:15:03	2005-02-08	22:33:48	timestamp = cuProductionHighTower_RF
'0289'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6039134',	 last => '6039136',	 list => '',  beginTime => '20050208.223348'}, # 	2005-02-08	22:33:48	2005-02-08	23:22:06
'0290'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6039138',	 last => '6039139',	 list => '',  beginTime => '20050208.232206'}, # 	2005-02-08	23:22:06	2005-02-08	23:59:45	timestamp = cuProductionMinBias_RF
'0291'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6039141',	 last => '6039145',	 list => '',  beginTime => '20050208.235945'}, # 	2005-02-08	23:59:45	2005-02-09	04:51:06
'0292'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6039154',	 last => '6039154',	 list => '',  beginTime => '20050209.045106'}, # 	2005-02-09	04:51:06	2005-02-09	05:48:22	timestamp = cuProductionHighTower_RF
'0293'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6040001',	 last => '6040001',	 list => '',  beginTime => '20050209.054822'}, # 	2005-02-09	05:48:22	2005-02-09	06:37:03
'0294'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6040003',	 last => '6040003',	 list => '',  beginTime => '20050209.063703'}, # 	2005-02-09	06:37:03	2005-02-09	07:18:23
'0295'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6040004',	 last => '6040004',	 list => '',  beginTime => '20050209.071823'}, # 	2005-02-09	07:18:23	2005-02-09	07:48:21	timestamp = cuProductionMinBias_RF
'0296'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6040006',	 last => '6040009',	 list => '',  beginTime => '20050209.074821'}, # 	2005-02-09	07:48:21	2005-02-09	12:51:47
'0297'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6040019',	 last => '6040019',	 list => '',  beginTime => '20050209.125147'}, # 	2005-02-09	12:51:47	2005-02-09	13:31:12
'0298'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6040023',	 last => '6040023',	 list => '',  beginTime => '20050209.133112'}, # 	2005-02-09	13:31:12	2005-02-09	13:36:06	timestamp = cuProductionHighTower_RF
'0299'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6040026',	 last => '6040026',	 list => '',  beginTime => '20050209.133606'}, # 	2005-02-09	13:36:06	2005-02-09	23:49:55
'0300'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6040043',	 last => '6040045',	 list => '',  beginTime => '20050209.234955'}, # 	2005-02-09	23:49:55	2005-02-10	01:04:02
'0301'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6040048',	 last => '6040052',	 list => '',  beginTime => '20050210.010402'}, # 	2005-02-10	01:04:02	2005-02-10	02:40:00
'0302'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6040054',	 last => '6040054',	 list => '',  beginTime => '20050210.024000'}, # 	2005-02-10	02:40:00	2005-02-10	02:57:31
'0303'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6040055',	 last => '6040058',	 list => '',  beginTime => '20050210.025731'}, # 	2005-02-10	02:57:31	2005-02-10	06:34:28	timestamp = cuProductionMinBias_RF
'0304'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041014',	 last => '6041015',	 list => '',  beginTime => '20050210.063428'}, # 	2005-02-10	06:34:28	2005-02-10	07:43:05	timestamp = cuProductionHighTower_RF
'0305'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041020',	 last => '6041023',	 list => '',  beginTime => '20050210.074305'}, # 	2005-02-10	07:43:05	2005-02-10	09:04:14
'0306'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041025',	 last => '6041025',	 list => '',  beginTime => '20050210.090414'}, # 	2005-02-10	09:04:14	2005-02-10	09:19:01
'0307'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041027',	 last => '6041028',	 list => '',  beginTime => '20050210.091901'}, # 	2005-02-10	09:19:01	2005-02-10	09:51:21
'0308'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6041031',	 last => '6041031',	 list => '',  beginTime => '20050210.095121'}, # 	2005-02-10	09:51:21	2005-02-10	10:01:57	timestamp = cuProductionMinBias_RF
'0309'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6041034',	 last => '6041036',	 list => '',  beginTime => '20050210.100157'}, # 	2005-02-10	10:01:57	2005-02-10	15:04:34
'0310'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041062',	 last => '6041062',	 list => '',  beginTime => '20050210.150434'}, # 	2005-02-10	15:04:34	2005-02-10	15:32:51	timestamp = cuProductionHighTower_RF
'0311'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6041063',	 last => '6041066',	 list => '',  beginTime => '20050210.153251'}, # 	2005-02-10	15:32:51	2005-02-10	23:04:41	timestamp = cuProductionMinBias_RF
'0312'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041091',	 last => '6041093',	 list => '',  beginTime => '20050210.230441'}, # 	2005-02-10	23:04:41	2005-02-10	23:59:29	timestamp = cuProductionHighTower_RF
'0313'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041095',	 last => '6041095',	 list => '',  beginTime => '20050210.235929'}, # 	2005-02-10	23:59:29	2005-02-11	00:02:36
'0314'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041097',	 last => '6041097',	 list => '',  beginTime => '20050211.000236'}, # 	2005-02-11	00:02:36	2005-02-11	00:40:58
'0315'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041099',	 last => '6041099',	 list => '',  beginTime => '20050211.004058'}, # 	2005-02-11	00:40:58	2005-02-11	00:52:06
'0316'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041101',	 last => '6041102',	 list => '',  beginTime => '20050211.005206'}, # 	2005-02-11	00:52:06	2005-02-11	01:24:56
'0317'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6041103',	 last => '6041103',	 list => '',  beginTime => '20050211.012456'}, # 	2005-02-11	01:24:56	2005-02-11	01:55:57	timestamp = cuProductionMinBias_RF
'0318'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6041105',	 last => '6041105',	 list => '',  beginTime => '20050211.015557'}, # 	2005-02-11	01:55:57	2005-02-11	04:35:30
'0319'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041118',	 last => '6041118',	 list => '',  beginTime => '20050211.043530'}, # 	2005-02-11	04:35:30	2005-02-11	04:41:19	timestamp = cuProductionHighTower_RF
'0320'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6041120',	 last => '6041121',	 list => '',  beginTime => '20050211.044119'}, # 	2005-02-11	04:41:19	2005-02-11	05:25:48
'0321'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042003',	 last => '6042003',	 list => '',  beginTime => '20050211.052548'}, # 	2005-02-11	05:25:48	2005-02-11	05:37:18
'0322'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042006',	 last => '6042006',	 list => '',  beginTime => '20050211.053718'}, # 	2005-02-11	05:37:18	2005-02-11	05:54:49
'0323'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042008',	 last => '6042012',	 list => '',  beginTime => '20050211.055449'}, # 	2005-02-11	05:54:49	2005-02-11	07:22:55
'0324'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042014',	 last => '6042014',	 list => '',  beginTime => '20050211.072255'}, # 	2005-02-11	07:22:55	2005-02-11	07:26:57
'0325'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042015',	 last => '6042016',	 list => '',  beginTime => '20050211.072657'}, # 	2005-02-11	07:26:57	2005-02-11	07:58:09	timestamp = cuProductionMinBias_RF
'0326'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042018',	 last => '6042018',	 list => '',  beginTime => '20050211.075809'}, # 	2005-02-11	07:58:09	2005-02-11	08:33:35
'0327'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042024',	 last => '6042024',	 list => '',  beginTime => '20050211.083335'}, # 	2005-02-11	08:33:35	2005-02-11	09:55:17
'0328'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042038',	 last => '6042038',	 list => '',  beginTime => '20050211.095517'}, # 	2005-02-11	09:55:17	2005-02-11	09:59:34
'0329'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042040',	 last => '6042041',	 list => '',  beginTime => '20050211.095934'}, # 	2005-02-11	09:59:34	2005-02-11	10:07:51
'0330'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042043',	 last => '6042043',	 list => '',  beginTime => '20050211.100751'}, # 	2005-02-11	10:07:51	2005-02-11	10:21:22
'0331'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042045',	 last => '6042045',	 list => '',  beginTime => '20050211.102122'}, # 	2005-02-11	10:21:22	2005-02-11	10:23:21
'0332'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042046',	 last => '6042049',	 list => '',  beginTime => '20050211.102321'}, # 	2005-02-11	10:23:21	2005-02-11	11:07:24	timestamp = cuProductionHighTower_RF
'0333'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042051',	 last => '6042052',	 list => '',  beginTime => '20050211.110724'}, # 	2005-02-11	11:07:24	2005-02-11	11:32:17
'0334'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042054',	 last => '6042054',	 list => '',  beginTime => '20050211.113217'}, # 	2005-02-11	11:32:17	2005-02-11	12:41:52
'0335'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042057',	 last => '6042057',	 list => '',  beginTime => '20050211.124152'}, # 	2005-02-11	12:41:52	2005-02-11	13:00:06
'0336'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042059',	 last => '6042060',	 list => '',  beginTime => '20050211.130006'}, # 	2005-02-11	13:00:06	2005-02-11	23:31:43	timestamp = cuProductionMinBias_RF
'0337'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042095',	 last => '6042095',	 list => '',  beginTime => '20050211.233143'}, # 	2005-02-11	23:31:43	2005-02-11	23:46:02	timestamp = cuProductionHighTower_RF
'0338'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042099',	 last => '6042099',	 list => '',  beginTime => '20050211.234602'}, # 	2005-02-11	23:46:02	2005-02-12	00:03:54	timestamp = cuProductionMinBias_RF
'0339'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042101',	 last => '6042101',	 list => '',  beginTime => '20050212.000354'}, # 	2005-02-12	00:03:54	2005-02-12	00:05:13
'0340'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042102',	 last => '6042102',	 list => '',  beginTime => '20050212.000513'}, # 	2005-02-12	00:05:13	2005-02-12	00:27:05	timestamp = cuProductionHighTower_RF
'0341'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042105',	 last => '6042105',	 list => '',  beginTime => '20050212.002705'}, # 	2005-02-12	00:27:05	2005-02-12	01:20:34
'0342'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042107',	 last => '6042107',	 list => '',  beginTime => '20050212.012034'}, # 	2005-02-12	01:20:34	2005-02-12	01:22:16
'0343'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6042109',	 last => '6042110',	 list => '',  beginTime => '20050212.012216'}, # 	2005-02-12	01:22:16	2005-02-12	02:06:30
'0344'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6042111',	 last => '6042113',	 list => '',  beginTime => '20050212.020630'}, # 	2005-02-12	02:06:30	2005-02-12	05:28:24	timestamp = cuProductionMinBias_RF
'0345'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043010',	 last => '6043011',	 list => '',  beginTime => '20050212.052824'}, # 	2005-02-12	05:28:24	2005-02-12	07:10:34	timestamp = cuProductionHighTower_RF
'0346'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043014',	 last => '6043014',	 list => '',  beginTime => '20050212.071034'}, # 	2005-02-12	07:10:34	2005-02-12	07:24:04
'0347'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043016',	 last => '6043017',	 list => '',  beginTime => '20050212.072404'}, # 	2005-02-12	07:24:04	2005-02-12	07:35:58
'0348'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043019',	 last => '6043019',	 list => '',  beginTime => '20050212.073558'}, # 	2005-02-12	07:35:58	2005-02-12	08:17:12
'0349'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043020',	 last => '6043022',	 list => '',  beginTime => '20050212.081712'}, # 	2005-02-12	08:17:12	2005-02-12	09:19:10	timestamp = cuProductionMinBias_RF
'0350'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043026',	 last => '6043027',	 list => '',  beginTime => '20050212.091910'}, # 	2005-02-12	09:19:10	2005-02-12	12:38:52
'0351'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043039',	 last => '6043039',	 list => '',  beginTime => '20050212.123852'}, # 	2005-02-12	12:38:52	2005-02-12	12:57:34	timestamp = cuProductionHighTower_RF
'0352'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043042',	 last => '6043043',	 list => '',  beginTime => '20050212.125734'}, # 	2005-02-12	12:57:34	2005-02-12	13:11:09
'0353'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043045',	 last => '6043045',	 list => '',  beginTime => '20050212.131109'}, # 	2005-02-12	13:11:09	2005-02-12	13:31:16
'0354'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043048',	 last => '6043048',	 list => '',  beginTime => '20050212.133116'}, # 	2005-02-12	13:31:16	2005-02-12	13:49:51
'0355'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043050',	 last => '6043051',	 list => '',  beginTime => '20050212.134951'}, # 	2005-02-12	13:49:51	2005-02-12	14:21:48	timestamp = cuProductionMinBias_RF
'0356'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043054',	 last => '6043054',	 list => '',  beginTime => '20050212.142148'}, # 	2005-02-12	14:21:48	2005-02-12	14:32:49	timestamp = cuProductionHighTower_RF
'0357'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043057',	 last => '6043058',	 list => '',  beginTime => '20050212.143249'}, # 	2005-02-12	14:32:49	2005-02-12	15:41:58	timestamp = cuProductionMinBias_RF
'0358'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043060',	 last => '6043060',	 list => '',  beginTime => '20050212.154158'}, # 	2005-02-12	15:41:58	2005-02-12	16:18:17
'0359'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043063',	 last => '6043063',	 list => '',  beginTime => '20050212.161817'}, # 	2005-02-12	16:18:17	2005-02-12	19:53:59
'0360'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043080',	 last => '6043082',	 list => '',  beginTime => '20050212.195359'}, # 	2005-02-12	19:53:59	2005-02-12	20:49:10	timestamp = cuProductionHighTower_RF
'0361'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043085',	 last => '6043085',	 list => '',  beginTime => '20050212.204910'}, # 	2005-02-12	20:49:10	2005-02-12	21:39:29
'0362'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043090',	 last => '6043090',	 list => '',  beginTime => '20050212.213929'}, # 	2005-02-12	21:39:29	2005-02-12	22:01:34
'0363'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043094',	 last => '6043094',	 list => '',  beginTime => '20050212.220134'}, # 	2005-02-12	22:01:34	2005-02-12	22:43:25
'0364'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043095',	 last => '6043095',	 list => '',  beginTime => '20050212.224325'}, # 	2005-02-12	22:43:25	2005-02-12	22:52:05	timestamp = cuProductionMinBias_RF
'0365'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043097',	 last => '6043098',	 list => '',  beginTime => '20050212.225205'}, # 	2005-02-12	22:52:05	2005-02-12	23:22:04
'0366'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043100',	 last => '6043101',	 list => '',  beginTime => '20050212.232204'}, # 	2005-02-12	23:22:04	2005-02-13	01:35:34
'0367'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043111',	 last => '6043114',	 list => '',  beginTime => '20050213.013534'}, # 	2005-02-13	01:35:34	2005-02-13	02:31:39	timestamp = cuProductionHighTower_RF
'0368'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043115',	 last => '6043115',	 list => '',  beginTime => '20050213.023139'}, # 	2005-02-13	02:31:39	2005-02-13	02:52:21	timestamp = cuProductionMinBias_RF
'0369'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6043117',	 last => '6043120',	 list => '',  beginTime => '20050213.025221'}, # 	2005-02-13	02:52:21	2005-02-13	03:56:41	timestamp = cuProductionHighTower_RF
'0370'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6043121',	 last => '6043123',	 list => '',  beginTime => '20050213.035641'}, # 	2005-02-13	03:56:41	2005-02-13	05:32:35	timestamp = cuProductionMinBias_RF
'0371'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6044001',	 last => '6044001',	 list => '',  beginTime => '20050213.053235'}, # 	2005-02-13	05:32:35	2005-02-13	08:00:47
'0372'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044010',	 last => '6044012',	 list => '',  beginTime => '20050213.080047'}, # 	2005-02-13	08:00:47	2005-02-13	08:38:56	timestamp = cuProductionHighTower_RF
'0373'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044015',	 last => '6044016',	 list => '',  beginTime => '20050213.083856'}, # 	2005-02-13	08:38:56	2005-02-13	08:55:59
'0374'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044020',	 last => '6044020',	 list => '',  beginTime => '20050213.085559'}, # 	2005-02-13	08:55:59	2005-02-13	09:47:16
'0375'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044024',	 last => '6044028',	 list => '',  beginTime => '20050213.094716'}, # 	2005-02-13	09:47:16	2005-02-13	17:14:39
'0376'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044044',	 last => '6044047',	 list => '',  beginTime => '20050213.171439'}, # 	2005-02-13	17:14:39	2005-02-13	18:12:01
'0377'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044049',	 last => '6044050',	 list => '',  beginTime => '20050213.181201'}, # 	2005-02-13	18:12:01	2005-02-13	19:06:53
'0378'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044053',	 last => '6044053',	 list => '',  beginTime => '20050213.190653'}, # 	2005-02-13	19:06:53	2005-02-13	19:25:19
'0379'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6044054',	 last => '6044055',	 list => '',  beginTime => '20050213.192519'}, # 	2005-02-13	19:25:19	2005-02-13	20:15:43	timestamp = cuProductionMinBias_RF
'0380'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6044058',	 last => '6044059',	 list => '',  beginTime => '20050213.201543'}, # 	2005-02-13	20:15:43	2005-02-13	22:35:10
'0381'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044061',	 last => '6044061',	 list => '',  beginTime => '20050213.223510'}, # 	2005-02-13	22:35:10	2005-02-13	23:37:16	timestamp = cuProductionHighTower_RF
'0382'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6044071',	 last => '6044071',	 list => '',  beginTime => '20050213.233716'}, # 	2005-02-13	23:37:16	2005-02-13	23:54:43	timestamp = cuProductionMinBias_RF
'0383'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044075',	 last => '6044075',	 list => '',  beginTime => '20050213.235443'}, # 	2005-02-13	23:54:43	2005-02-14	00:02:49	timestamp = cuProductionHighTower_RF
'0384'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044079',	 last => '6044079',	 list => '',  beginTime => '20050214.000249'}, # 	2005-02-14	00:02:49	2005-02-14	00:22:30
'0385'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044081',	 last => '6044081',	 list => '',  beginTime => '20050214.002230'}, # 	2005-02-14	00:22:30	2005-02-14	01:08:39
'0386'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6044083',	 last => '6044086',	 list => '',  beginTime => '20050214.010839'}, # 	2005-02-14	01:08:39	2005-02-14	03:12:53
'0387'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6044088',	 last => '6044090',	 list => '',  beginTime => '20050214.031253'}, # 	2005-02-14	03:12:53	2005-02-14	06:05:44	timestamp = cuProductionMinBias_RF
'0388'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6045008',	 last => '6045008',	 list => '',  beginTime => '20050214.060544'}, # 	2005-02-14	06:05:44	2005-02-14	06:53:22	timestamp = cuProductionHighTower_RF
'0389'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6045026',	 last => '6045027',	 list => '',  beginTime => '20050214.065322'}, # 	2005-02-14	06:53:22	2005-02-14	07:48:56
'0390'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6045029',	 last => '6045029',	 list => '',  beginTime => '20050214.074856'}, # 	2005-02-14	07:48:56	2005-02-14	08:12:05
'0391'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6045033',	 last => '6045033',	 list => '',  beginTime => '20050214.081205'}, # 	2005-02-14	08:12:05	2005-02-14	11:41:23
'0392'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6045042',	 last => '6045042',	 list => '',  beginTime => '20050214.114123'}, # 	2005-02-14	11:41:23	2005-02-15	01:15:59
'0393'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6045058',	 last => '6045058',	 list => '',  beginTime => '20050215.011559'}, # 	2005-02-15	01:15:59	2005-02-15	01:49:39	timestamp = cuProductionMinBias_RF
'0394'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6045065',	 last => '6045065',	 list => '',  beginTime => '20050215.014939'}, # 	2005-02-15	01:49:39	2005-02-15	01:56:40
'0395'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6045067',	 last => '6045067',	 list => '',  beginTime => '20050215.015640'}, # 	2005-02-15	01:56:40	2005-02-15	02:09:47	timestamp = cuProductionHighTower_RF
'0396'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6045070',	 last => '6045070',	 list => '',  beginTime => '20050215.020947'}, # 	2005-02-15	02:09:47	2005-02-15	02:17:45
'0397'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6045072',	 last => '6045072',	 list => '',  beginTime => '20050215.021745'}, # 	2005-02-15	02:17:45	2005-02-15	02:50:18
'0398'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6045075',	 last => '6045075',	 list => '',  beginTime => '20050215.025018'}, # 	2005-02-15	02:50:18	2005-02-15	03:13:34
'0399'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6045076',	 last => '6045082',	 list => '',  beginTime => '20050215.031334'}, # 	2005-02-15	03:13:34	2005-02-15	05:15:10	timestamp = cuProductionMinBias_RF
'0400'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6046004',	 last => '6046005',	 list => '',  beginTime => '20050215.051510'}, # 	2005-02-15	05:15:10	2005-02-15	06:45:10
'0401'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6046014',	 last => '6046014',	 list => '',  beginTime => '20050215.064510'}, # 	2005-02-15	06:45:10	2005-02-15	06:59:53	timestamp = cuProductionHighTower_RF
'0402'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6046016',	 last => '6046018',	 list => '',  beginTime => '20050215.065953'}, # 	2005-02-15	06:59:53	2005-02-15	08:19:39
'0403'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6046022',	 last => '6046022',	 list => '',  beginTime => '20050215.081939'}, # 	2005-02-15	08:19:39	2005-02-15	09:27:09
'0404'=> {trig=>'cuProductionMinBias',   	field => 'RF',	first=> '6046025',	 last => '6046027',	 list => '',  beginTime => '20050215.092709'}, # 	2005-02-15	09:27:09	2005-02-15	10:30:56	timestamp = cuProductionMinBias_RF
'0405'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6046028',	 last => '6046028',	 list => '',  beginTime => '20050215.103056'}, # 	2005-02-15	10:30:56	2005-02-15	11:34:28	timestamp = cuProductionHighTower_RF
'0406'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6046035',	 last => '6046035',	 list => '',  beginTime => '20050215.113428'}, # 	2005-02-15	11:34:28	2005-02-15	12:47:40
'0407'=> {trig=>'cuProductionHighTower', 	field => 'RF',	first=> '6046038',	 last => '6046038',	 list => '',  beginTime => '20050215.124740'}, # 	2005-02-15	12:47:40	2005-02-16	07:24:31
'0408'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6047017',	 last => '6047017',	 list => '',  beginTime => '20050216.072431'}, # 	2005-02-16	07:24:31	2005-02-16	07:39:09	timestamp = cuProductionHighTower_FF
'0409'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6047020',	 last => '6047020',	 list => '',  beginTime => '20050216.073909'}, # 	2005-02-16	07:39:09	2005-02-16	07:51:57
'0410'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6047022',	 last => '6047022',	 list => '',  beginTime => '20050216.075157'}, # 	2005-02-16	07:51:57	2005-02-16	08:57:15
'0411'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6047025',	 last => '6047026',	 list => '',  beginTime => '20050216.085715'}, # 	2005-02-16	08:57:15	2005-02-16	10:39:01
'0412'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6047037',	 last => '6047037',	 list => '',  beginTime => '20050216.103901'}, # 	2005-02-16	10:39:01	2005-02-16	11:05:52
'0413'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6047039',	 last => '6047040',	 list => '',  beginTime => '20050216.110552'}, # 	2005-02-16	11:05:52	2005-02-16	12:15:14
'0414'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6047044',	 last => '6047044',	 list => '',  beginTime => '20050216.121514'}, # 	2005-02-16	12:15:14	2005-02-17	09:50:19
'0415'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6048012',	 last => '6048012',	 list => '',  beginTime => '20050217.095019'}, # 	2005-02-17	09:50:19	2005-02-17	10:00:37	timestamp = cuProductionMinBias_FF
'0416'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6048013',	 last => '6048014',	 list => '',  beginTime => '20050217.100037'}, # 	2005-02-17	10:00:37	2005-02-17	11:04:49	timestamp = cuProductionHighTower_FF
'0417'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6048016',	 last => '6048017',	 list => '',  beginTime => '20050217.110449'}, # 	2005-02-17	11:04:49	2005-02-17	11:55:11
'0418'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6048018',	 last => '6048025',	 list => '',  beginTime => '20050217.115511'}, # 	2005-02-17	11:55:11	2005-02-18	01:42:16	timestamp = cuProductionMinBias_FF
'0419'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6048062',	 last => '6048062',	 list => '',  beginTime => '20050218.014216'}, # 	2005-02-18	01:42:16	2005-02-18	01:58:37
'0420'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6048067',	 last => '6048067',	 list => '',  beginTime => '20050218.015837'}, # 	2005-02-18	01:58:37	2005-02-18	02:05:55
'0421'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6048069',	 last => '6048069',	 list => '',  beginTime => '20050218.020555'}, # 	2005-02-18	02:05:55	2005-02-18	02:49:26	timestamp = cuProductionHighTower_FF
'0422'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6048075',	 last => '6048076',	 list => '',  beginTime => '20050218.024926'}, # 	2005-02-18	02:49:26	2005-02-18	03:28:16
'0423'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6048079',	 last => '6048082',	 list => '',  beginTime => '20050218.032816'}, # 	2005-02-18	03:28:16	2005-02-18	08:34:01	timestamp = cuProductionMinBias_FF
'0424'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6049030',	 last => '6049034',	 list => '',  beginTime => '20050218.083401'}, # 	2005-02-18	08:34:01	2005-02-18	10:08:43
'0425'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6049036',	 last => '6049039',	 list => '',  beginTime => '20050218.100843'}, # 	2005-02-18	10:08:43	2005-02-18	14:21:18
'0426'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6049055',	 last => '6049055',	 list => '',  beginTime => '20050218.142118'}, # 	2005-02-18	14:21:18	2005-02-18	18:51:54	timestamp = cuProductionHighTower_FF
'0427'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6049091',	 last => '6049092',	 list => '',  beginTime => '20050218.185154'}, # 	2005-02-18	18:51:54	2005-02-19	01:15:11	timestamp = cuProductionMinBias_FF
'0428'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6049114',	 last => '6049114',	 list => '',  beginTime => '20050219.011511'}, # 	2005-02-19	01:15:11	2005-02-19	01:39:47	timestamp = cuProductionHighTower_FF
'0429'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6049116',	 last => '6049118',	 list => '',  beginTime => '20050219.013947'}, # 	2005-02-19	01:39:47	2005-02-19	03:19:48
'0430'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6049126',	 last => '6049126',	 list => '',  beginTime => '20050219.031948'}, # 	2005-02-19	03:19:48	2005-02-19	04:01:04	timestamp = cuProductionMinBias_FF
'0431'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6049129',	 last => '6049131',	 list => '',  beginTime => '20050219.040104'}, # 	2005-02-19	04:01:04	2005-02-19	06:04:10
'0432'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6050007',	 last => '6050008',	 list => '',  beginTime => '20050219.060410'}, # 	2005-02-19	06:04:10	2005-02-19	06:45:08	timestamp = cuProductionHighTower_FF
'0433'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6050010',	 last => '6050010',	 list => '',  beginTime => '20050219.064508'}, # 	2005-02-19	06:45:08	2005-02-19	06:56:55
'0434'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6050012',	 last => '6050013',	 list => '',  beginTime => '20050219.065655'}, # 	2005-02-19	06:56:55	2005-02-19	07:46:42
'0435'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6050015',	 last => '6050022',	 list => '',  beginTime => '20050219.074642'}, # 	2005-02-19	07:46:42	2005-02-19	12:35:15	timestamp = cuProductionMinBias_FF
'0436'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6050031',	 last => '6050033',	 list => '',  beginTime => '20050219.123515'}, # 	2005-02-19	12:35:15	2005-02-19	13:30:01	timestamp = cuProductionHighTower_FF
'0437'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6050034',	 last => '6050035',	 list => '',  beginTime => '20050219.133001'}, # 	2005-02-19	13:30:01	2005-02-19	14:22:16	timestamp = cuProductionMinBias_FF
'0438'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6050041',	 last => '6050044',	 list => '',  beginTime => '20050219.142216'}, # 	2005-02-19	14:22:16	2005-02-19	23:27:38
'0439'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6050112',	 last => '6050112',	 list => '',  beginTime => '20050219.232738'}, # 	2005-02-19	23:27:38	2005-02-19	23:49:18
'0440'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6050115',	 last => '6050116',	 list => '',  beginTime => '20050219.234918'}, # 	2005-02-19	23:49:18	2005-02-20	00:21:24
'0441'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6050119',	 last => '6050119',	 list => '',  beginTime => '20050220.002124'}, # 	2005-02-20	00:21:24	2005-02-20	03:21:35
'0442'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6050130',	 last => '6050131',	 list => '',  beginTime => '20050220.032135'}, # 	2005-02-20	03:21:35	2005-02-20	04:59:44	timestamp = cuProductionHighTower_FF
'0443'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6050135',	 last => '6050135',	 list => '',  beginTime => '20050220.045944'}, # 	2005-02-20	04:59:44	2005-02-20	05:29:26
'0444'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051002',	 last => '6051002',	 list => '',  beginTime => '20050220.052926'}, # 	2005-02-20	05:29:26	2005-02-20	06:04:31	timestamp = cuProductionMinBias_FF
'0445'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051004',	 last => '6051004',	 list => '',  beginTime => '20050220.060431'}, # 	2005-02-20	06:04:31	2005-02-20	06:34:02
'0446'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051006',	 last => '6051006',	 list => '',  beginTime => '20050220.063402'}, # 	2005-02-20	06:34:02	2005-02-20	06:58:33
'0447'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051008',	 last => '6051008',	 list => '',  beginTime => '20050220.065833'}, # 	2005-02-20	06:58:33	2005-02-20	09:13:58
'0448'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051015',	 last => '6051015',	 list => '',  beginTime => '20050220.091358'}, # 	2005-02-20	09:13:58	2005-02-20	09:37:31	timestamp = cuProductionHighTower_FF
'0449'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051018',	 last => '6051018',	 list => '',  beginTime => '20050220.093731'}, # 	2005-02-20	09:37:31	2005-02-20	10:29:21
'0450'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051021',	 last => '6051021',	 list => '',  beginTime => '20050220.102921'}, # 	2005-02-20	10:29:21	2005-02-20	11:11:54
'0451'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051023',	 last => '6051023',	 list => '',  beginTime => '20050220.111154'}, # 	2005-02-20	11:11:54	2005-02-20	11:55:53
'0452'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051025',	 last => '6051025',	 list => '',  beginTime => '20050220.115553'}, # 	2005-02-20	11:55:53	2005-02-20	12:42:02
'0453'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051027',	 last => '6051027',	 list => '',  beginTime => '20050220.124202'}, # 	2005-02-20	12:42:02	2005-02-20	13:14:42
'0454'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051029',	 last => '6051029',	 list => '',  beginTime => '20050220.131442'}, # 	2005-02-20	13:14:42	2005-02-20	13:43:07	timestamp = cuProductionMinBias_FF
'0455'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051031',	 last => '6051031',	 list => '',  beginTime => '20050220.134307'}, # 	2005-02-20	13:43:07	2005-02-20	14:09:03
'0456'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051034',	 last => '6051034',	 list => '',  beginTime => '20050220.140903'}, # 	2005-02-20	14:09:03	2005-02-20	17:25:43
'0457'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051047',	 last => '6051047',	 list => '',  beginTime => '20050220.172543'}, # 	2005-02-20	17:25:43	2005-02-20	18:06:25	timestamp = cuProductionHighTower_FF
'0458'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051049',	 last => '6051049',	 list => '',  beginTime => '20050220.180625'}, # 	2005-02-20	18:06:25	2005-02-20	19:12:05
'0459'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051053',	 last => '6051053',	 list => '',  beginTime => '20050220.191205'}, # 	2005-02-20	19:12:05	2005-02-20	19:37:44
'0460'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051055',	 last => '6051055',	 list => '',  beginTime => '20050220.193744'}, # 	2005-02-20	19:37:44	2005-02-20	20:09:51	timestamp = cuProductionMinBias_FF
'0461'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051058',	 last => '6051058',	 list => '',  beginTime => '20050220.200951'}, # 	2005-02-20	20:09:51	2005-02-20	20:35:48
'0462'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051065',	 last => '6051065',	 list => '',  beginTime => '20050220.203548'}, # 	2005-02-20	20:35:48	2005-02-20	21:00:24
'0463'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051067',	 last => '6051067',	 list => '',  beginTime => '20050220.210024'}, # 	2005-02-20	21:00:24	2005-02-20	21:34:16
'0464'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051073',	 last => '6051074',	 list => '',  beginTime => '20050220.213416'}, # 	2005-02-20	21:34:16	2005-02-21	02:55:29
'0465'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051093',	 last => '6051093',	 list => '',  beginTime => '20050221.025529'}, # 	2005-02-21	02:55:29	2005-02-21	03:17:02	timestamp = cuProductionHighTower_FF
'0466'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051094',	 last => '6051094',	 list => '',  beginTime => '20050221.031702'}, # 	2005-02-21	03:17:02	2005-02-21	03:45:23	timestamp = cuProductionMinBias_FF
'0467'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6051099',	 last => '6051099',	 list => '',  beginTime => '20050221.034523'}, # 	2005-02-21	03:45:23	2005-02-21	03:52:58
'0468'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6051101',	 last => '6051101',	 list => '',  beginTime => '20050221.035258'}, # 	2005-02-21	03:52:58	2005-02-21	04:54:50	timestamp = cuProductionHighTower_FF
'0469'=> {trig=>'cuProductionHighTower', 	field => 'ZF',	first=> '6051111',	 last => '6051111',	 list => '',  beginTime => '20050221.045450'}, # 	2005-02-21	04:54:50	2005-02-21	05:42:06	timestamp = cuProductionHighTower_ZF
'0470'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052004',	 last => '6052004',	 list => '',  beginTime => '20050221.054206'}, # 	2005-02-21	05:42:06	2005-02-21	06:03:38	timestamp = cuProductionHighTower_FF
'0471'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052008',	 last => '6052008',	 list => '',  beginTime => '20050221.060338'}, # 	2005-02-21	06:03:38	2005-02-21	06:13:15
'0472'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052010',	 last => '6052010',	 list => '',  beginTime => '20050221.061315'}, # 	2005-02-21	06:13:15	2005-02-21	06:27:06
'0473'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052014',	 last => '6052014',	 list => '',  beginTime => '20050221.062706'}, # 	2005-02-21	06:27:06	2005-02-21	06:42:59
'0474'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052016',	 last => '6052016',	 list => '',  beginTime => '20050221.064259'}, # 	2005-02-21	06:42:59	2005-02-21	09:10:17
'0475'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052025',	 last => '6052025',	 list => '',  beginTime => '20050221.091017'}, # 	2005-02-21	09:10:17	2005-02-21	09:33:48
'0476'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052027',	 last => '6052027',	 list => '',  beginTime => '20050221.093348'}, # 	2005-02-21	09:33:48	2005-02-21	10:29:26
'0477'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052031',	 last => '6052031',	 list => '',  beginTime => '20050221.102926'}, # 	2005-02-21	10:29:26	2005-02-21	11:13:17
'0478'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052033',	 last => '6052033',	 list => '',  beginTime => '20050221.111317'}, # 	2005-02-21	11:13:17	2005-02-21	11:35:46	timestamp = cuProductionMinBias_FF
'0479'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052035',	 last => '6052035',	 list => '',  beginTime => '20050221.113546'}, # 	2005-02-21	11:35:46	2005-02-21	12:26:10
'0480'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052040',	 last => '6052040',	 list => '',  beginTime => '20050221.122610'}, # 	2005-02-21	12:26:10	2005-02-21	12:50:47
'0481'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052042',	 last => '6052042',	 list => '',  beginTime => '20050221.125047'}, # 	2005-02-21	12:50:47	2005-02-21	14:39:39
'0482'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052054',	 last => '6052054',	 list => '',  beginTime => '20050221.143939'}, # 	2005-02-21	14:39:39	2005-02-21	15:23:20	timestamp = cuProductionHighTower_FF
'0483'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052056',	 last => '6052056',	 list => '',  beginTime => '20050221.152320'}, # 	2005-02-21	15:23:20	2005-02-21	15:54:33
'0484'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052058',	 last => '6052058',	 list => '',  beginTime => '20050221.155433'}, # 	2005-02-21	15:54:33	2005-02-21	16:35:34
'0485'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052062',	 last => '6052062',	 list => '',  beginTime => '20050221.163534'}, # 	2005-02-21	16:35:34	2005-02-21	17:00:47	timestamp = cuProductionMinBias_FF
'0486'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052064',	 last => '6052064',	 list => '',  beginTime => '20050221.170047'}, # 	2005-02-21	17:00:47	2005-02-21	17:24:56
'0487'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052066',	 last => '6052066',	 list => '',  beginTime => '20050221.172456'}, # 	2005-02-21	17:24:56	2005-02-21	17:47:28
'0488'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052068',	 last => '6052068',	 list => '',  beginTime => '20050221.174728'}, # 	2005-02-21	17:47:28	2005-02-21	18:14:29
'0489'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052070',	 last => '6052070',	 list => '',  beginTime => '20050221.181429'}, # 	2005-02-21	18:14:29	2005-02-21	18:37:10
'0490'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052072',	 last => '6052072',	 list => '',  beginTime => '20050221.183710'}, # 	2005-02-21	18:37:10	2005-02-21	21:04:35
'0491'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052089',	 last => '6052089',	 list => '',  beginTime => '20050221.210435'}, # 	2005-02-21	21:04:35	2005-02-21	21:48:51	timestamp = cuProductionHighTower_FF
'0492'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052091',	 last => '6052091',	 list => '',  beginTime => '20050221.214851'}, # 	2005-02-21	21:48:51	2005-02-21	22:09:21
'0493'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052093',	 last => '6052093',	 list => '',  beginTime => '20050221.220921'}, # 	2005-02-21	22:09:21	2005-02-21	22:34:49
'0494'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052095',	 last => '6052095',	 list => '',  beginTime => '20050221.223449'}, # 	2005-02-21	22:34:49	2005-02-21	23:07:53
'0495'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052098',	 last => '6052098',	 list => '',  beginTime => '20050221.230753'}, # 	2005-02-21	23:07:53	2005-02-22	00:00:27
'0496'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052104',	 last => '6052104',	 list => '',  beginTime => '20050222.000027'}, # 	2005-02-22	00:00:27	2005-02-22	00:21:33
'0497'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6052106',	 last => '6052106',	 list => '',  beginTime => '20050222.002133'}, # 	2005-02-22	00:21:33	2005-02-22	00:41:09
'0498'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6052107',	 last => '6052108',	 list => '',  beginTime => '20050222.004109'}, # 	2005-02-22	00:41:09	2005-02-22	08:09:49	timestamp = cuProductionMinBias_FF
'0499'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6053011',	 last => '6053011',	 list => '',  beginTime => '20050222.080949'}, # 	2005-02-22	08:09:49	2005-02-22	10:55:27
'0500'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6053019',	 last => '6053019',	 list => '',  beginTime => '20050222.105527'}, # 	2005-02-22	10:55:27	2005-02-22	10:59:55	timestamp = cuProductionHighTower_FF
'0501'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6053021',	 last => '6053022',	 list => '',  beginTime => '20050222.105955'}, # 	2005-02-22	10:59:55	2005-02-22	11:54:59
'0502'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6053024',	 last => '6053025',	 list => '',  beginTime => '20050222.115459'}, # 	2005-02-22	11:54:59	2005-02-22	12:30:50
'0503'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6053028',	 last => '6053028',	 list => '',  beginTime => '20050222.123050'}, # 	2005-02-22	12:30:50	2005-02-22	13:16:00
'0504'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6053031',	 last => '6053031',	 list => '',  beginTime => '20050222.131600'}, # 	2005-02-22	13:16:00	2005-02-22	13:38:21
'0505'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6053033',	 last => '6053033',	 list => '',  beginTime => '20050222.133821'}, # 	2005-02-22	13:38:21	2005-02-22	14:21:43
'0506'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6053035',	 last => '6053035',	 list => '',  beginTime => '20050222.142143'}, # 	2005-02-22	14:21:43	2005-02-22	14:50:07	timestamp = cuProductionMinBias_FF
'0507'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6053037',	 last => '6053037',	 list => '',  beginTime => '20050222.145007'}, # 	2005-02-22	14:50:07	2005-02-22	15:03:50
'0508'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6053039',	 last => '6053039',	 list => '',  beginTime => '20050222.150350'}, # 	2005-02-22	15:03:50	2005-02-22	22:19:02
'0509'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6053081',	 last => '6053084',	 list => '',  beginTime => '20050222.221902'}, # 	2005-02-22	22:19:02	2005-02-22	23:49:06	timestamp = cuProductionHighTower_FF
'0510'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6053087',	 last => '6053087',	 list => '',  beginTime => '20050222.234906'}, # 	2005-02-22	23:49:06	2005-02-23	00:13:15	timestamp = cuProductionMinBias_FF
'0511'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6053089',	 last => '6053089',	 list => '',  beginTime => '20050223.001315'}, # 	2005-02-23	00:13:15	2005-02-23	00:33:23
'0512'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6053093',	 last => '6053095',	 list => '',  beginTime => '20050223.003323'}, # 	2005-02-23	00:33:23	2005-02-23	01:25:28
'0513'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6053097',	 last => '6053101',	 list => '',  beginTime => '20050223.012528'}, # 	2005-02-23	01:25:28	2005-02-23	04:32:18
'0514'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6053107',	 last => '6053108',	 list => '',  beginTime => '20050223.043218'}, # 	2005-02-23	04:32:18	2005-02-23	05:19:48	timestamp = cuProductionHighTower_FF
'0515'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6054002',	 last => '6054003',	 list => '',  beginTime => '20050223.051948'}, # 	2005-02-23	05:19:48	2005-02-23	06:21:51
'0516'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6054013',	 last => '6054018',	 list => '',  beginTime => '20050223.062151'}, # 	2005-02-23	06:21:51	2005-02-23	08:16:19
'0517'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6054019',	 last => '6054020',	 list => '',  beginTime => '20050223.081619'}, # 	2005-02-23	08:16:19	2005-02-23	10:11:18	timestamp = cuProductionMinBias_FF
'0518'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6054029',	 last => '6054031',	 list => '',  beginTime => '20050223.101118'}, # 	2005-02-23	10:11:18	2005-02-23	11:10:53	timestamp = cuProductionHighTower_FF
'0519'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6054034',	 last => '6054035',	 list => '',  beginTime => '20050223.111053'}, # 	2005-02-23	11:10:53	2005-02-23	11:42:14
'0520'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6054037',	 last => '6054037',	 list => '',  beginTime => '20050223.114214'}, # 	2005-02-23	11:42:14	2005-02-24	02:31:40
'0521'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6054068',	 last => '6054068',	 list => '',  beginTime => '20050224.023140'}, # 	2005-02-24	02:31:40	2005-02-24	02:54:29
'0522'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6054070',	 last => '6054073',	 list => '',  beginTime => '20050224.025429'}, # 	2005-02-24	02:54:29	2005-02-24	05:07:40
'0523'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6055001',	 last => '6055003',	 list => '',  beginTime => '20050224.050740'}, # 	2005-02-24	05:07:40	2005-02-24	07:46:23	timestamp = cuProductionMinBias_FF
'0524'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6055008',	 last => '6055009',	 list => '',  beginTime => '20050224.074623'}, # 	2005-02-24	07:46:23	2005-02-24	08:45:35	timestamp = cuProductionHighTower_FF
'0525'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6055011',	 last => '6055011',	 list => '',  beginTime => '20050224.084535'}, # 	2005-02-24	08:45:35	2005-02-24	09:04:24
'0526'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6055013',	 last => '6055013',	 list => '',  beginTime => '20050224.090424'}, # 	2005-02-24	09:04:24	2005-02-24	09:46:34
'0527'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6055015',	 last => '6055016',	 list => '',  beginTime => '20050224.094634'}, # 	2005-02-24	09:46:34	2005-02-24	10:47:26
'0528'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6055017',	 last => '6055022',	 list => '',  beginTime => '20050224.104726'}, # 	2005-02-24	10:47:26	2005-02-24	17:55:05	timestamp = cuProductionMinBias_FF
'0529'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6055035',	 last => '6055035',	 list => '',  beginTime => '20050224.175505'}, # 	2005-02-24	17:55:05	2005-02-24	18:15:46
'0530'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6055037',	 last => '6055037',	 list => '',  beginTime => '20050224.181546'}, # 	2005-02-24	18:15:46	2005-02-24	19:04:17
'0531'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6055040',	 last => '6055042',	 list => '',  beginTime => '20050224.190417'}, # 	2005-02-24	19:04:17	2005-02-25	00:27:10
'0532'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6055081',	 last => '6055081',	 list => '',  beginTime => '20050225.002710'}, # 	2005-02-25	00:27:10	2005-02-25	00:54:11	timestamp = cuProductionHighTower_FF
'0533'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6055084',	 last => '6055086',	 list => '',  beginTime => '20050225.005411'}, # 	2005-02-25	00:54:11	2005-02-25	02:41:21
'0534'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6055088',	 last => '6055090',	 list => '',  beginTime => '20050225.024121'}, # 	2005-02-25	02:41:21	2005-02-26	01:53:57	timestamp = cuProductionMinBias_FF
'0535'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6056061',	 last => '6056062',	 list => '',  beginTime => '20050226.015357'}, # 	2005-02-26	01:53:57	2005-02-26	03:06:49	timestamp = cuProductionHighTower_FF
'0536'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6056065',	 last => '6056066',	 list => '',  beginTime => '20050226.030649'}, # 	2005-02-26	03:06:49	2005-02-26	03:25:15	timestamp = cuProductionMinBias_FF
'0537'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6056068',	 last => '6056072',	 list => '',  beginTime => '20050226.032515'}, # 	2005-02-26	03:25:15	2005-02-26	11:02:00
'0538'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6057041',	 last => '6057043',	 list => '',  beginTime => '20050226.110200'}, # 	2005-02-26	11:02:00	2005-02-26	12:14:19
'0539'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6057046',	 last => '6057048',	 list => '',  beginTime => '20050226.121419'}, # 	2005-02-26	12:14:19	2005-02-26	21:39:53
'0540'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6057062',	 last => '6057065',	 list => '',  beginTime => '20050226.213953'}, # 	2005-02-26	21:39:53	2005-02-26	22:23:44
'0541'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6057068',	 last => '6057070',	 list => '',  beginTime => '20050226.222344'}, # 	2005-02-26	22:23:44	2005-02-27	01:32:20
'0542'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6057081',	 last => '6057081',	 list => '',  beginTime => '20050227.013220'}, # 	2005-02-27	01:32:20	2005-02-27	01:49:38
'0543'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6057085',	 last => '6057087',	 list => '',  beginTime => '20050227.014938'}, # 	2005-02-27	01:49:38	2005-02-27	03:22:06	timestamp = cuProductionHighTower_FF
'0544'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6057090',	 last => '6057090',	 list => '',  beginTime => '20050227.032206'}, # 	2005-02-27	03:22:06	2005-02-27	03:50:34	timestamp = cuProductionMinBias_FF
'0545'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6057092',	 last => '6057093',	 list => '',  beginTime => '20050227.035034'}, # 	2005-02-27	03:50:34	2005-02-27	05:13:11
'0546'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6058001',	 last => '6058002',	 list => '',  beginTime => '20050227.051311'}, # 	2005-02-27	05:13:11	2005-02-27	07:26:19
'0547'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058009',	 last => '6058009',	 list => '',  beginTime => '20050227.072619'}, # 	2005-02-27	07:26:19	2005-02-27	07:32:05	timestamp = cuProductionHighTower_FF
'0548'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058011',	 last => '6058011',	 list => '',  beginTime => '20050227.073205'}, # 	2005-02-27	07:32:05	2005-02-27	08:23:19
'0549'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058013',	 last => '6058014',	 list => '',  beginTime => '20050227.082319'}, # 	2005-02-27	08:23:19	2005-02-27	09:46:31
'0550'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058018',	 last => '6058018',	 list => '',  beginTime => '20050227.094631'}, # 	2005-02-27	09:46:31	2005-02-27	10:13:22
'0551'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6058020',	 last => '6058023',	 list => '',  beginTime => '20050227.101322'}, # 	2005-02-27	10:13:22	2005-02-27	13:47:18	timestamp = cuProductionMinBias_FF
'0552'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058031',	 last => '6058032',	 list => '',  beginTime => '20050227.134718'}, # 	2005-02-27	13:47:18	2005-02-27	15:24:10	timestamp = cuProductionHighTower_FF
'0553'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058035',	 last => '6058035',	 list => '',  beginTime => '20050227.152410'}, # 	2005-02-27	15:24:10	2005-02-27	16:10:22
'0554'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6058036',	 last => '6058041',	 list => '',  beginTime => '20050227.161022'}, # 	2005-02-27	16:10:22	2005-02-27	19:21:17	timestamp = cuProductionMinBias_FF
'0555'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058050',	 last => '6058052',	 list => '',  beginTime => '20050227.192117'}, # 	2005-02-27	19:21:17	2005-02-27	21:45:52	timestamp = cuProductionHighTower_FF
'0556'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058062',	 last => '6058063',	 list => '',  beginTime => '20050227.214552'}, # 	2005-02-27	21:45:52	2005-02-27	22:56:23
'0557'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6058064',	 last => '6058066',	 list => '',  beginTime => '20050227.225623'}, # 	2005-02-27	22:56:23	2005-02-28	01:47:31	timestamp = cuProductionMinBias_FF
'0558'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058071',	 last => '6058072',	 list => '',  beginTime => '20050228.014731'}, # 	2005-02-28	01:47:31	2005-02-28	02:23:30	timestamp = cuProductionHighTower_FF
'0559'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058075',	 last => '6058075',	 list => '',  beginTime => '20050228.022330'}, # 	2005-02-28	02:23:30	2005-02-28	02:50:56
'0560'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058080',	 last => '6058080',	 list => '',  beginTime => '20050228.025056'}, # 	2005-02-28	02:50:56	2005-02-28	03:24:50
'0561'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6058084',	 last => '6058088',	 list => '',  beginTime => '20050228.032450'}, # 	2005-02-28	03:24:50	2005-02-28	05:21:28
'0562'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6059001',	 last => '6059004',	 list => '',  beginTime => '20050228.052128'}, # 	2005-02-28	05:21:28	2005-02-28	09:50:57	timestamp = cuProductionMinBias_FF
'0563'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6059016',	 last => '6059016',	 list => '',  beginTime => '20050228.095057'}, # 	2005-02-28	09:50:57	2005-02-28	10:22:18
'0564'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6059019',	 last => '6059021',	 list => '',  beginTime => '20050228.102218'}, # 	2005-02-28	10:22:18	2005-03-01	01:16:13
'0565'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6059051',	 last => '6059051',	 list => '',  beginTime => '20050301.011613'}, # 	2005-03-01	01:16:13	2005-03-01	01:30:28
'0566'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6059053',	 last => '6059053',	 list => '',  beginTime => '20050301.013028'}, # 	2005-03-01	01:30:28	2005-03-01	01:37:33
'0567'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6059054',	 last => '6059054',	 list => '',  beginTime => '20050301.013733'}, # 	2005-03-01	01:37:33	2005-03-01	01:45:36	timestamp = cuProductionHighTower_FF
'0568'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6059056',	 last => '6059056',	 list => '',  beginTime => '20050301.014536'}, # 	2005-03-01	01:45:36	2005-03-01	02:39:12
'0569'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6059061',	 last => '6059061',	 list => '',  beginTime => '20050301.023912'}, # 	2005-03-01	02:39:12	2005-03-01	02:52:01
'0570'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6059064',	 last => '6059064',	 list => '',  beginTime => '20050301.025201'}, # 	2005-03-01	02:52:01	2005-03-01	03:07:06
'0571'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6059066',	 last => '6059066',	 list => '',  beginTime => '20050301.030706'}, # 	2005-03-01	03:07:06	2005-03-01	03:25:36
'0572'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6059068',	 last => '6059071',	 list => '',  beginTime => '20050301.032536'}, # 	2005-03-01	03:25:36	2005-03-01	04:55:29
'0573'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6059073',	 last => '6059073',	 list => '',  beginTime => '20050301.045529'}, # 	2005-03-01	04:55:29	2005-03-01	05:15:49	timestamp = cuProductionMinBias_FF
'0574'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6060001',	 last => '6060001',	 list => '',  beginTime => '20050301.051549'}, # 	2005-03-01	05:15:49	2005-03-01	08:52:14
'0575'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6060013',	 last => '6060014',	 list => '',  beginTime => '20050301.085214'}, # 	2005-03-01	08:52:14	2005-03-01	10:45:26	timestamp = cuProductionHighTower_FF
'0576'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6060018',	 last => '6060018',	 list => '',  beginTime => '20050301.104526'}, # 	2005-03-01	10:45:26	2005-03-01	11:03:39
'0577'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6060019',	 last => '6060021',	 list => '',  beginTime => '20050301.110339'}, # 	2005-03-01	11:03:39	2005-03-01	13:43:30	timestamp = cuProductionMinBias_FF
'0578'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6060029',	 last => '6060031',	 list => '',  beginTime => '20050301.134330'}, # 	2005-03-01	13:43:30	2005-03-01	15:23:00	timestamp = cuProductionHighTower_FF
'0579'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6060034',	 last => '6060035',	 list => '',  beginTime => '20050301.152300'}, # 	2005-03-01	15:23:00	2005-03-01	16:17:54
'0580'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6060036',	 last => '6060039',	 list => '',  beginTime => '20050301.161754'}, # 	2005-03-01	16:17:54	2005-03-01	19:19:34	timestamp = cuProductionMinBias_FF
'0581'=> {trig=>'cuProductionFPD',       	field => 'FF',	first=> '6060048',	 last => '6060048',	 list => '',  beginTime => '20050301.191934'}, # 	2005-03-01	19:19:34	2005-03-01	19:56:54	timestamp = cuProductionFPD_FF
'0582'=> {trig=>'cuProductionFPD',       	field => 'FF',	first=> '6060055',	 last => '6060057',	 list => '',  beginTime => '20050301.195654'}, # 	2005-03-01	19:56:54	2005-03-01	20:36:44
'0583'=> {trig=>'cuProductionFPD',       	field => 'FF',	first=> '6060059',	 last => '6060059',	 list => '',  beginTime => '20050301.203644'}, # 	2005-03-01	20:36:44	2005-03-01	20:55:46
'0584'=> {trig=>'cuProductionFPD',       	field => 'FF',	first=> '6060062',	 last => '6060066',	 list => '',  beginTime => '20050301.205546'}, # 	2005-03-01	20:55:46	2005-03-01	21:41:47
'0585'=> {trig=>'cuProductionFPD',       	field => 'FF',	first=> '6060073',	 last => '6060073',	 list => '',  beginTime => '20050301.214147'}, # 	2005-03-01	21:41:47	2005-03-01	22:16:58
'0586'=> {trig=>'cuProductionFPD',       	field => 'FF',	first=> '6060075',	 last => '6060078',	 list => '',  beginTime => '20050301.221658'}, # 	2005-03-01	22:16:58	2005-03-02	06:25:19
'0587'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6061022',	 last => '6061027',	 list => '',  beginTime => '20050302.062519'}, # 	2005-03-02	06:25:19	2005-03-02	07:56:44	timestamp = cuProductionHighTower_FF
'0588'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6061029',	 last => '6061031',	 list => '',  beginTime => '20050302.075644'}, # 	2005-03-02	07:56:44	2005-03-02	09:25:34
'0589'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6061033',	 last => '6061033',	 list => '',  beginTime => '20050302.092534'}, # 	2005-03-02	09:25:34	2005-03-02	10:52:29	timestamp = cuProductionMinBias_FF
'0590'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6061036',	 last => '6061036',	 list => '',  beginTime => '20050302.105229'}, # 	2005-03-02	10:52:29	2005-03-02	11:11:19	timestamp = cuProductionHighTower_FF
'0591'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6061040',	 last => '6061040',	 list => '',  beginTime => '20050302.111119'}, # 	2005-03-02	11:11:19	2005-03-02	11:24:05
'0592'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6061042',	 last => '6061042',	 list => '',  beginTime => '20050302.112405'}, # 	2005-03-02	11:24:05	2005-03-02	11:39:12
'0593'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6061044',	 last => '6061046',	 list => '',  beginTime => '20050302.113912'}, # 	2005-03-02	11:39:12	2005-03-04	18:14:10
'0594'=> {trig=>'cuProductionHighTower', 	field => 'ZF',	first=> '6063018',	 last => '6063018',	 list => '',  beginTime => '20050304.181410'}, # 	2005-03-04	18:14:10	2005-03-04	18:39:35	timestamp = cuProductionHighTower_ZF
'0595'=> {trig=>'cuProductionMinBias',   	field => 'ZF',	first=> '6063024',	 last => '6063025',	 list => '',  beginTime => '20050304.183935'}, # 	2005-03-04	18:39:35	2005-03-05	00:11:20	timestamp = cuProductionMinBias_ZF
'0596'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6063033',	 last => '6063043',	 list => '',  beginTime => '20050305.001120'}, # 	2005-03-05	00:11:20	2005-03-05	00:25:51	timestamp = cuProductionMinBias_FF
'0597'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6063045',	 last => '6063045',	 list => '',  beginTime => '20050305.002551'}, # 	2005-03-05	00:25:51	2005-03-05	01:11:14	timestamp = cuProductionHighTower_FF
'0598'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6063047',	 last => '6063047',	 list => '',  beginTime => '20050305.011114'}, # 	2005-03-05	01:11:14	2005-03-05	02:02:52
'0599'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6063052',	 last => '6063053',	 list => '',  beginTime => '20050305.020252'}, # 	2005-03-05	02:02:52	2005-03-05	03:59:28
'0600'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6063055',	 last => '6063055',	 list => '',  beginTime => '20050305.035928'}, # 	2005-03-05	03:59:28	2005-03-05	04:07:26	timestamp = cuProductionMinBias_FF
'0601'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6063058',	 last => '6063060',	 list => '',  beginTime => '20050305.040726'}, # 	2005-03-05	04:07:26	2005-03-05	05:06:06
'0602'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6064001',	 last => '6064006',	 list => '',  beginTime => '20050305.050606'}, # 	2005-03-05	05:06:06	2005-03-05	08:28:25
'0603'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6064020',	 last => '6064020',	 list => '',  beginTime => '20050305.082825'}, # 	2005-03-05	08:28:25	2005-03-05	10:01:20	timestamp = cuProductionHighTower_FF
'0604'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6064036',	 last => '6064037',	 list => '',  beginTime => '20050305.100120'}, # 	2005-03-05	10:01:20	2005-03-05	12:07:57
'0605'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6064039',	 last => '6064040',	 list => '',  beginTime => '20050305.120757'}, # 	2005-03-05	12:07:57	2005-03-05	14:06:42	timestamp = cuProductionMinBias_FF
'0606'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6064051',	 last => '6064051',	 list => '',  beginTime => '20050305.140642'}, # 	2005-03-05	14:06:42	2005-03-05	14:11:35
'0607'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6064052',	 last => '6064054',	 list => '',  beginTime => '20050305.141135'}, # 	2005-03-05	14:11:35	2005-03-05	15:19:59	timestamp = cuProductionHighTower_FF
'0608'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6064056',	 last => '6064056',	 list => '',  beginTime => '20050305.151959'}, # 	2005-03-05	15:19:59	2005-03-05	16:56:53
'0609'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6064066',	 last => '6064067',	 list => '',  beginTime => '20050305.165653'}, # 	2005-03-05	16:56:53	2005-03-05	17:32:57	timestamp = cuProductionMinBias_FF
'0610'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6064070',	 last => '6064074',	 list => '',  beginTime => '20050305.173257'}, # 	2005-03-05	17:32:57	2005-03-05	21:46:40
'0611'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6064082',	 last => '6064082',	 list => '',  beginTime => '20050305.214640'}, # 	2005-03-05	21:46:40	2005-03-05	22:37:33	timestamp = cuProductionHighTower_FF
'0612'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6064084',	 last => '6064085',	 list => '',  beginTime => '20050305.223733'}, # 	2005-03-05	22:37:33	2005-03-06	00:08:43
'0613'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6064086',	 last => '6064091',	 list => '',  beginTime => '20050306.000843'}, # 	2005-03-06	00:08:43	2005-03-06	02:44:58	timestamp = cuProductionMinBias_FF
'0614'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6064100',	 last => '6064100',	 list => '',  beginTime => '20050306.024458'}, # 	2005-03-06	02:44:58	2005-03-06	03:37:43	timestamp = cuProductionHighTower_FF
'0615'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6064102',	 last => '6064104',	 list => '',  beginTime => '20050306.033743'}, # 	2005-03-06	03:37:43	2005-03-06	05:35:49
'0616'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6065001',	 last => '6065001',	 list => '',  beginTime => '20050306.053549'}, # 	2005-03-06	05:35:49	2005-03-06	06:24:30
'0617'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6065002',	 last => '6065002',	 list => '',  beginTime => '20050306.062430'}, # 	2005-03-06	06:24:30	2005-03-06	06:45:10	timestamp = cuProductionMinBias_FF
'0618'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6065005',	 last => '6065005',	 list => '',  beginTime => '20050306.064510'}, # 	2005-03-06	06:45:10	2005-03-06	07:10:52
'0619'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6065007',	 last => '6065007',	 list => '',  beginTime => '20050306.071052'}, # 	2005-03-06	07:10:52	2005-03-06	13:29:06
'0620'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6065016',	 last => '6065018',	 list => '',  beginTime => '20050306.132906'}, # 	2005-03-06	13:29:06	2005-03-06	14:53:26	timestamp = cuProductionHighTower_FF
'0621'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6065021',	 last => '6065021',	 list => '',  beginTime => '20050306.145326'}, # 	2005-03-06	14:53:26	2005-03-06	16:11:02
'0622'=> {trig=>'cuProductionMinBias',   	field => 'FF',	first=> '6065022',	 last => '6065024',	 list => '',  beginTime => '20050306.161102'}, # 	2005-03-06	16:11:02	2005-03-06	20:01:24	timestamp = cuProductionMinBias_FF
'0623'=> {trig=>'cuProductionMinBias',   	field => 'ZF',	first=> '6065036',	 last => '6065039',	 list => '',  beginTime => '20050306.200124'}, # 	2005-03-06	20:01:24	2005-03-06	21:16:39	timestamp = cuProductionMinBias_ZF
'0624'=> {trig=>'cuProductionMinBias',   	field => 'ZF',	first=> '6065041',	 last => '6065043',	 list => '',  beginTime => '20050306.211639'}, # 	2005-03-06	21:16:39	2005-03-06	21:34:20
'0625'=> {trig=>'cuProductionMinBias',   	field => 'ZF',	first=> '6065045',	 last => '6065045',	 list => '',  beginTime => '20050306.213420'}, # 	2005-03-06	21:34:20	2005-03-06	23:35:29
'0626'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6065054',	 last => '6065056',	 list => '',  beginTime => '20050306.233529'}, # 	2005-03-06	23:35:29	2005-03-07	00:46:51	timestamp = cuProductionHighTower_FF
'0627'=> {trig=>'cuProductionHighTower', 	field => 'FF',	first=> '6065058',	 last => '6065058',	 list => '',  beginTime => '20050307.004651'}, # 	2005-03-07	00:46:51	2005-03-09	20:09:53
'0628'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6068018',	 last => '6068019',	 list => '',  beginTime => '20050309.200953'}, # 	2005-03-09	20:09:53	2005-03-09	20:24:38	timestamp = cu62productionMinBias_FF
'0629'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6068021',	 last => '6068025',	 list => '',  beginTime => '20050309.202438'}, # 	2005-03-09	20:24:38	2005-03-09	21:47:37
'0630'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6068029',	 last => '6068029',	 list => '',  beginTime => '20050309.214737'}, # 	2005-03-09	21:47:37	2005-03-09	22:18:54
'0631'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6068034',	 last => '6068034',	 list => '',  beginTime => '20050309.221854'}, # 	2005-03-09	22:18:54	2005-03-09	23:00:08
'0632'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6068036',	 last => '6068037',	 list => '',  beginTime => '20050309.230008'}, # 	2005-03-09	23:00:08	2005-03-10	03:03:14
'0633'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6068040',	 last => '6068040',	 list => '',  beginTime => '20050310.030314'}, # 	2005-03-10	03:03:14	2005-03-10	07:17:44
'0634'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069003',	 last => '6069003',	 list => '',  beginTime => '20050310.071744'}, # 	2005-03-10	07:17:44	2005-03-10	07:48:49
'0635'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069008',	 last => '6069008',	 list => '',  beginTime => '20050310.074849'}, # 	2005-03-10	07:48:49	2005-03-10	08:05:19
'0636'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069010',	 last => '6069010',	 list => '',  beginTime => '20050310.080519'}, # 	2005-03-10	08:05:19	2005-03-10	08:52:36
'0637'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069013',	 last => '6069013',	 list => '',  beginTime => '20050310.085236'}, # 	2005-03-10	08:52:36	2005-03-10	09:45:49
'0638'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069018',	 last => '6069020',	 list => '',  beginTime => '20050310.094549'}, # 	2005-03-10	09:45:49	2005-03-10	13:52:21
'0639'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069044',	 last => '6069045',	 list => '',  beginTime => '20050310.135221'}, # 	2005-03-10	13:52:21	2005-03-10	14:51:00
'0640'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069056',	 last => '6069056',	 list => '',  beginTime => '20050310.145100'}, # 	2005-03-10	14:51:00	2005-03-10	20:33:51
'0641'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069070',	 last => '6069071',	 list => '',  beginTime => '20050310.203351'}, # 	2005-03-10	20:33:51	2005-03-10	20:53:13
'0642'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069075',	 last => '6069076',	 list => '',  beginTime => '20050310.205313'}, # 	2005-03-10	20:53:13	2005-03-10	23:11:38
'0643'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069081',	 last => '6069081',	 list => '',  beginTime => '20050310.231138'}, # 	2005-03-10	23:11:38	2005-03-10	23:15:16
'0644'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069083',	 last => '6069083',	 list => '',  beginTime => '20050310.231516'}, # 	2005-03-10	23:15:16	2005-03-10	23:29:48
'0645'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069089',	 last => '6069089',	 list => '',  beginTime => '20050310.232948'}, # 	2005-03-10	23:29:48	2005-03-10	23:53:31
'0646'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069092',	 last => '6069092',	 list => '',  beginTime => '20050310.235331'}, # 	2005-03-10	23:53:31	2005-03-11	00:50:45
'0647'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069097',	 last => '6069100',	 list => '',  beginTime => '20050311.005045'}, # 	2005-03-11	00:50:45	2005-03-11	02:29:51
'0648'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069102',	 last => '6069103',	 list => '',  beginTime => '20050311.022951'}, # 	2005-03-11	02:29:51	2005-03-11	03:33:34
'0649'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6069105',	 last => '6069106',	 list => '',  beginTime => '20050311.033334'}, # 	2005-03-11	03:33:34	2005-03-11	07:26:53
'0650'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070006',	 last => '6070007',	 list => '',  beginTime => '20050311.072653'}, # 	2005-03-11	07:26:53	2005-03-11	08:45:49
'0651'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070009',	 last => '6070011',	 list => '',  beginTime => '20050311.084549'}, # 	2005-03-11	08:45:49	2005-03-11	10:45:42
'0652'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070018',	 last => '6070019',	 list => '',  beginTime => '20050311.104542'}, # 	2005-03-11	10:45:42	2005-03-11	13:21:46
'0653'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070046',	 last => '6070046',	 list => '',  beginTime => '20050311.132146'}, # 	2005-03-11	13:21:46	2005-03-11	13:44:41
'0654'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070048',	 last => '6070050',	 list => '',  beginTime => '20050311.134441'}, # 	2005-03-11	13:44:41	2005-03-11	14:25:46
'0655'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070052',	 last => '6070052',	 list => '',  beginTime => '20050311.142546'}, # 	2005-03-11	14:25:46	2005-03-11	15:06:54
'0656'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070057',	 last => '6070057',	 list => '',  beginTime => '20050311.150654'}, # 	2005-03-11	15:06:54	2005-03-11	16:09:40
'0657'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070062',	 last => '6070063',	 list => '',  beginTime => '20050311.160940'}, # 	2005-03-11	16:09:40	2005-03-11	23:56:34
'0658'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070077',	 last => '6070077',	 list => '',  beginTime => '20050311.235634'}, # 	2005-03-11	23:56:34	2005-03-12	00:18:18
'0659'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070079',	 last => '6070081',	 list => '',  beginTime => '20050312.001818'}, # 	2005-03-12	00:18:18	2005-03-12	01:03:55
'0660'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070083',	 last => '6070087',	 list => '',  beginTime => '20050312.010355'}, # 	2005-03-12	01:03:55	2005-03-12	02:19:06
'0661'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070091',	 last => '6070091',	 list => '',  beginTime => '20050312.021906'}, # 	2005-03-12	02:19:06	2005-03-12	02:47:27
'0662'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070093',	 last => '6070095',	 list => '',  beginTime => '20050312.024727'}, # 	2005-03-12	02:47:27	2005-03-12	04:08:21
'0663'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070098',	 last => '6070098',	 list => '',  beginTime => '20050312.040821'}, # 	2005-03-12	04:08:21	2005-03-12	04:14:09
'0664'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6070100',	 last => '6070100',	 list => '',  beginTime => '20050312.041409'}, # 	2005-03-12	04:14:09	2005-03-12	06:17:41
'0665'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071004',	 last => '6071004',	 list => '',  beginTime => '20050312.061741'}, # 	2005-03-12	06:17:41	2005-03-12	06:30:49
'0666'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071006',	 last => '6071006',	 list => '',  beginTime => '20050312.063049'}, # 	2005-03-12	06:30:49	2005-03-12	06:59:58
'0667'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071008',	 last => '6071008',	 list => '',  beginTime => '20050312.065958'}, # 	2005-03-12	06:59:58	2005-03-12	07:44:00
'0668'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071011',	 last => '6071011',	 list => '',  beginTime => '20050312.074400'}, # 	2005-03-12	07:44:00	2005-03-12	08:07:31
'0669'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071013',	 last => '6071013',	 list => '',  beginTime => '20050312.080731'}, # 	2005-03-12	08:07:31	2005-03-12	08:24:53
'0670'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071015',	 last => '6071015',	 list => '',  beginTime => '20050312.082453'}, # 	2005-03-12	08:24:53	2005-03-12	08:57:48
'0671'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071017',	 last => '6071018',	 list => '',  beginTime => '20050312.085748'}, # 	2005-03-12	08:57:48	2005-03-12	09:16:58
'0672'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071021',	 last => '6071021',	 list => '',  beginTime => '20050312.091658'}, # 	2005-03-12	09:16:58	2005-03-12	09:33:19
'0673'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071023',	 last => '6071025',	 list => '',  beginTime => '20050312.093319'}, # 	2005-03-12	09:33:19	2005-03-12	10:38:42
'0674'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071027',	 last => '6071027',	 list => '',  beginTime => '20050312.103842'}, # 	2005-03-12	10:38:42	2005-03-12	13:22:16
'0675'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071035',	 last => '6071035',	 list => '',  beginTime => '20050312.132216'}, # 	2005-03-12	13:22:16	2005-03-12	13:40:18
'0676'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071038',	 last => '6071040',	 list => '',  beginTime => '20050312.134018'}, # 	2005-03-12	13:40:18	2005-03-12	14:53:50
'0677'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071043',	 last => '6071046',	 list => '',  beginTime => '20050312.145350'}, # 	2005-03-12	14:53:50	2005-03-12	16:53:46
'0678'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071051',	 last => '6071053',	 list => '',  beginTime => '20050312.165346'}, # 	2005-03-12	16:53:46	2005-03-12	20:06:54
'0679'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071067',	 last => '6071069',	 list => '',  beginTime => '20050312.200654'}, # 	2005-03-12	20:06:54	2005-03-12	21:23:43
'0680'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071071',	 last => '6071083',	 list => '',  beginTime => '20050312.212343'}, # 	2005-03-12	21:23:43	2005-03-13	01:59:38
'0681'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071086',	 last => '6071086',	 list => '',  beginTime => '20050313.015938'}, # 	2005-03-13	01:59:38	2005-03-13	02:17:41
'0682'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071089',	 last => '6071089',	 list => '',  beginTime => '20050313.021741'}, # 	2005-03-13	02:17:41	2005-03-13	03:09:46
'0683'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6071091',	 last => '6071094',	 list => '',  beginTime => '20050313.030946'}, # 	2005-03-13	03:09:46	2005-03-13	05:11:56
'0684'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072001',	 last => '6072002',	 list => '',  beginTime => '20050313.051156'}, # 	2005-03-13	05:11:56	2005-03-13	06:11:31
'0685'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072004',	 last => '6072004',	 list => '',  beginTime => '20050313.061131'}, # 	2005-03-13	06:11:31	2005-03-13	08:58:37
'0686'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072012',	 last => '6072015',	 list => '',  beginTime => '20050313.085837'}, # 	2005-03-13	08:58:37	2005-03-13	10:23:42
'0687'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072017',	 last => '6072021',	 list => '',  beginTime => '20050313.102342'}, # 	2005-03-13	10:23:42	2005-03-13	16:17:35
'0688'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072033',	 last => '6072035',	 list => '',  beginTime => '20050313.161735'}, # 	2005-03-13	16:17:35	2005-03-13	17:35:38
'0689'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072037',	 last => '6072038',	 list => '',  beginTime => '20050313.173538'}, # 	2005-03-13	17:35:38	2005-03-13	18:06:54
'0690'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072040',	 last => '6072042',	 list => '',  beginTime => '20050313.180654'}, # 	2005-03-13	18:06:54	2005-03-13	19:07:59
'0691'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072044',	 last => '6072046',	 list => '',  beginTime => '20050313.190759'}, # 	2005-03-13	19:07:59	2005-03-13	20:12:26
'0692'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072048',	 last => '6072048',	 list => '',  beginTime => '20050313.201226'}, # 	2005-03-13	20:12:26	2005-03-13	20:36:19
'0693'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6072053',	 last => '6072053',	 list => '',  beginTime => '20050313.203619'}, # 	2005-03-13	20:36:19	2005-03-14	08:21:41
'0694'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073005',	 last => '6073006',	 list => '',  beginTime => '20050314.082141'}, # 	2005-03-14	08:21:41	2005-03-14	09:24:04
'0695'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073010',	 last => '6073010',	 list => '',  beginTime => '20050314.092404'}, # 	2005-03-14	09:24:04	2005-03-14	09:43:09
'0696'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073012',	 last => '6073013',	 list => '',  beginTime => '20050314.094309'}, # 	2005-03-14	09:43:09	2005-03-14	10:44:55
'0697'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073016',	 last => '6073018',	 list => '',  beginTime => '20050314.104455'}, # 	2005-03-14	10:44:55	2005-03-14	12:20:22
'0698'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073022',	 last => '6073023',	 list => '',  beginTime => '20050314.122022'}, # 	2005-03-14	12:20:22	2005-03-14	14:12:07
'0699'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073034',	 last => '6073034',	 list => '',  beginTime => '20050314.141207'}, # 	2005-03-14	14:12:07	2005-03-14	14:42:32
'0700'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073037',	 last => '6073037',	 list => '',  beginTime => '20050314.144232'}, # 	2005-03-14	14:42:32	2005-03-14	15:49:39
'0701'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073044',	 last => '6073047',	 list => '',  beginTime => '20050314.154939'}, # 	2005-03-14	15:49:39	2005-03-14	16:16:40
'0702'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073050',	 last => '6073050',	 list => '',  beginTime => '20050314.161640'}, # 	2005-03-14	16:16:40	2005-03-14	16:39:02
'0703'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073052',	 last => '6073053',	 list => '',  beginTime => '20050314.163902'}, # 	2005-03-14	16:39:02	2005-03-14	17:15:22
'0704'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073055',	 last => '6073058',	 list => '',  beginTime => '20050314.171522'}, # 	2005-03-14	17:15:22	2005-03-14	20:00:58
'0705'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073066',	 last => '6073067',	 list => '',  beginTime => '20050314.200058'}, # 	2005-03-14	20:00:58	2005-03-14	21:22:18
'0706'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073072',	 last => '6073075',	 list => '',  beginTime => '20050314.212218'}, # 	2005-03-14	21:22:18	2005-03-15	01:57:08
'0707'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073079',	 last => '6073079',	 list => '',  beginTime => '20050315.015708'}, # 	2005-03-15	01:57:08	2005-03-15	02:06:10
'0708'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073081',	 last => '6073081',	 list => '',  beginTime => '20050315.020610'}, # 	2005-03-15	02:06:10	2005-03-15	04:08:50
'0709'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073085',	 last => '6073085',	 list => '',  beginTime => '20050315.040850'}, # 	2005-03-15	04:08:50	2005-03-15	04:19:17
'0710'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073087',	 last => '6073087',	 list => '',  beginTime => '20050315.041917'}, # 	2005-03-15	04:19:17	2005-03-15	04:54:34
'0711'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6073089',	 last => '6073089',	 list => '',  beginTime => '20050315.045434'}, # 	2005-03-15	04:54:34	2005-03-15	05:29:33
'0712'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6074002',	 last => '6074008',	 list => '',  beginTime => '20050315.052933'}, # 	2005-03-15	05:29:33	2005-03-15	11:46:55
'0713'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6074016',	 last => '6074017',	 list => '',  beginTime => '20050315.114655'}, # 	2005-03-15	11:46:55	2005-03-15	12:41:37
'0714'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6074020',	 last => '6074020',	 list => '',  beginTime => '20050315.124137'}, # 	2005-03-15	12:41:37	2005-03-15	13:21:48
'0715'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6074023',	 last => '6074025',	 list => '',  beginTime => '20050315.132148'}, # 	2005-03-15	13:21:48	2005-03-16	05:42:09
'0716'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075009',	 last => '6075010',	 list => '',  beginTime => '20050316.054209'}, # 	2005-03-16	05:42:09	2005-03-16	06:22:38
'0717'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075012',	 last => '6075013',	 list => '',  beginTime => '20050316.062238'}, # 	2005-03-16	06:22:38	2005-03-16	06:55:35
'0718'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075016',	 last => '6075016',	 list => '',  beginTime => '20050316.065535'}, # 	2005-03-16	06:55:35	2005-03-16	07:04:57
'0719'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075018',	 last => '6075020',	 list => '',  beginTime => '20050316.070457'}, # 	2005-03-16	07:04:57	2005-03-16	09:07:33
'0720'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075022',	 last => '6075022',	 list => '',  beginTime => '20050316.090733'}, # 	2005-03-16	09:07:33	2005-03-16	09:17:59
'0721'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075024',	 last => '6075026',	 list => '',  beginTime => '20050316.091759'}, # 	2005-03-16	09:17:59	2005-03-16	11:47:22
'0722'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075036',	 last => '6075036',	 list => '',  beginTime => '20050316.114722'}, # 	2005-03-16	11:47:22	2005-03-16	12:26:42
'0723'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075038',	 last => '6075038',	 list => '',  beginTime => '20050316.122642'}, # 	2005-03-16	12:26:42	2005-03-16	12:54:25
'0724'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075040',	 last => '6075043',	 list => '',  beginTime => '20050316.125425'}, # 	2005-03-16	12:54:25	2005-03-16	14:24:59
'0725'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075048',	 last => '6075049',	 list => '',  beginTime => '20050316.142459'}, # 	2005-03-16	14:24:59	2005-03-16	21:14:10
'0726'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075091',	 last => '6075091',	 list => '',  beginTime => '20050316.211410'}, # 	2005-03-16	21:14:10	2005-03-16	22:15:52
'0727'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075102',	 last => '6075102',	 list => '',  beginTime => '20050316.221552'}, # 	2005-03-16	22:15:52	2005-03-16	22:23:00
'0728'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075104',	 last => '6075106',	 list => '',  beginTime => '20050316.222300'}, # 	2005-03-16	22:23:00	2005-03-17	00:08:40
'0729'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075125',	 last => '6075125',	 list => '',  beginTime => '20050317.000840'}, # 	2005-03-17	00:08:40	2005-03-17	00:13:27
'0730'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075127',	 last => '6075128',	 list => '',  beginTime => '20050317.001327'}, # 	2005-03-17	00:13:27	2005-03-17	01:11:05
'0731'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075130',	 last => '6075131',	 list => '',  beginTime => '20050317.011105'}, # 	2005-03-17	01:11:05	2005-03-17	03:23:53
'0732'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075141',	 last => '6075141',	 list => '',  beginTime => '20050317.032353'}, # 	2005-03-17	03:23:53	2005-03-17	03:54:22
'0733'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075146',	 last => '6075146',	 list => '',  beginTime => '20050317.035422'}, # 	2005-03-17	03:54:22	2005-03-17	04:31:02
'0734'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6075151',	 last => '6075152',	 list => '',  beginTime => '20050317.043102'}, # 	2005-03-17	04:31:02	2005-03-17	05:13:06
'0735'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076001',	 last => '6076003',	 list => '',  beginTime => '20050317.051306'}, # 	2005-03-17	05:13:06	2005-03-17	06:26:13
'0736'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076007',	 last => '6076008',	 list => '',  beginTime => '20050317.062613'}, # 	2005-03-17	06:26:13	2005-03-17	08:19:34
'0737'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076019',	 last => '6076020',	 list => '',  beginTime => '20050317.081934'}, # 	2005-03-17	08:19:34	2005-03-17	09:16:30
'0738'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076022',	 last => '6076022',	 list => '',  beginTime => '20050317.091630'}, # 	2005-03-17	09:16:30	2005-03-17	09:49:03
'0739'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076029',	 last => '6076029',	 list => '',  beginTime => '20050317.094903'}, # 	2005-03-17	09:49:03	2005-03-17	10:09:16
'0740'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076032',	 last => '6076038',	 list => '',  beginTime => '20050317.100916'}, # 	2005-03-17	10:09:16	2005-03-17	13:55:57
'0741'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076041',	 last => '6076042',	 list => '',  beginTime => '20050317.135557'}, # 	2005-03-17	13:55:57	2005-03-17	17:25:10
'0742'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076057',	 last => '6076060',	 list => '',  beginTime => '20050317.172510'}, # 	2005-03-17	17:25:10	2005-03-17	18:25:14
'0743'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076062',	 last => '6076062',	 list => '',  beginTime => '20050317.182514'}, # 	2005-03-17	18:25:14	2005-03-17	22:09:18
'0744'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076075',	 last => '6076075',	 list => '',  beginTime => '20050317.220918'}, # 	2005-03-17	22:09:18	2005-03-17	22:20:08
'0745'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076077',	 last => '6076077',	 list => '',  beginTime => '20050317.222008'}, # 	2005-03-17	22:20:08	2005-03-17	23:26:42
'0746'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076091',	 last => '6076091',	 list => '',  beginTime => '20050317.232642'}, # 	2005-03-17	23:26:42	2005-03-17	23:38:02
'0747'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076093',	 last => '6076093',	 list => '',  beginTime => '20050317.233802'}, # 	2005-03-17	23:38:02	2005-03-18	00:12:29
'0748'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076097',	 last => '6076099',	 list => '',  beginTime => '20050318.001229'}, # 	2005-03-18	00:12:29	2005-03-18	01:01:43
'0749'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076102',	 last => '6076102',	 list => '',  beginTime => '20050318.010143'}, # 	2005-03-18	01:01:43	2005-03-18	01:14:41
'0750'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076106',	 last => '6076106',	 list => '',  beginTime => '20050318.011441'}, # 	2005-03-18	01:14:41	2005-03-18	01:41:08
'0751'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076108',	 last => '6076109',	 list => '',  beginTime => '20050318.014108'}, # 	2005-03-18	01:41:08	2005-03-18	03:22:44
'0752'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076112',	 last => '6076112',	 list => '',  beginTime => '20050318.032244'}, # 	2005-03-18	03:22:44	2005-03-18	03:40:36
'0753'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6076118',	 last => '6076119',	 list => '',  beginTime => '20050318.034036'}, # 	2005-03-18	03:40:36	2005-03-18	05:05:43
'0754'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077001',	 last => '6077004',	 list => '',  beginTime => '20050318.050543'}, # 	2005-03-18	05:05:43	2005-03-18	07:15:24
'0755'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077006',	 last => '6077006',	 list => '',  beginTime => '20050318.071524'}, # 	2005-03-18	07:15:24	2005-03-18	07:52:51
'0756'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077012',	 last => '6077012',	 list => '',  beginTime => '20050318.075251'}, # 	2005-03-18	07:52:51	2005-03-18	09:36:03
'0757'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077026',	 last => '6077026',	 list => '',  beginTime => '20050318.093603'}, # 	2005-03-18	09:36:03	2005-03-18	10:27:33
'0758'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077034',	 last => '6077034',	 list => '',  beginTime => '20050318.102733'}, # 	2005-03-18	10:27:33	2005-03-18	11:25:28
'0759'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077039',	 last => '6077039',	 list => '',  beginTime => '20050318.112528'}, # 	2005-03-18	11:25:28	2005-03-18	11:43:51
'0760'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077044',	 last => '6077044',	 list => '',  beginTime => '20050318.114351'}, # 	2005-03-18	11:43:51	2005-03-18	12:00:14
'0761'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077046',	 last => '6077046',	 list => '',  beginTime => '20050318.120014'}, # 	2005-03-18	12:00:14	2005-03-18	12:46:13
'0762'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077049',	 last => '6077050',	 list => '',  beginTime => '20050318.124613'}, # 	2005-03-18	12:46:13	2005-03-18	18:03:08
'0763'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077063',	 last => '6077064',	 list => '',  beginTime => '20050318.180308'}, # 	2005-03-18	18:03:08	2005-03-18	19:30:42
'0764'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077067',	 last => '6077067',	 list => '',  beginTime => '20050318.193042'}, # 	2005-03-18	19:30:42	2005-03-18	20:13:27
'0765'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077069',	 last => '6077070',	 list => '',  beginTime => '20050318.201327'}, # 	2005-03-18	20:13:27	2005-03-18	21:18:59
'0766'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077073',	 last => '6077073',	 list => '',  beginTime => '20050318.211859'}, # 	2005-03-18	21:18:59	2005-03-18	22:04:09
'0767'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077076',	 last => '6077076',	 list => '',  beginTime => '20050318.220409'}, # 	2005-03-18	22:04:09	2005-03-19	01:22:37
'0768'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077087',	 last => '6077087',	 list => '',  beginTime => '20050319.012237'}, # 	2005-03-19	01:22:37	2005-03-19	02:07:14
'0769'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6077089',	 last => '6077090',	 list => '',  beginTime => '20050319.020714'}, # 	2005-03-19	02:07:14	2005-03-19	05:07:11
'0770'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078001',	 last => '6078001',	 list => '',  beginTime => '20050319.050711'}, # 	2005-03-19	05:07:11	2005-03-19	05:34:54
'0771'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078007',	 last => '6078008',	 list => '',  beginTime => '20050319.053454'}, # 	2005-03-19	05:34:54	2005-03-19	06:30:14
'0772'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078011',	 last => '6078012',	 list => '',  beginTime => '20050319.063014'}, # 	2005-03-19	06:30:14	2005-03-19	07:42:39
'0773'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078015',	 last => '6078015',	 list => '',  beginTime => '20050319.074239'}, # 	2005-03-19	07:42:39	2005-03-19	08:34:52
'0774'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078023',	 last => '6078025',	 list => '',  beginTime => '20050319.083452'}, # 	2005-03-19	08:34:52	2005-03-19	11:45:58
'0775'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078034',	 last => '6078034',	 list => '',  beginTime => '20050319.114558'}, # 	2005-03-19	11:45:58	2005-03-19	11:51:00
'0776'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078036',	 last => '6078036',	 list => '',  beginTime => '20050319.115100'}, # 	2005-03-19	11:51:00	2005-03-19	12:52:35
'0777'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078042',	 last => '6078042',	 list => '',  beginTime => '20050319.125235'}, # 	2005-03-19	12:52:35	2005-03-19	13:05:53
'0778'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078044',	 last => '6078045',	 list => '',  beginTime => '20050319.130553'}, # 	2005-03-19	13:05:53	2005-03-19	14:22:18
'0779'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078047',	 last => '6078047',	 list => '',  beginTime => '20050319.142218'}, # 	2005-03-19	14:22:18	2005-03-19	14:44:56
'0780'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078049',	 last => '6078052',	 list => '',  beginTime => '20050319.144456'}, # 	2005-03-19	14:44:56	2005-03-19	17:38:00
'0781'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078066',	 last => '6078068',	 list => '',  beginTime => '20050319.173800'}, # 	2005-03-19	17:38:00	2005-03-19	20:21:40
'0782'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078077',	 last => '6078077',	 list => '',  beginTime => '20050319.202140'}, # 	2005-03-19	20:21:40	2005-03-19	20:34:35
'0783'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078079',	 last => '6078080',	 list => '',  beginTime => '20050319.203435'}, # 	2005-03-19	20:34:35	2005-03-19	22:10:22
'0784'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078083',	 last => '6078086',	 list => '',  beginTime => '20050319.221022'}, # 	2005-03-19	22:10:22	2005-03-20	00:15:57
'0785'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6078089',	 last => '6078089',	 list => '',  beginTime => '20050320.001557'}, # 	2005-03-20	00:15:57	2005-03-20	05:20:13
'0786'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079003',	 last => '6079005',	 list => '',  beginTime => '20050320.052013'}, # 	2005-03-20	05:20:13	2005-03-20	07:32:20
'0787'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079014',	 last => '6079015',	 list => '',  beginTime => '20050320.073220'}, # 	2005-03-20	07:32:20	2005-03-20	08:23:30
'0788'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079019',	 last => '6079021',	 list => '',  beginTime => '20050320.082330'}, # 	2005-03-20	08:23:30	2005-03-20	09:05:35
'0789'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079026',	 last => '6079026',	 list => '',  beginTime => '20050320.090535'}, # 	2005-03-20	09:05:35	2005-03-20	09:32:39
'0790'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079028',	 last => '6079028',	 list => '',  beginTime => '20050320.093239'}, # 	2005-03-20	09:32:39	2005-03-20	10:02:55
'0791'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079032',	 last => '6079032',	 list => '',  beginTime => '20050320.100255'}, # 	2005-03-20	10:02:55	2005-03-20	10:30:09
'0792'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079035',	 last => '6079035',	 list => '',  beginTime => '20050320.103009'}, # 	2005-03-20	10:30:09	2005-03-20	10:57:52
'0793'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079037',	 last => '6079039',	 list => '',  beginTime => '20050320.105752'}, # 	2005-03-20	10:57:52	2005-03-20	13:02:46
'0794'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079042',	 last => '6079042',	 list => '',  beginTime => '20050320.130246'}, # 	2005-03-20	13:02:46	2005-03-20	13:14:11
'0795'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079047',	 last => '6079049',	 list => '',  beginTime => '20050320.131411'}, # 	2005-03-20	13:14:11	2005-03-20	14:34:30
'0796'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079051',	 last => '6079052',	 list => '',  beginTime => '20050320.143430'}, # 	2005-03-20	14:34:30	2005-03-20	15:28:24
'0797'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079054',	 last => '6079056',	 list => '',  beginTime => '20050320.152824'}, # 	2005-03-20	15:28:24	2005-03-20	15:48:14
'0798'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079058',	 last => '6079058',	 list => '',  beginTime => '20050320.154814'}, # 	2005-03-20	15:48:14	2005-03-20	16:32:43
'0799'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079067',	 last => '6079069',	 list => '',  beginTime => '20050320.163243'}, # 	2005-03-20	16:32:43	2005-03-20	17:41:16
'0800'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079071',	 last => '6079071',	 list => '',  beginTime => '20050320.174116'}, # 	2005-03-20	17:41:16	2005-03-20	19:30:20
'0801'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079094',	 last => '6079094',	 list => '',  beginTime => '20050320.193020'}, # 	2005-03-20	19:30:20	2005-03-20	19:39:06
'0802'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079096',	 last => '6079098',	 list => '',  beginTime => '20050320.193906'}, # 	2005-03-20	19:39:06	2005-03-20	20:46:14
'0803'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079101',	 last => '6079102',	 list => '',  beginTime => '20050320.204614'}, # 	2005-03-20	20:46:14	2005-03-20	21:24:20
'0804'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079104',	 last => '6079104',	 list => '',  beginTime => '20050320.212420'}, # 	2005-03-20	21:24:20	2005-03-20	22:05:39
'0805'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079107',	 last => '6079107',	 list => '',  beginTime => '20050320.220539'}, # 	2005-03-20	22:05:39	2005-03-20	22:30:41
'0806'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079109',	 last => '6079110',	 list => '',  beginTime => '20050320.223041'}, # 	2005-03-20	22:30:41	2005-03-21	00:00:14
'0807'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079113',	 last => '6079113',	 list => '',  beginTime => '20050321.000014'}, # 	2005-03-21	00:00:14	2005-03-21	00:15:01
'0808'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079119',	 last => '6079119',	 list => '',  beginTime => '20050321.001501'}, # 	2005-03-21	00:15:01	2005-03-21	00:58:07
'0809'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079121',	 last => '6079121',	 list => '',  beginTime => '20050321.005807'}, # 	2005-03-21	00:58:07	2005-03-21	01:44:59
'0810'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079123',	 last => '6079123',	 list => '',  beginTime => '20050321.014459'}, # 	2005-03-21	01:44:59	2005-03-21	01:54:47
'0811'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079125',	 last => '6079125',	 list => '',  beginTime => '20050321.015447'}, # 	2005-03-21	01:54:47	2005-03-21	02:45:51
'0812'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079128',	 last => '6079131',	 list => '',  beginTime => '20050321.024551'}, # 	2005-03-21	02:45:51	2005-03-21	04:43:00
'0813'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6079134',	 last => '6079134',	 list => '',  beginTime => '20050321.044300'}, # 	2005-03-21	04:43:00	2005-03-21	05:42:56
'0814'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080006',	 last => '6080006',	 list => '',  beginTime => '20050321.054256'}, # 	2005-03-21	05:42:56	2005-03-21	06:38:32
'0815'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080009',	 last => '6080011',	 list => '',  beginTime => '20050321.063832'}, # 	2005-03-21	06:38:32	2005-03-21	07:34:37
'0816'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080013',	 last => '6080018',	 list => '',  beginTime => '20050321.073437'}, # 	2005-03-21	07:34:37	2005-03-21	09:16:54
'0817'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080020',	 last => '6080021',	 list => '',  beginTime => '20050321.091654'}, # 	2005-03-21	09:16:54	2005-03-21	11:14:28
'0818'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080028',	 last => '6080028',	 list => '',  beginTime => '20050321.111428'}, # 	2005-03-21	11:14:28	2005-03-22	01:06:33
'0819'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080041',	 last => '6080041',	 list => '',  beginTime => '20050322.010633'}, # 	2005-03-22	01:06:33	2005-03-22	01:51:23
'0820'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080043',	 last => '6080043',	 list => '',  beginTime => '20050322.015123'}, # 	2005-03-22	01:51:23	2005-03-22	02:49:07
'0821'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080046',	 last => '6080047',	 list => '',  beginTime => '20050322.024907'}, # 	2005-03-22	02:49:07	2005-03-22	03:39:30
'0822'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080049',	 last => '6080050',	 list => '',  beginTime => '20050322.033930'}, # 	2005-03-22	03:39:30	2005-03-22	04:30:00
'0823'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6080052',	 last => '6080052',	 list => '',  beginTime => '20050322.043000'}, # 	2005-03-22	04:30:00	2005-03-22	05:04:18
'0824'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081002',	 last => '6081002',	 list => '',  beginTime => '20050322.050418'}, # 	2005-03-22	05:04:18	2005-03-22	05:28:36
'0825'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081004',	 last => '6081005',	 list => '',  beginTime => '20050322.052836'}, # 	2005-03-22	05:28:36	2005-03-22	07:08:53
'0826'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081014',	 last => '6081014',	 list => '',  beginTime => '20050322.070853'}, # 	2005-03-22	07:08:53	2005-03-22	08:09:12
'0827'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081017',	 last => '6081017',	 list => '',  beginTime => '20050322.080912'}, # 	2005-03-22	08:09:12	2005-03-22	08:25:50
'0828'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081019',	 last => '6081019',	 list => '',  beginTime => '20050322.082550'}, # 	2005-03-22	08:25:50	2005-03-22	09:03:44
'0829'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081022',	 last => '6081027',	 list => '',  beginTime => '20050322.090344'}, # 	2005-03-22	09:03:44	2005-03-22	12:32:26
'0830'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081033',	 last => '6081033',	 list => '',  beginTime => '20050322.123226'}, # 	2005-03-22	12:32:26	2005-03-22	13:02:06
'0831'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081035',	 last => '6081035',	 list => '',  beginTime => '20050322.130206'}, # 	2005-03-22	13:02:06	2005-03-22	13:56:03
'0832'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081038',	 last => '6081038',	 list => '',  beginTime => '20050322.135603'}, # 	2005-03-22	13:56:03	2005-03-22	14:49:54
'0833'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081041',	 last => '6081043',	 list => '',  beginTime => '20050322.144954'}, # 	2005-03-22	14:49:54	2005-03-22	16:12:54
'0834'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081046',	 last => '6081047',	 list => '',  beginTime => '20050322.161254'}, # 	2005-03-22	16:12:54	2005-03-22	16:36:50
'0835'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081051',	 last => '6081051',	 list => '',  beginTime => '20050322.163650'}, # 	2005-03-22	16:36:50	2005-03-22	17:04:48
'0836'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081054',	 last => '6081054',	 list => '',  beginTime => '20050322.170448'}, # 	2005-03-22	17:04:48	2005-03-22	17:21:20
'0837'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081057',	 last => '6081057',	 list => '',  beginTime => '20050322.172120'}, # 	2005-03-22	17:21:20	2005-03-22	17:30:15
'0838'=> {trig=>'cu62productionMinBias', 	field => 'FF',	first=> '6081059',	 last => '6081062',	 list => '',  beginTime => '20050322.173015'}, # 	2005-03-22	17:30:15	2005-03-23	00:08:41
'0839'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6081109',	 last => '6081109',	 list => '',  beginTime => '20050323.000841'}, # 	2005-03-23	00:08:41	2005-03-23	04:39:20	timestamp = cu22ProductionMinBias_FF
'0840'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6081121',	 last => '6081121',	 list => '',  beginTime => '20050323.043920'}, # 	2005-03-23	04:39:20	2005-03-23	06:35:25
'0841'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082009',	 last => '6082012',	 list => '',  beginTime => '20050323.063525'}, # 	2005-03-23	06:35:25	2005-03-23	07:45:49
'0842'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082014',	 last => '6082014',	 list => '',  beginTime => '20050323.074549'}, # 	2005-03-23	07:45:49	2005-03-23	08:19:44
'0843'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082017',	 last => '6082021',	 list => '',  beginTime => '20050323.081944'}, # 	2005-03-23	08:19:44	2005-03-23	09:59:47
'0844'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082023',	 last => '6082023',	 list => '',  beginTime => '20050323.095947'}, # 	2005-03-23	09:59:47	2005-03-23	10:14:53
'0845'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082025',	 last => '6082026',	 list => '',  beginTime => '20050323.101453'}, # 	2005-03-23	10:14:53	2005-03-23	10:58:30
'0846'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082030',	 last => '6082031',	 list => '',  beginTime => '20050323.105830'}, # 	2005-03-23	10:58:30	2005-03-23	11:24:37
'0847'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082033',	 last => '6082034',	 list => '',  beginTime => '20050323.112437'}, # 	2005-03-23	11:24:37	2005-03-23	12:31:40
'0848'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082037',	 last => '6082040',	 list => '',  beginTime => '20050323.123140'}, # 	2005-03-23	12:31:40	2005-03-23	13:40:05
'0849'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082043',	 last => '6082047',	 list => '',  beginTime => '20050323.134005'}, # 	2005-03-23	13:40:05	2005-03-23	15:49:06
'0850'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082051',	 last => '6082057',	 list => '',  beginTime => '20050323.154906'}, # 	2005-03-23	15:49:06	2005-03-23	16:41:13
'0851'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082060',	 last => '6082060',	 list => '',  beginTime => '20050323.164113'}, # 	2005-03-23	16:41:13	2005-03-23	17:13:08
'0852'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082067',	 last => '6082068',	 list => '',  beginTime => '20050323.171308'}, # 	2005-03-23	17:13:08	2005-03-23	17:50:56
'0853'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082071',	 last => '6082073',	 list => '',  beginTime => '20050323.175056'}, # 	2005-03-23	17:50:56	2005-03-23	19:04:18
'0854'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082076',	 last => '6082076',	 list => '',  beginTime => '20050323.190418'}, # 	2005-03-23	19:04:18	2005-03-23	20:13:59
'0855'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082084',	 last => '6082085',	 list => '',  beginTime => '20050323.201359'}, # 	2005-03-23	20:13:59	2005-03-23	21:33:34
'0856'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082090',	 last => '6082091',	 list => '',  beginTime => '20050323.213334'}, # 	2005-03-23	21:33:34	2005-03-23	22:29:53
'0857'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082094',	 last => '6082096',	 list => '',  beginTime => '20050323.222953'}, # 	2005-03-23	22:29:53	2005-03-24	02:45:31
'0858'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082100',	 last => '6082101',	 list => '',  beginTime => '20050324.024531'}, # 	2005-03-24	02:45:31	2005-03-24	04:32:45
'0859'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6082106',	 last => '6082107',	 list => '',  beginTime => '20050324.043245'}, # 	2005-03-24	04:32:45	2005-03-24	05:21:53
'0860'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6083003',	 last => '6083003',	 list => '',  beginTime => '20050324.052153'}, # 	2005-03-24	05:21:53	2005-03-24	06:31:17
'0861'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6083006',	 last => '6083006',	 list => '',  beginTime => '20050324.063117'}, # 	2005-03-24	06:31:17	2005-03-24	06:46:35
'0862'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6083008',	 last => '6083009',	 list => '',  beginTime => '20050324.064635'}, # 	2005-03-24	06:46:35	2005-03-24	08:14:49
'0863'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6083011',	 last => '6083013',	 list => '',  beginTime => '20050324.081449'}, # 	2005-03-24	08:14:49	2005-03-24	09:39:56
'0864'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6083019',	 last => '6083021',	 list => '',  beginTime => '20050324.093956'}, # 	2005-03-24	09:39:56	2005-03-24	10:16:27
'0865'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6083024',	 last => '6083024',	 list => '',  beginTime => '20050324.101627'}, # 	2005-03-24	10:16:27	2005-03-24	11:01:07
'0866'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6083027',	 last => '6083031',	 list => '',  beginTime => '20050324.110107'}, # 	2005-03-24	11:01:07	2005-03-24	12:42:36
'0867'=> {trig=>'cu22ProductionMinBias', 	field => 'FF',	first=> '6083034',	 last => '6083034',	 list => '',  beginTime => '20050324.124236'}, # 	2005-03-24	12:42:36	2005-05-06	12:05:32
'0868'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6126035',	 last => '6126036',	 list => '',  beginTime => '20050506.120532'}, # 	2005-05-06	12:05:32	2005-05-06	12:26:38	timestamp = ppProductionMinBias_FF
'0869'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6126037',	 last => '6126038',	 list => '',  beginTime => '20050506.122638'}, # 	2005-05-06	12:26:38	2005-05-06	13:24:15	timestamp = ppProduction_FF
'0870'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6126043',	 last => '6126043',	 list => '',  beginTime => '20050506.132415'}, # 	2005-05-06	13:24:15	2005-05-06	14:33:11
'0871'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6126048',	 last => '6126049',	 list => '',  beginTime => '20050506.143311'}, # 	2005-05-06	14:33:11	2005-05-06	16:19:31
'0872'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6126053',	 last => '6126054',	 list => '',  beginTime => '20050506.161931'}, # 	2005-05-06	16:19:31	2005-05-06	21:41:28
'0873'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6126069',	 last => '6126073',	 list => '',  beginTime => '20050506.214128'}, # 	2005-05-06	21:41:28	2005-05-07	00:41:43
'0874'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6126076',	 last => '6126078',	 list => '',  beginTime => '20050507.004143'}, # 	2005-05-07	00:41:43	2005-05-07	02:16:21
'0875'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6126080',	 last => '6126081',	 list => '',  beginTime => '20050507.021621'}, # 	2005-05-07	02:16:21	2005-05-07	03:18:12
'0876'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6126083',	 last => '6126084',	 list => '',  beginTime => '20050507.031812'}, # 	2005-05-07	03:18:12	2005-05-07	08:43:25
'0877'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6127008',	 last => '6127008',	 list => '',  beginTime => '20050507.084325'}, # 	2005-05-07	08:43:25	2005-05-07	10:00:55	timestamp = ppProductionMinBias_FF
'0878'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6127012',	 last => '6127012',	 list => '',  beginTime => '20050507.100055'}, # 	2005-05-07	10:00:55	2005-05-07	15:36:30
'0879'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6127030',	 last => '6127031',	 list => '',  beginTime => '20050507.153630'}, # 	2005-05-07	15:36:30	2005-05-07	16:09:29	timestamp = ppProduction_FF
'0880'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6127032',	 last => '6127032',	 list => '',  beginTime => '20050507.160929'}, # 	2005-05-07	16:09:29	2005-05-07	16:24:10	timestamp = ppProductionMinBias_FF
'0881'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6127034',	 last => '6127037',	 list => '',  beginTime => '20050507.162410'}, # 	2005-05-07	16:24:10	2005-05-07	19:04:00	timestamp = ppProduction_FF
'0882'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6127039',	 last => '6127040',	 list => '',  beginTime => '20050507.190400'}, # 	2005-05-07	19:04:00	2005-05-07	20:24:20
'0883'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6127042',	 last => '6127042',	 list => '',  beginTime => '20050507.202420'}, # 	2005-05-07	20:24:20	2005-05-07	20:42:41
'0884'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6127043',	 last => '6127043',	 list => '',  beginTime => '20050507.204241'}, # 	2005-05-07	20:42:41	2005-05-07	20:54:44	timestamp = ppProductionMinBias_FF
'0885'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6127046',	 last => '6127046',	 list => '',  beginTime => '20050507.205444'}, # 	2005-05-07	20:54:44	2005-05-08	02:20:01	timestamp = ppProduction_FF
'0886'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6127054',	 last => '6127056',	 list => '',  beginTime => '20050508.022001'}, # 	2005-05-08	02:20:01	2005-05-08	03:22:10
'0887'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6127059',	 last => '6127059',	 list => '',  beginTime => '20050508.032210'}, # 	2005-05-08	03:22:10	2005-05-08	04:03:54
'0888'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6128001',	 last => '6128001',	 list => '',  beginTime => '20050508.040354'}, # 	2005-05-08	04:03:54	2005-05-08	04:15:48	timestamp = ppProductionMinBias_FF
'0889'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6128005',	 last => '6128007',	 list => '',  beginTime => '20050508.041548'}, # 	2005-05-08	04:15:48	2005-05-08	05:27:32	timestamp = ppProduction_FF
'0890'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6128009',	 last => '6128009',	 list => '',  beginTime => '20050508.052732'}, # 	2005-05-08	05:27:32	2005-05-08	05:53:57
'0891'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6128010',	 last => '6128010',	 list => '',  beginTime => '20050508.055357'}, # 	2005-05-08	05:53:57	2005-05-08	05:58:23	timestamp = ppProductionMinBias_FF
'0892'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6128011',	 last => '6128016',	 list => '',  beginTime => '20050508.055823'}, # 	2005-05-08	05:58:23	2005-05-08	07:47:26	timestamp = ppProduction_FF
'0893'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6128018',	 last => '6128018',	 list => '',  beginTime => '20050508.074726'}, # 	2005-05-08	07:47:26	2005-05-08	07:53:45
'0894'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6128019',	 last => '6128019',	 list => '',  beginTime => '20050508.075345'}, # 	2005-05-08	07:53:45	2005-05-08	08:22:06	timestamp = ppProductionMinBias_FF
'0895'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6128022',	 last => '6128024',	 list => '',  beginTime => '20050508.082206'}, # 	2005-05-08	08:22:06	2005-05-08	09:02:13	timestamp = ppProduction_FF
'0896'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6128025',	 last => '6128025',	 list => '',  beginTime => '20050508.090213'}, # 	2005-05-08	09:02:13	2005-05-08	09:07:06	timestamp = ppProductionMinBias_FF
'0897'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6128026',	 last => '6128032',	 list => '',  beginTime => '20050508.090706'}, # 	2005-05-08	09:07:06	2005-05-08	11:02:16	timestamp = ppProduction_FF
'0898'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6128033',	 last => '6128033',	 list => '',  beginTime => '20050508.110216'}, # 	2005-05-08	11:02:16	2005-05-08	14:27:52	timestamp = ppProductionMinBias_FF
'0899'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6128035',	 last => '6128035',	 list => '',  beginTime => '20050508.142752'}, # 	2005-05-08	14:27:52	2005-05-08	15:32:32
'0900'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6128043',	 last => '6128044',	 list => '',  beginTime => '20050508.153232'}, # 	2005-05-08	15:32:32	2005-05-08	16:00:36	timestamp = ppProduction_FF
'0901'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6128046',	 last => '6128046',	 list => '',  beginTime => '20050508.160036'}, # 	2005-05-08	16:00:36	2005-05-08	16:28:36	timestamp = ppProductionMinBias_FF
'0902'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6128050',	 last => '6128059',	 list => '',  beginTime => '20050508.162836'}, # 	2005-05-08	16:28:36	2005-05-08	20:13:40	timestamp = ppProduction_FF
'0903'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6128062',	 last => '6128063',	 list => '',  beginTime => '20050508.201340'}, # 	2005-05-08	20:13:40	2005-05-10	06:45:12
'0904'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6130007',	 last => '6130009',	 list => '',  beginTime => '20050510.064512'}, # 	2005-05-10	06:45:12	2005-05-10	08:00:02
'0905'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6130013',	 last => '6130013',	 list => '',  beginTime => '20050510.080002'}, # 	2005-05-10	08:00:02	2005-05-10	08:25:41
'0906'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6130016',	 last => '6130018',	 list => '',  beginTime => '20050510.082541'}, # 	2005-05-10	08:25:41	2005-05-10	09:00:39	timestamp = ppProductionMinBias_FF
'0907'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6130019',	 last => '6130021',	 list => '',  beginTime => '20050510.090039'}, # 	2005-05-10	09:00:39	2005-05-10	10:15:31	timestamp = ppProduction_FF
'0908'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6130022',	 last => '6130022',	 list => '',  beginTime => '20050510.101531'}, # 	2005-05-10	10:15:31	2005-05-10	10:18:08	timestamp = ppProductionMinBias_FF
'0909'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6130023',	 last => '6130023',	 list => '',  beginTime => '20050510.101808'}, # 	2005-05-10	10:18:08	2005-05-10	10:27:00	timestamp = ppProduction_FF
'0910'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6130025',	 last => '6130029',	 list => '',  beginTime => '20050510.102700'}, # 	2005-05-10	10:27:00	2005-05-10	22:17:07
'0911'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6130054',	 last => '6130056',	 list => '',  beginTime => '20050510.221707'}, # 	2005-05-10	22:17:07	2005-05-10	23:27:13
'0912'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6130057',	 last => '6130057',	 list => '',  beginTime => '20050510.232713'}, # 	2005-05-10	23:27:13	2005-05-10	23:53:30	timestamp = ppProductionMinBias_FF
'0913'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6130060',	 last => '6130061',	 list => '',  beginTime => '20050510.235330'}, # 	2005-05-10	23:53:30	2005-05-11	00:27:31	timestamp = ppProduction_FF
'0914'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6130063',	 last => '6130065',	 list => '',  beginTime => '20050511.002731'}, # 	2005-05-11	00:27:31	2005-05-11	01:38:09
'0915'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6130068',	 last => '6130071',	 list => '',  beginTime => '20050511.013809'}, # 	2005-05-11	01:38:09	2005-05-11	05:00:20	timestamp = ppProductionMinBias_FF
'0916'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131007',	 last => '6131010',	 list => '',  beginTime => '20050511.050020'}, # 	2005-05-11	05:00:20	2005-05-11	06:24:30	timestamp = ppProduction_FF
'0917'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131013',	 last => '6131013',	 list => '',  beginTime => '20050511.062430'}, # 	2005-05-11	06:24:30	2005-05-11	09:33:50
'0918'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131048',	 last => '6131049',	 list => '',  beginTime => '20050511.093350'}, # 	2005-05-11	09:33:50	2005-05-11	10:42:08
'0919'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6131051',	 last => '6131051',	 list => '',  beginTime => '20050511.104208'}, # 	2005-05-11	10:42:08	2005-05-11	10:47:36	timestamp = ppProductionMinBias_FF
'0920'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131052',	 last => '6131054',	 list => '',  beginTime => '20050511.104736'}, # 	2005-05-11	10:47:36	2005-05-11	12:04:17	timestamp = ppProduction_FF
'0921'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131056',	 last => '6131057',	 list => '',  beginTime => '20050511.120417'}, # 	2005-05-11	12:04:17	2005-05-11	12:54:03
'0922'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6131060',	 last => '6131060',	 list => '',  beginTime => '20050511.125403'}, # 	2005-05-11	12:54:03	2005-05-11	12:57:50	timestamp = ppProductionMinBias_FF
'0923'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131061',	 last => '6131061',	 list => '',  beginTime => '20050511.125750'}, # 	2005-05-11	12:57:50	2005-05-11	13:00:03	timestamp = ppProduction_FF
'0924'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6131062',	 last => '6131062',	 list => '',  beginTime => '20050511.130003'}, # 	2005-05-11	13:00:03	2005-05-11	16:49:42	timestamp = ppProductionMinBias_FF
'0925'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131089',	 last => '6131089',	 list => '',  beginTime => '20050511.164942'}, # 	2005-05-11	16:49:42	2005-05-11	16:58:48	timestamp = ppProduction_FF
'0926'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131092',	 last => '6131092',	 list => '',  beginTime => '20050511.165848'}, # 	2005-05-11	16:58:48	2005-05-11	17:28:17
'0927'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131094',	 last => '6131094',	 list => '',  beginTime => '20050511.172817'}, # 	2005-05-11	17:28:17	2005-05-11	18:00:20
'0928'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6131097',	 last => '6131098',	 list => '',  beginTime => '20050511.180020'}, # 	2005-05-11	18:00:20	2005-05-12	04:33:45
'0929'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6132006',	 last => '6132007',	 list => '',  beginTime => '20050512.043345'}, # 	2005-05-12	04:33:45	2005-05-12	05:00:15	timestamp = ppProductionMinBias_FF
'0930'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6132009',	 last => '6132009',	 list => '',  beginTime => '20050512.050015'}, # 	2005-05-12	05:00:15	2005-05-12	05:43:09
'0931'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6132015',	 last => '6132016',	 list => '',  beginTime => '20050512.054309'}, # 	2005-05-12	05:43:09	2005-05-12	06:18:15
'0932'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6132019',	 last => '6132021',	 list => '',  beginTime => '20050512.061815'}, # 	2005-05-12	06:18:15	2005-05-12	07:40:12	timestamp = ppProduction_FF
'0933'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6132025',	 last => '6132026',	 list => '',  beginTime => '20050512.074012'}, # 	2005-05-12	07:40:12	2005-05-13	03:16:39
'0934'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6132115',	 last => '6132116',	 list => '',  beginTime => '20050513.031639'}, # 	2005-05-13	03:16:39	2005-05-13	03:55:59
'0935'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6132120',	 last => '6132120',	 list => '',  beginTime => '20050513.035559'}, # 	2005-05-13	03:55:59	2005-05-13	04:43:31
'0936'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6133009',	 last => '6133018',	 list => '',  beginTime => '20050513.044331'}, # 	2005-05-13	04:43:31	2005-05-13	08:47:26
'0937'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6133022',	 last => '6133022',	 list => '',  beginTime => '20050513.084726'}, # 	2005-05-13	08:47:26	2005-05-13	09:25:37
'0938'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6133026',	 last => '6133026',	 list => '',  beginTime => '20050513.092537'}, # 	2005-05-13	09:25:37	2005-05-14	01:30:40
'0939'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6133047',	 last => '6133047',	 list => '',  beginTime => '20050514.013040'}, # 	2005-05-14	01:30:40	2005-05-14	01:42:14	timestamp = ppProductionMinBias_FF
'0940'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6133049',	 last => '6133049',	 list => '',  beginTime => '20050514.014214'}, # 	2005-05-14	01:42:14	2005-05-14	01:52:31	timestamp = ppProduction_FF
'0941'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6133051',	 last => '6133052',	 list => '',  beginTime => '20050514.015231'}, # 	2005-05-14	01:52:31	2005-05-14	02:32:19	timestamp = ppProductionMinBias_FF
'0942'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6133060',	 last => '6133060',	 list => '',  beginTime => '20050514.023219'}, # 	2005-05-14	02:32:19	2005-05-14	02:37:40
'0943'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6133062',	 last => '6133062',	 list => '',  beginTime => '20050514.023740'}, # 	2005-05-14	02:37:40	2005-05-14	03:11:27
'0944'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6133068',	 last => '6133068',	 list => '',  beginTime => '20050514.031127'}, # 	2005-05-14	03:11:27	2005-05-14	03:25:48	timestamp = ppProduction_FF
'0945'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6133071',	 last => '6133072',	 list => '',  beginTime => '20050514.032548'}, # 	2005-05-14	03:25:48	2005-05-14	04:10:23
'0946'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134001',	 last => '6134003',	 list => '',  beginTime => '20050514.041023'}, # 	2005-05-14	04:10:23	2005-05-14	05:33:36
'0947'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134005',	 last => '6134008',	 list => '',  beginTime => '20050514.053336'}, # 	2005-05-14	05:33:36	2005-05-14	06:40:09
'0948'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134010',	 last => '6134011',	 list => '',  beginTime => '20050514.064009'}, # 	2005-05-14	06:40:09	2005-05-14	06:55:45
'0949'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6134013',	 last => '6134013',	 list => '',  beginTime => '20050514.065545'}, # 	2005-05-14	06:55:45	2005-05-14	07:05:39	timestamp = ppProductionMinBias_FF
'0950'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6134015',	 last => '6134015',	 list => '',  beginTime => '20050514.070539'}, # 	2005-05-14	07:05:39	2005-05-14	09:17:57
'0951'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134021',	 last => '6134021',	 list => '',  beginTime => '20050514.091757'}, # 	2005-05-14	09:17:57	2005-05-14	09:35:50	timestamp = ppProduction_FF
'0952'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134024',	 last => '6134026',	 list => '',  beginTime => '20050514.093550'}, # 	2005-05-14	09:35:50	2005-05-14	10:51:06
'0953'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6134027',	 last => '6134027',	 list => '',  beginTime => '20050514.105106'}, # 	2005-05-14	10:51:06	2005-05-14	10:54:36	timestamp = ppProductionMinBias_FF
'0954'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134028',	 last => '6134028',	 list => '',  beginTime => '20050514.105436'}, # 	2005-05-14	10:54:36	2005-05-14	11:16:25	timestamp = ppProduction_FF
'0955'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134032',	 last => '6134037',	 list => '',  beginTime => '20050514.111625'}, # 	2005-05-14	11:16:25	2005-05-14	13:04:27
'0956'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6134038',	 last => '6134038',	 list => '',  beginTime => '20050514.130427'}, # 	2005-05-14	13:04:27	2005-05-14	13:11:01	timestamp = ppProductionMinBias_FF
'0957'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134039',	 last => '6134040',	 list => '',  beginTime => '20050514.131101'}, # 	2005-05-14	13:11:01	2005-05-14	14:09:01	timestamp = ppProduction_FF
'0958'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134042',	 last => '6134044',	 list => '',  beginTime => '20050514.140901'}, # 	2005-05-14	14:09:01	2005-05-14	15:11:04
'0959'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134046',	 last => '6134047',	 list => '',  beginTime => '20050514.151104'}, # 	2005-05-14	15:11:04	2005-05-14	15:50:30
'0960'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6134048',	 last => '6134048',	 list => '',  beginTime => '20050514.155030'}, # 	2005-05-14	15:50:30	2005-05-14	20:14:51	timestamp = ppProductionMinBias_FF
'0961'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134060',	 last => '6134062',	 list => '',  beginTime => '20050514.201451'}, # 	2005-05-14	20:14:51	2005-05-14	21:07:10	timestamp = ppProduction_FF
'0962'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134064',	 last => '6134064',	 list => '',  beginTime => '20050514.210710'}, # 	2005-05-14	21:07:10	2005-05-14	21:22:28
'0963'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134066',	 last => '6134066',	 list => '',  beginTime => '20050514.212228'}, # 	2005-05-14	21:22:28	2005-05-15	02:05:27
'0964'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134084',	 last => '6134086',	 list => '',  beginTime => '20050515.020527'}, # 	2005-05-15	02:05:27	2005-05-15	03:12:53
'0965'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6134089',	 last => '6134089',	 list => '',  beginTime => '20050515.031253'}, # 	2005-05-15	03:12:53	2005-05-15	03:15:07	timestamp = ppProductionMinBias_FF
'0966'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134090',	 last => '6134092',	 list => '',  beginTime => '20050515.031507'}, # 	2005-05-15	03:15:07	2005-05-15	03:45:45	timestamp = ppProduction_FF
'0967'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6134094',	 last => '6134094',	 list => '',  beginTime => '20050515.034545'}, # 	2005-05-15	03:45:45	2005-05-15	04:17:18
'0968'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6135001',	 last => '6135002',	 list => '',  beginTime => '20050515.041718'}, # 	2005-05-15	04:17:18	2005-05-15	05:06:27
'0969'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6135005',	 last => '6135010',	 list => '',  beginTime => '20050515.050627'}, # 	2005-05-15	05:06:27	2005-05-15	07:09:29
'0970'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6135012',	 last => '6135012',	 list => '',  beginTime => '20050515.070929'}, # 	2005-05-15	07:09:29	2005-05-15	07:12:24	timestamp = ppProductionMinBias_FF
'0971'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6135013',	 last => '6135013',	 list => '',  beginTime => '20050515.071224'}, # 	2005-05-15	07:12:24	2005-05-15	07:33:05	timestamp = ppProduction_FF
'0972'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6135014',	 last => '6135014',	 list => '',  beginTime => '20050515.073305'}, # 	2005-05-15	07:33:05	2005-05-16	02:14:18	timestamp = ppProductionMinBias_FF
'0973'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6135051',	 last => '6135053',	 list => '',  beginTime => '20050516.021418'}, # 	2005-05-16	02:14:18	2005-05-16	07:34:02	timestamp = ppProduction_FF
'0974'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6136013',	 last => '6136018',	 list => '',  beginTime => '20050516.073402'}, # 	2005-05-16	07:34:02	2005-05-16	09:14:03
'0975'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6136023',	 last => '6136023',	 list => '',  beginTime => '20050516.091403'}, # 	2005-05-16	09:14:03	2005-05-16	09:19:06	timestamp = ppProductionMinBias_FF
'0976'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6136026',	 last => '6136026',	 list => '',  beginTime => '20050516.091906'}, # 	2005-05-16	09:19:06	2005-05-16	09:22:03
'0977'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6136027',	 last => '6136037',	 list => '',  beginTime => '20050516.092203'}, # 	2005-05-16	09:22:03	2005-05-16	13:16:32	timestamp = ppProduction_FF
'0978'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6136040',	 last => '6136040',	 list => '',  beginTime => '20050516.131632'}, # 	2005-05-16	13:16:32	2005-05-16	13:19:19	timestamp = ppProductionMinBias_FF
'0979'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6136041',	 last => '6136043',	 list => '',  beginTime => '20050516.131919'}, # 	2005-05-16	13:19:19	2005-05-16	22:03:48	timestamp = ppProduction_FF
'0980'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6136065',	 last => '6136065',	 list => '',  beginTime => '20050516.220348'}, # 	2005-05-16	22:03:48	2005-05-17	02:54:16	timestamp = ppProductionMinBias_FF
'0981'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6136119',	 last => '6136120',	 list => '',  beginTime => '20050517.025416'}, # 	2005-05-17	02:54:16	2005-05-17	03:32:31	timestamp = ppProduction_FF
'0982'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6136130',	 last => '6136131',	 list => '',  beginTime => '20050517.033231'}, # 	2005-05-17	03:32:31	2005-05-17	04:40:18
'0983'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137009',	 last => '6137011',	 list => '',  beginTime => '20050517.044018'}, # 	2005-05-17	04:40:18	2005-05-17	05:27:36
'0984'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6137014',	 last => '6137014',	 list => '',  beginTime => '20050517.052736'}, # 	2005-05-17	05:27:36	2005-05-17	05:45:30	timestamp = ppProductionMinBias_FF
'0985'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6137019',	 last => '6137019',	 list => '',  beginTime => '20050517.054530'}, # 	2005-05-17	05:45:30	2005-05-17	06:15:06
'0986'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6137030',	 last => '6137030',	 list => '',  beginTime => '20050517.061506'}, # 	2005-05-17	06:15:06	2005-05-17	06:41:31
'0987'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6137045',	 last => '6137046',	 list => '',  beginTime => '20050517.064131'}, # 	2005-05-17	06:41:31	2005-05-17	06:47:58
'0988'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137047',	 last => '6137048',	 list => '',  beginTime => '20050517.064758'}, # 	2005-05-17	06:47:58	2005-05-17	07:18:43	timestamp = ppProduction_FF
'0989'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137058',	 last => '6137058',	 list => '',  beginTime => '20050517.071843'}, # 	2005-05-17	07:18:43	2005-05-17	10:31:18
'0990'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137069',	 last => '6137071',	 list => '',  beginTime => '20050517.103118'}, # 	2005-05-17	10:31:18	2005-05-17	11:15:51
'0991'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137074',	 last => '6137074',	 list => '',  beginTime => '20050517.111551'}, # 	2005-05-17	11:15:51	2005-05-17	20:56:50
'0992'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137149',	 last => '6137149',	 list => '',  beginTime => '20050517.205650'}, # 	2005-05-17	20:56:50	2005-05-17	23:04:26
'0993'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137157',	 last => '6137161',	 list => '',  beginTime => '20050517.230426'}, # 	2005-05-17	23:04:26	2005-05-18	00:58:56
'0994'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137163',	 last => '6137164',	 list => '',  beginTime => '20050518.005856'}, # 	2005-05-18	00:58:56	2005-05-18	01:46:52
'0995'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137166',	 last => '6137167',	 list => '',  beginTime => '20050518.014652'}, # 	2005-05-18	01:46:52	2005-05-18	02:27:20
'0996'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6137169',	 last => '6137173',	 list => '',  beginTime => '20050518.022720'}, # 	2005-05-18	02:27:20	2005-05-18	04:24:08
'0997'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6138001',	 last => '6138005',	 list => '',  beginTime => '20050518.042408'}, # 	2005-05-18	04:24:08	2005-05-18	08:42:25
'0998'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6138010',	 last => '6138014',	 list => '',  beginTime => '20050518.084225'}, # 	2005-05-18	08:42:25	2005-05-18	10:22:48
'0999'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6138017',	 last => '6138018',	 list => '',  beginTime => '20050518.102248'}, # 	2005-05-18	10:22:48	2005-05-18	11:00:34
'1000'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6138019',	 last => '6138020',	 list => '',  beginTime => '20050518.110034'}, # 	2005-05-18	11:00:34	2005-05-19	02:03:15	timestamp = ppProductionMinBias_FF
'1001'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6138056',	 last => '6138057',	 list => '',  beginTime => '20050519.020315'}, # 	2005-05-19	02:03:15	2005-05-19	02:23:36	timestamp = ppProduction_FF
'1002'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6138059',	 last => '6138059',	 list => '',  beginTime => '20050519.022336'}, # 	2005-05-19	02:23:36	2005-05-19	02:36:04
'1003'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6138060',	 last => '6138060',	 list => '',  beginTime => '20050519.023604'}, # 	2005-05-19	02:36:04	2005-05-19	02:47:29	timestamp = ppProductionMinBias_FF
'1004'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6138061',	 last => '6138062',	 list => '',  beginTime => '20050519.024729'}, # 	2005-05-19	02:47:29	2005-05-19	03:28:22	timestamp = ppProduction_FF
'1005'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6138063',	 last => '6138063',	 list => '',  beginTime => '20050519.032822'}, # 	2005-05-19	03:28:22	2005-05-19	03:49:05	timestamp = ppProductionMinBias_FF
'1006'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6138067',	 last => '6138067',	 list => '',  beginTime => '20050519.034905'}, # 	2005-05-19	03:49:05	2005-05-19	04:01:35	timestamp = ppProduction_FF
'1007'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139001',	 last => '6139010',	 list => '',  beginTime => '20050519.040135'}, # 	2005-05-19	04:01:35	2005-05-19	07:35:41
'1008'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6139011',	 last => '6139011',	 list => '',  beginTime => '20050519.073541'}, # 	2005-05-19	07:35:41	2005-05-19	07:40:27	timestamp = ppProductionMinBias_FF
'1009'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139012',	 last => '6139012',	 list => '',  beginTime => '20050519.074027'}, # 	2005-05-19	07:40:27	2005-05-19	08:04:45	timestamp = ppProduction_FF
'1010'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6139013',	 last => '6139013',	 list => '',  beginTime => '20050519.080445'}, # 	2005-05-19	08:04:45	2005-05-19	10:44:45	timestamp = ppProductionMinBias_FF
'1011'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139018',	 last => '6139022',	 list => '',  beginTime => '20050519.104445'}, # 	2005-05-19	10:44:45	2005-05-19	12:11:09	timestamp = ppProduction_FF
'1012'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6139024',	 last => '6139024',	 list => '',  beginTime => '20050519.121109'}, # 	2005-05-19	12:11:09	2005-05-19	12:15:59	timestamp = ppProductionMinBias_FF
'1013'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139025',	 last => '6139030',	 list => '',  beginTime => '20050519.121559'}, # 	2005-05-19	12:15:59	2005-05-19	14:13:59	timestamp = ppProduction_FF
'1014'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139034',	 last => '6139034',	 list => '',  beginTime => '20050519.141359'}, # 	2005-05-19	14:13:59	2005-05-19	14:40:20
'1015'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139036',	 last => '6139039',	 list => '',  beginTime => '20050519.144020'}, # 	2005-05-19	14:40:20	2005-05-19	15:28:33
'1016'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139041',	 last => '6139041',	 list => '',  beginTime => '20050519.152833'}, # 	2005-05-19	15:28:33	2005-05-20	00:00:22
'1017'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139049',	 last => '6139050',	 list => '',  beginTime => '20050520.000022'}, # 	2005-05-20	00:00:22	2005-05-20	00:28:44
'1018'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139052',	 last => '6139056',	 list => '',  beginTime => '20050520.002844'}, # 	2005-05-20	00:28:44	2005-05-20	01:42:36
'1019'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6139057',	 last => '6139057',	 list => '',  beginTime => '20050520.014236'}, # 	2005-05-20	01:42:36	2005-05-20	01:58:39	timestamp = ppProductionMinBias_FF
'1020'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139061',	 last => '6139061',	 list => '',  beginTime => '20050520.015839'}, # 	2005-05-20	01:58:39	2005-05-20	02:24:29	timestamp = ppProduction_FF
'1021'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139063',	 last => '6139066',	 list => '',  beginTime => '20050520.022429'}, # 	2005-05-20	02:24:29	2005-05-20	03:44:24
'1022'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6139071',	 last => '6139071',	 list => '',  beginTime => '20050520.034424'}, # 	2005-05-20	03:44:24	2005-05-20	04:03:41
'1023'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6140001',	 last => '6140003',	 list => '',  beginTime => '20050520.040341'}, # 	2005-05-20	04:03:41	2005-05-20	05:24:33
'1024'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6140004',	 last => '6140005',	 list => '',  beginTime => '20050520.052433'}, # 	2005-05-20	05:24:33	2005-05-20	08:24:57	timestamp = ppProductionMinBias_FF
'1025'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6140018',	 last => '6140026',	 list => '',  beginTime => '20050520.082457'}, # 	2005-05-20	08:24:57	2005-05-20	11:13:12	timestamp = ppProduction_FF
'1026'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6140028',	 last => '6140036',	 list => '',  beginTime => '20050520.111312'}, # 	2005-05-20	11:13:12	2005-05-20	23:21:42
'1027'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6140054',	 last => '6140054',	 list => '',  beginTime => '20050520.232142'}, # 	2005-05-20	23:21:42	2005-05-21	00:25:17
'1028'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6140065',	 last => '6140069',	 list => '',  beginTime => '20050521.002517'}, # 	2005-05-21	00:25:17	2005-05-21	01:47:09
'1029'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6140070',	 last => '6140070',	 list => '',  beginTime => '20050521.014709'}, # 	2005-05-21	01:47:09	2005-05-21	02:08:28	timestamp = ppProductionMinBias_FF
'1030'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6140074',	 last => '6140076',	 list => '',  beginTime => '20050521.020828'}, # 	2005-05-21	02:08:28	2005-05-21	10:22:08	timestamp = ppProduction_FF
'1031'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6141008',	 last => '6141011',	 list => '',  beginTime => '20050521.102208'}, # 	2005-05-21	10:22:08	2005-05-21	11:28:51
'1032'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6141013',	 last => '6141013',	 list => '',  beginTime => '20050521.112851'}, # 	2005-05-21	11:28:51	2005-05-21	12:14:39
'1033'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6141020',	 last => '6141023',	 list => '',  beginTime => '20050521.121439'}, # 	2005-05-21	12:14:39	2005-05-21	13:06:46
'1034'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6141024',	 last => '6141024',	 list => '',  beginTime => '20050521.130646'}, # 	2005-05-21	13:06:46	2005-05-21	13:18:12	timestamp = ppProductionMinBias_FF
'1035'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6141026',	 last => '6141033',	 list => '',  beginTime => '20050521.131812'}, # 	2005-05-21	13:18:12	2005-05-21	19:26:38	timestamp = ppProduction_FF
'1036'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6141046',	 last => '6141048',	 list => '',  beginTime => '20050521.192638'}, # 	2005-05-21	19:26:38	2005-05-21	20:20:44
'1037'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6141050',	 last => '6141053',	 list => '',  beginTime => '20050521.202044'}, # 	2005-05-21	20:20:44	2005-05-21	21:28:42
'1038'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6141055',	 last => '6141055',	 list => '',  beginTime => '20050521.212842'}, # 	2005-05-21	21:28:42	2005-05-21	21:49:28	timestamp = ppProductionMinBias_FF
'1039'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6141058',	 last => '6141059',	 list => '',  beginTime => '20050521.214928'}, # 	2005-05-21	21:49:28	2005-05-21	22:35:19	timestamp = ppProduction_FF
'1040'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6141061',	 last => '6141066',	 list => '',  beginTime => '20050521.223519'}, # 	2005-05-21	22:35:19	2005-05-22	00:47:35
'1041'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6141068',	 last => '6141068',	 list => '',  beginTime => '20050522.004735'}, # 	2005-05-22	00:47:35	2005-05-22	01:08:14
'1042'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6141069',	 last => '6141069',	 list => '',  beginTime => '20050522.010814'}, # 	2005-05-22	01:08:14	2005-05-22	04:05:06	timestamp = ppProductionMinBias_FF
'1043'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142001',	 last => '6142008',	 list => '',  beginTime => '20050522.040506'}, # 	2005-05-22	04:05:06	2005-05-22	06:39:25	timestamp = ppProduction_FF
'1044'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142010',	 last => '6142018',	 list => '',  beginTime => '20050522.063925'}, # 	2005-05-22	06:39:25	2005-05-22	09:30:54
'1045'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6142019',	 last => '6142022',	 list => '',  beginTime => '20050522.093054'}, # 	2005-05-22	09:30:54	2005-05-22	10:27:14	timestamp = ppProductionMinBias_FF
'1046'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142023',	 last => '6142027',	 list => '',  beginTime => '20050522.102714'}, # 	2005-05-22	10:27:14	2005-05-22	14:36:08	timestamp = ppProduction_FF
'1047'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142034',	 last => '6142036',	 list => '',  beginTime => '20050522.143608'}, # 	2005-05-22	14:36:08	2005-05-22	14:50:37
'1048'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142038',	 last => '6142045',	 list => '',  beginTime => '20050522.145037'}, # 	2005-05-22	14:50:37	2005-05-22	17:05:56
'1049'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6142046',	 last => '6142046',	 list => '',  beginTime => '20050522.170556'}, # 	2005-05-22	17:05:56	2005-05-22	17:16:21	timestamp = ppProductionMinBias_FF
'1050'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142048',	 last => '6142057',	 list => '',  beginTime => '20050522.171621'}, # 	2005-05-22	17:16:21	2005-05-22	20:15:24	timestamp = ppProduction_FF
'1051'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142059',	 last => '6142059',	 list => '',  beginTime => '20050522.201524'}, # 	2005-05-22	20:15:24	2005-05-22	20:18:27
'1052'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6142060',	 last => '6142060',	 list => '',  beginTime => '20050522.201827'}, # 	2005-05-22	20:18:27	2005-05-22	20:26:45	timestamp = ppProductionMinBias_FF
'1053'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6142063',	 last => '6142064',	 list => '',  beginTime => '20050522.202645'}, # 	2005-05-22	20:26:45	2005-05-22	23:39:17
'1054'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142074',	 last => '6142074',	 list => '',  beginTime => '20050522.233917'}, # 	2005-05-22	23:39:17	2005-05-22	23:50:16	timestamp = ppProduction_FF
'1055'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142077',	 last => '6142084',	 list => '',  beginTime => '20050522.235016'}, # 	2005-05-22	23:50:16	2005-05-23	02:03:27
'1056'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6142085',	 last => '6142085',	 list => '',  beginTime => '20050523.020327'}, # 	2005-05-23	02:03:27	2005-05-23	02:15:24	timestamp = ppProductionMinBias_FF
'1057'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142087',	 last => '6142089',	 list => '',  beginTime => '20050523.021524'}, # 	2005-05-23	02:15:24	2005-05-23	03:15:45	timestamp = ppProduction_FF
'1058'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142093',	 last => '6142094',	 list => '',  beginTime => '20050523.031545'}, # 	2005-05-23	03:15:45	2005-05-23	04:00:11
'1059'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6142097',	 last => '6142097',	 list => '',  beginTime => '20050523.040011'}, # 	2005-05-23	04:00:11	2005-05-23	04:18:41
'1060'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6143001',	 last => '6143002',	 list => '',  beginTime => '20050523.041841'}, # 	2005-05-23	04:18:41	2005-05-23	07:55:52
'1061'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6143012',	 last => '6143019',	 list => '',  beginTime => '20050523.075552'}, # 	2005-05-23	07:55:52	2005-05-23	10:21:45
'1062'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6143021',	 last => '6143025',	 list => '',  beginTime => '20050523.102145'}, # 	2005-05-23	10:21:45	2005-05-23	12:00:41
'1063'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6143027',	 last => '6143027',	 list => '',  beginTime => '20050523.120041'}, # 	2005-05-23	12:00:41	2005-05-23	12:21:05
'1064'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6143028',	 last => '6143028',	 list => '',  beginTime => '20050523.122105'}, # 	2005-05-23	12:21:05	2005-05-23	13:13:17	timestamp = ppProductionMinBias_FF
'1065'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6143033',	 last => '6143033',	 list => '',  beginTime => '20050523.131317'}, # 	2005-05-23	13:13:17	2005-05-24	05:52:27
'1066'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6144009',	 last => '6144009',	 list => '',  beginTime => '20050524.055227'}, # 	2005-05-24	05:52:27	2005-05-24	06:49:17	timestamp = ppProduction_FF
'1067'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6144017',	 last => '6144017',	 list => '',  beginTime => '20050524.064917'}, # 	2005-05-24	06:49:17	2005-05-24	07:24:10
'1068'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6144019',	 last => '6144024',	 list => '',  beginTime => '20050524.072410'}, # 	2005-05-24	07:24:10	2005-05-24	10:08:35
'1069'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6144025',	 last => '6144025',	 list => '',  beginTime => '20050524.100835'}, # 	2005-05-24	10:08:35	2005-05-24	10:11:59	timestamp = ppProductionMinBias_FF
'1070'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6144026',	 last => '6144026',	 list => '',  beginTime => '20050524.101159'}, # 	2005-05-24	10:11:59	2005-05-24	10:31:34	timestamp = ppProduction_FF
'1071'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6144027',	 last => '6144029',	 list => '',  beginTime => '20050524.103134'}, # 	2005-05-24	10:31:34	2005-05-24	20:56:50	timestamp = ppProductionMinBias_FF
'1072'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6144051',	 last => '6144054',	 list => '',  beginTime => '20050524.205650'}, # 	2005-05-24	20:56:50	2005-05-24	23:01:42	timestamp = ppProduction_FF
'1073'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6144056',	 last => '6144056',	 list => '',  beginTime => '20050524.230142'}, # 	2005-05-24	23:01:42	2005-05-24	23:06:07	timestamp = ppProductionMinBias_FF
'1074'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6144057',	 last => '6144061',	 list => '',  beginTime => '20050524.230607'}, # 	2005-05-24	23:06:07	2005-05-25	01:22:50	timestamp = ppProduction_FF
'1075'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6144063',	 last => '6144063',	 list => '',  beginTime => '20050525.012250'}, # 	2005-05-25	01:22:50	2005-05-25	02:11:22
'1076'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6144066',	 last => '6144066',	 list => '',  beginTime => '20050525.021122'}, # 	2005-05-25	02:11:22	2005-05-25	02:38:46
'1077'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6144067',	 last => '6144067',	 list => '',  beginTime => '20050525.023846'}, # 	2005-05-25	02:38:46	2005-05-25	07:41:24	timestamp = ppProductionMinBias_FF
'1078'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6145011',	 last => '6145012',	 list => '',  beginTime => '20050525.074124'}, # 	2005-05-25	07:41:24	2005-05-25	07:58:16
'1079'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145013',	 last => '6145013',	 list => '',  beginTime => '20050525.075816'}, # 	2005-05-25	07:58:16	2005-05-25	08:28:39	timestamp = ppProduction_FF
'1080'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145015',	 last => '6145015',	 list => '',  beginTime => '20050525.082839'}, # 	2005-05-25	08:28:39	2005-05-25	09:02:17
'1081'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6145017',	 last => '6145017',	 list => '',  beginTime => '20050525.090217'}, # 	2005-05-25	09:02:17	2005-05-25	09:06:26	timestamp = ppProductionMinBias_FF
'1082'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145018',	 last => '6145021',	 list => '',  beginTime => '20050525.090626'}, # 	2005-05-25	09:06:26	2005-05-25	10:56:33	timestamp = ppProduction_FF
'1083'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145023',	 last => '6145023',	 list => '',  beginTime => '20050525.105633'}, # 	2005-05-25	10:56:33	2005-05-25	11:28:02
'1084'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145025',	 last => '6145025',	 list => '',  beginTime => '20050525.112802'}, # 	2005-05-25	11:28:02	2005-05-25	12:05:10
'1085'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145027',	 last => '6145028',	 list => '',  beginTime => '20050525.120510'}, # 	2005-05-25	12:05:10	2005-05-25	17:24:17
'1086'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145037',	 last => '6145037',	 list => '',  beginTime => '20050525.172417'}, # 	2005-05-25	17:24:17	2005-05-25	17:30:37
'1087'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6145039',	 last => '6145039',	 list => '',  beginTime => '20050525.173037'}, # 	2005-05-25	17:30:37	2005-05-25	17:33:53	timestamp = ppProductionMinBias_FF
'1088'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145040',	 last => '6145040',	 list => '',  beginTime => '20050525.173353'}, # 	2005-05-25	17:33:53	2005-05-25	17:55:36	timestamp = ppProduction_FF
'1089'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6145041',	 last => '6145041',	 list => '',  beginTime => '20050525.175536'}, # 	2005-05-25	17:55:36	2005-05-25	18:38:23	timestamp = ppProductionMinBias_FF
'1090'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145044',	 last => '6145045',	 list => '',  beginTime => '20050525.183823'}, # 	2005-05-25	18:38:23	2005-05-25	19:43:36	timestamp = ppProduction_FF
'1091'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6145048',	 last => '6145048',	 list => '',  beginTime => '20050525.194336'}, # 	2005-05-25	19:43:36	2005-05-25	19:47:25	timestamp = ppProductionMinBias_FF
'1092'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145049',	 last => '6145049',	 list => '',  beginTime => '20050525.194725'}, # 	2005-05-25	19:47:25	2005-05-25	20:12:37	timestamp = ppProduction_FF
'1093'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145053',	 last => '6145058',	 list => '',  beginTime => '20050525.201237'}, # 	2005-05-25	20:12:37	2005-05-26	02:39:31
'1094'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6145068',	 last => '6145068',	 list => '',  beginTime => '20050526.023931'}, # 	2005-05-26	02:39:31	2005-05-26	08:43:59
'1095'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6146017',	 last => '6146021',	 list => '',  beginTime => '20050526.084359'}, # 	2005-05-26	08:43:59	2005-05-26	10:19:18
'1096'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6146023',	 last => '6146023',	 list => '',  beginTime => '20050526.101918'}, # 	2005-05-26	10:19:18	2005-05-26	10:23:29	timestamp = ppProductionMinBias_FF
'1097'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6146024',	 last => '6146025',	 list => '',  beginTime => '20050526.102329'}, # 	2005-05-26	10:23:29	2005-05-26	22:41:43	timestamp = ppProduction_FF
'1098'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6146044',	 last => '6146044',	 list => '',  beginTime => '20050526.224143'}, # 	2005-05-26	22:41:43	2005-05-27	04:20:17
'1099'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6147001',	 last => '6147001',	 list => '',  beginTime => '20050527.042017'}, # 	2005-05-27	04:20:17	2005-05-27	17:53:57	timestamp = ppProductionMinBias_FF
'1100'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6147008',	 last => '6147009',	 list => '',  beginTime => '20050527.175357'}, # 	2005-05-27	17:53:57	2005-05-27	20:31:39
'1101'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6147024',	 last => '6147025',	 list => '',  beginTime => '20050527.203139'}, # 	2005-05-27	20:31:39	2005-05-27	21:49:52
'1102'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6147029',	 last => '6147030',	 list => '',  beginTime => '20050527.214952'}, # 	2005-05-27	21:49:52	2005-05-27	22:44:28	timestamp = ppProduction_FF
'1103'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6147031',	 last => '6147031',	 list => '',  beginTime => '20050527.224428'}, # 	2005-05-27	22:44:28	2005-05-28	05:33:25	timestamp = ppProductionMinBias_FF
'1104'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6148008',	 last => '6148014',	 list => '',  beginTime => '20050528.053325'}, # 	2005-05-28	05:33:25	2005-05-28	08:01:00	timestamp = ppProduction_FF
'1105'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6148016',	 last => '6148016',	 list => '',  beginTime => '20050528.080100'}, # 	2005-05-28	08:01:00	2005-05-28	08:07:54	timestamp = ppProductionMinBias_FF
'1106'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6148017',	 last => '6148020',	 list => '',  beginTime => '20050528.080754'}, # 	2005-05-28	08:07:54	2005-05-28	09:33:53	timestamp = ppProduction_FF
'1107'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6148021',	 last => '6148022',	 list => '',  beginTime => '20050528.093353'}, # 	2005-05-28	09:33:53	2005-05-28	10:35:00	timestamp = ppProductionMinBias_FF
'1108'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6148024',	 last => '6148024',	 list => '',  beginTime => '20050528.103500'}, # 	2005-05-28	10:35:00	2005-05-28	11:27:25
'1109'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6148027',	 last => '6148027',	 list => '',  beginTime => '20050528.112725'}, # 	2005-05-28	11:27:25	2005-05-28	15:17:22
'1110'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6148037',	 last => '6148037',	 list => '',  beginTime => '20050528.151722'}, # 	2005-05-28	15:17:22	2005-05-28	15:29:27
'1111'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6148039',	 last => '6148041',	 list => '',  beginTime => '20050528.152927'}, # 	2005-05-28	15:29:27	2005-05-29	00:17:15
'1112'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6148054',	 last => '6148060',	 list => '',  beginTime => '20050529.001715'}, # 	2005-05-29	00:17:15	2005-05-29	03:11:47	timestamp = ppProduction_FF
'1113'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6148062',	 last => '6148062',	 list => '',  beginTime => '20050529.031147'}, # 	2005-05-29	03:11:47	2005-05-29	03:16:23	timestamp = ppProductionMinBias_FF
'1114'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6148063',	 last => '6148064',	 list => '',  beginTime => '20050529.031623'}, # 	2005-05-29	03:16:23	2005-05-29	04:12:41	timestamp = ppProduction_FF
'1115'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6149003',	 last => '6149005',	 list => '',  beginTime => '20050529.041241'}, # 	2005-05-29	04:12:41	2005-05-29	05:31:40
'1116'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6149007',	 last => '6149007',	 list => '',  beginTime => '20050529.053140'}, # 	2005-05-29	05:31:40	2005-05-29	06:00:47
'1117'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6149009',	 last => '6149009',	 list => '',  beginTime => '20050529.060047'}, # 	2005-05-29	06:00:47	2005-05-29	08:23:52	timestamp = ppProductionMinBias_FF
'1118'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6149016',	 last => '6149021',	 list => '',  beginTime => '20050529.082352'}, # 	2005-05-29	08:23:52	2005-05-29	10:54:18	timestamp = ppProduction_FF
'1119'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6149023',	 last => '6149023',	 list => '',  beginTime => '20050529.105418'}, # 	2005-05-29	10:54:18	2005-05-29	10:58:26	timestamp = ppProductionMinBias_FF
'1120'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6149024',	 last => '6149026',	 list => '',  beginTime => '20050529.105826'}, # 	2005-05-29	10:58:26	2005-05-29	12:14:04	timestamp = ppProduction_FF
'1121'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6149029',	 last => '6149032',	 list => '',  beginTime => '20050529.121404'}, # 	2005-05-29	12:14:04	2005-05-29	14:03:30
'1122'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6149035',	 last => '6149036',	 list => '',  beginTime => '20050529.140330'}, # 	2005-05-29	14:03:30	2005-05-29	21:20:13
'1123'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6149047',	 last => '6149048',	 list => '',  beginTime => '20050529.212013'}, # 	2005-05-29	21:20:13	2005-05-29	22:07:42
'1124'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6149050',	 last => '6149052',	 list => '',  beginTime => '20050529.220742'}, # 	2005-05-29	22:07:42	2005-05-29	23:27:58
'1125'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6149054',	 last => '6149057',	 list => '',  beginTime => '20050529.232758'}, # 	2005-05-29	23:27:58	2005-05-30	04:14:59	timestamp = ppProductionMinBias_FF
'1126'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6150005',	 last => '6150006',	 list => '',  beginTime => '20050530.041459'}, # 	2005-05-30	04:14:59	2005-05-30	07:40:07	timestamp = ppProduction_FF
'1127'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6150013',	 last => '6150019',	 list => '',  beginTime => '20050530.074007'}, # 	2005-05-30	07:40:07	2005-05-30	09:54:39
'1128'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6150021',	 last => '6150021',	 list => '',  beginTime => '20050530.095439'}, # 	2005-05-30	09:54:39	2005-05-30	09:58:34	timestamp = ppProductionMinBias_FF
'1129'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6150022',	 last => '6150029',	 list => '',  beginTime => '20050530.095834'}, # 	2005-05-30	09:58:34	2005-05-31	03:20:47	timestamp = ppProduction_FF
'1130'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6150037',	 last => '6150038',	 list => '',  beginTime => '20050531.032047'}, # 	2005-05-31	03:20:47	2005-05-31	04:12:04
'1131'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6151001',	 last => '6151002',	 list => '',  beginTime => '20050531.041204'}, # 	2005-05-31	04:12:04	2005-05-31	05:16:21
'1132'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6151005',	 last => '6151005',	 list => '',  beginTime => '20050531.051621'}, # 	2005-05-31	05:16:21	2005-05-31	05:53:09
'1133'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6151007',	 last => '6151007',	 list => '',  beginTime => '20050531.055309'}, # 	2005-05-31	05:53:09	2005-05-31	05:56:58	timestamp = ppProductionMinBias_FF
'1134'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6151008',	 last => '6151009',	 list => '',  beginTime => '20050531.055658'}, # 	2005-05-31	05:56:58	2005-05-31	06:50:27	timestamp = ppProduction_FF
'1135'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6151011',	 last => '6151015',	 list => '',  beginTime => '20050531.065027'}, # 	2005-05-31	06:50:27	2005-05-31	08:52:25
'1136'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6151017',	 last => '6151024',	 list => '',  beginTime => '20050531.085225'}, # 	2005-05-31	08:52:25	2005-05-31	11:21:50
'1137'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6151025',	 last => '6151025',	 list => '',  beginTime => '20050531.112150'}, # 	2005-05-31	11:21:50	2005-05-31	11:27:50	timestamp = ppProductionMinBias_FF
'1138'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6151026',	 last => '6151026',	 list => '',  beginTime => '20050531.112750'}, # 	2005-05-31	11:27:50	2005-05-31	12:00:43	timestamp = ppProduction_FF
'1139'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6151028',	 last => '6151029',	 list => '',  beginTime => '20050531.120043'}, # 	2005-05-31	12:00:43	2005-05-31	12:42:56
'1140'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6151030',	 last => '6151030',	 list => '',  beginTime => '20050531.124256'}, # 	2005-05-31	12:42:56	2005-06-02	21:15:37	timestamp = ppProductionMinBias_FF
'1141'=> {trig=>'pp400MinBias',          	field => 'FF',	first=> '6153019',	 last => '6153021',	 list => '',  beginTime => '20050602.211537'}, # 	2005-06-02	21:15:37	2005-06-03	04:22:45	timestamp = pp400MinBias_FF
'1142'=> {trig=>'pp400Production',       	field => 'FF',	first=> '6154006',	 last => '6154006',	 list => '',  beginTime => '20050603.042245'}, # 	2005-06-03	04:22:45	2005-06-03	04:46:38	timestamp = pp400Production_FF
'1143'=> {trig=>'pp400Production',       	field => 'FF',	first=> '6154008',	 last => '6154011',	 list => '',  beginTime => '20050603.044638'}, # 	2005-06-03	04:46:38	2005-06-03	06:16:21
'1144'=> {trig=>'pp400MinBias',          	field => 'FF',	first=> '6154013',	 last => '6154013',	 list => '',  beginTime => '20050603.061621'}, # 	2005-06-03	06:16:21	2005-06-03	09:37:45	timestamp = pp400MinBias_FF
'1145'=> {trig=>'pp400Production',       	field => 'FF',	first=> '6154024',	 last => '6154025',	 list => '',  beginTime => '20050603.093745'}, # 	2005-06-03	09:37:45	2005-06-03	10:10:38	timestamp = pp400Production_FF
'1146'=> {trig=>'pp400Production',       	field => 'FF',	first=> '6154028',	 last => '6154028',	 list => '',  beginTime => '20050603.101038'}, # 	2005-06-03	10:10:38	2005-06-03	10:36:08
'1147'=> {trig=>'pp400Production',       	field => 'FF',	first=> '6154030',	 last => '6154032',	 list => '',  beginTime => '20050603.103608'}, # 	2005-06-03	10:36:08	2005-06-03	11:51:17
'1148'=> {trig=>'pp400MinBias',          	field => 'FF',	first=> '6154034',	 last => '6154034',	 list => '',  beginTime => '20050603.115117'}, # 	2005-06-03	11:51:17	2005-06-03	11:54:15	timestamp = pp400MinBias_FF
'1149'=> {trig=>'pp400Production',       	field => 'FF',	first=> '6154035',	 last => '6154041',	 list => '',  beginTime => '20050603.115415'}, # 	2005-06-03	11:54:15	2005-06-03	15:00:06	timestamp = pp400Production_FF
'1150'=> {trig=>'pp400Production',       	field => 'FF',	first=> '6154045',	 last => '6154045',	 list => '',  beginTime => '20050603.150006'}, # 	2005-06-03	15:00:06	2005-06-04	03:44:39
'1151'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6154055',	 last => '6154055',	 list => '',  beginTime => '20050604.034439'}, # 	2005-06-04	03:44:39	2005-06-04	04:09:28	timestamp = ppProduction_FF
'1152'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6155001',	 last => '6155001',	 list => '',  beginTime => '20050604.040928'}, # 	2005-06-04	04:09:28	2005-06-05	03:09:41
'1153'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6155026',	 last => '6155027',	 list => '',  beginTime => '20050605.030941'}, # 	2005-06-05	03:09:41	2005-06-05	03:46:33	timestamp = ppProductionMinBias_FF
'1154'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6155029',	 last => '6155029',	 list => '',  beginTime => '20050605.034633'}, # 	2005-06-05	03:46:33	2005-06-05	04:13:03
'1155'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6156004',	 last => '6156004',	 list => '',  beginTime => '20050605.041303'}, # 	2005-06-05	04:13:03	2005-06-05	05:09:21	timestamp = ppProduction_FF
'1156'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6156010',	 last => '6156016',	 list => '',  beginTime => '20050605.050921'}, # 	2005-06-05	05:09:21	2005-06-05	08:08:09
'1157'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6156019',	 last => '6156019',	 list => '',  beginTime => '20050605.080809'}, # 	2005-06-05	08:08:09	2005-06-05	10:19:39
'1158'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6156026',	 last => '6156030',	 list => '',  beginTime => '20050605.101939'}, # 	2005-06-05	10:19:39	2005-06-05	12:32:28
'1159'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6156031',	 last => '6156031',	 list => '',  beginTime => '20050605.123228'}, # 	2005-06-05	12:32:28	2005-06-05	12:55:07	timestamp = ppProductionMinBias_FF
'1160'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6156034',	 last => '6156034',	 list => '',  beginTime => '20050605.125507'}, # 	2005-06-05	12:55:07	2005-06-05	13:13:08	timestamp = ppProduction_FF
'1161'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6156036',	 last => '6156036',	 list => '',  beginTime => '20050605.131308'}, # 	2005-06-05	13:13:08	2005-06-05	14:31:07
'1162'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6156042',	 last => '6156042',	 list => '',  beginTime => '20050605.143107'}, # 	2005-06-05	14:31:07	2005-06-05	14:41:15	timestamp = ppProduction_FHF
'1163'=> {trig=>'ppProductionMinBias',   	field => 'FHF',	first=> '6156044',	 last => '6156045',	 list => '',  beginTime => '20050605.144115'}, # 	2005-06-05	14:41:15	2005-06-05	21:46:41	timestamp = ppProductionMinBias_FHF
'1164'=> {trig=>'ppProductionMinBias',   	field => 'FHF',	first=> '6156052',	 last => '6156053',	 list => '',  beginTime => '20050605.214641'}, # 	2005-06-05	21:46:41	2005-06-05	22:28:18
'1165'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6156054',	 last => '6156054',	 list => '',  beginTime => '20050605.222818'}, # 	2005-06-05	22:28:18	2005-06-05	23:06:43	timestamp = ppProduction_FHF
'1166'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6156060',	 last => '6156061',	 list => '',  beginTime => '20050605.230643'}, # 	2005-06-05	23:06:43	2005-06-05	23:33:14
'1167'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6156063',	 last => '6156064',	 list => '',  beginTime => '20050605.233314'}, # 	2005-06-05	23:33:14	2005-06-06	00:05:11
'1168'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6156066',	 last => '6156066',	 list => '',  beginTime => '20050606.000511'}, # 	2005-06-06	00:05:11	2005-06-06	00:37:58
'1169'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6156069',	 last => '6156069',	 list => '',  beginTime => '20050606.003758'}, # 	2005-06-06	00:37:58	2005-06-06	01:00:57
'1170'=> {trig=>'ppProductionMinBias',   	field => 'FHF',	first=> '6156070',	 last => '6156070',	 list => '',  beginTime => '20050606.010057'}, # 	2005-06-06	01:00:57	2005-06-06	01:26:29	timestamp = ppProductionMinBias_FHF
'1171'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6156071',	 last => '6156073',	 list => '',  beginTime => '20050606.012629'}, # 	2005-06-06	01:26:29	2005-06-06	02:56:58	timestamp = ppProduction_FHF
'1172'=> {trig=>'ppProductionMinBias',   	field => 'FHF',	first=> '6156074',	 last => '6156074',	 list => '',  beginTime => '20050606.025658'}, # 	2005-06-06	02:56:58	2005-06-06	03:32:43	timestamp = ppProductionMinBias_FHF
'1173'=> {trig=>'ppProductionMinBias',   	field => 'FHF',	first=> '6156076',	 last => '6156077',	 list => '',  beginTime => '20050606.033243'}, # 	2005-06-06	03:32:43	2005-06-06	06:47:27
'1174'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6157005',	 last => '6157006',	 list => '',  beginTime => '20050606.064727'}, # 	2005-06-06	06:47:27	2005-06-06	07:24:04	timestamp = ppProduction_FHF
'1175'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6157009',	 last => '6157012',	 list => '',  beginTime => '20050606.072404'}, # 	2005-06-06	07:24:04	2005-06-06	09:26:30
'1176'=> {trig=>'ppProductionMinBias',   	field => 'FHF',	first=> '6157014',	 last => '6157014',	 list => '',  beginTime => '20050606.092630'}, # 	2005-06-06	09:26:30	2005-06-06	09:29:35	timestamp = ppProductionMinBias_FHF
'1177'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6157015',	 last => '6157020',	 list => '',  beginTime => '20050606.092935'}, # 	2005-06-06	09:29:35	2005-06-06	11:42:53	timestamp = ppProduction_FHF
'1178'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6157022',	 last => '6157023',	 list => '',  beginTime => '20050606.114253'}, # 	2005-06-06	11:42:53	2005-06-06	12:30:50
'1179'=> {trig=>'ppProductionMinBias',   	field => 'FHF',	first=> '6157026',	 last => '6157026',	 list => '',  beginTime => '20050606.123050'}, # 	2005-06-06	12:30:50	2005-06-06	12:33:39	timestamp = ppProductionMinBias_FHF
'1180'=> {trig=>'ppProduction',          	field => 'FHF',	first=> '6157027',	 last => '6157027',	 list => '',  beginTime => '20050606.123339'}, # 	2005-06-06	12:33:39	2005-06-07	01:51:26	timestamp = ppProduction_FHF
'1181'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6157050',	 last => '6157051',	 list => '',  beginTime => '20050607.015126'}, # 	2005-06-07	01:51:26	2005-06-07	02:46:08	timestamp = ppProduction_FF
'1182'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6157058',	 last => '6157058',	 list => '',  beginTime => '20050607.024608'}, # 	2005-06-07	02:46:08	2005-06-07	03:02:15	timestamp = ppProductionMinBias_FF
'1183'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6157062',	 last => '6157063',	 list => '',  beginTime => '20050607.030215'}, # 	2005-06-07	03:02:15	2005-06-07	04:30:12
'1184'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6158009',	 last => '6158010',	 list => '',  beginTime => '20050607.043012'}, # 	2005-06-07	04:30:12	2005-06-07	04:47:23
'1185'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158011',	 last => '6158011',	 list => '',  beginTime => '20050607.044723'}, # 	2005-06-07	04:47:23	2005-06-07	04:59:02	timestamp = ppProduction_FF
'1186'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158013',	 last => '6158015',	 list => '',  beginTime => '20050607.045902'}, # 	2005-06-07	04:59:02	2005-06-07	06:03:20
'1187'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158017',	 last => '6158017',	 list => '',  beginTime => '20050607.060320'}, # 	2005-06-07	06:03:20	2005-06-07	06:34:21
'1188'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158019',	 last => '6158020',	 list => '',  beginTime => '20050607.063421'}, # 	2005-06-07	06:34:21	2005-06-07	07:24:15
'1189'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6158023',	 last => '6158024',	 list => '',  beginTime => '20050607.072415'}, # 	2005-06-07	07:24:15	2005-06-07	07:42:36	timestamp = ppProductionMinBias_FF
'1190'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158025',	 last => '6158025',	 list => '',  beginTime => '20050607.074236'}, # 	2005-06-07	07:42:36	2005-06-07	10:46:32	timestamp = ppProduction_FF
'1191'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158041',	 last => '6158041',	 list => '',  beginTime => '20050607.104632'}, # 	2005-06-07	10:46:32	2005-06-07	16:10:25
'1192'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158055',	 last => '6158055',	 list => '',  beginTime => '20050607.161025'}, # 	2005-06-07	16:10:25	2005-06-07	16:19:53
'1193'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158057',	 last => '6158057',	 list => '',  beginTime => '20050607.161953'}, # 	2005-06-07	16:19:53	2005-06-07	16:50:39
'1194'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158059',	 last => '6158063',	 list => '',  beginTime => '20050607.165039'}, # 	2005-06-07	16:50:39	2005-06-07	22:16:51
'1195'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158075',	 last => '6158077',	 list => '',  beginTime => '20050607.221651'}, # 	2005-06-07	22:16:51	2005-06-07	23:13:13
'1196'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158081',	 last => '6158082',	 list => '',  beginTime => '20050607.231313'}, # 	2005-06-07	23:13:13	2005-06-07	23:39:26
'1197'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6158084',	 last => '6158086',	 list => '',  beginTime => '20050607.233926'}, # 	2005-06-07	23:39:26	2005-06-09	02:30:21
'1198'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6159068',	 last => '6159070',	 list => '',  beginTime => '20050609.023021'}, # 	2005-06-09	02:30:21	2005-06-09	02:52:25
'1199'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6159072',	 last => '6159074',	 list => '',  beginTime => '20050609.025225'}, # 	2005-06-09	02:52:25	2005-06-09	04:02:16
'1200'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160001',	 last => '6160001',	 list => '',  beginTime => '20050609.040216'}, # 	2005-06-09	04:02:16	2005-06-09	04:38:03
'1201'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6160003',	 last => '6160003',	 list => '',  beginTime => '20050609.043803'}, # 	2005-06-09	04:38:03	2005-06-09	04:43:49	timestamp = ppProductionMinBias_FF
'1202'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160007',	 last => '6160014',	 list => '',  beginTime => '20050609.044349'}, # 	2005-06-09	04:43:49	2005-06-09	07:42:17	timestamp = ppProduction_FF
'1203'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160016',	 last => '6160016',	 list => '',  beginTime => '20050609.074217'}, # 	2005-06-09	07:42:17	2005-06-09	08:04:57
'1204'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6160017',	 last => '6160017',	 list => '',  beginTime => '20050609.080457'}, # 	2005-06-09	08:04:57	2005-06-09	10:17:17	timestamp = ppProductionMinBias_FF
'1205'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160021',	 last => '6160021',	 list => '',  beginTime => '20050609.101717'}, # 	2005-06-09	10:17:17	2005-06-09	10:44:35	timestamp = ppProduction_FF
'1206'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160024',	 last => '6160025',	 list => '',  beginTime => '20050609.104435'}, # 	2005-06-09	10:44:35	2005-06-09	11:01:44
'1207'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160027',	 last => '6160031',	 list => '',  beginTime => '20050609.110144'}, # 	2005-06-09	11:01:44	2005-06-09	15:24:48
'1208'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160039',	 last => '6160042',	 list => '',  beginTime => '20050609.152448'}, # 	2005-06-09	15:24:48	2005-06-09	16:53:03
'1209'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160044',	 last => '6160044',	 list => '',  beginTime => '20050609.165303'}, # 	2005-06-09	16:53:03	2005-06-09	17:06:20
'1210'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160047',	 last => '6160048',	 list => '',  beginTime => '20050609.170620'}, # 	2005-06-09	17:06:20	2005-06-09	17:44:51
'1211'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160050',	 last => '6160050',	 list => '',  beginTime => '20050609.174451'}, # 	2005-06-09	17:44:51	2005-06-09	18:00:22
'1212'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6160053',	 last => '6160053',	 list => '',  beginTime => '20050609.180022'}, # 	2005-06-09	18:00:22	2005-06-09	18:03:49	timestamp = ppProductionMinBias_FF
'1213'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160054',	 last => '6160054',	 list => '',  beginTime => '20050609.180349'}, # 	2005-06-09	18:03:49	2005-06-09	18:34:26	timestamp = ppProduction_FF
'1214'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160056',	 last => '6160058',	 list => '',  beginTime => '20050609.183426'}, # 	2005-06-09	18:34:26	2005-06-09	19:49:53
'1215'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160061',	 last => '6160062',	 list => '',  beginTime => '20050609.194953'}, # 	2005-06-09	19:49:53	2005-06-09	20:57:46
'1216'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160064',	 last => '6160066',	 list => '',  beginTime => '20050609.205746'}, # 	2005-06-09	20:57:46	2005-06-09	21:15:00
'1217'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6160067',	 last => '6160067',	 list => '',  beginTime => '20050609.211500'}, # 	2005-06-09	21:15:00	2005-06-09	21:21:21	timestamp = ppProductionMinBias_FF
'1218'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160068',	 last => '6160072',	 list => '',  beginTime => '20050609.212121'}, # 	2005-06-09	21:21:21	2005-06-10	03:15:36	timestamp = ppProduction_FF
'1219'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6160082',	 last => '6160083',	 list => '',  beginTime => '20050610.031536'}, # 	2005-06-10	03:15:36	2005-06-10	04:05:47
'1220'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161001',	 last => '6161001',	 list => '',  beginTime => '20050610.040547'}, # 	2005-06-10	04:05:47	2005-06-10	04:33:08
'1221'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6161002',	 last => '6161003',	 list => '',  beginTime => '20050610.043308'}, # 	2005-06-10	04:33:08	2005-06-10	04:41:51	timestamp = ppProductionMinBias_FF
'1222'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161004',	 last => '6161004',	 list => '',  beginTime => '20050610.044151'}, # 	2005-06-10	04:41:51	2005-06-10	05:02:21	timestamp = ppProduction_FF
'1223'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161006',	 last => '6161007',	 list => '',  beginTime => '20050610.050221'}, # 	2005-06-10	05:02:21	2005-06-10	05:45:25
'1224'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6161009',	 last => '6161009',	 list => '',  beginTime => '20050610.054525'}, # 	2005-06-10	05:45:25	2005-06-10	14:05:46	timestamp = ppProductionMinBias_FF
'1225'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161035',	 last => '6161035',	 list => '',  beginTime => '20050610.140546'}, # 	2005-06-10	14:05:46	2005-06-10	14:38:37	timestamp = ppProduction_FF
'1226'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161038',	 last => '6161038',	 list => '',  beginTime => '20050610.143837'}, # 	2005-06-10	14:38:37	2005-06-10	14:59:15
'1227'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161041',	 last => '6161044',	 list => '',  beginTime => '20050610.145915'}, # 	2005-06-10	14:59:15	2005-06-10	15:51:06
'1228'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161046',	 last => '6161047',	 list => '',  beginTime => '20050610.155106'}, # 	2005-06-10	15:51:06	2005-06-10	16:55:15
'1229'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6161049',	 last => '6161049',	 list => '',  beginTime => '20050610.165515'}, # 	2005-06-10	16:55:15	2005-06-10	16:59:11	timestamp = ppProductionMinBias_FF
'1230'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161050',	 last => '6161050',	 list => '',  beginTime => '20050610.165911'}, # 	2005-06-10	16:59:11	2005-06-10	22:46:19	timestamp = ppProduction_FF
'1231'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6161075',	 last => '6161075',	 list => '',  beginTime => '20050610.224619'}, # 	2005-06-10	22:46:19	2005-06-10	23:21:29	timestamp = ppProductionMinBias_FF
'1232'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6161082',	 last => '6161082',	 list => '',  beginTime => '20050610.232129'}, # 	2005-06-10	23:21:29	2005-06-10	23:36:52
'1233'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6161088',	 last => '6161089',	 list => '',  beginTime => '20050610.233652'}, # 	2005-06-10	23:36:52	2005-06-10	23:43:34
'1234'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161091',	 last => '6161094',	 list => '',  beginTime => '20050610.234334'}, # 	2005-06-10	23:43:34	2005-06-11	00:59:46	timestamp = ppProduction_FF
'1235'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6161096',	 last => '6161096',	 list => '',  beginTime => '20050611.005946'}, # 	2005-06-11	00:59:46	2005-06-11	01:02:58	timestamp = ppProductionMinBias_FF
'1236'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161097',	 last => '6161102',	 list => '',  beginTime => '20050611.010258'}, # 	2005-06-11	01:02:58	2005-06-11	03:30:20	timestamp = ppProduction_FF
'1237'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6161104',	 last => '6161105',	 list => '',  beginTime => '20050611.033020'}, # 	2005-06-11	03:30:20	2005-06-11	04:09:30
'1238'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6162001',	 last => '6162001',	 list => '',  beginTime => '20050611.040930'}, # 	2005-06-11	04:09:30	2005-06-11	04:23:10	timestamp = ppProductionMinBias_FF
'1239'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6162005',	 last => '6162005',	 list => '',  beginTime => '20050611.042310'}, # 	2005-06-11	04:23:10	2005-06-11	04:43:28	timestamp = ppProduction_FF
'1240'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6162007',	 last => '6162007',	 list => '',  beginTime => '20050611.044328'}, # 	2005-06-11	04:43:28	2005-06-11	07:36:28
'1241'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6162014',	 last => '6162014',	 list => '',  beginTime => '20050611.073628'}, # 	2005-06-11	07:36:28	2005-06-11	10:28:09
'1242'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6162027',	 last => '6162032',	 list => '',  beginTime => '20050611.102809'}, # 	2005-06-11	10:28:09	2005-06-11	12:54:05
'1243'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6162037',	 last => '6162037',	 list => '',  beginTime => '20050611.125405'}, # 	2005-06-11	12:54:05	2005-06-11	13:02:44	timestamp = ppProductionMinBias_FF
'1244'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6162039',	 last => '6162046',	 list => '',  beginTime => '20050611.130244'}, # 	2005-06-11	13:02:44	2005-06-11	21:19:35	timestamp = ppProduction_FF
'1245'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6162056',	 last => '6162058',	 list => '',  beginTime => '20050611.211935'}, # 	2005-06-11	21:19:35	2005-06-11	22:28:39
'1246'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6162061',	 last => '6162064',	 list => '',  beginTime => '20050611.222839'}, # 	2005-06-11	22:28:39	2005-06-12	00:13:29
'1247'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6162067',	 last => '6162067',	 list => '',  beginTime => '20050612.001329'}, # 	2005-06-12	00:13:29	2005-06-12	00:17:06	timestamp = ppProductionMinBias_FF
'1248'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6162068',	 last => '6162073',	 list => '',  beginTime => '20050612.001706'}, # 	2005-06-12	00:17:06	2005-06-12	02:13:38	timestamp = ppProduction_FF
'1249'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6162075',	 last => '6162076',	 list => '',  beginTime => '20050612.021338'}, # 	2005-06-12	02:13:38	2005-06-12	10:25:53
'1250'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163010',	 last => '6163010',	 list => '',  beginTime => '20050612.102553'}, # 	2005-06-12	10:25:53	2005-06-12	10:38:57
'1251'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163012',	 last => '6163018',	 list => '',  beginTime => '20050612.103857'}, # 	2005-06-12	10:38:57	2005-06-12	13:25:56
'1252'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6163020',	 last => '6163020',	 list => '',  beginTime => '20050612.132556'}, # 	2005-06-12	13:25:56	2005-06-12	13:31:05	timestamp = ppProductionMinBias_FF
'1253'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163021',	 last => '6163024',	 list => '',  beginTime => '20050612.133105'}, # 	2005-06-12	13:31:05	2005-06-12	15:14:02	timestamp = ppProduction_FF
'1254'=> {trig=>'ppProduction',          	field => 'ZF',	first=> '6163025',	 last => '6163025',	 list => '',  beginTime => '20050612.151402'}, # 	2005-06-12	15:14:02	2005-06-12	15:14:02	timestamp = ppProduction_ZF
'1255'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163025',	 last => '6163025',	 list => '',  beginTime => '20050612.151402'}, # 	2005-06-12	15:14:02	2005-06-12	22:37:51	timestamp = ppProduction_FF
'1256'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6163035',	 last => '6163035',	 list => '',  beginTime => '20050612.223751'}, # 	2005-06-12	22:37:51	2005-06-12	22:46:50	timestamp = ppProductionMinBias_FF
'1257'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6163037',	 last => '6163037',	 list => '',  beginTime => '20050612.224650'}, # 	2005-06-12	22:46:50	2005-06-12	22:52:55
'1258'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163038',	 last => '6163041',	 list => '',  beginTime => '20050612.225255'}, # 	2005-06-12	22:52:55	2005-06-13	00:00:31	timestamp = ppProduction_FF
'1259'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163043',	 last => '6163045',	 list => '',  beginTime => '20050613.000031'}, # 	2005-06-13	00:00:31	2005-06-13	01:11:34
'1260'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6163047',	 last => '6163047',	 list => '',  beginTime => '20050613.011134'}, # 	2005-06-13	01:11:34	2005-06-13	01:14:39	timestamp = ppProductionMinBias_FF
'1261'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163048',	 last => '6163048',	 list => '',  beginTime => '20050613.011439'}, # 	2005-06-13	01:14:39	2005-06-13	01:31:45	timestamp = ppProduction_FF
'1262'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163050',	 last => '6163051',	 list => '',  beginTime => '20050613.013145'}, # 	2005-06-13	01:31:45	2005-06-13	02:14:28
'1263'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163053',	 last => '6163054',	 list => '',  beginTime => '20050613.021428'}, # 	2005-06-13	02:14:28	2005-06-13	02:53:28
'1264'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6163056',	 last => '6163058',	 list => '',  beginTime => '20050613.025328'}, # 	2005-06-13	02:53:28	2005-06-13	04:10:48
'1265'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6164002',	 last => '6164004',	 list => '',  beginTime => '20050613.041048'}, # 	2005-06-13	04:10:48	2005-06-13	05:09:01
'1266'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6164005',	 last => '6164005',	 list => '',  beginTime => '20050613.050901'}, # 	2005-06-13	05:09:01	2005-06-13	10:18:03	timestamp = ppProductionMinBias_FF
'1267'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6164013',	 last => '6164013',	 list => '',  beginTime => '20050613.101803'}, # 	2005-06-13	10:18:03	2005-06-13	10:50:01	timestamp = ppProduction_FF
'1268'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6164016',	 last => '6164018',	 list => '',  beginTime => '20050613.105001'}, # 	2005-06-13	10:50:01	2005-06-13	12:21:40
'1269'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6164020',	 last => '6164021',	 list => '',  beginTime => '20050613.122140'}, # 	2005-06-13	12:21:40	2005-06-13	12:42:32	timestamp = ppProductionMinBias_FF
'1270'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6164022',	 last => '6164025',	 list => '',  beginTime => '20050613.124232'}, # 	2005-06-13	12:42:32	2005-06-14	19:52:38	timestamp = ppProduction_FF
'1271'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6165031',	 last => '6165035',	 list => '',  beginTime => '20050614.195238'}, # 	2005-06-14	19:52:38	2005-06-14	21:30:54	timestamp = ppTransProduction_FF
'1272'=> {trig=>'ppTransProductionMinBias',	field => 'FF',	first=> '6165042',	 last => '6165042',	 list => '',  beginTime => '20050614.213054'}, # 	2005-06-14	21:30:54	2005-06-14	21:37:28	timestamp = ppTransProductionMinBias_FF
'1273'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6165044',	 last => '6165044',	 list => '',  beginTime => '20050614.213728'}, # 	2005-06-14	21:37:28	2005-06-14	21:49:08	timestamp = ppTransProduction_FF
'1274'=> {trig=>'ppTransProductionMinBias',	field => 'FF',	first=> '6165045',	 last => '6165045',	 list => '',  beginTime => '20050614.214908'}, # 	2005-06-14	21:49:08	2005-06-14	21:55:36	timestamp = ppTransProductionMinBias_FF
'1275'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6165046',	 last => '6165047',	 list => '',  beginTime => '20050614.215536'}, # 	2005-06-14	21:55:36	2005-06-14	22:52:28	timestamp = ppTransProduction_FF
'1276'=> {trig=>'ppTransProductionMinBias',	field => 'FF',	first=> '6165049',	 last => '6165049',	 list => '',  beginTime => '20050614.225228'}, # 	2005-06-14	22:52:28	2005-06-14	23:20:53	timestamp = ppTransProductionMinBias_FF
'1277'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6165054',	 last => '6165054',	 list => '',  beginTime => '20050614.232053'}, # 	2005-06-14	23:20:53	2005-06-14	23:24:45	timestamp = ppProductionMinBias_FF
'1278'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6165055',	 last => '6165055',	 list => '',  beginTime => '20050614.232445'}, # 	2005-06-14	23:24:45	2005-06-14	23:46:42	timestamp = ppTransProduction_FF
'1279'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6165058',	 last => '6165059',	 list => '',  beginTime => '20050614.234642'}, # 	2005-06-14	23:46:42	2005-06-15	00:53:55
'1280'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6165063',	 last => '6165063',	 list => '',  beginTime => '20050615.005355'}, # 	2005-06-15	00:53:55	2005-06-15	08:53:28
'1281'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6166010',	 last => '6166010',	 list => '',  beginTime => '20050615.085328'}, # 	2005-06-15	08:53:28	2005-06-15	11:36:33	timestamp = ppProductionMinBias_FF
'1282'=> {trig=>'ppTransProductionMinBias',	field => 'FF',	first=> '6166026',	 last => '6166034',	 list => '',  beginTime => '20050615.113633'}, # 	2005-06-15	11:36:33	2005-06-15	13:51:57	timestamp = ppTransProductionMinBias_FF
'1283'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166045',	 last => '6166045',	 list => '',  beginTime => '20050615.135157'}, # 	2005-06-15	13:51:57	2005-06-15	14:40:48	timestamp = ppTransProduction_FF
'1284'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166051',	 last => '6166052',	 list => '',  beginTime => '20050615.144048'}, # 	2005-06-15	14:40:48	2005-06-15	15:12:48
'1285'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166054',	 last => '6166061',	 list => '',  beginTime => '20050615.151248'}, # 	2005-06-15	15:12:48	2005-06-15	17:11:53
'1286'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6166064',	 last => '6166064',	 list => '',  beginTime => '20050615.171153'}, # 	2005-06-15	17:11:53	2005-06-15	17:30:00	timestamp = ppProductionMinBias_FF
'1287'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166066',	 last => '6166067',	 list => '',  beginTime => '20050615.173000'}, # 	2005-06-15	17:30:00	2005-06-15	18:46:25	timestamp = ppTransProduction_FF
'1288'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166069',	 last => '6166071',	 list => '',  beginTime => '20050615.184625'}, # 	2005-06-15	18:46:25	2005-06-15	19:57:05
'1289'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6166072',	 last => '6166072',	 list => '',  beginTime => '20050615.195705'}, # 	2005-06-15	19:57:05	2005-06-15	20:04:05	timestamp = ppProductionMinBias_FF
'1290'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166073',	 last => '6166076',	 list => '',  beginTime => '20050615.200405'}, # 	2005-06-15	20:04:05	2005-06-16	00:00:31	timestamp = ppTransProduction_FF
'1291'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166089',	 last => '6166091',	 list => '',  beginTime => '20050616.000031'}, # 	2005-06-16	00:00:31	2005-06-16	00:51:31
'1292'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166094',	 last => '6166096',	 list => '',  beginTime => '20050616.005131'}, # 	2005-06-16	00:51:31	2005-06-16	02:19:45
'1293'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6166098',	 last => '6166099',	 list => '',  beginTime => '20050616.021945'}, # 	2005-06-16	02:19:45	2005-06-16	02:24:30	timestamp = ppProductionMinBias_FF
'1294'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166100',	 last => '6166107',	 list => '',  beginTime => '20050616.022430'}, # 	2005-06-16	02:24:30	2005-06-16	03:55:50	timestamp = ppTransProduction_FF
'1295'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6166109',	 last => '6166109',	 list => '',  beginTime => '20050616.035550'}, # 	2005-06-16	03:55:50	2005-06-16	04:01:59
'1296'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6167001',	 last => '6167002',	 list => '',  beginTime => '20050616.040159'}, # 	2005-06-16	04:01:59	2005-06-16	04:16:10
'1297'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6167004',	 last => '6167004',	 list => '',  beginTime => '20050616.041610'}, # 	2005-06-16	04:16:10	2005-06-16	04:29:16
'1298'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6167013',	 last => '6167013',	 list => '',  beginTime => '20050616.042916'}, # 	2005-06-16	04:29:16	2005-06-16	04:40:14
'1299'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6167015',	 last => '6167015',	 list => '',  beginTime => '20050616.044014'}, # 	2005-06-16	04:40:14	2005-06-16	05:17:26
'1300'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6167019',	 last => '6167024',	 list => '',  beginTime => '20050616.051726'}, # 	2005-06-16	05:17:26	2005-06-16	11:02:04
'1301'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6167076',	 last => '6167077',	 list => '',  beginTime => '20050616.110204'}, # 	2005-06-16	11:02:04	2005-06-16	11:27:12
'1302'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6167079',	 last => '6167079',	 list => '',  beginTime => '20050616.112712'}, # 	2005-06-16	11:27:12	2005-06-16	12:03:05
'1303'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6167081',	 last => '6167086',	 list => '',  beginTime => '20050616.120305'}, # 	2005-06-16	12:03:05	2005-06-16	13:36:34
'1304'=> {trig=>'ppTransProduction',     	field => 'FF',	first=> '6167088',	 last => '6167088',	 list => '',  beginTime => '20050616.133634'}, # 	2005-06-16	13:36:34	2005-06-16	21:22:06
'1305'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6167115',	 last => '6167120',	 list => '',  beginTime => '20050616.212206'}, # 	2005-06-16	21:22:06	2005-06-16	23:22:37	timestamp = ppProduction_FF
'1306'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6167121',	 last => '6167121',	 list => '',  beginTime => '20050616.232237'}, # 	2005-06-16	23:22:37	2005-06-16	23:37:05	timestamp = ppProductionMinBias_FF
'1307'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6167123',	 last => '6167131',	 list => '',  beginTime => '20050616.233705'}, # 	2005-06-16	23:37:05	2005-06-17	01:59:08	timestamp = ppProduction_FF
'1308'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6167132',	 last => '6167132',	 list => '',  beginTime => '20050617.015908'}, # 	2005-06-17	01:59:08	2005-06-17	02:06:09	timestamp = ppProductionMinBias_FF
'1309'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6167134',	 last => '6167134',	 list => '',  beginTime => '20050617.020609'}, # 	2005-06-17	02:06:09	2005-06-17	02:51:58	timestamp = ppProduction_FF
'1310'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6167140',	 last => '6167143',	 list => '',  beginTime => '20050617.025158'}, # 	2005-06-17	02:51:58	2005-06-17	04:18:07
'1311'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168002',	 last => '6168003',	 list => '',  beginTime => '20050617.041807'}, # 	2005-06-17	04:18:07	2005-06-17	04:32:11	timestamp = ppProductionMinBias_FF
'1312'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168004',	 last => '6168004',	 list => '',  beginTime => '20050617.043211'}, # 	2005-06-17	04:32:11	2005-06-17	04:41:04	timestamp = ppProduction_FF
'1313'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168005',	 last => '6168006',	 list => '',  beginTime => '20050617.044104'}, # 	2005-06-17	04:41:04	2005-06-17	07:25:18	timestamp = ppProductionMinBias_FF
'1314'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168017',	 last => '6168019',	 list => '',  beginTime => '20050617.072518'}, # 	2005-06-17	07:25:18	2005-06-17	08:47:58	timestamp = ppProduction_FF
'1315'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168022',	 last => '6168024',	 list => '',  beginTime => '20050617.084758'}, # 	2005-06-17	08:47:58	2005-06-17	10:42:12
'1316'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168036',	 last => '6168037',	 list => '',  beginTime => '20050617.104212'}, # 	2005-06-17	10:42:12	2005-06-17	11:15:30
'1317'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168038',	 last => '6168038',	 list => '',  beginTime => '20050617.111530'}, # 	2005-06-17	11:15:30	2005-06-17	11:30:13	timestamp = ppProductionMinBias_FF
'1318'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168040',	 last => '6168044',	 list => '',  beginTime => '20050617.113013'}, # 	2005-06-17	11:30:13	2005-06-17	18:36:03	timestamp = ppProduction_FF
'1319'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168067',	 last => '6168070',	 list => '',  beginTime => '20050617.183603'}, # 	2005-06-17	18:36:03	2005-06-17	19:34:53
'1320'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168072',	 last => '6168073',	 list => '',  beginTime => '20050617.193453'}, # 	2005-06-17	19:34:53	2005-06-17	20:28:16
'1321'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168077',	 last => '6168078',	 list => '',  beginTime => '20050617.202816'}, # 	2005-06-17	20:28:16	2005-06-17	20:44:31
'1322'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168079',	 last => '6168079',	 list => '',  beginTime => '20050617.204431'}, # 	2005-06-17	20:44:31	2005-06-17	20:59:55	timestamp = ppProductionMinBias_FF
'1323'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168081',	 last => '6168081',	 list => '',  beginTime => '20050617.205955'}, # 	2005-06-17	20:59:55	2005-06-17	21:03:06
'1324'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168082',	 last => '6168086',	 list => '',  beginTime => '20050617.210306'}, # 	2005-06-17	21:03:06	2005-06-17	22:28:50	timestamp = ppProduction_FF
'1325'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168087',	 last => '6168087',	 list => '',  beginTime => '20050617.222850'}, # 	2005-06-17	22:28:50	2005-06-17	22:40:45	timestamp = ppProductionMinBias_FF
'1326'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168088',	 last => '6168090',	 list => '',  beginTime => '20050617.224045'}, # 	2005-06-17	22:40:45	2005-06-17	23:44:57	timestamp = ppProduction_FF
'1327'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168091',	 last => '6168091',	 list => '',  beginTime => '20050617.234457'}, # 	2005-06-17	23:44:57	2005-06-17	23:56:09	timestamp = ppProductionMinBias_FF
'1328'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168093',	 last => '6168093',	 list => '',  beginTime => '20050617.235609'}, # 	2005-06-17	23:56:09	2005-06-18	00:13:08
'1329'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168099',	 last => '6168104',	 list => '',  beginTime => '20050618.001308'}, # 	2005-06-18	00:13:08	2005-06-18	02:44:28	timestamp = ppProduction_FF
'1330'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168105',	 last => '6168105',	 list => '',  beginTime => '20050618.024428'}, # 	2005-06-18	02:44:28	2005-06-18	02:55:48	timestamp = ppProductionMinBias_FF
'1331'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168107',	 last => '6168108',	 list => '',  beginTime => '20050618.025548'}, # 	2005-06-18	02:55:48	2005-06-18	03:33:22	timestamp = ppProduction_FF
'1332'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6168110',	 last => '6168111',	 list => '',  beginTime => '20050618.033322'}, # 	2005-06-18	03:33:22	2005-06-18	03:56:01	timestamp = ppProductionMinBias_FF
'1333'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6168112',	 last => '6168112',	 list => '',  beginTime => '20050618.035601'}, # 	2005-06-18	03:56:01	2005-06-18	04:24:10	timestamp = ppProduction_FF
'1334'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169001',	 last => '6169003',	 list => '',  beginTime => '20050618.042410'}, # 	2005-06-18	04:24:10	2005-06-18	05:44:14
'1335'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6169004',	 last => '6169004',	 list => '',  beginTime => '20050618.054414'}, # 	2005-06-18	05:44:14	2005-06-18	05:55:19	timestamp = ppProductionMinBias_FF
'1336'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169006',	 last => '6169008',	 list => '',  beginTime => '20050618.055519'}, # 	2005-06-18	05:55:19	2005-06-18	10:26:25	timestamp = ppProduction_FF
'1337'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6169019',	 last => '6169019',	 list => '',  beginTime => '20050618.102625'}, # 	2005-06-18	10:26:25	2005-06-18	10:56:10	timestamp = ppProductionMinBias_FF
'1338'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169025',	 last => '6169031',	 list => '',  beginTime => '20050618.105610'}, # 	2005-06-18	10:56:10	2005-06-18	13:15:29	timestamp = ppProduction_FF
'1339'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6169032',	 last => '6169032',	 list => '',  beginTime => '20050618.131529'}, # 	2005-06-18	13:15:29	2005-06-18	13:29:19	timestamp = ppProductionMinBias_FF
'1340'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6169034',	 last => '6169034',	 list => '',  beginTime => '20050618.132919'}, # 	2005-06-18	13:29:19	2005-06-18	13:36:28
'1341'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169035',	 last => '6169041',	 list => '',  beginTime => '20050618.133628'}, # 	2005-06-18	13:36:28	2005-06-18	14:51:47	timestamp = ppProduction_FF
'1342'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169043',	 last => '6169044',	 list => '',  beginTime => '20050618.145147'}, # 	2005-06-18	14:51:47	2005-06-18	15:12:59
'1343'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169047',	 last => '6169053',	 list => '',  beginTime => '20050618.151259'}, # 	2005-06-18	15:12:59	2005-06-18	16:33:08
'1344'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169055',	 last => '6169060',	 list => '',  beginTime => '20050618.163308'}, # 	2005-06-18	16:33:08	2005-06-18	20:47:08
'1345'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6169073',	 last => '6169073',	 list => '',  beginTime => '20050618.204708'}, # 	2005-06-18	20:47:08	2005-06-18	21:10:51	timestamp = ppProductionMinBias_FF
'1346'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169079',	 last => '6169080',	 list => '',  beginTime => '20050618.211051'}, # 	2005-06-18	21:10:51	2005-06-18	22:10:53	timestamp = ppProduction_FF
'1347'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169082',	 last => '6169084',	 list => '',  beginTime => '20050618.221053'}, # 	2005-06-18	22:10:53	2005-06-18	23:42:15
'1348'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6169087',	 last => '6169087',	 list => '',  beginTime => '20050618.234215'}, # 	2005-06-18	23:42:15	2005-06-18	23:45:35	timestamp = ppProductionMinBias_FF
'1349'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169088',	 last => '6169097',	 list => '',  beginTime => '20050618.234535'}, # 	2005-06-18	23:45:35	2005-06-19	02:29:12	timestamp = ppProduction_FF
'1350'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6169098',	 last => '6169098',	 list => '',  beginTime => '20050619.022912'}, # 	2005-06-19	02:29:12	2005-06-19	02:41:52	timestamp = ppProductionMinBias_FF
'1351'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6169101',	 last => '6169107',	 list => '',  beginTime => '20050619.024152'}, # 	2005-06-19	02:41:52	2005-06-19	04:13:41	timestamp = ppProduction_FF
'1352'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170002',	 last => '6170002',	 list => '',  beginTime => '20050619.041341'}, # 	2005-06-19	04:13:41	2005-06-19	04:43:56
'1353'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170004',	 last => '6170004',	 list => '',  beginTime => '20050619.044356'}, # 	2005-06-19	04:43:56	2005-06-19	05:08:07
'1354'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6170005',	 last => '6170005',	 list => '',  beginTime => '20050619.050807'}, # 	2005-06-19	05:08:07	2005-06-19	05:19:34	timestamp = ppProductionMinBias_FF
'1355'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170006',	 last => '6170006',	 list => '',  beginTime => '20050619.051934'}, # 	2005-06-19	05:19:34	2005-06-19	05:30:37	timestamp = ppProduction_FF
'1356'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6170007',	 last => '6170007',	 list => '',  beginTime => '20050619.053037'}, # 	2005-06-19	05:30:37	2005-06-19	05:44:05	timestamp = ppProductionMinBias_FF
'1357'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170009',	 last => '6170015',	 list => '',  beginTime => '20050619.054405'}, # 	2005-06-19	05:44:05	2005-06-19	08:40:24	timestamp = ppProduction_FF
'1358'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6170016',	 last => '6170017',	 list => '',  beginTime => '20050619.084024'}, # 	2005-06-19	08:40:24	2005-06-19	09:11:09	timestamp = ppProductionMinBias_FF
'1359'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170018',	 last => '6170018',	 list => '',  beginTime => '20050619.091109'}, # 	2005-06-19	09:11:09	2005-06-19	11:49:48	timestamp = ppProduction_FF
'1360'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170031',	 last => '6170035',	 list => '',  beginTime => '20050619.114948'}, # 	2005-06-19	11:49:48	2005-06-19	12:55:25
'1361'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6170036',	 last => '6170036',	 list => '',  beginTime => '20050619.125525'}, # 	2005-06-19	12:55:25	2005-06-19	12:59:48	timestamp = ppProductionMinBias_FF
'1362'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170037',	 last => '6170041',	 list => '',  beginTime => '20050619.125948'}, # 	2005-06-19	12:59:48	2005-06-19	14:28:39	timestamp = ppProduction_FF
'1363'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170045',	 last => '6170052',	 list => '',  beginTime => '20050619.142839'}, # 	2005-06-19	14:28:39	2005-06-19	17:32:29
'1364'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170054',	 last => '6170055',	 list => '',  beginTime => '20050619.173229'}, # 	2005-06-19	17:32:29	2005-06-19	17:56:52
'1365'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6170056',	 last => '6170056',	 list => '',  beginTime => '20050619.175652'}, # 	2005-06-19	17:56:52	2005-06-19	18:06:52	timestamp = ppProductionMinBias_FF
'1366'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170057',	 last => '6170062',	 list => '',  beginTime => '20050619.180652'}, # 	2005-06-19	18:06:52	2005-06-20	00:06:24	timestamp = ppProduction_FF
'1367'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170072',	 last => '6170076',	 list => '',  beginTime => '20050620.000624'}, # 	2005-06-20	00:06:24	2005-06-20	02:26:27
'1368'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6170079',	 last => '6170079',	 list => '',  beginTime => '20050620.022627'}, # 	2005-06-20	02:26:27	2005-06-20	02:29:34	timestamp = ppProductionMinBias_FF
'1369'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6170080',	 last => '6170083',	 list => '',  beginTime => '20050620.022934'}, # 	2005-06-20	02:29:34	2005-06-20	04:26:17	timestamp = ppProduction_FF
'1370'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6171001',	 last => '6171002',	 list => '',  beginTime => '20050620.042617'}, # 	2005-06-20	04:26:17	2005-06-20	05:14:43
'1371'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6171003',	 last => '6171003',	 list => '',  beginTime => '20050620.051443'}, # 	2005-06-20	05:14:43	2005-06-20	05:37:16	timestamp = ppProductionMinBias_FF
'1372'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6171008',	 last => '6171008',	 list => '',  beginTime => '20050620.053716'}, # 	2005-06-20	05:37:16	2005-06-20	05:58:13	timestamp = ppProduction_FF
'1373'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6171013',	 last => '6171013',	 list => '',  beginTime => '20050620.055813'}, # 	2005-06-20	05:58:13	2005-06-20	12:06:41	timestamp = ppProductionMinBias_FF
'1374'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6171021',	 last => '6171024',	 list => '',  beginTime => '20050620.120641'}, # 	2005-06-20	12:06:41	2005-06-20	13:32:36	timestamp = ppProduction_FF
'1375'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6171025',	 last => '6171026',	 list => '',  beginTime => '20050620.133236'}, # 	2005-06-20	13:32:36	2005-06-20	13:46:09	timestamp = ppProductionMinBias_FF
'1376'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6171030',	 last => '6171030',	 list => '',  beginTime => '20050620.134609'}, # 	2005-06-20	13:46:09	2005-06-20	13:59:06
'1377'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6171031',	 last => '6171031',	 list => '',  beginTime => '20050620.135906'}, # 	2005-06-20	13:59:06	2005-06-20	14:18:09	timestamp = ppProduction_FF
'1378'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6171034',	 last => '6171034',	 list => '',  beginTime => '20050620.141809'}, # 	2005-06-20	14:18:09	2005-06-20	14:55:18
'1379'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6171037',	 last => '6171037',	 list => '',  beginTime => '20050620.145518'}, # 	2005-06-20	14:55:18	2005-06-20	15:05:23	timestamp = ppProductionMinBias_FF
'1380'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6171039',	 last => '6171046',	 list => '',  beginTime => '20050620.150523'}, # 	2005-06-20	15:05:23	2005-06-20	17:47:54	timestamp = ppProduction_FF
'1381'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6171048',	 last => '6171049',	 list => '',  beginTime => '20050620.174754'}, # 	2005-06-20	17:47:54	2005-06-21	03:29:35
'1382'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6171062',	 last => '6171063',	 list => '',  beginTime => '20050621.032935'}, # 	2005-06-21	03:29:35	2005-06-21	04:23:54
'1383'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6172001',	 last => '6172003',	 list => '',  beginTime => '20050621.042354'}, # 	2005-06-21	04:23:54	2005-06-21	05:28:10
'1384'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172004',	 last => '6172004',	 list => '',  beginTime => '20050621.052810'}, # 	2005-06-21	05:28:10	2005-06-21	05:45:49	timestamp = ppProductionMinBias_FF
'1385'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6172006',	 last => '6172008',	 list => '',  beginTime => '20050621.054549'}, # 	2005-06-21	05:45:49	2005-06-21	06:44:27	timestamp = ppProduction_FF
'1386'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6172010',	 last => '6172010',	 list => '',  beginTime => '20050621.064427'}, # 	2005-06-21	06:44:27	2005-06-21	07:11:14
'1387'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172015',	 last => '6172016',	 list => '',  beginTime => '20050621.071114'}, # 	2005-06-21	07:11:14	2005-06-21	15:46:44	timestamp = ppProductionMinBias_FF
'1388'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6172037',	 last => '6172037',	 list => '',  beginTime => '20050621.154644'}, # 	2005-06-21	15:46:44	2005-06-21	15:51:04	timestamp = ppProduction_FF
'1389'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172038',	 last => '6172038',	 list => '',  beginTime => '20050621.155104'}, # 	2005-06-21	15:51:04	2005-06-21	15:56:08	timestamp = ppProductionMinBias_FF
'1390'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6172040',	 last => '6172040',	 list => '',  beginTime => '20050621.155608'}, # 	2005-06-21	15:56:08	2005-06-21	20:51:44	timestamp = ppProduction_FF
'1391'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6172059',	 last => '6172060',	 list => '',  beginTime => '20050621.205144'}, # 	2005-06-21	20:51:44	2005-06-21	21:24:17
'1392'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172061',	 last => '6172061',	 list => '',  beginTime => '20050621.212417'}, # 	2005-06-21	21:24:17	2005-06-21	21:39:21	timestamp = ppProductionMinBias_FF
'1393'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172064',	 last => '6172065',	 list => '',  beginTime => '20050621.213921'}, # 	2005-06-21	21:39:21	2005-06-21	22:16:41
'1394'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172068',	 last => '6172068',	 list => '',  beginTime => '20050621.221641'}, # 	2005-06-21	22:16:41	2005-06-21	22:36:04
'1395'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6172069',	 last => '6172069',	 list => '',  beginTime => '20050621.223604'}, # 	2005-06-21	22:36:04	2005-06-21	23:50:09	timestamp = ppProduction_FF
'1396'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172076',	 last => '6172076',	 list => '',  beginTime => '20050621.235009'}, # 	2005-06-21	23:50:09	2005-06-21	23:55:47	timestamp = ppProductionMinBias_FF
'1397'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172078',	 last => '6172078',	 list => '',  beginTime => '20050621.235547'}, # 	2005-06-21	23:55:47	2005-06-22	00:29:23
'1398'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6172085',	 last => '6172087',	 list => '',  beginTime => '20050622.002923'}, # 	2005-06-22	00:29:23	2005-06-22	02:08:09	timestamp = ppProduction_FF
'1399'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172088',	 last => '6172088',	 list => '',  beginTime => '20050622.020809'}, # 	2005-06-22	02:08:09	2005-06-22	02:25:04	timestamp = ppProductionMinBias_FF
'1400'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6172091',	 last => '6172091',	 list => '',  beginTime => '20050622.022504'}, # 	2005-06-22	02:25:04	2005-06-22	02:28:41
'1401'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6172092',	 last => '6172093',	 list => '',  beginTime => '20050622.022841'}, # 	2005-06-22	02:28:41	2005-06-22	06:37:06	timestamp = ppProduction_FF
'1402'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6173012',	 last => '6173013',	 list => '',  beginTime => '20050622.063706'}, # 	2005-06-22	06:37:06	2005-06-22	07:49:58	timestamp = ppProductionMinBias_FF
'1403'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6173015',	 last => '6173015',	 list => '',  beginTime => '20050622.074958'}, # 	2005-06-22	07:49:58	2005-06-22	08:19:23
'1404'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6173017',	 last => '6173017',	 list => '',  beginTime => '20050622.081923'}, # 	2005-06-22	08:19:23	2005-06-22	08:35:59
'1405'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6173019',	 last => '6173019',	 list => '',  beginTime => '20050622.083559'}, # 	2005-06-22	08:35:59	2005-06-22	08:43:38
'1406'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173021',	 last => '6173027',	 list => '',  beginTime => '20050622.084338'}, # 	2005-06-22	08:43:38	2005-06-22	11:25:02	timestamp = ppProduction_FF
'1407'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6173028',	 last => '6173028',	 list => '',  beginTime => '20050622.112502'}, # 	2005-06-22	11:25:02	2005-06-22	11:40:43	timestamp = ppProductionMinBias_FF
'1408'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173030',	 last => '6173032',	 list => '',  beginTime => '20050622.114043'}, # 	2005-06-22	11:40:43	2005-06-22	12:45:15	timestamp = ppProduction_FF
'1409'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6173033',	 last => '6173033',	 list => '',  beginTime => '20050622.124515'}, # 	2005-06-22	12:45:15	2005-06-22	12:49:41	timestamp = ppProductionMinBias_FF
'1410'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173034',	 last => '6173035',	 list => '',  beginTime => '20050622.124941'}, # 	2005-06-22	12:49:41	2005-06-22	13:54:38	timestamp = ppProduction_FF
'1411'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173041',	 last => '6173044',	 list => '',  beginTime => '20050622.135438'}, # 	2005-06-22	13:54:38	2005-06-22	20:36:22
'1412'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173062',	 last => '6173066',	 list => '',  beginTime => '20050622.203622'}, # 	2005-06-22	20:36:22	2005-06-22	22:48:19
'1413'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6173068',	 last => '6173068',	 list => '',  beginTime => '20050622.224819'}, # 	2005-06-22	22:48:19	2005-06-22	22:53:10	timestamp = ppProductionMinBias_FF
'1414'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173069',	 last => '6173073',	 list => '',  beginTime => '20050622.225310'}, # 	2005-06-22	22:53:10	2005-06-23	00:49:54	timestamp = ppProduction_FF
'1415'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173075',	 last => '6173075',	 list => '',  beginTime => '20050623.004954'}, # 	2005-06-23	00:49:54	2005-06-23	01:41:27
'1416'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6173077',	 last => '6173077',	 list => '',  beginTime => '20050623.014127'}, # 	2005-06-23	01:41:27	2005-06-23	01:44:31	timestamp = ppProductionMinBias_FF
'1417'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173078',	 last => '6173078',	 list => '',  beginTime => '20050623.014431'}, # 	2005-06-23	01:44:31	2005-06-23	02:16:40	timestamp = ppProduction_FF
'1418'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173080',	 last => '6173082',	 list => '',  beginTime => '20050623.021640'}, # 	2005-06-23	02:16:40	2005-06-23	03:00:28
'1419'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6173084',	 last => '6173084',	 list => '',  beginTime => '20050623.030028'}, # 	2005-06-23	03:00:28	2005-06-23	03:28:21	timestamp = ppProductionMinBias_FF
'1420'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6173085',	 last => '6173086',	 list => '',  beginTime => '20050623.032821'}, # 	2005-06-23	03:28:21	2005-06-23	08:10:39	timestamp = ppProduction_FF
'1421'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6174010',	 last => '6174014',	 list => '',  beginTime => '20050623.081039'}, # 	2005-06-23	08:10:39	2005-06-23	09:48:49
'1422'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6174015',	 last => '6174015',	 list => '',  beginTime => '20050623.094849'}, # 	2005-06-23	09:48:49	2005-06-23	10:00:59	timestamp = ppProductionMinBias_FF
'1423'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6174017',	 last => '6174022',	 list => '',  beginTime => '20050623.100059'}, # 	2005-06-23	10:00:59	2005-06-23	12:12:41	timestamp = ppProduction_FF
'1424'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6174024',	 last => '6174025',	 list => '',  beginTime => '20050623.121241'}, # 	2005-06-23	12:12:41	2005-06-23	12:24:38	timestamp = ppProductionMinBias_FF
'1425'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6174026',	 last => '6174027',	 list => '',  beginTime => '20050623.122438'}, # 	2005-06-23	12:24:38	2005-06-23	13:11:10	timestamp = ppProduction_FF
'1426'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6174029',	 last => '6174029',	 list => '',  beginTime => '20050623.131110'}, # 	2005-06-23	13:11:10	2005-06-23	13:14:58
'1427'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6174031',	 last => '6174031',	 list => '',  beginTime => '20050623.131458'}, # 	2005-06-23	13:14:58	2005-06-23	20:04:01
'1428'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6174043',	 last => '6174049',	 list => '',  beginTime => '20050623.200401'}, # 	2005-06-23	20:04:01	2005-06-23	22:54:16
'1429'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6174051',	 last => '6174052',	 list => '',  beginTime => '20050623.225416'}, # 	2005-06-23	22:54:16	2005-06-23	22:58:53	timestamp = ppProductionMinBias_FF
'1430'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6174053',	 last => '6174060',	 list => '',  beginTime => '20050623.225853'}, # 	2005-06-23	22:58:53	2005-06-24	02:04:26	timestamp = ppProduction_FF
'1431'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6174067',	 last => '6174068',	 list => '',  beginTime => '20050624.020426'}, # 	2005-06-24	02:04:26	2005-06-24	02:42:14	timestamp = ppProductionMinBias_FF
'1432'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6174069',	 last => '6174070',	 list => '',  beginTime => '20050624.024214'}, # 	2005-06-24	02:42:14	2005-06-24	03:35:39	timestamp = ppProduction_FF
'1433'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6174072',	 last => '6174072',	 list => '',  beginTime => '20050624.033539'}, # 	2005-06-24	03:35:39	2005-06-24	08:57:58
'1434'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6175008',	 last => '6175012',	 list => '',  beginTime => '20050624.085758'}, # 	2005-06-24	08:57:58	2005-06-24	10:57:27
'1435'=> {trig=>'ppProductionMinBias',   	field => 'FF',	first=> '6175013',	 last => '6175013',	 list => '',  beginTime => '20050624.105727'}, # 	2005-06-24	10:57:27	2005-06-24	11:17:57	timestamp = ppProductionMinBias_FF
'1436'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6175016',	 last => '6175017',	 list => '',  beginTime => '20050624.111757'}, # 	2005-06-24	11:17:57	2005-06-24	12:05:24	timestamp = ppProduction_FF
'1437'=> {trig=>'ppProduction',          	field => 'FF',	first=> '6175020',	 last => '6175020',	 list => '',  beginTime => '20050624.120524'}, # 	2005-06-24	12:05:24	2005-06-24	12:05:24
);
1;
