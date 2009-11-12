// non è (ancora) un file C ma serve per R

library(sna);
a <- scan("matrix.dat");
dim(a) <- c(100,100);
color <- c(rep(3,50), rep(2,50));
png("nomefigura.png");
gplot(a, vertex.col=color);
dev.off();
