
p_stat = 99302.02;
p_full = 99309.02;
t = 25 + 273;
fi = 50;
pv = fi*6.1078*(10^((7.5*t-2048.625)/(t-35.85)))
pd = p_stat - pv

ro = (pd/287.058 + pv/461.495)/t


p_dyn = p_full-p_stat

V = sqrt(2*p_dyn/ro)
