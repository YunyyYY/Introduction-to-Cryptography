function [r, s, t] = eea(a, b)
if a >= b
    r0 = b; r1 = a;
else
    r0 = a; r1 = b;
end
s0 = 0; s1 = 1;
t0 = 1; t1 = 0;
while r0 ~= 0
    q = floor(r1/r0);
    [r1, r0] = update(r0, r1 - q * r0);
    [s1, s0] = update(s0, s1 - q * s0);
    [t1, t0] = update(t0, t1 - q * t0);
end
r = r1;
s = s1;
t = t1;
disp([s1, s0])
disp([t1, t0])
end

function [a1, b1] = update(a, b)
a1 = a;
b1 = b;
end