p = 101325;
t = 25 + 273;
fi = 50;
pv = fi*6.1078*(10^((7.5*t-2048.625)/(t-35.85)))
pd = p - pv

ro = (pd/287.058 + pv/461.495)/t