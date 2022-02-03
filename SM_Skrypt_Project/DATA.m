close all
clear all
clc

%% DATA
y = load("DATA.txt");
U = linspace(100,100,length(y)).';

G = tf(tf2.Numerator, tf2.Denominator);
step(G);