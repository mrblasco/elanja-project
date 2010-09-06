load('Measures.dat');

t = [-0.8;-0.6;-0.4;-0.2;0.0;0.2;0.4;0.6;0.8];
f = [5;10;15;20;25;30];

%average degree
av_deg_f5 = [mean(Measures(1:20000,2));mean(Measures(20001:40000,2));mean(Measures(40001:60000,2));mean(Measures(60001:80000,2));mean(Measures(80001:100000,2));mean(Measures(100001:120000,2));mean(Measures(120001:140000,2));mean(Measures(140001:160000,2));mean(Measures(160001:180000,2))];
av_deg_f10 = [mean(Measures(180001:200000,2));mean(Measures(200001:220000,2));mean(Measures(220001:240000,2));mean(Measures(240001:260000,2));mean(Measures(260001:380000,2));mean(Measures(280001:300000,2));mean(Measures(300001:320000,2));mean(Measures(320001:340000,2));mean(Measures(340001:360000,2))];
av_deg_f15 = [mean(Measures(360001:380000,2));mean(Measures(380001:400000,2));mean(Measures(400001:420000,2));mean(Measures(420001:440000,2));mean(Measures(440001:460000,2));mean(Measures(460001:480000,2));mean(Measures(480001:500000,2));mean(Measures(500001:520000,2));mean(Measures(520001:540000,2))];
av_deg_f20 = [mean(Measures(540001:560000,2));mean(Measures(560001:580000,2));mean(Measures(580001:600000,2));mean(Measures(600001:620000,2));mean(Measures(620001:640000,2));mean(Measures(640001:660000,2));mean(Measures(660001:680000,2));mean(Measures(680001:700000,2));mean(Measures(700001:720000,2))];
av_deg_f25 = [mean(Measures(720001:740000,2));mean(Measures(740001:760000,2));mean(Measures(760001:780000,2));mean(Measures(780001:800000,2));mean(Measures(800001:820000,2));mean(Measures(820001:840000,2));mean(Measures(840001:860000,2));mean(Measures(860001:880000,2));mean(Measures(880001:900000,2))];
av_deg_f30 = [mean(Measures(900001:920000,2));mean(Measures(920001:940000,2));mean(Measures(940001:960000,2));mean(Measures(960001:980000,2));mean(Measures(980001:1000000,2));mean(Measures(1000001:1020000,2));mean(Measures(1020001:1040000,2));mean(Measures(1040001:1060000,2));mean(Measures(1060001:1080000,2))];
plot(t,av_deg_f5,'-o',t,av_deg_f10,'-o',t,av_deg_f15,'-o',t,av_deg_f20,'-o',t,av_deg_f25,'-o',t,av_deg_f30,'-o')
legend('# features = 5','# features = 10','# features = 15','# features = 20','# features = 25','# features = 30')
xlabel('threshold');
ylabel('average degree');
title('Average Degree');

%average average feature
av_feat_f5 = [mean(Measures(1:20000,4));mean(Measures(20001:40000,4));mean(Measures(40001:60000,4));mean(Measures(60001:80000,4));mean(Measures(80001:100000,4));mean(Measures(100001:120000,4));mean(Measures(120001:140000,4));mean(Measures(140001:160000,4));mean(Measures(160001:180000,4))];
av_feat_f10 = [mean(Measures(180001:200000,4));mean(Measures(200001:220000,4));mean(Measures(220001:240000,4));mean(Measures(240001:260000,4));mean(Measures(260001:380000,4));mean(Measures(280001:300000,4));mean(Measures(300001:320000,4));mean(Measures(320001:340000,4));mean(Measures(340001:360000,4))];
av_feat_f15 = [mean(Measures(360001:380000,4));mean(Measures(380001:400000,4));mean(Measures(400001:420000,4));mean(Measures(420001:440000,4));mean(Measures(440001:460000,4));mean(Measures(460001:480000,4));mean(Measures(480001:500000,4));mean(Measures(500001:520000,4));mean(Measures(520001:540000,4))];
av_feat_f20 = [mean(Measures(540001:560000,4));mean(Measures(560001:580000,4));mean(Measures(580001:600000,4));mean(Measures(600001:620000,4));mean(Measures(620001:640000,4));mean(Measures(640001:660000,4));mean(Measures(660001:680000,4));mean(Measures(680001:700000,4));mean(Measures(700001:720000,4))];
av_feat_f25 = [mean(Measures(720001:740000,4));mean(Measures(740001:760000,4));mean(Measures(760001:780000,4));mean(Measures(780001:800000,4));mean(Measures(800001:820000,4));mean(Measures(820001:840000,4));mean(Measures(840001:860000,4));mean(Measures(860001:880000,4));mean(Measures(880001:900000,4))];
av_feat_f30 = [mean(Measures(900001:920000,4));mean(Measures(920001:940000,4));mean(Measures(940001:960000,4));mean(Measures(960001:980000,4));mean(Measures(980001:1000000,4));mean(Measures(1000001:1020000,4));mean(Measures(1020001:1040000,4));mean(Measures(1040001:1060000,4));mean(Measures(1060001:1080000,4))];
figure, plot(t,av_feat_f5,'-o',t,av_feat_f10,'-o',t,av_feat_f15,'-o',t,av_feat_f20,'-o',t,av_feat_f25,'-o',t,av_feat_f30,'-o')
legend('# features = 5','# features = 10','# features = 15','# features = 20','# features = 25','# features = 30')
xlabel('threshold');
ylabel('average average feature');
title('Average Average Feature');

%average of variance of feature
av_var_feat_f5 = [mean(Measures(1:20000,5));mean(Measures(20001:40000,5));mean(Measures(40001:60000,5));mean(Measures(60001:80000,5));mean(Measures(80001:100000,5));mean(Measures(100001:120000,5));mean(Measures(120001:140000,5));mean(Measures(140001:160000,5));mean(Measures(160001:180000,5))];
av_var_feat_f10 = [mean(Measures(180001:200000,5));mean(Measures(200001:220000,5));mean(Measures(220001:240000,5));mean(Measures(240001:260000,5));mean(Measures(260001:380000,5));mean(Measures(280001:300000,5));mean(Measures(300001:320000,5));mean(Measures(320001:340000,5));mean(Measures(340001:360000,5))];
av_var_feat_f15 = [mean(Measures(360001:380000,5));mean(Measures(380001:400000,5));mean(Measures(400001:420000,5));mean(Measures(420001:440000,5));mean(Measures(440001:460000,5));mean(Measures(460001:480000,5));mean(Measures(480001:500000,5));mean(Measures(500001:520000,5));mean(Measures(520001:540000,5))];
av_var_feat_f20 = [mean(Measures(540001:560000,5));mean(Measures(560001:580000,5));mean(Measures(580001:600000,5));mean(Measures(600001:620000,5));mean(Measures(620001:640000,5));mean(Measures(640001:660000,5));mean(Measures(660001:680000,5));mean(Measures(680001:700000,5));mean(Measures(700001:720000,5))];
av_var_feat_f25 = [mean(Measures(720001:740000,5));mean(Measures(740001:760000,5));mean(Measures(760001:780000,5));mean(Measures(780001:800000,5));mean(Measures(800001:820000,5));mean(Measures(820001:840000,5));mean(Measures(840001:860000,5));mean(Measures(860001:880000,5));mean(Measures(880001:900000,5))];
av_var_feat_f30 = [mean(Measures(900001:920000,5));mean(Measures(920001:940000,5));mean(Measures(940001:960000,5));mean(Measures(960001:980000,5));mean(Measures(980001:1000000,5));mean(Measures(1000001:1020000,5));mean(Measures(1020001:1040000,5));mean(Measures(1040001:1060000,5));mean(Measures(1060001:1080000,5))];
figure, plot(t,av_var_feat_f5,'-o',t,av_var_feat_f10,'-o',t,av_var_feat_f15,'-o',t,av_var_feat_f20,'-o',t,av_var_feat_f25,'-o',t,av_var_feat_f30,'-o')
legend('# features = 5','# features = 10','# features = 15','# features = 20','# features = 25','# features = 30')
xlabel('threshold');
ylabel('average of the variance of features');
title('Average of Variance of Features');



%average degree in function of the number of features
av_deg_t1 = [mean(Measures(1:20000,2));mean(Measures(180001:200000,2));mean(Measures(360001:380000,2));mean(Measures(540001:560000,2));mean(Measures(720001:740000,2));mean(Measures(900001:920000,2))];
av_deg_t2 = [mean(Measures(20001:40000,2));mean(Measures(200001:220000,2));mean(Measures(380001:400000,2));mean(Measures(560001:580000,2));mean(Measures(740001:760000,2));mean(Measures(920001:940000,2))];
av_deg_t3 = [mean(Measures(40001:60000,2));mean(Measures(220001:240000,2));mean(Measures(400001:420000,2));mean(Measures(580001:600000,2));mean(Measures(760001:780000,2));mean(Measures(940001:960000,2))];
av_deg_t4 = [mean(Measures(60001:80000,2));mean(Measures(240001:260000,2));mean(Measures(420001:440000,2));mean(Measures(600001:620000,2));mean(Measures(780001:800000,2));mean(Measures(960001:980000,2))];
av_deg_t5 = [mean(Measures(80001:100000,2));mean(Measures(260001:380000,2));mean(Measures(440001:460000,2));mean(Measures(620001:640000,2));mean(Measures(800001:820000,2));mean(Measures(980001:1000000,2))];
av_deg_t6 = [mean(Measures(100001:120000,2));mean(Measures(280001:300000,2));mean(Measures(460001:480000,2));mean(Measures(640001:660000,2));mean(Measures(820001:840000,2));mean(Measures(1000001:1020000,2))];
av_deg_t7 = [mean(Measures(120001:140000,2));mean(Measures(300001:320000,2));mean(Measures(480001:500000,2));mean(Measures(660001:680000,2));mean(Measures(840001:860000,2));mean(Measures(1020001:1040000,2))];
av_deg_t8 = [mean(Measures(140001:160000,2));mean(Measures(320001:340000,2));mean(Measures(500001:520000,2));mean(Measures(680001:700000,2));mean(Measures(860001:880000,2));mean(Measures(1040001:1060000,2));];
av_deg_t9 = [mean(Measures(160001:180000,2));mean(Measures(340001:360000,2));mean(Measures(520001:540000,2));mean(Measures(700001:720000,2));mean(Measures(880001:900000,2));mean(Measures(1060001:1080000,2))];
figure, plot(f,av_deg_t1,'-o',f,av_deg_t2,'-o',f,av_deg_t3,'-o',f,av_deg_t4,'-o',f,av_deg_t5,'-o',f,av_deg_t6,'-o',f,av_deg_t7,'-o',f,av_deg_t8,'-o',f,av_deg_t9,'-o')
legend('threshold = -0.8','threshold = -0.6','threshold = -0.4','threshold = -0.2','threshold = 0','threshold = 0.2','threshold = 0.4','threshold = 0.6','threshold = 0.8');
xlabel('number of features');
ylabel('average degree');
title('Average Degree');

%average variance feature in function of the number of features
av_var_feat_t1 = [mean(Measures(1:20000,5));mean(Measures(180001:200000,5));mean(Measures(360001:380000,5));mean(Measures(540001:560000,5));mean(Measures(720001:740000,5));mean(Measures(900001:920000,5))];
av_var_feat_t2 = [mean(Measures(20001:40000,5));mean(Measures(200001:220000,5));mean(Measures(380001:400000,5));mean(Measures(560001:580000,5));mean(Measures(740001:760000,5));mean(Measures(920001:940000,5))];
av_var_feat_t3 = [mean(Measures(40001:60000,5));mean(Measures(220001:240000,5));mean(Measures(400001:420000,5));mean(Measures(580001:600000,5));mean(Measures(760001:780000,5));mean(Measures(940001:960000,5))];
av_var_feat_t4 = [mean(Measures(60001:80000,5));mean(Measures(240001:260000,5));mean(Measures(420001:440000,5));mean(Measures(600001:620000,5));mean(Measures(780001:800000,5));mean(Measures(960001:980000,5))];
av_var_feat_t5 = [mean(Measures(80001:100000,5));mean(Measures(260001:380000,5));mean(Measures(440001:460000,5));mean(Measures(620001:640000,5));mean(Measures(800001:820000,5));mean(Measures(980001:1000000,5))];
av_var_feat_t6 = [mean(Measures(100001:120000,5));mean(Measures(280001:300000,5));mean(Measures(460001:480000,5));mean(Measures(640001:660000,5));mean(Measures(820001:840000,5));mean(Measures(1000001:1020000,5))];
av_var_feat_t7 = [mean(Measures(120001:140000,5));mean(Measures(300001:320000,5));mean(Measures(480001:500000,5));mean(Measures(660001:680000,5));mean(Measures(840001:860000,5));mean(Measures(1020001:1040000,5))];
av_var_feat_t8 = [mean(Measures(140001:160000,5));mean(Measures(320001:340000,5));mean(Measures(500001:520000,5));mean(Measures(680001:700000,5));mean(Measures(860001:880000,5));mean(Measures(1040001:1060000,5));];
av_var_feat_t9 = [mean(Measures(160001:180000,5));mean(Measures(340001:360000,5));mean(Measures(520001:540000,5));mean(Measures(700001:720000,5));mean(Measures(880001:900000,5));mean(Measures(1060001:1080000,5))];
figure, plot(f,av_var_feat_t1,'-o',f,av_var_feat_t2,'-o',f,av_var_feat_t3,'-o',f,av_var_feat_t4,'-o',f,av_var_feat_t5,'-o',f,av_var_feat_t6,'-o',f,av_var_feat_t7,'-o',f,av_var_feat_t8,'-o',f,av_var_feat_t9,'-o')
legend('threshold = -0.8','threshold = -0.6','threshold = -0.4','threshold = -0.2','threshold = 0','threshold = 0.2','threshold = 0.4','threshold = 0.6','threshold = 0.8');
xlabel('number of features');
ylabel('average of the variance of features');
title('Average of Variance of Features');

%average tvalue
av_t_f5 = [mean(Measures(1:20000,8));mean(Measures(20001:40000,8));mean(Measures(40001:60000,8));mean(Measures(60001:80000,8));mean(Measures(80001:100000,8));mean(Measures(100001:120000,8));mean(Measures(120001:140000,8));mean(Measures(140001:160000,8));mean(Measures(160001:180000,8))];
av_t_f10 = [mean(Measures(180001:200000,8));mean(Measures(200001:220000,8));mean(Measures(220001:240000,8));mean(Measures(240001:260000,8));mean(Measures(260001:380000,8));mean(Measures(280001:300000,8));mean(Measures(300001:320000,8));mean(Measures(320001:340000,8));mean(Measures(340001:360000,8))];
av_t_f15 = [mean(Measures(360001:380000,8));mean(Measures(380001:400000,8));mean(Measures(400001:420000,8));mean(Measures(420001:440000,8));mean(Measures(440001:460000,8));mean(Measures(460001:480000,8));mean(Measures(480001:500000,8));mean(Measures(500001:520000,8));mean(Measures(520001:540000,8))];
av_t_f20 = [mean(Measures(540001:560000,8));mean(Measures(560001:580000,8));mean(Measures(580001:600000,8));mean(Measures(600001:620000,8));mean(Measures(620001:640000,8));mean(Measures(640001:660000,8));mean(Measures(660001:680000,8));mean(Measures(680001:700000,8));mean(Measures(700001:720000,8))];
av_t_f25 = [mean(Measures(720001:740000,8));mean(Measures(740001:760000,8));mean(Measures(760001:780000,8));mean(Measures(780001:800000,8));mean(Measures(800001:820000,8));mean(Measures(820001:840000,8));mean(Measures(840001:860000,8));mean(Measures(860001:880000,8));mean(Measures(880001:900000,8))];
av_t_f30 = [mean(Measures(900001:920000,8));mean(Measures(920001:940000,8));mean(Measures(940001:960000,8));mean(Measures(960001:980000,8));mean(Measures(980001:1000000,8));mean(Measures(1000001:1020000,8));mean(Measures(1020001:1040000,8));mean(Measures(1040001:1060000,8));mean(Measures(1060001:1080000,8))];
plot(t,av_t_f5,'-o',t,av_t_f10,'-o',t,av_t_f15,'-o',t,av_t_f20,'-o',t,av_t_f25,'-o',t,av_t_f30,'-o')
legend('# features = 5','# features = 10','# features = 15','# features = 20','# features = 25','# features = 30')
xlabel('threshold');
ylabel('average tvalue');
title('Average Tvalue');

%average tvalue in function of the number of features
av_t_t1 = [mean(Measures(1:20000,8));mean(Measures(180001:200000,8));mean(Measures(360001:380000,8));mean(Measures(540001:560000,8));mean(Measures(720001:740000,8));mean(Measures(900001:920000,8))];
av_t_t2 = [mean(Measures(20001:40000,8));mean(Measures(200001:220000,8));mean(Measures(380001:400000,8));mean(Measures(560001:580000,8));mean(Measures(740001:760000,8));mean(Measures(920001:940000,8))];
av_t_t3 = [mean(Measures(40001:60000,8));mean(Measures(220001:240000,8));mean(Measures(400001:420000,8));mean(Measures(580001:600000,8));mean(Measures(760001:780000,8));mean(Measures(940001:960000,8))];
av_t_t4 = [mean(Measures(60001:80000,8));mean(Measures(240001:260000,8));mean(Measures(420001:440000,8));mean(Measures(600001:620000,8));mean(Measures(780001:800000,8));mean(Measures(960001:980000,8))];
av_t_t5 = [mean(Measures(80001:100000,8));mean(Measures(260001:380000,8));mean(Measures(440001:460000,8));mean(Measures(620001:640000,8));mean(Measures(800001:820000,8));mean(Measures(980001:1000000,8))];
av_t_t6 = [mean(Measures(100001:120000,8));mean(Measures(280001:300000,8));mean(Measures(460001:480000,8));mean(Measures(640001:660000,8));mean(Measures(820001:840000,8));mean(Measures(1000001:1020000,8))];
av_t_t7 = [mean(Measures(120001:140000,8));mean(Measures(300001:320000,8));mean(Measures(480001:500000,8));mean(Measures(660001:680000,8));mean(Measures(840001:860000,8));mean(Measures(1020001:1040000,8))];
av_t_t8 = [mean(Measures(140001:160000,8));mean(Measures(320001:340000,8));mean(Measures(500001:520000,8));mean(Measures(680001:700000,8));mean(Measures(860001:880000,8));mean(Measures(1040001:1060000,8));];
av_t_t9 = [mean(Measures(160001:180000,8));mean(Measures(340001:360000,8));mean(Measures(520001:540000,8));mean(Measures(700001:720000,8));mean(Measures(880001:900000,8));mean(Measures(1060001:1080000,8))];
figure, plot(f,av_t_t1,'-o',f,av_t_t2,'-o',f,av_t_t3,'-o',f,av_t_t4,'-o',f,av_t_t5,'-o',f,av_t_t6,'-o',f,av_t_t7,'-o',f,av_t_t8,'-o',f,av_t_t9,'-o')
legend('threshold = -0.8','threshold = -0.6','threshold = -0.4','threshold = -0.2','threshold = 0','threshold = 0.2','threshold = 0.4','threshold = 0.6','threshold = 0.8');
xlabel('number of features');
ylabel('average tvalue');
title('Average Tvalue');

%other statistics with #features=10,threshold=0
figure, hist(Measures(260001:380000,2),20)
xlabel('degree');
ylabel('frequency of degree');
title('Degree Distribution');
figure, hist(Measures(260001:380000,4),20)
xlabel('average feature');
ylabel('frequency of average feature');
title('Average Feature Distribution');
figure, plot(Measures(260001:380000,2),Measures(260001:380000,3))
xlabel('degree');
ylabel('nearest neighbors average degree');
title('Degree VS Nearest Neighbors Average Degree');
figure, plot(Measures(260001:380000,4),Measures(260001:380000,6))
xlabel('average feature');
ylabel('nearest neighbors average average feature');
title('Average Feature VS Nearest Neighbors Average Average Feature');
figure, hist(Measures(260001:380000,5),20)
xlabel('average feature variance');
ylabel('frequency of average feature variance');
title('Average Feature Variance Distribution');
figure, plot(Measures(260001:380000,5),Measures(260001:380000,7))
xlabel('average feature variance');
ylabel('nearest neighbors average average feature variance');
title('Average Feature Variance VS Nearest Neighbors Average Average Feature Variance');