clear;
load data1.txt
figure;
x = data1(1:20,2);
z = plot(x,data1(1:20,5),"rx-",x,data1(1:20,6),"g*-",x,data1(1:20,7),"bo-",x,data1(1:20,8),"md-",x,data1(1:20,9),"cp-");
set(gca,'fontsize',24);
title("Variation of entropy of binding with registers");
xlabel("Cores");
ylabel("Entropy");
set(gca,'fontsize',18);
legend("Initial Value",	"Random Value",	"Left Right Value",	"Center Center Value","Blossom Value",'location', 'south');
set (z,"linewidth", 3) ;
axis([5 110 0 1800]);
print -deps -color data1.eps

clear;
load data2.txt
figure;
x = data2(1:20,3);
z = plot(x,data2(1:20,5),"rx-",x,data2(1:20,6),"g*-",x,data2(1:20,7),"bo-",x,data2(1:20,8),"md-",x,data2(1:20,9),"cp-");
set(gca,'fontsize',24);
title("Variation of entropy of binding with phases");
xlabel("Phases");
ylabel("Entropy");
set(gca,'fontsize',18);
legend("Initial Value",	"Random Value",	"Left Right Value",	"Center Center Value","Blossom Value",'location', 'south');
set (z,"linewidth", 3) ;
axis([0 45 0 1800]);
print -deps -color data2.eps

clear;
load data3.txt
figure;
x = data3(1:20,4);
z = plot(x,data3(1:20,5),"rx-",x,data3(1:20,6),"g*-",x,data3(1:20,7),"bo-",x,data3(1:20,8),"md-",x,data3(1:20,9),"cp-");
set(gca,'fontsize',24);
title("Variation of entropy of binding with applications");
xlabel("Applications");
ylabel("Entropy");
set(gca,'fontsize',18);
legend("Initial Value",	"Random Value",	"Left Right Value",	"Center Center Value","Blossom Value",'location', 'south');
set (z,"linewidth", 3) ;
axis([2 25 0 600]);
print -deps -color data3.eps



